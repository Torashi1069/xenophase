#pragma once
class CMapRes; // #include "MapRes.h"


enum MapResSchedulerIdentity
{
	TASK_VARIABLE_IDENENTITY_USE = 0,
	TASK_CREATE_BOSS_TOMB        = 1,
	MINIMUM_VARIABLE_IDENTITY    = 1000,
};


namespace MapResScheduler
{


class CTask
{
protected:
	/* this+0 */ //const MapResScheduler::CTask::`vftable';
	/* this+4 */ unsigned long m_Identity;
	/* this+8 */ unsigned long m_Time;

public:
	unsigned long GetExecuteTime() { return m_Time; }
	unsigned long GetIdentity() { return m_Identity; }
	virtual bool operator()(CMapRes* in_cpMapRes) { return true; }

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
	void Process(CMapRes* in_cpObject);
	void Insert(const std::tr1::shared_ptr<MapResScheduler::CTask>& in_TaskPtr, const bool IsUseVariableIdentity);
	void Init();
	void Delete(const unsigned long in_Identity); //TODO
	CTask* GetTask(const unsigned long in_Identity);  //TODO

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
	/* this+0 */ //const MapResScheduler::CScheduler::`vftable';
	typedef std::multiset<std::tr1::shared_ptr<CTask>,lcTaskPriority> TASKCONTAINER;
	/* this+4 */ TASKCONTAINER m_Tasks;
};


}; // namespace MapResScheduler
