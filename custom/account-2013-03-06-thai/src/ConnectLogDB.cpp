#include "ConnectLogDB.h"
#include "Common/DatabaseStatement.h"


/// singleton instance
static CConnectLogDB g_ConnectLogDB;
CConnectLogDB* CSingleton<CConnectLogDB>::ms_Singleton;


CConnectLogDB::CConnectLogDB()
{
}


CConnectLogDB::~CConnectLogDB()
{
}


/// @custom
void CConnectLogDB::AddConnectLog(SCONNECTLOG* pIn)
{
	m_csConnectLog.Enter();

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("{call AddConnectLog(%d, %s, %d, %s)}", pIn->bLogInOrOut, pIn->szIP, pIn->dwAID, pIn->szID); // [patch] login/logout event logging
	stmt.CDatabaseStatement::Release();

	m_csConnectLog.Leave();
}
