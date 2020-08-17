#pragma once
class CActor; // #include "Actor.h"


namespace ActorScheduler
{


class CTask
{
protected:
	/* this+0 */ //const ActorScheduler::CTask::`vftable';
	/* this+4 */ const unsigned long m_Identity;
	/* this+8 */ unsigned long m_Time;

public:
	unsigned long GetExecuteTime() { return m_Time; }
	unsigned long GetIdentity() { return m_Identity; }
	virtual bool operator()(CActor* in_cpActor) { return true; }

public:
	CTask(const unsigned long in_Identity, const unsigned long in_Time);
	virtual ~CTask() { }

private:
	CTask(); // = delete;
	CTask(const CTask&); // = delete;
};


class CScheduler
{
public:
	void Process(CActor* in_cpActor);
	void Insert(const std::tr1::shared_ptr<ActorScheduler::CTask>& in_TaskPtr);
	void Init();
	void Delete(const unsigned long in_Identity);

public:
	CScheduler();
	virtual ~CScheduler();

private:
	class lcTaskPriority
	{
	public:
		bool operator()(const std::tr1::shared_ptr<CTask>& in_Lhs, const std::tr1::shared_ptr<CTask>& in_Rhs)
		{
			return ( in_Lhs->CTask::GetExecuteTime() < in_Rhs->CTask::GetExecuteTime() );
		}
	};

private:
	/* this+0 */ //const ActorScheduler::CScheduler::`vftable';
	typedef std::multiset<std::tr1::shared_ptr<CTask>,lcTaskPriority> TASKCONTAINER;
	/* this+4 */ TASKCONTAINER m_Tasks;
};


}; // namespace ActorScheduler
