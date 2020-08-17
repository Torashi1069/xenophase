#include "Common/Database.h"
#include "Common/Reporter.h"
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


bool CDatabase::Connect(const char* lpszID, const char* lpszPassword, const char* lpszDSN)
{
	if( !SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv)) )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CDatabase::CDatabase() - SQLAllocHandle() fail(SQL_HANDLE_ENV)");
		return false;
	}

	if( !SQL_SUCCEEDED(SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER)) )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CDatabase::CDatabase() - SQLSetEnvAttr() fail");
		return false;
	}

	if( !SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDbc)) )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CDatabase::CDatabase() - SQLAllocHandle() fail(SQL_HANDLE_DBC)");
		return false;
	}

	if( !SQL_SUCCEEDED(SQLConnectA(m_hDbc, (SQLCHAR*)lpszDSN, SQL_NTS, (SQLCHAR*)lpszID, SQL_NTS, (SQLCHAR*)lpszPassword, SQL_NTS)) )
	{
		char szSQLError[MAX_BUFFER_LENGTH] = {};
		GetSQLErrorString(m_hEnv, m_hDbc, SQL_NULL_HSTMT, szSQLError);
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("%s - SQLDriverConnect() Fail!(id '%s', dsn '%s', error (%s))", __FUNCTION__, lpszID, lpszDSN, szSQLError);
		return false;
	}
	
	memcpy(m_szDSN, lpszDSN, sizeof(m_szDSN)); //FIXME: potential read out of bounds
	m_szDSN[sizeof(m_szDSN)-1] = '\0';

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
