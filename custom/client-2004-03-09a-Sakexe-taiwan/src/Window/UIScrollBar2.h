#pragma once
#include "Window/UIScrollBar.h"


class UIScrollBar2 : public UIScrollBar
{
public:
	UIScrollBar2();
	virtual void OnDraw();

public:
	/* this+0 */ //UIScrollBar baseclass_0;

private:
	static hook_func<void (UIScrollBar2::*)()> UIScrollBar2::_OnDraw;
};
