#pragma once
class CActor;


class CActorFormula_CommonSupport
{
public:
//	class CCharacter * ModifyAttackDamage(class CCharacter *, int &, int, unsigned short, short, bool, int, int);
//	void Check_SAFETYWALL(class CCharacter *, int &, short &, int, unsigned short, bool, int);
//	void Check_PNEUMA(class CCharacter *, int &, short &, int, unsigned short, bool, int);
//	void Check_IMITATIONSKILL(class CCharacter *, unsigned short, short);
//	void Check_FOGWALL(class CCharacter *, int &, int, unsigned short);
//	bool Check_TargetDamageToZero(class CCharacter *, int &, int, unsigned short, int);
//	void Check_TargetModifyDamage(class CCharacter *, int &, int, int, unsigned short);
//	void Check_SPIDERWEB(class CCharacter *, int, int &, int);
//	bool Check_WEAPONBLOCKING(class CCharacter *, class CCharacter *, const int, const int);
//	void Check_VOLCANIC_ASH(int &, const int);
//	void ModifyPhysicsAttackHITPercent(class CCharacter *, const int, int &, const int);
//	void TargetReflectSkillDamage(class CCharacter *, int &, struct SKILLATTACK_MSG *, class CSkillTypeInfo *, int, int, bool &, const int);
//	void TargetReflectAttackDamage(class CCharacter *, int &, short &, int, const int);
//	int GetFinalDamageATKPercent_AfterApplyTargetMDEF(class CCharacter *, const unsigned short);
//	void EXCEPTION_GetSkillAttackDamage_CheckDistinctDamage(class CCharacter *, int &, const unsigned short, const int, const int);
//	void Check_RaceAddDamageSelf(class CPC *, class CCharacter *, const int, int &);
//	void Check_AddRaceTolerace(class CPC *, class CCharacter *, const int, int &);
//	void Check_ClassAddDamageUSER(class CPC *, class CCharacter *, const int, int &);
//	void Check_ClassAddDamageTARGET(class CPC *, class CCharacter *, const int, const int, int &);
//	void Check_AddRangeAttackDamageTARGET(class CPC *, const unsigned short, const int, const int, int &);
//	void Check_AddRangeAttackDamageUSER(class CPC *, const unsigned short, const int, const int, int &);
//	bool IsMagicATKHit(class CCharacter *);

private:
//	bool Check_ReflectMagicDamage(class CCharacter *, int, struct SKILLATTACK_MSG *, class CSkillTypeInfo *, int);
//	bool Check_PARRYING(class CCharacter *, int &, int);
//	bool Check_AUTOGUARD(class CCharacter *, int &, int, unsigned short);
//	void Check_LG_REFLECTDAMAGE(class CCharacter *, int);
//	void Check_SHIELDSPELL_DEF(class CCharacter *, int, int, int);
//	void Check_REFLECTSHIELD(class CCharacter *, int, int);
//	void Check_DEATHBOUND(class CCharacter *, int &, short &, int);
//	bool Check_ElementalDefensiveEffect(class CCharacter *, int &, short &, const int);
//	bool Check_NEUTRALBARRIER(class CCharacter *, int &, int, const int);
//	void Check_GRANITIC_ARMOR(int &);
//	void Check_ASSUMPTIO2(int &, const unsigned short);
//	bool IsPhysicsAttackExceptionMiss(class CCharacter *, int, const int);
//	bool IsPhysicsAttackExceptionHit(class CCharacter *, int);

public:
	CActorFormula_CommonSupport(CActor* actor);

protected:
	/* this+0 */ CActor* m_actor;
};
