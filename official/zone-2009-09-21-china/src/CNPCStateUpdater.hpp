#pragma once
class CItem;
class CNPC;
class CFSM;
class CPC;


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
	/* this+ 0 */ public: //const CNPCStateUpdater::`vftable';
	/* this+ 4 */ public: NPC_STATEINFO m_npcStateInfo;
	/* this+24 */ private: int m_isItemLost;
	/* this+28 */ private: int m_isZenyLost;
	/* this+32 */ private: CNPC* m_npc;
	/* this+26 */ private: CFSM* m_fsm;

	public: CNPCStateUpdater::CNPCStateUpdater(void);
	public: virtual CNPCStateUpdater::~CNPCStateUpdater(void);
	public: void CNPCStateUpdater::Init(void);
	public: void CNPCStateUpdater::Reset(unsigned long deadTime);
	public: void CNPCStateUpdater::SetMyOwner(CNPC* npc);
	public: int CNPCStateUpdater::ProcessInput(CCharacter* ch, unsigned long inputType, int par1);
	public: int CNPCStateUpdater::DispatchInput(CCharacter* ch, unsigned long& inputType, int par1);
	public: void CNPCStateUpdater::DispatchOutput(CCharacter* ch, unsigned long outputType, unsigned long outputState, unsigned long inputType);
	public: int CNPCStateUpdater::DirectPathCheck(CCharacter* target, CNPC* npc);
	public: void CNPCStateUpdater::CheckInput(void);
	public: void CNPCStateUpdater::OnStartWait(unsigned long outputState);
	public: void CNPCStateUpdater::OnAttacked(int damage);
	public: CFSM* CNPCStateUpdater::GetFSM(void);
	public: void CNPCStateUpdater::SetFSM(CFSM* fsm);
	public: void CNPCStateUpdater::SetItemLostFlag(int flag);
	public: int CNPCStateUpdater::IsItemLost(void);
	public: unsigned short CNPCStateUpdater::GetLostItem(int percent);
	public: void CNPCStateUpdater::NotifyPickupablePCToItem(CItem* item, SORTED_PCLIST* sortedPCList);
	public: void CNPCStateUpdater::Disappear(int type, unsigned long killer);
	public: void CNPCStateUpdater::OnCallTouchEvent(CPC* pc, unsigned long outputState);
	public: void CNPCStateUpdater::OnCallClickEvent(CPC* pc, unsigned long outputState);
	public: void CNPCStateUpdater::OnCallArenaStart(unsigned long outputState);
	public: void CNPCStateUpdater::OnTradeStart(CPC* pc, unsigned long outputState);
	public: void CNPCStateUpdater::OnCallTouchNpcEvent(CNPC* npc, unsigned long outputState);
	public: void CNPCStateUpdater::OnCallTouchEvent2(CPC* pc, unsigned long outputState);
	public: void CNPCStateUpdater::OnCashTradeStart(CPC* pc, unsigned long npcId, unsigned long outputState);
	public: void CNPCStateUpdater::OnMoveStart(unsigned long outputState);
	public: void CNPCStateUpdater::OnStopAndCallClickEvent(CPC* pc, unsigned long outputState);
	private: void CNPCStateUpdater::OnStartRandomMove(unsigned long outputState);
	private: void CNPCStateUpdater::OnExpelEnemy(CCharacter* ch, unsigned long outputState, unsigned long inputType);
	private: int CNPCStateUpdater::OnRevengeEnemy(CCharacter* ch);
	private: void CNPCStateUpdater::RevengeEnemy(CCharacter* CH, unsigned long outputState);
	private: unsigned long CNPCStateUpdater::IsInputOccured(unsigned long inputType, int& pc);
	private: void CNPCStateUpdater::OnSearchEnemy(unsigned long outputState);
	private: void CNPCStateUpdater::OnRevival(unsigned long outputState);
	private: void CNPCStateUpdater::OnMoveToMyOwner(unsigned long outputState);
	private: void CNPCStateUpdater::DropItem(unsigned long killer);
	private: CItem* CNPCStateUpdater::CreateItemOnPosition(unsigned short itmID, int count);
	private: void CNPCStateUpdater::OnMoveToItem(CPC* pc, unsigned long outputState);
	private: void CNPCStateUpdater::OnPickUpItem(CPC* pc, unsigned long outputState);
	private: void CNPCStateUpdater::OnStopMove(CPC* pc, unsigned long outputState);
	private: void CNPCStateUpdater::OnChangeEnemy(CPC* pc, unsigned long outputState);
	private: void CNPCStateUpdater::OnRevengeRandom(unsigned long outputState);
	private: bool CNPCStateUpdater::DisappearBattleFieldMonster(unsigned long killer);
	private: int CNPCStateUpdater::IsFSMDependent(void);

private:
	static hook_method<void (CNPCStateUpdater::*)(void)> CNPCStateUpdater::_Init;
	static hook_method<void (CNPCStateUpdater::*)(unsigned long deadTime)> CNPCStateUpdater::_Reset;
	static hook_method<void (CNPCStateUpdater::*)(CNPC* npc)> CNPCStateUpdater::_SetMyOwner;
	static hook_method<int (CNPCStateUpdater::*)(CCharacter* ch, unsigned long inputType, int par1)> CNPCStateUpdater::_ProcessInput;
	static hook_method<int (CNPCStateUpdater::*)(CCharacter* ch, unsigned long& inputType, int par1)> CNPCStateUpdater::_DispatchInput;
	static hook_method<void (CNPCStateUpdater::*)(CCharacter* ch, unsigned long outputType, unsigned long outputState, unsigned long inputType)> CNPCStateUpdater::_DispatchOutput;
	static hook_method<int (CNPCStateUpdater::*)(CCharacter* target, CNPC* npc)> CNPCStateUpdater::_DirectPathCheck;
	static hook_method<void (CNPCStateUpdater::*)(void)> CNPCStateUpdater::_CheckInput;
	static hook_method<void (CNPCStateUpdater::*)(unsigned long outputState)> CNPCStateUpdater::_OnStartWait;
	static hook_method<void (CNPCStateUpdater::*)(int damage)> CNPCStateUpdater::_OnAttacked;
	static hook_method<CFSM* (CNPCStateUpdater::*)(void)> CNPCStateUpdater::_GetFSM;
	static hook_method<void (CNPCStateUpdater::*)(CFSM* fsm)> CNPCStateUpdater::_SetFSM;
	static hook_method<void (CNPCStateUpdater::*)(int flag)> CNPCStateUpdater::_SetItemLostFlag;
	static hook_method<int (CNPCStateUpdater::*)(void)> CNPCStateUpdater::_IsItemLost;
	static hook_method<unsigned short (CNPCStateUpdater::*)(int percent)> CNPCStateUpdater::_GetLostItem;
	static hook_method<void (CNPCStateUpdater::*)(CItem* item, SORTED_PCLIST* sortedPCList)> CNPCStateUpdater::_NotifyPickupablePCToItem;
	static hook_method<void (CNPCStateUpdater::*)(int type, unsigned long killer)> CNPCStateUpdater::_Disappear;
	static hook_method<void (CNPCStateUpdater::*)(CPC* pc, unsigned long outputState)> CNPCStateUpdater::_OnCallTouchEvent;
	static hook_method<void (CNPCStateUpdater::*)(CPC* pc, unsigned long outputState)> CNPCStateUpdater::_OnCallClickEvent;
	static hook_method<void (CNPCStateUpdater::*)(unsigned long outputState)> CNPCStateUpdater::_OnCallArenaStart;
	static hook_method<void (CNPCStateUpdater::*)(CPC* pc, unsigned long outputState)> CNPCStateUpdater::_OnTradeStart;
	static hook_method<void (CNPCStateUpdater::*)(CNPC* npc, unsigned long outputState)> CNPCStateUpdater::_OnCallTouchNpcEvent;
	static hook_method<void (CNPCStateUpdater::*)(CPC* pc, unsigned long outputState)> CNPCStateUpdater::_OnCallTouchEvent2;
	static hook_method<void (CNPCStateUpdater::*)(CPC* pc, unsigned long npcId, unsigned long outputState)> CNPCStateUpdater::_OnCashTradeStart;
	static hook_method<void (CNPCStateUpdater::*)(unsigned long outputState)> CNPCStateUpdater::_OnMoveStart;
	static hook_method<void (CNPCStateUpdater::*)(CPC* pc, unsigned long outputState)> CNPCStateUpdater::_OnStopAndCallClickEvent;
	static hook_method<void (CNPCStateUpdater::*)(unsigned long outputState)> CNPCStateUpdater::_OnStartRandomMove;
	static hook_method<void (CNPCStateUpdater::*)(CCharacter* ch, unsigned long outputState, unsigned long inputType)> CNPCStateUpdater::_OnExpelEnemy;
	static hook_method<int (CNPCStateUpdater::*)(CCharacter* ch)> CNPCStateUpdater::_OnRevengeEnemy;
	static hook_method<void (CNPCStateUpdater::*)(CCharacter* CH, unsigned long outputState)> CNPCStateUpdater::_RevengeEnemy;
	static hook_method<unsigned long (CNPCStateUpdater::*)(unsigned long inputType, int& pc)> CNPCStateUpdater::_IsInputOccured;
	static hook_method<void (CNPCStateUpdater::*)(unsigned long outputState)> CNPCStateUpdater::_OnSearchEnemy;
	static hook_method<void (CNPCStateUpdater::*)(unsigned long outputState)> CNPCStateUpdater::_OnRevival;
	static hook_method<void (CNPCStateUpdater::*)(unsigned long outputState)> CNPCStateUpdater::_OnMoveToMyOwner;
	static hook_method<void (CNPCStateUpdater::*)(unsigned long killer)> CNPCStateUpdater::_DropItem;
	static hook_method<CItem* (CNPCStateUpdater::*)(unsigned short itmID, int count)> CNPCStateUpdater::_CreateItemOnPosition;
	static hook_method<void (CNPCStateUpdater::*)(CPC* pc, unsigned long outputState)> CNPCStateUpdater::_OnMoveToItem;
	static hook_method<void (CNPCStateUpdater::*)(CPC* pc, unsigned long outputState)> CNPCStateUpdater::_OnPickUpItem;
	static hook_method<void (CNPCStateUpdater::*)(CPC* pc, unsigned long outputState)> CNPCStateUpdater::_OnChangeEnemy;
	static hook_method<void (CNPCStateUpdater::*)(unsigned long outputState)> CNPCStateUpdater::_OnRevengeRandom;
	static hook_method<void (CNPCStateUpdater::*)(CPC* pc, unsigned long outputState)> CNPCStateUpdater::_OnStopMove;
	static hook_method<bool (CNPCStateUpdater::*)(unsigned long killer)> CNPCStateUpdater::_DisappearBattleFieldMonster;
	static hook_method<int (CNPCStateUpdater::*)(void)> CNPCStateUpdater::_IsFSMDependent;

	friend class CNPC;
};
