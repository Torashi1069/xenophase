#pragma once
#include "Character.h"
#include "Struct.h"
class CMapRes;


enum enumPICKABLETYPE
{
	PICKABLETYPE_KILLUSER  = 0,
	PICKABLETYPE_PARTYUSER = 1,
};


struct ITEM_INFO
{
	/* this+ 0 */ unsigned long MoveReqLastTime;
	/* this+ 4 */ unsigned long state;
	/* this+ 8 */ unsigned short ITID;
	/* this+10 */ unsigned short type;
	/* this+12 */ unsigned short count;
	/* this+14 */ bool IsIdentified;
	/* this+16 */ __int64 unique_identity_numberV2;
	/* this+24 */ long hire_expire_date;
	/* this+28 */ bool IsDamaged;
	/* this+29 */ unsigned char RefiningLevel;
	/* this+30 */ EQUIPSLOTINFO slot;
	/* this+40 */ int xPos;
	/* this+44 */ int yPos;
	/* this+48 */ unsigned char subX;
	/* this+49 */ unsigned char subY;
	/* this+52 */ CMapRes* mapRes;
	/* this+56 */ char name[24];
	/* this+80 */ char DropMonsterName[24];

	ITEM_INFO()
	{
		this->unique_identity_numberV2 = 0;
		this->hire_expire_date = 0;
		this->DropMonsterName[0] = '\0';
	}
};


struct PICKUPABLE_PCLIST
{
	/* this+0 */ unsigned long AID;
	/* this+4 */ unsigned short limitTime;
};


class CItem : public CCharacter
{
public:
//	CItem();
//	virtual ~CItem();

public:
	const char* GetName();
//	unsigned long GetAccountID();
//	void Init(class CITP *, struct ITEM_INFO *);
//	void UpdateItem(class std::vector<CCharacter *,std::allocator<CCharacter *> > *);
//	void Reset();
	int OnProcess();
	void CheckStateChange();
//	int IsMyArea(class CCharacter *, int);
//	void NotifyUpdateInfo(class CPC *);
	void OnDisappear();
//	int OnMsg(class CCharacter *, class CCharacter *, unsigned long, int, int, int, class MSGpar::CVar);
//	int GetParameterValue(unsigned short, int &);
//	int UpdateParameterValue(unsigned short, int);
//	void InsertCommand(struct COMMAND_QUEUE *);
//	void CheckCommandQueue();
//	void DisableCommand(unsigned long);
//	int IsTarget(class CCharacter *, unsigned long);
//	void SetAccountID(unsigned long);
//	unsigned short GetITID();
//	unsigned short GetCount();

public:
	/* this+   0 */ //CCharacter baseclass_0;
	/* this+ 888 */ ITEM_INFO m_itemInfo;

public:
//	void SetPickableType(unsigned long);
//	unsigned long GetPickableType();
//	void SetPickableParty(unsigned long);
//	unsigned long GetPickablePartyID();
//	void AddPickupablePC(unsigned long, unsigned long);
//	int IsPickUpable(unsigned long);
//	void SetUniqueIdentifyNumber(const __int64);
//	__int64 GetUniqueIdentityNumber();
//	long GetHireExpireDate();
	void SetPickableTime(unsigned long time);
//	unsigned long GetMakerGID();

private:
//	void InitThePCCacheInfo(int);

private:
	/* this+ 992 */ unsigned long m_ITAID;
	/* this+ 996 */ unsigned long m_pickableType; // enumPICKABLETYPE
	/* this+1000 */ unsigned long m_pickablePARTYID;
	/* this+1004 */ std::vector<PICKUPABLE_PCLIST> m_pickupablePCList;
	/* this+1020 */ unsigned long m_pickableTime;
};
C_ASSERT( sizeof CItem == 1024 );
