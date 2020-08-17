#pragma once
#include "PCFormula_CommonSupport.h"
class CCharacter;
class CPC;


class CPCFormula_PhysicsSupport : public CPCFormula_CommonSupport
{
public:
//	void PreWork_BeforeGetPhysicsFinalDamage(int &, int &, unsigned short);
//	bool IsPhysicsATKHit(class CCharacter *, int, int, int, unsigned short &);
//	int GetPhysicsFinalATKPower(class CCharacter *, int, int, int, int, int, int, unsigned short, short);
//	bool PreWork_BeforeGetPhysicsBaseATKPower(int);
//	int GetPhysicsStatusPower(class CCharacter *);
//	int GetPhysicsItemPower(class CCharacter *, int, int, int, unsigned short, int);
//	int GetPhysicsExceptionalBaseATKPower(class CCharacter *, int);
//	int GetPhysicsBaseATKPower(class CCharacter *);
//	void ModifyPhysicsFinalATKPowerByTargetDEF(class CCharacter *, int &, int);
//	void ModifyPhysicsFinalATKPower_AfterApplyTargetDEF(class CCharacter *, int &, int, int, unsigned short);
//	bool IsEnableActionAttack(class CCharacter *, int, bool &);
//	void ResetHidingStateByActionAttack();
//	int GetActionAttackATKProperty();
//	bool ProcessActionAttackCounter(class CCharacter *, int, int);
//	bool SetActionAttackStartTime(unsigned long &);
//	void MotivateSkillByActionAttack(class CCharacter *);
//	void Check_AssassinWeapon(class CCharacter *, int &, short &);
	void InsertActionAttackCommandQueue(CCharacter* in_cpTarget, int in_Damage, short in_LeftDamage, int in_atkerATKMotionTime, int in_ATKCount, BOOL in_IsRangeAttack, int in_ATKProperty);
//	void PostWork_AfterActionAttack(int, int);
//	int GetActionAttackDamage(class CCharacter *, int, struct PACKET_ZC_NOTIFY_ACT *);
//	bool GetActionAttackCount(short &, int &);
	CPCFormula_PhysicsSupport(CPC* pc);
//	int GetPhysicsTargetSTDValueExposed(class CCharacter *, int, int, int, int, unsigned short, short);

private:
//	void Check_OVERTHRUST();
//	void ModifyPlusATKPercent_PhysicsFinalDamage(int &, unsigned short);
//	void ModifyPlusHITPercent_PhysicsFinalDamage(int &);
//	bool ReduceSPByPhysicsATK(const int);
//	void ModifyPhysicsItemPowerByScale(class CCharacter *, int &, int);
//	int GetPhysicsAtkerSTDValue(class CCharacter *, int, int, int, int, unsigned short, short);
//	int GetPhysicsTargetSTDValue(class CCharacter *, int, int, int, int, unsigned short, short);
//	int GetPhysicsAtkerSKValue(class CCharacter *, int, int, int, unsigned short, short, int);
//	int GetPhysicsTargetSKValue(class CCharacter *, const unsigned short, const int, const int);
};
