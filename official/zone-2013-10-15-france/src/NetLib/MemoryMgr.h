#pragma once
#include "shared/N3System/N3SyncObject.h"


template<typename T> class CMemoryMgr
{
public:
	bool Init(const int in_size);
	T* Alloc();
	void Free(T* in_cpObject);
	int GetFreeSize() const;
	int GetAllocSize() const;
	void Reset();
	int GetCapacity() const;

public:
	CMemoryMgr();
	virtual ~CMemoryMgr();
	CMemoryMgr(CMemoryMgr&); // = delete;
	CMemoryMgr& operator=(CMemoryMgr&); // = delete;

private:
	class lcMemory
	{
	public:
		/* this+0 */ //const CMemoryMgr<T>::lcMemory::`vftable';
		/* this+4 */ T* m_pObject;
		/* this+8 */ bool m_bUsed;

	public:
		lcMemory() : m_pObject(NULL), m_bUsed(false) { }
		virtual ~lcMemory() { }
	};

private:
	/* this+ 0 */ //const CMemoryMgr<T>::`vftable';
	/* this+ 4 */ lcMemory* m_MemoryPool;
	/* this+ 8 */ int m_MemoryCnt;
	/* this+12 */ RTL_CRITICAL_SECTION m_cs;
};


template<typename T> CMemoryMgr<T>::CMemoryMgr()
: m_MemoryPool(NULL), m_MemoryCnt(0)
{
	InitializeCriticalSection(&m_cs);
}


template<typename T> CMemoryMgr<T>::~CMemoryMgr()
{
	if( m_MemoryPool != NULL )
	{
		for( int idx = 0; idx < m_MemoryCnt; ++idx )
		{
			if( m_MemoryPool[idx].m_pObject != NULL )
			{
				delete m_MemoryPool[idx].m_pObject;
				m_MemoryPool[idx].m_pObject = NULL;
			}
		}

		delete[] m_MemoryPool;
		m_MemoryPool = NULL;
	}

	DeleteCriticalSection(&m_cs);
}


template<typename T> bool CMemoryMgr<T>::Init(const int in_size)
{
	N3SyncObject sync(m_cs);

	if( m_MemoryPool != NULL )
	{
		delete[] m_MemoryPool;
		m_MemoryPool = NULL;
	}

	m_MemoryCnt = in_size;
	m_MemoryPool = new(std::nothrow) lcMemory[in_size];
	if( m_MemoryPool == NULL )
	{
		m_MemoryCnt = 0;
		return false;
	}

	for( int idx = 0; idx < m_MemoryCnt; ++idx )
	{
		m_MemoryPool[idx].m_pObject = new(std::nothrow) T;
		if( m_MemoryPool[idx].m_pObject == NULL )
			return false; // alloc fail
	}

	return true;
}


template<typename T> T* CMemoryMgr<T>::Alloc()
{
	N3SyncObject sync(m_cs);

	T* result = NULL;

	for( int idx = 0; idx < m_MemoryCnt; ++idx )
	{
		if( !m_MemoryPool[idx].m_bUsed )
		{
			m_MemoryPool[idx].m_bUsed = true;
			result = m_MemoryPool[idx].m_pObject;
			break;
		}
	}

	return result;
}


template<typename T> void CMemoryMgr<T>::Free(T* in_cpObject)
{
	N3SyncObject sync(m_cs);

	for( int idx = 0; idx < m_MemoryCnt; ++idx )
	{
		if( m_MemoryPool[idx].m_pObject == in_cpObject )
		{
			m_MemoryPool[idx].m_bUsed = false;
			break;
		}
	}
}


template<typename T> int CMemoryMgr<T>::GetFreeSize() const
{
	N3SyncObject sync(const_cast<RTL_CRITICAL_SECTION&>(m_cs));

	int nCount = 0;

	for( int idx = 0; idx < m_MemoryCnt; ++idx )
		if( !m_MemoryPool[idx].m_bUsed )
			++nCount;

	return nCount;
}


template<typename T> int CMemoryMgr<T>::GetAllocSize() const
{
	N3SyncObject sync(const_cast<RTL_CRITICAL_SECTION&>(m_cs));

	int nCount = 0;

	for( int idx = 0; idx < m_MemoryCnt; ++idx )
		if( m_MemoryPool[idx].m_bUsed )
			++nCount;

	return nCount;
}


template<typename T> void CMemoryMgr<T>::Reset()
{
	N3SyncObject sync(m_cs);

	for( int idx = 0; idx < m_MemoryCnt; ++idx )
		m_MemoryPool[idx].m_bUsed = false;
}


template<typename T> int CMemoryMgr<T>::GetCapacity() const
{
	return m_MemoryCnt;
}
