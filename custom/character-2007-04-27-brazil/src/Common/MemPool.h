#pragma once
#include "Common/CriticalSection.h"
#include "Common/Reporter.h"


struct SPOOLOBJECT
{
	/* this+0 */ void* m_pObj;
	/* this+4 */ SPOOLOBJECT* m_pNext;
	/* this+8 */ bool m_bAllocated;
};


template<typename T> class CMemPool
{
private:
	/* this+ 0 */ CCriticalSection m_csMemPool;
	/* this+24 */ int m_nSize;
	/* this+28 */ int m_nAllocatedCount;
	/* this+32 */ SPOOLOBJECT* m_pFreeObjList;
	/* this+36 */ SPOOLOBJECT* m_pObjPoolArray;
	/* this+40 */ T* m_pObjArray;
	/* this+44 */ T* m_pStartPos;
	/* this+48 */ T* m_pEndPos;

public:
	CMemPool();
//	CMemPool(int);
	~CMemPool();
	int GetSize();
	int GetAllocatedCount();
	bool Create(int nCount);
	void Destroy();
	T* Allocate();
	bool Free(T* pObject);
//	T* begin();
//	T* end();
};


template<typename T> CMemPool<T>::CMemPool()
{
	m_nAllocatedCount = 0;
	m_nSize = 0;
	m_pFreeObjList = NULL;
	m_pStartPos = NULL;
	m_pEndPos = NULL;
	m_pObjPoolArray = NULL;
	m_pObjArray = NULL;
}


template<typename T> CMemPool<T>::~CMemPool()
{
	this->CMemPool<T>::Destroy();
}


template<typename T> int CMemPool<T>::GetSize()
{
	return m_nSize;
}


template<typename T> int CMemPool<T>::GetAllocatedCount()
{
	return m_nAllocatedCount;
}


template<typename T> bool CMemPool<T>::Create(int nCount)
{
	if( nCount < 1 || nCount > 2100000000 )
		return false;

	this->CMemPool<T>::Destroy();

	m_csMemPool.Enter();

	m_pFreeObjList = NULL;
	m_nSize = nCount;

	m_pObjPoolArray = new SPOOLOBJECT[nCount];
	if( m_pObjPoolArray == NULL )
	{
		m_csMemPool.Leave();
		return false;
	}

	m_pObjArray = new T[nCount];
	if( m_pObjArray == NULL )
	{
		m_csMemPool.Leave();
		return false;
	}

	m_pStartPos = &m_pObjArray[0];
	m_pEndPos = &m_pObjArray[nCount - 1];
	memset(m_pObjPoolArray, 0, nCount * sizeof(*m_pObjPoolArray));

	for( int i = nCount - 1; i >= 0; --i )
	{
		m_pObjPoolArray[i].m_pObj = &m_pObjArray[i];
		m_pObjPoolArray[i].m_pNext = m_pFreeObjList;
		m_pObjPoolArray[i].m_bAllocated = false;
		m_pFreeObjList = &m_pObjPoolArray[i];
	}

	m_csMemPool.Leave();
	return true;
}


template<typename T> void CMemPool<T>::Destroy()
{
	m_csMemPool.Enter();

	if( m_pObjPoolArray != NULL )
	{
		delete[] m_pObjPoolArray;
		m_pObjPoolArray = NULL;
	}

	if( m_pObjArray != NULL )
	{
		delete[] m_pObjArray;
		m_pObjArray = NULL;
	}

	m_nAllocatedCount = 0;
	m_nSize = 0;
	m_pFreeObjList = NULL;
	m_pStartPos = NULL;
	m_pEndPos = NULL;

	m_csMemPool.Leave();
}


template<typename T> T* CMemPool<T>::Allocate()
{
	T* result = NULL;
	m_csMemPool.Enter();

	if( m_pFreeObjList != NULL )
	{
		if( m_pFreeObjList->m_bAllocated )
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("already allocated - %s\n", __FUNCTION__);

		result = reinterpret_cast<T*>(m_pFreeObjList->m_pObj);

		m_pFreeObjList->m_bAllocated = true;
		m_pFreeObjList = m_pFreeObjList->m_pNext;
		++m_nAllocatedCount;
	}

	m_csMemPool.Leave();
	return result;
}


template<typename T> bool CMemPool<T>::Free(T* pObject)
{
	m_csMemPool.Enter();

	if( pObject < m_pStartPos || pObject > m_pEndPos )
	{// out of range
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("out of range - %s\n", __FUNCTION__);
		m_csMemPool.Leave();
		return false;
	}

	int offset = (char*)pObject - (char*)m_pObjArray;
	if( offset / sizeof(T) * sizeof(T) != offset )
	{// misaligned pointer
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("invalid pos - %s\n", __FUNCTION__);
		m_csMemPool.Leave();
		return false;
	}

	int index = offset / sizeof(T);
	if( !m_pObjPoolArray[index].m_bAllocated )
	{// already freed
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("already free - %s\n", __FUNCTION__);
		m_csMemPool.Leave();
		return false;
	}

	m_pObjPoolArray[index].m_bAllocated = false;
	m_pObjPoolArray[index].m_pNext = m_pFreeObjList;
	m_pFreeObjList = &m_pObjPoolArray[index];
	--m_nAllocatedCount;

	m_csMemPool.Leave();
	return true;
}
