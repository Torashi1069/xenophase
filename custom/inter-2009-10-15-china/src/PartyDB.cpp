#include "PartyDB.h"
#include "ErrorLog.h"
#include "globals.hpp"
#define SQL_NOUNICODEMAP
#include <sqlext.h>


CPartyDB::CPartyDB(void) // line 9-10
{
}


CPartyDB::~CPartyDB(void) // line 13-14
{
}


hook_method<unsigned long (CPartyDB::*)(unsigned long AID, unsigned long GID, const char* name, unsigned char ItemPickupRule, unsigned char ItemDivisionRule)> CPartyDB::_MakeGroup(SERVER, "?MakeGroup@CPartyDB@@QAEKKKPBDEE@Z");
unsigned long CPartyDB::MakeGroup(unsigned long AID, unsigned long GID, const char* name, unsigned char ItemPickupRule, unsigned char ItemDivisionRule) // line 77-141
{
	return (this->*_MakeGroup)(AID,GID,name,ItemPickupRule,ItemDivisionRule);

	CPartyDB::PARTY_RULE_VALUE PartyRuleValue; PartyRuleValue.DBValue = (ItemPickupRule&1) | (2 * (ItemDivisionRule&1));

	unsigned long GRID = this->CPartyDB::SearchMember(GID);
	if( GRID != 0 )
		return 2; // already in a party

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
		return 1; // failed to allocate statement
	}

	char groupName[24]; memcpy(groupName, name, sizeof(groupName)); // FIXME assumes name has 24 bytes or more
	SQLINTEGER cbChar = SQL_NTS;
	SQLINTEGER cbPartyRole = 0;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 24, 0, groupName, 0, &cbChar);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &PartyRuleValue, 0, &cbPartyRole);
	m_retcode = SQLExecDirect(m_hstmt, (SQLCHAR*)"{call InsertGroup(?,?)}", SQL_NTS);
	
	SQLCHAR temp2[50];
	SQLINTEGER temp3;
	SQLCHAR tempm[100];
	SQLSMALLINT tempo;
	SQLGetDiagRec(SQL_HANDLE_STMT, m_hstmt, 1, temp2, &temp3, tempm, 100, &tempo);

	if( SQL_SUCCEEDED(m_retcode) )
	{
		Trace("Group inserted\n");
		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
		return 0; // done
	}
	else
	{
		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
		return 1; // failed to create group
	}
}


hook_method<unsigned long (CPartyDB::*)(unsigned long AID, unsigned long GID, const char* name)> CPartyDB::_MakeGroup2(SERVER, "?MakeGroup@CPartyDB@@QAEKKKPBD@Z");
unsigned long CPartyDB::MakeGroup(unsigned long AID, unsigned long GID, const char* name) // line 17-74
{
	return (this->*_MakeGroup2)(AID,GID,name);

	unsigned long GRID = this->CPartyDB::SearchMember(GID);
	if( GRID != 0 )
		return 2; // already in a party

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
		{
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
			g_errorLogs.CErrorLog::CriticalErrorLog("SQL_NULL_HSTMT", 27, ".\\PartyDB.cpp");
		}
		return 1; // failed to allocate statement
	}

	char groupName[24]; memcpy(groupName, name, sizeof(groupName)); // FIXME assumes name has 24 bytes or more
	SQLINTEGER cbChar = SQL_NTS;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 24, 0, groupName, 0, &cbChar);
	m_retcode = SQLExecDirect(m_hstmt, (SQLCHAR*)"{call InsertGroup(?)}", SQL_NTS);

	SQLCHAR temp2[50];
	SQLINTEGER temp3;
	SQLCHAR tempm[100];
	SQLSMALLINT tempo;
	SQLGetDiagRec(SQL_HANDLE_STMT, m_hstmt, 1, temp2, &temp3, tempm, 100, &tempo);

	if( SQL_SUCCEEDED(m_retcode) )
	{
		Trace("Group inserted\n");
		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
		return 0; // done
	}
	else
	{
		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
		g_errorLogs.CErrorLog::CriticalErrorLog("Group inserted False", 66, ".\\PartyDB.cpp");
		return 1; // failed to create group
	}
}


hook_method<void (CPartyDB::*)(unsigned long GRID, char* name)> CPartyDB::_GetGroupName(SERVER, "CPartyDB::GetGroupName");
void CPartyDB::GetGroupName(unsigned long GRID, char* name) // line 220-250
{
	return (this->*_GetGroupName)(GRID,name);

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( SQL_SUCCEEDED(m_retcode) )
	{
		// FIXME no error checking
		SQLINTEGER cbGRID = 0;
		SQLINTEGER cbChar = SQL_NTS;

		SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GRID, 0, &cbGRID);
		m_retcode = SQLExecDirect(m_hstmt, (SQLCHAR*)"{call GetGroupName(?)}", SQL_NTS);

		SQLBindCol(m_hstmt, 1, SQL_C_CHAR, name, 24, &cbChar); // FIXME assumes name has 24 bytes or more
		m_retcode = SQLFetch(m_hstmt);

		SQLCloseCursor(m_hstmt);
	}
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}


hook_method<void (CPartyDB::*)(unsigned long GRID, char* name, unsigned char& ItemPickupRule, unsigned char& ItemDivisionRule)> CPartyDB::_GetGroupInfo(SERVER, "CPartyDB::GetGroupInfo");
void CPartyDB::GetGroupInfo(unsigned long GRID, char* name, unsigned char& ItemPickupRule, unsigned char& ItemDivisionRule) // line 253-290
{
	return (this->*_GetGroupInfo)(GRID,name,ItemPickupRule,ItemDivisionRule);

	CPartyDB::PARTY_RULE_VALUE PartyRuleValue; PartyRuleValue.DBValue = 0;

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( SQL_SUCCEEDED(m_retcode) )
	{
		// FIXME no error checking
		SQLINTEGER cbGRID = 0;
		SQLINTEGER cbChar = SQL_NTS;

		SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GRID, 0, &cbGRID);
		m_retcode = SQLExecDirect(m_hstmt, (SQLCHAR*)"{call GetGroupInfo(?)}", SQL_NTS);

		SQLBindCol(m_hstmt, 1, SQL_C_CHAR, name, 24, &cbChar); // FIXME assumes name has 24 bytes or more
		SQLBindCol(m_hstmt, 2, SQL_C_SLONG, &PartyRuleValue, 0, &cbGRID);
		m_retcode = SQLFetch(m_hstmt);

		ItemPickupRule = PartyRuleValue.RuleValue.ItemPickupRule;
		ItemDivisionRule = PartyRuleValue.RuleValue.ItemDivisionRule;

		SQLCloseCursor(m_hstmt);
	}
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}


hook_method<int (CPartyDB::*)(char* name)> CPartyDB::_DeleteGroup(SERVER, "?DeleteGroup@CPartyDB@@QAEHPAD@Z");
int CPartyDB::DeleteGroup(char* name) // line 327-358
{
	return (this->*_DeleteGroup)(name);

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
		return 0; // failed to allocate statement
	}

	SQLINTEGER cbChar = SQL_NTS;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 24, 0, name, 0, &cbChar); // FIXME assumes name has 24 bytes or more
	m_retcode = SQLExecDirect(m_hstmt, (SQLCHAR*)"{call DeleteGroupByName(?)}", SQL_NTS);

	int result;
	if( SQL_SUCCEEDED(m_retcode) )
		result = 1; // done
	else
		result = 0; // failed to delete group

	SQLCloseCursor(m_hstmt);

	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
	return result;
}


hook_method<int (CPartyDB::*)(unsigned long GRID)> CPartyDB::_DeleteGroup2(SERVER, "?DeleteGroup@CPartyDB@@QAEHK@Z");
int CPartyDB::DeleteGroup(unsigned long GRID) // line 293-324
{
	return (this->*_DeleteGroup2)(GRID);

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
		return 0; // failed to allocate statement
	}

	SQLINTEGER cbGRID = 0;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GRID, 0, &cbGRID); // FIXME assumes name has 24 bytes or more
	m_retcode = SQLExecDirect(m_hstmt, (SQLCHAR*)"{call DeleteGroup(?)}", SQL_NTS);

	int result;
	if( SQL_SUCCEEDED(m_retcode) )
		result = 1; // done
	else
		result = 0; // failed to delete group

	SQLCloseCursor(m_hstmt);

	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
	return result;
}


hook_method<unsigned long (CPartyDB::*)(const char* name)> CPartyDB::_GetGroupID(SERVER, "CPartyDB::GetGroupID");
unsigned long CPartyDB::GetGroupID(const char* name) // line 144-178
{
	return (this->*_GetGroupID)(name);

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
		return 0; // failed to allocate statement
	}

	char groupName[24]; memcpy(groupName, name, sizeof(groupName)); // FIXME assumes name has 24 bytes or more
	long GRID = 0;
	SQLINTEGER cbGRID;
	SQLINTEGER cbChar = SQL_NTS;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 24, 0, groupName, 0, &cbChar);
	m_retcode = SQLExecDirect(m_hstmt, (SQLCHAR*)"{call GetGroupID(?)}", SQL_NTS);

	SQLBindCol(m_hstmt, 1, SQL_C_SLONG, &GRID, 0, &cbGRID);
	m_retcode = SQLFetch(m_hstmt);

	if( m_retcode == SQL_NO_DATA )
		GRID = 0; // party not found

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return GRID; // done
}


hook_method<int (CPartyDB::*)(const unsigned long in_GRID, DBGROUPINFO* const in_pGroupInfoArray, const int in_GroupInfoArrayNum)> CPartyDB::_GetGroupMembers(SERVER, "CPartyDB::GetGroupMembers");
int CPartyDB::GetGroupMembers(const unsigned long in_GRID, DBGROUPINFO* const in_pGroupInfoArray, const int in_GroupInfoArrayNum) // line 365-407
{
	return (this->*_GetGroupMembers)(in_GRID,in_pGroupInfoArray,in_GroupInfoArrayNum);

	SQLRETURN retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt); // FIXME should use m_retcode
	if( !SQL_SUCCEEDED(retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
		return 0; // failed to allocate statement
	}

	SQLINTEGER cbGID = 0;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, (SQLPOINTER)&in_GRID, 0, &cbGID);
	retcode = SQLExecDirect(m_hstmt, (SQLCHAR*)"{call GetGroupMembers(?)}", SQL_NTS); // FIXME should use m_retcode

	if( !SQL_SUCCEEDED(retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
		return 0; // failed to get party members
	}

	SQLINTEGER cbChar = SQL_NTS;
	DBGROUPINFO data;

	SQLBindCol(m_hstmt, 1, SQL_C_SLONG, &data.GID, 0, &cbGID);
	SQLBindCol(m_hstmt, 2, SQL_C_SLONG, &data.AID, 0, &cbGID);
	SQLBindCol(m_hstmt, 3, SQL_C_CHAR, data.name, 24, &cbChar);
	SQLBindCol(m_hstmt, 4, SQL_C_SLONG, &data.GRID, 0, &cbGID);
	SQLBindCol(m_hstmt, 5, SQL_C_SLONG, &data.Role, 0, &cbGID);

	int MemberCnt = 0;
	while( SQLFetch(m_hstmt) != SQL_NO_DATA )
	{
		if( MemberCnt >= in_GroupInfoArrayNum )
			break;
		memcpy(in_pGroupInfoArray + MemberCnt, &data, sizeof(data));
		++MemberCnt;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
	return MemberCnt; // done
}


hook_method<int (CPartyDB::*)(unsigned long GID, unsigned long AID, unsigned long GRID, char* charName, int Role)> CPartyDB::_InsertMember(SERVER, "CPartyDB::InsertMember");
int CPartyDB::InsertMember(unsigned long GID, unsigned long AID, unsigned long GRID, char* charName, int Role) // line 410-448
{
	return (this->*_InsertMember)(GID,AID,GRID,charName,Role);

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
		return 0; // failed to allocate statement
	}

	SQLINTEGER cbInt = 0;
	SQLINTEGER cbChar = SQL_NTS;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &AID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 24, 0, charName, 0, &cbChar); // FIXME assumes charName has 24 bytes or more
	SQLBindParameter(m_hstmt, 4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GRID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Role, 0, &cbInt);
	m_retcode = SQLExecDirect(m_hstmt, (SQLCHAR*)"{call InsertMember(?,?,?,?,?)}", SQL_NTS);

	int result;
	if( SQL_SUCCEEDED(m_retcode) )
		result = 1; // done
	else
		result = 0; // failed to insert member

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return result;
}


hook_method<int (CPartyDB::*)(unsigned long GID)> CPartyDB::_DeleteMember(SERVER, "CPartyDB::DeleteMember");
int CPartyDB::DeleteMember(unsigned long GID) // line 451-483
{
	return (this->*_DeleteMember)(GID);

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
		return 0; // failed to allocate statement
	}

	SQLINTEGER cbGID = 0;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GID, 0, &cbGID);
	m_retcode = SQLExecDirect(m_hstmt, (SQLCHAR*)"{call DeleteMember(?)}", SQL_NTS);

	int result;
	if( SQL_SUCCEEDED(m_retcode) )
		result = 1; // done
	else
		result = 0; // failed to delete member

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return result;
}


hook_method<int (CPartyDB::*)(char* name)> CPartyDB::_DeleteMemberByName(SERVER, "CPartyDB::DeleteMemberByName");
int CPartyDB::DeleteMemberByName(char* name) // line 487-527
{
	return (this->*_DeleteMemberByName)(name);

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
		return 0; // failed to allocate statement
	}

	char charName[24]; memcpy(charName, name, sizeof(charName)); // FIXME assumes name has 24 bytes or more
	SQLINTEGER cbChar = SQL_NTS;

	SQLBindParameter(m_hstmt, 1u, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 24, 0, charName, 0, &cbChar);
	m_retcode = SQLExecDirect(m_hstmt, (SQLCHAR*)"{call DeleteMemberByName(?)}", SQL_NTS);

	SQLCHAR temp2[50];
	SQLINTEGER temp3;
	SQLCHAR tempm[100];
	SQLSMALLINT tempo;
	SQLGetDiagRec(SQL_HANDLE_STMT, m_hstmt, 1, temp2, &temp3, tempm, 100, &tempo);

	int result;
	if( SQL_SUCCEEDED(m_retcode) )
		result = 1; // done
	else
		result = 0; // failed to delete member

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return result;
}


hook_method<unsigned long (CPartyDB::*)(unsigned long GID)> CPartyDB::_SearchMember(SERVER, "CPartyDB::SearchMember");
unsigned long CPartyDB::SearchMember(unsigned long GID) // line 181-217
{
	return (this->*_SearchMember)(GID);

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
		return 0; // failed to allocate statement
	}

	SQLINTEGER cbGID = 0;
	long GRID = 0;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GID, 0, &cbGID);
	m_retcode = SQLExecDirect(m_hstmt, (SQLCHAR*)"{call GetMember(?)}", SQL_NTS);

	SQLCHAR temp2[50];
	SQLINTEGER temp3;
	SQLCHAR tempm[100];
	SQLSMALLINT tempo;
	SQLGetDiagRec(SQL_HANDLE_STMT, m_hstmt, 1, temp2, &temp3, tempm, 100, &tempo);

	SQLBindCol(m_hstmt, 1, SQL_C_SLONG, &GRID, 0, &cbGID);
	m_retcode = SQLFetch(m_hstmt);

	if( m_retcode == SQL_NO_DATA )
		GRID = 0; // party member not found

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return GRID;
}
