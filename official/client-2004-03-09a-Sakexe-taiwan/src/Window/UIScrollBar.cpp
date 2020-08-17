#include "Window/UIScrollBar.h"


UIScrollBar::UIScrollBar(void) // line 1446
{
	m_maxPos = 0;
	m_curPos = 0;
	m_drawMode = 0;
	m_startDragX = 0;
	m_startDragY = 0;
	m_deltaDrag = 0;
	m_parentNumItem = 0;
	m_parentnumCanDisplayItem = 0;
	m_scrollBtnSize = 13;
	m_isVert = 1;
}


UIScrollBar::~UIScrollBar(void) // line 1460
{
}


hook_method<void (UIScrollBar::*)(int x, int y, int type, int size)> UIScrollBar::_Create(SAKEXE, "UIScrollBar::Create");
void UIScrollBar::Create(int x, int y, int type, int size) // line 1487
{
	return (this->*_Create)(x, y, type, size);

	m_isVert = type;

	int cx;
	int cy;

	if( type == 0 )
	{// horizontal
		cx = size;
		cy = 13;
	}
	else
	if( type == 1 )
	{// vertical
		cx = 13;
		cy = size;
	}
	else
	{// ???
		cx = size;
		cy = size;
	}

	this->UIWindow::Resize(cx, cy);
	this->Move(x, y);
	this->OnCreate(cx, cy);
	this->OnSize(cx, cy);
}


hook_method<void (UIScrollBar::*)(int x, int y)> UIScrollBar::_OnLBtnDown(SAKEXE, "UIScrollBar::OnLBtnDown");
void UIScrollBar::OnLBtnDown(int x, int y) // line 1538
{
	return (this->*_OnLBtnDown)(x, y);

	//TODO
}


hook_method<void (UIScrollBar::*)(int x, int y)> UIScrollBar::_OnLBtnDblClk(SAKEXE, "UIScrollBar::OnLBtnDblClk");
void UIScrollBar::OnLBtnDblClk(int x, int y) // line 1533
{
	return (this->*_OnLBtnDblClk)(x, y);

	//TODO
}


hook_method<void (UIScrollBar::*)(int x, int y)> UIScrollBar::_OnMouseMove(SAKEXE, "UIScrollBar::OnMouseMove");
void UIScrollBar::OnMouseMove(int x, int y) // line 1620
{
	return (this->*_OnMouseMove)(x, y);

	//TODO
}


hook_method<void (UIScrollBar::*)(int x, int y)> UIScrollBar::_OnMouseShape(SAKEXE, "UIScrollBar::OnMouseShape");
void UIScrollBar::OnMouseShape(int x, int y) // line 1471
{
	return (this->*_OnMouseShape)(x, y);

	//TODO
}


hook_method<void (UIScrollBar::*)(int x, int y)> UIScrollBar::_OnLBtnUp(SAKEXE, "UIScrollBar::OnLBtnUp");
void UIScrollBar::OnLBtnUp(int x, int y) // line 1600
{
	return (this->*_OnLBtnUp)(x, y);

	//TODO
}


hook_method<void (UIScrollBar::*)(int x, int y)> UIScrollBar::_OnRBtnUp(SAKEXE, "UIScrollBar::OnRBtnUp");
void UIScrollBar::OnRBtnUp(int x, int y) // line 1611
{
	return (this->*_OnRBtnUp)(x, y);

	//TODO
}


hook_method<void (UIScrollBar::*)(int wheel)> UIScrollBar::_OnWheel(SAKEXE, "UIScrollBar::OnWheel");
void UIScrollBar::OnWheel(int wheel) // line 1480
{
	return (this->*_OnWheel)(wheel);

	//TODO
}


hook_method<void (UIScrollBar::*)(void)> UIScrollBar::_OnDraw(SAKEXE, "UIScrollBar::OnDraw");
void UIScrollBar::OnDraw(void) // line 1689
{
	return (this->*_OnDraw)();

	//TODO
}


hook_method<void (UIScrollBar::*)(int cx, int cy)> UIScrollBar::_Resize(SAKEXE, "UIScrollBar::Resize");
void UIScrollBar::Resize(int cx, int cy) // line 1512
{
	return (this->*_Resize)(cx, cy);

	//TODO
}


hook_method<bool (UIScrollBar::*)(void)> UIScrollBar::_IsTransmitMouseInput(SAKEXE, "UIScrollBar::IsTransmitMouseInput");
bool UIScrollBar::IsTransmitMouseInput(void) // line 1465
{
	return (this->*_IsTransmitMouseInput)();

	//TODO
}


hook_method<void (UIScrollBar::*)(int range, int parentnumCanDisplayItem, int parentNumItem)> UIScrollBar::_SetRange(SAKEXE, "UIScrollBar::SetRange");
void UIScrollBar::SetRange(int range, int parentnumCanDisplayItem, int parentNumItem) // line 1771
{
	return (this->*_SetRange)(range, parentnumCanDisplayItem, parentNumItem);

	//TODO
}


void UIScrollBar::SetPos(int pos) // line 1781-1784
{
	m_curPos = pos;
}


hook_method<int (UIScrollBar::*)(void)> UIScrollBar::_GetPos(SAKEXE, "UIScrollBar::GetPos");
int UIScrollBar::GetPos(void) // line 1788
{
	return (this->*_GetPos)();

	//TODO
}


hook_method<int (UIScrollBar::*)(int x, int y)> UIScrollBar::_HitTest(SAKEXE, "UIScrollBar::HitTest");
int UIScrollBar::HitTest(int x, int y) // line 1792
{
	return (this->*_HitTest)(x, y);

	//TODO
}


hook_method<int (UIScrollBar::*)(void)> UIScrollBar::_GetThumbSize(SAKEXE, "UIScrollBar::GetThumbSize");
int UIScrollBar::GetThumbSize(void) // line 1845
{
	return (this->*_GetThumbSize)();

	//TODO
}


hook_method<int (UIScrollBar::*)(void)> UIScrollBar::_GetScrollRange(SAKEXE, "UIScrollBar::GetScrollRange");
int UIScrollBar::GetScrollRange(void) // line 1865
{
	return (this->*_GetScrollRange)();

	//TODO
}


hook_method<int (UIScrollBar::*)(void)> UIScrollBar::_GetThumbOffset(SAKEXE, "UIScrollBar::GetThumbOffset");
int UIScrollBar::GetThumbOffset(void) // line 1879
{
	return (this->*_GetThumbOffset)();

	//TODO
}
