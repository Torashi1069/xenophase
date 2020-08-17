#pragma once
#include "NPC.h"
#include "AsyncDBWork/Effect3rd.h"
#include "shared/PollTimer.h"


struct EXTInfo
{
	/* this+0 */ short DEF;
};


class CNpcHomun : public CNPC
{
public:
	CNpcHomun();
	virtual ~CNpcHomun();

public:
//	virtual void Init();
//	virtual int GetParameterValue(unsigned short , int& );
//	virtual int UpdateParameterValue(unsigned short , int );
//	virtual int OnMsg(CCharacter* , CCharacter* , unsigned long , int , int , int , MSGpar::CVar );
//	virtual void OnProcess();
//	virtual BOOL IsTarget(CCharacter* , unsigned long );
	virtual CCharacter* GetMyOwner();
//	int SkillAttackExt(SKILLATTACK_MSG* , int , int , const bool );
//	static bool staticIsMutationType(const int );
//	static bool staticIsEvolutionType(const int );

private:
	enum { MAX_HOMUN_SPIRITS_CNT = 10 };

	typedef std::multiset<unsigned long> SPIRITS_TIME_CONTAINER;
	/* this+2104 */ SPIRITS_TIME_CONTAINER m_spiritsTime;

private:
//	void AddSpirits(const int);
//	void MinusSpirits(const int);
//	void UpdateSpiritsInfo();
	void NotifySpiritsInfo();
	void ParseSpiritsSaveInfo();
	void SetEffectiveSpiritsSaveInfo();
//	virtual void SetSkillSinglePostDelay(unsigned short , unsigned long );
//	bool IsEndPostdelaySkill(const unsigned short);
	int GetOwnerCategoryThirdJob();
//	bool IsMutationType();
//	short GetCategoryMutationJobType();
//	short GetCategoryEvolutionJobType();
//	short GetCategoryBirthJobType();
//	int IsSatisfySkill(const unsigned short, const short, const short);
//	unsigned short GetHomunFoodItemID();
//	void SaveHomunData();
//	void OnOpSkillToCharacterMER(const unsigned short, const int, struct MSG_TYPE4_FIVEDWORD *);
//	void OnOpSkillToGroundMER(const unsigned short, const int, struct MSG_TYPE5_SIXDWORD *);
//	void OnTouchedSkillObjectMER(int, int, int);
//	void OnProcessEffect_Attack(class CCharacter *, const int, const int, const int);
//	enum CActor::SKILL_RETURN MH_NEEDLE_OF_PARALYZE(class CCharacter *, struct SKILLATTACK_MSG &);
//	enum CActor::SKILL_RETURN MH_PAIN_KILLER(class CCharacter *, const int);
//	enum CActor::SKILL_RETURN MH_POISON_MIST(const int, const int, const int);
//	void MH_POISON_MIST_OnTouched(class CCharacter *, const unsigned long, const int, const int, const short);
//	enum CActor::SKILL_RETURN MH_SUMMON_LEGION(class CCharacter *, const int);
//	enum CActor::SKILL_RETURN MH_ERASER_CUTTER(class CCharacter *, struct SKILLATTACK_MSG &);
//	enum CActor::SKILL_RETURN MH_XENO_SLASHER(const int, const int, const int);
//	enum CActor::SKILL_RETURN MH_OVERED_BOOST(class CPC *, const int);
//	enum CActor::SKILL_RETURN MH_SILENT_BREEZE(class CCharacter *, const int);
//	enum CActor::SKILL_RETURN MH_LIGHT_OF_REGENE(class CPC *, const int);
//	enum CActor::SKILL_RETURN MH_STYLE_CHANGE();
//	void MH_STYLE_CHANGEoperation(const bool);
//	enum CActor::SKILL_RETURN MH_SONIC_CLAW(class CCharacter *, struct SKILLATTACK_MSG &);
//	enum CActor::SKILL_RETURN MH_SILVERVEIN_RUSH(const int);
//	enum CActor::SKILL_RETURN MH_MIDNIGHT_FRENZY(const int);
//	enum CActor::SKILL_RETURN MH_STAHL_HORN(class CCharacter *, struct SKILLATTACK_MSG &);
//	enum CActor::SKILL_RETURN MH_GOLDENE_FERSE(const int);
//	enum CActor::SKILL_RETURN MH_STEINWAND(const int);
//	enum CActor::SKILL_RETURN MH_HEILIGE_STANGE(class CCharacter *, struct SKILLATTACK_MSG &);
//	enum CActor::SKILL_RETURN MH_ANGRIFFS_MODUS(const int);
//	enum CActor::SKILL_RETURN MH_TINDER_BREAKER(class CCharacter *, struct SKILLATTACK_MSG &);
//	enum CActor::SKILL_RETURN MH_CBC(const int);
//	enum CActor::SKILL_RETURN MH_EQC(const int);
//	enum CActor::SKILL_RETURN MH_MAGMA_FLOW(const int);
//	void MH_MAGMA_FLOWoperation();
//	enum CActor::SKILL_RETURN MH_GRANITIC_ARMOR(const int);
//	enum CActor::SKILL_RETURN MH_LAVA_SLIDE(const int, const int, const int);
//	void MH_LAVA_SLIDE_OnTouched(class CCharacter *, const unsigned long, const int, const int, const short);
//	enum CActor::SKILL_RETURN MH_PYROCLASTIC(const int);
//	enum CActor::SKILL_RETURN MH_VOLCANIC_ASH(const int, const int, const int);
//	void MH_VOLCANIC_ASH_OnTouched(class CCharacter *, const unsigned long, const int, const int, const short);

public:
//	void UpdateSkillDB(const unsigned short, struct HO_SKINFO &);
//	void LoadSkill(const class std::map<unsigned short,HO_SKINFO,std::less<unsigned short>,std::allocator<std::pair<unsigned short const ,HO_SKINFO> > > &);
//	bool IsReadyMutationHomun();
//	void CompleteMutationHomun(const int, const struct HOMUN_DBINFO *, const class std::map<unsigned short,HO_SKINFO,std::less<unsigned short>,std::allocator<std::pair<unsigned short const ,HO_SKINFO> > > &);
	void GetEffectData(std::vector<Effect3rd::tagEffect3rdDBFmt>& io_List);
	void SetEffectData(const std::vector<Effect3rd::tagEffect3rdDBFmt>& in_EfstList);
	void GetSkillData(std::map<unsigned short,HO_SKINFO>& in_SkillSave);
//	void OnAttacked(const int);
//	int GetNumOfSpirits();
//	virtual int GetBaseFlee();
	virtual void Send(const int in_Length, char* in_pBuffer);
//	void SendStateHomun(char, int);
//	void OnTimerHomun();
//	void OnReqRename(char *);
//	void SetCharInfo(struct HOMUN_DBINFO *);
//	void InitProperty();
//	void InitTimer(unsigned long);
//	void InitConditionTime();
//	void IsLevelUp();
//	void UpdateHomunDBInfo(struct HOMUN_DBINFO *);
//	void SetModifiedState(int);
//	void ResetModifiedState(int);
//	int EvolutionHomun();
//	int IsEvolutionType();
//	void StartUseSkill();
//	int IsSkillUsable(unsigned short);
//	int IsSkillEnable(unsigned short, int, class CCharacter *);
	virtual short GetSKLevel(unsigned short SKID);
//	void UpgradeSKLevel(unsigned short);
	CPC* GetOwner();
//	int GetSP();
//	virtual int GetMaxHP();
//	virtual int GetMaxSP();
//	short GetStrValue();
//	virtual short GetDexValue();
//	short GetVitValue();
//	virtual short GetIntValue();
//	short GetAgiValue();
//	int GetLukValue();
//	int GetFullness();
//	int GetRelation();
//	void ProcessEffect_ATK(class CCharacter *, int &, int, int);
//	int GetInvincibleTimeInfo(int);
//	short GetJobType();
//	short GetRelationGrade(short);
	virtual void NotifyStatusAmount(unsigned short type, int amount);
//	virtual bool ApplyStatusAmount(unsigned short, int &);

private:
//	virtual void InitCore();
	virtual BOOL IsRechargeTime();
//	void ApplyLevelStatWeight();
//	virtual int GetMagicAttPower();
//	virtual short GetDefencePoint();
//	virtual short GetStatusDef();
//	virtual void NotifyParameter(const int, const int);
//	void UpdateMagicItemDefPower();
//	virtual short GetStatusMagicDef();
//	virtual short GetItemMagicDef();
//	int GetMATKPoint_Client();
//	int GetMDEF_Client();

private:
	/* this+2120 */ struct {
		/* this+0 */ int minimum;
		/* this+4 */ int maximum;
	} m_MATK;

private:
//	virtual int GetItemAttPower();
//	virtual int GetStatusAttPower();
//	int GetItemPowerMin();
//	int GetItemPowerMax();
//	int GetStatusMagicPower();
//	int GetMagicItemPowerMin();
//	int GetMagicItemPowerMax();
//	virtual short GetAvoidPercent_Client();
//	void CheckState(unsigned long);
//	void SaveCharInfo(int);
//	void DeleteCharInfo(int);
//	int AddSkill(unsigned short, struct HO_SKINFO *, bool, int);
//	struct HO_SKINFO * GetSkill(unsigned short);
//	void NotifyAllSKInfo();
//	void NotifySKInfo(unsigned short, int);
//	void ChkAllEnableSkill();
//	void ApplyPassiveSkill(unsigned short, short);
//	void AddFinalSkill();
//	void OnChangedHP();
//	void OnChangedSP();
//	void OnFeed(class CPC *);
//	void OnAddExp(class CCharacter *, int, int);
//	void OnShareExp(class CCharacter *, int, int);
//	void ModifyFullness(int);
//	void ModifyRelationship(float);
	void SendProperty();
//	void SetInvincibleTimeInfo(unsigned long, int);
//	void SetBodyStateTimeInfo(unsigned long, unsigned long, int);
	short GetATKPoint_Client();
	short GetCRI_Client();
	short GetDEF_Client();
//	short GetATKTime_Client();
//	int GetFullnessGrade(int);
//	int GetRecoverSPD_HP();
//	int GetRecoverSPD_SP();
//	int GetEmotion_Feed(int, int);
//	void UpdateStatusATKpower();
//	void UpgradeStatus_LevelUp();
//	void OPSkillToSelf(int, int, int);
//	void ATKSkillToChar(int, int, int);
//	int SK_LIF_Heal(class CPC *, const struct MSG_TYPE4_FIVEDWORD &);
//	int SK_LIF_Avoid(class CPC *, struct MSG_TYPE4_FIVEDWORD *);
//	int SK_LIF_Change(class CPC *, struct MSG_TYPE4_FIVEDWORD *);
//	int SK_AMI_Castle(class CPC *);
//	int SK_AMI_Defence(class CPC *, struct MSG_TYPE4_FIVEDWORD *);
//	int SK_AMI_BloodLust(class CPC *, struct MSG_TYPE4_FIVEDWORD *);
//	int SK_FLI_Fleet(class CPC *, struct MSG_TYPE4_FIVEDWORD *);
//	int SK_FLI_Speed(struct MSG_TYPE4_FIVEDWORD *);
//	int SK_VAN_Chaotic(class CPC *, struct MSG_TYPE4_FIVEDWORD *);
//	int SK_VAN_Explosion(class CPC *, struct MSG_TYPE4_FIVEDWORD *);

private:
	/* this+2128 */ CPollTimer m_timerF;
	/* this+2136 */ CPollTimer m_timerHunger;
	/* this+2144 */ CPollTimer m_timerState;
	/* this+2152 */ int m_modified;
	/* this+2156 */ int m_fullGrade;
	/* this+2160 */ int m_fullness;
	/* this+2164 */ float m_relation;
	/* this+2168 */ int m_SKPoint;
	/* this+2172 */ std::map<unsigned short,HO_SKINFO> m_skill;
	/* this+2188 */ EXTInfo m_EXTInfo;
};
