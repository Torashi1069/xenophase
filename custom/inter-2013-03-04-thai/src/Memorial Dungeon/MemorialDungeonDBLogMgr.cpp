#include "MemorialDungeonConfig.h"
#include "Memorial Dungeon/MemorialDungeonDBLogMgr.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/N2System/DBLog/N2DBLogMgr.h"


/// singleton instance
CMemorialDungeonDBLogMgr*& CMemorialDungeonDBLogMgr::m_cpSelf = VTOR<CMemorialDungeonDBLogMgr*>(DetourFindFunction(EXEPATH(), "CMemorialDungeonDBLogMgr::m_cpSelf"));


CMemorialDungeonDBLogMgr::CMemorialDungeonDBLogMgr()
{
	m_bOK = false;

	if( this->CMemorialDungeonDBLogMgr::Create() )
		m_bOK = true;
}


CMemorialDungeonDBLogMgr::~CMemorialDungeonDBLogMgr()
{
	this->CMemorialDungeonDBLogMgr::Destroy();
}


bool CMemorialDungeonDBLogMgr::Create()
{
	return true;
}


void CMemorialDungeonDBLogMgr::Destroy()
{
}


bool CMemorialDungeonDBLogMgr::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CMemorialDungeonDBLogMgr();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CMemorialDungeonDBLogMgr::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CMemorialDungeonDBLogMgr::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CMemorialDungeonDBLogMgr* CMemorialDungeonDBLogMgr::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CMemorialDungeonDBLogMgr::isOK() const
{
	return m_bOK;
}


void CMemorialDungeonDBLogMgr::Add(const CMemorialDungeonDBLog::enumTYPE in_Type, const std::string in_MemorialDungeonName, const std::string in_PartyName, const int in_PartyID, const int in_ZSID)
{
	if( !CMemorialDungeonConfig::GetObj()->CMemorialDungeonConfig::GetDatabaseLogOutput() )
		return;

	CMemorialDungeonDBLog* log = new(std::nothrow) CMemorialDungeonDBLog(in_Type, in_MemorialDungeonName, in_PartyName, in_PartyID, in_ZSID);
	if( log == NULL )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "check");
		return;
	}

	if( !N2DBLogMgr::GetObj()->N2DBLogMgr::Add(log) )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "check");
		delete log;
		return;
	}
}
