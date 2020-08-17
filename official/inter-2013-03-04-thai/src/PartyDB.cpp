#include "PartyDB.h"
#include "PartyMgr.h"
#include "shared/NCriticalErrorLog.h"


/// singleton instance
CPartyDB*& CPartyDB::m_cpSelf = VTOR<CPartyDB*>(DetourFindFunction(EXEPATH(), "CPartyDB::m_cpSelf"));


CPartyDB::CPartyDB()
{
}


CPartyDB::~CPartyDB()
{
}


unsigned long CPartyDB::MakeGroup(unsigned long AID, unsigned long GID, const char* name)
{
	if( this->CPartyDB::SearchMember(GID) )
		return GROUP_MAKE_FAILED_ALEADY_GROUP_MEMBER;

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
		{
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "SQL_NULL_HSTMT");
		}

		return GROUP_MAKE_FAILED_SAMENAME;
	}

	SQLLEN cbChar = SQL_NTS;
	char groupName[24];
	memcpy(groupName, name, 24);
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 24, 0, groupName, 0, &cbChar);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call InsertGroup(?)}", SQL_NTS);

	char temp2[50];
	SQLINTEGER temp3;
	char tempm[100];
	SQLSMALLINT tempo;
	SQLGetDiagRecA(SQL_HANDLE_STMT, m_hstmt, 1, (SQLCHAR*)temp2, &temp3, (SQLCHAR*)tempm, countof(tempm), &tempo);

	if( !SQL_SUCCEEDED(m_retcode) )
	{
		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Group inserted False");
		return GROUP_MAKE_FAILED_SAMENAME;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return GROUP_MAKE_SUCCEED;
}


unsigned long CPartyDB::MakeGroup(unsigned long AID, unsigned long GID, const char* name, bool ItemPickupRule, bool ItemDivisionRule)
{
	PARTY_RULE_VALUE PartyRuleValue;
	PartyRuleValue.RuleValue.ItemPickupRule = ItemPickupRule;
	PartyRuleValue.RuleValue.ItemDivisionRule = ItemDivisionRule;
	PartyRuleValue.RuleValue.expOption = EXP_NOTSHARED;

	if( this->CPartyDB::SearchMember(GID) )
		return GROUP_MAKE_FAILED_ALEADY_GROUP_MEMBER;

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return GROUP_MAKE_FAILED_SAMENAME;
	}

	SQLLEN cbPartyRole = 0;
	SQLLEN cbChar = SQL_NTS;
	char groupName[24];
	memcpy(groupName, name, 24);
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 24, 0, groupName, 0, &cbChar);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &PartyRuleValue, 0, &cbPartyRole);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call InsertGroup(?,?)}", SQL_NTS);

	char temp2[50];
	SQLINTEGER temp3;
	char tempm[100];
	SQLSMALLINT tempo;
	SQLGetDiagRecA(SQL_HANDLE_STMT, m_hstmt, 1, (SQLCHAR*)temp2, &temp3, (SQLCHAR*)tempm, countof(tempm), &tempo);

	if( !SQL_SUCCEEDED(m_retcode) )
	{
		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return GROUP_MAKE_FAILED_SAMENAME;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return GROUP_MAKE_SUCCEED;
}


unsigned long CPartyDB::GetGroupID(const char* name)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return 0;
	}

	unsigned long GRID = 0;

	SQLLEN cbChar = SQL_NTS;
	char groupName[24];
	memcpy(groupName, name, 24);
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 24, 0, groupName, 0, &cbChar);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetGroupID(?)}", SQL_NTS);

	SQLLEN cbGRID;
	SQLBindCol(m_hstmt, 1, SQL_C_SLONG, &GRID, 0, &cbGRID);

	m_retcode = SQLFetch(m_hstmt);
	if( m_retcode == SQL_NO_DATA )
		GRID = 0;

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return GRID;
}


unsigned long CPartyDB::SearchMember(unsigned long GID)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return 0;
	}

	unsigned long GRID = 0;

	SQLLEN cbGID = 0;
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GID, 0, &cbGID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetMember(?)}", SQL_NTS);

	char temp2[50];
	SQLINTEGER temp3;
	char tempm[100];
	SQLSMALLINT tempo;
	SQLGetDiagRecA(SQL_HANDLE_STMT, m_hstmt, 1, (SQLCHAR*)temp2, &temp3, (SQLCHAR*)tempm, 100, &tempo);

//	SQLLEN cbGID = 0;
	SQLBindCol(m_hstmt, 1, SQL_C_SLONG, &GRID, 0, &cbGID);

	m_retcode = SQLFetch(m_hstmt);
	if( m_retcode == SQL_NO_DATA )
		GRID = 0;

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return GRID;
}


void CPartyDB::GetGroupName(unsigned long GRID, char* name)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return;
	}

	SQLLEN cbGRID = 0;
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GRID, 0, &cbGRID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetGroupName(?)}", SQL_NTS);

	SQLLEN cbChar = SQL_NTS;
	SQLBindCol(m_hstmt, 1, SQL_C_CHAR, name, 24, &cbChar);

	m_retcode = SQLFetch(m_hstmt);

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}


void CPartyDB::GetGroupInfo(unsigned long GRID, char* name, bool& ItemPickupRule, bool& ItemDivisionRule)
{
	PARTY_RULE_VALUE PartyRuleValue;
	PartyRuleValue.DBValue = 0;

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return;
	}

	SQLLEN cbGRID = 0;
	SQLLEN cbChar = SQL_NTS;
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GRID, 0, &cbGRID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetGroupInfo(?)}", SQL_NTS);

	SQLBindCol(m_hstmt, 1, SQL_C_CHAR, name, 24, &cbChar);
	SQLBindCol(m_hstmt, 2, SQL_C_SLONG, &PartyRuleValue, 0, &cbGRID);

	m_retcode = SQLFetch(m_hstmt);

	ItemPickupRule = PartyRuleValue.RuleValue.ItemPickupRule;
	ItemDivisionRule = PartyRuleValue.RuleValue.ItemDivisionRule;

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}


BOOL CPartyDB::DeleteGroup(unsigned long GRID)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLLEN cbGRID = 0;
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GRID, 0, &cbGRID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call DeleteGroup(?)}", SQL_NTS);
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


BOOL CPartyDB::DeleteGroup(char* name)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLLEN cbChar = SQL_NTS;
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 24, 0, &name, 0, &cbChar);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call DeleteGroupByName(?)}", SQL_NTS);
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


int CPartyDB::GetGroupMembers(const unsigned long in_GRID, DBGROUPINFO* const in_pGroupInfoArray, const int in_GroupInfoArrayNum)
{
	SQLRETURN retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return 0;
	}

	SQLLEN cbGID = 0;
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, (SQLPOINTER)&in_GRID, 0, &cbGID);

	SQLRETURN retcode2 = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetGroupMembers(?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(retcode2) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return 0;
	}

	DBGROUPINFO data;
//	SQLLEN cbGID = 0;
	SQLLEN cbChar = SQL_NTS;
	SQLBindCol(m_hstmt, 1, SQL_C_SLONG, &data.GID, 0, &cbGID);
	SQLBindCol(m_hstmt, 2, SQL_C_SLONG, &data.AID, 0, &cbGID);
	SQLBindCol(m_hstmt, 3, SQL_C_CHAR, data.name, 24, &cbChar);
	SQLBindCol(m_hstmt, 4, SQL_C_SLONG, &data.GRID, 0, &cbGID);
	SQLBindCol(m_hstmt, 5, SQL_C_SLONG, &data.Role, 0, &cbGID);

	int MemberCnt = 0;
	while( SQLFetch(m_hstmt) != SQL_NO_DATA )
	{
		if( MemberCnt >= CPartyMgr::MAX_PARTY_MEMBER_NUM )
			break;

		memcpy(&in_pGroupInfoArray[MemberCnt], &data, sizeof(DBGROUPINFO));
		++MemberCnt;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return MemberCnt;
}


BOOL CPartyDB::InsertMember(unsigned long GID, unsigned long AID, unsigned long GRID, char* charName, int Role)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLLEN cbInt = 0;
	SQLLEN cbChar = SQL_NTS;
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &AID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 24, 0, charName, 0, &cbChar);
	SQLBindParameter(m_hstmt, 4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GRID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Role, 0, &cbInt);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call InsertMember(?,?,?,?,?)}", SQL_NTS);
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


BOOL CPartyDB::DeleteMember(unsigned long GID)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLLEN cbGID = 0;
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GID, 0, &cbGID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call DeleteMember(?)}", SQL_NTS);
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


BOOL CPartyDB::DeleteMemberByName(char* name)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLLEN cbChar = SQL_NTS;
	char charName[24];
	memcpy(charName, name, 24);
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 24, 0, charName, 0, &cbChar);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call DeleteMemberByName(?)}", SQL_NTS);

	char temp2[50];
	SQLINTEGER temp3;
	char tempm[100];
	SQLSMALLINT tempo;
	SQLGetDiagRecA(SQL_HANDLE_STMT, m_hstmt, 1, (SQLCHAR*)temp2, &temp3, (SQLCHAR*)tempm, countof(tempm), &tempo);

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


void CPartyDB::UpdateMemberRole(unsigned long in_GRID, unsigned long in_firstGID, int in_firstRole, unsigned long in_secondGID, int in_secondRole)
{
	SQLRETURN retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return;
	}

	SQLLEN cbInt = 0;
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &in_GRID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &in_firstGID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &in_firstRole, 0, &cbInt);
	SQLBindParameter(m_hstmt, 4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &in_secondGID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &in_secondRole, 0, &cbInt);

	SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call usp_party_role_change(?,?,?,?,?)}", SQL_NTS);

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}


bool CPartyDB::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CPartyDB();
	if( m_cpSelf == NULL )
		return false;

	return true;
}


void CPartyDB::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CPartyDB* CPartyDB::GetObj() /// @custom
{
	return m_cpSelf;
}
