#pragma once


template<typename T> class CObjectRecycleMgr
{
public:
	T* Get();
	void Put(T* in_cpObj);
	bool isOK() const;
	int GetObjectNewCnt() const;
	int GetObjectDeleteCnt() const;
	int GetObjectMaxCnt() const;
	static bool CreateInstance(const int in_ObjectMaxCnt);
	static void DestoryInstance();
	static CObjectRecycleMgr* Instance();

protected:
	/* static */ static CObjectRecycleMgr* m_cpSelf;

private:
	/* this+ 0 */ bool m_bOK;
	typedef std::list<T*> WASTEPAPERBASKER;
	/* this+ 4 */ WASTEPAPERBASKER m_WastepaperBasket;
	/* this+16 */ int m_ObjectNewCnt;
	/* this+20 */ int m_ObjectDeleteCnt;
	/* this+24 */ const int m_ObjectMaxCnt;

private:
	CObjectRecycleMgr(const int in_ObjectMaxCnt);
	~CObjectRecycleMgr();
};


template<typename T> CObjectRecycleMgr<T>::CObjectRecycleMgr(const int in_ObjectMaxCnt)
{
	m_ObjectNewCnt = 0;
	m_ObjectDeleteCnt = 0;
	m_ObjectMaxCnt = in_ObjectMaxCnt;
	m_bOK = true;
}


template<typename T> CObjectRecycleMgr<T>::~CObjectRecycleMgr()
{
	for( WASTEPAPERBASKER::iterator iter = m_WastepaperBasket.begin(); iter != m_WastepaperBasket.end(); ++iter )
		delete *iter;
}


template<typename T> T* CObjectRecycleMgr<T>::Get()
{
	T* result;

	if( m_WastepaperBasket.size() != 0 )
	{
		result = m_WastepaperBasket.front();
		if( m_WastepaperBasket.size() != 0 )
			m_WastepaperBasket.pop_front();
	}
	else
	{
		++m_ObjectNewCnt;
		result = new(std::nothrow) T;
	}

	return result;
}


template<typename T> void CObjectRecycleMgr<T>::Put(T* in_cpObj)
{
	if( in_cpObj == NULL )
		return;

	if( m_WastepaperBasket.size() <= (size_t)m_ObjectMaxCnt )
	{
		m_WastepaperBasket.push_back(in_cpObj);
	}
	else
	{
		++m_ObjectDeleteCnt;
		delete in_cpObj;
	}
}


template<typename T> bool CObjectRecycleMgr<T>::isOK() const
{
	return m_bOK;
}


template<typename T> int CObjectRecycleMgr<T>::GetObjectNewCnt() const
{
	return m_ObjectNewCnt;
}


template<typename T> int CObjectRecycleMgr<T>::GetObjectDeleteCnt() const
{
	return m_ObjectDeleteCnt;
}


template<typename T> int CObjectRecycleMgr<T>::GetObjectMaxCnt() const
{
	return m_ObjectMaxCnt;
}


template<typename T> bool CObjectRecycleMgr<T>::CreateInstance(const int in_ObjectMaxCnt)
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CObjectRecycleMgr(in_ObjectMaxCnt);
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CObjectRecycleMgr<T>::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


template<typename T> void CObjectRecycleMgr<T>::DestoryInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


template<typename T> CObjectRecycleMgr<T>* CObjectRecycleMgr<T>::Instance()
{
	return m_cpSelf;
}
