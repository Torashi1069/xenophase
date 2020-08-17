#include "DBScriptInfo.h"
#include "ErrorLog.h"
#include "ODBCV2.h"
#include "ODBCV2Connector.h"
#include "ODBCV2Handler.h"
#include "ODBCV2Util.h"
#include "CUIDGenerator.hpp"
#include "globals.hpp"
#include <sqlext.h>


hook_ptr<CUIDGenerator *> CUIDGenerator::m_cpSelf(SERVER, "CUIDGenerator::m_cpSelf"); // = ?


CUIDGenerator::CUIDGenerator(void) // line 24
{
	m_ServerBootSequeceNum = 0;
	m_SequenceNum = -1;
	m_bOK = true;
}


CUIDGenerator::~CUIDGenerator(void) // line 34
{
}


hook_method<bool (CUIDGenerator::*)(void)> CUIDGenerator::_LoadBootingSequenceNum(SERVER, "CUIDGenerator::LoadBootingSequenceNum");
bool CUIDGenerator::LoadBootingSequenceNum(void) // line 48
{
	return (this->*_LoadBootingSequenceNum)();

	CODBCV2 ConfigurationDB;
	const char* v1 = g_dbScriptInfo->CDBScriptInfo::Search("character");

	if( !ConfigurationDB.CODBCV2::Init(v1, "character", g_dbPWD, v1, CODBCV2Connector::DSN_CONNECT_TYPE, true) )
		return false;

	CODBCV2Handler Handler(&ConfigurationDB, false);
	SQLRETURN v6 = Handler.CODBCV2Handler::ExecDirect((unsigned char*)"{call usp_get_new_svr_boot_squence_num}", SQL_NTS);
	if( !SQL_SUCCEEDED(v6) )
	{
		mystd::string strError = CODBCV2Util::GetObj()->CODBCV2Util::GetErrorString(SQL_HANDLE_STMT, Handler);
		g_errorLogs->CErrorLog::CriticalErrorLog(strError.c_str(), 62, ".\\UIDGeneratorV4.cpp");
		return false;
	}

	long cbInt = 0;
	long int error_code = 0;
	Handler.CODBCV2Handler::BindCol(1, SQL_C_SLONG, &error_code, 0, &cbInt);
	Handler.CODBCV2Handler::BindCol(2, SQL_C_SLONG, &m_ServerBootSequeceNum, 0, &cbInt);
	SQLRETURN v9 = Handler.CODBCV2Handler::Fetch();
	if( !SQL_SUCCEEDED(v9) )
	{
		mystd::string strError = CODBCV2Util::GetObj()->CODBCV2Util::GetErrorString(SQL_HANDLE_STMT, Handler);
		g_errorLogs->CErrorLog::CriticalErrorLog(strError.c_str(), 75, ".\\UIDGeneratorV4.cpp");
		return false;
	}

	switch( error_code )
	{
	case 0:
		g_errorLogs->CErrorLog::CriticalErrorLogFmt(".\\UIDGeneratorV4.cpp", 81, "Read SvrBootSequnceNum=%d", m_ServerBootSequeceNum);
		return true;
	case 1:
		g_errorLogs->CErrorLog::CriticalErrorLog("overflow server booting sequence number", 84, ".\\UIDGeneratorV4.cpp");
		return false;
	case 2:
		g_errorLogs->CErrorLog::CriticalErrorLog("unknown error found", 88, ".\\UIDGeneratorV4.cpp");
		return false;
	case 3:
		g_errorLogs->CErrorLog::CriticalErrorLog("table or data record error in database", 92, ".\\UIDGeneratorV4.cpp");
		return false;
	default:
		g_errorLogs->CErrorLog::CriticalErrorLog("unknown error code found", 96, ".\\UIDGeneratorV4.cpp");
		return false;
	}
}


hook_method<static CUIDGenerator* (__cdecl *)(void)> CUIDGenerator::_GetObj(SERVER, "CUIDGenerator::GetObj");
CUIDGenerator* __cdecl CUIDGenerator::GetObj(void) // line 134
{
	return (CUIDGenerator::_GetObj)();

	if( m_cpSelf == NULL )
		m_cpSelf = new CUIDGenerator();

	return m_cpSelf;
}


hook_method<__int64 (CUIDGenerator::*)(void)> CUIDGenerator::_Get(SERVER, "CUIDGenerator::Get");
__int64 CUIDGenerator::Get(void) // line 117
{
	return (this->*_Get)();

	if( m_SequenceNum < 0xFFFFFFFF )
	{
		m_SequenceNum = m_SequenceNum + 1;
	}
	else
	{
		if( !this->CUIDGenerator::LoadBootingSequenceNum() )
		{
			MessageBoxA(NULL, "CUIDGenerator::LoadBootingSequenceNum()\n must be server restart...", "UID Generator Error", MB_OK);
			exit(EXIT_SUCCESS);
		}

		m_SequenceNum = 0;
	}

	return m_SequenceNum + ((unsigned __int64)m_ServerBootSequeceNum << 32);
}


//hook_method<bool (CUIDGenerator::*)(void)> CUIDGenerator::_isOK(SERVER, "CUIDGenerator::isOK");
bool CUIDGenerator::isOK(void) // line ???
{
//	return (this->*_isOK)();

	return m_bOK;
}


hook_method<bool (CUIDGenerator::*)(void)> CUIDGenerator::_Init(SERVER, "CUIDGenerator::Init");
bool CUIDGenerator::Init(void) // line 105
{
	return (this->*_Init)();

	bool result;

	if( this->CUIDGenerator::LoadBootingSequenceNum() )
	{
		m_SequenceNum = 0;
		result = true;
	}
	else
	{
		MessageBoxA(NULL, "CUIDGenerator::Init() Error check critical log file", "UID Generator Error", MB_OK);
		result = false;
	}

	return result;
}
