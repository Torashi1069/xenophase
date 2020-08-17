#include "CNPCAddSkillInfo.hpp"


hook_method<mystd::vector<NPCSKILLINFO *>* (CNPCAddSkillInfo::*)(int spriteType, int state)> CNPCAddSkillInfo::_Find(SERVER, "CNPCAddSkillInfo::Find");
mystd::vector<NPCSKILLINFO *>* CNPCAddSkillInfo::Find(int spriteType, int state)
{
	return (this->*_Find)(spriteType, state);

	//TODO
}


hook_method<int (CNPCAddSkillInfo::*)(const char* file)> CNPCAddSkillInfo::_Load(SERVER, "CNPCAddSkillInfo::Load");
int CNPCAddSkillInfo::Load(const char* file)
{
	return (this->*_Load)(file);

	//TODO
}


hook_method<const char* (CNPCAddSkillInfo::*)(int chatNo, unsigned long& color)> CNPCAddSkillInfo::_GetNPCChat(SERVER, "CNPCAddSkillInfo::GetNPCChat");
const char* CNPCAddSkillInfo::GetNPCChat(int chatNo, unsigned long& color)
{
	return (this->*_GetNPCChat)(chatNo, color);

	//TODO
}


hook_method<int (CNPCAddSkillInfo::*)(char* mob, char* status, char* skill, int level, int percent, int casttime, unsigned long cooldowntime, char* stTemp1, char* stTemp2, char* stTemp3, char* stTemp4, char* stTemp5, char* stTemp6)> CNPCAddSkillInfo::_LoadEntry(SERVER, "CNPCAddSkillInfo::LoadEntry");
int CNPCAddSkillInfo::LoadEntry(char* mob, char* status, char* skill, int level, int percent, int casttime, unsigned long cooldowntime, char* stTemp1, char* stTemp2, char* stTemp3, char* stTemp4, char* stTemp5, char* stTemp6)
{
	return (this->*_LoadEntry)(mob, status, skill, level, percent, casttime, cooldowntime, stTemp1, stTemp2, stTemp3, stTemp4, stTemp5, stTemp6);

	//TODO
}


hook_method<int (CNPCAddSkillInfo::*)(NPCSKILLINFO* info, char** stTemp)> CNPCAddSkillInfo::_SetSkillInfo(SERVER, "CNPCAddSkillInfo::SetSkillInfo");
int CNPCAddSkillInfo::SetSkillInfo(NPCSKILLINFO* info, char** stTemp)
{
	return (this->*_SetSkillInfo)(info, stTemp);

	//TODO
}


hook_method<void (CNPCAddSkillInfo::*)(void)> CNPCAddSkillInfo::_InitKeyword(SERVER, "CNPCAddSkillInfo::InitKeyword");
void CNPCAddSkillInfo::InitKeyword(void)
{
	return (this->*_InitKeyword)();

	//TODO
}


hook_method<unsigned long (CNPCAddSkillInfo::*)(const char* strKeyWord)> CNPCAddSkillInfo::_GetKeyWord(SERVER, "CNPCAddSkillInfo::GetKeyWord");
unsigned long CNPCAddSkillInfo::GetKeyWord(const char* strKeyWord)
{
	return (this->*_GetKeyWord)(strKeyWord);

	//TODO
}


hook_method<mystd::vector<NPCSKILLINFO *>* (CNPCAddSkillInfo::*)(int spriteType, int state)> CNPCAddSkillInfo::_InsertNewSkill(SERVER, "CNPCAddSkillInfo::InsertNewSkill");
mystd::vector<NPCSKILLINFO *>* CNPCAddSkillInfo::InsertNewSkill(int spriteType, int state)
{
	return (this->*_InsertNewSkill)(spriteType, state);

	//TODO
}


hook_method<void (CNPCAddSkillInfo::*)(void)> CNPCAddSkillInfo::_Free(SERVER, "CNPCAddSkillInfo::Free");
void CNPCAddSkillInfo::Free(void)
{
	return (this->*_Free)();

	//TODO
}


hook_method<bool (CNPCAddSkillInfo::*)(void)> CNPCAddSkillInfo::_LoadNPCChat(SERVER, "CNPCAddSkillInfo::LoadNPCChat");
bool CNPCAddSkillInfo::LoadNPCChat(void)
{
	return (this->*_LoadNPCChat)();

	//TODO
}

