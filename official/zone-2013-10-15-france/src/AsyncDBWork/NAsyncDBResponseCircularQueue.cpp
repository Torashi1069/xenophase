#include "AsyncDBWork/NAsyncDBResponseCircularQueue.h"
#include "AsyncDBWork/NXSyncObject.h"


NAsyncDBResponseCircularQueue::NAsyncDBResponseCircularQueue(const std::string in_strName, const int in_MaxEleNum)
: templateNCircularQueue<NAsyncDBWork*>(in_strName, in_MaxEleNum)
{
	m_bOK = false;

	InitializeCriticalSection(&m_CS);

	if( this->NAsyncDBResponseCircularQueue::isOK() )
		m_bOK = true;
}


NAsyncDBResponseCircularQueue::~NAsyncDBResponseCircularQueue()
{
	DeleteCriticalSection(&m_CS);
}


const bool NAsyncDBResponseCircularQueue::isOK() const
{
	return m_bOK;
}


bool NAsyncDBResponseCircularQueue::isFull()
{
	NXSyncObject sync(m_CS);

	return this->templateNCircularQueue<NAsyncDBWork*>::isFull();
}


bool NAsyncDBResponseCircularQueue::isEmpty()
{
	NXSyncObject sync(m_CS);

	return this->templateNCircularQueue<NAsyncDBWork*>::isEmpty();
}


bool NAsyncDBResponseCircularQueue::Write(NAsyncDBWork* const in_pAsyncDBWork)
{
	NXSyncObject sync(m_CS);

	return this->templateNCircularQueue<NAsyncDBWork*>::Write(in_pAsyncDBWork);
}


bool NAsyncDBResponseCircularQueue::Read(NAsyncDBWork*& out_Data)
{
	NXSyncObject sync(m_CS);

	return this->templateNCircularQueue<NAsyncDBWork*>::Read(out_Data);
}


bool NAsyncDBResponseCircularQueue::View(NAsyncDBWork*& out_Data)
{
	NXSyncObject sync(m_CS);

	return this->templateNCircularQueue<NAsyncDBWork*>::View(out_Data);
}


void NAsyncDBResponseCircularQueue::Clear()
{
	NXSyncObject sync(m_CS);

	this->templateNCircularQueue<NAsyncDBWork*>::Clear();
}


unsigned int NAsyncDBResponseCircularQueue::GetLastWriteTime()
{
	NXSyncObject sync(m_CS);

	return this->templateNCircularQueue<NAsyncDBWork*>::GetLastWriteTime();
}


int NAsyncDBResponseCircularQueue::GetNum()
{
	NXSyncObject sync(m_CS);

	return this->templateNCircularQueue<NAsyncDBWork*>::GetNum();
}


int NAsyncDBResponseCircularQueue::GetMaxNum()
{
	NXSyncObject sync(m_CS);

	return this->templateNCircularQueue<NAsyncDBWork*>::GetMaxNum();
}
