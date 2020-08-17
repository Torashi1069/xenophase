#include "Client_.h"
#include "Common/EnterTraceLog.h"
#include "Common/Network.h"


CClient_::CClient_()
{
	m_socket = INVALID_SOCKET;
	m_bProcessPermit = true;
	m_bConnected = false;
	m_bSendable = false;
	m_LastSendTime = time(NULL);
}


CClient_::~CClient_()
{
	if( m_socket != INVALID_SOCKET )
	{
		closesocket(m_socket);
		m_socket = INVALID_SOCKET;
	}
}


void CClient_::Init()
{
	m_qSend.CSendQueue::Init();
	m_qReceive.CReceiveQueue::Init();
	m_socket = INVALID_SOCKET;
	m_bConnected = false;
	m_bSendable = false;
	m_LastSendTime = time(NULL);
}


SOCKET CClient_::GetSocket()
{
	return m_socket;
}


bool CClient_::Send(char* Packet, int MsgSize)
{
	if( !m_bProcessPermit || !m_bConnected )
		return false;

	m_qSend.CSendQueue::InsertQueue(Packet, MsgSize, 0);
	return true;
}


BOOL CClient_::Recv()
{
	int nCapacity = sizeof(m_qReceive.Queue) - m_qReceive.CurPos;
	if( nCapacity < 0 )
		return FALSE;

	BOOL result = TRUE;
	if( nCapacity > 0 )
	{
		result = recv(m_socket, &m_qReceive.Queue[m_qReceive.CurPos], nCapacity, 0);
		if( result <= 0 )
		{
			char tmp[20];
			CNetwork::GetObj()->CNetwork::GetTextIP(m_dwIP, tmp);
			CEnterTraceLog::GetObj()->CEnterTraceLog::LogFile("billing.txt", "%s recv failed.. recv returned %d gle: %d", tmp, result, WSAGetLastError());
			return FALSE;
		}

		m_qReceive.CurPos += result;
	}

	int nProcessed;
	do
	{
		nProcessed = m_qReceive.CurPos - m_qReceive.Pos;
		if( !this->Process(&m_qReceive.Queue[m_qReceive.Pos], &nProcessed) )
			return FALSE;

		m_qReceive.Pos += nProcessed;
	}
	while( nProcessed != 0 );

	if( m_qReceive.Pos > 0 )
	{
		memmove(&m_qReceive.Queue[0], &m_qReceive.Queue[m_qReceive.Pos], m_qReceive.CurPos - m_qReceive.Pos);
		m_qReceive.CurPos -= m_qReceive.Pos;
		m_qReceive.Pos = 0;
	}

	return result;
}


// guessed
time_t CClient_::GetSendCount()
{
	return m_LastSendTime;
}
