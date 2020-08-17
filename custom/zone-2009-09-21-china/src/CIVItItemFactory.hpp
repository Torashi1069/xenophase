#pragma once
#include "CInventoryItemFactory.hpp"
#include "NetLib/MemoryMgr.h"
#include "InventoryItem.hpp"


class CIVItItemFactory : public CInventoryItemFactory
{
public:
	struct vtable_t // const CIVItItemFactory::`vftable'
	{
		void* vector_deleting_destructor; // void* CIVItItemFactory::`vector deleting destructor'(uint)
		IVItItem* (CIVItItemFactory::* AllocInventoryItem)(unsigned short, short); // IVItItem* CIVItItemFactory::AllocInventoryItem(ushort,short)
	};

	/* this+0x0  */ //CInventoryItemFactory
	/* this+0x4  */ CMemoryMgr<IVItNormalItem> m_NIMPool;
	/* this+0x34 */ CMemoryMgr<IVItNormalArrowItem> m_NAIMPool;
	/* this+0x64 */ CMemoryMgr<IVItEquipItem> m_EIMPool;
	/* this+0x94 */ CMemoryMgr<IVItQuestItem> m_QIMPool;
	/* this+0xC4 */ CMemoryMgr<IVItCashPointItem> m_CPIPool;

	//public: void CIVItItemFactory::CIVItItemFactory(void);
	//public: void CIVItItemFactory::~CIVItItemFactory(void);
	public: void CIVItItemFactory::Init(void);
	public: void CIVItItemFactory::Reset(void);
	public: IVItItem* CIVItItemFactory::AllocInventoryItem(unsigned short ID, short count);
	public: void CIVItItemFactory::FreeInventoryItem(InventoryItem* item);

private:
	static hook_method<void (CIVItItemFactory::*)(InventoryItem* item)> CIVItItemFactory::_FreeInventoryItem;
	static hook_method<void (CIVItItemFactory::*)(void)> CIVItItemFactory::_Init;
	static hook_method<void (CIVItItemFactory::*)(void)> CIVItItemFactory::_Reset;
	static hook_method<IVItItem* (CIVItItemFactory::*)(unsigned short ID, short count)> CIVItItemFactory::_AllocInventoryItem;
};
