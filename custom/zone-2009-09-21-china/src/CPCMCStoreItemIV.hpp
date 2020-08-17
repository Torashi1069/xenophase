#pragma once
#include "std/map"
#include "struct.hpp"
#include "PCItemInventory.h"


class CPCMCStoreItemIV : public CPCItemInventory
{
public:
	struct vtable_t // const CPCMCStoreItemIV::`vftable'
	{
		void* (CPCMCStoreItemIV::* vector_deleting_destructor)(unsigned int);
		void (CInventory::* Delete)(Request *);
		void (CInventory::* Load)(Request *);
		void (CInventory::* Save)(Request *);
		int (CPCItemInventory::* OnRequest)(Request *);
		void (CPCMCStoreItemIV::* Init)(void);
		IVItItem* (CPCMCStoreItemIV::* Add)(IVItItem *, int, int);
		int (CPCMCStoreItemIV::* Delete2)(short, short);
		int (CPCMCStoreItemIV::* Delete3)(short);
		IVItItem* (CPCMCStoreItemIV::* Remove)(short, short);
		int (CPCItemInventory::* GetSize)(void);
		void (CPCMCStoreItemIV::* Reset)(void);
	};

	/* this+0x0  */ //CPCItemInventory
	/* this+0x20 */ mystd::map<short,MCSTORE_ITEMEXTRA_INFO> m_extraInfo;
	/* this+0x2C */ char m_MCStoreName[0x80];
	/* this+0xAC */ int m_isMCStoreOpen;

	//public: void CPCMCStoreItemIV::CPCMCStoreItemIV();
	//public: void CPCMCStoreItemIV::~CPCMCStoreItemIV();
	//public: void CPCMCStoreItemIV::Init();
	//public: IVItItem* CPCMCStoreItemIV::Add(IVItItem*, int, int);
	//public: int CPCMCStoreItemIV::Delete(short, short);
	//public: int CPCMCStoreItemIV::Delete(short);
	public: IVItItem* CPCMCStoreItemIV::Remove(short index, short count);
	public: int CPCMCStoreItemIV::GetPrice(short index);
	//public: char * CPCMCStoreItemIV::GetMCStoreName();
	//public: int CPCMCStoreItemIV::IsMCStoreOpen();
	//public: void CPCMCStoreItemIV::SetMCStoreName(char *);
	//public: void CPCMCStoreItemIV::Reset();
	//protected: void CPCMCStoreItemIV::DeleteExtraInfo(short);

private:
	static hook_method<IVItItem* (CPCMCStoreItemIV::*)(short index, short count)> CPCMCStoreItemIV::_Remove;
	static hook_method<int (CPCMCStoreItemIV::*)(short index)> CPCMCStoreItemIV::_GetPrice;
};
