#include "NNetworkMgr.h"
#include "NetLib/AsyncStream.h"


CAsyncStream::CAsyncStream()
{
	InitializeCriticalSection(&m_csLock);

	m_socket = INVALID_SOCKET;
	m_packetHandler = NULL;
	m_lastError = CAsyncStream::ERR_NONE;

	m_recvQueue.CPacketQueue::Init(20480);
	m_sendQueue.CPacketQueue::Init(102400);

	memset(&m_recvOperation, 0, sizeof(m_recvOperation));
	m_recvOperation.m_dataBuf.buf = m_recvOperation.m_buffer;
	m_recvOperation.m_dataBuf.len = sizeof(m_recvOperation.m_buffer);
	m_recvOperation.m_type = CAsyncOperation::RECV;
	m_recvOperation.m_stream = this;

	memset(&m_sendOperation, 0, sizeof(m_sendOperation));
	m_sendOperation.m_dataBuf.buf = m_sendOperation.m_buffer;
//	m_recvOperation.m_dataBuf.len = 0;
	m_sendOperation.m_type = CAsyncOperation::SEND;
	m_sendOperation.m_stream = this;
}


CAsyncStream::CAsyncStream(int recvSize, int sendSize)
{
	InitializeCriticalSection(&m_csLock);

	m_socket = INVALID_SOCKET;
	m_packetHandler = NULL;
	m_lastError = CAsyncStream::ERR_NONE;

	m_recvQueue.CPacketQueue::Init(recvSize);
	m_sendQueue.CPacketQueue::Init(sendSize);

	memset(&m_recvOperation, 0, sizeof(m_recvOperation));
	m_recvOperation.m_dataBuf.buf = m_recvOperation.m_buffer;
	m_recvOperation.m_dataBuf.len = sizeof(m_recvOperation.m_buffer);
	m_recvOperation.m_type = CAsyncOperation::RECV;
	m_recvOperation.m_stream = this;

	memset(&m_sendOperation, 0, sizeof(m_sendOperation));
	m_sendOperation.m_dataBuf.buf = m_sendOperation.m_buffer;
//	m_recvOperation.m_dataBuf.len = 0;
	m_sendOperation.m_type = CAsyncOperation::SEND;
	m_sendOperation.m_stream = this;
}


CAsyncStream::~CAsyncStream()
{
	DeleteCriticalSection(&m_csLock);
}


void CAsyncStream::Init(CPacketHandler* handler)
{
	m_socket = INVALID_SOCKET;
	m_lastError = CAsyncStream::ERR_NONE;
	m_recvQueue.CPacketQueue::Reset();
	m_sendQueue.CPacketQueue::Reset();
	m_packetHandler = handler;
	handler->SetQueue(&m_recvQueue);
}


void CAsyncStream::SetRecvQueueSize(int size)
{
	m_recvQueue.CPacketQueue::Init(size);
}


void CAsyncStream::SetSendQueueSize(int size)
{
	m_sendQueue.CPacketQueue::Init(size);
}


DWORD CAsyncStream::GenerateCompletionKey()
{
	return NNetworkMgr::GetObj()->NNetworkMgr::GenerateCompletionKey();
}


bool CAsyncStream::Open(SOCKET socket)
{
	m_completionKey = this->CAsyncStream::GenerateCompletionKey();
	m_socket = socket;

	if( CreateIoCompletionPort((HANDLE)socket, NNetworkMgr::GetObj()->NNetworkMgr::GetIOCPHandle(), m_completionKey, 0) == NULL )
		return false;

	m_lastError = CAsyncStream::ERR_NONE;

	DWORD read;
	DWORD flags = 0;
	if( WSARecv(m_socket, &m_recvOperation.m_dataBuf, 1, &read, &flags, &m_recvOperation, NULL) == SOCKET_ERROR )
	{
		if( WSAGetLastError() != ERROR_IO_PENDING )
		{
			m_lastError = WSAGetLastError();
			return false;
		}
	}

	return true;
}


bool CAsyncStream::IsSendable2(const int in_DataBytes)
{
	return ( m_sendQueue.CPacketQueue::GetFreeSize() >= in_DataBytes );
}


bool CAsyncStream::Send2(const unsigned char* in_pData, const int in_DataBytes)
{
	if( in_DataBytes <= 0 )
		return false;

	int total = m_sendQueue.CPacketQueue::InsertData(in_DataBytes, (const char*)in_pData);
	if( total < 0 )
	{
		m_lastError = CAsyncStream::ERR_SENDQUEUEOVERFLOW;
		this->Close(false);
		return false;
	}

	if( total > in_DataBytes )
		return true; // ???

	if( !this->SendDataInQueue(in_DataBytes) )
	{
		this->Close(false);
		return true; // ???
	}

	return true;
}


void CAsyncStream::Send(int len, const char* buf)
{
	if( len <= 0 )
		return;

	int total = m_sendQueue.CPacketQueue::InsertData(len, buf);
	if( total < 0 )
	{
		m_lastError = CAsyncStream::ERR_SENDQUEUEOVERFLOW;
		this->Close(false);
		return;
	}

	if( total > len )
		return; // ???

	if( !this->SendDataInQueue(len) )
	{
		this->Close(false);
		return;
	}

	return;
}


BOOL CAsyncStream::Close(const bool in_bOnlySocketClose)
{
	if( m_socket == INVALID_SOCKET )
		return FALSE;

	EnterCriticalSection(&m_csLock);

	linger linger;
	linger.l_onoff = 1;
	linger.l_linger = 0;
	setsockopt(m_socket, SOL_SOCKET, SO_LINGER, (char*)&linger, sizeof(linger));

	BOOL result = TRUE;
	if( closesocket(m_socket) == SOCKET_ERROR )
		result = FALSE;

	m_socket = INVALID_SOCKET;

	if( !in_bOnlySocketClose )
		m_packetHandler->OnClose();

	LeaveCriticalSection(&m_csLock);

	return result;
}


ULONG CAsyncStream::GetIP()
{
	sockaddr_in name = {};
	int addrLen = sizeof(name);
	getpeername(m_socket, (sockaddr*)&name, &addrLen);

	return name.sin_addr.s_addr;
}


BOOL CAsyncStream::SendDataInQueue(int size)
{
	if( size >= sizeof(m_sendOperation.m_buffer) )
		size = sizeof(m_sendOperation.m_buffer);

	m_sendQueue.CPacketQueue::PeekData(size, m_sendOperation.m_buffer);
	m_sendOperation.m_dataBuf.len = size;

	DWORD sent;
	if( WSASend(m_socket, &m_sendOperation.m_dataBuf, 1, &sent, 0, &m_sendOperation, NULL) == SOCKET_ERROR )
	{
		if( WSAGetLastError() != ERROR_IO_PENDING )
		{
			m_lastError = WSAGetLastError();
			return FALSE;
		}
	}

	return TRUE;
}


BOOL CAsyncStream::OnSendCompletion(long len)
{
	int total = m_sendQueue.CPacketQueue::RemoveData(len);
	if( total <= 0 )
		return TRUE;

	return this->SendDataInQueue(total);
}


BOOL CAsyncStream::OnRecvCompletion(long len)
{
	if( m_recvQueue.CPacketQueue::InsertData(len, m_recvOperation.m_buffer) == -1 )
	{
		m_lastError = CAsyncStream::ERR_RECVQUEUEOVERFLOW;
		return FALSE;
	}

	DWORD read;
	DWORD flags = 0;
	if( WSARecv(m_socket, &m_recvOperation.m_dataBuf, 1, &read, &flags, &m_recvOperation, NULL) == SOCKET_ERROR )
	{
		if( WSAGetLastError() != ERROR_IO_PENDING )
		{
			m_lastError = WSAGetLastError();
			return FALSE;
		}
	}

	return TRUE;
}


void CAsyncStream::OnComplete(BOOL result, DWORD transferSize, CAsyncOperation* op)
{
	if( m_socket == INVALID_SOCKET )
		return;

	BOOL bSuccess;
	if( result && transferSize != 0 )
	{
		if( op->m_type == CAsyncOperation::SEND )
			bSuccess = this->OnSendCompletion(transferSize);
		else
			bSuccess = this->OnRecvCompletion(transferSize);
	}
	else
	{
		bSuccess = FALSE;
	}

	if ( !bSuccess )
	{
		m_packetHandler->SetLastError(m_lastError);
		this->Close(false);
	}
}


SOCKET CAsyncStream::GetSocket()
{
	return m_socket;
}


DWORD CAsyncStream::GetLastError()
{
	return m_lastError;
}


CPacketQueue* CAsyncStream::GetRecvQueuePtr()
{
	return &m_recvQueue;
}
