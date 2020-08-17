#pragma once
#include "CAutoSpellVar.h"
#include "MercenaryDB.h"
class CPC; // #include "PC.h"
#include "PCBattleHomun.h"
#include "PCBattleMercenary.h"
#include "Struct.h"


struct OptionInfo
{
	/* this+ 0 */ MSG_TYPE2_THREEDWORD receiveZENYInfo;
	/* this+12 */ int plusCRI_RANGE;
	/* this+16 */ bool receiveITMGROUP_ID[7];
	/* this+24 */ int reflectMagic;
	/* this+28 */ int damagePercent_Scale[2][3];
	/* this+52 */ int damagePercent_CRI[2];
	/* this+60 */ int healHP_Kill;
	/* this+64 */ int healSP_Kill;
	/* this+68 */ int healHP_Kill_Magic;
	/* this+72 */ int healSP_Kill_Magic;
	/* this+76 */ short plusStatusDEF;
	/* this+78 */ short healSkillPercent;
	/* this+80 */ short neverKnockBack;
	/* this+84 */ int reservedArmorProperty;
	/* this+88 */ int receiveItem_Equip;
};


struct MERSOL_DBINFO
{
	/* this+ 0 */ short faith;
	/* this+ 2 */ short job;
	/* this+ 4 */ short hp;
	/* this+ 6 */ short sp;
	/* this+ 8 */ short lifeTM;
	/* this+12 */ int exp;
	/* this+16 */ int property;
	/* this+20 */ int bodyState;
	/* this+24 */ int healthState;
	/* this+28 */ int effectState;
	/* this+32 */ int summonCount[3];
};


struct PropTM_Info
{
	/* this+ 0 */ std::map<unsigned short,short> propAmount;
	/* this+16 */ unsigned long time;
};


struct HEAL_REGULARLY_INFO
{
	void Set(unsigned long _term, short _amount)
	{
		nextUpdateTime = _term + timeGetTime();
		term = _term;
		amount = _amount;
	}

	/* this+0 */ unsigned long nextUpdateTime;
	/* this+4 */ unsigned long term;
	/* this+8 */ short amount;
};


struct AUTO_ACT_ITEMINFO
{
	/* this+0 */ unsigned long itemID;
	/* this+4 */ short percent;
	/* this+6 */ short time;
};


struct AUTO_ACT_ITEMSCRIPT
{
	/* this+0 */ unsigned long itemID;
	/* this+4 */ unsigned long time;
	/* this+8 */ unsigned char type;
};


struct TARGET_ATTACKED_BUFF
{
	/* this+ 0 */ unsigned long percent;
	/* this+ 4 */ short who;
	/* this+ 6 */ unsigned short buffType;
	/* this+ 8 */ unsigned long time;
	/* this+12 */ unsigned long value;
};


struct SKILL_AUTOSPELL
{
	/* this+ 0 */ unsigned long percent;
	/* this+ 4 */ unsigned long SKID;
	/* this+ 8 */ short who;
	/* this+10 */ short level;
};


struct SKILL_ACTIVE
{
	/* this+ 0 */ unsigned long itemID;
	/* this+ 4 */ unsigned long SKID;
	/* this+ 8 */ unsigned long percent;
	/* this+12 */ unsigned long time;
};


struct SKILL_ACTIVE_OPTION
{
	/* this+0 */ unsigned long itemID;
	/* this+4 */ unsigned long SKID;
	/* this+8 */ unsigned long time;
};


struct _SKILL_ACTIVE_INFO
{
	/* this+ 0 */ std::map<unsigned long,std::list<SKILL_ACTIVE>> skillActiveList;
	/* this+16 */ std::list<SKILL_ACTIVE_OPTION> skillDeactiveList;
	/* this+28 */ unsigned long lastActivatedSkill;
	/* this+32 */ unsigned long lastDeactivatedSkill;
};


struct SKILL_HANDICAP
{
	/* this+0 */ short who;
	/* this+2 */ short state;
	/* this+4 */ int percent;
};


struct AUTOSPELL_MAGIC
{
	/* this+0 */ unsigned long SKID;
	/* this+4 */ short level;
	/* this+6 */ short who;
	/* this+8 */ int percent;
};


class CPCBattle
{
public:
//	void ReflectDamageEx(class CCharacter *, int);

public:
	CPCBattle();
	virtual ~CPCBattle();

public:
	void Init();
	void Reset();
	void SetMyOwner(CPC* pc);
//	void CheckStateChange();
//	void CheckConsumedArrow(int);
//	void ActSkillToChar_ATK(int, int, int);
//	void OPSkillToCharacter(int, int, int);
//	void OPSkillToCharacter_AL_HEAL(const int, const int, const int, const struct MSG_TYPE4_FIVEDWORD *, const int, const int, const int, class CCharacter *);
//	void OPSkillToSelf(int, int, int);
//	struct OptionInfo * GetOptionInfo();
//	int GetPhysicalATKDamage(class CCharacter *, int, struct PACKET_ZC_NOTIFY_ACT *, bool &);
//	int GetMagicATKPower(class CCharacter *, bool);
//	int GetDamagePercent(unsigned long, unsigned short);
//	int GetDamagePercent_SKID(const int, const int);
//	int GetHealPercent_ITEM(unsigned short);
//	class std::map<unsigned short,int,std::less<unsigned short>,std::allocator<std::pair<unsigned short const ,int> > > & GetDropItemList_KILL(int);
	int GetSKCastingTM(CSkillTypeInfo* SKTypeInfo, short skLevel, CCharacter* ch, int x, int y, int spCost);
//	int GetSoulLinkSKCastingTM(unsigned short, short, int);
//	void SetHealPercent_ITEM(unsigned short, int);
//	void SetAutoSpell2(const int, const int, const int, const int, const unsigned int);
//	void SetAutoSpell2_MLEATKED(const int, const int, const int, const int, const unsigned int);
//	void SetAutoSpell2_MLEATKED_Short(const int, const int, const int, const int, const unsigned int);
//	void SetAutoSpell2_MLEATKED_Long(const int, const int, const int, const int, const unsigned int);
//	void SetAutoSpell2_MAGATKED(const int, const int, const int, const int, const unsigned int);
//	void SetAutoSpell2_MLEATK(const int, const int, const int, const int, const unsigned int);
//	void SetAutoSpell2_RANGEATK(const int, const int, const int, const int, const unsigned int);
//	void ResetAutoSpell2(const int, const int, const unsigned int);
//	void ResetAutoSpell2_MLEATKED(const int, const int, const unsigned int);
//	void ResetAutoSpell2_MLEATKED_Short(const int, const int, const unsigned int);
//	void ResetAutoSpell2_MLEATKED_Long(const int, const int, const unsigned int);
//	void ResetAutoSpell2_MAGATKED(const int, const int, const unsigned int);
//	void ResetAutoSpell2_MLEATK(const int, const int, const unsigned int);
//	void ResetAutoSpell2_RANGEATK(const int, const int, const unsigned int);
//	void PauseAutoSpell2(const int, const int, const unsigned int);
//	void PauseAutoSpell2_MLEATKED(const int, const int, const unsigned int);
//	void PauseAutoSpell2_MLEATKED_Short(const int, const int, const unsigned int);
//	void PauseAutoSpell2_MLEATKED_Long(const int, const int, const unsigned int);
//	void PauseAutoSpell2_MAGATKED(const int, const int, const unsigned int);
//	void PauseAutoSpell2_MLEATK(const int, const int, const unsigned int);
//	void PauseAutoSpell2_RANGEATK(const int, const int, const unsigned int);
//	void ResumeAutoSpell2(const int, const int, const unsigned int);
//	void ResumeAutoSpell2_MLEATKED(const int, const int, const unsigned int);
//	void ResumeAutoSpell2_MLEATKED_Short(const int, const int, const unsigned int);
//	void ResumeAutoSpell2_MLEATKED_Long(const int, const int, const unsigned int);
//	void ResumeAutoSpell2_MAGATKED(const int, const int, const unsigned int);
//	void ResumeAutoSpell2_MLEATK(const int, const int, const unsigned int);
//	void ResumeAutoSpell2_RANGEATK(const int, const int, const unsigned int);
//	void SetPushingSkill(int, int);
//	void SetATKPercentInfo(int, unsigned long, int);
//	void SetDEFPercentInfo(int, unsigned long, int);
//	void SetMATKPercentInfo(int, unsigned long, int);
//	void SetMDEFPercentInfo(int, unsigned long, int);
//	void SetDamagePercent_PROP(unsigned short, int, unsigned short);
//	void SetDamagePercent_SKID(unsigned short, int, unsigned short);
//	void SetDamagePercent_MON(unsigned short, int, unsigned short);
//	void SetMagicDamagePercent_MON(unsigned short, int, unsigned short);
//	void SetMagicDamagePercent_PROP(const unsigned short, const int);
//	int GetMagicDamagePercent_PROP(const unsigned short);
//	void SetBadState_ArrowATK(int, int, unsigned short);
//	void SetBadState_MLEATK(int, int, unsigned short);
//	void SetBadState_MLEAttacked(int, int, unsigned short);
//	void SetBadState_MATK(int, int, unsigned short);
//	void SetBadState_MAttacked(int, int, unsigned short);
//	void SetDropItemOfRace_KILL(int, unsigned short, int);
//	void SetDamage_PropTM(unsigned short, unsigned short, int, int, unsigned short);
//	void ResetPushingSkill(int);
	void ResetATKPercentInfo(int SKID);
	void ResetDEFPercentInfo(const int in_SKID);
//	void ResetMATKPercentInfo(int);
//	void ResetMDEFPercentInfo(int);
//	void ModifyDamage_ATK(class CCharacter *, int &, int, int, int);
//	void ModifyDamage_ATKED(class CCharacter *, int &, int, int, int, int, int);
//	void ModifyDamage_MATK(class CCharacter *, int &);
//	void ProcessEffect_ATK(class CCharacter *, int, int, int);
//	void ProcessEffectOnKill(class CCharacter *, int, unsigned short);
	void ApplyEffect_ATKED(CCharacter* other, BOOL isMLEATK, BOOL isMATK, unsigned short SKID, int in_Damage);
//	int ReflectMagic(class CCharacter *, struct SKILLATTACK_MSG *, int);
//	int IsImmuneMagic(class CCharacter *, int);
	void OnDoubleCasting(int SKID, int target, int level, int spCost);
//	int SetEffectiveByTarotCard(class CCharacter *);
//	void SetSkillCastTimePercent(unsigned short, int);
//	int GetSkillCastTimePercent(unsigned short);
//	void SetHPAmountTime(unsigned short, unsigned long, short);
//	void SetSPAmountTime(unsigned short, unsigned long, short);
//	void SetHPPercentTime(unsigned short, unsigned long, short);
//	void SetSPPercentTime(unsigned short, unsigned long, short);
//	void ProcessItemHealRegularly();
//	void SetSkillAutoSpell(unsigned long, unsigned long, unsigned long, short, short);
//	void ResetSkillAutoSpell(unsigned long, unsigned long, unsigned long, short, short);
//	void SetHomunDBInfo(struct HOMUN_DBINFO *);
//	class CNpcHomun * CallHomun(short);
//	void RemoveHomun();
//	void SetMyHomunID(int);
//	int GetMyHomunID();
//	struct HOMUN_DBINFO * GetHomunDBInfo();
//	class CNpcHomun * GetMyHomun();
//	short IsCallableHomun();
//	int RestHomun(int);
//	void EvolutionHomun();
//	bool SetReadyMutationHomun();
//	bool MutationHomun(const int);
//	void SetHomunDBFmt(const class CLogonPermitADBWork::CHomunLogonData &);
//	void GetHomunDBFmt(class HomunDataStuff::CHomunData &);
//	void UpdateHomunData(class CNpcHomun *);
//	void SetMerceDBInfo(struct MERSOL_DBINFO *);
//	struct MERSOL_DBINFO * GetMerceDBInfo();
//	void SetDropItemOfMonster_Kill(unsigned short, unsigned short, int);
//	bool GetDropItemOfMonster_Kill(unsigned short, class std::map<unsigned short,int,std::less<unsigned short>,std::allocator<std::pair<unsigned short const ,int> > > &);

public:
	/* this+   4 */ CPCBattleMercenary m_Mercenary;

public:
	enum enumMercenary_CallType { CREATE = 0, LOAD = 1 };
//	bool MercenaryCall(const enumMercenary_CallType, const int);
//	bool MercenaryCall_Create(const int);
//	bool MercenaryCall_Load();
//	void Mercenary_Delete(const int);
//	void Mercenary_Release(const bool);
	void MercenaryCall_Create_After(const int in_Job);
	void MercenaryCall_Delete_After(const int in_reason);
//	void Mercenary_TYPICALJOBINFO_CHANGED();
//	void Mercenary_SaveToProxyDB();
//	void SetMercenaryID(const int);
//	int GetMercenaryID();
//	short GetFaith();
//	short GetSummonCount(short);
//	short GetMerceType(short);
//	class CNpcMercenary * GetMercenary();
//	int GetEnemyAID();
//	short GetMercenaryJob();
//	int GetMercenary_Type();
//	void CheckSkillSpecialOption(unsigned long, class CCharacter *, short, short);
//	unsigned long GetActivatedSkill();
//	unsigned long GetDeactivatedSkill();
//	void SetSkillActivate(unsigned long, unsigned long, unsigned long, unsigned long);
//	void ResetSkillActivate(unsigned long, unsigned long, unsigned long, unsigned long);
//	void AddState_SKID(short, unsigned long, short, int);
//	void SubState_SKID(short, unsigned long, short, int);
//	void SetAutoSpellMagic(unsigned long, short, short, int);
//	void ResetAutoSpellMagic(unsigned long, short, short, int);
//	short IsHomunState();

private:
//	void ReflectDamage(class CCharacter *, int);
//	void ProcessAutoSpell(class CCharacter *, int);
//	void ProcessAutoSpell_ATKED(class CCharacter *, int, int);
	void UseAutoSpell(unsigned short SKID, CCharacter* ch, short skillLv, MSGpar::CVar in_par);
	void UseAutoSpellToGround(unsigned short SKID, short xPos, short yPos, short skillLv);
//	void AutoSpell(const class std::map<unsigned short,CAutoSpellVar,std::less<unsigned short>,std::allocator<std::pair<unsigned short const ,CAutoSpellVar> > > &, class CCharacter *, bool);
//	void CheckAutoSpellList(class std::map<unsigned short,MSG_TYPE1_TWODWORD,std::less<unsigned short>,std::allocator<std::pair<unsigned short const ,MSG_TYPE1_TWODWORD> > > *, class CCharacter *, int);
//	void ProcessRegionSkill(int, short, class CCharacter *, int, int);
//	int PartySkill(int, short);
//	void CheckAutoActItem(unsigned char);
//	void ProcessAutoActItemScript();
//	void AddAutoActItem(unsigned char, unsigned long, short, short);
//	void SubAutoActItem(unsigned char, unsigned long, short, short);
//	void AddAutoActItemScript(unsigned char, unsigned long, unsigned long);
//	void SubAutoActItemScript(unsigned char, unsigned long);
//	int GetTotalHealRegularlyAmount(class std::map<unsigned short,HEAL_REGULARLY_INFO,std::less<unsigned short>,std::allocator<std::pair<unsigned short const ,HEAL_REGULARLY_INFO> > > *);
//	void ProcessTargetAttackedBuff(class CCharacter *, unsigned short);
//	void SetTargetAttackedBuff(unsigned long, short, unsigned short, unsigned long, unsigned long);
//	void ResetTargetAttackedBuff(unsigned long, short, unsigned short, unsigned long, unsigned long);
//	void ProcessSkillActivate();
//	void CheckSkillAutoSpell(unsigned long, class CCharacter *, short, short);
//	void CheckSkillActivate(unsigned long);
//	void CheckSkillHandicap(unsigned long, class CCharacter *, const short);
//	void CheckAutoSpellMagic(class CCharacter *);
//	void CheckPushingSkill(unsigned long, class CCharacter *);
//	int SK_SM_Bash(struct MSG_TYPE4_FIVEDWORD *, struct SKILLATTACK_MSG *, class CCharacter *);
//	int SK_TF_SprinkleSand(struct MSG_TYPE4_FIVEDWORD *, struct SKILLATTACK_MSG *, class CCharacter *);
//	int SK_TF_ThrowStone(struct MSG_TYPE4_FIVEDWORD *, struct SKILLATTACK_MSG *, class CCharacter *);
//	void SK_KN_ChargeATK(struct MSG_TYPE4_FIVEDWORD *, struct SKILLATTACK_MSG *, class CCharacter *);
//	void SK_WZ_SightBlaster(struct MSG_TYPE4_FIVEDWORD *);
//	int SK_BA_PangVoice(struct MSG_TYPE4_FIVEDWORD *, class CCharacter *);
//	int SK_DC_WinkCharm(struct MSG_TYPE4_FIVEDWORD *, class CCharacter *);
//	int SK_BS_Greed(struct MSG_TYPE4_FIVEDWORD *);
//	int SK_PR_Redemtio(struct MSG_TYPE4_FIVEDWORD *);
//	int SK_MO_KITranslation(struct MSG_TYPE4_FIVEDWORD *, class CCharacter *);
//	int SK_MO_Balkyoung(struct MSG_TYPE4_FIVEDWORD *, struct SKILLATTACK_MSG *, class CCharacter *);
//	int SK_RG_CloseConfine(struct MSG_TYPE4_FIVEDWORD *, class CCharacter *);
//	void SK_SA_CreateConverter(struct MSG_TYPE4_FIVEDWORD *);
//	int SK_SA_ElementalCHG(struct MSG_TYPE4_FIVEDWORD *, class CCharacter *);
//	int SK_GS_Glittering(struct MSG_TYPE4_FIVEDWORD *);
//	int SK_GS_Fling(struct MSG_TYPE4_FIVEDWORD *, class CCharacter *);
//	int SK_GS_BullsEye(struct MSG_TYPE4_FIVEDWORD *, struct SKILLATTACK_MSG *, class CCharacter *);
//	int SK_GS_MadnessCancel(struct MSG_TYPE4_FIVEDWORD *);
//	int SK_GS_Adjustment(struct MSG_TYPE4_FIVEDWORD *);
//	int SK_GS_Increasing(struct MSG_TYPE4_FIVEDWORD *);
//	int SK_GS_MagicalBullet(struct MSG_TYPE4_FIVEDWORD *, struct SKILLATTACK_MSG *, class CCharacter *);
//	int SK_GS_Cracker(struct MSG_TYPE4_FIVEDWORD *, class CCharacter *);
//	int SK_GS_FullBuster(struct MSG_TYPE4_FIVEDWORD *, struct SKILLATTACK_MSG *);
//	void SK_GS_SingleAction(struct MSG_TYPE4_FIVEDWORD *);
//	void SK_GS_SnakeEye(struct MSG_TYPE4_FIVEDWORD *);
//	void SK_NJ_TobidoUgu(struct MSG_TYPE4_FIVEDWORD *);
//	void SK_NJ_NinPou(struct MSG_TYPE4_FIVEDWORD *);
//	int SK_GS_Disarm(struct MSG_TYPE4_FIVEDWORD *, class CCharacter *);
//	int SK_GS_PiercingShot(struct MSG_TYPE4_FIVEDWORD *, struct SKILLATTACK_MSG *, class CCharacter *);
//	int SK_GS_Desperado(struct MSG_TYPE4_FIVEDWORD *);
//	void SK_GS_GatlingFever(struct MSG_TYPE4_FIVEDWORD *);
//	int SK_NJ_Syuriken(struct MSG_TYPE4_FIVEDWORD *, struct SKILLATTACK_MSG *, class CCharacter *);
//	int SK_NJ_Kunai(struct MSG_TYPE4_FIVEDWORD *, struct SKILLATTACK_MSG *, class CCharacter *);
//	int SK_NJ_ZenyNage(struct MSG_TYPE4_FIVEDWORD *, struct SKILLATTACK_MSG *, class CCharacter *);
//	void SK_NJ_TatamiGaeshi(struct MSG_TYPE4_FIVEDWORD *);
//	int SK_NJ_KasumiKiri(struct MSG_TYPE4_FIVEDWORD *, struct SKILLATTACK_MSG *, class CCharacter *);
//	void SK_NJ_ShadowJump(struct MSG_TYPE5_SIXDWORD *);
//	int SK_NJ_KiriKage(struct MSG_TYPE4_FIVEDWORD *, struct SKILLATTACK_MSG *, class CCharacter *);
//	int SK_NJ_Utsusemi(struct MSG_TYPE4_FIVEDWORD *);
//	int SK_NJ_BunsinJyutsu(struct MSG_TYPE4_FIVEDWORD *);
//	int SK_NJ_KaenSin(struct MSG_TYPE4_FIVEDWORD *);
//	int SK_NJ_BakuenRyu(struct MSG_TYPE4_FIVEDWORD *, class CCharacter *);
//	int SK_NJ_HyousenSou(struct MSG_TYPE4_FIVEDWORD *, struct SKILLATTACK_MSG *);
//	void SK_NJ_SuiTon(struct MSG_TYPE5_SIXDWORD *);
//	int SK_NJ_HyouSyouRaku(struct MSG_TYPE4_FIVEDWORD *);
//	int SK_NJ_Raigekisai(struct MSG_TYPE4_FIVEDWORD *);
//	int SK_NJ_Nen(struct MSG_TYPE4_FIVEDWORD *);
//	int SK_NJ_Issen(struct MSG_TYPE4_FIVEDWORD *, struct SKILLATTACK_MSG *, class CCharacter *);
//	int SK_ALL_PARTYFLEE(struct MSG_TYPE4_FIVEDWORD *);
//	int SK_ALL_ANGEL_PROTECT(struct MSG_TYPE4_FIVEDWORD *, class CCharacter *);
//	int ALL_SONKRAN(const struct MSG_TYPE4_FIVEDWORD &, class CCharacter *);
//	int ALL_ODINS_POWER(class CCharacter *, const int, const int);

private:
	/* this+1108 */ CPC* m_pc;
	/* this+1112 */ int m_enemyAID;
	/* this+1116 */ int m_isReflectedMAGIC;
	/* this+1120 */ unsigned short m_DoubleCastingSKID;
	/* this+1124 */ OptionInfo m_optionInfo;
	/* this+1216 */ int m_myHomunID;
	/* this+1220 */ HOMUN_DBINFO m_homunDBInfo;
	/* this+1296 */ CPCBattleHomun m_Homun;
	/* this+1328 */ MERSOL_DBINFO m_merceDBInfo;
	/* this+1372 */ int m_mercenaryID;
	/* this+1376 */ short m_faith;
	/* this+1378 */ short m_summonCount[3];
	/* this+1384 */ std::map<int,AMOUNT_INFO> m_ATKPercentList;
	/* this+1400 */ std::map<int,AMOUNT_INFO> m_DEFPercentList;
	/* this+1416 */ std::map<int,AMOUNT_INFO> m_MATKPercentList;
	/* this+1432 */ std::map<int,AMOUNT_INFO> m_MDEFPercentList;
	/* this+1448 */ std::map<unsigned short,MSG_TYPE1_TWODWORD> m_pushSkillList;
	/* this+1464 */ std::map<unsigned short,int> m_damagePercent_PROP[2];
	/* this+1496 */ std::map<unsigned short,int> m_damagePercent_SKID[2];
	/* this+1528 */ std::map<unsigned short,int> m_damagePercent_MON[2];
	/* this+1560 */ std::map<unsigned short,int> m_magicDamagePercent_MON[2];
	/* this+1592 */ std::map<unsigned short,int> m_magicDamagePercent_PROP;
	/* this+1608 */ std::map<unsigned short,PropTM_Info> m_damageTM_PROP[2];
	/* this+1640 */ std::map<unsigned short,CAutoSpellVar> m_AutoSpell[2];
	/* this+1672 */ std::map<unsigned short,CAutoSpellVar> m_AutoSpell_MLEATKED[2];
	/* this+1704 */ std::map<unsigned short,CAutoSpellVar> m_AutoSpell_MLEATKED_Short[2];
	/* this+1736 */ std::map<unsigned short,CAutoSpellVar> m_AutoSpell_MLEATKED_Long[2];
	/* this+1768 */ std::map<unsigned short,CAutoSpellVar> m_AutoSpell_MAGATKED[2];
	/* this+1800 */ std::map<unsigned short,CAutoSpellVar> m_AutoSpell_MLEATK[2];
	/* this+1832 */ std::map<unsigned short,CAutoSpellVar> m_AutoSpell_RANGEATK[2];
	/* this+1864 */ std::map<unsigned short,unsigned short> m_badState_ArrowATK[2];
	/* this+1896 */ std::map<unsigned short,unsigned short> m_badState_MLEATK[2];
	/* this+1928 */ std::map<unsigned short,unsigned short> m_badState_MLEAttacked[2];
	/* this+1960 */ std::map<unsigned short,unsigned short> m_badState_MATK[2];
	/* this+1992 */ std::map<unsigned short,unsigned short> m_badState_MAttacked[2];

	struct stBADSTATE_EFST_INFO
	{
	public:
		/* this+0 */ WORD wPercent;
		/* this+4 */ DWORD dwKeepTime;
	};

	enum
	{
		enBADSTATE_EFST_MLEATK     = 0,
		enBADSTATE_EFST_MLEATKED   = 1,
		enBADSTATE_EFST_MATK       = 2,
		enBADSTATE_EFST_MATKED     = 3,
		enBADSTATE_EFST_ARROWATK   = 4,
		enBADSTATE_EFST_ARROWATKED = 5,
		enBADSTATE_EFST_ATK_MAX    = 6,
	};

	/* this+2024 */ std::map<int,stBADSTATE_EFST_INFO> m_badSate_EFST_ATK[enBADSTATE_EFST_ATK_MAX][2];

public:
//	void SetBadState_EFSTATK(const int , const unsigned short , const unsigned short , const int , const unsigned short );
//	void ResetBadState_EFSTATK();

private:
	/* this+2216 */ std::map<unsigned short,int> m_healPercent_ITEM;
	/* this+2232 */ std::map<unsigned short,int> m_dropItemOfRace_KILL[11];
	/* this+2408 */ std::map<unsigned short,std::map<unsigned short,int>> m_dropItemOfMonster_KILL;
	/* this+2424 */ std::map<unsigned short,int> m_skillCastTimePercent;
	/* this+2440 */ std::map<unsigned short,HEAL_REGULARLY_INFO> m_HPhealRegularlyAmountInfo;
	/* this+2456 */ std::map<unsigned short,HEAL_REGULARLY_INFO> m_SPhealRegularlyAmountInfo;
	/* this+2472 */ std::map<unsigned short,HEAL_REGULARLY_INFO> m_HPhealRegularlyPercentInfo;
	/* this+2488 */ std::map<unsigned short,HEAL_REGULARLY_INFO> m_SPhealRegularlyPercentInfo;
	/* this+2504 */ std::map<unsigned char,std::list<AUTO_ACT_ITEMINFO>> m_autoActItemInfo;
	/* this+2520 */ std::list<AUTO_ACT_ITEMSCRIPT> m_autoActItemScriptList;
	/* this+2532 */ std::list<TARGET_ATTACKED_BUFF> m_targetAttackedBuff;
	/* this+2544 */ int m_damageMeleeTolerace[10];
	/* this+2584 */ int m_damageMagicTolerace[10];
	/* this+2624 */ std::map<unsigned long,std::list<SKILL_AUTOSPELL>> m_skillAutoSpellInfo;
	/* this+2640 */ _SKILL_ACTIVE_INFO m_skillActiveInfo;
	/* this+2676 */ std::map<unsigned long,std::list<SKILL_HANDICAP>> m_skillHandicapInfo;
	/* this+2692 */ std::list<AUTOSPELL_MAGIC> m_autoSpellMagicList;

	struct tagSkillSP { int SpValue; };
	struct tagSkillDelay { int DelayTime; };
	struct tagSkillData { int Data; };
	struct tagSkillStateCastTime { int CastTime; };

	union unionSkillStdOption
	{
		/* this+0 */ tagSkillSP m_tagSkillSP;
		/* this+0 */ tagSkillDelay m_tagSkillDelay;
		/* this+0 */ tagSkillData m_tagSkillData;
		/* this+0 */ tagSkillStateCastTime m_tagSkillStateCastTime;

//		void operator+=(const unionSkillStdOption& );
//		unionSkillStdOption();
	};

private:
	typedef std::map<unsigned short,unionSkillStdOption> LIST_FUNC_SKILLSTD;
	/* this+2704 */ std::map<unsigned short,LIST_FUNC_SKILLSTD> m_SkillSTD;

private:
//	void OperateSkillStdOption(const unsigned short, const unsigned long, const union CPCBattle::unionSkillStdOption &);
//	void OperateFUNC_ADDSKILLSP(const unsigned short, const int);
//	void OperateFUNC_ADDSKILLDELAY(const unsigned short, const int);
//	void OperateFUNC_ADDSTATECASTTIME(const unsigned short, const int);
	const unionSkillStdOption* GetSkillStdOption(const unsigned short in_SKID, const unsigned long in_FuncType);
	int GetAdditionalSkillSPCost(const unsigned short in_SKID);
	int GetAdditionalSkillDelayTime(const unsigned short in_SKID);
	int GetAdditionalSkillStateCastTime(const unsigned short in_SKID);

	friend class CPC;
};
