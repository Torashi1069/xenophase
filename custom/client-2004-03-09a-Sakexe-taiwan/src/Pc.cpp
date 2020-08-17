#include "GameMode.h"
#include "GameWorld.h"
#include "Globals.h"
#include "ModeMgr.h"
#include "MsgStrings.h"
#include "Pc.h"
#include "Player.h"
#include "Base/ResMgr.h"
#include "Framework/Locale.h"
#include "Resource/ImfRes.h"
#include "Resource/PaletteRes.h"
#include "Resource/Wave.h"
#include "Window/UIGage.h"


CPc::CPc(void) // line 22
{
	m_sprResList.resize(8);
	m_actResList.resize(8);
	m_gage = NULL;
	m_headPalette = 0;
	m_shield = 0;
	m_honor = 0;
	m_virtue = 0;
	m_gdid = 0;
	m_emblemVersion = 0;
	m_headDir = 0;
	m_shoe = 0;
	m_renderWithoutLayer = 0;
	m_pk_rank = 0;
	m_pk_total = 0;
	m_isPc = 1;
}


CPc::~CPc(void) // line 30
{
	for( int i = 0; i < 8; ++i )
	{
		if( m_sprResList[i] != NULL )
			m_sprResList[i]->CRes::Unlock();

		if( m_actResList[i] != NULL )
			m_actResList[i]->CRes::Unlock();
	}

	if( m_gage != NULL )
	{
		g_windowMgr.UIWindowMgr::PostQuit(m_gage);
		m_gage = NULL;
	}

}


hook_method<void (CPc::*)(void)> CPc::_OnInit(SAKEXE, "CPc::OnInit");
void CPc::OnInit(void) // line 41
{
	return (this->*_OnInit)();

	m_isPc = 1;
	m_gage = NULL;
	m_headPalette = 0;
	m_shield = 0;
	m_honor = 0;
	m_virtue = 0;
	m_gdid = 0;
	m_emblemVersion = 0;
	m_headDir = 0;
	m_shoe = 0;
	m_renderWithoutLayer = 0;
	m_pk_rank = 0;
	m_pk_total = 0;
}


hook_method<void (CPc::*)(void)> CPc::_OnExit(SAKEXE, "CPc::OnExit");
void CPc::OnExit(void) // line 57
{
	return (this->*_OnExit)();

	if( m_gage != NULL )
	{
		g_windowMgr.UIWindowMgr::PostQuit(m_gage);
		m_gage = NULL;
	}
}


hook_method<bool (CPc::*)(void)> CPc::_OnProcess(SAKEXE, "CPc::OnProcess");
bool CPc::OnProcess(void) // line 368
{
	return (this->*_OnProcess)();

	this->CGameActor::ProcessEffectState();
	this->CGameActor::ProcessWillBeAttacked();
	this->CGameActor::ProcessChatBalloon();

	if( m_gage != NULL )
		m_gage->Move(m_lastTlvertX - 30, m_lastTlvertY + int(m_lastPixelRatio * 12 * g_renderer->CRenderer::GetHeight() / 480));

	if( m_isSingleColor && timeGetTime() > m_singleColorStartTick + 100 )
	{
		m_colorOfSingleColor = 0xFFFF0000;
		m_isSingleColor = false;
	}

	if( m_sprArgb != -1 )
		this->CRenderObject::ModifyArgb(8, 8, 8, 8);

	bool ret = this->ProcessState();
	this->CRenderObject::ProcessSound();

	if( m_isPlayHitWave )
	{
		vector3d& pos = g_modeMgr.CModeMgr::GetGameMode()->CGameMode::GetWorld()->m_player->m_pos;
		PlayWave(m_hitWaveName, m_pos.x - pos.x, 0.0, m_pos.z - pos.z, 250, 40, 1.0);
		m_isPlayHitWave = 0;
	}

	return ret;
}


hook_method<bool (CPc::*)(void)> CPc::_ProcessState(SAKEXE, "CPc::ProcessState");
bool CPc::ProcessState(void) // line 399
{
	return (this->*_ProcessState)();

	//TODO
}


hook_method<void (CPc::*)(int stateId)> CPc::_SetState(SAKEXE, "CPc::SetState");
void CPc::SetState(int stateId) // line 462
{
	return (this->*_SetState)(stateId);

	if( m_stateId == STATEID_DEAD || m_isTrickDead )
		return;

	if( m_stateId == STATEID_FLINCH )
	{
		m_pos.x = m_damageDestX;
		m_pos.z = m_damageDestZ;
	}

	switch( stateId )
	{
	case STATEID_CAST:
		this->RegisterPos();
		this->SetAction(96, 6, 1);
		m_isMotionFinished = 1;
	break;
	case STATEID_SIT:
		this->RegisterPos();
		this->SetAction(16, 4, 1);
		m_isMotionFinished = 1;
		m_curMotion = m_headDir;
	break;
	case STATEID_WALK:
		m_isCounter = 0;
		if( m_bodyState != 1 && m_bodyState != 2 )
			m_isMotionFreezed = 0;
		m_headDir = 0;
		this->CGameActor::SetState(1);
	break;
	case STATEID_STAND:
		this->CGameActor::SetState(0);
		m_curMotion = m_headDir;
		if( m_stateId == STATEID_FLINCH || m_stateId == STATEID_ATTACK || m_pkState || m_stateId == STATEID_CAST )
			this->SetAction(32, 4, 0);
		g_modeMgr.CModeMgr::GetGameMode()->CGameMode::SetWaitUseItemAck(0);
	break;
	case STATEID_CASTEND:
	{
		if( m_stateId == STATEID_SIT )
			return;

		if( this->CGameActor::GetJob() == JT_BARD   || this->CGameActor::GetJob() == JT_DANCER   || this->CGameActor::GetJob() == JT_CRUSADER
		 || this->CGameActor::GetJob() == JT_BARD_H || this->CGameActor::GetJob() == JT_DANCER_H || this->CGameActor::GetJob() == JT_CRUSADER_H
		 || this->CGameActor::GetJob() == JT_BARD_B || this->CGameActor::GetJob() == JT_DANCER_B || this->CGameActor::GetJob() == JT_CRUSADER_B )
		{
			this->SetAction(32, 6, 1);
		}
		else
		if( this->CGameActor::GetJob() == JT_MONK || this->CGameActor::GetJob() == JT_MONK_H || this->CGameActor::GetJob() == JT_MONK_B )
		{
			if( m_sex )
			{
				this->SetAction(96, 6, 1);
				this->CRenderObject::SetForceAnimSpeed(4);
				this->CRenderObject::SetForceAnimation(96, 0, 0, 96, 0, 1, 0x190u, 0);
			}
			else
			{
				this->SetAction(32, 6, 1);
			}
		}
		else
		{
			this->SetAction(32, 6, 1);
		}

		m_attackMotion = 6.0;
	}
	break;
	case STATEID_ATTACK:
	{
		m_isCounter = 0;
		if( m_bodyState != 1 && m_bodyState != 2 )
			m_isMotionFreezed = 0;

		bool isSecond = g_session.CSession::IsSecondAttack(this->CGameActor::GetJob(), m_sex, m_weapon);
		int state = ( isSecond ) ? STATEID_MULTIATTACK : STATEID_ATTACK;
		this->CGameActor::SetState(state);
		m_attackMotion = g_session.CSession::GetPCAttackMotion(this->CGameActor::GetJob(), m_sex, m_weapon, isSecond);

		int wType = ( m_weapon <= WEAPONTYPE_LAST ) ? m_weapon : g_session.CSession::GetWeaponType(m_weapon);
		if( wType == WEAPONTYPE_BOW )
		{
			g_modeMgr.CModeMgr::GetGameMode()->CGameMode::MakeArrowEffect(m_pos, m_targetGid, m_attackMotion * m_motionSpeed, 0);
			m_attackMotion = 8.0f / m_motionSpeed + m_attackMotion;
		}
	}
	break;
	case STATEID_MULTIATTACK:
	{
		m_isCounter = 0;
		if( m_bodyState != 1 && m_bodyState != 2 )
			m_isMotionFreezed = 0;

		bool isSecond = g_session.CSession::IsSecondAttack(this->CGameActor::GetJob(), m_sex, m_weapon);
		int state = ( isSecond ) ? STATEID_MULTIATTACK : STATEID_ATTACK;
		this->CGameActor::SetState(state);
		m_attackMotion = g_session.CSession::GetPCAttackMotion(this->CGameActor::GetJob(), m_sex, m_weapon, isSecond);

		if( m_weapon == WEAPONTYPE_WHIP || m_weapon == WEAPONTYPE_INSTRUMENT )
		{
			g_modeMgr.CModeMgr::GetGameMode()->CGameMode::MakeArrowEffect(m_pos, m_targetGid, m_attackMotion * m_motionSpeed, 0);
			m_attackMotion = 8.0f / m_motionSpeed + m_attackMotion;
		}
	}
	break;
	default:
		this->CGameActor::SetState(stateId);
		return;
	}

	m_stateId = stateId;
	m_curAction = m_baseAction + this->Get8Dir(m_roty);
	m_stateStartTick = timeGetTime();
}


hook_method<void (CPc::*)(matrix& vtm)> CPc::_Render(SAKEXE, "CPc::Render");
void CPc::Render(matrix& vtm) // line 1025
{
	return (this->*_Render)(vtm);

	if( IsEffectStateFootPrint(m_effectState) )
		this->CPc::RenderShoe(1);

	if( !m_isVisible )
	{
		this->CRenderObject::UpdateTlvertex(vtm);
		return;
	}

	if( m_stateId != STATEID_SIT && m_stateId != STATEID_DEAD )
		this->CRenderObject::RenderShadow(vtm, m_zoom);

	if( !m_isVisibleBody )
	{
		this->CRenderObject::UpdateTlvertex(vtm);
		return;
	}

	if( IsEventAID(m_gid) )
	{
		this->CPc::RenderBody2(vtm, 0);
	}
	else
	if( m_renderWithoutLayer )
	{
		this->CRenderObject::RenderBody(vtm);
	}
	else
	{
		this->CPc::RenderBodyLayer(vtm, 0);
	}
}


void CPc::SetSprAct(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal) // line 262-299
{
	this->CGameActor::SetSex(sex);
	m_head = head;
	m_weapon = weapon;
	m_accessory2 = accessory2;
	m_accessory = accessory;
	m_accessory3 = accessory3;
	m_headPalette = headPal;
	m_shield = shield;
	m_bodyPalette = bodyPal;
	this->CGameActor::SetJob(job);
	this->CGameActor::SetJob(IsEffectStateMarried(m_effectState) ? JT_MARRIED : job);
	this->SetSprHead(m_head);
	this->SetSprWeapon(m_weapon);
	this->SetSprAccessory(m_accessory);
	this->SetSprAccessory2(m_accessory2);
	this->SetSprAccessory3(m_accessory3);
	this->SetSprShield(m_shield);
	this->SetImfFileName();
	this->SetHeadPaletteName();
	this->SetBodyPaletteName();
}


hook_method<void (CPc::*)(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal, int effectState)> CPc::_SetSprAct2(SAKEXE, "CPc::SetSprAct2");
void CPc::SetSprAct2(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal, int effectState) // line 302
{
	return (this->*_SetSprAct2)(job, sex, head, weapon, accessory, accessory2, accessory3, shield, headPal, bodyPal, effectState);

	this->CGameActor::SetSex(sex);

	m_head = head;
	m_accessory2 = accessory2;
	m_accessory3 = accessory3;
	m_weapon = weapon;
	m_accessory = accessory;

	int left = HIWORD(weapon);
	if( g_session.CSession::GetWeaponType(left) >= 0 )
		m_shield = 0;
	else
		m_shield = left;

	if( m_shield > 2000 )
		m_shield = g_session.CSession::GetShieldType(m_shield);

	m_headPalette = headPal;
	m_bodyPalette = bodyPal;

	if( IsEffectStateMarried(effectState) )
		this->CGameActor::SetJob(JT_MARRIED);
	else
		this->CGameActor::SetJob(job);

	this->SetSprHead(m_head);

	if( !IsEffectStateMarried(effectState) )
	{
		if( this->CGameActor::GetJob() == JT_ASSASSIN || this->CGameActor::GetJob() == JT_ASSASSIN_H || this->CGameActor::GetJob() == JT_ASSASSIN_B )
			this->SetSprWeapon2(weapon);
		else
			this->SetSprWeapon2((WORD)weapon);
	}

	this->SetSprAccessory(m_accessory);
	this->SetSprAccessory2(m_accessory2);
	this->SetSprAccessory3(m_accessory3);
	if( !IsEffectStateMarried(effectState) )
		this->SetSprShield(m_shield);
	this->SetImfFileName();
	this->SetHeadPaletteName();
	this->SetBodyPaletteName();
}


hook_method<void (CPc::*)(int job)> CPc::_SetSprJob(SAKEXE, "CPc::SetSprJob");
void CPc::SetSprJob(int job) // line 65
{
	return (this->*_SetSprJob)(job);

	//TODO
}


hook_method<void (CPc::*)(int head)> CPc::_SetSprHead(SAKEXE, "CPc::SetSprHead");
void CPc::SetSprHead(int head) // line 99
{
	return (this->*_SetSprHead)(head);

	//TODO
}


hook_method<void (CPc::*)(int job)> CPc::_SetSprJobDye(SAKEXE, "CPc::SetSprJobDye");
void CPc::SetSprJobDye(int job) // line 107
{
	return (this->*_SetSprJobDye)(job);

	//TODO
}


hook_method<void (CPc::*)(int weapon)> CPc::_SetSprWeapon(SAKEXE, "CPc::SetSprWeapon");
void CPc::SetSprWeapon(int weapon) // line 155-210
{
	return (this->*_SetSprWeapon)(weapon);

	m_weapon = weapon;

	if( g_session.CSession::IsProperWeapon(this->CGameActor::GetJob(), weapon) )
	{
		char tmpName[256];
		sprintf(tmpName, "인간족\\%s%s%s.act", g_session.m_pcJobNameTable[this->CGameActor::GetJob()], g_session.m_pcSexNameTable[m_sex], g_session.m_pcWeaponNameTable[m_weapon]);
		this->CPc::SetActNameList(5, tmpName);
		sprintf(tmpName, "인간족\\%s%s%s.spr", g_session.m_pcJobNameTable[this->CGameActor::GetJob()], g_session.m_pcSexNameTable[m_sex], g_session.m_pcWeaponNameTable[m_weapon]);
		this->CPc::SetSprNameList(5, tmpName);

		switch( m_weapon )
		{
		default:
			this->CPc::SetActNameList(6, "");
			this->CPc::SetSprNameList(6, "");
		break;
		case WEAPONTYPE_SHORTSWORD:
		case WEAPONTYPE_SWORD:
		case WEAPONTYPE_TWOHANDSWORD:
		case WEAPONTYPE_SPEAR:
		case WEAPONTYPE_TWOHANDSPEAR:
		case WEAPONTYPE_AXE:
		case WEAPONTYPE_TWOHANDAXE:
		case WEAPONTYPE_CATARRH:
		case WEAPONTYPE_SHORTSWORD_SHORTSWORD:
		case WEAPONTYPE_SWORD_SWORD:
		case WEAPONTYPE_AXE_AXE:
		case WEAPONTYPE_SHORTSWORD_SWORD:
		case WEAPONTYPE_SHORTSWORD_AXE:
		case WEAPONTYPE_SWORD_AXE:
			sprintf(tmpName, "인간족\\%s%s%s_검광.act", g_session.m_pcJobNameTable[this->CGameActor::GetJob()], g_session.m_pcSexNameTable[m_sex], g_session.m_pcWeaponNameTable[m_weapon]);
			this->CPc::SetActNameList(6, tmpName);
			sprintf(tmpName, "인간족\\%s%s%s_검광.spr", g_session.m_pcJobNameTable[this->CGameActor::GetJob()], g_session.m_pcSexNameTable[m_sex], g_session.m_pcWeaponNameTable[m_weapon]);
			this->CPc::SetSprNameList(6, tmpName);
		break;
		}
	}
	else
	{
		this->CPc::SetActNameList(5, "");
		this->CPc::SetSprNameList(5, "");
		this->CPc::SetActNameList(6, "");
		this->CPc::SetSprNameList(6, "");
	}
}


hook_method<void (CPc::*)(int weapon)> CPc::_SetSprWeapon2(SAKEXE, "CPc::SetSprWeapon2");
void CPc::SetSprWeapon2(int weapon) // line 2037-2247
{
	return (this->*_SetSprWeapon2)(weapon);

	//TODO
}


hook_method<void (CPc::*)(int accessory)> CPc::_SetSprAccessory(SAKEXE, "CPc::SetSprAccessory");
void CPc::SetSprAccessory(int accessory) // line 114
{
	return (this->*_SetSprAccessory)(accessory);

	//TODO
}


hook_method<void (CPc::*)(int accessory)> CPc::_SetSprAccessory2(SAKEXE, "CPc::SetSprAccessory2");
void CPc::SetSprAccessory2(int accessory) // line 127
{
	return (this->*_SetSprAccessory2)(accessory);

	//TODO
}


hook_method<void (CPc::*)(int accessory)> CPc::_SetSprAccessory3(SAKEXE, "CPc::SetSprAccessory3");
void CPc::SetSprAccessory3(int accessory) // line 141
{
	return (this->*_SetSprAccessory3)(accessory);

	//TODO
}


hook_method<void (CPc::*)(int shield)> CPc::_SetSprShield(SAKEXE, "CPc::SetSprShield");
void CPc::SetSprShield(int shield) // line 213
{
	return (this->*_SetSprShield)(shield);

	//TODO
}


hook_method<void (CPc::*)(int shoe)> CPc::_SetSprShoe(SAKEXE, "CPc::SetSprShoe");
void CPc::SetSprShoe(int shoe) // line 15543 (RagEffect2.cpp)
{
	return (this->*_SetSprShoe)(shoe);

	m_shoe = shoe;
}


hook_method<void (CPc::*)(void)> CPc::_SetImfFileName(SAKEXE, "CPc::SetImfFileName");
void CPc::SetImfFileName(void) // line 226
{
	return (this->*_SetImfFileName)();

	char tmpName[256];
	m_imfName = g_session.CSession::GetImfName(this->CGameActor::GetJob(), m_head, m_sex, tmpName);
}


hook_method<void (CPc::*)(void)> CPc::_SetHeadPaletteName(SAKEXE, "CPc::SetHeadPaletteName");
void CPc::SetHeadPaletteName(void) // line 232
{
	return (this->*_SetHeadPaletteName)();

	if( m_headPalette == 0 )
		return;

	char palName[64];
	m_headPaletteName = g_session.CSession::GetHeadPaletteName(m_head, this->CGameActor::GetJob(), m_sex, m_headPalette, palName);
}


hook_method<void (CPc::*)(void)> CPc::_SetBodyPaletteName(SAKEXE, "CPc::SetBodyPaletteName");
void CPc::SetBodyPaletteName(void) // line 240
{
	return (this->*_SetBodyPaletteName)();

	if( m_bodyPalette == 0 )
		return;

	char palName[64];
	m_bodyPaletteName = g_session.CSession::GetBodyPaletteName(this->CGameActor::GetJob(), m_sex, m_bodyPalette, palName);
}


hook_method<int (CPc::*)(void)> CPc::_GetWeapon(SAKEXE, "CPc::GetWeapon");
int CPc::GetWeapon(void) // line 743 (GameActor.h)
{
	return (this->*_GetWeapon)();

	//TODO
}


hook_method<void (CPc::*)(int attackM)> CPc::_SetModifyFactorOfmotionSpeed(SAKEXE, "CPc::SetModifyFactorOfmotionSpeed");
void CPc::SetModifyFactorOfmotionSpeed(int attackM) // line 606
{
	return (this->*_SetModifyFactorOfmotionSpeed)(attackM);

	//TODO
}


hook_method<void (CPc::*)(CGameObject* sender, int message, int arg1, int arg2, int arg3)> CPc::_SendMsg(SAKEXE, "CPc::SendMsg");
void CPc::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3) // line 638
{
	return (this->*_SendMsg)(sender, message, arg1, arg2, arg3);

	CGameMode* gameMode = g_modeMgr.CModeMgr::GetGameMode();

	switch( message )
	{
	case 100:
	{
		int curMotion = (int)arg1;

		if( m_stateId == STATEID_STAND || m_stateId == STATEID_SIT )
			m_curMotion = curMotion;
	}
	break;
	case 35:
	{
		if( m_gage != NULL )
		{
			g_windowMgr.UIWindowMgr::PostQuit(m_gage);
			m_gage = NULL;
		}
	}
	break;
	case 34:
	{
		int hp = (int)arg1;
		int maxhp = (int)arg2;

		if( m_gage == NULL )
		{
			m_gage = new UIPcGage();
			m_gage->UIWindow::Create(60, 5);
			g_windowMgr.UIWindowMgr::AddWindowFront(m_gage);
		}

		m_gage->UIPcGage::SetHp(hp, maxhp);
		m_gage->UIPcGage::SetSp(0, 0);
		m_gage->Move(m_lastTlvertX - 30, m_lastTlvertY + 12 * g_renderer->CRenderer::GetHeight() / 480);
	}
	break;
	case 3:
	{
		STANDENTRYSTRUCT* entry = (STANDENTRYSTRUCT*)arg1;

		gameMode->CGameMode::GetClientCoor(entry->x, entry->y, m_pos.x, m_pos.z);
		m_pos.y = gameMode->CGameMode::GetWorld()->m_attr->C3dAttr::GetHeight(m_pos.x, m_pos.z);
		m_roty = float(45 * (entry->dir + 4));
		m_xSize = entry->xSize;
		m_ySize = entry->ySize;
		m_moveDestX = entry->x;
		m_moveDestY = entry->y;
		m_headDir = entry->headDir;
		m_headType = entry->head;
		entry->job = this->CGameActor::GetProperJob(entry->job, entry->effectState);
		this->SetSprAct(entry->job, entry->sex, entry->head, entry->weapon, entry->accessory, entry->accessory2, entry->accessory3, entry->shield, entry->headpalette, entry->bodypalette);
		this->CGameActor::SetAttrState(entry->bodyState, entry->effectState, entry->healthState, 0);
		this->CGameActor::SetPKState(entry->isPKModeON);
		this->SetGuildInfo(entry->guildId, entry->guildEmblemVersion);
		this->SetPropensityInfo(entry->honor, entry->virtue);

		if( entry->state == PCSTATE_STAND )
			this->SetState(STATEID_STAND);
		else
		if( entry->state == PCSTATE_DEAD )
			this->SetState(STATEID_DEAD);
		else
		if( entry->state == PCSTATE_SIT )
			this->SetState(STATEID_SIT);
		else
		{
			this->SetState(STATEID_STAND);
		}
	}
	break;
	case 124:
	{
		STANDENTRYSTRUCT* entry = (STANDENTRYSTRUCT*)arg1;

		gameMode->CGameMode::GetClientCoor(entry->x, entry->y, m_pos.x, m_pos.z);
		m_pos.y = gameMode->CGameMode::GetWorld()->m_attr->C3dAttr::GetHeight(m_pos.x, m_pos.z);
		m_roty = float(45 * (entry->dir + 4));
		m_xSize = entry->xSize;
		m_ySize = entry->ySize;
		m_moveDestX = entry->x;
		m_moveDestY = entry->x;
		m_headDir = entry->headDir;
		m_headType = entry->head;
		entry->job = this->CGameActor::GetProperJob(entry->job, entry->effectState);
		this->SetSprAct2(entry->job, entry->sex, entry->head, entry->weapon, entry->accessory, entry->accessory2, entry->accessory3, entry->shield, entry->headpalette, entry->bodypalette, entry->effectState);
		this->CGameActor::SetAttrState(entry->bodyState, entry->effectState, entry->healthState, 0);
		this->CGameActor::SetPKState(entry->isPKModeON);
		this->SetGuildInfo(entry->guildId, entry->guildEmblemVersion);
		this->SetPropensityInfo(entry->honor, entry->virtue);

		if( entry->state == PCSTATE_STAND )
			this->SetState(STATEID_STAND);
		else
		if( entry->state == PCSTATE_DEAD )
			this->SetState(STATEID_DEAD);
		else
		if( entry->state == PCSTATE_SIT )
			this->SetState(STATEID_SIT);
		else
		{
			this->SetState(STATEID_STAND);
		}
	}
	break;
	case 105:
	{
		this->SetSprJob(this->CGameActor::GetJob());
		this->SetImfFileName();

		int weapon = this->GetWeapon();
		if( weapon > WEAPONTYPE_NONE && weapon < WEAPONTYPE_LAST )
			this->SetSprWeapon(weapon);
		else
			this->SetSprWeapon2(weapon);

		this->SetSprShield(m_shield);
		this->SetHeadPaletteName();
		this->SetBodyPaletteName();
	}
	break;
	case 106:
	{
		this->SetSprJob(this->CGameActor::GetJob());
		this->SetImfFileName();

		int weapon = this->GetWeapon();
		if( weapon > WEAPONTYPE_NONE && weapon < WEAPONTYPE_LAST )
			this->SetSprWeapon(weapon);
		else
			this->SetSprWeapon2(weapon);

		this->SetSprShield(m_shield);
		this->SetHeadPaletteName();
		this->SetBodyPaletteName();
	}
	break;
	case 4:
	{
		STANDENTRYSTRUCT* entry = (STANDENTRYSTRUCT*)arg1;
		int flag = (int)arg2;

		m_gid = entry->GID;
		gameMode->CGameMode::GetClientCoor(entry->x, entry->y, m_pos.x, m_pos.z);
		m_pos.y = gameMode->CGameMode::GetWorld()->m_attr->C3dAttr::GetHeight(m_pos.x, m_pos.z);
		m_roty = float(45 * (entry->dir + 4));
		m_speed = entry->speed;
		m_xSize = entry->xSize;
		m_ySize = entry->ySize;
		m_moveDestX = entry->x;
		m_moveDestY = entry->y;
		m_headDir = entry->headDir;
		m_headType = entry->head;
		entry->job = this->CGameActor::GetProperJob(entry->job, entry->effectState);
		this->SetSprAct(entry->job, entry->sex, entry->head, entry->weapon, entry->accessory, entry->accessory2, entry->accessory3, entry->shield, entry->headpalette, entry->bodypalette);
		this->CGameActor::SetAttrState(entry->bodyState, entry->effectState, entry->healthState, 0);
		this->CGameActor::SetPKState(entry->isPKModeON);
		this->SetGuildInfo(entry->guildId, entry->guildEmblemVersion);
		this->SetPropensityInfo(entry->honor, entry->virtue);

		if( entry->state == PCSTATE_STAND )
			this->SetState(STATEID_STAND);
		else
		if( entry->state == PCSTATE_DEAD )
			this->SetState(STATEID_DEAD);
		else
		if( entry->state == PCSTATE_SIT )
			this->SetState(STATEID_SIT);
		else
		{
			Trace("UNKNOWN PCSTATE");
			this->SetState(STATEID_STAND);
		}

		if( flag == 2 )
		{
			if( !IsEffectStateSpecialHiding(m_effectState) )
				this->CAbleToMakeEffect::LaunchEffect(EF_ENTRY2, vector3d(0.,0.,0.), 0.0);
		}

		this->CGameActor::MakePartyEffect(entry->GID);
	}
	break;
	case 121:
	{
		STANDENTRYSTRUCT* entry = (STANDENTRYSTRUCT*)arg1;
		int flag = (int)arg2;

		m_gid = entry->GID;
		gameMode->CGameMode::GetClientCoor(entry->x, entry->y, m_pos.x, m_pos.z);
		m_pos.y = gameMode->CGameMode::GetWorld()->m_attr->C3dAttr::GetHeight(m_pos.x, m_pos.z);
		m_roty = float(45 * (entry->dir + 4));
		m_speed = entry->speed;
		m_xSize = entry->xSize;
		m_ySize = entry->ySize;
		m_moveDestX = entry->x;
		m_moveDestY = entry->y;
		m_headDir = entry->headDir;
		m_headType = entry->head;
		entry->job = this->CGameActor::GetProperJob(entry->job, entry->effectState);
		this->SetSprAct2(entry->job, entry->sex, entry->head, entry->weapon, entry->accessory, entry->accessory2, entry->accessory3, entry->shield, entry->headpalette, entry->bodypalette, entry->effectState);
		this->CGameActor::SetAttrState(entry->bodyState, entry->effectState, entry->healthState, 0);
		this->CGameActor::SetPKState(entry->isPKModeON);
		this->SetGuildInfo(entry->guildId, entry->guildEmblemVersion);
		this->SetPropensityInfo(entry->honor, entry->virtue);

		if( entry->state == PCSTATE_STAND )
			this->SetState(STATEID_STAND);
		else
		if( entry->state == PCSTATE_DEAD )
			this->SetState(STATEID_DEAD);
		else
		if( entry->state == PCSTATE_SIT )
			this->SetState(STATEID_SIT);
		else
		{
			Trace("UNKNOWN PCSTATE");
			this->SetState(STATEID_STAND);
		}

		if( flag == 2 )
		{
			if( !IsEffectStateSpecialHiding(m_effectState) )
				this->CAbleToMakeEffect::LaunchEffect(344, vector3d(0.,0.,0.), 0.0);
		}

		this->CGameActor::MakePartyEffect(entry->GID);
	}
	break;
	case 6:
	{
		MOVEENTRYSTRUCT* entry = (MOVEENTRYSTRUCT*)arg1;

		m_gid = entry->GID;
		m_speed = entry->speed;
		m_moveStartTime = entry->moveStartTime;
		m_headDir = 0;
		entry->job = this->CGameActor::GetProperJob(entry->job, entry->effectState);
		this->SetSprAct(entry->job, entry->sex, entry->head, entry->weapon, entry->accessory, entry->accessory2, entry->accessory3, entry->shield, entry->headpalette, entry->bodypalette);
		this->CGameActor::SetAttrState(entry->bodyState, entry->effectState, entry->healthState, 0);
		this->CGameActor::SetPKState(entry->isPKModeON);
		this->SetGuildInfo(entry->guildId, entry->guildEmblemVersion);
		this->SetPropensityInfo(entry->honor, entry->virtue);

		gameMode->CGameMode::GetClientCoor(entry->sx, entry->sy, m_pos.x, m_pos.z);
		m_pos.x += gameMode->CGameMode::GetWorld()->m_attr->m_zoom / 16.f * (entry->cellX - 8);
		m_pos.z += gameMode->CGameMode::GetWorld()->m_attr->m_zoom / 16.f * (entry->cellY - 8);
		m_pos.y = gameMode->CGameMode::GetWorld()->m_attr->C3dAttr::GetHeight(m_pos.x, m_pos.z);

		if( this->CGameActor::FindPath(entry->sx, entry->sy, entry->cellX, entry->cellY, entry->dx, entry->dy, entry->speed) )
		{
			m_moveDestX = entry->dx;
			m_moveDestY = entry->dy;

			this->SetState(STATEID_WALK);
			m_pathStartCell = 0;
		}
		else
		{
			this->SetState(STATEID_STAND);
		}

		this->CGameActor::MakePartyEffect(entry->GID);
	}
	break;
	case 122:
	{
		MOVEENTRYSTRUCT* entry = (MOVEENTRYSTRUCT*)arg1;

		m_gid = entry->GID;
		m_speed = entry->speed;
		m_moveStartTime = entry->moveStartTime;
		m_headDir = 0;
		entry->job = this->CGameActor::GetProperJob(entry->job, entry->effectState);
		this->SetSprAct2(entry->job, entry->sex, entry->head, entry->weapon, entry->accessory, entry->accessory2, entry->accessory3, entry->shield, entry->headpalette, entry->bodypalette, entry->effectState);
		this->CGameActor::SetAttrState(entry->bodyState, entry->effectState, entry->healthState, 0);
		this->CGameActor::SetPKState(entry->isPKModeON);
		this->SetGuildInfo(entry->guildId, entry->guildEmblemVersion);
		this->SetPropensityInfo(entry->honor, entry->virtue);

		gameMode->CGameMode::GetClientCoor(entry->sx, entry->sy, m_pos.x, m_pos.z);
		m_pos.x += gameMode->CGameMode::GetWorld()->m_attr->m_zoom / 16.f * (entry->cellX - 8);
		m_pos.z += gameMode->CGameMode::GetWorld()->m_attr->m_zoom / 16.f * (entry->cellY - 8);
		m_pos.y = gameMode->CGameMode::GetWorld()->m_attr->C3dAttr::GetHeight(m_pos.x, m_pos.z);

		if( this->CGameActor::FindPath(entry->sx, entry->sy, entry->cellX, entry->cellY, entry->dx, entry->dy, entry->speed) )
		{
			m_moveDestX = entry->dx;
			m_moveDestY = entry->dy;

			this->SetState(STATEID_WALK);
			m_pathStartCell = 0;
		}
		else
		{
			this->SetState(STATEID_STAND);
		}

		this->CGameActor::MakePartyEffect(entry->GID);
	}
	break;
	case 5:
	{
		MOVEENTRYSTRUCT* entry = (MOVEENTRYSTRUCT*)arg1;

		m_gid = entry->GID;
		m_speed = entry->speed;
		m_moveStartTime = entry->moveStartTime;
		m_headDir = 0;
		entry->job = this->CGameActor::GetProperJob(entry->job, entry->effectState);
		this->SetSprAct(entry->job, entry->sex, entry->head, entry->weapon, entry->accessory, entry->accessory2, entry->accessory3, entry->shield, entry->headpalette, entry->bodypalette);
		this->CGameActor::SetAttrState(entry->bodyState, entry->effectState, entry->healthState, 0);
		this->CGameActor::SetPKState(entry->isPKModeON);
		this->SetGuildInfo(entry->guildId, entry->guildEmblemVersion);
		this->SetPropensityInfo(entry->honor, entry->virtue);
		if( this->CGameActor::FindPath(entry->sx, entry->sy, entry->cellX, entry->cellY, entry->dx, entry->dy, entry->speed) )
		{
			m_moveDestX = entry->dx;
			m_moveDestY = entry->dy;
			this->SetState(STATEID_WALK);
			m_pathStartCell = 0;
		}

		this->CGameActor::MakePartyEffect(entry->GID);
	}
	break;
	case 123:
	{
		MOVEENTRYSTRUCT* entry = (MOVEENTRYSTRUCT*)arg1;

		m_gid = entry->GID;
		m_speed = entry->speed;
		m_moveStartTime = entry->moveStartTime;
		m_headDir = 0;
		entry->job = this->CGameActor::GetProperJob(entry->job, entry->effectState);
		this->SetSprAct2(entry->job, entry->sex, entry->head, entry->weapon, entry->accessory, entry->accessory2, entry->accessory3, entry->shield, entry->headpalette, entry->bodypalette, entry->effectState);
		this->CGameActor::SetAttrState(entry->bodyState, entry->effectState, entry->healthState, 0);
		this->CGameActor::SetPKState(entry->isPKModeON);
		this->SetGuildInfo(entry->guildId, entry->guildEmblemVersion);
		this->SetPropensityInfo(entry->honor, entry->virtue);

		if( this->CGameActor::FindPath(entry->sx, entry->sy, entry->cellX, entry->cellY, entry->dx, entry->dy, entry->speed) )
		{
			m_moveDestX = entry->dx;
			m_moveDestY = entry->dy;
			this->SetState(STATEID_WALK);
			m_pathStartCell = 0;
		}

		this->CGameActor::MakePartyEffect(entry->GID);
	}
	break;
	case 114:
	{
		m_pk_rank = (int)arg2;
		m_pk_total = (int)arg1;
	}
	break;
	case 77:
	{
	}
	break;
	default:
	{
		this->CGameActor::SendMsg(sender, message, arg1, arg2, arg3);
	}
	break;
	};
}


hook_method<void (CPc::*)(int bodyPalette)> CPc::_SetBodyPalette(SAKEXE, "CPc::SetBodyPalette");
void CPc::SetBodyPalette(int bodyPalette) // line 248
{
	return (this->*_SetBodyPalette)(bodyPalette);

	//TODO
}


hook_method<void (CPc::*)(int headPalette)> CPc::_SetHeadPalette(SAKEXE, "CPc::SetHeadPalette");
void CPc::SetHeadPalette(int headPalette) // line 255
{
	return (this->*_SetHeadPalette)(headPalette);

    m_headPalette = headPalette;
    this->SetHeadPaletteName();
}


hook_method<void (CPc::*)(int honor)> CPc::_SetHonor(SAKEXE, "CPc::SetHonor");
void CPc::SetHonor(int honor) // line 521
{
	return (this->*_SetHonor)(honor);

	//TODO
}


hook_method<void (CPc::*)(int honor, int virtue)> CPc::_SetPropensityInfo(SAKEXE, "CPc::SetPropensityInfo");
void CPc::SetPropensityInfo(int honor, int virtue) // line 632
{
	return (this->*_SetPropensityInfo)(honor, virtue);

	//TODO
}


//hook_method<long (CPc::*)(void)> CPc::_GetPKRank(SAKEXE, "CPc::GetPKRank");
long CPc::GetPKRank(void) // line ???
{
//	return (this->*_GetPKRank)();

	return m_pk_rank;
}


//hook_method<long (CPc::*)(void)> CPc::_GetPKTotal(SAKEXE, "CPc::GetPKTotal");
long CPc::GetPKTotal(void) // line ???
{
//	return (this->*_GetPKTotal)();

	return m_pk_total;
}


//hook_method<void (CPc::*)(int rank)> CPc::_SetPKRank(SAKEXE, "CPc::SetPKRank");
void CPc::SetPKRank(int rank) // line ???
{
//	return (this->*_SetPKRank)(rank);

	m_pk_rank = rank;
}


//hook_method<void (CPc::*)(int total)> CPc::_SetPKTotal(SAKEXE, "CPc::SetPKTotal");
void CPc::SetPKTotal(int total) // line ???
{
//	return (this->*_SetPKTotal)(total);

	m_pk_total = total;
}


hook_method<void (CPc::*)(matrix& vtm, int isBlur)> CPc::_RenderBody2(SAKEXE, "CPc::RenderBody2");
void CPc::RenderBody2(matrix& vtm, int isBlur) // line 1726
{
	return (this->*_RenderBody2)(vtm, isBlur);

	//TODO
}


hook_method<void (CPc::*)(matrix& vtm, int isBlur)> CPc::_RenderBodyLayer(SAKEXE, "CPc::RenderBodyLayer");
void CPc::RenderBodyLayer(matrix& vtm, int isBlur) // line 1350-1723
{
	return (this->*_RenderBodyLayer)(vtm, isBlur);
	
	vector3d tv;
	tv.z = m_pos.x * vtm.v13 + m_pos.y * vtm.v23 + m_pos.z * vtm.v33 + vtm.v43;

	float x, y, oow;
	g_renderer->CRenderer::ProjectVertex(m_pos, vtm, &x, &y, &oow);

	float pixelRatio = g_renderer->CRenderer::GetPixelRatio(oow);
	m_lastPixelRatio = pixelRatio / g_avgPixelRatio;

	float fSprShift = g_renderer->CRenderer::GetScreenXFactor() * m_sprShift * m_lastPixelRatio * m_zoom;
	float zHover = g_zHover * m_lastPixelRatio;

	float lmRIntensity = 1.0f;
	float lmGIntensity = 1.0f;
	float lmBIntensity = 1.0f;
	this->CRenderObject::SetLmIntensity(lmRIntensity, lmGIntensity, lmBIntensity);

	float m_fA = m_sprColor.a * (1/255.0f);
	float m_fR = m_sprColor.r * (1/255.0f) * lmRIntensity;
	float m_fG = m_sprColor.g * (1/255.0f) * lmGIntensity;
	float m_fB = m_sprColor.b * (1/255.0f) * lmBIntensity;

	RENDER_INFO_RECT info;
	info.left = (float)g_renderer->CRenderer::GetWidth();
	info.top = (float)g_renderer->CRenderer::GetHeight();
	info.right = 0;
	info.bottom = 0;
	info.oow = oow;

	CImfRes* imfRes = (CImfRes*)g_resMgr().CResMgr::Get(m_imfName.c_str());
	int bodyAndAccessoryIsExchanged = 0;
	bool headLayerPassed = false;
	bool isInsideScreen = false;
	int drawCount = 0;

	for( int p = 7; p >= 0; --p )
	{
		int subAction = m_curAction - m_baseAction; // direction of sprite: 0=S 1=SW 2=W 3=NW 4=N 5=NE 6=E 7=SE
		int layer; // 0=body(job) 1=head 2=accessory 3=accessory2 4=accessory3 5=weapon 6=weapon2 7=shield

		if( subAction < 2 || subAction > 5 ) // SW,S,SE,E layer=imf(0,1),{2,3,4,5,6,7}
		{
			if( p >= 6 && p <= 7 ) // {6,7} => {0,1} => imf
				layer = imfRes->CImfRes::GetLayer(p - 6, m_curAction, m_curMotion);
			else// {0,1,2,3,4,5} => {7,6,5,4,3,2}
				layer = 7 - p;
		}
		else // W,NW,N,NE layer={7},imf(0,1){2,3,4,5,6}
		{
			if( p == 7 ) // {7} => {7}
				layer = p;
			else if( p >= 5 && p <= 6 ) // {5,6} => {0,1} => imf
				layer = imfRes->CImfRes::GetLayer(p - 5, m_curAction, m_curMotion);
			else // {0,1,2,3,4} => {6,5,4,3,2}
				layer = 6 - p;
		}

		int oldLayer = layer;

		if( !headLayerPassed && layer == 1 )
			headLayerPassed = true;

		if( headLayerPassed && layer == 0 )
		{
			layer = 2;
			++bodyAndAccessoryIsExchanged;
		}

		if( bodyAndAccessoryIsExchanged == 1 && oldLayer == 2 )
		{
			bodyAndAccessoryIsExchanged = 2;
			layer = 0;
		}
		else if( layer < 0 || layer > 7 )
			layer = 0;
		else if( layer == 2 )
			layer = 4;
		else if( layer == 4 )
			layer = 2;

		CActRes* actRes = m_actResList[layer];
		CSprRes* sprRes = m_sprResList[layer];

		const char* actResName = ( actRes != NULL ) ? actRes->CRes::GetName() : "";
		const char* sprResName = ( sprRes != NULL ) ? sprRes->CRes::GetName() : "";
		if( strlen(actResName) == 0 || strlen(sprResName) == 0 )
			continue;

		if( !( // not
			(m_curAction >= 32 && m_curAction <= 39) || // standing
			(m_curAction >= 80 && m_curAction <= 95) || // hitting slowest(?)
			layer < 5 ) ) // body, head, accessory, accessory2, accessory3
			continue;

		if( layer == 1 && IsEffectStateOrcFace(m_effectState) )
		{
			actRes = (CActRes*)g_resMgr().Get("이팩트\\orcface.act");
			sprRes = (CSprRes*)g_resMgr().Get("이팩트\\orcface.spr");
		}

		unsigned int clipId = 0;
		if( layer == 1 )
			clipId = 1;

		if( m_curMotion >= actRes->CActRes::GetMotionCount(m_curAction) )
			continue;

		CMotion* mot = actRes->CActRes::GetMotion(m_curAction, m_curMotion);
		if( layer == 6 && mot->m_eventId != -1 )
		{
			mystd::string eventName = actRes->CActRes::GetEventName(mot->m_eventId);
			if( eventName.find_first_of(".wav") != eventName.npos )
				strcpy(m_hitWaveName, eventName.c_str());

			m_isPlayHitWave = 1;
		}

		CSprClip* sprClip = mot->CMotion::GetClip(clipId);
		if( sprClip->sprIndex == -1 )
			continue;

		unsigned int argb = ((((((
			int(sprClip->a * (1/255.0f) * m_fA * 255.0f)) << 8) +
			int(sprClip->r * (1/255.0f) * m_fR * 255.0f)) << 8) +
			int(sprClip->g * (1/255.0f) * m_fG * 255.0f)) << 8) +
			int(sprClip->b * (1/255.0f) * m_fB * 255.0f);

		float zoomX = m_zoom;
		float zoomY = m_zoom;
		SprImg* sprImg = sprRes->m_sprites[sprClip->clipType][sprClip->sprIndex];

		static int head_imfOffX = 0; // WARNING static variable unique to this function
		static int head_imfOffY = 0; // WARNING static variable unique to this function
		int imfOffX = 0;
		int imfOffY = 0;

		switch( layer )
		{
		case 0: // body layer
		break;
		case 1: // head layer
		{
			CMotion* bodyMotion = m_actResList[0]->CActRes::GetMotion(m_curAction, m_curMotion);
			if( mot->attachCnt != 0 && bodyMotion->attachCnt != 0 && mot->attachInfo[0].m_attr == bodyMotion->attachInfo[0].m_attr )
			{
				imfOffX = bodyMotion->attachInfo[0].x - mot->attachInfo[0].x;
				imfOffY = bodyMotion->attachInfo[0].y - mot->attachInfo[0].y;

				head_imfOffX = imfOffX;
				head_imfOffY = imfOffY;
			}
		}
		break;
		case 2: // accessory layer
		case 3: // accessory2 layer
		case 4: // accessory3 layer
		{
			CMotion* headMotion = m_actResList[1]->CActRes::GetMotion(m_curAction, m_curMotion);
			if( mot->attachCnt != 0 && headMotion->attachCnt != 0 && mot->attachInfo[0].m_attr == headMotion->attachInfo[0].m_attr )
			{
				imfOffX = headMotion->attachInfo[0].x - mot->attachInfo[0].x;
				imfOffY = headMotion->attachInfo[0].y - mot->attachInfo[0].y;
			}

			imfOffX += head_imfOffX;
			imfOffY += head_imfOffY;
		}
		break;
		default:
		break;
		}

		float top = (imfOffY + sprClip->y) * sprClip->zoomy * zoomY * pixelRatio + y;
		float btm = (imfOffY + sprClip->y + sprImg->height * (sprImg->isHalfH + 1)) * sprClip->zoomy * zoomY * pixelRatio + y + 1.0f;
		float left, right;

		if( sprClip->flags & 1 ) // mirror X
		{
			left = (imfOffX + sprClip->x + sprImg->width * (sprImg->isHalfW + 1)) * zoomX * pixelRatio * sprClip->zoomx + x;
			right = (imfOffX + sprClip->x) * zoomX * pixelRatio * sprClip->zoomx + x + 1.0f;

			if( g_renderer->CRenderer::GetHeight() <= top || btm <= 0.0f || g_renderer->CRenderer::GetWidth() <= right || left <= 0.0f )
				continue;
		}
		else
		{
			left = (imfOffX + sprClip->x) * zoomX * pixelRatio * sprClip->zoomx + x;
			right = (imfOffX + sprClip->x + sprImg->width * (sprImg->isHalfW + 1)) * zoomX * pixelRatio * sprClip->zoomx + x + 1.0f;

			if( g_renderer->CRenderer::GetHeight() <= top || btm <= 0.0f || g_renderer->CRenderer::GetWidth() <= left || right <= 0.0f )
				continue;
		}

		isInsideScreen = true;

		float sprOow, sprOowup;
		if( m_alwaysTopLayer )
		{
			sprOow = p * g_zOffset + 1.0f / 10.0f - g_zOffset * 20.0f + m_offsetOow * g_zOffset;
			sprOowup = sprOow;
		}
		else
		if( m_isLieOnGround )
		{
			sprOow = 1.0f / (tv.z - (btm - y) * g_shadowSlope) + (m_offsetOow + drawCount + 3) * g_zOffset + zHover;
			sprOowup = (m_offsetOow + drawCount + 3) * g_zOffset + 1.0f / (tv.z - (top - y) * g_shadowSlope) + zHover;
		}
		else
		{
			sprOow = 1.0f / ((btm - y) * g_slope + tv.z) + (m_offsetOow + drawCount + 3) * g_zOffset + zHover;
			sprOowup = (m_offsetOow + drawCount + 3) * g_zOffset + 1.0f / ((top - y) * g_slope + tv.z) + zHover;
		}

		++drawCount;

		if( m_isSingleColor && m_colorOfSingleColor != 0xFFFF0000 )
			argb = m_colorOfSingleColor;

		left += fSprShift;
		right += fSprShift;

		RPSprite spr; //NOTE: some fields uninitialized
		spr.spr = sprImg;
		spr.top = top;
		spr.bottom = btm;
		spr.left = left;
		spr.right = right;
		spr.rgba = argb;
		spr.oow  = sprOow;
		spr.oowup = sprOowup;
		spr.angle = static_cast<float>(m_sprAngle + sprClip->angle);

		if( (layer == 0 || layer == 1) && m_shouldAddPickInfo )
			info.RENDER_INFO_RECT::Update(spr);

		unsigned long* palette = sprRes->m_pal;
		if( layer == 0 && m_bodyPalette != 0 )
			palette = static_cast<CPaletteRes*>(g_resMgr().Get(m_bodyPaletteName.c_str()))->m_pal;
		else
		if( layer == 1 && m_headPalette != 0 )
			palette = static_cast<CPaletteRes*>(g_resMgr().Get(m_headPaletteName.c_str()))->m_pal;

		int effectId = 166;
		this->SendMsg(NULL, 120, (int)&effectId, 0, 0); // sets effectId to -1 if any CRagEffect.m_type is 166

		int renderFlag = 0x101;
		if( layer < 2 || layer > 4 )
		{
			if( argb < 0xFF000000 )
				renderFlag = 0x101;
		}
		else
		{
			renderFlag = 0x1;
		}

		if( (m_BodyLight & 1) == 1 && layer <= 4 )
			renderFlag = 0x5;
		if( (m_BodyLight & 2) == 2 && layer == 5 )
			renderFlag = 0x5;
		if( (m_BodyLight & 4) == 4 && layer == 5 )
		{
			if( m_BodyFlag )
			{
				m_BodyFlag = 0;
			}
			else
			{
				this->CRenderObject::RenderSprite(spr, palette, 5);
				m_BodyFlag = 1;
			}
		}
		if( (m_BodyLight & 8) == 8 && layer <= 4 )
		{
			++m_BodySin;
			if( m_BodySin > 180 )
				m_BodySin = 0;

			float sinValue = g_sinTable[m_BodySin] * 1.5f + 5.0f;

			RPSprite spr2; //NOTE: some fields uninitialized
			spr2.top = top - sinValue;
			spr2.bottom = btm + sinValue;
			if( left <= right )
			{
				spr2.left = left - sinValue;
				spr2.right = right + sinValue;
			}
			else
			{
				spr2.left = left + sinValue;
				spr2.right = right - sinValue;
			}
			spr2.oowup = sprOowup;
			spr2.spr = sprImg;
			spr2.oow = sprOow - 0.00005f;
			spr2.rgba = argb;
			spr2.angle = static_cast<float>(sprClip->angle + m_sprAngle);
			this->CRenderObject::RenderSprite(spr2, palette, 5);
		}

		this->CRenderObject::RenderSprite(spr, palette, renderFlag);
	}

	if( isInsideScreen )
		this->SetRenderInfo(info, x, y);
	else
		this->SetTlvert(x, y);
}


hook_method<void (CPc::*)(matrix& vtm)> CPc::_RenderShadowLayer(SAKEXE, "CPc::RenderShadowLayer");
void CPc::RenderShadowLayer(matrix& vtm) // line 1111
{
	return (this->*_RenderShadowLayer)(vtm);
	
	vector3d tv;
	tv.z = m_pos.x * vtm.v13 + m_pos.y * vtm.v23 + m_pos.z * vtm.v33 + vtm.v43;
	float x, y, oow;
	g_renderer->CRenderer::ProjectVertex(m_pos, vtm, &x, &y, &oow);
	float pixelRatio = g_renderer->CRenderer::GetPixelRatio(oow);
	m_lastPixelRatio = pixelRatio / g_avgPixelRatio;

	float lmRIntensity = 1.0f;
	float lmGIntensity = 1.0f;
	float lmBIntensity = 1.0f;
	float fSprShift = g_renderer->CRenderer::GetScreenXFactor() * m_sprShift * m_lastPixelRatio * m_zoom;
	float zHover = g_zHover * m_lastPixelRatio;
	this->CRenderObject::SetLmIntensity(lmRIntensity, lmGIntensity, lmBIntensity);

	RENDER_INFO_RECT info;
	info.left = (float)g_renderer->CRenderer::GetWidth();
	info.right = 0;
	info.top = (float)g_renderer->CRenderer::GetHeight();
	info.bottom = 0;
	info.oow = oow;

	CImfRes* imfRes = (CImfRes*)g_resMgr().CResMgr::Get(m_imfName.c_str());
	int bodyAndAccessoryIsExchanged = 0;
	bool headLayerPassed = false;
	bool isInsideScreen = false;
	int drawCount = 0;
	int priority = 7;
	do {
		int subAction = m_curAction - m_baseAction; // direction of sprite: 0=S 1=SW 2=W 3=NW 4=N 5=NE 6=E 7=SE
		int layerId; // 0=body(job) 1=head 2=accessory 3=accessory2 4=accessory3 5=weapon 6=weapon2 7=shield
		if( subAction < 2 || subAction > 5 ) // SW,S,SE,E
		{
			if( priority >= 6 && priority <= 7 ) // {6,7} => {0,1} => imf
				layerId = imfRes->CImfRes::GetLayer(priority - 6, m_curAction, m_curMotion);
			else// {0,1,2,3,4,5} => {7,6,5,4,3,2}
				layerId = 7 - priority;
		}
		else // W,NW,N,NE
		{
			if( priority >= 5 && priority <= 6 ) // {5,6} => {0,1} => imf
				layerId = imfRes->CImfRes::GetLayer(priority - 5, m_curAction, m_curMotion);
			else if( priority != 7 ) // {0,1,2,3,4} => {6,5,4,3,2}
				layerId = 6 - priority;
			else // {7} => {7}
				layerId = priority;
		}
		if( !headLayerPassed && layerId == 1 ) // TODO compare again, logic was confusing so mistakes are likely {START}
			headLayerPassed;
		int oldLayerId = layerId;
		if( headLayerPassed && layerId == 0 )
		{
			layerId = 2;
			++bodyAndAccessoryIsExchanged;
		}
		if( bodyAndAccessoryIsExchanged == 1 && oldLayerId == 2 )
		{
			bodyAndAccessoryIsExchanged = 2;
			layerId = 0;
		}
		else if( layerId < 0 || layerId > 7 )
			layerId = 0;
		else if( layerId == 2 )
			layerId = 4;
		else if( layerId == 4 )
			layerId = 2; // TODO compare again, logic was confusing so mistakes are likely {END}
		CActRes* actRes = m_actResList[layerId];
		if( actRes == NULL || strlen(actRes->CRes::GetName()) == 0 )
			continue;
		CSprRes* sprRes = m_sprResList[layerId];
		if( sprRes == NULL || strlen(sprRes->CRes::GetName()) == 0 )
			continue;
		if( !( // not
			(m_curAction >= 32 && m_curAction <= 39) || // standing
			(m_curAction >= 80 && m_curAction <= 95) || // hitting slowest(?)
			layerId < 5 ) ) // body, head, accessory, accessory2, accessory3
			continue;
		unsigned int clipId = 0;
		if( layerId == 1 ) 
			clipId = 1;
		if( m_curMotion >= actRes->CActRes::GetMotionCount(m_curAction) )
			continue;
		CMotion* motion = actRes->CActRes::GetMotion(m_curAction, m_curMotion);
		CSprClip* sprClip = motion->CMotion::GetClip(clipId);
		if( sprClip->sprIndex == -1 )
			continue;
		unsigned int argb = 0xFF0101FF;
		float zoomX = m_zoom;
		float zoomY = m_zoom;
		SprImg* sprImg = sprRes->m_sprites[sprClip->clipType][sprClip->sprIndex];
		static int headLayerImfOffX; // WARNING static variable unique to this function
		static int headLayerImfOffY; // WARNING static variable unique to this function
		int imfOffX = 0;
		int imfOffY = 0;
		switch( layerId )
		{
		case 0: // body layer
		break;
		case 1: // head layer
		{
			CMotion* bodyMotion = m_actResList[0]->CActRes::GetMotion(m_curAction, m_curMotion);
			if( motion->attachCnt == 0 || bodyMotion->attachCnt == 0 )
				break;
			CAttachPointInfo* bodyAttachInfo = &bodyMotion->attachInfo[0];
			CAttachPointInfo* attachInfo = &motion->attachInfo[0];
			if( attachInfo->m_attr == bodyAttachInfo->m_attr )
			{
				headLayerImfOffX = imfOffX = bodyAttachInfo->x - attachInfo->x;
				headLayerImfOffY = imfOffY = bodyAttachInfo->y - attachInfo->y;
			}
		}
		break;
		case 2: // accessory layer
		case 3: // accessory2 layer
		case 4: // accessory3 layer
			CMotion* headMotion = m_actResList[1]->CActRes::GetMotion(m_curAction, m_curMotion);
			CAttachPointInfo* headAttachInfo = &headMotion->attachInfo[0];
			CAttachPointInfo* attachInfo = &motion->attachInfo[0];
			imfOffX = headLayerImfOffX;
			imfOffY = headLayerImfOffY;
			if( attachInfo->m_attr == headAttachInfo->m_attr )
			{
				imfOffX += headAttachInfo->x - attachInfo->x;
				imfOffY += headAttachInfo->y - attachInfo->y;
			}
		break;
		}
		float top = (sprClip->y + imfOffY - 5) * zoomY * pixelRatio * sprClip->zoomy + y; // TODO compare again {START}
		float bottom = (sprClip->y + sprImg->height * (sprImg->isHalfH + 1) + imfOffY + 5) * zoomY * pixelRatio * sprClip->zoomy + y + 1.0f;
		float left, right;
		if( sprClip->flags & 1 ) // mirror X
		{
			left = (sprClip->x + sprImg->width * (sprImg->isHalfW + 1) + imfOffX - 5) * zoomX * pixelRatio * sprClip->zoomx + x;
			right = (sprClip->x + imfOffX + 5) * zoomX * pixelRatio * sprClip->zoomx + x + 1.0f;
			if( !(g_renderer->CRenderer::GetHeight() > top && bottom > 0.0f && g_renderer->CRenderer::GetWidth() > right && left > 0.0f) )
				continue;
		}
		else
		{
			left = (sprClip->x + imfOffX - 5) * zoomX * pixelRatio * sprClip->zoomx + x;
			right = (sprClip->x + sprImg->width * (sprImg->isHalfW + 1) + imfOffX + 5) * zoomX * pixelRatio * sprClip->zoomx + x + 1.0f;
			if( !(g_renderer->CRenderer::GetHeight() > top && bottom > 0.0f && g_renderer->CRenderer::GetWidth() > left && right > 0.0f) )
				continue;
		}
		isInsideScreen = true;
		float oowup;
		if( m_alwaysTopLayer )
			oow = oowup = priority * g_zOffset + 1.0f / 10.0f - g_zOffset * 20.0f + m_offsetOow * g_zOffset;
		else if( m_isLieOnGround )
		{
			oow = 1.0f / (tv.z - (bottom - y) * g_shadowSlope) + (drawCount + m_offsetOow) * g_zOffset + zHover;
			oowup = 1.0f / (tv.z - (top - y) * g_shadowSlope) + (drawCount + m_offsetOow) * g_zOffset + zHover;
		}
		else
		{
			oow = 1.0f / ((bottom - y) * g_slope + tv.z + 0.1f) + (drawCount + m_offsetOow) * g_zOffset + zHover;
			oowup = 1.0f / ((top - y) * g_slope + tv.z + 0.1f) + (drawCount + m_offsetOow) * g_zOffset + zHover;
		} // TODO compare again {END}
		++drawCount;
		RPSprite spr;
		spr.spr = sprImg;
		spr.top = top;
		spr.bottom = bottom;
		spr.left = left;
		spr.right = right;
		spr.rgba = (m_isSingleColor && m_colorOfSingleColor != 0xFFFF0000)? m_colorOfSingleColor: argb;
		spr.oow  = oow;
		spr.oowup = oowup;
		spr.angle = (float)(m_sprAngle + sprClip->angle);
		unsigned long* pal = sprRes->m_pal;
		if( layerId == 0 )
		{
			if( m_shouldAddPickInfo )
				info.RENDER_INFO_RECT::Update(spr);
			if( m_bodyPalette )
				pal = ((CPaletteRes*)(g_resMgr().CResMgr::Get(m_bodyPaletteName.c_str())))->m_pal;
		}
		if( layerId == 1 )
		{
			if( m_shouldAddPickInfo )
				info.RENDER_INFO_RECT::Update(spr);
			if( m_headPalette )
				pal = ((CPaletteRes*)(g_resMgr().CResMgr::Get(m_headPaletteName.c_str())))->m_pal;
		}
		this->CRenderObject::RenderSprite(spr, pal, 0x101);
	} while( --priority >= 0 );
	if( isInsideScreen )
		this->SetRenderInfo(info, x, y);
	else
		this->SetTlvert(x, y);
}


hook_method<void (CPc::*)(void)> CPc::_ProcessGage(SAKEXE, "CPc::ProcessGage");
void CPc::ProcessGage(void) // line 598
{
	return (this->*_ProcessGage)();

	if( m_gage != NULL )
		m_gage->Move(m_lastTlvertX - 30, static_cast<int>(m_lastTlvertY + (12 * g_renderer->CRenderer::GetHeight() / 480) * m_lastPixelRatio));
}


hook_method<void (CPc::*)(int Total, int Rank)> CPc::_SetRank(SAKEXE, "CPc::SetRank");
void CPc::SetRank(int Total, int Rank) // line 1022
{
	return (this->*_SetRank)(Total, Rank);

	;
}


hook_method<const mystd::vector<mystd::string> (CPc::*)(void)> CPc::_GetSprNames(SAKEXE, "CPc::GetSprNames");
const mystd::vector<mystd::string> CPc::GetSprNames(void) // line 1883
{
	return (this->*_GetSprNames)();

	//TODO
}


hook_method<void (CPc::*)(const mystd::vector<mystd::string>& sprNames)> CPc::_SetSprNames(SAKEXE, "CPc::SetSprNames");
void CPc::SetSprNames(const mystd::vector<mystd::string>& sprNames) // line 1878
{
	return (this->*_SetSprNames)(sprNames);

	for( int i = 0; i < 8; ++i )
		this->CPc::SetSprNameList(i, sprNames[i].c_str());
}


hook_method<const mystd::vector<mystd::string> (CPc::*)(void)> CPc::_GetActNames(SAKEXE, "CPc::GetActNames");
const mystd::vector<mystd::string> CPc::GetActNames(void) // line 1899
{
	return (this->*_GetActNames)();

	//TODO
}


hook_method<void (CPc::*)(const mystd::vector<mystd::string>& actNames)> CPc::_SetActNames(SAKEXE, "CPc::SetActNames");
void CPc::SetActNames(const mystd::vector<mystd::string>& actNames) // line 1894
{
	return (this->*_SetActNames)(actNames);

	for( int i = 0; i < 8; ++i )
		this->CPc::SetActNameList(i, actNames[i].c_str());
}


//hook_method<const mystd::string& (CPc::*)(void)> CPc::_GetImfNames(SAKEXE, "CPc::GetImfNames");
const mystd::string& CPc::GetImfNames(void) // line ???
{
//	return (this->*_GetImfNames)();

	return m_imfName;
}


//hook_method<int (CPc::*)(void)> CPc::_GetHeadPalette(SAKEXE, "CPc::GetHeadPalette");
int CPc::GetHeadPalette(void) // line ???
{
//	return (this->*_GetHeadPalette)();

	return m_headPalette;
}


hook_method<mystd::string (CPc::*)(void)> CPc::_GetHeadPaletteName(SAKEXE, "CPc::GetHeadPaletteName");
mystd::string CPc::GetHeadPaletteName(void) // line 770 (GameActor.h)
{
	return (this->*_GetHeadPaletteName)();

	return m_headPaletteName; //inlined
}


hook_method<void (CPc::*)(int shoenum)> CPc::_RenderShoe(SAKEXE, "CPc::RenderShoe");
void CPc::RenderShoe(int shoenum) // line 15464 (RagEffect2.cpp)
{
	return (this->*_RenderShoe)(shoenum);

	//TODO
}


hook_method<void (CPc::*)(int layer, const char* sprName)> CPc::_SetSprNameList(SAKEXE, "CPc::SetSprNameList");
void CPc::SetSprNameList(int layer, const char* sprName) // line 1910
{
	return (this->*_SetSprNameList)(layer, sprName);

	if( m_sprResList[layer] != NULL )
		m_sprResList[layer]->CRes::Unlock();

	if( IsNameYellow(m_gid) )
	{
		if( IsEventAID(m_gid) )
		{
			if( layer == 0 )
			{
				if( m_sex == SEX_MALE )
					m_sprResList[layer] = (CSprRes*)g_resMgr().CResMgr::Get("인간족\\몸통\\남\\운영자2_남.Spr");
				else
					m_sprResList[layer] = (CSprRes*)g_resMgr().CResMgr::Get("인간족\\몸통\\여\\운영자2_여.Spr");
			}
			else
			if( layer == 5 )
			{
				if( m_sex == SEX_MALE )
					m_sprResList[layer] = (CSprRes*)g_resMgr().CResMgr::Get("인간족\\운영자\\운영자2_남_검.Spr");
				else
					m_sprResList[layer] = (CSprRes*)g_resMgr().CResMgr::Get("인간족\\운영자\\운영자2_여_검.Spr");
			}
			else
			if( layer == 6 )
			{
				m_sprResList[layer] = NULL;
			}
		}
		else
		{
			if( layer == 0 )
			{
				if( m_sex == SEX_MALE )
					m_sprResList[layer] = (CSprRes*)g_resMgr().CResMgr::Get("인간족\\몸통\\남\\운영자_남.Spr");
				else
					m_sprResList[layer] = (CSprRes*)g_resMgr().CResMgr::Get("인간족\\몸통\\여\\운영자_여.Spr");
			}
			else
			if( layer == 5 )
			{
				if( m_sex == SEX_MALE )
					m_sprResList[layer] = (CSprRes*)g_resMgr().CResMgr::Get("인간족\\운영자\\운영자_남_검.Spr");
				else
					m_sprResList[layer] = (CSprRes*)g_resMgr().CResMgr::Get("인간족\\운영자\\운영자_여_검.Spr");
			}
			else
			if( layer == 6 )
			{
				m_sprResList[layer] = NULL;
			}
		}
	}
	else
	{
		m_sprResList[layer] = (CSprRes*)g_resMgr().CResMgr::Get(sprName);
	}

	if( m_sprResList[layer] != NULL )
		m_sprResList[layer]->CRes::Lock();
}


hook_method<const char* (CPc::*)(int layer)> CPc::_GetSprNameList(SAKEXE, "CPc::GetSprNameList");
const char* CPc::GetSprNameList(int layer) // line 1963
{
	return (this->*_GetSprNameList)(layer);

	return ( m_sprResList[layer] != NULL ) ? m_sprResList[layer]->CRes::GetName() : "";
}


hook_method<CSprRes* (CPc::*)(int layer)> CPc::_GetSprResList(SAKEXE, "CPc::GetSprResList");
CSprRes* CPc::GetSprResList(int layer) // line 1969
{
	return (this->*_GetSprResList)(layer);

	return m_sprResList[layer];
}


hook_method<void (CPc::*)(int layer, const char* actName)> CPc::_SetActNameList(SAKEXE, "CPc::SetActNameList");
void CPc::SetActNameList(int layer, const char* actName) // line 1974
{
	return (this->*_SetActNameList)(layer, actName);

	if( m_actResList[layer] != NULL )
		m_actResList[layer]->CRes::Unlock();

	if( IsNameYellow(m_gid) )
	{
		if( IsEventAID(m_gid) )
		{
			if( layer == 0 )
			{
				if( m_sex == SEX_MALE )
					m_actResList[layer] = (CActRes*)g_resMgr().CResMgr::Get("인간족\\몸통\\남\\운영자2_남.Act");
				else
					m_actResList[layer] = (CActRes*)g_resMgr().CResMgr::Get("인간족\\몸통\\여\\운영자2_여.Act");
			}
			else
			if( layer == 5 )
			{
				if( m_sex == SEX_MALE )
					m_actResList[layer] = (CActRes*)g_resMgr().CResMgr::Get("인간족\\운영자\\운영자2_남_검.Act");
				else
					m_actResList[layer] = (CActRes*)g_resMgr().CResMgr::Get("인간족\\운영자\\운영자2_여_검.Act");
			}
			else
			if( layer == 6 )
			{
				m_actResList[layer] = NULL;
			}
		}
		else
		{
			if( layer == 0 )
			{
				if( m_sex == SEX_MALE )
					m_actResList[layer] = (CActRes*)g_resMgr().CResMgr::Get("인간족\\몸통\\남\\운영자_남.Act");
				else
					m_actResList[layer] = (CActRes*)g_resMgr().CResMgr::Get("인간족\\몸통\\여\\운영자_여.Act");
			}
			else
			if( layer == 5 )
			{
				if( m_sex == SEX_MALE )
					m_actResList[layer] = (CActRes*)g_resMgr().CResMgr::Get("인간족\\운영자\\운영자_남_검.Act");
				else
					m_actResList[layer] = (CActRes*)g_resMgr().CResMgr::Get("인간족\\운영자\\운영자_여_검.Act");
			}
			else
			if( layer == 6 )
			{
				m_actResList[layer] = NULL;
			}
		}
	}
	else
	{
		m_actResList[layer] = (CActRes*)g_resMgr().CResMgr::Get(actName);
	}

	if( m_actResList[layer] != NULL )
		m_actResList[layer]->CRes::Lock();
}


hook_method<const char* (CPc::*)(int layer)> CPc::_GetActNameList(SAKEXE, "CPc::GetActNameList");
const char* CPc::GetActNameList(int layer) // line 2026
{
	return (this->*_GetActNameList)(layer);

	return ( m_actResList[layer] != NULL ) ? m_actResList[layer]->CRes::GetName() : "";
}


hook_method<CActRes* (CPc::*)(int layer)> CPc::_GetActResList(SAKEXE, "CPc::GetActResList");
CActRes* CPc::GetActResList(int layer) // line 2032
{
	return (this->*_GetActResList)(layer);

	return m_actResList[layer];
}


hook_method<int (CPc::*)(int left, int right)> CPc::_MakeWeaponType(SAKEXE, "CPc::MakeWeaponType");
int CPc::MakeWeaponType(int left, int right) // line 2250
{
	return (this->*_MakeWeaponType)(left, right);

	int result = WEAPONTYPE_NONE;
	int wpn1 = ITEM_NONE;
	int wpn2 = ITEM_NONE;

	if( left != ITEM_NONE )
	{
		wpn1 = left;
		wpn2 = right;
	}
	else
	if( right != ITEM_NONE )
	{
		wpn1 = right;
		wpn2 = ITEM_NONE;
	}

	if( wpn1 >= ITEM_SWORD_TYPE_START && wpn1 < ITEM_TWOHANDSWORD_START )
	{
		result = WEAPONTYPE_SWORD;

		if( wpn2 >= ITEM_SWORD_TYPE_START && wpn2 < ITEM_TWOHANDSWORD_START )
			result = WEAPONTYPE_SWORD_SWORD;
		else
		if( wpn2 >= ITEM_AXE_START && wpn2 < ITEM_TWOHANDAXE_START )
			result = WEAPONTYPE_SWORD_AXE;
	}
	else
	if( wpn1 >= ITEM_SHORTSWORD_START && wpn1 < ITEM_CATARRH_START )
	{
		result = WEAPONTYPE_SHORTSWORD;

		if( wpn2 >= ITEM_SHORTSWORD_START && wpn2 < ITEM_CATARRH_START )
			result = WEAPONTYPE_SHORTSWORD_SHORTSWORD;
		else
		if( wpn2 >= ITEM_SWORD_TYPE_START && wpn2 < ITEM_TWOHANDSWORD_START )
			result = WEAPONTYPE_SHORTSWORD_SWORD;
		else
		if( wpn2 >= ITEM_AXE_START && wpn2 < ITEM_TWOHANDAXE_START )
			result = WEAPONTYPE_SHORTSWORD_AXE;
	}
	else
	if( wpn1 >= ITEM_AXE_START && wpn1 < ITEM_TWOHANDAXE_START )
	{
		result = WEAPONTYPE_AXE;

		if( wpn2 >= ITEM_AXE_START && wpn2 < ITEM_TWOHANDAXE_START )
			result = WEAPONTYPE_AXE_AXE;
	}

	return result;
}


////////////////////////////////////////


CBlurPC::CBlurPC(CPc* pc) // line 564 (Npc.cpp)
{
	this->CBlurPC::OnInit(); //inlined
}


CBlurPC::~CBlurPC(void) // line 596 (Npc.cpp)
{
	this->CBlurPC::OnExit(); //inlined
}


hook_method<void (CBlurPC::*)(void)> CBlurPC::_OnInit(SAKEXE, "CBlurPC::OnInit");
void CBlurPC::OnInit(void) // line 601 (Npc.cpp)
{
	return (this->*_OnInit)();

	m_isVisible = true;
	m_shadowOn = false;
	m_stateStartTick = timeGetTime();
}


hook_method<void (CBlurPC::*)(void)> CBlurPC::_OnExit(SAKEXE, "CBlurPC::OnExit");
void CBlurPC::OnExit(void) // line 609 (Npc.cpp)
{
	return (this->*_OnExit)();

	;
}


hook_method<bool (CBlurPC::*)(void)> CBlurPC::_OnProcess(SAKEXE, "CBlurPC::OnProcess");
bool CBlurPC::OnProcess(void) // line 613 (Npc.cpp)
{
	return (this->*_OnProcess)();

	if( m_sprArgb < m_alphaDelta )
		return false;

	m_sprArgb = m_sprArgb - m_alphaDelta;
	return true;
}


hook_method<void (CBlurPC::*)(matrix& ptm)> CBlurPC::_Render(SAKEXE, "CBlurPC::Render");
void CBlurPC::Render(matrix& ptm) // line 621 (Npc.cpp)
{
	return (this->*_Render)(ptm);

	if( IsEffectStateHiding(m_effectState)
	||  IsEffectStateSpecialHiding(m_effectState)
	||  IsEffectStateBurrow(m_effectState) )
		return;

	rand();
	rand();
	rand();
	rand();

	if( !m_isVisible )
	{
		this->CRenderObject::UpdateTlvertex(ptm);
		return;
	}

	if( g_serviceType == ServiceTaiwan && IsGravityAid(m_gid) && m_gid == g_session.CSession::GetAid() )
		return;

	if( m_stateId != STATEID_SIT && m_stateId != STATEID_DEAD )
		this->CRenderObject::RenderShadow(ptm, m_zoom);

	if( !m_isVisibleBody )
	{
		this->CRenderObject::UpdateTlvertex(ptm);
		return;
	}

	if( IsEventAID(m_gid) )
	{
		this->CPc::RenderBody2(ptm, 1);
	}
	else
	if( m_renderWithoutLayer )
	{
		this->CRenderObject::RenderBody(ptm);
	}
	else
	{
		this->CPc::RenderBodyLayer(ptm, 1);
	}
}


hook_method<void (CBlurPC::*)(CGameObject* sender, int message, int arg1, int arg2, int arg3)> CBlurPC::_SendMsg(SAKEXE, "CBlurPC::SendMsg");
void CBlurPC::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3) // line 665 (Npc.cpp)
{
	return (this->*_SendMsg)(sender, message, arg1, arg2, arg3);

	switch( message )
	{
	case 0:
		this->CRenderObject::SetArgb(180, arg1, arg2, arg3);
		m_alphaDelta = 0x8000000;
	break;
	case 1:
		m_sprArgb &= (arg1 << 24) + 0xFFFFFF;
		m_alphaDelta = arg2 << 24;
	break;
	case 2:
		m_motionY = (float)arg1;
	break;
	case 3:
		m_isMotionFreezed = true;
	break;
	default:
		this->CPc::SendMsg(sender, message, arg1, arg2, arg3);
	break;
	}
}
