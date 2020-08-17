#include "CProcessMgr.h"
#include "ZoneProcess.h"
#include "ZSAcceptThread.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/NOutputTextMgr.h"
#include "shared/NSystem/NIPAddr.h"
#include "shared/N3System/N3MessageMgr.h"


/// singleton instance
CZSAcceptThread*& CZSAcceptThread::m_cpSelf = VTOR<CZSAcceptThread*>(DetourFindFunction(EXEPATH(), "CZSAcceptThread::m_cpSelf"));


CZSAcceptThread::CZSAcceptThread()
: N3Thread("ZSAcceptThread"), N3Object(),
  m_cpAcceptHandler(NULL), m_listenSocket(INVALID_SOCKET), m_ReqExit(false), m_bOK(false)
{
	m_bOK = true;
}


CZSAcceptThread::~CZSAcceptThread()
{
	if( m_listenSocket != INVALID_SOCKET )
	{
		closesocket(m_listenSocket);
		m_listenSocket = INVALID_SOCKET;
	}
}


std::pair<bool,std::string> CZSAcceptThread::Start(const unsigned long in_IPaddr, const int in_Port, CZSAcceptHandler* in_cpAcceptHandler)
{
	m_cpAcceptHandler = &g_zsAcceptHandler;

	m_listenSocket = WSASocketA(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if( m_listenSocket == INVALID_SOCKET )
		return std::pair<bool,std::string>(false, "WSASocket() Error");

	sockaddr_in hostAddr = {};
	hostAddr.sin_family = AF_INET;
	hostAddr.sin_addr.s_addr = in_IPaddr;
	hostAddr.sin_port = htons(in_Port);

	if( bind(m_listenSocket, (sockaddr*)&hostAddr, sizeof(hostAddr)) == SOCKET_ERROR )
		return std::pair<bool,std::string>(false, "bind() Error");

	if( listen(m_listenSocket, 20) == SOCKET_ERROR )
		return std::pair<bool,std::string>(false, "listen() Error");

	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("[listen] client %s:%d", NIPAddapter(in_IPaddr), in_Port);
	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[listen] client %s:%d", NIPAddapter(in_IPaddr), in_Port);

	if( !this->N3Thread::Begin() )
		return std::pair<bool,std::string>(false, "unknown");

	return std::pair<bool,std::string>(true, "good");
}


void CZSAcceptThread::Stop()
{
	this->N3Thread::End();

	if( m_listenSocket != INVALID_SOCKET )
	{
		closesocket(m_listenSocket);
		m_listenSocket = INVALID_SOCKET;
	}
}


bool CZSAcceptThread::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;
	
	m_cpSelf = new(std::nothrow) CZSAcceptThread();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CZSAcceptThread::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CZSAcceptThread::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CZSAcceptThread* CZSAcceptThread::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CZSAcceptThread::isOK() const
{
	return m_bOK;
}


unsigned int CZSAcceptThread::ThreadFunction()
{
	while( !m_ReqExit )
	{
		sockaddr_in remoteAddr = {};
		int sockLen = sizeof(remoteAddr);

		SOCKET s = WSAAccept(m_listenSocket, (sockaddr*)&remoteAddr, &sockLen, NULL, 0);
		if( s == SOCKET_ERROR )
			continue;

		N3MessageMgr::GetObj()->N3MessageMgr::Post(CProcessMgr::GetObj()->N3Object::GetMyID(), N3MSGID(CProcessMgr,MSG_ACCEPT), s, remoteAddr.sin_addr.s_addr);
	}

	return 0;
}


void CZSAcceptThread::PostThreadQuitMessage()
{
	m_ReqExit = true;

	if( m_listenSocket != INVALID_SOCKET )
	{
		closesocket(m_listenSocket);
		m_listenSocket = INVALID_SOCKET;
	}
}
