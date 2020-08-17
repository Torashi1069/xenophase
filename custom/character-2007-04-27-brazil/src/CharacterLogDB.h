#pragma once
#include "Common/CriticalSection.h"
#include "Common/Database.h"
#include "Common/Singleton.h"


class CCharacterLogDB : public CDatabase, public CSingleton<CCharacterLogDB>
{
private:
	/* this+   0 */ //CDatabase baseclass_0;
	/* this+2056 */ //CSingleton<CCharacterLogDB> baseclass_2056;
	/* this+2056 */ CCriticalSection m_csCharacterLogDB;

public:
	CCharacterLogDB();
	~CCharacterLogDB();
	BOOL DeleteCharaterLog(unsigned long GID, unsigned long AID, char* pDeleteCharname, char* szIP);
//	int AddCharConnectLog(unsigned long);
};
