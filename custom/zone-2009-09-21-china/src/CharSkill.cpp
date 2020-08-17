#include "CharSkill.h"


hook_func<CCharSkill* (__cdecl *)(void)> _GetCharSkill(SERVER, "GetCharSkill");
CCharSkill* __cdecl GetCharSkill(void) // line 30
{
	return (_GetCharSkill)();

	static CCharSkill g_charSkill;
	return &g_charSkill;
}


hook_method<int (CCharSkill::*)(CCharacter* owner, CCharacter* target, int SKID, MSG_TYPE4_FIVEDWORD* data, int sectionMove)> CCharSkill::_OnTouchedSkillObj(SERVER, "CCharSkill::OnTouchedSkillObj");
int CCharSkill::OnTouchedSkillObj(CCharacter* owner, CCharacter* target, int SKID, MSG_TYPE4_FIVEDWORD* data, int sectionMove)
{
	return (this->*_OnTouchedSkillObj)(owner, target, SKID, data, sectionMove);

	//TODO
}


hook_method<int (CCharSkill::*)(CCharacter* owner, CCharacter* target, int SKID, MSG_TYPE4_FIVEDWORD* data, SKILLATTACK_MSG* skillMsg)> CCharSkill::_AttSkillToChar(SERVER, "CCharSkill::AttSkillToChar");
int CCharSkill::AttSkillToChar(CCharacter* owner, CCharacter* target, int SKID, MSG_TYPE4_FIVEDWORD* data, SKILLATTACK_MSG* skillMsg)
{
	return (this->*_AttSkillToChar)(owner, target, SKID, data, skillMsg);

	//TODO
}
