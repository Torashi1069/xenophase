#include "Globals.h"
#include "Mode.h"
#include "ModeMgr.h"
#include "3dLib/Device.h"
#include "3dLib/DrawUtil.h"
#include "3dLib/Renderer.h"
#include "Base/ResMgr.h"
#include "Device/Sound.h"
#include "Window/UITransBalloonText.h"
#include <direct.h> // _mkdir


CMode::CMode()
{
	m_loopCond = TRUE;
	m_nextSubMode = -1;
	m_isConnected = 1;
	m_helpBalloon = NULL;
	m_helpBalloonTick = timeGetTime();
	m_cursorActNum = 0;
	m_cursorMotNum = 0;
	m_mouseAnimStartTick = timeGetTime();
	m_isMouseLockOn = 0;
	m_screenShotNow = 0;
	m_mouseSnapDiff.x = 0;
	m_mouseSnapDiff.y = 0;
	m_fadeInCount = 0;
}


CMode::~CMode()
{
}


void CMode::OnInit(const char* modeName)
{
}


int CMode::OnRun()
{
	return 0;
}


void CMode::OnExit()
{
}


void CMode::OnUpdate()
{
}


void CMode::Initialize()
{
	if( m_helpBalloon != NULL )
	{
		g_windowMgr.UIWindowMgr::PostQuit(m_helpBalloon);
		m_helpBalloon = NULL;
		m_helpBalloonTick = timeGetTime();
	}
}


BOOL CMode::GetLoopCond()
{
	return m_loopCond;
}


void CMode::PostQuitMsg()
{
	m_loopCond = FALSE;
}


int CMode::SendMsg(int messageId, int val1, int val2, int val3)
{
	switch( messageId )
	{
	case MM_QUIT:
		g_modeMgr.CModeMgr::Quit();
	break;
	case MM_SCREENSHOT:
		m_screenShotNow = 1;
	break;
	default:
	break;
	};

	return 0;
}


unsigned int __stdcall FadeBgm(void* res)
{
	static int FadeCnt;

	++FadeCnt;

	if( g_session.m_BgmVolume == 0 )
		return -1;

	while( FadeCnt != 1 )
		Sleep(5);

	int targetVolume = (int)res;
	if( targetVolume != 0 )
	{// increasing volume
		PauseStream(0);

		for( int i = 0; i < targetVolume; ++i )
		{
			if( FadeCnt != 1 )
				break;

			SetStreamVolume(i);
			Sleep(10);
		}
	}
	else
	{// decreasing volume
		int i;
		for( i = GetStreamVolume(); i > 0; --i )
		{
			if( FadeCnt != 1 )
				break;

			SetStreamVolume(i);
			Sleep(10);
		}

		if( i <= 0 )
			PauseStream(1);
	}

	--FadeCnt;

	return 0;
}


/// @see CMode::ProcessFadeIn, CMode::RunFadeOut
static DWORD dwFadeStart;


void CMode::ProcessFadeIn()
{
	if( m_fadeInCount != 0 )
	{
		dwFadeStart = timeGetTime();

		unsigned int hFadeBgmThread;
		_beginthreadex(NULL, 0, &FadeBgm, (void*)g_session.m_BgmVolume, 0, &hFadeBgmThread);

		m_fadeInCount = 0;
	}

	DWORD delta = timeGetTime() - dwFadeStart;
	if( delta < 0xFF )
		DrawBoxScreen(0, 0, g_renderer->CRenderer::GetWidth(), g_renderer->CRenderer::GetHeight(), (0xFF - delta) << 24);
}


void CMode::RunFadeOut(int bDrawLogo)
{
	unsigned int hFadeBgmThread;
	_beginthreadex(NULL, 0, &FadeBgm, NULL, 0, &hFadeBgmThread);

	dwFadeStart = timeGetTime();
	g_renderer->CRenderer::BackupFrame();

	for( DWORD i = timeGetTime() - dwFadeStart; i < 0xFF; i = timeGetTime() - dwFadeStart )
	{
		DrawBoxScreen(0, 0, g_renderer->CRenderer::GetWidth(), g_renderer->CRenderer::GetHeight(), i << 24);

		if( bDrawLogo )
			g_windowMgr.UIWindowMgr::DrawBitmapToFrame(g_renderer->CRenderer::GetWidth() - 192, g_renderer->CRenderer::GetHeight() - 122, (CBitmapRes*)g_resMgr().CResMgr::Get("rag_logo.bmp"));

		if( g_renderer->CRenderer::DrawScene() )
			g_renderer->CRenderer::Flip(1);

		g_renderer->CRenderer::RestoreFrame();
	}
}


void CMode::MakeHelpBalloon(const char* helpMsg, int x, int y, COLORREF fntColor)
{
	if( strlen(helpMsg) == 0 )
		return;

	char nHelpMsg[512];
	g_session.CSession::RemoveUnderbar(helpMsg, nHelpMsg);
	m_helpBalloonTick = timeGetTime();

	if( m_helpBalloon != NULL )
	{
		g_windowMgr.UIWindowMgr::MakeTopLayer(m_helpBalloon);
	}
	else
	{
		m_helpBalloon = new UITransBalloonText();
		m_helpBalloon->UIWindow::Create(8, 8);
		g_windowMgr.UIWindowMgr::AddWindow(m_helpBalloon);
	}

	m_helpBalloon->UIBalloonText::SetText(nHelpMsg, 35);
	m_helpBalloon->UIBalloonText::SetFntColor(0x00000000, RGB(fntColor >> 16, fntColor >> 8, fntColor >> 0));
	m_helpBalloon->UITransBalloonText::SetTransBoxColor(0x88000000);

	if( x < -3 )
		x = -3;
	if( x > g_renderer->CRenderer::GetWidth() - m_helpBalloon->UIWindow::GetWidth() + 3 )
		x = g_renderer->CRenderer::GetWidth() - m_helpBalloon->UIWindow::GetWidth() + 3;

	if( y < -3 )
		y = -3;
	if( y > g_renderer->CRenderer::GetHeight() - m_helpBalloon->UIWindow::GetHeight() + 3 )
		y = g_renderer->CRenderer::GetHeight() - m_helpBalloon->UIWindow::GetHeight() + 3;

	m_helpBalloon->Move(x, y);
}


void CMode::ProcessHelpBalloon()
{
	if( m_helpBalloon != NULL && timeGetTime() >= m_helpBalloonTick + 100 )
	{
		g_windowMgr.UIWindowMgr::PostQuit(m_helpBalloon);
		m_helpBalloon = NULL;
	}
}


void CMode::ProcessKeyBoard()
{
}


void CMode::SetCursorAction(int cursorActNum)
{
	if( m_cursorActNum != cursorActNum )
	{
		m_cursorActNum = cursorActNum;
		m_cursorMotNum = 0;
		m_mouseAnimStartTick = timeGetTime();
		g_windowMgr.UIWindowMgr::SendMsg(UIM_CURSOR_CHANGE_ACTION, m_cursorActNum, 0, 0);
	}
}


int CMode::GetCursorAction()
{
	return m_cursorActNum;
}


int CMode::GetCursorMotion()
{
	return m_cursorMotNum;
}


void CMode::DrawSprite(int x, int y, CActRes* act, CSprRes* spr, int actId, int motId, float zoom, float angle, COLORREF color)
{
	CacheInfo info = {};
	CMotion* curMotion = act->CActRes::GetMotion(actId, motId);

	for( int i = 0; i < curMotion->numClips; ++i )
	{
		RPQuadFace& rp = g_renderer->CRenderer::BorrowQuadRP();
		CSprClip* clip = curMotion->CMotion::GetClip(i);
		SprImg* img = spr->m_sprites[clip->clipType][clip->sprIndex];
		float x1 = clip->x * zoom * clip->zoomx;
		float y1 = clip->y * zoom * clip->zoomy;
		float x2 = (img->width * (img->isHalfW + 1) + clip->x - 1) * zoom * clip->zoomx;
		float y2 = (img->height * (img->isHalfH + 1) + clip->y - 1) * zoom * clip->zoomy;

		if( clip->clipType != 0 )
		{
			rp.tex = img->tex;
		}
		else
		{
			rp.tex = g_renderer->CRenderer::GetSpriteIndex(*img, (unsigned long)spr->m_pal, &info);
			if( rp.tex == NULL )
				rp.tex = g_renderer->CRenderer::AddSpriteIndex(*img, spr->m_pal, &info);
		}

		if( angle == 0.0 )
		{
			float xa = ( clip->flags & 1 ) ? x2 : x1;
			float xb = ( clip->flags & 1 ) ? x1 : x2;

			rp.m_verts[0].x = float(x + xa + 0.5f);
			rp.m_verts[0].y = float(y + y1 + 0.5f);
			rp.m_verts[1].x = float(x + xb + 0.5f);
			rp.m_verts[1].y = float(y + y1 + 0.5f);
			rp.m_verts[2].x = float(x + xa + 0.5f);
			rp.m_verts[2].y = float(y + y2 + 0.5f);
			rp.m_verts[3].x = float(x + xb + 0.5f);
			rp.m_verts[3].y = float(y + y2 + 0.5f);
		}
		else
		{
			float cs = GetCos((int)angle);
			float si = GetSin((int)angle);

			rp.m_verts[0].x = float(x1 * cs - y1 * si + x + 0.5f);
			rp.m_verts[0].y = float(x1 * si + y1 * cs + y + 0.5f);
			rp.m_verts[1].x = float(x2 * cs - y1 * si + x + 0.5f);
			rp.m_verts[1].y = float(x2 * si + y1 * cs + y + 0.5f);
			rp.m_verts[2].x = float(x2 * cs - y2 * si + x + 0.5f); //FIXME: x1 and x2 swapped?
			rp.m_verts[2].y = float(x2 * si + y2 * cs + y + 0.5f); //FIXME
			rp.m_verts[3].x = float(x1 * cs - y2 * si + x + 0.5f); //FIXME
			rp.m_verts[3].y = float(x1 * si + y2 * cs + y + 0.5f); //FIXME
		}

		rp.m_verts[0].z = 0.000001f;
		rp.m_verts[0].oow = 0.99999899f;
		rp.m_verts[0].tu = info.tu;
		rp.m_verts[0].tv = info.tv;
		rp.m_verts[0].color = color;
		rp.m_verts[1].z = 0.000001f;
		rp.m_verts[1].oow = 0.99999899f;
		rp.m_verts[1].tu = info.tu1;
		rp.m_verts[1].tv = info.tv;
		rp.m_verts[1].color = color;
		rp.m_verts[2].z = 0.000001f;
		rp.m_verts[2].oow = 0.99999899f;
		rp.m_verts[2].tu = info.tu;
		rp.m_verts[2].tv = info.tv1;
		rp.m_verts[2].color = color;
		rp.m_verts[3].z = 0.000001f;
		rp.m_verts[3].oow = 0.99999899f;
		rp.m_verts[3].tu = info.tu1;
		rp.m_verts[3].tv = info.tv1;
		rp.m_verts[3].color = color;

		g_renderer->CRenderer::AddRP(&rp, 0x201);
	}
}


void CMode::DrawTexture(RECT* rect, int angle, float oow, COLORREF argb, CTexture* tex, UVRECT uvRect)
{
	RPQuadFace& rp = g_renderer->CRenderer::BorrowQuadRP();
	rp.tex = tex;

	float z = GetZFromOow(oow);
	float z1 = GetZFromOow(oow);

	if( angle == 0 )
	{
		rp.verts[0].x = float(rect->left);
		rp.verts[0].y = float(rect->top);
		rp.verts[1].x = float(rect->right);
		rp.verts[1].y = float(rect->top);
		rp.verts[2].x = float(rect->left);
		rp.verts[2].y = float(rect->bottom);
		rp.verts[3].x = float(rect->right);
		rp.verts[3].y = float(rect->bottom);
	}
	else
	{
		float cs = GetCos(angle);
		float si = GetSin(angle);
		float w = float(rect->right - rect->left);
		float h = float(rect->bottom - rect->top);
		float x1 = w * -0.5f;
		float y1 = h * -0.5f;
		float x2 = w * 0.5f;
		float y2 = h * 0.5f;
		float x = rect->left + x2;
		float y = rect->top + y2;

		rp.verts[0].x = float(x1 * cs - y1 * si + x);
		rp.verts[0].y = float(x1 * si + y1 * cs + y);
		rp.verts[1].x = float(x2 * cs - y1 * si + x);
		rp.verts[1].y = float(x2 * si + y1 * cs + y);
		rp.verts[2].x = float(x1 * cs - y2 * si + x);
		rp.verts[2].y = float(x1 * si + y2 * cs + y);
		rp.verts[3].x = float(x2 * cs - y2 * si + x);
		rp.verts[3].y = float(x2 * si + y2 * cs + y);
	}

	float uAdjust = tex->CTexture::GetUAdjust();
	float vAdjust = tex->CTexture::GetVAdjust();
	rp.verts[0].oow = oow;
	rp.verts[1].oow = oow;
	rp.verts[2].oow = oow;
	rp.verts[3].oow = oow;
	rp.verts[0].z = z1;
	rp.verts[1].z = z1;
	rp.verts[2].z = z;
	rp.verts[3].z = z;
	rp.verts[0].color = argb;
	rp.verts[1].color = argb;
	rp.verts[2].color = argb;
	rp.verts[3].color = argb;
	rp.verts[0].tu = uvRect.u1 * uAdjust;
	rp.verts[0].tv = uvRect.v1 * vAdjust;
	rp.verts[1].tu = uvRect.u2 * uAdjust;
	rp.verts[1].tv = uvRect.v1 * vAdjust;
	rp.verts[3].tu = uvRect.u2 * uAdjust;
	rp.verts[2].tu = uvRect.u1 * uAdjust;
	rp.verts[2].tv = uvRect.v2 * vAdjust;
	rp.verts[3].tv = uvRect.v2 * vAdjust;

	g_renderer->CRenderer::AddRP(&rp, 0x201);
}


void CMode::DrawMouseCursor()
{
	CActRes* cursorAct = (CActRes*)g_resMgr().CResMgr::Get("cursors.act");
	CSprRes* cursorSpr = (CSprRes*)g_resMgr().CResMgr::Get("cursors.spr");
	DWORD motionDelta = (timeGetTime() - m_mouseAnimStartTick) / 24;
	cursorAct->CActRes::GetDelay(m_cursorActNum); // unused

	DWORD motionSpeed;
	switch( m_cursorActNum )
	{
	case 2: motionSpeed = 4; break;
	case 5: motionSpeed = 20; break;
	case 7: motionSpeed = 10; break;
	case 9: motionSpeed = 1; break;
	case 10: motionSpeed = 6; break;
	case 11: motionSpeed = 3; break;
	default: motionSpeed = 4; break;
	};

	int numFrames = motionDelta / motionSpeed;

	if( m_cursorActNum == 1 )
	{
		m_cursorMotNum = numFrames % cursorAct->CActRes::GetMotionCount(m_cursorActNum);
		if( numFrames / cursorAct->CActRes::GetMotionCount(m_cursorActNum) >= 1 )
			m_cursorMotNum = cursorAct->CActRes::GetMotionCount(m_cursorActNum) - 1;
	}
	else
	if( m_cursorActNum == 2 || m_cursorActNum == 9 )
	{
		if( g_mouse.CMouse::GetLBtn() == BTN_NONE )
		{
			m_mouseAnimStartTick = timeGetTime();
			m_cursorMotNum = 0;
		}
	}
	else
	{
		m_cursorMotNum = numFrames % cursorAct->CActRes::GetMotionCount(m_cursorActNum);
	}

	g_windowMgr.UIWindowMgr::SendMsg(16, m_cursorMotNum, 0, 0);
	this->CMode::DrawSprite(int(g_mouse.CMouse::GetXPos() + m_mouseSnapDiff.x), int(g_mouse.CMouse::GetYPos() + m_mouseSnapDiff.y), cursorAct, cursorSpr, m_cursorActNum, m_cursorMotNum, 1.0f, 0.0f, 0xFAFFFFFF);
}


void CMode::ScreenShot()
{
	if( m_screenShotNow == NULL )
		return;

	SYSTEMTIME st;
	GetLocalTime(&st);

	const char* week[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

	char msg[128];
	sprintf(msg, "%d/%02d/%02d/%s  %02d: %02d: %02d", st.wYear, st.wMonth, st.wDay, week[st.wDayOfWeek], st.wHour, st.wMinute, st.wSecond);

	g_renderer->CRenderer::TextOutScreen(5, g_renderer->CRenderer::GetHeight() - 16, msg, 0x000000);
	g_renderer->CRenderer::TextOutScreen(3, g_renderer->CRenderer::GetHeight() - 16, msg, 0x000000);
	g_renderer->CRenderer::TextOutScreen(4, g_renderer->CRenderer::GetHeight() - 15, msg, 0x000000);
	g_renderer->CRenderer::TextOutScreen(4, g_renderer->CRenderer::GetHeight() - 17, msg, 0x000000);
	g_renderer->CRenderer::TextOutScreen(4, g_renderer->CRenderer::GetHeight() - 16, msg, 0xFFFFFF);

	m_screenShotNow = 0;

	char tmp[2048];
	sprintf(tmp, "%s\\ScreenShot", g_baseDir3);

	if( access(tmp, 0) != 0 && mkdir(tmp) != 0 )
		return; // no screenshot directory

	mystd::string serverName = g_session.m_lastServerName;
	for( size_t i = 0; i < serverName.size(); ++i )
	{
		char c = serverName[i];
		if( c == '\\' || c == '/' || c == ':' || c == '*' || c == '?' || c == '\"' || c == '<' || c == '>' || c == '|' )
			serverName[i] = '_';
	}

	static int captureCnt;
	if( GetAsyncKeyState(VK_CONTROL) >> 8 == 0 )
	{// printscreen -> save as jpg
		do
			sprintf(tmp, "%s\\ScreenShot\\screen%s%03d.jpg", g_baseDir3, serverName.c_str(), captureCnt++);
		while( access(tmp, 0) == 0 );

		g_renderer->CRenderer::SaveJPG(tmp, (CBitmapRes*)g_resMgr().CResMgr::Get("scr_logo.bmp"));
	}
	else
	{// ctrl+printscreen -> save as bmp
		do
			sprintf(tmp, "%s\\ScreenShot\\screen%s%03d.bmp", g_baseDir3, serverName.c_str(), captureCnt++);
		while( access(tmp, 0) == 0 );

		g_renderer->CRenderer::SaveBmp(tmp, (CBitmapRes*)g_resMgr().CResMgr::Get("scr_logo.bmp"));
	}

	mystd::string screenShotMsg = tmp;
	screenShotMsg += " is Saved.";

	g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)screenShotMsg.c_str(), 0x00FF00, 0);
}


void CMode::OnChangeState(int state)
{
}
