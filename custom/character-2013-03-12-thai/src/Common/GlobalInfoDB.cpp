#include "Common/DatabaseStatement.h"
#include "Common/EnterTraceLog.h"
#include "Common/GlobalInfoDB.h"
#include "Common/Network.h"
#include "Common/ServerInfoList.h"


/// globals
CGlobalInfoDB g_GlobalInfo;


CGlobalInfoDB::CGlobalInfoDB()
{
	m_bIsColumnPrivateAdded = false;
}


CGlobalInfoDB::~CGlobalInfoDB()
{
}


bool CGlobalInfoDB::IsColumnPrivateAdded()
{
	return m_bIsColumnPrivateAdded;
}


void CGlobalInfoDB::InitColumnInfo()
{
	m_bIsColumnPrivateAdded = false;

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("EXEC sp_columns @table_name = ServerInfo, @column_name  = PrivateIP");

	while( SQL_SUCCEEDED(stmt.CDatabaseStatement::Fetch()) )
		m_bIsColumnPrivateAdded = true;
}


void CGlobalInfoDB::InitServerInfoList(bool bLogInfo)
{
	this->CGlobalInfoDB::InitColumnInfo();

	CDatabaseStatement stmt(this);
	if( m_bIsColumnPrivateAdded )
		stmt.CDatabaseStatement::Query("SELECT SID, Type, IP, Port, DestinationOneSID, DestinationTwoSID, SvrName, PrivateIP, PrivatePort FROM ServerInfo");
	else
		stmt.CDatabaseStatement::Query("SELECT SID, Type, IP, Port, DestinationOneSID, DestinationTwoSID, SvrName FROM ServerInfo");

	SSERVERINFO serverInfo;
	stmt.CDatabaseStatement::BindNumberColumn(1, &serverInfo.m_nSID);
	stmt.CDatabaseStatement::BindNumberColumn(2, &serverInfo.m_nType);
	stmt.CDatabaseStatement::BindStringColumn(3, serverInfo.m_szIP, sizeof(serverInfo.m_szIP)-1);
	stmt.CDatabaseStatement::BindNumberColumn(4, &serverInfo.m_nPort);
	stmt.CDatabaseStatement::BindNumberColumn(5, &serverInfo.m_nPrimaryDestnation);
	stmt.CDatabaseStatement::BindNumberColumn(6, &serverInfo.m_nSecondDestnation);
	stmt.CDatabaseStatement::BindStringColumn(7, serverInfo.m_szName, sizeof(serverInfo.m_szName)-1);
	if( m_bIsColumnPrivateAdded )
	{
		stmt.CDatabaseStatement::BindStringColumn(8, serverInfo.m_szPrivateIP, sizeof(serverInfo.m_szPrivateIP)-1);
		stmt.CDatabaseStatement::BindNumberColumn(9, &serverInfo.m_nPrivatePort);
	}

	memset(&serverInfo, 0, sizeof(serverInfo));
	while( SQL_SUCCEEDED(stmt.CDatabaseStatement::Fetch()) )
	{
		serverInfo.m_dwIP = CNetwork::GetObj()->CNetwork::GetDWORDIP(serverInfo.m_szIP);
		CNetwork::GetObj()->CNetwork::GetTextIP(serverInfo.m_dwIP, serverInfo.m_szIP);
		if( m_bIsColumnPrivateAdded )
		{
			serverInfo.m_dwPrivateIP = CNetwork::GetObj()->CNetwork::GetDWORDIP(serverInfo.m_szPrivateIP);
			CNetwork::GetObj()->CNetwork::GetTextIP(serverInfo.m_dwPrivateIP, serverInfo.m_szPrivateIP);
		}

		static CServerInfoList* pServerInfoList = CSingleton<CServerInfoList>::getSingletonPtr();
		pServerInfoList->CServerInfoList::AddServerInfo(&serverInfo);

		printf("%4d %4d %s %s\n", serverInfo.m_nSID, serverInfo.m_nType, serverInfo.m_szIP, serverInfo.m_szName);

		if( bLogInfo ) // guessed
			CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%4d %4d %s %s 1st %d 2nd %d\n", serverInfo.m_nSID, serverInfo.m_nType, serverInfo.m_szIP, serverInfo.m_szName, serverInfo.m_nPrimaryDestnation, serverInfo.m_nSecondDestnation);

		memset(&serverInfo, 0, sizeof(serverInfo));
	}
}
