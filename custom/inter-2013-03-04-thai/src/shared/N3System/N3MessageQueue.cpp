#include "shared/N3System/N3MessageQueue.h"
#include "shared/N3System/N3SyncObject.h"


N3MessageQueue::N3MessageQueue()
{
	m_hSemaphore = NULL;
	m_bOK = false;

	InitializeCriticalSection(&m_CS);
	m_hSemaphore = CreateSemaphoreA(NULL, 0, INT_MAX, "");
	if( m_hSemaphore != NULL )
		m_bOK = true;
}


N3MessageQueue::~N3MessageQueue()
{
	if( m_hSemaphore != NULL )
	{
		CloseHandle(m_hSemaphore);
		m_hSemaphore = NULL;
	}

	DeleteCriticalSection(&m_CS);
}


bool N3MessageQueue::isOK() const
{
	return m_bOK;
}


HANDLE N3MessageQueue::GetEventObj()
{
	return m_hSemaphore;
}


void N3MessageQueue::Put(const unsigned int in_Message, const unsigned int in_wParam, const unsigned int in_lParam)
{
	N3SyncObject sync(m_CS);

	m_Queue.push_back(lcData(in_Message, in_wParam, in_lParam));
	ReleaseSemaphore(m_hSemaphore, 1, NULL);
}


N3MessageQueue::RETGET N3MessageQueue::Get()
{
	N3SyncObject sync(m_CS);

	if( m_Queue.size() == 0 )
		return RETGET(false, 0, 0, 0);

	N3MessageQueue::lcData data = m_Queue.front();
	m_Queue.pop_front();

	return RETGET(true, data.m_Message, data.m_wParam, data.m_lParam);
}
