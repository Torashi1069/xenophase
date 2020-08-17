#include "CAuctionDB.h"
#include "shared/shared.h"

CAuctionDB::CAuctionDB()
{
}


CAuctionDB::~CAuctionDB()
{
}


int CAuctionDB::GetAuction(unsigned long ZoneServerID, int Type, CMemoryMgr<AUCTIONINFO>* pPool, std::map<unsigned long,AUCTIONINFO*>& AuctionInfo)
{
	int AuctionCount = 0;

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return 0;
	}

	SQLINTEGER cbGID = 0;
	SQLINTEGER cbChar = SQL_NTS;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &ZoneServerID, 0, &cbGID);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Type, 0, &cbGID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetAuction(?, ?)}", SQL_NTS);
	if( m_retcode == SQL_ERROR )
	{
		char Buf[1024];
		this->CODBC::GetErrorString(m_hstmt, Buf);
		Trace("%s\n", Buf);

		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
		return 0;
	}

	AUCTIONINFO AuctionDB;
	memset(&AuctionDB, 0, sizeof(AuctionDB));
	AuctionDB.ZoneServerID = ZoneServerID;
	AuctionDB.AuctionType = Type;
	AuctionDB.BuyerName[0] = '\0';
	AuctionDB.IsIdentified = 0;
	AuctionDB.IsDamaged = 0;

	TIMESTAMP_STRUCT DateTime;

	SQLBindCol(m_hstmt,  1, SQL_C_SLONG, &AuctionDB.AuctionID, 0, &cbGID);
	SQLBindCol(m_hstmt,  2, SQL_C_SLONG, &AuctionDB.ZoneServerID, 0, &cbGID);
	SQLBindCol(m_hstmt,  3, SQL_C_SLONG, &AuctionDB.AID, 0, &cbGID);
	SQLBindCol(m_hstmt,  4, SQL_C_SLONG, &AuctionDB.GID, 0, &cbGID);
	SQLBindCol(m_hstmt,  5, SQL_C_CHAR, AuctionDB.SellerName, sizeof(AuctionDB.SellerName), &cbChar);
	SQLBindCol(m_hstmt,  6, SQL_C_SLONG, &AuctionDB.BuyerAID, 0, &cbGID);
	SQLBindCol(m_hstmt,  7, SQL_C_SLONG, &AuctionDB.BuyerGID, 0, &cbGID);
	SQLBindCol(m_hstmt,  8, SQL_C_CHAR, AuctionDB.BuyerName, 24, &cbChar);
	SQLBindCol(m_hstmt,  9, SQL_C_SLONG, &AuctionDB.NowPrice, 0, &cbGID);
	SQLBindCol(m_hstmt, 10, SQL_C_SLONG, &AuctionDB.MaxPrice, 0, &cbGID);
	SQLBindCol(m_hstmt, 11, SQL_C_SLONG, &AuctionDB.AuctionType, 0, &cbGID);
	SQLBindCol(m_hstmt, 12, SQL_C_BINARY, AuctionDB.Item, sizeof(AuctionDB.Item), &cbChar);
	SQLBindCol(m_hstmt, 13, SQL_C_SLONG, &AuctionDB.ItemLen, 0, &cbGID);
	SQLBindCol(m_hstmt, 14, SQL_C_TYPE_TIMESTAMP, &DateTime, 8, &cbChar); //FIXME: wrong size

	for( ; ; )
	{
		m_retcode = SQLFetch(m_hstmt);
		if( m_retcode == SQL_NO_DATA )
			break; // done.

		if( m_retcode == SQL_ERROR )
			break; // error.

		AuctionDB.EndTime.Year = DateTime.year;
		AuctionDB.EndTime.Month = DateTime.month;
		AuctionDB.EndTime.Day = DateTime.day;
		AuctionDB.EndTime.Hour = DateTime.hour;

		AUCTIONINFO* pAuctionInfo = pPool->CMemoryMgr<AUCTIONINFO>::Alloc();
		memcpy_s(pAuctionInfo, sizeof(*pAuctionInfo), &AuctionDB, sizeof(AuctionDB));
		AuctionInfo[AuctionDB.AuctionID] = pAuctionInfo;
		++AuctionCount;

		if( AuctionCount > 50000 ) //FIXME: off-by-one
			break; // no more room.

		AuctionDB.BuyerName[0] = '\0';
	}

	if( m_retcode == SQL_ERROR )
	{
		char Buf[1024];
		this->CODBC::GetErrorString(m_hstmt, Buf);
		Trace("%s\n", Buf);
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return AuctionCount;
}


unsigned long CAuctionDB::AddAuction(unsigned long ZoneServerID, DBAUCTIONINFO* pAuctionDB)
{
	pAuctionDB->AuctionID = 0;

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return 0;
	}

	SQLINTEGER cbChar = SQL_NTS;
	SQLINTEGER cbDate = SQL_NTS;
	SQLINTEGER cbInt = 0;
	static char szItemBin[40];
	SQLINTEGER cbequipbin = pAuctionDB->ItemLen;
	memcpy_s(szItemBin, sizeof(szItemBin), pAuctionDB->Item, pAuctionDB->ItemLen);

	TIMESTAMP_STRUCT DateTime;
	DateTime.year = pAuctionDB->EndTime.Year;
	DateTime.month = pAuctionDB->EndTime.Month;
	DateTime.day = pAuctionDB->EndTime.Day;
	DateTime.hour = pAuctionDB->EndTime.Hour;
	DateTime.minute = 0;
	DateTime.second = 0;
	DateTime.fraction = 0;

	SQLBindParameter(m_hstmt,  1, SQL_PARAM_OUTPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &pAuctionDB->AuctionID, 0, &cbInt);
	SQLBindParameter(m_hstmt,  2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &ZoneServerID, 0, &cbInt);
	SQLBindParameter(m_hstmt,  3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &pAuctionDB->AID, 0, &cbInt);
	SQLBindParameter(m_hstmt,  4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &pAuctionDB->GID, 0, &cbInt);
	SQLBindParameter(m_hstmt,  5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, sizeof(pAuctionDB->SellerName), 0, pAuctionDB->SellerName, 0, &cbChar);
	SQLBindParameter(m_hstmt,  6, SQL_PARAM_INPUT, SQL_C_BINARY, SQL_BINARY, sizeof(szItemBin), 0, szItemBin, 0, &cbequipbin);
	SQLBindParameter(m_hstmt,  7, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &pAuctionDB->ItemLen, 0, &cbInt);
	SQLBindParameter(m_hstmt,  8, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &pAuctionDB->AuctionType, 0, &cbInt);
	SQLBindParameter(m_hstmt,  9, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &pAuctionDB->NowPrice, 0, &cbInt);
	SQLBindParameter(m_hstmt, 10, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &pAuctionDB->MaxPrice, 0, &cbInt);
	SQLBindParameter(m_hstmt, 11, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, sizeof(DateTime), 0, &DateTime, sizeof(DateTime), &cbDate);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{? = call InsertAuction(?,?,?,?,?,?,?,?,?,?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		char Buf[1024];
		this->CODBC::GetErrorString(m_hstmt, Buf); //NOTE: unused
		Trace("Auction DB 저장 에러\n");
	}
	else
	{
		do
		{
			m_retcode = SQLMoreResults(m_hstmt);
		}
		while( m_retcode != SQL_NO_DATA && m_retcode != SQL_ERROR );
		Trace("Auction Updated\n");
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return pAuctionDB->AuctionID;
}


BOOL CAuctionDB::DeleteAuction(unsigned long AuctionID)
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != NULL )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLINTEGER cbAuctionID = 0;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &AuctionID, 0, &cbAuctionID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call DeleteAuction(?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		SQLCloseCursor(m_hstmt);
		if( m_hstmt != NULL )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != NULL )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return TRUE;
}


BOOL CAuctionDB::ChangeBuyerAuction(unsigned long AuctionID, unsigned long BuyAID, unsigned long BuyGID, char* BuyName, int NowPrice)
{
	m_retcode = SQLAllocHandle(3, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLINTEGER cbInt = 0;
	SQLINTEGER cbChar = SQL_NTS;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &AuctionID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &BuyAID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &BuyGID, 0, &cbInt);
	SQLBindParameter(m_hstmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 24, 0, BuyName, 0, &cbChar);
	SQLBindParameter(m_hstmt, 5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &NowPrice, 0, &cbInt);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call UpdateAuction(?, ?, ?, ?, ?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		char Buf[1024];
		this->CODBC::GetErrorString(m_hstmt, Buf); //NOTE: unused
		Trace("Auction DB 저장 에러\n");

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


int CAuctionDB::GetBuyerAuctionID(unsigned long ZoneServerID, unsigned long BuyAID, unsigned long BuyGID, unsigned long* AuctionIDList)
{
	int AuctionCounter = 0;

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return 0;
	}

	SQLINTEGER cbGID = 0;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &ZoneServerID, 0, &cbGID);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &BuyAID, 0, &cbGID);
	SQLBindParameter(m_hstmt, 3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &BuyGID, 0, &cbGID);

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetBuyerAuctionID(?,?,?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		char Buf[1024];
		this->CODBC::GetErrorString(m_hstmt, Buf);
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return 0;
	}

	unsigned long AuctionID;
	SQLBindCol(m_hstmt, 1, SQL_C_SLONG, &AuctionID, 0, &cbGID);

	for( ; ; )
	{
		m_retcode = SQLFetch(m_hstmt);
		if( m_retcode == SQL_NO_DATA )
			break; // done.

		if( m_retcode == SQL_ERROR )
			break; // error.

		AuctionIDList[AuctionCounter] = AuctionID;
		++AuctionCounter;

		if( AuctionCounter > 5 )
			break; // no more room.
	}

	if( m_retcode == SQL_ERROR )
	{
		char Buf[1024];
		this->CODBC::GetErrorString(m_hstmt, Buf);
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != NULL )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return AuctionCounter;
}


int CAuctionDB::GetSellerAuctionID(unsigned long ZoneServerID, unsigned long SellerAID, unsigned long SellerGID, unsigned long* AuctionIDList)
{
	int AuctionCounter = 0;

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return 0;
	}

	SQLINTEGER cbGID = 0;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &ZoneServerID, 0, &cbGID);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &SellerAID, 0, &cbGID);
	SQLBindParameter(m_hstmt, 3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &SellerGID, 0, &cbGID);

	m_retcode = SQLExecDirect(m_hstmt, (SQLCHAR*)"{call GetSellerAuctionID(?,?,?)}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		char Buf[1024];
		this->CODBC::GetErrorString(m_hstmt, Buf);
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);

		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return 0;
	}

	unsigned long AuctionID;
	SQLBindCol(m_hstmt, 1, SQL_C_SLONG, &AuctionID, 0, &cbGID);

	for( ; ; )
	{
		m_retcode = SQLFetch(m_hstmt);
		if( m_retcode == SQL_NO_DATA )
			break; // done.

		if( m_retcode == SQL_ERROR )
			break; // error.

		AuctionIDList[AuctionCounter] = AuctionID;
		++AuctionCounter;

		if( AuctionCounter > 5 )
			break; // no more room.
	}

	if( m_retcode == SQL_ERROR )
	{
		char Buf[1024];
		this->CODBC::GetErrorString(m_hstmt, Buf);
		DBTrace(__FILE__, __LINE__, SQL_HANDLE_STMT, m_hstmt);
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return AuctionCounter;
}


int CAuctionDB::GetCountSellItem(unsigned long ZoneServerID, unsigned long AID, unsigned long GID)
{
	int AuctionCounter = 0;

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return 0;
	}

	SQLINTEGER cbGID = 0;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &ZoneServerID, 0, &cbGID);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &AID, 0, &cbGID);
	SQLBindParameter(m_hstmt, 3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GID, 0, &cbGID);

	m_retcode = SQLExecDirect(m_hstmt, (SQLCHAR*)"{call GetCountSellItem(?,?,?)}", SQL_NTS);
	if( m_retcode == SQL_ERROR )
	{
		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return 0;
	}

	SQLBindCol(m_hstmt, 1, SQL_C_SLONG, &AuctionCounter, 0, &cbGID);
	m_retcode = SQLFetch(m_hstmt);

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return AuctionCounter;
}


int CAuctionDB::GetCountBuyItem(unsigned long ZoneServerID, unsigned long AID, unsigned long GID)
{
	int AuctionCounter = 0;

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return 0;
	}

	SQLINTEGER cbGID = 0;

	SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &ZoneServerID, 0, &cbGID);
	SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &AID, 0, &cbGID);
	SQLBindParameter(m_hstmt, 3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GID, 0, &cbGID);

	m_retcode = SQLExecDirect(m_hstmt, (SQLCHAR*)"{call GetCountBuyItem(?,?,?)}", SQL_NTS);
	if( m_retcode == SQL_ERROR )
	{
		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return 0;
	}

	SQLBindCol(m_hstmt, 1, SQL_C_SLONG, &AuctionCounter, 0, &cbGID);
	m_retcode = SQLFetch(m_hstmt);

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return AuctionCounter;
}
