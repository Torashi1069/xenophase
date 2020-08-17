#include "ODBCV2Handler.h"
#include "ODBCV2Util.h"
#include "ErrorLog.h"
#include "globals.hpp"


CODBCV2Handler::CODBCV2Handler(CODBCV2* in_cpODBCV2, const bool in_bReqAutoAsyncConnectWhenError)
: m_bReqAutoAsyncConnectWhenError(in_bReqAutoAsyncConnectWhenError), m_vcpODBCV2(in_cpODBCV2), m_hStmt(SQL_NULL_HSTMT), m_bError(false)
{
	SQLHDBC v3 = in_cpODBCV2->CODBCV2::GetDBCHandle();
	if( v3 == SQL_NULL_HDBC )
	{
		m_bError = true;
		return;
	}

	SQLRETURN v7 = SQLAllocHandle(SQL_HANDLE_STMT, v3, &m_hStmt);
	if( !SQL_SUCCEEDED(v7) )
	{
		m_bError = true;
		mystd::string strError = CODBCV2Util::GetObj()->CODBCV2Util::GetErrorString(SQL_HANDLE_STMT, m_hStmt);
		g_errorLogs->CErrorLog::CriticalErrorLog(strError.c_str(), 33, ".\\ODBCV2Handler.cpp");
	}
}


CODBCV2Handler::~CODBCV2Handler(void)
{
	if( m_hStmt != NULL )
	{
		SQLCloseCursor(m_hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
		m_hStmt = SQL_NULL_HSTMT;
	}

	if( m_bError && m_bReqAutoAsyncConnectWhenError )
	{
		m_vcpODBCV2->CODBCV2::Disconnect();
		m_vcpODBCV2->CODBCV2::AsyncConnect();
	}
}


hook_method<short (CODBCV2Handler::*)(unsigned short ipar, short fParamType, short fCType, short fSqlType, unsigned long cbColDef, short ibScale, void* rgbValue, long cbValueMax, long* pcbValue)> CODBCV2Handler::_BindParameter(SERVER, "CODBCV2Handler::BindParameter");
SQLRETURN CODBCV2Handler::BindParameter(unsigned short ipar, short fParamType, short fCType, short fSqlType, unsigned long cbColDef, short ibScale, void* rgbValue, long cbValueMax, long* pcbValue)
{
	return (this->*_BindParameter)(ipar, fParamType, fCType, fSqlType, cbColDef, ibScale, rgbValue, cbValueMax, pcbValue);

	//TODO
}


hook_method<short (CODBCV2Handler::*)(unsigned char* StatementText, long TextLength)> CODBCV2Handler::_ExecDirect(SERVER, "CODBCV2Handler::ExecDirect");
SQLRETURN CODBCV2Handler::ExecDirect(unsigned char* StatementText, long TextLength)
{
	return (this->*_ExecDirect)(StatementText, TextLength);

	//TODO
}


hook_method<short (CODBCV2Handler::*)(unsigned short ColumnNumber, short TargetType, void* TargetValue, long BufferLength, long* StrLen_or_Ind)> CODBCV2Handler::_BindCol(SERVER, "CODBCV2Handler::BindCol");
SQLRETURN CODBCV2Handler::BindCol(unsigned short ColumnNumber, short TargetType, void* TargetValue, long BufferLength, long* StrLen_or_Ind)
{
	return (this->*_BindCol)(ColumnNumber, TargetType, TargetValue, BufferLength, StrLen_or_Ind);

	//TODO
}


hook_method<SQLRETURN (CODBCV2Handler::*)(void)> CODBCV2Handler::_Fetch(SERVER, "CODBCV2Handler::Fetch");
SQLRETURN CODBCV2Handler::Fetch(void)
{
	return (this->*_Fetch)();

	//TODO
}


//hook_method<SQLHSTMT (CODBCV2Handler::*)(void)> CODBCV2Handler::_operator_SQLHSTMT(SERVER, "??BCODBCV2Handler@@QAEPAXXZ");
CODBCV2Handler::operator SQLHSTMT(void)
{
//	return (this->*_operator_SQLHSTMT)();

	return m_hStmt;
}
