#include "Memorial Dungeon/MemorialDungeonConfiguration.h"
#include "Memorial Dungeon/MemorialDungeonDBLogMgr.h"
#include "N2System/DBLog/N2DBLogMgr.h"
#include "ErrorLog.h"
#include "globals.hpp"


hook_ptr<CMemorialDungeonDBLogMgr*> CMemorialDungeonDBLogMgr::m_cpSelf(SERVER, "CMemorialDungeonDBLogMgr::m_cpSelf"); // = NULL;


hook_func<CMemorialDungeonDBLogMgr* (__cdecl *)(void)> _InstanceCMemorialDungeonDBLogMgr(SERVER, "InstanceCMemorialDungeonDBLogMgr");
CMemorialDungeonDBLogMgr* __cdecl InstanceCMemorialDungeonDBLogMgr(void) // line 41 (Memorial Dungeon/MemorialDungeonDBLogMgr.h)
{
	return CMemorialDungeonDBLogMgr::m_cpSelf;
}


CMemorialDungeonDBLogMgr::CMemorialDungeonDBLogMgr(void) // line 17-21
{
	m_bOK = false;

	if( this->CMemorialDungeonDBLogMgr::Create() )
		m_bOK = true;
}


CMemorialDungeonDBLogMgr::~CMemorialDungeonDBLogMgr(void) // line 24-27
{
}


hook_method<bool (CMemorialDungeonDBLogMgr::*)(void)> CMemorialDungeonDBLogMgr::_Create(SERVER, "CMemorialDungeonDBLogMgr::Create");
bool CMemorialDungeonDBLogMgr::Create(void) // line 30-42
{
	return (this->*_Create)();

	return true;
}


hook_method<void (CMemorialDungeonDBLogMgr::*)(void)> CMemorialDungeonDBLogMgr::_Destroy(SERVER, "CMemorialDungeonDBLogMgr::Destroy");
void CMemorialDungeonDBLogMgr::Destroy(void) // line 44-47
{
	return (this->*_Destroy)();

	;
}


hook_method<static bool (__cdecl *)(void)> CMemorialDungeonDBLogMgr::_CreateInstance(SERVER, "CMemorialDungeonDBLogMgr::CreateInstance");
bool __cdecl CMemorialDungeonDBLogMgr::CreateInstance(void) // line 53-60
{
	return (CMemorialDungeonDBLogMgr::_CreateInstance)();

	if ( CMemorialDungeonDBLogMgr::m_cpSelf != NULL )
		return false; // already created

	CMemorialDungeonDBLogMgr::m_cpSelf = new CMemorialDungeonDBLogMgr();
	if( CMemorialDungeonDBLogMgr::m_cpSelf == NULL )
		return false;

	if( !CMemorialDungeonDBLogMgr::m_cpSelf->m_bOK )
	{
		delete CMemorialDungeonDBLogMgr::m_cpSelf;
		CMemorialDungeonDBLogMgr::m_cpSelf = (CMemorialDungeonDBLogMgr*)NULL;
		return false;
	}

	return true;
}


hook_method<static void (__cdecl *)(void)> CMemorialDungeonDBLogMgr::_DestroyInstance(SERVER, "CMemorialDungeonDBLogMgr::DestroyInstance");
void __cdecl CMemorialDungeonDBLogMgr::DestroyInstance(void) // line 63-66
{
	return (CMemorialDungeonDBLogMgr::_DestroyInstance)();

	if( CMemorialDungeonDBLogMgr::m_cpSelf != NULL )
	{
		delete CMemorialDungeonDBLogMgr::m_cpSelf;
		CMemorialDungeonDBLogMgr::m_cpSelf = (CMemorialDungeonDBLogMgr*)NULL;
	}
}


hook_method<bool (CMemorialDungeonDBLogMgr::*)(void) const> CMemorialDungeonDBLogMgr::_isOK(SERVER, "CMemorialDungeonDBLogMgr::isOK");
bool CMemorialDungeonDBLogMgr::isOK(void) const // line 22 (Memorial Dungeon/MemorialDungeonDBLogMgr.h)
{
	return (this->*_isOK)();

	return m_bOK;
}


hook_method<void (CMemorialDungeonDBLogMgr::*)(const enum CMemorialDungeonDBLog::enumTYPE in_Type, const mystd::string in_MemorialDungeonName, const mystd::string in_PartyName, const int in_PartyID, const int in_ZSID)> CMemorialDungeonDBLogMgr::_Add(SERVER, "CMemorialDungeonDBLogMgr::Add");
void CMemorialDungeonDBLogMgr::Add(const enum CMemorialDungeonDBLog::enumTYPE in_Type, const mystd::string in_MemorialDungeonName, const mystd::string in_PartyName, const int in_PartyID, const int in_ZSID) // line 83-110
{
	return (this->*_Add)(in_Type, in_MemorialDungeonName, in_PartyName, in_PartyID, in_ZSID);

	if( !InstanceCMemorialDungeonConfiguration()->CMemorialDungeonConfiguration::IsDBLogOutput() )
		return;

	CMemorialDungeonDBLog* log = new CMemorialDungeonDBLog(in_Type, in_MemorialDungeonName, in_PartyName, in_PartyID, in_ZSID);
	if( log == NULL )
	{
		g_errorLogs.CErrorLog::CriticalErrorLogFmt(".\\Memorial Dungeon\\MemorialDungeonDBLogMgr.cpp", 102, "check");
		return;
	}

	if( !InstanceN2DBLogMgr()->N2DBLogMgr::Add(log) )
	{
		g_errorLogs.CErrorLog::CriticalErrorLogFmt(".\\Memorial Dungeon\\MemorialDungeonDBLogMgr.cpp", 107, "check");
		delete log;
		return;
	}

	return; //done.
}
