#pragma once
#include "DatabaseLog.h"
#include "struct.hpp"
struct SPETLOG;


class CPetLog : public CDatabaseLog<SPETLOG*>
{
	/* this+0 */ public: //CDatabaseLog<SPETLOG*> baseclass_0;

	public: void CPetLog::AddPetLog(const unsigned long in_GID, const PET_PROPERTY in_petProperty, const char* in_mapName, const int in_logType);
	public: virtual void CPetLog::ConnectToDatabase(const char* Log);
	private: virtual int CPetLog::SaveToDatabase(SQLHSTMT hStmt, SPETLOG* pLog);

private:
	static hook_method<void (CPetLog::*)(const unsigned long in_GID, const PET_PROPERTY in_petProperty, const char* in_mapName, const int in_logType)> CPetLog::_AddPetLog;
	static hook_method<void (CPetLog::*)(const char* Log)> CPetLog::_ConnectToDatabase;
	static hook_method<int (CPetLog::*)(SQLHSTMT hStmt, SPETLOG* pLog)> CPetLog::_SaveToDatabase;
};
