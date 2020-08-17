#include "NetLib/PacketQueue.h"
#include "shared/NSystem/NSyncObject.h"


CPacketQueue::CPacketQueue()
{
	InitializeCriticalSection(&m_cs);
	m_buf = NULL;
}


CPacketQueue::CPacketQueue(int capacity)
{
	InitializeCriticalSection(&m_cs);
	m_buf = NULL;

	this->CPacketQueue::Init(capacity);
}


CPacketQueue::~CPacketQueue()
{
	if( m_buf != NULL )
	{
		delete[] m_buf;
		m_buf = NULL;
	}

	DeleteCriticalSection(&m_cs);
}


void CPacketQueue::Init(int capacity)
{
	EnterCriticalSection(&m_cs);

	m_capacity = capacity;
	m_front = 0;
	m_rear = 0;
	m_size = 0;

	delete[] m_buf;
	m_buf = new char[m_capacity];

	LeaveCriticalSection(&m_cs);
}


void CPacketQueue::Reset()
{
	EnterCriticalSection(&m_cs);

	m_front = 0;
	m_rear = 0;
	m_size = 0;

	LeaveCriticalSection(&m_cs);
}


int CPacketQueue::GetSize()
{
	return m_size;
}


int CPacketQueue::resetANDinsert(const int in_Bytes, const char* in_pData)
{
	NSyncObject sync(m_cs);

	this->CPacketQueue::Reset();
	return this->CPacketQueue::InsertData(in_Bytes, in_pData);
}


int CPacketQueue::InsertData(int len, const char* src)
{
	EnterCriticalSection(&m_cs);

	if( m_size + len > m_capacity )
	{
		LeaveCriticalSection(&m_cs);
		return -1;
	}

	m_size += len;

	int right = m_capacity - m_rear;
	if( len > right )
	{// cyclic
		int left = len - right;
		memcpy(&m_buf[m_rear], src, right);
		memcpy(&m_buf[0], src + right, left);
		m_rear = left;
	}
	else
	{// linear
		memcpy(&m_buf[m_rear], src, len);
		m_rear += len;
		if( m_rear >= m_capacity )
			m_rear -= m_capacity;
	}

	int result = m_size;
	LeaveCriticalSection(&m_cs);

	return result;
}


int CPacketQueue::GetData(int len, char* dst)
{
	EnterCriticalSection(&m_cs);

	if( len < 0 || len > m_size )
	{
		LeaveCriticalSection(&m_cs);
		return -1;
	}

	m_size -= len;

	int right = m_capacity - m_front;
	if( len > right )
	{// cyclic
		int left = len - right;
		memcpy(dst, &m_buf[m_front], right);
		memcpy(dst + right, &m_buf[0], left);
		m_front = left;
	}
	else
	{// linear
		memcpy(dst, &m_buf[m_front], len);
		m_front += len;
		if( m_front >= m_capacity )
			m_front -= m_capacity;
	}

	LeaveCriticalSection(&m_cs);

	return len;
}


void CPacketQueue::PeekData(int len, char* dst)
{
	EnterCriticalSection(&m_cs);

	int right = m_capacity - m_front;
	if( len > right )
	{// cyclic
		int left = len - right;
		memcpy(dst, &m_buf[m_front], right);
		memcpy(dst + right, &m_buf[0], left);
	}
	else
	{// linear
		memcpy(dst, &m_buf[m_front], len);
	}

	LeaveCriticalSection(&m_cs);
}


int CPacketQueue::RemoveData(int len)
{
	EnterCriticalSection(&m_cs);

	m_size -= len;

	m_front += len;
	if( m_front >= m_capacity )
		m_front -= m_capacity;

	int result = m_size;
	LeaveCriticalSection(&m_cs);

	return result;
}


int CPacketQueue::GetFreeSize()
{
	EnterCriticalSection(&m_cs);
	int result = m_capacity - m_size;
	LeaveCriticalSection(&m_cs);

	return result;
}
