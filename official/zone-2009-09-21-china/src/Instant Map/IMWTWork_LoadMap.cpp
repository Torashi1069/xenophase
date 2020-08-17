#include "globals.hpp"
#include "ErrorLog.h"
#include "Instant Map/InstantMapRes.h"
#include "Instant Map/IMWTWork_LoadMap.h"


CIMWTWork_LoadMap::CIMWTWork_LoadMap(const int in_MapID, const mystd::string in_MapName, const int in_MapType, CInstantMapRes* const in_cpInstantMapRes) // line 20
: CIMWTWork(TYPE_LOADMAP), m_cpInstantMapRes(in_cpInstantMapRes), m_MapName(in_MapName), m_MapID(in_MapID), m_MapType(in_MapType)
{
	m_Result = RESULT_NONE;
	m_bOK = true;
}


CIMWTWork_LoadMap::~CIMWTWork_LoadMap(void) // line 27
{
}


hook_method<void (CIMWTWork_LoadMap::*)(void)> CIMWTWork_LoadMap::_Run(SERVER, "CIMWTWork_LoadMap::Run");
void CIMWTWork_LoadMap::Run(void) // line 33
{
	return (this->*_Run)();

	if( m_cpInstantMapRes->Load(m_MapName.c_str(), m_MapID, m_MapType) )
	{
		m_cpInstantMapRes->CMapRes::SectionMgrInit();
		m_Result = RESULT_SUCCESS;
	}
	else
	{
		g_errorLogs->CErrorLog::CriticalErrorLogFmt(".\\Instant map\\IMWTWork_LoadMap.cpp", 36, "instnat map = mapfile loading error %s", m_MapName.c_str());
		m_Result = RESULT_ERROR;
	}
}
