#pragma once
#include "std/map"


class CImportantItem
{
	/* this+0 */ private: mystd::map<DWORD,DWORD> m_mapImportantItem;

	public: void CImportantItem::LoadImportantItem(void);
	public: int CImportantItem::IsImportantItem(DWORD dwItemID);

private:
	static hook_method<void (CImportantItem::*)(void)> CImportantItem::_LoadImportantItem;
	static hook_method<int (CImportantItem::*)(DWORD dwItemID)> CImportantItem::_IsImportantItem;
};
