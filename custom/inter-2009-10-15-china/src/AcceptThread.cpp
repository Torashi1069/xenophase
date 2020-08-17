#include "AcceptThread.h"


CAcceptThread::CAcceptThread(CAcceptHandler* const in_cpHandler, const unsigned long in_IPaddr, const short in_Port, const int in_Backlog, const unsigned int in_ipLog) // line 23
: m_cpHandler(in_cpHandler), m_IPaddr(in_IPaddr), m_Port(in_Port), m_Backlog(in_Backlog), m_ipLog(in_ipLog)
{
	m_bReqExit = false;
	m_Socket = INVALID_SOCKET;
	m_bOK = false;

	if( this->CAcceptThread::Create() )
		m_bOK = true;
}


CAcceptThread::~CAcceptThread(void) // line 31
{
	this->CAcceptThread::Destroy();
}


hook_method<unsigned int (CAcceptThread::*)(void)> CAcceptThread::_ThreadFunction(SERVER, "CAcceptThread::ThreadFunction");
unsigned int CAcceptThread::ThreadFunction(void) // line 90
{
	return (this->*_ThreadFunction)();

	while( !m_bReqExit )
	{
		sockaddr_in remoteAddr;
		int sockLen = sizeof(remoteAddr);

		SOCKET s = WSAAccept(m_Socket, (sockaddr*)&remoteAddr, &sockLen, NULL, NULL);
		if( s == INVALID_SOCKET )
			continue;

		if( m_ipLog )
		{
			char buf[32];
			sprintf(buf, "%s\n", inet_ntoa(remoteAddr.sin_addr));
			OutputDebugStringA(buf);
		}

		if( !m_cpHandler->OnConnect(s, remoteAddr.sin_addr.s_addr) )
			closesocket(s);
	}

	return 0;
}


hook_method<void (CAcceptThread::*)(void)> CAcceptThread::_PostThreadQuitMessage(SERVER, "CAcceptThread::PostThreadQuitMessage");
void CAcceptThread::PostThreadQuitMessage(void) // line 122
{
	return (this->*_PostThreadQuitMessage)();

	this->CAcceptThread::Destroy();
	m_bReqExit = true;
}


hook_method<bool (CAcceptThread::*)(void)> CAcceptThread::_Create(SERVER, "CAcceptThread::Create");
bool CAcceptThread::Create(void) // line 49
{
	return (this->*_Create)();

	m_Socket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if( m_Socket == INVALID_SOCKET )
	{
		MessageBoxA(NULL, "WSASocket() failed: listener", "error", MB_OK);
		ExitProcess(EXIT_FAILURE);
	}

	sockaddr_in hostAddr = {};
	hostAddr.sin_family = AF_INET;
	hostAddr.sin_addr.s_addr = m_IPaddr;
	hostAddr.sin_port = htons(m_Port);

	if( bind(m_Socket, (sockaddr*)&hostAddr, sizeof(hostAddr)) == SOCKET_ERROR )
	{
		MessageBoxA(NULL, "bind() failed: listener", "error", MB_OK);
		ExitProcess(EXIT_FAILURE);
	}

	if( listen(m_Socket, m_Backlog) == SOCKET_ERROR )
	{
		MessageBoxA(NULL, "listen() failed: listener", "error", MB_OK);
		ExitProcess(EXIT_FAILURE);
	}

	return true;
}


hook_method<void (CAcceptThread::*)(void)> CAcceptThread::_Destroy(SERVER, "CAcceptThread::Destory");
void CAcceptThread::Destroy(void) // line 81
{
	return (this->*_Destroy)();

	if( m_Socket != INVALID_SOCKET )
	{
		closesocket(m_Socket);
		m_Socket = INVALID_SOCKET;
	}
}


hook_method<const bool (CAcceptThread::*)(void)> CAcceptThread::_isOK(SERVER, "CAcceptThread::isOK");
const bool CAcceptThread::isOK(void) // line 28 (AcceptThread.h)
{
	return (this->*_isOK)();

	return m_bOK;
}


hook_method<bool (CAcceptThread::*)(void)> CAcceptThread::_Start(SERVER, "CAcceptThread::Start");
bool CAcceptThread::Start(void) // line 40
{
	return (this->*_Start)();

	return this->N2Thread::Begin();
}


hook_method<void (CAcceptThread::*)(void)> CAcceptThread::_Stop(SERVER, "CAcceptThread::Stop");
void CAcceptThread::Stop(void) // line 45
{
	return (this->*_Stop)();

	this->N2Thread::End();
}
