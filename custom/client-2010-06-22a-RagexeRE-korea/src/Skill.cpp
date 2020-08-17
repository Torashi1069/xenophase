#include "Skill.h"


CGroundScope::CGroundScope()
{
	m_lastingTime = 0;
	m_rot = 0.0f;
	m_scope_size = 1;
}


hook_func<void (CGroundScope::*)(matrix& vtm)> CGroundScope::_Render("CGroundScope::Render");
void CGroundScope::Render(matrix& vtm)
{
	return (this->*_Render)(vtm);

	//TODO
}


bool CGroundScope::OnProcess()
{
	return ( m_lastingTime >= timeGetTime() );
}


void CGroundScope::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3)
{
	switch ( message )
	{
	case 22:
		m_master_gid = arg1;
	break;
	case 14:
		m_ground_pos_x = arg1;
		m_ground_pos_y = arg2;
	break;
	case 115:
		m_lastingTime = arg1;
	break;
	case 117:
		m_scope_size = 2 + this->CGroundScope::GetScopeSize(arg1);
		m_rot_speed = 0.5f / m_scope_size;
		break;
	default:
		this->CAbleToMakeEffect::SendMsg(sender, message, arg1, arg2, arg3);
	break;
	};
}


int CGroundScope::GetScopeSize(int skill_id)
{
	switch( skill_id )
	{
	case 11: // SKID_MG_NAPALMBEAT
	case 25: // SKID_AL_PNEUMA
	case 47: // SKID_AC_SHOWER
	case 69: // SKID_PR_BENEDICTIO
	case 80: // SKID_WZ_FIREPILLAR
	case 86: // SKID_WZ_WATERBALL
	case 88: // SKID_WZ_FROSTNOVA
	case 110: // SKID_BS_HAMMERFALL
	case 129: // SKID_HT_BLITZBEAT
	case 130: // SKID_HT_DETECTING
	case 137: // SKID_AS_GRIMTOOTH
	case 140: // SKID_AS_VENOMDUST
		return 3;
	case 17: // SKID_MG_FIREBALL
	case 21: // SKID_MG_THUNDERSTORM
	case 70: // SKID_PR_SANCTUARY
	case 91: // SKID_WZ_HEAVENDRIVE
	case 92: // SKID_WZ_QUAGMIRE
		return 5;
	case 85: // SKID_WZ_VERMILION
		return 11;
	case 79: // SKID_PR_MAGNUS
		return 7;
	case 83: // SKID_WZ_METEOR
	case 89: // SKID_WZ_STORMGUST
		return 9;
	case 381: // SKID_SN_FALCONASSAULT
	case 483: // SKID_HW_GANBANTEIN
		return 3;
	case 484: // SKID_HW_GRAVITATION
		return 5;
	case 478: // SKID_CR_SLIMPITCHER
		return 7;
	case 2005: // SKID_RK_WINDCUTTER
		return 5;
	case 2032: // SKID_GC_POISONSMOKE
	case 2044: // SKID_AB_EPICLESIS
		return 5;
	case 2008: // SKID_RK_DRAGONBREATH
		return 9;
	case 2213: // SKID_WL_COMET
		return 30;
	case 2237: // SKID_RA_DETONATOR
		return 7;
	case 2261: // SKID_SO_EL_ACTION
		return 3;
	case 2449: // SKID_SO_PSYCHIC_WAVE
		return 11;
	case 2450: // SKID_SO_CLOUD_KILL
	case 2452: // SKID_SO_WARMER
	case 2453: // SKID_SO_VACUUM_EXTREME
	case 2454: // SKID_SO_VARETYR_SPEAR
		return 7;
	case 2260: // SKID_NC_COLDSLOWER
	case 2446: // SKID_SO_EARTHGRAVE
	case 2447: // SKID_SO_DIAMONDDUST
		return 9;
	default:
		return 0;
	};
}
