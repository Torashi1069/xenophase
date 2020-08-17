#include "AsyncDBWork/NODBCCtrl.h"
#include "shared/NCriticalErrorLog.h"


NODBCCtrl::NODBCCtrl()
{
	m_bOK = false;

	if( this->NODBCCtrl::Init() )
		m_bOK = true;
}


NODBCCtrl::~NODBCCtrl()
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


bool NODBCCtrl::isOK() const
{
	return m_bOK;
}


bool NODBCCtrl::Init()
{
	m_hEnv = SQL_NULL_HENV;
	m_hDbc = SQL_NULL_HDBC;

	if( !SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv)) )
		return false;

	if( !SQL_SUCCEEDED(SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER)) )
		return false;

	return true;
}


bool NODBCCtrl::Connect(const std::string in_strConnectionStr)
{
	if( !SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDbc)) )
		return false;

	char CompleteConnectionString[1024] = {};
	if( !SQL_SUCCEEDED(SQLDriverConnectA(m_hDbc, NULL, (SQLCHAR*)in_strConnectionStr.c_str(), SQL_NTS, (SQLCHAR*)CompleteConnectionString, countof(CompleteConnectionString), NULL, SQL_DRIVER_NOPROMPT)) )
	{
		SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
		m_hDbc = SQL_NULL_HDBC;
		return false;
	}

	return true;
}


void NODBCCtrl::Disconnect()
{
	if( m_hDbc != SQL_NULL_HDBC )
	{
		SQLDisconnect(m_hDbc);
		SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
		m_hDbc = SQL_NULL_HDBC;
	}
}


NODBCCtrl::operator SQLHDBC()
{
	return m_hDbc;
}


void NODBCCtrl::OutputErrorString(const short in_Type, void* const in_Handle, const char* in_pSourceFileName, const int in_SourceLineNum, const char* in_pMessage)
{
	const char* FileName = ( strrchr(in_pSourceFileName, '\\') != NULL ) ? strrchr(in_pSourceFileName, '\\') : in_pSourceFileName;
	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(FileName, in_SourceLineNum, "%s", in_pMessage);

	if( in_Handle == NULL )
		return;

	char state[64] = {};
	char msg[1024] = {};
	SQLINTEGER NativeError = 0;

	for( int i = 1; i < 10; ++i )
	{
		if( !SQL_SUCCEEDED(SQLGetDiagRecA(SQL_HANDLE_STMT, in_Handle, i, (SQLCHAR*)state, &NativeError, (SQLCHAR*)msg, countof(msg), NULL)) )
			break;

		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(FileName, in_SourceLineNum, "%s, %d, %s, %d", state, NativeError, msg, countof(msg));
	}
}
