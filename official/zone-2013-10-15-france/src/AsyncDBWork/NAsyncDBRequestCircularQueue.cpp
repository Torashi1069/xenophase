#include "AsyncDBWork/NAsyncDBRequestCircularQueue.h"
#include "AsyncDBWork/NXSyncObject.h"


NAsyncDBRequestCircularQueue::NAsyncDBRequestCircularQueue(const int in_MaxEleNum)
: m_MaxEleNum(in_MaxEleNum), m_hSemaphore(NULL), m_DuplicateRefCnt(0), m_Container(), m_SerialCheckContainer(), m_bOK(false)
{
	InitializeCriticalSection(&m_CS);

	if( this->NAsyncDBRequestCircularQueue::Create() )
		m_bOK = true;
}


NAsyncDBRequestCircularQueue::~NAsyncDBRequestCircularQueue()
{
	this->NAsyncDBRequestCircularQueue::Destory();

	DeleteCriticalSection(&m_CS);
}


const bool NAsyncDBRequestCircularQueue::isOK() const
{
	return m_bOK;
}


bool NAsyncDBRequestCircularQueue::Create()
{
	m_hSemaphore = CreateSemaphoreA(NULL, 0, INT_MAX, "");
	return ( m_hSemaphore != NULL );
}


void NAsyncDBRequestCircularQueue::Destory()
{
	if( m_hSemaphore != NULL )
	{
		CloseHandle(m_hSemaphore);
		m_hSemaphore = NULL;
	}
}


const HANDLE NAsyncDBRequestCircularQueue::GetEventObj() const
{
	return m_hSemaphore;
}


const int NAsyncDBRequestCircularQueue::GetSize()
{
	NXSyncObject sync(m_CS);

	return m_Container.size();
}


const bool NAsyncDBRequestCircularQueue::Write3(NAsyncDBWork* const in_cpAsyncDBWork)
{
	NXSyncObject sync(m_CS);

	if( m_Container.size() >= (size_t)m_MaxEleNum )
		return false;

	m_Container.push_back(in_cpAsyncDBWork);
	ReleaseSemaphore(m_hSemaphore, 1, NULL);
	return true;
}


NAsyncDBWork* NAsyncDBRequestCircularQueue::Read3()
{
	NXSyncObject sync(m_CS);

	if( m_Container.size() == 0 )
		return NULL;

	CONTAINERITOR itor;
	int num;

	for( itor = m_Container.begin(), num = 0; itor != m_Container.end() && num < 40; ++itor, ++num )
	{
		NAsyncDBWork* work = *itor;

		SERIALCHECKCONTAINERITOR i;
		for( i = m_SerialCheckContainer.begin(); i != m_SerialCheckContainer.end(); ++i )
			if( *i == work->NAsyncDBWork::GetID() )
				break;

		if( i == m_SerialCheckContainer.end() )
		{
			if( itor != m_Container.end() )
				m_Container.erase(itor);

			m_SerialCheckContainer.push_back(work->NAsyncDBWork::GetID());
			return work;
		}
	}

	++m_DuplicateRefCnt;
	return NULL;
}


const void NAsyncDBRequestCircularQueue::Complete3(const NAsyncDBWork* in_cpAsyncDBWork)
{
	NXSyncObject sync(m_CS);

	SERIALCHECKCONTAINERITOR i;
	for( i = m_SerialCheckContainer.begin(); i != m_SerialCheckContainer.end(); ++i )
		if( *i == in_cpAsyncDBWork->NAsyncDBWork::GetID() )
			break;

	if( i != m_SerialCheckContainer.end() )
		m_SerialCheckContainer.erase(i);

	if( m_DuplicateRefCnt > 0 )
	{
		--m_DuplicateRefCnt;
		ReleaseSemaphore(m_hSemaphore, 1, NULL);
	}
}
