#include "Common/Database.h"
#include "Common/DatabaseStatement.h"
#include "Common/Reporter.h"
#include <sql.h>
#include <sqlext.h>


CDatabaseStatement::CDatabaseStatement(CDatabase* pDatabase)
{
	m_hDbc = SQL_NULL_HDBC;
	m_hEnv = SQL_NULL_HENV;
	m_hStmt = SQL_NULL_HSTMT;
	this->CDatabaseStatement::Open(pDatabase);
}


CDatabaseStatement::~CDatabaseStatement()
{
	this->CDatabaseStatement::Release();
}


bool CDatabaseStatement::Open(CDatabase* pDatabase)
{
	if( m_hStmt != NULL )
		this->CDatabaseStatement::Release();

	m_hDbc = pDatabase->m_hDbc;
	m_hEnv = pDatabase->m_hEnv;
	m_pszDSN = pDatabase->m_szDSN;

	if( m_hEnv == SQL_NULL_HENV )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CDatabaseStatement::Open() (%s - SQL_NULL_HENV == m_hEnv)", m_pszDSN);
		return false;
	}

	if( m_hDbc == SQL_NULL_HDBC )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CDatabaseStatement::Open() (%s - SQL_NULL_HDBC == m_hDbc)", m_pszDSN);
		return false;
	}

	if( !SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &m_hStmt)) )
	{
		char szSQLError[MAX_BUFFER_LENGTH] = {};
		GetSQLErrorString(m_hEnv, m_hDbc, m_hStmt, szSQLError);
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CDatabaseStatement::Open() - SQLAllocStmt() fail(%s - %s)", m_pszDSN, szSQLError);
		return false;
	}

	return true;
}


void CDatabaseStatement::Release()
{
	if( m_hStmt != SQL_NULL_HSTMT )
	{
		SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
		m_hStmt = SQL_NULL_HSTMT;
	}
}


bool CDatabaseStatement::BindNumberColumn(int nColumn, void* pData)
{
	SQLINTEGER cbNum = 0;
	if( !SQL_SUCCEEDED(SQLBindCol(m_hStmt, nColumn, SQL_C_SLONG, pData, 0, &cbNum)) )
	{
		char szSQLError[MAX_BUFFER_LENGTH] = {};
		GetSQLErrorString(m_hEnv, m_hDbc, m_hStmt, szSQLError);
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CDatabaseStatement::BindNumberColumn() - SQLBindCol() fail(%s - %s)", m_pszDSN, szSQLError);
		return false;
	}

	return true;
}


bool CDatabaseStatement::BindStringColumn(int nColumn, char* pszData, int nBufferSize)
{
	SQLINTEGER cbChar = SQL_NTS;
	if( !SQL_SUCCEEDED(SQLBindCol(m_hStmt, nColumn, SQL_C_CHAR, pszData, nBufferSize, &cbChar)) )
	{
		char szSQLError[MAX_BUFFER_LENGTH] = {};
		GetSQLErrorString(m_hEnv, m_hDbc, m_hStmt, szSQLError);
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CDatabaseStatement::BindIntegerColumn() - SQLBindCol() fail(%s - %s)", m_pszDSN, szSQLError);
		return false;
	}

	return true;
}


bool CDatabaseStatement::BindBinaryColumn(int nColumn, char* pszData, int nBufferSize, SQLINTEGER* outBinSize)
{
	SQLINTEGER cbBin = SQL_NTS; // if length isn't provided, assume c-string
	SQLINTEGER* pOutBinSize = ( outBinSize != NULL ) ? outBinSize : &cbBin;
	if( !SQL_SUCCEEDED(SQLBindCol(m_hStmt, nColumn, SQL_C_BINARY, pszData, nBufferSize, pOutBinSize)) )
	{
		char szSQLError[MAX_BUFFER_LENGTH] = {};
		GetSQLErrorString(m_hEnv, m_hDbc, m_hStmt, szSQLError);
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CDatabaseStatement::BindBinaryColumn() - SQLBindCol() fail(%s - %s)", m_pszDSN, szSQLError);
		return false;
	}

	return true;
}


struct SODBCPARAM
{
	/* this+0 */ SQLINTEGER m_cdValue;
	/* this+4 */ int m_nParam;
	/* this+8 */ char m_szParam[256];
};


BOOL CDatabaseStatement::Query(char* lpszQuery, ...)
{
	if( m_hStmt == SQL_NULL_HSTMT )
		return FALSE;

	int nParam = 0;
	for( size_t i = 0; i < strlen(lpszQuery); ++i )
		if( lpszQuery[i] == '%' )
			++nParam;

	if( nParam == 0 )
	{// simple query (no parameters)
		SQLRETURN sqlResult = SQLExecDirectA(m_hStmt, (SQLCHAR*)lpszQuery, SQL_NTS);
		if( !SQL_SUCCEEDED(sqlResult) )
		{
			if( sqlResult == SQL_STILL_EXECUTING || sqlResult == SQL_NO_DATA ) // [patch] proper sql retcode handling
				return TRUE;

			char szSQLError[MAX_BUFFER_LENGTH] = {};
			GetSQLErrorString(m_hEnv, m_hDbc, m_hStmt, szSQLError);
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CDatabaseStatement::Query() - SQLExecDirect() fail(%s - %s)", m_pszDSN, szSQLError);
			return FALSE;
		}

		return TRUE;
	}

	va_list vaParam;
	va_start(vaParam, lpszQuery);

	SODBCPARAM odbcParam[MAX_ODBC_PARAM] = {};
	int nPosition = 0;

	for( int i = 0; i < nParam && i < MAX_ODBC_PARAM; ++i )
	{
		nPosition = strchr(lpszQuery + nPosition, '%') - lpszQuery + 1;
		BYTE byParam = lpszQuery[nPosition];
		SQLRETURN sqlResult;

		switch( byParam )
		{
		case PARAM_TYPE_DECIMAL:
		{// integer (<value>)
			int value = va_arg(vaParam, int);
			odbcParam[i].m_nParam = value;
			sqlResult = SQLBindParameter(m_hStmt, i + 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &odbcParam[i].m_nParam, 0, NULL);
		}
		break;
		case PARAM_TYPE_STRING:
		{// string (<pszText>)
			char* pszText = va_arg(vaParam, char*);
			odbcParam[i].m_cdValue = SQL_NTS;
			strncpy(odbcParam[i].m_szParam, pszText, sizeof(odbcParam[i].m_szParam)-1);
			sqlResult = SQLBindParameter(m_hStmt, i + 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, MAX_BUFFER_LENGTH, 0, &odbcParam[i].m_szParam, 0, &odbcParam[i].m_cdValue);
		}
		break;
		case PARAM_TYPE_BINARY:
		{// binary data (<pData>, <size>)
			void* pData = va_arg(vaParam, void*);
			size_t size = va_arg(vaParam, size_t);
			odbcParam[i].m_cdValue = size;
			sqlResult = SQLBindParameter(m_hStmt, i + 1, SQL_PARAM_INPUT, SQL_C_BINARY, SQL_VARBINARY, size, 0, pData, 0, &odbcParam[i].m_cdValue);
		}
		break;
		};

		if( !SQL_SUCCEEDED(sqlResult) )
		{
			char szSQLError[MAX_BUFFER_LENGTH] = {};
			GetSQLErrorString(m_hEnv, m_hDbc, m_hStmt, szSQLError);
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CDatabaseStatement::Query() - SQLBindParameter() fail(%s - %s)", m_pszDSN, szSQLError);
			return FALSE;
		}
	}

	va_end(vaParam);

	char szQuery[MAX_BUFFER_LENGTH] = {};
	strcpy(szQuery, lpszQuery);

	size_t nIndex = strlen(szQuery);
	while( nIndex != 0 )
	{
		--nIndex;
		if( szQuery[nIndex] == '%' )
		{
			szQuery[nIndex + 0] = ' ';
			szQuery[nIndex + 1] = '?';
		}
	}

	SQLRETURN sqlResult = SQLExecDirectA(m_hStmt, (SQLCHAR*)szQuery, SQL_NTS);
	if( !SQL_SUCCEEDED(sqlResult) )
	{
		if( sqlResult == SQL_STILL_EXECUTING || sqlResult == SQL_NO_DATA )
			return TRUE;

		char szSQLError[MAX_BUFFER_LENGTH] = {};
		GetSQLErrorString(m_hEnv, m_hDbc, m_hStmt, szSQLError);
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CDatabaseStatement::Query() - SQLExecDirect() fail(%s - %s)", m_pszDSN, szSQLError);
		return FALSE;
	}

	return TRUE;
}


SQLRETURN CDatabaseStatement::Fetch()
{
	return SQLFetch(m_hStmt);
}


SQLHSTMT CDatabaseStatement::GetStmtHandle()
{
	return m_hStmt;
}
