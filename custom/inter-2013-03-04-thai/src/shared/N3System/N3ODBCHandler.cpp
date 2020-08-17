#include "shared/N3System/N3ODBCHandler.h"


N3ODBCHandler::N3ODBCHandler(N3ODBCCtrl& in_cODBCCtrl)
: m_hStmt(SQL_NULL_HSTMT), m_vcODBCCtrl(in_cODBCCtrl)
{
	m_bOK = false;

	if( this->N3ODBCHandler::Init() )
		m_bOK = true;
}


N3ODBCHandler::~N3ODBCHandler()
{
	if( m_hStmt != SQL_NULL_HSTMT )
	{
		SQLCloseCursor(m_hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
		m_hStmt = SQL_NULL_HSTMT;
	}
}


bool N3ODBCHandler::isOK() const
{
	return m_bOK;
}


bool N3ODBCHandler::Init()
{
	return ( SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_STMT, m_vcODBCCtrl, &m_hStmt)) );
}


SQLRETURN N3ODBCHandler::ExecDirect(const std::string in_strQuery)
{
	return SQLExecDirectA(m_hStmt, (SQLCHAR*)in_strQuery.c_str(), SQL_NTS);
}


SQLRETURN N3ODBCHandler::UnBind()
{
	return SQLFreeStmt(m_hStmt, SQL_UNBIND);
}


SQLRETURN N3ODBCHandler::BindCol(SQLUSMALLINT ColumnNumber, SQLSMALLINT TargetType, SQLPOINTER TargetValue, SQLINTEGER BufferLength, SQLINTEGER* StrLen_or_Ind)
{
	return SQLBindCol(m_hStmt, ColumnNumber, TargetType, TargetValue, BufferLength, StrLen_or_Ind);
}


SQLRETURN N3ODBCHandler::Fetch()
{
	return SQLFetch(m_hStmt);
}


SQLRETURN N3ODBCHandler::BindParameter(SQLUSMALLINT ipar, SQLSMALLINT fParamType, SQLSMALLINT fCType, SQLSMALLINT fSqlType, SQLULEN cbColDef, SQLSMALLINT ibScale, SQLPOINTER rgbValue, SQLLEN cbValueMax, SQLLEN* pcbValue)
{
	return SQLBindParameter(m_hStmt, ipar, fParamType, fCType, fSqlType, cbColDef, ibScale, rgbValue, cbValueMax, pcbValue);
}


SQLRETURN N3ODBCHandler::PutData(SQLPOINTER Data, SQLLEN StrLen_or_Ind)
{
	return SQLPutData(m_hStmt, Data, StrLen_or_Ind);
}


N3ODBCHandler::operator SQLHSTMT()
{
	return m_hStmt;
}


SQLRETURN N3ODBCHandler::GetData(SQLUSMALLINT ColumnNumber, SQLSMALLINT TargetType, SQLPOINTER TargetValue, SQLLEN BufferLength, SQLLEN* StrLen_or_Ind)
{
	return SQLGetData(m_hStmt, ColumnNumber, TargetType, TargetValue, BufferLength, StrLen_or_Ind);
}


SQLRETURN N3ODBCHandler::CloseCursor()
{
	return SQLCloseCursor(m_hStmt);
}


SQLRETURN N3ODBCHandler::ParamData(SQLPOINTER* Value)
{
	return SQLParamData(m_hStmt, Value);
}


void N3ODBCHandler::OutputErrorString(const char* in_pSourceFileName, const int in_SourceLineNum, const char* in_pMessage)
{
	m_vcODBCCtrl.N3ODBCCtrl::OutputErrorString(SQL_HANDLE_STMT, m_hStmt, in_pSourceFileName, in_SourceLineNum, in_pMessage);
}


std::string N3ODBCHandler::GetErrorString()
{
	return m_vcODBCCtrl.N3ODBCCtrl::GetErrorString(SQL_HANDLE_STMT, m_hStmt);
}
