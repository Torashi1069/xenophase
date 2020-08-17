#pragma once
#include "Common/ScriptParser.h"
#include "Common/Singleton.h"


struct tag_MAPPOSINFO
{
	/* this+0 */ int m_nXPos;
	/* this+4 */ int m_nYPos;
	/* this+8 */ char m_szMapName[16];
};


class CForceMap : public CSingleton<CForceMap>
{
private:
	/* this+ 0 */ //CSingleton<CForceMap> baseclass_0;
	/* this+ 0 */ DWORD m_dwMapCount;
	/* this+ 4 */ DWORD m_dwRestartMapCount;
	/* this+ 8 */ tag_MAPPOSINFO* m_pMapInfo;
	/* this+12 */ tag_MAPPOSINFO* m_pRestartMapInfo;
	/* this+16 */ CScriptParser m_parser;

public:
	CForceMap();
	~CForceMap();
	DWORD getMapCount();
	DWORD getRestartMapCount();
//	int InitializeMap(const char*);
//	bool InitializeRestartMap(const char*);

private:
//	int InitializeMapInfoFromFile(FILE*, tag_MAPPOSINFO**, unsigned long*);

public:
//	void GetRandomMap(tag_MAPPOSINFO&);
//	void GetRandomRestartMap(tag_MAPPOSINFO&);
};
