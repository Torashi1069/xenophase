#include "AsyncDBWork/NAsyncDBMgr.h"
#include "AsyncDBWork/NAsyncDBThread.h"
#include "AsyncDBWork/NIDAllocator.h"
#include "AsyncDBWork/NInterMessageSystem.h"
#include "CGVar.hpp"


hook_ptr<NAsyncDBMgr*> NAsyncDBMgr::m_cpSelf(SERVER, "NAsyncDBMgr::m_cpSelf");


NAsyncDBMgr::NAsyncDBMgr(const mystd::string in_ODBCConnectionStr) // line 34-44
: NObject("Thread"), NInter()
{
	m_WorkThreadGroupID = 0;
	m_bOK = false;
	m_cpRequestCircularQueue = NULL;
	m_cpReponseCircularQueue = NULL;

	NInterMessageSystem::GetObj()->NInterMessageSystem::Insert(this->NObject::GetMyID(), this);

	if( this->NAsyncDBMgr::Create(in_ODBCConnectionStr) )
		m_bOK = true;
}


NAsyncDBMgr::~NAsyncDBMgr(void) // line 47-50
{
	this->NAsyncDBMgr::Destory();
	NInterMessageSystem::GetObj()->NInterMessageSystem::Remove(this->NObject::GetMyID(), this);
}


hook_method<bool (NAsyncDBMgr::*)(const mystd::string in_ODBCConnectionStr)> NAsyncDBMgr::_Create(SERVER, "NAsyncDBMgr::Create");
bool NAsyncDBMgr::Create(const mystd::string in_ODBCConnectionStr) // line 72-100
{
	return (this->*_Create)(in_ODBCConnectionStr);

	m_cpRequestCircularQueue = new(std::nothrow) NAsyncDBRequestCircularQueue(15000);
	if( m_cpRequestCircularQueue == NULL )
		return false; // failed to allocate request queue

	if( !m_cpRequestCircularQueue->NAsyncDBRequestCircularQueue::isOK() )
	{
		if( m_cpRequestCircularQueue != NULL )
			delete m_cpRequestCircularQueue;
		m_cpRequestCircularQueue = NULL;
		return false; // request queue not ok
	}

	m_cpReponseCircularQueue = new(std::nothrow) NAsyncDBResponseCircularQueue("async db response circular queue", 15000);
	if( m_cpReponseCircularQueue == NULL )
		return false; // failed to allocate response queue // FIXME doesn't clean up

	if( !m_cpReponseCircularQueue->NAsyncDBResponseCircularQueue::isOK() )
	{
		if( m_cpReponseCircularQueue != NULL )
			delete m_cpReponseCircularQueue;
		m_cpReponseCircularQueue = NULL;
		return false; // response queue not ok
	}

	if( !NIDAllocator::GetObj()->NIDAllocator::RegisterGroup("NAsyncDBThread", 1, 100) )
		return false; // failed to register group // FIXME doesn't clean up

	m_WorkThreadGroupID = NIDAllocator::GetObj()->NIDAllocator::GetGroupID("NAsyncDBThread");
	if( m_WorkThreadGroupID == 0 )
		return false; // group not found // FIXME doesn't clean up

	if( CGVar::GetObj()->m_AsyncDBThreadNum >= 1 )
	{
		for( int i = 1; i <= CGVar::GetObj()->m_AsyncDBThreadNum; ++i )
		{
			NAsyncDBThread* cpThread = new(std::nothrow) NAsyncDBThread(this->NObject::GetMyID(), in_ODBCConnectionStr, m_cpRequestCircularQueue, m_cpReponseCircularQueue);
			if( cpThread == NULL )
				return false; // failed to allocate thread // FIXME doesn't clean up

			if( !cpThread->NAsyncDBThread::isOK() )
			{
				delete cpThread;
				return false; // thread not ok
			}

			m_WorkThreadContainer.push_back(cpThread);
		}
	}

	return true;
}


hook_method<void (NAsyncDBMgr::*)(void)> NAsyncDBMgr::_Destory(SERVER, "NAsyncDBMgr::Destory");
void NAsyncDBMgr::Destory(void) // line 58-69
{
	return (this->*_Destory)();

	//TODO
}


hook_method<bool (NAsyncDBMgr::*)(void)> NAsyncDBMgr::_Start(SERVER, "NAsyncDBMgr::Start");
bool NAsyncDBMgr::Start(void) // line 153-172
{
	return (this->*_Start)();

	for( mystd::vector<NAsyncDBThread *>::const_iterator i = m_WorkThreadContainer.begin(); i != m_WorkThreadContainer.end(); ++i )
		if( !(*i)->NAsyncDBThread::Start() )
			return false;

	return true;
}


hook_method<void (NAsyncDBMgr::*)(void)> NAsyncDBMgr::_Stop(SERVER, "NAsyncDBMgr::Stop");
void NAsyncDBMgr::Stop(void) // line 177-183
{
	return (this->*_Stop)();

	//TODO
}


hook_method<void (NAsyncDBMgr::*)(void)> NAsyncDBMgr::_Process(SERVER, "NAsyncDBMgr::Process");
void NAsyncDBMgr::Process(void) // line 422-434
{
	return (this->*_Process)();

	//TODO
}


hook_method<bool (NAsyncDBMgr::*)(NAsyncDBWork* in_cpWork)> NAsyncDBMgr::_RequestWork(SERVER, "NAsyncDBMgr::RequestWork");
bool NAsyncDBMgr::RequestWork(NAsyncDBWork* in_cpWork) // line 186-187
{
	return (this->*_RequestWork)(in_cpWork);

	//TODO
}


hook_method<bool (__cdecl *)(const mystd::string in_ODBCConnectionStr)> NAsyncDBMgr::_CreateInstance(SERVER, "NAsyncDBMgr::CreateInstance");
bool NAsyncDBMgr::CreateInstance(const mystd::string in_ODBCConnectionStr) // line 110-117
{
	return (NAsyncDBMgr::_CreateInstance)(in_ODBCConnectionStr);

	//TODO
}


hook_method<void (__cdecl *)(void)> NAsyncDBMgr::_DestoryInstance(SERVER, "NAsyncDBMgr::DestoryInstance");
void NAsyncDBMgr::DestoryInstance(void) // line 120-123
{
	return (NAsyncDBMgr::_DestoryInstance)();

	//TODO
}


/// @custom
NAsyncDBMgr* NAsyncDBMgr::GetObj(void)
{
	return m_cpSelf;
}
