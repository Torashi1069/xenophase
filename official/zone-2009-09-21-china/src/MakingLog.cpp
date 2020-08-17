#include "MakingLog.h"
#include "globals.hpp"


hook_method<void (CMakingLog::*)(CPC* pPC, BYTE bySuccess, DWORD dwItemID, DWORD m_dwMaterial1, DWORD m_dwMaterial2, DWORD m_dwMaterial3)> CMakingLog::_AddMakingLog(SERVER, "CMakingLog::AddMakingLog");
void CMakingLog::AddMakingLog(CPC* pPC, BYTE bySuccess, DWORD dwItemID, DWORD m_dwMaterial1, DWORD m_dwMaterial2, DWORD m_dwMaterial3) // line 16
{
	return (this->*_AddMakingLog)(pPC, bySuccess, dwItemID, m_dwMaterial1, m_dwMaterial2, m_dwMaterial3);

	//TODO
}


hook_method<void (CMakingLog::*)(const char* Log)> CMakingLog::_ConnectToDatabase(SERVER, "CMakingLog::ConnectToDatabase");
void CMakingLog::ConnectToDatabase(const char* Log) // line ??
{
	return (this->*_ConnectToDatabase)(Log);

	this->CExtendedODBC::Connect("Loger", g_dbPWD, Log, 0, "");
}


hook_method<int (CMakingLog::*)(SQLHSTMT hStmt, SMAKINGLOG* pLog)> CMakingLog::_SaveToDatabase(SERVER, "CMakingLog::SaveToDatabase");
int CMakingLog::SaveToDatabase(SQLHSTMT hStmt, SMAKINGLOG* pLog) // line 50
{
	return (this->*_SaveToDatabase)(hStmt, pLog);

	//TODO
}
