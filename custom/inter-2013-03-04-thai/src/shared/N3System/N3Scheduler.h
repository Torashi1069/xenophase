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
	virtual bool operator()(T* ) { return true; }

public:
	N3SchedulerTask(const unsigned long in_Identity, const unsigned long in_Time) : m_Identity(in_Identity), m_Time(in_Time) { }
	virtual ~N3SchedulerTask() { }

private:
	N3SchedulerTask(); // = delete;
	N3SchedulerTask(const N3SchedulerTask&); // = delete;
	N3SchedulerTask& operator=(N3SchedulerTask&); // = delete;
};


template<typename T> class N3Scheduler
{
public:
	typedef std::tr1::shared_ptr<N3SchedulerTask<T>> TASKPTR;

public:
	void Process(T* in_cpObject);
	void Insert(const TASKPTR& in_TaskPtr);
	void Init();
	bool IsSchedul(const unsigned long in_Identity); //TODO
	void Delete(const unsigned long in_Identity);

public:
	N3Scheduler() { }
	virtual ~N3Scheduler() { }

private:
	class lcTaskPriority
	{
	public:
		bool operator()(const TASKPTR& in_Left, const TASKPTR& in_Right)
		{
			return ( in_Left->N3SchedulerTask<T>::GetExecuteTime() < in_Right->N3SchedulerTask<T>::GetExecuteTime() );
		}
	};

	/* this+0 */ //const N3Scheduler<T>::`vftable';
	typedef std::multiset<TASKPTR,lcTaskPriority> TASKCONTAINER;
	/* this+4 */ TASKCONTAINER m_Tasks;
};


template<typename T> void N3Scheduler<T>::Process(T* in_cpObject)
{
	TASKCONTAINER::iterator iter = m_Tasks.begin();
	if( iter == m_Tasks.end() )
		return; // nothing to process.

	TASKPTR TaskPtr = *iter;
	if( timeGetTime() < TaskPtr->N3SchedulerTask<T>::GetExecuteTime() )
		return; // it's too early.

	iter = m_Tasks.erase(iter);

	if( !TaskPtr->operator()(in_cpObject) )
	{
		this->N3Scheduler<T>::Insert(TaskPtr);
		return; // try again later.
	}
}


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


template<typename T> void N3Scheduler<T>::Delete(const unsigned long in_Identity)
{
	class CTaskCompare : std::binary_function<TASKPTR,unsigned long,bool>
	{
	public:
		bool operator()(const TASKPTR& in_TaskPtr, const unsigned long& in_Identity)
		{
			return ( in_TaskPtr->N3SchedulerTask<T>::GetIdentity() == in_Identity );
		}
	};

	for( TASKCONTAINER::iterator iter = m_Tasks.begin(); iter != m_Tasks.end(); )
	{
		if( CTaskCompare()(*iter, in_Identity) )
			iter = m_Tasks.erase(iter);
		else
			++iter;
	}
}