#pragma once
#include "ActorScheduler.h"
#include "Character.h"
#include "CharBuff.h"
#include "FixedSKcastingTMvar.h"
#include "Struct.h"
#include "ZoneProcess.h"
class CSkillTypeInfo;


enum SHOW_EFST_TYPE
{
	SHOW_EFST_NORMAL           = 0x00000,
	SHOW_EFST_QUICKEN          = 0x00001,
	SHOW_EFST_OVERTHRUST       = 0x00002,
	SHOW_EFST_ENERGYCOAT       = 0x00004,
	SHOW_EFST_EXPLOSIONSPIRITS = 0x00008,
	SHOW_EFST_STEELBODY        = 0x00010,
	SHOW_EFST_BLADESTOP        = 0x00020,
	SHOW_EFST_AURABLADE        = 0x00040,
	SHOW_EFST_REDBODY          = 0x00080,
	SHOW_EFST_LIGHTBLADE       = 0x00100,
	SHOW_EFST_MOON             = 0x00200,
	SHOW_EFST_PINKBODY         = 0x00400,
	SHOW_EFST_ASSUMPTIO        = 0x00800,
	SHOW_EFST_SUN_WARM         = 0x01000,
	SHOW_EFST_REFLECT          = 0x02000,
	SHOW_EFST_BUNSIN           = 0x04000,
	SHOW_EFST_SOULLINK         = 0x08000,
	SHOW_EFST_UNDEAD           = 0x10000,
	SHOW_EFST_CONTRACT         = 0x20000,
};


enum RESET_EFST_TYPE
{
	RESET_EFST_DEAD                                       = 0,
	RESET_EFST_DISPEL                                     = 1,
	RESET_EFST_PRETEND_DEAD                               = 2,
	RESET_EFST_TAROT                                      = 3,
	RESET_EFST_ALL                                        = 4,
	RESET_EFST_DEBUFF                                     = 5,
	RESET_EFST_CLEARANCE                                  = 6,
	RESET_EFST_GC_NEWPOISON                               = 7,
	RESET_EFST_WANDERERandMINSTREL_OVERLAPDENY            = 8,
	RESET_MADOGEAR                                        = 9,
	RESET_EFST_WANDERERandMINSTREL_OVERLAPDENY_GROUP_NONE = 10,
	RESET_EFST_WANDERERandMINSTREL_OVERLAPDENY_GROUP_A    = 11,
	RESET_EFST_WANDERERandMINSTREL_OVERLAPDENY_GROUP_B    = 12,
	RESET_EFST_BANISHING_BUSTER                           = 13,
};


struct ATTACK_INFO
{
	ATTACK_INFO()
	{
		this->plusATTPowerPercent = 100;
		this->plusATTSuccessPercent = 100;
		this->target = 0;
		this->position = 2;
		this->skillProperty = 0;
		this->calculateType = 1;
		this->isRangeAttack = FALSE;
		this->SKID = 0;
		this->skLevel = 0;
	}

	/* this+ 0 */ CCharacter* target;
	/* this+ 4 */ int position;
	/* this+ 8 */ int skillProperty;
	/* this+12 */ int plusATTPowerPercent;
	/* this+16 */ int plusATTSuccessPercent;
	/* this+20 */ int calculateType;
	/* this+24 */ BOOL isRangeAttack;
	/* this+28 */ unsigned short SKID;
	/* this+30 */ short skLevel;
};


struct EFFECTIVE_INFO
{
	/* this+ 0 */ DWORD time;
	/* this+ 4 */ int val[3];
	/* this+16 */ unsigned int Attr;
	enum enumATTR { ATTR_SEND = 1, ATTR_MULTICAST = 2 };
	/* this+20 */ BOOL bDeleteDBWhenReset;
};


class CActor : public CCharacter
{
public:
	/* this+  0 */ //CCharacter baseclass_0;

public:
	virtual int GetSPcostForSkill(const int in_SKID, const int in_SKLevel, const int in_SKType, CSkillTypeInfo* in_cpSKTypeInfo);

protected:
	/* this+ 888 */ std::map<int,int> m_MspdSlowPercentEfstList;
	/* this+ 904 */ std::map<int,int> m_MspdHastePercentEfstList;
	/* this+ 920 */ std::map<int,int> m_AspdSlowPercentEfstList;
	/* this+ 936 */ std::map<int,int> m_AspdHastePercentEfstList;

public:
	void InsertMspdSlowPercentEfstList(const int , const int ); //TODO
	void InsertMspdHastePercentEfstList(const int , const int ); //TODO
	void InsertAspdSlowPercentEfstList(const int , const int ); //TODO
	void InsertAspdHastePercentEfstList(const int , const int ); //TODO

private:
	/* this+ 952 */ CFixedSKcastingTMvar m_FixedSKcasingTMvar;

public:
	virtual int ModifyFixedSKcastingTM(const int in_TM, const int in_SKID);
	void FixedSKcastingTMPropertyAmountAdd(std::tr1::shared_ptr<FixedSKcastingTMvarStuff::CItem>& ); //TODO
	void FixedSKcastingTMPropertyPermillAdd(std::tr1::shared_ptr<FixedSKcastingTMvarStuff::CItem>& ); //TODO
	void FixedSKcastingTMPropertyAmountRemove(const FixedSKcastingTMvarStuff::CIdentity& ); //TODO
	void FixedSKcastingTMPropertyPermillRemove(const FixedSKcastingTMvarStuff::CIdentity& ); //TODO

public:
	virtual const char* GetNamePtr() const = 0;

protected:
	/* this+ 992 */ int m_BodyStateValue;
	/* this+ 996 */ DWORD m_BodyStateTime[3];
	/* this+1008 */ DWORD m_HealthStateTime[9][2];
	/* this+1080 */ unsigned long m_HealthStateValue[9];

public:
	DWORD GetHealthStateRemainMS(const int in_HealthState) const;
	DWORD GetBodyStateRemainMS(const int in_BodyState) const;
	virtual short GetHealthState() { return 0; }
	virtual void ResetHealthState(short state) { return; }

protected:
	/* this+1116 */ int m_resistByProperty[10];

	typedef std::map<int,unsigned long> EFFECTSTATEMAP;
	typedef std::map<int,unsigned long>::iterator EFFECTSTATEMAP_ITER;
	/* this+1156 */ EFFECTSTATEMAP m_effectStateTimeL;

	virtual void SetEffectStateTimeInfo(unsigned long time, int state) = 0;
	virtual void ResetEffectState(int state) = 0;
	virtual void SetEffectState(int state) = 0;

public:
	int GetStateDBFmt(unsigned char* out_pData, const int in_MaxBytes) const;
	void SetStateDBFmt(const unsigned char* in_pData, const int in_Length);
	virtual void ReduceSPByUseSkill(int sp) { return; }
	virtual bool IsExistItem(int itemID, int count, bool isExternalEffect) { return true; }
	virtual bool ConsumeItemByUseSkill(int itemID, int count, bool isExternalEffect) { return true; }
	virtual short GetAttackSuccessPercent(CCharacter* other, const int in_SKATKPattern, BOOL isRangeAttack) { return 0; }
	virtual int GetAttackFinalDamage(ATTACK_INFO* info) { return 0; }
	virtual int SkillAttack(SKILLATTACK_MSG* msg, int plusATTPowerPercent, int plusATTSuccessPercent, const bool in_bHideSkill) { return 0; }
	virtual short SplashAttack(int val1, short xPos, short yPos, int type, int range, int rangeIn, unsigned long exceptAID, void* msgDataPtr, int val2, int count) { return 0; }
	virtual int SplashAttack2(int plusATTPower, PosInfo dest, int type, int halfWidth, int height, MSG_TYPE1_TWODWORD* msgData, int count, int plusHitPercent, PosInfo* specialSrc) { return 0; }
	BOOL SetHandicapState(int in_state, CCharacter* in_cpTargetCH, int in_percent, int in_preDelayTime, int in_delayTime, BOOL in_isSpell, BOOL in_isFixedDelayTime);
	bool ResetHandicapState(CActor* in_cpTarget, const int in_HandicapState);
	const DWORD GetHandcapStateRemainTime(const int in_HandicapState);
	bool IsHandicapState(const int in_HandicapState);
	int GetCountInArea(int xPos, int yPos, int range, BOOL isAffectPlayer, BOOL isAffectTrap, BOOL isDeadPlayer);
	virtual int GetModifiedTargetItemDEF(CCharacter* target);
	virtual int GetModifiedTargetStatusDEF(CCharacter* target);
	virtual int GetModifiedTargetItemMDEF(CCharacter* target);
	int GetModifiedTargetTotalDEF(CCharacter* target);
	int GetModifiedTargetTotalMDEF(CCharacter* target);
	virtual void ApplyExtraDEF(int& def, CCharacter* in_cpAtkerCH) { return; }
	virtual void ApplyExtraMDEF(int& def) { return; }
	virtual int GetModifiedDamageByTargetDEF(CCharacter* in_cpTargetCH, const int in_Damage, const int in_MinimumDamage);
	virtual int GetModifiedDamageByTargetMDEF(CCharacter* in_cpTargetCH, const int in_Damage, const int in_MinimumDamage);
private:
	virtual int GetModifiedTargetStatusMDEF2(CCharacter* in_cpTargetCH);
	virtual int GetModifiedTargetItemMDEF2(CCharacter* in_cpTargetCH);
	virtual int GetModifiedTargetStatusDEF2(CCharacter* in_cpTargetCH);
	virtual int GetModifiedTargetItemDEF2(CCharacter* in_cpTargetCH);

public:
	virtual int SetEffective(int index, int time, int val1, int val2, int val3, BOOL isSendClient) { return 1; }
	virtual int GetEffective(int index, int enumVal);
	virtual void UpdateEffective(int index, int val, int enumVal);
	virtual void ResetEffective(int index, int val) { return; }
	virtual void ResetAllEffective(int resetType); // enum RESET_EFST_TYPE

public:
	enum
	{
		MODIFYEFFECTIVE_VAL1 = 1,
		MODIFYEFFECTIVE_VAL2 = 2,
		MODIFYEFFECTIVE_VAL3 = 4,
		MODIFYEFFECTIVE_TIME = 8,
	};

public:
	void ModifyEffective(const unsigned int , const int , const unsigned long , const int , const int , const int ); //TODO
	bool SetEffectiveCheckup(const int in_Index, int& io_Time, int& io_Val1, int& io_Val2, int& io_val3);
	void SetEffectiveComplete(const int index, const int time, const int val1, const int val2, const int val3);
	bool ResetEffectiveCheckup(const int in_Index, const int in_Val, EFFECTIVE_INFO* io_pInfo);
	void ResetEffectiveComplete(const int in_Index, const int in_Val1, const int in_Val2, const int in_Val3);
	void UpdateEffectiveTime(int index, int time);
	EFFECTIVE_INFO* GetEffectiveInfo(int index);
	void ProcessAllEffective();
	virtual bool IsGroundEffective(int index, int& SKID, bool& isPlaySolo);
	virtual void ProcessGroundEffective(int index, int SKID, bool isPlaySolo) { return; }
	virtual void ProcessCheckEffective(int index, EFFECTIVE_INFO* info);
	virtual void SetOnShowEFST(int value) { return; } // enum SHOW_EFST_TYPE
	virtual void SetOffShowEFST(int value) { return; } // enum SHOW_EFST_TYPE
	virtual void GetModifiedHealAmount(int& healAmount);
	void GetModifiedSPHealAmount(int& spHealAmount);
	virtual void OnChangeStatusAmount(int SKID, unsigned short type, unsigned long time, int amount) { return; }
	virtual void NotifyStatusAmount(unsigned short type, int amount) { return; }
	void ResetStatusAmount(unsigned short SKID, unsigned short type);
	void ProcessStatusAmount();
	void GetPushedPosition(PosInfo src, PosInfo dest, int distance, PosInfo& result);
	CCharBuff& InstanceCharBuff() { return m_charBuff2; }
	void BeginSkillPostDelay(unsigned short SKID, int skLevel);
	void BeginSkillSinglePostDelay(unsigned short SKID, int skLevel);
	void BeginSkillGlobalPostDelay(unsigned short SKID, int skLevel);
	virtual void SetSkillSinglePostDelay(unsigned short SKID, unsigned long delaytime) { return; }

protected:
	typedef std::map<int,EFFECTIVE_INFO> EFFECTIVE_CONTAINER;
	/* this+1172 */ EFFECTIVE_CONTAINER m_effectiveList;
	/* this+1188 */ std::map<int,std::map<unsigned short,AmountValue>> m_statusEffInfo;
	/* this+1204 */ CCharBuff m_charBuff2;

protected:
	int GetPlusPropertyDamage(CCharacter* other, int property, int damage);
	int GetModifyAttackPowerByEffective_Variation(CCharacter* ch, int attackProperty, int in_damage);

public:
	virtual int GetAdditionalSkillSPCost(const int in_SkillID) { return 0; }
	int GetDirection(const PosInfo& src, const PosInfo& dest) const;
	void GetForwardPosition(int xPos, int yPos, int destDir, int distance, PosInfo& result) const;

protected:
	virtual void Init();

public:
	void ValidTest_ItemUseBlock();
	void ValidTest_MoveBlock();
	void ValidTest_SkillUseBlock();
	void ValidTest_MeleeAtkBlock();
	void ValidTest_ChatBlock();

protected:
	/* this+1256 */ ActorScheduler::CScheduler m_Scheduler;

public:
	void Process();
	void InsertSchedule(std::tr1::shared_ptr<ActorScheduler::CTask>& in_TaskPtr);
	void DeleteSchedule(const unsigned long in_Identity);

public:
	CActor();
	virtual ~CActor();

public:
	enum SKILL_RETURN
	{
		SKILL_RETURN_UNKNOWN          = 0,
		SKILL_RETURN_FAIL_CONDITION   = 1,
		SKILL_RETURN_FAIL             = 2,
		SKILL_RETURN_SUCCESS          = 3,
		SKILL_RETURN_FAILED_POSTDEALY = 4,
	};

public:
	virtual bool IsActor() { return true; }
	SKILL_RETURN Actor_ThirdJobSkillAttackToCharacter(unsigned short SKID, CCharacter* target, MSG_TYPE_SKILLDATA* skilldata, SKILLATTACK_MSG* msg);
	SKILL_RETURN Actor_ThirdJobSkillOperateToCharacter(unsigned short SKID, CCharacter* target, MSG_TYPE_SKILLDATA* skilldata);
	SKILL_RETURN Actor_ThirdJobSkillToGround(unsigned short SKID, MSG_TYPE_SKILLDATA* skilldata);
	void RK_DEATHBOUND_REFLECT(CCharacter* atker, int& damage, short& leftdamage);
	void KnockBack(CCharacter* target, int distance);
	virtual bool IsRightWeaponItemClass(short class1, short class2, short class3) { return true; }
	void Broadcast_ZC_NOTIFY_SKILL2(int targetAID, unsigned short SKID, int skLevel);
	virtual void SkillUseAck(unsigned short SKID, unsigned short NUM, bool result, unsigned char cause) { return; }

protected:
	virtual void SetBodyStateImpl(const int in_SetBodyState);
	virtual void ResetBodyStateImpl(const int in_ResetBodyState);

public:
	virtual void DetectHidingCharacter(int range, SKILLATTACK_MSG* msg, int plusAttPower, int deltaX, int deltaY) { return; }
	virtual int UpdateResistByProperty(const int in_Property, const int in_offsetValue);
	void SetEffective_POISONINGWEAPON(const int in_PosionEFST, CCharacter* in_cpAtkerCH, int in_DelayTM);
	virtual short GetBodyState() { return 0; }

private:
	SKILL_RETURN RK_SONICWAVE(CCharacter* in_cpTarget, MSG_TYPE_SKILLDATA* in_skilldata, SKILLATTACK_MSG* in_msg);
	SKILL_RETURN RK_DEATHBOUND(MSG_TYPE_SKILLDATA* skilldata);
	SKILL_RETURN RK_WINDCUTTER(const MSG_TYPE_SKILLDATA& in_skilldata);
	SKILL_RETURN RK_IGNITIONBREAK(const MSG_TYPE_SKILLDATA& in_skilldata);
	SKILL_RETURN RK_DRAGONHOWLING(MSG_TYPE_SKILLDATA* skilldata);
	SKILL_RETURN RK_GIANTGROWTH(MSG_TYPE_SKILLDATA* skilldata);
	SKILL_RETURN GC_CLOAKINGEXCEED(const MSG_TYPE_SKILLDATA& in_skilldata);
	SKILL_RETURN GC_PHANTOMMENACE(const MSG_TYPE_SKILLDATA& in_skilldata);
	SKILL_RETURN GC_HALLUCINATIONWALK(const MSG_TYPE_SKILLDATA& in_skilldata);
	void ProcessEffective_ELECTRICSHOCKER();
	void ProcessEffective_CAMOUFLAGE(); //TODO

public:
	bool IsFailStartUseSkill();
	void SetHandicapStateEFST(CCharacter* in_cpTargetCH, const int in_EFSTID, const int in_DelayTime, const int in_Percent, const int in_KeepTime);
	virtual void SetHealthStateTimeInfo(const int in_firstTime, const int in_secondTime, const int in_state);
	virtual void SetHealthState(short state) = 0;
};
C_ASSERT( sizeof CActor == 1276 );
