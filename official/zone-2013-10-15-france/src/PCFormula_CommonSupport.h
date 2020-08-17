#pragma once
#include "ActorFormula_CommonSupport.h"
class CPC;


class CPCFormula_CommonSupport : public CActorFormula_CommonSupport
{
public:
//	void Check_MonsterType(class CCharacter *, int &, short &, unsigned short, bool);
//	void Check_MAPPROPERTY(class CCharacter *, int &, short &, int, unsigned short, bool);
//	bool Check_BASILICA(class CCharacter *, int &);
//	bool Check_MAGICROD(class CCharacter *, int &, unsigned short, short);
//	bool Check_TAEKWONCLASS_DODGE(class CCharacter *, int &, int);
//	bool Check_DEVOTION(class CCharacter *, int &, int, int, unsigned long &, unsigned short);
//	bool Check_SHADOWFORM(class CCharacter *, int &, int, int, unsigned long &, unsigned short);
//	bool Check_WATER_SCREEN(class CCharacter *, int &, int, int, unsigned long &, unsigned short);
//	void ProcessAtkerEffectByAttack(class CCharacter *, int, int, bool);
//	void ProcessTargetEffectByAttacked(class CCharacter *, int &, int, int, int, int);

public:
	CPCFormula_CommonSupport(CPC* pc);

private:
//	void Check_SetHandicapStateByAttack(class CCharacter *, int, bool);
//	void Check_SNATCHER(class CCharacter *, int, bool);
//	void Check_MELTDOWN(class CCharacter *);
//	void Check_AtkerSTDByAttack(class CCharacter *);
//	void Check_STAR(class CCharacter *);
//	void Check_STONEHARDSKIN(class CCharacter *, int, int);
//	void Check_ENERGYCOAT(class CCharacter *, int &);
//	void Check_SWORDREJECT(class CCharacter *, int &);
//	void Check_POISONREACT(class CCharacter *);
//	void Check_NINJA(class CCharacter *, int &);
//	void Check_SetHandicapStateByAttacked(class CCharacter *, int);
//	void Check_PYROCLASTIC(class CCharacter *, int, bool);

protected:
	/* this+0 */ //CActorFormula_CommonSupport baseclass_0;
	/* this+4 */ CPC* m_pc;
};
