#include "NAsyncDBResponseCircularQueue.h"


hook_method<const bool (NAsyncDBResponseCircularQueue::*)(void) const> NAsyncDBResponseCircularQueue::_isOK(SERVER, "NAsyncDBResponseCircularQueue::isOK");
const bool NAsyncDBResponseCircularQueue::isOK(void) const // line 29-31
{
	return(this->*_isOK)();

	return m_bOK;
}


NAsyncDBResponseCircularQueue::NAsyncDBResponseCircularQueue(const mystd::string in_strName, const int in_MaxEleNum) // line 14-21
: templateNCircularQueue<NAsyncDBWork*>(in_strName, in_MaxEleNum)
{
	m_bOK = false;
	InitializeCriticalSection(&m_CS);

	if( this->templateNCircularQueue<NAsyncDBWork*>::isOK() )
		m_bOK = true;
}


NAsyncDBResponseCircularQueue::~NAsyncDBResponseCircularQueue(void) // line 24-26
{
	DeleteCriticalSection(&m_CS);
}
