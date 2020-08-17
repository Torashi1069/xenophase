#include "Window/UIScrollBar2.h"


UIScrollBar2::UIScrollBar2() // line 1887-1889
{
	m_scrollBtnSize = 10;
}


hook_func<void (UIScrollBar2::*)()> UIScrollBar2::_OnDraw(SAKEXE, "UIScrollBar2::OnDraw");
void UIScrollBar2::OnDraw() // line 1892-1929
{
	return (this->*_OnDraw)();

	//TODO
}
