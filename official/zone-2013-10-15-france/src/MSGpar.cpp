#include "MSGpar.h"
namespace MSGpar {


bool IsNotifySkillAck(const int in_SKID, CVar in_par)
{
	switch( in_SKID )
	{
	case 215: // SKID_RG_STRIPWEAPON
		return !in_par.m_Var.m_RG_STRIPWEAPON.bBlockClientNotify;
	break;
	case 216: // SKID_RG_STRIPSHIELD
		return !in_par.m_Var.m_RG_STRIPSHIELD.bBlockClientNotify;
	break;
	case 217: // SKID_RG_STRIPARMOR
		return !in_par.m_Var.m_RG_STRIPARMOR.bBlockClientNotify;
	break;
	case 218: // SKID_RG_STRIPHELM
		return !in_par.m_Var.m_RG_STRIPHELM.bBlockClientNotify;
	break;
	case 2298: // SKID_SC_STRIPACCESSARY
		return !in_par.m_Var.m_SC_STRIPACCESSARY.bBlockClientNotify;
	break;
	case 2218: // SKID_WL_TETRAVORTEX_FIRE
	case 2219: // SKID_WL_TETRAVORTEX_WATER
	case 2220: // SKID_WL_TETRAVORTEX_WIND
	case 2221: // SKID_WL_TETRAVORTEX_GROUND
		return false;
	break;
	case 2415: // SKID_WM_REVERBERATION_MELEE
	case 2416: // SKID_WM_REVERBERATION_MAGIC
	case 2516: // SKID_WM_SEVERE_RAINSTORM_MELEE
		return false;
	break;
	};

	return true;
}


}; // namespace
