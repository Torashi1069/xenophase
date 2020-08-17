#pragma once
#include "Player/Inventory/CIVItItem.h"


struct IVItNormalItemData : public IVItItemData
{
	/* this+0 */ //IVItItemData baseclass_0;
	/* this+0 */ unsigned short ITID;
	/* this+2 */ bool IsIdentified;
	/* this+3 */ short count;
	/* this+5 */ EQUIPSLOTINFO slot;
};


struct IVItNormalItemDataV2 : public IVItItemDataV2
{
	/* this+0 */ //IVItItemDataV2 baseclass_0;
	/* this+3 */ short count;
	/* this+5 */ EQUIPSLOTINFO slot;
};


class IVItNormalItem : public IVItItem
{
public:
	void InitReal();
	virtual void InitVirtual();
	virtual unsigned long GetType();
	virtual void CopyFromParData(IVItItemData* data);
	virtual void CopyToParData(IVItItemData* data);
	virtual void CopyFromOtherItem(IVItItem* item);
	virtual int IBData_Set(char* in_pIBDBuffer);
	virtual int IBData_Get(char* in_pBuffer, const bool in_bIncType);

public:
	IVItNormalItem();
	virtual ~IVItNormalItem();
};
