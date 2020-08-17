#pragma once
#include "Window/UIControl2.h" // class UIListBox


class UITextViewer : public UIListBox
{
public:
	UITextViewer();
	virtual ~UITextViewer();
	virtual void Create2(int x, int y, int cx, int cy, bool trans);
	virtual void OnCreate(int cx, int cy);
	virtual void OnLBtnDown(int x, int y);
	virtual void OnLBtnDblClk(int x, int y);
	virtual void OnLBtnUp(int x, int y);
	virtual void OnDraw();
	virtual int SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);

public:
	/* this+  0 */ //UIListBox baseclass_0;
	/* this+144 */ int m_bgR;
	/* this+148 */ int m_bgG;
	/* this+152 */ int m_bgB;
};
