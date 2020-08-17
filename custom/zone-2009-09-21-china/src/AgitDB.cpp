#include "AgitDB.h"


CAgitDB::CAgitDB(void) // line 47
{
}


CAgitDB::~CAgitDB(void) // line 51
{
}


hook_method<int (CAgitDB::*)(const char* mapName, AGIT_DBINFO* pInfo)> CAgitDB::_Update(SERVER, "CAgitDB::Update");
int CAgitDB::Update(const char* mapName, AGIT_DBINFO* pInfo) // line 56
{
	return (this->*_Update)(mapName, pInfo);
/*
	CDBStatement st;
	st.m_hStmt = 0;
	if( !st.CDBStatement::Init(m_hdbc) )
		return -1;

	int cbInt = 0;
	int cbChar = SQL_NTS;
	SQLBindParameter(st.m_hStmt,  1, 1, 1, 12, 16, 0, (SQLPOINTER)mapName, 0, &cbChar);
	SQLBindParameter(st.m_hStmt,  2, 1, -16, 4, 0, 0, &pInfo->guildID, 0, &cbInt);
	SQLBindParameter(st.m_hStmt,  3, 1, -16, 4, 0, 0, &pInfo->economy, 0, &cbInt);
	SQLBindParameter(st.m_hStmt,  4, 1, -16, 4, 0, 0, &pInfo->defense, 0, &cbInt);
	SQLBindParameter(st.m_hStmt,  5, 1, -16, 4, 0, 0, &pInfo->triggerE, 0, &cbInt);
	SQLBindParameter(st.m_hStmt,  6, 1, -16, 4, 0, 0, &pInfo->triggerD, 0, &cbInt);
	SQLBindParameter(st.m_hStmt,  7, 1, -16, 4, 0, 0, &pInfo->nextTime, 0, &cbInt);
	SQLBindParameter(st.m_hStmt,  8, 1, -16, 4, 0, 0, &pInfo->payTime, 0, &cbInt);
	SQLBindParameter(st.m_hStmt,  9, 1, -16, 4, 0, 0, &pInfo->createTime, 0, &cbInt);
	SQLBindParameter(st.m_hStmt, 10, 1, -28, 4, 0, 0, &pInfo->visibleC, 0, &cbInt);
	SQLBindParameter(st.m_hStmt, 11, 1, -28, 4, 0, 0, &pInfo->visibleG[0], 0, &cbInt);
	SQLBindParameter(st.m_hStmt, 12, 1, -28, 4, 0, 0, &pInfo->visibleG[1], 0, &cbInt);
	SQLBindParameter(st.m_hStmt, 13, 1, -28, 4, 0, 0, &pInfo->visibleG[2], 0, &cbInt);
	SQLBindParameter(st.m_hStmt, 14, 1, -28, 4, 0, 0, &pInfo->visibleG[3], 0, &cbInt);
	SQLBindParameter(st.m_hStmt, 15, 1, -28, 4, 0, 0, &pInfo->visibleG[4], 0, &cbInt);
	SQLBindParameter(st.m_hStmt, 16, 1, -28, 4, 0, 0, &pInfo->visibleG[5], 0, &cbInt);
	SQLBindParameter(st.m_hStmt, 17, 1, -28, 4, 0, 0, &pInfo->visibleG[6], 0, &cbInt);
	SQLBindParameter(st.m_hStmt, 18, 1, -28, 4, 0, 0, &pInfo->visibleG[7], 0, &cbInt);

	m_retcode = SQLExecDirect(st.m_hStmt, "{call UpdateAgit(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)}", SQL_NTS);
	if( m_retcode != 0 && m_retcode != 1 )
	{
		DBTrace(".\\AgitDB.cpp", 92, 3, st.m_hStmt);
		return -1;
	}

	SQLCloseCursor(st.m_hStmt);
	return 1;
*/
}


hook_method<int (CAgitDB::*)(mystd::vector<AGIT_DBINFO *>& vt)> CAgitDB::_Get(SERVER, "CAgitDB::Get");
int CAgitDB::Get(mystd::vector<AGIT_DBINFO *>& vt) // line 102
{
	return (this->*_Get)(vt);

	//TODO
}
