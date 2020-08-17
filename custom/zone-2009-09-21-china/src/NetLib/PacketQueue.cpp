#include "Custom/Settings.h"
#include "NetLib/PacketQueue.h"


CPacketQueue::CPacketQueue(void) // line 7
{
	InitializeCriticalSection(&m_cs);
	m_buf = NULL;
}


CPacketQueue::CPacketQueue(int capacity) // line ??
{
	InitializeCriticalSection(&m_cs);
	m_buf = NULL;

	this->CPacketQueue::Init(capacity);
}


CPacketQueue::~CPacketQueue(void) // line 20
{
	if( m_buf )
	{
		delete[] m_buf;
		m_buf = NULL;
	}

	DeleteCriticalSection(&m_cs);
}


hook_method<void (CPacketQueue::*)(int capacity)> CPacketQueue::_Init(SERVER, "CPacketQueue::Init");
HOOKED void CPacketQueue::Init(int capacity) // line 29
{
	capacity = min(capacity, CSettings::GetObj()->max_stream_buffer);
	return (this->*_Init)(capacity);

	EnterCriticalSection(&m_cs);

	m_capacity = capacity;
	m_front = 0;
	m_rear = 0;
	m_size = 0;

	if( m_buf )
		delete[] m_buf;

	m_buf = new char[m_capacity];

	LeaveCriticalSection(&m_cs);
}


hook_method<void (CPacketQueue::*)(void)> CPacketQueue::_Reset(SERVER, "CPacketQueue::Reset");
void CPacketQueue::Reset(void) // line 47
{
	return (this->*_Reset)();

	EnterCriticalSection(&m_cs);

	m_front = 0;
	m_rear = 0;
	m_size = 0;

	LeaveCriticalSection(&m_cs);
}


hook_method<int  (CPacketQueue::*)(int len, const char* src)> CPacketQueue::_InsertData(SERVER, "CPacketQueue::InsertData");
int CPacketQueue::InsertData(int len, const char* src) // line 73
{
	return (this->*_InsertData)(len, src);

	EnterCriticalSection(&m_cs);

	if( m_size + len > m_capacity )
	{
		LeaveCriticalSection(&m_cs);
		return -1;
	}

	m_size += len;

	int rest = m_capacity - m_rear;

	if( len > rest )
	{// cyclic
		memcpy(&m_buf[m_rear], &src[0], rest);
		memcpy(&m_buf[0], &src[rest], len - rest);
		m_rear = len - rest;
	}
	else
	{// linear
		memcpy(&m_buf[m_rear], &src[0], len);
		m_rear += len;
		if( m_rear >= m_capacity )
			m_rear -= m_capacity;
	}

	int result = m_size;
	LeaveCriticalSection(&m_cs);

	return result;
}


hook_method<int  (CPacketQueue::*)(int len)> CPacketQueue::_RemoveData(SERVER, "CPacketQueue::RemoveData");
int CPacketQueue::RemoveData(int len) // line 197
{
	return (this->*_RemoveData)(len);

	EnterCriticalSection(&m_cs);

	m_size -= len;
	m_front += len;
	if( m_front >= m_capacity )
		m_front -= m_capacity;

	int result = m_size;
	LeaveCriticalSection(&m_cs);

	return result;
}


hook_method<void (CPacketQueue::*)(int len, char* dst)> CPacketQueue::_PeekData(SERVER, "CPacketQueue::PeekData");
void CPacketQueue::PeekData(int len, char* dst) // line 162
{
	return (this->*_PeekData)(len, dst);

	EnterCriticalSection(&m_cs);

	if( m_front + len > m_capacity )
	{// cyclic
		int blsize = m_capacity - m_front;
		memcpy(&dst[0], &m_buf[m_front], blsize);
		memcpy(&dst[blsize], &m_buf[0], len - blsize);
	}
	else
	{// linear
		memcpy(&dst[0], &m_buf[m_front], len);
	}

	LeaveCriticalSection(&m_cs);
}


hook_method<int (CPacketQueue::*)(int len, char* dst)> CPacketQueue::_GetData(SERVER, "CPacketQueue::GetData");
int CPacketQueue::GetData(int len, char* dst) // line 109
{
	return (this->*_GetData)(len, dst);

	EnterCriticalSection(&this->m_cs);

	if( len < 0 || len > m_size )
	{
		LeaveCriticalSection(&m_cs);
		return -1;
	}

	m_size -= len;

	if ( m_front + len > m_capacity )
	{// cyclic
		int blsize = m_capacity - m_front;
		memcpy(&dst[0], &m_buf[m_front], blsize);
		memcpy(&dst[blsize], &m_buf[0], len - blsize);
		m_front = len - blsize;
	}
	else
	{// linear
		memcpy(&dst[0], &m_buf[m_front], len);
		m_front += len;
		if( m_front >= m_capacity )
			m_front -= m_capacity;
	}

	LeaveCriticalSection(&m_cs);

	return len;
}


hook_method<int (CPacketQueue::*)(void)> CPacketQueue::_GetSize(SERVER, "CPacketQueue::GetSize");
int CPacketQueue::GetSize(void) // line ??
{
	return (this->*_GetSize)();

	return m_size;
}


hook_method<int (CPacketQueue::*)(void)> CPacketQueue::_GetFreeSize(SERVER, "CPacketQueue::GetFreeSize");
int CPacketQueue::GetFreeSize(void) // line 211
{
	return (this->*_GetFreeSize)();

	EnterCriticalSection(&m_cs);
	int result = m_capacity - m_size;
	LeaveCriticalSection(&m_cs);

	return result;
}
