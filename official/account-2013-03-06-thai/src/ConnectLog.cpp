#include "Account.h" // g_bProcessPermit
#include "ConnectLog.h"
#include "ConnectLogDB.h"
#include "Common/EnterTraceLog.h"
#include "Common/Network.h"
#include "Common/Thread.h"


/// singleton instance
static CConnectLog g_ConnectLog;
CConnectLog* CSingleton<CConnectLog>::ms_Singleton;


CConnectLog::CConnectLog()
{
	CreateMemberThread<CConnectLog>(this, &CConnectLog::threadConnectLog, NULL);
}


CConnectLog::~CConnectLog()
{
}


// guessed
void CConnectLog::AddConnectLog(char* pszID, DWORD dwIP, DWORD dwAID)
{
	m_csConnectLog.Enter();

	SCONNECTLOG* pLog = new SCONNECTLOG;
	if( pLog == NULL )
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "CConnectLog::AddConnectLog() new fail!");

	memcpy(pLog->szID, pszID, sizeof(pLog->szID));
	CNetwork::GetObj()->CNetwork::GetTextIP(dwIP, pLog->szIP);
	pLog->dwAID = dwAID;

	m_queueConnectLog.push(pLog);

	m_csConnectLog.Leave();
}


// guessed
void CConnectLog::threadConnectLog(void* lpParam)
{
	while( g_bProcessPermit )
	{
		Sleep(10);

		if( m_queueConnectLog.size() == 0 )
			continue;

		m_csConnectLog.Enter();
		SCONNECTLOG* log = m_queueConnectLog.front();
		m_queueConnectLog.pop();
		m_csConnectLog.Leave();

		static CConnectLogDB* pConnectLog = CSingleton<CConnectLogDB>::getSingletonPtr();
		pConnectLog->CConnectLogDB::AddConnectLog(log->szID, log->szIP, log->dwAID);
		delete log;
	}

	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "threadConnectLog OUT\n");
}
