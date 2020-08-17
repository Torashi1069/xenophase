#pragma once
#include "DatabaseLog.h"
struct SSTATUSLOG;
class CCharacter;


class CStatusLog : CDatabaseLog<SSTATUSLOG*>
{
	/* this+0 */ public: //CDatabaseLog<SSTATUSLOG*> baseclass_0;

	public: void CStatusLog::AddStatusLog(CCharacter* CH, DWORD dwStr, DWORD dwAgi, DWORD dwVit, DWORD dwInt, DWORD dwDex, DWORD dwLuk, DWORD dwJobpoint);
	public: virtual void CStatusLog::ConnectToDatabase(const char* Log);
	private: virtual int CStatusLog::SaveToDatabase(SQLHSTMT hStmt, SSTATUSLOG* pLog);

private:
	static hook_method<void (CStatusLog::*)(CCharacter* CH, DWORD dwStr, DWORD dwAgi, DWORD dwVit, DWORD dwInt, DWORD dwDex, DWORD dwLuk, DWORD dwJobpoint)> CStatusLog::_AddStatusLog;
	static hook_method<void (CStatusLog::*)(const char* Log)> CStatusLog::_ConnectToDatabase;
	static hook_method<int (CStatusLog::*)(SQLHSTMT hStmt, SSTATUSLOG* pLog)> CStatusLog::_SaveToDatabase;
};
