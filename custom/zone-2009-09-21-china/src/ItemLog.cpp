#include "ItemLog.h"
#include "globals.hpp"


hook_method<void (CItemLog::*)(int nType, CPC* pPC, CCharacter* pDestChar, IVItItem* pIvitItem, int nPrice, int nCount, char* Tx_ID)> CItemLog::_AddItemLog(SERVER, "CItemLog::AddItemLog");
void CItemLog::AddItemLog(int nType, CPC* pPC, CCharacter* pDestChar, IVItItem* pIvitItem, int nPrice, int nCount, char* Tx_ID) // line 325
{
	return (this->*_AddItemLog)(nType, pPC, pDestChar, pIvitItem, nPrice, nCount, Tx_ID);

	//TODO
}


hook_method<void (CItemLog::*)(unsigned long AuctionID, int nType, unsigned long SrcAID, unsigned long SrcGID, char* SrcName, unsigned long DestAID, unsigned long DestGID, char* DestName, CommonItemInfo* pItemInfo, int nPrice)> CItemLog::_AddMailAuctionLog(SERVER, "CItemLog::AddMailAuctionLog");
void CItemLog::AddMailAuctionLog(unsigned long AuctionID, int nType, unsigned long SrcAID, unsigned long SrcGID, char* SrcName, unsigned long DestAID, unsigned long DestGID, char* DestName, CommonItemInfo* pItemInfo, int nPrice) // line 108
{
	return (this->*_AddMailAuctionLog)(AuctionID, nType, SrcAID, SrcGID, SrcName, DestAID, DestGID, DestName, pItemInfo, nPrice);

	//TODO
}


hook_method<void (CItemLog::*)(unsigned long AuctionID, int nType, CPC* pPC, unsigned long DestAID, unsigned long DestGID, char* DestName, CommonItemInfo* pItemInfo, int nPrice)> CItemLog::_AddMailSendLog(SERVER, "CItemLog::AddMailSendLog");
void CItemLog::AddMailSendLog(unsigned long AuctionID, int nType, CPC* pPC, unsigned long DestAID, unsigned long DestGID, char* DestName, CommonItemInfo* pItemInfo, int nPrice) // line 180
{
	return (this->*_AddMailSendLog)(AuctionID, nType, pPC, DestAID, DestGID, DestName, pItemInfo, nPrice);

	//TODO
}


hook_method<void (CItemLog::*)(int nType, CPC* pPC, unsigned long DestAID, unsigned long DestGID, char* DestName, CommonItemInfo* pItemInfo, int nPrice)> CItemLog::_AddMailReceiveLog(SERVER, "CItemLog::AddMailReceiveLog");
void CItemLog::AddMailReceiveLog(int nType, CPC* pPC, unsigned long DestAID, unsigned long DestGID, char* DestName, CommonItemInfo* pItemInfo, int nPrice) // line 252
{
	return (this->*_AddMailReceiveLog)(nType, pPC, DestAID, DestGID, DestName, pItemInfo, nPrice);

	//TODO
}


hook_method<void (CItemLog::*)(int nType, CPC* pPC, CCharacter* pDestChar, int nPrice, int nCount, unsigned long AuctionID)> CItemLog::_AddItemLogOnMoney(SERVER, "CItemLog::AddItemLogOnMoney");
void CItemLog::AddItemLogOnMoney(int nType, CPC* pPC, CCharacter* pDestChar, int nPrice, int nCount, unsigned long AuctionID) // line 45
{
	return (this->*_AddItemLogOnMoney)(nType, pPC, pDestChar, nPrice, nCount, AuctionID);

	//TODO
}


hook_method<void (CItemLog::*)(const char* Log)> CItemLog::_ConnectToDatabase(SERVER, "CItemLog::ConnectToDatabase");
void CItemLog::ConnectToDatabase(const char* Log) // line ??
{
	return (this->*_ConnectToDatabase)(Log);

	this->CExtendedODBC::Connect("Loger", g_dbPWD, Log, 0, "");
}


/* hook_method<void (CItemLog::*)(int nType, CPC* pPC, CPC* pDestPC, CITP* piteminfo, int nPrice, int nCount)> CItemLog::_AddCITPLog(SERVER, "CItemLog::AddCITPLog");
void CItemLog::AddCITPLog(int nType, CPC* pPC, CPC* pDestPC, CITP* piteminfo, int nPrice, int nCount) // line ???
{
	return (this->*_AddCITPLog)(nType, pPC, pDestPC, piteminfo, nPrice, nCount);

	//TODO
} */


hook_method<int (CItemLog::*)(SQLHSTMT hStmt, SITEMLOG* pLog)> CItemLog::_SaveToDatabase(SERVER, "CItemLog::SaveToDatabase");
int CItemLog::SaveToDatabase(SQLHSTMT hStmt, SITEMLOG* pLog) // line 475
{
	return (this->*_SaveToDatabase)(hStmt, pLog);

	//TODO
}


/* hook_method<int (CItemLog::*)(SQLHSTMT hStmt, SITEMLOG* pLog)> CItemLog::_SaveToDatabaseV1(SERVER, "CItemLog::SaveToDatabaseV1");
int CItemLog::SaveToDatabaseV1(SQLHSTMT hStmt, SITEMLOG* pLog) // line ???
{
	return (this->*_SaveToDatabaseV1)(hStmt, pLog);

	//TODO
} */


hook_method<int (CItemLog::*)(SQLHSTMT const in_hStmt, SITEMLOG* pLog)> CItemLog::_SaveToDatabaseV2(SERVER, "CItemLog::SaveToDatabaseV2");
int CItemLog::SaveToDatabaseV2(SQLHSTMT const in_hStmt, SITEMLOG* pLog) // line 520
{
	return (this->*_SaveToDatabaseV2)(in_hStmt, pLog);

	//TODO
}
