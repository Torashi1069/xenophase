#include "MapResScheduler.h"


namespace {
class CIdentityGenerator
{
public:
	unsigned long operator()()
	{
		++m_IdentityCnt;
		if( m_IdentityCnt < MINIMUM_VARIABLE_IDENTITY )
			m_IdentityCnt = MINIMUM_VARIABLE_IDENTITY;

		return m_IdentityCnt;
	}

private:
	unsigned long m_IdentityCnt;

public:
	CIdentityGenerator() : m_IdentityCnt(MINIMUM_VARIABLE_IDENTITY) { }
	~CIdentityGenerator() { }
};
CIdentityGenerator gIdentityGenerator;
}; // namespace


namespace MapResScheduler
{


CTask::CTask(const unsigned long in_Identity, const unsigned long in_Time)
: m_Identity(in_Identity), m_Time(in_Time)
{
	if( m_Identity == TASK_VARIABLE_IDENENTITY_USE )
		m_Identity = gIdentityGenerator();
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


void CScheduler::Insert(const std::tr1::shared_ptr<MapResScheduler::CTask>& in_TaskPtr, const bool IsUseVariableIdentity)
{
	if( in_TaskPtr.get() == NULL )
		return;

	m_Tasks.insert(in_TaskPtr);
}


void CScheduler::Process(CMapRes* in_cpObject)
{
	TASKCONTAINER::iterator iter = m_Tasks.begin();
	if( iter == m_Tasks.end() )
		return; // nothing to process.

	std::tr1::shared_ptr<CTask> TaskPtr = *iter;
	if( timeGetTime() < TaskPtr->CTask::GetExecuteTime() )
		return; // it's too early.

	m_Tasks.erase(iter);

	if( !TaskPtr->CTask::operator()(in_cpObject) )
	{
		this->CScheduler::Insert(TaskPtr, 00000000); //TODO: unknown value
		return; // try again later.
	}
}


}; // namespace MapResScheduler
