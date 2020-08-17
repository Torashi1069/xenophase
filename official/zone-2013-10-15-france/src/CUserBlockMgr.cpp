#include "CUserBlockMgr.h"
#include "ZoneProcess.h"
#include "shared/CDateTime.h"
#include "shared/NCriticalErrorLog.h"


CUserBlockMgr::CUserBlockMgr()
{
}


CUserBlockMgr::~CUserBlockMgr()
{
}


void CUserBlockMgr::AddR2(const CUserBlock::enumTYPE in_Type, const CUserBlock::enumREASON in_Reason, const unsigned long in_AID, const int in_Second)
{
	if( in_Second <= 0 )
		return;

	CUserBlock* pLog = new(std::nothrow) CUserBlock(in_Type, in_AID, in_Reason, in_Second);
	if( pLog == NULL )
		return;

	this->CDatabaseLog<CUserBlock*>::AddLog(pLog);
}


void CUserBlockMgr::ConnectToDatabase(const char* in_DSN)
{
	this->CExtendedODBC::Connect(in_DSN, g_GlobaldbPWD);
}


BOOL CUserBlockMgr::SaveToDatabase(SQLHSTMT in_hStmt, CUserBlock* in_cpUserBlock)
{
	if( in_cpUserBlock == NULL )
		return TRUE;

	SQLINTEGER cbInt = 0;
	SQLBindParameter(in_hStmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, 4, 0, 0, &in_cpUserBlock->m_Type, 0, &cbInt);
	SQLBindParameter(in_hStmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, 4, 0, 0, &in_cpUserBlock->m_AID, 0, &cbInt);
	SQLBindParameter(in_hStmt, 3, SQL_PARAM_INPUT, SQL_C_SLONG, 4, 0, 0, &in_cpUserBlock->m_Reason, 0, &cbInt);
	TIMESTAMP_STRUCT EndDate = CDateTime(in_cpUserBlock->m_EndDate);
	SQLINTEGER cbDateTime = sizeof(EndDate);
	SQLBindParameter(in_hStmt, 4, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 22, 0, &EndDate, cbDateTime, &cbDateTime);

	if( !SQL_SUCCEEDED(SQLExecDirectA(in_hStmt, (SQLCHAR*)"{call usp_blockedUser_insert( ?, ?, ?, ?)}", SQL_NTS)) )
	{
		char szSQLError[256] = {};
		this->CExtendedODBC::GetErrorString(in_hStmt, szSQLError);
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s %s", "CUserBlockMgr::SaveToDatabase", szSQLError);
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s", "{call usp_blockedUser_insert( ?, ?, ?, ?)}");
	}

	operator delete(in_cpUserBlock);
	return TRUE;
}
