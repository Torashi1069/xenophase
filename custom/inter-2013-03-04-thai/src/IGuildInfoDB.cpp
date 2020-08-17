#include "IGuildInfoDB.h"
#include "InterServer.h"


CIGuildInfoDB::CIGuildInfoDB()
{
	this->CIGuildInfoDB::InitStoredProcTable();
}


CIGuildInfoDB::~CIGuildInfoDB()
{
}


int CIGuildInfoDB::MakeGuild(unsigned long AID, unsigned long GID, unsigned long& GDID, char* Name, char* GName)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return -1;
	}

	SQLLEN cbChar = SQL_NTS;

	char MasterName[24];
	char GuildName[24];
	memcpy(GuildName, GName, sizeof(GuildName));
	memcpy(MasterName, Name, sizeof(MasterName));

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, sizeof(GuildName), 0, GuildName, 0, &cbChar);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, sizeof(GuildName), 0, MasterName, 0, &cbChar);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call InsertGuild(?,?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return -1;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return 1;
}


void CIGuildInfoDB::InitStoredProcTable()
{
	m_inputProcTable[ 0] = "{call UpdateGuildLevel(?,?)}";
	m_inputProcTable[ 1] = "{call UpdateGuildName(?,?)}";
	m_inputProcTable[ 2] = "{call UpdateGuildMName(?,?)}";
	m_inputProcTable[ 3] = "{call UpdateGuildMaxUserNum(?,?)}";
	m_inputProcTable[ 4] = "{call UpdateGuildHonor(?,?)}";
	m_inputProcTable[ 5] = "{call UpdateGuildVirtue(?,?)}";
	m_inputProcTable[ 6] = "{call UpdateGuildType(?,?)}";
	m_inputProcTable[ 7] = "{call UpdateGuildClass(?,?)}";
	m_inputProcTable[ 8] = "{call UpdateGuildMoney(?,?)}";
	m_inputProcTable[ 9] = "{call UpdateGuildArenaWin(?,?)}";
	m_inputProcTable[10] = "{call UpdateGuildArenaLose(?,?)}";
	m_inputProcTable[11] = "{call UpdateGuildArenaDrawn(?,?)}";
	m_inputProcTable[12] = "{call UpdateGuildManageLand(?,?)}";
	m_inputProcTable[13] = "{call UpdateGuildExp(?,?)}";
	m_inputProcTable[14] = "{call UpdateGuildEmblem(?,?)}";
	m_inputProcTable[15] = "{call UpdateGuildPoint(?,?)}";
	m_inputProcTable[16] = "{call UpdateGuildDesc(?,?)}";
	m_inputProcTable[17] = "{call UpdateGuildMemberCharName(?,?)}";
	m_inputProcTable[18] = "{call UpdateGuildMemberClass(?,?)}";
	m_inputProcTable[19] = "{call UpdateGuildMemberLevel(?,?)}";
	m_inputProcTable[20] = "{call UpdateGuildMemberMemo(?,?)}";
	m_inputProcTable[21] = "{call UpdateGuildMemberService(?,?)}";
	m_inputProcTable[22] = "{call UpdateGuildMemberExp(?,?)}";
	m_inputProcTable[23] = "{call UpdateGuildMemberAID(?,?)}";
	m_inputProcTable[24] = "{call UpdateGuildMemberPositionID(?,?)}";
//	m_inputProcTable[25] = "{call UpdateGuildMemberGDID(?)}";
//	m_inputProcTable[26] = "{call UpdateGuildMemberGID(?)}";
	m_inputProcTable[27] = "{call UpdateGuildOpponentGDID(?,?)}";
	m_inputProcTable[28] = "{call UpdateGuildRelation(?,?)}";
	m_inputProcTable[29] = "{call UpdateGuildNotice(?,?)}";
	m_inputProcTable[30] = "{call UpdateGuildBMemberName(?,?)}";
	m_inputProcTable[31] = "{call UpdateGuildBMemberAccount(?,?)}";
	m_inputProcTable[32] = "{call UpdateGuildBReason(?,?)}";
	m_inputProcTable[33] = "{call UpdateGuildBGID(?,?)}";
	m_inputProcTable[34] = "{call UpdateGuildBAID(?,?)}";
	m_inputProcTable[35] = "{call UpdateGuildMPGrade(?,?)}";
	m_inputProcTable[36] = "{call UpdateGuildMPPos(?,?)}";
	m_inputProcTable[37] = "{call UpdateGuildMPJoinRight(?,?)}";
	m_inputProcTable[38] = "{call UpdateGuildMPPenaltyRight(?,?)}";
	m_inputProcTable[39] = "{call UpdateGuildMPPositionID(?,?)}";
}


BOOL CIGuildInfoDB::UpdateTableDWORD(unsigned long GDID, unsigned long Value, int ProcType)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLLEN cbInt = 0;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GDID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Value, 0, &cbInt);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)m_inputProcTable[ProcType], SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

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


BOOL CIGuildInfoDB::UpdateTableChar(unsigned long GDID, char* Value, int ProcType)
{

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLLEN cbInt = 0;
	SQLLEN cbChar = SQL_NTS;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GDID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(Value), 0, Value, 0, &cbChar);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)m_inputProcTable[ProcType], SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

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


BOOL CIGuildInfoDB::GetGuildInfoDB(unsigned long GDID, GUILDINFO& Guild)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLLEN cbGID = 0;
	SQLLEN cbChar = SQL_NTS;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GDID, 0, &cbGID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetGuildInfoDB(?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

	SQLBindCol(m_hstmt, 1, SQL_C_SLONG, &Guild.GDID, 0, &cbGID);
	SQLBindCol(m_hstmt, 2, SQL_C_SLONG, &Guild.Level, 0, &cbGID);
	SQLBindCol(m_hstmt, 3, SQL_C_CHAR, Guild.Name, sizeof(Guild.Name), &cbChar);
	SQLBindCol(m_hstmt, 4, SQL_C_CHAR, Guild.MName, sizeof(Guild.MName), &cbChar);
	SQLBindCol(m_hstmt, 5, SQL_C_SLONG, &Guild.MaxUserNum, 0, &cbGID);
	SQLBindCol(m_hstmt, 6, SQL_C_SLONG, &Guild.Honor, 0, &cbGID);
	SQLBindCol(m_hstmt, 7, SQL_C_SLONG, &Guild.Virtue, 0, &cbGID);
	SQLBindCol(m_hstmt, 8, SQL_C_SLONG, &Guild.Type, 0, &cbGID);
	SQLBindCol(m_hstmt, 9, SQL_C_SLONG, &Guild.Class, 0, &cbGID);
	SQLBindCol(m_hstmt, 10, SQL_C_SLONG, &Guild.Money, 0, &cbGID);
	SQLBindCol(m_hstmt, 11, SQL_C_SLONG, &Guild.ArenaWin, 0, &cbGID);
	SQLBindCol(m_hstmt, 12, SQL_C_SLONG, &Guild.ArenaLose, 0, &cbGID);
	SQLBindCol(m_hstmt, 13, SQL_C_SLONG, &Guild.ArenaDrawn, 0, &cbGID);
	SQLBindCol(m_hstmt, 14, SQL_C_CHAR, Guild.ManageLand, sizeof(Guild.ManageLand), &cbChar);
	SQLBindCol(m_hstmt, 15, SQL_C_SLONG, &Guild.Exp, 0, &cbGID);
	SQLBindCol(m_hstmt, 16, SQL_C_SLONG, &Guild.EmblemVersion, 0, &cbGID);
	SQLBindCol(m_hstmt, 17, SQL_C_SLONG, &Guild.Point, 0, &cbGID);
	SQLBindCol(m_hstmt, 18, SQL_C_CHAR, Guild.Desc, sizeof(Guild.Desc), &cbChar);

	m_retcode = SQLFetch(m_hstmt);
	if( m_retcode == SQL_NO_DATA )
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


int CIGuildInfoDB::GetGuildMInfoDB(unsigned long GDID, int& buflen, char* buf)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return 0;
	}

	SQLLEN cbGID = 0;
	SQLLEN cbChar = SQL_NTS;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GDID, 0, &cbGID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetGuildMInfoDB(?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

	GUILDMINFO Guild;
	SQLBindCol(m_hstmt, 1, SQL_C_SLONG, &Guild.GID, 0, &cbGID);
	SQLBindCol(m_hstmt, 2, SQL_C_CHAR, Guild.CharName, sizeof(Guild.CharName), &cbChar);
	SQLBindCol(m_hstmt, 3, SQL_C_CHAR, Guild.AccountName, sizeof(Guild.AccountName), &cbChar);
	SQLBindCol(m_hstmt, 4, SQL_C_SLONG, &Guild.Level, 0, &cbGID);
	SQLBindCol(m_hstmt, 5, SQL_C_SLONG, &Guild.job, 0, &cbGID);
	SQLBindCol(m_hstmt, 6, SQL_C_CHAR, Guild.Memo, sizeof(Guild.Memo), &cbChar);
	SQLBindCol(m_hstmt, 7, SQL_C_SLONG, &Guild.Service, 0, &cbGID);
	SQLBindCol(m_hstmt, 8, SQL_C_SLONG, &Guild.MemberExp, 0, &cbGID);
	SQLBindCol(m_hstmt, 9, SQL_C_SLONG, &Guild.GDID, 0, &cbGID);
	SQLBindCol(m_hstmt, 10, SQL_C_SLONG, &Guild.AID, 0, &cbGID);
	SQLBindCol(m_hstmt, 11, SQL_C_SLONG, &Guild.PositionID, 0, &cbGID);
	Guild.sex = 0;
	Guild.head = 0;
	Guild.headPalette = 0;
//	Guild.status = 0;

	int count = 0;
	buflen = 0;

	while( 1 )
	{
		m_retcode = SQLFetch(m_hstmt);
		if( !SQL_SUCCEEDED(m_retcode) )
			break;

		if( Guild.Level == 0 )
			continue;

		if( count >= MAX_GUILD_MEMBER_LIST )
			break;

		memcpy(&buf[buflen], &Guild, sizeof(Guild));
		buflen += sizeof(Guild);
		++count;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return count;
}


int CIGuildInfoDB::GetGuildAllyInfoDB(unsigned long GDID, int& buflen, char* buf)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return 0;
	}

	SQLLEN cbGID = 0;
	SQLLEN cbChar = SQL_NTS;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GDID, 0, &cbGID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetGuildAllyInfo(?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

	GUILDALLYINFO Guild;
	SQLBindCol(m_hstmt, 1, SQL_C_SLONG, &Guild.GDID, 0, &cbGID);
	SQLBindCol(m_hstmt, 2, SQL_C_SLONG, &Guild.OpponentGDID, 0, &cbGID);
	SQLBindCol(m_hstmt, 3, SQL_C_CHAR, Guild.GuildName, sizeof(Guild.GuildName), &cbChar);
	SQLBindCol(m_hstmt, 4, SQL_C_SLONG, &Guild.Relation, 0, &cbGID);

	int count = 0;
	buflen = 0;

	while( 1 )
	{
		m_retcode = SQLFetch(m_hstmt);
		if( !SQL_SUCCEEDED(m_retcode) )
			break;

		if( count > 6 )
			break;

		memcpy(&buf[buflen], &Guild, sizeof(Guild));
		buflen += sizeof(Guild);
		++count;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return count;
}


BOOL CIGuildInfoDB::GetGuildNoticeDB(unsigned long GDID, GUILDNOTICE& Guild)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLLEN cbGID = 0;
	SQLLEN cbChar = SQL_NTS;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GDID, 0, &cbGID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetGuildNoticeDB(?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

	SQLBindCol(m_hstmt, 1, SQL_C_SLONG, &Guild.GDID, 0, &cbGID);
	SQLBindCol(m_hstmt, 2, SQL_C_CHAR, Guild.Subject, sizeof(Guild.Subject), &cbChar);
	SQLBindCol(m_hstmt, 3, SQL_C_CHAR, Guild.Notice, sizeof(Guild.Notice), &cbChar);

	m_retcode = SQLFetch(m_hstmt);
	if( m_retcode == SQL_NO_DATA )
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


int CIGuildInfoDB::GetGuildBanishInfoDB(unsigned long GDID, int& buflen, char* buf)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return 0;
	}

	SQLLEN cbGID = 0;
	SQLLEN cbChar = SQL_NTS;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GDID, 0, &cbGID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetGuildBanishInfoDB(?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

	GUILDBANISHINFO Guild;
	SQLBindCol(m_hstmt, 1, SQL_C_SLONG, &Guild.GDID, 0, &cbGID);
	SQLBindCol(m_hstmt, 2, SQL_C_CHAR, Guild.MemberName, sizeof(Guild.MemberName), &cbChar);
	SQLBindCol(m_hstmt, 3, SQL_C_CHAR, Guild.MemberAccount, sizeof(Guild.MemberAccount), &cbChar);
	SQLBindCol(m_hstmt, 4, SQL_C_CHAR, Guild.Reason, 40, &cbChar);
	SQLBindCol(m_hstmt, 5, SQL_C_SLONG, &Guild.GID, 0, &cbGID);
	SQLBindCol(m_hstmt, 6, SQL_C_SLONG, &Guild.AID, 0, &cbGID);

	int count = 0;
	buflen = 0;

	while( 1 )
	{
		m_retcode = SQLFetch(m_hstmt);
		if( !SQL_SUCCEEDED(m_retcode) )
			break;

		if( count > 20 )
			break;

		memcpy(&buf[buflen], &Guild, sizeof(Guild));
		buflen += sizeof(Guild);
		++count;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return count;
}


int CIGuildInfoDB::GetGuildMemberPositionDB(unsigned long GDID, int& buflen, char* buf)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return 0;
	}

	SQLLEN cbGID = 0;
	SQLLEN cbChar = SQL_NTS;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GDID, 0, &cbGID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetGuildMPositionDB(?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
		DBTrace(__FILE__, __LINE__, SQL_NULL_HSTMT, m_hstmt);

	GUILDMPOSITION Guild;
	SQLBindCol(m_hstmt, 1, SQL_C_SLONG, &Guild.GDID, 0, &cbGID);
	SQLBindCol(m_hstmt, 2, SQL_C_SLONG, &Guild.Grade, 0, &cbGID);
	SQLBindCol(m_hstmt, 3, SQL_C_CHAR, Guild.PosName, sizeof(Guild.PosName), &cbChar);
	SQLBindCol(m_hstmt, 4, SQL_C_SLONG, &Guild.JoinRight, 0, &cbGID);
	SQLBindCol(m_hstmt, 5, SQL_C_SLONG, &Guild.PenaltyRight, 0, &cbGID);
	SQLBindCol(m_hstmt, 6, SQL_C_SLONG, &Guild.PositionID, 0, &cbGID);
	SQLBindCol(m_hstmt, 7, SQL_C_SLONG, &Guild.Service, 0, &cbGID);

	int count = 0;
	buflen = 0;

	while( 1 )
	{
		m_retcode = SQLFetch(m_hstmt);
		if( !SQL_SUCCEEDED(m_retcode) )
			break;

		if( count > 20 )
			break;

		memcpy(&buf[buflen], &Guild, sizeof(Guild));
		buflen += sizeof(Guild);
		++count;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return count;
}

unsigned long CIGuildInfoDB::GetGDID(unsigned long GID)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return 0;
	}

	SQLLEN cbGID = 0;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GID, 0, &cbGID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetGDIDByGID(?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

	unsigned long VALUE = 0;
	SQLBindCol(m_hstmt, 1, SQL_C_SLONG, &VALUE, 0, &cbGID);

	m_retcode = SQLFetch(m_hstmt);
	if( m_retcode == SQL_NO_DATA )
		VALUE = 0;

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return VALUE;
}


int CIGuildInfoDB::UpdateGuildInfoDB(CIGuildInfo& Guild)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != NULL )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return -1;
	}

	int GDID = Guild.CGuild::GetGDID();
	int Level = Guild.CGuild::GetLevel();
	int MaxUserNum = Guild.CGuild::GetMaxUserNum();
	int Honor = Guild.CGuild::GetHonor();
	int Virtue = Guild.CGuild::GetVirtue();
	int Type = Guild.CGuild::GetType();
	int Class = Guild.CGuild::GetClass();
	int Money = Guild.CGuild::GetMoney();
	int ArenaWin = Guild.CGuild::GetArenaWin();
	int ArenaLose = Guild.CGuild::GetArenaLose();
	int ArenaDrawn = Guild.CGuild::GetArenaDrawn();
	int Exp = Guild.CGuild::GetExp();
	int Point = Guild.CGuild::GetPoint();
	int Emblem = Guild.CGuild::GetEmblemVersion();

	SQLLEN cbInt = 0;
	SQLLEN cbChar = SQL_NTS;

	SQLBindParameter(m_hstmt,  1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GDID, 0, &cbInt);
	SQLBindParameter(m_hstmt,  2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Level, 0, &cbInt);
	SQLBindParameter(m_hstmt,  3, SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_VARCHAR, 24, 0, Guild.CGuild::GetGuildName(), 0, &cbChar);
	SQLBindParameter(m_hstmt,  4, SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_VARCHAR, 24, 0, Guild.CGuild::GetMasterName(), 0, &cbChar);
	SQLBindParameter(m_hstmt,  5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &MaxUserNum, 0, &cbInt);
	SQLBindParameter(m_hstmt,  6, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Honor, 0, &cbInt);
	SQLBindParameter(m_hstmt,  7, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Virtue, 0, &cbInt);
	SQLBindParameter(m_hstmt,  8, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Type, 0, &cbInt);
	SQLBindParameter(m_hstmt,  9, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Class, 0, &cbInt);
	SQLBindParameter(m_hstmt, 10, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Money, 0, &cbInt);
	SQLBindParameter(m_hstmt, 11, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &ArenaWin, 0, &cbInt);
	SQLBindParameter(m_hstmt, 12, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &ArenaLose, 0, &cbInt);
	SQLBindParameter(m_hstmt, 13, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &ArenaDrawn, 0, &cbInt);
	SQLBindParameter(m_hstmt, 14, SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_VARCHAR, 24, 0, Guild.CGuild::GetManageLand(), 0, &cbChar);
	SQLBindParameter(m_hstmt, 15, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Exp, 0, &cbInt);
	SQLBindParameter(m_hstmt, 16, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Emblem, 0, &cbInt);
	SQLBindParameter(m_hstmt, 17, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Point, 0, &cbInt);
	SQLBindParameter(m_hstmt, 18, SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_VARCHAR, 80, 0, Guild.CGuild::GetDesc(), 0, &cbChar);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call UpdateGuildInfo(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return -1;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return 1;
}


int CIGuildInfoDB::UpdateGuildMInfo(GUILDMINFO& Guild)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return -1;
	}

	SQLLEN cbInt = 0;
	SQLLEN cbChar = SQL_NTS;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Guild.GDID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARBINARY, sizeof(Guild.CharName), 0, Guild.CharName, 0, &cbChar);
	SQLBindParameter(m_hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARBINARY, sizeof(Guild.AccountName), 0, Guild.AccountName, 0, &cbChar);
	SQLBindParameter(m_hstmt, 4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Guild.Level, 0, &cbInt);
	SQLBindParameter(m_hstmt, 5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Guild.job, 0, &cbInt);
	SQLBindParameter(m_hstmt, 6, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARBINARY, sizeof(Guild.Memo), 0, Guild.Memo, 0, &cbChar);
	SQLBindParameter(m_hstmt, 7, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Guild.Service, 0, &cbInt);
	SQLBindParameter(m_hstmt, 8, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Guild.MemberExp, 0, &cbInt);
	SQLBindParameter(m_hstmt, 9, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Guild.GDID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 10, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Guild.AID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 11, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Guild.PositionID, 0, &cbInt);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call UpdateGuildMInfo(?,?,?,?,?,?,?,?,?,?,?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return -1;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return 1;
}


int CIGuildInfoDB::InsertGuildMember(GUILDMINFO& Guild)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return -1;
	}

	SQLLEN cbInt = 0;
	SQLLEN cbChar = SQL_NTS;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Guild.GDID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, sizeof(Guild.CharName), 0, Guild.CharName, 0, &cbChar);
	SQLBindParameter(m_hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, sizeof(Guild.AccountName), 0, Guild.AccountName, 0, &cbChar);
	SQLBindParameter(m_hstmt, 4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Guild.Level, 0, &cbInt);
	SQLBindParameter(m_hstmt, 5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Guild.job, 0, &cbInt);
	SQLBindParameter(m_hstmt, 6, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, sizeof(Guild.Memo), 0, Guild.Memo, 0, &cbChar);
	SQLBindParameter(m_hstmt, 7, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Guild.Service, 0, &cbInt);
	SQLBindParameter(m_hstmt, 8, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Guild.MemberExp, 0, &cbInt);
	SQLBindParameter(m_hstmt, 9, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Guild.GDID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 10, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Guild.AID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 11, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Guild.PositionID, 0, &cbInt);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call InsertGuildMInfo(?,?,?,?,?,?,?,?,?,?,?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return -1;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return 1;
}


BOOL CIGuildInfoDB::DeleteGuildMInfo(unsigned long GID)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLLEN cbGRID = 0;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GID, 0, &cbGRID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call DeleteGuildMInfo(?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) && m_retcode != SQL_NO_DATA )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

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


int CIGuildInfoDB::InsertGuildBanishInfo(GUILDBANISHINFO& Guild)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return -1;
	}

	SQLLEN cbInt = 0;
	SQLLEN cbChar = SQL_NTS;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Guild.GDID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, sizeof(Guild.MemberName), 0, Guild.MemberName, 0, &cbChar);
	SQLBindParameter(m_hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, sizeof(Guild.MemberAccount), 0, Guild.MemberAccount, 0, &cbChar);
	SQLBindParameter(m_hstmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 40, 0, Guild.Reason, 0, &cbChar);
	SQLBindParameter(m_hstmt, 5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Guild.GID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 6, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Guild.AID, 0, &cbInt);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call InsertGuildBanishInfo(?,?,?,?,?,?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return -1;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return 1;
}


int CIGuildInfoDB::InsertGuildAlly(GUILDALLYINFO& Guild)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return -1;
	}

	SQLLEN cbInt = 0;
	SQLLEN cbChar = SQL_NTS;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Guild.GDID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Guild.OpponentGDID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, sizeof(Guild.GuildName), 0, Guild.GuildName, 0, &cbChar);
	SQLBindParameter(m_hstmt, 4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Guild.Relation, 0, &cbInt);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call InsertGuildAllyInfo(?,?,?,?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return -1;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return 1;
}


int CIGuildInfoDB::InsertGuildMPosition(GUILDMPOSITION& Guild)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return -1;
	}

	SQLLEN cbInt = 0;
	SQLLEN cbChar = SQL_NTS;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Guild.GDID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Guild.Grade, 0, &cbInt);
	SQLBindParameter(m_hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, sizeof(Guild.PosName), 0, Guild.PosName, 0, &cbChar);
	SQLBindParameter(m_hstmt, 4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Guild.JoinRight, 0, &cbInt);
	SQLBindParameter(m_hstmt, 5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Guild.PenaltyRight, 0, &cbInt);
	SQLBindParameter(m_hstmt, 6, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Guild.PositionID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 7, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Guild.Service, 0, &cbInt);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call InsertGuildMPosition(?,?,?,?,?,?,?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return -1;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return 1;
}


BOOL CIGuildInfoDB::DeleteGuildInfoDB(unsigned long GDID)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLLEN cbGRID = 0;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GDID, 0, &cbGRID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call DeleteGuild(?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

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


BOOL CIGuildInfoDB::DeleteAllGuildAllyInfo(unsigned long GDID)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLLEN cbGRID = 0;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GDID, 0, &cbGRID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call DeleteGuildAllyInfo(?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

	for( int i = 0; i <= 6; ++i )
	{
		m_retcode = SQLFetch(m_hstmt);
		if( !SQL_SUCCEEDED(m_retcode) )
			break;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return TRUE;
}


BOOL CIGuildInfoDB::DeleteAllGuildBanish(unsigned long GDID)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLLEN cbGRID = 0;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GDID, 0, &cbGRID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call DeleteGuildBanishInfo(?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

	for( int i = 0; i <= 40; ++i )
	{
		m_retcode = SQLFetch(m_hstmt);
		if( !SQL_SUCCEEDED(m_retcode) )
			break;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return TRUE;
}


BOOL CIGuildInfoDB::DeleteAllGuildMPosition(unsigned long GDID)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLLEN cbGRID = 0;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GDID, 0, &cbGRID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call DeleteGuildMPosition(?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

	for( int i = 0; i <= 20; ++i )
	{
		m_retcode = SQLFetch(m_hstmt);
		if( !SQL_SUCCEEDED(m_retcode) )
			break;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return TRUE;
}


BOOL CIGuildInfoDB::UpdateMemberPos(unsigned long GDID, GUILD_REG_POSITION_INFO& Guild, int Join, int Penalty)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLLEN cbInt = 0;
	SQLLEN cbChar = SQL_NTS;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GDID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Guild.positionID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Guild.payRate, 0, &cbInt);
	SQLBindParameter(m_hstmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, sizeof(Guild.posName), 0, Guild.posName, 0, &cbChar);
	SQLBindParameter(m_hstmt, 5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Join, 0, &cbInt);
	SQLBindParameter(m_hstmt, 6, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Penalty, 0, &cbInt);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call UpdateGuildMPos(?,?,?,?,?,?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

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


BOOL CIGuildInfoDB::UpdateMemberChangePos(unsigned long GDID, unsigned long GID, unsigned long PosID)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLLEN cbInt = 0;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GDID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &PosID, 0, &cbInt);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call UpdateGuildMInfoPos(?,?,?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

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


BOOL CIGuildInfoDB::UpdateGuildEmblem(unsigned long GDID, unsigned long EmblemVer)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLLEN cbInt = 0;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GDID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &EmblemVer, 0, &cbInt);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call UpdateGuildEmblem(?,?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

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


int CIGuildInfoDB::InsertGuildNotice(unsigned long GDID)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return -1;
	}

	SQLLEN cbInt = 0;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GDID, 0, &cbInt);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call InsertGuildNotice(?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return -1;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return 1;
}


BOOL CIGuildInfoDB::UpdateGuildNotice(unsigned long GDID, char* Subject, char* Notice)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLLEN cbInt = 0;
	SQLLEN cbChar = SQL_NTS;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GDID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 60, 0, Subject, 0, &cbChar);
	SQLBindParameter(m_hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 120, 0, Notice, 0, &cbChar);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call UpdateGuildNotice(?,?,?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

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


BOOL CIGuildInfoDB::DeleteGuildNotice(unsigned long GDID)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLLEN cbGRID = 0;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GDID, 0, &cbGRID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call DeleteGuildNotice(?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

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


BOOL CIGuildInfoDB::DeleteGuildAllyInfo(unsigned long GDID, unsigned long OpponentGDID, int Relation)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLLEN cbGRID = 0;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GDID, 0, &cbGRID);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &OpponentGDID, 0, &cbGRID);
	SQLBindParameter(m_hstmt, 3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Relation, 0, &cbGRID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call DeleteGuildAllyInfo2(?, ?, ?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) && m_retcode != SQL_NO_DATA )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

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


BOOL CIGuildInfoDB::DeleteGuildBanishInfo(unsigned long GDID, unsigned long GID)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLLEN cbGRID = 0;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GDID, 0, &cbGRID);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GID, 0, &cbGRID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call DeleteGuildBanishInfoByGID(?, ?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

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


BOOL CIGuildInfoDB::UpdateGuildMember(unsigned long GDID, unsigned long GID, unsigned long Service, unsigned long Exp, int Level, int Class)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLLEN cbInt = 0;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GDID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Service, 0, &cbInt);
	SQLBindParameter(m_hstmt, 4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Exp, 0, &cbInt);
	SQLBindParameter(m_hstmt, 5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Level, 0, &cbInt);
	SQLBindParameter(m_hstmt, 6, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Class, 0, &cbInt);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call UpdateGuildMember(?,?,?,?,?,?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

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


BOOL CIGuildInfoDB::DeleteGuildSkill(unsigned long GDID)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLLEN cbGRID = 0;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GDID, 0, &cbGRID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call DeleteGuildSkill(?)}", SQL_NTS);
	BOOL bRetValue = ( SQL_SUCCEEDED(m_retcode) );
	if( !bRetValue )
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return bRetValue;
}


bool CIGuildInfoDB::GetGuildAgitDB(std::set<unsigned long>& out_setAgitOwnerGDID)
{
	CDBStatement Statement;
	if( !Statement.CDBStatement::Init(m_hdbc) )
		return false;

	SQLRETURN sqlRet = SQLExecDirectA(Statement, (SQLCHAR*)"{call GetGuildAgitDB}", SQL_NTS);
	if( !SQL_SUCCEEDED(sqlRet) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, Statement);
		return false;
	}

	int AgitGDID;
	SQLBindCol(Statement, 1, SQL_C_SLONG, &AgitGDID, 0, NULL);

	while( 1 )
	{
		SQLRETURN sqlRet2 = SQLFetch(Statement);
		if( sqlRet2 < 0 )
		{
			DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, Statement);
			SQLCloseCursor(Statement);
			return false;
		}

		if( sqlRet2 > 1 )
		{
			if( sqlRet2 != 100 )
			{
				DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, Statement);
				SQLCloseCursor(Statement);
				return false;
			}

			break;
		}

		out_setAgitOwnerGDID.insert(AgitGDID);
	}

	SQLCloseCursor(Statement);
	return true;
}


////////////////////////////////////////


CIGuildSkillDB::CIGuildSkillDB()
{
}


CIGuildSkillDB::~CIGuildSkillDB()
{
}


int CIGuildSkillDB::GetSkill(int GDID, unsigned char* data, int& SkillPoint)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
		return -1;
	}

	SQLLEN cbGDID = 0;
	SQLLEN cbPoint = 0;
	SQLLEN cbequipbin = SQL_NTS;

	int sGDID = GDID;
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &sGDID, 0, &cbGDID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetGuildSkill(?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return 0;
	}

	SQLBindCol(m_hstmt, 1, SQL_C_BINARY, data, 300, &cbequipbin);
	SQLBindCol(m_hstmt, 2, SQL_C_SLONG, &SkillPoint, 0, &cbPoint);

	m_retcode = SQLFetch(m_hstmt);
	if( m_retcode == SQL_NO_DATA )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return 0;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return cbequipbin;
}


BOOL CIGuildSkillDB::UpdateSkill(int GDID, char* data, int skillSize, int SkillPoint)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	char szequipBin[300] = {};
	SQLLEN cbGDID = 0;
	SQLLEN cbequipbin = skillSize;
	SQLLEN cbPoint = 0;

	if( skillSize <= 0 )
	{
		SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GDID, 0, &cbGDID);
		m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"update skill set skillInfo=NULL where GDID = ?", SQL_NTS);
	}
	else
	{
		SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GDID, 0, &cbGDID);
		SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_BINARY, SQL_VARBINARY, skillSize, 0, szequipBin, 0, &cbequipbin);
		SQLBindParameter(m_hstmt, 3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &SkillPoint, 0, &cbPoint);
		memcpy(szequipBin, data, skillSize);
		m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call UpdateGuildSkill(?, ?, ?)}", SQL_NTS);
	}

	BOOL bRetValue = ( SQL_SUCCEEDED(m_retcode) );
	if( !bRetValue )
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return bRetValue;
}


void CIGuildSkillDB::InsertSkill(int GDID, int Point)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return;
	}

	SQLLEN cbInt = 0;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GDID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Point, 0, &cbInt);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call InsertGuildSkill(?, ?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}
