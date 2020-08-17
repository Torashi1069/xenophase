#pragma once
#include "Player/Inventory/CIVItItem.h"


struct IVItEquipItemData : public IVItItemData
{
	/* this+ 0 */ //IVItItemData baseclass_0;
	/* this+ 0 */ unsigned short ITID;
	/* this+ 2 */ bool IsIdentified;
	/* this+ 3 */ int IdentifyNumber;
	/* this+ 7 */ unsigned short WearState;
	/* this+ 9 */ bool IsDamaged;
	/* this+10 */ unsigned char RefiningLevel;
	/* this+11 */ EQUIPSLOTINFO slot;
};


struct IVItEquipItemDataV2 : public IVItItemDataV2
{
	/* this+0 */ //IVItItemDataV2 baseclass_0;
	/* this+3 */ unsigned short WearState;
	/* this+5 */ bool IsDamaged;
	/* this+6 */ unsigned char RefiningLevel;
	/* this+7 */ EQUIPSLOTINFO slot;
};


class IVItEquipItem : public IVItItem
{
public:
	enum
	{
		BLOCK_EQUIPITEM_SLOT1 = 0,
		BLOCK_EQUIPITEM_SLOT2 = 1,
		BLOCK_EQUIPITEM_SLOT3 = 2,
		BLOCK_EQUIPITEM_SLOT4 = 3,
		BLOCK_EQUIPITEM       = 4,
	};

public:
	void InitReal();
	virtual void InitVirtual();

	virtual unsigned long GetType();

	void SetIdentifyNumber(const __int64 in_unique_identity_number);
	__int64 GetIdentifyNumber() const;

	void SetDamageFlag(bool flag);
	bool IsDamaged() const;

	void SetRefiningLevel(unsigned char level);
	unsigned char GetRefiningLevel() const;

	unsigned short GetWearState() const;
	void SetWearState(unsigned short wearState);

	void AddCardToSlot(unsigned short ITID);
	BOOL IsSlotAvailable();

	virtual void CopyFromParData(IVItItemData* data);
	virtual void CopyToParData(IVItItemData* data);
	virtual void CopyFromOtherItem(IVItItem* item);

	virtual bool IsMapPropertyBlocked(const int in_loc);
	virtual void SetMapPropertyBlocked(const int in_loc, bool flag);

	virtual int IBData_Set(char* in_pIBDBuffer);
	virtual int IBData_Get(char* in_pBuffer, const bool in_bIncType);

public:
	IVItEquipItem();
	virtual ~IVItEquipItem();

protected:
	/* this+ 0 */ //IVItItem baseclass_0;
	/* this+40 */ unsigned short m_wearState;
	/* this+42 */ bool m_isDamaged;
	/* this+43 */ unsigned char m_refiningLevel;
	/* this+44 */ bool m_isMapPropertyBlocked[5];
};
