#include "AsyncDBWork/NODBCHandler.h"


NODBCHandler::NODBCHandler(NODBCCtrl& in_cODBCCtrl) // line 11
: m_vcODBCCtrl(in_cODBCCtrl)
{
	m_bOK = false;
	m_hStmt = SQL_NULL_HSTMT;

	if( this->NODBCHandler::Init() )
		m_bOK = true;
}


NODBCHandler::~NODBCHandler(void) // line 21
{
	if( m_hStmt != SQL_NULL_HSTMT )
	{
		SQLCloseCursor(m_hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
		m_hStmt = SQL_NULL_HSTMT;
	}
}


hook_method<bool (NODBCHandler::*)(void)> NODBCHandler::_Init(SERVER, "NODBCHandler::Init");
bool NODBCHandler::Init(void) // line 38
{
	return (this->*_Init)();

	SQLRETURN v1 = SQLAllocHandle(SQL_HANDLE_STMT, m_vcODBCCtrl, &m_hStmt);
	return ( SQL_SUCCEEDED(v1) );
}
