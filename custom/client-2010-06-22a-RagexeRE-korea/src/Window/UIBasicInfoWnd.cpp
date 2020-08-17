#include "Window/UIBasicInfoWnd.h"
#include "Window/UIWindowMgr.h"


hook_func<UIBasicInfoWnd* (UIBasicInfoWnd::*)(void)> UIBasicInfoWnd::_cUIBasicInfoWnd("UIBasicInfoWnd::UIBasicInfoWnd");
UIBasicInfoWnd::UIBasicInfoWnd(void)
{
	(this->*_cUIBasicInfoWnd)(); return;

	m_info = NULL;
	bAreButtonsDisplayed = false;
	field_A4 = 13;
	field_60_height1 = 55;
	field_64_height2 = 134;
}


hook_func<void (UIBasicInfoWnd::*)(void)> UIBasicInfoWnd::_dUIBasicInfoWnd("UIBasicInfoWnd::~UIBasicInfoWnd");
UIBasicInfoWnd::~UIBasicInfoWnd(void)
{
//	(this->*_dUIBasicInfoWnd)(); return;

	;
}
