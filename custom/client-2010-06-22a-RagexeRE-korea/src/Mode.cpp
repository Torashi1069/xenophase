#include "Globals.h"
#include "Mode.h"
#include "ModeMgr.h"
#include "Window/UIWindowMgr.h"


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


void CMode::vfn5(int a1) //TODO
{
}


void CMode::OnChangeState(int state)
{
}


hook_func<void (CMode::*)()> CMode__Initialize("CMode::Initialize");
void CMode::Initialize()
{
	return (this->*CMode__Initialize)();
/*
	if( m_helpBalloon != NULL )
	{
		g_windowMgr.UIWindowMgr::PostQuit(m_helpBalloon);
		m_helpBalloon = NULL;
		m_helpBalloonTick = timeGetTime();
	}
*/
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
//		aossdk_sub_57B4E0(); //TODO
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


hook_func<void (CMode::*)(int x, int y, CActRes* act, CSprRes* spr, int actId, int motId, float zoom, float angle, COLORREF color)> CMode__DrawSprite("CMode::DrawSprite");
void CMode::DrawSprite(int x, int y, CActRes* act, CSprRes* spr, int actId, int motId, float zoom, float angle, COLORREF color)
{
	return (this->*CMode__DrawSprite)(x, y, act, spr, actId, motId, zoom, angle, color);

	//TODO
}


hook_func<void (CMode::*)(RECT* rect, int angle, float oow, COLORREF argb, CTexture* tex, UVRECT uvRect)> CMode__DrawTexture("CMode::DrawTexture");
void CMode::DrawTexture(RECT* rect, int angle, float oow, COLORREF argb, CTexture* tex, UVRECT uvRect)
{
	return (this->*CMode__DrawTexture)(rect, angle, oow, argb, tex, uvRect);

	//TODO
}


hook_func<void (CMode::*)()> CMode__DrawBattleMode("CMode::DrawBattleMode");
void CMode::DrawBattleMode()
{
	return (this->*CMode__DrawBattleMode)();

	//TODO
}


hook_func<void (CMode::*)()> CMode__DrawMouseCursor("CMode::DrawMouseCursor");
void CMode::DrawMouseCursor()
{
	return (this->*CMode__DrawMouseCursor)();

	//TODO
}


hook_func<unsigned int (__stdcall *)(void* res)> _FadeBgm("FadeBgm");
unsigned int __stdcall FadeBgm(void* res)
{
	return (_FadeBgm)(res);

	//TODO
}


hook_func<void (CMode::*)()> CMode__ProcessFadeIn("CMode::ProcessFadeIn");
void CMode::ProcessFadeIn()
{
	return (this->*CMode__ProcessFadeIn)();

	//TODO
}


hook_func<void (CMode::*)(BOOL bDrawLogo)> CMode__RunFadeOut("CMode::RunFadeOut");
void CMode::RunFadeOut(BOOL bDrawLogo)
{
	return (this->*CMode__RunFadeOut)(bDrawLogo);

	//TODO
}


hook_func<void (CMode::*)(const char* helpMsg, int x, int y, COLORREF fntColor)> CMode__MakeHelpBalloon("CMode::MakeHelpBalloon");
void CMode::MakeHelpBalloon(const char* helpMsg, int x, int y, COLORREF fntColor)
{
	return (this->*CMode__MakeHelpBalloon)(helpMsg, x, y, fntColor);

	//TODO
}


hook_func<void (CMode::*)()> CMode__ProcessHelpBalloon("CMode::ProcessHelpBalloon");
void CMode::ProcessHelpBalloon()
{
	return (this->*CMode__ProcessHelpBalloon)();

	//TODO
}


void CMode::ProcessKeyBoard()
{
}


int CMode::GetCursorAction()
{
	return m_cursorActNum;
}


int CMode::GetCursorMotion()
{
	return m_cursorMotNum;
}


void CMode::SetCursorAction(int cursorActNum)
{
	if( m_cursorActNum != cursorActNum )
	{
		m_cursorActNum = cursorActNum;
		m_cursorMotNum = 0;
		m_mouseAnimStartTick = timeGetTime();
		g_windowMgr.UIWindowMgr::SendMsg(UIM_CURSOR_CHANGE_ACTION, m_cursorActNum, 0, 0, 0);
	}
}


hook_func<void (CMode::*)()> CMode__ScreenShot("CMode::ScreenShot");
void CMode::ScreenShot()
{
	return (this->*CMode__ScreenShot)();

	//TODO
}
