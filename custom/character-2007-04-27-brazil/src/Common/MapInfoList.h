#pragma once
#include "Common/CriticalSection.h"
#include "Common/Singleton.h"


struct SMAPINFO
{
	/* this+ 0 */ DWORD m_dwSID;
	/* this+ 4 */ char m_szMapName[16];
	/* this+20 */ DWORD m_dwMapID;
	/* this+24 */ DWORD m_dwMapType;
};


class CMapInfoList : public CSingleton<CMapInfoList>
{
private:
	/* this+ 0 */ //CSingleton<CMapInfoList> baseclass_0;
	/* this+ 0 */ std::vector<SMAPINFO> m_vectorMapInfoList;
	/* this+16 */ CCriticalSection m_csMapInfoList;

public:
	void AddMapInfo(SMAPINFO* pMapInfo);
	int GetSID(char* pMapName);
	int GetMapType(char* pMapName);
};
