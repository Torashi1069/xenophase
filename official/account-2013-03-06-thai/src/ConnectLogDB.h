#pragma once
#include "Common/CriticalSection.h"
#include "Common/Database.h"
#include "Common/Singleton.h"


class CConnectLogDB : public CDatabase, public CSingleton<CConnectLogDB>
{
private:
	/* this+ 0 */ //CDatabase baseclass_0;
	/* this+37 */ //CSingleton<CConnectLogDB> baseclass_37;
	/* this+40 */ CCriticalSection m_csConnectLog;

public:
	CConnectLogDB();
	~CConnectLogDB();
	void AddConnectLog(char* pszID, char* pszIP, DWORD dwAID);
};
