#pragma once
#include "PCItemInventory.h"


class CPCCartItemIV : public CPCItemInventory
{
public:
	CPCCartItemIV();
	virtual ~CPCCartItemIV();

public:
	virtual void Init();
	virtual IVItItem* Add(IVItItem* item, int par1, BOOL isIndexChangable);
	virtual BOOL Delete(short index);
	virtual BOOL Delete(short index, short count);
	virtual IVItItem* Remove(short index, short count);
	void SetCartOnFlag(int flag);
	BOOL IsCartOn();
	virtual void Reset();

private:
	/* this+ 0 */ //CPCItemInventory baseclass_0;
	/* this+32 */ BOOL m_isFirstCartOn;
};
