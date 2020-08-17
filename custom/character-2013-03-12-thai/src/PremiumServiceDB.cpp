#include "PremiumServiceDB.h"
#include "Common/DatabaseStatement.h"
#include "Common/EnterTraceLog.h"
#include "Common/Network.h"
#include "Common/NODBCHandler.h"
#include "Common/SyncObject.h"
#include <sqlext.h>


/// singleton instance
static CPremiumServiceDB gPCBangBonusDB;
CPremiumServiceDB* CSingleton<CPremiumServiceDB>::ms_Singleton;


CPremiumServiceDB::CPremiumServiceDB()
{
}


CPremiumServiceDB::~CPremiumServiceDB()
{
}


int CPremiumServiceDB::ReloadPCBangIPList()
{
	int nCount = 0;
	m_csPremiumServiceDB.Enter();

	int nNewPos = ( m_nCurrPos == 0 ) ? 1 : 0;

	for( int i = 0; i < 10; ++i )
		m_listPCBangIPList[nNewPos][i].clear();

	char szIP[36] = {};
	bool bReadDefault = false;

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("Select IP from dbo.PcPremiumServiceListDB");
	stmt.CDatabaseStatement::BindStringColumn(1, szIP, sizeof(szIP)-1);

	FILE* fp = fopen("PCBangList.txt", "wt");

	if( fp != NULL )
	{
		SYSTEMTIME st;
		GetLocalTime(&st);
		fprintf(fp, "reload %d-%d-%d %d:%d:%d\n(Common Exp1:%.3f\tExp2:%.3f\tDrop:%.3f)\n\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, m_defaultExp.fExp1, m_defaultExp.fExp2, m_defaultExp.fdrp);
	}

	while( SQL_SUCCEEDED(stmt.CDatabaseStatement::Fetch()) )
	{
		if( fp != NULL )
			fprintf(fp, "%d:\t%s\n", nCount, szIP);

		if( !bReadDefault && stricmp("default", szIP) == 0 )
		{
			bReadDefault = true;
		}
		else
		{
			DWORD dwIP = CNetwork::GetObj()->CNetwork::GetDWORDIP(szIP);
			m_listPCBangIPList[nNewPos][dwIP % 10].push_back(dwIP);
			++nCount;

			memset(szIP, '\0', sizeof(szIP));
		}
	}

	if( fp != NULL )
		fclose(fp);

	m_nCurrPos = nNewPos;

	m_csPremiumServiceDB.Leave();
	return nCount;
}


bool CPremiumServiceDB::Get(DWORD dwIP)
{
	bool bFound = false;
	m_csPremiumServiceDB.Enter();

	std::list<DWORD>& list = m_listPCBangIPList[m_nCurrPos][dwIP % 10];
	for( std::list<DWORD>::const_iterator it = list.begin(); it != list.end(); ++it )
	{
		if( *it == dwIP )
		{
			bFound = true;
			break;
		}
	}

	m_csPremiumServiceDB.Leave();
	return bFound;
}


std::pair<bool,std::string> CPremiumServiceDB::InitIPBonusList()
{
	SyncObject sync(m_csPremiumServiceDB);

	NODBCHandler handler(this);
	if( !SQL_SUCCEEDED(handler.NODBCHandler::ExecDirect("{ call usp_getpcbonuslist }")) )
	{
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s", handler.NODBCHandler::GetErrorString().c_str());
		return std::pair<bool,std::string>(false, "call sp(usp_getpcbonuslist) failed");
	}

	while( 1 )
	{
		char szIP[16];
		float fExp = 0.0f;
		float fDeath = 0.0f;
		float fDrp = 0.0f;
		int nLimitNum = 0;
		int nAcafe_ID = 0;
		SQLINTEGER nIPLen = SQL_NTS;
		SQLINTEGER cbInt = 0;
		handler.NODBCHandler::BindCol(1, SQL_C_CHAR, szIP, sizeof(szIP), &nIPLen);
		handler.NODBCHandler::BindCol(2, SQL_C_FLOAT, &fExp, 0, &cbInt);
		handler.NODBCHandler::BindCol(3, SQL_C_FLOAT, &fDeath, 0, &cbInt);
		handler.NODBCHandler::BindCol(4, SQL_C_FLOAT, &fDrp, 0, &cbInt);
		handler.NODBCHandler::BindCol(5, SQL_C_LONG, &nLimitNum, 0, &cbInt);
		handler.NODBCHandler::BindCol(6, SQL_C_LONG, &nAcafe_ID, 0, &cbInt);

		SQLRETURN sqlRet = handler.NODBCHandler::Fetch();
		if( sqlRet == SQL_NO_DATA )
		{// done.
			return std::pair<bool,std::string>(true, "good");
		}

		if( !SQL_SUCCEEDED(sqlRet) )
		{
			CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s", handler.NODBCHandler::GetErrorString().c_str());
			return std::pair<bool,std::string>(false, handler.NODBCHandler::GetErrorString().c_str());
		}

		if( stricmp(szIP, "default") != 0 )
		{
			DWORD dwIP = CNetwork::GetObj()->CNetwork::GetDWORDIP(szIP);
			sExtraExp exp(nAcafe_ID, fExp, fDeath, fDrp, nLimitNum);
			m_mapIPBonusList.insert(std::pair<DWORD,sExtraExp>(dwIP, exp));
			CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "IP Bonus Init : Acafe_ID[%d], IP[%s], Exp[%0.2f], Death[%0.2f], Drp[%0.2f], LimitNum[%d]", nAcafe_ID, szIP, fExp, fDeath, fDrp, nLimitNum);
		}
		else
		{
			m_fDefaultExp = fExp;
			m_fDefaultDeath = fDeath;
			m_fDeafultDrp = fDrp;
			m_nLimitNum = nLimitNum;
			m_nAcafeID = nAcafe_ID;
		}
	}
}


bool CPremiumServiceDB::ReloadIPBonusList()
{
	SyncObject sync(m_csPremiumServiceDB);

	NODBCHandler handler(this); // unused
	m_mapIPBonusList.clear();

	std::pair<bool,std::string> ipbonusRet = this->CPremiumServiceDB::InitIPBonusList();
	if( !ipbonusRet.first )
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, ipbonusRet.second.c_str());

	return true;
}


std::tr1::tuple<bool,float,float,float,int> CPremiumServiceDB::GetExp(const DWORD in_dwAID, const DWORD in_dwIP)
{
	SyncObject sync(m_csPremiumServiceDB);

	std::map<DWORD,sExtraExp>::const_iterator it_IPBonus = m_mapIPBonusList.find(in_dwIP);
	if( it_IPBonus == m_mapIPBonusList.end() )
		return std::tr1::tuple<bool,float,float,float,int>(false, 0.0f, 0.0f, 0.0f, 0);

	int nCount = 0;
	for( std::list<sCurIPBonusUser>::const_iterator i = m_listCurIPBonusUser.begin(); i != m_listCurIPBonusUser.end(); ++i )
		if( i->dwIP == in_dwIP )
			++nCount;

	if( nCount >= it_IPBonus->second.nLimitNum )
		return std::tr1::tuple<bool,float,float,float,int>(false, 0.0f, 0.0f, 0.0f, 0);

	m_listCurIPBonusUser.push_back(sCurIPBonusUser(it_IPBonus->second.nAcafe_ID, in_dwAID, in_dwIP));
	return std::tr1::tuple<bool,float,float,float,int>(false, it_IPBonus->second.fExp, it_IPBonus->second.fDeath, it_IPBonus->second.fDrp, it_IPBonus->second.nLimitNum - nCount);
}


std::tr1::tuple<bool,int,int> CPremiumServiceDB::DeleteUserPcbonusEFSTList(const DWORD in_dwAID, const DWORD in_dwIP)
{
	SyncObject sync(m_csPremiumServiceDB);

	int nCount = 0;
	for( std::list<sCurIPBonusUser>::iterator i = m_listCurIPBonusUser.begin(); i != m_listCurIPBonusUser.end(); ++i )
	{
		if( i->dwAID == in_dwAID )
		{
			m_listCurIPBonusUser.erase(i);

			for( std::list<sCurIPBonusUser>::iterator j = m_listCurIPBonusUser.begin(); j != m_listCurIPBonusUser.end(); ++j )
			{
				if( in_dwIP == j->dwIP )
					++nCount;
			}

			break;
		}
	}

	std::map<DWORD,sExtraExp>::const_iterator it_IPBonus = m_mapIPBonusList.find(in_dwIP);
	if( it_IPBonus == m_mapIPBonusList.end() )
		return std::tr1::tuple<bool,int,int>(false, 0, 0);

	return std::tr1::tuple<bool,int,int>(true, nCount, it_IPBonus->second.nLimitNum);
}


bool CPremiumServiceDB::InitPCBonusInit()
{
	NODBCHandler handler(this);

	if( !SQL_SUCCEEDED(handler.NODBCHandler::ExecDirect("{ call usp_init_pcbonus_db }")) )
	{
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s", handler.NODBCHandler::GetErrorString().c_str());
		return false;
	}

	return true;
}


bool CPremiumServiceDB::DeletePCBonusLog(const DWORD in_dwAID)
{
	SyncObject sync(m_csPremiumServiceDB);

	NODBCHandler handler(this);

	SQLINTEGER cbInt = 0;
	handler.NODBCHandler::BindParameter(1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, const_cast<DWORD*>(&in_dwAID), 0, &cbInt);

	SQLRETURN sqlRet = handler.NODBCHandler::ExecDirect("{ call usp_deletepcbonuslog( ? ) }");
	if( !SQL_SUCCEEDED(sqlRet) )
	{
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s", handler.NODBCHandler::GetErrorString().c_str());
		return false;
	}

	return true;
}


std::tr1::tuple<bool,float,float,float> CPremiumServiceDB::GetPremiumIPBonus(const DWORD in_dwAID)
{
	SyncObject sync(m_csPremiumServiceDB);

	NODBCHandler handler(this);

	SQLINTEGER cbInt = 0;
	handler.NODBCHandler::BindParameter(1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, const_cast<DWORD*>(&in_dwAID), 0, &cbInt);

	SQLRETURN sqlRet = handler.NODBCHandler::ExecDirect("{ call GetPremiumExp( ? ) }");
	if( !SQL_SUCCEEDED(sqlRet) )
	{
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s", handler.NODBCHandler::GetErrorString().c_str());
		return std::tr1::tuple<bool,float,float,float>(false, 0.0f, 0.0f, 0.0f);
	}

	float fExp1 = 0.0f;
	float fExp2 = 0.0f;
	float fDrp = 0.0f;
	handler.NODBCHandler::BindCol(1, SQL_C_FLOAT, &fExp1, 0, &cbInt);
	handler.NODBCHandler::BindCol(2, SQL_C_FLOAT, &fExp2, 0, &cbInt);
	handler.NODBCHandler::BindCol(3, SQL_C_FLOAT, &fDrp, 0, &cbInt);

	SQLRETURN sqlRet2 = handler.NODBCHandler::Fetch();
	if( !SQL_SUCCEEDED(sqlRet2) )
	{
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s", handler.NODBCHandler::GetErrorString().c_str());
		return std::tr1::tuple<bool,float,float,float>(false, 0.0f, 0.0f, 0.0f);
	}

	if( sqlRet == SQL_NO_DATA )
		return std::tr1::tuple<bool,float,float,float>(true, 0.0f, 0.0f, 0.0f);

	return std::tr1::tuple<bool,float,float,float>(true, fExp1, fExp2, fDrp);
}
