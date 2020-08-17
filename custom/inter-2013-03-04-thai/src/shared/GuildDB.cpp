#include "shared/GuildDB.h"


CGuildDB::CGuildDB()
{
	this->CGuildDB::InitStoredProcTable();
}


CGuildDB::~CGuildDB()
{
	this->CODBC::Reset();
}


DWORD CGuildDB::GetTableDWORD(unsigned long GDID, int Type)
{
	return this->CGuildDB::GetDWORD(GDID, m_getProcTable[Type]);
}


void CGuildDB::GetTableChar(unsigned long GDID, int Type, char* Data, int Length)
{
	this->CGuildDB::GetChar(GDID, m_getProcTable[Type], Data, Length);
}


DWORD CGuildDB::GetDWORD(unsigned long GDID, char* StoredProc)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
		return 0;

	SQLINTEGER cbGID = 0;
	SQLINTEGER VALUE = 0;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GDID, 0, &cbGID);
	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)StoredProc, SQL_NTS);
	SQLBindCol(m_hstmt, 1, SQL_C_SLONG, &VALUE, 0, &cbGID);
	m_retcode = SQLFetch(m_hstmt);
	if( m_retcode == SQL_NO_DATA )
		VALUE = 0;
	SQLCloseCursor(m_hstmt);

	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return VALUE;
}


void CGuildDB::GetChar(unsigned long GDID, char* StoredProc, char* Data, int Length)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
		return;

	SQLINTEGER cbGID = 0;
	SQLINTEGER cbChar = SQL_NTS;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GDID, 0, &cbGID);
	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)StoredProc, SQL_NTS);
	SQLBindCol(m_hstmt, 1, SQL_C_CHAR, Data, Length, &cbChar);
	m_retcode = SQLFetch(m_hstmt);
	SQLCloseCursor(m_hstmt);

	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}


void CGuildDB::InitStoredProcTable()
{
	m_getProcTable[ 0] = "{call GetGuildLevel(?)}";
	m_getProcTable[ 1] = "{call GetGuildName(?)}";
	m_getProcTable[ 2] = "{call GetGuildMName(?)}";
	m_getProcTable[ 3] = "{call GetGuildMaxUserNum(?)}";
	m_getProcTable[ 4] = "{call GetGuildHonor(?)}";
	m_getProcTable[ 5] = "{call GetGuildVirtue(?)}";
	m_getProcTable[ 6] = "{call GetGuildType(?)}";
	m_getProcTable[ 7] = "{call GetGuildClass(?)}";
	m_getProcTable[ 8] = "{call GetGuildMoney(?)}";
	m_getProcTable[ 9] = "{call GetGuildArenaWin(?)}";
	m_getProcTable[10] = "{call GetGuildArenaLose(?)}";
	m_getProcTable[11] = "{call GetGuildArenaDrawn(?)}";
	m_getProcTable[12] = "{call GetGuildManageLand(?)}";
	m_getProcTable[13] = "{call GetGuildExp(?)}";
	m_getProcTable[14] = "{call GetGuildEmblem(?)}";
	m_getProcTable[15] = "{call GetGuildPoint(?)}";
	m_getProcTable[16] = "{call GetGuildDesc(?)}";
	m_getProcTable[17] = "{call GetGuildMemberCharName(?)}";
	m_getProcTable[18] = "{call GetGuildMemberClass(?)}";
	m_getProcTable[19] = "{call GetGuildMemberLevel(?)}";
	m_getProcTable[20] = "{call GetGuildMemberMemo(?)}";
	m_getProcTable[21] = "{call GetGuildMemberService(?)}";
	m_getProcTable[22] = "{call GetGuildMemberExp(?)}";
	m_getProcTable[23] = "{call GetGuildMemberAID(?)}";
	m_getProcTable[24] = "{call GetGuildMemberPositionID(?)}";
//	m_getProcTable[25] = "{call GetGuildMemberGDID(?)}";
//	m_getProcTable[26] = "{call GetGuildMemberGID(?)}";
	m_getProcTable[27] = "{call GetGuildOpponentGDID(?)}";
	m_getProcTable[28] = "{call GetGuildRelation(?)}";
	m_getProcTable[29] = "{call GetGuildNotice(?)}";
	m_getProcTable[30] = "{call GetGuildBMemberName(?)}";
	m_getProcTable[31] = "{call GetGuildBMemberAccount(?)}";
	m_getProcTable[32] = "{call GetGuildBReason(?)}";
	m_getProcTable[33] = "{call GetGuildBGID(?)}";
	m_getProcTable[34] = "{call GetGuildBAID(?)}";
	m_getProcTable[35] = "{call GetGuildMPGrade(?)}";
	m_getProcTable[36] = "{call GetGuildMPPos(?)}";
	m_getProcTable[37] = "{call GetGuildMPJoinRight(?)}";
	m_getProcTable[38] = "{call GetGuildMPPenaltyRight(?)}";
	m_getProcTable[39] = "{call GetGuildMPPositionID(?)}";
}


int CGuildDB::GetGuildID(char* GName)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
		return 0;

	int GDID = 0;
	SQLINTEGER cbChar = SQL_NTS;
	SQLINTEGER cbGRID;

	char GuildName[24+1];
	memcpy_s(GuildName, sizeof(GuildName), GName, 24);
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 24, 0, GuildName, 0, &cbChar);
	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetGuildID(?)}", SQL_NTS);
	SQLBindCol(m_hstmt, 1, SQL_C_SLONG, &GDID, 0, &cbGRID);
	m_retcode = SQLFetch(m_hstmt);
	if( m_retcode == SQL_NO_DATA )
		GDID = 0;
	SQLCloseCursor(m_hstmt);

	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return GDID;
}


BOOL CGuildDB::Init(const char* dsnFile, const char* PASS)
{
	this->CODBC::Init(dsnFile, PASS);
	return TRUE;
}
