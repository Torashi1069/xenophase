#pragma once


class CItemList
{
public:
	enum
	{
		MAX_ITEM = 1000,
	};

	/* this+0x0 */ int m_itemNum;
	/* this+0x4 */ int m_itemArray[MAX_ITEM];

	//public: void CItemList::CItemList(void);
	//public: void CItemList::~CItemList(void);
	public: void CItemList::LoadFromFile(const char* fileName, int verDate);
	public: int CItemList::GetNth(int n);
private:
	static hook_method<void (CItemList::*)(const char* fileName, int verDate)> CItemList::_LoadFromFile;
	static hook_method<int (CItemList::*)(int n)> CItemList::_GetNth;
};
