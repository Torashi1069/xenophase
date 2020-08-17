#include "Common/Database.h"
#include "Common/EnterTraceLog.h"
#include <sql.h>
#include <sqlext.h>
#include <odbcss.h>


void GetSQLErrorString(SQLHENV hEnv, SQLHDBC hDbc, SQLHSTMT hStmt, char* pszError)
{
	char szState[MAX_BUFFER_LENGTH] = {};
	SQLErrorA(hEnv, hDbc, hStmt, (SQLCHAR*)szState, (SQLINTEGER*)NULL, (SQLCHAR*)pszError, MAX_BUFFER_LENGTH, (SQLSMALLINT*)NULL);
}


CDatabase::CDatabase()
{
	m_hEnv = SQL_NULL_HENV;
	m_hDbc = SQL_NULL_HDBC;
}


CDatabase::~CDatabase()
{
	this->CDatabase::Disconnect();
}


bool CDatabase::Connect(const char* in_szpFileDSN, const char* in_Pwd)
{
	m_Name = in_szpFileDSN;

	if( !SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv)) )
	{
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CDatabase::CDatabase() - SQLAllocHandle() fail(SQL_HANDLE_ENV)");
		return false;
	}

	if( !SQL_SUCCEEDED(SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER)) )
	{
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CDatabase::CDatabase() - SQLSetEnvAttr() fail");
		return false;
	}

	if( !SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDbc)) )
	{
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CDatabase::CDatabase() - SQLAllocHandle() fail(SQL_HANDLE_DBC)");
		return false;
	}

	std::string ConnectionStr = std::string("FILEDSN=.\\") + in_szpFileDSN + std::string(";PWD=") + in_Pwd;
	char ConnectionOutStr[256] = {};
	int cbConnectionOutStr = 0;

	if( !SQL_SUCCEEDED(SQLDriverConnectA(m_hDbc, NULL, (SQLCHAR*)ConnectionStr.c_str(), SQL_NTS, (SQLCHAR*)ConnectionOutStr, sizeof(ConnectionOutStr), (SQLSMALLINT*)&cbConnectionOutStr, SQL_DRIVER_NOPROMPT)) )
	{
		char szSQLError[MAX_BUFFER_LENGTH] = {};
		GetSQLErrorString(m_hEnv, m_hDbc, SQL_NULL_HSTMT, szSQLError);
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s - SQLDriverConnect() Fail!(%s) \n:%s", __FUNCTION__, ConnectionStr.c_str(), szSQLError);
		return false;
	}

	return true;
}


void CDatabase::Disconnect()
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


bool CDatabase::SetTranslateOption(bool bTranslateOpt)
{
	if( m_hDbc == SQL_NULL_HDBC )
		return false;

	int opt = ( bTranslateOpt ) ? SQL_XL_ON : SQL_XL_OFF;
	SQLRETURN sqlResult = SQLSetConnectAttr(m_hDbc, SQL_COPT_SS_TRANSLATE, (SQLPOINTER)opt, SQL_IS_INTEGER);
	if( !SQL_SUCCEEDED(sqlResult) )
		return false;

	return true;
}
