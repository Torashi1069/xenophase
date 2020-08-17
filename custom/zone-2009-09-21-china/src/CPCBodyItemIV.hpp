#pragma once
#include "PCItemInventory.h"


class CPCBodyItemIV : public CPCItemInventory
{
public:
	struct vtable_t // const CPCBodyItemIV::`vftable'
	{
		void* (CPCBodyItemIV::* scalar_deleting_destructor)(unsigned int);
		void (CInventory::* Delete)(Request *);
		void (CInventory::* Load)(Request *);
		void (CInventory::* Save)(Request *);
		int (CPCItemInventory::* OnRequest)(Request *);
		void (CPCBodyItemIV::* Init)(void);
		IVItItem* (CPCBodyItemIV::* Add)(IVItItem *, int, int);
		int (CPCBodyItemIV::* Delete2)(short, short);
		int (CPCBodyItemIV::* Delete3)(short);
		IVItItem* (CPCItemInventory::* Remove)(short, short);
		int (CPCBodyItemIV::* GetSize)(void);
		void (CPCBodyItemIV::* Reset)(void);
	};

	/* this+0x0  */ //CPCItemInventory
	/* this+0x20 */ int m_questItemCount;

	public: CPCBodyItemIV::CPCBodyItemIV(void);
	public: virtual CPCBodyItemIV::~CPCBodyItemIV(void);
	public: virtual IVItItem* CPCBodyItemIV::Add(IVItItem* item, int par1, int isIndexChangable);
	//public: int CPCBodyItemIV::IdentifyItem(short);
	//public: void CPCBodyItemIV::DeadPenalty(int);
	public: virtual void CPCBodyItemIV::Init(void);
	public: virtual void CPCBodyItemIV::Reset(void);
	public: virtual int CPCBodyItemIV::Delete(short index);
	public: virtual int CPCBodyItemIV::Delete(short index, short count);
	public: virtual int CPCBodyItemIV::GetSize(void);

private:
	static hook_method<IVItItem* (CPCBodyItemIV::*)(IVItItem* item, int par1, int isIndexChangable)> CPCBodyItemIV::_Add;
	static hook_method<void (CPCBodyItemIV::*)(void)> CPCBodyItemIV::_Init;
	static hook_method<void (CPCBodyItemIV::*)(void)> CPCBodyItemIV::_Reset;
	static hook_method<int (CPCBodyItemIV::*)(short index, short count)> CPCBodyItemIV::_Delete2;
	static hook_method<int (CPCBodyItemIV::*)(short index)> CPCBodyItemIV::_Delete3;
	static hook_method<int (CPCBodyItemIV::*)(void)> CPCBodyItemIV::_GetSize;
};
