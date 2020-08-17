#include "AsyncDBWork/NODBCCtrl.h"
#include <sqlext.h>


NODBCCtrl::NODBCCtrl(void) // line 12
{
	m_bOK = false;

	if( this->NODBCCtrl::Init() )
		m_bOK = true;
}


NODBCCtrl::~NODBCCtrl(void) // line 21
{
	if( m_hDbc != SQL_NULL_HDBC )
	{
		SQLDisconnect(m_hDbc);
		SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
		m_hDbc = SQL_NULL_HDBC;
	}

	if( m_hEnv != SQL_NULL_HENV )
	{
		SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);
		m_hEnv = SQL_NULL_HENV;
	}
}


hook_method<bool (NODBCCtrl::*)(void)> NODBCCtrl::_Init(SERVER, "NODBCCtrl::Init");
bool NODBCCtrl::Init(void) // line 43
{
	return (this->*_Init)();

	m_hEnv = SQL_NULL_HENV;
	m_hDbc = SQL_NULL_HDBC;

	SQLRETURN v1 = SQLAllocHandle(SQL_HANDLE_ENV, (SQLPOINTER)SQL_NULL_HANDLE, &m_hEnv);
	if( !SQL_SUCCEEDED(v1) )
		return false;

	SQLRETURN v4 = SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	if( !SQL_SUCCEEDED(v4) )
		return false;

	return true;
}


//hook_method<SQLHDBC (NODBCCtrl::*)(void)> NODBCCtrl::_operator_SQLHDBC(SERVER, "??BNODBCCtrl@@QAEPAXXZ");
NODBCCtrl::operator SQLHDBC(void) // line ??
{
//	return( this->*_operator_SQLHDBC)();

	return m_hDbc;
}
