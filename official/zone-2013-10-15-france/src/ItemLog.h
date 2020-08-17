#pragma once
class CCharacter; // #include "Character.h"
class CITP; // #include "ITP.h"
class CPC; // #include "PC.h"
class IVItItem; // #include "Player/Inventory/CIvItem.h"
#include "Struct.h"
#include "shared/DatabaseLog.h"


enum enumITEMLOGACTIONTYPE
{
	ITEMLOG_THROWITEM                  = 0,
	ITEMLOG_PICKUPITEM                 = 1,
	ITEMLOG_USEITEM                    = 2,
	ITEMLOG_EXECEXCHANGEITEM           = 3,
	ITEMLOG_PURCHASEITEMFROMMCSTORE    = 4,
	ITEMLOG_PURCHASEITEM               = 5,
	ITEMLOG_SELLITEM                   = 6,
	ITEMLOG_MVP                        = 7,
	ITEMLOG_STEAL                      = 8,
	ITEMLOG_UPDATEBODYITEM_PLUS        = 9,
	ITEMLOG_UPDATEBODYITEM_SUB         = 10,
	ITEMLOG_NPC_SETITEM                = 11,
	ITEMLOG_MOBILE_EVENT               = 12,
	ITEMLOG_GM_CREATEITEM              = 13,
	ITEMLOG_ITEM_CREATEITEM            = 14,
	ITEMLOG_BS_CREATEITEM              = 15,
	ITEMLOG_QUEST_ITEMPLUS             = 16,
	ITEMLOG_QUEST_ITEMSUB              = 17,
	ITEMLOG_QUEST_CHANGEMONEY          = 18,
	ITEMLOG_MOVEITEM_BODY_STORE        = 19,
	ITEMLOG_MOVEITEM_BODY_CART         = 20,
	ITEMLOG_MOVEITEM_STORE_BODY        = 21,
	ITEMLOG_MOVEITEM_STORE_CART        = 22,
	ITEMLOG_MOVEITEM_CART_BODY         = 23,
	ITEMLOG_MOVEITEM_CART_STORE        = 24,
	ITEMLOG_MAIL_SEND                  = 25,
	ITEMLOG_AUCTION_END                = 26,
	ITEMLOG_MAIL_RECEIVE               = 27,
	ITEMLOG_MAIL_AUTO_DELETE           = 28,
	ITEMLOG_AUCTION_START              = 29,
	ITEMLOG_AUCTION_SELLER_CANCLE      = 30,
	ITEMLOG_AUCTION_BUYER_ADD          = 31,
	ITEMLOG_AUCTION_BUYER_CANCLE       = 32,
	ITEMLOG_MAIL_RETURN                = 33,
	ITEMLOG_DELETE_ERROR               = 34,
	ITEMLOG_CASH_BUY_ITEM              = 35,
	ITEMLOG_CASH_CREATEITEM            = 36,
	ITEMLOG_CASH_AUTO_DELETE           = 37,
	ITEMLOG_CASH_MOBILE                = 38,
	ITEMLOG_CASH_BILLING_SERVER        = 39,
	ITEMLOG_CASH_REAL_MOBILE           = 40,
	ITEMLOG_TRADE_ITEM_BUYING_STORE    = 41,
	ITEMLOG_GETITEM2                   = 42,
	ITEMLOG_CLIENT_MODIFY              = 43,
	ITEMLOG_MERGEITEM                  = 44,
	ITEMLOG_RESULT_MERGEDITEM          = 45,
	ITEMLOG_RENT_ITEM                  = 46,
	ITEMLOG_SELLITEM2                  = 47,
	ITEMLOG_FAILED_ITEM_EXCHANGE       = 48,
	ITEMLOG_MOVEITEM_BODY_GUILDSTORAGE = 49,
	ITEMLOG_MOVEITEM_CART_GUILDSTORAGE = 50,
	ITEMLOG_MOVEITEM_GUILDSTORAGE_BODY = 51,
	ITEMLOG_MOVEITEM_GUILDSTORAGE_CART = 52,
};


struct SITEMLOG_USERINFO
{
	/* this+ 0 */ int m_nAccountID;
	/* this+ 4 */ char m_szAccount[24];
	/* this+28 */ DWORD m_dwCharID;
	/* this+32 */ char m_szCharName[24];
};


struct SITEMLOG
{
	/* this+  0 */ int m_nVersion;
	/* this+  4 */ int m_nServerID;
	/* this+  8 */ int m_ActionType; // enumITEMLOGACTIONTYPE
	/* this+ 12 */ char m_szIP[20];
	/* this+ 32 */ int m_nEventPosX;
	/* this+ 36 */ int m_nEventPosY;
	/* this+ 40 */ SITEMLOG_USERINFO m_srcUserInfo;
	/* this+ 96 */ SITEMLOG_USERINFO m_desUserInfo;
	/* this+152 */ DWORD m_dwItemSerialcode;
	/* this+156 */ char m_szItemName[24];
	/* this+180 */ DWORD m_dwITID;
	/* this+184 */ DWORD m_dwItemCount;
	/* this+188 */ char m_szMapName[24+1];
	/* this+216 */ DWORD m_dwPrice;
	/* this+220 */ EQUIPSLOTINFO m_equipSlotInfo;
	/* this+228 */ int m_nRefingLevel;
	/* this+232 */ DWORD m_dwAuctionID;
	/* this+236 */ DWORD m_dwRemainZeny;
	/* this+240 */ DWORD m_dwDestRemainZeny;
	/* this+248 */ __int64 m_NP_ItemSerialNum;
	/* this+256 */ time_t m_NP_ItemHireExpireDate;
	/* this+260 */ int m_NP_bCashItem;
	/* this+264 */ __int64 m_Identity;
};


class CItemLog : public CDatabaseLog<SITEMLOG*>
{
public:
	enum { KEEP_OBJECT_MAXCNT = 10000 };

public:
	void AddItemLog(int nType, CPC* pPC, CCharacter* pDestChar, IVItItem* pIvitItem, int nPrice, int nCount, char* Tx_ID, const __int64 in_Identity);
	void AddMailAuctionLog(unsigned long AuctionID, int nType, unsigned long SrcAID, unsigned long SrcGID, char* SrcName, unsigned long DestAID, unsigned long DestGID, char* DestName, CommonItemInfo* pItemInfo, int nPrice);
	void AddMailSendLog(unsigned long AuctionID, int nType, CPC* pPC, unsigned long DestAID, unsigned long DestGID, char* DestName, CommonItemInfo* pItemInfo, int nPrice);
	void AddMailReceiveLog(int nType, CPC* pPC, unsigned long DestAID, unsigned long DestGID, char* DestName, CommonItemInfo* pItemInfo, int nPrice);
	void AddItemLogOnMoney(int nType, CPC* pPC, CCharacter* pDestChar, int nPrice, int nCount, unsigned long AuctionID, const __int64 in_Identity);
	virtual void ConnectToDatabase(const char* Log);
	void AddCITPLog(int nType, CPC* pPC, CPC* pDestPC, CITP* piteminfo, int nPrice, int nCount);

private:
	virtual BOOL SaveToDatabase(SQLHSTMT hStmt, SITEMLOG* pLog);
	BOOL SaveToDatabaseV1(SQLHSTMT hStmt, SITEMLOG* pLog);
	BOOL SaveToDatabaseV2(const SQLHSTMT in_hStmt, SITEMLOG* pLog);
};
