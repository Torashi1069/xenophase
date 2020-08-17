#pragma once
#include "std/map"
#include "struct.hpp"
#include "CAuctionDB.hpp"
#include "CDateTime.h"
#include "NetLib/MemoryMgr.h"
class CPC;


class CAuctionCtrl
{
	/* this+  0 */ public: // const CAuctionCtrl::`vftable'
	/* this+  4 */ private: int m_ZoneServerID;
	/* this+  8 */ private: CAuctionDB m_AuctionDB;
	/* this+ 28 */ private: CDateTime m_DateTime;
	/* this+ 32 */ private: unsigned long m_lastTime;
	/* this+ 36 */ private: int m_EndChkItemType;
	/* this+ 40 */ private: mystd::map<unsigned long,AUCTIONINFO *> m_ArmorItem;
	/* this+ 52 */ private: mystd::map<unsigned long,AUCTIONINFO *> m_WeaponItem;
	/* this+ 64 */ private: mystd::map<unsigned long,AUCTIONINFO *> m_CardItem;
	/* this+ 76 */ private: mystd::map<unsigned long,AUCTIONINFO *> m_EtcItem;
	/* this+ 88 */ private: CMemoryMgr<AUCTIONINFO> m_ArmorPool;
	/* this+136 */ private: CMemoryMgr<AUCTIONINFO> m_WeaponPool;
	/* this+184 */ private: CMemoryMgr<AUCTIONINFO> m_CardPool;
	/* this+232 */ private: CMemoryMgr<AUCTIONINFO> m_EtcPool;

	enum
	{
		TYPE_AUCTION_ARMOR  = 0,
		TYPE_AUCTION_WEAPON = 1,
		TYPE_AUCTION_CARD   = 2,
		TYPE_AUCTION_ETC    = 3,
	};

	public: CAuctionCtrl::CAuctionCtrl(void);
	public: virtual CAuctionCtrl::~CAuctionCtrl(void);
	public: HOOKED void CAuctionCtrl::Init(unsigned int ZoneServerID, const char* DSN, const char* UID, const char* PASS, const char* DB, char type);
	public: void CAuctionCtrl::Process(void);
	public: int CAuctionCtrl::AddAuction(CPC* pPC, unsigned long NowPrice, unsigned long MaxPrice, int Hour, CommonItemInfo* pCommonItemInfo, char* pItemBuffer, int ItemLen);
	public: int CAuctionCtrl::DeleteAuction(unsigned long AuctionID, int ItemType);
	public: int CAuctionCtrl::ChangeBuyerAuction(CPC* pBuyerPc, unsigned long AuctionID, unsigned long BuyAID, unsigned long BuyGID, char* BuyName, int NowPrice);
	public: void CAuctionCtrl::FindItem(unsigned long AccountID, int ItemType, int Page);
	public: void CAuctionCtrl::FindItemAuctionID(unsigned long AccountID, unsigned long AuctionID);
	public: void CAuctionCtrl::FindItemName(unsigned long AccountID, char* ItemName, int Page);
	public: int CAuctionCtrl::AuctionAddCancel(unsigned long AuctionID, unsigned long SellerAID, unsigned long SellerGID);
	public: int CAuctionCtrl::ReqMyInfo(int Type, unsigned long AID, unsigned long GID);
	public: int CAuctionCtrl::MySellStop(unsigned long AuctionID, unsigned long AID, unsigned long GID);
	public: int CAuctionCtrl::GetCountSellItem(unsigned long AID, unsigned long GID);
	public: int CAuctionCtrl::GetCountBuyItem(unsigned long AID, unsigned long GID);
	private: int CAuctionCtrl::SendMailAuctionEnd(AUCTIONINFO* pAuctionInfo);
	private: int CAuctionCtrl::SendMailAuctionCanle(AUCTIONINFO* pAuctionInfo);
	private: int CAuctionCtrl::SendBuyerAuctionCancel(AUCTIONINFO* pAuctionInfo, unsigned long AuctionID);
	private: void CAuctionCtrl::TimeOver(int ItemType);
	private: AUCTIONINFO* CAuctionCtrl::GetAuctionInfo(unsigned long AuctionID);
	private: void CAuctionCtrl::ItemParser(int PaserType);
	private: int CAuctionCtrl::GetAuctionType(int ITID);
	private: void CAuctionCtrl::SendAuctionInfo(unsigned long AID, int ItemCounter, int MaxCounter, char* Buffer, int BufferSize);
	private: void CAuctionCtrl::GetClientItemName(int ITID, char* ItemName);

private:
	static hook_method<void (CAuctionCtrl::*)(unsigned int ZoneServerID, const char* DSN, const char* UID, const char* PASS, const char* DB, char type)> CAuctionCtrl::_Init;
	static hook_method<void (CAuctionCtrl::*)(void)> CAuctionCtrl::_Process;
	static hook_method<int (CAuctionCtrl::*)(CPC* pPC, unsigned long NowPrice, unsigned long MaxPrice, int Hour, CommonItemInfo* pCommonItemInfo, char* pItemBuffer, int ItemLen)> CAuctionCtrl::_AddAuction;
	static hook_method<int (CAuctionCtrl::*)(unsigned long AuctionID, int ItemType)> CAuctionCtrl::_DeleteAuction;
	static hook_method<int (CAuctionCtrl::*)(CPC* pBuyerPc, unsigned long AuctionID, unsigned long BuyAID, unsigned long BuyGID, char* BuyName, int NowPrice)> CAuctionCtrl::_ChangeBuyerAuction;
	static hook_method<void (CAuctionCtrl::*)(unsigned long AccountID, int ItemType, int Page)> CAuctionCtrl::_FindItem;
	static hook_method<void (CAuctionCtrl::*)(unsigned long AccountID, unsigned long AuctionID)> CAuctionCtrl::_FindItemAuctionID;
	static hook_method<void (CAuctionCtrl::*)(unsigned long AccountID, char* ItemName, int Page)> CAuctionCtrl::_FindItemName;
	static hook_method<int (CAuctionCtrl::*)(unsigned long AuctionID, unsigned long SellerAID, unsigned long SellerGID)> CAuctionCtrl::_AuctionAddCancel;
	static hook_method<int (CAuctionCtrl::*)(int Type, unsigned long AID, unsigned long GID)> CAuctionCtrl::_ReqMyInfo;
	static hook_method<int (CAuctionCtrl::*)(unsigned long AuctionID, unsigned long AID, unsigned long GID)> CAuctionCtrl::_MySellStop;
	static hook_method<int (CAuctionCtrl::*)(unsigned long AID, unsigned long GID)> CAuctionCtrl::_GetCountSellItem;
	static hook_method<int (CAuctionCtrl::*)(unsigned long AID, unsigned long GID)> CAuctionCtrl::_GetCountBuyItem;
	static hook_method<int (CAuctionCtrl::*)(AUCTIONINFO* pAuctionInfo)> CAuctionCtrl::_SendMailAuctionEnd;
	static hook_method<int (CAuctionCtrl::*)(AUCTIONINFO* pAuctionInfo)> CAuctionCtrl::_SendMailAuctionCanle;
	static hook_method<int (CAuctionCtrl::*)(AUCTIONINFO* pAuctionInfo, unsigned long AuctionID)> CAuctionCtrl::_SendBuyerAuctionCancel;
	static hook_method<void (CAuctionCtrl::*)(int ItemType)> CAuctionCtrl::_TimeOver;
	static hook_method<AUCTIONINFO* (CAuctionCtrl::*)(unsigned long AuctionID)> CAuctionCtrl::_GetAuctionInfo;
	static hook_method<void (CAuctionCtrl::*)(int PaserType)> CAuctionCtrl::_ItemParser;
	static hook_method<int (CAuctionCtrl::*)(int ITID)> CAuctionCtrl::_GetAuctionType;
	static hook_method<void (CAuctionCtrl::*)(unsigned long AID, int ItemCounter, int MaxCounter, char* Buffer, int BufferSize)> CAuctionCtrl::_SendAuctionInfo;
	static hook_method<void (CAuctionCtrl::*)(int ITID, char* ItemName)> CAuctionCtrl::_GetClientItemName;
};
