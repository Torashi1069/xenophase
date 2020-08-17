#pragma once
#include "Common/CriticalSection.h"
class CUserProcess;


struct __SUSERAUTHENTICATE__
{
	/* this+ 0 */ CUserProcess* m_pUserProcess;
	/* this+ 4 */ DWORD m_dwSessionID;
	/* this+ 8 */ DWORD m_dwSecurityCode;
	union {
	/* this+12 */ int m_iAccountSID;
	/* this+12 */ DWORD m_dwIP;
	};
};


struct tag_SMAP_AUTH
{
	/* this+ 0 */ stdext::hash_map<DWORD,__SUSERAUTHENTICATE__*> m_Map;
	/* this+44 */ CCriticalSection m_csMap;
};


class CUserAuthenticate
{
private:
	/* this+ 0 */ CCriticalSection m_cs;
	/* this+24 */ int m_nSize;
	/* this+28 */ tag_SMAP_AUTH* m_pAuthenticate;

public:
	CUserAuthenticate();
	~CUserAuthenticate();
	void Insert(DWORD dwAID, __SUSERAUTHENTICATE__& object);
//	void Delete(DWORD dwAID);
	BOOL Bring(DWORD dwAID, __SUSERAUTHENTICATE__* pObject);
//	int Get(DWORD dwAID, __SUSERAUTHENTICATE__* pObject);
//	int IsObject(DWORD dwAID);
	int GetCount();
};
