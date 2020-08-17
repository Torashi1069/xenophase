#include "shared/NCriticalErrorLog.h"
#include "shared/ODBCV2Util.h"


/// singleton instance
CODBCV2Util*& CODBCV2Util::m_cpSelf = VTOR<CODBCV2Util*>(DetourFindFunction(EXEPATH(), "CODBCV2Util::m_cpSelf"));


CODBCV2Util::CODBCV2Util()
{
}


CODBCV2Util::~CODBCV2Util()
{
}


CODBCV2Util* CODBCV2Util::GetObj()
{
	if( m_cpSelf == NULL )
		m_cpSelf = new CODBCV2Util();

	return m_cpSelf;
}


bool CODBCV2Util::AddSystemDSN(const std::string in_strDSN, const std::string in_ServerIP, const std::string in_strDBName)
{
	std::string strDSN = "DSN=" + in_strDSN;
	std::string strServerIP = "Server=" + in_ServerIP;
	std::string strDBName = "Database=" + in_strDBName;
	std::string strNetwork = "Network=DBMSSOCN";

	char Buffer[512] = {};
	char* p = Buffer;
	sprintf(p, "%s", strDSN.c_str()); p += strDSN.size() + 1;
	sprintf(p, "%s", strServerIP.c_str()); p += strServerIP.size() + 1;
	sprintf(p, "%s", strDBName.c_str()); p += strDBName.size() + 1;
	sprintf(p, "%s", strNetwork.c_str()); p += strNetwork.size() + 1;

	if( !SQLConfigDataSource(NULL, ODBC_ADD_SYS_DSN, "SQL Server", Buffer) )
	{
		DWORD errorCode = 0;
		char errorMsg[512+1] = {};

		for( int i = 1; i <= 8; ++i )
		{
			if( !SQL_SUCCEEDED(SQLInstallerError(i, &errorCode, errorMsg, countof(errorMsg)-1, NULL)) )
				break;

			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s", errorMsg);
		}

		MessageBoxA(NULL, "Add System DSN Error", "Error", MB_OK);
		return false;
	}

	return true;
}


std::string CODBCV2Util::GetErrorString(const SQLSMALLINT in_HandleType, const SQLHANDLE in_Handle)
{
	std::string result = "";

	SQLINTEGER iDiagNum;
	SQLSMALLINT DiagNumLen = 0;
	SQLGetDiagField(in_HandleType, in_Handle, 0, SQL_DIAG_NUMBER, &iDiagNum, 0, &DiagNumLen); //NOTE: result not used

	for( int iDiag = 1; iDiag < 10; ++iDiag )
	{
		char SqlState[5+1] = {};
		SQLINTEGER NativeError = 0;
		char Msg[255] = {};
		SQLSMALLINT MsgLen = 0;

		if( !SQL_SUCCEEDED(SQLGetDiagRecA(in_HandleType, in_Handle, iDiag, (SQLCHAR*)SqlState, &NativeError, (SQLCHAR*)Msg, countof(Msg), &MsgLen)) )
			break;

		result += "[" + std::string(SqlState) + "]" + std::string(Msg);
	}

	return result;
}
