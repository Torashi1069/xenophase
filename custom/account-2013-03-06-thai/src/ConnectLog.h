#pragma once
#include "Common/CriticalSection.h"
#include "Common/Singleton.h"


struct SCONNECTLOG
{
	/* this+ 0 */ char szID[24+1];
	/* this+25 */ char szIP[16+1];
	/* this+44 */ DWORD dwAID;
	/* this+48 */ int bLogInOrOut; //@custom
};


class CConnectLog : public CSingleton<CConnectLog>
{
private:
	/* this+ 0 */ //CSingleton<CConnectLog> baseclass_0;
	/* this+ 0 */ std::queue<SCONNECTLOG*> m_queueConnectLog;
	/* this+24 */ CCriticalSection m_csConnectLog;

public:
	CConnectLog();
	~CConnectLog();
	void AddConnectLog(char* pszID, DWORD dwIP, DWORD dwAID, BOOL bLogInOrOut); //@custom
	void threadConnectLog(void* lpParam);
};
