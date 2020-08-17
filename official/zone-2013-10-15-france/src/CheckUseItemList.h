#pragma once


class CCheckUseItemList
{
private:
	CCheckUseItemList();
	~CCheckUseItemList();

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CCheckUseItemList* GetObj(); ///@custom

public:
	void AddItemID_Create(unsigned short ITEMID);
	bool IsLimited_Create(unsigned short ITEMID);

private:
	/* this+0 */ std::map<unsigned short,char> m_createItemList;
	/* static */ static CCheckUseItemList*& m_self; //TODO
};
