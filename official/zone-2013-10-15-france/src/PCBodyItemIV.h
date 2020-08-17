#pragma once
#include "PCItemInventory.h"


class CPCBodyItemIV : public CPCItemInventory
{
public:
	CPCBodyItemIV();
	virtual ~CPCBodyItemIV();

public:
	virtual IVItItem* Add(IVItItem* item, int par1, BOOL isIndexChangable);
	BOOL IdentifyItem(short index);
	void DeadPenalty(int percent); //TODO
	void SendNotifyQuest(); //TODO
	std::vector<short> GetIsMergeItemList();
	virtual void Init();
	virtual void Reset();
	virtual BOOL Delete(short index);
	virtual BOOL Delete(short index, short count);
	virtual int GetSize();

protected:
	/* this+ 0 */ //CPCItemInventory baseclass_0;
	/* this+32 */ int m_questItemCount;
};
