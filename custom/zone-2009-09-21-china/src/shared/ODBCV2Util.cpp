#include "ErrorLog.h"
#include "ODBCV2Util.h"
#include "globals.hpp"
#include <odbcinst.h>
#undef SQLConfigDataSource
#undef SQLInstallerError


hook_ptr<CODBCV2Util*> CODBCV2Util::m_cpSelf(SERVER, "CODBCV2Util::m_cpSelf"); // = ?


CODBCV2Util::CODBCV2Util(void) // line 15
{
}


CODBCV2Util::~CODBCV2Util(void) // line 20
{
}


hook_method<static CODBCV2Util* (__cdecl *)(void)> CODBCV2Util::_GetObj(SERVER, "CODBCV2Util::GetObj");
CODBCV2Util* __cdecl CODBCV2Util::GetObj(void) // line 26
{
	return (CODBCV2Util::_GetObj)();

	//TODO
}


hook_method<mystd::string (CODBCV2Util::*)(const short in_HandleType, SQLHANDLE const in_Handle)> CODBCV2Util::_GetErrorString(SERVER, "CODBCV2Util::GetErrorString");
mystd::string CODBCV2Util::GetErrorString(const short in_HandleType, SQLHANDLE const in_Handle) // line 98
{
	return (this->*_GetErrorString)(in_HandleType, in_Handle);

	//TODO
}


//hook_method<bool (CODBCV2Util::*)(const mystd::string in_strDSN, const mystd::string in_ServerIP, const mystd::string in_strDBName)> CODBCV2Util::_AddSystemDSN(SERVER, "CODBCV2Util::AddSystemDSN");
bool CODBCV2Util::AddSystemDSN(const mystd::string in_strDSN, const mystd::string in_ServerIP, const mystd::string in_strDBName) // line ???
{
//	return (this->*_AddSystemDSN)(in_strDSN, in_ServerIP, in_strDBName);

	mystd::string strDSN = in_strDSN;
	mystd::string strServerIP = "Server=" + in_ServerIP;
	mystd::string strDBName = "Database=" + in_strDBName;
	mystd::string strNetwork = "Network=" + mystd::string("DBMSSOCN");

	char Buffer[512];
	memset(Buffer, 0, sizeof(Buffer));
	strcpy(Buffer, strDSN.c_str());
	strcat(Buffer, strServerIP.c_str());
	strcat(Buffer, strDBName.c_str());
	strcat(Buffer, strNetwork.c_str());

	if( SQLConfigDataSource(NULL, ODBC_ADD_SYS_DSN, "SQL Server", Buffer) == FALSE )
	{
		char errorMsg[513];
		memset(errorMsg, 0, sizeof(errorMsg));

		for( int i = 1; i <= 8; ++i )
		{
			DWORD errorCode = 0;

			SQLRETURN v8 = SQLInstallerError(i, &errorCode, errorMsg, sizeof(errorMsg) - 1, NULL);
			if( !SQL_SUCCEEDED(v8) )
				break;

			g_errorLogs->CErrorLog::CriticalErrorLog(errorMsg, 65, ".\\ODBCV2Util.cpp");
		}

		MessageBoxA(NULL, "Add System DSN Error", "Error", MB_OK);
		return false;
	}

	return true;
}
