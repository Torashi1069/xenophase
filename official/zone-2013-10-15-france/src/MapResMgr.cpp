#include "AgitDB.h"
#include "AgitMapRes.h"
#include "BattleFieldMapRes.h"
#include "CharacterMgr.h"
#include "Enum.h"
#include "MapRes.h"
#include "MapResMgr.h"
#include "MapTypePropertyMgr.h"
#include "Path.h"
#include "ZoneProcess.h"
#include "Common/Packet.h"
#include "shared/CMapInfoMgr.h"
#include "shared/NCriticalErrorLog.h"


CMapResMgr::CMapResMgr()
{
}


CMapResMgr::~CMapResMgr()
{
}


std::pair<bool,std::string> CMapResMgr::Init(int ZSID)
{
	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "my ZSID = %d", ZSID);
	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "map loading start...");

	std::vector<int> MapIDList = CMapInfoMgr::GetObj()->CMapInfoMgr::GetMapIDList();
	for( std::vector<int>::const_iterator it = MapIDList.begin(); it != MapIDList.end(); ++it )
	{
		const int MapID = *it;
		std::pair<bool,CMapInfo> miRet = CMapInfoMgr::GetObj()->CMapInfoMgr::GetMapInfo(MapID);
		if( !miRet.first )
		{
			char buffer[260] = {};
			_snprintf_s(buffer, countof(buffer), _TRUNCATE, "can't find map(mapid = %d)", MapID);
			return std::pair<bool,std::string>(false, buffer);
		}

		if( miRet.second.ZSID != ZSID )
			continue;

		CMapTypeProperty& mapProperty = CMapTypePropertyMgr::GetObj()->CMapTypePropertyMgr::GetProperty(miRet.second.type);
		CMapRes* mapRes;

		if( mapProperty.CMapTypeProperty::IsItPossible(MAPPROPERTY_SIEGETIME_VERSION) )
			mapRes = new(std::nothrow) CAgitMapRes(miRet.second.type);
		else
		if( mapProperty.CMapTypeProperty::IsItPossible(MAPPROPERTY_BATTLEFIELD) )
			mapRes = new(std::nothrow) CBattleFieldMapRes(miRet.second.type);
		else
		{
			mapRes = new(std::nothrow) CMapRes(miRet.second.type);
		}

		if( mapRes == NULL )
			return std::pair<bool,std::string>(false, "mapres memory allocation error");

		if( mapProperty.CMapTypeProperty::IsItPossible(MAPPROPERTY_COUNT_PK) && !mapRes->CMapRes::AllocMapPropertyCountPK() )
			return std::pair<bool,std::string>(false, "Can't Init MAPPROPERTY_COUNT_PK");

		if( !mapRes->Load(miRet.second.Name, miRet.second.MapID, miRet.second.type) )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "map loading %s ...fail", miRet.second.Name);

			delete mapRes;

			char buffer[260] = {};
			_snprintf_s(buffer, countof(buffer), _TRUNCATE, "map loading %s ...fail", miRet.second.Name);
			MessageBoxA(NULL, buffer, "MapLoad", MB_OK);

			continue;
		}

		mapRes->CMapRes::SectionMgrInit();
		m_map[mapRes->CMapRes::GetName()] = mapRes;
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "map loading %s ...ok", mapRes->CMapRes::GetName());
	}

	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "map loading end...");

	std::vector<AGIT_DBINFO*> vt;
	if( g_AgitDB.CAgitDB::Get(vt) != 1 )
		return std::pair<bool,std::string>(false, "check Agit DB table");

	for( std::vector<AGIT_DBINFO*>::iterator it = vt.begin(); it != vt.end(); ++it )
	{
		AGIT_DBINFO* info = *it;

		if( info->mapName[0] == '\0' || info->agitName[0] == '\0' )
			return std::pair<bool,std::string>(false, "AgitDB mapName or agitName invalid.");

		CMapRes* mapRes = this->CMapResMgr::GetMapRes(info->mapName);
		if( mapRes != NULL && mapRes->IsAgit() )
		{
			CAgitMapRes* agitMapRes = static_cast<CAgitMapRes*>(mapRes);
			agitMapRes->CAgitMapRes::InitAgit(*info);
		}

		CAgitMapRes::InsertTable(info->mapName, info->guildID, info->agitName);

		delete info;
	}

	vt.clear();

	m_timer.CPollTimer::Init(timeGetTime(), 2000);
	this->CMapResMgr::LoadBattleFieldMapInfo();
	return std::pair<bool,std::string>(true, "good");
}


CMapRes* CMapResMgr::GetFirstMap()
{
	for( MAPCONTAINER_ITER iter = m_map.begin(); iter != m_map.end(); ++iter )
		if( !iter->second->isInstantMap() )
			return iter->second; // found.

	return NULL; // not found.
}


CMapRes* CMapResMgr::GetMapRes(const char* mapName)
{
	MAPCONTAINER_ITER iter = m_map.find(mapName);
	if( iter == m_map.end() )
		return NULL;

	return iter->second;
}


BOOL CMapResMgr::UpdateTileInfo(CMapRes* mapRes, int xPos, int yPos, int type, unsigned long exceptAID)
{
	if( mapRes == NULL )
		return FALSE;

	PACKET_ZC_UPDATE_MAPINFO outpacket;
	outpacket.PacketType = HEADER_ZC_UPDATE_MAPINFO;
	memcpy_s(outpacket.mapName, sizeof(outpacket.mapName), mapRes->CMapRes::GetName(), 16);
	outpacket.xPos = xPos;
	outpacket.yPos = yPos;
	outpacket.type = type;

	if( exceptAID != 0 )
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, exceptAID, CM_SEND_PACKET, sizeof(outpacket), (int)&outpacket, 0, 0);

	CCharacterMgr::GetObj()->CCharacterMgr::Multicast(mapRes, xPos, yPos, sizeof(outpacket), (char*)&outpacket, 18);

	return mapRes->CMapRes::UpdateTileInfo(xPos, yPos, type);
}


bool CMapResMgr::UpdateWinPoint(CMapRes* mapRes, unsigned int AID, int winpoint)
{
	if( mapRes == NULL )
		return false;

	return mapRes->CMapRes::UpdateWinPoint(AID, winpoint);
}


bool CMapResMgr::DeleteWinPoint(CMapRes* mapRes, unsigned long AID)
{
	if( mapRes == NULL )
		return false;

	return mapRes->CMapRes::DeleteWinPoint(AID);
}


//int CMapResMgr::GetPcRanking(CMapRes* mapRes, unsigned long AID)
//{
//	//TODO (NOTE: official implementation is broken)
//}


int CMapResMgr::GetTotalSectionSize()
{
	int total = 0;

	for( MAPCONTAINER_ITER iter = m_map.begin(); iter != m_map.end(); ++iter )
		total += iter->second->CMapRes::GetTotalSectionSize();

	return total;
}


void CMapResMgr::Process()
{
	if( m_timer.CPollTimer::CheckTimeout(timeGetTime()) )
	{
		for( MAPCONTAINER_ITER iter = m_map.begin(); iter != m_map.end(); ++iter )
			iter->second->OnTimer();
	}

	for( MAPCONTAINER_ITER iter = m_map.begin(); iter != m_map.end(); ++iter )
		iter->second->Process();
}


void CMapResMgr::OnDisoranizeGuild(unsigned long GDID)
{
	for( MAPCONTAINER_ITER iter = m_map.begin(); iter != m_map.end(); ++iter )
	{
		CMapRes* mapRes = iter->second;
		if( mapRes->IsAgit() )
		{
			CAgitMapRes* agitMapRes = static_cast<CAgitMapRes*>(mapRes);
			if( GDID == agitMapRes->GetGDID() )
				agitMapRes->CAgitMapRes::SetProperty(8, 0);
		}
	}
}


void CMapResMgr::UnlinkNPC()
{
	for( MAPCONTAINER_ITER iter = m_map.begin(); iter != m_map.end(); ++iter )
	{
		CMapRes* mapRes = iter->second;
		if( mapRes->IsAgit() )
		{
			CAgitMapRes* agitMapRes = static_cast<CAgitMapRes*>(mapRes);
			agitMapRes->CAgitMapRes::UnlinkNPC();
		}
	}
}


void CMapResMgr::OnChangeEmblem(unsigned long GDID, short ver)
{
	for( MAPCONTAINER_ITER iter = m_map.begin(); iter != m_map.end(); ++iter )
	{
		CMapRes* mapRes = iter->second;
		if( mapRes->IsAgit() )
		{
			CAgitMapRes* agitMapRes = static_cast<CAgitMapRes*>(mapRes);
			if( GDID == agitMapRes->GetGDID() )
			{
				agitMapRes->CAgitMapRes::SetProperty(14, ver);
				break; // found.
			}
		}
	}
}


void CMapResMgr::OnDeleteRelated(unsigned long GDID, unsigned long deleted)
{
	for( MAPCONTAINER_ITER iter = m_map.begin(); iter != m_map.end(); ++iter )
	{
		CMapRes* mapRes = iter->second;
		if( mapRes->IsAgit() )
		{
			CAgitMapRes* agitMapRes = static_cast<CAgitMapRes*>(mapRes);
			if( GDID == agitMapRes->GetGDID() )
			{
				agitMapRes->CAgitMapRes::Method(AF_FLUSH_GDID, deleted, 0);
				break; // found.
			}
		}
	}
}


void CMapResMgr::OnChangeGDForce(unsigned long GDID)
{
	for( MAPCONTAINER_ITER iter = m_map.begin(); iter != m_map.end(); ++iter )
	{
		CMapRes* mapRes = iter->second;
		if( mapRes->IsAgit() )
		{
			CAgitMapRes* agitMapRes = static_cast<CAgitMapRes*>(mapRes);
			if( GDID == agitMapRes->GetGDID() )
				agitMapRes->CAgitMapRes::Method(AF_CHANGE_DEFENSE, 0, 0);
		}
	}
}


bool CMapResMgr::InstantMapAdd(CMapRes* const in_cpMapRes)
{
	std::pair<MAPCONTAINER_ITER,bool> ret = m_map.insert(std::pair<const std::string,CMapRes*>(in_cpMapRes->CMapRes::GetName(), in_cpMapRes));
	return ret.second;
}


void CMapResMgr::OutputAll() const
{
	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[MD] mapres list start");

	for( MAPCONTAINER::const_iterator iter = m_map.begin(); iter != m_map.end(); ++iter )
	{
		std::string name = iter->first;
		CMapRes* ptr = iter->second;
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[MD] %s : 0x%08X", name.c_str(), ptr);
	}

	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[MD] mapres list end");
}


void CMapResMgr::InstantMapRemove(CMapRes* const in_cpMapRes)
{
	if( in_cpMapRes == NULL )
		return;

	MAPCONTAINER_ITER iter = m_map.find(in_cpMapRes->CMapRes::GetName());
	if( iter == m_map.end() )
		return;

	m_map.erase(iter);
}


bool CMapResMgr::LoadBattleFieldMapInfo()
{
	FILE* fp = fopen(g_pathData.CPathData::SetFileName("BattleFieldMapInfo.scp"), "r");
	if( fp == NULL )
		return true;

	bool result = true;
	char buf[1024] = {};
	char error[1024] = {};
	CBattleFieldMapRes* map = NULL;

	while( !feof(fp) )
	{
		memset(buf, '\0', sizeof(buf));
		if( fgets(buf, countof(buf), fp) == NULL )
			break;

		char* key = strtok(buf, " \t\n");
		if( key == NULL )
			continue;
		
		if( strstr(key, "//") != NULL )
			continue;

		if( strcmp(key, "MAP") == 0 )
		{
			if( map != NULL )
			{
				sprintf_s(error, countof(error), "CMapResMgr::LoadBattleFieldMapInfo, Not Match {, }, %s", map->CMapRes::GetName());
				MessageBoxA(NULL, error, "", MB_OK);
				result = false;
				break;
			}

			char* mapname = strtok(NULL, " \t\n");
			if( mapname == NULL )
			{
				sprintf_s(error, countof(error), "CMapResMgr::LoadBattleFieldMapInfo, Can't Find Map, %s", key);
				MessageBoxA(NULL, error, "", MB_OK);
				result = false;
				break;
			}

			map = static_cast<CBattleFieldMapRes*>(this->CMapResMgr::GetMapRes(strcat(mapname, ".gat"))); //FIXME: casting before checking
			if( map != NULL && map->CMapRes::GetType() != MAPTYPE_BATTLEFIELD )
			{
				sprintf_s(error, countof(error), "CMapResMgr::LoadBattleFieldMapInfo, Not BattleFieldMapType, %s", mapname);
				MessageBoxA(NULL, error, "", MB_OK);
				result = false;
				break;
			}
		}
		else
		if( strstr(key, "{") != NULL )
		{
		}
		else
		if( strstr(key, "}") != NULL )
		{
			map = NULL;
		}
		else
		{
			if( map == NULL )
				continue;

			char* value = strtok(NULL, " \t\n");
			if( value == NULL )
			{
				sprintf_s(error, countof(error), "CMapResMgr::LoadBattleFieldMapInfo, No Value, %s", key);
				MessageBoxA(NULL, error, "", MB_OK);
				result = false;
				break;
			}

			map->CBattleFieldMapRes::SetBattleFieldMapInfo(key, value);
		}
	}

	fclose(fp);
	return result;
}
