#pragma once
#include "Common/CriticalSection.h"
#include "Common/Singleton.h"


struct SBLOCKTIME
{
	/* this+0 */ DWORD m_dwKey;
	/* this+4 */ DWORD m_dwBlockTime;
};


class CBlockTime : public CSingleton<CBlockTime>
{
private:
	/* this+   0 */ //CSingleton<CBlockTime> baseclass_0;
	/* this+   0 */ std::list<SBLOCKTIME> m_listBlockTime[100];
	/* this+1200 */ CCriticalSection m_csBlockTime[100];

public:
	CBlockTime();
	~CBlockTime();
	void UpdateBlockTime(DWORD dwKey, DWORD dwBlockTime);
	void DeleteBlockTime(DWORD dwKey);
	BOOL IsBlock(DWORD dwKey);
	void threadBlockTime(void* lpParam);
};
