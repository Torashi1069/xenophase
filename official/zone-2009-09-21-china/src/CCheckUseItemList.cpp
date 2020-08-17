#include "CCheckUseItemList.hpp"


hook_ptr<CCheckUseItemList*> CCheckUseItemList::m_self(SERVER, "CCheckUseItemList::m_self"); // = ?


CCheckUseItemList::CCheckUseItemList(void)
{
}


CCheckUseItemList::~CCheckUseItemList(void) // line 11
{
}


hook_method<static bool (__cdecl *)(void)> CCheckUseItemList::_CreateInstance(SERVER, "CCheckUseItemList::CreateInstance");
bool __cdecl CCheckUseItemList::CreateInstance(void) // line 16
{
	return (CCheckUseItemList::_CreateInstance)();

	//TODO
}


hook_method<static void (__cdecl *)(void)> CCheckUseItemList::_DestroyInstance(SERVER, "CCheckUseItemList::DestroyInstance");
void __cdecl CCheckUseItemList::DestroyInstance(void) // line 26
{
	return (CCheckUseItemList::_DestroyInstance)();

	//TODO
}


hook_method<void (CCheckUseItemList::*)(unsigned short ITEMID)> CCheckUseItemList::_AddItemID_Create(SERVER, "CCheckUseItemList::AddItemID_Create");
void CCheckUseItemList::AddItemID_Create(unsigned short ITEMID)
{
	return (this->*_AddItemID_Create)(ITEMID);

	//TODO
}


hook_method<bool (CCheckUseItemList::*)(unsigned short ITEMID)> CCheckUseItemList::_IsLimited_Create(SERVER, "CCheckUseItemList::IsLimited_Create");
bool CCheckUseItemList::IsLimited_Create(unsigned short ITEMID)
{
	return (this->*_IsLimited_Create)(ITEMID);

	//TODO
}
