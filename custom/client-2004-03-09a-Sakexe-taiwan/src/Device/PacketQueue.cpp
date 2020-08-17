#include "Device/PacketQueue.h"


CPacketQueue::CPacketQueue()
{
	m_buf = NULL;
}


CPacketQueue::CPacketQueue(int capacity)
{
	m_buf = NULL;
	this->CPacketQueue::Init(capacity);
}


CPacketQueue::~CPacketQueue()
{
}


int CPacketQueue::GetSize() const
{
	return m_rearPos - m_frontPos;
}


void CPacketQueue::Init(int capacity)
{
	m_frontPos = 0;
	m_rearPos = 0;
	m_buffer.resize(capacity);
	m_buf = &m_buffer[0];
}


void CPacketQueue::InsertData(int len, const char* src)
{
	int capacity = this->CPacketQueue::GetSafeDataLen();
	if( m_rearPos + len > capacity )
	{// no more room to append
		if( m_rearPos - m_frontPos + len > capacity )
		{// not enough overall capacity, add more
			m_buffer.resize(2 * m_buffer.size());
			m_buf = &m_buffer[0]; // refresh
		}

		// shift everything to beginning of buffer
		memmove(&m_buf[0], &m_buf[m_frontPos], m_rearPos - m_frontPos);
		m_rearPos -= m_frontPos;
		m_frontPos = 0;
	}

	// append data
	memcpy(&m_buf[m_rearPos], src, len);
	m_rearPos += len;
}


bool CPacketQueue::GetData(int len, char* dst)
{
	if( len > this->CPacketQueue::GetSize() )
		return false;

	memcpy(dst, &m_buf[m_frontPos], len);
	m_frontPos += len;
	return true;
}


bool CPacketQueue::PeekData(int len, char* dst) const
{
	if( len > this->CPacketQueue::GetSize() )
		return false;

	memcpy(dst, &m_buf[m_frontPos], len);
	return true;
}


bool CPacketQueue::RemoveData(int len)
{
	if( len > this->CPacketQueue::GetSize() )
		return false;

	m_frontPos += len;
	return true;
}


int CPacketQueue::GetSafeDataLen()
{
	return (int)m_buffer.size();
}


char* CPacketQueue::GetDataPtr()
{
	return &m_buf[m_frontPos];
}
