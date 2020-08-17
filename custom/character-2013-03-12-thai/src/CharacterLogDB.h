#pragma once
#include "Common/CriticalSection.h"
#include "Common/Database.h"
#include "Common/Singleton.h"


class CCharacterLogDB : public CDatabase, public CSingleton<CCharacterLogDB>
{
private:
	/* this+ 0 */ //CDatabase baseclass_0;
	/* this+37 */ //CSingleton<CCharacterLogDB> baseclass_37;
	/* this+40 */ CCriticalSection m_csCharacterLogDB;
	/* this+64 */ std::string m_strPwd;
	/* static  */ static const std::string m_strFileDSNfileName;

public:
	CCharacterLogDB();
	~CCharacterLogDB();
	BOOL DeleteCharaterLog(const unsigned long GID, const unsigned long AID, const char* pDeleteCharname, const char* szIP);
//	int CreateCharacterLog(unsigned long, unsigned long, const char *, char *, int);
//	int GetCharConnectLog_Login(unsigned long, unsigned long, char *, short, short, int, const bool, char *);
//	int GetCharConnectLog_LogOut(unsigned long);
//	int AddCharConnectLog(unsigned long);
	void SetPwd(const char* in_szPwd);
	bool Connect();
};
