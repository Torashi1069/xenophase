#include "Instant map/InstantMapWorkerThread.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/N3System/N3MessageMgr.h"


/// singleton instance
CInstantMapWorkerThread*& CInstantMapWorkerThread::m_cpSelf = VTOR<CInstantMapWorkerThread*>(DetourFindFunction(EXEPATH(), "CInstantMapWorkerThread::m_cpSelf"));


CInstantMapWorkerThread::CInstantMapWorkerThread()
: N3Object(), N3Thread("InstantMapWorkerThread"), N3Inter(),
  m_MessageQueue(), m_bOK(false)
{
	N3MessageMgr::GetObj()->N3MessageMgr::Insert(this->N3Object::GetMyID(), this);

	if( this->N3Thread::isOK() )
		m_bOK = true;
}


CInstantMapWorkerThread::~CInstantMapWorkerThread()
{
	N3MessageMgr::GetObj()->N3MessageMgr::Remove(this->N3Object::GetMyID(), this);
}


unsigned int CInstantMapWorkerThread::ThreadFunction()
{
	return 0;
	//TODO
/*
	while( 1 )
	{
		if( WaitForSingleObject(m_MessageQueue.N3MessageQueue::GetEventObj(), INFINITE) == WAIT_OBJECT_0 )
		{
			N3MessageQueue::RETGET mRet = m_MessageQueue.N3MessageQueue::Get();
			if( std::tr1::get<0>(mRet) == true )
			{
				unsigned int Message = std::tr1::get<1>(mRet);

				if( Message == 0x640000 )
				{
					return 0;
				}
				else
				if( Message == 0x640001 )
				{
					CIMWTWork* work = reinterpret_cast<CIMWTWork*>(std::tr1::get<2>(mRet));
					unsigned int senderId = std::tr1::get<3>(mRet);

					work->Run();
					N3MessageMgr::GetObj()->N3MessageMgr::Post(senderId, 0x640002, work, 0);
				}
				else
				{
					NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "unknown message receive(Msg:0x%X)", Message);
				}
			}
		}
	}; // while(1)
*/
}


void CInstantMapWorkerThread::PostThreadQuitMessage()
{
	m_MessageQueue.N3MessageQueue::Put(0x640000, 0, 0);
}


bool CInstantMapWorkerThread::Start()
{
	return this->N3Thread::Begin();
}


void CInstantMapWorkerThread::Stop()
{
	this->N3Thread::End();
}


bool CInstantMapWorkerThread::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CInstantMapWorkerThread();
	if( m_cpSelf == NULL )
		return false;
	
	if( !m_cpSelf->CInstantMapWorkerThread::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CInstantMapWorkerThread::DestoryInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CInstantMapWorkerThread* CInstantMapWorkerThread::GetObj() /// @custom
{
	return m_cpSelf;
}


const bool CInstantMapWorkerThread::isOK() const
{
	return m_bOK;
}


void CInstantMapWorkerThread::Receive(const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam)
{
	m_MessageQueue.N3MessageQueue::Put(in_Msg, in_wParam, in_lParam);
}
