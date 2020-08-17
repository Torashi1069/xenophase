#include "AsyncDBWork/NAsyncDBRequestCircularQueue.h"


NAsyncDBRequestCircularQueue::NAsyncDBRequestCircularQueue(const int in_MaxEleNum) // line 15
: m_MaxEleNum(in_MaxEleNum), m_hSemaphore(NULL), m_DuplicateRefCnt(0), m_bOK(false)
{
	InitializeCriticalSection(&m_CS);

	if( this->NAsyncDBRequestCircularQueue::Create() )
		m_bOK = true;
}


NAsyncDBRequestCircularQueue::~NAsyncDBRequestCircularQueue(void) // line 26
{
	this->NAsyncDBRequestCircularQueue::Destroy();
	DeleteCriticalSection(&m_CS);
}


hook_method<bool (NAsyncDBRequestCircularQueue::*)(void)> NAsyncDBRequestCircularQueue::_Create(SERVER, "NAsyncDBRequestCircularQueue::Create");
bool NAsyncDBRequestCircularQueue::Create(void) // line 39
{
	return (this->*_Create)();

	//TODO
}


hook_method<void (NAsyncDBRequestCircularQueue::*)(void)> NAsyncDBRequestCircularQueue::_Destroy(SERVER, "NAsyncDBRequestCircularQueue::Destory");
void NAsyncDBRequestCircularQueue::Destroy(void) // line 46
{
	return (this->*_Destroy)();

	//TODO
}


hook_method<const bool (NAsyncDBRequestCircularQueue::*)(void) const> NAsyncDBRequestCircularQueue::_isOK(SERVER, "NAsyncDBRequestCircularQueue::isOK");
const bool NAsyncDBRequestCircularQueue::isOK(void) const // line 29-31
{
	return(this->*_isOK)();

	return m_bOK;
}
