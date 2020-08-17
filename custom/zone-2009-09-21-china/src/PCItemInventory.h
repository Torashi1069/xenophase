#pragma once
#include "Inventory.h"
#include "InventoryItem.hpp"
#include "struct.hpp" // struct Request
#include "std/vector"
class CPCItemInventoryMgr;


class CPCItemInventory : public CInventory
{
public:
	struct vtable_t // const CPCItemInventory::`vftable'
	{
		void* (CPCItemInventory::* scalar_deleting_destructor)(unsigned int flags);
		void (CInventory::* Delete)(Request* request);
		void (CInventory::* Load)(Request* request);
		void (CInventory::* Save)(Request* request);
		int (CPCItemInventory::* OnRequest)(Request* request);
		void (CPCItemInventory::* Init)(void);
		IVItItem* (CPCItemInventory::* Add)(IVItItem* item, int par1, int isIndexChangable);
		int (CPCItemInventory::* Delete2)(short index, short count);
		int (CPCItemInventory::* Delete3)(short index);
		IVItItem* (CPCItemInventory::* Remove)(short index, short count);
		int (CPCItemInventory::* GetSize)(void);
		void (CPCItemInventory::* Reset)(void);
	};

	/* this+ 0 */ public: //CInventory baseclass_0;
	/* this+ 4 */ protected: CPCItemInventoryMgr* m_owner;
	/* this+ 8 */ protected: short m_indexIncrement;
	/* this+12 */ protected: int m_weight;
	/* this+16 */ protected: mystd::vector<IVItItem*> m_itemData;

	public: CPCItemInventory::CPCItemInventory(void);
	public: virtual CPCItemInventory::~CPCItemInventory(void);
	public: virtual void CPCItemInventory::Init(void);
	public: virtual IVItItem* CPCItemInventory::Add(IVItItem* item, int par1, int isIndexChangable);
	public: virtual int CPCItemInventory::Delete(short index);
	public: virtual int CPCItemInventory::Delete(short index, short count);
	public: virtual IVItItem* CPCItemInventory::Remove(short index, short count);
	//public: void CPCItemInventory::GetAllItemWithDBFormat(char *, int &, const bool);
	//public: void CPCItemInventory::GetAllItemWithDBFormatV4(char *, int &, const bool);
	//public: void CPCItemInventory::GetAllItemWithDBFormatV3under(char *, int &, int);
	public: int CPCItemInventory::GetAllNormalItemInfoWithBinaryFormat3(char* out_pBuffer, const int in_MaxBytes);
	public: int CPCItemInventory::GetAllEquipedItemInfoWithBinaryFormat3(char* out_pBuffer, const int in_MaxBytes, const bool in_bPet);
	public: virtual int CPCItemInventory::OnRequest(Request* request);
	//public: void CPCItemInventory::PlusWeight(int);
	//public: void CPCItemInventory::MinusWeight(int);
	//public: int CPCItemInventory::GetWeight();
	public: virtual int CPCItemInventory::GetSize(void);
	//public: int CPCItemInventory::IsAlreadyExist(IVItItem *);
	//public: void CPCItemInventory::SetOwner(CPCItemInventoryMgr *);
	//public: IVItItem* CPCItemInventory::SearchItemByUniqueIdentityNum(const __int64);
	public: IVItItem* CPCItemInventory::SearchItemByIndex(short index);
	public: IVItItem* CPCItemInventory::SearchItemByID(unsigned short ITID, bool in_IsIdentified);
	//public: IVItItem* CPCItemInventory::SearchItem(unsigned short, unsigned long, const __int64);
	//public: IVItItem* CPCItemInventory::SearchItemByID_GID(unsigned short, unsigned long);
	public: mystd::vector<IVItItem*>::iterator CPCItemInventory::GetDataBeginIterator();
	public: mystd::vector<IVItItem*>::iterator CPCItemInventory::GetDataEndIterator();
	//public: IVItItem* CPCItemInventory::GetFirstItem();
	//public: IVItItem* CPCItemInventory::PeekFirstItem();
	public: virtual void CPCItemInventory::Reset(void);

private:
	static hook_method<void (CPCItemInventory::*)(void)> CPCItemInventory::_Init;
	static hook_method<IVItItem* (CPCItemInventory::*)(IVItItem* item, int par1, int isIndexChangable)> CPCItemInventory::_Add;
	static hook_method<int (CPCItemInventory::*)(short index, short count)> CPCItemInventory::_Delete2;
	static hook_method<int (CPCItemInventory::*)(short index)> CPCItemInventory::_Delete3;
	static hook_method<IVItItem* (CPCItemInventory::*)(short index, short count)> CPCItemInventory::_Remove;
	static hook_method<int (CPCItemInventory::*)(char* out_pBuffer, const int in_MaxBytes)> CPCItemInventory::_GetAllNormalItemInfoWithBinaryFormat3;
	static hook_method<int (CPCItemInventory::*)(char* out_pBuffer, const int in_MaxBytes, const bool in_bPet)> CPCItemInventory::_GetAllEquipedItemInfoWithBinaryFormat3;
	static hook_method<int (CPCItemInventory::*)(Request* request)> CPCItemInventory::_OnRequest;
	static hook_method<int (CPCItemInventory::*)(void)> CPCItemInventory::_GetSize;
	static hook_method<IVItItem* (CPCItemInventory::*)(short index)> CPCItemInventory::_SearchItemByIndex;
	static hook_method<IVItItem* (CPCItemInventory::*)(unsigned short ITID, bool in_IsIdentified)> CPCItemInventory::_SearchItemByID;
	static hook_method<mystd::vector<IVItItem*>::iterator (CPCItemInventory::*)(void)> CPCItemInventory::_GetDataBeginIterator;
	static hook_method<mystd::vector<IVItItem*>::iterator (CPCItemInventory::*)(void)> CPCItemInventory::_GetDataEndIterator;
	static hook_method<void (CPCItemInventory::*)(void)> CPCItemInventory::_Reset;
};
