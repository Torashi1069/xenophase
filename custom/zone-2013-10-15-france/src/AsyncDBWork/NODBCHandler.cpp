#include "AsyncDBWork/NODBCHandler.h"


NODBCHandler::NODBCHandler(NODBCCtrl& in_cODBCCtrl)
: m_vcODBCCtrl(in_cODBCCtrl), m_hStmt(SQL_NULL_HSTMT), m_bOK(false)
{
	if( this->NODBCHandler::Init() )
		m_bOK = true;
}


NODBCHandler::~NODBCHandler()
{
	if( m_hStmt != SQL_NULL_HSTMT )
	{
		SQLCloseCursor(m_hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
		m_hStmt = SQL_NULL_HSTMT;
	}
}


bool NODBCHandler::isOK() const
{
	return m_bOK;
}


bool NODBCHandler::Init()
{
	return ( SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_STMT, m_vcODBCCtrl, &m_hStmt)) );
}


SQLRETURN NODBCHandler::ExecDirect(const std::string in_strQuery)
{
	return SQLExecDirectA(m_hStmt, (SQLCHAR*)in_strQuery.c_str(), SQL_NTS);
}


SQLRETURN NODBCHandler::UnBind()
{
	return SQLFreeStmt(m_hStmt, SQL_UNBIND);
}


SQLRETURN NODBCHandler::BindCol(SQLUSMALLINT ColumnNumber, SQLSMALLINT TargetType, SQLPOINTER TargetValue, SQLINTEGER BufferLength, SQLINTEGER* StrLen_or_Ind)
{
	return SQLBindCol(m_hStmt, ColumnNumber, TargetType, TargetValue, BufferLength, StrLen_or_Ind);
}


SQLRETURN NODBCHandler::Fetch()
{
	return SQLFetch(m_hStmt);
}


SQLRETURN NODBCHandler::BindParameter(SQLUSMALLINT ipar, SQLSMALLINT fParamType, SQLSMALLINT fCType, SQLSMALLINT fSqlType, SQLULEN cbColDef, SQLSMALLINT ibScale, SQLPOINTER rgbValue, SQLLEN cbValueMax, SQLLEN* pcbValue)
{
	return SQLBindParameter(m_hStmt, ipar, fParamType, fCType, fSqlType, cbColDef, ibScale, rgbValue, cbValueMax, pcbValue);
}


SQLRETURN NODBCHandler::PutData(SQLPOINTER Data, SQLLEN StrLen_or_Ind)
{
	return SQLPutData(m_hStmt, Data, StrLen_or_Ind);
}


NODBCHandler::operator SQLHSTMT()
{
	return m_hStmt;
}


SQLRETURN NODBCHandler::GetData(SQLUSMALLINT ColumnNumber, SQLSMALLINT TargetType, SQLPOINTER TargetValue, SQLLEN BufferLength, SQLLEN* StrLen_or_Ind)
{
	return SQLGetData(m_hStmt, ColumnNumber, TargetType, TargetValue, BufferLength, StrLen_or_Ind);
}


SQLRETURN NODBCHandler::CloseCursor()
{
	return SQLCloseCursor(m_hStmt);
}


SQLRETURN NODBCHandler::ParamData(SQLPOINTER* Value)
{
	return SQLParamData(m_hStmt, Value);
}


void NODBCHandler::OutputErrorString(const char* in_pSourceFileName, const int in_SourceLineNum, const char* in_pMessage)
{
	m_vcODBCCtrl.NODBCCtrl::OutputErrorString(SQL_HANDLE_STMT, m_hStmt, in_pSourceFileName, in_SourceLineNum, in_pMessage);
}
