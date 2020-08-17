#pragma once
#include "Common/CriticalSection.h"
#include "Common/Database.h"


class CUserDB : public CDatabase
{
public:
//	int IsUser(int nAID);
//	void AddUser(SUSER_* pUser);
//	int GetUser(int, SUSER_*);
//	void UpdateUser(SUSER_* pUser);
//	void InitUserList(CUserList& mapUserList);
//	void UpdateUserDisconnect(int);
//	void DeleteUserDisconnect(int nAID);
//	int IsConnect(int);

private:
	/* this+   0 */ //CDatabase baseclass_0;
	/* this+2056 */ CCriticalSection m_csUserDB;
};
