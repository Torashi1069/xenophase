#include "Common/Network.h"
#include "Common/Reporter.h"
#include "Common/Thread.h"
#include "Network3/CompletionPort.h"
#include "Network3/Process.h"
#include "Network3/Stream.h"
#include "Network3/StreamManager.h"


/// @see CStreamManager::ConnectThread
struct SVR_INFO
{
	/* this+  0 */ char m_pszIP[100];
	/* this+100 */ WORD m_wPort;
};


CStreamManager::CStreamManager()
{
	m_ListenSocket = INVALID_SOCKET;
	m_ListenPort = 0;
	m_bAcceptPermit = false;
	m_bPauseAccept = false;
	m_bProcessPermit = true;
	m_bMultiIPCheck = false;
	m_dwPingTime = 0;
	m_pStreams = NULL;
	m_nMAX_STREAM_NUM = 0;
	m_nFSNum = 0;
	m_dwClientCutLine = 0;
	m_dwTimeInterval = 0;
}


CStreamManager::~CStreamManager()
{
	this->CStreamManager::Destroy();

	if( m_pStreams != NULL )
	{
		delete[] m_pStreams;
		m_pStreams = NULL;
	}
}


void CStreamManager::Broadcast(char* pBuffer, int nLength)
{
	if( m_pStreams != NULL )
		for( int i = 0; i < m_nMAX_STREAM_NUM; ++i )
			if( m_pStreams[i].CStream::GetSessionID() != 0 )
				m_pStreams[i].m_pProcess->Send(pBuffer, nLength, 0, true);
}


//void CStreamManager::BroadcastExcept(CProcess* pProcess, char* pBuffer, int nLength)
//{
//	// not available
//}


bool CStreamManager::Create(std::list<CProcess*>& rProcessList, int SendQueueSize, int RecvBufSize, CCompletionPort* pCompletionPort, bool bDetailedCloseInfo)
{
	int ProcessObjNum = (int)rProcessList.size();
	if( ProcessObjNum < 1 || SendQueueSize < 2 || RecvBufSize < 2 )
		return false;

	this->CStreamManager::Destroy();

	if( m_pStreams != NULL )
	{
		delete[] m_pStreams;
		m_pStreams = NULL;
	}

	m_FreeStreamList.clear();
	InterlockedExchange(&m_nFSNum, 0);
	m_AllocStreamList.clear();

	m_pStreams = new CStream[ProcessObjNum];
	if( m_pStreams == NULL )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("%s - new CStream faied\n", __FUNCTION__);
		return false;
	}

	m_nMAX_STREAM_NUM = ProcessObjNum;

	for( int i = 0; i < m_nMAX_STREAM_NUM; ++i )
	{
		if( !m_pStreams[i].CStream::CreateRecvBuf(RecvBufSize)
		||  !m_pStreams[i].CStream::CreateSendQueue(SendQueueSize) )
		{
			delete[] m_pStreams;
			m_pStreams = NULL;
			m_nMAX_STREAM_NUM = 0;
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("%s - stream buffer creation failed\n", __FUNCTION__);
			return false;
		}
	}

	int i;
	std::list<CProcess*>::iterator it;
	for( i = 0, it = rProcessList.begin(); it != rProcessList.end(); ++i, ++it )
	{
		CProcess* p = *it;
		CStream* s = &m_pStreams[i];

		p->CProcess::SetStream(s);
		s->CStream::SetProcessObj(p, bDetailedCloseInfo);
		m_FreeStreamList.push_back(s);
		InterlockedIncrement(&m_nFSNum);
	}

	m_pCompletionPort = pCompletionPort;
	m_bAcceptPermit = true;
	m_bProcessPermit = true;
	return true;
}


void CStreamManager::Destroy()
{
	m_bAcceptPermit = false;

	Sleep(100);

	if( m_ListenSocket != INVALID_SOCKET )
	{
		closesocket(m_ListenSocket);
		m_ListenSocket = INVALID_SOCKET;
	}

	Sleep(100);

	if( m_pStreams != NULL )
	{
		for( int i = 0; i < m_nMAX_STREAM_NUM; ++i )
			m_pStreams[i].CStream::Close(100);

		Sleep(1000);
		m_bProcessPermit = false;
		Sleep(500);
	}
}


bool CStreamManager::Listen(WORD port, int nBackLog, DWORD dwPingTime, DWORD dwListenIP)
{
	if( m_pStreams == NULL )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("%s - m_pStreams is 0\n", __FUNCTION__);
		return false;
	}

	m_ListenPort = port;
	m_dwPingTime = dwPingTime;
	m_ListenSocket = WSASocketA(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);

	if( m_ListenSocket == INVALID_SOCKET )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("%s port %d create listen socket error - %d\n", __FUNCTION__, port, WSAGetLastError());
		return false;
	}

	sockaddr_in sa = {};
	sa.sin_family = AF_INET;
	sa.sin_port = htons(port);
	sa.sin_addr.s_addr = dwListenIP;

	if( bind(m_ListenSocket, (sockaddr*)&sa, sizeof(sa)) != 0 )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("%s - port %d bind error, gle - %d\n", __FUNCTION__, port, WSAGetLastError());
		return false;
	}

	if( listen(m_ListenSocket, nBackLog) != 0 )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("%s - port %d backlog %d listen error, gle - %d\n", __FUNCTION__, port, nBackLog, WSAGetLastError());
		return false;
	}

	if( (HANDLE)CreateMemberThread<CStreamManager>(this, &CStreamManager::AcceptThread, NULL) == INVALID_HANDLE_VALUE )
	{
		if( errno == EAGAIN )
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CreateMemberThread< CStreamManager > AcceptThread fail! errno EAGAIN(%d)", errno);
		else if( errno == EINVAL )
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CreateMemberThread< CStreamManager > AcceptThread fail! errno EINVAL(%d)", errno);
		else
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CreateMemberThread< CStreamManager > AcceptThread fail! errno %d", errno);

		return false;
	}

	return true;
}


void CStreamManager::AcceptThread(void* lpParam)
{
	m_bPauseAccept = false;

	while( m_bAcceptPermit )
	{
		while( m_bPauseAccept && m_bAcceptPermit && m_bProcessPermit )
			Sleep(10);

		fd_set rfds;
		fd_set efds;
		FD_ZERO(&rfds);
		FD_ZERO(&efds);
		FD_SET(m_ListenSocket, &rfds);
		FD_SET(m_ListenSocket, &efds);

		timeval tv;
		tv.tv_sec = 0;
		tv.tv_usec = 500;

		if( select(FD_SETSIZE, &rfds, NULL, &efds, &tv) == SOCKET_ERROR )
		{
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("%s - select error wsagle: %d\n", __FUNCTION__, WSAGetLastError());
			break;
		}

		if( FD_ISSET(m_ListenSocket, &efds) )
		{
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("%s - exception is set\n", __FUNCTION__);
			break;
		}

		if( FD_ISSET(m_ListenSocket, &rfds) )
		{
			sockaddr_in sa_client;
			int sa_len = sizeof(sa_client);

			SOCKET client_socket = accept(m_ListenSocket, (sockaddr*)&sa_client, &sa_len);
			if( client_socket == INVALID_SOCKET )
			{
				if( m_bAcceptPermit )
					CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("%s - port %d accept error, wsagle - %d\n", __FUNCTION__, m_ListenPort, WSAGetLastError());

				this->CStreamManager::ArrangeStreams();
				continue;
			}

			linger li;
			li.l_onoff = 1;
			li.l_linger = 0;

			if( setsockopt(client_socket, SOL_SOCKET, SO_LINGER, (const char*)&li, sizeof(li)) != 0 )
			{
				CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("%s - setsockopt SO_LINGER failed, wsagle - %d\n", __FUNCTION__, WSAGetLastError());
				closesocket(client_socket);
				this->CStreamManager::ArrangeStreams();
				continue;
			}

			if( m_FreeStreamList.begin() == m_FreeStreamList.end() )
			{
				CSingleton<CReporter>::getSingletonPtr()->CReporter::MessagePrint("MAX CLIENT %u \n", timeGetTime());
				closesocket(client_socket);
				this->CStreamManager::ArrangeStreams();
				continue;
			}

			CStream* pStream = m_FreeStreamList.front();
			m_FreeStreamList.pop_front();
			InterlockedDecrement(&m_nFSNum);

			pStream->CStream::AddRef();
			pStream->CStream::SetConnected(true);
			m_AllocStreamList.push_back(pStream);

			DWORD dwError;
			if( m_pCompletionPort->CCompletionPort::AssociateSocket(client_socket, (DWORD)pStream, dwError) == NULL )
			{
				closesocket(client_socket);
				pStream->CStream::SubRef();
				CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("%s - AssociateSocket failed gle %d, port %d\n", __FUNCTION__, dwError, m_ListenPort);
				continue;
			}

			pStream->CStream::Init(client_socket, sa_client.sin_addr.s_addr, m_dwPingTime);
		}

		this->CStreamManager::ArrangeStreams();
		this->CStreamManager::CheckDOSIP();
	}

	while( m_bProcessPermit )
	{
		this->CStreamManager::ArrangeStreams();
		Sleep(10);
	}
}


//void CStreamManager::SetDOSCheck(DWORD dwClientCutLine, DWORD dwTimeInterval)
//{
//	// not available
//}


BOOL CStreamManager::CheckDOSIP()
{
	static DWORD dwNowTime;
	static DWORD dwLastTime;

	if( !m_bMultiIPCheck || m_dwTimeInterval == 0 || m_dwClientCutLine == 0 )
		return TRUE; // DOS checking disabled.

	dwNowTime = timeGetTime();

	if( dwNowTime <= dwLastTime + m_dwTimeInterval )
		return TRUE;

	if( this->CStreamManager::GetConnectionCount() <= static_cast<int>(m_dwClientCutLine) )
		return TRUE;

	dwLastTime = timeGetTime();

	typedef struct tag_DOSData
	{
		/* this+0 */ DWORD dwIP;
		/* this+4 */ long count;

	} DOSData;

	stdext::hash_map<DWORD,DOSData> data;
	for( int i = 0; i < m_nMAX_STREAM_NUM; ++i )
	{
		CStream* pStream = &m_pStreams[i];

		if( pStream->CStream::GetSessionID() == 0 )
			continue;

		stdext::hash_map<DWORD,DOSData>::iterator it = data.find(pStream->CStream::GetIP());
		if( it == data.end() )
		{
			DOSData one_data;
			one_data.dwIP = pStream->CStream::GetIP();
			one_data.count = 1;
			data[one_data.dwIP] = one_data;
		}
		else
		{
			DOSData one_data;
			one_data.dwIP = it->second.dwIP;
			one_data.count = it->second.count + 1;
			data.erase(it);
			data[one_data.dwIP] = one_data;
		}
	}

	for( stdext::hash_map<DWORD,DOSData>::const_iterator it = data.begin(); it != data.end(); ++it )
	{
		if( it->second.count > 1 )
		{
			char szIP[16];
			CSingleton<CNetwork>::getSingletonPtr()->CNetwork::GetTextIP(it->second.dwIP, szIP);
			CSingleton<CReporter>::getSingletonPtr()->CReporter::FilePrint("DOSIP.txt", "IP: %s\tCount: %d", szIP, it->second.count);
		}
	}

	return TRUE;
}


int CStreamManager::ArrangeStreams()
{
	int arrange_count = 0;

	std::list<CStream*>::iterator it = m_AllocStreamList.begin();
	while( it != m_AllocStreamList.end() )
	{
		CStream* pStream = *it;

		if( pStream->CStream::GetRef() != 0 )
		{// active stream
			pStream->CStream::CheckPingTime();
			++it;
		}
		else
		{// closed stream
			it = m_AllocStreamList.erase(it);
			pStream->CStream::SetConnected(false);
			m_FreeStreamList.push_back(pStream);
			InterlockedIncrement(&m_nFSNum);
			++arrange_count;
		}
	}

	return arrange_count;
}


int CStreamManager::GetConnectionCount()
{
	int nCount = 0;

	if( m_pStreams != NULL )
		for( int i = 0; i < m_nMAX_STREAM_NUM; ++i )
			if( m_pStreams[i].CStream::GetSessionID() != 0 )
				++nCount;

	return nCount;
}


LONG CStreamManager::GetFreeStreamNum()
{
	return m_nFSNum;
}


void CStreamManager::PauseAccept()
{
	m_bPauseAccept = true;
}


void CStreamManager::ResumeAccept()
{
	m_bPauseAccept = false;
}


bool CStreamManager::IsAcceptPaused()
{
	return m_bPauseAccept;
}


bool CStreamManager::Connect(const char* szIP, WORD wPort, DWORD dwPingTime)
{
	SVR_INFO* info = new SVR_INFO;
	if( info == NULL )
		return false;

	memset(info, 0, sizeof(*info));
	strcpy(info->m_pszIP, szIP);
	info->m_wPort = wPort;

	if( m_pStreams == NULL )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("%s - m_pStreams is 0\n", __FUNCTION__);
		return false;
	}

	m_dwPingTime = dwPingTime;

	if( (HANDLE)CreateMemberThread<CStreamManager>(this, &CStreamManager::ConnectThread, info) == INVALID_HANDLE_VALUE )
	{
		if( errno == EAGAIN )
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CreateMemberThread< CStreamManager > ConnectThread fail! errno EAGAIN(%d)", errno);
		else if( errno == EINVAL )
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CreateMemberThread< CStreamManager > ConnectThread fail! errno EINVAL(%d)", errno);
		else
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CreateMemberThread< CStreamManager > ConnectThread fail! errno %d", errno);

		return false;
	}

	return true;
}


void CStreamManager::ConnectThread(void* lpParam)
{
	SVR_INFO SvrInfo = *reinterpret_cast<SVR_INFO*>(lpParam);
	delete lpParam;

	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("start connecting %s:%d\n", SvrInfo.m_pszIP, SvrInfo.m_wPort);

	while( m_bProcessPermit )
	{
		Sleep(10);

		if( m_AllocStreamList.size() != 0 )
		{
			this->CStreamManager::ArrangeStreams();
			Sleep(10);
			continue;
		}

		if( m_FreeStreamList.size() <= 0 )
			continue;

		SOCKET s = WSASocketA(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
		if( s == INVALID_SOCKET )
			continue;

		sockaddr_in server_addr = {};
		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.s_addr = CSingleton<CNetwork>::getSingletonPtr()->CNetwork::GetDWORDIP(SvrInfo.m_pszIP);
		server_addr.sin_port = htons(SvrInfo.m_wPort);

		if( connect(s, (sockaddr*)&server_addr, sizeof(server_addr)) != 0 )
		{
			if( closesocket(s) != 0 )
				CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("%s - closesocket error, wsagle %d", __FUNCTION__, WSAGetLastError());

			continue;
		}

		linger li;
		li.l_onoff = 1;
		li.l_linger = 0;

		if( setsockopt(s, SOL_SOCKET, SO_LINGER, (char*)&li, sizeof(li)) != 0 )
		{
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("%s - setsockopt SO_LINGER failed, wsagle - %d\n", __FUNCTION__, WSAGetLastError());
			closesocket(s);
			this->CStreamManager::ArrangeStreams();
			continue;
		}

		int nZero = 0;
		if( setsockopt(s, SOL_SOCKET, SO_SNDBUF, (char*)&nZero, sizeof(nZero)) != 0 )
		{
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("%s - setsockopt SO_SNDBUF failed, wsagle - %d\n", __FUNCTION__, WSAGetLastError());
			closesocket(s);
			this->CStreamManager::ArrangeStreams();
			continue;
		}

		std::list<CStream*>::iterator it = m_FreeStreamList.begin();
		if( it == m_FreeStreamList.end() )
		{
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("%s - m_FreeStreamList is empty!!!!\n", __FUNCTION__);
			closesocket(s);
			this->CStreamManager::ArrangeStreams();
			continue;
		}

		CStream* pStream = *it;
		m_FreeStreamList.erase(it);
		InterlockedDecrement(&m_nFSNum);
		pStream->CStream::AddRef();
		pStream->CStream::SetConnected(true);
		m_AllocStreamList.push_back(pStream);

		DWORD dwError;
		if( !m_pCompletionPort->CCompletionPort::AssociateSocket(s, (DWORD)pStream, dwError) )
		{
			closesocket(s);
			pStream->CStream::SubRef();
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("%s - AssociateSocket failed gle %d\n", __FUNCTION__, dwError);
			continue;
		}

		pStream->CStream::Init(s, server_addr.sin_addr.s_addr, m_dwPingTime);
	}

	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("end connecting %s:%d\n", SvrInfo.m_pszIP, SvrInfo.m_wPort);
	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("thread %s OUT\n", __FUNCTION__);
}
