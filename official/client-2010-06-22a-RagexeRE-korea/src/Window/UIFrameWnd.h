#pragma once
#include "ItemInfo.h"
#include "Window/UIWindow.h"


class UIFrameWnd : public UIWindow
{
public:
	UIFrameWnd();
	virtual ~UIFrameWnd();
	virtual void OnLBtnDown(int x, int y);
	virtual void OnMouseMove(int x, int y);
	virtual void OnMouseHover(int x, int y);
	virtual void OnLBtnUp(int x, int y);
	virtual void Move(int x, int y);
	virtual bool IsFrameWnd();
	virtual void SaveOriginalPos();
	virtual void MoveDelta(int deltaDragX, int deltaDragY);
	virtual int SendMsg(UIWindow* sender, int message, int val1, int val2, int val3, int val4);
	virtual void RefreshSnap();

protected:
	void DrawItem(int x, int y, const ITEM_INFO& iteminfo, bool forceidentified);
	void DrawItem(int x, int y, const char* itemName, bool identified);
	void DrawItemWithCount(int x, int y, const ITEM_INFO& iteminfo, bool forceidentified, bool boldtext);
	void DrawItemFrame(int x, int y);
	void DrawLatticeFrame(int x, int y, int width, int height);
//	int MakeItemText(const ITEM_INFO& iteminfo, COLORREF& manufacturerColor, mystd::vector<const char*>& itemNameList, char*& itemNameIter, char*& itemNameColored, bool bIsColorList, bool a8); //TODO
//	int TextOutWithItemRect(int x, int y, int width, mystd::vector<const char*>& itemNameList, char* itemName, char* itemNameColored, COLORREF manufacturerColor, COLORREF color, int fontType, int fontHeight);
//	int DrawItemText(int x, int y, const ITEM_INFO& iteminfo, COLORREF color, int fontType, int fontHeight, bool a8); //TODO
//	int DrawItemTextRect(int x, int y, int width, const ITEM_INFO& iteminfo, COLORREF color int fontType, int fontHeight);
//	int DrawItemObtainTextRect(int x, int y, int width, const ITEM_INFO& iteminfo, COLORREF color, int fontType, int fontHeight);

protected:
	/* this+ 0 */ //UIWindow baseclass_0;
	/* this+72 */ int m_startGlobalX;
	/* this+76 */ int m_startGlobalY;
	/* this+80 */ int m_orgX;
	/* this+84 */ int m_orgY;
	/* this+88 */ int m_defPushId;
	/* this+92 */ int m_defCancelPushId;
};
C_ASSERT( sizeof UIFrameWnd == 96 );


struct UIFrameWndVtbl
{
	void* (UIFrameWnd::* scalar_deleting_destructor)(unsigned int flags);
	void (UIWindow::* Invalidate)();
	void (UIWindow::* InvalidateWallPaper)();
	void (UIWindow::* Resize)(int cx, int cy);
	bool (UIFrameWnd::* IsFrameWnd)();
	bool (UIWindow::* IsUpdateNeed)();
	void (UIFrameWnd::* Move)(int x, int y);
	bool (UIWindow::* CanGetFocus)();
	bool (UIWindow::* GetTransBoxInfo)(BOXINFO* boxInfo);
	bool (UIWindow::* IsTransmitMouseInput)();
	bool (UIWindow::* ShouldDoHitTest)();
	void (UIWindow::* DragAndDrop)(int x, int y, const DRAG_INFO* const dragInfo);
	void (UIWindow::* StoreInfo)();
	void (UIFrameWnd::* SaveOriginalPos)();
	void (UIFrameWnd::* MoveDelta)(int deltaDragX, int deltaDragY);
	COLORREF (UIWindow::* GetColor)();
	void (UIWindow::* SetShow)(BOOL visible);
	void (UIWindow::* OnCreate)(int cx, int cy);
	void (UIWindow::* OnDestroy)();
	void (UIWindow::* OnProcess)();
	void (UIWindow::* OnDraw)();
	void (UIWindow::* OnRun)();
	void (UIWindow::* OnSize)(int cx, int cy);
	void (UIWindow::* OnBeginEdit)();
	void (UIWindow::* OnFinishEdit)();
	void (UIFrameWnd::* OnLBtnDown)(int x, int y);
	void (UIWindow::* OnLBtnDblClk)(int x, int y);
	void (UIFrameWnd::* OnMouseMove)(int x, int y);
	void (UIFrameWnd::* OnMouseHover)(int x, int y);
	void (UIWindow::* OnMouseShape)(int x, int y);
	void (UIFrameWnd::* OnLBtnUp)(int x, int y);
	void (UIWindow::* OnRBtnDown)(int x, int y);
	void (UIWindow::* OnRBtnUp)(int x, int y);
	void (UIWindow::* OnRBtnDblClk)(int x, int y);
	void (UIWindow::* OnWheel)(int wheel);
	void (UIFrameWnd::* RefreshSnap)();
	int (UIFrameWnd::* SendMsg)(UIWindow* sender, int message, int val1, int val2, int val3, int val4);
	bool (UIWindow::* GetTransBoxInfo2)(BOXINFO* boxInfo);
	void (UIWindow::* DrawBoxScreen2)();
};
