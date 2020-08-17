#include "MakerRankDB.h"


int CMakerRankDB::UpdateMakerRank(unsigned long GID, char* charname, int type, int point)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return -1;
	}

	SQLINTEGER cbChar = SQL_NTS;
	SQLINTEGER cbInt = 0;
	char name[24];

	memcpy_s(name, sizeof(name), charname, 24);
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, sizeof(name), 0, name, 0, &cbChar);
	SQLBindParameter(m_hstmt, 3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &type, 0, &cbInt);
	SQLBindParameter(m_hstmt, 4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &point, 0, &cbInt);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call UpdateMakerRank(?,?,?,?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return -1;
	}

	SQLCloseCursor(m_hstmt);

	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return 1;
}


int CMakerRankDB::Get_TOP_MakerRank(int type, MAKER_RANKING* makerRank)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return -1;
	}

	SQLINTEGER cbChar = SQL_NTS;
	SQLINTEGER cbInt = 0;
	int gid;
	char charname[24];
	int mtype;
	int point;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &type, 0, &cbInt);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetTopMakerRank(?)}", SQL_NTS);

	SQLBindCol(m_hstmt, 1, SQL_C_SLONG, &gid, 0, &cbInt);
	SQLBindCol(m_hstmt, 2, SQL_C_CHAR, charname, 24, &cbChar);
	SQLBindCol(m_hstmt, 3, SQL_C_SLONG, &mtype, 0, &cbInt);
	SQLBindCol(m_hstmt, 4, SQL_C_SLONG, &point, 0, &cbInt);

	MAKER_RANKING* out_p = makerRank;
	for( ; ; )
	{
		m_retcode = SQLFetch(m_hstmt);
		if( m_retcode != SQL_SUCCESS )
			break;

		out_p->GID = gid;
		memcpy(out_p->charname, charname, 24);
		out_p->point = point;
	}

	if( m_retcode != SQL_SUCCESS && m_retcode != SQL_SUCCESS_WITH_INFO && m_retcode != SQL_NO_DATA )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return -1;
	}

	SQLCloseCursor(m_hstmt);

	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return 1;
}


int CMakerRankDB::GetMakerRank(unsigned long GID, int& point, int Type)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return -1;
	}

	SQLINTEGER cbInt = 0;
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Type, 0, &cbInt);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetMakerRank(?,?)}", SQL_NTS);

	SQLBindCol(m_hstmt, 1, SQL_C_SLONG, &point, 0, &cbInt);

	if( m_retcode != SQL_SUCCESS && m_retcode != SQL_SUCCESS_WITH_INFO && m_retcode != SQL_NO_DATA )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return -1;
	}

	SQLINTEGER retCode = SQLFetch(m_hstmt);
	m_retcode = retCode == SQL_NO_DATA;
	if( retCode == SQL_NO_DATA )
		point = 0;

	SQLCloseCursor(m_hstmt);

	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return 1;
}
