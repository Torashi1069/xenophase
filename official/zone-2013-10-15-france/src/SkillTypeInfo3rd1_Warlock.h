#pragma once
#include "SkillTypeInfo2.h"


class SK_WL_WHITEIMPRISON : public CSkillTypeInfo2
{
public:
	int GetSpellPercent(const int in_Level) const; //TODO
	int GetLifeTM_when_targetISplayer_and_exclusionOneself(const int in_Level) const;
	virtual int OnMsg(CCharacter* in_cpSender, unsigned short in_SKID, int in_MsgID, int in_par1, int in_par2, int in_par3, MSGpar::CVar in_par4);
	static int ModifyDamageATKED(CCharacter* in_cpDefCharacter, CCharacter* in_cpAtkCharacter, int& io_damage, const int in_SKID);
	static void TimeOutProc_BODYSTATE_IMPRISON(CCharacter* in_cpDefCharacter, CCharacter* in_cpAtkCharacter);
	virtual BOOL IsSpellConditionGratify(CCharacter* in_cpSpellCH, CCharacter* in_cpTargetCH, const int in_Level, int& out_USESKILL_FAIL);
};
