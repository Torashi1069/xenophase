#include "UserLogDB.h"


CUserLogDB::CUserLogDB()
{
}


CUserLogDB::~CUserLogDB()
{
}


BOOL CUserLogDB::InsertZoneUserLog(int SID, int DestSID, int UserNum)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLINTEGER cbInt = 0;
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &SID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &DestSID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &UserNum, 0, &cbInt);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call InsertZoneUserLog(?,?,?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return TRUE;
}


BOOL CUserLogDB::InsertInterUserLog(int SID, int UserNum)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLINTEGER cbInt = 0;
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &SID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &UserNum, 0, &cbInt);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call InsertInterUserLog(?,?)}", SQL_NTS);

	if( !SQL_SUCCEEDED(m_retcode) )
	{
		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return TRUE;
}
