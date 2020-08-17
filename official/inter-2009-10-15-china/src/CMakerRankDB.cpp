#include "CMakerRankDB.h"
#include "globals.hpp"
#include <sql.h>
#include <sqlext.h>


CMakerRankDB::CMakerRankDB(void) // line 13
{
}


CMakerRankDB::~CMakerRankDB(void) // line 18
{
}


hook_method<int (CMakerRankDB::*)(int type, MAKER_RANKING* makerRank)> CMakerRankDB::_Get_TOP_MakerRank(SERVER, "CMakerRankDB::Get_TOP_MakerRank");
int CMakerRankDB::Get_TOP_MakerRank(int type, MAKER_RANKING* makerRank) // line 23
{
	return (this->*_Get_TOP_MakerRank)(type, makerRank);

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
		DBTrace(".\\CMakerRankDB.cpp", 81, SQL_HANDLE_STMT, m_hstmt);

		char Buf[1024];
		this->CODBC::GetErrorString(m_hstmt, Buf);
		Trace("%s\n", Buf);

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

	for( int i = 0; i != 11 && (m_retcode = SQLFetch(m_hstmt)) == SQL_SUCCESS; ++i )
	{
		makerRank[i].GID = gid;
		memcpy(makerRank[i].charname, charname, sizeof(charname));
		makerRank[i].point = point;
	}

	if( m_retcode != SQL_SUCCESS && m_retcode != SQL_SUCCESS_WITH_INFO && m_retcode != SQL_NO_DATA )
	{
		DBTrace(".\\CMakerRankDB.cpp", 64, SQL_HANDLE_STMT, m_hstmt);

		char Buf[1024];
		this->CODBC::GetErrorString(m_hstmt, Buf);
		Trace("%s\n", Buf);

		if( m_hstmt != NULL )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
		return -1;
	}

	SQLCloseCursor(m_hstmt);

	if( m_hstmt != NULL )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
	return 1;
}
