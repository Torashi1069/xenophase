#include "Window/UIComboBoxWnd.h"


UIComboBoxWnd::UIComboBoxWnd() // line 8581-8583 (UIFrameWnd2.cpp)
{
	m_comboBox = NULL;
}


UIComboBoxWnd::~UIComboBoxWnd() // line 8586-8587 (UIFrameWnd2.cpp)
{
}


hook_func<void (UIComboBoxWnd::*)(int cx, int cy)> UIComboBoxWnd::_OnCreate(SAKEXE, "UIComboBoxWnd::OnCreate");
void UIComboBoxWnd::OnCreate(int cx, int cy) // line 8590-8594 (UIFrameWnd2.cpp)
{
	return (this->*_OnCreate)(cx, cy);

	//TODO
}


hook_func<void (UIComboBoxWnd::*)(int cx, int cy)> UIComboBoxWnd::_Resize(SAKEXE, "UIComboBoxWnd::Resize");
void UIComboBoxWnd::Resize(int cx, int cy) // line 8597-8603 (UIFrameWnd2.cpp)
{
	return (this->*_Resize)(cx, cy);

	//TODO
}


void UIComboBoxWnd::OnDraw() // line 8606-8608 (UIFrameWnd2.cpp)
{
	this->UIWindow::ClearDC(0xFFFF00FF);
}


hook_func<int (UIComboBoxWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIComboBoxWnd::_SendMsg(SAKEXE, "UIComboBoxWnd::SendMsg");
int UIComboBoxWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 8611-8613 (UIFrameWnd2.cpp)
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);
	/*
	return m_comboBox->SendMsg(sender, message, val1, val2, val3);
	*/
}
