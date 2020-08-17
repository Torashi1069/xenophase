#include "Memorial Dungeon/MemorialDungeonDBLog.h"
#include "shared/N2System/ODBC(open database connectivity)/N2ODBCCtrl.h"
#include "shared/N2System/ODBC(open database connectivity)/N2ODBCHandler.h"


CMemorialDungeonDBLog::CMemorialDungeonDBLog(const enumTYPE in_Type, const std::string in_MemorialDungeonName, const std::string in_PartyName, const int in_PartyID, const int in_CreateZSID)
: N2DBLog(), m_Type(in_Type), m_MemorialDungeonName(in_MemorialDungeonName), m_PartyName(in_PartyName), m_PartyID(in_PartyID), m_CreateZSID(in_CreateZSID), m_bOK(true)
{
}


CMemorialDungeonDBLog::~CMemorialDungeonDBLog()
{
}


bool CMemorialDungeonDBLog::isOK() const
{
	return m_bOK;
}


bool CMemorialDungeonDBLog::Run(N2ODBCCtrl& in_ODBCCtrl)
{
	N2ODBCHandler Handler(in_ODBCCtrl);

	SQLINTEGER cbInt = 0;
	SQLINTEGER cbChar = SQL_NTS;

	Handler.N2ODBCHandler::BindParameter(1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, (SQLPOINTER*)&m_Type, 0, &cbInt);
	Handler.N2ODBCHandler::BindParameter(2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 61, 0, (SQLPOINTER*)m_MemorialDungeonName.c_str(), 0, &cbChar);
	Handler.N2ODBCHandler::BindParameter(3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 24, 0, (SQLPOINTER*)m_PartyName.c_str(), 0, &cbChar);
	Handler.N2ODBCHandler::BindParameter(4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, (SQLPOINTER*)&m_PartyID, 0, &cbInt);
	Handler.N2ODBCHandler::BindParameter(5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, (SQLPOINTER*)&m_CreateZSID, 0, &cbInt);

	if( !SQL_SUCCEEDED(Handler.N2ODBCHandler::ExecDirect("{call usp_mdungeonlog_add(?, ?, ?, ?, ?)}")) )
	{
		Handler.N2ODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
		return false;
	}

	return true;
}
