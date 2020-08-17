#pragma once
#include "Enum.h"
#include "SkillTypeInfo.h"
class CPC;
class CSkill3rdUpdateADBWork { public: enum enumAferAction { AFTER_ACTION_NONE = 0 }; }; //TODO
class CSkill3rdResetADBWork { public: enum enumAfterAction { }; }; //TODO
struct PC_SKILL_INFO;


namespace Skill3rd
{


inline void Delete(const int in_AID, const int in_GID, const int in_SKID)
{
	//TODO
}


inline void Reset(CPC* in_cpPlayer, CSkill3rdResetADBWork::enumAfterAction in_AfterAction)
{
	//TODO
}


enum
{
	SKILL3RD_ATTR_NONE   = 0,
	SKILL3RD_ATTR_NOVICE = 1,
	SKILL3RD_ATTR_QUEST  = 2,
};


inline int GetAttr(const int in_SKID)
{
	if( in_SKID == SKID_NV_BASIC )
		return SKILL3RD_ATTR_NOVICE;

	CSkillTypeInfo* skillTypeInfo = g_skillTypeInfoMgr.CSkillTypeInfoMgr::SearchSkillTypeInfo(in_SKID);
	if( skillTypeInfo == NULL )
		return SKILL3RD_ATTR_NONE;

	if( skillTypeInfo->CSkillTypeInfo::IsEventSkill() )
		return SKILL3RD_ATTR_QUEST;
	
	return SKILL3RD_ATTR_NONE;
}


inline void Update(CPC* in_cpPlayer, CSkill3rdUpdateADBWork::enumAferAction in_AfterAction, const int in_SKID, PC_SKILL_INFO* in_pSkill)
{
	//TODO
}


} // namespace Skill3rd
