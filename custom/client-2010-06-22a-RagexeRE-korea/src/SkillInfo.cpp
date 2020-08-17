#include "Lua.h"
#include "Session.h"
#include "SkillInfo.h"


/// locals
static const char* unknownSkill = "Unknown-Skill";


const char* GetSkillName(int SKID)
{
	const char* result = NULL;

	if( !g_session.m_lua->CLua::Execute("GetSkillName", "d>s", SKID, &result) )
		result = unknownSkill;

	return result;
}


bool SKILL_INFO::IsGoodSkillForActor(int skillId)
{
	switch( skillId )
	{
	case 4: // SKID_SM_RECOVERY
	case 28: // SKID_AL_HEAL
	case 29: // SKID_AL_INCAGI
	case 34: // SKID_AL_BLESSING
	case 35: // SKID_AL_CURE
	case 53: // SKID_TF_DETOXIFY
	case 54: // SKID_ALL_RESURRECTION
	case 66: // SKID_PR_IMPOSITIO
	case 67: // SKID_PR_SUFFRAGIUM
	case 68: // SKID_PR_ASPERSIO
	case 71: // SKID_PR_SLOWPOISON
	case 72: // SKID_PR_STRECOVERY
	case 73: // SKID_PR_KYRIE
		return true;
	case 108: // SKID_BS_REPAIRWEAPON
		return true;
	case 138: // SKID_AS_ENCHANTPOISON
	case 139: // SKID_AS_POISONREACT
	case 231: // SKID_AM_POTIONPITCHER
	case 234: // SKID_AM_CP_WEAPON
	case 235: // SKID_AM_CP_SHIELD
	case 236: // SKID_AM_CP_ARMOR
	case 237: // SKID_AM_CP_HELM
	case 255: // SKID_CR_DEVOTION
	case 256: // SKID_CR_PROVIDENCE
	case 262: // SKID_MO_ABSORBSPIRITS
		return true;
	case 280: // SKID_SA_FLAMELAUNCHER
	case 281: // SKID_SA_FROSTWEAPON
	case 282: // SKID_SA_LIGHTNINGLOADER
	case 283: // SKID_SA_SEISMICWEAPON
		return true;
	case 361: // SKID_HP_ASSUMPTIO
	case 445: // SKID_SL_ALCHEMIST
	case 446: // SKID_AM_BERSERKPITCHER
	case 447: // SKID_SL_MONK
	case 448: // SKID_SL_STAR
	case 449: // SKID_SL_SAGE
	case 450: // SKID_SL_CRUSADER
	case 451: // SKID_SL_SUPERNOVICE
	case 452: // SKID_SL_KNIGHT
	case 453: // SKID_SL_WIZARD
	case 454: // SKID_SL_PRIEST
	case 455: // SKID_SL_BARDDANCER
	case 456: // SKID_SL_ROGUE
	case 457: // SKID_SL_ASSASIN
	case 458: // SKID_SL_BLACKSMITH
	case 460: // SKID_SL_HUNTER
	case 461: // SKID_SL_SOULLINKER
	case 462: // SKID_SL_KAIZEL
	case 463: // SKID_SL_KAAHI
	case 464: // SKID_SL_KAUPE
	case 465: // SKID_SL_KAITE
	case 479: // SKID_CR_FULLPROTECTION
	case 494: // SKID_SL_HIGH
	case 564: // SKID_MB_B_EXCLUDE
		return true;
	case 572: // SKID_SL_DEATHKNIGHT
	case 573: // SKID_SL_COLLECTOR
	case 574: // SKID_SL_NINJA
	case 575: // SKID_SL_GUNNER
		return true;
	case 577: // SKID_DA_RESET
	case 593: // SKID_DE_COIL
	case 621: // SKID_DA_FIRSTSLOT
	case 622: // SKID_DA_HEADDEF
	case 626: // SKID_DA_REWARD
	case 636: // SKID_DA_EARPLUG
	case 637: // SKID_DA_CONTRACT
		return true;
	case 641: // SKID_DA_COPY
	case 642: // SKID_DA_CRYSTAL
	case 643: // SKID_DA_EXP
		return true;
	case 645: // SKID_DA_REBUILD
	case 646: // SKID_DA_JOBCHANGE
	case 688: // SKID_GM_SANDMAN
	case 689: // SKID_CASH_BLESSING
	case 690: // SKID_CASH_INCAGI
	case 691: // SKID_CASH_ASSUMPTIO
	case 694: // SKID_ALL_ANGEL_PROTECT
		return true;
	case 1015: // SKID_MO_KITRANSLATION
		return true;
	case 2001: // SKID_RK_ENCHANTBLADE
		return true;
	case 2026: // SKID_GC_ANTIDOTE
		return true;
	case 2041: // SKID_AB_CLEMENTIA
	case 2042: // SKID_AB_CANTO
	case 2043: // SKID_AB_CHEAL
		return true;
	case 2050: // SKID_AB_RENOVATIO
	case 2051: // SKID_AB_HIGHNESSHEAL
	case 2052: // SKID_AB_CLEARANCE
		return true;
	case 2275: // SKID_NC_REPAIR
		return true;
	case 2287: // SKID_SC_SHADOWFORM
		return true;
	case 2322: // SKID_LG_PIETY
		return true;
	case 2341: // SKID_SR_POWERVELOCITY
		return true;
	case 2345: // SKID_SR_GENTLETOUCH_CURE
		return true;
	case 2347: // SKID_SR_GENTLETOUCH_CHANGE
	case 2348: // SKID_SR_GENTLETOUCH_REVITALIZE
	case 2383: // SKID_MI_HARMONIZE
	case 2421: // SKID_WM_DEADHILLHERE
	case 2425: // SKID_WM_GLOOMYDAY
	case 2451: // SKID_SO_STRIKING
		return true;
	case 2482: // SKID_GN_WALLOFTHORN
		return true;
	case 2515: // SKID_AB_SECRAMENT
		return true;
	case 2537: // SKID_ALL_ODINS_POWER
		return true;
	case 8021: // SKID_MH_PAIN_KILLER
		return true;
	case 8226: // SKID_MER_REGAIN
	case 8227: // SKID_MER_TENDER
	case 8228: // SKID_MER_BENEDICTION
	case 8229: // SKID_MER_RECUPERATE
	case 8230: // SKID_MER_MENTALCURE
	case 8231: // SKID_MER_COMPRESS
	case 8238: // SKID_MER_KYRIE
	case 8239: // SKID_MER_BLESSING
	case 8240: // SKID_MER_INCAGI
		return true;
	default:
		return false;
	};
}
