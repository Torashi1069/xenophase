#pragma once
#include "NetLib/MemoryMgr.h"
#include "ODBC.h"
#include "struct.hpp"


class CAuctionDB : public CODBC
{
	public: CAuctionDB::CAuctionDB(void);
	public: virtual CAuctionDB::~CAuctionDB(void);
	public: unsigned long CAuctionDB::AddAuction(unsigned long ZoneServerID, DBAUCTIONINFO* pAuctionDB);
	public: int CAuctionDB::DeleteAuction(unsigned long AuctionID);
	public: int CAuctionDB::ChangeBuyerAuction(unsigned long AuctionID, unsigned long BuyAID, unsigned long BuyGID, char* BuyName, int NowPrice);
	public: int CAuctionDB::GetAuction(unsigned long ZoneServerID, int Type, CMemoryMgr<AUCTIONINFO>* pPool, mystd::map<unsigned long,AUCTIONINFO*>& AuctionInfo);
	public: int CAuctionDB::GetBuyerAuctionID(unsigned long ZoneServerID, unsigned long BuyAID, unsigned long BuyGID, unsigned long* AuctionIDList);
	public: int CAuctionDB::GetSellerAuctionID(unsigned long ZoneServerID, unsigned long SellerAID, unsigned long SellerGID, unsigned long* AuctionIDList);
	public: int CAuctionDB::GetCountSellItem(unsigned long ZoneServerID, unsigned long AID, unsigned long GID);
	public: int CAuctionDB::GetCountBuyItem(unsigned long ZoneServerID, unsigned long AID, unsigned long GID);

private:
	static hook_method<unsigned long (CAuctionDB::*)(unsigned long ZoneServerID, DBAUCTIONINFO* pAuctionDB)> CAuctionDB::_AddAuction;
	static hook_method<int (CAuctionDB::*)(unsigned long AuctionID)> CAuctionDB::_DeleteAuction;
	static hook_method<int (CAuctionDB::*)(unsigned long AuctionID, unsigned long BuyAID, unsigned long BuyGID, char* BuyName, int NowPrice)> CAuctionDB::_ChangeBuyerAuction;
	static hook_method<int (CAuctionDB::*)(unsigned long ZoneServerID, int Type, CMemoryMgr<AUCTIONINFO>* pPool, mystd::map<unsigned long,AUCTIONINFO*>& AuctionInfo)> CAuctionDB::_GetAuction;
	static hook_method<int (CAuctionDB::*)(unsigned long ZoneServerID, unsigned long BuyAID, unsigned long BuyGID, unsigned long* AuctionIDList)> CAuctionDB::_GetBuyerAuctionID;
	static hook_method<int (CAuctionDB::*)(unsigned long ZoneServerID, unsigned long SellerAID, unsigned long SellerGID, unsigned long* AuctionIDList)> CAuctionDB::_GetSellerAuctionID;
	static hook_method<int (CAuctionDB::*)(unsigned long ZoneServerID, unsigned long AID, unsigned long GID)> CAuctionDB::_GetCountSellItem;
	static hook_method<int (CAuctionDB::*)(unsigned long ZoneServerID, unsigned long AID, unsigned long GID)> CAuctionDB::_GetCountBuyItem;
};
