#pragma once


template<typename T> class templateNCircularQueue
{
protected:
	/* this+ 0 */ //const templateNCircularQueue<T>::`vftable';
	/* this+ 4 */ const int m_MaxEleNum;
	/* this+ 8 */ bool m_bOK;
	/* this+12 */ int m_Rear;
	/* this+16 */ int m_Front;
	/* this+20 */ T* m_pBuffer;
	/* this+24 */ int m_Number;
	/* this+28 */ unsigned int m_LastWriteTime;

private:
	bool Init();

public:
	bool isOK() const;
	virtual bool isFull();
	virtual bool isEmpty();
	virtual bool Write(T const in_Data);
	virtual bool Read(T& out_Data);
	virtual bool View(T& out_Data);
	virtual void Clear();
	virtual unsigned int GetLastWriteTime();
	virtual int GetNum();
	virtual int GetMaxNum();

public:
	templateNCircularQueue(const std::string in_strName, const int in_MaxEleNum);
	virtual ~templateNCircularQueue();
};


template<typename T> templateNCircularQueue<T>::templateNCircularQueue(const std::string in_strName, const int in_MaxEleNum)
: m_MaxEleNum(in_MaxEleNum), m_bOK(false), m_Rear(1), m_Front(1), m_pBuffer(0), m_Number(0), m_LastWriteTime(GetTickCount())
{
	if( this->templateNCircularQueue<T>::Init() )
		m_bOK = true;
}


template<typename T> templateNCircularQueue<T>::~templateNCircularQueue()
{
	if( m_pBuffer != NULL )
	{
		delete[] m_pBuffer;
		m_pBuffer = NULL;
	}
}


template<typename T> bool templateNCircularQueue<T>::Init()
{
	m_pBuffer = new T[m_MaxEleNum];
	return ( m_pBuffer != NULL );
}


template<typename T> bool templateNCircularQueue<T>::isFull()
{
	int RearNext = m_Rear + 1;
	if( RearNext > m_MaxEleNum )
		RearNext = 1;

	return ( RearNext == m_Front );
}


template<typename T> bool templateNCircularQueue<T>::isEmpty()
{
	return ( m_Rear == m_Front );
}


template<typename T> bool templateNCircularQueue<T>::Write(T const in_Data)
{
	if( this->templateNCircularQueue<T>::isFull() == true )
		return false;

	++m_Rear;
	if( m_Rear > m_MaxEleNum )
		m_Rear = 1;

	m_pBuffer[m_Rear - 1] = in_Data;
	++m_Number;

	m_LastWriteTime = GetTickCount();

	return true;
}


template<typename T> bool templateNCircularQueue<T>::Read(T& out_Data)
{
	if( this->templateNCircularQueue<T>::isEmpty() == true )
		return false;

	++m_Front;
	if( m_Front > m_MaxEleNum )
		m_Front = 1;

	out_Data = m_pBuffer[m_Front - 1];
	--m_Number;

	return true;
}


template<typename T> bool templateNCircularQueue<T>::View(T& out_Data)
{
	if( this->templateNCircularQueue<T>::isEmpty() == true )
		return false;

	int FrontNext = m_Front + 1;
	if( FrontNext > m_MaxEleNum )
		FrontNext = 1;

	out_Data = m_pBuffer[FrontNext - 1];

	return true;
}


template<typename T> void templateNCircularQueue<T>::Clear()
{
	m_Number = 0;
	m_Rear = 1;
	m_Front = 1;
	m_LastWriteTime = GetTickCount();
}


template<typename T> unsigned int templateNCircularQueue<T>::GetLastWriteTime()
{
	return m_LastWriteTime;
}


template<typename T> bool templateNCircularQueue<T>::isOK() const
{
	return m_bOK;
}


template<typename T> int templateNCircularQueue<T>::GetNum()
{
	return m_Number;
}


template<typename T> int templateNCircularQueue<T>::GetMaxNum()
{
	return m_MaxEleNum;
}
