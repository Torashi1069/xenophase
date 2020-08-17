#pragma once
#include "std/map"
class CPC;


class CPubSchedulerJob
{
public:
	typedef void function(CPC*, CPubSchedulerJob&);
	/* this+0 */ public: function* m_FuncPtr;

	public: CPubSchedulerJob(function* FuncPtr)
	{
		m_FuncPtr = FuncPtr;
	}

	public: ~CPubSchedulerJob(void)
	{
	}
};


class CPubScheduler
{
	/* this+0 */ public: //const CPubScheduler::`vftable';
	/* this+4 */ private: mystd::multimap<unsigned long,CPubSchedulerJob> m_JobContainer;

	public: CPubScheduler::CPubScheduler(void);
	public: virtual CPubScheduler::~CPubScheduler(void);
	//public: bool CPubScheduler::Add(const unsigned long in_Time, CPubSchedulerJob& in_Job);
	public: void CPubScheduler::Init(void);
	public: void CPubScheduler::Process(const unsigned long in_CurTM, CPC* in_cpPlayer);

private:
	static hook_method<void (CPubScheduler::*)(void)> CPubScheduler::_Init;
	static hook_method<void (CPubScheduler::*)(const unsigned long in_CurTM, CPC* in_cpPlayer)> CPubScheduler::_Process;
};
