#include "CMakerRankDB.h"


CMakerRankDB::CMakerRankDB()
{
}


CMakerRankDB::~CMakerRankDB()
{
}


int CMakerRankDB::Get_TOP_MakerRank(int type, MAKER_RANKING* makerRank)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != NULL )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return -1;
	}

	SQLINTEGER cbChar = SQL_NTS;
	SQLINTEGER cbInt = 0;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &type, 0, &cbInt);
	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetTopMakerRank(?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		char szState[1024] = {};
		char Buf[1024];
		SQLErrorA(m_henv, m_hdbc, m_hstmt, (SQLCHAR*)szState, NULL, (SQLCHAR*)Buf, sizeof(Buf), NULL);

		if( m_hstmt != NULL )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return -1;
	}

	int gid;
	char charname[24];
	int mtype;
	int point;
	SQLBindCol(m_hstmt, 1, SQL_C_SLONG, &gid, 0, &cbInt);
	SQLBindCol(m_hstmt, 2, SQL_C_CHAR, charname, sizeof(charname), &cbChar);
	SQLBindCol(m_hstmt, 3, SQL_C_SLONG, &mtype, 0, &cbInt);
	SQLBindCol(m_hstmt, 4, SQL_C_SLONG, &point, 0, &cbInt);

	int rank = 0;
	while( 1 )
	{
		m_retcode = SQLFetch(m_hstmt);
		if( m_retcode != SQL_SUCCESS )
			break;

		if( rank == 12-1 )
			break;

		makerRank[rank].GID = gid;
		memcpy(makerRank[rank].charname, charname, sizeof(makerRank[rank].charname));
		makerRank[rank].point = point;

		++rank;
	}

	if( m_retcode != SQL_SUCCESS && m_retcode != SQL_SUCCESS_WITH_INFO && m_retcode != SQL_NO_DATA )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		char szState[1024] = {};
		char Buf[1024];
		SQLErrorA(m_henv, m_hdbc, m_hstmt, (SQLCHAR*)szState, NULL, (SQLCHAR*)Buf, sizeof(Buf), NULL);

		if( m_hstmt != NULL )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return -1;
	}

	SQLCloseCursor(m_hstmt);

	if( m_hstmt != NULL )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return 1;
}
