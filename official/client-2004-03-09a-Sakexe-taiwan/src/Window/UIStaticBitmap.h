#pragma once
#include "Window/UIWindow.h"


class UIStaticBitmap : public UIWindow
{
public:
	UIStaticBitmap();
	~UIStaticBitmap();
	virtual void OnLBtnDown(int x, int y);
	virtual void OnMouseMove(int x, int y);
	virtual void OnLBtnUp(int x, int y);
	virtual void OnDraw();
	void SetBitmap(const char* bitmapName);

private:
	/* this+ 0 */ //UIWindow baseclass_0;
	/* this+72 */ mystd::string m_bitmapName;
};
