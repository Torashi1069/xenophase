#include "CharacterMgr.h"
#include "CITP.hpp"
#include "CITPMgr.hpp"
#include "CMsg.hpp"
#include "NpcEvt.h"
#include "Common/Packet.h"
#include "shared.h" // Trace()
#include "struct.hpp"


CNpcEvt::CNpcEvt(void) // line 29
{
	m_type = NPC_EVT_TYPE;
}


CNpcEvt::~CNpcEvt(void) // line 35
{
}


hook_method<void (CNpcEvt::*)(void)> CNpcEvt::_OnProcess(SERVER, "CNpcEvt::OnProcess");
void CNpcEvt::OnProcess(void) // line 62
{
	return (this->*_OnProcess)();

	//TODO
}


hook_method<int (CNpcEvt::*)(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4)> CNpcEvt::_OnMsg(SERVER, "CNpcEvt::OnMsg");
int CNpcEvt::OnMsg(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4)
{
	return (this->*_OnMsg)(sender, receiver, msgID, par1, par2, par3, par4);

	//TODO
}


hook_method<int (CNpcEvt::*)(void)> CNpcEvt::_GetEmblemVersion(SERVER, "CNpcEvt::GetEmblemVersion");
int CNpcEvt::GetEmblemVersion(void)
{
	return (this->*_GetEmblemVersion)();

	//TODO
}


hook_method<int (CNpcEvt::*)(unsigned short ITID)> CNpcEvt::_IsSellItem(SERVER, "CNpcEvt::IsSellItem");
int CNpcEvt::IsSellItem(unsigned short ITID)
{
	return (this->*_IsSellItem)(ITID);

	//TODO
}


hook_method<void (CNpcEvt::*)(unsigned long senderAID, unsigned long receiverAID, CMsg* msg, unsigned long par1, unsigned long par2)> CNpcEvt::_OnMsgFromNPCServer(SERVER, "CNpcEvt::OnMsgFromNPCServer");
void CNpcEvt::OnMsgFromNPCServer(unsigned long senderAID, unsigned long receiverAID, CMsg* msg, unsigned long par1, unsigned long par2)
{
	return (this->*_OnMsgFromNPCServer)(senderAID, receiverAID, msg, par1, par2);

	if( msg == NULL )
		return;

	switch( msg->CMsg::GetMsgID() )
	{
	case 9u: Trace("NPC2ZMSG_SETARENAEVENTSIZE%d\n", msg->par1); m_arenaEventSize = msg->par1; break;
	case 0xAu: Trace("NPC2ZMSG_MAKEWAITINGROOM\n"); this->CNpcEvt::OnMakeWaitingRoom(msg->par1, msg->par2, msg->par3); break;
	case 0xBu: Trace("NPC2ZMSG_ENABLEARENA\n"); m_isArenaPossible = 1; break;
	case 0xCu: Trace("NPC2ZMSG_DISABLEARENA\n"); m_isArenaPossible = 0; break;
	case 0xDu: Trace("NPC2ZMSG_WARPWAITINGPCTOARENA\n"); this->CNpcEvt::OnWarpWaitingPCTOARENA(msg); break;
	case 0xEu: Trace("NPC2ZMSG_RESETMYMOB\n"); this->CNPC::OnResetMyMob(); break;
	case 0xFu: Trace("NPC2ZMSG_WARPALLPCINTHEMAP\n"); this->CNpcEvt::OnWarpAllPCInTheMap(msg); break;
	case 0x10u: this->CNpcEvt::OnBroadcastInthemap(msg); break;
	case 0x3Cu: // fall through
	case 0x3Du: this->CNpcEvt::OnBroadcast(msg); break;
	case 0x14u: this->CNpcEvt::OnOpenDiaLog(msg); break;
	case 0x11u: this->CNPC::Enable(); break;
	case 0x12u: this->CNPC::Disable(); break;
	case 0x15u: this->CNpcEvt::OnMapMove(msg); break;
	case 0x16u: this->CNpcEvt::OnDisableItemMove(msg); break;
	case 0x17u: this->CNpcEvt::OnEnableItemMove(msg); break;
	case 0x18u: this->CNpcEvt::OnSuccessRefItem(senderAID, msg); break;
	case 0x19u: this->CNpcEvt::OnFailedRefItem(senderAID, msg); break;
	case 0x1Bu: this->CNpcEvt::OnSetEffectState(senderAID, msg->par2); break;
	case 0x1Cu: this->CNpcEvt::OnSetFeeZeny(senderAID, msg->par1); break;
	case 0x1Du: this->CNpcEvt::OnSetFeeItem(senderAID, msg->par1, msg->par2); break;
	case 0x1Eu: this->CNpcEvt::OnSetLevel(senderAID, msg->par1, msg->par2); break;
	case 0x1Fu: this->CNpcEvt::OnSetExJob(senderAID, msg->par1); break;
	case 0x20u: this->CNpcEvt::OnChangeMoney(senderAID, msg->par1); break;
	case 0x21u: this->CNpcEvt::OnResetStat(senderAID); break;
	case 0x22u: this->CNpcEvt::OnResetSkill(senderAID); break;
	case 0x26u: this->CNpcEvt::OnShowImage(senderAID, msg->par1, msg->par2); break;
	case 0x27u: this->CNpcEvt::OnChangePalete(senderAID, msg->par1, msg->par2); break;
	case 0x28u: this->CNpcEvt::OnCompass(senderAID, msg->par1, msg->par2, msg->par3, msg->par4, msg->par5); break;
	case 0x29u: this->CNpcEvt::OnCheckPoint(senderAID, msg->par1, msg->par2, msg->par3); break;
	case 0x2Bu: this->CNpcEvt::OnWaitDialog(senderAID); break;
	case 0x2Cu: this->CNpcEvt::OnCloseDialog(senderAID); break;
	case 0x2Du: this->CNpcEvt::OnSetItem(senderAID, msg->par1, msg->par2); break;
	case 0x2Eu: this->CNpcEvt::OnChangeItem(senderAID, msg->par1, msg->par2, msg->par3); break;
	case 0x2Fu: g_characterMgr->CCharacterMgr::SendMsg(this, senderAID, 79, msg->par1, msg->par2, 0, 0); break;
	case 0x30u: this->CNpcEvt::OnChangeVar(senderAID, msg->par1, msg->par2); break;
	case 0x31u: this->CNpcEvt::OnDLG_Write(senderAID); break;
	case 0x32u: this->CNpcEvt::OnNude(senderAID); break;
	case 0x33u: this->CNpcEvt::OnCartOn(senderAID); break;
	case 0x34u: this->CNpcEvt::OnNotifyStoredItem(senderAID); break;
	case 0x35u: this->CNpcEvt::OnMenu(senderAID, msg->par1, msg->par2); break;
	case 0x36u: this->CNpcEvt::OnTradeNpcCommandRegister(senderAID, msg->par1, msg->par2); break;
	case 0x39u: this->CNpcEvt::OnShowDigit(senderAID, msg->par1); break;
	case 0x3Au: this->CNpcEvt::OnEnableSkill(senderAID, msg->par1, msg->par2); break;
	case 0x3Bu: this->CNpcEvt::OnDisableSkill(senderAID, msg->par1); break;
	case 0x3Eu: this->CNpcEvt::OnSound(senderAID, msg); break;
	case 0x3Fu: this->CNpcEvt::OnDLG_WriteStr(senderAID); break;
	case 0x40u: g_characterMgr->CCharacterMgr::SendMsg(this, senderAID, 61, msg->par1, 0, 0, 0); break;
	case 0x41u: this->CNpcEvt::UseSkillToPC(senderAID, receiverAID, msg->par1, msg->par2, msg->par3, msg->par4); break;
	case 0x42u: this->CNpcEvt::OnCashTradeNpcCommandRegister(receiverAID, msg); break;
	case 0x43u: this->CNpcEvt::OnCashItemList(senderAID, msg); break;
	case 0x47u: this->CNpcEvt::OnReloadMobileEvent(senderAID, msg); break;
	case 0x48u: this->CNpcEvt::OnEventItem(senderAID, msg); break;
	case 0x4Eu: // fall through
	case 0x4Fu: this->CNpcEvt::OnMyMobSkillUse(receiverAID, msg); break;
	case 0x50u: this->CNpcEvt::OnWideMobSkillUse(receiverAID, msg, par1, par2); break;
	case 0x51u: this->CNpcEvt::OnWideMobSkillUse2(receiverAID, msg); break;
	case 0x52u: this->CNpcEvt::OnGetItemSocket(senderAID, msg, par1); break;
	case 0x53u: this->CNpcEvt::OnNonSlotGetItemSocket(senderAID, msg, par1); break;
	default:
		return;
	}
}


hook_method<int (CNpcEvt::*)(void)> CNpcEvt::_IsArenaPossible(SERVER, "CNpcEvt::IsArenaPossible");
int CNpcEvt::IsArenaPossible(void)
{
	return (this->*_IsArenaPossible)();

	//TODO
}


//hook_method<void (CNpcEvt::*)(int num)> CNpcEvt::_SetGraffiti(SERVER, "CNpcEvt::SetGraffiti");
void CNpcEvt::SetGraffiti(int num)
{
//	return (this->*_SetGraffiti)(num);

	m_flagGraffitiNum = num;
}


hook_method<bool (CNpcEvt::*)(unsigned long id)> CNpcEvt::_IsTouchObject(SERVER, "CNpcEvt::IsTouchObject");
bool CNpcEvt::IsTouchObject(unsigned long id)
{
	return (this->*_IsTouchObject)(id);

	//TODO
}


hook_method<void (CNpcEvt::*)(unsigned long id)> CNpcEvt::_AddTouchObjects(SERVER, "CNpcEvt::AddTouchObjects");
void CNpcEvt::AddTouchObjects(unsigned long id)
{
	return (this->*_AddTouchObjects)(id);

	//TODO
}


hook_method<void (CNpcEvt::*)(void)> CNpcEvt::_CheckTouchObjects(SERVER, "CNpcEvt::CheckTouchObjects");
void CNpcEvt::CheckTouchObjects(void)
{
	return (this->*_CheckTouchObjects)();

	//TODO
}


hook_method<void (CNpcEvt::*)(void)> CNpcEvt::_InitCore(SERVER, "CNpcEvt::InitCore");
void CNpcEvt::InitCore(void)
{
	return (this->*_InitCore)();

	//TODO
}


//hook_method<void (CNpcEvt::*)(CMsg* msg)> CNpcEvt::_AddSkill(SERVER, "CNpcEvt::AddSkill");
void CNpcEvt::AddSkill(CMsg* msg)
{
//	return (this->*_AddSkill)(msg);

	return;
}


//hook_method<void (CNpcEvt::*)(int size)> CNpcEvt::_SetArenaEventsize(SERVER, "CNpcEvt::SetArenaEventsize");
void CNpcEvt::SetArenaEventsize(int size)
{
//	return (this->*_SetArenaEventsize)(size);

	m_arenaEventSize = size;
}


hook_method<void (CNpcEvt::*)(int len, int bufpointer, int limitSize)> CNpcEvt::_OnMakeWaitingRoom(SERVER, "CNpcEvt::OnMakeWaitingRoom");
void CNpcEvt::OnMakeWaitingRoom(int len, int bufpointer, int limitSize)
{
	return (this->*_OnMakeWaitingRoom)(len, bufpointer, limitSize);

	//TODO
}


//hook_method<void (CNpcEvt::*)(void)> CNpcEvt::_EnableArena(SERVER, "CNpcEvt::EnableArena");
void CNpcEvt::EnableArena(void)
{
//	return (this->*_EnableArena)();

	m_isArenaPossible = 1;
}


//hook_method<void (CNpcEvt::*)(void)> CNpcEvt::_DisableArena(SERVER, "CNpcEvt::DisableArena");
void CNpcEvt::DisableArena(void)
{
//	return (this->*_DisableArena)();

	m_isArenaPossible = 0;
}


hook_method<void (CNpcEvt::*)(CMsg* msg)> CNpcEvt::_OnWarpWaitingPCTOARENA(SERVER, "CNpcEvt::OnWarpWaitingPCTOARENA");
void CNpcEvt::OnWarpWaitingPCTOARENA(CMsg* msg)
{
	return (this->*_OnWarpWaitingPCTOARENA)(msg);

	//TODO
}


hook_method<void (CNpcEvt::*)(CMsg* msg)> CNpcEvt::_OnWarpAllPCInTheMap(SERVER, "CNpcEvt::OnWarpAllPCInTheMap");
void CNpcEvt::OnWarpAllPCInTheMap(CMsg* msg)
{
	return (this->*_OnWarpAllPCInTheMap)(msg);

	//TODO
}


hook_method<void (CNpcEvt::*)(CMsg* msg)> CNpcEvt::_OnBroadcastInthemap(SERVER, "CNpcEvt::OnBroadcastInthemap");
void CNpcEvt::OnBroadcastInthemap(CMsg* msg)
{
	return (this->*_OnBroadcastInthemap)(msg);

	//TODO
}


hook_method<void (CNpcEvt::*)(CMsg* msg)> CNpcEvt::_OnBroadcast(SERVER, "CNpcEvt::OnBroadcast");
void CNpcEvt::OnBroadcast(CMsg* msg)
{
	return (this->*_OnBroadcast)(msg);

	//TODO
}


hook_method<void (CNpcEvt::*)(CMsg* msg)> CNpcEvt::_OnOpenDiaLog(SERVER, "CNpcEvt::OnOpenDiaLog");
void CNpcEvt::OnOpenDiaLog(CMsg* msg)
{
	return (this->*_OnOpenDiaLog)(msg);

	//TODO
}


hook_method<void (CNpcEvt::*)(CMsg* msg)> CNpcEvt::_OnMapMove(SERVER, "CNpcEvt::OnMapMove");
void CNpcEvt::OnMapMove(CMsg* msg)
{
	return (this->*_OnMapMove)(msg);

	//TODO
}


hook_method<void (CNpcEvt::*)(CMsg* msg)> CNpcEvt::_OnDisableItemMove(SERVER, "CNpcEvt::OnDisableItemMove");
void CNpcEvt::OnDisableItemMove(CMsg* msg)
{
	return (this->*_OnDisableItemMove)(msg);

	//TODO
}


hook_method<void (CNpcEvt::*)(CMsg* msg)> CNpcEvt::_OnEnableItemMove(SERVER, "CNpcEvt::OnEnableItemMove");
void CNpcEvt::OnEnableItemMove(CMsg* msg)
{
	return (this->*_OnEnableItemMove)(msg);

	//TODO
}


hook_method<void (CNpcEvt::*)(int receiverAID, CMsg* msg)> CNpcEvt::_OnSuccessRefItem(SERVER, "CNpcEvt::OnSuccessRefItem");
void CNpcEvt::OnSuccessRefItem(int receiverAID, CMsg* msg)
{
	return (this->*_OnSuccessRefItem)(receiverAID, msg);

	//TODO
}


hook_method<void (CNpcEvt::*)(int receiverAID, CMsg* msg)> CNpcEvt::_OnFailedRefItem(SERVER, "CNpcEvt::OnFailedRefItem");
void CNpcEvt::OnFailedRefItem(int receiverAID, CMsg* msg)
{
	return (this->*_OnFailedRefItem)(receiverAID, msg);

	//TODO
}


hook_method<void (CNpcEvt::*)(int senderAID, int enu)> CNpcEvt::_OnSetEffectState(SERVER, "CNpcEvt::OnSetEffectState");
void CNpcEvt::OnSetEffectState(int senderAID, int enu)
{
	return (this->*_OnSetEffectState)(senderAID, enu);

	//TODO
}


hook_method<void (CNpcEvt::*)(int senderAID, int zeny)> CNpcEvt::_OnSetFeeZeny(SERVER, "CNpcEvt::OnSetFeeZeny");
void CNpcEvt::OnSetFeeZeny(int senderAID, int zeny)
{
	return (this->*_OnSetFeeZeny)(senderAID, zeny);

	//TODO
}


hook_method<void (CNpcEvt::*)(int senderAID, int ITID, int count)> CNpcEvt::_OnSetFeeItem(SERVER, "CNpcEvt::OnSetFeeItem");
void CNpcEvt::OnSetFeeItem(int senderAID, int ITID, int count)
{
	return (this->*_OnSetFeeItem)(senderAID, ITID, count);

	//TODO
}


hook_method<void (CNpcEvt::*)(int senderAID, int lowLevel, int highLevel)> CNpcEvt::_OnSetLevel(SERVER, "CNpcEvt::OnSetLevel");
void CNpcEvt::OnSetLevel(int senderAID, int lowLevel, int highLevel)
{
	return (this->*_OnSetLevel)(senderAID, lowLevel, highLevel);

	//TODO
}


hook_method<void (CNpcEvt::*)(int senderAID, int job)> CNpcEvt::_OnSetExJob(SERVER, "CNpcEvt::OnSetExJob");
void CNpcEvt::OnSetExJob(int senderAID, int job)
{
	return (this->*_OnSetExJob)(senderAID, job);

	//TODO
}


hook_method<void (CNpcEvt::*)(int senderAID, int amount)> CNpcEvt::_OnChangeMoney(SERVER, "CNpcEvt::OnChangeMoney");
void CNpcEvt::OnChangeMoney(int senderAID, int amount)
{
	return (this->*_OnChangeMoney)(senderAID, amount);

	//TODO
}


hook_method<void (CNpcEvt::*)(int senderAID)> CNpcEvt::_OnResetStat(SERVER, "CNpcEvt::OnResetStat");
void CNpcEvt::OnResetStat(int senderAID)
{
	return (this->*_OnResetStat)(senderAID);

	//TODO
}


hook_method<void (CNpcEvt::*)(int senderAID)> CNpcEvt::_OnResetSkill(SERVER, "CNpcEvt::OnResetSkill");
void CNpcEvt::OnResetSkill(int senderAID)
{
	return (this->*_OnResetSkill)(senderAID);

	//TODO
}


hook_method<void (CNpcEvt::*)(unsigned long senderAID, int type, int imageName)> CNpcEvt::_OnShowImage(SERVER, "CNpcEvt::OnShowImage");
void CNpcEvt::OnShowImage(unsigned long senderAID, int type, int imageName)
{
	return (this->*_OnShowImage)(senderAID, type, imageName);

	//TODO
}


hook_method<void (CNpcEvt::*)(unsigned long pcID, int where, int type)> CNpcEvt::_OnChangePalete(SERVER, "CNpcEvt::OnChangePalete");
void CNpcEvt::OnChangePalete(unsigned long pcID, int where, int type)
{
	return (this->*_OnChangePalete)(pcID, where, type);

	//TODO
}


hook_method<void (CNpcEvt::*)(unsigned long senderAID, int id, int x, int y, int type, int color)> CNpcEvt::_OnCompass(SERVER, "CNpcEvt::OnCompass");
void CNpcEvt::OnCompass(unsigned long senderAID, int id, int x, int y, int type, int color)
{
	return (this->*_OnCompass)(senderAID, id, x, y, type, color);

	//TODO
}


hook_method<void (CNpcEvt::*)(unsigned long senderAID, int x, int y, int mapName)> CNpcEvt::_OnCheckPoint(SERVER, "CNpcEvt::OnCheckPoint");
void CNpcEvt::OnCheckPoint(unsigned long senderAID, int x, int y, int mapName)
{
	return (this->*_OnCheckPoint)(senderAID, x, y, mapName);

	//TODO
}


hook_method<void (CNpcEvt::*)(unsigned long senderAID)> CNpcEvt::_OnWaitDialog(SERVER, "CNpcEvt::OnWaitDialog");
void CNpcEvt::OnWaitDialog(unsigned long senderAID)
{
	return (this->*_OnWaitDialog)(senderAID);

	//TODO
}


hook_method<void (CNpcEvt::*)(unsigned long senderAID)> CNpcEvt::_OnCloseDialog(SERVER, "CNpcEvt::OnCloseDialog");
void CNpcEvt::OnCloseDialog(unsigned long senderAID)
{
	return (this->*_OnCloseDialog)(senderAID);

	//TODO
}


hook_method<void (CNpcEvt::*)(unsigned long senderAID, int ITID, int num)> CNpcEvt::_OnSetItem(SERVER, "CNpcEvt::OnSetItem");
void CNpcEvt::OnSetItem(unsigned long senderAID, int ITID, int num)
{
	return (this->*_OnSetItem)(senderAID, ITID, num);

	//TODO
}


hook_method<void (CNpcEvt::*)(unsigned long senderAID, int ITID, int num, int event)> CNpcEvt::_OnChangeItem(SERVER, "CNpcEvt::OnChangeItem");
void CNpcEvt::OnChangeItem(unsigned long senderAID, int ITID, int num, int event)
{
	return (this->*_OnChangeItem)(senderAID, ITID, num, event);

	//TODO
}


hook_method<void (CNpcEvt::*)(unsigned long senderAID, CMsg* msg, int event)> CNpcEvt::_OnGetItemSocket(SERVER, "CNpcEvt::OnGetItemSocket");
void CNpcEvt::OnGetItemSocket(unsigned long senderAID, CMsg* msg, int event)
{
	return (this->*_OnGetItemSocket)(senderAID, msg, event);

	//TODO
}


hook_method<void (CNpcEvt::*)(unsigned long senderAID, CMsg* msg, int event)> CNpcEvt::_OnNonSlotGetItemSocket(SERVER, "CNpcEvt::OnNonSlotGetItemSocket");
void CNpcEvt::OnNonSlotGetItemSocket(unsigned long senderAID, CMsg* msg, int event)
{
	return (this->*_OnNonSlotGetItemSocket)(senderAID, msg, event);

	//TODO
}


hook_method<void (CNpcEvt::*)(unsigned long senderAID, int var, int num)> CNpcEvt::_OnChangeVar(SERVER, "CNpcEvt::OnChangeVar");
void CNpcEvt::OnChangeVar(unsigned long senderAID, int var, int num)
{
	return (this->*_OnChangeVar)(senderAID, var, num);

	//TODO
}


hook_method<void (CNpcEvt::*)(unsigned long senderAID)> CNpcEvt::_OnDLG_Write(SERVER, "CNpcEvt::OnDLG_Write");
void CNpcEvt::OnDLG_Write(unsigned long senderAID)
{
	return (this->*_OnDLG_Write)(senderAID);

	//TODO
}


hook_method<void (CNpcEvt::*)(unsigned long senderAID)> CNpcEvt::_OnNude(SERVER, "CNpcEvt::OnNude");
void CNpcEvt::OnNude(unsigned long senderAID)
{
	return (this->*_OnNude)(senderAID);

	//TODO
}


hook_method<void (CNpcEvt::*)(unsigned long senderAID)> CNpcEvt::_OnCartOn(SERVER, "CNpcEvt::OnCartOn");
void CNpcEvt::OnCartOn(unsigned long senderAID)
{
	return (this->*_OnCartOn)(senderAID);

	//TODO
}


hook_method<void (CNpcEvt::*)(unsigned long senderAID)> CNpcEvt::_OnNotifyStoredItem(SERVER, "CNpcEvt::OnNotifyStoredItem");
void CNpcEvt::OnNotifyStoredItem(unsigned long senderAID)
{
	return (this->*_OnNotifyStoredItem)(senderAID);

	//TODO
}


hook_method<void (CNpcEvt::*)(unsigned long senderAID, int len, int str)> CNpcEvt::_OnMenu(SERVER, "CNpcEvt::OnMenu");
void CNpcEvt::OnMenu(unsigned long senderAID, int len, int str)
{
	return (this->*_OnMenu)(senderAID, len, str);

	//TODO
}


hook_method<void (CNpcEvt::*)(unsigned long senderAID, int type, int ITID)> CNpcEvt::_OnTradeNpcCommandRegister(SERVER, "CNpcEvt::OnTradeNpcCommandRegister");
void CNpcEvt::OnTradeNpcCommandRegister(unsigned long senderAID, int type, int ITID)
{
	return (this->*_OnTradeNpcCommandRegister)(senderAID, type, ITID);

	//TODO
}


hook_method<void (CNpcEvt::*)(unsigned long senderAID, int time)> CNpcEvt::_OnShowDigit(SERVER, "CNpcEvt::OnShowDigit");
void CNpcEvt::OnShowDigit(unsigned long senderAID, int time)
{
	return (this->*_OnShowDigit)(senderAID, time);

	//TODO
}


hook_method<void (CNpcEvt::*)(unsigned long senderAID, int skill, int level)> CNpcEvt::_OnEnableSkill(SERVER, "CNpcEvt::OnEnableSkill");
void CNpcEvt::OnEnableSkill(unsigned long senderAID, int skill, int level)
{
	return (this->*_OnEnableSkill)(senderAID, skill, level);

	//TODO
}


hook_method<void (CNpcEvt::*)(unsigned long senderAID, int skill)> CNpcEvt::_OnDisableSkill(SERVER, "CNpcEvt::OnDisableSkill");
void CNpcEvt::OnDisableSkill(unsigned long senderAID, int skill)
{
	return (this->*_OnDisableSkill)(senderAID, skill);

	//TODO
}


hook_method<void (CNpcEvt::*)(unsigned long senderAID, CMsg* msg)> CNpcEvt::_OnSound(SERVER, "CNpcEvt::OnSound");
void CNpcEvt::OnSound(unsigned long senderAID, CMsg* msg)
{
	return (this->*_OnSound)(senderAID, msg);

	//TODO
}


hook_method<void (CNpcEvt::*)(unsigned long senderAID)> CNpcEvt::_OnDLG_WriteStr(SERVER, "CNpcEvt::OnDLG_WriteStr");
void CNpcEvt::OnDLG_WriteStr(unsigned long senderAID)
{
	return (this->*_OnDLG_WriteStr)(senderAID);

	//TODO
}


hook_method<void (CNpcEvt::*)(unsigned long senderAID, unsigned long receiverAID, int SKID, int skLevel, int statPoint, int cLevel)> CNpcEvt::_UseSkillToPC(SERVER, "CNpcEvt::UseSkillToPC");
void CNpcEvt::UseSkillToPC(unsigned long senderAID, unsigned long receiverAID, int SKID, int skLevel, int statPoint, int cLevel)
{
	return (this->*_UseSkillToPC)(senderAID, receiverAID, SKID, skLevel, statPoint, cLevel);

	//TODO
}


hook_method<void (CNpcEvt::*)(unsigned long receiverAID, CMsg* msg)> CNpcEvt::_OnCashTradeNpcCommandRegister(SERVER, "CNpcEvt::OnCashTradeNpcCommandRegister");
void CNpcEvt::OnCashTradeNpcCommandRegister(unsigned long receiverAID, CMsg* msg)
{
	return (this->*_OnCashTradeNpcCommandRegister)(receiverAID, msg);

	const char* str = (const char*)msg->par1;

	if( str == NULL || str == "" ) //FIXME: pointer comparison
		return;

	if( m_npcType != CASHTRADER_NPC )
		return;

	CNPC* npc = (CNPC*)g_characterMgr->CCharacterMgr::FindCharacter(receiverAID, NPC_TYPE);
	if( npc == NULL )
		return;

	NpcInfo* info = npc->CNPC::GetCharacterInfo();
	if( info == NULL )
		return;

	strcpy(info->cashShopName, str);

	mystd::vector<CCashItemShopScript::CProduct>* data = CCashItemShopScript::GetObj()->CCashItemShopScript::GetStandMapPtr(str);
	if( data == NULL )
		return;

	for( mystd::vector<CCashItemShopScript::CProduct>::iterator it = data->begin(); it != data->end(); ++it )
		m_cashMap.push_back(*it);
}


hook_method<void (CNpcEvt::*)(unsigned long senderAID, CMsg* msg)> CNpcEvt::_OnCashItemList(SERVER, "CNpcEvt::OnCashItemList");
void CNpcEvt::OnCashItemList(unsigned long senderAID, CMsg* msg)
{
	return (this->*_OnCashItemList)(senderAID, msg);

	//TODO
}


//hook_method<void (CNpcEvt::*)(unsigned long pcID, CMsg* msg)> CNpcEvt::_OnUpdateContectPcList(SERVER, "CNpcEvt::OnUpdateContectPcList");
void CNpcEvt::OnUpdateContectPcList(unsigned long pcID, CMsg* msg)
{
//	return (this->*_OnUpdateContectPcList)(pcID, msg);

	return;
}


//hook_method<void (CNpcEvt::*)(unsigned long npcId, CMsg* msg)> CNpcEvt::_OnAddMoveNpcCommand(SERVER, "CNpcEvt::OnAddMoveNpcCommand");
void CNpcEvt::OnAddMoveNpcCommand(unsigned long npcId, CMsg* msg)
{
//	return (this->*_OnAddMoveNpcCommand)(npcId, msg);

	return;
}


hook_method<void (CNpcEvt::*)(unsigned long pcID, CMsg* msg)> CNpcEvt::_OnReloadMobileEvent(SERVER, "CNpcEvt::OnReloadMobileEvent");
void CNpcEvt::OnReloadMobileEvent(unsigned long pcID, CMsg* msg)
{
	return (this->*_OnReloadMobileEvent)(pcID, msg);

	//TODO
}


hook_method<void (CNpcEvt::*)(unsigned long senderAID, CMsg* msg)> CNpcEvt::_OnEventItem(SERVER, "CNpcEvt::OnEventItem");
void CNpcEvt::OnEventItem(unsigned long senderAID, CMsg* msg)
{
	return (this->*_OnEventItem)(senderAID, msg);

	//TODO
}


hook_method<void (CNpcEvt::*)(unsigned long npcId, CMsg* msg)> CNpcEvt::_OnMyMobSkillUse(SERVER, "CNpcEvt::OnMyMobSkillUse");
void CNpcEvt::OnMyMobSkillUse(unsigned long npcId, CMsg* msg)
{
	return (this->*_OnMyMobSkillUse)(npcId, msg);

	//TODO
}


hook_method<void (CNpcEvt::*)(unsigned long npcId, CMsg* msg, int xPos, int yPos)> CNpcEvt::_OnWideMobSkillUse(SERVER, "CNpcEvt::OnWideMobSkillUse");
void CNpcEvt::OnWideMobSkillUse(unsigned long npcId, CMsg* msg, int xPos, int yPos)
{
	return (this->*_OnWideMobSkillUse)(npcId, msg, xPos, yPos);

	//TODO
}


hook_method<void (CNpcEvt::*)(unsigned long npcId, CMsg* msg)> CNpcEvt::_OnWideMobSkillUse2(SERVER, "CNpcEvt::OnWideMobSkillUse2");
void CNpcEvt::OnWideMobSkillUse2(unsigned long npcId, CMsg* msg)
{
	return (this->*_OnWideMobSkillUse2)(npcId, msg);

	//TODO
}


//hook_method<void (CNpcEvt::*)(int speed)> CNpcEvt::_OnMoveNpcSpeedChange(SERVER, "CNpcEvt::OnMoveNpcSpeedChange");
void CNpcEvt::OnMoveNpcSpeedChange(int speed)
{
//	return (this->*_OnMoveNpcSpeedChange)(speed);

	return;
}


//hook_method<int (CNpcEvt::*)(void)> CNpcEvt::_GetArenaEventSize(SERVER, "CNpcEvt::GetArenaEventSize");
int CNpcEvt::GetArenaEventSize(void)
{
//	return (this->*_GetArenaEventSize)();

	return m_arenaEventSize;
}


hook_method<CRoom* (CNpcEvt::*)(void)> CNpcEvt::_GetMyRoom(SERVER, "CNpcEvt::GetMyRoom");
CRoom* CNpcEvt::GetMyRoom(void)
{
	return (this->*_GetMyRoom)();

	//TODO
}


hook_method<void (CNpcEvt::*)(CCharacter* character)> CNpcEvt::_OnPurchaseItem(SERVER, "CNpcEvt::OnPurchaseItem");
void CNpcEvt::OnPurchaseItem(CCharacter* character)
{
	return (this->*_OnPurchaseItem)(character);

	int tempdiscount;
	character->GetParameterValue(VAR_DISCOUNTPERCENT, tempdiscount);

	double percent = tempdiscount / 100.0;
	if( percent <= 0.75 )
		percent = 0.75;
	float discount = (float)percent;

	char outbuf[2048];
	int outlen = 0;

	for( mystd::list<int>::const_iterator it = m_sellList.begin(); it != m_sellList.end() && outlen <= 2000; ++it )
	{
		unsigned short ITID = static_cast<unsigned short>(*it);
		CITP* itp = g_itpMgr->CITPMgr::GetITP(ITID);

		PURCHASE_ITEM puritem;
		puritem.price = itp->m_price;
		puritem.discountprice = static_cast<int>(max(1.0, discount * itp->m_price));
		puritem.type = static_cast<unsigned char>(itp->GetType());
		puritem.ITID = itp->m_ITID;

		memcpy(&outbuf[outlen], &puritem, sizeof(PURCHASE_ITEM));
		outlen += sizeof(PURCHASE_ITEM);
	}

	PACKET_ZC_PC_PURCHASE_ITEMLIST outpacket;
	outpacket.PacketType = HEADER_ZC_PC_PURCHASE_ITEMLIST;
	outpacket.PacketLength = sizeof(outpacket) + outlen;
	g_characterMgr->CCharacterMgr::SendMsg(this, character, CM_SEND_PACKET, sizeof(outpacket), (int)&outpacket, 0, 0);
	g_characterMgr->CCharacterMgr::SendMsg(this, character, CM_SEND_PACKET, outlen, (int)outbuf, 0, 0);
}


hook_method<void (CNpcEvt::*)(int par1)> CNpcEvt::_OnZNCloseDialog(SERVER, "CNpcEvt::OnZNCloseDialog");
void CNpcEvt::OnZNCloseDialog(int par1)
{
	return (this->*_OnZNCloseDialog)(par1);

	//TODO
}


hook_method<void (CNpcEvt::*)(int inputValue, unsigned long CAID)> CNpcEvt::_OnInputEditDlg(SERVER, "CNpcEvt::OnInputEditDlg");
void CNpcEvt::OnInputEditDlg(int inputValue, unsigned long CAID)
{
	return (this->*_OnInputEditDlg)(inputValue, CAID);

	//TODO
}


hook_method<void (CNpcEvt::*)(int answer, unsigned long CAID)> CNpcEvt::_OnInputEditDlgStr(SERVER, "CNpcEvt::OnInputEditDlgStr");
void CNpcEvt::OnInputEditDlgStr(int answer, unsigned long CAID)
{
	return (this->*_OnInputEditDlgStr)(answer, CAID);

	//TODO
}


hook_method<void (CNpcEvt::*)(unsigned long AID)> CNpcEvt::_OnWarpCharBetweenServer(SERVER, "CNpcEvt::OnWarpCharBetweenServer");
void CNpcEvt::OnWarpCharBetweenServer(unsigned long AID) // line 1039
{
	return (this->*_OnWarpCharBetweenServer)(AID);

	Trace("OnWarpCharBetweenServer\n");

	CPC* pc = (CPC*)g_characterMgr->CCharacterMgr::FindCharacter(AID, PC_TYPE);
	if( pc != NULL )
		pc->CPC::ServerMove();
}


hook_method<void (CNpcEvt::*)(unsigned long roomID)> CNpcEvt::_MulticastRoomNewEntry(SERVER, "CNpcEvt::MulticastRoomNewEntry");
void CNpcEvt::MulticastRoomNewEntry(unsigned long roomID) // line 1049
{
	return (this->*_MulticastRoomNewEntry)(roomID);

	//TODO
}
