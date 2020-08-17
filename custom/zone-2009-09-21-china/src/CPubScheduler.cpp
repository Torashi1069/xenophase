#include "CPubScheduler.h"


CPubScheduler::CPubScheduler(void) // line 9
{
}


CPubScheduler::~CPubScheduler(void) // line 14
{
}


hook_method<void (CPubScheduler::*)(void)> CPubScheduler::_Init(SERVER, "CPubScheduler::Init");
void CPubScheduler::Init(void) // line 20
{
	return (this->*_Init)();

	m_JobContainer.clear();
}


hook_method<void (CPubScheduler::*)(const unsigned long in_CurTM, CPC* in_cpPlayer)> CPubScheduler::_Process(SERVER, "CPubScheduler::Process");
void CPubScheduler::Process(const unsigned long in_CurTM, CPC* in_cpPlayer) // line 35
{
	return (this->*_Process)(in_CurTM, in_cpPlayer);

	mystd::multimap<unsigned long,CPubSchedulerJob>::iterator front = m_JobContainer.begin();
	if( front == m_JobContainer.end() )
		return;

	unsigned long time = front->first;
	CPubSchedulerJob& job = front->second;

	if( in_CurTM < time )
		return;

	if( job.m_FuncPtr != NULL )
		job.m_FuncPtr(in_cpPlayer, job);

	m_JobContainer.erase(front);
}
