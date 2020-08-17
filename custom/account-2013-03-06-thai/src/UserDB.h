#pragma once
#include "Common/CriticalSection.h"
#include "Common/Database.h"


class CUserDB : public CDatabase
{
public:
	CUserDB();
	virtual ~CUserDB();

private:
	/* this+ 0 */ //const CUserDB::`vftable';
	/* this+ 4 */ //CDatabase baseclass_4;
	/* this+40 */ CCriticalSection m_csUserDB;
	/* this+64 */ RTL_CRITICAL_SECTION m_cs;

public:
//	bool CanLogin(int, int, int);
//	bool InsertUser(SUSER_&);
//	bool GetUser(int, SUSER_*);
//	void DeleteUser(int, int, int);
//	void DeleteUser(SUSER_&);
//	void InitUserList(CUserList*, int, int);
};
