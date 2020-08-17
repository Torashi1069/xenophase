#pragma once
#include "Struct.h"
struct DRAG_INFO;
struct SKILL_DESC;


struct CommonObject
{
	/* this+0 */ mystd::vector<char*> m_deleteList;

	public: CommonObject::CommonObject(void);
	public: CommonObject::~CommonObject(void);
	public: void CommonObject::Clear(void);
	public: bool CommonObject::TokenFileToPCharList(mystd::vector<const char*>& pCharList, const char* fName, bool desc);

private:
	static hook_method<void (CommonObject::*)(void)> CommonObject::_Clear;
	static hook_method<bool (CommonObject::*)(mystd::vector<const char*>& pCharList, const char* fName, bool desc)> CommonObject::_TokenFileToPCharList;
};


struct ITEM_DESC
{
	/* this+ 0 */ const char* identifiedDisplayName;
	/* this+ 4 */ const char* identifiedResourceName;
	/* this+ 8 */ mystd::vector<const char*> identifiedDescriptionName;
	/* this+24 */ const char* unidentifiedDisplayName;
	/* this+28 */ const char* unidentifiedResourceName;
	/* this+32 */ mystd::vector<const char*> unidentifiedDescriptionName;
	/* this+48 */ unsigned long slot;
	/* this+52 */ int slotCount;
	/* this+56 */ mystd::vector<int> parameter;

	public: ITEM_DESC::ITEM_DESC(void) : identifiedDisplayName(NULL), identifiedResourceName(NULL), unidentifiedDisplayName(NULL), unidentifiedResourceName(NULL), slot(0), slotCount(0) { } // line 35
};


struct CARD_DESC
{
	/* this+0 */ const char* illustName;
	/* this+4 */ const char* prefix;
	/* this+8 */ const char* postfix;

	public: CARD_DESC::CARD_DESC(void) : illustName(NULL), prefix(NULL), postfix(NULL) { } // line 50
};


struct ITEM_INFO
{
	/* this+ 0 */ int m_itemType; // enum ITEM_TYPE
	/* this+ 4 */ int m_location;
	/* this+ 8 */ unsigned long m_itemIndex;
	/* this+12 */ int m_wearLocation;
	/* this+16 */ int m_num;
	/* this+20 */ int m_price;
	/* this+24 */ int m_realPrice;
	/* this+28 */ int m_slot[4];
	/* this+44 */ mystd::string m_itemName;
	/* this+60 */ bool m_isIdentified;
	/* this+61 */ bool m_isDamaged;
	/* this+64 */ int m_refiningLevel;
	/* static  */ static mystd::map<int,ITEM_DESC>& s_itemDescMap;
	/* static  */ static mystd::map<int,CARD_DESC>& s_cardDescMap;
	/* static  */ static mystd::map<int,mystd::vector<const char*> >& s_maketargetdesc;
	/* static  */ static CommonObject& s_obj;

	public: ITEM_INFO::ITEM_INFO(void); // line 73
	public: ITEM_INFO::ITEM_INFO(int); // line 74
	public: void ITEM_INFO::SetItemId(int itemId);
	public: int ITEM_INFO::GetItemId(void) const; // line 76
	public: int ITEM_INFO::GetRefining(char* refining) const;
	public: int ITEM_INFO::GetNamed(char* named) const;
	public: int ITEM_INFO::GetPrefix(char* prefix) const;
	public: int ITEM_INFO::GetPostfix(char* postfix) const;
	public: int ITEM_INFO::GetManufacturedItemPrefix(char* text) const;
	public: int ITEM_INFO::GetManufacturedItemProducer(char* text) const;
	public: int ITEM_INFO::GetManufacturedItemPostfix(char* text) const;
	public: int ITEM_INFO::GetIdDisplayName(char* name) const;
	public: int ITEM_INFO::GetUnidDisplayName(char* name) const;
	public: char* ITEM_INFO::GetItemName(char* itemName);
	public: bool ITEM_INFO::IsValid(void); // line 89
	//public: void Reset();
	public: const char* ITEM_INFO::GetResName(void);
	public: const mystd::vector<const char*>& ITEM_INFO::GetDescription(void);
	public: int ITEM_INFO::GetSlotCount(void);
	public: void ITEM_INFO::CopyItemInfo(const DRAG_INFO* dragInfo);
	//public: unsigned char IsIdentified();
	public: static bool __cdecl ITEM_INFO::IsCardItem(const char* itemName);
	public: static bool __cdecl ITEM_INFO::IsCardItem(int itemName);
	public: bool ITEM_INFO::IsCardItem(void) const;
	//public: unsigned char HasCardItem();
	public: bool ITEM_INFO::IsManufacturedItem(void) const;
	public: bool ITEM_INFO::IsRecoveryItem(void) const;
	public: bool ITEM_INFO::IsAttachableItem(void) const;
	public: bool ITEM_INFO::IsPropertyItem(void) const;
	public: bool ITEM_INFO::IsMaterialItem(void) const;
	//public: int GetRefiningName(char *);
	//public: int GetPrefixName(char *);
	//public: int GetManufacturerName(char *);
	//public: int GetDisplayName(char *);
	//public: int GetPostfixName(char *);
	public: ITEM_INFO& ITEM_INFO::operator=(const ITEM_INFO& iteminfo);
	public: ITEM_INFO& ITEM_INFO::operator=(const SHOP_ITEM& shopitem);
	public: static void __cdecl ITEM_INFO::InitItemInfoTables(void);
	public: static const ITEM_DESC& __cdecl ITEM_INFO::GetItemDesc(const char* itemName);
	public: static const ITEM_DESC& __cdecl ITEM_INFO::GetItemDesc(int itemName);
	public: static const CARD_DESC& __cdecl ITEM_INFO::GetCardDesc(const char* itemName);
	public: static const CARD_DESC& __cdecl ITEM_INFO::GetCardDesc(int itemName);
	public: static const mystd::vector<const char*>& __cdecl ITEM_INFO::GetMakeTargetDesc(const char* itemName);
	public: static const mystd::vector<const char*>& __cdecl ITEM_INFO::GetMakeTargetDesc(int itemName);

private:
	static hook_method<void (ITEM_INFO::*)(int itemId)> ITEM_INFO::_SetItemId;
	static hook_method<int (ITEM_INFO::*)(void) const> ITEM_INFO::_GetItemId;
	static hook_method<int (ITEM_INFO::*)(char* refining) const> ITEM_INFO::_GetRefining;
	static hook_method<int (ITEM_INFO::*)(char* named) const> ITEM_INFO::_GetNamed;
	static hook_method<int (ITEM_INFO::*)(char* prefix) const> ITEM_INFO::_GetPrefix;
	static hook_method<int (ITEM_INFO::*)(char* postfix) const> ITEM_INFO::_GetPostfix;
	static hook_method<int (ITEM_INFO::*)(char* text) const> ITEM_INFO::_GetManufacturedItemPrefix;
	static hook_method<int (ITEM_INFO::*)(char* text) const> ITEM_INFO::_GetManufacturedItemProducer;
	static hook_method<int (ITEM_INFO::*)(char* text) const> ITEM_INFO::_GetManufacturedItemPostfix;
	static hook_method<int (ITEM_INFO::*)(char* name) const> ITEM_INFO::_GetIdDisplayName;
	static hook_method<int (ITEM_INFO::*)(char* name) const> ITEM_INFO::_GetUnidDisplayName;
	static hook_method<char* (ITEM_INFO::*)(char* itemName)> ITEM_INFO::_GetItemName;
	static hook_method<bool (ITEM_INFO::*)(void)> ITEM_INFO::_IsValid;
	static hook_method<const char* (ITEM_INFO::*)(void)> ITEM_INFO::_GetResName;
	static hook_method<const mystd::vector<const char*>& (ITEM_INFO::*)(void)> ITEM_INFO::_GetDescription;
	static hook_method<int (ITEM_INFO::*)(void)> ITEM_INFO::_GetSlotCount;
	static hook_method<void (ITEM_INFO::*)(const DRAG_INFO* dragInfo)> ITEM_INFO::_CopyItemInfo;
	static hook_method<static bool (__cdecl *)(const char* itemName)> ITEM_INFO::_IsCardItem;
	static hook_method<static bool (__cdecl *)(int itemName)> ITEM_INFO::_IsCardItem2;
	static hook_method<bool (ITEM_INFO::*)(void) const> ITEM_INFO::_IsCardItem3;
	static hook_method<bool (ITEM_INFO::*)(void) const> ITEM_INFO::_IsManufacturedItem;
	static hook_method<bool (ITEM_INFO::*)(void) const> ITEM_INFO::_IsRecoveryItem;
	static hook_method<bool (ITEM_INFO::*)(void) const> ITEM_INFO::_IsAttachableItem;
	static hook_method<bool (ITEM_INFO::*)(void) const> ITEM_INFO::_IsPropertyItem;
	static hook_method<bool (ITEM_INFO::*)(void) const> ITEM_INFO::_IsMaterialItem;
	static hook_method<ITEM_INFO& (ITEM_INFO::*)(const ITEM_INFO& iteminfo)> ITEM_INFO::_operator_eq2;
	static hook_method<ITEM_INFO& (ITEM_INFO::*)(const SHOP_ITEM& shopitem)> ITEM_INFO::_operator_eq;
	static hook_method<void (__cdecl *)(void)> ITEM_INFO::_InitItemInfoTables;
	static hook_method<static const ITEM_DESC& (__cdecl *)(const char* itemName)> ITEM_INFO::_GetItemDesc;
	static hook_method<static const ITEM_DESC& (__cdecl *)(int itemName)> ITEM_INFO::_GetItemDesc2;
	static hook_method<static const CARD_DESC& (__cdecl *)(const char* itemName)> ITEM_INFO::_GetCardDesc;
	static hook_method<static const CARD_DESC& (__cdecl *)(int itemName)> ITEM_INFO::_GetCardDesc2;
	static hook_method<static const mystd::vector<const char*>& (__cdecl *)(const char* itemName)> ITEM_INFO::_GetMakeTargetDesc;
	static hook_method<static const mystd::vector<const char*>& (__cdecl *)(int itemName)> ITEM_INFO::_GetMakeTargetDesc2;
};


template<typename T> T& __cdecl GetDesc(int itemName, mystd::map<int,T>& table) // line 161
{
	static T nullDesc;
	mystd::map<int,T>::iterator it = table.find(itemName);
	return ( it != table.end() ) ? it->second : nullDesc;
}
