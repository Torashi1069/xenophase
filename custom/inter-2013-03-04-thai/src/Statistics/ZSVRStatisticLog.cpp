#include "shared/CDateTime.h"
#include "shared/N2System/ODBC(open database connectivity)/N2ODBCHandler.h"
#include "Statistics/ZSVRStatisticLog.h"


CZSVRStatisticLog::CZSVRStatisticLog(const time_t in_Date, const int in_ZSID, const int in_PlayerNum, const int in_NPCNum, const int in_MemoryKBytes, const int in_TotalServiceMapNum, const int in_ServiceInstantMapNum)
: m_Date(in_Date), m_ZSID(in_ZSID), m_PlayerNum(in_PlayerNum), m_NPCNum(in_NPCNum), m_MemoryKBytes(in_MemoryKBytes), m_TotalServiceMapNum(in_TotalServiceMapNum), m_ServiceInstantMapNum(in_ServiceInstantMapNum)
{
}


CZSVRStatisticLog::~CZSVRStatisticLog()
{
}


bool CZSVRStatisticLog::Run(N2ODBCCtrl& in_ODBCCtrl)
{
	N2ODBCHandler Handler(in_ODBCCtrl);

	TIMESTAMP_STRUCT Date = CDateTime(m_Date);
	SQLINTEGER cbDateTime = sizeof(Date);
	SQLINTEGER cbInt = 0;

	Handler.N2ODBCHandler::BindParameter(1, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 22, 0, (SQLPOINTER*)&Date, 16, &cbDateTime);
	Handler.N2ODBCHandler::BindParameter(2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, (SQLPOINTER*)&m_ZSID, 0, &cbInt);
	Handler.N2ODBCHandler::BindParameter(3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, (SQLPOINTER*)&m_PlayerNum, 0, &cbInt);
	Handler.N2ODBCHandler::BindParameter(4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, (SQLPOINTER*)&m_NPCNum, 0, &cbInt);
	Handler.N2ODBCHandler::BindParameter(5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, (SQLPOINTER*)&m_MemoryKBytes, 0, &cbInt);
	Handler.N2ODBCHandler::BindParameter(6, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, (SQLPOINTER*)&m_TotalServiceMapNum, 0, &cbInt);
	Handler.N2ODBCHandler::BindParameter(7, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, (SQLPOINTER*)&m_ServiceInstantMapNum, 0, &cbInt);

	if( !SQL_SUCCEEDED(Handler.N2ODBCHandler::ExecDirect("{call usp_szvrstatistic_add_r2( ?, ?, ?, ?, ?, ?, ?)}")) )
	{
		Handler.N2ODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
		return false;
	}

	return true;
}
