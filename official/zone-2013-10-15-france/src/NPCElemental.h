#pragma once
#include "NpcMob.h"


namespace ElementalStuff {


enum enumKind
{
	KIND_AGNI   = 1,
	KIND_AQUA   = 2,
	KIND_VENTUS = 3,
	KIND_TERA   = 4,
};


enum enumScale
{
	SCALE_SMALL  = 1,
	SCALE_MEDIUM = 2,
	SCALE_BIG    = 3,
};


class ESummaryData
{
public:
	/* this+ 0 */ int m_hp;
	/* this+ 4 */ int m_maxhp;
	/* this+ 8 */ int m_sp;
	/* this+12 */ int m_maxsp;
	/* this+16 */ int m_atk;
	/* this+20 */ int m_attackMT;
	/* this+24 */ int m_def;
	/* this+28 */ int m_mdef;
	/* this+32 */ int m_flee;
	/* this+36 */ int m_hit;
	/* this+40 */ int m_matk;
};


}; // namespace ElementalStuff


class CNpcElemental : public CNpcMob
{
public:
//	virtual int GetModifiedValueByEnemySize(int);
//	virtual void NotifyParameter(unsigned short, int);
//	virtual void OnDead(unsigned long);
//	CCharacter* GetMyOwner();
//	virtual int UpdateParameterValue(unsigned short, int);
//	virtual int IsTarget(CCharacter*, unsigned long);
//	virtual void Reset();
//	virtual int GetBaseFlee();
//	virtual int GetBaseHit();
//	virtual int GetMaxSP();
//	virtual int GetSpeed();
	int SkillAttackExt(SKILLATTACK_MSG* msg, int plusATTPowerPercent, int plusATTSuccessPercent, const bool in_bSilenceSkill);
//	CPC* GetOwner();
//	void ChangeControlMode(const int);
//	virtual int OnMsg(CCharacter*, CCharacter*, unsigned long, int, int, int, MSGpar::CVar);
//	int GetSP();
//	virtual void ReduceSPByUseSkill(int);
//	ElementalStuff::enumKind GetKind();
//	ElementalStuff::enumScale GetScale();
//	void PacketSend_ZC_EL_INIT();
//	void InsertEnemyInfo(ENEMY_INFO*);
//	void UpdateEnemyInfo();
//	void SetSummaryData(const ElementalStuff::enumKind, const ElementalStuff::enumScale, const ElementalStuff::ESummaryData&);
//	void SetEfstData(const std::vector<Effect3rd::tagEffect3rdDBFmt>&);
//	void GetSummaryData(ElementalStuff::ESummaryData&);
//	void GetEffectData(std::vector<Effect3rd::tagEffect3rdDBFmt>&);

public:
	CNpcElemental();
	virtual ~CNpcElemental();

private:
//	virtual int GetMagicAttPower();
//	virtual void InitCore();
//	bool IsEnableThirdJobSkillOperate(const int, CCharacter*, CSkillTypeInfo*);
//	void ChangeHP(const int);
//	void ChangeSP(const int);
//	void BroadcastHP();
//	void OnThirdJobSkillOperateToCharacter(unsigned short, int, MSG_TYPE_SKILLDATA*, MSGpar::CVar);
//	void OnThirdJobSkillAttackToCharacter(unsigned short, int, MSG_TYPE_SKILLDATA*, MSGpar::CVar);
//	void OnTouchedSkillObject(int, int, int);
//	void OnADD_EXP(CCharacter*, const int);
//	void OnSHARE_EXP(CCharacter*, const int);
//	int OnGET_GRID_IFEXPSHARE(CCharacter*, int, int, int, MSGpar::CVar);
//	void OnADD_JOBEXP(CCharacter*, const int, const int, const int);
//	void OnSHARE_JOBEXP(CCharacter*, const int);
//	void EL_FIRE_MANTLE_OnTouched(CCharacter*, const int, const unsigned long);
//	void EL_WATER_BARRIER_OnTouched(CCharacter*, const int, const unsigned long);
//	void EL_ZEPHYR__OnTouched(CCharacter*, const int, const unsigned long);
//	void EL_POWER_OF_GAIA_OnTouched(CCharacter*, const int, const unsigned long);
//	CActor::SKILL_RETURN EL_CIRCLE_OF_FIRE(const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_FIRE_CLOAK(const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_FIRE_MANTLE(const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_WATER_SCREEN(const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_WATER_DROP(const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_WATER_BARRIER(const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_WIND_STEP(const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_WIND_CURTAIN(const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_ZEPHYR(const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_SOLID_SKIN(const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_STONE_SHIELD(const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_POWER_OF_GAIA(const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_PYROTECHNIC(const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_HEATER(const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_TROPIC(const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_AQUAPLAY(const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_COOLER(const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_CHILLY_AIR(const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_GUST(const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_BLAST(const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_WILD_STORM(const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_PETROLOGY(const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_CURSED_SOIL(const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_UPHEAVAL(const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_FIRE_ARROW(CCharacter*, const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_FIRE_BOMB(CCharacter*, const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_FIRE_WAVE(CCharacter*, const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_ICE_NEEDLE(CCharacter*, const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_WATER_SCREW(CCharacter*, const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_TIDAL_WEAPON(CCharacter*, const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_WIND_SLASH(CCharacter*, const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_HURRICANE(CCharacter*, const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_TYPOON_MIS(CCharacter*, const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_STONE_HAMMER(CCharacter*, const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_ROCK_CRUSHER(CCharacter*, const MSG_TYPE_SKILLDATA&);
//	CActor::SKILL_RETURN EL_STONE_RAIN(CCharacter*, const MSG_TYPE_SKILLDATA&);

private:
	/* this+   0 */ //CNpcMob baseclass_0;
	/* this+2172 */ std::vector<ENEMY_INFO> m_enemyInfo;
	/* this+2188 */ ElementalStuff::enumKind m_Kind;
	/* this+2192 */ ElementalStuff::enumScale m_Scale;
	/* this+2196 */ int m_flee;
	/* this+2200 */ int m_hit;
	/* this+2204 */ int m_matk;
};
