#pragma once
#include "Common/CriticalSection.h"
#include "Common/Singleton.h"


struct tag_BLOCKTIME
{
	/* this+ 0 */ stdext::hash_map<DWORD,DWORD> m_map;
	/* this+40 */ CCriticalSection m_csMap;
};


class CBlockTime : public CSingleton<CBlockTime>
{
private:
	/* this+0 */ //CSingleton<CBlockTime> baseclass_0;
	/* this+0 */ tag_BLOCKTIME* m_pBlockTime;

public:
	CBlockTime();
	~CBlockTime();
	void UpdateBlockTime(DWORD dwKey, DWORD dwBlockTime);
	void DeleteBlockTime(DWORD dwKey);
	BOOL IsBlock(DWORD dwKey);
};
