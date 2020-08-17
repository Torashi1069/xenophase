#include "NPCElemental.h"


CNpcElemental::CNpcElemental()
{
}


CNpcElemental::~CNpcElemental()
{
}


int CNpcElemental::SkillAttackExt(SKILLATTACK_MSG* msg, int plusATTPowerPercent, int plusATTSuccessPercent, const bool in_bSilenceSkill) // (34.h)
{
	return this->SkillAttack(msg, plusATTPowerPercent, plusATTSuccessPercent, in_bSilenceSkill);
}
