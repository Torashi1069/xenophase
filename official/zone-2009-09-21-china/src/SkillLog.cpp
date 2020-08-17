#include "SkillLog.h"
#include "globals.hpp"


hook_method<void (CSkillLog::*)(CPC* pPC, DWORD dwSkillID, DWORD dwSkillLevel, DWORD dwExtraSkillPoint)> CSkillLog::_AddSkillLog(SERVER, "CSkillLog::AddSkillLog");
void CSkillLog::AddSkillLog(CPC* pPC, DWORD dwSkillID, DWORD dwSkillLevel, DWORD dwExtraSkillPoint) // line 16
{
	return (this->*_AddSkillLog)(pPC, dwSkillID, dwSkillLevel, dwExtraSkillPoint);

	//TODO
}


hook_method<void (CSkillLog::*)(const char* Log)> CSkillLog::_ConnectToDatabase(SERVER, "CSkillLog::ConnectToDatabase");
void CSkillLog::ConnectToDatabase(const char* Log) // line ??
{
	return (this->*_ConnectToDatabase)(Log);

	this->CExtendedODBC::Connect("Loger", g_dbPWD, Log, 0, "");
}


hook_method<int (CSkillLog::*)(SQLHSTMT hStmt, SSKILLLOG* pLog)> CSkillLog::_SaveToDatabase(SERVER, "CSkillLog::SaveToDatabase");
int CSkillLog::SaveToDatabase(SQLHSTMT hStmt, SSKILLLOG* pLog) // line 48
{
	return (this->*_SaveToDatabase)(hStmt, pLog);

	//TODO
}
