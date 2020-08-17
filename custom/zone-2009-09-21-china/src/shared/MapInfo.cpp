#include "MapInfo.h"


CMapInfo::CMapInfo(void) // line 5
{
}


CMapInfo::~CMapInfo(void) // line 9
{
}


hook_method<void (CMapInfo::*)(void)> CMapInfo::_GetMapInfo(SERVER, "CMapInfo::GetMapInfo");
void CMapInfo::GetMapInfo(void)
{
	return (this->*_GetMapInfo)();

	//TODO
}


hook_method<int (CMapInfo::*)(const char* mapName)> CMapInfo::_GetServerID(SERVER, "CMapInfo::GetServerID");
int CMapInfo::GetServerID(const char* mapName)
{
	return (this->*_GetServerID)(mapName);

	//TODO
}


hook_method<int (CMapInfo::*)(const char* mapName)> CMapInfo::_IsSiege(SERVER, "CMapInfo::IsSiege");
int CMapInfo::IsSiege(const char* mapName)
{
	return (this->*_IsSiege)(mapName);

	//TODO
}


hook_method<bool (CMapInfo::*)(const MapInfo& in_MapInfo)> CMapInfo::_InstantMapAdd2(SERVER, "CMapInfo::InstantMapAdd2");
bool CMapInfo::InstantMapAdd2(const MapInfo& in_MapInfo)
{
	return (this->*_InstantMapAdd2)(in_MapInfo);

	//TODO
}


hook_method<void (CMapInfo::*)(const mystd::string in_mapName)> CMapInfo::_InstantMapRemove(SERVER, "CMapInfo::InstantMapRemove");
void CMapInfo::InstantMapRemove(const mystd::string in_mapName)
{
	return (this->*_InstantMapRemove)(in_mapName);

	//TODO
}


hook_method<bool (CMapInfo::*)(const mystd::string in_mapName)> CMapInfo::_GetPlayerEnter(SERVER, "CMapInfo::GetPlayerEnter");
bool CMapInfo::GetPlayerEnter(const mystd::string in_mapName)
{
	return (this->*_GetPlayerEnter)(in_mapName);

	//TODO
}


hook_method<void (CMapInfo::*)(const mystd::string in_mapName, const bool in_bPlayerEnter)> CMapInfo::_SetPlayerEnter(SERVER, "CMapInfo::SetPlayerEnter");
void CMapInfo::SetPlayerEnter(const mystd::string in_mapName, const bool in_bPlayerEnter)
{
	return (this->*_SetPlayerEnter)(in_mapName, in_bPlayerEnter);

	//TODO
}


hook_method<void (CMapInfo::*)(const mystd::string in_mapName, int& out_ZSVR, bool& out_bPlayerEnter)> CMapInfo::_GetZSVRandPlayerEnter(SERVER, "CMapInfo::GetZSVRandPlayerEnter");
void CMapInfo::GetZSVRandPlayerEnter(const mystd::string in_mapName, int& out_ZSVR, bool& out_bPlayerEnter) // line 133
{
	return (this->*_GetZSVRandPlayerEnter)(in_mapName, out_ZSVR, out_bPlayerEnter);

	MAPINFOCONTAINER_ITER iter = m_mapInfo.find(in_mapName);
	if( iter != m_mapInfo.end() )
	{
		MapInfo* info = iter->second;
		out_ZSVR = info->ZSID;
		out_bPlayerEnter = info->bPlayerEnter;
	}
	else
	{
		out_ZSVR = -1;
		out_bPlayerEnter = false;
	}
}
