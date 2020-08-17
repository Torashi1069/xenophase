#include "NetLib/AsyncStream.h"
#include "globals.hpp"


hook_val<unsigned long> CAsyncStream::m_newCompletionKey(SERVER, "CAsyncStream::m_newCompletionKey"); // = ?


hook_func<unsigned int (__stdcall *)(void* CP)> _CompletionProactor(SERVER, "CompletionProactor");
unsigned int __stdcall CompletionProactor(void* CP) // line 11
{
	return (_CompletionProactor)(CP);

	while( 1 )
	{
		DWORD transferSize;
		ULONG_PTR compKey;
		CAsyncOperation* op;

		BOOL result = ::GetQueuedCompletionStatus((HANDLE)CP, &transferSize, &compKey, (LPOVERLAPPED*)&op, INFINITE);

		if( op == NULL )
			continue;

		if( op->m_stream == NULL )
			continue;

		if( op->m_stream->m_completionKey != compKey )
			continue;

		op->m_stream->CAsyncStream::OnComplete(result, transferSize, op);
	}

	return 0;
}


hook_func<int (__cdecl *)(void)> _StartCompletionProactor(SERVER, "StartCompletionProactor");
int __cdecl StartCompletionProactor(void) // line 27
{
	return (_StartCompletionProactor)();

	g_completionPort = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	if( g_completionPort == NULL )
		return 0;

	CAsyncStream::m_newCompletionKey = 0;

	SYSTEM_INFO sysInfo;
	::GetSystemInfo(&sysInfo);

	for( int v1 = 0; v1 < 32; ++v1 )
	{
		unsigned int threadID;
		HANDLE v2 = (HANDLE)::_beginthreadex(0, 0, &CompletionProactor, g_completionPort, 0, &threadID);
		if( v2 == 0 )
			return 0;

		::CloseHandle(v2);
	}

	return 1;
}


CAsyncStream::CAsyncStream(void) // line 54
{
	InitializeCriticalSection(&m_csLock);

	m_socket = INVALID_SOCKET;
	m_packetHandler = NULL;
	m_lastError = CAsyncStream::ERR_NONE;

	m_recvQueue.CPacketQueue::Init(20480);
	m_sendQueue.CPacketQueue::Init(102400);

	memset(&m_recvOperation, 0, sizeof(OVERLAPPED));
	memset(&m_recvOperation.m_dataBuf, 0, sizeof(m_recvOperation.m_dataBuf));
	memset(&m_recvOperation.m_buffer, 0, sizeof(m_recvOperation.m_buffer));
	m_recvOperation.m_dataBuf.len = sizeof(m_recvOperation.m_buffer);
	m_recvOperation.m_dataBuf.buf = m_recvOperation.m_buffer;
	m_recvOperation.m_type = CAsyncOperation::RECV;
	m_recvOperation.m_stream = this;

	memset(&m_sendOperation, 0, sizeof(OVERLAPPED));
	memset(&m_sendOperation.m_dataBuf, 0, sizeof(m_sendOperation.m_dataBuf));
	memset(&m_sendOperation.m_buffer, 0, sizeof(m_sendOperation.m_buffer));
	m_sendOperation.m_dataBuf.buf = m_sendOperation.m_buffer;
	m_sendOperation.m_type = CAsyncOperation::SEND;
	m_sendOperation.m_stream = this;
}


CAsyncStream::CAsyncStream(int recvSize, int sendSize) // line 76
{
	InitializeCriticalSection(&m_csLock);

	m_socket = INVALID_SOCKET;
	m_packetHandler = NULL;
	m_lastError = CAsyncStream::ERR_NONE;

	m_recvQueue.CPacketQueue::Init(recvSize);
	m_sendQueue.CPacketQueue::Init(sendSize);

	memset(&m_recvOperation, 0, sizeof(OVERLAPPED));
	memset(&m_recvOperation.m_dataBuf, 0, sizeof(m_recvOperation.m_dataBuf));
	memset(&m_recvOperation.m_buffer, 0, sizeof(m_recvOperation.m_buffer));
	m_recvOperation.m_dataBuf.len = sizeof(m_recvOperation.m_buffer);
	m_recvOperation.m_dataBuf.buf = m_recvOperation.m_buffer;
	m_recvOperation.m_type = CAsyncOperation::RECV;
	m_recvOperation.m_stream = this;

	memset(&m_sendOperation, 0, sizeof(OVERLAPPED));
	memset(&m_sendOperation.m_dataBuf, 0, sizeof(m_sendOperation.m_dataBuf));
	memset(&m_sendOperation.m_buffer, 0, sizeof(m_sendOperation.m_buffer));
	m_sendOperation.m_dataBuf.buf = m_sendOperation.m_buffer;
	m_sendOperation.m_type = CAsyncOperation::SEND;
	m_sendOperation.m_stream = this;
}


CAsyncStream::~CAsyncStream(void) // line 98
{
	DeleteCriticalSection(&m_csLock);
}


hook_method<void (CAsyncStream::*)(CPacketHandler* handler)> CAsyncStream::_Init(SERVER, "CAsyncStream::Init");
void CAsyncStream::Init(CPacketHandler* handler) // line 107
{
	return (this->*_Init)(handler);

	m_socket = INVALID_SOCKET;
	m_lastError = CAsyncStream::ERR_NONE;
	m_recvQueue.CPacketQueue::Reset();
	m_sendQueue.CPacketQueue::Reset();
	m_packetHandler = handler;
	handler->SetQueue(&m_recvQueue);
}


hook_method<bool (CAsyncStream::*)(SOCKET socket)> CAsyncStream::_Open(SERVER, "CAsyncStream::Open");
bool CAsyncStream::Open(SOCKET socket) // line 135
{
	return (this->*_Open)(socket);

	m_completionKey = CAsyncStream::m_newCompletionKey++;
	m_socket = socket;
	if( !CreateIoCompletionPort((HANDLE)socket, g_completionPort, m_completionKey, 0) )
		return false;
	m_lastError = CAsyncStream::ERR_NONE;

	DWORD read = 0;
	DWORD flags = 0;
	if( WSARecv((SOCKET)m_socket, &m_recvOperation.m_dataBuf, 1, (LPDWORD)&read, &flags, &m_recvOperation, NULL) == SOCKET_ERROR
	&&  WSAGetLastError() != ERROR_IO_PENDING )
	{
		m_lastError = WSAGetLastError();
		return false;
	}

	return true;
}


hook_method<void (CAsyncStream::*)(int len, const char* buf)> CAsyncStream::_Send(SERVER, "CAsyncStream::Send");
void CAsyncStream::Send(int len, const char* buf) // line 177
{
	return (this->*_Send)(len, buf);

	if( len <= 0 )
		return;

	int v4 = m_sendQueue.CPacketQueue::InsertData(len, buf);
	if( v4 < 0 )
	{
		m_lastError = CAsyncStream::ERR_SENDQUEUEOVERFLOW;
		this->CAsyncStream::Close();
		return;
	}

	if( v4 <= len )
	{
		if( !this->CAsyncStream::SendDataInQueue(len) )
			this->CAsyncStream::Close();
	}
}


//hook_method<bool (CAsyncStream::*)(const unsigned char* in_pData, const int in_DataBytes)> CAsyncStream::_Send2(SERVER, "CAsyncStream::Send2");
bool CAsyncStream::Send2(const unsigned char* in_pData, const int in_DataBytes) // line ???
{
//	return (this->*_Send2)(in_pData, in_DataBytes);

	if( in_DataBytes <= 0 )
		return false;

	int v4 = m_sendQueue.CPacketQueue::InsertData(in_DataBytes, (const char*)in_pData);
	if( v4 < 0 )
	{
		m_lastError = CAsyncStream::ERR_SENDQUEUEOVERFLOW;
		this->CAsyncStream::Close();
		return false;
	}

	if( v4 <= in_DataBytes )
	{
		if( !this->CAsyncStream::SendDataInQueue(in_DataBytes) )
			this->CAsyncStream::Close();
	}

	return true;
}


//hook_method<bool (CAsyncStream::*)(const int in_DataBytes)> CAsyncStream::_IsSendable2(SERVER, "CAsyncStream::IsSendable2");
bool CAsyncStream::IsSendable2(const int in_DataBytes) // line ???
{
//	return (this->*_IsSendable2)(in_DataBytes);

	return( m_sendQueue.CPacketQueue::GetFreeSize() >= in_DataBytes );
}


hook_method<int (CAsyncStream::*)(void)> CAsyncStream::_Close(SERVER, "CAsyncStream::Close");
int CAsyncStream::Close(void) // line 198
{
	return (this->*_Close)();

	int result = 1;

	if( m_socket == INVALID_SOCKET )
		return 0;

	::EnterCriticalSection(&m_csLock);

	struct linger linger = {1, 0};
	::setsockopt(m_socket, SOL_SOCKET, SO_LINGER, (const char *)&linger, sizeof(linger));

	if( ::closesocket(m_socket) == SOCKET_ERROR )
		result = 0;

	m_socket = INVALID_SOCKET;
	m_packetHandler->OnClose();

	::LeaveCriticalSection(&m_csLock);

	return result;
}


//hook_method<SOCKET (CAsyncStream::*)(void)> CAsyncStream::_GetSocket(SERVER, "CAsyncStream::GetSocket");
SOCKET CAsyncStream::GetSocket(void) // line ???
{
//	return (this->*_GetSocket)();

	return m_socket;
}


hook_method<void (CAsyncStream::*)(int size)> CAsyncStream::_SetRecvQueueSize(SERVER, "CAsyncStream::SetRecvQueueSize");
void CAsyncStream::SetRecvQueueSize(int size) // line 125
{
	return (this->*_SetRecvQueueSize)(size);

	m_recvQueue.CPacketQueue::Init(size);
}


//hook_method<void (CAsyncStream::*)(int size)> CAsyncStream::_SetSendQueueSize(SERVER, "CAsyncStream::SetSendQueueSize");
void CAsyncStream::SetSendQueueSize(int size) // line ???
{
//	return (this->*_SetSendQueueSize)(size);

	m_sendQueue.CPacketQueue::Init(size);
}


//hook_method<unsigned long (CAsyncStream::*)(void)> CAsyncStream::_GetIP(SERVER, "CAsyncStream::GetIP");
unsigned long CAsyncStream::GetIP(void) // line ???
{
//	return (this->*_GetIP)();

	sockaddr name = {};
	int addrLen = sizeof(name);
	getpeername(m_socket, &name, &addrLen);

	return reinterpret_cast<sockaddr_in*>(&name)->sin_addr.s_addr;
}


hook_method<void (CAsyncStream::*)(int result, unsigned long transferSize, CAsyncOperation* op)> CAsyncStream::_OnComplete(SERVER, "CAsyncStream::OnComplete");
void CAsyncStream::OnComplete(int result, unsigned long transferSize, CAsyncOperation* op) // line 311
{
	return (this->*_OnComplete)(result, transferSize, op);

	if( this->m_socket == INVALID_SOCKET )
		return;

	if( result == 0 || transferSize <= 0 )
	{
		this->CAsyncStream::Close();
		return;
	}

	int v5 = ( op->m_type != CAsyncOperation::SEND ) ? this->CAsyncStream::OnRecvCompletion(transferSize) : this->CAsyncStream::OnSendCompletion(transferSize);
	
	if( v5 == 0 )
	{
		this->CAsyncStream::Close();
		return;
	}
}


//hook_method<unsigned long (CAsyncStream::*)(void)> CAsyncStream::_GetLastError(SERVER, "CAsyncStream::GetLastError");
unsigned long CAsyncStream::GetLastError(void) // line ???
{
//	return (this->*_GetLastError)();

	return m_lastError;
}


//hook_method<CPacketQueue* (CAsyncStream::*)(void)> CAsyncStream::_GetRecvQueuePtr(SERVER, "CAsyncStream::GetRecvQueuePtr");
CPacketQueue* CAsyncStream::GetRecvQueuePtr(void) // line ???
{
//	return (this->*_GetRecvQueuePtr)();

	return &m_recvQueue;
}


hook_method<int (CAsyncStream::*)(int size)> CAsyncStream::_SendDataInQueue(SERVER, "CAsyncStream::SendDataInQueue");
int CAsyncStream::SendDataInQueue(int size) // line 240
{
	return (this->*_SendDataInQueue)(size);

	if( size >= sizeof(m_sendOperation.m_buffer) )
		size = sizeof(m_sendOperation.m_buffer);

	m_sendQueue.CPacketQueue::PeekData(size, m_sendOperation.m_buffer);
	m_sendOperation.m_dataBuf.len = size;

	if( WSASend(m_socket, &m_sendOperation.m_dataBuf, 1, (LPDWORD)&size, 0, &m_sendOperation, NULL) == SOCKET_ERROR
	&&  WSAGetLastError() != ERROR_IO_PENDING )
	{
		m_lastError = WSAGetLastError();
		return 0;
	}

	return 1;
}


hook_method<int (CAsyncStream::*)(long len)> CAsyncStream::_OnRecvCompletion(SERVER, "CAsyncStream::OnRecvCompletion");
int CAsyncStream::OnRecvCompletion(long len) // line 291
{
	return (this->*_OnRecvCompletion)(len);

	if( m_recvQueue.CPacketQueue::InsertData(len, m_recvOperation.m_buffer) == SOCKET_ERROR )
	{
		m_lastError = CAsyncStream::ERR_RECVQUEUEOVERFLOW;
		return 0;
	}

	DWORD read = 0;
	DWORD flags = 0;
	if( WSARecv(m_socket, &m_recvOperation.m_dataBuf, 1, &read, &flags, &m_recvOperation, NULL) == SOCKET_ERROR
	||  WSAGetLastError() == ERROR_IO_PENDING )
	{
		m_lastError = WSAGetLastError();
		return 0;
	}

	return 1;
}


hook_method<int (CAsyncStream::*)(long len)> CAsyncStream::_OnSendCompletion(SERVER, "CAsyncStream::OnSendCompletion");
int CAsyncStream::OnSendCompletion(long len) // line 279
{
	return (this->*_OnSendCompletion)(len);

	int v2 = m_sendQueue.CPacketQueue::RemoveData(len);
	if( v2 <= 0 )
		return 1;

	return this->CAsyncStream::SendDataInQueue(v2);
}


//hook_method<unsigned long (CAsyncStream::*)(void)> CAsyncStream::_GenerateCompletionKey(SERVER, "CAsyncStream::GenerateCompletionKey");
unsigned long CAsyncStream::GenerateCompletionKey(void) // line ???
{
//	return (this->*_GenerateCompletionKey)();

	return CAsyncStream::m_newCompletionKey++;
}
