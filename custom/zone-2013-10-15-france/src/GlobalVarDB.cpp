#include "GlobalVarDB.h"


CGlobalVarDB::CGlobalVarDB()
{
}


CGlobalVarDB::~CGlobalVarDB()
{
}


int CGlobalVarDB::CreateGlobalVar(const char* name, int value)
{
	if( name == NULL )
		return -1;

	CDBStatement st;
	if( !st.CDBStatement::Init(m_hdbc) )
		return -1;

	SQLINTEGER cbChar = SQL_NTS;
	SQLINTEGER cbInt;

	SQLBindParameter(st, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 24, 0, const_cast<char*>(name), 0, &cbChar);
	SQLBindParameter(st, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &value, 0, &cbInt);

	m_retcode = SQLExecDirect(st, (SQLCHAR*)"{call InsertGlobalVar(?, ?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, st);
		return -1;
	}

	return 1;
}


int CGlobalVarDB::GetGlobalVar(const char* name, int& value)
{
	if( name == NULL )
		return -1;

	CDBStatement st;
	if( !st.CDBStatement::Init(m_hdbc) )
		return -1;

	SQLINTEGER cbChar = SQL_NTS;
	SQLINTEGER cbInt;
	int ret = -1;
	value = 0;

	SQLBindParameter(st, 1, SQL_PARAM_OUTPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &ret, 0, &cbInt);
	SQLBindParameter(st, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 24, 0, const_cast<char*>(name), 0, &cbChar);
	SQLBindParameter(st, 3, SQL_PARAM_OUTPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &value, 0, &cbInt);

	m_retcode = SQLExecDirect(st, (SQLCHAR*)"{?=call GetGlobalVar(?,?)}", SQL_NTS);
	if( SQL_SUCCEEDED(m_retcode) )
	{
		while( 1 )
		{
			m_retcode = SQLMoreResults(st);

			if( m_retcode == SQL_NO_DATA )
			{
				SQLCloseCursor(st);

				if( ret == 1 )
					return 1;

				if( ret == 0 )
					return 0;

				break;
			}

			if( m_retcode == SQL_ERROR )
				break;
		}
	}

	DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, st);
	return -1;
}


int CGlobalVarDB::SetGlobalVar(const char* name, int value)
{
	if( name == NULL )
		return -1;

	CDBStatement st;
	if( !st.CDBStatement::Init(m_hdbc) )
		return -1;

	SQLINTEGER cbChar = SQL_NTS;
	SQLINTEGER cbInt;
	int ret = -1;

	SQLBindParameter(st, 1, SQL_PARAM_OUTPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &ret, 0, &cbInt);
	SQLBindParameter(st, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 24, 0, const_cast<char*>(name), 0, &cbChar);
	SQLBindParameter(st, 3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &value, 0, &cbInt);

	m_retcode = SQLExecDirect(st, (SQLCHAR*)"{?=call UpdateGlobalVar(?, ?)}", SQL_NTS);
	if( SQL_SUCCEEDED(m_retcode) )
	{
		while( 1 )
		{
			m_retcode = SQLMoreResults(st);

			if( m_retcode == SQL_NO_DATA )
			{
				SQLCloseCursor(st);

				if( ret == 1 )
					return 1;

				if( ret == 0 )
					return 0;

				break;
			}

			if( m_retcode == SQL_ERROR )
				break;
		}
	}

	DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, st);
	return -1;
}


bool CGlobalVarDB::CreateGlobalStr(const char* name, char* value) // 130-155
{
	if( name == NULL || value == NULL )
		return false;

	CDBStatement st;
	if( !st.CDBStatement::Init(m_hdbc) )
		return 0;

	SQLINTEGER cbChar = SQL_NTS;
	bool ret = false;

	SQLBindParameter(st, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 24, 0, const_cast<char*>(name), SQL_NTS, &cbChar);
	SQLBindParameter(st, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 24, 0, value, 0, &cbChar);

	m_retcode = SQLExecDirect(st, (SQLCHAR*)"{call InsertGlobalStr(?, ?)}", SQL_NTS);
	if( SQL_SUCCEEDED(m_retcode) )
		ret = true;
	else
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, st);

	SQLCloseCursor(st);
	return ret;
}


bool CGlobalVarDB::GetGlobalStr(const char* name, char* value) // 160-186
{
	if( name == NULL )
		return false;

	CDBStatement st;
	if( !st.CDBStatement::Init(m_hdbc) )
		return false;

	SQLINTEGER cbChar = SQL_NTS;
	bool ret = false;

	char szQuery[1024+1] = {};
	sprintf(szQuery, "{call GetGlobalStr ('%s')}", name);
	m_retcode = SQLExecDirect(st, (SQLCHAR*)szQuery, SQL_NTS);

	SQLBindCol(st, 1, SQL_PARAM_INPUT, value, 24, &cbChar);

	if( SQL_SUCCEEDED(m_retcode) )
	{
		m_retcode = SQLFetch(st);
		if( m_retcode != SQL_ERROR && m_retcode != SQL_NO_DATA )
			ret = true;
	}
	else
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, st);
	}

	SQLCloseCursor(m_hstmt);
	return ret;
}


bool CGlobalVarDB::SetGlobalStr(const char* name, char* value) // 192-223
{
	if( name == NULL || value == NULL )
		return false;

	CDBStatement st;
	if( !st.CDBStatement::Init(m_hdbc) )
		return false;

	SQLINTEGER cbChar = SQL_NTS;
	bool ret = false;

	SQLBindParameter(st, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 24, 0, const_cast<char*>(name), SQL_NTS, &cbChar);
	SQLBindParameter(st, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 24, 0, value, 0, &cbChar);

	m_retcode = SQLExecDirect(st, (SQLCHAR*)"{call UpdateGlobalStr(?, ?)}", SQL_NTS);
	if( SQL_SUCCEEDED(m_retcode) )
	{
		while( 1 )
		{
			m_retcode = SQLMoreResults(st);

			if( m_retcode == SQL_NO_DATA )
			{
				ret = true;
				break;
			}

			if( m_retcode == SQL_ERROR )
				break;
		}
	}
	else
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, st);
	}

	SQLCloseCursor(st);
	return ret;
}


int CGlobalVarDB::IncGlobalVar(const char* in_Name, int in_nValue) // 227-260
{
	if( in_Name == NULL || in_nValue <= 0 )
		return -1;

	CDBStatement st;
	if( !st.CDBStatement::Init(m_hdbc) )
		return -1;

	SQLINTEGER cbChar = SQL_NTS;
	SQLINTEGER cbInt;
	int ret = -1;

	SQLBindParameter(st, 1, SQL_PARAM_OUTPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &ret, 0, &cbInt);
	SQLBindParameter(st, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 24, 0, const_cast<char*>(in_Name), 0, &cbChar);
	SQLBindParameter(st, 3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &in_nValue, 0, &cbInt);

	m_retcode = SQLExecDirect(st, (SQLCHAR*)"{ ? = call IncGlobalVar(?, ?) }", SQL_NTS);
	if( SQL_SUCCEEDED(m_retcode) )
	{
		while( 1 )
		{
			m_retcode = SQLMoreResults(st);

			if( m_retcode == SQL_NO_DATA )
			{
				SQLCloseCursor(st);

				if( ret == 1 )
					return true;

				if( ret == 0 )
					return false;

				break;
			}

			if( m_retcode == SQL_ERROR )
				break;
		}
	}

	DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, st);
	return -1;
}


int CGlobalVarDB::DecGlobalVar(const char* in_Name, int in_nValue) // 265-298
{
	if ( !in_Name || in_nValue <= 0 )
		return -1;

	CDBStatement st;
	if( !st.CDBStatement::Init(m_hdbc) )
		return -1;

	SQLINTEGER cbChar = SQL_NTS;
	SQLINTEGER cbInt;
	int ret = -1;

	SQLBindParameter(st, 1, SQL_PARAM_OUTPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &ret, 0, &cbInt);
	SQLBindParameter(st, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 24, 0, const_cast<char*>(in_Name), 0, &cbChar);
	SQLBindParameter(st, 3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &in_nValue, 0, &cbInt);

	m_retcode = SQLExecDirect(st, (SQLCHAR*)"{ ? = call DecGlobalVar(?, ?) }", SQL_NTS);
	if( SQL_SUCCEEDED(m_retcode) )
	{
		while( 1 )
		{
			m_retcode = SQLMoreResults(st);

			if( m_retcode == SQL_NO_DATA )
			{
				SQLCloseCursor(st);

				if( ret == 1 )
					return true;

				if( ret == 0 )
					return false;

				break;
			}

			if( m_retcode == SQL_ERROR )
				break;
		}
	}

	DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, st);
	return -1;
}
