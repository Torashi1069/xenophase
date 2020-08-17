#include "N2System/ODBC(open database connectivity)/N2ODBCCtrl.h"
#include "ErrorLog.h"
#include "globals.hpp"
#include <sql.h>
#include <sqlext.h>


N2ODBCCtrl::N2ODBCCtrl(void) // line 14-18
{
	m_bConnect = false;
	m_bOK = false;

	if( this->N2ODBCCtrl::Init() )
		m_bOK = true;
}


N2ODBCCtrl::~N2ODBCCtrl(void) // line 23-36
{
	if( m_hDbc != SQL_NULL_HDBC )
	{
		SQLDisconnect(m_hDbc);
		SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
		m_hDbc = SQL_NULL_HDBC;
	}

	if( m_hEnv != SQL_NULL_HENV )
	{
		SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);
		m_hEnv = SQL_NULL_HENV;
	}
}


hook_method<bool (N2ODBCCtrl::*)(void) const> N2ODBCCtrl::_isOK(SERVER, "N2ODBCCtrl::isOK");
bool N2ODBCCtrl::isOK(void) const // line 39-41
{
	return (this->*_isOK)();

	return m_bOK;
}


hook_method<bool (N2ODBCCtrl::*)(void)> N2ODBCCtrl::_Init(SERVER, "N2ODBCCtrl::Init");
bool N2ODBCCtrl::Init(void) // line 45-58
{
	return (this->*_Init)();

	m_hEnv = SQL_NULL_HENV;
	m_hDbc = SQL_NULL_HDBC;

	if( !SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv)) )
		return false;
	
	if( !SQL_SUCCEEDED(SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER)) )
		return false;

	m_bConnect = false;
	return true;
}


hook_method<bool (N2ODBCCtrl::*)(const mystd::string in_strConnectionStr)> N2ODBCCtrl::_Connect(SERVER, "N2ODBCCtrl::Connect");
bool N2ODBCCtrl::Connect(const mystd::string in_strConnectionStr) // line 61-88
{
	return (this->*_Connect)(in_strConnectionStr);

	if( m_bConnect )
		return false;

	if( !SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDbc)) )
		return false;

	char CompleteConnectionString[1024];
	memset(CompleteConnectionString, '\0', sizeof(CompleteConnectionString));

	if( !SQL_SUCCEEDED(SQLDriverConnectA(m_hDbc, NULL, (SQLCHAR*)in_strConnectionStr.c_str(), SQL_NTS, (SQLCHAR*)CompleteConnectionString, countof(CompleteConnectionString), NULL, NULL)) )
	{
		SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
		m_hDbc = SQL_NULL_HDBC;
		return false;
	}

	m_bConnect = true;
	return true;
}


hook_method<void (N2ODBCCtrl::*)(void)> N2ODBCCtrl::_Disconnect(SERVER, "N2ODBCCtrl::Disconnect");
void N2ODBCCtrl::Disconnect(void) // line 91-99
{
	return (this->*_Disconnect)();

	if( m_hDbc != SQL_NULL_HDBC )
	{
		SQLDisconnect(m_hDbc);
		SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
		m_hDbc = SQL_NULL_HDBC;
	}

	m_bConnect = false;
}


hook_method<SQLHDBC (N2ODBCCtrl::*)(void)> N2ODBCCtrl::_operator_SQLHDBC(SERVER, "??BN2ODBCCtrl@@QAEPAXXZ");
N2ODBCCtrl::operator SQLHDBC(void) // line 27 (N2System/ODBC(open database connectivity)/N2ODBCCtrl.h)
{
	return (this->*_operator_SQLHDBC)();

	return m_hDbc;
}


hook_method<const bool (N2ODBCCtrl::*)(void) const> N2ODBCCtrl::_isConnect(SERVER, "N2ODBCCtrl::isConnect");
const bool N2ODBCCtrl::isConnect(void) const // line 28 (N2System/ODBC(open database connectivity)/N2ODBCCtrl.h)
{
	return (this->*_isConnect)();

	return m_bConnect;
}


hook_method<void (N2ODBCCtrl::*)(const short in_Type, const SQLHANDLE in_Handle, const char* in_pSourceFileName, const int in_SourceLineNum, const char* in_pMessage)> N2ODBCCtrl::_OutputErrorString(SERVER, "N2ODBCCtrl::OutputErrorString");
void N2ODBCCtrl::OutputErrorString(const short in_Type, const SQLHANDLE in_Handle, const char* in_pSourceFileName, const int in_SourceLineNum, const char* in_pMessage) // line 108-121
{
	return (this->*_OutputErrorString)(in_Type, in_Handle, in_pSourceFileName, in_SourceLineNum, in_pMessage);

	if( in_Handle == SQL_NULL_HANDLE )
		return;

	char state[64];
	memset(state, '\0', sizeof(state));

	char msg[1024];
	memset(msg, '\0', sizeof(msg));

	for( int i = 1; i < 10; ++i )
	{
		int NativeError = 0;
		if( !SQL_SUCCEEDED(SQLGetDiagRecA(in_Type, in_Handle, i, (SQLCHAR*)state, (SQLINTEGER*)&NativeError, (SQLCHAR*)msg, sizeof(msg), NULL)) )
			break; // error during error logging...

		g_errorLogs.CErrorLog::CriticalErrorLogFmt(in_pSourceFileName, in_SourceLineNum, "%s, %d, %s, %d", state, NativeError, msg, sizeof(msg));
	}
}
