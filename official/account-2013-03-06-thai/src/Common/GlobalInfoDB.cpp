#include "Common/DatabaseStatement.h"
#include "Common/EnterTraceLog.h"
#include "Common/GlobalInfoDB.h"
#include "Common/Network.h"
#include "Common/ServerInfoList.h"


/// singleton instance
CGlobalInfoDB* CGlobalInfoDB::m_cpSelf;


CGlobalInfoDB::CGlobalInfoDB()
{
	m_bIsColumnPrivateAdded = false;
	m_bOK = true;
}


CGlobalInfoDB::~CGlobalInfoDB()
{
}


bool CGlobalInfoDB::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CGlobalInfoDB();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->m_bOK )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CGlobalInfoDB::DestroyInstance()
{
	if( m_cpSelf != NULL)
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
};


/// @custom
CGlobalInfoDB* CGlobalInfoDB::GetObj()
{
	return m_cpSelf;
}


bool CGlobalInfoDB::isOK() const
{
	return m_bOK;
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

	memset(&serverInfo, 0, sizeof(serverInfo));
	while( SQL_SUCCEEDED(stmt.CDatabaseStatement::Fetch()) )
	{
		serverInfo.m_dwIP = CNetwork::GetObj()->CNetwork::GetDWORDIP(serverInfo.m_szIP);
		CNetwork::GetObj()->CNetwork::GetTextIP(serverInfo.m_dwIP, serverInfo.m_szIP);

		static CServerInfoList* pServerInfoList = CSingleton<CServerInfoList>::getSingletonPtr();
		pServerInfoList->CServerInfoList::AddServerInfo(&serverInfo);

		if( bLogInfo ) // guessed
			CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%4d %4d %s %s 1st %d 2nd %d\n", serverInfo.m_nSID, serverInfo.m_nType, serverInfo.m_szIP, serverInfo.m_szName, serverInfo.m_nPrimaryDestnation, serverInfo.m_nSecondDestnation);

		memset(&serverInfo, 0, sizeof(serverInfo));
	}
}


int CGlobalInfoDB::GetEventItemCount(const int iAID, const int nServerType)
{
	CDatabaseStatement stmt(this);

	int iMobileItemCount = 0;
	if( nServerType == 16 || nServerType == 8 )
	{
		stmt.CDatabaseStatement::Query("{ call GetMobileEventCount( %d, 2 ) } ", iAID);
	}
	else
	if( nServerType == 32 )
	{
		stmt.CDatabaseStatement::Query("{ call GetMobileEventCount( %d, 1 ) } ", iAID);
	}

	stmt.CDatabaseStatement::BindNumberColumn(1, &iMobileItemCount);
	stmt.CDatabaseStatement::Fetch();
	stmt.CDatabaseStatement::Release();

	return iMobileItemCount;
}


int CGlobalInfoDB::GetBlockedUser(const int nAID, int& nBlockType, int& nReason, char* szBlockDate)
{
	CDatabaseStatement stmt(this);

	int nRet = 0;
	char szBlockedEndDate[24] = {};
	char szCurrentDBDate[24] = {};

	stmt.CDatabaseStatement::Query("{ call usp_blockedUser_get( %d ) } ", nAID);
	stmt.CDatabaseStatement::BindNumberColumn(1, &nBlockType);
	stmt.CDatabaseStatement::BindNumberColumn(2, &nReason);
	stmt.CDatabaseStatement::BindStringColumn(3, szBlockedEndDate, sizeof(szBlockedEndDate));
	stmt.CDatabaseStatement::BindStringColumn(4, szCurrentDBDate, sizeof(szCurrentDBDate));

	if( SQL_SUCCEEDED(stmt.CDatabaseStatement::Fetch())
	 && (nBlockType == 1 || nBlockType == 2 )
	 && strncmp(szBlockedEndDate, szCurrentDBDate, 16) > 0 )
	{
		strncpy(szBlockDate, szBlockedEndDate, 16);
		nRet = nBlockType;
	}

	stmt.CDatabaseStatement::Release();
	return nRet;
}


bool CGlobalInfoDB::GetUserBlockList(std::vector<DWORD>* const list)
{
	CDatabaseStatement stmt(this);

	char szStr[256] = {};
	sprintf(szStr, "{ call usp_get_rt_blocklist"); //FIXME: missing closing brace(?)
	stmt.CDatabaseStatement::Query(szStr);

	int dwAid = 0;
	stmt.CDatabaseStatement::BindNumberColumn(1, &dwAid);

	while( SQL_SUCCEEDED(stmt.CDatabaseStatement::Fetch()) )
		list->push_back(dwAid);

	stmt.CDatabaseStatement::Release();
	return true;
}


void CGlobalInfoDB::DeleteBlockedUser(const int nAID)
{
	CDatabaseStatement stmt(this);

	stmt.CDatabaseStatement::Query("{ call usp_delete_rt_blocklist( %d ) } ", nAID);
	stmt.CDatabaseStatement::Fetch();
	stmt.CDatabaseStatement::Release();
}
