#include "shared/NCriticalErrorLog.h"
#include "shared/N3System/N3ODBCCtrl.h"


N3ODBCCtrl::N3ODBCCtrl()
{
	m_bConnect = false;
	m_bOK = false;

	if( this->N3ODBCCtrl::Init() )
		m_bOK = true;
}


N3ODBCCtrl::~N3ODBCCtrl()
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


bool N3ODBCCtrl::isOK() const
{
	return m_bOK;
}


bool N3ODBCCtrl::Init()
{
	m_hDbc = SQL_NULL_HDBC;
	m_hEnv = SQL_NULL_HENV;

	if( !SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv)) )
		return false;

	if( !SQL_SUCCEEDED(SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER)) )
		return false;

	m_bConnect = false;
	return true;
}


bool N3ODBCCtrl::Connect(const std::string in_strConnectionStr)
{
	if( m_bConnect == true )
		return false;

	if( !SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDbc)) )
		return false;

	char CompleteConnectionString[1024] = {};
	if( !SQL_SUCCEEDED(SQLDriverConnectA(m_hDbc, NULL, (SQLCHAR*)in_strConnectionStr.c_str(), SQL_NTS, (SQLCHAR*)CompleteConnectionString, countof(CompleteConnectionString), NULL, SQL_DRIVER_NOPROMPT)) )
	{
		char state[64] = {};
		char msg[1024] = {};
		SQLINTEGER NativeError = 0;

		for( int i = 1; i < 10; ++i )
		{
			if( !SQL_SUCCEEDED(SQLGetDiagRecA(SQL_HANDLE_DBC, m_hDbc, i, (SQLCHAR*)state, &NativeError, (SQLCHAR*)msg, countof(msg), NULL)) )
				break;

			Sleep(0); //FIXME: huh.
		}

		SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
		m_hDbc = SQL_NULL_HDBC;
		return false;
	}

	m_bConnect = true;
	return true;
}


void N3ODBCCtrl::Disconnect()
{
	if( m_hDbc != SQL_NULL_HDBC )
	{
		SQLDisconnect(m_hDbc);
		SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
		m_hDbc = SQL_NULL_HDBC;
	}

	m_bConnect = false;
}


N3ODBCCtrl::operator SQLHDBC()
{
	return m_hDbc;
}


const bool N3ODBCCtrl::isConnect()
{
	return m_bConnect;
}


void N3ODBCCtrl::OutputErrorString(const SQLSMALLINT in_Type, const SQLHANDLE in_Handle, const char* in_pSourceFileName, const int in_SourceLineNum, const char* in_pMessage)
{
	if( in_Handle == SQL_NULL_HANDLE )
		return;

	char state[64] = {};
	char msg[1024] = {};
	SQLINTEGER NativeError = 0;

	for( int i = 1; i < 10; ++i )
	{
		if( !SQL_SUCCEEDED(SQLGetDiagRecA(in_Type, in_Handle, i, (SQLCHAR*)state, &NativeError, (SQLCHAR*)msg, countof(msg), NULL)) )
			break;

		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(in_pSourceFileName, in_SourceLineNum, "%s, %d, %s, %d", state, NativeError, msg, countof(msg));
	}
}


std::string N3ODBCCtrl::GetErrorString(const SQLSMALLINT in_HandleType, const SQLHANDLE in_Handle)
{
	std::string result = "";

	SQLINTEGER iDiagNum = 0;
	SQLSMALLINT DiagNumLen = 0;
	SQLGetDiagField(in_HandleType, in_Handle, 0, SQL_DIAG_NUMBER, &iDiagNum, 0, &DiagNumLen); //NOTE: result not used

	for( int iDiag = 1; iDiag < 10; ++iDiag )
	{
		SQLCHAR SqlState[5+1] = {};
		SQLINTEGER NativeError = 0;
		SQLCHAR Msg[255] = {};
		SQLSMALLINT MsgLen = 0;

		if( !SQL_SUCCEEDED(SQLGetDiagRecA(in_HandleType, in_Handle, iDiag, SqlState, &NativeError, Msg, countof(Msg), &MsgLen)) )
			break;

		result += std::string("[") + std::string((char*)SqlState) + std::string("]") + std::string((char*)Msg);
	}

	return result;
}
