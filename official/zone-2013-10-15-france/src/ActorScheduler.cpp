#include "ActorScheduler.h"


namespace ActorScheduler
{


CTask::CTask(const unsigned long in_Identity, const unsigned long in_Time)
: m_Identity(in_Identity), m_Time(in_Time)
{
}


CScheduler::CScheduler()
{
}


CScheduler::~CScheduler()
{
	m_Tasks.clear();
}


void CScheduler::Init()
{
	m_Tasks.clear();
}


void CScheduler::Insert(const std::tr1::shared_ptr<ActorScheduler::CTask>& in_TaskPtr)
{
	if( in_TaskPtr.get() == NULL )
		return;

	m_Tasks.insert(in_TaskPtr);
}


void CScheduler::Delete(const unsigned long in_Identity)
{
	for( TASKCONTAINER::iterator iter = m_Tasks.begin(); iter != m_Tasks.end(); )
	{
		if( (*iter)->CTask::GetIdentity() == in_Identity )
			iter = m_Tasks.erase(iter);
		else
			++iter;
	}
}


void CScheduler::Process(CActor* in_cpActor)
{
	TASKCONTAINER::iterator iter = m_Tasks.begin();
	if( iter == m_Tasks.end() )
		return; // nothing to process.

	std::tr1::shared_ptr<CTask> TaskPtr = *iter;
	if( timeGetTime() < TaskPtr->CTask::GetExecuteTime() )
		return; // it's too early.

	m_Tasks.erase(iter);

	if( !TaskPtr->CTask::operator()(in_cpActor) )
	{
		this->CScheduler::Insert(TaskPtr);
		return; // try again later.
	}
}


}; // namespace ActorScheduler
