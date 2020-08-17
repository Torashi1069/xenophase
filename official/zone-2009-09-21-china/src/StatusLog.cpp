#include "StatusLog.h"
#include "globals.hpp"


hook_method<void (CStatusLog::*)(CCharacter* CH, DWORD dwStr, DWORD dwAgi, DWORD dwVit, DWORD dwInt, DWORD dwDex, DWORD dwLuk, DWORD dwJobpoint)> CStatusLog::_AddStatusLog(SERVER, "CStatusLog::AddStatusLog");
void CStatusLog::AddStatusLog(CCharacter* CH, DWORD dwStr, DWORD dwAgi, DWORD dwVit, DWORD dwInt, DWORD dwDex, DWORD dwLuk, DWORD dwJobpoint) // line 20
{
	return (this->*_AddStatusLog)(CH, dwStr, dwAgi, dwVit, dwInt, dwDex, dwLuk, dwJobpoint);

	//TODO
}


hook_method<void (CStatusLog::*)(const char* Log)> CStatusLog::_ConnectToDatabase(SERVER, "CStatusLog::ConnectToDatabase");
void CStatusLog::ConnectToDatabase(const char* Log) // line ??
{
	return (this->*_ConnectToDatabase)(Log);

	this->CExtendedODBC::Connect("Loger", g_dbPWD, Log, 0, "");
}


hook_method<int (CStatusLog::*)(SQLHSTMT hStmt, SSTATUSLOG* pLog)> CStatusLog::_SaveToDatabase(SERVER, "CStatusLog::SaveToDatabase");
int CStatusLog::SaveToDatabase(SQLHSTMT hStmt, SSTATUSLOG* pLog) // line 96
{
	return (this->*_SaveToDatabase)(hStmt, pLog);

	//TODO
}
