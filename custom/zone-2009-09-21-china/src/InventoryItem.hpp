#pragma once
#include "enum.hpp"
#include "struct.hpp"
#include "CITP.hpp"
#include "CITPMgr.hpp"


#pragma pack(push,1)
struct InventoryItem
{
	struct vtable_t // const InventoryItem::`vftable'
	{
		unsigned int (InventoryItem::* GetType)(void);
	};

	/* this+0x0 */ //const InventoryItem::`vftable'
	/* this+0x4 */ unsigned short m_ID;

	InventoryItem(void)
	{
	}

	void Init(void)
	{
		m_ID = 0;
	}

	virtual unsigned long GetType(void)
	{
		return INVENTORYITEMTYPE_UNNONE;
	}

	void SetID(unsigned short ID)
	{
		m_ID = ID;
	}

	unsigned short GetID(void)
	{
		return m_ID;
	}

	/*
	public void Init();
	public unsigned long GetType();
	public void SetID(unsigned short);
	public unsigned short GetID();
	public void InventoryItem(const InventoryItem &);
	public void InventoryItem();
	*/
};
#pragma pack(pop)


#pragma pack(push,1)
struct IVItItemData;
struct IVItItem : public InventoryItem
{
	struct vtable_t // const IVItItem::`vftable'
	{
		unsigned long (IVItItem::* GetType)(void);
		void (IVItItem::* Init)(void);
		void (IVItItem::* CopyFromParData)(IVItItemData *);
		void (IVItItem::* CopyToParData)(IVItItemData *);
		void (IVItItem::* CopyFromOtherItem)(IVItItem *);
		int  (IVItItem::* IBData_Get)(char *, bool);
		int  (IVItItem::* IBData_Set)(char *);
		bool (IVItItem::* IsMapPropertyBlocked)(int);
		void (IVItItem::* SetMapPropertyBlocked)(int, bool);
	};

	/* this+0x0  */ //InventoryItem
	/* this+0x6  */ EQUIPSLOTINFO m_slotInfo;
	/* this+0xE  */ bool m_isIdentified;
	/* this+0xF  */ short m_count;
	/* this+0x11 */ short m_index;
	/* this+0x13 */ __int64 m_unique_identity_number;
	/* this+0x1B */ long m_hire_expire_date;
	/* this+0x1F */ bool m_isBind;

	public: IVItItem::IVItItem(void)
	{
		this->IVItItem::Init();
	}

	public: virtual void IVItItem::Init(void)
	{
		m_ID = 0;
		m_slotInfo.info[0] = 0;
		m_slotInfo.info[1] = 0;
		m_slotInfo.info[2] = 0;
		m_slotInfo.info[3] = 0;
		m_isIdentified = false;
		m_count = 1;
		m_index = -1;
		m_unique_identity_number = 0;
		m_hire_expire_date = 0;
		m_isBind = false;
	}

	public: virtual unsigned long IVItItem::GetType(void)
	{
		return INVENTORYITEMTYPE_ITEM;
	}

	//public: bool IVItItem::IsIdentified();
	//public: void IVItItem::SetIdentifyflag(bool);
	//public: short IVItItem::GetCount();
	//public: void IVItItem::SetCount(short);
	//public: void IVItItem::AddCount(short);
	//public: void IVItItem::SetIndex(unsigned short);
	//public: short IVItItem::GetIndex();

	public: void IVItItem::CopyFromParData(IVItItemData* data)
	{
		m_ID = ((IVItItem*)data)->m_ID;
		m_isIdentified = ((IVItItem*)data)->m_isIdentified;
		m_count = ((IVItItem*)data)->m_count;
		m_slotInfo = ((IVItItem*)data)->m_slotInfo;
	}

	public: void IVItItem::CopyToParData(IVItItemData* data)
	{
		((IVItItem*)data)->m_ID = m_ID;
		((IVItItem*)data)->m_isIdentified = m_isIdentified;
		((IVItItem*)data)->m_count = m_count;
		((IVItItem*)data)->m_slotInfo = m_slotInfo;
	}

	public: void IVItItem::CopyFromOtherItem(IVItItem* item)
	{
		m_ID = item->m_ID;
		m_isIdentified = item->m_isIdentified;
		m_count = item->m_count;
		m_slotInfo = item->m_slotInfo;
		this->IVItItem::SetUniqueIdentityNumV2(item->m_unique_identity_number);
		this->IVItItem::SetHireExpireDate(item->m_hire_expire_date);
	}

	//public: bool IVItItem::IsBind();
	//public: void IVItItem::SetBind(bool);

	public: int IVItItem::IsMovable() // line 124-134 (IvItItem.cpp)
	{
		if( m_isBind )
			return 239;

		CITP* itp = g_itpMgr->CITPMgr::GetITP(m_ID);
		if( itp == NULL )
			return 255;

		return itp->IsMovable();
	}

	//public: void IVItItem::SetSlotInfo(EQUIPSLOTINFO *);
	//public: EQUIPSLOTINFO* IVItItem::GetSlotInfo();
	//public: unsigned long IVItItem::GetMakerGID();

	public: void IVItItem::SetUniqueIdentityNumV2(const __int64 in_unique_identity_number)
	{
		m_unique_identity_number = in_unique_identity_number;
	}

	//__int64 IVItItem::GetUniqueIdentityNumV2();

	public: void IVItItem::SetHireExpireDate(const long in_hire_expire_date)
	{
		m_hire_expire_date = in_hire_expire_date;
	}

	//public: long GetHireExpireDate();

	public: int IVItItem::IBData_Get(char* in_pBuffer, const bool in_bIncType)
	{
		return 0;
	}

	public: int IVItItem::IBData_Set(char* in_pIBDBuffer)
	{
		return 0;
	}

	public: virtual bool IVItItem::IsMapPropertyBlocked(const int in_loc)
	{
		return false;
	}

	public: virtual void IVItItem::SetMapPropertyBlocked(const int in_loc, bool flag)
	{
	}

	//protected: int IVItItem::IBData_Save_AdditionalElement(char *, const IVItItemDataV2::tagFlag);
	//protected: int IVItItem::IBData_Save_Type(char *, const bool);
	//protected: int IVItItem::IBData_Load_AdditionalElement(const IVItItemDataV2::tagFlag, char *);
};
C_ASSERT(sizeof(IVItItem) == 0x20);
#pragma pack(pop)



struct IVItNormalItem : public IVItItem
{
	struct vtable_t // const IVItNormalItem::`vftable'
	{
		void* GetType;               // unsigned long IVItNormalItem::GetType(void)
		void* Init;                  // void IVItNormalItem::Init(void)
		void* CopyFromParData;       // void IVItNormalItem::CopyFromParData(IVItItemData *)
		void* CopyToParData;         // void IVItNormalItem::CopyToParData(IVItItemData *)
		void* CopyFromOtherItem;     // void IVItNormalItem::CopyFromOtherItem(IVItItem *)
		void* IBData_Get;            // int IVItNormalItem::IBData_Get(char *,bool)
		void* IBData_Set;            // int IVItNormalItem::IBData_Set(char *)
		void* IsMapPropertyBlocked;  // bool IVItItem::IsMapPropertyBlocked(int)
		void* SetMapPropertyBlocked; // void IVItItem::SetMapPropertyBlocked(int,bool)
	};

	/* this+0x0  */ //IVItItem

	virtual unsigned long GetType(void)
	{
		return INVENTORYITEMTYPE_NORMALITEM;
	}

	/*
	public void IVItNormalItem();
	public void IVItNormalItem::Init();
	public unsigned long IVItNormalItem::GetType();
	public void IVItNormalItem::CopyFromParData(IVItItemData *);
	public void IVItNormalItem::CopyToParData(IVItItemData *);
	public void IVItNormalItem::CopyFromOtherItem(IVItItem *);
	public int IVItNormalItem::IBData_Get(char *, const bool);
	public int IVItNormalItem::IBData_Set(char *);
	*/
};
C_ASSERT(sizeof(IVItNormalItem) == 0x20);


struct IVItNormalArrowItem : public IVItNormalItem
{
	struct vtable_t
	{
		//TODO
	};

	/* this+0x0  */ //IVItNormalItem
	/* this+0x20 */ unsigned short m_wearState;

	virtual unsigned long GetType(void)
	{
		return INVENTORYITEMTYPE_NORMALARROWITEM;
	}

	/*
	public void IVItNormalArrowItem::IVItNormalArrowItem();
	public void IVItNormalArrowItem::Init();
	public unsigned long IVItNormalArrowItem::GetType();
	public unsigned short GetWearState();
	public void SetWearState(unsigned short);
	public void IVItNormalArrowItem::CopyFromParData(IVItItemData *);
	public void IVItNormalArrowItem::CopyToParData(IVItItemData *);
	public void IVItNormalArrowItem::CopyFromOtherItem(IVItItem *);
	public int IVItNormalArrowItem::IBData_Get(char *, const bool);
	public int IVItNormalArrowItem::IBData_Set(char *);
	*/
};
C_ASSERT(sizeof(IVItNormalArrowItem) == 0x22);


#pragma pack(push,1)
struct IVItEquipItem : public IVItItem
{
	struct vtable_t
	{
		//TODO
	};

	enum
	{
		BLOCK_EQUIPITEM_SLOT1 = 0x0,
		BLOCK_EQUIPITEM_SLOT2 = 0x1,
		BLOCK_EQUIPITEM_SLOT3 = 0x2,
		BLOCK_EQUIPITEM_SLOT4 = 0x3,
		BLOCK_EQUIPITEM = 0x4,
	};

	/* this+0x0  */ //IVItItem
	/* this+0x20 */ unsigned short m_wearState;
	/* this+0x22 */ bool m_isDamaged;
	/* this+0x23 */ unsigned char m_refiningLevel;
	/* this+0x24 */ bool m_isMapPropertyBlocked[0x5];

	public: virtual unsigned long GetType(void)
	{
		return INVENTORYITEMTYPE_EQUIPITEM;
	}

	public: unsigned char IVItEquipItem::GetRefiningLevel(void)
	{
		return this->m_refiningLevel <= 10 ? this->m_refiningLevel : 0;
	}

	/*
	public void IVItEquipItem::IVItEquipItem();
	public void IVItEquipItem::Init();
	public unsigned long IVItEquipItem::GetType();
	public void SetIdentifyNumber(const __int64);
	public __int64 GetIdentifyNumber();
	public void SetDamageFlag(bool);
	public bool IsDamaged();
	public void SetRefiningLevel(unsigned char);
	public unsigned char IVItEquipItem::GetRefiningLevel();
	public unsigned short GetWearState();
	public void SetWearState(unsigned short);
	public void IVItEquipItem::AddCardToSlot(unsigned short);
	public int IVItEquipItem::IsSlotAvailable();
	public void IVItEquipItem::CopyFromParData(IVItItemData *);
	public void IVItEquipItem::CopyToParData(IVItItemData *);
	public void IVItEquipItem::CopyFromOtherItem(IVItItem *);
	public bool IVItEquipItem::IsMapPropertyBlocked(const int);
	public void IVItEquipItem::SetMapPropertyBlocked(const int, bool);
	public int IVItEquipItem::IBData_Get(char *, const bool);
	public int IVItEquipItem::IBData_Set(char *);
	*/
};
C_ASSERT(sizeof(IVItEquipItem) == 0x29);
#pragma pack(pop)


struct IVItMoneyItem : public IVItItem
{
	struct vtable_t
	{
		//TODO
	};

	/* this+0x0  */ //IVItItem
	/* this+0x20 */ int m_money;

	virtual unsigned long GetType(void)
	{
		return INVENTORYITEMTYPE_MONEYITEM;
	}

	/*
	public void IVItMoneyItem::IVItMoneyItem();
	public void IVItMoneyItem::Init();
	public unsigned long IVItMoneyItem::GetType();
	public void SetMoney(int);
	public int GetMoney();
	*/
};
C_ASSERT(sizeof(IVItMoneyItem) == 0x24);


struct IVItQuestItem : public IVItItem
{
	struct vtable_t
	{
		//TODO
	};

	/* this+0x0  */ //IVItItem

	virtual unsigned long GetType(void)
	{
		return INVENTORYITEMTYPE_QUESTITEM;
	}

	/*
	public void IVItQuestItem();
	public void IVItQuestItem::Init();
	public unsigned long IVItQuestItem::GetType();
	public void IVItQuestItem::CopyFromParData(IVItItemData *);
	public void IVItQuestItem::CopyToParData(IVItItemData *);
	public void IVItQuestItem::CopyFromOtherItem(IVItItem *);
	public int IVItQuestItem::IBData_Get(char *, const bool);
	public int IVItQuestItem::IBData_Set(char *);
	*/
};
C_ASSERT(sizeof(IVItQuestItem) == 0x20);


struct IVItCashPointItem : public IVItItem
{
	struct vtable_t
	{
		//TODO
	};

	/* this+0x0  */ //IVItItem

	virtual unsigned long GetType(void)
	{
		return INVENTORYITEMTYPE_CASHPOINTITEM;
	}

	/*
	public void IVItCashPointItem();
	public void IVItCashPointItem::Init();
	public unsigned long IVItCashPointItem::GetType();
	public void IVItCashPointItem::CopyFromParData(IVItItemData *);
	public void IVItCashPointItem::CopyToParData(IVItItemData *);
	public void IVItCashPointItem::CopyFromOtherItem(IVItItem *);
	public int IVItCashPointItem::IBData_Get(char *, const bool);
	public int IVItCashPointItem::IBData_Set(char *);
	*/
};
C_ASSERT(sizeof(IVItCashPointItem) == 0x20);
