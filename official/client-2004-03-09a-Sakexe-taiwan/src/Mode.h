#pragma once
#include "Struct.h"
#include "3dLib/Prim.h" // vector2d
#include "Resource/Action.h"
#include "Resource/Sprite.h"
class UITransBalloonText;


class CMode
{
public:
	CMode();
	virtual ~CMode();

public:
	virtual void OnInit(const char* modeName);
	virtual int OnRun();
	virtual void OnExit();
	virtual void OnUpdate();
	virtual int SendMsg(int messageId, int val1, int val2, int val3);

public:
	void Initialize();
	void RunFadeOut(int bDrawLogo);
	BOOL GetLoopCond();
	void PostQuitMsg();
	void ScreenShot();
	void SetCursorAction(int cursorActNum);
	int GetCursorAction();
	int GetCursorMotion();
	void DrawSprite(int x, int y, CActRes* act, CSprRes* spr, int actId, int motId, float zoom, float angle, COLORREF color);
	void DrawTexture(RECT* rect, int angle, float oow, COLORREF argb, CTexture* tex, UVRECT uvRect);
	void DrawMouseCursor();
	void MakeHelpBalloon(const char* helpMsg, int x, int y, COLORREF fntColor);
	void ProcessHelpBalloon();
	void ProcessFadeIn();
	void ProcessKeyBoard();
//	int GetSubMode();

protected:
//	void SetNextSubState(int );
//	void SetSubState(int );
	virtual void OnChangeState(int state);

protected:
	/* this+ 0 */ //const CMode::`vftable';
	/* this+ 4 */ int m_subMode;
	/* this+ 8 */ int m_subModeCnt;
	/* this+12 */ int m_nextSubMode;
	/* this+16 */ int m_fadeInCount;
	/* this+20 */ BOOL m_loopCond;
	/* this+24 */ int m_isConnected;
	/* this+28 */ UITransBalloonText* m_helpBalloon;
	/* this+32 */ DWORD m_helpBalloonTick;
	/* this+36 */ DWORD m_mouseAnimStartTick;
	/* this+40 */ int m_isMouseLockOn;
	/* this+44 */ int m_screenShotNow;
	/* this+48 */ vector2d m_mouseSnapDiff;
private:
	/* this+56 */ int m_cursorActNum;
	/* this+60 */ int m_cursorMotNum;
};


struct CModeVtbl
{
	void* (CMode::* scalar_deleting_destructor)(unsigned int __flags);
	void (CMode::* OnInit)(const char* modeName);
	int (CMode::* OnRun)();
	void (CMode::* OnExit)();
	void (CMode::* OnUpdate)();
	int (CMode::* SendMsg)(int messageId, int val1, int val2, int val3);
	void (CMode::* OnChangeState)(int state);
};
