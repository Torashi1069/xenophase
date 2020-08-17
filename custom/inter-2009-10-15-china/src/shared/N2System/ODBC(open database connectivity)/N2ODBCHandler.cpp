#include "N2System/ODBC(open database connectivity)/N2ODBCHandler.h"
#include <sql.h>
#include <sqlext.h>


N2ODBCHandler::N2ODBCHandler(N2ODBCCtrl& in_cODBCCtrl) // line 8-14
: m_vcODBCCtrl(in_cODBCCtrl)
{
	m_bOK = false;
	m_hStmt = SQL_NULL_HSTMT;

	if( this->N2ODBCHandler::Init() )
		m_bOK = true;
}


N2ODBCHandler::~N2ODBCHandler(void) // line 18-25
{
	if( m_hStmt != SQL_NULL_HSTMT )
	{
		SQLCloseCursor(m_hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
		m_hStmt = SQL_NULL_HSTMT;
	}
}


hook_method<bool (N2ODBCHandler::*)(void) const> N2ODBCHandler::_isOK(SERVER, "N2ODBCHandler::isOK");
bool N2ODBCHandler::isOK(void) const // line 28-30
{
	return (this->*_isOK)();

	return m_bOK;
}


hook_method<bool (N2ODBCHandler::*)(void)> N2ODBCHandler::_Init(SERVER, "N2ODBCHandler::Init");
bool N2ODBCHandler::Init(void) // line 34-39
{
	return (this->*_Init)();

	return ( SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_STMT, m_vcODBCCtrl, &m_hStmt)) );
}


hook_method<SQLRETURN (N2ODBCHandler::*)(const mystd::string in_strQuery)> N2ODBCHandler::_ExecDirect(SERVER, "N2ODBCHandler::ExecDirect");
SQLRETURN N2ODBCHandler::ExecDirect(const mystd::string in_strQuery) // line 43-45
{
	return (this->*_ExecDirect)(in_strQuery);

	return SQLExecDirectA(m_hStmt, (SQLCHAR*)in_strQuery.c_str(), SQL_NTS);
}


hook_method<SQLRETURN (N2ODBCHandler::*)(void)> N2ODBCHandler::_UnBind(SERVER, "N2ODBCHandler::UnBind");
SQLRETURN N2ODBCHandler::UnBind(void) // line 49-51
{
	return (this->*_UnBind)();

	return SQLFreeStmt(m_hStmt, SQL_UNBIND);
}


hook_method<SQLRETURN (N2ODBCHandler::*)(unsigned short ColumnNumber, short TargetType, void* TargetValue, long BufferLength, long* StrLen_or_Ind)> N2ODBCHandler::_BindCol(SERVER, "N2ODBCHandler::BindCol");
SQLRETURN N2ODBCHandler::BindCol(unsigned short ColumnNumber, short TargetType, void* TargetValue, long BufferLength, long* StrLen_or_Ind) // line 61-68
{
	return (this->*_BindCol)(ColumnNumber, TargetType, TargetValue, BufferLength, StrLen_or_Ind);

	return SQLBindCol(m_hStmt, ColumnNumber, TargetType, TargetValue, BufferLength, StrLen_or_Ind);
}


hook_method<SQLRETURN (N2ODBCHandler::*)(unsigned short ipar, short fParamType, short fCType, short fSqlType, unsigned long cbColDef, short ibScale, void* rgbValue, long cbValueMax, long* pcbValue)> N2ODBCHandler::_BindParameter(SERVER, "N2ODBCHandler::BindParameter");
SQLRETURN N2ODBCHandler::BindParameter(unsigned short ipar, short fParamType, short fCType, short fSqlType, unsigned long cbColDef, short ibScale, void* rgbValue, long cbValueMax, long* pcbValue) // line 96-98
{
	return (this->*_BindParameter)(ipar, fParamType, fCType, fSqlType, cbColDef, ibScale, rgbValue, cbValueMax, pcbValue);

	return SQLBindParameter(m_hStmt, ipar, fParamType, fCType, fSqlType, cbColDef, ibScale, rgbValue, cbValueMax, pcbValue);
}


hook_method<SQLRETURN (N2ODBCHandler::*)(unsigned short ColumnNumber, short TargetType, void* TargetValue, long BufferLength, long* StrLen_or_Ind)> N2ODBCHandler::_GetData(SERVER, "N2ODBCHandler::GetData");
SQLRETURN N2ODBCHandler::GetData(unsigned short ColumnNumber, short TargetType, void* TargetValue, long BufferLength, long* StrLen_or_Ind) // line 119-121
{
	return (this->*_GetData)(ColumnNumber, TargetType, TargetValue, BufferLength, StrLen_or_Ind);

	return SQLGetData(m_hStmt, ColumnNumber, TargetType, TargetValue, BufferLength, StrLen_or_Ind);
}


hook_method<SQLRETURN (N2ODBCHandler::*)(void)> N2ODBCHandler::_CloseCursor(SERVER, "N2ODBCHandler::CloseCursor");
SQLRETURN N2ODBCHandler::CloseCursor(void) // line 125-127
{
	return (this->*_CloseCursor)();

	return SQLCloseCursor(m_hStmt);
}


hook_method<SQLRETURN (N2ODBCHandler::*)(void* Data, long StrLen_or_Ind)> N2ODBCHandler::_PutData(SERVER, "N2ODBCHandler::PutData");
SQLRETURN N2ODBCHandler::PutData(void* Data, long StrLen_or_Ind) // line 101-103
{
	return (this->*_PutData)(Data, StrLen_or_Ind);

	return SQLPutData(m_hStmt, Data, StrLen_or_Ind);
}


hook_method<SQLRETURN (N2ODBCHandler::*)(void)> N2ODBCHandler::_Fetch(SERVER, "N2ODBCHandler::Fetch");
SQLRETURN N2ODBCHandler::Fetch(void) // line 72-75
{
	return (this->*_Fetch)();

	return SQLFetch(m_hStmt);
}


hook_method<SQLRETURN (N2ODBCHandler::*)(void** Value)> N2ODBCHandler::_ParamData(SERVER, "N2ODBCHandler::ParamData");
SQLRETURN N2ODBCHandler::ParamData(void** Value) // line 131-133
{
	return (this->*_ParamData)(Value);

	return SQLParamData(m_hStmt, Value);
}


//hook_method<SQLHSTMT (N2ODBCHandler::*)(void)> N2ODBCHandler::_operator_SQLHSTMT(SERVER, "??BN2ODBCHandler@@QAEPAXXZ");
N2ODBCHandler::operator SQLHSTMT(void) // line ???
{
//	return (this->*_operator_SQLHSTMT)();

	return m_hStmt;
}


hook_method<void (N2ODBCHandler::*)(const char* in_pSourceFileName, const int in_SourceLineNum, const char* in_pMessage)> N2ODBCHandler::_OutputErrorString(SERVER, "N2ODBCHandler::OutputErrorString");
void N2ODBCHandler::OutputErrorString(const char* in_pSourceFileName, const int in_SourceLineNum, const char* in_pMessage) // line 139-146
{
	return (this->*_OutputErrorString)(in_pSourceFileName, in_SourceLineNum, in_pMessage);

	m_vcODBCCtrl.N2ODBCCtrl::OutputErrorString(SQL_HANDLE_STMT, m_hStmt, in_pSourceFileName, in_SourceLineNum, in_pMessage);
}
