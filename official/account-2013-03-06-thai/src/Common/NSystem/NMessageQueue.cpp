#include "Common/NSystem/NMessageQueue.h"
#include "Common/NSyncObject.h"


NMessageQueue::NMessageQueue()
{
	m_hSemaphore = NULL;
	m_bOK = false;

	InitializeCriticalSection(&m_CS);
	m_hSemaphore = CreateSemaphoreA(NULL, 0, INT_MAX, "");
	if( m_hSemaphore != NULL )
		m_bOK = true;
}


NMessageQueue::~NMessageQueue()
{
	if( m_hSemaphore != NULL )
	{
		CloseHandle(m_hSemaphore);
		m_hSemaphore = NULL;
	}

	DeleteCriticalSection(&m_CS);
}


void NMessageQueue::Put(const unsigned int in_Message, const unsigned int in_wParam, const unsigned int in_lParam)
{
	NSyncObject sync(m_CS);
	m_Queue.push_back(NMessageQueue::lcData(in_Message, in_wParam, in_lParam));
	ReleaseSemaphore(m_hSemaphore, 1, NULL);
}


NMessageQueue::RETG NMessageQueue::Get()
{
	NSyncObject sync(m_CS);

	if( m_Queue.size() == 0 )
		return RETG(false, 0, 0, 0);

	NMessageQueue::lcData& data = m_Queue.front();
	return RETG(true, data.m_Message, data.m_wParam, data.m_lParam);
}


bool NMessageQueue::isOK() const
{
	return m_bOK;
}


HANDLE NMessageQueue::GetEventObj() const
{
	return m_hSemaphore;
}
