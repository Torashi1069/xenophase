#include "shared/ExtendedODBC.h"
#include "shared/NCriticalErrorLog.h"


CExtendedODBC::CExtendedODBC()
{
}


CExtendedODBC::~CExtendedODBC()
{
}


void CExtendedODBC::FreeStmt(SQLHSTMT* phStmt, int nOption)
{
	SQLFreeStmt(*phStmt, nOption);
	*phStmt = SQL_NULL_HSTMT;
}


struct SODBCPARAM
{
	/* this+0 */ SQLINTEGER m_cdValue;
	/* this+4 */ int m_nParam;
	/* this+8 */ char m_szParam[256];
};


BOOL CExtendedODBC::Query(SQLHSTMT hStmt, const char* lpszQuery, ...)
{
	if( hStmt == SQL_NULL_HSTMT )
		return FALSE;

	int nParam = 0;
	for( size_t i = 0; i < strlen(lpszQuery); ++i )
		if( lpszQuery[i] == '%' )
			++nParam;

	if( nParam == 0 )
	{// simple query (no parameters)
		SQLRETURN sqlResult = SQLExecDirectA(hStmt, (SQLCHAR*)lpszQuery, SQL_NTS);
		if( !SQL_SUCCEEDED(sqlResult) )
		{
			char szSQLError[256] = {};
			this->CExtendedODBC::GetErrorString(hStmt, szSQLError);
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s %s", __FUNCTION__, szSQLError);
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s", lpszQuery);

			char szError[256] = {};
			_snprintf(szError, countof(szError), "CDatabase::Query() - SQLExecDirect() Fail!(%s)", szSQLError);
			MessageBoxA(NULL, szError, "", MB_OK);

			return FALSE;
		}

		return TRUE;
	}

	va_list vaParam;
	va_start(vaParam, lpszQuery);

	SODBCPARAM odbcParam[MAX_ODBC_PARAM] = {};
	int nPosition = 0;

	for( int i = 0; i < nParam; ++i )
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
			sqlResult = SQLBindParameter(hStmt, i + 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &odbcParam[i].m_nParam, 0, NULL);
		}
		break;
		case PARAM_TYPE_STRING:
		{// string (<pszText>)
			char* pszText = va_arg(vaParam, char*);
			odbcParam[i].m_cdValue = SQL_NTS;
			strcpy(odbcParam[i].m_szParam, pszText);
			sqlResult = SQLBindParameter(hStmt, i + 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 256, 0, &odbcParam[i].m_szParam, 0, &odbcParam[i].m_cdValue);
		}
		break;
		};

		if( !SQL_SUCCEEDED(sqlResult) )
		{
			char szSQLError[256] = {};
			this->CExtendedODBC::GetErrorString(hStmt, szSQLError);
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s %s", __FUNCTION__, szSQLError);
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s", lpszQuery);

			this->CExtendedODBC::FreeStmt(&hStmt, SQL_DROP);

			char szError[256] = {};
			_snprintf(szError, countof(szError), "CDatabase::Query() - SQLBindParameter() Fail!(%s)", szSQLError);
			MessageBoxA(NULL, szError, "", MB_OK);

			return FALSE;
		}
	}

	va_end(vaParam);

	char szQuery[256] = {};
	strncpy(szQuery, lpszQuery, countof(szQuery));

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

	SQLRETURN sqlResult = SQLExecDirectA(hStmt, (SQLCHAR*)szQuery, SQL_NTS);
	if( !SQL_SUCCEEDED(sqlResult) )
	{
		char szSQLError[256] = {};
		this->CExtendedODBC::GetErrorString(hStmt, szSQLError);
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s %s", __FUNCTION__, szSQLError);
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s", szQuery);

		this->CExtendedODBC::FreeStmt(&hStmt, SQL_DROP);

		char szError[256] = {};
		_snprintf(szError, countof(szError), "CDatabase::Query() - SQLExecDirect() Fail!(%s)", szSQLError);
		MessageBoxA(NULL, szError, "", MB_OK);

		return FALSE;
	}

	return TRUE;
}


BOOL CExtendedODBC::AllocStmt(SQLHSTMT* phStmt)
{
	SQLRETURN sqlRet = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, phStmt);
	return !this->CExtendedODBC::IsError(sqlRet);
}


void CExtendedODBC::GetErrorString(SQLHSTMT hStmt, char* lpszError)
{
	char szState[256] = {};
	SQLError(m_henv, m_hdbc, hStmt, (SQLCHAR*)szState, NULL, (SQLCHAR*)lpszError, 256, 0);
}


BOOL CExtendedODBC::IsError(SQLRETURN sqlResult)
{
	return ( !SQL_SUCCEEDED(sqlResult) );
}


BOOL CExtendedODBC::Connect(const char* FileDsn, const char* lpszPassword)
{
	return this->CODBC::Init(FileDsn, lpszPassword);
}
