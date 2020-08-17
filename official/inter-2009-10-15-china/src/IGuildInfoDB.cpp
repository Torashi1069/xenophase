#include "IGuildInfoDB.h"
#include "Guild.h"
#include "ErrorLog.h"
#include "globals.hpp"
#include <sqlext.h>


hook_method<unsigned long (CIGuildInfoDB::*)(unsigned long GID)> CIGuildInfoDB::_GetGDID(SERVER, "CIGuildInfoDB::GetGDID");
unsigned long CIGuildInfoDB::GetGDID(unsigned long GID)
{
	return (this->*_GetGDID)(GID);

	//TODO
}


hook_method<int (CIGuildInfoDB::*)(GUILDMINFO& Guild)> CIGuildInfoDB::_InsertGuildMember(SERVER, "CIGuildInfoDB::InsertGuildMember");
int CIGuildInfoDB::InsertGuildMember(GUILDMINFO& Guild)
{
	return (this->*_InsertGuildMember)(Guild);

	//TODO
}


hook_method<int (CIGuildSkillDB::*)(int GDID, unsigned char* data, int& SkillPoint)> CIGuildSkillDB::_GetSkill(SERVER, "CIGuildSkillDB::GetSkill");
int CIGuildSkillDB::GetSkill(int GDID, unsigned char* data, int& SkillPoint)
{
	return (this->*_GetSkill)(GDID, data, SkillPoint);

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( m_retcode != SQL_SUCCESS && m_retcode != SQL_SUCCESS_WITH_INFO )
	{
		g_errorLogs.CErrorLog::CriticalErrorLogFmt(".\\IGuildInfoDB.cpp", 1595, "error");

		if( m_hstmt != NULL )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return -1;
	}

	int sGDID = GDID;
	SQLINTEGER cbGDID = 0;
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, sizeof(int), 0, 0, &sGDID, 0, &cbGDID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetGuildSkill(?)}", SQL_NTS);

	SQLINTEGER cbequipbin = SQL_NTS;
	SQLBindCol(m_hstmt, 1, SQL_BINARY, data, GUILDSKILL_BUFSIZE, &cbequipbin);

	SQLINTEGER cbPoint = 0;
	SQLBindCol(m_hstmt, 2, SQL_C_SLONG, (SQLPOINTER*)&SkillPoint, 0, &cbPoint);

	if( m_retcode != SQL_SUCCESS && m_retcode != SQL_SUCCESS_WITH_INFO )
	{
		DBTrace(".\\IGuildInfoDB.cpp", 1629, SQL_HANDLE_STMT, m_hstmt);

		SQLCloseCursor(m_hstmt);

		if( m_hstmt != NULL )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return 0;
	}

	m_retcode = SQLFetch(m_hstmt);
	if( m_retcode == SQL_NO_DATA )
	{
		SQLCloseCursor(m_hstmt);

		if( m_hstmt != NULL )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return 0;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != NULL )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return cbequipbin;
}


hook_method<int (CIGuildSkillDB::*)(int GDID, char* data, int skillSize, int SkillPoint)> CIGuildSkillDB::_UpdateSkill(SERVER, "CIGuildSkillDB::UpdateSkill");
int CIGuildSkillDB::UpdateSkill(int GDID, char* data, int skillSize, int SkillPoint)
{
	return (this->*_UpdateSkill)(GDID, data, skillSize, SkillPoint);

	//TODO
}


hook_method<void (CIGuildSkillDB::*)(int GDID, int Point)> CIGuildSkillDB::_InsertSkill(SERVER, "CIGuildSkillDB::InsertSkill");
void CIGuildSkillDB::InsertSkill(int GDID, int Point)
{
	return (this->*_InsertSkill)(GDID, Point);

	//TODO
}
