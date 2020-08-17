#include "shared/NCriticalErrorLog.h"
#include "shared/ODBC.h"


void DBTrace(const char* in_SrcFileName, const int in_SrcLineNum, SQLSMALLINT type, SQLHSTMT handle)
{
	if( handle == SQL_NULL_HSTMT )
		return;

	char state[64] = {};
	char msg[1024] = {};
	SQLINTEGER NativeError = 0;

	for( int i = 1; SQL_NO_DATA != SQLGetDiagRecA(type, handle, i, (SQLCHAR*)state, &NativeError, (SQLCHAR*)msg, countof(msg), NULL); ++i )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(in_SrcFileName, in_SrcLineNum, "%s, %d, %s", state, NativeError, msg);
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


CODBC::operator SQLHSTMT()
{
	return m_hstmt;
}


BOOL CODBC::Init(const char* FileDSN, const char* PASS)
{
	this->CODBC::Reset();

	std::string strConnectInfo = "FILEDSN=.\\" + std::string(FileDSN) + ";PWD=" + std::string(PASS);
	char ConnStrOut[255] = {};
	SQLSMALLINT cbConnStrOut = 0;

	m_retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_henv);
	if( SQL_SUCCEEDED(m_retcode) )
	{
		m_retcode = SQLSetEnvAttr(m_henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
		if( SQL_SUCCEEDED(m_retcode) )
		{
			m_retcode = SQLAllocHandle(SQL_HANDLE_DBC, m_henv, &m_hdbc);
			if( !SQL_SUCCEEDED(m_retcode) )
				return FALSE;

			m_retcode = SQLDriverConnectA(m_hdbc, NULL, (SQLCHAR*)strConnectInfo.c_str(), SQL_NTS, (SQLCHAR*)ConnStrOut, countof(ConnStrOut), (SQLSMALLINT*)&cbConnStrOut, SQL_DRIVER_NOPROMPT);
			if( SQL_SUCCEEDED(m_retcode) )
			{// success.
				return TRUE;
			}

			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "strConnectInfo : %s", strConnectInfo.c_str());
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "FileDSN : %s", FileDSN);

			char szError[1024] = {};
			char szState[1024] = {};
			SQLErrorA(m_henv, m_hdbc, SQL_NULL_HSTMT, (SQLCHAR*)szState, NULL, (SQLCHAR*)szError, countof(szError), NULL);
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Error:%s State:%s", szError, szState);
			MessageBoxA(NULL, szError, NULL, MB_OK);

			char temp[1024];
			sprintf_s(temp, countof(temp), "DBServer connect error DSNFILE :%s", FileDSN);
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s", temp);
			MessageBoxA(NULL, temp, "db connect error", MB_OK);
		}
	}

	char temp[1024];
	sprintf_s(temp, countof(temp), "DBServer Init Error DSNFILE:%s", FileDSN);
	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s", temp);
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
	SQLErrorA(m_henv, m_hdbc, hStmt, (SQLCHAR*)szState, NULL, (SQLCHAR*)lpszError, 1024, NULL);
}


////////////////////////////////////////


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
	return ( SQL_SUCCEEDED(ret) );
}
