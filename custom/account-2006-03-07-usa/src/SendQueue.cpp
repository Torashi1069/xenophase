#include "Client_.h"
#include "SendQueue.h"
#include "Common/Reporter.h"


CSendQueue::CSendQueue()
{
	front = 0;
	rear = 0;

	for( int i = 0; i < countof(Packet); ++i )
	{
		PacketSize[i] = 0;
		Packet[i] = NULL;
	}
}


CSendQueue::~CSendQueue()
{
	for( int i = 0; i < countof(Packet); ++i )
	{
		if( Packet[i] != NULL )
		{
			free(Packet[i]);
			Packet[i] = NULL;
		}
	}
}


void CSendQueue::Init()
{
	for( int i = 0; i < countof(Packet); ++i )
	{
		if( Packet[i] != NULL )
		{
			free(Packet[i]);
			Packet[i] = NULL;
		}
	}

	front = 0;
	rear = 0;
	m_dwCount = 0;

	for( int i = 0; i < countof(Packet); ++i )
	{
		PacketSize[i] = 0;
		Packet[i] = NULL;
	}
}


BOOL CSendQueue::InsertQueue(char* packet, int MsgSize, int TotalSendSize)
{
	m_csSendQueue.CCriticalSection::Enter();
	int next = rear + 1;
	if( rear >= countof(Packet) )
		next = 0;
	if( next == front )
	{
		m_csSendQueue.CCriticalSection::Leave();
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CSendQueue FULL !!!!!\n");
		return TRUE;
	}
	m_csSendQueue.CCriticalSection::Leave();

	if( Packet[rear] != NULL )
	{
		free(Packet[rear]);
		Packet[rear] = NULL;
	}

	Packet[rear] = (char*)malloc(MsgSize - TotalSendSize);
	if( Packet[rear] == NULL )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CSendQueue InsertQueue fail !!!!!\n");
		return TRUE;
	}

	memcpy(Packet[rear], &packet[TotalSendSize], MsgSize - TotalSendSize);
	PacketSize[rear] = MsgSize - TotalSendSize;
	SentSize[rear] = TotalSendSize;

	m_csSendQueue.CCriticalSection::Enter();
	++rear;
	if( rear >= countof(Packet) )
		rear = 0;
	m_csSendQueue.CCriticalSection::Leave();

	InterlockedIncrement(&m_dwCount);
	return TRUE;
}


bool CSendQueue::ProcessQueue(CClient_* pClient)
{
	LONG nCount = m_dwCount;
	while( nCount != 0 )
	{
		m_csSendQueue.Enter();
		if( rear == front )
		{
			m_csSendQueue.Leave();
			return true;
		}
		m_csSendQueue.Leave();

		int nSent = send(pClient->m_socket, &Packet[front][SentSize[front]], PacketSize[front] - SentSize[front], 0);
		if( nSent == SOCKET_ERROR )
		{
			DWORD gle = WSAGetLastError();
			if( gle == WSAEWOULDBLOCK )
			{
				pClient->m_bSendable = false;
				return true;
			}
			else
			{
				CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("send error gle: %d\n", gle);
				return false;
			}
		}

		SentSize[front] += nSent;
		if( SentSize[front] == PacketSize[front] )
		{
			m_csSendQueue.Enter();
			free(Packet[front]);
			Packet[front] = NULL;
			++front;
			if( front >= countof(Packet) )
				front = 0;
			m_csSendQueue.Leave();

			InterlockedDecrement(&m_dwCount);
			--nCount;
		}
	}

	return true;
}


LONG CSendQueue::GetCount()
{
	return m_dwCount;
}
