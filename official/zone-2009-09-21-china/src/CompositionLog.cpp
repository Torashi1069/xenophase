#include "CompositionLog.h"
#include "globals.hpp"


hook_method<void (CCompositionLog::*)(CPC* pPC, DWORD dwCardID, DWORD dwSlot1, DWORD dwSlot2, DWORD dwSlot3, DWORD dwSlot4, unsigned short equipItem, unsigned long serial)> CCompositionLog::_AddCompositionLog(SERVER, "CCompositionLog::AddCompositionLog");
void CCompositionLog::AddCompositionLog(CPC* pPC, DWORD dwCardID, DWORD dwSlot1, DWORD dwSlot2, DWORD dwSlot3, DWORD dwSlot4, unsigned short equipItem, unsigned long serial) // line 21
{
	return (this->*_AddCompositionLog)(pPC, dwCardID, dwSlot1, dwSlot2, dwSlot3, dwSlot4, equipItem, serial);

	//TODO
}


hook_method<void (CCompositionLog::*)(const char* Log)> CCompositionLog::_ConnectToDatabase(SERVER, "CCompositionLog::ConnectToDatabase");
void CCompositionLog::ConnectToDatabase(const char* Log) // line ??
{
	return (this->*_ConnectToDatabase)(Log);

	this->CExtendedODBC::Connect("Loger", g_dbPWD, Log, 0, "");
}


hook_method<int (CCompositionLog::*)(SQLHSTMT hStmt, SCOMPOSITIONLOG* pLog)> CCompositionLog::_SaveToDatabase(SERVER, "CCompositionLog::SaveToDatabase");
int CCompositionLog::SaveToDatabase(SQLHSTMT hStmt, SCOMPOSITIONLOG* pLog) // line 57
{
	return (this->*_SaveToDatabase)(hStmt, pLog);

	//TODO
}
