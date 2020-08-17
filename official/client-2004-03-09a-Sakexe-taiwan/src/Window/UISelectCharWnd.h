#pragma once
#include "Struct.h" // viewSprite
#include "Window/UIFrameWnd.h"
class UIBitmapButton;
class UISlotBitmap;
class UIStaticText;
class UIWindow;


class UISelectCharWnd : public UIFrameWnd
{
public:
	UISelectCharWnd();
	virtual ~UISelectCharWnd();
	virtual void OnCreate(int cx, int cy);
	virtual void OnProcess();
	virtual void OnDraw();
	virtual void OnMouseMove(int x, int y);
	virtual void OnLBtnDown(int x, int y);
	virtual int SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	virtual void InvalidateWallPaper();
	void MakeButton(int id);
	void DeleteButton(int id);
	void InitTextControls();
	void InitFromReg();
	void WriteToReg();

private:
	/* this+   0 */ //UIFrameWnd baseclass_0;
	/* this+  96 */ viewSprite m_viewChar[9];
	/* this+2220 */ BOOL m_isEmpty[9];
	/* this+2256 */ bool m_isAvailable[9];
	/* this+2268 */ int m_curSlot;
	/* this+2272 */ int m_curPage;
	/* this+2276 */ int m_pageCount;
	/* this+2280 */ char m_dontmove;
	/* this+2284 */ UIBitmapButton* m_okButton;
	/* this+2288 */ UIBitmapButton* m_makeButton;
	/* this+2292 */ UIBitmapButton* m_cancelButton;
	/* this+2296 */ UIBitmapButton* m_deleteButton;
	/* this+2300 */ UIBitmapButton* m_chargeButton;
	/* this+2304 */ UIBitmapButton* m_noticeButton;
	/* this+2308 */ UISlotBitmap* m_slots[12+1];
	/* this+2360 */ UIStaticText* m_text[22];

private:
	static hook_method<void (UISelectCharWnd::*)(int x, int y)> UISelectCharWnd::_OnMouseMove;
	static hook_method<void (UISelectCharWnd::*)(int x, int y)> UISelectCharWnd::_OnLBtnDown;
	static hook_method<int (UISelectCharWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UISelectCharWnd::_SendMsg;
	static hook_method<void (UISelectCharWnd::*)()> UISelectCharWnd::_InvalidateWallPaper;
	static hook_method<void (UISelectCharWnd::*)(int id)> UISelectCharWnd::_MakeButton;
	static hook_method<void (UISelectCharWnd::*)(int id)> UISelectCharWnd::_DeleteButton;
	static hook_method<void (UISelectCharWnd::*)()> UISelectCharWnd::_InitFromReg;
	static hook_method<void (UISelectCharWnd::*)()> UISelectCharWnd::_WriteToReg;
};
