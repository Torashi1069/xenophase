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


void CConnectLogDB::AddConnectLog(char* pszID, char* pszIP, DWORD dwAID)
{
	m_csConnectLog.Enter();

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("{call AddConnectLog(%s, %s, %d)}", pszIP, pszID, dwAID);
	stmt.CDatabaseStatement::Release();

	m_csConnectLog.Leave();
}
