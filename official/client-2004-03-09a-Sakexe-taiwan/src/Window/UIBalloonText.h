#pragma once
#include "Window/UIWindow.h"


class UIBalloonText : public UIWindow
{
public:
	UIBalloonText();
	virtual ~UIBalloonText();
	virtual void OnProcess();
	virtual void OnDraw();
	virtual bool ShouldDoHitTest();
	void SetText(const char* msg, const int maxNumCharLine);
	void AddText(const char* msg);
	void SetFntColor(COLORREF fontColor, COLORREF bgColor);
	void SetFntSize(int fontSize);
	void SetBackTrans(bool isBack);

protected:
	void AdjustSizeByText();

protected:
	/* this+  0 */ //UIWindow baseclass_0;
	/* this+ 72 */ bool m_isBold;
	/* this+ 76 */ int m_fontSize;
	/* this+ 80 */ mystd::vector<mystd::string> m_strings;
	/* this+ 96 */ COLORREF m_fontColor;
	/* this+100 */ COLORREF m_bgColor;
	/* this+104 */ bool m_isBack;
};
