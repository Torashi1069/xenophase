#include "Window/UIChatHisBox.h"
#include "Window/UIScrollBar2.h"


UIChatHisBox::UIChatHisBox() // line 979-984 (UIControl2.cpp)
{
	m_maxItem = 240;
	m_itemSpacing = 14;
	m_items.resize(240);
	m_itemColors.resize(240);
}


UIChatHisBox::~UIChatHisBox() // line 987-988 (UIControl2.cpp)
{
}


void UIChatHisBox::Create2(int x, int y, int cx, int cy, bool trans) // line 991-993 (UIControl2.cpp)
{
	this->UIListBox::Create2(x, y, cx, cy, true); // inlined
}


void UIChatHisBox::OnCreate(int cx, int cy) // line 996-1006 (UIControl2.cpp)
{
	m_vertScrollBar = new UIScrollBar2();
	m_vertScrollBar->UIScrollBar::Create(cx - 13, 0, 1, cy); // inlined
	this->UIWindow::AddChild(m_vertScrollBar);

	m_horzScrollBar = new UIScrollBar2();
	m_horzScrollBar->UIScrollBar::Create(0, cy - 13, 0, cx - 13); // inlined
	this->UIWindow::AddChild(m_horzScrollBar);
}


void UIChatHisBox::SetShow(BOOL visible) // line 1009-1012 (UIControl2.cpp)
{
	m_show = visible;
	if( visible ) this->Invalidate();
}


void UIChatHisBox::Resize(int cx, int cy) // line 1015-1027 (UIControl2.cpp)
{
	this->UIListBox::Resize(cx, cy); // inlined

	if( m_vertScrEnabled )
	{
		int endpos = (int)m_items.size() + m_horzScrEnabled - m_h / m_itemSpacing;
		m_vertViewOffset = endpos;
		m_vertScrollBar->UIScrollBar::SetPos(endpos);
		m_vertScrollBar->Move(cx - 13, 0);
		this->Invalidate();
	}
	else
	{
		m_vertViewOffset = 0;
		m_vertScrollBar->UIScrollBar::SetPos(0);
		m_vertScrollBar->Move(cx - 13, 0);
	}
}


hook_func<void (UIChatHisBox::*)()> UIChatHisBox::_DeleteFirstHalfItem(SAKEXE, "UIChatHisBox::DeleteFirstHalfItem");
void UIChatHisBox::DeleteFirstHalfItem() // line 1030-1043 (UIControl2.cpp)
{
	return (this->*_DeleteFirstHalfItem)();

	//TODO
}


hook_func<void (UIChatHisBox::*)(const char* txt, COLORREF itemRGB)> UIChatHisBox::_AddItem(SAKEXE, "UIChatHisBox::AddItem");
void UIChatHisBox::AddItem(const char* txt, COLORREF itemRGB) // line 1046-1069 (UIControl2.cpp)
{
	return (this->*_AddItem)(txt, itemRGB);

	//TODO
}


void UIChatHisBox::ClearAllItems() // line 1072-1075 (UIControl2.cpp)
{
	this->UIListBox::ClearAllItems(); // inlined
	m_itemColors.clear();
}


void UIChatHisBox::OnLBtnDown(int x, int y) // line 1078-1079 (UIControl2.cpp)
{
}


void UIChatHisBox::OnLBtnDblClk(int x, int y) // line 1082-1083 (UIControl2.cpp)
{
}


void UIChatHisBox::OnLBtnUp(int x, int y) // line 1086-1087 (UIControl2.cpp)
{
}


void UIChatHisBox::OnDraw() // line 1090-1103 (UIControl2.cpp)
{
	this->UIWindow::ClearDC(0xFFFF00FF);
	if( m_parent != NULL )
		m_parent->OnDraw2();

	int lastItem = min(m_vertViewOffset + m_h / m_itemSpacing - m_horzScrEnabled, (int)m_items.size());
	for( int i = 0; m_vertViewOffset + i < lastItem; ++i )
	{
		this->UIWindow::TextOutA(3, i * m_itemSpacing + 4, m_items[m_vertViewOffset + i].c_str(), 0, 0, 12, 0x000000);
		this->UIWindow::TextOutA(2, i * m_itemSpacing + 3, m_items[m_vertViewOffset + i].c_str(), 0, 0, 12, m_itemColors[m_vertViewOffset + i]);
	}
}


int UIChatHisBox::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 1106-1113 (UIControl2.cpp)
{
	switch( message )
	{
	default:
		return this->UIListBox::SendMsg(sender, message, val1, val2, val3);
	break;
	};

	return 0;
}


hook_func<BOOL (UIChatHisBox::*)(const char* fileName)> UIChatHisBox::_WriteChatToFile(SAKEXE, "UIChatHisBox::WriteChatToFile");
BOOL UIChatHisBox::WriteChatToFile(const char* fileName) // line 1116-1131 (UIControl2.cpp)
{
	return (this->*_WriteChatToFile)(fileName);

	//TODO
}


bool UIChatHisBox::IsTransmitMouseInput() // line 874 (Window/UISys.h)
{
	return true;
}
