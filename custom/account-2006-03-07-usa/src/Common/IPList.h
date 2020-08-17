#pragma once
#include "Common/CriticalSection.h"


struct tag_range
{
	/* this+0 */ bool exist;
	/* this+1 */ bool list[256];
};


struct tag_IPRange
{
	/* this+0 */ WORD baseIP;
	/* this+2 */ tag_range list[256];
};


struct tag_HashedIPList
{
	/* this+ 0 */ stdext::hash_map<WORD,tag_IPRange*> m_map;
	/* this+40 */ CCriticalSection m_cs;
};


class CIPList
{
private:
	/* this+0 */ tag_HashedIPList* m_pIPList;

public:
	CIPList();
	~CIPList();
//	bool AddIP(DWORD dwIP);
	bool AddIP(DWORD dwLowIP, DWORD dwHighIP);
//	bool DeleteIP(DWORD dwIP);
//	bool DeleteIP(DWORD dwLowIP, DWORD dwHighIP);
	bool IsExist(DWORD dwIP);
};
