#pragma once
#include "DatabaseLog.h"
struct SCOMPOSITIONLOG;
class CPC;


class CCompositionLog : public CDatabaseLog<SCOMPOSITIONLOG*>
{
	/* this+0 */ public: //CDatabaseLog baseclass_0;

	public: void CCompositionLog::AddCompositionLog(CPC* pPC, DWORD dwCardID, DWORD dwSlot1, DWORD dwSlot2, DWORD dwSlot3, DWORD dwSlot4, unsigned short equipItem, unsigned long serial);
	public: virtual void CCompositionLog::ConnectToDatabase(const char* Log);
	private: virtual int CCompositionLog::SaveToDatabase(SQLHSTMT hStmt, SCOMPOSITIONLOG* pLog);

private:
	static hook_method<void (CCompositionLog::*)(CPC* pPC, DWORD dwCardID, DWORD dwSlot1, DWORD dwSlot2, DWORD dwSlot3, DWORD dwSlot4, unsigned short equipItem, unsigned long serial)> CCompositionLog::_AddCompositionLog;
	static hook_method<void (CCompositionLog::*)(const char* Log)> CCompositionLog::_ConnectToDatabase;
	static hook_method<int (CCompositionLog::*)(SQLHSTMT hStmt, SCOMPOSITIONLOG* pLog)> CCompositionLog::_SaveToDatabase;
};
