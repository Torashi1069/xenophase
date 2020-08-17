#include "HomunLog.h"
#include "globals.hpp"


hook_method<void (CHomunLog::*)(CNpcHomun* homun, HOMUN_DBINFO* pDBInfo, short desc)> CHomunLog::_AddHomunLog(SERVER, "CHomunLog::AddHomunLog");
void CHomunLog::AddHomunLog(CNpcHomun* homun, HOMUN_DBINFO* pDBInfo, short desc) // line 21
{
	return (this->*_AddHomunLog)(homun, pDBInfo, desc);

	//TODO
}


hook_method<void (CHomunLog::*)(const char* Log)> CHomunLog::_ConnectToDatabase(SERVER, "CHomunLog::ConnectToDatabase");
void CHomunLog::ConnectToDatabase(const char* Log) // line ??
{
	return (this->*_ConnectToDatabase)(Log);

	this->CExtendedODBC::Connect("Loger", g_dbPWD, Log, 0, "");
}


hook_method<int (CHomunLog::*)(SQLHSTMT hStmt, SHOMUNLOG* pLog)> CHomunLog::_SaveToDatabase(SERVER, "CHomunLog::SaveToDatabase");
int CHomunLog::SaveToDatabase(SQLHSTMT hStmt, SHOMUNLOG* pLog) // line 76
{
	return (this->*_SaveToDatabase)(hStmt, pLog);

	//TODO
}
