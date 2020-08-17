#include "Window/UIChatHisBox2.h"
#include "Window/UIScrollBar.h"
#include "Window/UIScrollBar2.h"


UIChatHisBox2::UIChatHisBox2() // line 1222-1226 (UIControl2.cpp)
{
	m_r = 255;
	m_g = 255;
	m_b = 255;
}


UIChatHisBox2::~UIChatHisBox2() // line 1229-1230 (UIControl2.cpp)
{
}


void UIChatHisBox2::OnCreate(int cx, int cy) // line 1233-1243 (UIControl2.cpp)
{
	m_vertScrollBar = new UIScrollBar();
	m_vertScrollBar->UIScrollBar::Create(cx - 13, 0, 1, cy);
	this->UIWindow::AddChild(m_vertScrollBar);

	m_horzScrollBar = new UIScrollBar2();
	m_vertScrollBar->UIScrollBar::Create(0, cy - 13, 0, cx - 13);
	this->UIWindow::AddChild(m_horzScrollBar);
}


void UIChatHisBox2::Create2(int x, int y, int cx, int cy, bool trans) // line 1246-1248 (UIControl2.cpp)
{
	this->UIChatHisBox::Create2(x, y, cx, cy, trans); // inlined
}


void __thiscall UIChatHisBox2::OnRBtnUp(int x, int y) // line 1251-1253 (UIControl2.cpp)
{
	m_parent->OnRBtnUp(x + m_x, y + m_y);
}


void UIChatHisBox2::OnDraw() // line 1256-1267 (UIControl2.cpp)
{
	this->UIWindow::ClearDC(RGB(m_r,m_g,m_b));

	int lastItem = min(m_vertViewOffset + m_h / m_itemSpacing - m_horzScrEnabled, (int)m_items.size());

	for( int i = 0; m_vertViewOffset + i < lastItem; ++i )
		this->UIWindow::TextOutA(2, i * m_itemSpacing + 3, m_items[m_vertViewOffset + i].c_str(), 0, 0, 12, m_itemColors[m_vertViewOffset + i]);
}


bool UIChatHisBox2::IsTransmitMouseInput() // line 899 (Window/UISys.h)
{
	return false;
}
