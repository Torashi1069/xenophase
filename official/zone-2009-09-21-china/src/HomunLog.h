#pragma once
#include "DatabaseLog.h"
struct SHOMUNLOG;
struct HOMUN_DBINFO;
class CNpcHomun;


class CHomunLog : CDatabaseLog<SHOMUNLOG*>
{
	/* this+0 */ public: //CDatabaseLog<SHOMUNLOG*> baseclass_0;

	public: void CHomunLog::AddHomunLog(CNpcHomun* homun, HOMUN_DBINFO* pDBInfo, short desc);
	public: virtual void CHomunLog::ConnectToDatabase(const char* Log);
	private: virtual int CHomunLog::SaveToDatabase(SQLHSTMT hStmt, SHOMUNLOG* pLog);

private:
	static hook_method<void (CHomunLog::*)(CNpcHomun* homun, HOMUN_DBINFO* pDBInfo, short desc)> CHomunLog::_AddHomunLog;
	static hook_method<void (CHomunLog::*)(const char* Log)> CHomunLog::_ConnectToDatabase;
	static hook_method<int (CHomunLog::*)(SQLHSTMT hStmt, SHOMUNLOG* pLog)> CHomunLog::_SaveToDatabase;
};
