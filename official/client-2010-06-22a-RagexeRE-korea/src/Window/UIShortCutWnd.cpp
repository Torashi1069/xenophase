#include "Window/UIShortCutWnd.h"


hook_func<void (UIShortCutWnd::*)(void)> UIShortCutWnd::_OnDraw("UIShortCutWnd::OnDraw");
void UIShortCutWnd::OnDraw(void)
{
	return (this->*_OnDraw)();

	//TODO
}


hook_func<void (UIShortCutWnd::*)(int visible)> UIShortCutWnd::_SetShow("UIShortCutWnd::SetShow");
void UIShortCutWnd::SetShow(int visible)
{
	return (this->*_SetShow)(visible);

	//TODO
}
