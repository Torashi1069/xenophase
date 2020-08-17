#include "shared/N2System/N2SyncObject.h"
#include "shared/N2System/DBLog/N2DBLogRequestQueue.h"


N2DBLogRequestQueue::N2DBLogRequestQueue()
{
	m_hSemaphore = NULL;
	m_bOK = false;

	InitializeCriticalSection(&m_CS);

	if( this->N2DBLogRequestQueue::Create() )
		m_bOK = true;
}


N2DBLogRequestQueue::~N2DBLogRequestQueue()
{
	this->N2DBLogRequestQueue::Destroy();
	DeleteCriticalSection(&m_CS);
}


bool N2DBLogRequestQueue::Create()
{
	m_hSemaphore = CreateSemaphoreA(NULL, 0, INT_MAX, "");
	return ( m_hSemaphore != NULL );
}


void N2DBLogRequestQueue::Destroy()
{
	if( m_hSemaphore != NULL )
	{
		CloseHandle(m_hSemaphore);
		m_hSemaphore = NULL;
	}
}


bool N2DBLogRequestQueue::isOK() const
{
	return m_bOK;
}


N2DBLog* N2DBLogRequestQueue::Get()
{
	N2SyncObject sync(m_CS);

	if( m_Container.size() == 0 )
		return NULL;

	N2DBLog* result = m_Container.front();
	m_Container.pop_front();

	return result;
}


HANDLE& N2DBLogRequestQueue::GetEventObject()
{
	return m_hSemaphore;
}


bool N2DBLogRequestQueue::Add(N2DBLog* const in_cpDBLog)
{
	N2SyncObject sync(m_CS);

	CONTAINER_ITER iter = m_Container.insert(m_Container.end(), in_cpDBLog);
	if( iter == m_Container.end() )
		return false;

	ReleaseSemaphore(m_hSemaphore, 1, NULL);

	return true;
}
