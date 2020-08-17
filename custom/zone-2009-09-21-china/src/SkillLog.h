#pragma once
#include "DatabaseLog.h"
struct SSKILLLOG;
class CPC;


class CSkillLog : public CDatabaseLog<SSKILLLOG*>
{
	/* this+0 */ public: //CDatabaseLog<SSKILLLOG*> baseclass_0;

	public: void CSkillLog::AddSkillLog(CPC* pPC, DWORD dwSkillID, DWORD dwSkillLevel, DWORD dwExtraSkillPoint);
	public: virtual void CSkillLog::ConnectToDatabase(const char* Log);
	private: virtual int CSkillLog::SaveToDatabase(SQLHSTMT hStmt, SSKILLLOG* pLog);

private:
	static hook_method<void (CSkillLog::*)(CPC* pPC, DWORD dwSkillID, DWORD dwSkillLevel, DWORD dwExtraSkillPoint)> CSkillLog::_AddSkillLog;
	static hook_method<void (CSkillLog::*)(const char* Log)> CSkillLog::_ConnectToDatabase;
	static hook_method<int (CSkillLog::*)(SQLHSTMT hStmt, SSKILLLOG* pLog)> CSkillLog::_SaveToDatabase;
};
