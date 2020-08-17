#include "ODBC.h"
#include "ErrorLog.h"
#include "globals.hpp"
#include "shared.h" // Trace()
#define SQL_NOUNICODEMAP
#include <sql.h>
#include <sqlext.h>
#include <odbcinst.h>


void __cdecl DBTrace(const char* in_SrcFileName, const int in_SrcLineNum, SQLSMALLINT type, SQLHANDLE handle)
{
	if( handle == SQL_NULL_HANDLE )
		return;

	char state[64] = {};
	char msg[1024] = {};
	int NativeError = 0;
	char strlog[512] = {};

	for( int i = 1; SQLGetDiagRecA(type, handle, i, (SQLCHAR*)state, (SQLINTEGER*)&NativeError, (SQLCHAR*)msg, sizeof(msg), NULL) != SQL_NO_DATA; ++i )
	{
		Trace("NO:%d, STATE:%s, MESSAGE:%s, NativeError:%d\n", i, state, msg, NativeError);
		sprintf(strlog, "*** %s, %d, %s, %d ***\r\n", state, NativeError, msg, sizeof(msg));
		g_errorLogs->CErrorLog::CriticalErrorLog(strlog, in_SrcLineNum, in_SrcFileName);
	}
}


CODBC::CODBC()
{
	m_henv = SQL_NULL_HENV;
	m_hdbc = SQL_NULL_HDBC;
	m_hstmt = SQL_NULL_HSTMT;
}


CODBC::~CODBC()
{
	this->CODBC::Reset();
}


int CODBC::Init(const char* DSN, const char* UID, const char* PASS, const char* DB, unsigned char type)
{
	this->CODBC::Reset();

	char ConnStrIn[255];
	sprintf(ConnStrIn, "DRIVER={SQL Server}; SERVER=%s; UID=%s; PWD=%s; DATABASE=%s; ", DSN, UID, PASS, DB);

	if( (m_retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_henv))      , SQL_SUCCEEDED(m_retcode)
	&&  (m_retcode = SQLSetEnvAttr(m_henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)3, 0)), SQL_SUCCEEDED(m_retcode)
	&&  (m_retcode = SQLAllocHandle(SQL_HANDLE_DBC, m_henv, &m_hdbc))               , SQL_SUCCEEDED(m_retcode) )
	{
		switch( type )
		{
			case DSN_CONNECT_TYPE:
			{
				m_retcode = SQLConnectA(m_hdbc, (SQLCHAR*)DSN, SQL_NTS, (SQLCHAR*)UID, SQL_NTS, (SQLCHAR*)PASS, SQL_NTS);
			}
			break;
			case DRIVER_CONNECT_TYPE:
			{
				char ConnStrOut[255];
				int cbConnStrOut = 0;
				m_retcode = SQLDriverConnectA(m_hdbc, NULL, (SQLCHAR*)ConnStrIn, SQL_NTS, (SQLCHAR*)ConnStrOut, sizeof(ConnStrOut), (SQLSMALLINT*)&cbConnStrOut, SQL_DRIVER_NOPROMPT);
			}
			break;
			default:
				return FALSE;
			break;
		};

		if( SQL_SUCCEEDED(m_retcode) )
			return TRUE;

		char szError[1024] = {};
		char szState[1024] = {};
		SQLErrorA(m_henv, m_hdbc, SQL_NULL_HSTMT, (SQLCHAR*)szState, NULL, (SQLCHAR*)szError, sizeof(szError), NULL);
		g_errorLogs->CErrorLog::CriticalErrorLog(szError, __LINE__, __FILE__);
		g_errorLogs->CErrorLog::CriticalErrorLog(szState, __LINE__, __FILE__);
		MessageBoxA(NULL, szError, NULL, MB_OK);

		char temp[1024];
		sprintf(temp, "DBServer connect error:%s, :DB:%s, UID:%s PASs = %s\n", DSN, DB, UID, PASS);
		g_errorLogs->CErrorLog::CriticalErrorLog(temp, __LINE__, __FILE__);
		MessageBoxA(NULL, temp, "db connect error", MB_OK);
	}

	char temp[1024];
	sprintf(temp, "DBServer Init Error:%s, :DB:%s, UID:%s\n", DSN, DB, UID);
	g_errorLogs->CErrorLog::CriticalErrorLog(temp, __LINE__, __FILE__);
	MessageBoxA(NULL, temp, "alloc handle error", MB_OK);

	return FALSE;
}


void CODBC::Reset()
{
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


void CODBC::GetErrorString(SQLHSTMT hStmt, char* lpszError)
{
	char szState[1024] = {};
	SQLErrorA(m_henv, m_hdbc, hStmt, (SQLCHAR*)szState, NULL, (SQLCHAR*)lpszError, 1024, 0);
}


CDBStatement::CDBStatement()
{
	m_hStmt = SQL_NULL_HSTMT;
}


CDBStatement::~CDBStatement()
{
	if( m_hStmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
}


CDBStatement::operator SQLHSTMT()
{
	return m_hStmt;
}


bool CDBStatement::Init(SQLHDBC hDBC)
{
	SQLRETURN ret = SQLAllocHandle(SQL_HANDLE_STMT, hDBC, &m_hStmt);
	return SQL_SUCCEEDED(ret);
}


BOOL __cdecl AddSystemDSN(const char* dsn, const char* server, const char* db)
{
	if( dsn == NULL || server == NULL || db == NULL )
		return FALSE;
	if( strlen(dsn) == 0 || strlen(server) == 0 || strlen(db) == 0 )
		return FALSE;

	char dsnAttr[64];
	char serverAttr[64];
	char dbAttr[64];
	char networkAttr[64];
	sprintf(dsnAttr, "DSN=%s", dsn);
	sprintf(serverAttr, "Server=%s", server);
	sprintf(dbAttr, "Database=%s", db);
	sprintf(networkAttr, "Network=DBMSSOCN");

	char attrs[512] = {};
	strcat(attrs, dsnAttr);
	strcat(attrs, serverAttr);
	strcat(attrs, dbAttr);
	strcat(attrs, networkAttr);

	if( SQLConfigDataSource(NULL, ODBC_ADD_SYS_DSN, "SQL Server", attrs) == FALSE )
	{
		char errorMsg[512];
		int errorCode;
		short cbErrorMsg;
		SQLInstallerError(8, (DWORD*)&errorCode, errorMsg, sizeof(errorMsg)-1, (WORD*)&cbErrorMsg);
		Trace("SQLConfigDataSource error %d, %s\n", errorCode, errorMsg);
		return FALSE;
	}

	Trace("AddSystenDSN DSN:%s, Server: %s, Default DB:%s\n", dsn, server, db);
	return TRUE;
}
