#pragma once
#include "Common/CriticalSection.h"


struct SUSER_
{
	/* this+  0 */ int m_nState;
	/* this+  4 */ int m_nSecurityCode;
	/* this+  8 */ int m_nAID;
	/* this+ 12 */ char m_szID[24];
	/* this+ 36 */ char m_szPersonalNum[25];
	/* this+ 61 */ char m_szEmail[40];
	/* this+104 */ int m_nSex;
	/* this+108 */ int m_nIP;
	/* this+112 */ int m_nPresentSID;
	/* this+116 */ int m_nIsGameStarted;
};


struct tag_SMAP
{
	/* this+ 0 */ stdext::hash_map<int,SUSER_*> m_mapMap;
	/* this+40 */ CCriticalSection m_csMap;
};


class CUserList
{
private:
	/* this+ 0 */ CCriticalSection m_csUserList;
	/* this+24 */ int m_nSize;
	/* this+28 */ int m_nCountAuth;
	/* this+32 */ tag_SMAP* m_pUser;

public:
	CUserList();
	~CUserList();
	void Insert(DWORD dwAID, SUSER_& object);
	void Delete(DWORD dwAID);
	int GetCount();
	int GetCountAuth();
	BOOL Bring(DWORD dwAID, SUSER_* pObject);
	BOOL Get(DWORD dwAID, SUSER_* pObject);
//	int IsObject(DWORD dwAID);
//	void GetAllObject(std::list<SUSER_>*);
};
