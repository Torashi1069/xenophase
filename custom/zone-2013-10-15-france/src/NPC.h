#pragma once
#include "Actor.h"
#include "Struct.h" // EQUIPSLOTINFO
#include "NetLib/MemoryMgr.h"


struct NpcInfo
{
	/* this+  0 */ int accountID;
	/* this+  4 */ short job;
	/* this+  6 */ short clevel;
	/* this+  8 */ short head;
	/* this+ 10 */ short weapon;
	/* this+ 12 */ short accessory;
	/* this+ 14 */ short headerDir;
	/* this+ 16 */ int speed;
	/* this+ 20 */ int isValid;
	/* this+ 24 */ int mapID;
	/* this+ 28 */ unsigned long reChargeTime;
	/* this+ 32 */ int exp;
	/* this+ 36 */ int jexp;
	/* this+ 40 */ short inc;
	/* this+ 44 */ int hp;
	/* this+ 48 */ int maxhp;
	/* this+ 52 */ int sp;
	/* this+ 56 */ int maxsp;
	/* this+ 60 */ int jobpoint;
	/* this+ 64 */ char accountName[24];
	/* this+ 88 */ char mapName[16];
	/* this+104 */ unsigned char sex;
	/* this+108 */ int Str;
	/* this+112 */ int Agi;
	/* this+116 */ int Vit;
	/* this+120 */ int Int;
	/* this+124 */ int Dex;
	/* this+128 */ int Luk;
	/* this+132 */ int xSize;
	/* this+136 */ int ySize;
	/* this+140 */ int virtue;
	/* this+144 */ short attackRange;
	/* this+146 */ short srcAttackSight;
	/* this+148 */ short attackSight;
	/* this+150 */ short srcExpelSight;
	/* this+152 */ short expelSight;
	/* this+154 */ short atk1;
	/* this+156 */ short atk2;
	/* this+158 */ short def;
	/* this+160 */ short attackedMT;
	/* this+162 */ short attackMT;
	/* this+164 */ short StrAmount;
	/* this+166 */ short AgiAmount;
	/* this+168 */ short VitAmount;
	/* this+170 */ short IntAmount;
	/* this+172 */ short DexAmount;
	/* this+174 */ short LukAmount;
	/* this+176 */ int ATKPercent;
	/* this+180 */ int DEFPercent;
	/* this+184 */ int property;
	/* this+188 */ int scale;
	/* this+192 */ int _class;
	/* this+196 */ int race;
	/* this+200 */ int mdef;
	/* this+204 */ int roomID;
	/* this+208 */ int IsRegen;
	/* this+212 */ int revivalXPos;
	/* this+216 */ int revivalYPos;
	/* this+220 */ int revivalXRange;
	/* this+224 */ int revivalYRange;
	/* this+228 */ int RegenMinTime;
	/* this+232 */ int RegenMaxTime;
	/* this+236 */ int RegenType;
	/* this+240 */ int GuildID;
	/* this+244 */ short originalJob;
	/* this+248 */ int MATKPercent;
	/* this+252 */ int MDEFPercent;
	/* this+256 */ char cashShopName[51];
	/* this+307 */ char campID;
	/* this+308 */ unsigned int attr;
};


struct NpcTimeInfo
{
	/* this+ 0 */ unsigned long StrEffectiveTime;
	/* this+ 4 */ unsigned long AgiEffectiveTime;
	/* this+ 8 */ unsigned long VitEffectiveTime;
	/* this+12 */ unsigned long IntEffectiveTime;
	/* this+16 */ unsigned long DexEffectiveTime;
	/* this+20 */ unsigned long LukEffectiveTime;
	/* this+24 */ unsigned long HPHealVelocity;
	/* this+28 */ unsigned long HPLastHealTime;
	/* this+32 */ unsigned long SPLastHealTime;
	/* this+36 */ unsigned long DamageNoMotionTime;
	/* this+40 */ unsigned long SightRange;
	/* this+44 */ unsigned long SightplusAttackPower;
	/* this+48 */ unsigned long SpeedMount;
	/* this+52 */ int ChangeSpeed;
	/* this+56 */ int ChangeSpeedTime;
};


struct EATING_ITEM_INVENTORY
{
	/* this+ 0 */ unsigned short ITID;
	/* this+ 2 */ unsigned short count;
	/* this+ 4 */ bool IsIdentified;
	/* this+ 8 */ __int64 unique_identity_numberV2;
	/* this+16 */ long hire_expire_date;
	/* this+20 */ bool IsDamaged;
	/* this+21 */ unsigned char RefiningLevel;
	/* this+22 */ EQUIPSLOTINFO slot;
	/* this+30 */ char DropMonsterName[24];
};


struct MYMOBDATA
{
	/* this+0 */ unsigned long AID;
};


struct AMOUNT_INFO
{
	/* this+0 */ unsigned long time;
	/* this+4 */ int amount;
};


class CNPC : public CActor
{
public:
//	const char* GetNamePtr();
//	int GetJobType();

public:
//	CNPC();
//	virtual ~CNPC();

public:
//	unsigned long GetMyCreatorPCAID();
//	void Init();
//	void InitTimeInfo();
//	void Reset();
//	unsigned char GetNPCType();
//	void OnDead(unsigned long);
//	void Send(const int, char *);
//	void NotifySkillAction(class CCharacter *, class CCharacter *, class CCharacter *, int, short, short, unsigned short);
//	void SkillUseAck(unsigned short, unsigned short, bool, unsigned char);
//	void OnProcess();
//	int OnMsg(class CCharacter *, class CCharacter *, unsigned long, int, int, int, class MSGpar::CVar);
//	int GetParameterValue(unsigned short, int &);
//	int UpdateParameterValue(unsigned short, int);
//	void CheckCommandQueue();
//	void DisableCommand(unsigned long);
//	void InsertCommand(struct COMMAND_QUEUE *);
//	int IsMyArea(class CCharacter *, int);
//	int IsTarget(class CCharacter *, unsigned long);
//	void OnMsgFromItemServer(unsigned long, class CITZMsg *);
//	CCharacter* GetMyOwner();
//	int GetErrorCount();
//	void SetErrorCount(int);
//	unsigned long GetAccountID();
//	int GetAttackPoint(class CCharacter *, unsigned short, int);
//	int IsDamageMotionPossible();
//	int IsRightProperty(int);
//	unsigned long GetState();
//	int IsMovable();
//	int IsAttackable();
//	int IsAvoidable(int, int, int);
//	unsigned short GetLostItem(int, class CCharacter * const);
//	int GetSpeed();
//	int GetATKHasteVal1();
//	int GetATKHasteVal2();
//	int GetAttackSlowValue();
//	int GetMoveHasteValue();
//	int GetMoveSlowValue();
//	int GetScale();
//	int GetAvoidableSuccessPercent();
//	short GetStatusDef();
//	short GetDefencePoint();
//	int GetModifiedValueByEnemySize(int);
//	short GetItemMagicDef();
//	short GetStatusMagicDef();
//	int GetBaseFlee();
//	int GetBaseHit();
//	int GetItemAttPower();
//	int GetStatusAttPower();
//	int GetDeadTime();
//	void SetParentAID(unsigned long);
//	unsigned long GetParentAID();
//	void SetParentGID(unsigned long);
//	unsigned long GetParentGID();
//	void SetRegen(int);
//	int IsRegen();
//	int GetMaxHP();
//	int GetMaxSP();
//	short GetDexValue();
//	short GetIntValue();
//	char* GetAccountName();
//	short GetAttackRange();
//	int GetRevivalTerm();
//	int GetAttackMotionTime();
//	int GetAttackedMotionTime();
//	int IsCritical();
//	void SetEffectStateTimeInfo(unsigned long, int);
//	NpcInfo* GetCharacterInfo();
//	unsigned long GetCurrentFSMState();
//	void SetCurrentFSMState(unsigned long);
//	void OnUseSkill(unsigned short, int, int, int, int);
//	class CCharacter * GetTarget();
//	void SetFSMDependent(int);
//	int IsFSMDependent();
//	void StopMove();
//	int IsMovableAround(int);
//	unsigned long GetEnemyAID();
//	void SetEnemyAID(unsigned long);
//	void ResetHealthState(short);
//	void SetBodyState(short);
//	void SetHealthState(short);
//	void SetCurrentState(short);
	virtual void SetEffectState(int state);
//	void SetSpeed(int);
//	void SetZenyLost();
//	int IsZenyLost();
//	int InitByPacket(void *);
//	int SetAccountID(int);
//	bool RegistBattleFiledNpc(const char *);
//	int GetBattleFieldAliveMemberCount(const char);
//	void KVM_StartAliveCheck();
//	void KVM_Npc_Noti(const char *);
//	void InitSkill();
//	void Dump(int, int);
//	void OnEmotion(int);
//	void ChangeSprite(unsigned long);
//	int IsSameGuild(int);
//	void Revival();
//	struct COMMAND_QUEUE * SearchCommand(unsigned long);
//	int IsRechargeTime();
//	void CancelNPCSkill();
//	void SetRangedAttacked(bool, unsigned long);
//	void SetRudeAttacked(bool, unsigned long);
//	void SetAttackedSkillID(unsigned long);
//	void ResetEffectState(int);
//	void OnTeleportCharacter(int, int, int);
//	void OnGroundSkill(int, int, int);
//	void OnTouchedSkillObject(int, int, int);
//	void OperationSkillToCharacter(int, int, int);
//	void SPAttackSkillToCharacter(int, int, int);
//	void OperationSkillToSelf(int, int, int);
//	short SplashAttack(int, short, short, int, int, int, unsigned long, void *, int, int);
//	int SplashAttack2(int, struct PosInfo, int, int, int, struct MSG_TYPE1_TWODWORD *, int, int, struct PosInfo *);
//	void SplashAttack3(int, struct PosInfo, int, struct MSG_TYPE1_TWODWORD *, int, int);
//	void SplashNapalmBeat(struct SKILLATTACK_MSG *, short, short, int, unsigned long);
//	void GetPushedPosition2(int, int, int, int, struct PosInfo &);
//	void GetSplashCells(struct PosInfo, struct PosInfo, int, int, struct PosInfo *);
//	void GetSplashCells2(struct PosInfo, struct PosInfo, int, struct PosInfo *);
//	int GetFireWallNeighborCells(short, short, int, int, int *);
//	void NotifyUseSkill(unsigned short, unsigned long, unsigned long, short, bool);
//	void NotifyGroundSkillUsing(unsigned short, short, short, short, unsigned long);
//	void DetectHidingCharacter(int, struct SKILLATTACK_MSG *, int, int, int);
//	void SummonMonster(struct SummonMobList *, unsigned short, int, int);
//	void Metamorphosis(struct SummonMobList *);
//	class CCharacter * AddMonster(unsigned long, int, int);
//	void ModifyDamage(int &, int, int, class CCharacter *, unsigned short);
//	void ModifyDamage_ATKED(class CCharacter *, int &, int, int, int, int);

public:
	enum enumATTRMASK
	{
		ATTRMASK_MUST_DAMAGE_ONE_SHORT_RNG_PHYSICAL_ATK = 1,
		ATTRMASK_MUST_DAMAGE_ONE_SPELLATK               = 2,
		ATTRMASK_MUST_DAMAGE_ONE_LONG_RNG_PHYSICAL_ATK  = 4,
		ATTRMASK_MVP                                    = 8,
		ATTRMASK_MUST_DAMAGE_ONE_SKILLPATT_NONE         = 16,
		ATTRMASK_KNOCKBACK_BLOCK                        = 32,
	};

public:
//	bool IsMustDamageOne(const int, const int);
//	int GetParameterAttr();
//	void SetParameterAttr(enum CNPC::enumATTRMASK);
//	void ReSetParameterAttr(enum CNPC::enumATTRMASK);
//	void NotifyMissSkill(unsigned short, unsigned long, unsigned long, int);
//	void NeighborPCAttack(int, short, short, int, int, int, unsigned long, struct MSG_TYPE1_TWODWORD *, int, int);
//	int GetMagicAttackModifiedPower(class CCharacter *, int, int, unsigned short, int);
	void Enable();
	void Disable();
	BOOL IsEnable();
//	void OnChangeDefense(int, int);
//	int SetParameter();
//	void InitCache();
//	void OnChangeGuildID();
//	void SetATKPercentInfo(int, unsigned long, int);
//	void SetDEFPercentInfo(int, unsigned long, int);
//	void ResetATKPercentInfo(int);
//	void ResetDEFPercentInfo(int);
//	void SetMATKPercentInfo(int, unsigned long, int);
//	void SetMDEFPercentInfo(int, unsigned long, int);
//	void ResetMATKPercentInfo(int);
//	void ResetMDEFPercentInfo(int);
//	unsigned short GetSpellCasting();
//	void ModifyAttackPowerByEffective(class CCharacter *, int, int &);
//	int IsSiegeMode();
//	int OnWhereMyMob_XPos(const char *);
//	int OnWhereMyMob_YPos(const char *);
//	unsigned long FindMyMobAID(const char *);
//	void SetSpellCasting(const unsigned short);
//	int GetSKLevel(const int);
//	bool OpSKToChar_SKID_ML_DEVOTION(class CCharacter *, struct MSG_TYPE4_FIVEDWORD *);
//	void OpSKToSelf_SKID_ML_DEFENDER(const int);
//	void OpSKToSelf_SKID_MER_MAGNIFICAT(const int, const int, const int, const int);
//	void OpSKToSelf_SKID_MER_AUTOBERSERK();
//	void NotifyParameter(unsigned short, int);
//	void ResetEffective_after_EFST_DEFENDER();

public:
	class Neighbor
	{
		/* this+0 */ std::vector<CCharacter*>* m_pSectionList;
		/* this+4 */ CCharacter* m_pCharacter;

		Neighbor(CCharacter* , std::vector<CCharacter*>* ); //TODO
	};

protected:
//	void CollideSplashAttack(const int, class CCharacter * const, class CCharacter * const, const int, const unsigned short, const int, class std::map<CCharacter *,CollideInfo,std::less<CCharacter *>,std::allocator<std::pair<CCharacter * const,CollideInfo> > > &);

private:
//	void DispatchCommand(struct COMMAND_QUEUE *);
//	void OnUseGroundSkill(int, struct MSG_TYPE1_TWODWORD *, int, int);
//	void NPC_WIDEHEALTHFEAR(const int);
//	void NPC_WIDEBODYBURNNING(const int);
//	void NPC_WIDEFROSTMISTY(const int);
//	void NPC_WIDE_COLD(const int);
//	void NPC_WIDE_DEEP_SLEEP(const int);
//	void NPC_WIDESIREN(const int);

public:
//	int GetEmblemVersion();
//	unsigned long GetNeighborPcNumber(int);
//	void CheckSpecialState(unsigned long);
//	void CheckCondition(unsigned long);
//	CItem* CreateItemOnMap(unsigned short, int, int, int);
//	short GetAttackSuccessPercent(class CCharacter *, const int, int, const int);

protected:
//	int GetAttackFinalDamage(class CCharacter *, int, int, unsigned short, int, int);

public:
//	int GetAttackFinalDamage(struct ATTACK_INFO *);
//	void AddSpecialZoneList(unsigned long);
//	void DelSpecialZoneList();
//	int SetEffective(int, int, int, int, int, int);
//	void ResetEffective(int, int);
//	bool IsGroundEffective(int, int &, bool &);
//	void ProcessGroundEffective(int, int, bool);
//	void SetOnShowEFST(int);
//	void SetOffShowEFST(int);
//	void OnChangeStatusAmount(int, unsigned short, unsigned long, int);
//	void NotifyStatusAmount(unsigned short, int);
//	bool ApplyStatusAmount(unsigned short, int &);
//	short GetBodyState();
//	short GetHealthState();
//	void Chat(const char *, unsigned long);
//	char GetCampID();
//	void SetCampID(char);
//	short GetAttSucPercent();
//	int GetModifiedTargetStatusDEF(class CCharacter *);

private:
//	int GetModifiedTargetStatusDEF2(CCharacter* );
//	int GetModifiedTargetItemMDEF2(CCharacter* );

public:
//	void ApplyExtraDEF(int &, class CCharacter *);
//	void ApplyExtraMDEF(int &);
//	int GetMinusStdPropertyDamage(class CCharacter *, int, unsigned short, int);
//	int GetRoomSize();
//	int GetPhysicsFinalDamage(class CCharacter *, int, int, unsigned short, int, int);
//	int GetPhysicsBaseATKPower(class CCharacter *, unsigned short, int);
//	int GetMagicFinalDamage(class CCharacter *, int, int, unsigned short);
//	int GetMagicFinalATKPower(class CCharacter *, int, int, unsigned short, int);
//	int GetMagicTargetSKValue(class CCharacter *, const int, const unsigned short);
//	int GetTargetSTDValue(class CCharacter *, int, unsigned short, int);
//	int ProcessRevengeEnemy(class CCharacter *);

protected:
//	void InitCore();
//	void AddMYMob(unsigned long);
//	void OnMyMonsterDead(unsigned long, unsigned long);
//	int StartPath(struct PACKET_CZ_REQUEST_MOVE *, unsigned long);
//	int OnMove(struct PACKET_CZ_REQUEST_MOVE *);
	void MultiCastStateInfo();
//	void NotifyInfoToSection();
//	short GetCurrentState();
//	int GetEffectState();
//	int GetMYMobSize();
//	int SpawnMyMob(unsigned long);
	void OnResetMyMob();
//	void UseSkillToCharacter(int, int, int);
//	int GetMagicAttackFinalDamage(class CCharacter *, int, int, unsigned short);
//	int GetMagicAttPower();
//	int SkillAttack(struct SKILLATTACK_MSG *, int, int, const bool);
//	void SplashDamageAttack(int, short, short, short, int, unsigned long);
//	void OnMoveStop(int, int, int, const bool);
//	void OnCM_KNOCKBACK(const int, const int, const bool, const bool);
//	void OnCM_PROGRESSBAR(const unsigned long, const unsigned long);
//	void OnChangeAGI(int, int, int);
//	void OnChangeDEX(int, int, int);
//	void OnChangeINT(int, int, int);
//	void OnChangeLUK(int, int, int);
//	void OnChangeSTR(int, int, int);
//	void OnChangeVIT(int, int, int);
//	void InitThePCCacheInfo(int);
//	void OnShowEffect(int);
//	void OnShowEffect3(int, int);
//	void OnShowScript(const char *);
//	short GetAvoidPercent_Client();

protected:
	struct stTombInfo
	{
		stTombInfo()
		{
			this->MPV_GID = 0;
			this->MOB_AID = 0;
			this->bUse = false;
			this->hour = 0;
			this->min = 0;
		}

		void Reset(); //TODO

		/* this+ 0 */ bool bUse;
		/* this+ 2 */ short hour;
		/* this+ 4 */ short min;
		/* this+ 8 */ unsigned long MPV_GID;
		/* this+12 */ unsigned long MOB_AID;
	};

protected:
//	const struct CNPC::stTombInfo & SetTombInfo();
//	void SetTombInfo(const short, const short, const unsigned long, const unsigned long);

public:
//	void SetUseTomb(const bool);
//	bool GetUseTomb();
//	void DisappearBossTomb();

protected:
	/* this+   0 */ //CActor baseclass_0;
	/* this+1276 */ NpcTimeInfo m_characterTimeInfo;
	/* this+1336 */ BYTE m_npcSkill[120]; // TODO // CNPCSkill m_npcSkill;
	/* this+1456 */ std::list<EATING_ITEM_INVENTORY*> m_eatingItem;
	/* this+1468 */ CMemoryMgr<EATING_ITEM_INVENTORY> m_eatingItemMPool;
	/* this+1504 */ BYTE m_pathInfo[56]; // TODO // CHostPathInfo m_pathInfo;
	/* this+1560 */ BYTE m_npcUpdater[20]; // TODO // CNPCUpdater m_npcUpdater;
	/* this+1580 */ unsigned long m_currentState;
	/* this+1584 */ unsigned long m_myParentAID;
	/* this+1588 */ unsigned long m_myParentGID;
	/* this+1592 */ int m_isSkilledFromCrucis;
	/* this+1596 */ int m_isFSMDependent;
	/* this+1600 */ int m_asDelta;
	/* this+1604 */ std::list<MYMOBDATA> m_myMobList;
	/* this+1616 */ std::map<int,AMOUNT_INFO> m_ATKPercentList;
	/* this+1632 */ std::map<int,AMOUNT_INFO> m_DEFPercentList;
	/* this+1648 */ std::map<int,AMOUNT_INFO> m_MATKPercentList;
	/* this+1664 */ std::map<int,AMOUNT_INFO> m_MDEFPercentList;
	/* this+1680 */ int m_isMagicLocked;
	/* this+1684 */ int m_isRangeAttacked;
	/* this+1688 */ int m_isRudeAttacked;
	/* this+1692 */ unsigned long m_attackedSkillID;
	/* this+1696 */ std::map<unsigned long,unsigned long> m_invincibleInfo;
	/* this+1712 */ NpcInfo m_characterInfo;
	/* this+2024 */ BYTE m_npcStateUpdater[40]; // TODO // CNPCStateUpdater m_npcStateUpdater;
	/* this+2064 */ unsigned char m_npcType;

protected:
//	unsigned long GetRoomID();
//	void SetRoomID(unsigned long);

protected:
	/* this+2068 */ BYTE m_emoticonTM[8]; // TODO // CPollTimer m_emoticonTM;
	/* this+2076 */ std::list<unsigned long> m_specialZoneList;
	/* this+2088 */ stTombInfo m_TombInfo;

private:
//	void PA_PRESSURE(class CCharacter *, struct MSG_TYPE4_FIVEDWORD *);
//	void CR_ACIDDEMONSTRATION(class CCharacter *, const struct MSG_TYPE4_FIVEDWORD * const, struct SKILLATTACK_MSG &);
//	void SA_LANDPROTECTOR(const int, const int, const int, const int);
//	void ST_FULLSTRIP(class CCharacter *, struct MSG_TYPE4_FIVEDWORD *);
//	void MO_BALKYOUNG(class CCharacter *, const int, struct SKILLATTACK_MSG *);
//	void NPC_ASSASSINCROSS(const int, const int);
//	void NPC_DISSONANCE(const int);
//	void NPC_UGLYDANCE(const int);
//	void MO_EXTREMITYFIST(class CCharacter *, struct SKILLATTACK_MSG *);
//	bool RG_STRIPWEAPON(class CCharacter *, struct MSG_TYPE4_FIVEDWORD *, const bool);
//	bool RG_STRIPSHIELD(class CCharacter *, struct MSG_TYPE4_FIVEDWORD *, const bool);
//	bool RG_STRIPARMOR(class CCharacter *, struct MSG_TYPE4_FIVEDWORD *, const bool);
//	bool RG_STRIPHELM(class CCharacter *, struct MSG_TYPE4_FIVEDWORD *, const bool);
//	void OnCM_MODIFY_SKILLCOUNT(class CCharacter *);

public:
//	int SkillAttackEx(struct SKILLATTACK_MSG *, const int, const int, const bool);
};
C_ASSERT( sizeof CNPC == 2104 );
