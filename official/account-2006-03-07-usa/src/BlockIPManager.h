#pragma once
#include "Common/CriticalSection.h"
#include "Common/IPList.h"
#include "Common/Singleton.h"


struct tag_info
{
	/* this+0 */ char incorrectCount;
	/* this+4 */ DWORD dwBlockTime;
};


struct tag_blockdata
{
	/* this+ 0 */ CCriticalSection m_cs;
	/* this+24 */ stdext::hash_map<DWORD,tag_info> m_mapBlockInfo;
};


class CBlockIPManager : public CSingleton<CBlockIPManager>
{
private:
	/* this+0 */ //CSingleton<CBlockIPManager> baseclass_0;
	/* this+0 */ CIPList m_iplistPermanentBlock;
	/* this+4 */ tag_blockdata* m_pBlockData;

public:
	CBlockIPManager();
	~CBlockIPManager();
	bool IsBlock(DWORD dwKey);
	void IncreaseIncorrectCount(char* szName, DWORD dwAID, DWORD dwIP, unsigned char keyType);
	void ClearIncorrectCount(DWORD dwKey);
	bool loadBlockIPListFile(char* szFileName);
	bool IsPermanentBlock(DWORD dwKey);
};
