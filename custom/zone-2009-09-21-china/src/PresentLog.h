#pragma once
#include "DatabaseLog.h"
struct SPRESENTLOG;
class CPC;


class CPresentLog : CDatabaseLog<SPRESENTLOG*>
{
	/* this+0 */ public: //CDatabaseLog<SPRESENTLOG*> baseclass_0;

	public: void CPresentLog::AddPresentLog(CPC* pPC, DWORD dwItemID);
	public: virtual void CPresentLog::ConnectToDatabase(const char* Log);
	private: virtual int CPresentLog::SaveToDatabase(SQLHSTMT hStmt, SPRESENTLOG* pLog);

private:
	static hook_method<void (CPresentLog::*)(CPC* pPC, DWORD dwItemID)> CPresentLog::_AddPresentLog;
	static hook_method<void (CPresentLog::*)(const char* Log)> CPresentLog::_ConnectToDatabase;
	static hook_method<int (CPresentLog::*)(SQLHSTMT hStmt, SPRESENTLOG* pLog)> CPresentLog::_SaveToDatabase;
};
