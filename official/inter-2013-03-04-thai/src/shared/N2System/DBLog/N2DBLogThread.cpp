#include "shared/NCriticalErrorLog.h"
#include "shared/N2System/DBLog/N2DBLogRequestQueue.h"
#include "shared/N2System/DBLog/N2DBLogThread.h"


N2DBLogThread::N2DBLogThread(N2DBLogRequestQueue* in_cpRequestQueue, const std::string in_ConnectStr)
: N2Thread("N2DBLogThread"), m_cpRequestQueue(in_cpRequestQueue), m_hMessageSemaphore(NULL), m_ConnectStr(in_ConnectStr)
{
	m_bOK = false;

	if( this->N2DBLogThread::Create() )
		m_bOK = true;
}


N2DBLogThread::~N2DBLogThread()
{
	this->N2DBLogThread::Destroy();
}


bool N2DBLogThread::Create()
{
	m_hMessageSemaphore = CreateSemaphoreA(NULL, 0, INT_MAX, "");
	if( m_hMessageSemaphore == NULL )
		return false;

	this->N2DBLogThread::PostMessage(N2DBLogThread::MSG_CONNECT_REQUEST);
	return true;
}


void N2DBLogThread::Destroy()
{
	if( m_hMessageSemaphore != NULL )
	{
		CloseHandle(m_hMessageSemaphore);
		m_hMessageSemaphore = NULL;
	}
}


bool N2DBLogThread::MessageProcessor()
{
	switch( this->N2DBLogThread::GetMessage() )
	{
	case N2DBLogThread::MSG_CONNECT_REQUEST:
		if( !m_ODBCCtrl.N2ODBCCtrl::Connect(m_ConnectStr) )
		{
			this->N2DBLogThread::PostMessage(N2DBLogThread::MSG_CONNECT_REQUEST);
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "connect fail(%s)", m_ConnectStr.c_str());
		}

		return true;
	break;
	case N2DBLogThread::MSG_THREAD_TERMINATE:
		return false;
	break;
	default:
		return true;
	break;
	};
}


unsigned int N2DBLogThread::ThreadFunction()
{
	do
	{
		if( !m_ODBCCtrl.N2ODBCCtrl::isConnect() )
		{
			WaitForSingleObject(m_hMessageSemaphore, INFINITE);
			continue;
		}

		HANDLE EventList[2];
		EventList[0] = m_hMessageSemaphore;
		EventList[1] = m_cpRequestQueue->N2DBLogRequestQueue::GetEventObject();

		int nEvent = WaitForMultipleObjects(countof(EventList), EventList, FALSE, INFINITE);
		if( nEvent == WAIT_OBJECT_0 )
		{
		}
		else
		if( nEvent == WAIT_OBJECT_0+1 )
		{
			N2DBLog* Log = m_cpRequestQueue->N2DBLogRequestQueue::Get();
			if( Log != NULL )
			{
				if( !Log->Run(m_ODBCCtrl) )
				{
					m_ODBCCtrl.N2ODBCCtrl::Disconnect();
					this->N2DBLogThread::PostMessage(N2DBLogThread::MSG_CONNECT_REQUEST);
				}

				delete Log;
			}
		}
	}
	while( this->N2DBLogThread::MessageProcessor() );

	return 0;
}


bool N2DBLogThread::isOK() const
{
	return m_bOK;
}


void N2DBLogThread::PostThreadQuitMessage()
{
	this->N2DBLogThread::PostMessage(N2DBLogThread::MSG_THREAD_TERMINATE);
}


void N2DBLogThread::PostMessage(const enumMessage in_Message)
{
	this->N2MessageQueue<int>::Post(in_Message);
	ReleaseSemaphore(m_hMessageSemaphore, 1, NULL);
}


const N2DBLogThread::enumMessage N2DBLogThread::GetMessage()
{
	N2DBLogThread::enumMessage message = N2DBLogThread::MSG_NONE;
	if( this->N2MessageQueue<int>::Get(*(int*)&message) != true )
		return N2DBLogThread::MSG_NONE;

	return message;
}
