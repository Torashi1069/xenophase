#include "CharacterMgr.h"
#include "SkillTypeInfo.h"


CSkillTypeInfo::CSkillTypeInfo(void) // line 6
{
	m_attackRange = 1;
	m_pattern = 0;
	m_flag = 0;
	m_property = 0;
	m_isEventSkill = 0;
	m_dispel = 0;
	m_joblevel = 0;
	m_joblevel_ValidJob = 0;
	m_GNDRange = 0;
	m_referSKRNG = 0;
	m_singlePostDelay[0] = 0;
	m_singlePostDelay[1] = 0;
	m_singlePostDelay[2] = 0;
	m_singlePostDelay[3] = 0;
	m_singlePostDelay[4] = 0;
	m_singlePostDelay[5] = 0;
	m_singlePostDelay[6] = 0;
	m_singlePostDelay[7] = 0;
	m_singlePostDelay[8] = 0;
	m_singlePostDelay[9] = 0;
	m_globalPostDelay[0] = 0;
	m_globalPostDelay[1] = 0;
	m_globalPostDelay[2] = 0;
	m_globalPostDelay[3] = 0;
	m_globalPostDelay[4] = 0;
	m_globalPostDelay[5] = 0;
	m_globalPostDelay[6] = 0;
	m_globalPostDelay[7] = 0;
	m_globalPostDelay[8] = 0;
	m_globalPostDelay[9] = 0;
	m_castFixedDelay[0] = 0;
	m_castFixedDelay[1] = 0;
	m_castFixedDelay[2] = 0;
	m_castFixedDelay[3] = 0;
	m_castFixedDelay[4] = 0;
	m_castFixedDelay[5] = 0;
	m_castFixedDelay[6] = 0;
	m_castFixedDelay[7] = 0;
	m_castFixedDelay[8] = 0;
	m_castFixedDelay[9] = 0;
	m_castStatDelay[0] = 0;
	m_castStatDelay[1] = 0;
	m_castStatDelay[2] = 0;
	m_castStatDelay[3] = 0;
	m_castStatDelay[4] = 0;
	m_castStatDelay[5] = 0;
	m_castStatDelay[6] = 0;
	m_castStatDelay[7] = 0;
	m_castStatDelay[8] = 0;
	m_castStatDelay[9] = 0;
}


CSkillTypeInfo::~CSkillTypeInfo(void) // line 41 (SkillTypeInfo.h)
{
}


//hook_method<void (CSkillTypeInfo::*)(unsigned short SKID)> CSkillTypeInfo::_SetSKID(SERVER, "CSkillTypeInfo::SetSKID");
void CSkillTypeInfo::SetSKID(unsigned short SKID) // line ??
{
//	return (this->*_SetSKID)(SKID);

	m_SKID = SKID;
}


//hook_method<void (CSkillTypeInfo::*)(int pattern)> CSkillTypeInfo::_SetPattern(SERVER, "CSkillTypeInfo::SetPattern");
void CSkillTypeInfo::SetPattern(int pattern)
{
//	return (this->*_SetPattern)(pattern);

	m_pattern = pattern;
}


//hook_method<char* (CSkillTypeInfo::*)(void)> CSkillTypeInfo::_GetName(SERVER, "CSkillTypeInfo::GetName");
char* CSkillTypeInfo::GetName(void) // line ??
{
//	return (this->*_GetName)();

	return m_name;
}


//hook_method<unsigned short (CSkillTypeInfo::*)(void)> CSkillTypeInfo::_GetSKID(SERVER, "CSkillTypeInfo::GetSKID");
unsigned short CSkillTypeInfo::GetSKID(void) // line ??
{
//	return (this->*_GetSKID)();

	return m_SKID;
}


//hook_method<int (CSkillTypeInfo::*)(void)> CSkillTypeInfo::_GetType(SERVER, "CSkillTypeInfo::GetType");
int CSkillTypeInfo::GetType(void) // line ??
{
//	return (this->*_GetType)();

	return m_type;
}


//hook_method<int (CSkillTypeInfo::*)(void)> CSkillTypeInfo::_GetPattern(SERVER, "CSkillTypeInfo::GetPattern");
int CSkillTypeInfo::GetPattern(void)
{
//	return (this->*_GetPattern)();

	return m_pattern;
}


hook_method<int (CSkillTypeInfo::*)(short skLevel)> CSkillTypeInfo::_GetGNDRange(SERVER, "CSkillTypeInfo::GetGNDRange");
int CSkillTypeInfo::GetGNDRange(short skLevel) // line 54 (SkillTypeInfo.h)
{
	return (this->*_GetGNDRange)(skLevel);

	return m_GNDRange;
}


//hook_method<int (CSkillTypeInfo::*)(void)> CSkillTypeInfo::_IsEventSkill(SERVER, "CSkillTypeInfo::IsEventSkill");
int CSkillTypeInfo::IsEventSkill(void) // line ??
{
//	return (this->*_IsEventSkill)();

	return m_isEventSkill;
}


//hook_method<void (CSkillTypeInfo::*)(int isEventSkill)> CSkillTypeInfo::_SetEventSkill(SERVER, "CSkillTypeInfo::SetEventSkill");
void CSkillTypeInfo::SetEventSkill(int isEventSkill) // line ??
{
//	return (this->*_SetEventSkill)(isEventSkill);

	m_isEventSkill = isEventSkill;
}


hook_method<bool (CSkillTypeInfo::*)(short level, char job)> CSkillTypeInfo::_IsNextLevelUpgradable(SERVER, "CSkillTypeInfo::IsNextLevelUpgradable");
bool CSkillTypeInfo::IsNextLevelUpgradable(short level, char job) // line 63 (SkillTypeInfo.h)
{
	return (this->*_IsNextLevelUpgradable)(level, job);

	//TODO
}


hook_method<short (CSkillTypeInfo::*)(void)> CSkillTypeInfo::_GetMaxLevel(SERVER, "CSkillTypeInfo::GetMaxLevel");
short CSkillTypeInfo::GetMaxLevel(void) // line ??
{
	return (this->*_GetMaxLevel)();

	return 0;
}


hook_method<int (CSkillTypeInfo::*)(CCharacter* sender, unsigned short receiver, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4)> CSkillTypeInfo::_OnMsg(SERVER, "CSkillTypeInfo::OnMsg");
int CSkillTypeInfo::OnMsg(CCharacter* sender, unsigned short receiver, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4) // line 35
{
	return (this->*_OnMsg)(sender, receiver, MsgID, skLevel, targetID, par3, par4);

	if( MsgID == 9 )
	{
		g_characterMgr->CCharacterMgr::SendMsg(NULL, sender, CM_SKILL_LEVELUP, receiver, 0, 0, 0);
	}

	return 0;
}


hook_method<short (CSkillTypeInfo::*)(short level)> CSkillTypeInfo::_GetSPCost(SERVER, "CSkillTypeInfo::GetSPCost");
short CSkillTypeInfo::GetSPCost(short level) // line ??
{
	return (this->*_GetSPCost)(level);

	return 0;
}


hook_method<int (CSkillTypeInfo::*)(short job)> CSkillTypeInfo::_IsAvailableJob(SERVER, "CSkillTypeInfo::IsAvailableJob");
int CSkillTypeInfo::IsAvailableJob(short job) // line ??
{
	return (this->*_IsAvailableJob)(job);

	return 0;
}


hook_method<short (CSkillTypeInfo::*)(int level)> CSkillTypeInfo::_GetAttackRange(SERVER, "CSkillTypeInfo::GetAttackRange");
short CSkillTypeInfo::GetAttackRange(int level) // line 71
{
	return (this->*_GetAttackRange)(level);

	return m_attackRange;
}


hook_method<short (CSkillTypeInfo::*)(short level)> CSkillTypeInfo::_GetPreDelayTime(SERVER, "CSkillTypeInfo::GetPreDelayTime");
short CSkillTypeInfo::GetPreDelayTime(short level) // line ??
{
	return (this->*_GetPreDelayTime)(level);

	return 0;
}


hook_method<short (CSkillTypeInfo::*)(short level)> CSkillTypeInfo::_GetPostDelayTM(SERVER, "CSkillTypeInfo::GetPostDelayTM");
short CSkillTypeInfo::GetPostDelayTM(short level) // line ??
{
	return (this->*_GetPostDelayTM)(level);

	return 0;
}


hook_method<unsigned long (CSkillTypeInfo::*)(void)> CSkillTypeInfo::_GetProperty(SERVER, "CSkillTypeInfo::GetProperty");
unsigned long CSkillTypeInfo::GetProperty(void) // line 53
{
	return (this->*_GetProperty)();

	return m_property;
}


hook_method<void (CSkillTypeInfo::*)(unsigned long property)> CSkillTypeInfo::_SetProperty(SERVER, "CSkillTypeInfo::SetProperty");
void CSkillTypeInfo::SetProperty(unsigned long property) // line 58
{
	return (this->*_SetProperty)(property);

	m_property = property;
}


//hook_method<int (CSkillTypeInfo::*)(void)> CSkillTypeInfo::_GetAvailableJobLevel(SERVER, "CSkillTypeInfo::GetAvailableJobLevel");
int CSkillTypeInfo::GetAvailableJobLevel(void) // line ??
{
//	return (this->*_GetAvailableJobLevel)();

	return m_joblevel;
}


//hook_method<int (CSkillTypeInfo::*)(void)> CSkillTypeInfo::_GetAvailableJobLevel_ValidJob(SERVER, "CSkillTypeInfo::GetAvailableJobLevel_ValidJob");
int CSkillTypeInfo::GetAvailableJobLevel_ValidJob(void) // line ??
{
//	return (this->*_GetAvailableJobLevel_ValidJob)();

	return m_joblevel_ValidJob;
}


hook_method<short (CSkillTypeInfo::*)(void)> CSkillTypeInfo::_GetVersion(SERVER, "CSkillTypeInfo::GetVersion");
short CSkillTypeInfo::GetVersion(void) // line ??
{
	return (this->*_GetVersion)();

	return 1;
}


hook_method<bool (CSkillTypeInfo::*)(int skLevel)> CSkillTypeInfo::_IsEnableIgnoreMagicImmune(SERVER, "CSkillTypeInfo::IsEnableIgnoreMagicImmune");
bool CSkillTypeInfo::IsEnableIgnoreMagicImmune(int skLevel) // line 63
{
	return (this->*_IsEnableIgnoreMagicImmune)(skLevel);

	return ( m_pattern != 2 );
}


hook_method<int (CSkillTypeInfo::*)(CCharacter* in_cpSpellCH, CCharacter* in_cpTargetCH, const int in_Level, int& out_USESKILL_FAIL) const> CSkillTypeInfo::_IsSpellConditionGratify(SERVER, "CSkillTypeInfo::IsSpellConditionGratify");
int CSkillTypeInfo::IsSpellConditionGratify(CCharacter* in_cpSpellCH, CCharacter* in_cpTargetCH, const int in_Level, int& out_USESKILL_FAIL) const // line 105 (SkillTypeInfo.h)
{
	return (this->*_IsSpellConditionGratify)(in_cpSpellCH, in_cpTargetCH, in_Level, out_USESKILL_FAIL);

	return 1;
}


int SK_KN_BOWLINGBASH::OnMsg(CCharacter* sender, unsigned short receiver, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4) // line 2384-2400
{
	if( MsgID == 12 )
	{
		MSG_TYPE4_FIVEDWORD data;
		data.data1 = 40 * skLevel + 100;
		data.data2 = 100;
		data.data3 = 1;
		data.data4 = par3; // sp cost
		data.data5 = skLevel;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, sender, CM_SPATTACKSKILL_TOCHARACTER, (int)receiver, (int)targetID, (int)&data, 0);
		return 0;
	}
	else
	{
		this->CSkillTypeInfo::OnMsg(sender, receiver, MsgID, skLevel, targetID, par3, 0);
		return 0;
	}
}


int SK_PR_SANCTUARY::OnMsg(CCharacter* sender, unsigned short receiver, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4) // line 2644-2669
{
	if( MsgID == 12 )
	{
		MSG_TYPE5_SIXDWORD data;
		data.data1 = *((int*)par3 + 0); //TODO
		data.data2 = *((int*)par3 + 4); //TODO
		data.data3 = 100 * skLevel;
		if( skLevel > 6 )
			data.data3 = 777;
		data.data4 = 3000 * skLevel + 1000;
		data.data5 = targetID;
		data.data6 = skLevel;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, sender, CM_SKILL_GROUNDTYPE, receiver, targetID, (int)&data, 0);
		return 0;
	}
	else
	if ( MsgID == 14 )
	{
		return 2 * skLevel + 6;
	}
	else
	{
		this->CSkillTypeInfo::OnMsg(sender, receiver, MsgID, skLevel, targetID, par3, 0);
		return 0;
	}
}
