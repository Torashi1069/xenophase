#pragma once
#include "Window/UIFrameWnd.h"


struct ShortCutWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;
};


class UIShortCutWnd : public UIFrameWnd
{
public:
	/* this+  0 */ //UIFrameWnd baseclass_0;
	/* this+ 96 */ ShortCutWndInfo* m_info;
	/* this+100 */ BYTE dummy_64[252];
	/* this+352 */ int field_160;
	/* this+356 */ int field_164;
	/* this+360 */ int field_168;
	/* this+364 */ int m_nTotalBars;
	/* this+368 */ int m_nDisplayedBars;
	/* this+372 */ int field_174;

public:
	void UIShortCutWnd::OnDraw(void);
	void UIShortCutWnd::SetShow(int visible);

public:
	static hook_func<void (UIShortCutWnd::*)(void)> UIShortCutWnd::_OnDraw;
	static hook_func<void (UIShortCutWnd::*)(int visible)> UIShortCutWnd::_SetShow;
};
C_ASSERT( sizeof UIShortCutWnd == 376 );
