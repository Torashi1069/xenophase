#include "globals.hpp"
#include "struct.hpp"
#include "AgitDB.h"
#include "CAgitMapRes.hpp"
#include "BattleFieldMapRes.h"
#include "ErrorLog.h"
#include "MapInfo.h"
#include "MapResMgr.h"
#include "MapTypeProperty.h"
#include "MapTypePropertyMgr.h"
#include "StdAfx.h" // stlwipe_second()
#include "shared.h" // Trace()


CMapResMgr::CMapResMgr(void) // line 21
{
}


CMapResMgr::~CMapResMgr(void) // line 25
{
	stlwipe_second(&m_map);
}


hook_method<int (CMapResMgr::*)(int ZSID)> CMapResMgr::_Init(SERVER, "CMapResMgr::Init");
int CMapResMgr::Init(int ZSID) // line 30
{
	return (this->*_Init)(ZSID);

	g_errorLogs->CErrorLog::CriticalErrorLogFmt(".\\MapResMgr.cpp", 31, "my ZSID = %d", ZSID);
	g_errorLogs->CErrorLog::CriticalErrorLogFmt(".\\MapResMgr.cpp", 32, "map loading start...");

	for( mystd::map<mystd::string,MapInfo *>::const_iterator it = g_mapInfo->m_mapInfo.begin(); it != g_mapInfo->m_mapInfo.end(); ++it )
	{
		const char* name = it->first.c_str();
		MapInfo* info = it->second;

		if( info->ZSID != ZSID )
			continue;

		char mapName[16];
		strncpy(mapName, name, sizeof(mapName)); mapName[sizeof(mapName)-1] = 0;

		CMapTypeProperty& prop = CMapTypePropertyMgr::GetObj()->CMapTypePropertyMgr::GetProperty(info->type);

		CMapRes* map = NULL;
		if( prop.CMapTypeProperty::IsItPossible(MAPPROPERTY_SIEGETIME_VERSION) )
			map = new CAgitMapRes(info->type);
		else
		if( prop.CMapTypeProperty::IsItPossible(MAPPROPERTY_BATTLEFIELD) )
			map = new CBattleFieldMapRes(info->type);
		else
			map = new CMapRes(info->type);

		if( map && prop.CMapTypeProperty::IsItPossible(MAPPROPERTY_COUNT_PK) && !map->CMapRes::AllocMapPropertyCountPK() )
		{
			MessageBoxA(NULL, "Can't Init MAPPROPERTY_COUNT_PK", "error", MB_OK);
			return 0;
		}

		if( map->Load(mapName, info->MapID, info->type) )
		{
			map->CMapRes::SectionMgrInit();
			m_map[map->CMapRes::GetName()] = map;

			Trace("MapLoad OK: %s\n", mapName);
			g_errorLogs->CErrorLog::CriticalErrorLogFmt(".\\MapResMgr.cpp", 117, "map loading %s ...ok", mapName);
		}
		else
		{
			g_errorLogs->CErrorLog::CriticalErrorLogFmt(".\\MapResMgr.cpp", 120, "map loading %s ...fail", mapName);
			delete map;
			Trace("MapLoad NG: %s\n", mapName);

			char temp[256];
			sprintf(temp, "MapLoad NG: %s\n", mapName);
			MessageBoxA(NULL, temp, "zone server", MB_ICONEXCLAMATION);
		}
	}

	g_errorLogs->CErrorLog::CriticalErrorLogFmt(".\\MapResMgr.cpp", 133, "map loading end...");

	mystd::vector<AGIT_DBINFO *> vt;
	if( g_AgitDB->CAgitDB::Get(vt) != 1 )
	{
		MessageBoxA(NULL, "check Agit DB table", "error", MB_OK);
		return 0;
	}

	for( mystd::vector<AGIT_DBINFO *>::const_iterator it = vt.begin(); it != vt.end(); ++it )
	{
		AGIT_DBINFO* info = *it;

		if( info->mapName[0] == '\0' || info->agitName[0] == '\0' )
		{
			MessageBoxA(NULL, "AgitDB mapName or agitName invalid.", "error", MB_OK);
			return 0;
		}

		CMapRes* res = this->CMapResMgr::GetMapRes(info->mapName);
		if( res && res->IsAgit() )
			((CAgitMapRes*)res)->CAgitMapRes::InitAgit(*info);

		CAgitMapRes::InsertTable(info->mapName, info->guildID, info->agitName);

		delete info;
	}

	m_timer.CPollTimer::Init(timeGetTime(), 2000);
	this->CMapResMgr::LoadBattleFieldMapInfo();
	return 1;
}


hook_method<CMapRes* (CMapResMgr::*)(const char* mapName)> CMapResMgr::_GetMapRes(SERVER, "CMapResMgr::GetMapRes");
CMapRes* CMapResMgr::GetMapRes(const char* mapName) // line 182
{
	return (this->*_GetMapRes)(mapName);

	mystd::map<mystd::string,CMapRes*>::const_iterator it = m_map.find(mapName);
	if( it == m_map.end() )
	{
		Trace("Error : wanted not existed mapname:%s\n", mapName);
		return NULL;
	}

	return it->second;
}


hook_method<CMapRes* (CMapResMgr::*)(void)> CMapResMgr::_GetFirstMap(SERVER, "CMapResMgr::GetFirstMap");
CMapRes* CMapResMgr::GetFirstMap(void) // line 168
{
	return (this->*_GetFirstMap)();

	//TODO
}


hook_method<int (CMapResMgr::*)(CMapRes* mapRes, int xPos, int yPos, int type, unsigned long exceptAID)> CMapResMgr::_UpdateTileInfo(SERVER, "CMapResMgr::UpdateTileInfo");
int CMapResMgr::UpdateTileInfo(CMapRes* mapRes, int xPos, int yPos, int type, unsigned long exceptAID) // line 194
{
	return (this->*_UpdateTileInfo)(mapRes, xPos, yPos, type, exceptAID);

	//TODO
}


hook_method<bool (CMapResMgr::*)(CMapRes* mapRes, unsigned int AID, int winpoint)> CMapResMgr::_UpdateWinPoint(SERVER, "CMapResMgr::UpdateWinPoint");
bool CMapResMgr::UpdateWinPoint(CMapRes* mapRes, unsigned int AID, int winpoint) // line 222
{
	return (this->*_UpdateWinPoint)(mapRes, AID, winpoint);

	//TODO
}


hook_method<bool (CMapResMgr::*)(CMapRes* mapRes, unsigned long AID)> CMapResMgr::_DeleteWinPoint(SERVER, "CMapResMgr::DeleteWinPoint");
bool CMapResMgr::DeleteWinPoint(CMapRes* mapRes, unsigned long AID) // line 244
{
	return (this->*_DeleteWinPoint)(mapRes, AID);

	//TODO
}


hook_method<int (CMapResMgr::*)(void)> CMapResMgr::_GetTotalSectionSize(SERVER, "CMapResMgr::GetTotalSectionSize");
int CMapResMgr::GetTotalSectionSize(void) // line 293
{
	return (this->*_GetTotalSectionSize)();

	//TODO
}


hook_method<void (CMapResMgr::*)(void)> CMapResMgr::_Process(SERVER, "CMapResMgr::Process");
void CMapResMgr::Process(void) // line 311-321
{
	return (this->*_Process)();

	if( !m_timer.CPollTimer::CheckTimeout(timeGetTime()) )
		return; // not yet.

	for( mystd::map<mystd::string,CMapRes*>::iterator iter = m_map.begin(); iter != m_map.end(); ++iter )
		iter->second->OnTimer();
}


hook_method<void (CMapResMgr::*)(unsigned long GDID)> CMapResMgr::_OnDisoranizeGuild(SERVER, "CMapResMgr::OnDisoranizeGuild");
void CMapResMgr::OnDisoranizeGuild(unsigned long GDID) // line 326
{
	return (this->*_OnDisoranizeGuild)(GDID);

	//TODO
}


//hook_method<void (CMapResMgr::*)(void)> CMapResMgr::_UnlinkNPC(SERVER, "CMapResMgr::UnlinkNPC");
void CMapResMgr::UnlinkNPC(void) // line ???
{
//	return (this->*_UnlinkNPC)();

	for( mystd::map<mystd::string,CMapRes*>::iterator iter = m_map.begin(); iter != m_map.end(); ++iter )
		if( iter->second->IsAgit() )
			((CAgitMapRes*)iter->second)->CAgitMapRes::UnlinkNPC();
}


hook_method<void (CMapResMgr::*)(unsigned long GDID, unsigned long deleted)> CMapResMgr::_OnDeleteRelated(SERVER, "CMapResMgr::OnDeleteRelated");
void CMapResMgr::OnDeleteRelated(unsigned long GDID, unsigned long deleted) // line 379
{
	return (this->*_OnDeleteRelated)(GDID, deleted);

	//TODO
}


hook_method<bool (CMapResMgr::*)(void)> CMapResMgr::_LoadBattleFieldMapInfo(SERVER, "CMapResMgr::LoadBattleFieldMapInfo");
bool CMapResMgr::LoadBattleFieldMapInfo(void) // line 440
{
	return (this->*_LoadBattleFieldMapInfo)();

	//TODO
}
