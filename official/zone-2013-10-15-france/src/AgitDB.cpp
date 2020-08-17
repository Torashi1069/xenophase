#include "AgitDB.h"


CAgitDB::CAgitDB()
{
}


CAgitDB::~CAgitDB()
{
}


int CAgitDB::Update(const char* mapName, AGIT_DBINFO* pInfo)
{
	CDBStatement st;
	if( !st.CDBStatement::Init(m_hdbc) )
		return -1;

	SQLINTEGER cbInt = 0;
	SQLINTEGER cbChar = SQL_NTS;

	SQLBindParameter(st,  1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 16, 0, (SQLPOINTER)mapName, 0, &cbChar);
	SQLBindParameter(st,  2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &pInfo->guildID, 0, &cbInt);
	SQLBindParameter(st,  3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &pInfo->economy, 0, &cbInt);
	SQLBindParameter(st,  4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &pInfo->defense, 0, &cbInt);
	SQLBindParameter(st,  5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &pInfo->triggerE, 0, &cbInt);
	SQLBindParameter(st,  6, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &pInfo->triggerD, 0, &cbInt);
	SQLBindParameter(st,  7, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &pInfo->nextTime, 0, &cbInt);
	SQLBindParameter(st,  8, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &pInfo->payTime, 0, &cbInt);
	SQLBindParameter(st,  9, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &pInfo->createTime, 0, &cbInt);
	SQLBindParameter(st, 10, SQL_PARAM_INPUT, SQL_C_UTINYINT, SQL_INTEGER, 0, 0, &pInfo->visibleC, 0, &cbInt);
	SQLBindParameter(st, 11, SQL_PARAM_INPUT, SQL_C_UTINYINT, SQL_INTEGER, 0, 0, &pInfo->visibleG[0], 0, &cbInt);
	SQLBindParameter(st, 12, SQL_PARAM_INPUT, SQL_C_UTINYINT, SQL_INTEGER, 0, 0, &pInfo->visibleG[1], 0, &cbInt);
	SQLBindParameter(st, 13, SQL_PARAM_INPUT, SQL_C_UTINYINT, SQL_INTEGER, 0, 0, &pInfo->visibleG[2], 0, &cbInt);
	SQLBindParameter(st, 14, SQL_PARAM_INPUT, SQL_C_UTINYINT, SQL_INTEGER, 0, 0, &pInfo->visibleG[3], 0, &cbInt);
	SQLBindParameter(st, 15, SQL_PARAM_INPUT, SQL_C_UTINYINT, SQL_INTEGER, 0, 0, &pInfo->visibleG[4], 0, &cbInt);
	SQLBindParameter(st, 16, SQL_PARAM_INPUT, SQL_C_UTINYINT, SQL_INTEGER, 0, 0, &pInfo->visibleG[5], 0, &cbInt);
	SQLBindParameter(st, 17, SQL_PARAM_INPUT, SQL_C_UTINYINT, SQL_INTEGER, 0, 0, &pInfo->visibleG[6], 0, &cbInt);
	SQLBindParameter(st, 18, SQL_PARAM_INPUT, SQL_C_UTINYINT, SQL_INTEGER, 0, 0, &pInfo->visibleG[7], 0, &cbInt);

	m_retcode = SQLExecDirectA(st, (SQLCHAR*)"{call UpdateAgit(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, st);
		return -1;
	}

	SQLCloseCursor(st);
	return 1;
}


int CAgitDB::Get(std::vector<AGIT_DBINFO*>& vt)
{
	CDBStatement st;
	if( !st.CDBStatement::Init(m_hdbc) )
		return -1;

	m_retcode = SQLExecDirectA(st, (SQLCHAR*)"{call GetAgit2}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, st);
		return -1;
	}

	SQLINTEGER cbInt = 0;
	SQLINTEGER cbChar = SQL_NTS;

	AGIT_DBINFO info;
	SQLBindCol(st,  1, SQL_C_CHAR, &info.mapName, 16, &cbChar);
	SQLBindCol(st,  2, SQL_C_CHAR, info.agitName, 24, &cbChar);
	SQLBindCol(st,  3, SQL_C_SLONG, &info.guildID, 0, &cbInt);
	SQLBindCol(st,  4, SQL_C_SLONG, &info.economy, 0, &cbInt);
	SQLBindCol(st,  5, SQL_C_SLONG, &info.defense, 0, &cbInt);
	SQLBindCol(st,  6, SQL_C_SLONG, &info.triggerE, 0, &cbInt);
	SQLBindCol(st,  7, SQL_C_SLONG, &info.triggerD, 0, &cbInt);
	SQLBindCol(st,  8, SQL_C_SLONG, &info.nextTime, 0, &cbInt);
	SQLBindCol(st,  9, SQL_C_SLONG, &info.payTime, 0, &cbInt);
	SQLBindCol(st, 10, SQL_C_SLONG, &info.createTime, 0, &cbInt);
	SQLBindCol(st, 11, SQL_C_UTINYINT, &info.visibleC, 0, &cbInt);
	for( int i = 12; i < 20; ++i )
		SQLBindCol(st, i, SQL_C_UTINYINT, &info.visibleG[i], 0, &cbInt);

	while( 1 )
	{
		m_retcode = SQLFetch(st);
		if( !SQL_SUCCEEDED(m_retcode) )
			break;

		AGIT_DBINFO* p = new AGIT_DBINFO;
		memcpy_s(p, sizeof(*p), &info, sizeof(info));
		vt.push_back(p);
	}

	if( m_retcode != SQL_NO_DATA )
	{
		vt.clear();

		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, st);
		return -1;
	}

	SQLCloseCursor(st);
	return 1;
}
