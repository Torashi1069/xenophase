#include "StorePasswordDB.h"
#include <sql.h>
#include <sqlext.h>


CStorePasswordDB::CStorePasswordDB() // line 15-17
{
}


CStorePasswordDB::~CStorePasswordDB() // line 20-22
{
}


int CStorePasswordDB::GetStorePassword(int aid, _STORE_PASSWORD_INFO& info) // line 59-92
{
	int result = -1;

	CDBStatement st;
	if( !st.CDBStatement::Init(m_hdbc) )
		return -1;

	SQLINTEGER cbAID = 0;
	SQLBindParameter(st, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &aid, 0, &cbAID);
	m_retcode = SQLExecDirectA(st, (SQLCHAR*)"{call GetStorePassword(?)}", SQL_NTS);

	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, st);
		SQLCloseCursor(st);
		return -1;
	}

	SQLBindCol(st, 1, SQL_C_SLONG, &info.Password, 0, &cbAID);
	SQLBindCol(st, 2, SQL_C_SLONG, &info.ErrorCount, 0, &cbAID);
	SQLBindCol(st, 3, SQL_C_SLONG, &info.PanaltyTime, 0, &cbAID);
	m_retcode = SQLFetch(st);
	if( SQL_SUCCEEDED(m_retcode) )
	{
		result = 0;
	}
	else
	if( m_retcode == SQL_NO_DATA )
	{
		this->CStorePasswordDB::InsertStorePassword(aid);
		info._STORE_PASSWORD_INFO::Init();
		info.Password = -1;
		info.PanaltyTime = 0;
		info.ErrorCount = 0;

		result = 0;
	}
	else
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, st);
	}

	SQLCloseCursor(st);
	return result;
}


int CStorePasswordDB::InsertStorePassword(int aid) // line 97-113
{
	int result = -1;

	CDBStatement st;
	if( !st.CDBStatement::Init(m_hdbc) )
		return -1;

	SQLINTEGER cbAID = 0;
	SQLBindParameter(st, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &aid, 0, &cbAID);
	m_retcode = SQLExecDirectA(st, (SQLCHAR*)"{call InsertStorePassword(?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
		DBTrace(__FILE__, __LINE__, 3, st);
	else
		result = 1;

	SQLCloseCursor(st);
	return result;
}


int CStorePasswordDB::UpdateStorePassword(int aid, _STORE_PASSWORD_INFO& info) // line 123-150
{
	int result = -1;

	CDBStatement st;
	if( !st.CDBStatement::Init(m_hdbc) )
		return -1;

	SQLINTEGER cbInt = 0;
	SQLBindParameter(st, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &aid, 0, &cbInt);
	SQLBindParameter(st, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &info.Password, 0, &cbInt);
	SQLBindParameter(st, 3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &info.ErrorCount, 0, &cbInt);
	SQLBindParameter(st, 4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &info.PanaltyTime, 0, &cbInt);
	m_retcode = SQLExecDirectA(st, (SQLCHAR*)"{call UpdateStorePassword(?,?,?,?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, st);
	else
		result = 0;

	SQLCloseCursor(st);
	return result;
}


int CStorePasswordDB::GetCashPassword(int aid, _CASHSHOP_PASSWORD_INFO& info) // line 157-190
{
	int result = -1;

	CDBStatement st;
	if( !st.CDBStatement::Init(m_hdbc) )
		return -1;

	SQLINTEGER cbAID = 0;
	SQLBindParameter(st, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &aid, 0, &cbAID);
	m_retcode = SQLExecDirectA(st, (SQLCHAR*)"{call GetCashPassword(?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, st);
		SQLCloseCursor(st);
		return -1;
	}

	SQLBindCol(st, 1, SQL_C_SLONG, &info.Password, 0, &cbAID);
	SQLBindCol(st, 2, SQL_C_SLONG, &info.ErrorCount, 0, &cbAID);
	SQLBindCol(st, 3, SQL_C_SLONG, &info.PanaltyTime, 0, &cbAID);
	m_retcode = SQLFetch(st);
	if( SQL_SUCCEEDED(m_retcode) )
	{
		result = 0;
	}
	else
	if( m_retcode == SQL_NO_DATA )
	{
		this->CStorePasswordDB::InsertCashPassword(aid);
		info._CASHSHOP_PASSWORD_INFO::Init();
		info.Password = -1;
		info.ErrorCount = 0;
		info.PanaltyTime = 0;

		result = 0;
	}
	else
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, st);
	}

	SQLCloseCursor(st);
	return result;
}


int CStorePasswordDB::InsertCashPassword(int aid) // line 195-211
{
	int result = -1;

	CDBStatement st;
	if( !st.CDBStatement::Init(m_hdbc) )
		return -1;

	SQLINTEGER cbAID = 0;
	SQLBindParameter(st, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &aid, 0, &cbAID);
	m_retcode = SQLExecDirectA(st, (SQLCHAR*)"{call InsertCashPassword(?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, st);
	else
		result = 1;

	SQLCloseCursor(st.m_hStmt);
	return result;
}


int CStorePasswordDB::UpdateCashPassword(int aid, _CASHSHOP_PASSWORD_INFO& info) // line 221-248
{
	int result = -1;

	CDBStatement st;
	if( !st.CDBStatement::Init(m_hdbc) )
		return -1;

	SQLINTEGER cbInt = 0;
	SQLBindParameter(st, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &aid, 0, &cbInt);
	SQLBindParameter(st, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &info.Password, 0, &cbInt);
	SQLBindParameter(st, 3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &info.ErrorCount, 0, &cbInt);
	SQLBindParameter(st, 4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &info.PanaltyTime, 0, &cbInt);
	m_retcode = SQLExecDirectA(st, (SQLCHAR*)"{call UpdateCashPassword(?,?,?,?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, st);
	else
		result = 0;

	SQLCloseCursor(st);
	return result;
}
