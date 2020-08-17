#pragma once
class CCharSvrProcess;


struct SUSER_
{
	/* this+  0 */ int m_nState;
	/* this+  4 */ int m_nSecurityCode;
	/* this+  8 */ int m_nAID;
	/* this+ 12 */ char m_szID[24];
	/* this+ 36 */ char m_szPersonalNum[25];
	/* this+ 61 */ char m_szEmail[40];
	/* this+104 */ int m_nSex;
	/* this+108 */ DWORD m_nIP;
	/* this+112 */ int m_nPresentSID;
	/* this+116 */ int m_nIsGameStarted;
	/* this+120 */ int m_nBirthDay;
	/* this+124 */ bool m_bNotPaid;
	/* this+128 */ int m_nAccountSID;
	/* this+132 */ int m_isPCBang;
	/* this+136 */ CCharSvrProcess* m_process;
	/* this+140 */ DWORD m_dwSessionID;
	/* this+144 */ int m_nPayTypeEx;
	/* this+148 */ int m_nConnectionArea;
	/* this+152 */ int m_nConnectionState;
	/* this+156 */ int m_nEventNum;
	/* this+160 */ DWORD m_dwConnectionTime;
};


class CUserList
{
private:
	/* this+ 0 */ //const CUserList::`vftable';
	/* this+ 4 */ int m_nSize;
	/* this+ 8 */ int m_nCountAuth;
	/* this+12 */ int m_nAllocSize;
	/* this+16 */ SUSER_** m_pUser;
	/* this+20 */ LONG* m_pLock;
	/* this+24 */ char* m_pStatus;
	/* this+28 */ bool m_bInitSuccess;

private:
	void LockAID(DWORD dwAID);
	void ReleaseAID(DWORD dwAID);

public:
	CUserList();
	virtual ~CUserList();
	void Insert(DWORD dwAID, SUSER_& object);
	void Delete(DWORD dwAID);
	BOOL Bring(DWORD dwAID, SUSER_* pObject);
	BOOL Get(DWORD dwAID, SUSER_* pObject);
//	int IsObject(DWORD);
//	void GetAllObject(std::list<SUSER_>*);
	int GetCount();
	int GetCountAuth();
	int GetAllocCount();
//	void SetCharProcess(DWORD, DWORD, CCharSvrProcess*);
	CCharSvrProcess* GetCharProcess(DWORD dwAID);
	bool IsPCBangUser(DWORD dwAID);
};
