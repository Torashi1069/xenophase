#pragma once
#include "struct.hpp"
#include "std/list"
class CNPC;
class CPC;

class CNPCUpdater
{
	/* this+0 */ public: //const CNPCUpdater::`vftable';
	/* this+4 */ private: CNPC* m_npc;
	/* this+8 */ private: mystd::list<ATTACK_PC> m_attackPC;

	public: CNPCUpdater::CNPCUpdater(void);
	public: virtual CNPCUpdater::~CNPCUpdater(void);
	public: void CNPCUpdater::SetMyOwner(CNPC* npc);
	public: BOOL CNPCUpdater::SetAccountID(int AccountID);
	public: void CNPCUpdater::SetAccountName(const char* buf);
	public: void CNPCUpdater::SetValidate(int isActive);
	public: int CNPCUpdater::IsMyArea(CCharacter* other, int xRange, int yRange);
	public: int CNPCUpdater::IsMyArea(CCharacter* other, int Range);
	public: int CNPCUpdater::IsSomeOne(int x, int y, int range);
	public: void CNPCUpdater::Pause(unsigned long time);
	public: int CNPCUpdater::AddSectionMgr(void);
	public: void CNPCUpdater::RemoveSectionMgr(void);
	public: CNPC* CNPCUpdater::GetNeighborFriendNpc(int range, unsigned long state);
	public: CPC* CNPCUpdater::GetNeighborPc(int xRange, int yRange);
	public: CPC* CNPCUpdater::GetNeighborPc(int range);
	public: CPC* CNPCUpdater::GetNeighborPcExceptG(int range);
	public: CPC* CNPCUpdater::GetNeighborLowerLevelPc(int range, int level);
	public: CCharacter* CNPCUpdater::GetNeighborEnemy(int range);
	public: CCharacter* CNPCUpdater::GetMyOwnerEnemy(int range);
	//public: void CNPCUpdater::AddEnemy(unsigned long, unsigned long, unsigned long, int, int);
	public: void CNPCUpdater::AddEnemy(CCharacter* ch, int damage, int attdamage);
	public: CCharacter* CNPCUpdater::GetEnemy_AttackMyOwer(int range);
	public: int CNPCUpdater::InitPosition(int xPos, int yPos, unsigned char dir);
	public: short CNPCUpdater::GetEnemy(unsigned long AID);
	public: void CNPCUpdater::GiveExpToPC(void);
	//public: int CNPCUpdater::IsPurchaseItemExist(unsigned short);
	public: void CNPCUpdater::NotifyUpdateInfo(CPC* other);
	public: void CNPCUpdater::StopMoveSlowly(void);
	public: void CNPCUpdater::StopMove(void);
	public: void CNPCUpdater::StopMove(short x, short y, int isMove);
	public: unsigned long CNPCUpdater::GetAccountID(void);
	public: void CNPCUpdater::NotifyStopMove(unsigned long type);
	public: int CNPCUpdater::IsValid(void);
	public: void CNPCUpdater::Stop(void);
	public: MVPINFO* CNPCUpdater::GetMVPInfo(void);
	public: unsigned long CNPCUpdater::GetMVP(void);
	public: void CNPCUpdater::GetPickableSortList(SORTED_PCLIST* sortList);
	public: CPC* CNPCUpdater::GetNearestPcMoreThanEnemy(int length, int curEnemyAID);
	public: void CNPCUpdater::CheckMove(void);
	public: void CNPCUpdater::CheckState(void);
	public: unsigned long CNPCUpdater::GetNeighborPcNumber(int range);
	public: CNPC* CNPCUpdater::GetNeighborNPC(int xRange, int yRange);
	public: void CNPCUpdater::NotifyOptionalInfo(CPC* other, int characterState);
	private: void CNPCUpdater::UpdateCharacter(mystd::vector<CCharacter*>* section);
	private: void CNPCUpdater::NotifyDisconnect(void);
	private: void CNPCUpdater::ResetAttackPCList(void);

private:
	static hook_method<void (CNPCUpdater::*)(CNPC* npc)> CNPCUpdater::_SetMyOwner;
	static hook_method<int (CNPCUpdater::*)(int AccountID)> CNPCUpdater::_SetAccountID;
	static hook_method<void (CNPCUpdater::*)(const char* buf)> CNPCUpdater::_SetAccountName;
	static hook_method<void (CNPCUpdater::*)(int isActive)> CNPCUpdater::_SetValidate;
	static hook_method<int (CNPCUpdater::*)(CCharacter* other, int xRange, int yRange)> CNPCUpdater::_IsMyArea;
	static hook_method<int (CNPCUpdater::*)(CCharacter* other, int Range)> CNPCUpdater::_IsMyArea2;
	static hook_method<int (CNPCUpdater::*)(int x, int y, int range)> CNPCUpdater::_IsSomeOne;
	static hook_method<void (CNPCUpdater::*)(unsigned long time)> CNPCUpdater::_Pause;
	static hook_method<int (CNPCUpdater::*)(void)> CNPCUpdater::_AddSectionMgr;
	static hook_method<void (CNPCUpdater::*)(void)> CNPCUpdater::_RemoveSectionMgr;
	static hook_method<CNPC* (CNPCUpdater::*)(int range, unsigned long state)> CNPCUpdater::_GetNeighborFriendNpc;
	static hook_method<CPC* (CNPCUpdater::*)(int xRange, int yRange)> CNPCUpdater::_GetNeighborPc;
	static hook_method<CPC* (CNPCUpdater::*)(int range)> CNPCUpdater::_GetNeighborPc2;
	static hook_method<CPC* (CNPCUpdater::*)(int range)> CNPCUpdater::_GetNeighborPcExceptG;
	static hook_method<CPC* (CNPCUpdater::*)(int range, int level)> CNPCUpdater::_GetNeighborLowerLevelPc;
	static hook_method<CCharacter* (CNPCUpdater::*)(int range)> CNPCUpdater::_GetNeighborEnemy;
	static hook_method<CCharacter* (CNPCUpdater::*)(int range)> CNPCUpdater::_GetMyOwnerEnemy;
	static hook_method<void (CNPCUpdater::*)(CCharacter* ch, int damage, int attdamage)> CNPCUpdater::_AddEnemy;
	static hook_method<CCharacter* (CNPCUpdater::*)(int range)> CNPCUpdater::_GetEnemy_AttackMyOwer;
	static hook_method<int (CNPCUpdater::*)(int xPos, int yPos, unsigned char dir)> CNPCUpdater::_InitPosition;
	static hook_method<short (CNPCUpdater::*)(unsigned long AID)> CNPCUpdater::_GetEnemy;
	static hook_method<void (CNPCUpdater::*)(void)> CNPCUpdater::_GiveExpToPC;
	static hook_method<void (CNPCUpdater::*)(CPC* other)> CNPCUpdater::_NotifyUpdateInfo;
	static hook_method<void (CNPCUpdater::*)(void)> CNPCUpdater::_StopMoveSlowly;
	static hook_method<void (CNPCUpdater::*)(void)> CNPCUpdater::_StopMove;
	static hook_method<void (CNPCUpdater::*)(short x, short y, int isMove)> CNPCUpdater::_StopMove2;
	static hook_method<unsigned long (CNPCUpdater::*)(void)> CNPCUpdater::_GetAccountID;
	static hook_method<void (CNPCUpdater::*)(unsigned long type)> CNPCUpdater::_NotifyStopMove;
	static hook_method<int (CNPCUpdater::*)(void)> CNPCUpdater::_IsValid;
	static hook_method<void (CNPCUpdater::*)(void)> CNPCUpdater::_Stop;
	static hook_method<MVPINFO* (CNPCUpdater::*)(void)> CNPCUpdater::_GetMVPInfo;
	static hook_method<unsigned long (CNPCUpdater::*)(void)> CNPCUpdater::_GetMVP;
	static hook_method<void (CNPCUpdater::*)(SORTED_PCLIST* sortList)> CNPCUpdater::_GetPickableSortList;
	static hook_method<CPC* (CNPCUpdater::*)(int length, int curEnemyAID)> CNPCUpdater::_GetNearestPcMoreThanEnemy;
	static hook_method<void (CNPCUpdater::*)(void)> CNPCUpdater::_CheckMove;
	static hook_method<void (CNPCUpdater::*)(void)> CNPCUpdater::_CheckState;
	static hook_method<unsigned long (CNPCUpdater::*)(int range)> CNPCUpdater::_GetNeighborPcNumber;
	static hook_method<CNPC* (CNPCUpdater::*)(int xRange, int yRange)> CNPCUpdater::_GetNeighborNPC;
	static hook_method<void (CNPCUpdater::*)(CPC* other, int characterState)> CNPCUpdater::_NotifyOptionalInfo;
	static hook_method<void (CNPCUpdater::*)(mystd::vector<CCharacter *>* section)> CNPCUpdater::_UpdateCharacter;
	static hook_method<void (CNPCUpdater::*)(void)> CNPCUpdater::_NotifyDisconnect;
	static hook_method<void (CNPCUpdater::*)(void)> CNPCUpdater::_ResetAttackPCList;

	friend class CNPC;
};
