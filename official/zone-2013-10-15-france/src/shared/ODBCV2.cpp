#include "shared/NCriticalErrorLog.h"
#include "shared/ODBCV2.h"


CODBCV2::CODBCV2()
{
	m_henv = SQL_NULL_HENV;
	m_hdbc = SQL_NULL_HDBC;
	m_cpConnector = NULL;
}


CODBCV2::~CODBCV2()
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


bool CODBCV2::SyncConnect()
{
	if( m_cpConnector == NULL )
		return false;

	m_cpConnector->CODBCV2Connector::SyncConnect();
	return m_cpConnector->CODBCV2Connector::isConnect();
}


void CODBCV2::AsyncConnect()
{
	if( m_cpConnector == NULL )
		return;

	m_cpConnector->CODBCV2Connector::AsyncConnect();
}


void CODBCV2::Disconnect()
{
	if( m_cpConnector == NULL )
		return;

	m_cpConnector->CODBCV2Connector::Disconnect();
}


SQLHDBC const CODBCV2::GetDBCHandle()
{
	if( m_cpConnector == NULL || !m_cpConnector->CODBCV2Connector::isConnect() )
		return false;
	
	return m_hdbc;
}


bool CODBCV2::Init(const std::string in_strDsnFile, const std::string in_strPassword, const CODBCV2Connector::enumConncetType in_eConnectType, const bool in_bConnect)
{
	if( m_henv != SQL_NULL_HENV || m_hdbc != SQL_NULL_HDBC )
		return false; // already initialized

	do { // try

	if( !SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_henv)) )
		break;

	if( !SQL_SUCCEEDED(SQLSetEnvAttr(m_henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)3, 0)) )
		break;

	if( !SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_DBC, m_henv, &m_hdbc)) )
		break;

	m_cpConnector = new CODBCV2Connector(m_henv, m_hdbc, in_strDsnFile, in_strPassword, in_eConnectType);
	if( m_cpConnector == NULL )
		break;

	if( in_bConnect )
	{
		m_cpConnector->CODBCV2Connector::SyncConnect();
		if( !m_cpConnector->CODBCV2Connector::isConnect() )
			break;
	}

	return true; // success.

	} while( 0 ); // finally

	char szError[1024] = {};
	char szState[1024] = {};
	SQLErrorA(m_henv, m_hdbc, SQL_NULL_HSTMT, (SQLCHAR*)szState, NULL, (SQLCHAR*)szError, countof(szError), NULL);
	MessageBoxA(NULL, szError, NULL, MB_OK);

	char temp[1024];
	sprintf_s(temp, countof(temp), "DBServer connect error:%s, :FileDSN:%s", szError, in_strDsnFile.c_str());
	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s", temp);
	MessageBoxA(NULL, temp, "db connect error", MB_OK);

	return false; // error.
}
