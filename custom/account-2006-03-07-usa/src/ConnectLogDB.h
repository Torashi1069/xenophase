#pragma once
#include "ConnectLog.h"
#include "Common/CriticalSection.h"
#include "Common/Database.h"
#include "Common/Singleton.h"


class CConnectLogDB : public CDatabase, public CSingleton<CConnectLogDB>
{
private:
	/* this+   0 */ //CDatabase baseclass_0;
	/* this+2056 */ //CSingleton<CConnectLogDB> baseclass_2056;
	/* this+2056 */ CCriticalSection m_csConnectLog;

public:
	CConnectLogDB();
	~CConnectLogDB();
	void AddConnectLog(SCONNECTLOG* pIn); // @custom
};
