#pragma once
#include "PCItemInventory.h"


class CPCStoreItemIV : public CPCItemInventory
{
public:
	CPCStoreItemIV();
	virtual ~CPCStoreItemIV();

public:
	virtual void Init();
	virtual BOOL Delete(short index, short count);
	virtual IVItItem* Remove(short index, short count);
	BOOL IsOpen();
	virtual void Reset();
	void SetStoreOpenFlag(BOOL flag);

private:
	/* this+ 0 */ //CPCItemInventory baseclass_0;
	/* this+32 */ BOOL m_isStoreOpen;
};
