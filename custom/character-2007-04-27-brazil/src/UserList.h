#pragma once
#include "Common/CriticalSection.h"
class CUserProcess;


struct __SUSER__
{
	/* this+  0 */ CUserProcess* m_pUserProcess;
	/* this+  4 */ DWORD m_dwSessionID;
	/* this+  8 */ int m_nSelectedGID;
	/* this+ 12 */ int m_nSelectedSlotIndex;
	/* this+ 16 */ int m_nSID;
	/* this+ 20 */ char m_szID[26];
	/* this+ 46 */ char m_szPersonalNumber[24];
	/* this+ 70 */ char m_szEMail[52];
	/* this+124 */ DWORD m_dwSecurityCode;
	/* this+128 */ DWORD m_dwIP;
	/* this+132 */ DWORD m_dwAID;
	/* this+136 */ int m_bIsPCBang;
	/* this+140 */ int m_nPayTypeEx;
	/* this+144 */ int m_nConnectionArea;
	/* this+148 */ int m_nConnectionState;
	/* this+152 */ int m_nEventNum;
	/* this+156 */ DWORD m_dwConnectionTime;
};


struct tag_SMAP
{
	/* this+ 0 */ stdext::hash_map<DWORD,__SUSER__*> m_Map;
	/* this+40 */ CCriticalSection m_csMap;
};


class CUserList
{
private:
	/* this+ 0 */ CCriticalSection m_csUserList;
	/* this+24 */ int m_nSize;
	/* this+28 */ tag_SMAP* m_pUser;

public:
	CUserList();
	~CUserList();
	void Insert(DWORD dwAID, __SUSER__& object);
	void Delete(DWORD dwAID);
	int GetCount();
	BOOL Bring(DWORD dwAID, __SUSER__* pObject);
	BOOL Get(DWORD dwAID, __SUSER__* pObject);
//	int IsObject(DWORD dwAID);
};
