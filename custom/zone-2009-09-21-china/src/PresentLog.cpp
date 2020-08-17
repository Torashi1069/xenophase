#include "PresentLog.h"
#include "globals.hpp"


hook_method<void (CPresentLog::*)(CPC* pPC, DWORD dwItemID)> CPresentLog::_AddPresentLog(SERVER, "CPresentLog::AddPresentLog");
void CPresentLog::AddPresentLog(CPC* pPC, DWORD dwItemID) // line 16
{
	return (this->*_AddPresentLog)(pPC, dwItemID);

	//TODO
}


hook_method<void (CPresentLog::*)(const char* Log)> CPresentLog::_ConnectToDatabase(SERVER, "CPresentLog::ConnectToDatabase");
void CPresentLog::ConnectToDatabase(const char* Log) // line ??
{
	return (this->*_ConnectToDatabase)(Log);

	this->CExtendedODBC::Connect("Loger", g_dbPWD, Log, 0, "");
}


hook_method<int (CPresentLog::*)(SQLHSTMT hStmt, SPRESENTLOG* pLog)> CPresentLog::_SaveToDatabase(SERVER, "CPresentLog::SaveToDatabase");
int CPresentLog::SaveToDatabase(SQLHSTMT hStmt, SPRESENTLOG* pLog) // line 46
{
	return (this->*_SaveToDatabase)(hStmt, pLog);

	//TODO
}
