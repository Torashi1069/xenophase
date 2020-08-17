#include "Memorial Dungeon/MemorialDungeonMgr.h"
#include "shared/NCriticalErrorLog.h"


/// singleton instance
CMemorialDungeonMgr*& CMemorialDungeonMgr::m_cpSelf = VTOR<CMemorialDungeonMgr*>(DetourFindFunction(EXEPATH(), "CMemorialDungeonMgr::m_cpSelf"));


CMemorialDungeonMgr::CMemorialDungeonMgr()
{
	m_OpenState = OPENSTATE_UNKNOWN;
	m_bOK = false;

	if( this->CMemorialDungeonMgr::Create() )
		m_bOK = true;
}


CMemorialDungeonMgr::~CMemorialDungeonMgr()
{
	this->CMemorialDungeonMgr::Destroy();
}


bool CMemorialDungeonMgr::Create()
{
	return true;
}


void CMemorialDungeonMgr::Destroy()
{
}


bool CMemorialDungeonMgr::Exist(const unsigned long in_hPartyID, const std::string in_MDungeonName)
{
	CONTAINER_ITER iter = m_Container.find(in_hPartyID);
	if( iter == m_Container.end() )
		return false;

	if( iter->second.m_Name != in_MDungeonName )
		return false;

	return true;
}


void CMemorialDungeonMgr::Add(const unsigned long in_ExistZSID, const std::string in_Name, const unsigned long in_hPartyID, const std::string in_PartyName, const unsigned long in_MemorialDungeonID, const int in_Factor)
{
	CONTAINER_ITER iter = m_Container.find(in_hPartyID);
	if( iter != m_Container.end() )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "memorial dungeon add error");
		return;
	}

	std::pair<CONTAINER_ITER,bool> ret = m_Container.insert(std::make_pair(in_hPartyID, CMemorialDungeon(in_ExistZSID, in_Name, in_hPartyID, in_PartyName, in_MemorialDungeonID, in_Factor)));
	if( !ret.second )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "memorial dungeon add error");
		return;
	}
}


void CMemorialDungeonMgr::Remove(const unsigned long in_hPartyID)
{
	CONTAINER_ITER iter = m_Container.find(in_hPartyID);
	if( iter == m_Container.end() )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "memorial dungeon remove error");
		return;
	}

	m_Container.erase(iter);
}


bool CMemorialDungeonMgr::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CMemorialDungeonMgr();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CMemorialDungeonMgr::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CMemorialDungeonMgr::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CMemorialDungeonMgr* CMemorialDungeonMgr::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CMemorialDungeonMgr::isOK() const
{
	return m_bOK;
}


void CMemorialDungeonMgr::DisconnectISVR()
{
	for( CONTAINER_ITER iter = m_Container.begin(); iter != m_Container.end(); iter = m_Container.erase(iter) )
		;
}


CMemorialDungeonMgr::enumOpenState CMemorialDungeonMgr::GetOpenState()
{
	return m_OpenState;
}


void CMemorialDungeonMgr::SetOpenState(enumOpenState in_OpenState)
{
	m_OpenState = in_OpenState;
}
