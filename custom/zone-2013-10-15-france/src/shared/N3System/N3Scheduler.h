#pragma once


template<typename T> class N3SchedulerTask
{
protected:
	/* this+0 */ //const N3SchedulerTask<T>::`vftable';
	/* this+4 */ const unsigned long m_Identity;
	/* this+8 */ unsigned long m_Time;

public:
	unsigned long GetExecuteTime() { return m_Time; }
	unsigned long GetIdentity() { return m_Identity; }

public:
	bool operator()(T*) { return true; }

private:
	N3SchedulerTask(); // = delete;
	N3SchedulerTask(const N3SchedulerTask&); // = delete;
	N3SchedulerTask& operator=(N3SchedulerTask&); // = delete;

public:
	N3SchedulerTask(const unsigned long in_Identity, const unsigned long in_Time) : m_Identity(in_Identity), m_Time(in_Time) { }
	virtual ~N3SchedulerTask() { }
};


template<typename T> class N3Scheduler
{
public:
	typedef std::tr1::shared_ptr<N3SchedulerTask<T>> TASKPTR;

public:
	void Process(T* in_cpObject);
	void Insert(const TASKPTR& in_TaskPtr);
	void Init();
//	bool IsSchedul(const unsigned long );
	void Delete(const unsigned long in_Identity);

public:
	N3Scheduler() { }
	virtual ~N3Scheduler() { }

private:
	class lcTaskPriority
	{
	public:
		bool operator()(const TASKPTR& in_Lhs, const TASKPTR& in_Rhs)
		{
			return ( in_Lhs->N3SchedulerTask<T>::GetExecuteTime() < in_Rhs->N3SchedulerTask<T>::GetExecuteTime() );
		}
	};

private:
	typedef std::multiset<TASKPTR,lcTaskPriority> TASKCONTAINER;
	/* this+4 */ TASKCONTAINER m_Tasks;
};


template<typename T> void N3Scheduler<T>::Insert(const TASKPTR& in_TaskPtr)
{
	if( in_TaskPtr.get() == NULL )
		return;

	m_Tasks.insert(in_TaskPtr);
}


template<typename T> void N3Scheduler<T>::Init()
{
	m_Tasks.clear();
}


template<typename T> void N3Scheduler<T>::Process(T* in_cpObject)
{
	TASKCONTAINER::iterator iter = m_Tasks.begin();
	if( iter == m_Tasks.end() )
		return;

	TASKPTR TaskPtr = *iter;

	if( timeGetTime() < TaskPtr->N3SchedulerTask<T>::GetExecuteTime() )
		return;

	m_Tasks.erase(iter);

	if( !TaskPtr->N3SchedulerTask<T>::operator()(in_cpObject) )
		this->N3Scheduler<T>::Insert(TaskPtr);
}


template<typename T> void N3Scheduler<T>::Delete(const unsigned long in_Identity)
{
	TASKCONTAINER::iterator iter = m_Tasks.begin();
	while( iter != m_Tasks.end() )
	{
		if( (*iter)->N3SchedulerTask<T>::GetIdentity() == in_Identity )
			iter = m_Tasks.erase(iter);
		else
			++iter;
	}
}
