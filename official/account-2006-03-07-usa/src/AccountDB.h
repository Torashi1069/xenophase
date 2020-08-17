#pragma once
#include "Common/CriticalSection.h"
#include "Common/Database.h"


struct SUSERINFO
{
	/* this+ 0 */ int m_nSex;
	/* this+ 4 */ char m_szPersonalNum[25];
	/* this+29 */ char m_szEmail[40];
	/* this+72 */ int m_nGrade;
	/* this+76 */ int m_nIP;
	/* this+80 */ char m_szLastConnectionTime[30];
};


struct SAUTHENTICATE
{
	/* this+ 0 */ DWORD m_dwResult; // enum REFUSE_*
	/* this+ 4 */ DWORD m_dwAID;
	/* this+ 8 */ DWORD m_dwGrade;
	/* this+12 */ DWORD m_dwConfirmed;
	/* this+16 */ char m_passwd[24];
};


class CAccountDB : public CDatabase
{
private:
	/* this+   0 */ //CDatabase baseclass_0;
	/* this+2056 */ CCriticalSection m_csAccountDB;

public:
	CAccountDB();
	~CAccountDB();
	void GetBlockDate(char* lpszID, char* lpszBlockDate);
	DWORD GetAID(const char* lpszID);
	void GetID(DWORD dwAID, const char* lpszID);
	void AuthenticateUser(char* lpszID, char* lpszPassword, SAUTHENTICATE& authenticate, BYTE byClientType);
	BOOL GetUserInfo(DWORD dwAID, SUSERINFO* pUserInfo);
	int UpdateUserInfo(DWORD dwAID, SUSERINFO* pUserInfo);
	int UpdateUserInfo2(DWORD dwAID, SUSERINFO* pUserInfo);
	void GetAuthenticateInfo(char* lpszID, BYTE byClientType, SAUTHENTICATE* pAuthencate);
};
