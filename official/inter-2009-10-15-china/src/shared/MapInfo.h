#pragma once
#include "ODBC.h"
#include "structs.hpp"
#include "std/map"
#include "std/string"


class CMapInfo : public CODBC
{
	/* this+0x0  */ //CODBC
	/* this+0x14 */ private: mystd::map<mystd::string,MapInfo*> m_mapInfo;

	//public: void CMapInfo::CMapInfo();
	//public: void CMapInfo::~CMapInfo();
	public: void CMapInfo::GetMapInfo(void);
	//public: int CMapInfo::GetServerID(const char *);
	//public: int CMapInfo::IsSiege(const char *);
	//public: bool CMapInfo::InstantMapAdd2(const MapInfo &);
	//public: void CMapInfo::InstantMapRemove(const mystd::string);
	//public: bool CMapInfo::GetPlayerEnter(const mystd::string);
	//public: void CMapInfo::SetPlayerEnter(const mystd::string, const bool);
	//public: void CMapInfo::GetZSVRandPlayerEnter(const mystd::string, int &, bool &);

	typedef mystd::map<mystd::string,MapInfo*>::const_iterator MAPINFOCONTAINER_ITER;

private:
	static hook_method<void (CMapInfo::*)(void)> CMapInfo::_GetMapInfo;
};
