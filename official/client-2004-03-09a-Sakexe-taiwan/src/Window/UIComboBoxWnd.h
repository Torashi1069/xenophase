#pragma once
#include "Window/UIFrameWnd.h"
class UIComboBox;


class UIComboBoxWnd : public UIFrameWnd
{
public:
	UIComboBoxWnd();
	virtual ~UIComboBoxWnd();
	virtual void OnCreate(int cx, int cy);
	virtual void Resize(int cx, int cy);
	virtual void OnDraw();
	virtual int SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);

protected:
	/* this+ 0 */ //UIFrameWnd baseclass_0;
	/* this+96 */ UIComboBox* m_comboBox;

private:
	static hook_func<void (UIComboBoxWnd::*)(int cx, int cy)> UIComboBoxWnd::_OnCreate;
	static hook_func<void (UIComboBoxWnd::*)(int cx, int cy)> UIComboBoxWnd::_Resize;
	static hook_func<int (UIComboBoxWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIComboBoxWnd::_SendMsg;
};
