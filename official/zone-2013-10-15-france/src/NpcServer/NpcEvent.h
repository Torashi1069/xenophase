#pragma once
#include "ScriptEventHandler.h"
class CBinBuf;
class CNpc;
class CNpcMgr;
struct NpcSvrNpcInfo;


enum _AnswerType
{
	REQ_NONE      = 0,
	REQ_NEXT_ANS  = 1,
	CHOOSE_ANS    = 2,
	ITEM_EXCHANGE = 3,
	ITEM_GET      = 4,
	DLG_WRITE     = 5,
	REQ_CLOSE_ANS = 6,
	DLG_WRITESTR  = 7,
	PROGRESS      = 8,
	NPCPROGRESS   = 9,
};


class CNpcEvent : public CScriptEventHandler
{
public:
	CNpcEvent();
	virtual ~CNpcEvent();

public:
	void Clear();
	void End(); // not implemented
	bool IsEmpty(); // not implemented
	char* GetDungeonIdent();
	bool Run_Dungeon(CNpcMgr* npcMgr, CBinBuf* binBuf, const char* dg_ident, unsigned int instantID, int pcId, int npcId, int act);
	bool Run(CNpcMgr* npcMgr, CBinBuf* binBuf, int pcId, int npcId, int actIndex);
	virtual unsigned int Proc(bool isOnce);
	void Answer(int type, int answer);
	virtual bool OnFunc(int func, std::deque<TokenData>& parm, TokenData& ret);
	virtual void OnError(const char* str);
	void Stop();
	void StopDungern();
	CNpc* GetNpc();
	void SetReserveTime(unsigned long t);
	unsigned long GetReserveTime();
	bool IsGlobalEvent() const;
	bool GetOnInit() const;
	void SetOnInit(bool oninit);

public:
	/* static */ static int& m_serverID; //TODO

protected:
	virtual void EventLog(char* str, ...);

private:
//	int GetCharacterVar(int , int );
	bool GlobalFunc(int func, std::deque<TokenData>& parm, TokenData& ret);
	bool DefaultNpcFunc(int func, std::deque<TokenData>& parm, TokenData& ret);
//	bool FuncChangePallete(int , int );
//	bool FuncCallMonster(char *, int, char *, int, int, int, int, int, bool);
//	bool FuncAddSkill(int, int, int, int);
//	bool FuncOtherNpcCmd(const char *, char *);
//	bool FuncStrLocalVar(int, char *);
//	bool FuncSetArenaEventSize(int);
//	bool FuncGetArenaEventSize(struct TokenData &);
//	bool FuncMakeWaitingRoom(char *, int);
//	bool FuncEnableArena();
//	bool FuncDisableArena();
//	bool FuncWarpWaitingPcToArena(char *, int, int);
//	bool FuncResetMyMob();
//	bool FuncWarpAllPcInTheMap(char *, int, int);
//	bool FuncBroadcastInTheMap(char *);
//	bool FuncAddNpcTimer(char *, int);
//	bool FuncSubNpcTimer(char *, int);
//	bool FuncEnableNpc(char *);
//	bool FuncDisableNpc(char *);
//	bool FuncCallNpc(char *, int, char *, int, int, int);
//	bool FuncSetFeeZeny(int);
//	bool FuncSetFeeItem(int, int);
//	bool FuncSetReqLevel(int, int);
//	bool FuncSetTexJob(int);
//	bool FuncDisableItemMove();
	bool FuncEnableItemMove();
//	bool FuncSuccessRefItem(int);
//	bool FuncFailedRefItem(int);
	virtual bool FuncSetEffectStatus(int effect);
//	bool FuncResetStat();
	bool FuncTrace(char* str);
//	bool FuncVar(int, struct TokenData &);
//	bool FuncLV(char *, struct TokenData &);
//	bool FuncNpcV(char *, int, struct TokenData &);
//	bool FuncIncLocalVar(char *, int);
//	bool FuncDecLocalVar(char *, int);
//	bool FuncSetLocalVar(char *, int);
//	bool FuncGetEquipIsIdentify(int, struct TokenData &);
//	bool FuncGetEquipRefineryCnt(int, struct TokenData &);
//	bool FuncGetEquipRefineryCost(int, struct TokenData &);
//	bool FuncGetEquipWeaponLv(int, struct TokenData &);
//	bool FuncGetEquipIsEnableRef(int, struct TokenData &);
//	bool FuncLastNpcName(char *);
//	bool FuncInitTimer();
//	bool FuncLabel(int, class std::deque<TokenData,std::allocator<TokenData> > &);
//	bool FuncRegSay(char *);
//	bool FuncRegMapMove(const char *, int, int);
//	bool FuncRegSellItem(int);
//	bool FuncMob(int, struct NpcSvrNpcInfo *);
//	bool FuncCompass(int, int, int, int, const char *);
//	bool FuncNpc(struct NpcSvrNpcInfo *, bool);
	unsigned long FuncNpc2(NpcSvrNpcInfo* npcInfo, bool isNpc);
//	bool FuncInput(struct TokenData &);
//	bool FuncDlgWrite(int, int);
//	bool FuncNude();
	bool FuncCart(BOOL flag);
//	bool FuncStore();
	bool FuncMenu(const char* str, bool bExtra);
//	bool FuncJobChange(int);
//	bool FuncGetMoney(int);
//	bool FuncDropMoney(int, struct TokenData &);
//	bool FuncSetItem(int, int);
//	bool FuncGetItem(int, int);
//	bool FuncGetItem2(const int, const int, const int, const int);
//	bool FuncDropItem(int, int);
//	bool FuncExchangeItem(int, int, int, int);
//	bool FuncInc(int, int);
//	bool FuncDec(int, int);
//	bool FuncHeal(int, int);
//	bool FuncRand(int, int, struct TokenData &);
	bool FuncLot(int numerator, int denominator, TokenData& ret);
//	bool FuncGetPcCount(const char *, struct TokenData &);
	bool FuncError(TokenData& ret);
//	bool FuncCheckPoint(const char *, int, int);
//	bool FuncShowDigit(int);
//	bool FuncEnableSkill(int, int);
//	bool FuncDisableSkill(int);
//	bool FuncSetParameter(int, int);
//	bool FuncEmotion(char *, int);
//	bool FuncChangeSpr(char *, int);
//	bool FuncGetEquipCount(int, struct TokenData &);
//	bool FuncAgitGet(char *, int, struct TokenData &);
//	bool FuncAgitSet(int, int);
//	bool FuncAgitFunc(int, int, int);
//	bool FuncAgitNpcGet(int, int, struct TokenData &);
//	bool FuncAgitNpcSet(int, int, int);
//	bool FuncIsGuildMaster(int, struct TokenData &);
//	bool FuncAgitRegister(char *);
//	bool FuncBroadcast(bool, char *, int, int, int, int, char *);
//	bool FuncSound(char *, int, int, int);
//	bool FuncGetDamagedItemNum(struct TokenData &);
//	bool FuncRepairDamagedItem();
//	bool FuncSavePPL(int);
//	bool FuncAgitEmblemFlag(char *);
//	bool FuncChangeEXP(int);
//	bool FuncServerTime(struct TokenData &);
//	bool FuncGetLocalVarName(int, struct TokenData &);
//	bool FuncGetMarried(struct TokenData &);
//	bool FuncGetGuildName(struct TokenData &);
//	bool FuncCountDown(int);
//	bool FuncGetNeighborPcNumber(int, struct TokenData &);
//	bool FuncGetNamedItem(int, int);
//	bool FuncDropNamedItem(int, int);
//	bool FuncGetCountOfMyNameItem(int, struct TokenData &);
//	bool FuncChangeHairStyle(int);
//	bool FuncShowEffect(const char *, int);
//	bool FuncFalcon(int);
//	bool FuncPeco(int);
//	bool FuncCheckMaxZeny(int, struct TokenData &);
//	bool FuncCheckMaxCount(int, int, struct TokenData &);
//	bool FuncCheckMaxWeight(int, int, struct TokenData &);
//	bool FuncMGetEventItem(int, struct TokenData &);
//	bool FuncMGetEventZeny(int, struct TokenData &);
//	bool FuncMGetEventItemName(int, struct TokenData &);
//	bool FuncMGetEventZenyName(int, struct TokenData &);
//	bool FuncCreateGuild(char *);
//	bool FuncCreateGlobalVar(const char *, int);
//	bool FuncGetGlobalVar(const char *, struct TokenData &);
//	bool FuncSetGlobalVar(const char *, int);
//	bool FuncStrCmp(const char *, const char *, struct TokenData &);
//	bool FuncStrStr(const char *, const char *, struct TokenData &);
//	bool FuncUpgradeGuildLevel();
//	bool FuncCreateGlobalStr(const char *, char *);
//	bool FuncGetGlobalStr(const char *, struct TokenData &);
//	bool FuncSetGlobalStr(const char *, char *);
//	bool FuncDivorce();
//	bool FuncPEventGet(struct TokenData &);
//	bool FuncPEventAdd(int, struct TokenData &);
//	bool FuncPEventDel(int, struct TokenData &);
//	bool FuncPCDataMoveToPVP();
//	bool FuncMGetEventItemID(int, struct TokenData &);
//	bool FuncGetJobExp(int);
//	bool FuncDropJobExp(int);
//	bool FuncChkSkill(int, struct TokenData &);
//	bool FuncGetBodyState(int, int);
//	bool FuncGetHealthState(int, int);
//	bool FuncUseSkillToPC(int, int, int, int);
//	bool FuncIsBaby(struct TokenData &);
//	bool FuncGetLotto(int, struct TokenData &);
//	bool FuncSetLotto(int, int, int, int, int, int);
//	bool FuncInitLotto();
//	bool FuncOpenAuction();
//	bool FuncOpenMailing();
//	bool FuncStripPC(int);
//	bool FuncPushPC(int, int);
//	bool FuncItemDown(int, int, int, int);
//	bool FuncSetNumArray(int, int);
//	bool FuncGetNumArray(int, struct TokenData &);
//	bool FuncShuffleNumbers(int, int);
//	bool FuncPartyName(struct TokenData &);
//	bool FuncChangeSpeed(int, int);
//	bool FuncIsSiegeTime(struct TokenData &);
//	bool FuncConsumeSpecialItem(int);
//	bool FuncSetItemPartyInMap(int, int);
//	bool FuncIsHuntingListFull(struct TokenData &);
//	bool FuncFindHuntingList(int, struct TokenData &);
//	bool FuncAddHuntingList(int);
//	bool FuncDeleteHuntingList(int);
//	bool FuncDisplayHuntingList(struct TokenData &);
//	bool FuncDisplayHuntingList2(struct TokenData &);
//	bool FuncSetHuntingList(int, int);
//	bool FuncClearHuntingList();
//	bool FUNCUseHuntingList(struct TokenData &);
//	bool FUNCCheckHuntingList(int, struct TokenData &);
//	bool FuncIsTimeListFull(struct TokenData &);
//	bool FuncFindTimeList(int, struct TokenData &);
//	bool FuncAddTimeList(int);
//	bool FuncDeleteTimeList(int);
//	bool FuncDisplayTimeList(struct TokenData &);
//	bool FuncSetTimeList(int, int);
//	bool FuncClearTimeList();
//	bool FuncChangeCellType(int, int, int);
//	bool FuncGetCellType(int, int, struct TokenData &);
//	bool FuncIsPcCafe(struct TokenData &);
//	bool FuncGetPayType(struct TokenData &);
//	bool FuncGetConnectionArea(struct TokenData &);
//	bool FuncGetConnectionState(struct TokenData &);
//	bool FuncIsPremiumPcCafe(struct TokenData &);
//	bool FuncGetPetEgg(int);
//	bool FuncCashItem(char *);
//	bool FuncMovePos(int, int);
//	bool FuncMoveWait(int);
//	bool FuncRefinery(int, struct TokenData &);
//	bool FuncRelaodMobileEvent();
//	bool FuncSetTempTime(int);
//	bool FuncElapseTempTime(int, struct TokenData &);
//	bool FuncGetInventoryRemainCount(int, int, struct TokenData &);
//	bool FuncIsBeginQuest(int, struct TokenData &);
//	bool FuncSetQuest(int);
//	bool FuncChangQuest(int, int);
//	bool FuncEraseQuest(int);
//	bool FuncComplateQuest(int);
//	bool FuncCompleteQuest_Between(int, int);
//	bool FuncRecall_CompleteQuest(int);
//	bool FuncCheckQuest_Hunting(int, struct TokenData &);
//	bool FuncCheckQuest_PlayTime(int, struct TokenData &);
//	bool FuncPCDataMoveTo_Sakray();
//	bool FuncCallGuardian(char *, int, char *, int, int);
//	bool FuncGetLastSiegeMsg(char *, struct TokenData &);
	virtual bool FuncDialog(char* str, int npcID);
	virtual bool FuncWaitDialog(int npcID);
	virtual bool FuncCloseDialog(int npcID);
	virtual bool FuncDlgWriteStr(int npcID);
	virtual bool FuncMapMove(const char* zone, int x, int y);
//	bool FuncMdungeon_Subscription(const char *, struct TokenData &);
//	bool FuncMdungeon_Enter(const char *, struct TokenData &);
//	bool FuncMdungeon_List(const char *, const char *, const char *);
//	bool FuncMdungeon_Destroy(const char *);
//	bool FuncMdungeon_OpenState(const int, struct TokenData &);
	bool FuncMDungeon_NpcName(const char* name, TokenData& out_ret);
	bool FuncMDungeon_MapName(const char* map_name, TokenData& out_ret);
	bool FuncMDungeon_Npc(NpcSvrNpcInfo* npcInfo, bool isNpc);
//	bool FuncMDungeon_PutMob(const char *, int, int, int, int, int, int, int, int, int, char *);
//	bool FuncCampCode(char *, int, int);
//	bool FuncGetCampCode(struct TokenData &);
//	bool FuncCallCampMob(int, int, int, char *, char *);
//	bool FuncSetRP2(int, int);
//	bool FuncMassSetRP2(char *, int, int);
//	bool FuncPlayerToRP(int);
//	bool FuncUpdateCampPoint(char *, int);
//	bool FuncGetCampPoint(char *, struct TokenData &);
//	bool FuncResetCampPoint();
//	bool FuncMyMobSkillUse(const char *, int, int, int, int);
//	bool FuncWhereMyMob_X(const char *, struct TokenData &);
//	bool FuncWhereMyMob_Y(const char *, struct TokenData &);
//	bool FuncWideMobSkillUse(int, int, int, int, int, int, int);
//	bool FuncWideMobSkillUse2(struct MSG_TYPE7_EIGHTWORD *);
//	bool FuncCheckSiegeTime(int, struct TokenData &);
//	bool FuncIsBender(struct TokenData &);
//	bool FuncGetNpcPosition(const char *, struct TokenData &);
//	bool FuncChangMoveSpeed(int);
//	bool FuncProgressBar(const char *, int);
//	bool FuncNPCProgressBar(const char *, int);
//	bool FuncMercenaryCheck(struct TokenData &);
//	bool FuncMercenaryType(struct TokenData &);
//	bool FuncIsFreeServer(struct TokenData &);
//	bool FuncCheckPartyJob(struct TokenData &);
//	bool FuncClearBuff();
//	bool FuncCheckAlive(const char *, struct TokenData &);
//	bool FuncKVMNpc(struct NpcSvrNpcInfo *);
//	bool FuncKVMStartAliveCheck();
//	bool FuncPVPRankCheck(struct TokenData &);
//	bool FuncKvm_Npc_Noti(const char *);
//	bool FuncGetItemSocket(const int, const int, const int, const int, const int);
//	bool FuncGetNonSlotItemSocket(const int, const int, const int, const int, const int);
//	bool FuncGetNonSlotItemSocket2(const int, const int, const int, const int, const int, const int);
//	bool FuncGetMyMercenary(struct TokenData &);
//	bool FuncErrorLog(const char *);
//	bool FuncIsMadogear(struct TokenData &);
//	bool FuncSetMadogear(const char *);
//	bool FuncIsAllianceGuild(int, struct TokenData &);
//	bool FuncOpenHour_SiegeMode(int, int, struct TokenData &);
//	bool FuncSetBattleFieldMovePosition(const char *, const char *, const int, const int);
//	bool FuncGetEquipcompositionType(const int, const int, struct TokenData &);
//	bool FuncGetEquipDBName(const int, struct TokenData &);
//	bool FuncGetEquipcardID(const int, const int, struct TokenData &);
//	bool Funcdropequipitem(const int);
//	bool Funcgetrefitem(const int, const char *);
//	bool FuncTalkShow(const char *, const char *);
//	bool FuncRentItem(const int, const int);
//	bool FuncGetMonsterHP(const char *, struct TokenData &);
//	bool FuncMonsterTalkShow(const char *, const char *);
//	bool FuncSetMonsterHP(const char *, const int, struct TokenData &);
//	bool FuncItemDown2(const int, int, int, const int, const int, const int, const int, const int);
//	bool FuncGetElapsedTimer(struct TokenData &);
//	bool FuncIsEnableNpc(const char *, struct TokenData &);
//	bool FuncGetNpcMonsterX(const char *, const char *, struct TokenData &);
//	bool FuncGetNpcMonsterY(const char *, const char *, struct TokenData &);
//	bool FuncDelayTime(const int);
//	bool FuncSetMonsterHP2(const char *, const char *, const int, struct TokenData &);
//	bool FuncGetRankingPoint(const int, struct TokenData &);
//	bool FuncIncRankingPoint(const int, const int);
//	bool FuncDecRankingPoint(const int, const int);
//	bool FuncNpcMontransform(const int, const int);
//	bool FuncPartyMapMove(const int, const char *, const int, const int);
//	bool FuncSkillOrder(const char *, const int, const int, const int, const int, const int);
//	bool ReducePCCafePlayTime(const int, struct TokenData &);
//	bool GetPCCafePlayTime(struct TokenData &);
//	bool FuncGetMEventItemName_V2(const int, struct TokenData &);
//	bool FuncGetNonSlotItemSock3(const int, const char *, const int, const int, const int, const int);
//	bool GetNpcParm(struct NpcSvrNpcInfo *);
	void TraceCurPos();
	void Wait(int type, int delay);
//	CAgitMapRes* GetAgit(char* );
//	CBattleFieldMapRes* GetCurrentBattleFieldMapRes();

private:
	/* this+  0 */ //CScriptEventHandler baseclass_0;
	/* this+120 */ CBinBuf* m_binBuf;
	/* this+124 */ CNpcMgr* m_npcMgr;
	/* this+128 */ CNpc* m_npc;
	/* this+132 */ int m_pcId;
	/* this+136 */ int m_npcId;
	/* this+140 */ int m_waitTime;
	/* this+144 */ int m_waitType; // _AnswerType
	/* this+148 */ bool m_isDisableItemMove;
	/* this+152 */ int m_min;
	/* this+156 */ int m_max;
	/* this+160 */ int m_error;
	/* this+164 */ int m_input;
	/* this+168 */ bool m_dialogFlag;
	/* this+172 */ int m_curInitNpc;
	/* this+176 */ char m_dgIdent[4];
	/* this+180 */ unsigned int m_instantID;
	/* this+184 */ unsigned long m_reserveTime;
	/* this+188 */ std::vector<int> m_initList;
	/* this+204 */ bool m_OnInit;
	/* this+208 */ std::map<int,int> m_numArray;
public:
	int GetDeleteCount();
	void AddDeleteCount();
private:
	/* this+224 */ int m_DeleteCount;

private:
//	void FuncSavePosition();
//	void FuncMoveToSavePosition();
};
