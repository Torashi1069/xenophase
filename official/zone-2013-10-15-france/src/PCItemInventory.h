#pragma once
#include "Player/Inventory/CIVItItem.h"
#include "Inventory.h"
class CPCItemInventoryMgr;


class CPCItemInventory : public CInventory
{
public:
	CPCItemInventory();
	virtual ~CPCItemInventory();

public:
	virtual void Init();
	virtual IVItItem* Add(IVItItem* item, int par1, BOOL isIndexChangable);
	virtual BOOL Delete(short index);
	virtual BOOL Delete(short index, short count);
	virtual IVItItem* Remove(short index, short count);
	void DeleteAll();
	void GetAllItemWithDBFormat(char* in_pBuffer, int& out_size, const bool in_bSetItemType);
	void GetAllItemWithDBFormatV4(char* in_pBuffer, int& out_size, const bool in_bSetItemType);
	void GetAllItemWithDBFormatV3under(char* , const int , int& , int ); //TODO
	void GetAllNormalItemInfoWithBinaryFormat3(std::vector<unsigned char>& io_vecBuffer);
	void GetAllEquipedItemInfoWithBinaryFormat3(std::vector<unsigned char>& io_vecBuffer, const bool in_bPet);
	virtual int OnRequest(Request* request);
	void PlusWeight(int weight);
	void MinusWeight(int weight);
	int GetWeight();
	int GetSize();
	BOOL IsAlreadyExist(IVItItem* item);
	void SetOwner(CPCItemInventoryMgr* owner);
	IVItItem* SearchItemByUniqueIdentityNum(const __int64 in_UID);
	IVItItem* SearchItemByIndex(short index);
	IVItItem* SearchItemByID(unsigned short ITID, bool in_IsIdentified);
	IVItItem* SearchItem(unsigned short ITID, unsigned long GID, const __int64 in_UID);
	IVItItem* SearchItemByID_GID(unsigned short ITID, unsigned long GID);
	std::vector<IVItItem*>::iterator GetDataBeginIterator();
	std::vector<IVItItem*>::iterator GetDataEndIterator();
	IVItItem* GetFirstItem();
	IVItItem* PeekFirstItem();
	void SendNotifyQuest();
	virtual void Reset();

protected:
	/* this+ 0 */ //CInventory baseclass_0;
	/* this+ 4 */ CPCItemInventoryMgr* m_owner;
	/* this+ 8 */ short m_indexIncrement;
	/* this+12 */ int m_weight;
	/* this+16 */ std::vector<IVItItem*> m_itemData;
};
