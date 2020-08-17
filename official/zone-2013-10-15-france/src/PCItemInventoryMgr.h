#pragma once
#include "Enum.h"
#include "PCBodyItemIV.h"
#include "PCCartItemIV.h"
#include "PCStoreItemIV.h"
#include "Struct.h"
struct CommonItemInfo;
struct Request;
class CITP;
class InventoryItem;
class IVItEquipItem;
class IVItItem;
class CPC;


struct PASERRET
{
	enum enumError
	{
		ERROR_NONE                         = 0,
		ERROR_CRITICAL_MEMORY_ALLOC        = 1,
		ERROR_CRITICAL_UNKNOWN_VERSION     = 2,
		ERROR_CRITICAL_MISMATCH_TYPE       = 3,
		ERROR_CRITICAL_UNKNOWN_PASING_TYPE = 4,
		ERROR_CRITICAL_ZIP_UNCOMPRESS      = 5,
		ERROR_CRITICAL_NOTEXIST_TYPE       = 6,
		ERROR_CRITICAL_UNKNOWN             = 7,
		ERROR_ADD                          = 8,
	};

	/* this+0 */ enumError m_error;
	/* this+4 */ int m_used_bytes;

	PASERRET() : m_error(ERROR_NONE), m_used_bytes(0) { }
	PASERRET(const enumError in_error, const int in_used_bytes) : m_error(in_error), m_used_bytes(in_used_bytes) { }
};


class CPCItemInventoryMgr
{
public:
//	void GetAllEquipedItemInfoWithBinaryFormat3(class std::vector<unsigned char,std::allocator<unsigned char> > &, const bool);
//	int GetBodyItemDBFormat(unsigned char *, const int);
//	int GetStoreItemDBFormat(unsigned char *, const int);
//	int GetCartItemDBFormat(unsigned char *, const int);
	void StoreItemReset();
//	int IsCartOn();

public:
	CPCItemInventoryMgr();
	virtual ~CPCItemInventoryMgr();
	void Init();
//	void Reset();
	void SetMyOwner(CPC* owner);
	void OnMediatorRequest(Request* request);
//	void OnDispatchClientRequest(struct Request *);
//	int IsBodyItemParsing();
	IVItItem* Add(IVItItem* item, unsigned long type, unsigned short desPos, BOOL IsClientNotified, BOOL IsFroceInsert);
	BOOL isBodyAddMailItem(unsigned short ITID, unsigned long ItemType, int count, EQUIPSLOTINFO slotInfo, __int64 UniqueSerialNum);
//	class IVItItem * Remove(unsigned long, short, short);
//	void NotifyPickUpToParty(class IVItItem *);
	static BOOL DBValueParser(CommonItemInfo* item, char* buf, int len);
//	static int DBValueParserV3under(struct CommonItemInfo *, char *, int);
	static BOOL DBValueParserV4(CommonItemInfo* out_pItemINFO, char* in_pBuffer, const int in_BufferBytes);
	static int DBValueParserV4_INVENTORYITEMTYPE_NORMALITEM(const unsigned short in_Version, CommonItemInfo* out_pItemINFO, char* in_pIBDBuffer);
	static int DBValueParserV4_INVENTORYITEMTYPE_NORMALARROWITEM(const unsigned short in_Version, CommonItemInfo* out_pItemINFO, char* in_pIBDBuffer);
	static int DBValueParserV4_INVENTORYITEMTYPE_EQUIPITEM(const unsigned short in_Version, CommonItemInfo* out_pItemINFO, char* in_pIBDBuffer);
	static int DBValueParserV4_INVENTORYITEMTYPE_CASHPOINTITEM(const unsigned short in_Version, CommonItemInfo* out_pItemINFO, char* in_pIBDBuffer);
	PASERRET::enumError Parse(Request* in_pRequest, const bool in_bNotify, const bool in_bUseZip, const bool in_bUseItemType);
private:
//	enum PASERRET::enumError ParseV4(struct Request *, const bool, const bool, const bool);
//	int ParseV3under(struct Request *, int, int, int);
//	class PASERRET ParseV4_INVENTORYITEMTYPE_NORMALITEM(const int, const bool, const int, const char *);
//	class PASERRET ParseV4_INVENTORYITEMTYPE_NORMALARROWITEM(const int, const bool, const int, const char *);
//	class PASERRET ParseV4_INVENTORYITEMTYPE_EQUIPITEM(const int, const bool, const int, const char *);
//	class PASERRET ParseV4_INVENTORYITEMTYPE_QUESTITEM(const int, const bool, const int, const char *);
//	class PASERRET ParseV4_INVENTORYITEMTYPE_CASHPOINTITEM(const int, const bool, const int, const char *);
//	class IVItItem * GetThrowItem(const short, const short, const int);
public:
	void HireItemCheckAdd(const enumInventoryType in_InventoryType, IVItItem* in_pItem);
	unsigned long GetEquipLocationbyIndex(const int in_index);
	unsigned short GetEquipItemIDbyIndex(const int in_index);
//	void ChangeMaterial(const class std::vector<std::pair<int,int>,std::allocator<std::pair<int,int> > > &);
//	void GN_MIX_COOKING_operation(const int);
//	void GN_MAKEBOMB_operation(const int);
//	void GN_S_PHARMACY_operation(const int);
//	int Save(struct Request *);
//	void MoveItem(unsigned char, short, int);
	IVItItem* SearchItemByUniqueIdentityNum(const enumInventoryType in_InventoryType, const __int64 in_UID);
	IVItItem* SearchItem(unsigned long type, short index);
	IVItItem* SearchItemByID(unsigned long type, unsigned short ITID);
	BOOL DeleteItem(unsigned long type, short index, short count);
//	void DeleteAllBodyItem();
	void NotifyItemInfo(const unsigned long in_Type);
	void RefreshItemWeight();
//	bool ParseDBFmtBodyItemData(const int, const unsigned char *);
//	bool IsBodyItemEmpty();
//	void OnHireItemReturn(const short);
//	class CItem * OnThrowItem(short, short, int);
//	void OnUseItem(short, unsigned long);
//	void OnWearItem(short, unsigned short);
//	void OnPickUpItem(unsigned long);
//	void OnTakeOffEquip(short);
//	short GetStatusValueOfEquipedItem(unsigned long);
	int GetBodyItemWeight();
//	int GetCartItemWeight();
//	int GetExchangeItemWeight();
	BOOL GetBodyItemCount(unsigned short id, int& value);
	BOOL GetJustBodyItemCount(unsigned short id, int& value);
	BOOL GetJustEquipItemCount(unsigned short id, int& value);
//	bool IsHaveBodyItem(unsigned short, bool);
	void OnSetBodyItem(int npcAID, int ITID, int count);

	enum IsAddableItemToBodyRet
	{
		LOGICAL_ERROR     = -1,
		SUCCESS            = 0,
		OVERWEIGHT         = 1,
		OVERCOUNT          = 2,
		RUNE_OVERCOUNT     = 3,
		EACHITEM_OVERCOUNT = 4,
	};
//	int IsAddableMoreItemToBody(unsigned short, short, class CPC *);
//	void OnExecExchangeItem(int, const int, const int);
//	void CancelExchangeItem();
	void TakeOffEquip(unsigned long loc);
//	void TakeOffAllEquip();
	int GetBodyItemWeightByPercent();
	CITP* GetITPEquipedWeapon();
	short GetEquipedWeaponType();
//	class CITP * GetITPEquipedArmor();
	int GetPlusPowerOfItem(unsigned long type);
//	class IVItItem * UpdateBodyItemCount(unsigned short, int, unsigned short, bool);
	int GetAttackDistance();
	IVItItem* GetEquipedArrow();
//	int OnNotifyItemIdentifyList();
//	int OnNotifyMakingArrowList();
//	int OnNotifyMakingElementalList();
//	int OnNotifyCookingList();
//	int OnNotifyRepairItemList(class CPC *);
//	void IdentifyItem(short);
	IVItEquipItem* GetEquipedItem(unsigned long loc);
//	void ReqItemCompositionList(short);
//	void ReqItemComposition(short, short);
	void ReqMakeArrow(unsigned short id);
//	void ReqMakeItem(short, unsigned short);
//	void DeadPenaltyInEquip(int);
//	void DeadPenaltyInBody(int);
//	int CheckMaxItemCount(int, int);
//	int isAddBodyItem(int, int);
//	bool isAddBodyCashItem(int, int);
//	bool IsMaxWeight(int, int);
//	int OnNotifyWeaponItemList();
//	int IsInventoryRemainCount(int, int);
//	class IVItItem * OnGetItemSocket(int, int *);
//	class IVItItem * OnGetNonSlotItemSocket(const unsigned short, int *, const unsigned char);
//	bool ParseDBFmtCartItemData(const int, const unsigned char *);
	void NotifyStoreItemCountInfo();
//	void CloseStore();
	int IsStoreOpen();
	void ParseDBFmtStoreItemData(const int in_Length, const unsigned char* in_pData);
//	void NotifyAckAddItemToCart(unsigned char, class IVItItem *);
//	void NotifyCartItemCountInfo();
//	void CloseCart();
//	void OnReqOpenMCStore(int, char *);
//	void OnReqOpenMCStore2(int, char *);
//	void NotifyItemInfoInMCStore(unsigned long);
//	void PurchaseItemFromMCStore(unsigned long, int, char *, const unsigned long);
//	void NotifyMCStore(unsigned long);
//	void CancelMCStore();
//	void NotifyMYMCStoreItemInfo();
//	int IsMCStoreOpen();
//	void NotifyMySellableItem(float);
//	void PurchaseItemR2(const int, const char *);
//	void SellItem(const class std::vector<CZ_SELL_ITEM,std::allocator<CZ_SELL_ITEM> > &, const float);
//	void OnExchangeItem(int);
	virtual IVItItem* AllocInventoryItem(unsigned short ID, short count);
	void FreeInventoryItem(InventoryItem* item);
//	void UpgradeRefiningLevel(unsigned long, int);
//	void DestoryItemOnRefining(unsigned long);
//	void NotifyAckAddItemToBody(unsigned long, class IVItItem *);
//	void InsertEmpeliumItem(unsigned short);
//	int GetEmpeliumItem();
//	void CallPet(class IVItEquipItem *);
//	int SendPetEggList();
//	void ConvertPetEggToPet(short);
//	int ConvertPetToPetEgg(int, int);
//	class IVItItem * SearchPet(int);
	CPC* GetPC();
//	int GetDamagedItemNum();
//	void RepairDamagedItem();
//	void RandomDivision(class CItem *);
	int GetCountItemOfMyGID(unsigned long ITID);
//	int RemoveItemOfMyGID(unsigned long, int);
//	void CreateItemOfMyGID(unsigned long, int, unsigned long);
//	class IVItEquipItem * ConvertPet(class IVItItem *);
//	int GetMailItemSize();
//	void CancelMailItem(int, int);
//	int GetMailItem(class IVItItem &, int &, char *, const int, int &, unsigned long &);
	BOOL PutMailBinaryItem(char* ItemBuffer, int ItemLen);
//	int GetAuctionItemSize();
//	void CancelAuctionItem();
//	int GetAuctionItem(class IVItItem &, int &, char *, const int, int &);
//	class IVItItem * BuyCashPointItem(const unsigned short);
//	int GetBlacksmithPlusAttackPower(int);
//	bool GetBlacksmithWeaponProperty(int, int &);
//	void SetItemPartyInMap(int, int, int);
//	void DownGradeRefiningLevel(unsigned long, int);
//	short GetEquipeditemLocation(const short);
//	bool IsUnPackItem(const class std::vector<NEO_PACKAGEITEM::ProvideItem,std::allocator<NEO_PACKAGEITEM::ProvideItem> > &);
//	const bool IsOpenBuyingStore();
//	const unsigned long GetBuyingStoreID();
//	const char * GetBuyingStoreName();
//	const int GetBuyingStoreItemListCnt();
//	const int GetLimitMoneyBuyingStore();
//	const int SubLimitMoneyBuyingStore(const int);
//	const bool IsTradeBuyingStore(const int);
//	void ResetBuyingStore();
//	void CreateBuyingStore(const char *, const int);
//	bool SetItemBuyingStore(const unsigned short, const int, const short, const unsigned char);
//	const unsigned long GetBuyingStoreSSI_ID(const unsigned short);
//	const int GetPriceBuyingStore(const short);
//	const struct std::pair<int,short> GetPriceAndCntBuyingStore(const short);
//	bool IsPossibleTradeItem(const unsigned short);
//	void CancelBuyingStore();
//	void CloseBuyingStore();
//	void SendMyItemListBuyingStore();
//	void MutiCast_NotifyBuyingStoreEntry();
//	void NotifyDisappearBuyingStoreEntry();
//	void NotifyByingStoreEntry(const unsigned long);
//	void SendFailedOpenBuyingStore(const int , const int );
//	void SendtoSeller_FailedTradeBuyingStore(const int , const unsigned short );
//	void SendtoBuyer_FailedTradeBuyingStore(const int );
//	void NotifyItemInfoInBuyingStore(const unsigned long );
//	void OpenBuyingStore(const PACKET_CZ_REQ_OPEN_BUYING_STORE* , std::vector<PRODUCTINFO_IN_BUYING_STORE const*>& );
//	void ReqTradeBuyingStore(const char* , const int );
//	int GetBodyItemSize();
//	void ForceChangeSpriteNonCostume();
//	void ForceChangeSpriteCostume();
//	void SendMergeItemOpen();
//	void MergeItem(const std::vector<short>& );

private:
//	void OnInventoryTabPlace(const int, bool);
//	int GetExchangeItemSize();

private:
	/* this+  0 */ //const CPCItemInventoryMgr::`vftable';
	/* this+  4 */ std::list<unsigned short> m_tempItemInventory;

private:
//	void NotifyAckAddItemToStore(class IVItItem *);
//	void NotifySoldedResultOnMCStore(short, short);
//	class IVItEquipItem * ConvertPetEgg(class IVItItem *);
//	bool IsEnable_UseItem(unsigned short);
//	static bool Check_PetNameModified(int, struct EQUIPSLOTINFO *);
//	void OnUsePackageItem(const int, const int, const int, const unsigned long, class IVItItem * const);

	/* this+ 16 */ CPCBodyItemIV m_bodyItem;
	/* this+ 52 */ CPCCartItemIV m_cartItem;
	/* this+ 88 */ CPCStoreItemIV m_storeItem;
	/* this+124 */ BYTE m_exchangeItem[36]; //CPCExchangeItemIV m_exchangeItem; //TODO
	/* this+160 */ BYTE m_MailItem[36]; //CPCExtraItemIV m_MailItem; //TODO
	/* this+196 */ BYTE m_AuctionItem[36]; //CPCExtraItemIV m_AuctionItem; //TODO
	/* this+232 */ BYTE m_equipedItem[128]; //CPCEquipedItemIV m_equipedItem; //TODO
	/* this+360 */ BYTE m_mcStoreItem[184]; //CPCMCStoreItemIV m_mcStoreItem; //TODO
	/* this+544 */ BYTE m_IVItItemFactory[184]; //CIVItItemFactory m_IVItItemFactory; //TODO
	/* this+728 */ CPC* m_owner;
	/* this+732 */ int m_bodyItemParsing;
	/* this+736 */ unsigned long m_MCStoreUniqueID;
	/* this+740 */ BYTE m_BuyingStore[124]; //CPCBuyingStore m_BuyingStore; //TODO

private:
//	bool OnUseIUtemCashPointItem(const int , CITPCashPointItem* const );
};
C_ASSERT( sizeof CPCItemInventoryMgr == 864 );
