#include "NNetworkMgr.h"
#include "NNetworkWorkThread.h"
#include "NetLib/AsyncStream.h"
#include "shared/N3System/N3MessageMgr.h"


NNetworkWorkThread::NNetworkWorkThread(const std::string in_Name)
: N3Thread(in_Name), N3Inter(), N3Object(), m_MessageQueue()
{
	N3MessageMgr::GetObj()->N3MessageMgr::Insert(this->N3Object::GetMyID(), this);
}


NNetworkWorkThread::~NNetworkWorkThread()
{
	N3MessageMgr::GetObj()->N3MessageMgr::Remove(this->N3Object::GetMyID(), this);
}


bool NNetworkWorkThread::MessageDispatch()
{
	if( WaitForSingleObject(m_MessageQueue.N3MessageQueue::GetEventObj(), 0) == WAIT_OBJECT_0 )
	{
		N3MessageQueue::RETGET ret = m_MessageQueue.N3MessageQueue::Get();
		if( std::tr1::get<0>(ret) == true )
		{
			unsigned int Message = std::tr1::get<1>(ret);

			switch( Message )
			{
			case MSG_THREAD_QUIT:
				return false;
			break;
			default:
			break;
			};
		}
	}

	return true;
}


unsigned int NNetworkWorkThread::ThreadFunction()
{
	while( this->NNetworkWorkThread::MessageDispatch() )
	{
		BOOL result;
		DWORD transferSize = 0;
		ULONG_PTR compKey = 0;
		CAsyncOperation* op = 0;

		result = GetQueuedCompletionStatus(NNetworkMgr::GetObj()->NNetworkMgr::GetIOCPHandle(), &transferSize, &compKey, (LPOVERLAPPED*)&op, INFINITE);
		if( op != NULL && op->m_stream != NULL && op->m_stream->m_completionKey == compKey )
			op->m_stream->OnComplete(result, transferSize, op);
	}

	return 0;
}


void NNetworkWorkThread::PostThreadQuitMessage()
{
	m_MessageQueue.N3MessageQueue::Put(MSG_THREAD_QUIT, 0, 0);
}


void NNetworkWorkThread::Receive(const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam)
{
	m_MessageQueue.N3MessageQueue::Put(in_Msg, in_wParam, in_lParam);
}


bool NNetworkWorkThread::Start()
{
	return this->N3Thread::Begin();
}


void NNetworkWorkThread::Stop()
{
	this->N3Thread::End();
}
