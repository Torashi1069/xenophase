#pragma once
#include "DatabaseLog.h"
struct SREFININGLOG;
class CPC;


class CRefiningLog : public CDatabaseLog<SREFININGLOG*>
{
	/* this+0 */ public: //CDatabaseLog<SREFININGLOG*> baseclass_0;

	public: void CRefiningLog::AddRefiningLogV2(CPC* pPC, BYTE bySuccess, DWORD dwItemID, DWORD dwItemLevel, __int64 dwItemSerialcode);
	public: virtual void CRefiningLog::ConnectToDatabase(const char* Log);
	private: virtual int CRefiningLog::SaveToDatabase(SQLHSTMT in_hStmt, SREFININGLOG* pLog);

private:
	static hook_method<void (CRefiningLog::*)(CPC* pPC, BYTE bySuccess, DWORD dwItemID, DWORD dwItemLevel, __int64 dwItemSerialcode)> CRefiningLog::_AddRefiningLogV2;
	static hook_method<void (CRefiningLog::*)(const char* Log)> CRefiningLog::_ConnectToDatabase;
	static hook_method<int (CRefiningLog::*)(SQLHSTMT in_hStmt, SREFININGLOG* pLog)> CRefiningLog::_SaveToDatabase;
};
