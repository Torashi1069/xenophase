#pragma once
#include "CCashItemShopScript.hpp"
#include "NPC.h"
#include "std/list"
#include "std/set"
#include "std/vector"
class CRoom;


class CNpcEvt : public CNPC
{
	/* this+   0 */ public: //CNPC baseclass_0;
	/* this+1132 */ public: bool m_isSecertChshShop;
	/* this+1136 */ private: mystd::list<int> m_sellList;
	/* this+1148 */ private: mystd::vector<CCashItemShopScript::CProduct> m_cashMap;
	/* this+1164 */ private: int m_isArenaPossible;
	/* this+1168 */ private: int m_arenaEventSize;
	/* this+1172 */ private: int m_flagGraffitiNum;
	/* this+1176 */ private: mystd::set<unsigned long> m_touchObjects;

	public: CNpcEvt::CNpcEvt(void);
	public: CNpcEvt::~CNpcEvt(void);
	public: void CNpcEvt::OnProcess(void);
	public: int CNpcEvt::OnMsg(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4);
	public: int CNpcEvt::GetEmblemVersion(void);
	public: int CNpcEvt::IsSellItem(unsigned short ITID);
	public: void CNpcEvt::OnMsgFromNPCServer(unsigned long senderAID, unsigned long receiverAID, CMsg* msg, unsigned long par1, unsigned long par2);
	public: int CNpcEvt::IsArenaPossible(void);
	public: void CNpcEvt::SetGraffiti(int num);
	public: bool CNpcEvt::IsTouchObject(unsigned long id);
	public: void CNpcEvt::AddTouchObjects(unsigned long id);
	public: void CNpcEvt::CheckTouchObjects(void);
	private: void CNpcEvt::InitCore(void);
	private: void CNpcEvt::AddSkill(CMsg* msg);
	private: void CNpcEvt::SetArenaEventsize(int size);
	private: void CNpcEvt::OnMakeWaitingRoom(int len, int bufpointer, int limitSize);
	private: void CNpcEvt::EnableArena(void);
	private: void CNpcEvt::DisableArena(void);
	private: void CNpcEvt::OnWarpWaitingPCTOARENA(CMsg* msg);
	private: void CNpcEvt::OnWarpAllPCInTheMap(CMsg* msg);
	private: void CNpcEvt::OnBroadcastInthemap(CMsg* msg);
	private: void CNpcEvt::OnBroadcast(CMsg* msg);
	private: void CNpcEvt::OnOpenDiaLog(CMsg* msg);
	private: void CNpcEvt::OnMapMove(CMsg* msg);
	private: void CNpcEvt::OnDisableItemMove(CMsg* msg);
	private: void CNpcEvt::OnEnableItemMove(CMsg* msg);
	private: void CNpcEvt::OnSuccessRefItem(int receiverAID, CMsg* msg);
	private: void CNpcEvt::OnFailedRefItem(int receiverAID, CMsg* msg);
	private: void CNpcEvt::OnSetEffectState(int senderAID, int enu);
	private: void CNpcEvt::OnSetFeeZeny(int senderAID, int zeny);
	private: void CNpcEvt::OnSetFeeItem(int senderAID, int ITID, int count);
	private: void CNpcEvt::OnSetLevel(int senderAID, int lowLevel, int highLevel);
	private: void CNpcEvt::OnSetExJob(int senderAID, int job);
	private: void CNpcEvt::OnChangeMoney(int senderAID, int amount);
	private: void CNpcEvt::OnResetStat(int senderAID);
	private: void CNpcEvt::OnResetSkill(int senderAID);
	private: void CNpcEvt::OnShowImage(unsigned long senderAID, int type, int imageName);
	private: void CNpcEvt::OnChangePalete(unsigned long pcID, int where, int type);
	private: void CNpcEvt::OnCompass(unsigned long senderAID, int id, int x, int y, int type, int color);
	private: void CNpcEvt::OnCheckPoint(unsigned long senderAID, int x, int y, int mapName);
	private: void CNpcEvt::OnWaitDialog(unsigned long senderAID);
	private: void CNpcEvt::OnCloseDialog(unsigned long senderAID);
	private: void CNpcEvt::OnSetItem(unsigned long senderAID, int ITID, int num);
	private: void CNpcEvt::OnChangeItem(unsigned long senderAID, int ITID, int num, int event);
	private: void CNpcEvt::OnGetItemSocket(unsigned long senderAID, CMsg* msg, int event);
	private: void CNpcEvt::OnNonSlotGetItemSocket(unsigned long senderAID, CMsg* msg, int event);
	private: void CNpcEvt::OnChangeVar(unsigned long senderAID, int var, int num);
	private: void CNpcEvt::OnDLG_Write(unsigned long senderAID);
	private: void CNpcEvt::OnNude(unsigned long senderAID);
	private: void CNpcEvt::OnCartOn(unsigned long senderAID);
	private: void CNpcEvt::OnNotifyStoredItem(unsigned long senderAID);
	private: void CNpcEvt::OnMenu(unsigned long senderAID, int len, int str);
	private: void CNpcEvt::OnTradeNpcCommandRegister(unsigned long senderAID, int type, int ITID);
	private: void CNpcEvt::OnShowDigit(unsigned long senderAID, int time);
	private: void CNpcEvt::OnEnableSkill(unsigned long senderAID, int skill, int level);
	private: void CNpcEvt::OnDisableSkill(unsigned long senderAID, int skill);
	private: void CNpcEvt::OnSound(unsigned long senderAID, CMsg* msg);
	private: void CNpcEvt::OnDLG_WriteStr(unsigned long senderAID);
	private: void CNpcEvt::UseSkillToPC(unsigned long senderAID, unsigned long receiverAID, int SKID, int skLevel, int statPoint, int cLevel);
	private: void CNpcEvt::OnCashTradeNpcCommandRegister(unsigned long receiverAID, CMsg* msg);
	private: void CNpcEvt::OnCashItemList(unsigned long senderAID, CMsg* msg);
	private: void CNpcEvt::OnUpdateContectPcList(unsigned long pcID, CMsg* msg);
	private: void CNpcEvt::OnAddMoveNpcCommand(unsigned long npcId, CMsg* msg);
	private: void CNpcEvt::OnReloadMobileEvent(unsigned long pcID, CMsg* msg);
	private: void CNpcEvt::OnEventItem(unsigned long senderAID, CMsg* msg);
	private: void CNpcEvt::OnMyMobSkillUse(unsigned long npcId, CMsg* msg);
	private: void CNpcEvt::OnWideMobSkillUse(unsigned long npcId, CMsg* msg, int xPos, int yPos);
	private: void CNpcEvt::OnWideMobSkillUse2(unsigned long npcId, CMsg* msg);
	private: void CNpcEvt::OnMoveNpcSpeedChange(int speed);
	private: int CNpcEvt::GetArenaEventSize(void);
	private: CRoom* CNpcEvt::GetMyRoom(void);
	private: void CNpcEvt::OnPurchaseItem(CCharacter* character);
	private: void CNpcEvt::OnZNCloseDialog(int par1);
	private: void CNpcEvt::OnInputEditDlg(int inputValue, unsigned long CAID);
	private: void CNpcEvt::OnInputEditDlgStr(int answer, unsigned long CAID);
	private: void CNpcEvt::OnWarpCharBetweenServer(unsigned long AID);
	private: void CNpcEvt::MulticastRoomNewEntry(unsigned long roomID);

private:
	static hook_method<void (CNpcEvt::*)(void)> CNpcEvt::_OnProcess;
	static hook_method<int (CNpcEvt::*)(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4)> CNpcEvt::_OnMsg;
	static hook_method<int (CNpcEvt::*)(void)> CNpcEvt::_GetEmblemVersion;
	static hook_method<int (CNpcEvt::*)(unsigned short ITID)> CNpcEvt::_IsSellItem;
	static hook_method<void (CNpcEvt::*)(unsigned long senderAID, unsigned long receiverAID, CMsg* msg, unsigned long par1, unsigned long par2)> CNpcEvt::_OnMsgFromNPCServer;
	static hook_method<int (CNpcEvt::*)(void)> CNpcEvt::_IsArenaPossible;
	static hook_method<void (CNpcEvt::*)(int num)> CNpcEvt::_SetGraffiti;
	static hook_method<bool (CNpcEvt::*)(unsigned long id)> CNpcEvt::_IsTouchObject;
	static hook_method<void (CNpcEvt::*)(unsigned long id)> CNpcEvt::_AddTouchObjects;
	static hook_method<void (CNpcEvt::*)(void)> CNpcEvt::_CheckTouchObjects;
	static hook_method<void (CNpcEvt::*)(void)> CNpcEvt::_InitCore;
	static hook_method<void (CNpcEvt::*)(CMsg* msg)> CNpcEvt::_AddSkill;
	static hook_method<void (CNpcEvt::*)(int size)> CNpcEvt::_SetArenaEventsize;
	static hook_method<void (CNpcEvt::*)(int len, int bufpointer, int limitSize)> CNpcEvt::_OnMakeWaitingRoom;
	static hook_method<void (CNpcEvt::*)(void)> CNpcEvt::_EnableArena;
	static hook_method<void (CNpcEvt::*)(void)> CNpcEvt::_DisableArena;
	static hook_method<void (CNpcEvt::*)(CMsg* msg)> CNpcEvt::_OnWarpWaitingPCTOARENA;
	static hook_method<void (CNpcEvt::*)(CMsg* msg)> CNpcEvt::_OnWarpAllPCInTheMap;
	static hook_method<void (CNpcEvt::*)(CMsg* msg)> CNpcEvt::_OnBroadcastInthemap;
	static hook_method<void (CNpcEvt::*)(CMsg* msg)> CNpcEvt::_OnBroadcast;
	static hook_method<void (CNpcEvt::*)(CMsg* msg)> CNpcEvt::_OnOpenDiaLog;
	static hook_method<void (CNpcEvt::*)(CMsg* msg)> CNpcEvt::_OnMapMove;
	static hook_method<void (CNpcEvt::*)(CMsg* msg)> CNpcEvt::_OnDisableItemMove;
	static hook_method<void (CNpcEvt::*)(CMsg* msg)> CNpcEvt::_OnEnableItemMove;
	static hook_method<void (CNpcEvt::*)(int receiverAID, CMsg* msg)> CNpcEvt::_OnSuccessRefItem;
	static hook_method<void (CNpcEvt::*)(int receiverAID, CMsg* msg)> CNpcEvt::_OnFailedRefItem;
	static hook_method<void (CNpcEvt::*)(int senderAID, int enu)> CNpcEvt::_OnSetEffectState;
	static hook_method<void (CNpcEvt::*)(int senderAID, int zeny)> CNpcEvt::_OnSetFeeZeny;
	static hook_method<void (CNpcEvt::*)(int senderAID, int ITID, int count)> CNpcEvt::_OnSetFeeItem;
	static hook_method<void (CNpcEvt::*)(int senderAID, int lowLevel, int highLevel)> CNpcEvt::_OnSetLevel;
	static hook_method<void (CNpcEvt::*)(int senderAID, int job)> CNpcEvt::_OnSetExJob;
	static hook_method<void (CNpcEvt::*)(int senderAID, int amount)> CNpcEvt::_OnChangeMoney;
	static hook_method<void (CNpcEvt::*)(int senderAID)> CNpcEvt::_OnResetStat;
	static hook_method<void (CNpcEvt::*)(int senderAID)> CNpcEvt::_OnResetSkill;
	static hook_method<void (CNpcEvt::*)(unsigned long senderAID, int type, int imageName)> CNpcEvt::_OnShowImage;
	static hook_method<void (CNpcEvt::*)(unsigned long pcID, int where, int type)> CNpcEvt::_OnChangePalete;
	static hook_method<void (CNpcEvt::*)(unsigned long senderAID, int id, int x, int y, int type, int color)> CNpcEvt::_OnCompass;
	static hook_method<void (CNpcEvt::*)(unsigned long senderAID, int x, int y, int mapName)> CNpcEvt::_OnCheckPoint;
	static hook_method<void (CNpcEvt::*)(unsigned long senderAID)> CNpcEvt::_OnWaitDialog;
	static hook_method<void (CNpcEvt::*)(unsigned long senderAID)> CNpcEvt::_OnCloseDialog;
	static hook_method<void (CNpcEvt::*)(unsigned long senderAID, int ITID, int num)> CNpcEvt::_OnSetItem;
	static hook_method<void (CNpcEvt::*)(unsigned long senderAID, int ITID, int num, int event)> CNpcEvt::_OnChangeItem;
	static hook_method<void (CNpcEvt::*)(unsigned long senderAID, CMsg* msg, int event)> CNpcEvt::_OnGetItemSocket;
	static hook_method<void (CNpcEvt::*)(unsigned long senderAID, CMsg* msg, int event)> CNpcEvt::_OnNonSlotGetItemSocket;
	static hook_method<void (CNpcEvt::*)(unsigned long senderAID, int var, int num)> CNpcEvt::_OnChangeVar;
	static hook_method<void (CNpcEvt::*)(unsigned long senderAID)> CNpcEvt::_OnDLG_Write;
	static hook_method<void (CNpcEvt::*)(unsigned long senderAID)> CNpcEvt::_OnNude;
	static hook_method<void (CNpcEvt::*)(unsigned long senderAID)> CNpcEvt::_OnCartOn;
	static hook_method<void (CNpcEvt::*)(unsigned long senderAID)> CNpcEvt::_OnNotifyStoredItem;
	static hook_method<void (CNpcEvt::*)(unsigned long senderAID, int len, int str)> CNpcEvt::_OnMenu;
	static hook_method<void (CNpcEvt::*)(unsigned long senderAID, int type, int ITID)> CNpcEvt::_OnTradeNpcCommandRegister;
	static hook_method<void (CNpcEvt::*)(unsigned long senderAID, int time)> CNpcEvt::_OnShowDigit;
	static hook_method<void (CNpcEvt::*)(unsigned long senderAID, int skill, int level)> CNpcEvt::_OnEnableSkill;
	static hook_method<void (CNpcEvt::*)(unsigned long senderAID, int skill)> CNpcEvt::_OnDisableSkill;
	static hook_method<void (CNpcEvt::*)(unsigned long senderAID, CMsg* msg)> CNpcEvt::_OnSound;
	static hook_method<void (CNpcEvt::*)(unsigned long senderAID)> CNpcEvt::_OnDLG_WriteStr;
	static hook_method<void (CNpcEvt::*)(unsigned long senderAID, unsigned long receiverAID, int SKID, int skLevel, int statPoint, int cLevel)> CNpcEvt::_UseSkillToPC;
	static hook_method<void (CNpcEvt::*)(unsigned long receiverAID, CMsg* msg)> CNpcEvt::_OnCashTradeNpcCommandRegister;
	static hook_method<void (CNpcEvt::*)(unsigned long senderAID, CMsg* msg)> CNpcEvt::_OnCashItemList;
	static hook_method<void (CNpcEvt::*)(unsigned long pcID, CMsg* msg)> CNpcEvt::_OnUpdateContectPcList;
	static hook_method<void (CNpcEvt::*)(unsigned long npcId, CMsg* msg)> CNpcEvt::_OnAddMoveNpcCommand;
	static hook_method<void (CNpcEvt::*)(unsigned long pcID, CMsg* msg)> CNpcEvt::_OnReloadMobileEvent;
	static hook_method<void (CNpcEvt::*)(unsigned long senderAID, CMsg* msg)> CNpcEvt::_OnEventItem;
	static hook_method<void (CNpcEvt::*)(unsigned long npcId, CMsg* msg)> CNpcEvt::_OnMyMobSkillUse;
	static hook_method<void (CNpcEvt::*)(unsigned long npcId, CMsg* msg, int xPos, int yPos)> CNpcEvt::_OnWideMobSkillUse;
	static hook_method<void (CNpcEvt::*)(unsigned long npcId, CMsg* msg)> CNpcEvt::_OnWideMobSkillUse2;
	static hook_method<void (CNpcEvt::*)(int speed)> CNpcEvt::_OnMoveNpcSpeedChange;
	static hook_method<int (CNpcEvt::*)(void)> CNpcEvt::_GetArenaEventSize;
	static hook_method<CRoom* (CNpcEvt::*)(void)> CNpcEvt::_GetMyRoom;
	static hook_method<void (CNpcEvt::*)(CCharacter* character)> CNpcEvt::_OnPurchaseItem;
	static hook_method<void (CNpcEvt::*)(int par1)> CNpcEvt::_OnZNCloseDialog;
	static hook_method<void (CNpcEvt::*)(int inputValue, unsigned long CAID)> CNpcEvt::_OnInputEditDlg;
	static hook_method<void (CNpcEvt::*)(int answer, unsigned long CAID)> CNpcEvt::_OnInputEditDlgStr;
	static hook_method<void (CNpcEvt::*)(unsigned long AID)> CNpcEvt::_OnWarpCharBetweenServer;
	static hook_method<void (CNpcEvt::*)(unsigned long roomID)> CNpcEvt::_MulticastRoomNewEntry;
};
