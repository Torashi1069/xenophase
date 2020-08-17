#pragma once
#include "Player/Inventory/CInventoryItem.h"
#include "Struct.h" // EQUIPSLOTINFO


struct IVItItemData
{
public:
	unsigned long GetType(); //TODO
};


struct IVItItemDataV2
{
	struct tagFlag
	{
		/* this(bf)+0:0 len(1) */ unsigned char IsIdentified : 1;
		/* this(bf)+0:1 len(1) */ unsigned char IsBind : 1;
		/* this(bf)+0:2 len(4) */ unsigned char unused : 4;
		/* this(bf)+0:6 len(1) */ unsigned char exist_unique_identity_number : 1;
		/* this(bf)+0:7 len(1) */ unsigned char exist_hire_expire_date : 1;

		void clear()
		{
			this->IsIdentified = false;
			this->IsBind = false;
			this->exist_unique_identity_number = false;
			this->exist_hire_expire_date = false;
			this->unused = 0;
		}
	};

	/* this+0 */ unsigned short ITID;
	/* this+2 */ tagFlag Flag;

	IVItItemDataV2()
	{
		this->ITID = 0;
		this->Flag.clear();
	}
};


class IVItItem : public InventoryItem
{
public:
	IVItItem();
//	virtual ~IVItItem();

public:
	void InitReal();
	virtual void InitVirtual();
	virtual unsigned long GetType();
	bool IsIdentified();
	void SetIdentifyflag(bool flag);
	short GetCount();
	void SetCount(short count);
	void AddCount(short count);
	void SetIndex(unsigned short index);
	short GetIndex();
	virtual void CopyFromParData(IVItItemData* data);
	virtual void CopyToParData(IVItItemData* data);
	virtual void CopyFromOtherItem(IVItItem* item);
	bool IsBind();
	void SetBind(bool flag);
	int IsMovable();

	void SetSlotInfo(EQUIPSLOTINFO* par);
	EQUIPSLOTINFO* GetSlotInfo();

	unsigned long GetMakerGID();

public:
	/* this+ 0 */ //InventoryItem baseclass_0;
	/* this+ 8 */ EQUIPSLOTINFO m_slotInfo;

public:
	void SetUniqueIdentityNumV2(const __int64 in_unique_identity_number);
	__int64 GetUniqueIdentityNumV2();
	void SetHireExpireDate(const time_t in_hire_expire_date);
	time_t GetHireExpireDate();
	virtual int IBData_Set(char* in_pIBDBuffer);
	virtual bool IsMapPropertyBlocked(const int in_loc);
	virtual void SetMapPropertyBlocked(const int in_loc, bool flag);
	virtual int IBData_Get(char* in_pBuffer, const bool in_bIncType);

protected:
	int IBData_Save_AdditionalElement(char* in_pBuffer, const IVItItemDataV2::tagFlag in_Flag);
	int IBData_Save_Type(char* in_pBuffer, const bool in_bType);
	int IBData_Load_AdditionalElement(const IVItItemDataV2::tagFlag in_Flag, char* in_pBuffer);

protected:
	/* this+16 */ bool m_isIdentified;
	/* this+18 */ short m_count;
	/* this+20 */ short m_index;
	/* this+24 */ __int64 m_unique_identity_number;
	/* this+32 */ time_t m_hire_expire_date;
	/* this+36 */ bool m_isBind;
};
