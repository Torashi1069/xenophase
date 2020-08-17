#include "Common/Reporter.h"
#include "Common/Thread.h"
#include "Network2/Process.h"
#include "Network2/StreamManager.h"


/// @see CStreamManager::ConnectThread
struct SVR_INFO
{
	/* this+  0 */ char m_pszIP[100];
	/* this+100 */ WORD m_wPort;
};


/// @see CStreamManager::ProcessThread
struct PROCESS_INFO
{
	/* this+0 */ int first;
	/* this+4 */ int second;
	/* this+8 */ int index;
};


CStreamManager::CStreamManager()
{
	m_ListenSocket = INVALID_SOCKET;
	m_ListenPort = 0;
	m_bAcceptPermit = false;
	m_bPauseAccept = false;
	m_bProcessPermit = true;
	m_dwPingTime = 0;
	m_pStreams = NULL;
	m_nMAX_STREAM_NUM = 0;
	m_bArrangeThreadStarted = false;
	m_csFSQ = NULL;
	m_FSQ = NULL;
}


CStreamManager::~CStreamManager()
{
	this->CStreamManager::Destroy();

	if( m_pStreams != NULL )
	{
		delete[] m_pStreams;
		m_pStreams = NULL;
	}

	if( m_csFSQ != NULL )
	{
		delete[] m_csFSQ;
		m_csFSQ = NULL;
	}

	if( m_FSQ != NULL )
	{
		delete[] m_FSQ;
		m_FSQ = NULL;
	}
}


void CStreamManager::Broadcast(char* pBuffer, int nLength)
{
	if( m_pStreams != NULL )
		for( int i = 0; i < m_nMAX_STREAM_NUM; ++i )
			if( m_pStreams[i].CStream::GetSessionID() != 0 )
				m_pStreams[i].m_pProcess->Send(pBuffer, nLength, 0, true);
}


void CStreamManager::Init()
{
	if( m_pStreams != NULL )
	{
		delete[] m_pStreams;
		m_pStreams = NULL;
	}

	if( m_csFSQ != NULL )
	{
		delete[] m_csFSQ;
		m_csFSQ = NULL;
	}

	if( m_FSQ != NULL )
	{
		delete[] m_FSQ;
		m_FSQ = NULL;
	}

	m_nFSNum = 0;
}


bool CStreamManager::Create(std::list<CProcess*>& rProcessList, int SendQueueSize, int RecvQueueSize, int RecvBufSize, bool bDetailedCloseInfo)
{
	int ProcessObjNum = (int)rProcessList.size();
	if( ProcessObjNum < 1 || SendQueueSize < 2 || RecvQueueSize < 2 || RecvBufSize < 2 )
		return false;

	this->CStreamManager::Init();
	m_bRefuseAccept = false;

	m_pStreams = new CStream[ProcessObjNum];
	if( m_pStreams == NULL )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CStreamManager::Create - new CStream faied\n");
		return false;
	}

	m_nMAX_STREAM_NUM = ProcessObjNum;

	for( int i = 0; i < m_nMAX_STREAM_NUM; ++i )
	{
		if( !m_pStreams[i].CStream::Create_RecvBuf_RecvQueue(RecvBufSize, RecvQueueSize)
		||  !m_pStreams[i].CStream::CreateSendQueue(SendQueueSize) )
		{
			delete[] m_pStreams;
			m_pStreams = NULL;
			m_nMAX_STREAM_NUM = 0;
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CStreamManager::Create - stream buffer creation failed\n");
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
	}

	m_bAcceptPermit = true;
	m_bProcessPermit = true;
	return true;
}


void CStreamManager::Destroy()
{
	m_bAcceptPermit = false;

	Sleep(500);

	closesocket(m_ListenSocket);

	if( m_pStreams != NULL )
	{
		for( int i = 0; i < m_nMAX_STREAM_NUM; ++i )
			m_pStreams[i].CStream::Close(300);

		Sleep(2000);
		m_bProcessPermit = false;
		Sleep(500);
	}
}


bool CStreamManager::Listen(WORD port, int nBackLog, DWORD dwPingTime, int nWorkerThreadNum, int nRefuseLow, int nRefuseHigh, DWORD dwBindIP)
{
	if( m_pStreams == NULL )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CStreamManager::Listen - m_pStreams is 0\n");
		return false;
	}

	if( m_CompletionPort.CCompletionPort::GetThreadNum() > 0 )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CStreamManager::Listen port %d - m_CompletionPort.GetThreadNum() > 0\n", port);
		return false;
	}

	if( !m_CompletionPort.CCompletionPort::Create(nWorkerThreadNum) )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CStreamManager::Listen port %d - m_CompletionPort.Create failed\n", port);
		return false;
	}

	m_nRefuseLow = nRefuseLow;
	m_nRefuseHigh = nRefuseHigh;
	m_ListenPort = port;
	m_dwPingTime = dwPingTime;
	m_ListenSocket = WSASocketA(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);

	if( m_ListenSocket == INVALID_SOCKET )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CStreamManager::Listen port %d create listen socket error - %d\n", port, WSAGetLastError());
		return false;
	}

	sockaddr_in sa = {};
	sa.sin_family = AF_INET;
	sa.sin_port = htons(port);
	sa.sin_addr.s_addr = dwBindIP;

	if( bind(m_ListenSocket, (sockaddr*)&sa, sizeof(sa)) != 0 )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("port %d bind error, gle - %d\n", port, WSAGetLastError());
		return false;
	}

	if( listen(m_ListenSocket, nBackLog) != 0 )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("port %d backlog %d listen error, gle - %d\n", port, nBackLog, WSAGetLastError());
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
	DWORD dwTime = timeGetTime();
	int nIndexFSQ = 0;
	m_bRefuseAccept = false;
	m_bPauseAccept = false;

	while( m_bProcessPermit )
	{
		if( m_bPauseAccept )
		{
			if( !m_bAcceptPermit || !m_bProcessPermit )
				break;

			Sleep(10);
			continue;
		}

		if( m_bRefuseAccept )
		{
			Sleep(1000);

			if( this->CStreamManager::GetConnectionCount() < m_nRefuseLow )
				m_bRefuseAccept = false;

			continue;
		}

		if( timeGetTime() - dwTime > 1000 )
		{
			dwTime = timeGetTime();

			if( this->CStreamManager::GetConnectionCount() > m_nRefuseHigh )
			{
				m_bRefuseAccept = true;
				CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("----- Refuse Accepting...\n");
			}
		}

		sockaddr_in sa_client = {};
		int sa_len = sizeof(sa_client);

		SOCKET s = accept(m_ListenSocket, (sockaddr*)&sa_client, &sa_len);
		if( s == INVALID_SOCKET )
		{
			if( m_bAcceptPermit )
				CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("port %d accept error, gle - %d\n", m_ListenPort, WSAGetLastError());

			continue;
		}

		linger li;
		li.l_onoff = 1;
		li.l_linger = 0;

		if( setsockopt(s, SOL_SOCKET, SO_LINGER, (char*)&li, sizeof(li)) != 0 )
		{
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("setsockopt SO_LINGER failed, gle - %d\n", WSAGetLastError());
			closesocket(s);
			continue;
		}

		if( !m_bAcceptPermit )
		{
			closesocket(s);
			break;
		}

		CStream* pStream = NULL;
		int cnt;
		for( cnt = 0; pStream == NULL && cnt <= m_nProcessThreadNum; ++cnt )
		{
			nIndexFSQ = (nIndexFSQ + 1) % m_nProcessThreadNum; // next index, with wraparound

			m_csFSQ[nIndexFSQ].Enter();

			if( m_FSQ[nIndexFSQ].size() != 0 )
			{
				pStream = m_FSQ[nIndexFSQ].front();
				m_FSQ[nIndexFSQ].pop();
				InterlockedDecrement(&m_nFSNum);
			}

			m_csFSQ[nIndexFSQ].Leave();
		}

		if( pStream == NULL && cnt > m_nProcessThreadNum )
		{
			CSingleton<CReporter>::getSingletonPtr()->CReporter::MessagePrint("MAX CLIENTS !!! time %u\n", timeGetTime());
			closesocket(s);
			continue;
		}

		pStream->AddRef();
		pStream->SetConnected(true);

		DWORD dwError;
		if( !m_CompletionPort.CCompletionPort::AssociateSocket(s, (DWORD)pStream, dwError) )
		{
			closesocket(s);
			pStream->CStream::SubRef();
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("AssociateSocket failed gle %d, port %d\n", dwError, m_ListenPort);
			continue;
		}

		pStream->CStream::Init(s, sa_client.sin_addr.s_addr, m_dwPingTime);
	}

	m_ListenSocket = INVALID_SOCKET;
	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("AcceptThread out, port %d\n", m_ListenPort);
}


bool CStreamManager::StartProcessing(int nProcessThreadNum, int nSleepRatio, int nThreadPriority)
{
	if( m_pStreams == NULL )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CStreamManager::StartProcessing - m_pStreams is NULL\n");
		return false;
	}

	if( nProcessThreadNum <= 0 || nProcessThreadNum > 1000 )
		return false;

	int div = m_nMAX_STREAM_NUM / nProcessThreadNum;
	int mod = m_nMAX_STREAM_NUM % nProcessThreadNum;
	m_nProcessThreadNum = nProcessThreadNum;
	m_nRunningProcessNum = 0;

	m_csFSQ = new CCriticalSection[nProcessThreadNum];
	if( m_csFSQ == NULL )
		return false;

	m_FSQ = new std::queue<CStream*,std::list<CStream*>>[m_nProcessThreadNum];
	if( m_FSQ == NULL )
		return false;

	m_nSleepRatio = max(1, nSleepRatio);

	int start = 0;
	int end = 0;
	for( int i = 0; i < nProcessThreadNum; ++i )
	{
		PROCESS_INFO* pProcessInfo = new PROCESS_INFO;
		if( pProcessInfo == NULL )
			return false;

		end = start + div + mod * (i == 0);

		pProcessInfo->first = start;
		pProcessInfo->second = end;
		pProcessInfo->index = i;

		for( int j = 0; j < end - start; ++j )
		{
			m_csFSQ[i].Enter();
			m_FSQ[i].push(&m_pStreams[start]);
			m_csFSQ[i].Leave();

			InterlockedIncrement(&m_nFSNum);
		}

		HANDLE hThread = (HANDLE)CreateMemberThread<CStreamManager>(this, &CStreamManager::ProcessThread, pProcessInfo);
		if( hThread == INVALID_HANDLE_VALUE )
		{
			if( errno == EAGAIN )
				CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CreateMemberThread< CStreamManager > ProcessThread fail! errno EAGAIN(%d)", errno);
			else
			if( errno == EINVAL )
				CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CreateMemberThread< CStreamManager > ProcessThread fail! errno EINVAL(%d)", errno);
			else
				CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CreateMemberThread< CStreamManager > ProcessThread fail! errno %d", errno);

			return false;
		}

		if( nThreadPriority )
		{
			if( !SetThreadPriority(hThread, nThreadPriority) )
				CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("SetThreadPriority %d failed\n", nThreadPriority);
		}

		CloseHandle(hThread);

		start = end;
	}

	return true;
}


void CStreamManager::ProcessThread(void* lpParam)
{
	PROCESS_INFO process_info = *reinterpret_cast<PROCESS_INFO*>(lpParam);
	delete lpParam;

	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("ProcessThread %d %d IN\n", process_info.first, process_info.second);

	InterlockedIncrement(&m_nRunningProcessNum);

	while( m_bProcessPermit )
	{
		InterlockedDecrement(&m_nRunningProcessNum);

		for( int i = process_info.first; i < process_info.second; ++i )
		{
			CStream& stream = m_pStreams[i];

			DWORD SID = stream.GetSessionID();
			if( SID != 0 )
			{
				if( stream.CStream::IsRecvPermit() )
				{
					if( !stream.m_pProcess->Process() )
						stream.CStream::CloseOuter(SID, 0);
				}
			}

			if( stream.CStream::IsConnected() )
			{
				if( stream.GetRef() )
				{
					stream.CStream::CheckPingTime();
				}
				else
				{
					stream.CStream::SetConnected(false);

					m_csFSQ[process_info.index].Enter();
					m_FSQ[process_info.index].push(&stream);
					m_csFSQ[process_info.index].Leave();

					InterlockedIncrement(&m_nFSNum);
				}
			}
		}

		InterlockedIncrement(&m_nRunningProcessNum);

		if( m_nSleepRatio == 1 || timeGetTime() % m_nSleepRatio == 0 )
			Sleep(1);
	}

	InterlockedDecrement(&m_nRunningProcessNum);
	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("ProcessThread %d %d OUT\n", process_info.first, process_info.second);
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


int CStreamManager::GetWorkerThreadNum()
{
	return m_CompletionPort.CCompletionPort::GetThreadNum();
}


int CStreamManager::GetRunningWorkerThreadNum()
{
	return m_CompletionPort.CCompletionPort::GetRunningThreadNum();
}


LONG CStreamManager::GetFreeStreamNum()
{
	return m_nFSNum;
}


// not available
//bool CStreamManager::Connect(const char* szIP, WORD wPort, int _unknown, DWORD dwPingTime)
//{
//}


// not available
//void CStreamManager::ConnectThread(void* lpParam)
//{
//	SVR_INFO SvrInfo = *reinterpret_cast<SVR_INFO*>(lpParam);
//	delete lpParam;
//
//}
