#pragma once
#include "3dLib/Prim.h"
#include "3dLib/Texture.h"
#include "Resource/Action.h"
#include "Resource/Sprite.h"
class UITransBalloonText;


/// @see CMode::SendMsg
enum MODEMESSAGE
{
	MM_COMMAND     = 0,
	MM_SOCKETERROR = 1,
	MM_QUIT        = 2,
	MM_CANCEL_DRAG = 18,
	MM_SCREENSHOT  = 68,
};


class CMode
{
public:
	CMode();
	virtual ~CMode();

public:
	virtual int OnRun();
	virtual void OnInit(const char* modeName);
	virtual void OnExit();
	virtual void OnUpdate();
	virtual void vfn5(int a1); //TODO
	virtual int SendMsg(int messageId, int val1, int val2, int val3);

public:
	void Initialize();
	void PostQuitMsg();
	void ScreenShot();
	void SetCursorAction(int cursorActNum);
	void RunFadeOut(BOOL bDrawLogo);
	void DrawSprite(int x, int y, CActRes* act, CSprRes* spr, int actId, int motId, float zoom, float angle, COLORREF color);
	void DrawTexture(RECT* rect, int angle, float oow, COLORREF argb, CTexture* tex, UVRECT uvRect);
	void DrawMouseCursor();
	void DrawBattleMode();
	void MakeHelpBalloon(const char* helpMsg, int x, int y, COLORREF fntColor);
	void ProcessHelpBalloon();
	void ProcessFadeIn();
	void ProcessKeyBoard();
	int GetCursorAction();
	int GetCursorMotion();
//	int GetSubMode();
	BOOL GetLoopCond();

protected:
	virtual void OnChangeState(int state);
//	void SetNextSubState(int );
//	void SetSubState(int );

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
	int (CMode::* OnRun)();
	void (CMode::* OnInit)(const char* modeName);
	void (CMode::* OnExit)();
	void (CMode::* OnUpdate)();
	void (CMode::* vfn5)(int a1); //TODO
	int (CMode::* SendMsg)(int messageId, int val1, int val2, int val3);
	void (CMode::* OnChangeState)(int state);
};
