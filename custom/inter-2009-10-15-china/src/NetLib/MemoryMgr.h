#pragma once
#include "std/map"


template<typename T> class CMemoryMgr
{
	/* this+ 0 */ public: //const CMemoryMgr<T>::`vftable';
	/* this+ 4 */ private: int m_size;
	/* this+ 8 */ private: mystd::map<T*,bool> m_data;
	/* this+20 */ private: T** m_buf;
	/* this+24 */ private: RTL_CRITICAL_SECTION m_cs;

	public: CMemoryMgr<T>::CMemoryMgr(void);
	public: virtual CMemoryMgr<T>::~CMemoryMgr(void);
	public: bool CMemoryMgr<T>::Init(int size);
	public: T* CMemoryMgr<T>::Alloc(void);
	public: void CMemoryMgr<T>::Free(T* t);
	public: int CMemoryMgr<T>::GetFreeSize(void);
	public: int CMemoryMgr<T>::GetAllocSize(void);
	public: void CMemoryMgr<T>::Reset(void);

	public: int CMemoryMgr<T>::size(void);
};


template<typename T> CMemoryMgr<T>::CMemoryMgr(void) // line 31
{
	m_buf = NULL;

	InitializeCriticalSection(&m_cs);
}


template<typename T> CMemoryMgr<T>::~CMemoryMgr(void) // line 38
{
	if( m_buf != NULL )
		for( int i = 0; i < m_size; ++i )
			delete m_buf[i];

	delete[] m_buf;

	DeleteCriticalSection(&m_cs);
}


template<typename T> bool CMemoryMgr<T>::Init(int size) // line 51
{
	if( m_buf )
		for( int i = 0; i < m_size; ++i )
			delete m_buf[i];

	delete[] m_buf;

	m_buf = new T*[size];
	m_size = size;

	for( int i = 0; i < m_size; ++i )
	{
		m_buf[i] = new T;

		if( !m_buf[i] )
			return false;

		m_data[m_buf[i]] = false;
	}

	return true;
}


template<typename T> T* CMemoryMgr<T>::Alloc(void) // line 76
{
	T* result = NULL;
	EnterCriticalSection(&m_cs);

	for( mystd::map<T*,bool>::iterator it = m_data.begin(); it != m_data.end(); ++it )
	{
		if( it->second == false )
		{
			it->second = true;
			result = it->first;
			break;
		}
	}

	LeaveCriticalSection(&m_cs);
	return result;
}


template<typename T> void CMemoryMgr<T>::Free(T* t) // line 93
{
	if( t == NULL )
		return;

	EnterCriticalSection(&m_cs);

	mystd::map<T*,bool>::iterator it = m_data.find(t);
	if( it != m_data.end() )
		it->second = false;

	LeaveCriticalSection(&m_cs);
}


template<typename T> int CMemoryMgr<T>::GetFreeSize(void) // line 109
{
	int result = 0;
	EnterCriticalSection(&m_cs);

	for( mystd::map<T*,bool>::const_iterator i = m_data.begin(); i != m_data.end(); ++i )
		if( i->second == false )
			++result;

	LeaveCriticalSection(&m_cs);
	return result;
}


template<typename T> int CMemoryMgr<T>::GetAllocSize(void) // line 124
{
	int result = 0;
	EnterCriticalSection(&m_cs);

	for( mystd::map<T*,bool>::const_iterator i = m_data.begin(); i != m_data.end(); ++i )
		if( i->second == true )
			++result;

	LeaveCriticalSection(&m_cs);
	return result;
}


template<typename T> void CMemoryMgr<T>::Reset(void) // line 139
{
	EnterCriticalSection(&m_cs);

	for( mystd::map<T*,bool>::iterator it = m_data.begin(); it != m_data.end(); ++it )
		it->second = false;

	LeaveCriticalSection(&m_cs);
}


/// Retrieves the total capacity of the memory manager.
/// @custom
template<typename T> int CMemoryMgr<T>::size(void)
{
	return m_size;
}
