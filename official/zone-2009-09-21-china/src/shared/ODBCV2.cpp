#include "ODBCV2.h"
#include "ErrorLog.h"
#include "globals.hpp"


CODBCV2::CODBCV2(void) // line 18
{
	m_henv = SQL_NULL_HENV;
	m_hdbc = SQL_NULL_HDBC;
	m_cpConnector = NULL;
}


CODBCV2::~CODBCV2(void) // line 27
{
	if( m_cpConnector != NULL )
	{
		delete m_cpConnector;
		m_cpConnector = NULL;
	}

	if( m_hdbc != SQL_NULL_HDBC )
	{
		SQLFreeHandle(SQL_HANDLE_DBC, m_hdbc);
		m_hdbc = SQL_NULL_HDBC;
	}

	if( m_henv != SQL_NULL_HENV )
	{
		SQLFreeHandle(SQL_HANDLE_ENV, m_henv);
		m_henv = SQL_NULL_HENV;
	}
}


hook_method<bool (CODBCV2::*)(const mystd::string in_strDSN, const mystd::string in_strUserID, const mystd::string in_strPassword, const mystd::string in_strDBName, const enum CODBCV2Connector::enumConnectType in_eConnectType, const bool in_bConnect)> CODBCV2::_Init(SERVER, "CODBCV2::Init");
bool CODBCV2::Init(const mystd::string in_strDSN, const mystd::string in_strUserID, const mystd::string in_strPassword, const mystd::string in_strDBName, const enum CODBCV2Connector::enumConnectType in_eConnectType, const bool in_bConnect) // line 99
{
	return (this->*_Init)(in_strDSN, in_strUserID, in_strPassword, in_strDBName, in_eConnectType, in_bConnect);

	if( m_henv || m_hdbc )
		return false;

	SQLRETURN retcode;
	if((retcode = SQLAllocHandle(1, 0, &m_henv))               , !SQL_SUCCEEDED(retcode)
	|| (retcode = SQLSetEnvAttr(m_henv, 200, (SQLPOINTER)3, 0)), !SQL_SUCCEEDED(retcode)
	|| (retcode = SQLAllocHandle(2, m_henv, &m_hdbc))          , !SQL_SUCCEEDED(retcode)
	|| (m_cpConnector = new CODBCV2Connector(m_henv, m_hdbc, in_strDSN, in_strUserID, in_strPassword, in_strDBName, in_eConnectType)), (m_cpConnector == NULL)
	|| in_bConnect == 1 && (m_cpConnector->CODBCV2Connector::SyncConnect(), !m_cpConnector->CODBCV2Connector::isConnect()) )
	{
		char szError[1024];
		char szState[1024];
		memset(szError, 0, sizeof(szError));
		memset(szState, 0, sizeof(szState));
		SQLError(m_henv, m_hdbc, 0, (SQLCHAR*)szState, NULL, (SQLCHAR*)szError, sizeof(szError), NULL);
		MessageBoxA(NULL, szError, 0, MB_OK);

		char temp[1024];
		sprintf(temp, "DBServer connect error:%s, :DB:%s, UID:%s\n", in_strDSN.c_str(), in_strDBName.c_str(), in_strUserID.c_str());
		g_errorLogs->CErrorLog::CriticalErrorLog(temp, 139, ".\\ODBCV2.cpp");
		MessageBoxA(0, temp, "db connect error", 0);
		return false;
	}

	return true;
}


hook_method<SQLHDBC const (CODBCV2::*)(void)> CODBCV2::_GetDBCHandle(SERVER, "CODBCV2::GetDBCHandle");
SQLHDBC const CODBCV2::GetDBCHandle(void) // line 76
{
	return (this->*_GetDBCHandle)();

	if( m_cpConnector != NULL && m_cpConnector->CODBCV2Connector::isConnect() )
		return m_hdbc;
	else
		return NULL;
}


hook_method<void (CODBCV2::*)(void)> CODBCV2::_Disconnect(SERVER, "CODBCV2::Disconnect");
void CODBCV2::Disconnect(void) // line 69
{
	return (this->*_Disconnect)();

	if( m_cpConnector == NULL )
		return;

	m_cpConnector->CODBCV2Connector::Disconnect();
}


hook_method<void (CODBCV2::*)(void)> CODBCV2::_AsyncConnect(SERVER, "CODBCV2::AsyncConnect");
void CODBCV2::AsyncConnect(void) // line 62
{
	return (this->*_AsyncConnect)();

	if( m_cpConnector == NULL )
		return;

	m_cpConnector->CODBCV2Connector::AsyncConnect();
}


hook_method<bool (CODBCV2::*)(void)> CODBCV2::_SyncConnect(SERVER, "CODBCV2::SyncConnect");
bool CODBCV2::SyncConnect(void) // line 51
{
	return (this->*_SyncConnect)();

	if( m_cpConnector == NULL )
		return false;

	m_cpConnector->CODBCV2Connector::SyncConnect();
	return m_cpConnector->CODBCV2Connector::isConnect();
}
