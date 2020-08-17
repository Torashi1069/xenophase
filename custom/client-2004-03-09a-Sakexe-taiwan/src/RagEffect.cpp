#include "Globals.h"
#include "RagEffect.h"
#include "Base/ResMgr.h"


CRagEffect::CRagEffect() // line 477-496
{
	m_master = NULL;
	m_type = 0;
	m_level = 1;
	m_flag = 0;
	m_count = 0;
	m_stateCnt = 0;

	m_defZ = 0;
	m_isDirection = 0;
	m_deltaPos.vector3d::Set(0, 0, 0);
	m_deltaPos2.vector3d::Set(0, 0, 0);
	m_deltaPos3.vector3d::Set(0, 0, 0);

	m_ezEffectRes = NULL;
	m_aniClips = NULL;
	m_iCurLayer = 0;
	memset(m_aiCurAniKey, 0, sizeof(m_aiCurAniKey));
	memset(m_rp, 0, sizeof(m_rp));
}


CRagEffect::~CRagEffect() // line 499-515
{
	if( m_primList.size() != 0 )
	{
		for( mystd::list<CEffectPrim*>::iterator it = m_primList.begin(); it != m_primList.end(); ++it )
			(*it)->SendMsg(NULL, 24, 0, 0, 0);

		m_primList.clear();
	}

	if( m_master != NULL )
		m_master->SendMsg(this, 23, 0, 0, 0);

	if( m_ezEffectRes != NULL )
		m_ezEffectRes->CRes::Unlock();
}


hook_func<bool (CRagEffect::*)()> CRagEffect::_OnProcess(SAKEXE, "CRagEffect::OnProcess");
bool CRagEffect::OnProcess() // line 518-1658
{
	return (this->*_OnProcess)();

	//TODO
}


hook_func<void (CRagEffect::*)(CGameObject* sender, int message, int arg1, int arg2, int arg3)> CRagEffect::_SendMsg(SAKEXE, "CRagEffect::SendMsg");
void CRagEffect::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3) // line 1661-1767
{
	return (this->*_SendMsg)(sender, message, arg1, arg2, arg3);

	//TODO
}


void CRagEffect::Render(matrix& wtm) // line 1770-1784
{
	if( m_aniClips == NULL )
		return;

	int rpCnt = 0;
	for( int i = 1; i < m_aniClips->cLayer; ++i )
	{
		if( m_isLayerDrawn[i] )
		{
			this->CRagEffect::RenderAniClip(m_aniClips->aLayer[i], &m_actXformData[i], rpCnt, wtm);
			rpCnt += 2;
		}
	}
}


hook_func<void (CRagEffect::*)(CRenderObject* master, int effectId, vector3d fDeltaPos)> CRagEffect::_Init(SAKEXE, "CRagEffect::Init");
void CRagEffect::Init(CRenderObject* master, int effectId, vector3d fDeltaPos) // line 1787-2247
{
	return (this->*_Init)(master, effectId, fDeltaPos);

	m_type = effectId;
	m_master = master;
	m_pos.x = master->m_pos.x;
	m_pos.y = master->m_pos.y;
	m_pos.z = master->m_pos.z;
	m_longitude = master->m_roty;
	m_duration = durationTable[m_type];
	m_deltaPos.x = fDeltaPos.x;
	m_deltaPos.y = fDeltaPos.y;
	m_deltaPos.z = fDeltaPos.z;

	char StrName[64];
	sprintf(StrName, "");

	switch( m_type )
	{
	case 0x173: sprintf(StrName, "angel.str"); break;
	case 0x174: sprintf(StrName, "devil.str"); break;
	case 0x29: sprintf(StrName, "Angelus.str"); break;
	case 0x40: sprintf(StrName, "ArrowShot.str"); break;
	case 0x41: sprintf(StrName, "Invenom.str"); break;
	case 0x42: sprintf(StrName, g_session.m_isMinEffect ? "cure_min.str" : "Cure.str"); break;
	case 0x43: sprintf(StrName, "Provoke.str"); break;
	case 0x44: sprintf(StrName, "Mvp.str"); break;
	case 0x45: sprintf(StrName, "SkidTrap.str"); break;
	case 0x4B: sprintf(StrName, g_session.m_isMinEffect ? "gloria_min.str" : "Gloria.str"); break;
	case 0x4C: sprintf(StrName, g_session.m_isMinEffect ? "magnificat_min.str" : "Magnificat.str"); break;
	case 0x4D: sprintf(StrName, g_session.m_isMinEffect ? "resurrection_min.str" : "Resurrection.str"); break;
	case 0x4E: sprintf(StrName, "Recovery.str"); break;
	case 0x53: sprintf(StrName, "Sanctuary.str"); break;
	case 0x54: sprintf(StrName, "Impositio.str"); break;
	case 0x55: sprintf(StrName, g_session.m_isMinEffect ? "lexaeterna_min.str" : "LexAeterna.str"); break;
	case 0x56: sprintf(StrName, "Aspersio.str"); break;
	case 0x57: sprintf(StrName, "LexDivina.str"); break;
	case 0x58: sprintf(StrName, g_session.m_isMinEffect ? "suffragium_min.str" : "Suffragium.str"); break;
	case 0x59: sprintf(StrName, "StormGust.str"); break;
	case 0x5A: sprintf(StrName, "Lord.str"); break;
	case 0x5B: sprintf(StrName, "Benedictio.str"); break;
	case 0x5C: sprintf(StrName, "Meteor%d.str", rand() % 3 + 1); break;
	case 0x5F: sprintf(StrName, "Quagmire.str"); break;
	case 0x60: sprintf(StrName, "FirePillar.str"); break;
	case 0x61: sprintf(StrName, "FirePillarBomb.str"); break;
	case 0x65: sprintf(StrName, "RepairWeapon.str"); break;
	case 0x66: sprintf(StrName, "CrashEarth.str"); break;
	case 0x67: sprintf(StrName, g_session.m_isMinEffect ? "WeaponPerfection_min.str" : "WeaponPerfection.str"); break;
	case 0x68: sprintf(StrName, g_session.m_isMinEffect ? "maximize_min.str" : "MaximizePower.str"); break;
	case 0x6A: sprintf(StrName, "BlastMine.str"); break;
	case 0x6B: sprintf(StrName, "Claymore.str"); break;
	case 0x6C: sprintf(StrName, "Freezing.str"); break;
	case 0x6F: sprintf(StrName, "Spring.str"); break;
	case 0x6D: sprintf(StrName, "Bubble%d.str", rand() % 4 + 1); break;
	case 0x6E: sprintf(StrName, "GasPush.str"); break;
	case 0x70: sprintf(StrName, g_session.m_isMinEffect ? "kyrie_min.str" : "Kyrie.str"); break;
	case 0x71: sprintf(StrName, "Magnus.str"); break;
	case 0x7C: sprintf(StrName, "VenomDust.str"); break;
	case 0x7E: sprintf(StrName, "PoisonReact_1st.str"); break;
	case 0x7F: sprintf(StrName, "PoisonReact.str"); break;
	case 0x83: sprintf(StrName, "AutoCounter.str"); break;
	case 0x81: sprintf(StrName, "VenomSplasher.str"); break;
	case 0x85: sprintf(StrName, "Freeze.str"); break;
	case 0x86: sprintf(StrName, "Freezed.str"); break;
	case 0x87: sprintf(StrName, "IceCrash.str"); break;
	case 0x8B: sprintf(StrName, "SandMan.str"); break;
	case 0x8D: sprintf(StrName, "Pneuma%d.str", rand() % 3 + 1); break;
	case 0x8F: sprintf(StrName, "SonicBlow.str"); break;
	case 0x46: sprintf(StrName, "Brandish.str"); break;
	case 0x90: sprintf(StrName, "Brandish2.str"); break;
	case 0x31: sprintf(StrName, "FireHit%d.str", rand() % 3 + 1); break;
	case 0x34: sprintf(StrName, "WindHit%d.str", rand() % 3 + 1); break;
	case 0x91: sprintf(StrName, "ShockWave.str"); break;
	case 0x92: sprintf(StrName, "ShockWaveHit.str"); break;
	case 0x93: sprintf(StrName, "EarthHit.str"); break;
	case 0x94: sprintf(StrName, "Pierce.str"); break;
	case 0x95: sprintf(StrName, "Bowling.str"); break;
	case 0x96: sprintf(StrName, "SpearStab.str"); break;
	case 0x97: sprintf(StrName, "SpearBoomerang.str"); break;
	case 0x98: sprintf(StrName, "HolyHit.str"); break;
	case 0x99: sprintf(StrName, "Concentration.str"); break;
	case 0x9A: sprintf(StrName, "bs_RefineSuccess.str"); break;
	case 0x9B: sprintf(StrName, "bs_RefineFailed.str"); break;
	case 0x131: sprintf(StrName, "p_success.str"); break;
	case 0x132: sprintf(StrName, "p_failed.str"); break;
	case 0x9C: sprintf(StrName, "JobChange.str"); break;
	case 0x9D: sprintf(StrName, "LevelUP.str"); break;
	case 0x9E: sprintf(StrName, "JobLvUP.str"); break;
	case 0x151: sprintf(StrName, "JobLvUP.str"); break;
	case 0x82: sprintf(StrName, "TwoHand.str"); break;
	case 0xFA: sprintf(StrName, "TwoHand.str"); break;
	case 0xA: sprintf(StrName, g_session.m_isMinEffect ? "memor_min.str" : "Maemor.str"); break;
	case 0x19: sprintf(StrName, "Firewall%d.str", rand() % 2 + 1); break;
	case 0xD: sprintf(StrName, "SafetyWall.str"); break;
	case 0x13B: sprintf(StrName, "SafetyWall.str"); break;
	case 0x1E: sprintf(StrName, "ThunderStorm.str"); break;
	case 0x1D: sprintf(StrName, "Lightning.str"); break;
	case 0x17: sprintf(StrName, "StoneCurse.str"); break;
	case 0x28: sprintf(StrName, "Cross.str"); break;
	case 0xA7: sprintf(StrName, "TamingSuccess.str"); break;
	case 0xA8: sprintf(StrName, "TamingFailed.str"); break;
	case 0xA9: sprintf(StrName, "EnergyCoat.str"); break;
	case 0xAA: sprintf(StrName, "CartRevolution.str"); break;
	case 0xB7: sprintf(StrName, "sui_explosion.str"); break;
	case 0xB5: sprintf(StrName, "MentalBreak.str"); break;
	case 0xB6: sprintf(StrName, "magical.str"); break;
	case 0xB9: sprintf(StrName, "suicide.str"); break;
	case 0xBA: sprintf(StrName, "yunta_1.str"); break;
	case 0xBB: sprintf(StrName, "yunta_2.str"); break;
	case 0xBC: sprintf(StrName, "yunta_3.str"); break;
	case 0xBD: sprintf(StrName, "yunta_4.str"); break;
	case 0xBE: sprintf(StrName, "yunta_5.str"); break;
	case 0xBF: sprintf(StrName, "homing.str"); break;
	case 0xC0: sprintf(StrName, "poison.str"); break;
	case 0xC1: sprintf(StrName, "silence.str"); break;
	case 0xC2: sprintf(StrName, "stun.str"); break;
	case 0xC5: sprintf(StrName, "sleep.str"); break;
	case 0xC3: sprintf(StrName, "StoneCurse.str"); break;
	case 0xC7: sprintf(StrName, "Pong%d.str", rand() % 3 + 1); break;
	case 0xCC: sprintf(StrName, "빨간포션.str"); break;
	case 0xCD: sprintf(StrName, "주홍포션.str"); break;
	case 0xCE: sprintf(StrName, "노란포션.str"); break;
	case 0xCF: sprintf(StrName, "하얀포션.str"); break;
	case 0xD0: sprintf(StrName, "파란포션.str"); break;
	case 0xD1: sprintf(StrName, "초록포션.str"); break;
	case 0xD2: sprintf(StrName, "fruit.str"); break;
	case 0xD3: sprintf(StrName, "fruit_.str"); break;
	case 0xD5: sprintf(StrName, "Deffender.str"); break;
	case 0xD6: sprintf(StrName, "Keeping.str"); break;
	case 0xDA: sprintf(StrName, "집중.str"); break;
	case 0xDB: sprintf(StrName, "각성.str"); break;
	case 0xDC: sprintf(StrName, "버서크.str"); break;
	case 0xEA: sprintf(StrName, "spell.str"); break;
	case 0xEB: sprintf(StrName, "디스펠.str"); break;
	case 0xF4: sprintf(StrName, "매직로드.str"); break;
	case 0xF5: sprintf(StrName, "holy_cross.str"); break;
	case 0x111: sprintf(StrName, "연환.str"); break;
	case 0x10C: sprintf(StrName, "steal_coin.str"); break;
	case 0x10D: sprintf(StrName, "strip_weapon.str"); break;
	case 0x10E: sprintf(StrName, "strip_shield.str"); break;
	case 0x10F: sprintf(StrName, "strip_armor.str"); break;
	case 0x110: sprintf(StrName, "strip_helm.str"); break;
	case 0xF6:  sprintf(StrName, "shield_charge.str"); break;
	case 0xFB:  sprintf(StrName, "devotion.str"); break;
	case 0xF8:  sprintf(StrName, "providence.str"); break;
	case 0xFF:  sprintf(StrName, "enc_fire.str"); break;
	case 0x100: sprintf(StrName, "enc_ice.str"); break;
	case 0x101: sprintf(StrName, "enc_wind.str"); break;
	case 0x102: sprintf(StrName, "enc_earth.str"); break;
	case 0x137: sprintf(StrName, "loud.str"); break;
	case 0x171: sprintf(StrName, "TwoHand.str"); break;
	default:
		break;
	}

	if( strlen(StrName) != 0 )
		this->CRagEffect::LoadEzEffect(StrName);
}


int CRagEffect::GetType()
{
	return m_type;
}


void CRagEffect::LoadEzEffect(char* fName) // line 2267-2282
{
	m_ezEffectRes = (CEZeffectRes*)g_resMgr().CResMgr::Get(fName);
	if( m_ezEffectRes == NULL )
		return; // not found.

	m_ezEffectRes->CRes::Lock();
	m_aniClips = &m_ezEffectRes->m_aniClips;
	m_cEndLayer = m_aniClips->cLayer;
	if( m_aniClips->aLayer[0].cAniKey == 0 )
		--m_cEndLayer;
}


hook_func<void (CRagEffect::*)(KAC_LAYER& pLayer, const KAC_XFORMDATA* pXformData, int rpCnt, matrix& wtm)> CRagEffect::_RenderAniClip(SAKEXE, "CRagEffect::RenderAniClip");
void CRagEffect::RenderAniClip(KAC_LAYER& pLayer, const KAC_XFORMDATA* pXformData, int rpCnt, matrix& wtm) // line 2450-2571
{
	return (this->*_RenderAniClip)(pLayer, pXformData, rpCnt, wtm);

	//TODO
}
