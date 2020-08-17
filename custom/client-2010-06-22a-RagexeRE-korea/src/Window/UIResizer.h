#pragma once
#include "Window/UIWindow.h"


enum RESIZERTYPE
{
	RT_LEFT      = 0,
	RT_RIGHT     = 1,
	RT_UP        = 2,
	RT_DOWN      = 3,
	RT_UPLEFT    = 4,
	RT_UPRIGHT   = 5,
	RT_DOWNLEFT  = 6,
	RT_DOWNRIGHT = 7,
};


class UIResizer : public UIWindow
{
public:
	UIResizer();
	virtual void OnDraw();
	virtual void OnLBtnDown(int x, int y);
	virtual void OnMouseMove(int x, int y);
	virtual void OnLBtnUp(int x, int y);
	virtual void OnMouseHover(int x, int y);
	virtual void OnMouseShape(int x, int y);
	void SetBitmap(const char* bitmapName);
	void SetType(RESIZERTYPE type);
//	void SetColor(unsigned long);
	void SetColor(COLORREF color, COLORREF backColor);

protected:
	/* this+  0 */ //UIWindow baseclass_0;
	/* this+ 72 */ mystd::string m_bitmapName;
	/* this+ 88 */ int m_startX;
	/* this+ 92 */ int m_startY;
	/* this+ 96 */ RESIZERTYPE m_type;
	/* this+100 */ int m_parentWidth;
	/* this+104 */ int m_parentHeight;
	/* this+108 */ COLORREF m_color;
	/* this+112 */ COLORREF m_backColor;
};
C_ASSERT( sizeof UIResizer == 116 );


struct UIResizerVtbl
{
	void* (UIResizer::* scalar_deleting_destructor)(unsigned int flags);
	void (UIWindow::* Invalidate)();
	void (UIWindow::* InvalidateWallPaper)();
	void (UIWindow::* Resize)(int cx, int cy);
	bool (UIWindow::* IsFrameWnd)();
	bool (UIWindow::* IsUpdateNeed)();
	void (UIWindow::* Move)(int x, int y);
	bool (UIWindow::* CanGetFocus)();
	bool (UIWindow::* GetTransBoxInfo)(BOXINFO* boxInfo);
	bool (UIWindow::* IsTransmitMouseInput)();
	bool (UIWindow::* ShouldDoHitTest)();
	void (UIWindow::* DragAndDrop)(int x, int y, const DRAG_INFO* const dragInfo);
	void (UIWindow::* StoreInfo)();
	void (UIWindow::* SaveOriginalPos)();
	void (UIWindow::* MoveDelta)(int deltaDragX, int deltaDragY);
	COLORREF (UIWindow::* GetColor)();
	void (UIWindow::* SetShow)(BOOL visible);
	void (UIWindow::* OnCreate)(int cx, int cy);
	void (UIWindow::* OnDestroy)();
	void (UIWindow::* OnProcess)();
	void (UIResizer::* OnDraw)();
	void (UIWindow::* OnRun)();
	void (UIWindow::* OnSize)(int cx, int cy);
	void (UIWindow::* OnBeginEdit)();
	void (UIWindow::* OnFinishEdit)();
	void (UIResizer::* OnLBtnDown)(int x, int y);
	void (UIWindow::* OnLBtnDblClk)(int x, int y);
	void (UIResizer::* OnMouseMove)(int x, int y);
	void (UIResizer::* OnMouseHover)(int x, int y);
	void (UIResizer::* OnMouseShape)(int x, int y);
	void (UIResizer::* OnLBtnUp)(int x, int y);
	void (UIWindow::* OnRBtnDown)(int x, int y);
	void (UIWindow::* OnRBtnUp)(int x, int y);
	void (UIWindow::* OnRBtnDblClk)(int x, int y);
	void (UIWindow::* OnWheel)(int wheel);
	void (UIWindow::* RefreshSnap)();
	int (UIWindow::* SendMsg)(UIWindow* sender, int message, int val1, int val2, int val3, int val4);
	bool (UIWindow::* GetTransBoxInfo2)(BOXINFO* boxInfo);
	void (UIWindow::* DrawBoxScreen2)();
};
