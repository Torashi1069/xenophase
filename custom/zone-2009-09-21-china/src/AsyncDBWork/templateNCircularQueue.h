#pragma once
#include "std/string"


template<typename T> class templateNCircularQueue
{
	struct vtable_t
	{
		bool (templateNCircularQueue<T>::* isFull)(void);
		bool (templateNCircularQueue<T>::* isEmpty)(void);
		bool (templateNCircularQueue<T>::* Write)(T const);
		bool (templateNCircularQueue<T>::* Read)(T&);
		bool (templateNCircularQueue<T>::* View)(T&);
		void (templateNCircularQueue<T>::* Clear)(void);
		unsigned int (templateNCircularQueue<T>::* GetLastWriteTime)(void);
		int (templateNCircularQueue<T>::* GetNum)(void);
		int (templateNCircularQueue<T>::* GetMaxNum)(void);
		void* (templateNCircularQueue<T>::* scalar_deleting_destructor)(unsigned int);
	};

	/* this+0x0  */ //const templateNCircularQueue<T>::`vftable'
	/* this+0x4  */ protected: const int m_MaxEleNum;
	/* this+0x8  */ protected: bool m_bOK;
	/* this+0xC  */ protected: int m_Rear;
	/* this+0x10 */ protected: int m_Front;
	/* this+0x14 */ protected: T* m_pBuffer;
	/* this+0x18 */ protected: int m_Number;
	/* this+0x1C */ protected: unsigned int m_LastWriteTime;

	private: bool templateNCircularQueue<T>::Init(void);
	public: bool templateNCircularQueue<T>::isOK(void);
	public: virtual bool templateNCircularQueue<T>::isFull(void);
	public: virtual bool templateNCircularQueue<T>::isEmpty(void);
	public: virtual bool templateNCircularQueue<T>::Write(T const in_Data);
	public: virtual bool templateNCircularQueue<T>::Read(T& out_Data);
	public: virtual bool templateNCircularQueue<T>::View(T& out_Data);
	public: virtual void templateNCircularQueue<T>::Clear(void);
	public: virtual unsigned int templateNCircularQueue<T>::GetLastWriteTime(void);
	public: virtual int templateNCircularQueue<T>::GetNum(void);
	public: virtual int templateNCircularQueue<T>::GetMaxNum(void);
	public: templateNCircularQueue<T>::templateNCircularQueue(const mystd::string in_strName, const int in_MaxEleNum);
	public: virtual templateNCircularQueue<T>::~templateNCircularQueue(void);
};


template<typename T> templateNCircularQueue<T>::templateNCircularQueue(const mystd::string in_strName, const int in_MaxEleNum) // line 48
: m_MaxEleNum(in_MaxEleNum)
{
	m_bOK = false;
	m_Rear = 1;
	m_Front = 1;
	m_pBuffer = NULL;
	m_Number = 0;
	m_LastWriteTime = GetTickCount();

	if( this->templateNCircularQueue<T>::Init() )
		m_bOK = true;
}


template<typename T> templateNCircularQueue<T>::~templateNCircularQueue(void) // line 66
{
	if( m_pBuffer != NULL )
	{
		delete[] m_pBuffer;
		m_pBuffer = NULL;
	}
}


template<typename T> bool templateNCircularQueue<T>::Init(void) // line 77
{
	m_pBuffer = new T[m_MaxEleNum];
	return ( m_pBuffer != NULL );
}


template<typename T> bool templateNCircularQueue<T>::isOK(void) // line ??
{
	return m_bOK;
}


template<typename T> bool templateNCircularQueue<T>::isFull(void) // line 90
{
	int n = m_Rear + 1;
	if( n > m_MaxEleNum )
		n = 1;

	return ( n == m_Front );
}


template<typename T> bool templateNCircularQueue<T>::isEmpty(void) // line 103
{
	return ( m_Rear == m_Front );
}


template<typename T> bool templateNCircularQueue<T>::Write(T const in_Data) // line 111
{
	if( this->templateNCircularQueue<T>::isFull() )
		return false;

	++m_Rear;
	if( m_Rear > m_MaxEleNum )
		m_Rear = 1;

	m_pBuffer[m_Rear - 1] = in_Data;
	++m_Number;
	m_LastWriteTime = GetTickCount();

	return true;
}


template<typename T> bool templateNCircularQueue<T>::Read(T& out_Data) // line 130
{
	if( this->templateNCircularQueue<T>::isEmpty() )
		return false;

	++m_Front;
	if( m_Front > m_MaxEleNum )
		m_Front = 1;

	out_Data = m_pBuffer[m_Front - 1];
	--m_Number;

	return true;
}


template<typename T> bool templateNCircularQueue<T>::View(T& out_Data) // line 148
{
	if( this->templateNCircularQueue<T>::isEmpty() )
		return false;

	int n = m_Front + 1;
	if( n > m_MaxEleNum )
		n = true;

	out_Data = m_pBuffer[n - 1];

	return true;
}


template<typename T> void templateNCircularQueue<T>::Clear(void) // line 163
{
	m_Rear = 1;
	m_Front = 1;
	m_Number = 0;
	m_LastWriteTime = GetTickCount();
}


template<typename T> unsigned int templateNCircularQueue<T>::GetLastWriteTime(void) // line 175
{
	return m_LastWriteTime;
}

			
template<typename T> int templateNCircularQueue<T>::GetNum(void) // line 191
{
	return m_Number;
}


template<typename T> int templateNCircularQueue<T>::GetMaxNum(void) // line ???
{
	return m_MaxEleNum;
}
