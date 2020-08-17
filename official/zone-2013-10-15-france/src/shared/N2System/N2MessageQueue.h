#pragma once
#include "shared/N2System/N2SyncObject.h"


template<typename T> class N2MessageQueue
{
private:
	typedef typename std::list<T> MESSAGE_CONTAINER;
	typedef typename std::list<T>::iterator MESSAGE_CONTAINER_ITER;
	
	/* this+ 0 */ //const N2MessageQueue<T>::`vftable';
	/* this+ 4 */ RTL_CRITICAL_SECTION m_CS;
	/* this+28 */ MESSAGE_CONTAINER m_Container;
	/* this+56 */ bool m_bOK;

public:
	bool isOK() const;
	void Post(const T in_Message);
	bool Peek(T& out_Message);
	bool Get(T& out_Message);

public:
	N2MessageQueue();
	virtual ~N2MessageQueue();
};


template<typename T> N2MessageQueue<T>::N2MessageQueue()
{
	m_bOK = false;

	InitializeCriticalSection(&m_CS);
	m_bOK = true;
}


template<typename T> N2MessageQueue<T>::~N2MessageQueue()
{
	DeleteCriticalSection(&m_CS);
}


template<typename T> bool N2MessageQueue<T>::isOK() const
{
	return m_bOK;
}


template<typename T> void N2MessageQueue<T>::Post(const T in_Message)
{
	N2SyncObject sync(m_CS);

	m_Container.push_back(in_Message);
}


template<typename T> bool N2MessageQueue<T>::Peek(T& out_Message)
{
	N2SyncObject sync(m_CS);

	if( m_Container.size() == 0 )
		return false;

	out_Message = m_Container.front();

	return true;
}


template<typename T> bool N2MessageQueue<T>::Get(T& out_Message)
{
	N2SyncObject sync(m_CS);

	if( m_Container.size() == 0 )
		return false;

	out_Message = m_Container.front();
	m_Container.pop_front();

	return true;
}
