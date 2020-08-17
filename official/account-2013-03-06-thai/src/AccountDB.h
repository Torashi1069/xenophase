#pragma once
#include "Common/CriticalSection.h"
#include "Common/Database.h"


struct SUSERINFO
{
	/* this+  0 */ int m_nSex;
	/* this+  4 */ char m_szPersonalNum[25];
	/* this+ 29 */ char m_szEmail[40];
	/* this+ 72 */ int m_nGrade;
	/* this+ 76 */ int m_nIP;
	/* this+ 80 */ char m_szLastConnectionTime[30];
	/* this+112 */ int m_nBirthdate;
};


struct SAUTHENTICATE
{
	/* this+ 0 */ char m_ID[26];
	/* this+28 */ DWORD m_dwResult; // enum REFUSE_*
	/* this+32 */ DWORD m_dwAID;
	/* this+36 */ DWORD m_dwGrade;
	/* this+40 */ DWORD m_dwConfirmed;
	/* this+44 */ char m_passwd[23+1];
};


class CAccountDB : public CDatabase
{
private:
	/* this+ 0 */ //CDatabase baseclass_0;
	/* this+36 */ CCriticalSection m_csAccountDB;
	/* this+60 */ std::map<int,std::string> m_mapIsConfirmedMsg;

public:
	CAccountDB();
	~CAccountDB();
	void GetBlockDate(char* lpszID, char* lpszBlockDate);
	DWORD GetAID(const char* lpszID);
	bool GetID(DWORD dwAID, const char* lpszID);
	BOOL GetUserInfo(DWORD dwAID, SUSERINFO* pUserInfo);
	int UpdateUserInfo(DWORD dwAID, SUSERINFO* pUserInfo);
	int UpdateUserInfo2(DWORD dwAID, SUSERINFO* pUserInfo);
	void GetAuthenticateInfo(char* szRecvID, BYTE byClientType, SAUTHENTICATE* pAuthencate);
//	void AuthenticateUser(char* lpszID, char* lpszPassword, SAUTHENTICATE& authenticate);
	void AuthenticateUser(char* lpszID, char* lpszPassword, SAUTHENTICATE& authenticate, BYTE byClientType);
	void UpdateIsConfirmed(DWORD dwAID, int nVal);
//	void InitIsConfirmedMsg();
	void GetIsConfirmedMsg(int isConfirmed, char* msg_buf, int buf_len);
};
