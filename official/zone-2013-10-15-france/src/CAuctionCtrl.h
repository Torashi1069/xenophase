#pragma once
#include "CAuctionDB.h"
class CPC; // #include "PC.h"
#include "NetLib/MemoryMgr.h"
#include "shared/CDateTime.h"


class CAuctionCtrl
{
public:
	void Init(unsigned long ZoneServerID, const char* FileDSN, const char* PASS);
	void Process();
	BOOL AddAuction(CPC* pPC, unsigned long NowPrice, unsigned long MaxPrice, int Hour, CommonItemInfo* pCommonItemInfo, char* pItemBuffer, int ItemLen);
	BOOL DeleteAuction(unsigned long AuctionID, int ItemType);
	BOOL ChangeBuyerAuction(CPC* pBuyerPc, unsigned long AuctionID, unsigned long BuyAID, unsigned long BuyGID, char* BuyName, int NowPrice);
	void FindItem(unsigned long AccountID, int ItemType, int Page);
	void FindItemAuctionID(unsigned long AccountID, unsigned long AuctionID);
	void FindItemName(unsigned long AccountID, char* ItemName, int Page);
	BOOL AuctionAddCancel(unsigned long AuctionID, unsigned long SellerAID, unsigned long SellerGID);
	BOOL ReqMyInfo(int Type, unsigned long AID, unsigned long GID);
	int MySellStop(unsigned long AuctionID, unsigned long AID, unsigned long GID);
	int GetCountSellItem(unsigned long AID, unsigned long GID);
	int GetCountBuyItem(unsigned long AID, unsigned long GID);

private:
	BOOL SendMailAuctionEnd(AUCTIONINFO* pAuctionInfo);
	BOOL SendMailAuctionCanle(AUCTIONINFO* pAuctionInfo);
	BOOL SendBuyerAuctionCancel(AUCTIONINFO* pAuctionInfo, unsigned long AuctionID);
	void TimeOver(int ItemType);
	AUCTIONINFO* GetAuctionInfo(unsigned long AuctionID);
	void ItemParser(int PaserType);
	int GetAuctionType(int ITID);
	void SendAuctionInfo(unsigned long AID, int ItemCounter, int MaxCounter, char* Buffer, int BufferSize);
	void GetClientItemName(int ITID, char* ItemName);

private:
	enum
	{
		TYPE_AUCTION_ARMOR  = 0,
		TYPE_AUCTION_WEAPON = 1,
		TYPE_AUCTION_CARD   = 2,
		TYPE_AUCTION_ETC    = 3,
	};

private:
	/* this+  0 */ //const CAuctionCtrl::`vftable';
	/* this+  4 */ int m_ZoneServerID;
	/* this+  8 */ CAuctionDB m_AuctionDB;
	/* this+ 28 */ CDateTime m_DateTime;
	/* this+ 32 */ DWORD m_lastTime;
	/* this+ 36 */ int m_EndChkItemType;
	/* this+ 40 */ std::map<unsigned long,AUCTIONINFO*> m_ArmorItem;
	/* this+ 56 */ std::map<unsigned long,AUCTIONINFO*> m_WeaponItem;
	/* this+ 72 */ std::map<unsigned long,AUCTIONINFO*> m_CardItem;
	/* this+ 88 */ std::map<unsigned long,AUCTIONINFO*> m_EtcItem;
	/* this+104 */ CMemoryMgr<AUCTIONINFO> m_ArmorPool;
	/* this+140 */ CMemoryMgr<AUCTIONINFO> m_WeaponPool;
	/* this+176 */ CMemoryMgr<AUCTIONINFO> m_CardPool;
	/* this+212 */ CMemoryMgr<AUCTIONINFO> m_EtcPool;

public:
	CAuctionCtrl();
	virtual ~CAuctionCtrl();
};
