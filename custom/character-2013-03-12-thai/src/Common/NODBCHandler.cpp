#include "Common/Database.h"
#include "Common/NODBCHandler.h"
#include <sql.h>
#include <sqlext.h>


NODBCHandler::NODBCHandler(CDatabase* in_cpDatabase)
{
	m_cpDatabase = in_cpDatabase;
	m_hStmt = NULL;
	m_bOK = false;

	if( this->NODBCHandler::Init() )
		m_bOK = true;
}


NODBCHandler::~NODBCHandler()
{
	if( m_hStmt != NULL )
	{
		SQLCloseCursor(m_hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
		m_hStmt = NULL;
	}
}


bool NODBCHandler::Init()
{
	SQLRETURN sqlResult = SQLAllocHandle(SQL_HANDLE_STMT, m_cpDatabase->m_hDbc, &m_hStmt);
	return ( SQL_SUCCEEDED(sqlResult) );
}


bool NODBCHandler::isOK() const
{
	return m_bOK;
}


SQLRETURN NODBCHandler::ExecDirect(const std::string in_strQuery)
{
    return SQLExecDirectA(m_hStmt, (SQLCHAR*)in_strQuery.c_str(), SQL_NTS);
}


SQLRETURN NODBCHandler::BindCol(SQLUSMALLINT ColumnNumber, SQLSMALLINT TargetType, SQLPOINTER TargetValue, SQLINTEGER BufferLength, SQLINTEGER* StrLen_or_Ind)
{
	return SQLBindCol(m_hStmt, ColumnNumber, TargetType, TargetValue, BufferLength, StrLen_or_Ind);
}


SQLRETURN NODBCHandler::BindParameter(SQLUSMALLINT ipar, SQLSMALLINT fParamType, SQLSMALLINT fCType, SQLSMALLINT fSqlType, SQLUINTEGER cbColDef, SQLSMALLINT ibScale, SQLPOINTER rgbValue, SQLINTEGER cbValueMax, SQLINTEGER* pcbValue)
{
	return SQLBindParameter(m_hStmt, ipar, fParamType, fCType, fSqlType, cbColDef, ibScale, rgbValue, cbValueMax, pcbValue);
}


SQLRETURN NODBCHandler::GetData(SQLUSMALLINT ColumnNumber, SQLSMALLINT TargetType, SQLPOINTER TargetValue, SQLINTEGER BufferLength, SQLINTEGER* StrLen_or_IndPtr)
{
	return SQLGetData(m_hStmt, ColumnNumber, TargetType, TargetValue, BufferLength, StrLen_or_IndPtr);
}


SQLRETURN NODBCHandler::CloseCursor()
{
	return SQLCloseCursor(m_hStmt);
}


SQLRETURN NODBCHandler::PutData(SQLPOINTER Data, SQLINTEGER StrLen_or_Ind)
{
	return SQLPutData(m_hStmt, Data, StrLen_or_Ind);
}


SQLRETURN NODBCHandler::Fetch()
{
	return SQLFetch(m_hStmt);
}


SQLRETURN NODBCHandler::ParamData(SQLPOINTER* Value)
{
	return SQLParamData(m_hStmt, Value);
}


NODBCHandler::operator SQLHSTMT()
{
	return m_hStmt;
}


std::string NODBCHandler::GetErrorString()
{
	if( m_hStmt == SQL_NULL_HSTMT )
		return "unknown";

	std::string retstr;

	for( int iDiag = 1; iDiag < 10; ++iDiag )
	{
		char state[64] = {};
		char msg[1024] = {};
		int NativeError = 0;

		if( !SQL_SUCCEEDED(SQLGetDiagRecA(SQL_HANDLE_STMT, m_hStmt, iDiag, (SQLCHAR*)state, (SQLINTEGER*)&NativeError, (SQLCHAR*)msg, sizeof(msg), NULL)) )
			break; // error.

		retstr += msg;
	}

	return retstr;
}
