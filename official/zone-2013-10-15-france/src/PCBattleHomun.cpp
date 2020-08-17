#include "NpcHomun.h"
#include "PCBattleHomun.h"


CPCBattleHomun::CPCBattleHomun()
{
	this->CPCBattleHomun::Reset();
}


CPCBattleHomun::~CPCBattleHomun()
{
}


void CPCBattleHomun::Reset()
{
	m_EfstList.clear();
	m_Skill.clear();
}


void CPCBattleHomun::GetHomunDBFmt(CNpcHomun* in_cpHomun, HomunDataStuff::CHomunData& io_HomunData)
{
	if( in_cpHomun == NULL )
		return;

	io_HomunData.m_bExist = true;
	in_cpHomun->CNpcHomun::GetEffectData(m_EfstList);
	in_cpHomun->CNpcHomun::GetSkillData(m_Skill);
	io_HomunData.m_EfstList = m_EfstList;

	timeGetTime(); // unused

	for( std::map<unsigned short,HO_SKINFO>::iterator iter = m_Skill.begin(); iter != m_Skill.end(); ++iter )
	{
		unsigned short SKID = iter->first;
		HO_SKINFO Info = iter->second;

		if( Info.bDBupdateWhenLogout || Info.BlockUseTM != 0 )
			io_HomunData.m_Skill[SKID] = Info;
	}
}


void CPCBattleHomun::SetHomunDBFmt(const CLogonPermitADBWork::CHomunLogonData& in_HomunData)
{
	m_EfstList = in_HomunData.m_EfstList;
	m_Skill = in_HomunData.m_Skill;
}


const std::vector<Effect3rd::tagEffect3rdDBFmt>& CPCBattleHomun::GetHomunEffectData()
{
	return m_EfstList;
}


const std::map<unsigned short,HO_SKINFO>& CPCBattleHomun::GetHomunSkillData()
{
	return m_Skill;
}
