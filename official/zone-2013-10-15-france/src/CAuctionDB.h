#pragma once
#include "Struct.h" // EQUIPSLOTINFO
#include "shared/ODBC.h"
#include "NetLib/MemoryMgr.h"


struct AUCTIONTIME
{
	/* this+0 */ short Year;
	/* this+2 */ short Month;
	/* this+4 */ short Day;
	/* this+6 */ short Hour;
};


struct DBAUCTIONINFO
{
	/* this+  0 */ unsigned long AuctionID;
	/* this+  4 */ unsigned long ZoneServerID;
	/* this+  8 */ unsigned long AID;
	/* this+ 12 */ unsigned long GID;
	/* this+ 16 */ char SellerName[24];
	/* this+ 40 */ unsigned long BuyerAID;
	/* this+ 44 */ unsigned long BuyerGID;
	/* this+ 48 */ char BuyerName[24];
	/* this+ 72 */ unsigned long NowPrice;
	/* this+ 76 */ unsigned long MaxPrice;
	/* this+ 80 */ AUCTIONTIME EndTime;
	/* this+ 88 */ int AuctionType;
	/* this+ 92 */ char Item[40];
	/* this+132 */ unsigned long ItemLen;
};


struct AUCTIONINFO : public DBAUCTIONINFO
{
	/* this+  0 */ //DBAUCTIONINFO baseclass_0;
	/* this+136 */ BOOL isBuyer;
	/* this+140 */ unsigned short ITID;
	/* this+142 */ unsigned short ItemType;
	/* this+144 */ int count;
	/* this+148 */ bool IsIdentified;
	/* this+149 */ bool IsDamaged;
	/* this+150 */ unsigned char refiningLevel;
	/* this+151 */ EQUIPSLOTINFO slot;
};


class CAuctionDB : public CODBC
{
public:
	unsigned long AddAuction(unsigned long ZoneServerID, DBAUCTIONINFO* pAuctionDB);
	BOOL DeleteAuction(unsigned long AuctionID);
	BOOL ChangeBuyerAuction(unsigned long AuctionID, unsigned long BuyAID, unsigned long BuyGID, char* BuyName, int NowPrice);
	int GetAuction(unsigned long ZoneServerID, int Type, CMemoryMgr<AUCTIONINFO>* pPool, std::map<unsigned long,AUCTIONINFO*>& AuctionInfo);
	int GetBuyerAuctionID(unsigned long ZoneServerID, unsigned long BuyAID, unsigned long BuyGID, unsigned long* AuctionIDList);
	int GetSellerAuctionID(unsigned long ZoneServerID, unsigned long SellerAID, unsigned long SellerGID, unsigned long* AuctionIDList);
	int GetCountSellItem(unsigned long ZoneServerID, unsigned long AID, unsigned long GID);
	int GetCountBuyItem(unsigned long ZoneServerID, unsigned long AID, unsigned long GID);

public:
	CAuctionDB();
	virtual ~CAuctionDB();
};
