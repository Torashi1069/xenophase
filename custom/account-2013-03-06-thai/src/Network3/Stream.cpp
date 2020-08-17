#include "Common/EnterTraceLog.h"
#include "Common/Network.h"
#include "Common/Packet.h"
#include "Network3/Process.h"
#include "Network3/Stream.h"


LONG CStream::m_SESSIONID;
DWORD CStream::CreateSessionID()
{
	DWORD dwStreamSessionID;

	do
	dwStreamSessionID = InterlockedIncrement(&m_SESSIONID);
	while( dwStreamSessionID == 0 );

	return dwStreamSessionID;
}


CStream::CStream()
{
//	m_bDetailedCloseInfo = false;
	m_socket = INVALID_SOCKET;
	m_wCurProcPKT = 0;
	m_dwSessionID = 0;
	m_dwIP = 0;
	m_dwPingTime = 0;
	m_dwLastRecvTime = 0;
	RECV_BUF_SIZE = 0;
	m_pRecvBuf = NULL;
	m_nRecvPos = 0;
	m_bRecvPermit = false;
	m_cRef = 0;
	m_bConnected = false;
//	m_pProcess = NULL;
	memset(&m_ovRecv, 0, sizeof(m_ovRecv));
	memset(&m_ovSend, 0, sizeof(m_ovSend));
	m_SendQueue.CCircleQueue::ClearBuffer();
	m_bInitialSendPostPermit = false;
}


CStream::~CStream()
{
	if( m_pRecvBuf != NULL )
	{
		delete[] m_pRecvBuf;
		m_pRecvBuf = NULL;
		RECV_BUF_SIZE = 0;
	}
}


bool CStream::CreateRecvBuf(int buf_size)
{
	if( buf_size <= 1 )
		return false;

	m_cs.Enter();

	if( m_pRecvBuf != NULL )
	{
		delete[] m_pRecvBuf;
		m_pRecvBuf = NULL;
		RECV_BUF_SIZE = 0;
	}

	m_pRecvBuf = new char[buf_size];
	if( m_pRecvBuf == NULL )
	{
		m_cs.Leave();
		return false;
	}

	RECV_BUF_SIZE = buf_size;

	m_cs.Leave();

	return true;
}


bool CStream::CreateSendQueue(int queue_size)
{
	return m_SendQueue.CCircleQueue::Create(queue_size);
}


void CStream::SetProcessObj(CProcess* pProcess, bool bDetailedCloseInfo)
{
	m_pProcess = pProcess;
	m_bDetailedCloseInfo = bDetailedCloseInfo;
}


bool CStream::Init(SOCKET s, DWORD dwIP, DWORD dwPingTime)
{
	DWORD dwNewSessionID = CStream::CreateSessionID();

	m_cs.Enter();
	m_SendQueue.CCircleQueue::ClearBuffer();
	m_socket = s;
	m_dwIP = dwIP;
	m_nRecvPos = 0;
	m_bRecvPermit = true;
	m_dwPingTime = dwPingTime;
	m_dwLastRecvTime = timeGetTime();
	m_dwSessionID = dwNewSessionID;
	m_bInitialSendPostPermit = false;
	m_cs.Leave();

	memset(&m_ovRecv, 0, sizeof(m_ovRecv));
	m_ovRecv.m_byOperationCode = 1; // recv
	m_ovRecv.m_dwTryBytes = RECV_BUF_SIZE - m_nRecvPos;
	m_ovRecv.m_dwTransferredBytes = 0;

	WSABUF wsabuf;
	wsabuf.buf = &m_pRecvBuf[m_nRecvPos];
	wsabuf.len = RECV_BUF_SIZE - m_nRecvPos;

	DWORD dwReceivedBytes = 0;
	DWORD dwFlags = 0;
	if( WSARecv(m_socket, &wsabuf, 1, &dwReceivedBytes, &dwFlags, (LPWSAOVERLAPPED)&m_ovRecv, NULL) == SOCKET_ERROR )
	{
		if( WSAGetLastError() != WSA_IO_PENDING )
		{
			CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "WSAGetLastError(%d)\n", WSAGetLastError());
			this->CStream::DetailedCloseInfo(__FILE__, __LINE__, __FUNCTION__, "WSAGetLastError()!=WSA_IO_PENDING");
			this->CStream::Close(0);
			return false;
		}
	}

	this->CStream::AddRef();
	this->CStream::AddRef();

	m_cs.Enter();
	m_bInitialSendPostPermit = true;
	m_cs.Leave();

	if( !m_pProcess->CProcess::Init(dwNewSessionID, dwIP) )
	{
		this->CStream::DetailedCloseInfo(__FILE__, __LINE__, __FUNCTION__, "!m_pProcess->Init(dwNewSessionID, dwIP)");
		this->CStream::Close(0);
	}

	this->CStream::SubRef();
	return true;
}


bool CStream::HandleIo(OVERLAPPEDEX* lpOverlappedEx, DWORD dwTransferredBytes)
{
	if( lpOverlappedEx->m_byOperationCode == 1 )
		return this->CStream::OnRecv(lpOverlappedEx, dwTransferredBytes);
	else
	if( lpOverlappedEx->m_byOperationCode == 2 )
		return this->CStream::OnSendCompleted(lpOverlappedEx, dwTransferredBytes);
	else
		return false;
}


LONG CStream::GetRef()
{
	return m_cRef;
}


LONG CStream::AddRef()
{
	return InterlockedIncrement(&m_cRef);
}


LONG CStream::SubRef()
{
	return InterlockedDecrement(&m_cRef);
}


bool CStream::OnRecv(OVERLAPPEDEX* lpOverlappedEx, DWORD dwTransferredBytes)
{
	CSubRef subref(this);

	if( dwTransferredBytes == 0 )
	{
		this->CStream::DetailedCloseInfo(__FILE__, __LINE__, __FUNCTION__, "dwTransferredBytes==0");
		this->CStream::Close(0);
		return false;
	}

	this->CStream::UpdateReceivedTime();

	m_nRecvPos += dwTransferredBytes;
	if( m_nRecvPos > RECV_BUF_SIZE )
	{
		this->CStream::DetailedCloseInfo(__FILE__, __LINE__, __FUNCTION__, "m_nRecvPos>RECV_BUF_SIZE");
		this->CStream::Close(0);
		return false;
	}

	m_wCurProcPKT = reinterpret_cast<PACKET*>(m_pRecvBuf)->PacketType;

	int processed_len = m_nRecvPos;
	if( !m_pProcess->OnRecv(m_pRecvBuf, &processed_len) )
	{
		this->CStream::DetailedCloseInfo(__FILE__, __LINE__, __FUNCTION__, "!m_pProcess->OnRecv(m_pRecvBuf,&processed_len)");
		this->CStream::Close(0);
		return false;
	}

	if( processed_len < 0 || processed_len > m_nRecvPos )
	{
		this->CStream::DetailedCloseInfo(__FILE__, __LINE__, __FUNCTION__, "processed_len<0||processed_len>m_nRecvPos");
		this->CStream::Close(0);
		return false;
	}

	if( processed_len == 0 && m_nRecvPos >= RECV_BUF_SIZE )
	{
		this->CStream::DetailedCloseInfo(__FILE__, __LINE__, __FUNCTION__, "processed_len==0&&m_nRecvPos>=RECV_BUF_SIZE");
		this->CStream::Close(0);
		return false;
	}

	if( processed_len > 0 )
	{
		int nRemain = m_nRecvPos - processed_len;
		if( nRemain <= 0 )
		{
			m_nRecvPos = 0;
		}
		else
		{
			memmove(m_pRecvBuf, &m_pRecvBuf[processed_len], nRemain);
			m_nRecvPos = nRemain;
		}
	}

	memset(&m_ovRecv, 0, sizeof(m_ovRecv));
	m_ovRecv.m_byOperationCode = 1; // recv
	m_ovRecv.m_dwTryBytes = RECV_BUF_SIZE - m_nRecvPos;
	m_ovRecv.m_dwTransferredBytes = 0;

	WSABUF wsabuf;
	wsabuf.buf = &m_pRecvBuf[m_nRecvPos];
	wsabuf.len = RECV_BUF_SIZE - m_nRecvPos;

	DWORD dwReceivedBytes = 0;
	DWORD dwFlags = 0;
	if( WSARecv(m_socket, &wsabuf, 1, &dwReceivedBytes, &dwFlags, (LPWSAOVERLAPPED)&m_ovRecv, NULL) == SOCKET_ERROR )
	{
		if( WSAGetLastError() != WSA_IO_PENDING )
		{
			this->CStream::DetailedCloseInfo(__FILE__, __LINE__, __FUNCTION__, "WSAGetLastError()!=WSA_IO_PENDING");
			this->CStream::Close(0);
			return false;
		}
	}

	this->CStream::AddRef();
	return true;
}


bool CStream::Send(char* buf, DWORD dwLen, DWORD dwSessionID, bool bBroadCast)
{
	m_cs.Enter();
	if( m_dwSessionID == 0 || (!bBroadCast && dwSessionID != m_dwSessionID) )
	{
		m_cs.Leave();
		return false;
	}

	this->CStream::AddRef();
	m_cs.Leave();

	CSubRef subref(this);

	if( dwLen == 0 )
		return false;

	if( m_SendQueue.CCircleQueue::Insert(buf, dwLen) == FALSE )
	{
		char szIP[100] = {};
		CNetwork::GetObj()->CNetwork::GetTextIP(m_dwIP, szIP);

		this->CStream::DetailedCloseInfo(__FILE__, __LINE__, __FUNCTION__, "!m_SendQueue.Insert(buf,dwLen)");
		this->CStream::Close(0);

		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s - SendQueue FULL %s", __FUNCTION__, szIP);
		return false;
	}

	m_cs.Enter();
	if( m_dwSessionID == 0 || !m_bInitialSendPostPermit )
	{
		m_cs.Leave();
		return true;
	}

	m_bInitialSendPostPermit = false;
	m_cs.Leave();

	int nCopy = m_SendQueue.CCircleQueue::GetDataLength();
	if( nCopy > WSABUFFER_SIZE )
		nCopy = WSABUFFER_SIZE;

	if( nCopy < 0 )
	{
		this->CStream::DetailedCloseInfo(__FILE__, __LINE__, __FUNCTION__, "nCopy < 0");
		this->CStream::Close(0);
		return false;
	}

	if( nCopy == 0 )
	{
		m_cs.Enter();
		m_bInitialSendPostPermit = true;
		m_cs.Leave();
		return true;
	}

	if( m_SendQueue.CCircleQueue::Peek(m_ovSend.m_pBuf, nCopy) == FALSE )
	{
		this->CStream::DetailedCloseInfo(__FILE__, __LINE__, __FUNCTION__, "if(!m_SendQueue.Peek(m_ovSend.m_pBuf, nCopy))");
		this->CStream::Close(0);
		return false;
	}

	memset(&m_ovSend.m_overlapped, 0, sizeof(m_ovSend.m_overlapped));
	m_ovSend.m_byOperationCode = 2; // send
	m_ovSend.m_dwTryBytes = nCopy;
	m_ovSend.m_dwTransferredBytes = 0;

	WSABUF wsabuf;
	wsabuf.buf = m_ovSend.m_pBuf;
	wsabuf.len = nCopy;

	DWORD dwSendBytes = 0;
	if( WSASend(m_socket, &wsabuf, 1, &dwSendBytes, 0, (LPWSAOVERLAPPED)&m_ovSend, NULL) == SOCKET_ERROR )
	{
		if( WSAGetLastError() != WSA_IO_PENDING )
		{
			this->CStream::DetailedCloseInfo(__FILE__, __LINE__, __FUNCTION__, "if(WSAGetLastError()!=WSA_IO_PENDING)");
			this->CStream::Close(0);
			return false;
		}
	}

	this->CStream::AddRef();
	return true;
}


bool CStream::OnSendCompleted(OVERLAPPEDEX* lpOverlappedEx, DWORD dwTransferredBytes)
{
	CSubRef subref(this);

	if( dwTransferredBytes == 0 )
	{
		this->CStream::DetailedCloseInfo(__FILE__, __LINE__, __FUNCTION__, "if(dwTransferredBytes == 0)");
		this->CStream::Close(0);
		return false;
	}

	lpOverlappedEx->m_dwTransferredBytes += dwTransferredBytes;
	if( lpOverlappedEx->m_dwTransferredBytes == lpOverlappedEx->m_dwTryBytes )
	{
		if( !m_SendQueue.CCircleQueue::RemoveFrontData(lpOverlappedEx->m_dwTryBytes) )
		{
			this->CStream::DetailedCloseInfo(__FILE__, __LINE__, __FUNCTION__, "if(!m_SendQueue.RemoveFrontData(lpOverlappedEx->m_dwTryBytes))");
			this->CStream::Close(0);
			return false;
		}

		if( m_SendQueue.CCircleQueue::Empty() )
		{
			m_cs.Enter();
			m_bInitialSendPostPermit = true;
			m_cs.Leave();
			return true;
		}

		int nCopy = m_SendQueue.CCircleQueue::GetDataLength();
		if( nCopy > WSABUFFER_SIZE )
			nCopy = WSABUFFER_SIZE;

		if( nCopy <= 0 )
		{
			this->CStream::DetailedCloseInfo(__FILE__, __LINE__, __FUNCTION__, "if(nCopy<=0)");
			this->CStream::Close(0);
			return false;
		}

		if( m_SendQueue.CCircleQueue::Peek(m_ovSend.m_pBuf, nCopy) == FALSE )
		{
			this->CStream::DetailedCloseInfo(__FILE__, __LINE__, __FUNCTION__, "if(!m_SendQueue.Peek(m_ovSend.m_pBuf, nCopy))");
			this->CStream::Close(0);
			return false;
		}

		memset(&m_ovSend.m_overlapped, 0, sizeof(m_ovSend.m_overlapped));
		m_ovSend.m_byOperationCode = 2; // send
		m_ovSend.m_dwTryBytes = nCopy;
		m_ovSend.m_dwTransferredBytes = 0;

		WSABUF wsabuf;
		wsabuf.buf = m_ovSend.m_pBuf;
		wsabuf.len = nCopy;

		DWORD dwSendBytes = 0;
		if( WSASend(m_socket, &wsabuf, 1, &dwSendBytes, 0, (LPWSAOVERLAPPED)&m_ovSend, NULL) == SOCKET_ERROR )
		{
			if( WSAGetLastError() != WSA_IO_PENDING )
			{
				this->CStream::DetailedCloseInfo(__FILE__, __LINE__, __FUNCTION__, "if(WSAGetLastError()!=WSA_IO_PENDING)");
				this->CStream::Close(0);
				return false;
			}
		}

		this->CStream::AddRef();
		return true;
	}
	else
	if( lpOverlappedEx->m_dwTransferredBytes < lpOverlappedEx->m_dwTryBytes )
	{
		char szIP[100] = {};
		CNetwork::GetObj()->CNetwork::GetTextIP(m_dwIP, szIP);
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "send retry %d %d %s", lpOverlappedEx->m_dwTransferredBytes, lpOverlappedEx->m_dwTryBytes, szIP);

		if( lpOverlappedEx->m_dwTransferredBytes >= WSABUFFER_SIZE )
		{
			this->CStream::DetailedCloseInfo(__FILE__, __LINE__, __FUNCTION__, "if(lpOverlappedEx->m_dwTransferredBytes>=WSABUFFER_SIZE)");
			this->CStream::Close(0);
			return false;
		}

		memset(&lpOverlappedEx->m_overlapped, 0, sizeof(lpOverlappedEx->m_overlapped));
		lpOverlappedEx->m_byOperationCode = 2; // send

		int retry_len = lpOverlappedEx->m_dwTryBytes - lpOverlappedEx->m_dwTransferredBytes;

		WSABUF wsabuf;
		wsabuf.buf = &lpOverlappedEx->m_pBuf[lpOverlappedEx->m_dwTransferredBytes];
		wsabuf.len = retry_len;

		if( retry_len > WSABUFFER_SIZE || retry_len <= 0 )
		{
			this->CStream::DetailedCloseInfo(__FILE__, __LINE__, __FUNCTION__, "if(retry_len>WSABUFFER_SIZE||retry_len<=0)");
			this->CStream::Close(0);
			return false;
		}

		DWORD dwSendBytes = 0;
		if( WSASend(m_socket, &wsabuf, 1, &dwSendBytes, 0, (LPWSAOVERLAPPED)lpOverlappedEx, NULL) == SOCKET_ERROR )
		{
			if( WSAGetLastError() != WSA_IO_PENDING )
			{
				this->CStream::DetailedCloseInfo(__FILE__, __LINE__, __FUNCTION__, "if(WSAGetLastError()!=WSA_IO_PENDING)");
				this->CStream::Close(0);
				return false;
			}
		}

		this->CStream::AddRef();
		return true;
	}
	else //( lpOverlappedEx->m_dwTransferredBytes > lpOverlappedEx->m_dwTryBytes )
	{
		DWORD dwIP = m_dwIP;
		SOCKET sock = m_socket;

		this->CStream::Close(0);

		char szIP[100] = {};
		CNetwork::GetObj()->CNetwork::GetTextIP(dwIP, szIP);
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "lpOverlappedEx->m_dwTransferredBytes(%d) > lpOverlappedEx->m_dwTryBytes(%d) %s sock %d !!", lpOverlappedEx->m_dwTransferredBytes, lpOverlappedEx->m_dwTryBytes, szIP, sock);
		return false;
	}
}


void CStream::InternalClose()
{
	if( m_socket == INVALID_SOCKET )
		return;

	m_bInitialSendPostPermit = false;
	m_pProcess->CProcess::OnStreamClose();

	SOCKET s = m_socket;
	m_dwSessionID = 0;
	m_socket = INVALID_SOCKET;

	if( closesocket(s) != 0 )
	{
		char szIP[100] = {};
		CNetwork::GetObj()->CNetwork::GetTextIP(m_dwIP, szIP);
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s - closesocket error, wsagle - %d, %s", __FUNCTION__, WSAGetLastError(), szIP);
	}

	m_dwLastRecvTime = 0;
	m_dwPingTime = 0;
	m_bRecvPermit = false;
	m_dwIP = 0;

	this->CStream::SubRef();
}


void CStream::Close(DWORD dwTime)
{
	m_cs.Enter();

	if( dwTime != 0 )
	{
		m_dwLastRecvTime = timeGetTime();
		m_dwPingTime = dwTime;
		m_bRecvPermit = false;
		m_bInitialSendPostPermit = false;
	}
	else
	{
		this->CStream::InternalClose();
	}

	m_cs.Leave();
}


bool CStream::CloseOuter(DWORD dwSessionID, DWORD dwTime)
{
	m_cs.Enter();

	if( m_dwSessionID == 0 || dwSessionID != m_dwSessionID )
	{
		m_cs.Leave();
		return false;
	}

	m_cs.Leave();

	this->CStream::Close(dwTime);
	return true;
}


void CStream::CheckPingTime()
{
	m_cs.Enter();

	if( m_dwPingTime != 0 && m_dwSessionID != 0 )
	{
		if( timeGetTime() - m_dwLastRecvTime > m_dwPingTime )
		{
			this->CStream::DetailedCloseInfo(__FILE__, __LINE__, __FUNCTION__, "if(timeGetTime()-m_dwLastRecvTime>m_dwPingTime)");
			this->CStream::InternalClose();
		}

		m_pProcess->OnIdle();
	}

	m_cs.Leave();
}


void CStream::SetConnected(bool bConnected)
{
	m_cs.Enter();
	m_bConnected = bConnected;
	m_cs.Leave();
}


bool CStream::IsConnected()
{
	bool result;
	m_cs.Enter();
	result = m_bConnected;
	m_cs.Leave();
	return result;
}


DWORD CStream::GetSessionID()
{
	return m_dwSessionID;
}


DWORD CStream::GetIP()
{
	return m_dwIP;
}


bool CStream::IsRecvPermit()
{
	return m_bRecvPermit;
}


void CStream::UpdateReceivedTime()
{
	m_cs.Enter();
	m_dwLastRecvTime = timeGetTime();
	m_cs.Leave();
}


/// @custom
void CStream::DetailedCloseInfo(const char* szFile, const int nLine, const char* szFunc, const char* szReason)
{
	if( m_bDetailedCloseInfo )
	{
		char szIP[100] = {};
		CNetwork::GetObj()->CNetwork::GetTextIP(m_dwIP, szIP);
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(szFile, nLine, "closed %s) func %s, reason %s", szIP, szFunc, szReason);
	}
}
