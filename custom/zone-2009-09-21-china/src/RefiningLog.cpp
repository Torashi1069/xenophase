#include "RefiningLog.h"
#include "globals.hpp"


hook_method<void (CRefiningLog::*)(CPC* pPC, BYTE bySuccess, DWORD dwItemID, DWORD dwItemLevel, __int64 dwItemSerialcode)> CRefiningLog::_AddRefiningLogV2(SERVER, "CRefiningLog::AddRefiningLogV2");
void CRefiningLog::AddRefiningLogV2(CPC* pPC, BYTE bySuccess, DWORD dwItemID, DWORD dwItemLevel, __int64 dwItemSerialcode) // line 25
{
	return (this->*_AddRefiningLogV2)(pPC, bySuccess, dwItemID, dwItemLevel, dwItemSerialcode);

	//TODO
}


hook_method<void (CRefiningLog::*)(const char* Log)> CRefiningLog::_ConnectToDatabase(SERVER, "CRefiningLog::ConnectToDatabase");
void CRefiningLog::ConnectToDatabase(const char* Log) // line ??
{
	return (this->*_ConnectToDatabase)(Log);

	this->CExtendedODBC::Connect("Loger", g_dbPWD, Log, 0, "");
}


hook_method<int (CRefiningLog::*)(SQLHSTMT in_hStmt, SREFININGLOG* pLog)> CRefiningLog::_SaveToDatabase(SERVER, "CRefiningLog::SaveToDatabase");
int CRefiningLog::SaveToDatabase(SQLHSTMT in_hStmt, SREFININGLOG* pLog) // line 105
{
	return (this->*_SaveToDatabase)(in_hStmt, pLog);

	//TODO
}
