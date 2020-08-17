#pragma once
class CFSM; // #include "FSM.h"
class CItem; // #include "Item.h"
class CNPC; // #include "NPC.h"
struct SORTED_PCLIST; // #include "Struct.h"


struct NPC_STATEINFO
{
	/* this+ 0 */ unsigned long enemyAID;
	/* this+ 4 */ unsigned long targetItemAID;
	/* this+ 8 */ unsigned long waitStartTime;
	/* this+12 */ unsigned long reChargeTime;
	/* this+16 */ unsigned long deadTime;
};


class CNPCStateUpdater
{
public:
	CNPCStateUpdater();
	virtual ~CNPCStateUpdater();

public:
//	void Init();
//	void Reset(unsigned long );
//	void SetMyOwner(CNPC* );
//	int ProcessInput(CCharacter* , unsigned long , int );
//	int DispatchInput(CCharacter* , unsigned long& , int );
//	void DispatchOutput(CCharacter* , unsigned long , unsigned long , unsigned long );
//	int DirectPathCheck(CCharacter* , CNPC* );
	void CheckInput();
//	void OnStartWait(unsigned long );
//	void OnAttacked(int );
//	CFSM* GetFSM();
	void SetFSM(CFSM* fsm);
//	void SetItemLostFlag(int );
//	int IsItemLost();
//	unsigned short GetLostItem(int , CCharacter* const );
	void NotifyPickupablePCToItem(CItem* item, SORTED_PCLIST* sortedPCList);
//	void Disappear(int , unsigned long );
//	void OnCallTouchEvent(CPC* , unsigned long );
//	void OnCallClickEvent(CPC* , unsigned long );
//	void OnCallArenaStart(unsigned long );
//	void OnTradeStart(CPC* , unsigned long );
//	void OnCallTouchNpcEvent(CNPC* , unsigned long );
//	void OnCallTouchEvent2(CPC* , unsigned long );
//	void OnCashTradeStart(CPC* , unsigned long , unsigned long );
//	void OnMoveStart(unsigned long );
//	void OnStopAndCallClickEvent(CPC* , unsigned long );

public:
	/* this+0 */ //const CNPCStateUpdater::`vftable';
	/* this+4 */ NPC_STATEINFO m_npcStateInfo;

public:
//	void OnClickMobTombEvent(CPC* , unsigned long );

private:
//	void OnStartRandomMove(unsigned long );
//	void OnExpelEnemy(CCharacter* , unsigned long , unsigned long );
	BOOL OnRevengeEnemy(CCharacter* ch);
//	int RevengeEnemy(CCharacter* , unsigned long );
//	unsigned long IsInputOccured(unsigned long , int& );
//	void OnSearchEnemy(unsigned long );
	void OnRevival(unsigned long outputState);
//	void OnMoveToMyOwner(unsigned long );
	void DropItem(unsigned long killer);
	CItem* CreateItemOnPosition(unsigned short itmID, int count);
//	void OnMoveToItem(CPC* , unsigned long );
//	void OnPickUpItem(CPC* , unsigned long );
//	void OnStopMove(CPC* , unsigned long );
//	void OnChangeEnemy(CPC* , unsigned long );
//	void OnRevengeRandom(unsigned long );
//	bool DisappearBattleFieldMonster(unsigned long );
//	int IsFSMDependent();

private:
	/* this+24 */ int m_isItemLost;
	/* this+28 */ int m_isZenyLost;
	/* this+32 */ CNPC* m_npc;
	/* this+36 */ CFSM* m_fsm;

	friend class CNPC;
	friend int LuaGlueFunc_Attack(lua_State* L); // FIXME
	friend int LuaGlueFunc_Revival(lua_State* L); // FIXME
};
