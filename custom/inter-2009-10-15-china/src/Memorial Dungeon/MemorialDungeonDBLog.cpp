#include "Memorial Dungeon/MemorialDungeonDBLog.h"
#include "N2System/ODBC(open database connectivity)/N2ODBCHandler.h"
#include <sql.h>
#include <sqlext.h>


CMemorialDungeonDBLog::CMemorialDungeonDBLog(const enum CMemorialDungeonDBLog::enumTYPE in_Type, const mystd::string in_MemorialDungeonName, const mystd::string in_PartyName, const int in_PartyID, const int in_CreateZSID) // line 22-25
: m_Type(in_Type), m_MemorialDungeonName(in_MemorialDungeonName), m_PartyName(in_PartyName), m_PartyID(in_PartyID), m_CreateZSID(in_CreateZSID)
{
	m_bOK = true;
}


CMemorialDungeonDBLog::~CMemorialDungeonDBLog(void) // line 28-30
{
}


//hook_method<bool (CMemorialDungeonDBLog::*)(void)> CMemorialDungeonDBLog::_isOK(SERVER, "CMemorialDungeonDBLog::isOK");
bool CMemorialDungeonDBLog::isOK(void) // line ??
{
//	return (this->*_isOK);

	return m_bOK;
}


hook_method<bool (CMemorialDungeonDBLog::*)(N2ODBCCtrl& in_ODBCCtrl)> CMemorialDungeonDBLog::_Run(SERVER, "CMemorialDungeonDBLog::Run");
bool CMemorialDungeonDBLog::Run(N2ODBCCtrl& in_ODBCCtrl) // line 35-56
{
	return (this->*_Run)(in_ODBCCtrl);

	N2ODBCHandler Handler(in_ODBCCtrl);

	int cbInt = 0;
	int cbChar = SQL_NTS;
	Handler.N2ODBCHandler::BindParameter(1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER,  0, 0, (SQLPOINTER)&m_Type,                       0, (SQLLEN*)&cbInt);
	Handler.N2ODBCHandler::BindParameter(2, SQL_PARAM_INPUT, SQL_CHAR,    SQL_VARCHAR, 61, 0, (SQLPOINTER)m_MemorialDungeonName.c_str(), 0, (SQLLEN*)&cbChar);
	Handler.N2ODBCHandler::BindParameter(3, SQL_PARAM_INPUT, SQL_CHAR,    SQL_VARCHAR, 24, 0, (SQLPOINTER)m_PartyName.c_str(),           0, (SQLLEN*)&cbChar);
	Handler.N2ODBCHandler::BindParameter(4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER,  0, 0, (SQLPOINTER)&m_PartyID,                    0, (SQLLEN*)&cbInt);
	Handler.N2ODBCHandler::BindParameter(5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER,  0, 0, (SQLPOINTER)&m_CreateZSID,                 0, (SQLLEN*)&cbInt);

	if( !SQL_SUCCEEDED(Handler.N2ODBCHandler::ExecDirect("{call usp_mdungeonlog_add(?, ?, ?, ?, ?)}")) )
	{
		Handler.N2ODBCHandler::OutputErrorString(".\\Memorial Dungeon\\MemorialDungeonDBLog.cpp", 51, 0);
		return false;
	}

	return true;
}
