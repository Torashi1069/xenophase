#pragma once
#include "NPC.h"
#include "Msg.h"
class CRoom; // #include "Room.h"


class CNpcEvt : public CNPC
{
public:
	CNpcEvt();
	virtual ~CNpcEvt();

public:
	virtual void OnProcess();
	virtual int OnMsg(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4);
	virtual int GetEmblemVersion();
	BOOL IsSellItem(unsigned short ITID);
	void OnMsgFromNPCServer(unsigned long senderAID, unsigned long receiverAID, CMsg* msg, unsigned long par1, unsigned long par2);
	int IsArenaPossible();
	void SetGraffiti(int num);
	bool IsTouchObject(unsigned long id);
	void AddTouchObjects(unsigned long id);
	void CheckTouchObjects();

public:
	/* this+   0 */ //CNPC baseclass_0;
	/* this+2104 */ bool m_isSecertChshShop;

private:
	virtual void InitCore();
	void AddSkill(CMsg* msg);
	void SetArenaEventsize(int size);
	void OnMakeWaitingRoom(int len, int bufpointer, int limitSize);
	void EnableArena();
	void DisableArena();
	void OnWarpWaitingPCTOARENA(CMsg* msg);
	void OnWarpAllPCInTheMap(CMsg* msg);
	void OnBroadcastInthemap(CMsg* msg);
	void OnBroadcast(CMsg* in_pMSG);
	void OnOpenDiaLog(CMsg* msg);
	void OnMapMove(CMsg* msg);
	void OnDisableItemMove(CMsg* msg);
	void OnEnableItemMove(CMsg* msg);
	void OnSuccessRefItem(int receiverAID, CMsg* msg);
	void OnFailedRefItem(int receiverAID, CMsg* msg);
	void OnSetEffectState(int senderAID, int enu);
	void OnSetFeeZeny(int senderAID, int zeny);
	void OnSetFeeItem(int senderAID, int ITID, int count);
	void OnSetLevel(int senderAID, int lowLevel, int highLevel);
	void OnSetExJob(int senderAID, int job);
	void OnChangeMoney(int senderAID, int amount);
	void OnResetStat(int senderAID);
	void OnResetSkill(int senderAID);
	void OnShowImage(unsigned long senderAID, int type, int imageName);
	void OnChangePalete(unsigned long pcID, int where, int type);
	void OnCompass(unsigned long senderAID, int id, int x, int y, int type, int color);
	void OnCheckPoint(unsigned long senderAID, int x, int y, int mapName);
	void OnWaitDialog(unsigned long senderAID);
	void OnCloseDialog(unsigned long senderAID);
	void OnSetItem(unsigned long senderAID, int ITID, int num);
	void OnChangeItem(const unsigned long in_SenderAID, const int in_ITID, const int in_Num, const int in_Event, const int in_bBroadcasting, const int in_bLog);
	void OnGetItemSocket(unsigned long senderAID, CMsg* msg, int event);
	void OnNonSlotGetItemSocket(unsigned long senderAID, CMsg* msg, int event);
	void OnNonSlotGetItemSocket2(unsigned long senderAID, CMsg* msg, int event);
	void OnChangeVar(unsigned long senderAID, int var, int num);
	void OnDLG_Write(unsigned long senderAID);
	void OnNude(unsigned long senderAID);
	void OnCartOn(unsigned long senderAID);
	void OnNotifyStoredItem(unsigned long senderAID);
	void OnMenu(unsigned long senderAID, int len, int str);
	void OnTradeNpcCommandRegister(unsigned long senderAID, int type, int ITID);
	void OnShowDigit(unsigned long senderAID, int time);
	void OnEnableSkill(unsigned long senderAID, int skill, int level);
	void OnDisableSkill(unsigned long senderAID, int skill);
	void OnSound(unsigned long senderAID, CMsg* msg);
	void OnDLG_WriteStr(unsigned long senderAID);
	void UseSkillToPC(unsigned long senderAID, unsigned long receiverAID, int SKID, int skLevel, int statPoint, int cLevel);
	void OnCashTradeNpcCommandRegister(unsigned long receiverAID, CMsg* msg);
	void OnCashItemList(unsigned long senderAID, CMsg* msg);
	void OnUpdateContectPcList(unsigned long pcID, CMsg* msg);
	void OnAddMoveNpcCommand(unsigned long npcId, CMsg* msg);
	void OnReloadMobileEvent(unsigned long pcID, CMsg* msg);
	void OnEventItem(unsigned long senderAID, CMsg* msg);
	void OnMyMobSkillUse(unsigned long npcId, CMsg* msg);
	void OnWideMobSkillUse(unsigned long npcId, CMsg* msg, int xPos, int yPos);
	void OnWideMobSkillUse2(unsigned long npcId, CMsg* msg);
	void OnMoveNpcSpeedChange(int speed);
	int GetArenaEventSize();
	CRoom* GetMyRoom();
	void OnPurchaseItem(CCharacter* character, const int in_GroupNum);
	void OnZNCloseDialog(int par1);
	void OnInputEditDlg(int inputValue, unsigned long CAID);
	void OnInputEditDlgStr(int answer, unsigned long CAID);
	void OnWarpCharBetweenServer(unsigned long AID);
	void MulticastRoomNewEntry(unsigned long roomID);

private:
	/* this+2108 */ std::list<int> m_sellList;
	/* this+2120 */ BYTE m_cashMap[16]; // TODO // std::vector<CCashItemShopScript::CProduct> m_cashMap;
	/* this+2136 */ BOOL m_isArenaPossible;
	/* this+2140 */ int m_arenaEventSize;
	/* this+2144 */ int m_flagGraffitiNum;
	/* this+2148 */ std::set<unsigned long> m_touchObjects;

private:
	void MobTombClick(const unsigned int PC_AID);
	void Dialog(const char* Msg, const unsigned int PC_AID);
};
