#pragma once
#include "Window/UIStaticBitmap.h"


class UISlotBitmap : public UIStaticBitmap
{
public:
	UISlotBitmap();
	~UISlotBitmap();
	virtual void OnLBtnDown(int x, int y);
	virtual void OnLBtnDblClk(int x, int y);
	virtual int SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);

private:
	/* this+0 */ //UIStaticBitmap baseclass_0;
};
