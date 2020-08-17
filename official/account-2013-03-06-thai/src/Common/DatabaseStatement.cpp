#include "Common/Database.h"
#include "Common/DatabaseStatement.h"
#include "Common/EnterTraceLog.h"
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
	m_Name = pDatabase->m_Name;

	if( m_hEnv == SQL_NULL_HENV )
	{
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CDatabaseStatement::Open() (%s - SQL_NULL_HENV == m_hEnv)", m_Name.c_str());
		return false;
	}

	if( m_hDbc == SQL_NULL_HDBC )
	{
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CDatabaseStatement::Open() (%s - SQL_NULL_HDBC == m_hDbc)", m_Name.c_str());
		return false;
	}

	if( !SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &m_hStmt)) )
	{
		char szSQLError[MAX_BUFFER_LENGTH] = {};
		GetSQLErrorString(m_hEnv, m_hDbc, m_hStmt, szSQLError);
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CDatabaseStatement::Open() - SQLAllocStmt() fail(%s - %s)", m_Name.c_str(), szSQLError);
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
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CDatabaseStatement::BindNumberColumn() - SQLBindCol() fail(%s - %s)", m_Name.c_str(), szSQLError);
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
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CDatabaseStatement::BindIntegerColumn() - SQLBindCol() fail(%s - %s)", m_Name.c_str(), szSQLError);
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
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CDatabaseStatement::BindBinaryColumn() - SQLBindCol() fail(%s - %s)", m_Name.c_str(), szSQLError);
		return false;
	}

	return true;
}


bool CDatabaseStatement::BindFloatColumn(int nColumn, void* pData)
{
	SQLINTEGER cbNum = 0;
	if( !SQL_SUCCEEDED(SQLBindCol(m_hStmt, nColumn, SQL_C_FLOAT, pData, 0, &cbNum)) )
	{
		char szSQLError[MAX_BUFFER_LENGTH] = {};
		GetSQLErrorString(m_hEnv, m_hDbc, m_hStmt, szSQLError);
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CDatabaseStatement::BindFloatColumn() - SQLBindCol() fail(%s - %s)", m_Name.c_str(), szSQLError);
		return false;
	}

	return true;
}


struct SODBCPARAM
{
	/* this+0 */ SQLINTEGER m_cdValue;
	/* this+4 */ __int64 m_nParam;
	/* this+8 */ char m_szParam[256];

	SODBCPARAM()
	{
		//m_cdValue = 0;
		//m_nParam = 0;
		memset(m_szParam, '\0', sizeof(m_szParam));
	}
};


BOOL CDatabaseStatement::Query(char* lpszQuery, ...)
{
	if( m_hStmt == SQL_NULL_HSTMT )
		return FALSE;

	int nParam = 0;
	for( size_t i = 0; i < strlen(lpszQuery); ++i )
		if( lpszQuery[i] == '%' )
			++nParam;

	BOOL bIsReturn = FALSE;
	int nReturn = 0;
	int nStartidx = 0;

	// check if return value is to be retrieved as well
	size_t queryLen = strlen(lpszQuery);
	for( size_t i = 0; i < queryLen; ++i )
	{
		if( lpszQuery[i] == '?' && lpszQuery[i + 1] == '=' )
		{// bind additional 'return' parameter
			bIsReturn = TRUE;
			nStartidx = 1;

			SQLINTEGER cbInt = sizeof(nReturn);
			if( !SQL_SUCCEEDED(SQLBindParameter(m_hStmt, 1, SQL_PARAM_OUTPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &nReturn, 0, &cbInt)) )
			{
				char szSQLError[MAX_BUFFER_LENGTH] = {};
				GetSQLErrorString(m_hEnv, m_hDbc, m_hStmt, szSQLError);
				CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "CDatabaseStatement::Query() - SQLExecDirect() fail#1(%s - %s)", m_Name.c_str(), szSQLError);
				return FALSE;
			}

			break;
		}
	}

	if( nParam == 0 && !bIsReturn )
	{// simple query (no parameters)
		SQLRETURN sqlResult = SQLExecDirectA(m_hStmt, (SQLCHAR*)lpszQuery, SQL_NTS);
		if( !SQL_SUCCEEDED(sqlResult) )
		{
			char szSQLError[MAX_BUFFER_LENGTH] = {};
			GetSQLErrorString(m_hEnv, m_hDbc, m_hStmt, szSQLError);
			CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "CDatabaseStatement::Query() - SQLExecDirect() fail#2(%s - %s)", m_Name.c_str(), szSQLError);
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
			sqlResult = SQLBindParameter(m_hStmt, nStartidx + i + 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &odbcParam[i].m_nParam, 0, NULL);
		}
		break;
		case PARAM_TYPE_BIGINT:
		{// bigint (<value>)
			__int64 value = va_arg(vaParam, __int64);
			odbcParam[i].m_nParam = value;
			sqlResult = SQLBindParameter(m_hStmt, nStartidx + i + 1, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &odbcParam[i].m_nParam, 0, NULL);
		}
		break;
		case PARAM_TYPE_STRING:
		{// string (<pszText>)
			char* pszText = va_arg(vaParam, char*);
			odbcParam[i].m_cdValue = SQL_NTS;
			strncpy(odbcParam[i].m_szParam, pszText, sizeof(odbcParam[i].m_szParam)-1);
			sqlResult = SQLBindParameter(m_hStmt, nStartidx + i + 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, MAX_BUFFER_LENGTH, 0, &odbcParam[i].m_szParam, 0, &odbcParam[i].m_cdValue);
		}
		break;
		case PARAM_TYPE_BINARY:
		{// binary data (<pData>, <size>)
			void* pData = va_arg(vaParam, void*);
			size_t size = va_arg(vaParam, size_t);
			odbcParam[i].m_cdValue = size;
			sqlResult = SQLBindParameter(m_hStmt, nStartidx + i + 1, SQL_PARAM_INPUT, SQL_C_BINARY, SQL_VARBINARY, size, 0, pData, 0, &odbcParam[i].m_cdValue);
		}
		break;
		};

		if( !SQL_SUCCEEDED(sqlResult) )
		{
			char szSQLError[MAX_BUFFER_LENGTH] = {};
			GetSQLErrorString(m_hEnv, m_hDbc, m_hStmt, szSQLError);
			CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CDatabaseStatement::Query() - SQLBindParameter() fail#3(%s - %s)", m_Name.c_str(), szSQLError);
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
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CDatabaseStatement::Query() - SQLExecDirect() fail#3(%s - %s)", m_Name.c_str(), szSQLError);
		return FALSE;
	}

	if( bIsReturn )
	{
		// consume all remaining batched result sets
		while( SQLMoreResults(m_hStmt) != SQL_NO_DATA )
			;

		// special return value check
		if( nReturn <= 0 )
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


void CDatabaseStatement::ErrLog()
{
	char szSQLError[MAX_BUFFER_LENGTH] = {};
	GetSQLErrorString(m_hEnv, m_hDbc, m_hStmt, szSQLError);
	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CDatabaseStatement::Query() - SQLExecDirect() fail#6(%s - %s)", m_Name.c_str(), szSQLError);
}
