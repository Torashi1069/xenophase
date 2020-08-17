#include "ErrorLog.h"
#include "ODBC.h"
#include "globals.hpp"
#include <sql.h>
#include <sqlext.h>


hook_func<void (__cdecl *)(const char* in_SrcFileName, const int in_SrcLineNum, SQLSMALLINT type, SQLHSTMT handle)> _DBTrace(SERVER, "DBTrace");
void __cdecl DBTrace(const char* in_SrcFileName, const int in_SrcLineNum, SQLSMALLINT type, SQLHSTMT handle) // line 9
{
	return (_DBTrace)(in_SrcFileName, in_SrcLineNum, type, handle);

	if( handle == SQL_NULL_HSTMT )
		return;

	char state[64];
	char msg[1024];
	char strlog[512];
	memset(state, 0, sizeof(state));
	memset(msg, 0, sizeof(msg));
	memset(strlog, 0, sizeof(strlog));

	SQLINTEGER NativeError = 0;
	for( int i = 0; SQL_NO_DATA != SQLGetDiagRecA(type, handle, i, (SQLCHAR*)state, &NativeError, (SQLCHAR*)msg, sizeof(msg), NULL); ++i )
	{
		Trace("NO:%d, STATE:%s, MESSAGE:%s, NativeError:%d\n", i, state, msg, NativeError);
		sprintf(strlog, "*** %s, %d, %s, %d ***\r\n", state, NativeError, msg, sizeof(msg));
		g_errorLogs.CErrorLog::CriticalErrorLog(strlog, in_SrcLineNum, in_SrcFileName);
	}
}


CODBC::CODBC(void) // line 35
{
	m_henv = SQL_NULL_HENV;
	m_hdbc = SQL_NULL_HDBC;
	m_hstmt = SQL_NULL_HSTMT;
}


CODBC::~CODBC(void) // line 42
{
	this->CODBC::Reset();
}


hook_method<int (CODBC::*)(const char* DSN, const char* UID, const char* PASS, const char* DB, unsigned char type)> CODBC::_Init(SERVER, "CODBC::Init");
int CODBC::Init(const char* DSN, const char* UID, const char* PASS, const char* DB, unsigned char type) // line 47
{
	return (this->*_Init)(DSN, UID, PASS, DB, type);

	this->CODBC::Reset();

	char ConnStrIn[255];
	sprintf(ConnStrIn, "DRIVER={SQL Server}; SERVER=%s; UID=%s; PWD=%s; DATABASE=%s; ", DSN, UID, PASS, DB);

	if( (m_retcode = SQLAllocHandle(SQL_HANDLE_ENV, 0, &m_henv))                               , SQL_SUCCEEDED(m_retcode)
	&&  (m_retcode = SQLSetEnvAttr(m_henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0)), SQL_SUCCEEDED(m_retcode)
	&&  (m_retcode = SQLAllocHandle(SQL_HANDLE_DBC, m_henv, &m_hdbc))                          , SQL_SUCCEEDED(m_retcode) )
	{
		if( type == 0 )
		{
			m_retcode = SQLConnectA(m_hdbc, (SQLCHAR*)DSN, SQL_NTS, (SQLCHAR*)UID, SQL_NTS, (SQLCHAR*)PASS, SQL_NTS);
		}
		else
		if( type == 1 )
		{
			char ConnStrOut[255];
			int cbConnStrOut = 0;
			m_retcode = SQLDriverConnectA(m_hdbc, 0, (SQLCHAR*)ConnStrIn, SQL_NTS, (SQLCHAR*)ConnStrOut, sizeof(ConnStrOut), (SQLSMALLINT*)&cbConnStrOut, 0);
		}
		else
		{
			return 0;
		}

		if( SQL_SUCCEEDED(m_retcode) )
			return 1;

		char szError[1024];
		char szState[1024];
		memset(szError, 0, sizeof(szError));
		memset(szState, 0, sizeof(szState));
		SQLErrorA(m_henv, m_hdbc, 0, (SQLCHAR*)szState, 0, (SQLCHAR*)szError, 1024, 0);
		g_errorLogs.CErrorLog::CriticalErrorLog(szError, 76, ".\\ODBC.cpp");
		g_errorLogs.CErrorLog::CriticalErrorLog(szState, 77, ".\\ODBC.cpp");
		MessageBoxA(NULL, szError, NULL, MB_OK);
		
		char Text[1024];
		sprintf(Text, "DBServer connect error:%s, :DB:%s, UID:%s PASs = %s\n", DSN, DB, UID, PASS);
		g_errorLogs.CErrorLog::CriticalErrorLog(Text, 82, ".\\ODBC.cpp");
		MessageBoxA(NULL, Text, "db connect error", MB_OK);
	}

	char temp[1024];
	sprintf(temp, "DBServer Init Error:%s, :DB:%s, UID:%s\n", DSN, DB, UID);
	g_errorLogs.CErrorLog::CriticalErrorLog(temp, 91, ".\\ODBC.cpp");
	MessageBoxA(0, temp, "alloc handle error", MB_OK);

	return 0;
}


hook_method<void (CODBC::*)(void)> CODBC::_Reset(SERVER, "CODBC::Reset");
void CODBC::Reset(void) // line 98
{
	return (this->*_Reset)();

	if( m_hdbc != SQL_NULL_HDBC )
	{
		SQLDisconnect(m_hdbc);
		SQLFreeHandle(SQL_HANDLE_DBC, m_hdbc);
		m_hdbc = SQL_NULL_HDBC;
	}

	if( m_henv != SQL_NULL_HENV )
	{
		SQLFreeHandle(SQL_HANDLE_ENV, m_henv);
		m_henv = SQL_NULL_HENV;
	}
}


hook_method<void (CODBC::*)(void* hStmt, char* lpszError)> CODBC::_GetErrorString(SERVER, "CODBC::GetErrorString");
void CODBC::GetErrorString(SQLHSTMT hStmt, char* lpszError) // line 111
{
	return (this->*_GetErrorString)(hStmt, lpszError);

	char szState[1024];
	memset(szState, 0, sizeof(szState));
	SQLErrorA(m_henv, m_hdbc, hStmt, (SQLCHAR*)szState, NULL, (SQLCHAR*)lpszError, 1024, 0);
}


////////////////////////////////////////


CDBStatement::CDBStatement(void) // line 59 (ODBC.h)
{
	m_hStmt = SQL_NULL_HSTMT;
}


CDBStatement::~CDBStatement(void) // line 122
{
	if( m_hStmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
}


//hook_method<SQLHSTMT (CDBStatement::*)(void)> CDBStatement::_operator_SQLHSTMT(SERVER, "???");
CDBStatement::operator SQLHSTMT(void) // line ???
{
//	return (this->*_operator_SQLHSTMT)();

	return m_hStmt;
}


hook_method<bool (CDBStatement::*)(SQLHDBC hDBC)> CDBStatement::_Init(SERVER, "CDBStatement::Init");
bool CDBStatement::Init(SQLHDBC hDBC) // line 128
{
	return (this->*_Init)(hDBC);

	SQLRETURN ret = SQLAllocHandle(SQL_HANDLE_STMT, hDBC, &m_hStmt);
	return ( SQL_SUCCEEDED(ret) );
}
