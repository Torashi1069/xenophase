#include "CITPMgr.hpp"


CITPMgr::CITPMgr(void)
{
}


CITPMgr::~CITPMgr(void)
{
	m_itp.clear();
}


hook_method<bool (CITPMgr::*)(const char* fName)> CITPMgr::_Save(SERVER, "CITPMgr::Save");
bool CITPMgr::Save(const char* fName)
{
	return (this->*_Save)(fName);

	//TODO
}


hook_method<void (CITPMgr::*)(const char* Script)> CITPMgr::_Init(SERVER, "CITPMgr::Init");
void CITPMgr::Init(const char* Script)
{
	return (this->*_Init)(Script);

	//TODO
}


hook_method<void (CITPMgr::*)(void)> CITPMgr::_LoadITP(SERVER, "CITPMgr::LoadITP");
void CITPMgr::LoadITP(void)
{
	return (this->*_LoadITP)();

	//TODO
}


//hook_method<mystd::map<mystd::string,unsigned short>& (CITPMgr::*)(void)> CITPMgr::_GetNameMap(SERVER, "CITPMgr::GetNameMap");
mystd::map<mystd::string,unsigned short>& CITPMgr::GetNameMap(void)
{
//	return (this->*_GetNameMap)();

	return m_itemName;
}


//hook_method<mystd::map<unsigned short,mystd::vector<unsigned short> >& (CITPMgr::*)(void)> CITPMgr::_GetCombiItemList(SERVER, "CITPMgr::GetCombiItemList");
mystd::map<unsigned short,mystd::vector<unsigned short> >& CITPMgr::GetCombiItemList(void)
{
//	return (this->*_GetCombiItemList)();

	 return m_combiItem;
}


/* hook_method<void (CITPMgr::*)(void)> CITPMgr::_InsertITP(SERVER, "CITPMgr::InsertITP");
void CITPMgr::InsertITP(void)
{
	return (this->*_InsertITP)();

	//TODO
} */


hook_method<CITP* (CITPMgr::*)(unsigned short ITID)> CITPMgr::_GetITP(SERVER, "CITPMgr::GetITP");
CITP* CITPMgr::GetITP(unsigned short ITID)
{
	return (this->*_GetITP)(ITID);

	//TODO
}


hook_method<enum enumInventoryItemType (CITPMgr::*)(const unsigned short in_ITID)> CITPMgr::_GetInventoryItemType(SERVER, "CITPMgr::GetInventoryItemType");
enum enumInventoryItemType CITPMgr::GetInventoryItemType(const unsigned short in_ITID)
{
	return (this->*_GetInventoryItemType)(in_ITID);

	//TODO
}


hook_method<unsigned long (CITPMgr::*)(const char* effectName)> CITPMgr::_GetEffectID(SERVER, "CITPMgr::GetEffectID");
unsigned long CITPMgr::GetEffectID(const char* effectName)
{
	return (this->*_GetEffectID)(effectName);

	//TODO
}


/// Finds an item id by item name.
hook_method<unsigned short (CITPMgr::*)(const char* itemName)> CITPMgr::_GetITID(SERVER, "CITPMgr::GetITID");
unsigned short CITPMgr::GetITID(const char* itemName)
{
	return (this->*_GetITID)(itemName);

	mystd::map<mystd::string,unsigned short>::iterator it = m_itemName.find(itemName);
	return ( it != m_itemName.end() ) ? it->second : 0;
}


/// Finds up to 10 ids of items whose names contain the search string.
/// Remaining fields are left untouched (so zero the array out first).
hook_method<int (CITPMgr::*)(const char* itemName, unsigned long* pItemIDList)> CITPMgr::_FindITID(SERVER, "CITPMgr::FindITID");
int CITPMgr::FindITID(const char* itemName, unsigned long* pItemIDList)
{
	return (this->*_FindITID)(itemName, pItemIDList);

	int Counter = 0;

	mystd::map<mystd::string,unsigned short>::iterator it;
	for( it = m_itemName.begin(); it != m_itemName.end() && Counter < 10; ++it )
	{
		mystd::string ItemName = it->first;

		if( ItemName.find(itemName, 0, strlen(itemName)) != -1 )
			pItemIDList[Counter++] = it->second;
	}

	return Counter;
}


hook_method<short (CITPMgr::*)(unsigned short ITID)> CITPMgr::_GetItemWeight(SERVER, "CITPMgr::GetItemWeight");
short CITPMgr::GetItemWeight(unsigned short ITID)
{
	return (this->*_GetItemWeight)(ITID);

	//TODO
}


hook_method<int (CITPMgr::*)(unsigned short ITID)> CITPMgr::_IsApparel(SERVER, "CITPMgr::IsApparel");
int CITPMgr::IsApparel(unsigned short ITID)
{
	return (this->*_IsApparel)(ITID);

	//TODO
}


hook_method<int (CITPMgr::*)(unsigned short ITID)> CITPMgr::_IsCashPointItem(SERVER, "CITPMgr::IsCashPointItem");
int CITPMgr::IsCashPointItem(unsigned short ITID)
{
	return (this->*_IsCashPointItem)(ITID);

	//TODO
}


/* hook_method<char* (CITPMgr::*)(unsigned short ITID)> CITPMgr::_GetItemName(SERVER, "CITPMgr::GetItemName");
char* CITPMgr::GetItemName(unsigned short ITID)
{
	return (this->*_GetItemName)(ITID);

	//TODO
} */


hook_method<void (CITPMgr::*)(void)> CITPMgr::_DBClose(SERVER, "CITPMgr::DBClose");
void CITPMgr::DBClose(void)
{
	return (this->*_DBClose)();

	//TODO
}


hook_method<bool (CITPMgr::*)(unsigned short ITID)> CITPMgr::_IsScrollItem(SERVER, "CITPMgr::IsScrollItem");
bool CITPMgr::IsScrollItem(unsigned short ITID)
{
	return (this->*_IsScrollItem)(ITID);

	//TODO
}


hook_method<void (CITPMgr::*)(void)> CITPMgr::_GetQuest(SERVER, "CITPMgr::GetQuest");
void CITPMgr::GetQuest(void)
{
	return (this->*_GetQuest)();

	//TODO
}


hook_method<void (CITPMgr::*)(unsigned long type)> CITPMgr::_GetArmor(SERVER, "CITPMgr::GetArmor");
void CITPMgr::GetArmor(unsigned long type)
{
	return (this->*_GetArmor)(type);

	//TODO
}


/* hook_method<void (CITPMgr::*)(void)> CITPMgr::_GetCannonball(SERVER, "CITPMgr::GetCannonball");
void CITPMgr::GetCannonball(void)
{
	return (this->*_GetCannonball)();

	//TODO
} */


hook_method<void (CITPMgr::*)(void)> CITPMgr::_GetArrow(SERVER, "CITPMgr::GetArrow");
void CITPMgr::GetArrow(void)
{
	return (this->*_GetArrow)();

	//TODO
}


hook_method<void (CITPMgr::*)(void)> CITPMgr::_GetAmmo(SERVER, "CITPMgr::GetAmmo");
void CITPMgr::GetAmmo(void)
{
	return (this->*_GetAmmo)();

	//TODO
}


hook_method<void (CITPMgr::*)(void)> CITPMgr::_GetGun(SERVER, "CITPMgr::GetGun");
void CITPMgr::GetGun(void)
{
	return (this->*_GetGun)();

	//TODO
}


hook_method<void (CITPMgr::*)(void)> CITPMgr::_GetWeapon(SERVER, "CITPMgr::GetWeapon");
void CITPMgr::GetWeapon(void)
{
	return (this->*_GetWeapon)();

	//TODO
}


hook_method<void (CITPMgr::*)(void)> CITPMgr::_GetBothhand(SERVER, "CITPMgr::GetBothhand");
void CITPMgr::GetBothhand(void)
{
	return (this->*_GetBothhand)();

	//TODO
}


hook_method<void (CITPMgr::*)(void)> CITPMgr::_GetBow(SERVER, "CITPMgr::GetBow");
void CITPMgr::GetBow(void)
{
	return (this->*_GetBow)();

	//TODO
}


hook_method<void (CITPMgr::*)(void)> CITPMgr::_GetEvent(SERVER, "CITPMgr::GetEvent");
void CITPMgr::GetEvent(void)
{
	return (this->*_GetEvent)();

	//TODO
}


hook_method<void (CITPMgr::*)(void)> CITPMgr::_GetSpecial(SERVER, "CITPMgr::GetSpecial");
void CITPMgr::GetSpecial(void)
{
	return (this->*_GetSpecial)();

	//TODO
}


hook_method<void (CITPMgr::*)(void)> CITPMgr::_GetHeal(SERVER, "CITPMgr::GetHeal");
void CITPMgr::GetHeal(void)
{
	return (this->*_GetHeal)();

	//TODO
}


hook_method<void (CITPMgr::*)(void)> CITPMgr::_GetCard(SERVER, "CITPMgr::GetCard");
void CITPMgr::GetCard(void)
{
	return (this->*_GetCard)();

	//TODO
}


hook_method<void (CITPMgr::*)(void)> CITPMgr::_GetCashPointItem(SERVER, "CITPMgr::GetCashPointItem");
void CITPMgr::GetCashPointItem(void)
{
	return (this->*_GetCashPointItem)();

	//TODO
}


hook_method<void (CITPMgr::*)(void)> CITPMgr::_GetThrowWeapon(SERVER, "CITPMgr::GetThrowWeapon");
void CITPMgr::GetThrowWeapon(void)
{
	return (this->*_GetThrowWeapon)();

	//TODO
}


hook_method<void (CITPMgr::*)(void)> CITPMgr::_LoadItemMoveInfo(SERVER, "CITPMgr::LoadItemMoveInfo");
void CITPMgr::LoadItemMoveInfo(void)
{
	return (this->*_LoadItemMoveInfo)();

	//TODO
}


hook_method<bool (CITPMgr::*)(void)> CITPMgr::_LoadCashItemList(SERVER, "CITPMgr::LoadCashItemList");
bool CITPMgr::LoadCashItemList(void)
{
	return (this->*_LoadCashItemList)();

	//TODO
}


hook_method<int (CITPMgr::*)(const char* fileName)> CITPMgr::_LoadCombiItemList(SERVER, "CITPMgr::LoadCombiItemList");
int CITPMgr::LoadCombiItemList(const char* fileName)
{
	return (this->*_LoadCombiItemList)(fileName);

	//TODO
}


hook_method<void (CITPMgr::*)(void)> CITPMgr::_LoadScrollItemList(SERVER, "CITPMgr::LoadScrollItemList");
void CITPMgr::LoadScrollItemList(void)
{
	return (this->*_LoadScrollItemList)();

	//TODO
}


hook_method<void (CITPMgr::*)(void)> CITPMgr::_LoadItemBindOnEquip(SERVER, "CITPMgr::LoadItemBindOnEquip");
void CITPMgr::LoadItemBindOnEquip(void)
{
	return (this->*_LoadItemBindOnEquip)();

	//TODO
}


hook_method<int (CITPMgr::*)(CITP* itp)> CITPMgr::_AddITP(SERVER, "CITPMgr::AddITP");
int CITPMgr::AddITP(CITP* itp)
{
	return (this->*_AddITP)(itp);

	//TODO
}
