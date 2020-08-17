#pragma once
#include "std/map"


class CCheckUseItemList
{
public:
	/* this+0x0 */ private: mystd::map<unsigned short,char> m_createItemList;
	/* static   */ private: static hook_ptr<CCheckUseItemList *> m_self;

	private: CCheckUseItemList::CCheckUseItemList(void);
	private: CCheckUseItemList::~CCheckUseItemList(void);
	public: static bool __cdecl CCheckUseItemList::CreateInstance(void);
	public: static void __cdecl CCheckUseItemList::DestroyInstance(void);
	public: void CCheckUseItemList::AddItemID_Create(unsigned short ITEMID);
	public: bool CCheckUseItemList::IsLimited_Create(unsigned short ITEMID);

private:
	static hook_method<static bool (__cdecl *)(void)> CCheckUseItemList::_CreateInstance;
	static hook_method<static void (__cdecl *)(void)> CCheckUseItemList::_DestroyInstance;
	static hook_method<void (CCheckUseItemList::*)(unsigned short ITEMID)> CCheckUseItemList::_AddItemID_Create;
	static hook_method<bool (CCheckUseItemList::*)(unsigned short ITEMID)> CCheckUseItemList::_IsLimited_Create;
};
