#include "AsyncDBWork/NAsyncDBThread.h"
#include "AsyncDBWork/NInterMessageSystem.h"


NAsyncDBThread::NAsyncDBThread(const unsigned int in_hMotherInter, const std::string in_ODBCConnectionStr, NAsyncDBRequestCircularQueue* const in_cpRequestCircularQueue, NAsyncDBResponseCircularQueue* const in_cpReponseCircularQueue)
: NXObject("NAsyncDBThread"),
  NXThread("NAsyncDBThread"),
  NXInter(),
  m_MessageQueue(),
  m_hMessageEvent(NULL),
  m_ODBCConnectionStr(in_ODBCConnectionStr),
  m_ODBCCtrl(),
  m_State(STATE_DISCONNECT),
  m_hMotherInter(in_hMotherInter),
  m_vcpRequestCircularQueue(in_cpRequestCircularQueue),
  m_vcpReponseCircularQueue(in_cpReponseCircularQueue),
  m_bOK(false)
{
	NInterMessageSystem::GetObj()->NInterMessageSystem::Insert(this->NXObject::GetMyID(), this);

	if( this->NXThread::isOK() && this->NAsyncDBThread::Create() )
		m_bOK = true;
}


NAsyncDBThread::~NAsyncDBThread()
{
	this->NAsyncDBThread::Destory();

	NInterMessageSystem::GetObj()->NInterMessageSystem::Remove(this->NXObject::GetMyID(), this);
}


void NAsyncDBThread::Destory()
{
	if( m_hMessageEvent != NULL )
	{
		CloseHandle(m_hMessageEvent);
		m_hMessageEvent = NULL;
	}
}


bool NAsyncDBThread::Create()
{
	m_hMessageEvent = CreateWaitableTimerA(NULL, FALSE, NULL);
	return ( m_hMessageEvent != NULL );
}


bool NAsyncDBThread::Start()
{
	if( m_State == STATE_DISCONNECT )
	{
		if( m_ODBCCtrl.NODBCCtrl::Connect(m_ODBCConnectionStr) != true )
		{
			MessageBoxA(NULL, "database connect error \n NAsyncDBThread", "NAsyncDBThread", MB_OK);
			return false;
		}

		m_State = STATE_CONNECT;
	}

	return this->NXThread::Begin();
}


void NAsyncDBThread::Stop()
{
	this->NXThread::End();
}


void NAsyncDBThread::PostThreadQuitMessage()
{
	this->PostInterMessage(this->NXObject::GetMyID(), GetTickCount(), NXInter::NINTERMSG_REQ_THREAD_QUIT, 0, 0);
}


const bool NAsyncDBThread::isOK() const
{
	return m_bOK;
}


const bool NAsyncDBThread::ThreadFunction_Message() // 118-144
{
	unsigned int FromInter = 0;
	int Message = 0;
	int wParam = 0;
	int lParam = 0;

	if( this->PeekInterMessage(GetTickCount(), FromInter, Message, wParam, lParam, true) )
	{
		switch( Message )
		{
		case NXInter::NINTERMSG_REQ_THREAD_QUIT:
			return false;
		break;
		case NXInter::NINTERMSG_REQ_CONNECT:
			if( m_State == STATE_DISCONNECT )
			{
				if( m_ODBCCtrl.NODBCCtrl::Connect(m_ODBCConnectionStr) == true )
				{
					m_State = STATE_CONNECT;
					NInterMessageSystem::GetObj()->NInterMessageSystem::PostInterMessage(m_hMotherInter, this->NXObject::GetMyID(), GetTickCount(), NXInter::NINTERMSG_RES_CONNECT_SUCCESS, 0, 0);
				}
				else
				{
					m_State = STATE_DISCONNECT;
					NInterMessageSystem::GetObj()->NInterMessageSystem::PostInterMessage(m_hMotherInter, this->NXObject::GetMyID(), GetTickCount(), NXInter::NINTERMSG_RES_CONNECT_FAIL, 0, 0);
				}
			}
		break;
		};
	}

	return true;
}


unsigned int NAsyncDBThread::ThreadFunction() // 149-190
{
	while( 1 )
	{
		if( m_State != STATE_CONNECT )
		{
			WaitForSingleObject(m_hMessageEvent, INFINITE);

			if( !this->NAsyncDBThread::ThreadFunction_Message() )
				break;
		}

		HANDLE EventList[2];
		EventList[0] = m_vcpRequestCircularQueue->NAsyncDBRequestCircularQueue::GetEventObj();
		EventList[1] = m_hMessageEvent;

		if( WaitForMultipleObjects(countof(EventList), EventList, FALSE, INFINITE) == WAIT_OBJECT_0 + 1 )
		{
			if( !this->NAsyncDBThread::ThreadFunction_Message() )
				break;
		}

		NAsyncDBWork* cpWork = m_vcpRequestCircularQueue->NAsyncDBRequestCircularQueue::Read3();
		if( cpWork == NULL )
			continue;

		if( !cpWork->ExecQuery(m_ODBCCtrl) )
		{
			m_ODBCCtrl.NODBCCtrl::Disconnect();
			m_State = STATE_DISCONNECT;
			NInterMessageSystem::GetObj()->NInterMessageSystem::PostInterMessage(m_hMotherInter, this->NXObject::GetMyID(), GetTickCount() + 1, NXInter::NINTERMSG_NOTIFY_DISCONNECT, 0, 0);
		}

		m_vcpRequestCircularQueue->NAsyncDBRequestCircularQueue::Complete3(cpWork);
		if( !m_vcpReponseCircularQueue->NAsyncDBResponseCircularQueue::Write(cpWork) )
			NInterMessageSystem::GetObj()->NInterMessageSystem::PostInterMessage(m_hMotherInter, this->NXObject::GetMyID(), GetTickCount(), NXInter::NINTERMSG_NOTIFY_ERROR_RESQUEUE_WRITE, (int)cpWork, 0);
	}

	return 0;
}


void NAsyncDBThread::PostInterMessage(const unsigned int in_FromInter, const unsigned long in_ExecTimeMS, const int in_Msg, const int in_wParam, const int in_lParam)
{
	if( this == NULL )
		return;

	m_MessageQueue.NTPMessageQueue::Post(in_FromInter, in_ExecTimeMS, in_Msg, in_wParam, in_lParam);

	LARGE_INTEGER liDueTime;
	liDueTime.QuadPart = -10000i64 * abs(int(GetTickCount() - m_MessageQueue.NTPMessageQueue::GetFirstExecTimeMS()));
	SetWaitableTimer(m_hMessageEvent, &liDueTime, 0, NULL, NULL, FALSE);
}


bool NAsyncDBThread::PeekInterMessage(const DWORD in_ExecTimeMS, unsigned int& out_FromInter, int& out_Msg, int& out_wParam, int& out_lParam, const bool in_bRemove)
{
	bool bRet = m_MessageQueue.NTPMessageQueue::Peek(out_FromInter, out_Msg, out_wParam, out_lParam, in_bRemove);
	if( bRet == true && in_bRemove == true && !m_MessageQueue.NTPMessageQueue::isEmpty() )
	{
		LARGE_INTEGER liDueTime;
		liDueTime.QuadPart = 10000i64 * (GetTickCount() - m_MessageQueue.NTPMessageQueue::GetFirstExecTimeMS());
		SetWaitableTimer(m_hMessageEvent, &liDueTime, 0, NULL, NULL, FALSE);
	}

	return bRet;
}
