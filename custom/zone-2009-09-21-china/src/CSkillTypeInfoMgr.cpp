#include "CSkillTypeInfoMgr.hpp"


CSkillTypeInfoMgr::CSkillTypeInfoMgr(void) // line 23
{
}


CSkillTypeInfoMgr::~CSkillTypeInfoMgr(void) // line 27
{
	this->CSkillTypeInfoMgr::Reset();
}


hook_method<void (CSkillTypeInfoMgr::*)(void)> CSkillTypeInfoMgr::_Init(SERVER, "CSkillTypeInfoMgr::Init");
void CSkillTypeInfoMgr::Init(void) // line 32
{
	return (this->*_Init)();

	//TODO
}


hook_method<void (CSkillTypeInfoMgr::*)(void)> CSkillTypeInfoMgr::_Reset(SERVER, "CSkillTypeInfoMgr::Reset");
void CSkillTypeInfoMgr::Reset(void) // line 94
{
	return (this->*_Reset)();

	//TODO
}


hook_method<unsigned short (CSkillTypeInfoMgr::*)(const char* skName) const> CSkillTypeInfoMgr::_GetSKID(SERVER, "CSkillTypeInfoMgr::GetSKID");
unsigned short CSkillTypeInfoMgr::GetSKID(const char* skName) const // line 122-127
{
	return (this->*_GetSKID)(skName);

	//TODO
}


hook_method<int (CSkillTypeInfoMgr::*)(CCharacter* sender, int SKID, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4)> CSkillTypeInfoMgr::_SendMsg(SERVER, "CSkillTypeInfoMgr::SendMsg");
int CSkillTypeInfoMgr::SendMsg(CCharacter* sender, int SKID, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4) // line 251
{
	return (this->*_SendMsg)(sender, SKID, MsgID, skLevel, targetID, par3, par4);

	CSkillTypeInfo* info = this->CSkillTypeInfoMgr::SearchSkillTypeInfo(SKID);
	if( info == NULL )
		return 0;

	return info->OnMsg(sender, SKID, MsgID, skLevel, targetID, par3, par4);
}


hook_method<CSkillTypeInfo* (CSkillTypeInfoMgr::*)(unsigned short SKID)> CSkillTypeInfoMgr::_SearchSkillTypeInfo(SERVER, "CSkillTypeInfoMgr::SearchSkillTypeInfo");
CSkillTypeInfo* CSkillTypeInfoMgr::SearchSkillTypeInfo(unsigned short SKID) // line 263
{
	return (this->*_SearchSkillTypeInfo)(SKID);

	//TODO
}


hook_method<short (CSkillTypeInfoMgr::*)(unsigned short SKID)> CSkillTypeInfoMgr::_GetSKClass(SERVER, "CSkillTypeInfoMgr::GetSKClass");
short CSkillTypeInfoMgr::GetSKClass(unsigned short SKID) // line 351
{
	return (this->*_GetSKClass)(SKID);

	//TODO
}


hook_method<short (CSkillTypeInfoMgr::*)(unsigned short SKID, int level)> CSkillTypeInfoMgr::_GetAttackRange(SERVER, "CSkillTypeInfoMgr::GetAttackRange");
short CSkillTypeInfoMgr::GetAttackRange(unsigned short SKID, int level) // line 432
{
	return (this->*_GetAttackRange)(SKID, level);

	CSkillTypeInfo* info = this->CSkillTypeInfoMgr::SearchSkillTypeInfo(SKID);
	return ( info != NULL ) ? info->GetAttackRange(level) : 0;
}


hook_method<int (CSkillTypeInfoMgr::*)(short job, unsigned short SKID)> CSkillTypeInfoMgr::_IsAvailableJob(SERVER, "CSkillTypeInfoMgr::IsAvailableJob");
int CSkillTypeInfoMgr::IsAvailableJob(short job, unsigned short SKID) // line 913
{
	return (this->*_IsAvailableJob)(job, SKID);

	//TODO
}


hook_method<int (CSkillTypeInfoMgr::*)(short job, unsigned short SKID)> CSkillTypeInfoMgr::_IsConditionalSkill(SERVER, "CSkillTypeInfoMgr::IsConditionalSkill");
int CSkillTypeInfoMgr::IsConditionalSkill(short job, unsigned short SKID) // line 968
{
	return (this->*_IsConditionalSkill)(job, SKID);

	//TODO
}


hook_method<int (CSkillTypeInfoMgr::*)(short job, unsigned short SKID)> CSkillTypeInfoMgr::_IsConditionSkill_HO(SERVER, "CSkillTypeInfoMgr::IsConditionSkill_HO");
int CSkillTypeInfoMgr::IsConditionSkill_HO(short job, unsigned short SKID) // line 998
{
	return (this->*_IsConditionSkill_HO)(job, SKID);

	//TODO
}


hook_method<mystd::map<unsigned short,int>* (CSkillTypeInfoMgr::*)(short job, unsigned short SKID)> CSkillTypeInfoMgr::_GetLowerSkillTreeInfo(SERVER, "CSkillTypeInfoMgr::GetLowerSkillTreeInfo");
mystd::map<unsigned short,int>* CSkillTypeInfoMgr::GetLowerSkillTreeInfo(short job, unsigned short SKID) // line 1022
{
	return (this->*_GetLowerSkillTreeInfo)(job, SKID);

	//TODO
}


hook_method<int (CSkillTypeInfoMgr::*)(unsigned short SKID, int type)> CSkillTypeInfoMgr::_IsSkillCategory(SERVER, "CSkillTypeInfoMgr::IsSkillCategory");
int CSkillTypeInfoMgr::IsSkillCategory(unsigned short SKID, int type) // line 1140
{
	return (this->*_IsSkillCategory)(SKID, type);

	//TODO
}


hook_method<short (CSkillTypeInfoMgr::*)(unsigned short SKID, short level)> CSkillTypeInfoMgr::_GetPostDelayTM(SERVER, "CSkillTypeInfoMgr::GetPostDelayTM");
short CSkillTypeInfoMgr::GetPostDelayTM(unsigned short SKID, short level) // line 1287-1293
{
	return (this->*_GetPostDelayTM)(SKID, level);

	CSkillTypeInfo* info = this->CSkillTypeInfoMgr::SearchSkillTypeInfo(SKID);
	if( info == NULL )
		return 0;

	return info->GetPostDelayTM(level);
}


hook_method<bool (CSkillTypeInfoMgr::*)(void)> CSkillTypeInfoMgr::_InitSkillScript(SERVER, "CSkillTypeInfoMgr::InitSkillScript");
bool CSkillTypeInfoMgr::InitSkillScript(void) // line 1297
{
	return (this->*_InitSkillScript)();

	//TODO
}
