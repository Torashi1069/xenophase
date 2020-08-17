#pragma once
#include "shared/CVTBLErrorLog.h"
#include "shared/N3System/N3SyncObject.h"


template<typename T> class CMemoryMgr2
{
public:
	bool Init(const int in_size);
	T* Alloc();
	void Free(T* in_cpObject);
	int GetFreeSize() const;
	int GetAllocSize() const;
	void Reset();
	int GetCapacity();

public:
	CMemoryMgr2();
	virtual ~CMemoryMgr2();
	CMemoryMgr2(CMemoryMgr2&); // = delete;
	CMemoryMgr2& operator=(CMemoryMgr2&); // = delete;

private:
	class lcMemory
	{
	public:
		/* this+0 */ //const CMemoryMgr2<T>::lcMemory::`vftable';
		/* this+4 */ T* m_pObject;
		/* this+8 */ bool m_bUsed;

	public:
		lcMemory() : m_pObject(NULL), m_bUsed(false) { }
		virtual ~lcMemory() { }
	};

private:
	/* this+ 0 */ //const CMemoryMgr2<T>::`vftable';
	/* this+ 4 */ lcMemory* m_MemoryPool;
	/* this+ 8 */ int m_MemoryCnt;
	/* this+12 */ RTL_CRITICAL_SECTION m_cs;
};


template<typename T> CMemoryMgr2<T>::CMemoryMgr2()
: m_MemoryPool(NULL), m_MemoryCnt(0)
{
	InitializeCriticalSection(&m_cs);
}


template<typename T> CMemoryMgr2<T>::~CMemoryMgr2()
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

		if( m_MemoryPool != NULL )
		{
			delete[] m_MemoryPool;
			m_MemoryPool = NULL;
		}
	}

	DeleteCriticalSection(&m_cs);
}


template<typename T> bool CMemoryMgr2<T>::Init(const int in_size)
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


template<typename T> T* CMemoryMgr2<T>::Alloc()
{
	N3SyncObject sync(m_cs);

	T* result = NULL;

	for( int idx = 0; idx < m_MemoryCnt; ++idx )
	{
		if( m_MemoryPool[idx].m_bUsed != true )
		{
			m_MemoryPool[idx].m_bUsed = true;
			result = m_MemoryPool[idx].m_pObject;
			break;
		}
	}

	return result;
}


template<typename T> void CMemoryMgr2<T>::Free(T* in_cpObject)
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


template<typename T> int CMemoryMgr2<T>::GetFreeSize() const
{
	N3SyncObject sync(const_cast<RTL_CRITICAL_SECTION&>(m_cs));

	int nCount = 0;

	for( int idx = 0; idx < m_MemoryCnt; ++idx )
		if( !m_MemoryPool[idx].m_bUsed )
			++nCount;

	return nCount;
}


template<typename T> int CMemoryMgr2<T>::GetAllocSize() const
{
	N3SyncObject sync(const_cast<RTL_CRITICAL_SECTION&>(m_cs));

	int nCount = 0;

	for( int idx = 0; idx < m_MemoryCnt; ++idx )
		if( m_MemoryPool[idx].m_bUsed )
			++nCount;

	return nCount;
}


template<typename T> void CMemoryMgr2<T>::Reset()
{
	N3SyncObject sync(m_cs);

	for( int idx = 0; idx < m_MemoryCnt; ++idx )
		m_MemoryPool[idx].m_bUsed = false;
}


template<typename T> int CMemoryMgr2<T>::GetCapacity()
{
	return m_MemoryCnt;
}


////////////////////////////////////////


template<typename T> class CMemoryMgr
{
public:
	bool Init(const int in_size);
	T* Alloc();
	void Free(T* in_cpObject);
	int GetFreeSize() const;
	int GetAllocSize() const;
	void Reset();
	int GetCapacity();
	std::pair<bool,std::string> VtblLeakTest();
	T* Get(int in_idx);

public:
	CMemoryMgr();
	virtual ~CMemoryMgr();
	CMemoryMgr<T>(CMemoryMgr<T>&){}; // = delete;
	CMemoryMgr<T>& operator=(CMemoryMgr<T>&){return *this;}; // = delete;

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
	/* this+12 */ unsigned int m_vtbl;
	/* this+16 */ RTL_CRITICAL_SECTION m_cs;
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

		if( m_MemoryPool != NULL )
		{
			delete[] m_MemoryPool;
			m_MemoryPool = NULL;
		}
	}

	DeleteCriticalSection(&m_cs);
}


template<typename T> std::pair<bool,std::string> CMemoryMgr<T>::VtblLeakTest()
{
	for( int idx = 0; idx < m_MemoryCnt; ++idx )
	{
		T* ptr = m_MemoryPool[idx].m_pObject;
		unsigned int vtbl = *(unsigned int*)ptr;

		if( vtbl != m_vtbl )
		{
			char buffer[260] = {};
			_snprintf_s(buffer, countof(buffer), _TRUNCATE, " idx:%d ptr:%d ", idx, vtbl);
			return std::pair<bool,std::string>(false, buffer);
		}
	}

	return std::pair<bool,std::string>(true, "good");
}


template<typename T> T* CMemoryMgr<T>::Get(int in_idx)
{
	if( in_idx >= m_MemoryCnt )
		return NULL;

	return m_MemoryPool[in_idx].m_pObject;
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

		m_vtbl = *(unsigned int*)m_MemoryPool[idx].m_pObject;
	}

	return true;
}


template<typename T> T* CMemoryMgr<T>::Alloc()
{
	N3SyncObject sync(m_cs);

	int idx;
	for( idx = 0; idx < m_MemoryCnt; ++idx )
		if( !m_MemoryPool[idx].m_bUsed )
			break;

	if( idx >= m_MemoryCnt )
		return NULL;

	T* ptr = m_MemoryPool[idx].m_pObject;
	unsigned int vtbl = *(unsigned int*)ptr;

	if( vtbl != m_vtbl )
	{
		CVTBLErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "VTBL ERROR idx = %d, org = 0x%08X err= 0x%08X ptr= 0x%08X ", idx, m_vtbl, vtbl, ptr);

		BYTE* pDumpData = (BYTE*)m_MemoryPool[idx].m_pObject;

		char HexDataBuffer[48] = {};
		char* string = HexDataBuffer;
		for( int hdbIdx = 0; hdbIdx < 16; ++hdbIdx )
		{
			_snprintf_s(string, 2+1, _TRUNCATE, "%02X", pDumpData[hdbIdx]);
			string += 2;
		}
		CVTBLErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "0x%s", HexDataBuffer);

		char CharDataBuffer[16+1] = {};
		memcpy_s(CharDataBuffer, sizeof(CharDataBuffer), pDumpData, 16);
		CVTBLErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s", CharDataBuffer);

		*(unsigned int*)ptr = m_vtbl;
	}

	m_MemoryPool[idx].m_bUsed = true;
	return m_MemoryPool[idx].m_pObject;
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


template<typename T> int CMemoryMgr<T>::GetCapacity()
{
	return m_MemoryCnt;
}
