#include "ErrorLog.h"
#include "FriendDB.h"
#include <sqlext.h>


CFriendDB::CFriendDB(void) // line 14
{
}


CFriendDB::~CFriendDB(void) // line 19
{
}


hook_method<void (CFriendDB::*)(unsigned long GID)> CFriendDB::_DropFriend(SERVER, "CFriendDB::DropFriend");
void CFriendDB::DropFriend(unsigned long GID) // line 134
{
	return (this->*_DropFriend)(GID);

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
		return;

	SQLINTEGER cbGID = 0;
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GID, 0, &cbGID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call DeleteFriends(?)}", SQL_NTS);
	if( m_retcode == SQL_SUCCESS )
		m_retcode = SQLFetch(m_hstmt);

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != NULL )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}


/// @param pFriend array of STRUCT_FRIEND[MAX_FRIENDS_LIST]
/// @return number of friend slots written, or -1 (fatal error)
hook_method<int (CFriendDB::*)(unsigned long GID, STRUCT_FRIEND* pFriend)> CFriendDB::_LoadFriend(SERVER, "CFriendDB::LoadFriend");
int CFriendDB::LoadFriend(unsigned long GID, STRUCT_FRIEND* pFriend) // line 86
{
	return (this->*_LoadFriend)(GID, pFriend);

	if( pFriend == NULL )
		return -1;

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
		return -1;

	SQLINTEGER cbGID = 0;
	long sGID = GID;
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &sGID, 0, &cbGID);
	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetFriends(?)}", SQL_NTS);

	pFriend->AID = 0;
	pFriend->GID = 0;

	int result = 0;
	if( SQL_SUCCEEDED(m_retcode) )
	{
		SQLINTEGER cbLength;
		SQLBindCol(m_hstmt, 1, SQL_C_BINARY, pFriend, MAX_FRIENDS_LIST*sizeof(STRUCT_FRIEND), &cbLength);
		m_retcode = SQLFetch(m_hstmt);
		if( m_retcode == SQL_SUCCESS|| m_retcode == SQL_SUCCESS_WITH_INFO )
		{
			if( cbLength != SQL_NULL_DATA )
				result = cbLength / sizeof(STRUCT_FRIEND);
		}
		else
		if( m_retcode != SQL_NO_DATA )
			result = -1;
	}

	if( result == -1 )
	{
		DBTrace(".\\FriendDB.cpp", 122, SQL_HANDLE_STMT, m_hstmt);
		return 0;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != NULL )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return result;
}


hook_method<void (CFriendDB::*)(unsigned long GID, STRUCT_FRIEND* pFriend, int Number)> CFriendDB::_SaveFriend(SERVER, "CFriendDB::SaveFriend");
void CFriendDB::SaveFriend(unsigned long GID, STRUCT_FRIEND* pFriend, int Number) // line 24 
{
	return (this->*_SaveFriend)(GID, pFriend, Number);

	if( Number == 0 )
	{
		this->CFriendDB::DropFriend(GID);
		return;
	}

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
		return;

	char szcartBin[1312];
	memset(szcartBin, 0, sizeof(szcartBin));

	if( Number > MAX_FRIENDS_LIST )
	{
		char buf[256];
		sprintf(buf, "SaveFriend :: Number > MAX_FRIENDS_LIST");
		g_errorLogs.CErrorLog::CriticalErrorLog(buf, 44, ".\\FriendDB.cpp");
		Number = MAX_FRIENDS_LIST;
	}

	memcpy(szcartBin, pFriend, Number * sizeof(STRUCT_FRIEND));

	SQLINTEGER cbGID = 0;
	SQLINTEGER cbfriendbin = 0;
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GID, 0, &cbGID);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_BINARY, SQL_NTS, Number * sizeof(STRUCT_FRIEND), 0, szcartBin, 0, &cbfriendbin);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call UpdateFriends(?, ?)}", SQL_NTS);
	if( m_retcode == SQL_SUCCESS || m_retcode == SQL_SUCCESS_WITH_INFO )
		;
	else
	if( m_retcode == SQL_NO_DATA )
	{
		m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call InsertFriends(?, ?)}", SQL_NTS);
		if( !SQL_SUCCEEDED(m_retcode) )
			DBTrace(".\\FriendDB.cpp", 68, SQL_HANDLE_STMT, m_hstmt);
	}
	else
	{
		DBTrace(".\\FriendDB.cpp", 73, SQL_HANDLE_STMT, m_hstmt);
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != NULL )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}
