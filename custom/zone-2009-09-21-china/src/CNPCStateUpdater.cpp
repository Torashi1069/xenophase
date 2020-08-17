#include "globals.hpp"
#include "FSM.h"
#include "CharacterMgr.h"
#include "CITP.hpp"
#include "CITPMgr.hpp"
#include "MonParameterMgr.h"
#include "CNPCStateUpdater.hpp"
#include "CMsg.hpp"
#include "NPC.h"
#include "CNpcHomun.hpp"
#include "CNpcMob.hpp"
#include "NpcPet.h"
#include "NpcServer/NpcSvr.h"
#include "CPCBattle.hpp"
#include "CUIDGenerator.hpp"
#include "ZoneScript.h"
#include "zoneprocess.h"
#include "Common/Packet.h"
#include "Custom/umage.hpp" //Autoloot()
#include "shared.h" // Trace


CNPCStateUpdater::CNPCStateUpdater(void) // line 47
{
}


CNPCStateUpdater::~CNPCStateUpdater(void) // line 51
{
}


hook_method<void (CNPCStateUpdater::*)(void)> CNPCStateUpdater::_Init(SERVER, "CNPCStateUpdater::Init");
void CNPCStateUpdater::Init(void)
{
	return (this->*_Init)();

	CNPCStateUpdater::Reset(0);
	m_fsm = 0;
	m_npcStateInfo.waitStartTime = timeGetTime();
}


hook_method<void (CNPCStateUpdater::*)(unsigned long deadTime)> CNPCStateUpdater::_Reset(SERVER, "CNPCStateUpdater::Reset");
void CNPCStateUpdater::Reset(unsigned long deadTime)
{
	return (this->*_Reset)(deadTime);

	m_npcStateInfo.enemyAID = 0;
	m_npcStateInfo.targetItemAID = 0;
	m_npcStateInfo.waitStartTime = 0;
	m_npcStateInfo.reChargeTime = 0;
	m_npcStateInfo.deadTime = deadTime;
	m_isItemLost = 0;
	m_isZenyLost = 0;
}


hook_method<void (CNPCStateUpdater::*)(CNPC* npc)> CNPCStateUpdater::_SetMyOwner(SERVER, "CNPCStateUpdater::SetMyOwner");
void CNPCStateUpdater::SetMyOwner(CNPC* npc)
{
	return (this->*_SetMyOwner)(npc);

	m_npc = npc;
}


hook_method<int (CNPCStateUpdater::*)(CCharacter* ch, unsigned long inputType, int par1)> CNPCStateUpdater::_ProcessInput(SERVER, "CNPCStateUpdater::ProcessInput");
int CNPCStateUpdater::ProcessInput(CCharacter* ch, unsigned long inputType, int par1)
{
	return (this->*_ProcessInput)(ch, inputType, par1);

	if( m_fsm == NULL )
		return 1;
	
	CFSMState* st = m_fsm->CFSM::GetFSMState(m_npc->m_currentState);
	if( st == NULL )
		return 1;

	if( this->CNPCStateUpdater::DispatchInput(ch, inputType, par1) )
	{
		unsigned long outputType;
		unsigned long outputState;
		if( st->CFSMState::GetOutput(inputType, outputType, outputState) )
			this->CNPCStateUpdater::DispatchOutput(ch, outputType, outputState, inputType);
		return 1;
	}

	if( m_npc->m_currentState != DEAD_ST )
		return 1;

	return 0;
}


hook_method<int (CNPCStateUpdater::*)(CCharacter* ch, unsigned long& inputType, int par1)> CNPCStateUpdater::_DispatchInput(SERVER, "CNPCStateUpdater::DispatchInput");
int CNPCStateUpdater::DispatchInput(CCharacter* ch, unsigned long& inputType, int par1)
{
	return (this->*_DispatchInput)(ch, inputType, par1);

	//TODO
}


hook_method<void (CNPCStateUpdater::*)(CCharacter* ch, unsigned long outputType, unsigned long outputState, unsigned long inputType)> CNPCStateUpdater::_DispatchOutput(SERVER, "CNPCStateUpdater::DispatchOutput");
void CNPCStateUpdater::DispatchOutput(CCharacter* ch, unsigned long outputType, unsigned long outputState, unsigned long inputType)
{
	return (this->*_DispatchOutput)(ch, outputType, outputState, inputType);

	switch( outputType )
	{
	case NONE_OUT: m_npc->CNPC::SetCurrentFSMState(outputState); break;
	case TRADE_START_OUT: this->CNPCStateUpdater::OnTradeStart((CPC *)ch, outputState); break;
	case CALL_CLICKEVENT_OUT: this->CNPCStateUpdater::OnCallClickEvent((CPC *)ch, outputState); break;
	case CALL_TOUCHEVENT_OUT: this->CNPCStateUpdater::OnCallTouchEvent((CPC *)ch, outputState); break;
	case MOVE_RANDOM_START_OUT: this->CNPCStateUpdater::OnStartRandomMove(outputState); break;
	case WAIT_START_OUT: this->CNPCStateUpdater::OnStartWait(outputState); break;
	case EXPEL_OUT: this->CNPCStateUpdater::OnExpelEnemy(ch, outputState, inputType); break;
	case SEARCH_OUT: this->CNPCStateUpdater::OnSearchEnemy(outputState); break;
	case REVENGE_ENEMY_OUT: this->CNPCStateUpdater::RevengeEnemy(ch, outputState); break;
	case TRY_REVIVAL_OUT: this->CNPCStateUpdater::OnRevival(outputState); break;
	case MOVETO_ITEM_OUT: this->CNPCStateUpdater::OnMoveToItem((CPC*)NULL, outputState); break;
	case PICKUP_ITEM_OUT: this->CNPCStateUpdater::OnPickUpItem((CPC*)NULL, outputState); break;
	case STOP_MOVE_OUT: this->CNPCStateUpdater::OnStopMove((CPC*)NULL, outputState); break;
	case CHANGE_ENEMY_OUT: this->CNPCStateUpdater::OnChangeEnemy((CPC *)ch, outputState); break;
	case CHANGE_NORMALST_OUT: this->CNPCStateUpdater::OnStartWait(outputState); break;
	case CALL_ARENASTART_OUT: this->CNPCStateUpdater::OnCallArenaStart(outputState); break;
	case MOVETO_MYOWNER_OUT: this->CNPCStateUpdater::OnMoveToMyOwner(outputState); break;
	case REVENGE_RANDOM_OUT: this->CNPCStateUpdater::OnRevengeRandom(outputState); break;
	case CALL_TOUCHNPCEVENT_OUT: this->CNPCStateUpdater::OnCallTouchNpcEvent((CNPC *)ch, outputState); break;
	case CALL_TOUCHEVENT2_OUT: this->CNPCStateUpdater::OnCallTouchEvent2((CPC *)ch, outputState); break;
	default:
		return;
	}
}


hook_method<int (CNPCStateUpdater::*)(CCharacter* target, CNPC* npc)> CNPCStateUpdater::_DirectPathCheck(SERVER, "CNPCStateUpdater::DirectPathCheck");
int CNPCStateUpdater::DirectPathCheck(CCharacter* target, CNPC* npc)
{
	return (this->*_DirectPathCheck)(target, npc);

	//TODO
}


hook_method<void (CNPCStateUpdater::*)(void)> CNPCStateUpdater::_CheckInput(SERVER, "CNPCStateUpdater::CheckInput");
void CNPCStateUpdater::CheckInput(void)
{
	return (this->*_CheckInput)();

	if( m_npc->m_npcType == 3 )
		return;

	if( !this->CNPCStateUpdater::IsFSMDependent() )
		return;

	CFSMState* state = m_fsm->CFSM::GetFSMState(m_npc->m_currentState);
	if( state == NULL )
		return;

	for( int i = 0; i < state->m_count; ++i )
	{
		CCharacter* pc;
		if( this->CNPCStateUpdater::IsInputOccured(state->m_transition[i], (int&)pc) == 0 )
		{
			this->CNPCStateUpdater::ProcessInput(pc, state->m_transition[i], 0);
			break;
		}
	}
}


hook_method<void (CNPCStateUpdater::*)(unsigned long outputState)> CNPCStateUpdater::_OnStartWait(SERVER, "CNPCStateUpdater::OnStartWait");
void CNPCStateUpdater::OnStartWait(unsigned long outputState)
{
	return (this->*_OnStartWait)(outputState);

	//TODO
}


hook_method<void (CNPCStateUpdater::*)(int damage)> CNPCStateUpdater::_OnAttacked(SERVER, "CNPCStateUpdater::OnAttacked");
void CNPCStateUpdater::OnAttacked(int damage)
{
	return (this->*_OnAttacked)(damage);

	//TODO
}


//hook_method<CFSM* (CNPCStateUpdater::*)(void)> CNPCStateUpdater::_GetFSM(SERVER, "CNPCStateUpdater::GetFSM");
CFSM* CNPCStateUpdater::GetFSM(void)
{
//	return (this->*_GetFSM)();

	return m_fsm;
}


hook_method<void (CNPCStateUpdater::*)(CFSM* fsm)> CNPCStateUpdater::_SetFSM(SERVER, "CNPCStateUpdater::SetFSM");
void CNPCStateUpdater::SetFSM(CFSM* fsm)
{
	return (this->*_SetFSM)(fsm);

	m_fsm = fsm;
}


//hook_method<void (CNPCStateUpdater::*)(int flag)> CNPCStateUpdater::_SetItemLostFlag(SERVER, "CNPCStateUpdater::SetItemLostFlag");
void CNPCStateUpdater::SetItemLostFlag(int flag)
{
//	return (this->*_SetItemLostFlag)(flag);

	m_isItemLost = flag;
}


hook_method<int (CNPCStateUpdater::*)(void)> CNPCStateUpdater::_IsItemLost(SERVER, "CNPCStateUpdater::IsItemLost");
int CNPCStateUpdater::IsItemLost(void)
{
	return (this->*_IsItemLost)();

	return m_isItemLost;
}


hook_method<unsigned short (CNPCStateUpdater::*)(int percent)> CNPCStateUpdater::_GetLostItem(SERVER, "CNPCStateUpdater::GetLostItem");
unsigned short CNPCStateUpdater::GetLostItem(int percent)
{
	return (this->*_GetLostItem)(percent);

	//TODO
}


hook_method<void (CNPCStateUpdater::*)(CItem* item, SORTED_PCLIST* sortedPCList)> CNPCStateUpdater::_NotifyPickupablePCToItem(SERVER, "CNPCStateUpdater::NotifyPickupablePCToItem");
void CNPCStateUpdater::NotifyPickupablePCToItem(CItem* item, SORTED_PCLIST* sortedPCList)
{
	return (this->*_NotifyPickupablePCToItem)(item, sortedPCList);

	//TODO
}


hook_method<void (CNPCStateUpdater::*)(int type, unsigned long killer)> CNPCStateUpdater::_Disappear(SERVER, "CNPCStateUpdater::Disappear");
void CNPCStateUpdater::Disappear(int type, unsigned long killer)
{
	return (this->*_Disappear)(type, killer);

	this->m_npc->m_npcUpdater.CNPCUpdater::SetValidate(0);

	PACKET_ZC_NOTIFY_VANISH packet;
	packet.PacketType = HEADER_ZC_NOTIFY_VANISH;
	packet.GID = m_npc->GetAccountID();
	packet.type = type;
	m_npc->CCharacter::MultiCast((char*)&packet, sizeof(packet));

	m_npc->CNPC::OnResetMyMob();

	if( m_npc->GetEffective(EFST_BLADESTOP,0) )
		m_npc->ResetEffective(EFST_BLADESTOP,0);

	if( m_npc->m_npcSkill.m_creatorPCAID )
	{
		CPC* pc = (CPC*)g_characterMgr->CCharacterMgr::FindCharacter(m_npc->m_npcSkill.m_creatorPCAID, PC_TYPE);
		if( pc != NULL )
			pc->CPC::UpdateCreatedMobCount(m_npc->m_characterInfo.job, -1);
	}

	if( m_npc->GetEffective(EFST_STOP,0) )
		m_npc->ResetEffective(EFST_STOP,0);

	if( type == 1 ) // died
	{
		int npcType = m_npc->GetType();
		if( npcType == NPC_HO_TYPE )
		{
			((CNpcHomun *)m_npc)->CNpcHomun::SetModifiedState(4);
		}
		else
		if( npcType == NPC_MERSOL_TYPE )
		{
			;
		}
		else
		if( killer != 0 )
		{
			m_npc->m_npcUpdater.CNPCUpdater::GiveExpToPC();

			if( !m_npc->m_npcSkill.m_isRebirth )
				this->CNPCStateUpdater::DropItem(killer);

			if( m_npc->m_myParentAID )
				g_characterMgr->CCharacterMgr::SendMsg(m_npc, m_npc->m_myParentAID, CM_MYMONSTER_DEAD, m_npc->GetAccountID(), killer, 0, 0);

			g_characterMgr->CCharacterMgr::SendMsg(m_npc, m_npc->m_npcUpdater.GetMVP(), CM_HUNTINGLIST, m_npc->m_characterInfo.job, 0, 0, 0);
			g_characterMgr->CCharacterMgr::SendMsg(m_npc, killer, CM_QUESTMISSION_HUNTINGLIST, m_npc->m_characterInfo.job, 0, 0, 0);
		}
	}

	m_npc->m_npcUpdater.CNPCUpdater::RemoveSectionMgr();

	if( m_npc->m_characterInfo.job != JT_OBJ_NEUTRAL
	&&  m_npc->m_characterInfo.job != JT_OBJ_FLAG_A
	&&  m_npc->m_characterInfo.job != JT_OBJ_FLAG_B
	||  this->CNPCStateUpdater::DisappearBattleFieldMonster(killer) != 1 )
	{
		if( m_npc->m_characterInfo.IsRegen )
		{
			m_npc->Reset();
		}
		else
		{
			if( m_npc->GetType() == NPC_PET_TYPE )
			{
				((CNpcPet *)m_npc)->CNpcPet::ModifyRelationship(0);
				((CNpcPet *)m_npc)->CNpcPet::UpdateDB();
			}

			m_npc->CNPC::SetCurrentFSMState(0xBu);

			m_npc->AddErrorCount(".\\NPCStateUpdater.cpp", 695, 4, timeGetTime());
		}
	}
}


hook_method<void (CNPCStateUpdater::*)(CPC* pc, unsigned long outputState)> CNPCStateUpdater::_OnCallTouchEvent(SERVER, "CNPCStateUpdater::OnCallTouchEvent");
void CNPCStateUpdater::OnCallTouchEvent(CPC* pc, unsigned long outputState) // line 884-899
{
	return (this->*_OnCallTouchEvent)(pc, outputState);

	if( pc == NULL )
		return; // no player

	if( pc->m_eventNo != 0 )
		g_npcSvr->CNpcSvr::CancelEvent(pc->m_eventNo);

	CZNPC2Msg msg;
	msg.CMsg::SetMsgID(37);
	msg.par1 = 3;

	int eventNo = g_npcSvr->CNpcSvr::SendMsg(pc->GetAccountID(), m_npc->GetAccountID(), &msg);
	if( eventNo != 0 )
		pc->m_eventNo = eventNo;

	m_npc->CNPC::SetCurrentFSMState(outputState);
}


hook_method<void (CNPCStateUpdater::*)(CPC* pc, unsigned long outputState)> CNPCStateUpdater::_OnCallClickEvent(SERVER, "CNPCStateUpdater::OnCallClickEvent");
void CNPCStateUpdater::OnCallClickEvent(CPC* pc, unsigned long outputState)
{
	return (this->*_OnCallClickEvent)(pc, outputState);

	//TDOO
}


hook_method<void (CNPCStateUpdater::*)(unsigned long outputState)> CNPCStateUpdater::_OnCallArenaStart(SERVER, "CNPCStateUpdater::OnCallArenaStart");
void CNPCStateUpdater::OnCallArenaStart(unsigned long outputState)
{
	return (this->*_OnCallArenaStart)(outputState);

	//TODO
}


hook_method<void (CNPCStateUpdater::*)(CPC* pc, unsigned long outputState)> CNPCStateUpdater::_OnTradeStart(SERVER, "CNPCStateUpdater::OnTradeStart");
void CNPCStateUpdater::OnTradeStart(CPC* pc, unsigned long outputState)
{
	return (this->*_OnTradeStart)(pc, outputState);

	//TODO
}


hook_method<void (CNPCStateUpdater::*)(CNPC* npc, unsigned long outputState)> CNPCStateUpdater::_OnCallTouchNpcEvent(SERVER, "CNPCStateUpdater::OnCallTouchNpcEvent");
void CNPCStateUpdater::OnCallTouchNpcEvent(CNPC* npc, unsigned long outputState)
{
	return (this->*_OnCallTouchNpcEvent)(npc, outputState);

	//TODO
}


hook_method<void (CNPCStateUpdater::*)(CPC* pc, unsigned long outputState)> CNPCStateUpdater::_OnCallTouchEvent2(SERVER, "CNPCStateUpdater::OnCallTouchEvent2");
void CNPCStateUpdater::OnCallTouchEvent2(CPC* pc, unsigned long outputState) // line 2282-2296
{
	return (this->*_OnCallTouchEvent2)(pc, outputState);

	if( pc == NULL )
		return; // no player

	if( pc->m_eventNo != 0 )
		g_npcSvr->CNpcSvr::CancelEvent(pc->m_eventNo);

	CZNPC2Msg msg;
	msg.CMsg::SetMsgID(37);
	msg.par1 = 9;

	int eventNo = g_npcSvr->CNpcSvr::SendMsg(pc->GetAccountID(), m_npc->GetAccountID(), &msg);
	if( eventNo != 0 )
		pc->m_eventNo = eventNo;

	m_npc->CNPC::SetCurrentFSMState(outputState);
}


hook_method<void (CNPCStateUpdater::*)(CPC* pc, unsigned long npcId, unsigned long outputState)> CNPCStateUpdater::_OnCashTradeStart(SERVER, "CNPCStateUpdater::OnCashTradeStart");
void CNPCStateUpdater::OnCashTradeStart(CPC* pc, unsigned long npcId, unsigned long outputState)
{
	return (this->*_OnCashTradeStart)(pc, npcId, outputState);

	//TODO
}


//hook_method<void (CNPCStateUpdater::*)(unsigned long outputState)> CNPCStateUpdater::_OnMoveStart(SERVER, "CNPCStateUpdater::OnMoveStart");
void CNPCStateUpdater::OnMoveStart(unsigned long outputState)
{
//	return (this->*_OnMoveStart)(outputState);

	return;
}


//hook_method<void (CNPCStateUpdater::*)(CPC* pc, unsigned long outputState)> CNPCStateUpdater::_OnStopAndCallClickEvent(SERVER, "CNPCStateUpdater::OnStopAndCallClickEvent");
void CNPCStateUpdater::OnStopAndCallClickEvent(CPC* pc, unsigned long outputState)
{
//	return (this->*_OnStopAndCallClickEvent)(pc, outputState);

	return;
}


hook_method<void (CNPCStateUpdater::*)(unsigned long outputState)> CNPCStateUpdater::_OnStartRandomMove(SERVER, "CNPCStateUpdater::OnStartRandomMove");
void CNPCStateUpdater::OnStartRandomMove(unsigned long outputState)
{
	return (this->*_OnStartRandomMove)(outputState);

	int xPos = m_npc->m_pathInfo.m_moveInfo.xPos;
	int yPos = m_npc->m_pathInfo.m_moveInfo.yPos;

	m_npc->m_npcStateUpdater.m_npcStateInfo.enemyAID = 0;
	m_npc->m_mapRes->CMapRes::GetRandomPos(xPos, yPos, 0, 8, m_npc->GetAccountID());

	if( xPos == m_npc->m_pathInfo.m_moveInfo.xPos && yPos == m_npc->m_pathInfo.m_moveInfo.yPos )
		return; // already there

	PACKET_CZ_REQUEST_MOVE move;
	EncodePosDir(xPos, yPos, 0, move.dest);

	if( m_npc->CNPC::OnMove(&move) )
		m_npc->CNPC::SetCurrentFSMState(outputState);
}


hook_method<void (CNPCStateUpdater::*)(CCharacter* ch, unsigned long outputState, unsigned long inputType)> CNPCStateUpdater::_OnExpelEnemy(SERVER, "CNPCStateUpdater::OnExpelEnemy");
void CNPCStateUpdater::OnExpelEnemy(CCharacter* ch, unsigned long outputState, unsigned long inputType)
{
	return (this->*_OnExpelEnemy)(ch, outputState, inputType);

	//TODO
}


hook_method<int (CNPCStateUpdater::*)(CCharacter* ch)> CNPCStateUpdater::_OnRevengeEnemy(SERVER, "CNPCStateUpdater::OnRevengeEnemy");
int CNPCStateUpdater::OnRevengeEnemy(CCharacter* ch)
{
	return (this->*_OnRevengeEnemy)(ch);

	//TODO
}


hook_method<void (CNPCStateUpdater::*)(CCharacter* CH, unsigned long outputState)> CNPCStateUpdater::_RevengeEnemy(SERVER, "CNPCStateUpdater::RevengeEnemy");
void CNPCStateUpdater::RevengeEnemy(CCharacter* CH, unsigned long outputState)
{
	return (this->*_RevengeEnemy)(CH, outputState);

	//TODO
}


hook_method<unsigned long (CNPCStateUpdater::*)(unsigned long inputType, int& pc)> CNPCStateUpdater::_IsInputOccured(SERVER, "CNPCStateUpdater::IsInputOccured");
unsigned long CNPCStateUpdater::IsInputOccured(unsigned long inputType, int& pc)
{
	return (this->*_IsInputOccured)(inputType, pc);

	//TODO
}


hook_method<void (CNPCStateUpdater::*)(unsigned long outputState)> CNPCStateUpdater::_OnSearchEnemy(SERVER, "CNPCStateUpdater::OnSearchEnemy");
void CNPCStateUpdater::OnSearchEnemy(unsigned long outputState)
{
	return (this->*_OnSearchEnemy)(outputState);

	//TODO
}


hook_method<void (CNPCStateUpdater::*)(unsigned long outputState)> CNPCStateUpdater::_OnRevival(SERVER, "CNPCStateUpdater::OnRevival");
void CNPCStateUpdater::OnRevival(unsigned long outputState)
{
	return (this->*_OnRevival)(outputState);

	m_npc->m_characterInfo.virtue = 0;

	int xPos, yPos;
	if( m_npc->m_characterInfo.revivalXPos == 0 && m_npc->m_characterInfo.revivalYPos == 0 )
	{
		if( !m_npc->m_mapRes->CMapRes::GetRandomPos(xPos, yPos) )
		{
			if( m_npc->GetType() == NPC_MOB_TYPE )
			{
				CNpcMob* mob = (CNpcMob*)m_npc;
				if( mob->CNpcMob::IsBossInMap() )
				{
					Trace("Can't Regen %s, [%d, %d]", mob->m_characterInfo.accountName, xPos, yPos);
					return;
				}
			}

			return;
		}
	}
	else
	{
		xPos = m_npc->m_characterInfo.revivalXPos;
		yPos = m_npc->m_characterInfo.revivalYPos;

		if( !m_npc->m_mapRes->CMapRes::GetRandomPosByRange(xPos, yPos, m_npc->m_characterInfo.revivalXRange, m_npc->m_characterInfo.revivalYRange, m_npc->GetAccountID())
		&&  !m_npc->m_mapRes->CMapRes::GetRandomPos(xPos, yPos) )
		{
			if( m_npc->GetType() == NPC_MOB_TYPE )
			{
				CNpcMob* mob = (CNpcMob*)m_npc;
				if( mob->CNpcMob::IsBossInMap() )
				{
					Trace("Can't Regen %s, [%d, %d]", mob->m_characterInfo.accountName, xPos, yPos);
					return;
				}
			}

			return;
		}
	}

	if( !m_npc->m_npcUpdater.CNPCUpdater::InitPosition(xPos, yPos, 0) )
	{
		if( m_npc->GetType() == NPC_MOB_TYPE )
		{
			CNpcMob* mob = (CNpcMob*)m_npc;
			if( mob->CNpcMob::IsBossInMap() )
				Trace("Can't Regen %s, [%d, %d], Fail InitPosition", mob->m_characterInfo.accountName, xPos, yPos);
		}

		return;
	}

	m_npc->m_npcUpdater.CNPCUpdater::SetValidate(1);
	m_npc->CNPC::SpawnMyMob(m_npc->m_characterInfo.job);
	m_npcStateInfo.deadTime = 0;
	m_npc->CNPC::SetCurrentFSMState(outputState);
	m_npc->CNPC::InitSkill();
}


hook_method<void (CNPCStateUpdater::*)(unsigned long outputState)> CNPCStateUpdater::_OnMoveToMyOwner(SERVER, "CNPCStateUpdater::OnMoveToMyOwner");
void CNPCStateUpdater::OnMoveToMyOwner(unsigned long outputState)
{
	return (this->*_OnMoveToMyOwner)(outputState);

	//TODO
}


hook_method<void (CNPCStateUpdater::*)(unsigned long killer)> CNPCStateUpdater::_DropItem(SERVER, "CNPCStateUpdater::DropItem");
HOOKED void CNPCStateUpdater::DropItem(unsigned long killer)
{
//	return (this->*_DropItem)(killer);

	int count = 1; // CreateItemOnPosition position

	MONPARAMETER* monparam = g_monParameter->CMonParameterMgr::GetMonParameter(this->m_npc->m_characterInfo.job);
	if( monparam == NULL )
		return;

	SORTED_PCLIST sortedList[3];
	sortedList[0].limitTime = 0;
	sortedList[1].limitTime = 0;
	sortedList[2].limitTime = 0;
	sortedList[0].AID = 0;
	sortedList[0].val = 0;
	sortedList[1].AID = 0;
	sortedList[1].val = 0;
	sortedList[2].AID = 0;
	sortedList[2].val = 0;
	sortedList[0].limitTime = 0;
	sortedList[1].limitTime = 3000;
	sortedList[2].limitTime = 5000;

	if ( this->m_npc->m_characterInfo._class == NPC_CLASS_BOSS )
	{
	  sortedList[1].limitTime = 10000;
	  sortedList[2].limitTime = 20000;
	}

	m_npc->m_npcUpdater.GetPickableSortList(sortedList);

	CPC* pFirstPc = (CPC*) g_characterMgr->CCharacterMgr::FindCharacter(sortedList[0].AID, PC_TYPE);
	CPC* killerPC = (CPC*) g_characterMgr->FindCharacter(killer, PC_TYPE);
	if ( killerPC )
	{
		mystd::map<unsigned short,int> dropList = killerPC->m_pcBattle.m_dropItemOfRace_KILL[this->m_npc->m_characterInfo.race];
		for( mystd::map<unsigned short,int>::iterator it = dropList.begin(); it != dropList.end(); ++it )
		{
			if ( it->second > GetServerRandom(0, 20000) % 10000 )
			{
				CItem* v9 = this->CNPCStateUpdater::CreateItemOnPosition(it->first, count);
				if ( v9 && !(killerPC && Autoloot(pFirstPc, v9, it->second)) )
				{
					this->CNPCStateUpdater::NotifyPickupablePCToItem(v9, sortedList);
					++count;
				}
			}
		}

		mystd::map<unsigned short,int> dropItemMap;
		if( killerPC->m_pcBattle.GetDropItemOfMonster_Kill(this->m_npc->m_characterInfo.job, dropItemMap) )
		{
			for( mystd::map<unsigned short,int>::iterator it = dropItemMap.begin(); it != dropItemMap.end(); ++it )
			{
				if( it->second > GetServerRandom(0, 20000) % 1000 )
				{
					CItem* v12 = this->CNPCStateUpdater::CreateItemOnPosition(it->first, count);
					if ( v12 && !(killerPC && Autoloot(pFirstPc, v12, 10 * it->second)) ) //TODO: is this right?
					{
						this->CNPCStateUpdater::NotifyPickupablePCToItem(v12, sortedList);
						++count;
					}
				}
			}
		}

		for( int i = 1; i <= 5; ++i )
		{
			if( killerPC->m_pcBattle.m_optionInfo.receiveITMGROUP_ID[i] )
			{
				unsigned long itemID = g_zoneScript->GetITMFromGroupID(i);
				CItem* item = this->CNPCStateUpdater::CreateItemOnPosition((unsigned short)itemID, count);
				if( item != NULL )
				if( item != NULL && !(killerPC && Autoloot(pFirstPc, item, 10000)) ) //TODO: get correct droprate
				{
					this->CNPCStateUpdater::NotifyPickupablePCToItem(item, sortedList);
					++count;
				}
			}
		}
	}

	float fDropFactor = 1.0;
	bool bisBPBang = false;
	int esp_20h = 0; // droprate % bonus

	if( pFirstPc != NULL )
	{
		bisBPBang = ( pFirstPc->m_PCBangInfo.isPCBang != 0 );
		if( bisBPBang && &pFirstPc->m_PCBangInfo.isPCBang != NULL ) // never null O.o
		{
			fDropFactor = pFirstPc->m_PCBangInfo.DropFactor;
			if( fDropFactor == 0. )
				return; // no drops for anybody?
		}

		esp_20h += pFirstPc->GetEffective(EFST_CASH_RECEIVEITEM, 0);
		esp_20h += pFirstPc->m_pcBattle.m_optionInfo.receiveItem_Equip;
	}

	for( int x = 0; x < 8; ++x )
	{
		short roll = GetServerRandom(0, 20000) % 10000;
		unsigned short DropID = monparam->itemInfo[x].ITID;
		int DropValue = monparam->itemInfo[x].percent;

		if( DropValue == 0 && DropID == 512 ) // apple
			roll = 10000;

		if( DropValue < 9000 )
		{
			if( bisBPBang )
			{
				DropValue = static_cast<int>(DropValue * fDropFactor);
				if( DropValue > 9000 )
					DropValue = 9000;
			}

			if( esp_20h != 0 )
			{
				DropValue += DropValue * esp_20h / 100;
				if( DropValue > 9000 )
					DropValue = 9000;
			}
		}

		if( (int)roll <= DropValue )
		{
			CItem* eax = this->CNPCStateUpdater::CreateItemOnPosition(DropID, count);
			if( eax && !(killerPC && Autoloot(pFirstPc, eax, DropValue)) )
			{
				this->CNPCStateUpdater::NotifyPickupablePCToItem(eax, sortedList);
				++count;
			}
		}
	}

	if ( pFirstPc != NULL )
	{
		if( pFirstPc->CPC::GetCategorySecondJob(pFirstPc->m_characterInfo.job) == JT_BLACKSMITH )
		{
			if( pFirstPc->m_pcSkill.GetSkillLevel(SKID_BS_FINDINGORE,0) >= 1 )
			{
				unsigned long itemID = g_zoneScript->CZoneScript::GetITMFromGroupID(1);
				CItem* item = this->CNPCStateUpdater::CreateItemOnPosition((unsigned short)itemID, count);
				if( item != NULL && !(killerPC && Autoloot(pFirstPc, item, 10)) ) //TODO: custom eA value
					this->CNPCStateUpdater::NotifyPickupablePCToItem(item, sortedList);
			}
		}
	}

	int esp_1C = 1; // shared stack with pFirstPc from earlier, used as a counter

	mystd::list<EATING_ITEM_INVENTORY*>::iterator it = m_npc->m_eatingItem.begin();
	while( it != m_npc->m_eatingItem.end() )
	{
		ITEM_INFO itemInfo;
		int x, y;

		x = m_npc->m_pathInfo.m_moveInfo.xPos + esp_1C - 3 * (esp_1C / 3) - 1; // [ 0, +1, -1]
		y = m_npc->m_pathInfo.m_moveInfo.yPos + (esp_1C + 1) % 3 - 1;          // [+1, -1,  0]
		esp_1C++;

		int aid = m_npc->GetAccountID();
		m_npc->m_mapRes->CMapRes::GetEmptyPosition(aid, x, y);

		itemInfo.unique_identity_numberV2 = 0i64;
		itemInfo.hire_expire_date = 0;
		itemInfo.xPos = x;
		itemInfo.yPos = y;
		itemInfo.mapRes = m_npc->m_mapRes;
		itemInfo.count = (*it)->count;
		itemInfo.IsIdentified = (*it)->IsIdentified;
		itemInfo.unique_identity_numberV2 = (*it)->unique_identity_numberV2;
		itemInfo.hire_expire_date = (*it)->hire_expire_date;
		itemInfo.IsDamaged = (*it)->IsDamaged;
		itemInfo.RefiningLevel = (*it)->RefiningLevel;

		CopyEquipItemSlotInfo(&itemInfo.slot, &(*it)->slot);

		CITP* itp = g_itpMgr->GetITP((*it)->ITID);
		CItem* eax = g_characterMgr->CreateItem(itp, &itemInfo);
		if( eax && !(killerPC && Autoloot(pFirstPc, eax, 10000)) )
			this->CNPCStateUpdater::NotifyPickupablePCToItem(eax, sortedList);

		m_npc->m_eatingItemMPool.Free((*it));

		it = this->m_npc->m_eatingItem.erase(it);
	}
}


/// @param count A counter. Determines the precise location of where the item will appear.
hook_method<CItem* (CNPCStateUpdater::*)(unsigned short itmID, int count)> CNPCStateUpdater::_CreateItemOnPosition(SERVER, "CNPCStateUpdater::CreateItemOnPosition");
CItem* CNPCStateUpdater::CreateItemOnPosition(unsigned short itmID, int count)
{
	return (this->*_CreateItemOnPosition)(itmID, count);

	if( this->m_npc->CCharacter::m_mapRes == NULL )
		return NULL;

	CITP* v6 = g_itpMgr->CITPMgr::GetITP(itmID);
	if ( v6 == NULL )
		return NULL;

	ITEM_INFO itmInfo;
	itmInfo.unique_identity_numberV2 = 0i64;
	itmInfo.hire_expire_date = 0;
	itmInfo.count = 1;
	itmInfo.IsDamaged = 0;
	itmInfo.RefiningLevel = 0;
	itmInfo.mapRes = m_npc->CCharacter::m_mapRes;
	CopyEquipItemSlotInfo(&itmInfo.slot, NULL);
	itmInfo.IsIdentified = ( v6->IsApparel() == 0 );

	if ( count == 1 )
	{
		itmInfo.xPos = m_npc->m_pathInfo.m_moveInfo.xPos;
		itmInfo.yPos = m_npc->m_pathInfo.m_moveInfo.yPos;
	}
	else
	{
		int x = m_npc->m_pathInfo.m_moveInfo.xPos + count - 3 * (count / 3) - 1;
		int y = m_npc->m_pathInfo.m_moveInfo.yPos + (count + 1) % 3 - 1;
		unsigned int aid = m_npc->GetAccountID();
		m_npc->CCharacter::m_mapRes->CMapRes::GetEmptyPosition(aid, x, y);
		itmInfo.xPos = x;
		itmInfo.yPos = y;
	}

	CItem* v11 = g_characterMgr->CCharacterMgr::CreateItem(v6, &itmInfo);

	switch ( v6->GetType() )
	{
		case 0x4u:
		case 0x5u:
		case 0x8u:
		case 0x9u:
		case 0xBu:
		case 0xCu:
		case 0xDu:
		case 0xEu:
		case 0x12u:
			if ( v11 )
				v11->m_itemInfo.unique_identity_numberV2 = CUIDGenerator::GetObj()->CUIDGenerator::Get();
		break;
		default:
		break;
	}

	return v11;
}


hook_method<void (CNPCStateUpdater::*)(CPC* pc, unsigned long outputState)> CNPCStateUpdater::_OnMoveToItem(SERVER, "CNPCStateUpdater::OnMoveToItem");
void CNPCStateUpdater::OnMoveToItem(CPC* pc, unsigned long outputState)
{
	return (this->*_OnMoveToItem)(pc, outputState);

	//TODO
}


/// @patch dynamic mob loot memmgr - r2569
/// @patch athena-style circular mob loot list - r2570
hook_method<void (CNPCStateUpdater::*)(CPC* pc, unsigned long outputState)> CNPCStateUpdater::_OnPickUpItem(SERVER, "CNPCStateUpdater::OnPickUpItem");
HOOKED void CNPCStateUpdater::OnPickUpItem(CPC* pc, unsigned long outputState)
{
//	return (this->*_OnPickUpItem)(pc, outputState);

	CItem* item = (CItem *)g_characterMgr->CCharacterMgr::FindCharacter(m_npcStateInfo.targetItemAID, ITEM_TYPE);
	if( item != NULL )
	{
		if( m_npc->m_eatingItem.size() >= MAX_EATINGITEM )
		{// remove the entry in front (oldest one)
			EATING_ITEM_INVENTORY* e = m_npc->m_eatingItem.front();
			m_npc->m_eatingItem.pop_front();
			m_npc->m_eatingItemMPool.CMemoryMgr<EATING_ITEM_INVENTORY>::Free(e);
		}

		EATING_ITEM_INVENTORY* eating = m_npc->m_eatingItemMPool.CMemoryMgr<EATING_ITEM_INVENTORY>::Alloc();
		if( eating != NULL )
		{
			int ITID = 0;
			int count = 0;
			int isdamaged;
			int isidentified;
			int refininglevel;
			int slot1;
			int slot2;
			int slot3;
			int slot4;

			item->GetParameterValue(VAR_ITEM_ITID, ITID);
			item->GetParameterValue(VAR_ITEM_COUNT, count);
			item->GetParameterValue(VAR_ISDAMAGED, isdamaged);
			item->GetParameterValue(VAR_ISIDENTIFIED, isidentified);
			item->GetParameterValue(VAR_REFININGLEVEL, refininglevel);
			item->GetParameterValue(VAR_ITEM_SLOT1, slot1);
			item->GetParameterValue(VAR_ITEM_SLOT2, slot2);
			item->GetParameterValue(VAR_ITEM_SLOT3, slot3);
			item->GetParameterValue(VAR_ITEM_SLOT4, slot4);

			eating->ITID = ITID;
			eating->count = count;
			eating->unique_identity_numberV2 = item->m_itemInfo.unique_identity_numberV2;
			eating->hire_expire_date = item->m_itemInfo.hire_expire_date;
			eating->IsDamaged = ( isdamaged != 0 );
			eating->IsIdentified = ( isidentified != 0 );
			eating->RefiningLevel = refininglevel;
			eating->slot.info[0] = slot1;
			eating->slot.info[1] = slot2;
			eating->slot.info[2] = slot3;
			eating->slot.info[3] = slot4;

			m_npc->m_eatingItem.push_back(eating);
		}

		g_characterMgr->CCharacterMgr::RemoveCharacter(item);
	}

	m_npc->CNPC::SetCurrentFSMState(0);
}


hook_method<void (CNPCStateUpdater::*)(CPC* pc, unsigned long outputState)> CNPCStateUpdater::_OnStopMove(SERVER, "CNPCStateUpdater::OnStopMove");
void CNPCStateUpdater::OnStopMove(CPC* pc, unsigned long outputState)
{
	return (this->*_OnStopMove)(pc, outputState);

	//TODO
}


hook_method<void (CNPCStateUpdater::*)(unsigned long outputState)> CNPCStateUpdater::_OnRevengeRandom(SERVER, "CNPCStateUpdater::OnRevengeRandom");
void CNPCStateUpdater::OnRevengeRandom(unsigned long outputState)
{
	return (this->*_OnRevengeRandom)(outputState);

	//TODO
}


hook_method<void (CNPCStateUpdater::*)(CPC* pc, unsigned long outputState)> CNPCStateUpdater::_OnChangeEnemy(SERVER, "CNPCStateUpdater::OnChangeEnemy");
void CNPCStateUpdater::OnChangeEnemy(CPC* pc, unsigned long outputState)
{
	return (this->*_OnChangeEnemy)(pc, outputState);

	//TODO
}


hook_method<bool (CNPCStateUpdater::*)(unsigned long killer)> CNPCStateUpdater::_DisappearBattleFieldMonster(SERVER, "CNPCStateUpdater::DisappearBattleFieldMonster");
bool CNPCStateUpdater::DisappearBattleFieldMonster(unsigned long killer)
{
	return (this->*_DisappearBattleFieldMonster)(killer);

	//TODO
}


hook_method<int (CNPCStateUpdater::*)(void)> CNPCStateUpdater::_IsFSMDependent(SERVER, "CNPCStateUpdater::IsFSMDependent");
int CNPCStateUpdater::IsFSMDependent(void)
{
	return (this->*_IsFSMDependent)();

	//TODO
}
