#pragma once
#include "Window/UIChatHisBox.h"


class UIChatHisBox2 : public UIChatHisBox
{
public:
	UIChatHisBox2();
	virtual ~UIChatHisBox2();
	virtual void Create2(int x, int y, int cx, int cy, bool trans);
	virtual void OnCreate(int cx, int cy);
	virtual void OnDraw();
	virtual void OnRBtnUp(int x, int y);
	virtual bool IsTransmitMouseInput();

public:
	/* this+  0 */ //UIChatHisBox baseclass_0;
	/* this+164 */ int m_r;
	/* this+168 */ int m_g;
	/* this+172 */ int m_b;
};
