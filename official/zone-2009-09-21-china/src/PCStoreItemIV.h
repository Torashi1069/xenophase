#pragma once
#include "PCItemInventory.h"


class CPCStoreItemIV : public CPCItemInventory
{
public:
	CPCStoreItemIV();
	virtual ~CPCStoreItemIV();
	virtual void CPCStoreItemIV::Init();
	virtual int CPCStoreItemIV::Delete(short index, short count);
	virtual IVItItem* CPCStoreItemIV::Remove(short index, short count);
	BOOL IsOpen();
	void Reset();
	void SetStoreOpenFlag(BOOL isStoreOpen);

private:
	/* this+ 0 */ //CPCItemInventory baseclass_0;
	/* this+32 */ BOOL m_isStoreOpen;

private:
	static hook_func<void (CPCStoreItemIV::*)()> CPCStoreItemIV::_Init;
	static hook_func<int (CPCStoreItemIV::*)(short index, short count)> CPCStoreItemIV::_Delete;
	static hook_func<IVItItem* (CPCStoreItemIV::*)(short index, short count)> CPCStoreItemIV::_Remove;
	static hook_func<BOOL (CPCStoreItemIV::*)()> CPCStoreItemIV::_IsOpen;
	static hook_func<void (CPCStoreItemIV::*)()> CPCStoreItemIV::_Reset;
	static hook_func<void (CPCStoreItemIV::*)(BOOL isStoreOpen)> CPCStoreItemIV::_SetStoreOpenFlag;
};
