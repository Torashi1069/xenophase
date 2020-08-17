#include "AsyncStream.h"


hook_val<unsigned long> CAsyncStream::m_newCompletionKey(SERVER, "CAsyncStream::m_newCompletionKey"); // = 0;


hook_func<int (__cdecl *)(void)> _StartCompletionProactor(SERVER, "StartCompletionProactor");
int __cdecl StartCompletionProactor(void) // line 27
{
	return (_StartCompletionProactor)();

	//TODO
}


hook_method<void (CAsyncStream::*)(CPacketHandler* handler)> CAsyncStream::_Init(SERVER, "CAsyncStream::Init");
void CAsyncStream::Init(CPacketHandler* handler) // line 107
{
	return (this->*_Init)(handler);

	//TODO
}


hook_method<bool (CAsyncStream::*)(SOCKET s)> CAsyncStream::_Open(SERVER, "CAsyncStream::Open");
bool CAsyncStream::Open(SOCKET s) // line 135
{
	return (this->*_Open)(s);

	//TODO
}


hook_method<void (CAsyncStream::*)(int len, const char* buf)> CAsyncStream::_Send(SERVER, "CAsyncStream::Send");
void CAsyncStream::Send(int len, const char* buf) // line 177
{
	return (this->*_Send)(len,buf);

	// TODO
}


hook_method<int (CAsyncStream::*)(void)> CAsyncStream::_Close(SERVER, "CAsyncStream::Close");
int CAsyncStream::Close(void) // line 198
{
	return (this->*_Close)();

	int result = 1;

	if( m_socket == INVALID_SOCKET )
		return 0;

	EnterCriticalSection(&m_csLock);

	struct linger linger = {1, 0};
	setsockopt(m_socket, SOL_SOCKET, SO_LINGER, (const char*)&linger, sizeof(linger));

	if( closesocket(m_socket) == INVALID_SOCKET )
		result = 0;

	m_socket = INVALID_SOCKET;
	m_packetHandler->OnClose();

	LeaveCriticalSection(&m_csLock);
	return result;
}


hook_method<void (CAsyncStream::*)(int size)> CAsyncStream::_SetRecvQueueSize(SERVER, "CAsyncStream::SetRecvQueueSize");
void CAsyncStream::SetRecvQueueSize(int size) // line 125
{
	return (this->*_SetRecvQueueSize)(size);

	m_recvQueue.CPacketQueue::Init(size);
}


hook_method<void (CAsyncStream::*)(int size)> CAsyncStream::_SetSendQueueSize(SERVER, "CAsyncStream::SetSendQueueSize");
void CAsyncStream::SetSendQueueSize(int size) // line 130
{
	return (this->*_SetSendQueueSize)(size);

	m_sendQueue.CPacketQueue::Init(size);
}
