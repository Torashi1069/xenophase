#include "Character.h"
#include "CharBuff.h"


CCharBuff::CCharBuff()
{
	this->CCharBuff::Reset();
}


CCharBuff::~CCharBuff()
{
	this->CCharBuff::Reset();
}


void CCharBuff::SetOwner(CCharacter* owner)
{
	this->Reset();
	m_owner = owner;
}


void CCharBuff::Reset()
{
	m_owner = NULL;
	memset(&m_status, 0, sizeof(m_status));
	memset(&m_damaged, 0, sizeof(m_damaged));
	memset(&m_heal, 0, sizeof(m_heal));
	memset(&m_aspd, 0, sizeof(m_aspd));
	memset(&m_immuneMagic, 0, sizeof(m_immuneMagic));
}


bool CCharBuff::UpdateParameterValue(unsigned short type, int value)
{
	switch( type )
	{
	case VAR_ATTPOWER:
		m_status.atk += value;
		m_owner->UpdateParameterValue(VAR_ATTPOWER, 0);
	break;
	case VAR_HITSUCCESSVALUE:
		m_status.hit += value;
		m_owner->UpdateParameterValue(VAR_HITSUCCESSVALUE, 0);
	break;
	case VAR_MAXHPPERCENT:
		m_status.mhpPercent += value;
		m_owner->UpdateParameterValue(VAR_MAXHPPERCENT, 0);
		m_owner->UpdateParameterValue(VAR_MAXHP, 0);
	break;
	case VAR_MAXSPPERCENT:
		m_status.mspPercent += value;
		m_owner->UpdateParameterValue(VAR_MAXSPPERCENT, 0);
		m_owner->UpdateParameterValue(VAR_MAXSP, 0);
	break;
	case VAR_BASICAVOIDANCE:
		m_status.flee += value;
		m_owner->UpdateParameterValue(VAR_BASICAVOIDANCE, 0);
	break;
	case VAR_PLUSASPDPERCENT:
		m_aspd.plusAttackSpeedPercent += value;
		m_owner->UpdateParameterValue(VAR_ASPD, 0);
	break;
	default:
		return false;
	break;
	};

	return true;
}


int CCharBuff::GetParameterValue(unsigned short type)
{
	switch( type )
	{
	case VAR_ATTPOWER:
		return m_status.atk;
	break;
	case VAR_HITSUCCESSVALUE:
		return m_status.hit;
	break;
	case VAR_MAXHPPERCENT:
		return m_status.mhpPercent;
	break;
	case VAR_MAXSPPERCENT:
		return m_status.mspPercent;
	break;
	case VAR_BASICAVOIDANCE:
		return m_status.flee;
	break;
	case VAR_PLUSASPDPERCENT:
		return m_aspd.plusAttackSpeedPercent;
	break;
	default:
		return 0;
	break;
	};
}


void CCharBuff::Update_Damaged_DirectSubPercent(int value)
{
	m_damaged.directSubPercent += value;
}


int CCharBuff::Get_Damaged_DirectSubPercent()
{
	return m_damaged.directSubPercent;
}


void CCharBuff::Update_Damaged_MagicSubPercent(int value)
{
	m_damaged.magicSubPercent += value;
}


int CCharBuff::Get_Damaged_MagicSubPercent()
{
	return m_damaged.magicSubPercent;
}


void CCharBuff::Update_Heal_HP_ModifyPercent(int value)
{
	m_heal.hp_modifyPercent += value;
}


int CCharBuff::Get_Heal_HP_ModifyPercent()
{
	return m_heal.hp_modifyPercent;
}


void CCharBuff::Update_Heal_SP_ModifyPercent(int value)
{
	m_heal.sp_modifyPercent += value;
}


int CCharBuff::Get_Heal_SP_ModifyPercent()
{
	return m_heal.sp_modifyPercent;
}


void CCharBuff::Update_ImmuneMagic_Percent(int value)
{
	m_immuneMagic.percent += value;
}


int CCharBuff::Get_ImmnueMagic_Percnet()
{
	return m_immuneMagic.percent;
}
