#pragma once
#include "std/map"
class CPC;


class CPCItem
{
public:
	/* this+ 0 */ public: //const CPCItem::`vftable';
	/* this+ 4 */ private: CPC* m_pc;
	/* this+ 8 */ private: mystd::map<unsigned short,unsigned short> m_equipedSPItem;
	/* this+20 */ private: mystd::map<unsigned short,int> m_isCombination;

	public: CPCItem::CPCItem(void);
	public: virtual CPCItem::~CPCItem(void);
	//public: void CPCItem::Init(void);
	//public: void CPCItem::SetMyOwner(CPC *);
	public: int CPCItem::ParseItem(const char* buf, short len);
	public: int CPCItem::ParseStoredItem(const char* buf, short len);
	public: int CPCItem::ParseCartItem(const char* buf, short len);
	public: void CPCItem::CheckStateSpecialItem(void);
	public: void CPCItem::OnEquipedSpecialITM(unsigned long itmID);
	public: void CPCItem::OnTakeOffSpecialITM(unsigned long itmID);
	//public: void RefreshEquipItem(void);
	//public: int GetCombinationItemCount(void);
	//private: int CPCItem::IsEquipedSPItem(unsigned long);
	//private: void CPCItem::CHK_CompleteCombination(void);
	//private: void CPCItem::CHK_ReleaseCombination(void);

private:
	static hook_method<int (CPCItem::*)(const char* buf, short len)> CPCItem::_ParseItem;
	static hook_method<int (CPCItem::*)(const char* buf, short len)> CPCItem::_ParseStoredItem;
	static hook_method<int (CPCItem::*)(const char* buf, short len)> CPCItem::_ParseCartItem;
	static hook_method<void (CPCItem::*)(void)> CPCItem::_CheckStateSpecialItem;
	static hook_method<void (CPCItem::*)(unsigned long itmID)> CPCItem::_OnEquipedSpecialITM;
	static hook_method<void (CPCItem::*)(unsigned long itmID)> CPCItem::_OnTakeOffSpecialITM;
};
