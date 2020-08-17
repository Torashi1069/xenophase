#include "CNPCSkill.hpp"


CNPCSkill::CNPCSkill(void) // line 20
{
}


CNPCSkill::~CNPCSkill(void) // line 24
{
}


hook_method<void (CNPCSkill::*)(void)> CNPCSkill::_Init(SERVER, "CNPCSkill::Init");
void CNPCSkill::Init(void) // line 28
{
	return (this->*_Init)();

	//TODO
}


//hook_method<void (CNPCSkill::*)(CNPC* npc)> CNPCSkill::_SetMyOwner(SERVER, "CNPCSkill::SetMyOwner");
void CNPCSkill::SetMyOwner(CNPC* npc)
{
//	return (this->*_SetMyOwner)(npc);

	m_npc = npc;
}


hook_method<int (CNPCSkill::*)(void)> CNPCSkill::_OnProcess(SERVER, "CNPCSkill::OnProcess");
int CNPCSkill::OnProcess(void) // line 567
{
	return (this->*_OnProcess)();

	//TODO
}


hook_method<void (CNPCSkill::*)(unsigned short SKID, int skLevel, int targetAID, int xPos, int yPos)> CNPCSkill::_OnUseSkill(SERVER, "CNPCSkill::OnUseSkill");
void CNPCSkill::OnUseSkill(unsigned short SKID, int skLevel, int targetAID, int xPos, int yPos)
{
	return (this->*_OnUseSkill)(SKID, skLevel, targetAID, xPos, yPos);

	//TODO
}


hook_method<void (CNPCSkill::*)(int SKID, MSG_TYPE1_TWODWORD* position, int skLevel, int spCost)> CNPCSkill::_OnUseGroundSkill(SERVER, "CNPCSkill::OnUseGroundSkill");
void CNPCSkill::OnUseGroundSkill(int SKID, MSG_TYPE1_TWODWORD* position, int skLevel, int spCost)
{
	return (this->*_OnUseGroundSkill)(SKID, position, skLevel, spCost);

	//TODO
}


hook_method<void (CNPCSkill::*)(void)> CNPCSkill::_StartUseSkill(SERVER, "CNPCSkill::StartUseSkill");
void CNPCSkill::StartUseSkill(void)
{
	return (this->*_StartUseSkill)();

	//TODO
}


hook_method<void (CNPCSkill::*)(unsigned short SKID)> CNPCSkill::_EndUseSkill(SERVER, "CNPCSkill::EndUseSkill");
void CNPCSkill::EndUseSkill(unsigned short SKID)
{
	return (this->*_EndUseSkill)(SKID);

	//TODO
}


hook_method<void (CNPCSkill::*)(int flag)> CNPCSkill::_CancelSkill(SERVER, "CNPCSkill::CancelSkill");
void CNPCSkill::CancelSkill(int flag)
{
	return (this->*_CancelSkill)(flag);

	//TODO
}


hook_method<int (CNPCSkill::*)(unsigned long FSMState)> CNPCSkill::_IsSkillUsable(SERVER, "CNPCSkill::IsSkillUsable");
int CNPCSkill::IsSkillUsable(unsigned long FSMState)
{
	return (this->*_IsSkillUsable)(FSMState);

	//TODO
}


//hook_method<void (CNPCSkill::*)(int job)> CNPCSkill::_SetNPCJob(SERVER, "CNPCSkill::SetNPCJob");
void CNPCSkill::SetNPCJob(int job)
{
//	return (this->*_SetNPCJob)(job);

	m_npcJob = job;
}


hook_method<int (CNPCSkill::*)(unsigned long SKID)> CNPCSkill::_GetSkillLevel(SERVER, "CNPCSkill::GetSkillLevel");
int CNPCSkill::GetSkillLevel(unsigned long SKID)
{
	return (this->*_GetSkillLevel)(SKID);

	//TODO
}


hook_method<void (CNPCSkill::*)(unsigned long SKID)> CNPCSkill::_SetPostDelayTimer(SERVER, "CNPCSkill::SetPostDelayTimer");
void CNPCSkill::SetPostDelayTimer(unsigned long SKID)
{
	return (this->*_SetPostDelayTimer)(SKID);

	//TODO
}


/* hook_method<void (CNPCSkill::*)(unsigned long SKID)> CNPCSkill::_ResetPostDelayTimer(SERVER, "CNPCSkill::ResetPostDelayTimer");
void CNPCSkill::ResetPostDelayTimer(unsigned long SKID)
{
	return (this->*_ResetPostDelayTimer)(SKID);

	//TODO
} */


hook_method<void (CNPCSkill::*)(unsigned long time)> CNPCSkill::_SetFSMReleaseTime(SERVER, "CNPCSkill::SetFSMReleaseTime");
void CNPCSkill::SetFSMReleaseTime(unsigned long time)
{
	return (this->*_SetFSMReleaseTime)(time);

	//TODO
}


hook_method<void (CNPCSkill::*)(void)> CNPCSkill::_ProcessFSMReleaseTime(SERVER, "CNPCSkill::ProcessFSMReleaseTime");
void CNPCSkill::ProcessFSMReleaseTime(void)
{
	return (this->*_ProcessFSMReleaseTime)();

	//TODO
}


hook_method<void (CNPCSkill::*)(unsigned long id, unsigned long lifeTime)> CNPCSkill::_SetInfoByCreatorPC(SERVER, "CNPCSkill::SetInfoByCreatorPC");
void CNPCSkill::SetInfoByCreatorPC(unsigned long id, unsigned long lifeTime)
{
	return (this->*_SetInfoByCreatorPC)(id, lifeTime);

	//TODO
}


//hook_method<unsigned long (CNPCSkill::*)(void)> CNPCSkill::_GetMyCreatorPCAID(SERVER, "CNPCSkill::GetMyCreatorPCAID");
unsigned long CNPCSkill::GetMyCreatorPCAID(void)
{
//	return (this->*_GetMyCreatorPCAID)();

	return m_creatorPCAID;
}


//hook_method<void (CNPCSkill::*)(short par)> CNPCSkill::_SetEmoticon(SERVER, "CNPCSkill::SetEmoticon");
void CNPCSkill::SetEmoticon(short par)
{
//	return (this->*_SetEmoticon)(par);

	m_emoticon = par;
}


//hook_method<void (CNPCSkill::*)(short par)> CNPCSkill::_SetAITypeAfter(SERVER, "CNPCSkill::SetAITypeAfter");
void CNPCSkill::SetAITypeAfter(short par)
{
//	return (this->*_SetAITypeAfter)(par);

	m_aiType = par;
}


hook_method<void (CNPCSkill::*)(unsigned short SKID, int skLevel, int castTime, int chatNo)> CNPCSkill::_ForceUseSkill(SERVER, "CNPCSkill::ForceUseSkill");
void CNPCSkill::ForceUseSkill(unsigned short SKID, int skLevel, int castTime, int chatNo)
{
	return (this->*_ForceUseSkill)(SKID, skLevel, castTime, chatNo);

	//TODO
}


hook_method<void (CNPCSkill::*)(void)> CNPCSkill::_ResetAttackedState(SERVER, "CNPCSkill::ResetAttackedState");
void CNPCSkill::ResetAttackedState(void)
{
	return (this->*_ResetAttackedState)();

	//TODO
}


hook_method<int (CNPCSkill::*)(CNPC* npc, int condition, int value)> CNPCSkill::_IsCondition(SERVER, "CNPCSkill::IsCondition");
int CNPCSkill::IsCondition(CNPC* npc, int condition, int value)
{
	return (this->*_IsCondition)(npc, condition, value);

	//TODO
}


hook_method<int (CNPCSkill::*)(CNPC* npc, int condition, int value)> CNPCSkill::_IsComradeCondition(SERVER, "CNPCSkill::IsComradeCondition");
int CNPCSkill::IsComradeCondition(CNPC* npc, int condition, int value)
{
	return (this->*_IsComradeCondition)(npc, condition, value);

	//TODO
}


hook_method<void (CNPCSkill::*)(void)> CNPCSkill::_ProcessPostDelayTimer(SERVER, "CNPCSkill::ProcessPostDelayTimer");
void CNPCSkill::ProcessPostDelayTimer(void)
{
	return (this->*_ProcessPostDelayTimer)();

	//TODO
}


hook_method<int (CNPCSkill::*)(unsigned long SKID)> CNPCSkill::_GetPostDelayTime(SERVER, "CNPCSkill::GetPostDelayTime");
int CNPCSkill::GetPostDelayTime(unsigned long SKID)
{
	return (this->*_GetPostDelayTime)(SKID);

	//TODO
}


hook_method<NPCSKILLINFO* (CNPCSkill::*)(unsigned long SKID)> CNPCSkill::_GetNPCSkillInfo(SERVER, "CNPCSkill::GetNPCSkillInfo");
NPCSKILLINFO* CNPCSkill::GetNPCSkillInfo(unsigned long SKID)
{
	return (this->*_GetNPCSkillInfo)(SKID);

	//TODO
}


hook_method<int (CNPCSkill::*)(unsigned long SKID)> CNPCSkill::_IsAvailableSkill(SERVER, "CNPCSkill::IsAvailableSkill");
int CNPCSkill::IsAvailableSkill(unsigned long SKID)
{
	return (this->*_IsAvailableSkill)(SKID);

	//TODO
}


hook_method<void (CNPCSkill::*)(NPCSKILLINFO* skillInfo)> CNPCSkill::_ProcessSkillPreDelayTime(SERVER, "CNPCSkill::ProcessSkillPreDelayTime");
void CNPCSkill::ProcessSkillPreDelayTime(NPCSKILLINFO* skillInfo)
{
	return (this->*_ProcessSkillPreDelayTime)(skillInfo);

	//TODO
}
