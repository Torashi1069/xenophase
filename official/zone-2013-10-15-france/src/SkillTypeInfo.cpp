#include "Character.h"
#include "CharacterMgr.h"
#include "SkillTypeInfo.h"
#include "SkillTypeInfoMgr.h"


CSkillTypeInfo::CSkillTypeInfo()
{
	m_property = 0;
	m_flag = 0;
//	m_SKID = 0;
	m_referSKRNG = 0;
	m_pattern = SKILLPATT_NONE;
	m_isEventSkill = FALSE;
//	m_type = 0;
	m_attackRange = 1;
//	memset(m_name, '\0', sizeof(m_name));
	m_dispel = 0;
	m_joblevel = 0;
	m_joblevel_ValidJob = 0;
	m_GNDRange = 0;

	memset(m_singlePostDelay, 0, sizeof(m_singlePostDelay));
	memset(m_globalPostDelay, 0, sizeof(m_globalPostDelay));
	memset(m_castFixedDelay, 0, sizeof(m_castFixedDelay));
	memset(m_castStatDelay, 0, sizeof(m_castStatDelay));
}


CSkillTypeInfo::~CSkillTypeInfo()
{
}


void CSkillTypeInfo::SetName(const char* name)
{
	memcpy_s(m_name, sizeof(m_name), name, 24);
	m_name[countof(m_name)-1] = '\0';
}


int CSkillTypeInfo::OnMsg(CCharacter* sender, unsigned short receiver, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4)
{
	switch( MsgID )
	{
	case SM_LEVEL_UP:
	{
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, sender, CM_SKILL_LEVELUP, receiver, 0, 0, 0);
	}
	break;
	};

	return 0;
}


BOOL CSkillTypeInfo::IsAvailableJob(short job)
{
	return FALSE;
}


unsigned long CSkillTypeInfo::GetProperty()
{
	return m_property;
}


void CSkillTypeInfo::SetProperty(unsigned long property)
{
	m_property = property;
}


bool CSkillTypeInfo::IsEnableIgnoreMagicImmune(int skLevel)
{
	return ( m_pattern != SKILLPATT_ATTACKSPELL );
}


void CSkillTypeInfo::SetSKID(unsigned short SKID)
{
	m_SKID = SKID;
}


void CSkillTypeInfo::SetType(int type)
{
	m_type = type;
}


void CSkillTypeInfo::SetFlag(unsigned long flag)
{
	m_flag |= flag;
}


void CSkillTypeInfo::SetReferSKRNG(unsigned short SKID)
{
	m_referSKRNG = SKID;
}


void CSkillTypeInfo::SetPattern(int pattern)
{
	m_pattern = pattern;
}


char* CSkillTypeInfo::GetName()
{
	return m_name;
}


unsigned short CSkillTypeInfo::GetSKID()
{
	return m_SKID;
}


int CSkillTypeInfo::GetType()
{
	return m_type;
}


int CSkillTypeInfo::GetPattern()
{
	return m_pattern;
}


int CSkillTypeInfo::GetGNDRange(short skLevel)
{
	return m_GNDRange;
}


unsigned long CSkillTypeInfo::GetFlag()
{
	return m_flag;
}


unsigned short CSkillTypeInfo::GetReferSKRNG()
{
	return m_referSKRNG;
}


BOOL CSkillTypeInfo::IsEventSkill()
{
	return m_isEventSkill;
}


void CSkillTypeInfo::SetEventSkill(BOOL flag)
{
	m_isEventSkill = flag;
}


bool CSkillTypeInfo::IsNextLevelUpgradable(short level, char job)
{
	if( m_isEventSkill )
		return false;

	return ( level < this->GetMaxLevel() );
}


short CSkillTypeInfo::GetMaxLevel()
{
	return 0;
}


short CSkillTypeInfo::GetSPCost(short level)
{
	return 0;
}


short CSkillTypeInfo::GetAttackRange(int level)
{
	return m_attackRange;
}


short CSkillTypeInfo::GetPreDelayTime(short level)
{
	return 0;
}


short CSkillTypeInfo::GetPostDelayTM(short level)
{
	return 0;
}


int CSkillTypeInfo::IsPossibleDispel()
{
	return m_dispel;
}


void CSkillTypeInfo::SetAvailableJobLevel(int validJob, int joblevel)
{
	m_joblevel_ValidJob = validJob;
	m_joblevel = joblevel;
}


int CSkillTypeInfo::GetAvailableJobLevel()
{
	return m_joblevel;
}


int CSkillTypeInfo::GetAvailableJobLevel_ValidJob()
{
	return m_joblevel_ValidJob;
}


short CSkillTypeInfo::GetVersion()
{
	return 1;
}


int CSkillTypeInfo::GetSinglePostDelay(short skLevel)
{
	return m_singlePostDelay[skLevel - 1];
}


int CSkillTypeInfo::GetGlobalPostDelay(short skLevel)
{
	return m_globalPostDelay[skLevel - 1];
}


void CSkillTypeInfo::SetSinglePostDelay(short skLevel, int time)
{
	m_singlePostDelay[skLevel - 1] = time;
}


void CSkillTypeInfo::SetGlobalPostDelay(short skLevel, int time)
{
	m_globalPostDelay[skLevel - 1] = time;
}


void CSkillTypeInfo::SetCastFixedDelay(short skLevel, int time)
{
	m_castFixedDelay[skLevel - 1] = time;
}


int CSkillTypeInfo::GetCastFixedDelay(short skLevel)
{
	return m_castFixedDelay[skLevel - 1];
}


void CSkillTypeInfo::SetCastStatDelay(short skLevel, int time)
{
	m_castStatDelay[skLevel - 1] = time;
}


int CSkillTypeInfo::GetCastStatDelay(short skLevel)
{
	return m_castStatDelay[skLevel - 1];
}


BOOL CSkillTypeInfo::IsSpellConditionGratify(CCharacter* in_cpSpellCH, CCharacter* in_cpTarget, const int in_Level, int& out_USESKILL_FAIL) const
{
	return TRUE;
}


std::pair<bool,int> CSkillTypeInfo::IsSpellConditionGratify2nd(CCharacter* in_cpSpellCH, CCharacter* in_cpTargetCH, const int in_Level, const int in_spcost) const
{
	int out_USESKILL_FAIL = USESKILL_FAIL;
	if( !this->IsSpellConditionGratify(in_cpSpellCH, in_cpTargetCH, in_Level, out_USESKILL_FAIL) )
		return std::pair<bool,int>(false, out_USESKILL_FAIL);

	return std::pair<bool,int>(true, 0);
}
