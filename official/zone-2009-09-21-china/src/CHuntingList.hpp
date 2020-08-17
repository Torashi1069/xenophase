#pragma once
#include "std/map"


class CHuntingList
{
public:
	struct vtable_t // const CHuntingList::`vftable'
	{
		 void* (CHuntingList::* vector_deleting_destructor)(unsigned int);
	};

	/* this+0x0 */ //const CHuntingList::`vftable'
	/* this+0x4 */ mystd::map<int,int> m_mob2Count;

	enum
	{
		MAX_HUNTINGLIST_SIZE = 10,
	};

	public: CHuntingList::CHuntingList(void);
	public: virtual CHuntingList::~CHuntingList(void);
	public: bool CHuntingList::IsHuntingListFull(void);
	public: int CHuntingList::FindHuntingList(int mob);
	public: int CHuntingList::AddHuntingList(int mob);
	public: bool CHuntingList::DeleteHuntingList(int mob);
	public: bool CHuntingList::SetHuntingList(int mob, int count);
	public: void CHuntingList::ClearHuntingList(void);
	public: int CHuntingList::ReadBinary(unsigned char* buf, int len);
	public: int CHuntingList::WriteBinary(unsigned char* buf, int& len);
	public: bool CHuntingList::PlusOneCount(int mob);
	public: void CHuntingList::DisplayHuntingList(mystd::string& str);
	public: void CHuntingList::DisplayHuntingList2(mystd::string& str);
	public: int CHuntingList::UseHuntingList(void);
	public: int CHuntingList::CheckHuntingList(int mob);
private:
	static hook_method<bool (CHuntingList::*)(void)> CHuntingList::_IsHuntingListFull;
	static hook_method<int (CHuntingList::*)(int mob)> CHuntingList::_FindHuntingList;
	static hook_method<int (CHuntingList::*)(int mob)> CHuntingList::_AddHuntingList;
	static hook_method<bool (CHuntingList::*)(int mob)> CHuntingList::_DeleteHuntingList;
	static hook_method<bool (CHuntingList::*)(int mob, int count)> CHuntingList::_SetHuntingList;
	static hook_method<void (CHuntingList::*)(void)> CHuntingList::_ClearHuntingList;
	static hook_method<int (CHuntingList::*)(unsigned char* buf, int len)> CHuntingList::_ReadBinary;
	static hook_method<int (CHuntingList::*)(unsigned char* buf, int& len)> CHuntingList::_WriteBinary;
	static hook_method<bool (CHuntingList::*)(int mob)> CHuntingList::_PlusOneCount;
	static hook_method<void (CHuntingList::*)(mystd::string& str)> CHuntingList::_DisplayHuntingList;
	static hook_method<void (CHuntingList::*)(mystd::string& str)> CHuntingList::_DisplayHuntingList2;
	static hook_method<int (CHuntingList::*)(void)> CHuntingList::_UseHuntingList;
	static hook_method<int (CHuntingList::*)(int mob)> CHuntingList::_CheckHuntingList;
};
