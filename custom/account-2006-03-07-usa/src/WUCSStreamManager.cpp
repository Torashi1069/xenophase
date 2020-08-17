#include "WUCSStreamManager.h"
#include "Common/Network.h"
#include "Common/Reporter.h"
#include "Common/Thread.h"


CWUCSStreamManager::CWUCSStreamManager()
{
}


CWUCSStreamManager::~CWUCSStreamManager()
{
}


bool CWUCSStreamManager::Connect(const char* szIP, const char* szSecIP, unsigned short wPort, int nWorkerThreadNum, unsigned long dwPingTime)
{
	WUCS_SVR_INFO* info = new WUCS_SVR_INFO;
	if( info == NULL )
		return false;

	memset(info, 0, sizeof(*info));
	strcpy(info->m_pszIP, szIP);
	strcpy(info->m_pszSecIP, szSecIP);
	info->m_wPort = wPort;

	if( m_pStreams == NULL )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CStreamManager::Listen - m_pStreams is 0\n");
		return false;
	}

	if( m_CompletionPort.CCompletionPort::GetThreadNum() > 0 )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CStreamManager::Listen port %d - m_CompletionPort.GetThreadNum() > 0\n", wPort);
		return false;
	}

	if( !m_CompletionPort.CCompletionPort::Create(nWorkerThreadNum) )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CStreamManager::Listen port %d - m_CompletionPort.Create failed\n", wPort);
		return false;
	}

	m_dwPingTime = dwPingTime;

	if( (HANDLE)CreateMemberThread<CWUCSStreamManager>(this, &CWUCSStreamManager::ConnectThread, info) == INVALID_HANDLE_VALUE )
	{
		if( errno == EAGAIN )
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CreateMemberThread< CStreamManager > ConnectThread fail! errno EAGAIN(%d)", errno);
		else
		if( errno == EINVAL )
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CreateMemberThread< CStreamManager > ConnectThread fail! errno EINVAL(%d)", errno);
		else
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CreateMemberThread< CStreamManager > ConnectThread fail! errno %d", errno);

		return false;
	}

	return true;
}


void CWUCSStreamManager::ConnectThread(void* lpParam)
{
	WUCS_SVR_INFO SvrInfo;
	memcpy(&SvrInfo, lpParam, sizeof(SvrInfo));
	delete lpParam;

	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("start connecting %s:%d\n", SvrInfo.m_pszIP, SvrInfo.m_wPort);

	while( m_bProcessPermit )
	{
		m_csFSQ->Enter();

		if( m_FSQ->size() == 0 )
		{
			m_csFSQ->Leave();
			Sleep(1000);
			continue;
		}

		m_csFSQ->Leave();

		SOCKET s = WSASocketA(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
		if( s == INVALID_SOCKET )
			continue;

		// [patch] bind outgoing socket to private ip
		sockaddr_in bind_addr = {};
		bind_addr.sin_family = AF_INET;
		bind_addr.sin_addr.s_addr = CSingleton<CNetwork>::getSingletonPtr()->CNetwork::GetLocalIP(false);
		bind_addr.sin_port = htons(0);
		if( bind(s, (sockaddr*)&bind_addr, sizeof(bind_addr)) != 0 )
		{
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CWUCSStreamManager::ConnectThread - bind error, wsagle %d", WSAGetLastError());
			closesocket(s);
			continue;
		}

		sockaddr_in server_addr = {};
		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.s_addr = CSingleton<CNetwork>::getSingletonPtr()->CNetwork::GetDWORDIP(SvrInfo.m_pszIP);
		server_addr.sin_port = htons(SvrInfo.m_wPort);

		sockaddr_in sec_server_addr = {};
		sec_server_addr.sin_family = AF_INET;
		sec_server_addr.sin_addr.s_addr = CSingleton<CNetwork>::getSingletonPtr()->CNetwork::GetDWORDIP(SvrInfo.m_pszSecIP);
		sec_server_addr.sin_port = htons(SvrInfo.m_wPort);

		if( connect(s, (sockaddr*)&server_addr, sizeof(server_addr)) != 0
		&&  connect(s, (sockaddr*)&sec_server_addr, sizeof(sec_server_addr)) != 0 )
		{
			if( closesocket(s) != 0 )
				CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CWUCSStreamManager::ConnectThread - closesocket error, wsagle %d", WSAGetLastError());

			continue;
		}

		char tmp[16];
		memcpy(tmp, SvrInfo.m_pszIP, 16);
		memcpy(SvrInfo.m_pszIP, SvrInfo.m_pszSecIP, 16);
		memcpy(SvrInfo.m_pszSecIP, tmp, 16);

		m_csFSQ->Enter();

		if( m_FSQ->size() == 0 )
		{
			m_csFSQ->Leave();

			if( closesocket(s) != 0 )
				CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CWUCSStreamManager::ConnectThread - closesocket error, wsagle %d", WSAGetLastError());

			Sleep(500);
			continue;
		}

		CStream* strm = m_FSQ->front();
		m_FSQ->pop();
		
		m_csFSQ->Leave();

		InterlockedDecrement(&m_nFSNum);
		strm->CStream::AddRef();
		strm->CStream::SetConnected(true);

		unsigned long ulError = 0;
		if( m_CompletionPort.CCompletionPort::AssociateSocket(s, (unsigned long)strm, ulError) == 0 )
		{
			closesocket(s);
			strm->CStream::SubRef();
			continue;
		}

		strm->CStream::Init(s, server_addr.sin_addr.s_addr, m_dwPingTime);
	}

	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("end connecting %s:%d\n", SvrInfo.m_pszIP, SvrInfo.m_wPort);
}
