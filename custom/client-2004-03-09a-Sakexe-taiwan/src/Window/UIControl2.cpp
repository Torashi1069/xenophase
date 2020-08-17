#include "Globals.h"
#include "MsgStrings.h"
#include "Base/ResMgr.h"
#include "Window/UIScrollBar.h"


////////////////////////////////////////


UIBarGraph::UIBarGraph(void) // line 20
{
	m_percent = 0.0;
}


UIBarGraph::~UIBarGraph(void) // line 25
{
}


hook_method<void (UIBarGraph::*)(void)> UIBarGraph::_OnDraw(SAKEXE, "UIBarGraph::OnDraw");
void UIBarGraph::OnDraw(void) // line 29
{
	return (this->*_OnDraw)();

	this->UIWindow::DrawBitmap(0, 0, (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\gze_bg.bmp")), 0);

	if( m_percent == 0.0 )
		return;

	mystd::string colorName = ( m_percent >= 25.0 ) ? "blue" : "red";
	int drawCount = (int)(m_percent * (m_w - 8)) / 100;

	this->UIWindow::DrawBitmap(0, 0, (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp((mystd::string("유저인터페이스\\basic_interface\\gze") + colorName + "_left.bmp").c_str())), 1);

	for( int i = 0; i < drawCount; ++i )
		this->UIWindow::DrawBitmap(i + 4, 0, (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp((mystd::string("유저인터페이스\\basic_interface\\gze") + colorName + "_mid.bmp").c_str())), 1);

	this->UIWindow::DrawBitmap(drawCount + 4, 0, (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp((mystd::string("유저인터페이스\\basic_interface\\gze") + colorName + "_right.bmp").c_str())), 1);
}


hook_method<void (UIBarGraph::*)(float percent)> UIBarGraph::_SetAmount(SAKEXE, "UIBarGraph::SetAmount");
void UIBarGraph::SetAmount(float percent) // line 57
{
	return (this->*_SetAmount)(percent);

	m_percent = percent;
	this->Invalidate();
}


////////////////////////////////////////


UIBarGraph2::UIBarGraph2(void) // line 68
{
	m_isVertical = 0;
	m_backR = 0xF2;
	m_backG = 0xF2;
	m_backB = 0xF2;
	m_r = 0x2A;
	m_g = 0x4B;
	m_b = 0x8F;
}


UIBarGraph2::~UIBarGraph2(void) // line 80
{
}


hook_method<void (UIBarGraph2::*)(void)> UIBarGraph2::_OnDraw(SAKEXE, "UIBarGraph2::OnDraw");
void UIBarGraph2::OnDraw(void) // line 83
{
	return (this->*_OnDraw)();

	//TODO
}


////////////////////////////////////////


UIListBox::UIListBox() // line 471-485
: m_curItem(0),
  m_vertViewOffset(0),
  m_horzViewOffset(0),
  m_maxTextWidth(0),
  m_vertScrollBar(0),
  m_horzScrollBar(0),
  m_vertScrEnabled(0),
  m_horzScrEnabled(0),
  m_isTransParent(0)
{
	m_bR = 255;
	m_bG = 255;
	m_bB = 255;
	m_itemSpacing = 16;
//	m_noColor; // uninitialized
}


UIListBox::~UIListBox() // line 488-489
{
}


void UIListBox::Create2(int x, int y, int cx, int cy, bool trans) // line 492-498
{
	m_isTransParent = trans;
	this->UIWindow::Resize(cx, cy);
	this->Move(x, y);
	this->OnCreate(cx, cy);
	this->OnSize(cx, cy);
}


hook_method<void (UIListBox::*)(int cx, int cy)> UIListBox::_OnCreate(SAKEXE, "UIListBox::OnCreate");
void UIListBox::OnCreate(int cx, int cy) /// line 501
{
	return (this->*_OnCreate)(cx, cy);

	//TODO
}


hook_method<void (UIListBox::*)(int x, int y)> UIListBox::_OnLBtnDown(SAKEXE, "UIListBox::OnLBtnDown");
void UIListBox::OnLBtnDown(int x, int y) // line 527
{
	return (this->*_OnLBtnDown)(x, y);

	//TODO
}


hook_method<void (UIListBox::*)(int x, int y)> UIListBox::_OnLBtnDblClk(SAKEXE, "UIListBox::OnLBtnDblClk");
void UIListBox::OnLBtnDblClk(int x, int y) // line 533
{
	return (this->*_OnLBtnDblClk)(x, y);

	//TODO
}


hook_method<void (UIListBox::*)(int wheel)> UIListBox::_OnWheel(SAKEXE, "UIListBox::OnWheel");
void UIListBox::OnWheel(int wheel) // line 539
{
	return (this->*_OnWheel)(wheel);

	//TODO
}


hook_method<void (UIListBox::*)(void)> UIListBox::_OnDraw(SAKEXE, "UIListBox::OnDraw");
void UIListBox::OnDraw(void) // line 549
{
	return (this->*_OnDraw)();

	//TODO
}


hook_method<int (UIListBox::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIListBox::_SendMsg(SAKEXE, "UIListBox::SendMsg");
int UIListBox::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 570
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	//TODO
}


hook_method<void (UIListBox::*)(const char* txt)> UIListBox::_AddItem(SAKEXE, "UIListBox::AddItem");
void UIListBox::AddItem(const char* txt) // line 668
{
	return (this->*_AddItem)(txt);

	//TODO
}


void UIListBox::ClearAllItems() // line 706-714
{
	m_curItem = -1;
	m_maxTextWidth = 0;
	m_horzViewOffset = 0;
	m_vertViewOffset = 0;
	m_vertScrEnabled = 0;
	m_horzScrEnabled = 0;
	m_items.clear();
}


void UIListBox::Resize(int cx, int cy) // line 514-524
{
	this->UIWindow::Resize(cx, cy);

	m_vertScrollBar->Resize(12, cy);
	m_vertScrollBar->Move(cx - 13, 0);

	m_horzScrollBar->Resize(cx - 13, 12);
	m_horzScrollBar->Move(0, cy - 13);

	this->RecalcScrbarPos();
}


hook_method<void (UIListBox::*)(void)> UIListBox::_RecalcScrbarPos(SAKEXE, "UIListBox::RecalcScrbarPos");
void UIListBox::RecalcScrbarPos(void) // line 675
{
	return (this->*_RecalcScrbarPos)();

	//TODO
}


//hook_method<int (UIListBox::*)(void)> UIListBox::_IsVertScrEnabled(SAKEXE, "UIListBox::IsVertScrEnabled");
int UIListBox::IsVertScrEnabled(void) // line ???
{
//	return (this->*_IsVertScrEnabled)();

	return m_vertScrEnabled;
}


//hook_method<int (UIListBox::*)(void)> UIListBox::_GetSelected(SAKEXE, "UIListBox::GetSelected");
int UIListBox::GetSelected(void) // line ???
{
//	return (this->*_GetSelected)();

	return m_curItem;
}


///////////////////////////////////////
