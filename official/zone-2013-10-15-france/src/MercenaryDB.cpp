#include "MercenaryDB.h"
#include "shared/NCriticalErrorLog.h"


CMerceDB::CMerceDB()
{
}


CMerceDB::~CMerceDB()
{
}


namespace {
std::vector<int> GetHoumunJobList()
{
	int InitTbl[] = {
		6048, 6049, 6050, 6051, 6052, // JT_MER_EIRA // JT_MER_BAYERI // JT_MER_SERA // JT_MER_DIETER // JT_MER_ELEANOR
		6001, 6002, 6003, 6004, // JT_MER_LIF // JT_MER_AMISTR // JT_MER_FILIR // JT_MER_VANILMIRTH
		6005, 6006, 6007, 6008, // JT_MER_LIF2 // JT_MER_AMISTR2 // JT_MER_FILIR2 // JT_MER_VANILMIRTH2
		6009, 6010, 6011, 6012, // JT_MER_LIF_H // JT_MER_AMISTR_H // JT_MER_FILIR_H // JT_MER_VANILMIRTH_H
		6013, 6014, 6015, 6016, // JT_MER_LIF_H2 // JT_MER_AMISTR_H2 // JT_MER_FILIR_H2 // JT_MER_VANILMIRTH_H2
	};

	return std::vector<int>(&InitTbl[0], &InitTbl[countof(InitTbl)]);
}
}; // namespace


namespace {
bool IsHomunJob(int in_Job)
{
	static std::vector<int> Tbl = GetHoumunJobList();

	std::vector<int>::iterator iter;

	for( iter = Tbl.begin(); iter != Tbl.end(); ++iter )
		if( *iter == in_Job )
			break;

	return ( iter != Tbl.end() );
}
}; // namespace


BOOL CMerceDB::InsertHomunInfo(int GID, HOMUN_DBINFO* info)
{
	if( !IsHomunJob(info->job) )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s GID(%d) Job(%d)", "CMerceDB::InsertHomunInfo", GID, info->job);
		return FALSE;
	}

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
		return FALSE;

	SQLINTEGER cbInt = 0;
	SQLINTEGER cbChar = SQL_NTS;

	SQLBindParameter(m_hstmt,  1, SQL_PARAM_INPUT, SQL_C_SLONG,    SQL_INTEGER, 0, 0, &GID, 0, &cbInt);
	SQLBindParameter(m_hstmt,  2, SQL_PARAM_INPUT, SQL_C_CHAR,     SQL_VARCHAR, sizeof(info->name), 0, info->name, 0, &cbChar);
	SQLBindParameter(m_hstmt,  3, SQL_PARAM_INPUT, SQL_C_SLONG,    SQL_INTEGER, 0, 0, &info->modified, 0, &cbInt);
	SQLBindParameter(m_hstmt,  4, SQL_PARAM_INPUT, SQL_C_SSHORT,   SQL_INTEGER, 0, 0, &info->clevel, 0, &cbInt);
	SQLBindParameter(m_hstmt,  5, SQL_PARAM_INPUT, SQL_C_SSHORT,   SQL_INTEGER, 0, 0, &info->job, 0, &cbInt);
	SQLBindParameter(m_hstmt,  6, SQL_PARAM_INPUT, SQL_C_SLONG,    SQL_INTEGER, 0, 0, &info->exp, 0, &cbInt);
	SQLBindParameter(m_hstmt,  7, SQL_PARAM_INPUT, SQL_C_SSHORT,   SQL_INTEGER, 0, 0, &info->SKPoint, 0, &cbInt);
	SQLBindParameter(m_hstmt,  8, SQL_PARAM_INPUT, SQL_C_SSHORT,   SQL_INTEGER, 0, 0, &info->hp, 0, &cbInt);
	SQLBindParameter(m_hstmt,  9, SQL_PARAM_INPUT, SQL_C_SSHORT,   SQL_INTEGER, 0, 0, &info->maxhp, 0, &cbInt);
	SQLBindParameter(m_hstmt, 10, SQL_PARAM_INPUT, SQL_C_SSHORT,   SQL_INTEGER, 0, 0, &info->sp, 0, &cbInt);
	SQLBindParameter(m_hstmt, 11, SQL_PARAM_INPUT, SQL_C_SSHORT,   SQL_INTEGER, 0, 0, &info->maxsp, 0, &cbInt);
	SQLBindParameter(m_hstmt, 12, SQL_PARAM_INPUT, SQL_C_SSHORT,   SQL_INTEGER, 0, 0, &info->accessory, 0, &cbInt);
	SQLBindParameter(m_hstmt, 13, SQL_PARAM_INPUT, SQL_C_UTINYINT, SQL_INTEGER, 0, 0, &info->Str, 0, &cbInt);
	SQLBindParameter(m_hstmt, 14, SQL_PARAM_INPUT, SQL_C_UTINYINT, SQL_INTEGER, 0, 0, &info->Agi, 0, &cbInt);
	SQLBindParameter(m_hstmt, 15, SQL_PARAM_INPUT, SQL_C_UTINYINT, SQL_INTEGER, 0, 0, &info->Vit, 0, &cbInt);
	SQLBindParameter(m_hstmt, 16, SQL_PARAM_INPUT, SQL_C_UTINYINT, SQL_INTEGER, 0, 0, &info->Int, 0, &cbInt);
	SQLBindParameter(m_hstmt, 17, SQL_PARAM_INPUT, SQL_C_UTINYINT, SQL_INTEGER, 0, 0, &info->Dex, 0, &cbInt);
	SQLBindParameter(m_hstmt, 18, SQL_PARAM_INPUT, SQL_C_UTINYINT, SQL_INTEGER, 0, 0, &info->Luk, 0, &cbInt);
	SQLBindParameter(m_hstmt, 19, SQL_PARAM_INPUT, SQL_C_SLONG,    SQL_INTEGER, 0, 0, &info->bodystate, 0, &cbInt);
	SQLBindParameter(m_hstmt, 20, SQL_PARAM_INPUT, SQL_C_SLONG,    SQL_INTEGER, 0, 0, &info->healthstate, 0, &cbInt);
	SQLBindParameter(m_hstmt, 21, SQL_PARAM_INPUT, SQL_C_SLONG,    SQL_INTEGER, 0, 0, &info->effectstate, 0, &cbInt);
	SQLBindParameter(m_hstmt, 22, SQL_PARAM_INPUT, SQL_C_SSHORT,   SQL_INTEGER, 0, 0, &info->property, 0, &cbInt);
	SQLBindParameter(m_hstmt, 23, SQL_PARAM_INPUT, SQL_C_SLONG,    SQL_INTEGER, 0, 0, &info->fullness, 0, &cbInt);
	int tmp = static_cast<int>(info->relation);
	SQLBindParameter(m_hstmt, 24, SQL_PARAM_INPUT, SQL_C_SLONG,    SQL_INTEGER, 0, 0, &tmp, 0, &cbInt);

	m_retcode = SQLExecDirect(m_hstmt, (SQLCHAR*)"{call usp_homun_insert_info(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return TRUE;
}


BOOL CMerceDB::SaveHomunInfo(int GID, HOMUN_DBINFO* info)
{
	if( !IsHomunJob(info->job) )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s GID(%d) Job(%d)", "CMerceDB::SaveHomunInfo", GID, info->job);
		return TRUE;
	}

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
		return FALSE;

	SQLINTEGER cbInt = 0;
	SQLINTEGER cbChar = SQL_NTS;

	SQLBindParameter(m_hstmt,  1, SQL_PARAM_INPUT, SQL_C_SLONG,    SQL_INTEGER, 0, 0, &GID, 0, &cbInt);
	SQLBindParameter(m_hstmt,  2, SQL_PARAM_INPUT, SQL_C_CHAR,     SQL_VARCHAR, sizeof(info->name), 0, info->name, 0, &cbChar);
	SQLBindParameter(m_hstmt,  3, SQL_PARAM_INPUT, SQL_C_SLONG,    SQL_INTEGER, 0, 0, &info->modified, 0, &cbInt);
	SQLBindParameter(m_hstmt,  4, SQL_PARAM_INPUT, SQL_C_SSHORT,   SQL_INTEGER, 0, 0, &info->clevel, 0, &cbInt);
	SQLBindParameter(m_hstmt,  5, SQL_PARAM_INPUT, SQL_C_SSHORT,   SQL_INTEGER, 0, 0, &info->job, 0, &cbInt);
	SQLBindParameter(m_hstmt,  6, SQL_PARAM_INPUT, SQL_C_SLONG,    SQL_INTEGER, 0, 0, info, 0, &cbInt);
	SQLBindParameter(m_hstmt,  7, SQL_PARAM_INPUT, SQL_C_SSHORT,   SQL_INTEGER, 0, 0, &info->SKPoint, 0, &cbInt);
	SQLBindParameter(m_hstmt,  8, SQL_PARAM_INPUT, SQL_C_SSHORT,   SQL_INTEGER, 0, 0, &info->hp, 0, &cbInt);
	SQLBindParameter(m_hstmt,  9, SQL_PARAM_INPUT, SQL_C_SSHORT,   SQL_INTEGER, 0, 0, &info->maxhp, 0, &cbInt);
	SQLBindParameter(m_hstmt, 10, SQL_PARAM_INPUT, SQL_C_SSHORT,   SQL_INTEGER, 0, 0, &info->sp, 0, &cbInt);
	SQLBindParameter(m_hstmt, 11, SQL_PARAM_INPUT, SQL_C_SSHORT,   SQL_INTEGER, 0, 0, &info->maxsp, 0, &cbInt);
	SQLBindParameter(m_hstmt, 12, SQL_PARAM_INPUT, SQL_C_SSHORT,   SQL_INTEGER, 0, 0, &info->accessory, 0, &cbInt);
	SQLBindParameter(m_hstmt, 13, SQL_PARAM_INPUT, SQL_C_UTINYINT, SQL_INTEGER, 0, 0, &info->Str, 0, &cbInt);
	SQLBindParameter(m_hstmt, 14, SQL_PARAM_INPUT, SQL_C_UTINYINT, SQL_INTEGER, 0, 0, &info->Agi, 0, &cbInt);
	SQLBindParameter(m_hstmt, 15, SQL_PARAM_INPUT, SQL_C_UTINYINT, SQL_INTEGER, 0, 0, &info->Vit, 0, &cbInt);
	SQLBindParameter(m_hstmt, 16, SQL_PARAM_INPUT, SQL_C_UTINYINT, SQL_INTEGER, 0, 0, &info->Int, 0, &cbInt);
	SQLBindParameter(m_hstmt, 17, SQL_PARAM_INPUT, SQL_C_UTINYINT, SQL_INTEGER, 0, 0, &info->Dex, 0, &cbInt);
	SQLBindParameter(m_hstmt, 18, SQL_PARAM_INPUT, SQL_C_UTINYINT, SQL_INTEGER, 0, 0, &info->Luk, 0, &cbInt);
	SQLBindParameter(m_hstmt, 19, SQL_PARAM_INPUT, SQL_C_SLONG,    SQL_INTEGER, 0, 0, &info->bodystate, 0, &cbInt);
	SQLBindParameter(m_hstmt, 20, SQL_PARAM_INPUT, SQL_C_SLONG,    SQL_INTEGER, 0, 0, &info->healthstate, 0, &cbInt);
	SQLBindParameter(m_hstmt, 21, SQL_PARAM_INPUT, SQL_C_SLONG,    SQL_INTEGER, 0, 0, &info->effectstate, 0, &cbInt);
	SQLBindParameter(m_hstmt, 22, SQL_PARAM_INPUT, SQL_C_SSHORT,   SQL_INTEGER, 0, 0, &info->property, 0, &cbInt);
	SQLBindParameter(m_hstmt, 23, SQL_PARAM_INPUT, SQL_C_SLONG,    SQL_INTEGER, 0, 0, &info->fullness, 0, &cbInt);
	int tmp = static_cast<int>(info->relation * 100.0);
	SQLBindParameter(m_hstmt, 24, SQL_PARAM_INPUT, SQL_C_SLONG,    SQL_INTEGER, 0, 0, &tmp, 0, &cbInt);

	m_retcode = SQLExecDirect(m_hstmt, (SQLCHAR*)"{call usp_homun_update_info(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return TRUE;
}


void CMerceDB::DeleteHomunInfo(int GID)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
		return;

	SQLINTEGER cbInt = 0;
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GID, 0, &cbInt);

	m_retcode = SQLExecDirect(m_hstmt, (SQLCHAR*)"{call usp_homun_delete_info(?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != NULL )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != NULL )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}
