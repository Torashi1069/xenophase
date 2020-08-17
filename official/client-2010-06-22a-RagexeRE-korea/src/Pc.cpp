#include "Globals.h"
#include "GameMode.h"
#include "ModeMgr.h"
#include "MsgStrings.h"
#include "Pc.h"
#include "Session.h"
#include "View.h"
#include "3dLib/Renderer.h"
#include "Base/Res.h"
#include "Framework/Locale.h"
#include "Resource/Action.h"
#include "Resource/ImfRes.h"
#include "Resource/PaletteRes.h"
#include "Resource/Sprite.h"
#include "Window/UIPcGage.h"
#include "Window/UIWindowMgr.h"
////////////////////////////////////////


CPc::CPc()
{
	m_sprResList.resize(8);
	m_actResList.resize(8);
	this->CPc::OnInit();
}


CPc::~CPc()
{
	for( int i = 0; i < 8; ++i )
	{
		if( m_sprResList[i] != NULL )
			m_sprResList[i]->CRes::Unlock();

		if( m_actResList[i] != NULL )
			m_actResList[i]->CRes::Unlock();
	}

	this->CPc::OnExit();
}


void CPc::OnInit()
{
	m_isPc = TRUE;
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


void CPc::OnExit()
{
	if( m_gage != NULL )
	{
		g_windowMgr.UIWindowMgr::PostQuit(m_gage);
		m_gage = NULL;
	}
}


hook_func<bool (CPc::*)()> CPc::_OnProcess("CPc::OnProcess");
bool CPc::OnProcess()
{
	return (this->*_OnProcess)();
}


hook_func<void (CPc::*)(CGameObject* sender, int message, int arg1, int arg2, int arg3)> CPc::_SendMsg("CPc::SendMsg");
void CPc::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3)
{
	return (this->*_SendMsg)(sender, message, arg1, arg2, arg3);
}


hook_func<void (CPc::*)(matrix& vtm)> CPc::_Render("CPc::Render");
void CPc::Render(matrix& vtm)
{
	return (this->*_Render)(vtm);

	if( IsEffectStateFootPrint(m_effectState) )
		this->CPc::RenderShoe(1);

	if( (m_BodyLight & 0x8000) == 0x8000 )
		this->CPc::RenderShoe(2);

	bool bHasState184 = false; //TODO
	for( size_t i = 0; i < stateId.size(); ++i )
		if( stateId[i] == 184 )
			bHasState184 = true;

	if( bHasState184 && (!m_isVisible || !m_isVisibleBody) && !IsEffectStateSpecialHiding(m_effectState) )
	{
		this->CRenderObject::SetArgb(-1, 0, 0, 0);
		this->CPc::RenderBodyLayer(vtm, 0, 0);
		return;
	}

	if( !m_isVisible )
	{
		this->CRenderObject::UpdateTlvertex(vtm);
		return;
	}

	if( m_stateId != STATEID_SIT && m_stateId != STATEID_DEAD )
		this->CRenderObject::RenderShadow(vtm, m_zoom);

	if( m_stateId == STATEID_SIT && this->CGameActor::GetJob() == JT_STAR2 )
		this->CRenderObject::RenderShadow(vtm, m_zoom);

	if( !m_isVisibleBody )
		this->CRenderObject::UpdateTlvertex(vtm);
	else
	if( IsEventAID(m_gid) )
		this->CPc::RenderBody2(vtm, 0);
	else
	if( m_renderWithoutLayer )
		this->CRenderObject::RenderBody(vtm, 0);
	else
		this->CPc::RenderBodyLayer(vtm, 0, 0);
}


hook_func<bool (CPc::*)()> CPc::_ProcessState("CPc::ProcessState");
bool CPc::ProcessState()
{
	return (this->*_ProcessState)();
}


hook_func<void (CPc::*)(int stateId)> CPc::_SetState("CPc::SetState");
void CPc::SetState(int stateId)
{
	return (this->*_SetState)(stateId);
}


hook_func<void (CPc::*)(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal)> CPc::_SetSprAct("CPc::SetSprAct");
void CPc::SetSprAct(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal)
{
	return (this->*_SetSprAct)(job, sex, head, weapon, accessory, accessory2, accessory3, shield, headPal, bodyPal);
}


hook_func<void (CPc::*)(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal, int effectState)> CPc::_SetSprAct2("CPc::SetSprAct2");
void CPc::SetSprAct2(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal, int effectState)
{
	return (this->*_SetSprAct2)(job, sex, head, weapon, accessory, accessory2, accessory3, shield, headPal, bodyPal, effectState);
}


hook_func<void (CPc::*)(int job)> CPc::_SetSprJob("CPc::SetSprJob");
void CPc::SetSprJob(int job)
{
	return (this->*_SetSprJob)(job);
}


hook_func<void (CPc::*)(int head)> CPc::_SetSprHead("CPc::SetSprHead");
void CPc::SetSprHead(int head)
{
	return (this->*_SetSprHead)(head);
}


hook_func<void (CPc::*)(int job)> CPc::_SetSprJobDye("CPc::SetSprJobDye");
void CPc::SetSprJobDye(int job)
{
	return (this->*_SetSprJobDye)(job);
}


hook_func<void (CPc::*)(int weapon)> CPc::_SetSprWeapon("CPc::SetSprWeapon");
void CPc::SetSprWeapon(int weapon)
{
	return (this->*_SetSprWeapon)(weapon);
}


hook_func<void (CPc::*)(int weapon)> CPc::_SetSprWeapon2("CPc::SetSprWeapon2");
void CPc::SetSprWeapon2(int weapon)
{
	return (this->*_SetSprWeapon2)(weapon);
}


hook_func<void (CPc::*)(int accessory)> CPc::_SetSprAccessory("CPc::SetSprAccessory");
void CPc::SetSprAccessory(int accessory)
{
	return (this->*_SetSprAccessory)(accessory);
}


hook_func<void (CPc::*)(int accessory2)> CPc::_SetSprAccessory2("CPc::SetSprAccessory2");
void CPc::SetSprAccessory2(int accessory2)
{
	return (this->*_SetSprAccessory2)(accessory2);
}


hook_func<void (CPc::*)(int accessory3)> CPc::_SetSprAccessory3("CPc::SetSprAccessory3");
void CPc::SetSprAccessory3(int accessory3)
{
	return (this->*_SetSprAccessory3)(accessory3);
}


hook_func<void (CPc::*)(int shield)> CPc::_SetSprShield("CPc::SetSprShield");
void CPc::SetSprShield(int shield)
{
	return (this->*_SetSprShield)(shield);
}


hook_func<void (CPc::*)(int shoe)> CPc::_SetSprShoe("CPc::SetSprShoe");
void CPc::SetSprShoe(int shoe)
{
	return (this->*_SetSprShoe)(shoe);
}


hook_func<void (CPc::*)()> CPc::_SetImfFileName("CPc::SetImfFileName");
void CPc::SetImfFileName()
{
	return (this->*_SetImfFileName)();
}


hook_func<void (CPc::*)()> CPc::_SetHeadPaletteName("CPc::SetHeadPaletteName");
void CPc::SetHeadPaletteName()
{
	return (this->*_SetHeadPaletteName)();
}


hook_func<void (CPc::*)()> CPc::_SetBodyPaletteName("CPc::SetBodyPaletteName");
void CPc::SetBodyPaletteName()
{
	return (this->*_SetBodyPaletteName)();
}


hook_func<void (CPc::*)(int bodyPalette)> CPc::_SetBodyPalette("CPc::SetBodyPalette");
void CPc::SetBodyPalette(int bodyPalette)
{
	return (this->*_SetBodyPalette)(bodyPalette);
}


hook_func<void (CPc::*)(int headPalette)> CPc::_SetHeadPalette("CPc::SetHeadPalette");
void CPc::SetHeadPalette(int headPalette)
{
	return (this->*_SetHeadPalette)(headPalette);
}


hook_func<int (CPc::*)()> CPc::_GetWeapon("CPc::GetWeapon");
int CPc::GetWeapon()
{
	return (this->*_GetWeapon)();
}


hook_func<void (CPc::*)(int attackM)> CPc::_SetModifyFactorOfmotionSpeed("CPc::SetModifyFactorOfmotionSpeed");
void CPc::SetModifyFactorOfmotionSpeed(int attackM)
{
	return (this->*_SetModifyFactorOfmotionSpeed)(attackM);
}


hook_func<void (CPc::*)(int honor)> CPc::_SetHonor("CPc::SetHonor");
void CPc::SetHonor(int honor)
{
	return (this->*_SetHonor)(honor);
}


hook_func<void (CPc::*)(int honor, int virtue)> CPc::_SetPropensityInfo("CPc::SetPropensityInfo");
void CPc::SetPropensityInfo(int honor, int virtue)
{
	return (this->*_SetPropensityInfo)(honor, virtue);
}


hook_func<void (CPc::*)(matrix& vtm, int isBlur)> CPc::_RenderBody2("CPc::RenderBody2");
void CPc::RenderBody2(matrix& vtm, int isBlur)
{
	return (this->*_RenderBody2)(vtm, isBlur);
}


hook_func<void (CPc::*)(matrix& vtm, int isBlur, bool arg3_2010)> CPc::_RenderBodyLayer("CPc::RenderBodyLayer");
void CPc::RenderBodyLayer(matrix& vtm, int isBlur, bool arg3_2010)
{
	return (this->*_RenderBodyLayer)(vtm, isBlur, arg3_2010);

	vector3d tv;
	tv.z = vtm.v13 * m_pos.x + m_pos.y * vtm.v23 + m_pos.z * vtm.v33 + vtm.v43;

	float x, y, oow;
	g_renderer->CRenderer::ProjectVertex(m_pos, vtm, &x, &y, &oow);

	float pixelRatio = g_renderer->CRenderer::GetPixelRatio(oow);
	m_lastPixelRatio = pixelRatio / g_avgPixelRatio;

	float fSprShift = g_renderer->CRenderer::GetScreenXFactor() * m_sprShift * m_zoom * m_lastPixelRatio;
	float zHover = g_zHover * m_lastPixelRatio;

	float lmRIntensity = 1.0;
	float lmGIntensity = 1.0;
	float lmBIntensity = 1.0;
	this->CRenderObject::SetLmIntensity(lmRIntensity, lmGIntensity, lmBIntensity);

	float m_fA = m_sprColor.a / 255.0f;
	float m_fR = m_sprColor.r / 255.0f * lmRIntensity;
	float m_fG = m_sprColor.g / 255.0f * lmGIntensity;
	float m_fB = m_sprColor.b / 255.0f * lmBIntensity;

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

	this->CRenderObject::SetCharacterPixelRatio(&pixelRatio);
	if( (this->CGameActor::GetJob() >= JT_NOVICE_B && this->CGameActor::GetJob() <= JT_THIEF_B) || this->CGameActor::GetJob() == JT_SUPERNOVICE_B )
		pixelRatio = pixelRatio * 0.75f;
	else
	if( this->CGameActor::GetJob() >= JT_KNIGHT_B && this->CGameActor::GetJob() <= JT_CHICKEN2_B || this->CGameActor::GetJob() >= JT_RUNE_KNIGHT_B && this->CGameActor::GetJob() <= JT_MADOGEAR_B )
		pixelRatio = pixelRatio * 0.82f;

	short fpos = 0;
	if( this->CGameActor::GetJob() == JT_STAR2 )
	{
		fpos = this->CRenderObject::SetCharacterFlying();
	}
	else
	if( this->CGameActor::GetJob() == JT_STAR )
	{
		if( m_FlyNow != 0 )
			--m_FlyNow;
	}

	int DoubleAcc = 0;
	int drawCount = 0;

	for( int p = 7; p >= 0; --p )
	{
		int subAction = m_curAction - m_baseAction; // direction of sprite: 0=S 1=SW 2=W 3=NW 4=N 5=NE 6=E 7=SE
		int layer; // 0=body(job) 1=head 2=accessory 3=accessory2 4=accessory3 5=weapon 6=weapon2 7=shield

		if( subAction < 2 || subAction > 5 )
		{// SW,S,SE,E layer=imf(0,1),{2,3,4,5,6,7}
			if( p >= 6 && p <= 7 ) // {6,7} => {0,1} => imf
				layer = imfRes->CImfRes::GetLayer(p - 6, m_curAction, m_curMotion);
			else// {0,1,2,3,4,5} => {7,6,5,4,3,2}
				layer = 7 - p;
		}
		else
		{// W,NW,N,NE layer={7},imf(0,1){2,3,4,5,6}
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
		else if( layer < 0 || layer >= 8 )
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

		if( DoubleAcc > 0 )
		{// looping a second time (for special headgear)
			char accname[256];
			switch( DoubleAcc )
			{
			case 1: sprintf(accname, "_요정의귀"); break;
			case 2: sprintf(accname, "_눈가리개"); break;
			case 3: sprintf(accname, "_헬름"); break;
			default: break;
			}

			char buf[1024];
			const char* sexName = g_session.m_newPcSexNameTable[m_sex];

			sprintf(buf, "sprite\\악세사리\\%s\\%s%s.act", sexName, sexName, accname);
			actRes = (CActRes*)g_resMgr().CResMgr::Get(buf);

			sprintf(buf, "sprite\\악세사리\\%s\\%s%s.spr", sexName, sexName, accname);
			sprRes = (CSprRes*)g_resMgr().CResMgr::Get(buf);

			DoubleAcc = 100; // mark as processed.
		}

		if( actRes == NULL )
			actRes = m_actResList[layer];

		if( sprRes == NULL )
			sprRes = m_sprResList[layer];

		if( layer == 1 && IsEffectStateOrcFace(m_effectState) )
		{
			actRes = (CActRes*)g_resMgr().CResMgr::Get("이팩트\\orcface.act");
			sprRes = (CSprRes*)g_resMgr().CResMgr::Get("이팩트\\orcface.spr");
		}

		if( m_stateId == 45 )
		{
			if( layer == 0 )
				actRes = (CActRes*)g_resMgr().CResMgr::Get("인간족\\몸통\\여\\아크비숍_여2.Act");
			else
			if( layer == 1 )
				actRes = (CActRes*)g_resMgr().CResMgr::Get("인간족\\머리통\\여\\2_여2.Act");
		}

		unsigned int clipId = 0;
		if( layer == 1 )
			clipId = 1;

		if( m_curMotion >= actRes->CActRes::GetMotionCount(m_curAction) )
			continue;

		bool unkFlag = 0; //TODO
		int tempAction;

		unsigned int actIndex, motIndex;
		if( this->CGameActor::GetJob() >= JT_TAEKWON && this->CGameActor::GetJob() <= JT_STAR2 && m_curAction >= 88 && layer >= 1 && layer <= 4 )
		{
			if( m_curAction <= 95 && m_curMotion >= 3 && m_curMotion <= 5 )
			{
				if( m_sex == 0 && m_curMotion != 3 )
				{
					unkFlag = true;

					if( m_curAction <= 89 )
					{
						if( m_curMotion == 4 )
							tempAction = 6;
						else
						if( m_curMotion == 5 )
							tempAction = 5;
					}
					else
					if( m_curAction <= 91 )
					{
						if( m_curMotion == 4 )
							tempAction = 6;
						else
						if( m_curMotion == 5 )
							tempAction = 7;
					}
					else
					if( m_curAction <= 93 )
					{
						if( m_curMotion == 4 )
							tempAction = 2;
						else
						if( m_curMotion == 5 )
							tempAction = 1;
					}
					else
					{
						if( m_curMotion == 4 )
							tempAction = 2;
						else
						if( m_curMotion == 5 )
							tempAction = 3;
					}
				}
				else
				if( m_sex == 1 && m_curMotion != 5 )
				{
					unkFlag = true;

					if( m_curAction <= 89 )
					{
						if( m_curMotion == 3 )
							tempAction = 6;
						else
						if( m_curMotion == 4 )
							tempAction = 5;
					}
					else
					if( m_curAction <= 91 )
					{
						if( m_curMotion == 3 )
							tempAction = 6;
						else
						if( m_curMotion == 4 )
							tempAction = 7;
					}
					else
					if( m_curAction <= 93 )
					{
						if( m_curMotion == 3 )
							tempAction = 2;
						else
						if( m_curMotion == 4 )
							tempAction = 1;
					}
					else
					{
						if( m_curMotion == 3 )
							tempAction = 2;
						else
						if( m_curMotion == 4 )
							tempAction = 3;
					}
				}
			}

			if( m_curAction >= 96 && m_curMotion == 1 )
			{
				unkFlag = true;

				if( m_curAction <= 97 )
					tempAction = 0;
				else
				if( m_curAction >= 98 && m_curAction <= 99 )
					tempAction = 6;
				else
				if( m_curAction >= 100 && m_curAction <= 101 )
					tempAction = 4;
				else
					tempAction = 2;

				motIndex = 0;
				actIndex = tempAction;
			}
			else
			{
				if( unkFlag == 1 )
				{
					motIndex = 0;
					actIndex = tempAction;
				}
				else
				{
					motIndex = m_curMotion;
					actIndex = m_curAction;
				}
			}
		}
		else
		{
			motIndex = m_curMotion;
			actIndex = m_curAction;
		}

		CMotion* mot = actRes->CActRes::GetMotion(actIndex, motIndex);
		if( layer == 6 )
		{
			if( mot->m_eventId != -1 )
			{
				mystd::string eventName = actRes->CActRes::GetEventName(mot->m_eventId);
				if( eventName.find_first_of(".wav") != eventName.npos )
					strcpy(m_hitWaveName, eventName.c_str());

				m_isPlayHitWave = 1;
			}
		}
		else
		if( layer == 2 || layer == 3 || layer == 4 )
		{
			int headMotionCnt = m_actResList[1]->CActRes::GetMotionCount(m_curAction);
			int curMotionCnt = m_actResList[layer]->CActRes::GetMotionCount(m_curAction);
			if( headMotionCnt > 0 && curMotionCnt > 0 && curMotionCnt != headMotionCnt && curMotionCnt > headMotionCnt && curMotionCnt % headMotionCnt == 0 )
			{
				unsigned int motIndex = m_curMotion * curMotionCnt / headMotionCnt;
				mot = actRes->CActRes::GetMotion(m_curAction, motIndex);
			}
		}

		CSprClip* sprClip = mot->CMotion::GetClip(clipId);
		if( sprClip->sprIndex == -1 )
			continue;

		unsigned int argb = ((((((
			int(sprClip->a / 255.0f * m_fA * 255.0f)) << 8) +
			int(sprClip->r / 255.0f * m_fR * 255.0f)) << 8) +
			int(sprClip->g / 255.0f * m_fG * 255.0f)) << 8) +
			int(sprClip->b / 255.0f * m_fB * 255.0f);

		SprImg* sprImg = sprRes->m_sprites[sprClip->clipType][sprClip->sprIndex];

		static int head_imfOffX; // WARNING static variable unique to this function
		static int head_imfOffY; // WARNING static variable unique to this function
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
		case 8: // ???
		{
			int headMotionCnt = m_actResList[1]->CActRes::GetMotionCount(m_curAction);
			int layerMotionCnt = m_actResList[layer]->CActRes::GetMotionCount(m_curAction);

			if( headMotionCnt > 0 && layerMotionCnt > 0 && layerMotionCnt != headMotionCnt && layerMotionCnt > headMotionCnt && (layerMotionCnt % headMotionCnt) == 0 )
			{
				int ratio = layerMotionCnt / headMotionCnt;
				int delta = timeGetTime() - m_stateStartTick;
				int delay = (int)m_actResList[layer]->CActRes::GetDelay(0);
				if( delay == 0 )
					delay = 4;
				unsigned int motIndex = m_curMotion * ratio + (int)(delta / 24.0f / delay) % ratio;

				mot = m_actResList[layer]->CActRes::GetMotion(m_curAction, motIndex);
				sprClip = mot->CMotion::GetClip(clipId);
				if( sprClip->sprIndex != -1 )
					sprImg = sprRes->m_sprites[sprClip->clipType][sprClip->sprIndex];
			}

			unsigned int actIndex, motIndex;
			if( unkFlag == 1 )
			{
				motIndex = 0;
				actIndex = tempAction;
			}
			else
			{
				motIndex = m_curMotion;
				actIndex = m_curAction;
			}

			CMotion* headMotion = m_actResList[1]->CActRes::GetMotion(actIndex, motIndex);
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

		this->CRenderObject::SetCharacterPreAngle(layer, &imfOffX, &imfOffY, &head_imfOffX, &head_imfOffY);

		float top = (imfOffY + sprClip->y) * sprClip->zoomy * m_zoom * pixelRatio + y;
		float btm = (imfOffY + sprClip->y + sprImg->height * (sprImg->isHalfH + 1)) * sprClip->zoomy * m_zoom * pixelRatio + y + 1.0f;
		float left, right;

		if( (sprClip->flags & 1) == 0 )
		{
			left = (sprClip->x + imfOffX) * m_zoom * sprClip->zoomx * pixelRatio + x;
			right = (sprClip->x + imfOffX + sprImg->width * (sprImg->isHalfW + 1)) * m_zoom * sprClip->zoomx * pixelRatio + x + 1.0f;

			if( top >= g_renderer->CRenderer::GetHeight() || btm <= 0.0 || g_renderer->CRenderer::GetWidth() <= left || right <= 0.0 )
				continue;
		}
		else // mirror X
		{
			left = (sprClip->x + imfOffX + sprImg->width * (sprImg->isHalfW + 1)) * m_zoom * sprClip->zoomx * pixelRatio + x;
			right = (sprClip->x + imfOffX) * m_zoom * sprClip->zoomx * pixelRatio + x + 1.0f;

			if( top >= g_renderer->CRenderer::GetHeight() || btm <= 0.0 || g_renderer->CRenderer::GetWidth() <= right || left <= 0.0 )
				continue;
		}

		this->CRenderObject::SetCharacterSquare(&top, &btm, &left, &right);
		isInsideScreen = true;

		float sprOow, sprOowup;
		if( m_alwaysTopLayer )
		{
			sprOowup = p * g_zOffset + 1.0f / 10.0f - g_zOffset * 20.0f + m_offsetOow * g_zOffset;
			sprOow = sprOowup;
		}
		else
		if( m_isLieOnGround )
		{
			float unkVal = (m_offsetOow + drawCount + 3) * g_zOffset; //TODO
			sprOowup = 1.0f / (tv.z - (top - y) * g_shadowSlope) + unkVal + zHover;
			sprOow = 1.0f / (tv.z - (btm - y) * g_shadowSlope) + unkVal + zHover;
		}
		else
		{
			float unkVal = (m_offsetOow + drawCount + 3) * g_zOffset; //TODO
			sprOowup = 1.0f / ((top - y) * g_slope + tv.z) + unkVal + zHover;
			sprOow = 1.0f / ((btm - y) * g_slope + tv.z) + unkVal + zHover;
		}

		++drawCount;

		if( m_isSingleColor != 0x00000000 && m_colorOfSingleColor != 0xFFFF0000 )
			argb = m_colorOfSingleColor;

		RPSprite spr;
		spr.top = top;
		spr.bottom = btm;
		spr.left = left + fSprShift;
		spr.right = right + fSprShift;

		switch( layer )
		{
		case 5:
			spr.oow = sprOow + 0.00006f;
			spr.oowup = sprOowup + 0.00006f;
		break;
		case 3:
			if( g_viewDistance >= 320.0 )
			{
				spr.oow = sprOow;
				spr.oowup = sprOowup;
			}
			else
			{
				spr.oow = sprOow + 0.00004f;
				spr.oowup = sprOowup + 0.00004f;
			}
		break;
		case 4:
			if( g_viewDistance >= 320.0 )
			{
				spr.oow = sprOow;
				spr.oowup = sprOowup;
			}
			else
			{
				spr.oow = sprOow + 0.00003f;
				spr.oowup = sprOowup + 0.00003f;
			}
		break;
		case 2:
			if( g_viewDistance >= 320.0 )
			{
				spr.oow = sprOow;
				spr.oowup = sprOowup;
			}
			else
			{
				spr.oow = sprOow + 0.000027f;
				spr.oowup = sprOowup + 0.000027f;
			}
		break;
		case 1:
			if( g_viewDistance >= 320.0 )
			{
				spr.oow = sprOow;
				spr.oowup = sprOowup;
			}
			else
			{
				spr.oow = sprOow + 0.000025f;
				spr.oowup = sprOowup + 0.000025f;
			}
		break;
		default:
			spr.oow = sprOow;
			spr.oowup = sprOowup;
		break;
		}

		spr.spr = sprImg;
		spr.rgba = argb;
		spr.angle = float(m_sprAngle + sprClip->angle);
		this->CRenderObject::SetCharacterAngle(&spr.angle);

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

		if( layer < 2 )
		{
			if( argb < 0xFF000000 )
				renderFlag = 0x101;
		}
		else
		if( layer <= 3 )
		{
			renderFlag = 0x1;
		}
		else
		if( layer == 4 )
		{
			renderFlag = (m_accessory3 != 185);
		}
		else
		{
			if( argb < 0xFF000000 )
				renderFlag = 0x101;
		}

		m_actResList[1]->CActRes::GetMotionCount(m_curAction); // unused?
		m_actResList[layer]->CActRes::GetMotionCount(m_curAction); // unused?

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
				this->CRenderObject::RenderSprite(spr, palette, 0x5);
				m_BodyFlag = 1;
			}
		}

		if( (m_BodyLight & 8) == 8 && layer <= 4 && (m_BodyLight & 0x10000) != 0x10000 && (m_BodyLight & 0x20000) != 0x20000 )
		{
			++m_BodySin;
			if( m_BodySin > 180 )
				m_BodySin = 0;

			float fval = 400.0f / g_modeMgr.CModeMgr::GetGameMode()->CGameMode::GetView()->CView::GetDestDistance() * (g_sinTable[m_BodySin] + 3.0f);

			RPSprite spr2;
			spr2.bottom = fval + btm;
			spr2.top = top - fval - fpos;
			spr2.bottom = spr2.bottom - fpos;
			spr2.left = left + fSprShift;
			spr2.right = right + fSprShift;
			if( spr2.left <= spr2.right )
			{
				spr2.left = spr2.left - fval;
				spr2.right = spr2.right + fval;
			}
			else
			{
				spr2.left = spr2.left + fval;
				spr2.right = spr2.right - fval;
			}
			spr2.spr = sprImg;
			spr2.oow = sprOow - 0.00005f;
			spr2.oowup = sprOowup - 0.00005f;
			spr2.rgba = 0x64FFFFFF;
			spr2.angle = float(m_sprAngle + sprClip->angle);
			this->CRenderObject::RenderSprite(spr2, palette, 0x5);

			float fval2 = 400.0f / g_modeMgr.CModeMgr::GetGameMode()->CGameMode::GetView()->CView::GetDestDistance() * (2 * g_sinTable[m_BodySin] + 5.0f);

//			RPSprite spr2;
			spr2.bottom = fval2 + btm;
			spr2.top = top - fval2 - fpos;
			spr2.bottom = spr2.bottom - fpos;
			spr2.left = left + fSprShift;
			spr2.right = right + fSprShift;
			if( spr2.left <= spr2.right )
			{
				spr2.left = spr2.left - fval2;
				spr2.right = spr2.right + fval2;
			}
			else
			{
				spr2.left = spr2.left + fval2;
				spr2.right = spr2.right - fval2;
			}
			spr2.oow = sprOow - 0.00005f;
			spr2.spr = sprImg;
			spr2.oowup = sprOowup - 0.00005f;
			spr2.rgba = 0x78FFFFFF;
			spr2.angle = float(m_sprAngle + sprClip->angle);
			this->CRenderObject::RenderSprite(spr2, palette, 0x5);
		}

		if( ((m_BodyLight & 0x800) == 0x800 || (m_BodyLight & 0x80000) == 0x80000) && (m_BodyLight & 0x20000) != 0x20000 )
		{
			for( int i = 1; i <= 2; ++i )
			{
				float ratio = g_renderer->CRenderer::GetPixelRatio(oow);
				if( (this->CGameActor::GetJob() >= JT_NOVICE_B && this->CGameActor::GetJob() <= JT_THIEF_B) || this->CGameActor::GetJob() == JT_SUPERNOVICE_B )
					ratio = ratio * 0.75f;
				else
				if( this->CGameActor::GetJob() >= JT_KNIGHT_B && this->CGameActor::GetJob() <= JT_CHICKEN2_B )
					ratio = ratio * 0.82f;
				else
				if( this->CGameActor::GetJob() >= JT_RUNE_KNIGHT_B && this->CGameActor::GetJob() <= JT_SHADOW_CHASER_B )
					ratio = ratio * 0.82f;

				float ratio2 = (i * 0.01f + 1.0f) * ratio;
				float fval = g_renderer->CRenderer::GetScreenXFactor() * m_sprShift * m_zoom * ratio2;

				float top2 = (imfOffY + sprClip->y) * sprClip->zoomy * ratio2 * m_zoom + y;
				float btm2 = (sprClip->y + imfOffY + sprImg->height * (sprImg->isHalfH + 1)) * sprClip->zoomy * ratio2 * m_zoom + y + 1.0f;
				float left2, right2;

				if( (sprClip->flags & 1) == 0 )
				{
					left2 = (imfOffX + sprClip->x) * ratio2 * m_zoom * sprClip->zoomx + x;
					right2 = (imfOffX + sprClip->x + sprImg->width * (sprImg->isHalfW + 1)) * ratio2 * m_zoom * sprClip->zoomx + x + 1.0f;

					if( top >= g_renderer->CRenderer::GetHeight() || btm <= 0.0 || g_renderer->CRenderer::GetWidth() <= left || right <= 0.0 )
						continue;
				}
				else // mirror X
				{
					left2 = (imfOffX + sprClip->x + sprImg->width * (sprImg->isHalfW + 1)) * ratio2 * m_zoom * sprClip->zoomx + x;
					right2 = (imfOffX + sprClip->x) * ratio2 * m_zoom * sprClip->zoomx + x + 1.0f;

					if( top >= g_renderer->CRenderer::GetHeight() || btm <= 0.0 || g_renderer->CRenderer::GetWidth() <= right || left <= 0.0 )
						continue;
				}

				RPSprite spr2;
				spr2.spr = sprImg;
				spr2.left = left2 + fval;
				spr2.right = right2 + fval;
				spr2.top = top2 - fpos;
				spr2.bottom = (top - top2) * 0.5f + btm - fpos;
				spr2.oow = sprOow + 3*i * 0.000005f + 0.00001f;
				spr2.oowup = sprOowup + 3*i * 0.000005f + 0.00001f;

				if( (m_BodyLight & 0x800) == 0x800 )
					spr2.rgba = (m_BodySin5 << 24) + 0x3737FF;
				else
				if( (m_BodyLight & 0x80000) == 0x80000 )
					spr2.rgba = (m_BodySin5 << 24) + 0x056405;

				spr2.angle = float(m_sprAngle + sprClip->angle);
				this->CRenderObject::RenderSprite(spr2, palette, 0x5);
			}
		}

		if( (m_BodyLight & 0x1000) == 0x1000 && (m_BodyLight & 0x10000) != 0x10000 && (m_BodyLight & 0x20000) != 0x20000 )
		{
			for( int i = 1; i <= 4; ++i )
			{
				short alpha = 5 * (30 - m_BodyTime);
				if( alpha < 0 )
					alpha = 0;

				float fval = 400.0f / g_modeMgr.CModeMgr::GetGameMode()->CGameMode::GetView()->CView::GetDestDistance() * (4 * m_BodyTime);
				
				RPSprite spr2;
				if( i == 1 )
				{
					spr2.top = top;
					spr2.bottom = btm;
					spr2.left = fval + left + fSprShift;
					spr2.right = fval + right + fSprShift;
				}
				else
				if( i == 2 )
				{
					spr2.top = top;
					spr2.bottom = btm;
					spr2.left = left + fSprShift - fval;
					spr2.right = right + fSprShift - fval;
				}
				else
				if( i == 3 )
				{
					spr2.top = fval + top;
					spr2.bottom = fval + btm;
					spr2.left = left + fSprShift;
					spr2.right = right + fSprShift;
				}
				else
				if( i == 4 )
				{
					spr2.top = top - fval;
					spr2.bottom = btm - fval;
					spr2.left = left + fSprShift;
					spr2.right = right + fSprShift;
				}

				spr2.top = spr2.top - fpos;
				spr2.bottom = spr2.bottom - fpos;
				spr2.oow = sprOow + 0.1f;
				spr2.oowup = sprOowup + 0.1f;
				spr2.spr = sprImg;
				spr2.rgba = (alpha << 24) + 0xFFFFFF;
				spr2.angle = float(m_sprAngle + sprClip->angle);
				this->CRenderObject::RenderSprite(spr2, palette, 0x201);
			}
		}

		if( (m_BodyLight & 0x200) == 0x200 && (m_BodyLight & 0x10000) != 0x10000 && (m_BodyLight  & 0x20000) != 0x20000 )
		{
			++m_BodySin2;
			if( m_BodySin2 >= 200 )
				m_BodySin2 = m_BodySin2 + 56;

			for( int i = 5; i < 20; i += 5 )
			{
				float fval2 = m_BodySin2 * 0.1f + i;
				if( fval2 >= 20.0f )
					fval2 -= 20.0f;
				int alpha = int(100.0f - fval2 * 5.0f);

				float fval = 400.0f / g_modeMgr.CModeMgr::GetGameMode()->CGameMode::GetView()->CView::GetDestDistance() * fval2;

				RPSprite spr2;
				spr2.bottom = fval + btm;
				spr2.top = top - fval - fpos;
				spr2.bottom = spr2.bottom - fpos;
				spr2.left = left + fSprShift;
				spr2.right = right + fSprShift;
				if( spr2.left <= spr2.right )
				{
					spr2.left = spr2.left - fval;
					spr2.right = spr2.right + fval;
				}
				else
				{
					spr2.left = spr2.left + fval;
					spr2.right = spr2.right - fval;
				}
				spr2.spr = sprImg;
				spr2.rgba = (alpha << 24) + 0xFFFFFF;
				spr2.oow = sprOow - fval * 0.000005f - 0.00001f;
				spr2.oowup = sprOowup - fval * 0.000005f - 0.00001f;
				spr2.angle = float(m_sprAngle + sprClip->angle);
				if( renderFlag != 0x5 )
					this->CRenderObject::RenderSprite(spr2, palette, renderFlag);
			}

			spr.rgba = 0x96FFFFFF;
		}

		if( (m_BodyLight & 0x2000) == 0x2000 )
		{
			float ran[4];
			for( int i = 0; i < countof(ran); ++i )
				ran[i] = 400.0f / g_modeMgr.CModeMgr::GetGameMode()->CGameMode::GetView()->CView::GetDestDistance() * (rand() % 11 - 5);

			spr.top = ran[0] + top;
			spr.bottom = ran[1] + btm;
			spr.left = ran[2] + left + fSprShift;
			spr.right = ran[3] + right + fSprShift;
		}

		if( (m_BodyLight & 0x10000) == 0x10000 )
		{
			short alpha = 255 - 20 * m_BodyTime;
			if( alpha < 0 )
				alpha = 0;

			float fval = 400.0f / g_modeMgr.CModeMgr::GetGameMode()->CGameMode::GetView()->CView::GetDestDistance() * (20 * m_BodyTime);
			spr.rgba = (alpha << 24) + 0xFFFFFF;
			spr.top = top - fval;
			spr.bottom = btm - fval;
		}

		if( (m_BodyLight & 0x20000) == 0x20000 )
		{
			float fval = 400.0f / g_modeMgr.CModeMgr::GetGameMode()->CGameMode::GetView()->CView::GetDestDistance() * (20 * (25 - m_BodyTime2));
			if( fval < 0.0f )
				fval = 0.0f;

			short alpha = 17 * (m_BodyTime2 - 10);
			if( alpha > 255 )
				alpha = 255;
			else
			if( alpha < 0 )
				alpha = 0;

			spr.rgba = (alpha << 24) + 0xFFFFFF;
			spr.top = top - fval;
			spr.bottom = btm - fval;
		}

		if( fpos )
		{
			spr.top = spr.top - fpos;
			spr.bottom = spr.bottom - fpos;
		}

		if( (m_BodyLight & 0x100000) == 0x100000 )
		{
			if( layer == 0 || layer > 4 )
			{
				spr.rgba = 0x1E373737;
				renderFlag = 0x5;
			}

			float fval = 24000.0f / g_modeMgr.CModeMgr::GetGameMode()->CGameMode::GetView()->CView::GetDestDistance();
			spr.top = fval + top;
			spr.bottom = fval + btm;
		}

		if( arg3_2010 )
		{
			if( layer == 5 )
			{
				this->CRenderObject::RenderSprite(spr, palette, 5);
				this->CRenderObject::SetCharacterLight(spr, palette);
			}
		}
		else
		{
			this->CRenderObject::RenderSprite(spr, palette, renderFlag);
			this->CRenderObject::SetCharacterLight(spr, palette);
		}

		if( DoubleAcc == 100 )
		{// successfully looped a second time, clear flag.
			DoubleAcc = 0;
		}
		else
		{// check if looping a second time is needed
			if( layer == 4 )
			{
				++p; // should loop a second time?

				if( m_accessory3 == 288 || m_accessory3 == 289 )
					DoubleAcc = 1;
				else
				if( m_accessory3 == 292 || m_accessory3 == 293 )
					DoubleAcc = 2;
				else
					--p; // nope.
			}
			else
			if( layer == 3 )
			{
				++p; // should loop a second time?

				if( m_accessory2 == 290 || m_accessory2 == 291 )
					DoubleAcc = 3;
				else
					--p; // nope.
			}
		}
	}// for(p=7..0)

	if( isInsideScreen )
	{
		this->SetRenderInfo(info, x, y);
		m_BeZero = 1;
	}
	else
	{
		this->SetTlvert(x, y);
		m_BeZero = 1;
	}
}


hook_func<void (CPc::*)(int shoenum)> CPc::_RenderShoe("CPc::RenderShoe");
void CPc::RenderShoe(int shoenum)
{
	return (this->*_RenderShoe)(shoenum);
}


////////////////////////////////////////


hook_func<CBlurPC* (CBlurPC::*)(CPc* pc)> CBlurPC::_cCBlurPC("CBlurPC::CBlurPC");
CBlurPC::CBlurPC(CPc* pc)
{
	(this->*_cCBlurPC)(pc); return;
}


hook_func<void (CBlurPC::*)(void)> CBlurPC::_dCBlurPC("CBlurPC::~CBlurPC");
CBlurPC::~CBlurPC(void)
{
	(this->*_dCBlurPC)(); return;
}


hook_func<void (CBlurPC::*)(matrix& ptm)> CBlurPC::_Render("CBlurPC::Render");
void CBlurPC::Render(matrix& ptm)
{
	return (this->*_Render)(ptm);

	if( IsEffectStateHiding(m_effectState) || IsEffectStateSpecialHiding(m_effectState) || IsEffectStateBurrow(m_effectState) )
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

	if( g_serviceType == ServiceTaiwan && IsGravityAid(m_gid) && m_gid != g_session.m_aid )
		return;

	if( m_stateId != STATEID_SIT && m_stateId != STATEID_DEAD )
		this->CRenderObject::RenderShadow(ptm, m_zoom);

	if( !m_isVisibleBody )
		this->CRenderObject::UpdateTlvertex(ptm);
	else
	if( IsEventAID(m_gid) )
		this->CPc::RenderBody2(ptm, 1);
	else
	if( m_renderWithoutLayer )
		this->CRenderObject::RenderBody(ptm, 0);
	else
		this->CPc::RenderBodyLayer(ptm, 1, 0);
}


////////////////////////////////////////
