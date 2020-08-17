#pragma once


enum enumInventoryItemType
{
	INVENTORYITEMTYPE_ITEM            = 0,
	INVENTORYITEMTYPE_NORMALITEM      = 1,
	INVENTORYITEMTYPE_NORMALARROWITEM = 2,
	INVENTORYITEMTYPE_EQUIPITEM       = 3,
	INVENTORYITEMTYPE_MONEYITEM       = 4,
	INVENTORYITEMTYPE_SKILL           = 5,
	INVENTORYITEMTYPE_UNNONE          = 6,
	INVENTORYITEMTYPE_QUESTITEM       = 7,
	INVENTORYITEMTYPE_CASHPOINTITEM   = 8,
};


class InventoryItem
{
public:
	void InitReal() { m_ID = 0; }
	virtual unsigned long GetType() { return INVENTORYITEMTYPE_UNNONE; }
	void SetID(unsigned short ID) { m_ID = ID; }
	unsigned short GetID() { return m_ID; }

public:
	InventoryItem() { }
	virtual ~InventoryItem() { }

protected:
	/* this+0 */ //const InventoryItem::`vftable';
	/* this+4 */ unsigned short m_ID;
};
