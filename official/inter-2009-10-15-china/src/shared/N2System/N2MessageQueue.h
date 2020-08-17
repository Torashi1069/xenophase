#pragma once
#include "std/list"


template<typename T> class N2MessageQueue
{
	/* this+0x0  */ void* vtable;
	/* this+0x4  */ private: RTL_CRITICAL_SECTION m_CS;
	/* this+0x1C */ private: mystd::list<T> m_Container;
	/* this+0x28 */ private: bool m_bOK;

	typedef typename mystd::list<T>::const_iterator MESSAGE_CONTAINER_ITER;

	//public: bool N2MessageQueue<T>::isOK(void);
	//public: void N2MessageQueue<T>::Post(const T);
	//public: bool N2MessageQueue<T>::Peek(T&);
	//public: bool N2MessageQueue<T>::Get(T&);
	//public: N2MessageQueue<T>::N2MessageQueue(void);
	//public: N2MessageQueue<T>::~N2MessageQueue(void);
};
