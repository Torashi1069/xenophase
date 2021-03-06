#pragma once
#include "CItem.hpp"
#include "InventoryItem.hpp"
#include "CIVItItemFactory.hpp"
#include "CPCBodyItemIV.hpp"
#include "CPCCartItemIV.hpp"
#include "CPCEquipedItemIV.hpp"
#include "CPCMCStoreItemIV.hpp"
#include "PCStoreItemIV.h"
#include "CPCExchangeItemIV.hpp"
#include "CPCExtraItemIV.hpp"
#include "std/list"
struct Request;
class CPC;


class CPCItemInventoryMgr
{
	struct vtable_t // const CPCItemInventoryMgr::`vftable'
	{
		void* (CPCItemInventoryMgr::* scalar_deleting_destructor)(unsigned int flags);
		IVItItem* (CPCItemInventoryMgr::* AllocInventoryItem)(unsigned short ID, short count);
	};

	/* this+  0 */ public: //const CPCItemInventoryMgr::`vftable';
	/* this+  4 */ private: mystd::list<unsigned short> m_tempItemInventory;
	/* this+ 16 */ private: CPCBodyItemIV m_bodyItem;
	/* this+ 52 */ private: CPCCartItemIV m_cartItem;
	/* this+ 88 */ private: CPCStoreItemIV m_storeItem;
	/* this+124 */ private: CPCExchangeItemIV m_exchangeItem;
	/* this+160 */ private: CPCExtraItemIV m_MailItem;
	/* this+196 */ private: CPCExtraItemIV m_AuctionItem;
	/* this+232 */ private: CPCEquipedItemIV m_equipedItem;
	/* this+344 */ private: CPCMCStoreItemIV m_mcStoreItem;
	/* this+520 */ private: CIVItItemFactory m_IVItItemFactory;
	/* this+764 */ private: CPC* m_owner;
	/* this+768 */ private: int m_bodyItemParsing;

	public: CPCItemInventoryMgr::CPCItemInventoryMgr(void);
	public: virtual CPCItemInventoryMgr::~CPCItemInventoryMgr(void);
	//public: int CPCItemInventoryMgr::GetAllEquipedItemInfoWithBinaryFormat3(char* out_pBuffer, const int in_MaxBytes, const bool in_bPet);
	public: int CPCItemInventoryMgr::GetBodyItemDBFormat(unsigned char* out_pBuffer, const int in_MaxBytes);
	public: int CPCItemInventoryMgr::GetStoreItemDBFormat(unsigned char* out_pBuffer, const int in_MaxBytes);
	public: int CPCItemInventoryMgr::GetCartItemDBFormat(unsigned char* out_pBuffer, const int in_MaxBytes);
	public: void CPCItemInventoryMgr::StoreItemReset(void);
	public: int CPCItemInventoryMgr::IsCartOn(void);
	//public: void CPCItemInventoryMgr::Init(void);
	//public: void CPCItemInventoryMgr::Reset(void);
	//public: void CPCItemInventoryMgr::SetMyOwner(CPC* owner);
	public: void CPCItemInventoryMgr::OnMediatorRequest(Request* request);
	public: void CPCItemInventoryMgr::OnDispatchClientRequest(Request* request);
	//public: int CPCItemInventoryMgr::IsBodyItemParsing(void);
	public: IVItItem* CPCItemInventoryMgr::Add(IVItItem* item, unsigned long type, unsigned short desPos, int IsClientNotified, int IsFroceInsert);
	//public: int CPCItemInventoryMgr::isBodyAddMailItem(unsigned short ITID, unsigned long ItemType, int, EQUIPSLOTINFO slotInfo, __int64 UniqueSerialNum);
	//public: IVItItem* CPCItemInventoryMgr::Remove(unsigned long type, short index, short count);
	public: void CPCItemInventoryMgr::NotifyPickUpToParty(IVItItem* item);
	public: static int CPCItemInventoryMgr::DBValueParser(CommonItemInfo* item, char* buf, int len);
	//private: static int CPCItemInventoryMgr::DBValueParserV3under(CommonItemInfo* item, char* buf, int len);
	//private: static int CPCItemInventoryMgr::DBValueParserV4(CommonItemInfo* out_pItemINFO, char* in_pBuffer, const int in_BufferBytes);
	//private: static int CPCItemInventoryMgr::DBValueParserV4_INVENTORYITEMTYPE_NORMALITEM(const unsigned short in_Version, CommonItemInfo* out_pItemINFO, char* in_pIBDBuffer);
	//private: static int CPCItemInventoryMgr::DBValueParserV4_INVENTORYITEMTYPE_NORMALARROWITEM(const unsigned short in_Version, CommonItemInfo* out_pItemINFO, char* in_pIBDBuffer);
	//private: static int CPCItemInventoryMgr::DBValueParserV4_INVENTORYITEMTYPE_EQUIPITEM(const unsigned short in_Version, CommonItemInfo*out_pItemINFO, char* in_pIBDBuffer);
	//private: static int CPCItemInventoryMgr::DBValueParserV4_INVENTORYITEMTYPE_CASHPOINTITEM(const unsigned short in_Version, CommonItemInfo* out_pItemINFO, char* in_pIBDBuffer);
	public: PASERRET::enumError CPCItemInventoryMgr::Parse(Request* in_pRequest, const bool in_bNotify, const bool in_bUseZip, const bool in_bUseItemType);
	private: PASERRET::enumError CPCItemInventoryMgr::ParseV4(Request* in_pRequest, const bool in_bNotify, const bool in_bUseZip, const bool in_bUseItemType);
	//private: PASERRET CPCItemInventoryMgr::ParseV4_INVENTORYITEMTYPE_NORMALITEM(const int in_AddType, const bool in_bNotify, const int in_IBDataVer, const char* in_pIBDBuffer);
	//private: PASERRET CPCItemInventoryMgr::ParseV4_INVENTORYITEMTYPE_NORMALARROWITEM(const int in_AddType, const bool in_bNotify, const int in_IBDataVer, const char* in_pIBDBuffer);
	//private: PASERRET CPCItemInventoryMgr::ParseV4_INVENTORYITEMTYPE_EQUIPITEM(const int in_AddType, const bool in_bNotify, const int in_IBDataVer, const char* in_pIBDBuffer);
	//private: PASERRET CPCItemInventoryMgr::ParseV4_INVENTORYITEMTYPE_QUESTITEM(const int in_AddType, const bool in_bNotify, const int in_IBDataVer, const char*in_pIBDBuffer);
	//private: PASERRET CPCItemInventoryMgr::ParseV4_INVENTORYITEMTYPE_CASHPOINTITEM(const int in_AddType, const bool in_bNotify, const int in_IBDataVer, const char* in_pIBDBuffer);
	//private: int CPCItemInventoryMgr::ParseV3under(Request* request, int bNotify, int bUseZip, int bUseItemType);
	//public: void CPCItemInventoryMgr::HireItemCheckAdd(const enum enumInventoryType in_InventoryType, IVItItem* in_pItem);
	public: int CPCItemInventoryMgr::Save(Request* request);
	//public: void CPCItemInventoryMgr::MoveItem(unsigned char type, short index, int count);
	public: IVItItem* CPCItemInventoryMgr::SearchItemByUniqueIdentityNum(const enum enumInventoryType in_InventoryType, const __int64 in_UID);
	public: IVItItem* CPCItemInventoryMgr::SearchItem(unsigned long type, short index);
	public: IVItItem* CPCItemInventoryMgr::SearchItemByID(unsigned long type, unsigned short ITID);
	public: int CPCItemInventoryMgr::DeleteItem(unsigned long type, short index, short count);
	public: void CPCItemInventoryMgr::NotifyItemInfo(const unsigned long in_Type);
	public: void CPCItemInventoryMgr::RefreshItemWeight(void);
	public: bool CPCItemInventoryMgr::ParseDBFmtBodyItemData(const int in_Length, const unsigned char* in_pData);
	//public: bool CPCItemInventoryMgr::IsBodyItemEmpty(void);
	//public: void CPCItemInventoryMgr::OnHireItemReturn(const short in_Index);
	//public: CItem* CPCItemInventoryMgr::OnThrowItem(short index, short count, int type);
	public: void CPCItemInventoryMgr::OnUseItem(short index, unsigned long AID);
	public: void CPCItemInventoryMgr::OnWearItem(short index, unsigned short wearLocation);
	public: void CPCItemInventoryMgr::OnPickUpItem(unsigned long ITAID);
	public: void CPCItemInventoryMgr::OnTakeOffEquip(short index);
	//public: short CPCItemInventoryMgr::GetStatusValueOfEquipedItem(unsigned long type);
	public: int CPCItemInventoryMgr::GetBodyItemWeight(void);
	//public: int CPCItemInventoryMgr::GetCartItemWeight(void);
	//public: int CPCItemInventoryMgr::GetExchangeItemWeight(void);
	//public: int CPCItemInventoryMgr::GetBodyItemCount(unsigned short id, int& value);
	public: int CPCItemInventoryMgr::GetJustBodyItemCount(unsigned short id, int& value);
	public: int CPCItemInventoryMgr::GetJustEquipItemCount(unsigned short id, int& value);
	//public: bool CPCItemInventoryMgr::IsHaveBodyItem(unsigned short, bool);
	public: void CPCItemInventoryMgr::OnSetBodyItem(int npcAID, int ITID, int count);
	//public: int CPCItemInventoryMgr::IsAddableMoreItemToBody(unsigned short ITID, short count, CPC* other);
	//public: void CPCItemInventoryMgr::OnExecExchangeItem(int par1);
	public: void CPCItemInventoryMgr::CancelExchangeItem(void);
	public: void CPCItemInventoryMgr::TakeOffEquip(unsigned long loc);
	public: void CPCItemInventoryMgr::TakeOffAllEquip(void);
	public: int CPCItemInventoryMgr::GetBodyItemWeightByPercent(void);
	//public: CITP* CPCItemInventoryMgr::GetITPEquipedWeapon(void);
	//public: CITP* CPCItemInventoryMgr::GetITPEquipedArmor(void);
	public: int CPCItemInventoryMgr::GetPlusPowerOfItem(unsigned long type);
	//public: IVItItem* CPCItemInventoryMgr::UpdateBodyItemCount(unsigned short id, int count, unsigned short log, bool isidentified);
	//public: int CPCItemInventoryMgr::GetAttackDistance(void);
	public: IVItItem* CPCItemInventoryMgr::GetEquipedArrow();
	//public: int CPCItemInventoryMgr::OnNotifyItemIdentifyList(void);
	//public: int CPCItemInventoryMgr::OnNotifyMakingArrowList(void);
	//public: int CPCItemInventoryMgr::OnNotifyMakingElementalList(void);
	//public: int CPCItemInventoryMgr::OnNotifyCookingList(void);
	//public: int CPCItemInventoryMgr::OnNotifyRepairItemList(CPC* Operator);
	//public: void CPCItemInventoryMgr::IdentifyItem(short index);
	public: IVItEquipItem* CPCItemInventoryMgr::GetEquipedItem(unsigned long loc);
	//public: void CPCItemInventoryMgr::ReqItemCompositionList(short cardIndex);
	//public: void CPCItemInventoryMgr::ReqItemComposition(short cardIndex, short equipIndex);
	public: void CPCItemInventoryMgr::ReqMakeArrow(unsigned short id);
	//public: void CPCItemInventoryMgr::ReqMakeItem(short type, unsigned short id);
	//public: void CPCItemInventoryMgr::DeadPenaltyInEquip(int percent);
	//public: void CPCItemInventoryMgr::DeadPenaltyInBody(int percent);
	//public: int CPCItemInventoryMgr::CheckMaxItemCount(int item, int count);
	//public: bool CPCItemInventoryMgr::isAddBodyCashItem(int item, int count);
	//public: bool CPCItemInventoryMgr::IsMaxWeight(int item, int count);
	//public: int CPCItemInventoryMgr::OnNotifyWeaponItemList(void);
	//public: int CPCItemInventoryMgr::IsInventoryRemainCount(int item, int count);
	//public: IVItItem* CPCItemInventoryMgr::OnGetItemSocket(int itemid, int* card);
	//public: IVItItem* CPCItemInventoryMgr::OnGetNonSlotItemSocket(int itemid, int* card);
	public: void CPCItemInventoryMgr::ParseDBFmtStoreItemData(const int in_Length, const unsigned char* in_pData);
	public: bool CPCItemInventoryMgr::ParseDBFmtCartItemData(const int in_Length, const unsigned char* in_pData);
	public: void CPCItemInventoryMgr::NotifyStoreItemCountInfo(void);
	public: void CPCItemInventoryMgr::CloseStore(void);
	public: int CPCItemInventoryMgr::IsStoreOpen(void);
	//public: void CPCItemInventoryMgr::NotifyAckAddItemToCart(unsigned char cause, IVItItem* item);
	//public: void CPCItemInventoryMgr::NotifyCartItemCountInfo(void);
	//public: void CPCItemInventoryMgr::CloseCart(void);
	public: void CPCItemInventoryMgr::OnReqOpenMCStore(int len, char* buf);
	//public: void CPCItemInventoryMgr::OnReqOpenMCStore2(int len, char* buf);
	public: void CPCItemInventoryMgr::NotifyItemInfoInMCStore(unsigned long AID);
	public: void CPCItemInventoryMgr::PurchaseItemFromMCStore(unsigned long targetAID, int contentLength, char* buf);
	//public: void CPCItemInventoryMgr::NotifyMCStore(unsigned long AID);
	//public: void CPCItemInventoryMgr::CancelMCStore(void);
	//public: void CPCItemInventoryMgr::NotifyMYMCStoreItemInfo(void);
	public: int CPCItemInventoryMgr::IsMCStoreOpen(void);
	public: void CPCItemInventoryMgr::NotifyMySellableItem(float overcharge);
	//public: void CPCItemInventoryMgr::PurchaseItem(int leftLen, char* buf, float discount);
	//public: void CPCItemInventoryMgr::SellItem(int leftLen, char* buf, float overcharge);
	public: void CPCItemInventoryMgr::OnExchangeItem(int par1);
	public: virtual IVItItem* CPCItemInventoryMgr::AllocInventoryItem(unsigned short ID, short count);
	public: void CPCItemInventoryMgr::FreeInventoryItem(InventoryItem* item);
	//public: void CPCItemInventoryMgr::UpgradeRefiningLevel(unsigned long loc, int Up);
	//public: void CPCItemInventoryMgr::DestroyItemOnRefining(unsigned long);
	public: void CPCItemInventoryMgr::NotifyAckAddItemToBody(unsigned long type, IVItItem* item);
	public: void CPCItemInventoryMgr::InsertEmpeliumItem(unsigned short ITID);
	//public: int CPCItemInventoryMgr::GetEmpeliumItem(void);
	//public: void CPCItemInventoryMgr::CallPet(IVItEquipItem* item);
	//public: int CPCItemInventoryMgr::SendPetEggList(void);
	//public: void CPCItemInventoryMgr::ConvertPetEggToPet(short index);
	//public: int CPCItemInventoryMgr::ConvertPetToPetEgg(int dbkey, int modified);
	public: IVItItem* CPCItemInventoryMgr::SearchPet(int dbkey);
	public: CPC* CPCItemInventoryMgr::GetPC(void);
	//public: int CPCItemInventoryMgr::GetDamagedItemNum(void);
	//public: void CPCItemInventoryMgr::RepairDamagedItem(void);
	public: void CPCItemInventoryMgr::RandomDivision(CItem* item);
	public: int CPCItemInventoryMgr::GetCountItemOfMyGID(unsigned long ITID);
	public: int CPCItemInventoryMgr::RemoveItemOfMyGID(unsigned long ITID, int count);
	public: void CPCItemInventoryMgr::CreateItemOfMyGID(unsigned long ITID, int count, unsigned long sGID);
	//public: IVItEquipItem* CPCItemInventoryMgr::ConvertPet(IVItItem* p);
	//public: int CPCItemInventoryMgr::GetMailItemSize(void);
	public: void CPCItemInventoryMgr::CancelMailItem(int bResetItem, int bResetMoney);
	public: int CPCItemInventoryMgr::GetMailItem(IVItItem& Item, int& ItemCounter, char* ItemBuffer, int& BufferLen, unsigned long& Money);
	//public: int CPCItemInventoryMgr::PutMailBinaryItem(char* ItemBuffer, int ItemLen);
	//public: int CPCItemInventoryMgr::GetAuctionItemSize(void);
	public: void CPCItemInventoryMgr::CancelAuctionItem(void);
	//public: int CPCItemInventoryMgr::GetAuctionItem(IVItItem& IVItItem, int& ItemCounter, char* ItemBuffer, int& BufferLen);
	//public: IVItItem* CPCItemInventoryMgr::BuyCashPointItem(unsigned short ITID);
	//public: int CPCItemInventoryMgr::GetBlacksmithPlusAttackPower(int position);
	//public: bool CPCItemInventoryMgr::GetBlacksmithWeaponProperty(int position, int& weaponProperty);
	public: void CPCItemInventoryMgr::SetItemPartyInMap(int npcAID, int ITID, int count);
	//public: void CPCItemInventoryMgr::DownGradeRefiningLevel(unsigned long loc, int Down);
	//private: int CPCItemInventoryMgr::GetBodyItemSize(void);
	//private: int CPCItemInventoryMgr::GetExchangeItemSize(void);
	//private: void CPCItemInventoryMgr::NotifyAckAddItemToStore(IVItItem* item);
	private: void CPCItemInventoryMgr::NotifySoldedResultOnMCStore(short index, short count);
	//private: IVItEquipItem* CPCItemInventoryMgr::ConvertPetEgg(IVItItem* p);
	//private: bool CPCItemInventoryMgr::IsEnable_UseItem(unsigned short ITID);
	//private: static bool CPCItemInventoryMgr::Check_PetNameModified(int dbkey, EQUIPSLOTINFO* slotInfo);

private:
	static hook_method<int (CPCItemInventoryMgr::*)(unsigned char* out_pBuffer, const int in_MaxBytes)> CPCItemInventoryMgr::_GetBodyItemDBFormat;
	static hook_method<int (CPCItemInventoryMgr::*)(unsigned char* out_pBuffer, const int in_MaxBytes)> CPCItemInventoryMgr::_GetStoreItemDBFormat;
	static hook_method<int (CPCItemInventoryMgr::*)(unsigned char* out_pBuffer, const int in_MaxBytes)> CPCItemInventoryMgr::_GetCartItemDBFormat;
	static hook_method<void (CPCItemInventoryMgr::*)(void)> CPCItemInventoryMgr::_StoreItemReset;
	static hook_method<int (CPCItemInventoryMgr::*)(void)> CPCItemInventoryMgr::_IsCartOn;
	static hook_method<void (CPCItemInventoryMgr::*)(Request* request)> CPCItemInventoryMgr::_OnMediatorRequest;
	static hook_method<void (CPCItemInventoryMgr::*)(Request* request)> CPCItemInventoryMgr::_OnDispatchClientRequest;
	static hook_method<IVItItem* (CPCItemInventoryMgr::*)(IVItItem* item, unsigned long type, unsigned short desPos, int IsClientNotified, int IsFroceInsert)> CPCItemInventoryMgr::_Add;
	static hook_method<void (CPCItemInventoryMgr::*)(IVItItem* item)> CPCItemInventoryMgr::_NotifyPickUpToParty;
	static hook_method<static int (__cdecl *)(CommonItemInfo* item, char* buf, int len)> CPCItemInventoryMgr::_DBValueParser;
	static hook_method<PASERRET::enumError (CPCItemInventoryMgr::*)(Request* in_pRequest, const bool in_bNotify, const bool in_bUseZip, const bool in_bUseItemType)> CPCItemInventoryMgr::_Parse;
	static hook_method<PASERRET::enumError (CPCItemInventoryMgr::*)(Request* in_pRequest, const bool in_bNotify, const bool in_bUseZip, const bool in_bUseItemType)> CPCItemInventoryMgr::_ParseV4;
	static hook_method<int (CPCItemInventoryMgr::*)(Request* request)> CPCItemInventoryMgr::_Save;
	static hook_method<IVItItem* (CPCItemInventoryMgr::*)(const enum enumInventoryType in_InventoryType, const __int64 in_UID)> CPCItemInventoryMgr::_SearchItemByUniqueIdentityNum;
	static hook_method<IVItItem* (CPCItemInventoryMgr::*)(unsigned long type, short index)> CPCItemInventoryMgr::_SearchItem;
	static hook_method<IVItItem* (CPCItemInventoryMgr::*)(unsigned long type, unsigned short ITID)> CPCItemInventoryMgr::_SearchItemByID;
	static hook_method<int (CPCItemInventoryMgr::*)(unsigned long type, short index, short count)> CPCItemInventoryMgr::_DeleteItem;
	static hook_method<void (CPCItemInventoryMgr::*)(const unsigned long in_Type)> CPCItemInventoryMgr::_NotifyItemInfo;
	static hook_method<void (CPCItemInventoryMgr::*)(void)> CPCItemInventoryMgr::_RefreshItemWeight;
	static hook_method<bool (CPCItemInventoryMgr::*)(const int in_Length, const unsigned char* in_pData)> CPCItemInventoryMgr::_ParseDBFmtBodyItemData;
	static hook_method<void (CPCItemInventoryMgr::*)(short index, unsigned long AID)> CPCItemInventoryMgr::_OnUseItem;
	static hook_method<void (CPCItemInventoryMgr::*)(short index, unsigned short wearLocation)> CPCItemInventoryMgr::_OnWearItem;
	static hook_method<void (CPCItemInventoryMgr::*)(unsigned long ITAID)> CPCItemInventoryMgr::_OnPickUpItem;
	static hook_method<void (CPCItemInventoryMgr::*)(short index)> CPCItemInventoryMgr::_OnTakeOffEquip;
	static hook_method<int (CPCItemInventoryMgr::*)(void)> CPCItemInventoryMgr::_GetBodyItemWeight;
	static hook_method<int (CPCItemInventoryMgr::*)(unsigned short id, int& value)> CPCItemInventoryMgr::_GetJustBodyItemCount;
	static hook_method<int (CPCItemInventoryMgr::*)(unsigned short id, int& value)> CPCItemInventoryMgr::_GetJustEquipItemCount;
	static hook_method<void (CPCItemInventoryMgr::*)(int npcAID, int ITID, int count)> CPCItemInventoryMgr::_OnSetBodyItem;
	static hook_method<void (CPCItemInventoryMgr::*)(void)> CPCItemInventoryMgr::_CancelExchangeItem;
	static hook_method<void (CPCItemInventoryMgr::*)(unsigned long loc)> CPCItemInventoryMgr::_TakeOffEquip;
	static hook_method<void (CPCItemInventoryMgr::*)(void)> CPCItemInventoryMgr::_TakeOffAllEquip;
	static hook_method<int (CPCItemInventoryMgr::*)(void)> CPCItemInventoryMgr::_GetBodyItemWeightByPercent;
	static hook_method<int (CPCItemInventoryMgr::*)(unsigned long type)> CPCItemInventoryMgr::_GetPlusPowerOfItem;
	static hook_method<void (CPCItemInventoryMgr::*)(unsigned short id)> CPCItemInventoryMgr::_ReqMakeArrow;
	static hook_method<void (CPCItemInventoryMgr::*)(const int in_Length, const unsigned char* in_pData)> CPCItemInventoryMgr::_ParseDBFmtStoreItemData;
	static hook_method<bool (CPCItemInventoryMgr::*)(const int in_Length, const unsigned char* in_pData)> CPCItemInventoryMgr::_ParseDBFmtCartItemData;
	static hook_method<void (CPCItemInventoryMgr::*)(void)> CPCItemInventoryMgr::_NotifyStoreItemCountInfo;
	static hook_method<void (CPCItemInventoryMgr::*)(void)> CPCItemInventoryMgr::_CloseStore;
	static hook_method<int (CPCItemInventoryMgr::*)(void)> CPCItemInventoryMgr::_IsStoreOpen;
	static hook_method<void (CPCItemInventoryMgr::*)(int len, char* buf)> CPCItemInventoryMgr::_OnReqOpenMCStore;
	static hook_method<void (CPCItemInventoryMgr::*)(unsigned long AID)> CPCItemInventoryMgr::_NotifyItemInfoInMCStore;
	static hook_method<void (CPCItemInventoryMgr::*)(unsigned long targetAID, int contentLength, char* buf)> CPCItemInventoryMgr::_PurchaseItemFromMCStore;
	static hook_method<int (CPCItemInventoryMgr::*)(void)> CPCItemInventoryMgr::_IsMCStoreOpen;
	static hook_method<void (CPCItemInventoryMgr::*)(float overcharge)> CPCItemInventoryMgr::_NotifyMySellableItem;
	static hook_method<void (CPCItemInventoryMgr::*)(int par1)> CPCItemInventoryMgr::_OnExchangeItem;
	static hook_method<IVItItem* (CPCItemInventoryMgr::*)(unsigned short ID, short count)> CPCItemInventoryMgr::_AllocInventoryItem;
	static hook_method<void (CPCItemInventoryMgr::*)(InventoryItem* item)> CPCItemInventoryMgr::_FreeInventoryItem;
	static hook_method<void (CPCItemInventoryMgr::*)(unsigned long type, IVItItem* item)> CPCItemInventoryMgr::_NotifyAckAddItemToBody;
	static hook_method<void (CPCItemInventoryMgr::*)(unsigned short ITID)> CPCItemInventoryMgr::_InsertEmpeliumItem;
	static hook_method<IVItItem* (CPCItemInventoryMgr::*)(int dbkey)> CPCItemInventoryMgr::_SearchPet;
	static hook_method<CPC* (CPCItemInventoryMgr::*)(void)> CPCItemInventoryMgr::_GetPC;
	static hook_method<void (CPCItemInventoryMgr::*)(CItem* item)> CPCItemInventoryMgr::_RandomDivision;
	static hook_method<int (CPCItemInventoryMgr::*)(unsigned long ITID)> CPCItemInventoryMgr::_GetCountItemOfMyGID;
	static hook_method<int (CPCItemInventoryMgr::*)(unsigned long ITID, int count)> CPCItemInventoryMgr::_RemoveItemOfMyGID;
	static hook_method<void (CPCItemInventoryMgr::*)(unsigned long ITID, int count, unsigned long sGID)> CPCItemInventoryMgr::_CreateItemOfMyGID;
	static hook_method<void (CPCItemInventoryMgr::*)(int bResetItem, int bResetMoney)> CPCItemInventoryMgr::_CancelMailItem;
	static hook_method<int (CPCItemInventoryMgr::*)(IVItItem& Item, int& ItemCounter, char* ItemBuffer, int& BufferLen, unsigned long& Money)> CPCItemInventoryMgr::_GetMailItem;
	static hook_method<void (CPCItemInventoryMgr::*)(void)> CPCItemInventoryMgr::_CancelAuctionItem;
	static hook_method<void (CPCItemInventoryMgr::*)(int npcAID, int ITID, int count)> CPCItemInventoryMgr::_SetItemPartyInMap;
	static hook_method<void (CPCItemInventoryMgr::*)(short index, short count)> CPCItemInventoryMgr::_NotifySoldedResultOnMCStore;
};
