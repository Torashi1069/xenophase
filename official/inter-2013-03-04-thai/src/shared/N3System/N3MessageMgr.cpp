#include "shared/N3System/N3MessageMgr.h"
#include "shared/N3System/N3SyncObject.h"


/// singleton instance
N3MessageMgr*& N3MessageMgr::m_cpSelf = VTOR<N3MessageMgr*>(DetourFindFunction(EXEPATH(), "N3MessageMgr::m_cpSelf"));


N3MessageMgr::N3MessageMgr()
{
	m_bOK = false;

	InitializeCriticalSection(&m_CS);
	m_bOK = true;
}


N3MessageMgr::~N3MessageMgr()
{
	DeleteCriticalSection(&m_CS);
}


bool N3MessageMgr::CreateInstance()
{
	m_cpSelf = new(std::nothrow) N3MessageMgr();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->N3MessageMgr::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void N3MessageMgr::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


N3MessageMgr* N3MessageMgr::GetObj() /// @custom
{
	return m_cpSelf;
}


bool N3MessageMgr::isOK() const
{
	return m_bOK;
}


bool N3MessageMgr::Insert(const unsigned int in_hID, N3Inter* in_cpInter)
{
	N3SyncObject sync(m_CS);

	std::pair<OBJCONTAINER::iterator,bool> ret = m_ObjContainer.insert(std::pair<unsigned int,N3Inter*>(in_hID, in_cpInter));
	return ret.second;
}


void N3MessageMgr::Remove(const unsigned int in_hID, N3Inter* in_cpInter)
{
	N3SyncObject sync(m_CS);

	OBJCONTAINER::iterator iter = m_ObjContainer.find(in_hID);
	if( iter == m_ObjContainer.end() )
		return;

	if( iter->second != in_cpInter )
		return;

	m_ObjContainer.erase(iter);
}


bool N3MessageMgr::Post(const unsigned int in_ToInter, const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam)
{
	N3SyncObject sync(m_CS);

	OBJCONTAINER::iterator iter = m_ObjContainer.find(in_ToInter);
	if( iter == m_ObjContainer.end() )
		return false;

	iter->second->Receive(in_Msg, in_wParam, in_lParam);
	return true;
}
