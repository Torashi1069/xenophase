#pragma once
#include "std/map"
#include "std/string"
#include "struct.hpp"
#include "ODBC.h"


class CMapInfo : public CODBC
{
	/* this+ 0 */ public: //CODBC baseclass_0;
	/* this+20 */ private: mystd::map<mystd::string,MapInfo*> m_mapInfo;

	typedef mystd::map<mystd::string,MapInfo*>::const_iterator MAPINFOCONTAINER_ITER;

	public: CMapInfo::CMapInfo(void);
	public: virtual CMapInfo::~CMapInfo(void);
	public: void CMapInfo::GetMapInfo(void);
	public: int CMapInfo::GetServerID(const char* mapName);
	public: int CMapInfo::IsSiege(const char* mapName);
	public: bool CMapInfo::InstantMapAdd2(const MapInfo& in_MapInfo);
	public: void CMapInfo::InstantMapRemove(const mystd::string in_mapName);
	public: bool CMapInfo::GetPlayerEnter(const mystd::string in_mapName);
	public: void CMapInfo::SetPlayerEnter(const mystd::string in_mapName, const bool in_bPlayerEnter);
	public: void CMapInfo::GetZSVRandPlayerEnter(const mystd::string in_mapName, int& out_ZSVR, bool& out_bPlayerEnter);

private:
	static hook_method<void (CMapInfo::*)(void)> CMapInfo::_GetMapInfo;
	static hook_method<int (CMapInfo::*)(const char* mapName)> CMapInfo::_GetServerID;
	static hook_method<int (CMapInfo::*)(const char* mapName)> CMapInfo::_IsSiege;
	static hook_method<bool (CMapInfo::*)(const MapInfo& in_MapInfo)> CMapInfo::_InstantMapAdd2;
	static hook_method<void (CMapInfo::*)(const mystd::string in_mapName)> CMapInfo::_InstantMapRemove;
	static hook_method<bool (CMapInfo::*)(const mystd::string in_mapName)> CMapInfo::_GetPlayerEnter;
	static hook_method<void (CMapInfo::*)(const mystd::string in_mapName, const bool in_bPlayerEnter)> CMapInfo::_SetPlayerEnter;
	static hook_method<void (CMapInfo::*)(const mystd::string in_mapName, int& out_ZSVR, bool& out_bPlayerEnter)> CMapInfo::_GetZSVRandPlayerEnter;

	friend class CMapResMgr;
};
