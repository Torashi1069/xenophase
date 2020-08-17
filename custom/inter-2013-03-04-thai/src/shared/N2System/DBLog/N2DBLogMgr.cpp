#include "shared/N2System/DBLog/N2DBLogMgr.h"
#include "shared/N2System/DBLog/N2DBLogThread.h"


/// singleton instance
N2DBLogMgr*& N2DBLogMgr::m_cpSelf = VTOR<N2DBLogMgr*>(DetourFindFunction(EXEPATH(), "N2DBLogMgr::m_cpSelf"));


N2DBLogMgr::N2DBLogMgr(const int in_WorkThreadNum, const std::string in_ConnectStr)
{
	m_bOK = false;

	if( this->N2DBLogMgr::Create(in_WorkThreadNum, in_ConnectStr) )
		m_bOK = true;
}


N2DBLogMgr::~N2DBLogMgr()
{
	this->N2DBLogMgr::Destroy();
}


bool N2DBLogMgr::Create(const int in_WorkThreadNum, const std::string in_ConnectStr)
{
	for( int WorkThreadNum = 1; WorkThreadNum <= in_WorkThreadNum; ++WorkThreadNum )
	{
		N2DBLogThread* cpThread = new(std::nothrow) N2DBLogThread(&m_RequestQueue, in_ConnectStr);
		if( cpThread == NULL )
			return false;

		if( !cpThread->N2DBLogThread::isOK() )
		{
			delete cpThread;
			return false;
		}

		m_ThreadContainer.push_back(cpThread);
	}

	return true;
}


void N2DBLogMgr::Destroy()
{
	for( std::vector<N2DBLogThread*>::iterator iter = m_ThreadContainer.begin(); iter != m_ThreadContainer.end(); ++iter )
		delete *iter;
}


bool N2DBLogMgr::CreateInstance(const int in_WorkThreadNum, const std::string in_ConnectStr)
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) N2DBLogMgr(in_WorkThreadNum, in_ConnectStr);
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->N2DBLogMgr::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void N2DBLogMgr::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


N2DBLogMgr* N2DBLogMgr::GetObj() /// @custom
{
	return m_cpSelf;
}


const bool N2DBLogMgr::isOK() const
{
	return m_bOK;
}


bool N2DBLogMgr::Start()
{
	for( THREADCONTAINER_ITER iter = m_ThreadContainer.begin(); iter != m_ThreadContainer.end(); ++iter )
		if( !(*iter)->N2Thread::Begin() )
			return false;

	return true;
}


void N2DBLogMgr::Stop()
{
	for( THREADCONTAINER_ITER iter = m_ThreadContainer.begin(); iter != m_ThreadContainer.end(); ++iter )
		(*iter)->N2Thread::End();
}


bool N2DBLogMgr::Add(N2DBLog* const in_cpDBLog)
{
	return m_RequestQueue.N2DBLogRequestQueue::Add(in_cpDBLog);
}
