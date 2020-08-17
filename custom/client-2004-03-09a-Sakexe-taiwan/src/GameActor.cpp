#include "GameActor.h"
#include "GameMode.h"
#include "GameWorld.h"
#include "Globals.h"
#include "ModeMgr.h"
#include "MsgStrings.h"
#include "Player.h"
#include "RagEffect.h"
#include "Skill.h"
#include "3dLib/Prim.h"
#include "Base/ResMgr.h"
#include "Resource/PaletteRes.h"
#include "Resource/Wave.h"
#include "Window/UIBalloonText.h"
#include "Window/UIEmblemWnd.h"
#include "Window/UIGage.h"
#define _USE_MATH_DEFINES
#include <math.h>
//////////////////////////////////////////////////


void RENDER_INFO_RECT::SetInfo(float left, float top, float right, float bottom, float oow) // line 30-37
{
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->oow = oow;
}


void RENDER_INFO_RECT::Update(const struct RPSprite& spr) // line 39-52
{
	float left = min(spr.left, spr.right);
	float right = max(spr.left, spr.right);
	
    if( this->left > left )
        this->left = left;
    if( this->top > spr.top )
        this->top = spr.top;
    if( this->right < right )
        this->right = right;
    if( this->bottom < spr.bottom )
        this->bottom = spr.bottom;
}


//////////////////////////////////////////////////


WBA::WBA(int message, int damage, unsigned long time, unsigned long targetGid, int tCellX, int tCellY, int effectId1, int effectId2, int effectLevel, float attackedSpeedFactor)
{
	this->message = message;
	this->damage = damage;
	this->time = time;
	this->targetGid = targetGid;
	this->tCellX = tCellX;
	this->tCellY = tCellY;
	this->effectId1 = effectId1;
	this->effectId2 = effectId2;
	this->effectLevel = effectLevel;
	this->attackedSpeedFactor = attackedSpeedFactor;
}


//////////////////////////////////////////////////


CGameObject::CGameObject() // line 58-60
{
	this->CGameObject::OnInit(); //inlined
}


CGameObject::~CGameObject() // line 63-65
{
	this->CGameObject::OnExit(); //inlined
}


void CGameObject::OnInit() // line 68-69
{
}


void CGameObject::OnExit() // line 72-73
{
}


bool CGameObject::OnProcess() // line 76-78
{
	return true;
}


void CGameObject::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3) // line 142-147
{
	switch( message )
	{
	default:
	break;
	};
}


void CGameObject::Render(matrix& ptm) // line 259 (GameActor.h)
{
}


int CGameObject::Get8Dir(float rot) // line 81-102
{
	CGameMode* mode = g_modeMgr.CModeMgr::GetGameMode();
	if( mode == NULL )
		return 0;

	float angle = -mode->CGameMode::GetView()->CView::GetCurLongitude() - rot;

	while( angle < 0.0 )
		angle += 360.0;

	while( angle >= 360.0 )
		angle -= 360.0;

	return int(angle / 45.0);
}


int CGameObject::Get8Dir2(float rot, BOOL isReal8Dir) // line 105-125
{
	CGameMode* mode = g_modeMgr.CModeMgr::GetGameMode();
	if( mode == NULL )
		return 0;

	float angle = -mode->CGameMode::GetView()->CView::GetCurLongitude() - rot;

	while( angle < 0.0 )
		angle += 360.0;

	while( angle >= 360.0 )
		angle -= 360.0;

	if( !isReal8Dir )
		return int(angle / 45.0);
	else
	if( angle >= 22.5 && angle <= 337.5 )
		return int((angle + 22.5) / 45.0);
	else
		return 0;
}


int CGameObject::GetDir(float rot) // line 128-139
{
	CGameMode* mode = g_modeMgr.CModeMgr::GetGameMode();
	if( mode == NULL )
		return 0;

	int angle = int(-mode->CGameMode::GetView()->CView::GetCurLongitude() - rot);

	if( angle < 0 )
		angle = angle + 360 * ((-1 - angle) / 360 + 1);

	if( angle >= 360 )
		angle = angle % 360;

	return angle;
}


//////////////////////////////////////////////////


CRenderObject::CRenderObject() // line 153-158
{
	m_sprRes = NULL;
	m_actRes = NULL;
	this->CRenderObject::OnInit();
}


CRenderObject::~CRenderObject() // line 161-166
{
	if( m_sprRes != NULL )
		m_sprRes->CRes::Unlock();

	if( m_actRes != NULL )
		m_actRes->CRes::Unlock();

	this->CRenderObject::OnExit(); // inlined
}


void CRenderObject::OnInit() // line 169-227
{
	m_pos.x = 0.0;
	m_pos.y = 0.0;
	m_pos.z = 0.0;
	m_baseAction = 0;
	m_curAction = 0;
	m_oldBaseAction = 0;
	m_curMotion = 0;
	m_oldMotion = 0;
	m_roty = 0.0;
	m_zoom = 1.0;
	m_shadowZoom = 1.0;
	m_motionType = 0;
	m_motionSpeed = 1.0;
	m_stateId = 0;
	m_isVisible = true;
	m_isVisibleBody = true;
	m_sprArgb = 0xFFFFFFFF;
	m_alwaysTopLayer = false;
	m_shadowOn = false;
	m_isMotionFinished = false;
	m_isMotionFreezed = false;
	m_shouldAddPickInfo = false;
	m_sprShift = 0;
	m_sprAngle = 0;
	m_singleColorStartTick = timeGetTime();
	m_isSingleColor = false;
	m_isLieOnGround = false;
	m_isSprArgbFixed = false;
	m_colorOfSingleColor = 0xFFFF0000;
	m_offsetOow = 0;
	m_bodyPalette = 0;
	m_lastPixelRatio = 1.0;
	m_loopCountOfmotionFinish = 1.0;
	m_modifyFactorOfmotionSpeed = 1.0;
	m_isPc = 0;

	char actName[128];
	char sprName[128];
	sprintf(sprName, "NPC\\%s.spr", g_session.m_jobNameTable[JT_1_ETC_01]);
	sprintf(actName, "NPC\\%s.act", g_session.m_jobNameTable[JT_1_ETC_01]);

	if( m_sprRes != NULL )
		m_sprRes->CRes::Unlock();

	m_sprRes = (CSprRes*)g_resMgr().CResMgr::Get(sprName);
	if( m_sprRes != NULL )
		m_sprRes->CRes::Lock();

	if( m_actRes != NULL )
		m_actRes->CRes::Unlock();

	m_actRes = (CActRes*)g_resMgr().CResMgr::Get(actName);
	m_actRes->CRes::Lock();

	m_oldColor.a = 0;
	m_oldColor.r = 0;
	m_oldColor.g = 0;
	m_oldColor.b = 0;
	m_isForceState = 0;
	m_forceAnimSpeed = 10;
	m_BodyLight = 0;
	m_BodyHit = 0;
	m_BodyHeight = 0.0;
	m_BodyFlag = 0;
	m_BodySin = 0;
}


void CRenderObject::OnExit() // line 230-231
{
}


bool CRenderObject::OnProcess() // line 278 (GameActor.h)
{
	return false;
}


void CRenderObject::Render(matrix& vtm) // line 902-907
{
	if( !m_isVisible )
		return;
	this->CRenderObject::RenderShadow(vtm, m_zoom);
	this->CRenderObject::RenderBody(vtm);
}


void CRenderObject::UpdateTlvertex(matrix& vtm) // line 544-549
{
	float x, y, oow;
	g_renderer->CRenderer::ProjectVertex(m_pos, vtm, &x, &y, &oow);
	this->SetTlvert(x, y);
}


void CRenderObject::RenderBody(matrix& vtm) // line 552-732
{
	vector3d tv;  tv.z = m_pos.x * vtm.v13 + m_pos.y * vtm.v23 + m_pos.z * vtm.v33 + vtm.v43;
	float x, y, oow;  g_renderer->CRenderer::ProjectVertex(m_pos, vtm, &x, &y, &oow);
	float pixelRatio = g_renderer->CRenderer::GetPixelRatio(oow);
	float fSprShift = g_renderer->CRenderer::GetScreenXFactor() * m_sprShift * m_lastPixelRatio * m_zoom;
	float zHover = g_zHover * m_lastPixelRatio;
	CMotion* motion = m_actRes->CActRes::GetMotion(m_curAction, m_curMotion);

	float lmRIntensity = 1.0f;
	float lmGIntensity = 1.0f;
	float lmBIntensity = 1.0f;
	this->CRenderObject::SetLmIntensity(lmRIntensity, lmGIntensity, lmBIntensity); // inlined
	float m_fA = m_sprColor.a;
	float m_fR = m_sprColor.r * lmRIntensity;
	float m_fG = m_sprColor.g * lmGIntensity;
	float m_fB = m_sprColor.b * lmBIntensity;

	RENDER_INFO_RECT info;
	info.left = (float)g_renderer->GetWidth();
	info.right = 0.0f;
	info.bottom = 0.0f;
	info.top = (float)g_renderer->GetHeight();
	info.oow = oow;

	bool isInsideScreen = false;
	for( int clipId = 0; clipId < motion->numClips; ++clipId )
	{
		CSprClip* sprClip = motion->CMotion::GetClip(clipId);
		if( sprClip->sprIndex == -1 )
			continue;

		SprImg* sprImg = m_sprRes->m_sprites[sprClip->clipType][sprClip->sprIndex];
		float top = sprClip->y * sprClip->zoomy * m_zoom * pixelRatio + y;
		float bottom = (sprClip->y + sprImg->height * int(sprImg->isHalfH + 1)) * sprClip->zoomy * m_zoom * pixelRatio + y + 1.0f;
		float left, right;
		if( (sprClip->flags & 1) == 0 )
		{
			left = sprClip->x * sprClip->zoomx * m_zoom * pixelRatio + x;
			right = (sprClip->x + sprImg->width * int(sprImg->isHalfW + 1)) * sprClip->zoomx * m_zoom * pixelRatio + x + 1.0f;
			if( g_renderer->GetHeight() <= top || bottom <= 0.0f || g_renderer->GetWidth() <= left || right <= 0.0f )
				continue;
		}
		else
		{
			left = (sprClip->x + sprImg->width * int(sprImg->isHalfW + 1)) * sprClip->zoomx * m_zoom * pixelRatio + x;
			right = sprClip->x * sprClip->zoomx * m_zoom * pixelRatio + x + 1.0f;
			if( g_renderer->GetHeight() <= top || bottom <= 0.0 || g_renderer->GetWidth() <= right || left <= 0.0f )
				continue;
		}

		isInsideScreen = true;

		RPSprite spr;
		if( m_alwaysTopLayer )
		{
			spr.oow = clipId * g_zOffset + 1.0f / 10.0f - g_zOffset * 20.0f + m_offsetOow * g_zOffset;
			spr.oowup = spr.oow;
		}
		else
		if( m_isLieOnGround )
		{
			spr.oow = 1.0f / (tv.z - (bottom - y) * g_shadowSlope) + ((m_offsetOow + clipId + 3) * g_zOffset) + zHover;
			spr.oowup = 1.0f / (tv.z - (top - y) * g_shadowSlope) + ((m_offsetOow + clipId + 3) * g_zOffset) + zHover;
		}
		else
		{
			spr.oow = 1.0f / ((bottom - y) * g_slope + tv.z) + ((m_offsetOow + clipId + 3) * g_zOffset) + zHover;
			spr.oowup = 1.0f / ((top - y) * g_slope + tv.z) + ((m_offsetOow + clipId + 3) * g_zOffset) + zHover;
		}

		COLOR argb;
		if( m_isSingleColor && m_colorOfSingleColor != 0xFFFF0000 )
		{
			argb.color = m_colorOfSingleColor;
		}
		else
		{
			argb.a = (unsigned char)int(sprClip->a * m_fA * (1/255.0f));
			argb.r = (unsigned char)int(sprClip->r * m_fR * (1/255.0f));
			argb.g = (unsigned char)int(sprClip->g * m_fG * (1/255.0f));
			argb.b = (unsigned char)int(sprClip->b * m_fB * (1/255.0f));
		}

		spr.top = top;
		spr.bottom = bottom;
		spr.spr = sprImg;
		spr.left = left + fSprShift;
		spr.right = right + fSprShift;
		spr.rgba = argb.color;
		spr.angle = float(m_sprAngle + sprClip->angle);
		if( m_shouldAddPickInfo )
			info.RENDER_INFO_RECT::Update(spr);
		unsigned long* pal = m_sprRes->m_pal;
		if( m_bodyPalette )
			pal = ((CPaletteRes*)g_resMgr().CResMgr::Get(m_bodyPaletteName.c_str()))->m_pal;
		int renderFlag = 0x101;
		if( argb.a < 0xFF )
			renderFlag = 0x1;
		if( (m_BodyLight & 1) == 1 )
			renderFlag = 0x5;
		if( (m_BodyLight & 8) == 8 )
		{
			m_BodySin += 1;
			if( m_BodySin > 180 )
				m_BodySin = 0;

			RPSprite spr2;
			spr2.right = spr.right;
			spr2.top = spr.top - (g_sinTable[m_BodySin] * 1.5f + 5.0f);
			spr2.bottom = spr.bottom + (g_sinTable[m_BodySin] * 1.5f + 5.0f);
			if( spr.left <= spr.right ) //TODO: recheck comparison
			{
				spr2.left = spr.left - (g_sinTable[m_BodySin] * 1.5f + 5.0f);
				spr2.right = spr.right + (g_sinTable[m_BodySin] * 1.5f + 5.0f);
			}
			else
			{
				spr2.left = spr.left + (g_sinTable[m_BodySin] * 1.5f + 5.0f);
				spr2.right = spr.right - (g_sinTable[m_BodySin] * 1.5f + 5.0f);
			}
			spr2.spr = spr.spr;
			spr2.oowup = spr.oowup;
			spr2.oow = spr.oow - (1/20000.0f);
			spr2.rgba = spr.rgba;
			spr2.angle = spr.angle;
			this->CRenderObject::RenderSprite(spr2, pal, 5);
		}

		this->CRenderObject::RenderSprite(spr, pal, renderFlag);
	}

	if( isInsideScreen )
		this->SetRenderInfo(info, x, y);
	else
		this->SetTlvert(x, y);
}


void CRenderObject::RenderShadow(matrix& vtm, float zoom) // line 735-785
{
	if( !m_shadowOn || m_shadowZoom == 0.0f || zoom == 0.0f )
		return;

	vector3d pos;
	pos.x = m_pos.x;
	pos.y = g_modeMgr.CModeMgr::GetGameMode()->GetWorld()->m_attr->C3dAttr::GetHeight(m_pos.x, m_pos.z);
	pos.z = m_pos.z;

	vector3d tv;  tv.z = pos.x * vtm.v13 + pos.y * vtm.v23 + pos.z * vtm.v33 + vtm.v43;
	float x, y, oow;  g_renderer->CRenderer::ProjectVertex(pos, vtm, &x, &y, &oow);
	float pixelRatio = g_renderer->CRenderer::GetPixelRatio(oow);
	CSprRes* sprRes = (CSprRes*)g_resMgr().CResMgr::Get("shadow.spr");
	CSprClip* sprClip = ((CActRes*)g_resMgr().CResMgr::Get("shadow.act"))->CActRes::GetMotion(0, 0)->GetClip(0);
	SprImg* sprImg = sprRes->m_sprites[sprClip->clipType][0];

	float top = sprClip->y * sprClip->zoomy * (zoom * m_shadowZoom) * pixelRatio + y;
	float bottom = (zoom * m_shadowZoom) * ((sprClip->y + sprImg->height * (sprImg->isHalfH + 1)) * sprClip->zoomy) * pixelRatio + y + 1.0f;
	float left = (sprClip->zoomx * sprClip->x) * (zoom * m_shadowZoom) * pixelRatio + x;
	float right = (zoom * m_shadowZoom) * (sprClip->x + sprImg->width * (sprImg->isHalfW + 1)) * sprClip->zoomx * pixelRatio + x + 1.0f;
	if( g_renderer->CRenderer::GetHeight() <= top || bottom <= 0.0f || g_renderer->CRenderer::GetWidth() <= left || right <= 0.0f )
		return;

	RPSprite spr;
	spr.spr = sprImg;
	spr.left = left + m_sprShift;
	spr.top = top;
	spr.bottom = bottom;
	spr.rgba = (unsigned int)((((((int(sprClip->a) << 8) + int(sprClip->r)) << 8) + int(sprClip->g)) << 8) + int(sprClip->b));
	spr.right = m_sprShift + right;
	spr.oow = 1.0f / (tv.z - (bottom - y) * g_shadowSlope) + (1/100000.0f);
	spr.oowup = 1.0f / (tv.z - (top - y) * g_shadowSlope) + (1/100000.0f);
	spr.angle = (float)sprClip->angle;
	this->CRenderObject::RenderSprite(spr, sprRes->m_pal, 0x101);
}


void CRenderObject::RenderSprite(const RPSprite& spr, unsigned long* pal, int renderFlag) // line 788-888
{
	SprImg* img = spr.spr;
	CTexture* tex = img->tex;

	CacheInfo info = {};
	if( tex != NULL )
	{
		info.tu = 0.0f;
		info.tv = 0.0f;
		info.tu1 = tex->CTexture::GetUAdjust(); // inlined
		info.tv1 = tex->CTexture::GetVAdjust(); // inlined
	}
	else
	{
		tex = g_renderer->CRenderer::GetSpriteIndex(*img, (unsigned long)pal, &info);
		if( tex == NULL )
			tex = g_renderer->CRenderer::AddSpriteIndex(*img, pal, &info);
	}

	float z = GetZFromOow(spr.oow);
	float z1 = GetZFromOow(spr.oowup);

	RPQuadFace& quadFace = g_renderer->CRenderer::BorrowQuadRP();
	quadFace.tex = tex;
	if( spr.angle == 0 )
	{
		quadFace.verts[0].x = spr.left  + 0.5f; quadFace.verts[0].y = spr.top    + 0.5f;
		quadFace.verts[1].x = spr.right + 0.5f; quadFace.verts[1].y = spr.top    + 0.5f;
		quadFace.verts[2].x = spr.left  + 0.5f; quadFace.verts[2].y = spr.bottom + 0.5f;
		quadFace.verts[3].x = spr.right + 0.5f; quadFace.verts[3].y = spr.bottom + 0.5f;
	}
	else
	{
		float fCos = GetCos((int)spr.angle);
		float fSin = GetSin((int)spr.angle);
		float w = (spr.right - spr.left) / 2;
		float h = (spr.bottom - spr.top) / 2;
		float x = w + spr.left;
		float y = h + spr.top;

		float x1cs = -w * fCos;
		float x1sn = -w * fSin;
		float x2cs = w * fCos;
		float x2sn = w * fSin;
		float y1cs = -h * fCos;
		float y1sn = -h * fSin;
		float y2cs = h * fCos;
		float y2sn = h * fSin;

		quadFace.verts[0].x = x1cs - y1sn + x + 0.5f;
		quadFace.verts[0].y = y1cs + x1sn + y + 0.5f;
		quadFace.verts[1].x = x2cs - y1sn + x + 0.5f;
		quadFace.verts[1].y = y1cs + x2sn + y + 0.5f;
		quadFace.verts[2].x = x1cs - y2sn + x + 0.5f;
		quadFace.verts[2].y = y2cs + x1sn + y + 0.5f;
		quadFace.verts[3].x = x2cs - y2sn + x + 0.5f;
		quadFace.verts[3].y = y2cs + x2sn + y + 0.5f;
	}

	quadFace.verts[0].oow = spr.oowup; quadFace.verts[0].z = z1; quadFace.verts[0].tu = info.tu;  quadFace.verts[0].tv = info.tv;  quadFace.verts[0].color = spr.rgba;
	quadFace.verts[1].oow = spr.oowup; quadFace.verts[1].z = z1; quadFace.verts[1].tu = info.tu1; quadFace.verts[1].tv = info.tv;  quadFace.verts[1].color = spr.rgba;
	quadFace.verts[2].oow = spr.oow;   quadFace.verts[2].z = z;  quadFace.verts[2].tu = info.tu;  quadFace.verts[2].tv = info.tv1; quadFace.verts[2].color = spr.rgba;
	quadFace.verts[3].oow = spr.oow;   quadFace.verts[3].z = z;  quadFace.verts[3].tu = info.tu1; quadFace.verts[3].tv = info.tv1; quadFace.verts[3].color = spr.rgba;

	quadFace.srcAlphaMode = D3DBLEND_SRCALPHA;
	quadFace.destAlphaMode = ( renderFlag == D3DBLEND_SRCALPHA ) ? D3DBLEND_ONE : D3DBLEND_INVSRCALPHA;

	g_renderer->CRenderer::AddRP(&quadFace, renderFlag);
}


void CRenderObject::SetRenderInfo(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY) // line 891-893
{
}


void CRenderObject::SetTlvert(float tlvertX, float tlvertY) // line 896-899
{
	m_lastTlvertX = (int)tlvertX;
	m_lastTlvertY = (int)tlvertY;
}


void CRenderObject::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3) // line 519-525
{
	switch( message )
	{
	default:
		return this->CGameObject::SendMsg(sender, message, arg1, arg2, arg3);
	break;
	};
}


void CRenderObject::SetAction(int action, int speed, int type) // line 499-516
{
	m_motionSpeed = m_actRes->CActRes::GetDelay(action);
	if( m_motionSpeed < 1.0 )
		m_motionSpeed = 1.0;
	m_baseAction = action;
	m_curAction = action;
	m_curMotion = 0;
	m_motionType = type;
	m_motionSpeed = m_modifyFactorOfmotionSpeed * m_motionSpeed;
	m_isMotionFinished = false;
	m_loopCountOfmotionFinish = 1.0;
	m_modifyFactorOfmotionSpeed = 1.0;
	m_isForceState = 0;
}


float CRenderObject::CalcDist(float x, float z) // line 234-239
{
	float dx = x - m_pos.x;
	float dy = z - m_pos.z;

	return _sqrt(dx * dx + dy * dy);
}


float CRenderObject::CalcDist(float x, float y, float z) // line 242-249
{
	float dx = x - m_pos.x;
	float dy = y - m_pos.y;
	float dz = z - m_pos.z;

	float sq = _sqrt(dz * dz + dx * dx);
	return _sqrt(sq * sq + dy * dy); //NOTE: identical to _sqrt(dx*dx + dy*dy + dz*dz)
}


void CRenderObject::CalcDir(float x, float z) // line 252-260
{
	m_roty = (float)(atan2(-(z - m_pos.z), (x - m_pos.x)) / M_PI * 180.0);

	if( m_roty >= 360.0f )
		m_roty -= 360.0f;

	if( m_roty < 0.0f )
		m_roty += 360.0f;
}


float CRenderObject::CalcDir(float sx, float sz, float x, float z) // line 263-272
{
	float result;

	result = (float)(atan2(-(z - sz), (x - sx)) / M_PI * 180.0);

	if( result >= 360.0f )
		result -= 360.0f;

	if( result < 0.0f )
		result += 360.0f;

	return result;
}


void CRenderObject::ModifyArgb(int a, int r, int g, int b) // line 275-291
{
	m_sprColor.a = ( a + m_sprColor.a < 255 ) ? a + m_sprColor.a : 255;
	m_sprColor.r = ( r + m_sprColor.r < 255 ) ? r + m_sprColor.r : 255;
	m_sprColor.g = ( g + m_sprColor.g < 255 ) ? g + m_sprColor.g : 255;
	m_sprColor.b = ( b + m_sprColor.b < 255 ) ? b + m_sprColor.b : 255;
}


void CRenderObject::SetArgb(int a, int r, int g, int b) // line 294-299
{
	if( a != -1 ) m_sprColor.a = (BYTE)a;
	if( r != -1 ) m_sprColor.r = (BYTE)r;
	if( g != -1 ) m_sprColor.g = (BYTE)g;
	if( b != -1 ) m_sprColor.b = (BYTE)b;
}


bool CRenderObject::GetTargetPos(unsigned long targetGid, vector3d& tPos) // line 302-318
{
	if( targetGid == g_session.GetAid() )
	{
		tPos = g_modeMgr.CModeMgr::GetGameMode()->CGameMode::GetWorld()->m_player->m_pos;
		return true;
	}

	CGameActor* target = g_modeMgr.CModeMgr::GetGameMode()->CGameMode::GetWorld()->CWorld::GetGameActorByAID(targetGid);
	if( target != NULL )
	{
		tPos = target->m_pos;
		return true;
	}

	vector3d& playerPos = g_modeMgr.CModeMgr::GetGameMode()->CGameMode::GetWorld()->m_player->m_pos;
	tPos.x = m_pos.x - (playerPos.x - m_pos.x);
	tPos.y = m_pos.y - (playerPos.y - m_pos.y);
	tPos.z = m_pos.z - (playerPos.z - m_pos.z);
	return false;
}


float CRenderObject::GetLastPixelRatio()
{
	return m_lastPixelRatio;
}


int CRenderObject::GetLastTlvertX()
{
	return m_lastTlvertX;
}


int CRenderObject::GetLastTlvertY()
{
	return m_lastTlvertY;
}


void CRenderObject::ProcessMotion() // line 321-440
{
	m_curAction = this->Get8Dir(m_roty) + m_baseAction;
	g_modeMgr.CModeMgr::GetGameMode(); //NOTE: nop call
	float stateCnt = timeGetTime() - m_stateStartTick * (1/24.0f);

	if( m_actRes == NULL )
		return;

	if( m_isForceState )
	{
		if( m_isForceAnimFinish )
		{
			m_baseAction = m_forceFinishedAct;
			m_curMotion = m_forceFinishedMot;
			m_curAction = m_forceFinishedAct + this->Get8Dir(m_roty);
			if( !m_forceStateEndTick )
			{
				m_isForceState = 0;
				m_motionType = 1;
			}
		}
		else
		{
			m_baseAction = m_forceAct;
			m_curAction = m_forceAct + this->Get8Dir(m_roty);
			m_curMotion = m_forceMot;
		}

		if( m_isForceAnimation )
		{
			timeGetTime(); // NOTE: nop call
			if( timeGetTime() >= m_forceStateEndTick )
			{
				m_isForceState = 0;
				m_forceStateEndTick = 0;
				m_motionType = 1;
				m_isMotionFinished = 1;
			}

			if( !m_isForceAnimFinish && !(m_forceStateCnt % m_forceAnimSpeed) )
			{
				if( m_isForceAnimLoop && !m_forceFinishedAct && m_forceFinishedMot )
				{
					m_forceFinishedMot = 0;
					m_forceMot = m_forceMot - 1;
				}
				else
				{
					m_forceMot = m_forceMot + 1;
				}
			}

			unsigned char maxMotion = m_forceMaxMot;
			if( m_forceMot > maxMotion )
			{
				if( m_isForceAnimLoop )
				{
					if( !m_forceFinishedAct )
					{
						m_forceMot = m_forceStartMot + 1;
						m_forceFinishedMot = 1;
						m_forceStateCnt = m_forceStateCnt + 1;
						return;
					}

					maxMotion = m_forceStartMot;
				}
				else
				{
					m_isForceAnimFinish = 1;
				}

				m_forceMot = maxMotion;
			}

			++m_forceStateCnt;
		}
	}
	else
	if( m_isMotionFinished || m_isMotionFreezed )
	{
		if( m_curMotion > m_actRes->CActRes::GetMotionCount(m_curAction) - 1 )
			m_curMotion = m_actRes->CActRes::GetMotionCount(m_curAction) - 1;
	}
	else
	{
		if( m_motionType == 0 )
		{
			m_curMotion = int(stateCnt / m_motionSpeed) % m_actRes->CActRes::GetMotionCount(m_curAction);
		}
		else
		if( m_motionType == 1 )
		{
			m_curMotion = int(stateCnt / m_motionSpeed) % m_actRes->CActRes::GetMotionCount(m_curAction);
			if( (stateCnt / m_motionSpeed) / m_actRes->CActRes::GetMotionCount(m_curAction) >= 1.0f )
			{
				m_curMotion = m_actRes->CActRes::GetMotionCount(m_curAction) - 1;
				if( (stateCnt / m_motionSpeed) / m_actRes->CActRes::GetMotionCount(m_curAction) >= m_loopCountOfmotionFinish )
					m_isMotionFinished = true;
			}
		}
	}
}


void CRenderObject::ProcessSound() // line 443-496
{
	if( (m_oldMotion != m_curMotion) || (m_oldBaseAction != m_baseAction) )
	{
		if( m_oldBaseAction != m_baseAction )
			m_oldMotion = 0;

		if( m_curMotion > m_oldMotion ) // normal
		{
			for( int motionId = m_oldMotion + 1; motionId <= m_curMotion; ++motionId ) // from old to current
			{
				int eventId = m_actRes->CActRes::GetMotion(m_curAction, motionId)->m_eventId;
				if( eventId == -1 )
					continue;

				mystd::string eventName = m_actRes->CActRes::GetEventName(eventId);
				if( eventName.find(".wav") == mystd::string::npos )
					continue;

				vector3d& playerPos = g_modeMgr.CModeMgr::GetGameMode()->CGameMode::GetWorld()->m_player->m_pos;
				PlayWave(eventName.c_str(), m_pos.x - playerPos.x, 0, m_pos.z - playerPos.z, 250, 40, 1.0f);
			}
		}
		else
		if( m_curMotion < m_oldMotion ) // loop
		{
			int motioncount = m_actRes->CActRes::GetMotionCount(m_curAction);
			if( m_oldMotion >= motioncount )
				m_oldMotion = motioncount - 1;

			for( int motionId = m_oldMotion + 1; motionId < motioncount; ++motionId ) // from old to end of action
			{
				int eventId = m_actRes->CActRes::GetMotion(m_curAction, motionId)->m_eventId;
				if( eventId == -1 )
					continue;

				mystd::string eventName = m_actRes->CActRes::GetEventName(eventId);
				if( eventName.find(".wav") == mystd::string::npos )
					continue;

				vector3d* playerPos = &g_modeMgr.CModeMgr::GetGameMode()->CGameMode::GetWorld()->m_player->m_pos;
				PlayWave(eventName.c_str(), m_pos.x - playerPos->x, 0.0f, m_pos.z - playerPos->z, 250, 40, 1.0f);
			}

			if( m_curMotion >= 0 )
			{
				for( int motionId = 0; motionId <= m_curMotion; ++motionId ) // from start to current
				{
					int eventId = m_actRes->CActRes::GetMotion(m_curAction, motionId)->m_eventId;
					if( eventId == -1 )
						continue;

					mystd::string eventName = m_actRes->CActRes::GetEventName(eventId);
					if( eventName.find(".wav") == mystd::string::npos )
						continue;

					vector3d* playerPos = &g_modeMgr.CModeMgr::GetGameMode()->CGameMode::GetWorld()->m_player->m_pos;
					PlayWave(eventName.c_str(), m_pos.x - playerPos->x, 0.0f, m_pos.z - playerPos->z, 250, 40, 1.0f);
				}
			}
		}
	}

	m_oldBaseAction = m_baseAction;
	m_oldMotion = m_curMotion;
}


void CRenderObject::SetLmIntensity(float& lmRIntensity, float& lmGIntensity, float& lmBIntensity) // line 528-541
{
	if( !g_isLightMap )
		return;

	CGameMode* gamemode = g_modeMgr.CModeMgr::GetGameMode();
	C3dGround* ground = gamemode->GetWorld()->m_ground;

	if( ground->IsNewVer() )
	{
		int sx, sy;
		gamemode->CGameMode::GetServerCoor(m_pos.x, m_pos.z, sx, sy);
		ground->GetLmIntensityFloatRGBByGatCoor(sx, sy, lmRIntensity, lmGIntensity, lmBIntensity);
	}
}


void CRenderObject::SetForceAnimSpeed(unsigned char speed) // line 4062-4064
{
	m_forceAnimSpeed = speed;
}


void CRenderObject::SetForceAnimEndTick(unsigned long tick) // line 4057-4059
{
	m_forceStateEndTick = tick + timeGetTime();
}


void CRenderObject::SetForceAnimation(int act, int mot, int maxMot, int finishAct, int finishMot, int isAnim, unsigned long endTick, int isLoop) // line 4037-4054
{
	m_forceAct = act;
	m_forceMot = mot;
	m_forceStartMot = mot;
	m_forceMaxMot = maxMot;
	m_forceFinishedMot = finishMot;
	m_forceAct = act;
	m_forceMot = mot;
	m_forceStartMot = mot;
	m_forceMaxMot = maxMot;
	m_forceFinishedMot = finishMot;
	m_isForceAnimLoop = isLoop;
	m_forceFinishedAct = finishAct;
	m_isForceAnimation = isAnim;
	m_isForceAnimFinish = 0;
	m_isForceState = 1;
	m_forceStateCnt = 1;
	m_forceStateEndTick = ( isAnim ) ? endTick + timeGetTime() : 0;
}


void CRenderObject::SetSprName(const char* sprName) // line 910-918
{
	if( m_sprRes != NULL )
		m_sprRes->CRes::Unlock();

	m_sprRes = (CSprRes*)g_resMgr().CResMgr::Get(sprName);

	if( m_sprRes != NULL )
		m_sprRes->CRes::Lock();
}


const char* CRenderObject::GetSprName() // line 921-924
{
	return ( m_sprRes != NULL ) ? m_sprRes->CRes::GetName() : NULL;
}


CSprRes* CRenderObject::GetSprRes() // line 927-929
{
	return m_sprRes;
}


void CRenderObject::SetActName(const char* actName) // line 932-940
{
	if( m_actRes != NULL )
		m_actRes->CRes::Unlock();

	m_actRes = (CActRes*)g_resMgr().CResMgr::Get(actName);
	m_actRes->CRes::Lock();
}


const char* CRenderObject::GetActName() // line 948-951
{
	return ( m_actRes != NULL ) ? m_actRes->CRes::GetName() : NULL;
}


CActRes* CRenderObject::GetActRes() // line 943-945
{
	return m_actRes;
}


//////////////////////////////////////////////////


CMousePointer::CMousePointer() // line 957-959
{
	this->CMousePointer::OnInit(); //inlined
}


CMousePointer::~CMousePointer() // line 962-964
{
	this->CMousePointer::OnExit(); //inlined
}


void CMousePointer::OnInit() // line 967-975
{
	m_visibleTime = 0;
	m_alwaysTopLayer = true;
	m_isVisible = false;
	m_stateStartTick = timeGetTime();

	this->CRenderObject::SetSprName("cursors.spr");
	this->CRenderObject::SetActName("cursors.act");
	this->SetAction(3, 2, 0);
}


void CMousePointer::OnExit() // line 978-979
{
}


void CMousePointer::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3) // line 998-1029
{
	switch( message )
	{
	case 1:// set position and color
	{
		float* data = (float*)arg1;//TODO: recheck type when calling this message
		m_pos.x = data[0];
		m_pos.z = data[1];
		m_isVisible = true;
		m_pos.y = g_modeMgr.CModeMgr::GetGameMode()->GetWorld()->m_attr->C3dAttr::GetHeight(m_pos.x, m_pos.z);
		if( arg2 )
			m_sprArgb = 0xFFFF0000;
		else
			m_sprArgb = 0xFFFFFFFF;
	}
	break;
	case 2:// set visible time
	{
		if( arg1 )
			m_visibleTime = arg1;
		else
			m_isVisible = false;
	}
	break;
	default:
	{
	}
	break;
	};
}


bool CMousePointer::OnProcess() // line 982-995
{
	m_curAction = m_baseAction;
	m_curMotion = int((timeGetTime() - m_stateStartTick) * (1/24.0f) / m_motionSpeed) % this->CRenderObject::GetActRes()->CActRes::GetMotionCount(m_baseAction);

	if( m_visibleTime != 0 )
	{
		--m_visibleTime;
		if( m_visibleTime == 0 )
			m_isVisible = false;
	}

	return true;
}


//////////////////////////////////////////////////


CAbleToMakeEffect::CAbleToMakeEffect() // line 1034-1036
{
	this->CAbleToMakeEffect::OnInit(); // inlined
}


CAbleToMakeEffect::~CAbleToMakeEffect() // line 1039-1041
{
	this->CAbleToMakeEffect::OnExit();
}


void CAbleToMakeEffect::OnInit() // line 1044-1051
{
	m_efId = -1;
	m_Sk_Level = 0;
	m_isLoop = 0;
	m_beginSpellEffect = NULL;
	m_magicTargetEffect = NULL;
}


void CAbleToMakeEffect::OnExit() // line 1054-1083
{
	if( m_effectList.size() != 0 )
	{
		for( mystd::list<CRagEffect*>::iterator it = m_effectList.begin(); it != m_effectList.end(); ++it )
		{
			CRagEffect* effect = *it;
			if( effect == NULL )
				continue;

			effect->SendMsg(this, 24, 0, 0, 0);
		}

		m_effectList.clear();
	}

	m_beginSpellEffect = NULL;
	m_magicTargetEffect = NULL;
}


void CAbleToMakeEffect::SendMsg(CGameObject* sender, int msgid, int val1, int val2, int val3) // line 1156-1267
{
	switch( msgid )
	{
	case 86:
	{
		if( m_magicTargetEffect == NULL )
			m_magicTargetEffect = this->CAbleToMakeEffect::LaunchEffect(val1, vector3d(0.,0.,0.), 0.0);

		if( m_magicTargetEffect != NULL )
			m_magicTargetEffect->SendMsg(NULL, 80, val2, 0, 0);
	}
	break;
	case 87:
	{
		if( m_magicTargetEffect == NULL )
			break;

		mystd::list<CRagEffect*>::iterator it;

		for( it = m_effectList.begin(); it != m_effectList.end(); ++it )
			if( *it == m_magicTargetEffect )
				break;

		if( it != m_effectList.end() )
		{
			(*it)->SendMsg(this, 24, 0, 0, 0);
			m_effectList.erase(it);
		}

		m_magicTargetEffect = NULL;
	}
	break;
	case 85:
	{
		if( m_beginSpellEffect == NULL )
			m_beginSpellEffect = this->CAbleToMakeEffect::LaunchEffect(val1, vector3d(0.,0.,0.), 0.0);

		if( m_beginSpellEffect != NULL )
		{
			if( val1 > 0 )
			{
				this->SendMsg(NULL, 109, val1, 0, 0);
				m_beginSpellEffect = this->CAbleToMakeEffect::LaunchEffect(val1, vector3d(0.,0.,0.), 0.0);
			}

			m_beginSpellEffect->SendMsg(NULL, 80, val2, 0, 0);
		}
	}
	break;
	case 84:
	{
		if( m_beginSpellEffect == NULL )
			break;

		mystd::list<CRagEffect*>::iterator it;

		for( it = m_effectList.begin(); it != m_effectList.end(); ++it )
			if( *it == m_beginSpellEffect )
				break;

		if( it != m_effectList.end() )
		{
			(*it)->SendMsg(this, 24, 0, 0, 0);
			m_effectList.erase(it);
		}

		m_beginSpellEffect = NULL;
	}
	break;
	case 23:
	{
		if( sender == NULL )
			break;

		mystd::list<CRagEffect*>::iterator it;

		for( it = m_effectList.begin(); it != m_effectList.end(); ++it )
			if( *it == sender )
				break;

		if( it != m_effectList.end() )
		{
			m_effectList.erase(it);

			if( m_beginSpellEffect == sender )
				m_beginSpellEffect = NULL;
			else
			if( m_magicTargetEffect == sender )
				m_magicTargetEffect = NULL;
		}
	}
	break;
	case 109:
	{
		for( mystd::list<CRagEffect*>::iterator it = m_effectList.begin(); it != m_effectList.end(); ++it )
		{
			if( *it == NULL )
			{
				it = m_effectList.erase(it);
				continue;
			}

			if( (*it)->CRagEffect::GetType() != val1 )
				continue;

			(*it)->SendMsg(this, 24, 0, 0, 0);
			m_effectList.erase(it);
			break;
		}
	}
	break;
	case 120:
	{
		for( mystd::list<CRagEffect*>::iterator it = m_effectList.begin(); it != m_effectList.end(); ++it )
		{
			if( *it == NULL )
			{
				it = m_effectList.erase(it);
				continue;
			}

			if( (*it)->CRagEffect::GetType() != *(DWORD*)val1 )
				continue;

			*(DWORD*)val1 = -1;
			break;
		}
	}
	break;
	default:
	{
		return this->CRenderObject::SendMsg(sender, msgid, val1, val2, val3);
	}
	break;
	};
}


CRagEffect* CAbleToMakeEffect::LaunchEffect(int effectId, vector3d fDeltaPos, float fRot) // line 1088-1141
{
	CAbleToMakeEffect* master = this;
	int isAlwaysShow = 0;

	switch( effectId )
	{
	case 35:
	case 36:
	case 60:
	case 114:
	case 137:
	case 138:
	case 154:
	case 155:
	case 159:
	case 160:
	case 164:
	case 295:
	case 296:
	case 334:
	case 338:
	case 357:
	case 371:
		isAlwaysShow = 1;
	break;
	case 127:
		m_isLoop = 1;
	break;
	default:
	break;
	};

	if( !(g_session.m_isEffectOn && effectId >= 0 && effectId <= 60000) && !isAlwaysShow )
		return NULL;

	// insert effectId to front of array and shift the rest to the right
	int buf[32];
	buf[0] = effectId;
	memcpy(&buf[1], g_recentEffectId, 31); //FIXME: they forgot to multiply 31 by sizeof(int)
	memcpy(g_recentEffectId, buf, 32); //FIXME: they forgot to multiply 32 by sizeof(int)

	float fSin = GetSin((int)fRot);
	float fCos = GetCos((int)fRot);
	fDeltaPos.x = fDeltaPos.x * fCos - fDeltaPos.z * fSin;
	fDeltaPos.z = fDeltaPos.z * fCos + fDeltaPos.x * fSin;

	CRagEffect* effect = new CRagEffect();
	effect->CRagEffect::Init(master, effectId, fDeltaPos);

	g_modeMgr.CModeMgr::GetGameMode()->GetWorld()->m_gameObjectList.push_back(effect);
	master->m_effectList.push_back(effect);

	return effect;
}


bool CAbleToMakeEffect::IsExistEffect(CRagEffect* pEffect) // line 1144-1153
{
	for( mystd::list<CRagEffect*>::const_iterator it = m_effectList.begin(); it != m_effectList.end(); ++it )
		if( *it == pEffect )
			return true;

	return false;
}


int CAbleToMakeEffect::IsEffectExist(int EffectId) // line 1270-1280
{
	for( mystd::list<CRagEffect*>::const_iterator it = m_effectList.begin(); it != m_effectList.end(); ++it )
		if( (*it)->CRagEffect::GetType() == EffectId )
			return true;

	return false;
}


//////////////////////////////////////////////////


CGameActor::CGameActor() // line 1284-1286
{
	this->CGameActor::OnInit();
}


CGameActor::~CGameActor() // line 1289-1291
{
	this->CGameActor::OnExit();
}


void CGameActor::OnInit() // line 1294-1367
{
	m_pkEffect = NULL;
	m_iceEffect = NULL;
	m_cartEffect = NULL;
	m_birdEffect = NULL;
	m_stunEffect = NULL;
	m_curseEffect = NULL;
	m_sleepEffect = NULL;
	m_crusisEffect = NULL;
	m_silenceEffect = NULL;
	m_angelusEffect = NULL;
	m_chatProhibitEffect = NULL;
	m_pos.x = 0.0;
	m_pos.y = 0.0;
	m_pos.z = 0.0;
	m_roty = 0.0;
	m_baseAction = 0;
	m_curAction = 0;
	m_curMotion = 0;
	m_stateId = 0;
	m_motionType = 0;
	m_motionSpeed = 1.0;
	m_shadowOn = true;
	m_accel.x = 0.0;
	m_accel.y = 0.0;
	m_accel.z = 0.0;
	m_dist = 0.0;
	m_gid = -1;
	m_lastServerTime = g_session.CSession::GetServerTime();
	m_lastProcessStateTime = timeGetTime();
	m_lastTlvertX = 0;
	m_lastTlvertY = 0;
	m_balloon = NULL;
	m_chatTitle = NULL;
	m_merchantShopTitle = NULL;
	m_skillRechargeGage = NULL;
	m_chatWidth = 0;
	m_nameWidth = 0;
	m_isMotionFinished = false;
	m_targetGid = 0;
	m_attackMotion = -1.0;
	m_pathStartCell = -1;
	m_shouldAddPickInfo = true;
	m_stateStartTick = timeGetTime();
	m_petEmotionStartTick = 0;
	m_skillRechargeEndTick = timeGetTime() - 5000;
	m_skillRechargeStartTick = timeGetTime() - 10000;
	m_effectLaunchCnt = 3600;
	m_sprArgb = -1;
	m_isVisible = true;
	m_alwaysTopLayer = false;
	m_willBeDead = 0;
	m_bodyState = 0;
	m_effectState = 0;
	m_healthState = 0;
	m_pkState = 0;
	m_vanishTime = 0;
	m_99 = 0;
	m_is99 = 0;
	m_isCounter = 0;
	m_isTrickDead = 0;
	m_isPlayHitWave = 0;
	memset(m_hitWaveName, 0, sizeof(m_hitWaveName));
	m_gdid = 0;
	m_freezeEndTick = 0;
	m_actorType = 0;
	m_emblemWnd = NULL;
	m_isNeverAnimation = false;
	m_colorEndTick = 0;
	m_isAsuraAttack = 0;
	m_isBladeStop = 0;
}


void CGameActor::OnExit() // line 1370-1395
{
	if( m_balloon != NULL )
	{
		g_windowMgr.UIWindowMgr::PostQuit(m_balloon);
		m_balloon = NULL;
	}

	if( m_chatTitle != NULL )
	{
		g_windowMgr.UIWindowMgr::PostQuit(m_chatTitle);
		m_chatTitle = NULL;
	}

	if( m_merchantShopTitle != NULL )
	{
		g_windowMgr.UIWindowMgr::PostQuit(m_merchantShopTitle);
		m_merchantShopTitle = NULL;
	}

	if( m_skillRechargeGage != NULL )
	{
		g_windowMgr.UIWindowMgr::PostQuit(m_skillRechargeGage);
		m_skillRechargeGage = NULL;
	}

	for( mystd::list<CMsgEffect*>::iterator it = m_msgEffectList.begin(); it != m_msgEffectList.end(); ++it )
		(*it)->SendMsg(NULL, 49, 0, 0, 0);
	m_msgEffectList.clear();

	this->CGameActor::DeleteEmblemWnd(); // inlined
}


hook_func<bool (CGameActor::*)()> CGameActor::_ProcessState(SAKEXE, "CGameActor::ProcessState");
bool CGameActor::ProcessState() // line 1862-2159
{
	return (this->*_ProcessState)();

	//TODO
}


hook_func<void (CGameActor::*)(CGameObject* sender, int message, int arg1, int arg2, int arg3)> CGameActor::_SendMsg(SAKEXE, "CGameActor::SendMsg");
void CGameActor::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3) // line 2299-3520
{
	return (this->*_SendMsg)(sender, message, arg1, arg2, arg3);

	CGameMode* gameMode = g_modeMgr.CModeMgr::GetGameMode();

	switch( message )
	{
	case 0:
		//TODO
	break;
	case AM_3_STANDENTRY_EXISTING:
	{
		STANDENTRYSTRUCT* entry = (STANDENTRYSTRUCT*)arg1;

		gameMode->CGameMode::GetClientCoor(entry->x, entry->y, m_pos.x, m_pos.z);
		m_pos.y = gameMode->CGameMode::GetWorld()->m_attr->C3dAttr::GetHeight(m_pos.x, m_pos.z);
		m_roty = float(45 * (entry->dir + 4));
		m_xSize = entry->xSize;
		m_ySize = entry->ySize;
		m_moveDestX = entry->x;
		m_moveDestY = entry->y;
		m_headType = entry->head;
		this->CGameActor::SetAttrState(entry->bodyState, entry->effectState, entry->healthState, false);
		this->SetState(STATEID_STAND);
		this->SetGuildInfo(entry->guildId, entry->guildEmblemVersion);
	}
	break;
	case AM_4_STANDENTRY_NEW:
	{
		STANDENTRYSTRUCT* entry = (STANDENTRYSTRUCT*)arg1;
		int flag = (int)arg2;

		m_gid = entry->GID;
		entry->job = this->CGameActor::GetProperJob(entry->job, entry->effectState); // inlined
		this->SetSprAct(entry->job, entry->sex);
		gameMode->CGameMode::GetClientCoor(entry->x, entry->y, m_pos.x, m_pos.z);
		m_pos.y = gameMode->CGameMode::GetWorld()->m_attr->C3dAttr::GetHeight(m_pos.x, m_pos.z);
		m_roty = float(45 * (entry->dir + 4));
		m_xSize = entry->xSize;
		m_ySize = entry->ySize;
		m_moveDestX = entry->x;
		m_moveDestY = entry->y;
		m_speed = entry->speed;
		m_headType = entry->head;
		this->CGameActor::SetAttrState(entry->bodyState, entry->effectState, entry->healthState, false);
		this->SetState(STATEID_STAND);
		this->CGameActor::SetPKState(entry->isPKModeON); // inlined

		if( entry->job == JT_GUILD_FLAG )
		{
			entry->guildId = entry->accessory3 | (entry->accessory2 << 16);
			entry->guildEmblemVersion = entry->shield;
			this->SetGuildInfo(entry->guildId, entry->guildEmblemVersion);
		}

		this->SetPropensityInfo(entry->honor, entry->virtue);

		if( flag == 1 )
		{
			m_sprArgb = 0x44FFFFFF;
		}
		else
		if( flag == 2 )
		{
			if( !IsEffectStateSpecialHiding(entry->effectState) )
				this->CAbleToMakeEffect::LaunchEffect(EF_ENTRY2, vector3d(0.,0.,0.), 0.0);
		}
	}
	break;
	case 5:
		//TODO
	break;
	case 6:
		//TODO
	break;
	case 7:
		//TODO
	break;
	case 11:
		//TODO
	break;
	case 12:
		//TODO
	break;
	case 19:
		//TODO
	break;
	case 20:
		//TODO
	break;
	case 21:
		//TODO
	break;
	case 26:
	case 39:
	case 93:
	case 94:
	case 111:
	{
		WBA& wba = *reinterpret_cast<WBA*>(arg1);

		unsigned long tGid = wba.targetGid;
		int effectId1 = wba.effectId1;
		int effectId2 = wba.effectId2;
		int damage = wba.damage;
		float attackedSpeedFactor = wba.attackedSpeedFactor;
		int level = wba.effectLevel;

		if( wba.tCellX == -1 || wba.tCellY == -1 )
		{
			m_damageDestX = m_pos.x;
			m_damageDestZ = m_pos.z;
		}
		else
		{
			gameMode->CGameMode::GetClientCoor(wba.tCellX, wba.tCellY, m_damageDestX, m_damageDestZ);
		}

		int tJob = this->CGameActor::GetJob();
		int tActorWeapon = -1;

		CGameActor* tActor;
		if( g_session.CSession::GetAid() == tGid )
			tActor = gameMode->CGameMode::GetWorld()->m_player;
		else
			tActor = gameMode->CGameMode::GetWorld()->CWorld::GetGameActorByAID(tGid);

		if( tActor != NULL )
		{
			tJob = tActor->CGameActor::GetJob();
			tActorWeapon = tActor->GetWeapon();
		}

		if( message == 94 )
			damage = 0;

		bool recoverDamage = false;
		if( damage < 0 )
		{
			damage = -damage;
			recoverDamage = true;
		}

		//TODO
	}
	break;
	case 27:
		//TODO
	break;
	case 28:
		//TODO
	break;
	case 32:
		//TODO
	break;
	case 33:
		//TODO
	break;
	case 36:
		//TODO
	break;
	case 37:
		//TODO
	break;
	case 38:
		//TODO
	break;
//	case 39:
//		//@see case 26:
//	break;
	case 43:
		//TODO
	break;
	case 48:
		//TODO
	break;
	case 51:
		//TODO
	break;
	case 52:
		//TODO
	break;
	case 54:
		//TODO
	break;
	case 55:
		//TODO
	break;
	case 56:
		//TODO
	break;
	case 57:
		//TODO
	break;
	case 58:
		//TODO
	break;
	case 59:
	case 107:
		//TODO
	break;
	case 61:
		//TODO
	break;
	case 62:
		//TODO
	break;
	case 63:
		//TODO
	break;
	case 67:
		//TODO
	break;
	case 68:
		//TODO
	break;
	case 69:
		//TODO
	break;
	case 70:
		//TODO
	break;
	case 71:
		//TODO
	break;
	case 72:
		//TODO
	break;
	case 73:
		//TODO
	break;
	case 74:
		//TODO
	break;
	case 75:
		//TODO
	break;
	case 76:
		//TODO
	break;
	case 78:
		//TODO
	break;
	case 79:
		//TODO
	break;
	case 81:
		//TODO
	break;
	case 82:
		//TODO
	break;
	case 83:
		//TODO
	break;
	case 88:
		//TODO
	break;
	case 89:
		//TODO
	break;
	case 92:
		//TODO
	break;
//	case 93:
//		//@see case 26:
//	break;
//	case 94:
//		//@see case 26:
//	break;
	case 95:
		//TODO
	break;
	case 96:
	case 97:
		//TODO
	break;
	case 98:
		//TODO
	break;
	case 99:
		//TODO
	break;
	case 101:
		//TODO
	break;
	case 102:
		//TODO
	break;
//	case 107:
//		//@see case 59:
//	break;
	case 108:
		//TODO
	break;
	case 110:
		//TODO
	break;
//	case 111:
//		//@see case 26:
//	break;
	case 118:
		if( m_chatProhibitEffect != NULL )
			gameMode->CGameMode::GetWorld()->CWorld::RemoveGameObject(m_chatProhibitEffect);
	break;
	case 125:
		//TODO
	break;
	case 126:
		this->CAbleToMakeEffect::LaunchEffect(EF_GUARD, vector3d(0,0,0), 0.0);
	break;
	case 127:
	{
		int r = (int)arg1;
		int g = (int)arg2;
		int b = (int)arg3;

		m_isSprArgbFixed = true;
		if( m_oldColor.a == 0 && m_oldColor.r == 0 && m_oldColor.g == 0 && m_oldColor.b == 0 )
		{
			m_oldColor.a = m_sprColor.a;
			m_oldColor.r = m_sprColor.r;
			m_oldColor.g = m_sprColor.g;
			m_oldColor.b = m_sprColor.b;
		}
		m_curColor.a = 0xFF;
		m_curColor.r = r;
		m_curColor.g = g;
		m_curColor.b = b;
		m_sprArgb = b << 0 | g << 8 | r << 16 || 0xFF << 24;
	}
	break;
	case 128:
		m_oldColor.a = 0;
		m_oldColor.r = 0;
		m_oldColor.g = 0;
		m_oldColor.b = 0;
		m_isSprArgbFixed = 0;
	break;
	default:
		this->CAbleToMakeEffect::SendMsg(sender, message, arg1, arg2, arg3);
	break;
	}
}


hook_func<void (CGameActor::*)(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY)> CGameActor::_SetRenderInfo(SAKEXE, "CGameActor::SetRenderInfo");
void CGameActor::SetRenderInfo(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY) // line 1442-1537
{
	return (this->*_SetRenderInfo)(info, tlvertX, tlvertY);

	//TODO
}


void CGameActor::SetState(int stateId) // line 1699-1830
{
	if( m_stateId == STATEID_DEAD || m_isTrickDead )
		return;

	CGameMode* mode = g_modeMgr.CModeMgr::GetGameMode();
	if( m_stateId == STATEID_FLINCH )
	{
		m_pos.x = m_damageDestX;
		m_pos.z = m_damageDestZ;
		m_pos.y = mode->CGameMode::GetWorld()->m_attr->C3dAttr::GetHeight(m_damageDestX, m_damageDestZ);
	}

	switch( stateId )
	{
	case STATEID_COUNTER:
		if( !g_session.CSession::IsPc(this->CGameActor::GetJob()) )
		{
			this->SetAction(16, 4, 1);
			m_isMotionFreezed = 1;
		}
		else
		if( g_session.CSession::IsSecondAttack(this->CGameActor::GetJob(), m_sex, this->GetWeapon()) )
		{
			this->SetAction(88, 4, 1);
			m_isMotionFreezed = 1;
		}
		else
		{
			this->SetAction(80, 4, 1);
			m_isMotionFreezed = 1;
		}
		return;
	break;
	case STATEID_FLINCH:
	{
		if( m_isForceState )
			return;

		CGameActor* target = ( m_targetGid == g_session.CSession::GetAid() ) ? mode->CGameMode::GetWorld()->m_player : mode->CGameMode::GetWorld()->CWorld::GetGameActorByAID(m_targetGid);
		if( target != NULL )
			target->SendMsg(NULL, 87, 0, 0, 0);
		this->SetAction(48, 5, 1);
		this->RegisterPos();
		return;
	}
	break;
	case STATEID_CASTEND:
		if( m_stateId == STATEID_SIT )
			return;
		this->SetAction(80, 3, 1);

		if( m_targetGid == g_session.CSession::GetAid() )
		{
			this->CRenderObject::CalcDir(mode->CGameMode::GetWorld()->m_player->m_pos.x, mode->CGameMode::GetWorld()->m_player->m_pos.z);
		}
		else
		{
			CGameActor* actor = mode->CGameMode::GetWorld()->CWorld::GetGameActorByAID(m_targetGid);
			if( actor != NULL )
				this->CRenderObject::CalcDir(actor->m_pos.x, actor->m_pos.z);
		}

		if( this->CGameActor::GetJob() == JT_ARCHER_GUARDIAN )
			this->CGameActor::MakeSpecialAttackEffect(m_targetGid, 28.0); //inlined

		m_attackMotion = (float)this->GetAttackMotion();
		this->RegisterPos();
	break;
	case STATEID_ATTACK:
	case STATEID_MULTIATTACK:
		if( stateId == STATEID_MULTIATTACK )
			this->SetAction(88, 3, 1);
		else
			this->SetAction(80, 3, 1);

		if( m_targetGid == g_session.CSession::GetAid() )
		{
			this->CRenderObject::CalcDir(mode->CGameMode::GetWorld()->m_player->m_pos.x, mode->CGameMode::GetWorld()->m_player->m_pos.z);
		}
		else
		{
			CGameActor* actor = mode->CGameMode::GetWorld()->CWorld::GetGameActorByAID(m_targetGid);
			if( actor != NULL )
				this->CRenderObject::CalcDir(actor->m_pos.x, actor->m_pos.z);
		}

		if( this->CGameActor::GetJob() == JT_ARCHER_GUARDIAN )
			this->CGameActor::MakeSpecialAttackEffect(m_targetGid, 28.0); //inlined

		m_attackMotion = (float)this->GetAttackMotion();
		this->RegisterPos();
	break;
	case STATEID_DEAD:
		m_isMotionFreezed = 0;
		if( m_bodyState == 2 )
		{
			this->SendMsg(NULL, 59, 0, 0, 0);
			this->SendMsg(NULL, 62, 0, 0, 0);
		}
		m_isLieOnGround = 1;
		m_isMotionFinished = 0;
		m_isMotionFreezed = 0;
		this->SetAction(64, 4, 1);
	break;
	case STATEID_STAND:
		this->SetAction(0, 4, 0);
		if( !IsEventAID(m_gid) )
			m_isMotionFinished = 1;
		this->RegisterPos();
	break;
	case STATEID_WALK:
		if( !m_isAsuraAttack )
			this->SetAction(8, 6, 0);
		this->UnRegisterPos();
	break;
	case STATEID_PICKUP:
		m_isCounter = 0;
		m_isMotionFreezed = 0;
		this->SetAction(24, 6, 1);
	break;
	case STATEID_11:
		this->SetAction(32, 6, 1);
	break;
	case STATEID_12:
		this->SetAction(40, 3, 1);
		this->RegisterPos();
	break;
	case STATEID_DANCE:
		m_forceAct = 96;
		m_forceFinishedAct = 0;
		m_forceFinishedMot = 0;
		m_forceAnimSpeed = 10;
		m_forceMot = 1;
		m_forceStartMot = 1;
		m_forceMaxMot = 3;
		m_isForceAnimLoop = 1;
		m_isForceAnimation = 1;
		m_isForceAnimFinish = 0;
		m_isForceState = 1;
		m_forceStateEndTick = timeGetTime() + 99999999;
		m_forceStateCnt = 1;
	break;
	case STATEID_SONG:
		m_forceAct = 96;
		m_forceFinishedAct = 96;
		m_forceFinishedMot = 1;
		m_forceAnimSpeed = 10;
		m_forceMot = 1;
		m_forceStartMot = 1;
		m_forceMaxMot = 3;
		m_isForceAnimLoop = 1;
		m_isForceAnimation = 1;
		m_isForceAnimFinish = 0;
		m_isForceState = 1;
		m_forceStateEndTick = timeGetTime() + 99999999;
		m_forceStateCnt = 1;
	break;
	case STATEID_18:
		m_forceAnimSpeed = 10;
		m_forceAct = 88;
		m_forceMot = 0;
		m_forceStartMot = 0;
		m_forceMaxMot = 0;
		m_forceFinishedAct = 88;
		m_forceFinishedMot = 0;
		m_isForceAnimLoop = 0;
		m_isForceAnimation = 1;
		m_isForceAnimFinish = 0;
		m_isForceState = 1;
		m_forceStateEndTick = timeGetTime() + 3000;
		m_forceStateCnt = 1;
	break;
	default:
	break;
	};

	m_stateId = stateId;
	m_curAction = m_baseAction + this->Get8Dir(m_roty);
	m_stateStartTick = timeGetTime();
}


void CGameActor::RegisterPos() // line 1574-1579
{
	CGameMode* gameMode = g_modeMgr.CModeMgr::GetGameMode();

	int sx, sy;
	gameMode->CGameMode::GetServerCoor(m_pos.x, m_pos.z, sx, sy);

	gameMode->SendMsg(MM_ADDREGISTERPOS, m_gid, sx, sy);
}


void CGameActor::UnRegisterPos() // line 1582-1585
{
	CGameMode* gameMode = g_modeMgr.CModeMgr::GetGameMode();
	gameMode->SendMsg(MM_DELETEREGISTERPOS, m_gid, 0, 0);
}


void CGameActor::SetAction(int action, int speed, int type) // line 1540-1544
{
	this->CRenderObject::SetAction(action, speed, type); // inlined
    m_isNeverAnimation = false;
    m_attackMotion = -1.0;
}


hook_func<int (CGameActor::*)(float rot)> CGameActor::_Get8Dir(SAKEXE, "CGameActor::Get8Dir");
int CGameActor::Get8Dir(float rot) // line 1398-1420
{
	return (this->*_Get8Dir)(rot);

	//TODO
}


void CGameActor::SetSprAct(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal) // line 536 (GameActor.h)
{
}


void CGameActor::SetSprAct2(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal, int effectState) // line 537 (GameActor.h)
{
}


void CGameActor::SetSprAct(int job, int sex) // line 538 (GameActor.h)
{
}


void CGameActor::SetSprJob(int job) // line 539 (GameActor.h)
{
}


void CGameActor::SetSprHead(int head) // line 530 (GameActor.h)
{
}


void CGameActor::SetSprJobDye(int job) // line 541 (GameActor.h)
{
}


void CGameActor::SetSprWeapon(int weapon) // line 542 (GameActor.h)
{
}


void CGameActor::SetSprWeapon2(int weapon) // line 543 (GameActor.h)
{
}


void CGameActor::SetSprAccessory(int accessory) // line 544 (GameActor.h)
{
}


void CGameActor::SetSprAccessory2(int accessory) // line 545 (GameActor.h)
{
}


void CGameActor::SetSprAccessory3(int accessory) // line 546 (GameActor.h)
{
}


void CGameActor::SetSprShield(int shield) // line 547 (GameActor.h)
{
}


void CGameActor::SetSprShoe(int shoe) // line 548 (GameActor.h)
{
}


void CGameActor::SetImfFileName() // line 549 (GameActor.h)
{
}


void CGameActor::SetHeadPaletteName() // line 550 (GameActor.h)
{
}


void CGameActor::SetBodyPaletteName() // line 551 (GameActor.h)
{
}


void CGameActor::SetBodyPalette(int bodyPalette) // line 552 (GameActor.h)
{
}


void CGameActor::SetHeadPalette(int headPalette) // line 553 (GameActor.h)
{
}


int CGameActor::GetWeapon() // line 554 (GameActor.h)
{
	return -1;
}


void CGameActor::ProcessMotionWithDist() // line 1597-1601
{
	int totalmot = int(1.48f / m_motionSpeed * m_dist);
	int motcount = this->CRenderObject::GetActRes()->CActRes::GetMotionCount(m_curAction);
	m_curMotion = totalmot % motcount;
}


hook_func<int (CGameActor::*)()> CGameActor::_GetAttackMotion(SAKEXE, "CGameActor::GetAttackMotion");
int CGameActor::GetAttackMotion() // line 1556-1571
{
	return (this->*_GetAttackMotion)();

	//TODO
}


void CGameActor::MakeCorpse() // line 2162-2166
{
	const char* sprName = this->CRenderObject::GetSprName(); // inlined
	const char* actName = this->CRenderObject::GetActName(); // inlined
	g_modeMgr.CModeMgr::GetGameMode()->CGameMode::MakeCorpse(m_pos.x, m_pos.y, m_pos.z, actName, sprName, m_baseAction, m_curMotion, m_roty);
}


void CGameActor::SetModifyFactorOfmotionSpeed(int attackMT) // line 48-52 (GameActorMsgHandler.cpp)
{
	if( attackMT > MAX_ATTACKMT )
		attackMT = MAX_ATTACKMT;

	m_modifyFactorOfmotionSpeed = (float)attackMT / (float)MAX_ATTACKMT;
}


void CGameActor::SetHonor(int honor) // line 559 (GameActor.h)
{
}


void CGameActor::SetPropensityInfo(int honor, int virtue) // line 560 (GameActor.h)
{
}


hook_func<bool (CGameActor::*)(int mssx, int mssy, int mscellX, int mscellY, int msdx, int msdy, int msspeed)> CGameActor::_FindPath(SAKEXE, "CGameActor::FindPath");
bool CGameActor::FindPath(int mssx, int mssy, int mscellX, int mscellY, int msdx, int msdy, int msspeed) // line 3523
{
	return (this->*_FindPath)(mssx, mssy, mscellX, mscellY, msdx, msdy, msspeed);

	//TODO
}


void CGameActor::ProcessWillBeAttacked(void) // line 2169-2181
{
	DWORD curTime = timeGetTime();

	for( mystd::list<WBA>::iterator it = m_willBeAttackedList.begin(); it != m_willBeAttackedList.end(); )
	{
		WBA& wba = *it;

		if( curTime >= wba.time )
		{
			this->SendMsg(NULL, wba.message, (int)&wba, 0, 0);
			it = m_willBeAttackedList.erase(it);
		}
		else
		{
			++it;
		}
	}
}


void CGameActor::MakeSpecialAttackEffect(unsigned long targetGid, float hideTime) // line 2184-2211
{
	switch( this->CGameActor::GetJob() )
	{
	case JT_MANDRAGORA:
	case JT_HYDRA:
		g_modeMgr.CModeMgr::GetGameMode()->CGameMode::MakeMandraAttackEffect(targetGid, this->CGameActor::GetJob(), 0.0);
	break;
	case JT_ARCHER_SKELETON:
	case JT_ORC_ARCHER:
	case JT_GARGOYLE:
	case JT_GOBLIN_ARCHER:
	case JT_RAYDRIC_ARCHER:
	case JT_KOBOLD_ARCHER:
	case JT_ARCHER_GUARDIAN:
	case JT_LIVE_PEACH_TREE:
	case JT_EVIL_CLOUD_HERMIT:
	case JT_STONE_SHOOTER:
	case JT_WOOTAN_SHOOTER:
	case JT_PARASITE:
		g_modeMgr.CModeMgr::GetGameMode()->CGameMode::MakeArrowEffect(m_pos, targetGid, hideTime, this->CGameActor::GetJob());
	break;
	default:
	break;
	};
}


unsigned long CGameActor::GetGID()
{
	return m_gid;
}


hook_func<void (CGameActor::*)()> CGameActor::_ProcessChatBalloon(SAKEXE, "CGameActor::ProcessChatBalloon");
void CGameActor::ProcessChatBalloon() // line 1605-1655
{
	return (this->*_ProcessChatBalloon)();

	//TODO
}


void CGameActor::SetJob(int job) // line 1658-1676
{
	m_job = job;

	switch( job )
	{
	case JT_CHICKEN:
		m_job = JT_KNIGHT;
	break;
	case JT_CHICKEN2:
		m_job = JT_CRUSADER;
	break;
	case JT_CHICKEN_H:
		m_job = JT_KNIGHT_H;
	break;
	case JT_CHICKEN_B:
		m_job = JT_KNIGHT_B;
	break;
	case JT_CHICKEN2_H:
		m_job = JT_CRUSADER_H;
	break;
	case JT_CHICKEN2_B:
		m_job = JT_CRUSADER_B;
	break;
	};

	this->SetSprJob(this->CGameActor::GetJob());
}


int CGameActor::GetJob() // line 1679-1695
{
	switch( m_job )
	{
	case JT_KNIGHT:
		if( IsEffectStateChicken(m_effectState) ) return JT_CHICKEN;
	break;
	case JT_CRUSADER:
		if( IsEffectStateChicken(m_effectState) ) return JT_CHICKEN2;
	break;
	case JT_KNIGHT_H:
		if( IsEffectStateChicken(m_effectState) ) return JT_CHICKEN_H;
	break;
	case JT_KNIGHT_B:
		if( IsEffectStateChicken(m_effectState) ) return JT_CHICKEN_B;
	break;
	case JT_CRUSADER_H:
		if( IsEffectStateChicken(m_effectState) ) return JT_CHICKEN2_H;
	break;
	case JT_CRUSADER_B:
		if( IsEffectStateChicken(m_effectState) ) return JT_CHICKEN2_B;
	break;
	};

	return m_job;
}


void CGameActor::SetSex(int sex)
{
	m_sex = sex & 1;
}


void CGameActor::SetPKState(int isPKModeON)
{
	m_pkState = isPKModeON;
}


hook_func<void (CGameActor::*)(int bodyState, int effectState, int healthState, bool changedNow)> CGameActor::_SetAttrState(SAKEXE, "CGameActor::SetAttrState");
void CGameActor::SetAttrState(int bodyState, int effectState, int healthState, bool changedNow) // line 3573-3940
{
	return (this->*_SetAttrState)(bodyState, effectState, healthState, changedNow);

	//TODO
}


hook_func<void (CGameActor::*)()> CGameActor::_ProcessEffectState(SAKEXE, "CGameActor::ProcessEffectState");
void CGameActor::ProcessEffectState() // line 3943-3994
{
	return (this->*_ProcessEffectState)();

	//TODO
}


void CGameActor::DeleteMatchingEffect(CMsgEffect* msgEffect) // line 2214-2238
{
	if( m_cartEffect == msgEffect )
		m_cartEffect = 0;
	else
	if( m_birdEffect == msgEffect )
		m_birdEffect = 0;
	else
	if( m_pkEffect == msgEffect )
		m_pkEffect = 0;
	else
	if( m_iceEffect == msgEffect )
		m_iceEffect = 0;
	else
	if( m_curseEffect == msgEffect )
		m_curseEffect = 0;
	else
	if( m_sleepEffect == msgEffect )
		m_sleepEffect = 0;
	else
	if( m_stunEffect == msgEffect )
		m_stunEffect = 0;
	else
	if( m_angelusEffect == msgEffect )
		m_angelusEffect = 0;
	else
	if( m_crusisEffect == msgEffect )
		m_crusisEffect = 0;
	else
	if( m_silenceEffect == msgEffect )
		m_silenceEffect = 0;
	else
	if( m_chatProhibitEffect == msgEffect )
		m_chatProhibitEffect = 0;
}


void CGameActor::ProcessBodyState() // line 3997-4008
{
	if( m_bodyState > BODYSTATE_NORMAL && m_bodyState <= BODYSTATE_FREEZING )
		m_isMotionFreezed = true;
}


void CGameActor::SetVanish() // line 1849-1859
{
	m_gid = -1;
	m_99 = 0;
	m_shadowOn = 0;
	m_vanishTime = timeGetTime() + 510;

	if( m_vanishTime == 0 )
		m_vanishTime = 1;
}


int CGameActor::GetProperJob(int job, int effectState) // line 2241-2255
{
	switch( job )
	{
	case JT_KNIGHT:
		if( IsEffectStateChicken(effectState) ) return JT_CHICKEN;
	break;
	case JT_CRUSADER:
		if( IsEffectStateChicken(effectState) ) return JT_CHICKEN2;
	break;
	case JT_KNIGHT_H:
		if( IsEffectStateChicken(effectState) ) return JT_CHICKEN_H;
	break;
	case JT_KNIGHT_B:
		if( IsEffectStateChicken(effectState) ) return JT_CHICKEN_B;
	break;
	case JT_CRUSADER_H:
		if( IsEffectStateChicken(effectState) ) return JT_CHICKEN2_H;
	break;
	case JT_CRUSADER_B:
		if( IsEffectStateChicken(effectState) ) return JT_CHICKEN2_B;
	break;
	};

	return job;
}


int CGameActor::GetBodyState() // line 585 (GameActor.h)
{
	return m_bodyState;
}


int CGameActor::GetEffectState() // line 586 (GameActor.h)
{
	return m_effectState;
}


void CGameActor::SetHeadType(int headType)
{
	m_headType = headType;
}


int CGameActor::GetHeadType()
{
	return m_headType;
}


int CGameActor::GetActorType()
{
	return m_actorType;
}


hook_func<void (CGameActor::*)(CGameObject* sender, int arg1, int arg2, int arg3)> CGameActor::_Am_Action(SAKEXE, "CGameActor::Am_Action");
void CGameActor::Am_Action(CGameObject* sender, int arg1, int arg2, int arg3) // line 59-223 (GameActorMsgHandler.cpp)
{
	return (this->*_Am_Action)(sender, arg1, arg2, arg3);

	//TODO
}


hook_func<void (CGameActor::*)(CGameObject* sender, int arg1, int arg2, int arg3)> CGameActor::_Am_Skill(SAKEXE, "CGameActor::Am_Skill");
void CGameActor::Am_Skill(CGameObject* sender, int arg1, int arg2, int arg3) // line 226-645 (GameActorMsgHandler.cpp)
{
	return (this->*_Am_Skill)(sender, arg1, arg2, arg3);

	//TODO
}


hook_func<void (CGameActor::*)(CGameObject* sender, int arg1, int arg2, int arg3)> CGameActor::_Am_Groundskill(SAKEXE, "CGameActor::Am_Groundskill");
void CGameActor::Am_Groundskill(CGameObject* sender, int arg1, int arg2, int arg3) // line 650-846 (GameActorMsgHandler.cpp)
{
	return (this->*_Am_Groundskill)(sender, arg1, arg2, arg3);

	//TODO
}


void CGameActor::Am_Make_Number(CGameObject* sender, int arg1, int arg2, int arg3) // line 849-898 (GameActorMsgHandler.cpp)
{
	int number = (int)arg1;
	int color = (int)arg2;
	int msgeffecttype = (int)arg3;

	if( number > 999999 )
		number = 999999;
	else
	if( number < 0 )
		number = 0;

	int numberCnt = ( number > 99999 ) ? 6
	              : ( number >  9999 ) ? 5
	              : ( number >   999 ) ? 4
	              : ( number >    99 ) ? 3
	              : ( number >     9 ) ? 2
	              :                      1;

	int eachNum[6];
	int n = number;
	eachNum[0] = n % 10; n = n / 10;
	eachNum[1] = n % 10; n = n / 10;
	eachNum[2] = n % 10; n = n / 10;
	eachNum[3] = n % 10; n = n / 10;
	eachNum[4] = n % 10; n = n / 10;
	eachNum[5] = n;

	CGameMode* gameMode = g_modeMgr.CModeMgr::GetGameMode();

	if( msgeffecttype == 22 )
		this->CGameActor::DeleteTotalNumber();

	for( int i = 0; i < numberCnt; ++i )
	{
		CMsgEffect* effect = new CMsgEffect();
		effect->m_sprArgb = color;
		effect->SendMsg(NULL, 22, m_gid, msgeffecttype, 0);
		effect->SendMsg(NULL, 64, (int)&m_pos, eachNum[i], 4 * (numberCnt - 1 - 2*i));
		effect->SendMsg(this, 50, 0, 0, 0);

		if( msgeffecttype == 22 )
			effect->m_zoom = 1.0f;

		gameMode->CGameMode::PushGameObject(effect);
		m_msgEffectList.push_back(effect);
	}
}


void CGameActor::MakePartyEffect(int AID) // line 2258-2270
{
	CWorld* world = g_modeMgr.CModeMgr::GetGameMode()->CGameMode::GetWorld();
	if( !world->CWorld::IsPKZone() && !world->CWorld::IsEventPVPMode() )
		return;

	// locate AID in party list
	int i;
	for( i = 0; i < g_session.CSession::GetNumParty(); ++i )
	{
		FRIEND_INFO fi = g_session.CSession::GetPartyInfoBySequence(i);
		if( fi.AID == AID )
			break;
	}

	if( i >= g_session.CSession::GetNumParty() )
		return; // AID not in party.

	// locate EF_PARTY in effect list
	mystd::list<CRagEffect*>::iterator it;
	for( it = m_effectList.begin(); it != m_effectList.end(); ++it )
	{
		CRagEffect* effect = *it;
		if( effect != NULL && effect->CRagEffect::GetType() == 160 )
			break;
	}

	if( it != m_effectList.end() )
		return; // effect already active.

	this->CAbleToMakeEffect::LaunchEffect(160, vector3d(0.,0.,0.), 0.0);
}


void CGameActor::DeleteTotalNumber() // line 901-916 (GameActorMsgHandler.cpp)
{
	for( mystd::list<CMsgEffect*>::iterator it = m_msgEffectList.begin(); it != m_msgEffectList.end(); )
	{
		CMsgEffect* effect = *it;

		if( effect->CMsgEffect::GetMsgEffectType() == 22 )
		{
			this->CGameActor::DeleteMatchingEffect(effect);
			effect->SendMsg(this, 24, 0, 0, 0);

			it = m_msgEffectList.erase(it);
			g_modeMgr.CModeMgr::GetGameMode()->CGameMode::GetWorld()->CWorld::RemoveGameObject(effect);
		}
		else
		{
			++it;
		}
	}
}


void CGameActor::SetGuildInfo(int gdid, int emblemVersion) // line 2273-2288
{
	if( gdid <= 0 )
		return;

	if( emblemVersion <= 0 && this->CGameActor::GetJob() != JT_GUILD_FLAG )
		return;

	if( !g_session.CSession::IsPc(this->CGameActor::GetJob())
	 && !g_session.CSession::IsGuardian(this->CGameActor::GetJob())
	 && this->CGameActor::GetJob() != JT_GUILD_FLAG )
		return;

	m_gdid = gdid;
	m_emblemVersion = emblemVersion;
	char emblemResName[256];
	g_session.CSession::GetEmblemFileName(emblemResName, gdid, emblemVersion);

	if( !g_resMgr().CResMgr::IsExist(emblemResName) )
		g_modeMgr.CModeMgr::GetCurMode()->SendMsg(MM_QUEUE_REQ_GUILD_EMBLEM_IMG, m_gdid, 0, 0);
}


int CGameActor::GetGdid() // line 606 (GameActor.h)
{
	return m_gdid;
}


int CGameActor::GetEmblemVersion() // line 607 (GameActor.h)
{
	return m_emblemVersion;
}


void CGameActor::DeleteEmblemWnd() // line 4021-4026
{
	if( g_session.CSession::IsSiegeMode() )
	{
		if( m_emblemWnd != NULL )
		{
			g_windowMgr.UIWindowMgr::PostQuit(m_emblemWnd);
			m_emblemWnd = NULL;
		}
	}
}


void CGameActor::MakeEmblemWnd() // line 4029-4033
{
	if( g_session.CSession::IsSiegeMode() )
		g_modeMgr.CModeMgr::GetGameMode()->CGameMode::MakeEmblemWnd(this, this->GetGdid(), this->GetEmblemVersion());
}


BOOL CGameActor::IsFreezeState() // line 4068-4072
{
	return ( m_isBladeStop != 0 );
}


void CGameActor::SetFreezeEndTick(unsigned long freezeEndTick)
{
	m_freezeEndTick = freezeEndTick;
}


int CGameActor::GetTargetGid()
{
	return m_targetGid;
}
