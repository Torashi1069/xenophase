#include "shared/CDateTime.h"
#include "shared/N2System/ODBC(open database connectivity)/N2ODBCHandler.h"
#include "Statistics/MAPStatisticLog.h"


CMAPStatisticLog::CMAPStatisticLog(const time_t in_Date, const int in_ZSID, const MAPINFO_CONTAINER& in_MapInfoContainer)
: m_Date(in_Date), m_ZSID(in_ZSID), m_MapInfoContainer(in_MapInfoContainer)
{
}


CMAPStatisticLog::~CMAPStatisticLog()
{
}


bool CMAPStatisticLog::Run(N2ODBCCtrl& in_ODBCCtrl)
{
	N2ODBCHandler Handler(in_ODBCCtrl);

	char mapName[16] = {};
	int PlayerNum = 0;

	TIMESTAMP_STRUCT Date = CDateTime(m_Date);
	SQLINTEGER cbDateTime = sizeof(Date);
	SQLINTEGER cbInt = 0;
	SQLINTEGER cbChar = SQL_NTS;

	Handler.N2ODBCHandler::BindParameter(1, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 22, 0, (SQLPOINTER*)&Date, 16, &cbDateTime);
	Handler.N2ODBCHandler::BindParameter(2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, sizeof(mapName), 0, (SQLPOINTER*)mapName, 0, &cbChar);
	Handler.N2ODBCHandler::BindParameter(3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, (SQLPOINTER*)&m_ZSID, 0, &cbInt);
	Handler.N2ODBCHandler::BindParameter(4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, (SQLPOINTER*)&PlayerNum, 0, &cbInt);

	for( MAPINFO_CONTAINER_ITER iter = m_MapInfoContainer.begin(); iter != m_MapInfoContainer.end(); ++iter )
	{
		memcpy(mapName, iter->first.c_str(), sizeof(mapName)-1);
		PlayerNum = iter->second;

		if( !SQL_SUCCEEDED(Handler.N2ODBCHandler::ExecDirect("{call usp_mapstatistic_add_r2( ?,?, ?, ?)}")) )
		{
			Handler.N2ODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
			return false;
		}
	}

	return true;
}
