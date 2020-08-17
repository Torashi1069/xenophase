#include "CharInfoDB.h"
#include "PC.h"
#include "Struct.h"
#include "shared/NCriticalErrorLog.h"


CCharInfoDB::CCharInfoDB()
{
}


CCharInfoDB::~CCharInfoDB()
{
}


void CCharInfoDB::UpdateItemStoreMoney(int AID, int money)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "error");
		return;
	}

	SQLINTEGER cbAID = 0;
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &money, 0, &cbAID);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &AID, 0, &cbAID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"update storeitem set money=? where AID = ?", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}


void CCharInfoDB::DeleteItem(int GID)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
		return;

	int sGID = GID;
	SQLINTEGER cbGID = 0;
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &sGID, 0, &cbGID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call DeleteItem(?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}


void CCharInfoDB::GetCharacterName(int GID, char* charname)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
		return;

	SQLINTEGER cbGID = 0;
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GID, 0, &cbGID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"select charname from charinfo where GID = ?", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return;
	}

	SQLINTEGER cbChar = SQL_NTS;
	SQLBindCol(m_hstmt, 1, SQL_C_CHAR, charname, 24, &cbChar);

	BOOL bSuccess = FALSE;

	m_retcode = SQLFetch(m_hstmt);
	if( m_retcode != SQL_NO_DATA )
		bSuccess = TRUE;

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	if( !bSuccess )
		charname[0] = '\0';
}


BOOL CCharInfoDB::LoadMPInfo(unsigned long AID, std::list<MannerPointData>* info, int& LastDate)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "db handle allocation error");
		return FALSE;
	}

	SQLINTEGER cbAID = 0;
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &AID, 0, &cbAID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetMannerPoint(?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	MannerPointData data;
	int day = 0;
	SQLBindCol(m_hstmt, 1, SQL_C_SLONG, &data.otherGID, 0, &cbAID);
	SQLBindCol(m_hstmt, 2, SQL_C_SLONG, &data.type, 0, &cbAID);
	SQLBindCol(m_hstmt, 3, SQL_C_SLONG, &day, 0, &cbAID);

	BOOL flag = FALSE;
	int i = 0;
	for( ; ; )
	{
		m_retcode = SQLFetch(m_hstmt);
		if( m_retcode == SQL_NO_DATA )
			break;

		if( i >= 40 )
			break;

		++i;
		info->push_back(data);
		flag = TRUE;
	}

	LastDate = day;

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return flag;
}


void CCharInfoDB::DeleteMP(unsigned long AID, unsigned long otherGID)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
		return;

	SQLINTEGER sAID = AID;
	SQLINTEGER oGID = otherGID;
	SQLINTEGER cbAID = 0;
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &sAID, 0, &cbAID);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &oGID, 0, &cbAID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call DeleteMannerPoint(?,?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}


BOOL CCharInfoDB::InsertNewMP(unsigned long AID, unsigned long otherGID, int type)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
		return FALSE;

	SQLINTEGER sAID = AID;
	SQLINTEGER oGID = otherGID;
	SQLINTEGER mtype = type;
	SQLINTEGER cbAID = 0;
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &sAID, 0, &cbAID);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &oGID, 0, &cbAID);
	SQLBindParameter(m_hstmt, 3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &mtype, 0, &cbAID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call InsertMannerPoint(?,?,?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return TRUE;
}


BOOL CCharInfoDB::GetCharacterID(char* Name, unsigned long& AID, unsigned long& GID)
{
	if( strcmp("MailManager", Name) == 0 || strcmp("AuctionManager", Name) == 0 )
	{
		AID = 0;
		GID = 0;
		return FALSE;
	}

	m_retcode = SQLAllocHandle(3, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLINTEGER cbGID = 0;
	SQLINTEGER cbChar = SQL_NTS;
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 24, 0, Name, 0, &cbChar);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetCharacterID(?)}", SQL_NTS);

	unsigned long DB_GID;
	unsigned long DB_AID;
	SQLBindCol(m_hstmt, 1, SQL_C_SLONG, &DB_AID, 0, &cbGID);
	SQLBindCol(m_hstmt, 2, SQL_C_SLONG, &DB_GID, 0, &cbGID);

	m_retcode = SQLFetch(m_hstmt);
	if( m_retcode == SQL_NO_DATA || m_retcode == SQL_ERROR )
	{
		char Buf[1024];
		this->CODBC::GetErrorString(m_hstmt, Buf);
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	AID = DB_AID;
	GID = DB_GID;

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return TRUE;
}


BOOL CCharInfoDB::UpdatePVPEvent(char* GID, char* Name)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
		return FALSE;

	SQLINTEGER cbChar = SQL_NTS;
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 24, 0, GID, 0, &cbChar);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 36, 0, Name, 0, &cbChar);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call UpdatePVPEvent(?,?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		char Buf[1024];
		this->CCharInfoDB::GetErrorString(m_hstmt, Buf);

		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return TRUE;
}


BOOL CCharInfoDB::GetPVPEvent(char* GID, char* Name)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLINTEGER cbChar = SQL_NTS;
	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 24, 0, GID, 0, &cbChar);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetPVPEvent(?)}", SQL_NTS);

	SQLBindCol(m_hstmt, 1, SQL_C_CHAR, Name, 36, &cbChar);

	m_retcode = SQLFetch(m_hstmt);

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return TRUE;
}


void CCharInfoDB::GetErrorString(SQLHSTMT hStmt, char* lpszError)
{
	char szState[1024] = {};
	SQLErrorA(m_henv, m_hdbc, hStmt, (SQLCHAR*)szState, NULL, (SQLCHAR*)lpszError, 1024, NULL);
}


int CCharInfoDB::InsertHuntingList(int GID)
{
	CDBStatement st;
	if( !st.CDBStatement::Init(m_hdbc) )
		return -1;

	int sGID = GID;
	SQLINTEGER cbGID = 0;
	SQLBindParameter(st, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &sGID, 0, &cbGID);

	m_retcode = SQLExecDirectA(st, (SQLCHAR*)"{call InsertHuntingList(?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, st);
		SQLCloseCursor(st);
		return -1;
	}

	SQLCloseCursor(st);
	return 1;
}


int CCharInfoDB::InsertTimeList(int GID)
{
	CDBStatement st;
	if( !st.CDBStatement::Init(m_hdbc) )
		return -1;

	int sGID = GID;
	SQLINTEGER cbGID = 0;
	SQLBindParameter(st, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &sGID, 0, &cbGID);

	m_retcode = SQLExecDirectA(st, (SQLCHAR*)"{call InsertTimeList(?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, st);
		SQLCloseCursor(st);
		return -1;
	}

	SQLCloseCursor(st);
	return 1;
}


int CCharInfoDB::SelectHuntingList(unsigned long GID, unsigned char* buf)
{
	if( buf == NULL )
		return -1;

	CDBStatement st;
	if( !st.CDBStatement::Init(m_hdbc) )
		return -1;

	int sGID = GID;
	SQLINTEGER cbGID = SQL_NTS;
	SQLBindParameter(st, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &sGID, 0, &cbGID);

	m_retcode = SQLExecDirectA(st, (SQLCHAR*)"{call SelectHuntingList(?)}", SQL_NTS);
	if( SQL_SUCCEEDED(m_retcode) )
	{
		SQLINTEGER cbBin = SQL_NTS;
		SQLBindCol(st, 1, SQL_C_BINARY, buf, 512, &cbBin);

		m_retcode = SQLFetch(st);
		if( SQL_SUCCEEDED(m_retcode) )
		{
			if( cbBin == -1 )
				cbBin = 0;

			SQLCloseCursor(st);
			return cbBin;
		}
		else
		if( m_retcode == SQL_NO_DATA )
		{
			this->CCharInfoDB::InsertHuntingList(GID);
			SQLCloseCursor(st);
			return 0;
		}
	}

	DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, st);
	SQLCloseCursor(st);
	return -1;
}


int CCharInfoDB::UpdateHuntingList(unsigned long GID, unsigned char* buf, int size)
{
	if( buf == NULL )
		return -1;

	CDBStatement st;
	if( !st.CDBStatement::Init(m_hdbc) )
		return -1;

	SQLINTEGER cbGID = 0;
	SQLINTEGER cbBin = size;

	if( size <= 0 )
	{
		SQLBindParameter(st, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GID, 0, &cbGID);

		cbGID = SQL_NTS;
		m_retcode = SQLExecDirectA(st, (SQLCHAR*)"{call UpdateHuntingList(NULL, ?)}", cbGID);
	}
	else
	{
		SQLBindParameter(st, 1, SQL_PARAM_INPUT, SQL_C_BINARY, SQL_VARBINARY, size, 0, buf, 0, &cbBin);
		SQLBindParameter(st, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GID, 0, &cbGID);

		cbGID = SQL_NTS;
		m_retcode = SQLExecDirectA(st, (SQLCHAR*)"{call UpdateHuntingList(?, ?)}", cbGID);
	}

	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, st);
		SQLCloseCursor(st);
		return -1;
	}

	SQLCloseCursor(st);
	return 1;
}


int CCharInfoDB::SelectTimeList(unsigned long GID, unsigned char* buf)
{
	if( buf == NULL )
		return -1;

	CDBStatement st;
	if( !st.CDBStatement::Init(m_hdbc) )
		return -1;

	int sGID = GID;
	SQLINTEGER cbGID = SQL_NTS;
	SQLBindParameter(st, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &sGID, 0, &cbGID);

	m_retcode = SQLExecDirectA(st, (SQLCHAR*)"{call SelectTimeList(?)}", SQL_NTS);
	if( SQL_SUCCEEDED(m_retcode) )
	{
		SQLINTEGER cbBin = SQL_NTS;
		SQLBindCol(st, 1, SQL_C_BINARY, buf, 512, &cbBin);

		m_retcode = SQLFetch(st);
		if( SQL_SUCCEEDED(m_retcode) )
		{
			if( cbBin == -1 )
				cbBin = 0;

			SQLCloseCursor(st);
			return cbBin;
		}
		else
		if( m_retcode == SQL_NO_DATA )
		{
			this->CCharInfoDB::InsertTimeList(GID);
			SQLCloseCursor(st);
			return 0;
		}
	}

	DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, st);
	SQLCloseCursor(st);
	return -1;
}


int CCharInfoDB::UpdateTimeList(unsigned long GID, unsigned char* buf, int size)
{
	if( buf == NULL )
		return -1;

	CDBStatement st;
	if( !st.CDBStatement::Init(m_hdbc) )
		return -1;

	SQLINTEGER cbGID = 0;
	SQLINTEGER cbBin = size;

	if( size <= 0 )
	{
		SQLBindParameter(st, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GID, 0, &cbGID);

		cbGID = SQL_NTS;
		m_retcode = SQLExecDirectA(st, (SQLCHAR*)"{call UpdateTimeList(NULL, ?)}", cbGID);
	}
	else
	{
		SQLBindParameter(st, 1, SQL_PARAM_INPUT, SQL_C_BINARY, SQL_VARBINARY, size, 0, buf, 0, &cbBin);
		SQLBindParameter(st, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GID, 0, &cbGID);

		cbGID = SQL_NTS;
		m_retcode = SQLExecDirectA(st, (SQLCHAR*)"{call UpdateTimeList(?, ?)}", cbGID);
	}
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, st);
		SQLCloseCursor(st);
		return -1;
	}

	SQLCloseCursor(st);
	return 1;
}


int CCharInfoDB::GetShortCutKey(unsigned long GID, unsigned char* pShortCutKey)
{
	if( pShortCutKey == NULL )
		return -1;

	CDBStatement st;
	if( !st.CDBStatement::Init(m_hdbc) )
		return -1;

	int sGID = GID;
	SQLINTEGER cbGID = 0;
	SQLBindParameter(st, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &sGID, 0, &cbGID);

	m_retcode = SQLExecDirectA(st, (SQLCHAR*)"{call GetShortCutKey(?)}", SQL_NTS);
	if( SQL_SUCCEEDED(m_retcode) )
	{
		memset(pShortCutKey, 0, 38 * sizeof(tagShortCutKey));

		SQLINTEGER cbBin = SQL_NTS;
		SQLBindCol(st, 1, SQL_C_BINARY, pShortCutKey, 38 * sizeof(tagShortCutKey), &cbBin);

		m_retcode = SQLFetch(st);
		if( SQL_SUCCEEDED(m_retcode) )
		{
			if( cbBin == -1 )
				cbBin = 0;

			SQLCloseCursor(st);
			return cbBin;
		}
		else
		if( m_retcode == SQL_NO_DATA )
		{
			SQLCloseCursor(st);
			return 0;
		}
	}

	DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, st);
	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "GID(%d) : GetShortCutKey DB error", GID);
	SQLCloseCursor(st);
	return -1;
}


int CCharInfoDB::UpdateShortCutKey(unsigned long GID, unsigned char* pShortCutKey)
{
	if( pShortCutKey == NULL )
		return -1;

	CDBStatement st;
	if( !st.CDBStatement::Init(m_hdbc) )
		return -1;

	SQLINTEGER cbGID = 0;
	SQLINTEGER cbBin = 38 * sizeof(tagShortCutKey);
	SQLBindParameter(st, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GID, 0, &cbGID);
	SQLBindParameter(st, 2, SQL_PARAM_INPUT, SQL_C_BINARY, SQL_VARBINARY, 38 * sizeof(tagShortCutKey), 0, pShortCutKey, 0, &cbBin);

	m_retcode = SQLExecDirectA(st, (SQLCHAR*)"{call UpdateShortCutKey(?, ?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, st);
		SQLCloseCursor(st);
		return -1;
	}

	SQLCloseCursor(st);
	return 1;
}
