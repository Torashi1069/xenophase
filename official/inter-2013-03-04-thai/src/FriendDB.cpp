#include "FriendDB.h"
#include "InterServer.h"
#include "shared/NCriticalErrorLog.h"


CFriendDB::CFriendDB()
{
}


CFriendDB::~CFriendDB()
{
}


void CFriendDB::SaveFriend(unsigned long GID, STRUCT_FRIEND* pFriend, int Number)
{
	if( Number == 0 )
	{
		this->CFriendDB::DropFriend(GID);
		return;
	}

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
		return;

	char szcartBin[sizeof(STRUCT_FRIEND) * (MAX_FRIENDS_LIST+1)] = {}; //FIXME: copy-paste mistake in name
	SQLLEN cbGID = 0;
	SQLLEN cbfriendbin = sizeof(STRUCT_FRIEND) * Number; //FIXME: 'Number' used before getting bounds-checked

	if( Number > MAX_FRIENDS_LIST )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "SaveFriend :: Number > MAX_FRIENDS_LIST");
		Number = MAX_FRIENDS_LIST;
	}

	memcpy(szcartBin, pFriend, sizeof(STRUCT_FRIEND) * Number);

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GID, 0, &cbGID);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_BINARY, SQL_VARBINARY, sizeof(STRUCT_FRIEND) * Number, 0, szcartBin, 0, &cbfriendbin);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call UpdateFriends(?, ?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_retcode == SQL_NO_DATA )
		{
			m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call InsertFriends(?, ?)}", SQL_NTS);
			if( !SQL_SUCCEEDED(m_retcode) )
			{
				DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);
			}
		}
		else
		{
			DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);
		}
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}


int CFriendDB::LoadFriend(unsigned long GID, STRUCT_FRIEND* pFriend)
{
	if( pFriend == NULL )
		return -1;

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
		return -1;

	SQLLEN cbGID = 0;
	unsigned long sGID = GID;
	SQLLEN cbfriendbin = SQL_NTS;
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &sGID, 0, &cbGID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetFriends(?)}", SQL_NTS);
	pFriend->AID = 0;
	pFriend->GID = 0;

	if( !SQL_SUCCEEDED(m_retcode) )
	{
		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return 0;
	}

	SQLBindCol(m_hstmt, 1, SQL_C_BINARY, pFriend, sizeof(STRUCT_FRIEND) * MAX_FRIENDS_LIST, &cbfriendbin);

	m_retcode = SQLFetch(m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_retcode != SQL_NO_DATA )
		{
			DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);
			return 0; //FIXME: sql cleanup not done
		}

		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return 0;
	}

	if( cbfriendbin == SQL_NULL_DATA )
	{
		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return 0;
	}

	int Number = cbfriendbin / sizeof(STRUCT_FRIEND);
	if( Number == -1 )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);
		return 0; //FIXME: sql cleanup not done
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return Number;
}


void CFriendDB::DropFriend(unsigned long GID)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
		return;

	SQLLEN cbGID = 0;
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GID, 0, &cbGID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call DeleteFriends(?)}", SQL_NTS);
	if( m_retcode == SQL_SUCCESS )
		m_retcode = SQLFetch(m_hstmt);

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}
