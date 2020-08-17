#pragma once
#include "struct.hpp"
#include "PCItemInventory.h"
struct IVItItem;


class CPCEquipedItemIV : public CPCItemInventory
{
public:
	struct vtable_t // const CPCEquipedItemIV::`vftable'
	{
		void* (CPCEquipedItemIV::* scalar_deleting_destructor)(unsigned int);
		void (CInventory::* Delete)(Request *);
		void (CInventory::* Load)(Request *);
		void (CInventory::* Save)(Request *);
		int (CPCItemInventory::* OnRequest)(Request *);
		void (CPCEquipedItemIV::* Init)(void);
		IVItItem* (CPCEquipedItemIV::* Add)(IVItItem *, int, int);
		int (CPCEquipedItemIV::* Delete2)(short, short);
		int (CPCItemInventory::* Delete3)(short);
		IVItItem* (CPCEquipedItemIV::* Remove)(short, short);
		int (CPCItemInventory::* GetSize)(void);
		void (CPCItemInventory::* Reset)(void);
	};

	/* this+0x0  */ //CPCItemInventory
	/* this+0x20 */ ITEM_PLUSSTATUS_VALUE m_statusValueOfItem;
	/* this+0x2C */ ITEM_PLUSPOWEROFITEM m_plusPowerOfItem;
	/* this+0x40 */ IVItItem* m_head;
	/* this+0x44 */ IVItItem* m_body;
	/* this+0x48 */ IVItItem* m_larm;
	/* this+0x4C */ IVItItem* m_rarm;
	/* this+0x50 */ IVItItem* m_robe;
	/* this+0x54 */ IVItItem* m_shoes;
	/* this+0x58 */ IVItItem* m_accessory1;
	/* this+0x5C */ IVItItem* m_accessory2;
	/* this+0x60 */ IVItItem* m_head2;
	/* this+0x64 */ IVItItem* m_head3;
	/* this+0x68 */ IVItItem* m_arrow;
	/* this+0x6C */ unsigned short m_wearState;

	public: CPCEquipedItemIV::CPCEquipedItemIV(void);
	public: virtual CPCEquipedItemIV::~CPCEquipedItemIV(void);
	public: virtual void CPCEquipedItemIV::Init(void);
	public: virtual IVItItem* CPCEquipedItemIV::Add(IVItItem* item, int par1, int isIndexChangable);
	public: virtual int CPCEquipedItemIV::Delete(short index, short count);
	public: virtual IVItItem* CPCEquipedItemIV::Remove(short index, short count);
	//public: short CPCEquipedItemIV::GetStatusValueOfEquipedItem(unsigned long);
	public: short CPCEquipedItemIV::GetPlusPowerOfItem(unsigned long type);
	//public: void Equip(unsigned short, IVItItem *);
	public: int CPCEquipedItemIV::IsEquipable(unsigned short& loc, IVItItem* item);
	//public: CITP* CPCEquipedItemIV::GetITPEquipedWeapon();
	public: IVItEquipItem* CPCEquipedItemIV::GetEquipedItem(unsigned long loc);
	//public: CITP* CPCEquipedItemIV::GetITPEquipedArmor();
	public: IVItItem* CPCEquipedItemIV::GetEquipedArrow();
	//public: void CPCEquipedItemIV::TakeOffAllEquip();
	//public: void CPCEquipedItemIV::TakeOffEquipItem(unsigned long);
	//public: void CPCEquipedItemIV::DeadPenalty(int);
	//public: void CPCEquipedItemIV::DropItem(unsigned short);
	//public: int CPCEquipedItemIV::GetRefiningAttackValue(IVItItem *, CITP*);
	//protected: void CPCEquipedItemIV::PlusStatus(CITP*);
	//protected: void CPCEquipedItemIV::MinusStatus(CITP*);
	//protected: void OnEquip(IVItItem *);
	//protected: int CPCEquipedItemIV::IsAvailablePos(unsigned short &);
	//protected: void CPCEquipedItemIV::SetPos(unsigned short, IVItItem *);
	//protected: void CPCEquipedItemIV::ProcessItemPropertyOnTakeOff(IVItItem *);
	//protected: void CPCEquipedItemIV::ProcessItemProperty(IVItItem *);
	//protected: short CPCEquipedItemIV::GetJob();
	//protected: int CPCEquipedItemIV::GetLevel();
	//protected: void CPCEquipedItemIV::SetItemPointerNull(IVItItem *);
	//private: void CPCEquipedItemIV::SetPosAvailable(unsigned short &);

private:
	static hook_method<void (CPCEquipedItemIV::*)(void)> CPCEquipedItemIV::_Init;
	static hook_method<IVItItem* (CPCEquipedItemIV::*)(IVItItem* item, int par1, int isIndexChangable)> CPCEquipedItemIV::_Add;
	static hook_method<int (CPCEquipedItemIV::*)(short index, short count)> CPCEquipedItemIV::_Delete;
	static hook_method<IVItItem* (CPCEquipedItemIV::*)(short index, short count)> CPCEquipedItemIV::_Remove;
	static hook_method<short (CPCEquipedItemIV::*)(unsigned long type)> CPCEquipedItemIV::_GetPlusPowerOfItem;
	static hook_method<int (CPCEquipedItemIV::*)(unsigned short& loc, IVItItem* item)> CPCEquipedItemIV::_IsEquipable;
};
