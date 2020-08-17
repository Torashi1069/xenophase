#pragma once
#include "Actor.h"
#include "FSMState.h"
#include "HostPathFinder.h"
#include "NPCSkill.h"
#include "NPCStateUpdater.h"
#include "NPCUpdater.h"
#include "Struct.h" // EQUIPSLOTINFO
#include "NetLib/MemoryMgr.h"
#include "shared/PollTimer.h"
struct PACKET_CZ_REQUEST_MOVE;


enum enumNPCCLASS
{
	CLASS_NONE                  = 0,
	NPC_CLASS_BOSS              = 1,
	NPC_CLASS_GUARDIAN          = 2,
	UNUSED_NPC_CLASS_INVINCIBLE = 3,
	NPC_CLASS_BATTLEFIELD       = 4,
	NPC_CLASS_FIXED_ITEMDROP    = 5,
	CLASS_MAX                   = 6,
};


enum _npcType
{
	WARP_NPC                 = 0,
	GUIDE_NPC                = 1,
	TALK_NPC                 = 2,
	TRADER_NPC               = 3,
	EFFECT_NPC               = 4,
	ARENA_GUIDE_NPC          = 5,
	MONSTER_TYPE_01          = 6,
	MONSTER_TYPE_02          = 7,
	MONSTER_TYPE_03          = 8,
	MONSTER_TYPE_04          = 9,
	MONSTER_TYPE_05          = 10,
	MONSTER_TYPE_06          = 11,
	MONSTER_TYPE_07          = 12,
	MONSTER_TYPE_08          = 13,
	MONSTER_TYPE_09          = 14,
	MONSTER_TYPE_10          = 15,
	MONSTER_TYPE_11          = 16,
	MONSTER_TYPE_12          = 17,
	MONSTER_TYPE_13          = 18,
	MONSTER_TYPE_14          = 19,
	MONSTER_TYPE_15          = 20,
	MONSTER_TYPE_16          = 21,
	MONSTER_TYPE_17          = 22,
	MONSTER_TYPE_18          = 23,
	MONSTER_TYPE_19          = 24,
	MONSTER_TYPE_20          = 25,
	MONSTER_TYPE_21          = 26,
	MONSTER_TYPE_22          = 27,
	MONSTER_TYPE_23          = 28,
	MONSTER_TYPE_24          = 29,
	MONSTER_TYPE_25          = 30,
	MONSTER_TYPE_26          = 31,
	MONSTER_TYPE_27          = 32,
	HIDDEN_WARP_NPC          = 33,
	MERCENARY_TYPE_01        = 34,
	MERCENARY_TYPE_02        = 35,
	CASHTRADER_NPC           = 36,
	MOVE_NPC_TYPE01          = 37,
	MOVE_NPC_TRADER          = 38,
	LUA_AI_TYPE              = 39,
	MONSTER_TYPE_28          = 40,
	LUA_ELEMENTAL_TYPE       = 41,
	ELEMENTAL_TYPE_WAIT      = 42,
	ELEMENTAL_TYPE_PASSIVE   = 43,
	ELEMENTAL_TYPE_DEFENSIVE = 44,
	ELEMENTAL_TYPE_OFFENSIVE = 45,
	MOB_TOMB_NPC             = 46,
	MONSTER_TYPE_29          = 47,
};


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
	/* this+ 20 */ BOOL isValid;
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
	/* this+188 */ int scale; // enumCHARSCALE
	/* this+192 */ int _class; // enumNPCCLASS
	/* this+196 */ int race;
	/* this+200 */ int mdef;
	/* this+204 */ int roomID;
	/* this+208 */ BOOL IsRegen;
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
	/* this+0 */ DWORD time;
	/* this+4 */ int amount;
};


class CNPC : public CActor
{
public:
	virtual const char* GetNamePtr() const;
	int GetJobType() const;

public:
	CNPC();
	virtual ~CNPC();

public:
//	unsigned long GetMyCreatorPCAID();
	virtual void Init();
//	void InitTimeInfo();
	virtual void Reset();
	unsigned char GetNPCType(); // enum _npcType
	virtual void OnDead(unsigned long killer);
	virtual void Send(const int in_Length, char* in_pBuffer); //NOTE: possibly unintended overload
//	void NotifySkillAction(class CCharacter *, class CCharacter *, class CCharacter *, int, short, short, unsigned short);
	virtual void SkillUseAck(unsigned short SKID, unsigned short NUM, bool result, unsigned char cause);
	virtual void OnProcess();
	virtual int OnMsg(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4);
	virtual int GetParameterValue(unsigned short id, int& value);
	virtual int UpdateParameterValue(unsigned short id, int value);
	virtual void CheckCommandQueue();
	virtual void DisableCommand(unsigned long commandID);
	virtual void InsertCommand(COMMAND_QUEUE* command);
	virtual BOOL IsMyArea(CCharacter* ch, int range);
	virtual BOOL IsTarget(CCharacter* ch, unsigned long flag);
	virtual void OnMsgFromItemServer(unsigned long AID, CITZMsg* reqMsg);
	virtual CCharacter* GetMyOwner();
	int GetErrorCount();
	void SetErrorCount(int i);
	virtual unsigned long GetAccountID();
	virtual int GetAttackPoint(CCharacter* other, unsigned short SKID, int property);
	virtual BOOL IsDamageMotionPossible();
	virtual BOOL IsRightProperty(int property);
	virtual unsigned long GetState(); // enumCHARACTERSTATE
//	int IsMovable();
//	int IsAttackable();
	virtual BOOL IsAvoidable(int race, int _class, int level);
//	unsigned short GetLostItem(int, class CCharacter * const);
	virtual int GetSpeed();
//	int GetATKHasteVal1();
//	int GetATKHasteVal2();
//	int GetAttackSlowValue();
//	int GetMoveHasteValue();
//	int GetMoveSlowValue();
	virtual int GetScale(); // enumCHARSCALE
	virtual int GetAvoidableSuccessPercent();
	virtual short GetStatusDef();
	virtual short GetDefencePoint();
	virtual int GetModifiedValueByEnemySize(int value);
	virtual short GetItemMagicDef();
	virtual short GetStatusMagicDef();
	virtual int GetBaseFlee();
	virtual int GetBaseHit();
	virtual int GetItemAttPower();
	virtual int GetStatusAttPower();
//	int GetDeadTime();
	void SetParentAID(unsigned long AID);
	unsigned long GetParentAID() const;
	void SetParentGID(unsigned long GID);
	unsigned long GetParentGID() const;
	void SetRegen(BOOL flag);
	BOOL IsRegen();
	virtual int GetMaxHP();
	virtual int GetMaxSP();
	virtual short GetDexValue();
	virtual short GetIntValue();
	char* GetAccountName();
	short GetAttackRange();
	virtual int GetRevivalTerm();
	int GetAttackMotionTime();
	int GetAttackedMotionTime();
//	int IsCritical();
	virtual void SetEffectStateTimeInfo(unsigned long time, int state);
	NpcInfo* GetCharacterInfo();
	unsigned long GetCurrentFSMState(); // enum stateList
	void SetCurrentFSMState(unsigned long state); // enum stateList
//	void OnUseSkill(unsigned short, int, int, int, int);
//	class CCharacter * GetTarget();
//	void SetFSMDependent(int);
//	int IsFSMDependent();
//	void StopMove();
//	int IsMovableAround(int);
	unsigned long GetEnemyAID();
	void SetEnemyAID(unsigned long AID);
	virtual void ResetHealthState(short state);
//	void SetBodyState(short);
	virtual void SetHealthState(short state);
//	void SetCurrentState(short);
	virtual void SetEffectState(int state);
	void SetSpeed(int speed);
//	void SetZenyLost();
//	int IsZenyLost();
	BOOL InitByPacket(void* p);
	BOOL SetAccountID(int AID);
//	bool RegistBattleFiledNpc(const char *);
//	int GetBattleFieldAliveMemberCount(const char);
//	void KVM_StartAliveCheck();
//	void KVM_Npc_Noti(const char *);
	void InitSkill();
//	void Dump(int, int);
	void OnEmotion(int type);
//	void ChangeSprite(unsigned long);
//	int IsSameGuild(int);
	void Revival();
	virtual COMMAND_QUEUE* SearchCommand(unsigned long commandID);
	virtual int IsRechargeTime();
//	void CancelNPCSkill();
//	void SetRangedAttacked(bool, unsigned long);
//	void SetRudeAttacked(bool, unsigned long);
//	void SetAttackedSkillID(unsigned long);
	virtual void ResetEffectState(int state);
//	void OnTeleportCharacter(int, int, int);
//	void OnGroundSkill(int, int, int);
//	void OnTouchedSkillObject(int, int, int);
//	void OperationSkillToCharacter(int, int, int);
//	void SPAttackSkillToCharacter(int, int, int);
//	void OperationSkillToSelf(int, int, int);
	virtual short SplashAttack(int val1, short xPos, short yPos, int type, int range, int rangeIn, unsigned long exceptAID, void* msgDataPtr, int val2, int count);
	virtual int SplashAttack2(int plusATTPower, PosInfo dest, int type, int halfWidth, int height, MSG_TYPE1_TWODWORD* msgData, int count, int plusHitPercent, PosInfo* specialSrc);
//	void SplashAttack3(int, struct PosInfo, int, struct MSG_TYPE1_TWODWORD *, int, int);
//	void SplashNapalmBeat(struct SKILLATTACK_MSG *, short, short, int, unsigned long);
//	void GetPushedPosition2(int, int, int, int, struct PosInfo &);
//	void GetSplashCells(struct PosInfo, struct PosInfo, int, int, struct PosInfo *);
//	void GetSplashCells2(struct PosInfo, struct PosInfo, int, struct PosInfo *);
//	int GetFireWallNeighborCells(short, short, int, int, int *);
//	void NotifyUseSkill(unsigned short, unsigned long, unsigned long, short, bool);
//	void NotifyGroundSkillUsing(unsigned short, short, short, short, unsigned long);
	virtual void DetectHidingCharacter(int range, SKILLATTACK_MSG* msg, int plusAttPower, int deltaX, int deltaY);
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
	void OnChangeDefense(int defense, BOOL isInit);
//	int SetParameter();
//	void InitCache();
	void OnChangeGuildID();
	void SetATKPercentInfo(int SKID, DWORD time, int val);
	void SetDEFPercentInfo(int SKID, DWORD time, int val);
	void ResetATKPercentInfo(int SKID);
	void ResetDEFPercentInfo(int SKID);
//	void SetMATKPercentInfo(int, unsigned long, int);
//	void SetMDEFPercentInfo(int, unsigned long, int);
//	void ResetMATKPercentInfo(int);
//	void ResetMDEFPercentInfo(int);
//	unsigned short GetSpellCasting();
	virtual void ModifyAttackPowerByEffective(CCharacter* ch, int attackProperty, int& damage);
	virtual BOOL IsSiegeMode();
//	int OnWhereMyMob_XPos(const char *);
//	int OnWhereMyMob_YPos(const char *);
//	unsigned long FindMyMobAID(const char *);
//	void SetSpellCasting(const unsigned short);
	virtual int GetSKLevel(const int in_SKID) const;
	virtual bool OpSKToChar_SKID_ML_DEVOTION(CCharacter* in_TargetCH, MSG_TYPE4_FIVEDWORD* in_pData);
	virtual void OpSKToSelf_SKID_ML_DEFENDER(const int in_SKlevel);
	virtual void OpSKToSelf_SKID_MER_MAGNIFICAT(const int in_SKLevel, const int in_EFST, const int in_EFST_time, const int in_EFST_value);
	virtual void OpSKToSelf_SKID_MER_AUTOBERSERK();
	virtual void NotifyParameter(unsigned short type, int count);
	virtual void ResetEffective_after_EFST_DEFENDER();

public:
	class Neighbor
	{
		/* this+0 */ std::vector<CCharacter*>* m_pSectionList;
		/* this+4 */ CCharacter* m_pCharacter;

		Neighbor(CCharacter* in_pCharacter, std::vector<CCharacter*>* in_pSectionList) : m_pSectionList(in_pSectionList), m_pCharacter(in_pCharacter) { }
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
	virtual int GetEmblemVersion();
//	unsigned long GetNeighborPcNumber(int);
//	void CheckSpecialState(unsigned long);
//	void CheckCondition(unsigned long);
//	CItem* CreateItemOnMap(unsigned short, int, int, int);
	virtual short GetAttackSuccessPercent(CCharacter* other, const int in_SKATKPattern, int isRNGATK, const int in_SKID); //NOTE: possibly unintended overload

protected:
	int GetAttackFinalDamage(CCharacter* other, int plusATKPercent, int plusHITPercent, unsigned short SKID, int SKProperty, int isRNGATK);

public:
	virtual int GetAttackFinalDamage(ATTACK_INFO* info);
//	void AddSpecialZoneList(unsigned long);
//	void DelSpecialZoneList();
	virtual int SetEffective(int index, int tm, int val1, int val2, int val3, BOOL isSend);
	virtual void ResetEffective(int index, int val);
	virtual bool IsGroundEffective(int index, int& SKID, bool& isPlaySolo);
	virtual void ProcessGroundEffective(int index, int SKID, bool isPlaySolo);
	virtual void SetOnShowEFST(int value);
	virtual void SetOffShowEFST(int value);
	virtual void OnChangeStatusAmount(int SKID, unsigned short type, unsigned long time, int amount);
	virtual void NotifyStatusAmount(unsigned short type, int amount);
	virtual bool ApplyStatusAmount(unsigned short type, int& amount);
	virtual short GetBodyState();
	virtual short GetHealthState();
	void Chat(const char* buf, unsigned long color);
	virtual char GetCampID();
	virtual void SetCampID(char campID);
	short GetAttSucPercent();
	virtual int GetModifiedTargetStatusDEF(CCharacter* target);

private:
	virtual int GetModifiedTargetStatusDEF2(CCharacter* in_cpTargetCH);
	virtual int GetModifiedTargetItemMDEF2(CCharacter* in_cpTargetCH);

public:
	virtual void ApplyExtraDEF(int& def, CCharacter* in_cpAtkerCH);
	virtual void ApplyExtraMDEF(int& mdef);
//	int GetMinusStdPropertyDamage(class CCharacter *, int, unsigned short, int);
//	int GetRoomSize();
	int GetPhysicsFinalDamage(CCharacter* in_cpTarget, int in_PlusATKPercent, int in_PlusHITPercent, unsigned short in_SKID, int in_SKATKProperty, int in_IsRangeAttack);
	int GetPhysicsBaseATKPower(CCharacter* in_cpTarget, unsigned short in_SKID, int in_ATKProperty);
//	int GetMagicFinalDamage(class CCharacter *, int, int, unsigned short);
//	int GetMagicFinalATKPower(class CCharacter *, int, int, unsigned short, int);
//	int GetMagicTargetSKValue(class CCharacter *, const int, const unsigned short);
//	int GetTargetSTDValue(class CCharacter *, int, unsigned short, int);
	BOOL ProcessRevengeEnemy(CCharacter* in_cpTarget);

protected:
	virtual void InitCore();
//	void AddMYMob(unsigned long);
//	void OnMyMonsterDead(unsigned long, unsigned long);
//	int StartPath(struct PACKET_CZ_REQUEST_MOVE *, unsigned long);
	BOOL OnMove(PACKET_CZ_REQUEST_MOVE* p);
	void MultiCastStateInfo();
//	void NotifyInfoToSection();
	short GetCurrentState();
	virtual int GetEffectState();
//	int GetMYMobSize();
	BOOL SpawnMyMob(unsigned long spriteType);
	void OnResetMyMob();
//	void UseSkillToCharacter(int, int, int);
//	int GetMagicAttackFinalDamage(class CCharacter *, int, int, unsigned short);
	virtual int GetMagicAttPower();
	virtual int SkillAttack(SKILLATTACK_MSG* in_Msg, int in_PlusATKPercent, int in_PlusHITPercent, const bool in_bHideSkill);
//	void SplashDamageAttack(int, short, short, short, int, unsigned long);
//	void OnMoveStop(int, int, int, const bool);
//	void OnCM_KNOCKBACK(const int, const int, const bool, const bool);
//	void OnCM_PROGRESSBAR(const unsigned long, const unsigned long);
	void OnChangeAGI(int par1, int par2, int par3);
	void OnChangeDEX(int par1, int par2, int par3);
	void OnChangeINT(int par1, int par2, int par3);
	void OnChangeLUK(int par1, int par2, int par3);
	void OnChangeSTR(int par1, int par2, int par3);
	void OnChangeVIT(int par1, int par2, int par3);
//	void InitThePCCacheInfo(int);
	virtual void OnShowEffect(int effect);
	virtual void OnShowEffect3(int effect, int numdata);
	virtual void OnShowScript(const char* In_Msg);
	virtual short GetAvoidPercent_Client();

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
	void SetUseTomb(const bool bUse);
	bool GetUseTomb();
	void DisappearBossTomb();

protected:
	/* this+   0 */ //CActor baseclass_0;
	/* this+1276 */ NpcTimeInfo m_characterTimeInfo;
	/* this+1336 */ CNPCSkill m_npcSkill;
	/* this+1456 */ std::list<EATING_ITEM_INVENTORY*> m_eatingItem;
	/* this+1468 */ CMemoryMgr<EATING_ITEM_INVENTORY> m_eatingItemMPool;
	/* this+1504 */ CHostPathInfo m_pathInfo;
	/* this+1560 */ CNPCUpdater m_npcUpdater;
	/* this+1580 */ unsigned long m_currentState; // stateList
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
	/* this+2024 */ CNPCStateUpdater m_npcStateUpdater;
	/* this+2064 */ unsigned char m_npcType; // enum _npcType

protected:
//	unsigned long GetRoomID();
//	void SetRoomID(unsigned long);

protected:
	/* this+2068 */ CPollTimer m_emoticonTM;
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

	friend class CNPCStateUpdater;
	friend class CNPCUpdater; // IsMyArea()
	friend class CSectionMgr; // IsEmptyPos()
	friend int LuaGlueFunc_Skill(lua_State* L); // FIXME
	friend int LuaGlueFunc_Attack(lua_State* L); // FIXME
	friend int LuaGlueFunc_SummaryUpdate(lua_State* L); // FIXME
	friend int LuaGlueFunc_Move(lua_State* L); // FIXME
	friend int LuaGlueFunc_Revival(lua_State* L); // FIXME
};
C_ASSERT( sizeof CNPC == 2104 );
