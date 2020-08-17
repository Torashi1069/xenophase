#pragma once
#include "Character.h"


struct EFFECTIVE_INFO
{
	/* this+ 0 */ unsigned long time;
	/* this+ 4 */ int val[3];
	/* this+16 */ unsigned int Attr;
	enum enumATTR { ATTR_SEND = 1, ATTR_MULTICAST = 2 };
	/* this+20 */ BOOL bDeleteDBWhenReset;
};


struct AmountValue
{
	/* this+0 */ DWORD time;
	/* this+4 */ int resetAmount;

	AmountValue(DWORD _time, int _resetAmount)
	{
		time = _time;
		resetAmount = _resetAmount;
	}
};


class CActor : public CCharacter
{
public:
	/* this+  0 */ //CCharacter baseclass_0;

public:
//	int GetSPcostForSkill(const int , const int , const int , CSkillTypeInfo* );

protected:
	/* this+ 888 */ std::map<int,int> m_MspdSlowPercentEfstList;
	/* this+ 904 */ std::map<int,int> m_MspdHastePercentEfstList;
	/* this+ 920 */ std::map<int,int> m_AspdSlowPercentEfstList;
	/* this+ 936 */ std::map<int,int> m_AspdHastePercentEfstList;

public:
//	void InsertMspdSlowPercentEfstList(const int , const int );
//	void InsertMspdHastePercentEfstList(const int , const int );
//	void InsertAspdSlowPercentEfstList(const int , const int );
//	void InsertAspdHastePercentEfstList(const int , const int );

private:
	/* this+ 952 */ BYTE m_FixedSKcastingTMvar[40]; //CFixedSKcastingTMvar m_FixedSKcasingTMvar; //TODO

public:
//	int ModifyFixedSKcastingTM(const int , const int );
//	void FixedSKcastingTMPropertyAmountAdd(std::tr1::shared_ptr<FixedSKcastingTMvarStuff::CItem>& );
//	void FixedSKcastingTMPropertyPermillAdd(std::tr1::shared_ptr<FixedSKcastingTMvarStuff::CItem>& );
//	void FixedSKcastingTMPropertyAmountRemove(const FixedSKcastingTMvarStuff::CIdentity& );
//	void FixedSKcastingTMPropertyPermillRemove(const FixedSKcastingTMvarStuff::CIdentity& );

public:
//	const char* GetNamePtr();

protected:
	/* this+ 992 */ int m_BodyStateValue;
	/* this+ 996 */ unsigned long m_BodyStateTime[3];
	/* this+1008 */ unsigned long m_HealthStateTime[9][2];
	/* this+1080 */ unsigned long m_HealthStateValue[9];

public:
//	unsigned long GetHealthStateRemainMS(const int );
//	unsigned long GetBodyStateRemainMS(const int );
//	short GetHealthState();
//	void ResetHealthState(short );

protected:
	/* this+1116 */ int m_resistByProperty[10];

	typedef std::map<int,unsigned long> EFFECTSTATEMAP;
	typedef std::map<int,unsigned long>::iterator EFFECTSTATEMAP_ITER;
	/* this+1156 */ EFFECTSTATEMAP m_effectStateTimeL;

//	void SetEffectStateTimeInfo(unsigned long , int );
//	void ResetEffectState(int );
//	void SetEffectState(int );

public:
	int GetStateDBFmt(unsigned char* out_pData, const int in_MaxBytes) const;
//	void SetStateDBFmt(const unsigned char* , const int );
//	void ReduceSPByUseSkill(int );
//	bool IsExistItem(int , int , bool );
//	bool ConsumeItemByUseSkill(int , int , bool );
//	short GetAttackSuccessPercent(CCharacter* , const int , int );
//	int GetAttackFinalDamage(ATTACK_INFO* );
//	int SkillAttack(SKILLATTACK_MSG* , int , int , const bool );
//	short SplashAttack(int , short , short , int , int , int , unsigned long , void* , int , int );
//	int SplashAttack2(int , PosInfo , int , int , int , MSG_TYPE1_TWODWORD* , int , int , PosInfo* );
//	int SetHandicapState(int, CCharacter* , int , int , int , int , int );
//	bool ResetHandicapState(CActor* , const int );
//	const unsigned long GetHandcapStateRemainTime(const int );
//	bool IsHandicapState(const int );
//	int GetCountInArea(int , int , int , int , int , int );
//	int GetModifiedTargetItemDEF(CCharacter* );
//	int GetModifiedTargetStatusDEF(CCharacter* );
//	int GetModifiedTargetItemMDEF(CCharacter* );
//	int GetModifiedTargetTotalDEF(CCharacter* );
//	int GetModifiedTargetTotalMDEF(CCharacter* );
//	void ApplyExtraDEF(int& , CCharacter* );
//	void ApplyExtraMDEF(int& );
//	int GetModifiedDamageByTargetDEF(CCharacter* , const int , const int );
//	int GetModifiedDamageByTargetMDEF(CCharacter* , const int , const int );
private:
//	int GetModifiedTargetStatusMDEF2(CCharacter* );
//	int GetModifiedTargetItemMDEF2(CCharacter* );
//	int GetModifiedTargetStatusDEF2(CCharacter* );
//	int GetModifiedTargetItemDEF2(CCharacter* );

public:
//	int SetEffective(int , int , int , int , int , int );
//	int GetEffective(int , int );
//	void UpdateEffective(int , int , int );
//	void ResetEffective(int , int );
//	void ResetAllEffective(int );

public:
	enum
	{
		MODIFYEFFECTIVE_VAL1 = 1,
		MODIFYEFFECTIVE_VAL2 = 2,
		MODIFYEFFECTIVE_VAL3 = 4,
		MODIFYEFFECTIVE_TIME = 8,
	};

public:
//	void ModifyEffective(const unsigned int, const int, const unsigned long, const int, const int, const int);
//	bool SetEffectiveCheckup(const int, int &, int &, int &, int &);
//	void SetEffectiveComplete(const int, const int, const int, const int, const int);
//	bool ResetEffectiveCheckup(const int, const int, struct EFFECTIVE_INFO *);
//	void ResetEffectiveComplete(const int, const int, const int, const int);
//	void UpdateEffectiveTime(int, int);
//	struct EFFECTIVE_INFO * GetEffectiveInfo(int);
//	void ProcessAllEffective();
//	bool IsGroundEffective(int, int &, bool &);
//	void ProcessGroundEffective(int, int, bool);
//	void ProcessCheckEffective(int, struct EFFECTIVE_INFO *);
//	void SetOnShowEFST(int);
//	void SetOffShowEFST(int);
//	void GetModifiedHealAmount(int &);
//	void GetModifiedSPHealAmount(int &);
//	void OnChangeStatusAmount(int, unsigned short, unsigned long, int);
//	void NotifyStatusAmount(unsigned short, int);
//	void ResetStatusAmount(unsigned short, unsigned short);
//	void ProcessStatusAmount();
//	void GetPushedPosition(struct PosInfo, struct PosInfo, int, struct PosInfo &);
//	CCharBuff& InstanceCharBuff();
//	void BeginSkillPostDelay(unsigned short, int);
//	void BeginSkillSinglePostDelay(unsigned short, int);
//	void BeginSkillGlobalPostDelay(unsigned short, int);
//	void SetSkillSinglePostDelay(unsigned short, unsigned long);

protected:
	typedef std::map<int,EFFECTIVE_INFO> EFFECTIVE_CONTAINER;
	/* this+1172 */ EFFECTIVE_CONTAINER m_effectiveList;
	/* this+1188 */ std::map<int,std::map<unsigned short,AmountValue>> m_statusEffInfo;
	/* this+1204 */ BYTE m_charBuff2[52]; //CCharBuff m_charBuff2; //TODO

protected:
//	int GetPlusPropertyDamage(CCharacter* , int , int );
//	int GetModifyAttackPowerByEffective_Variation(CCharacter* , int , int );

public:
//	int GetAdditionalSkillSPCost(const int );
//	int GetDirection(const PosInfo& , const PosInfo& );
//	void GetForwardPosition(int , int , int , int , PosInfo& );

protected:
	virtual void Init();

public:
//	void ValidTest_ItemUseBlock();
//	void ValidTest_MoveBlock();
//	void ValidTest_SkillUseBlock();
//	void ValidTest_MeleeAtkBlock();
//	void ValidTest_ChatBlock();

protected:
	/* this+1256 */ BYTE m_Scheduler[20]; //ActorScheduler::CScheduler m_Scheduler; //TODO

public:
//	void Process();
//	void InsertSchedule(std::tr1::shared_ptr<ActorScheduler::CTask>& );
//	void DeleteSchedule(const unsigned long );

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
	virtual bool IsActor();
//	SKILL_RETURN Actor_ThirdJobSkillAttackToCharacter(unsigned short, CCharacter* , MSG_TYPE_SKILLDATA* , SKILLATTACK_MSG* );
//	SKILL_RETURN Actor_ThirdJobSkillOperateToCharacter(unsigned short, CCharacter* , MSG_TYPE_SKILLDATA* );
//	SKILL_RETURN Actor_ThirdJobSkillToGround(unsigned short , MSG_TYPE_SKILLDATA* );
//	void RK_DEATHBOUND_REFLECT(CCharacter* , int& , short& );
//	void KnockBack(CCharacter* , int );
//	bool IsRightWeaponItemClass(short , short , short );
//	void Broadcast_ZC_NOTIFY_SKILL2(int , unsigned short , int );
//	void SkillUseAck(unsigned short , unsigned short , bool , unsigned char );

protected:
//	void SetBodyStateImpl(const int );
//	void ResetBodyStateImpl(const int );

public:
//	void DetectHidingCharacter(int , SKILLATTACK_MSG* , int , int , int );
//	int UpdateResistByProperty(const int , const int );
//	void SetEffective_POISONINGWEAPON(const int , CCharacter* , int );
//	short GetBodyState();

private:
//	SKILL_RETURN RK_SONICWAVE(CCharacter* , MSG_TYPE_SKILLDATA* , SKILLATTACK_MSG* );
//	SKILL_RETURN RK_DEATHBOUND(MSG_TYPE_SKILLDATA* );
//	SKILL_RETURN RK_WINDCUTTER(const MSG_TYPE_SKILLDATA& );
//	SKILL_RETURN RK_IGNITIONBREAK(const MSG_TYPE_SKILLDATA& );
//	SKILL_RETURN RK_DRAGONHOWLING(MSG_TYPE_SKILLDATA* );
//	SKILL_RETURN RK_GIANTGROWTH(MSG_TYPE_SKILLDATA* );
//	SKILL_RETURN GC_CLOAKINGEXCEED(const MSG_TYPE_SKILLDATA& );
//	SKILL_RETURN GC_PHANTOMMENACE(const MSG_TYPE_SKILLDATA& );
//	SKILL_RETURN GC_HALLUCINATIONWALK(const MSG_TYPE_SKILLDATA& );
//	void ProcessEffective_ELECTRICSHOCKER();
//	void ProcessEffective_CAMOUFLAGE();

public:
//	bool IsFailStartUseSkill();
//	void SetHandicapStateEFST(CCharacter* , const int , const int , const int , const int );
//	void SetHealthStateTimeInfo(const int , const int , const int );
//	void SetHealthState(short);
};
C_ASSERT( sizeof CActor == 1276 );
