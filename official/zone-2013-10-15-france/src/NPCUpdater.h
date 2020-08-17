#pragma once
class CCharacter;
class CNPC;
class CPC;
struct SORTED_PCLIST;


struct ATTACK_PC
{
	/* this+ 0 */ unsigned long AID;
	/* this+ 4 */ int damage;
	/* this+ 8 */ int attdamage;
	/* this+12 */ unsigned long GRID;
	/* this+16 */ unsigned long GID;
};


class CNPCUpdater
{
public:
	CNPCUpdater();
	virtual ~CNPCUpdater();

public:
//	void SetMyOwner(class CNPC *);
	BOOL SetAccountID(int AccountID);
//	void SetAccountName(const char *);
	void SetValidate(BOOL isActive);
	BOOL IsMyArea(CCharacter* other, int Range);
	BOOL IsMyArea(CCharacter* other, int xRange, int yRange);
//	int IsSomeOne(int, int, int);
//	void Pause(unsigned long);
	BOOL AddSectionMgr();
//	void RemoveSectionMgr();
//	CNPC* GetNeighborFriendNpc(int, unsigned long);
//	CPC* GetNeighborPc(int);
//	CPC* GetTouchedPC(const int, const int);
//	CPC* GetNeighborPcExceptG(int);
//	CPC* GetNeighborLowerLevelPc(int, int);
//	CCharacter* GetNeighborEnemy(int);
//	CCharacter* GetMyOwnerEnemy(int);
//	void AddEnemy(unsigned long, unsigned long, unsigned long, int, int);
//	void AddEnemy(class CCharacter *, int, int);
//	CCharacter* GetEnemy_AttackMyOwer(int);
	BOOL InitPosition(int xPos, int yPos, unsigned char dir);
//	short GetEnemy(unsigned long);
//	void GiveExpToPC();
//	int IsPurchaseItemExist(unsigned short);
//	void NotifyUpdateInfo(class CPC *);
//	void StopMoveSlowly();
//	void StopMove();
//	void StopMove(short, short, int, const bool);
//	unsigned long GetAccountID();
//	void NotifyStopMove(unsigned long);
//	int IsValid();
//	void Stop();
//	MVPINFO* GetMVPInfo();
//	unsigned long GetMVP();
	void GetPickableSortList(SORTED_PCLIST* sortList);
//	CPC* GetNearestPcMoreThanEnemy(int, int);
	void CheckMove();
	void CheckState();
//	unsigned long GetNeighborPcNumber(int);
//	CNPC* GetNeighborNPC(int, int);
//	void NotifyOptionalInfo(class CPC *, int);

private:
	/* this+0 */ //const CNPCUpdater::`vftable';
	/* this+4 */ CNPC* m_npc;
//	void UpdateCharacter(std::vector<CCharacter*>* );
//	void NotifyDisconnect();
//	void ResetAttackPCList();
	/* this+8 */ std::list<ATTACK_PC> m_attackPC;
};
