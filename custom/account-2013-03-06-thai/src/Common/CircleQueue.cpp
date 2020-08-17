#include "Common/CircleQueue.h"


CCircleQueue::CCircleQueue()
{
//	m_nBufferSize = 0;
	m_nFront = 0;
	m_nRear = 0;
	m_nDataLength = 0;
	m_pbyQueue = NULL;
}


CCircleQueue::~CCircleQueue()
{
	if( m_pbyQueue != NULL )
	{
		delete[] m_pbyQueue;
		m_pbyQueue = NULL;
	}
}


bool CCircleQueue::Create(int nSize)
{
	if( nSize <= 0 )
		return false;

	m_cs.Enter();

	if( m_pbyQueue == NULL || m_nBufferSize != nSize )
	{
		// remove existing buffer
		if( m_pbyQueue != NULL )
		{
			delete[] m_pbyQueue;
			m_pbyQueue = NULL;
		}

		// allocate new buffer
		m_pbyQueue = new BYTE[nSize];
		if( m_pbyQueue == NULL )
		{
			m_cs.Leave();
			return false;
		}

		m_nBufferSize = nSize;
	}

	m_cs.Leave();

	this->CCircleQueue::ClearBuffer();
	return true;
}


void CCircleQueue::ClearBuffer()
{
	m_cs.Enter();

	m_nFront = 0;
	m_nRear = 0;
	m_nDataLength = 0;

	m_cs.Leave();
}


int CCircleQueue::GetDataLength()
{
	int nDataLength;
	m_cs.Enter();

	nDataLength = m_nDataLength;

	m_cs.Leave();
	return nDataLength;
}


BOOL CCircleQueue::Insert(void* pData, int nLength)
{
	m_cs.Enter();

	if( this->CCircleQueue::IsOverflow(nLength) )
	{// not enough free space
		m_cs.Leave();
		return FALSE;
	}

	if( m_nRear < m_nFront )
	{// wrapped around, gap used is [m_nRear, m_nFront)
		memcpy(&m_pbyQueue[m_nRear], pData, nLength);
		m_nRear += nLength;
	}
	else
	if( m_nRear + nLength <= m_nBufferSize )
	{// simple append, gap used is [m_nRear, m_nBufferSize)
		memcpy(&m_pbyQueue[m_nRear], pData, nLength);
		m_nRear = (m_nRear + nLength) % m_nBufferSize;
	}
	else
	{// split, gap used is [m_nRear, m_nBufferSize) + [0, m_nFront)
		int nRearCapacity = m_nBufferSize - m_nRear;
		memcpy(&m_pbyQueue[m_nRear], (BYTE*)pData, nRearCapacity);
		memcpy(&m_pbyQueue[0], (BYTE*)pData + nRearCapacity, nLength - nRearCapacity);
		m_nRear = nLength - nRearCapacity;
	}

	m_nDataLength += nLength;

	m_cs.Leave();
	return TRUE;
}


BOOL CCircleQueue::Peek(void* pData, int nLength)
{
	m_cs.Enter();

	if( this->CCircleQueue::IsUnderflow(nLength) )
	{// not enough data
		m_cs.Leave();
		return FALSE;
	}

	int nFrontSize = m_nBufferSize - m_nFront;
	if( nLength <= nFrontSize )
	{
		memcpy((BYTE*)pData, &m_pbyQueue[m_nFront], nLength);
	}
	else
	{
		memcpy((BYTE*)pData, &m_pbyQueue[m_nFront], nFrontSize);
		memcpy((BYTE*)pData + nFrontSize, &m_pbyQueue[0], nLength - nFrontSize);
	}

	m_cs.Leave();
	return TRUE;
}


BOOL CCircleQueue::Get(void* pData, int nLength)
{
	m_cs.Enter();

	if( this->CCircleQueue::IsUnderflow(nLength) )
	{// not enough data
		m_cs.Leave();
		return FALSE;
	}

	int nFrontSize = m_nBufferSize - m_nFront;
	if( nLength <= nFrontSize )
	{
		memcpy((BYTE*)pData, &m_pbyQueue[m_nFront], nLength);
		m_nFront = (m_nFront + nLength) % m_nBufferSize;
	}
	else
	{
		memcpy((BYTE*)pData, &m_pbyQueue[m_nFront], nFrontSize);
		memcpy((BYTE*)pData + nFrontSize, &m_pbyQueue[0], nLength - nFrontSize);
		m_nFront = nLength - nFrontSize;
	}

	m_nDataLength -= nLength;

	m_cs.Leave();
	return TRUE;
}


bool CCircleQueue::RemoveFrontData(int nLength)
{
	m_cs.Enter();

	if( this->CCircleQueue::IsUnderflow(nLength) )
	{// not enough data
		m_cs.Leave();
		return false;
	}

	int nFrontAmount = m_nBufferSize - m_nFront;
	if( nLength <= nFrontAmount )
	{
		m_nFront = (m_nFront + nLength) % m_nBufferSize;
	}
	else
	{
		m_nFront = nLength - nFrontAmount;
	}

	m_nDataLength -= nLength;

	m_cs.Leave();
	return true;
}


int CCircleQueue::GetFreeSize()
{
	int nFreeSize;
	m_cs.Enter();

	nFreeSize = m_nBufferSize - m_nDataLength;

	m_cs.Leave();
	return nFreeSize;
}


int CCircleQueue::GetBufferSize()
{
	return m_nBufferSize;
}


bool CCircleQueue::Empty()
{
	bool bResult;
	m_cs.Enter();

	bResult = ( m_nDataLength == 0 );

	m_cs.Leave();
	return bResult;
}


int CCircleQueue::IsOverflow(int nLength)
{
	return ( nLength + m_nDataLength > m_nBufferSize );
}


int CCircleQueue::IsUnderflow(int nLength)
{
	return ( nLength > m_nDataLength );
}
