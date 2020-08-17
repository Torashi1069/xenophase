#include "shared/N2System/ODBC(open database connectivity)/N2ODBCHandler.h"


N2ODBCHandler::N2ODBCHandler(N2ODBCCtrl& in_cODBCCtrl)
: m_hStmt(SQL_NULL_HSTMT), m_vcODBCCtrl(in_cODBCCtrl)
{
	m_bOK = false;

	if( this->N2ODBCHandler::Init() )
		m_bOK = true;
}


N2ODBCHandler::~N2ODBCHandler()
{
	if( m_hStmt != SQL_NULL_HSTMT )
	{
		SQLCloseCursor(m_hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
		m_hStmt = SQL_NULL_HSTMT;
	}
}


bool N2ODBCHandler::isOK() const
{
	return m_bOK;
}


bool N2ODBCHandler::Init()
{
	return ( SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_STMT, m_vcODBCCtrl, &m_hStmt)) );
}


SQLRETURN N2ODBCHandler::ExecDirect(const std::string in_strQuery)
{
	return SQLExecDirectA(m_hStmt, (SQLCHAR*)in_strQuery.c_str(), SQL_NTS);
}


SQLRETURN N2ODBCHandler::UnBind()
{
	return SQLFreeStmt(m_hStmt, SQL_UNBIND);
}


SQLRETURN N2ODBCHandler::BindCol(SQLUSMALLINT ColumnNumber, SQLSMALLINT TargetType, SQLPOINTER TargetValue, SQLINTEGER BufferLength, SQLINTEGER* StrLen_or_Ind)
{
	return SQLBindCol(m_hStmt, ColumnNumber, TargetType, TargetValue, BufferLength, StrLen_or_Ind);
}


SQLRETURN N2ODBCHandler::Fetch()
{
	return SQLFetch(m_hStmt);
}


SQLRETURN N2ODBCHandler::BindParameter(SQLUSMALLINT ipar, SQLSMALLINT fParamType, SQLSMALLINT fCType, SQLSMALLINT fSqlType, SQLULEN cbColDef, SQLSMALLINT ibScale, SQLPOINTER rgbValue, SQLLEN cbValueMax, SQLLEN* pcbValue)
{
	return SQLBindParameter(m_hStmt, ipar, fParamType, fCType, fSqlType, cbColDef, ibScale, rgbValue, cbValueMax, pcbValue);
}


SQLRETURN N2ODBCHandler::PutData(SQLPOINTER Data, SQLLEN StrLen_or_Ind)
{
	return SQLPutData(m_hStmt, Data, StrLen_or_Ind);
}


N2ODBCHandler::operator SQLHSTMT()
{
	return m_hStmt;
}


SQLRETURN N2ODBCHandler::GetData(SQLUSMALLINT ColumnNumber, SQLSMALLINT TargetType, SQLPOINTER TargetValue, SQLLEN BufferLength, SQLLEN* StrLen_or_Ind)
{
	return SQLGetData(m_hStmt, ColumnNumber, TargetType, TargetValue, BufferLength, StrLen_or_Ind);
}


SQLRETURN N2ODBCHandler::CloseCursor()
{
	return SQLCloseCursor(m_hStmt);
}


SQLRETURN N2ODBCHandler::ParamData(SQLPOINTER* Value)
{
	return SQLParamData(m_hStmt, Value);
}


void N2ODBCHandler::OutputErrorString(const char* in_pSourceFileName, const int in_SourceLineNum, const char* in_pMessage)
{
	m_vcODBCCtrl.N2ODBCCtrl::OutputErrorString(SQL_HANDLE_STMT, m_hStmt, in_pSourceFileName, in_SourceLineNum, in_pMessage);
}
