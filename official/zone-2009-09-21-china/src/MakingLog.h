#pragma once
#include "DatabaseLog.h"
struct SMAKINGLOG;
class CPC;


class CMakingLog : public CDatabaseLog<SMAKINGLOG*>
{
	/* this+0 */ public: //CDatabaseLog<SMAKINGLOG*> baseclass_0;

	public: void CMakingLog::AddMakingLog(CPC* pPC, BYTE bySuccess, DWORD dwItemID, DWORD m_dwMaterial1, DWORD m_dwMaterial2, DWORD m_dwMaterial3);
	public: virtual void CMakingLog::ConnectToDatabase(const char* Log);
	private: virtual int CMakingLog::SaveToDatabase(SQLHSTMT hStmt, SMAKINGLOG* pLog);

private:
	static hook_method<void (CMakingLog::*)(CPC* pPC, BYTE bySuccess, DWORD dwItemID, DWORD m_dwMaterial1, DWORD m_dwMaterial2, DWORD m_dwMaterial3)> CMakingLog::_AddMakingLog;
	static hook_method<void (CMakingLog::*)(const char* Log)> CMakingLog::_ConnectToDatabase;
	static hook_method<int (CMakingLog::*)(SQLHSTMT hStmt, SMAKINGLOG* pLog)> CMakingLog::_SaveToDatabase;
};
