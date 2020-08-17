#include "ServerManager/CMsvrAcceptThread.h"
#include "ServerManager/CMsvrMgr.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/NOutputTextMgr.h"
#include "shared/NSystem/NIPAddr.h"
#include "shared/N3System/N3MessageMgr.h"


/// singleton instance
CMsvrAcceptThread*& CMsvrAcceptThread::m_cpSelf = VTOR<CMsvrAcceptThread*>(DetourFindFunction(EXEPATH(), "CMsvrAcceptThread::m_cpSelf"));


CMsvrAcceptThread::CMsvrAcceptThread(const unsigned long in_IPaddr, const short in_Port)
: N3Thread("CMsvrAcceptThread"), m_Socket(INVALID_SOCKET), m_IPaddr(in_IPaddr), m_Port(in_Port)
{
	m_bOK = false;

	if( this->CMsvrAcceptThread::Create() )
		m_bOK = true;
}


CMsvrAcceptThread::~CMsvrAcceptThread()
{
	this->CMsvrAcceptThread::Destory();
}


bool CMsvrAcceptThread::Create()
{
	m_Socket = WSASocketA(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if( m_Socket == INVALID_SOCKET )
	{
		MessageBoxA(NULL, "WSASocket() failed: listener", "error", MB_OK);
		return false;
	}

	sockaddr_in hostAddr = {};
	hostAddr.sin_family = AF_INET;
	hostAddr.sin_addr.s_addr = m_IPaddr;
	hostAddr.sin_port = htons(m_Port);

	if( bind(m_Socket, (sockaddr*)&hostAddr, sizeof(hostAddr)) == SOCKET_ERROR )
	{
		MessageBoxA(NULL, "bind() failed: listener", "error", MB_OK);
		return false;
	}

	if( listen(m_Socket, 20) == SOCKET_ERROR )
	{
		MessageBoxA(NULL, "listen() failed: listener", "error", MB_OK);
		return false;
	}

	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("[listen] ServerManager %s:%d", NIPAddapter(NIPAddr(m_IPaddr)), m_Port);
	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[listen] ServerManager %s:%d", NIPAddapter(NIPAddr(m_IPaddr)), m_Port);

	return true;
}


void CMsvrAcceptThread::Destory()
{
	if( m_Socket != INVALID_SOCKET )
	{
		closesocket(m_Socket);
		m_Socket = INVALID_SOCKET;
	}
}


bool CMsvrAcceptThread::CreateInstance(NIPAddr in_IPAddr, int in_Port)
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CMsvrAcceptThread(in_IPAddr, in_Port);
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CMsvrAcceptThread::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CMsvrAcceptThread::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CMsvrAcceptThread* CMsvrAcceptThread::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CMsvrAcceptThread::isOK() const
{
	return m_bOK;
}


bool CMsvrAcceptThread::Start()
{
	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("MGR wait %s(%d)", NIPAddapter(NIPAddr(m_IPaddr)), m_Port);
	return this->N3Thread::Begin();
}


void CMsvrAcceptThread::Stop()
{
	this->N3Thread::End();
}


unsigned int CMsvrAcceptThread::ThreadFunction()
{
	while( 1 )
	{
		if( WaitForSingleObject(m_MessageQueue.N3MessageQueue::GetEventObj(), 0) == WAIT_OBJECT_0 )
		{
			N3MessageQueue::RETGET ret = m_MessageQueue.N3MessageQueue::Get();
			if( std::tr1::get<0>(ret) == true )
			{
				unsigned int Message = std::tr1::get<1>(ret);
				switch( Message )
				{
				case N3MSGID(CMsvrAcceptThread,MSG_REQ_THREAD_QUIT):
				{
					return 0;
				}
				break;
				default:
				{
					NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "unknown message receive(Msg:0x%X)", Message);
				}
				break;
				};
			}
		}

		fd_set tempfdset;
		FD_ZERO(&tempfdset);
		FD_SET(m_Socket, &tempfdset);

		timeval timeout;
		timeout.tv_sec = 0;
		timeout.tv_usec = 10000;

		int ret = select(1, &tempfdset, NULL, NULL, &timeout);
		if( ret == SOCKET_ERROR || ret <= 0 || !FD_ISSET(m_Socket, &tempfdset) )
			continue;

		sockaddr_in remoteAddr = {};
		int sockLen = sizeof(remoteAddr);

		SOCKET s = WSAAccept(m_Socket, (sockaddr*)&remoteAddr, &sockLen, NULL, NULL);
		if( s == INVALID_SOCKET )
			continue;

		N3MessageMgr::GetObj()->N3MessageMgr::Post(CMsvrMgr::GetObj()->N3Object::GetMyID(), N3MSGID(CMsvrMgr,MSG_MSVR_ACCEPT), s, remoteAddr.sin_addr.s_addr);
	}
}


void CMsvrAcceptThread::PostThreadQuitMessage()
{
	m_MessageQueue.N3MessageQueue::Put(N3MSGID(CMsvrAcceptThread,MSG_REQ_THREAD_QUIT), 0, 0);
}


void CMsvrAcceptThread::Receive(const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam)
{
	m_MessageQueue.N3MessageQueue::Put(in_Msg, in_wParam, in_lParam);
}
