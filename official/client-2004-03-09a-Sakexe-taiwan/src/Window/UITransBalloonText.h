#pragma once
#include "Struct.h" // struct BOXINFO
#include "Window/UIBalloonText.h"


class UITransBalloonText : public UIBalloonText
{
public:
	UITransBalloonText();
	virtual ~UITransBalloonText();
	virtual void OnDraw();
	virtual bool GetTransBoxInfo(BOXINFO* boxInfo);
	virtual void OnCreate(int cx, int cy);
	virtual void Move(int x, int y);
	virtual void Resize(int cx, int cy);
	void SetTransBoxColor(COLORREF transboxColor);

public:
	/* this+  0 */ //UIBalloonText baseclass_0;
	/* this+108 */ BOXINFO m_transBoxInfo;
};
