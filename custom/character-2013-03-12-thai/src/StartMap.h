#pragma once
#include "Common/ScriptParser.h"
#include "Common/Singleton.h"


struct _SSTARTMAP_
{
	/* this+ 0 */ int m_nXPos;
	/* this+ 4 */ int m_nYPos;
	/* this+ 8 */ char m_szMapName[16];
	/* this+24 */ int m_nSxPos;
	/* this+28 */ int m_nSyPos;
	/* this+32 */ char m_szRestartMapName[16];
};


class CStartMap : public CSingleton<CStartMap>
{
private:
	/* this+0 */ //CSingleton<CStartMap> baseclass_0;
	/* this+0 */ DWORD m_dwMapCount;
	/* this+4 */ _SSTARTMAP_* m_pStartMapInfo;
	/* this+8 */ CScriptParser m_parser;

public:
	CStartMap();
	~CStartMap();
	bool Initialize();
	void GetRandomOne(_SSTARTMAP_& rData);
};
