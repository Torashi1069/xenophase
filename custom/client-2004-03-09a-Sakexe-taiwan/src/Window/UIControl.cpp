#include "Globals.h"
#include "Mode.h"
#include "ModeMgr.h"
#include "MsgStrings.h" // UIBmp()
#include "Base/ResMgr.h"
#include "Resource/Emblem.h"
#include "Window/UIControl.h"


///////////////////////////////////////


UIStaticText::UIStaticText(void) // line 22
{
	m_fontType = 0;
	m_drawBackGround = 0;
	m_isShorten = 0;
	m_drawTwice = 0;
	m_drawBold = 0;

	m_fontHeight = 12;
	m_backR = 255;
	m_backG = 255;
	m_backB = 255;
}


UIStaticText::~UIStaticText(void) // line 35
{
}


hook_method<void (UIStaticText::*)(void)> UIStaticText::_OnDraw(SAKEXE, "UIStaticText::OnDraw");
void UIStaticText::OnDraw(void) // line 45
{
	return (this->*_OnDraw)();

	//TODO
}


hook_method<void (UIStaticText::*)(int x, int y)> UIStaticText::_OnLBtnDown(SAKEXE, "UIStaticText::OnLBtnDown");
void UIStaticText::OnLBtnDown(int x, int y) // line 157
{
	return (this->*_OnLBtnDown)(x, y);

	//TODO
}


hook_method<void (UIStaticText::*)(int x, int y)> UIStaticText::_OnLBtnDblClk(SAKEXE, "UIStaticText::OnLBtnDblClk");
void UIStaticText::OnLBtnDblClk(int x, int y) // line 152
{
	return (this->*_OnLBtnDblClk)(x, y);

	//TODO
}


hook_method<void (UIStaticText::*)(int x, int y)> UIStaticText::_OnMouseMove(SAKEXE, "UIStaticText::OnMouseMove");
void UIStaticText::OnMouseMove(int x, int y) // line 162
{
	return (this->*_OnMouseMove)(x, y);

	//TODO
}


hook_method<void (UIStaticText::*)(int x, int y)> UIStaticText::_OnLBtnUp(SAKEXE, "UIStaticText::OnLBtnUp");
void UIStaticText::OnLBtnUp(int x, int y) // line 168
{
	return (this->*_OnLBtnUp)(x, y);

	//TODO
}


hook_method<void (UIStaticText::*)(int x, int y)> UIStaticText::_OnMouseHover(SAKEXE, "UIStaticText::OnMouseHover");
void UIStaticText::OnMouseHover(int x, int y) // line 137
{
	return (this->*_OnMouseHover)(x, y);

	//TODO
}


hook_method<void (UIStaticText::*)(int x, int y)> UIStaticText::_OnMouseShape(SAKEXE, "UIStaticText::OnMouseShape");
void UIStaticText::OnMouseShape(int x, int y) // line 147
{
	return (this->*_OnMouseShape)(x, y);

	//TODO
}


hook_method<void (UIStaticText::*)(int wheel)> UIStaticText::_OnWheel(SAKEXE, "UIStaticText::OnWheel");
void UIStaticText::OnWheel(int wheel) // line 173
{
	return (this->*_OnWheel)(wheel);

	//TODO
}


hook_method<void (UIStaticText::*)(int x, int y)> UIStaticText::_OnRBtnDown(SAKEXE, "UIStaticText::OnRBtnDown");
void UIStaticText::OnRBtnDown(int x, int y) // line 178
{
	return (this->*_OnRBtnDown)(x, y);

	//TODO
}


hook_method<void (UIStaticText::*)(int x, int y)> UIStaticText::_OnRBtnUp(SAKEXE, "UIStaticText::OnRBtnUp");
void UIStaticText::OnRBtnUp(int x, int y) // line 183
{
	return (this->*_OnRBtnUp)(x, y);

	//TODO
}


hook_method<void (UIStaticText::*)(const char* txt, int drawBold)> UIStaticText::_SetText(SAKEXE, "UIStaticText::SetText");
void UIStaticText::SetText(const char* txt, int drawBold) // line 68
{
	return (this->*_SetText)(txt, drawBold);

	//TODO
}


hook_method<void (UIStaticText::*)(int number)> UIStaticText::_SetTextWithNumber(SAKEXE, "UIStaticText::SetTextWithNumber");
void UIStaticText::SetTextWithNumber(int number) // line 77
{
	return (this->*_SetTextWithNumber)(number);

	//TODO
}


hook_method<void (UIStaticText::*)(const char* txt)> UIStaticText::_SetTextWithShorten(SAKEXE, "UIStaticText::SetTextWithShorten");
void UIStaticText::SetTextWithShorten(const char* txt) // line 87
{
	return (this->*_SetTextWithShorten)(txt);

	//TODO
}


hook_method<void (UIStaticText::*)(const char* txt)> UIStaticText::_SetTextWithNewWidth(SAKEXE, "UIStaticText::SetTextWithNewWidth");
void UIStaticText::SetTextWithNewWidth(const char* txt) // line 124
{
	return (this->*_SetTextWithNewWidth)(txt);

	//TODO
}


///////////////////////////////////////


UICheckBox::UICheckBox() // line 241-245
{
	m_isDisabled = FALSE;
	m_state = 0;
	m_id = ID_CHECK;
}


UICheckBox::~UICheckBox() // line 248-249
{
}


void UICheckBox::OnLBtnDown(int x, int y) // line 252-257
{
	if( m_isDisabled )
		return;

	m_state = 1 - m_state;
	this->Invalidate();

	if( m_parent != NULL )
		m_parent->SendMsg(this, UM_COMMAND, m_id, m_state, 0);
}


void UICheckBox::SetCheck(int check) // line 260-268
{
	if( m_isDisabled )
		return;

	m_state = check;
	this->Invalidate();

	if( m_parent != NULL )
		m_parent->SendMsg(this, UM_COMMAND, m_id, m_state, 0);
}


void UICheckBox::OnMouseShape(int x, int y) // line 271-273
{
	g_modeMgr.CModeMgr::GetCurMode()->CMode::SetCursorAction(2);
}


void UICheckBox::OnDraw() // line 276-301
{
	if( m_onBitmapName.size() == 0 || m_offBitmapName.size() == 0 )
		return;

	if( m_isDisabled )
	{
		this->UIWindow::ClearDC(0xFFFF00FF);
		return;
	}

	if( m_state == 0 )
	{
		CBitmapRes* bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp(m_offBitmapName.c_str()));
		this->UIWindow::DrawBitmap(0, (m_h - bitmapRes->m_height) / 2, bitmapRes, false);
	}
	else
	if( m_state == 1 )
	{
		CBitmapRes* bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp(m_onBitmapName.c_str()));
		this->UIWindow::DrawBitmap(0, (m_h - bitmapRes->m_height) / 2, bitmapRes, false);
	}

	if( m_checkMsg.size() != 0 )
	{
		this->UIWindow::TextOutA(11, 0, m_checkMsg.c_str(), 0, 0, 12, 0x000000);
	}
}


void UICheckBox::SetBitmap(const char* onBitmapName, const char* offBitmapName) // line 304-313
{
	m_onBitmapName = onBitmapName;
	m_offBitmapName = offBitmapName;

	CBitmapRes* bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(m_onBitmapName.c_str());
	m_w = bitmapRes->m_width;
	m_h = bitmapRes->m_height;
	g_resMgr().CResMgr::Get(m_offBitmapName.c_str());
}


void UICheckBox::SetBitmap2(const char* onBitmapName, const char* offBitmapName, const char* checkMsg) // line 316-325
{
	m_onBitmapName = onBitmapName;
	m_offBitmapName = offBitmapName;
	g_resMgr().CResMgr::Get(m_onBitmapName.c_str());
	g_resMgr().CResMgr::Get(m_offBitmapName.c_str());
	m_checkMsg = checkMsg;
}


///////////////////////////////////////


UIButton::UIButton(void) // line 368
{
	m_state = 0; 
	m_isDisabled = 0;
}


UIButton::~UIButton(void) // line 374
{
}


hook_method<void (UIButton::*)(int x, int y)> UIButton::_OnLBtnDblClk(SAKEXE, "UIButton::OnLBtnDblClk");
void UIButton::OnLBtnDblClk(int x, int y) // line 378
{
	return (this->*_OnLBtnDblClk)(x, y);

	//TODO
}


hook_method<void (UIButton::*)(int x, int y)> UIButton::_OnLBtnDown(SAKEXE, "UIButton::OnLBtnDown");
void UIButton::OnLBtnDown(int x, int y) // line 383
{
	return (this->*_OnLBtnDown)(x, y);

	//TODO
}


hook_method<void (UIButton::*)(int x, int y)> UIButton::_OnMouseMove(SAKEXE, "UIButton::OnMouseMove");
void UIButton::OnMouseMove(int x, int y) // line 419
{
	return (this->*_OnMouseMove)(x, y);

	//TODO
}


hook_method<void (UIButton::*)(int x, int y)> UIButton::_OnLBtnUp(SAKEXE, "UIButton::OnLBtnUp");
void UIButton::OnLBtnUp(int x, int y) // line 450
{
	return (this->*_OnLBtnUp)(x, y);

	//TODO
}


hook_method<void (UIButton::*)(int x, int y)> UIButton::_OnMouseShape(SAKEXE, "UIButton::OnMouseShape");
void UIButton::OnMouseShape(int x, int y) // line 392
{
	return (this->*_OnMouseShape)(x, y);

	//TODO
}


hook_method<void (UIButton::*)(void)> UIButton::_OnDraw(SAKEXE, "UIButton::OnDraw");
void UIButton::OnDraw(void) // line 470
{
	return (this->*_OnDraw)();

	//TODO
}


hook_method<void (UIButton::*)(int x, int y)> UIButton::_OnMouseHover(SAKEXE, "UIButton::OnMouseHover");
void UIButton::OnMouseHover(int x, int y) // line 401
{
	return (this->*_OnMouseHover)(x, y);

	//TODO
}


hook_method<void (UIButton::*)(const char* toolTip)> UIButton::_SetToolTip(SAKEXE, "UIButton::SetToolTip");
void UIButton::SetToolTip(const char* toolTip) // line 414
{
	return (this->*_SetToolTip)(toolTip);

	m_toolTip = toolTip;
}


//hook_method<void (UIButton::*)(mystd::string text)> UIButton::_SetText(SAKEXE, "UIButton::SetText");
void UIButton::SetText(mystd::string text) // line ???
{
//	return (this->*_SetText)(text);

	m_text = text;
}


//hook_method<void (UIButton::*)(int isDisabled)> UIButton::_SetDiabled(SAKEXE, "UIButton::SetDiabled");
void UIButton::SetDiabled(int isDisabled) // line ???
{
//	return (this->*_SetDiabled)(isDisabled);

	m_isDisabled = isDisabled;
}


///////////////////////////////////////


UIBitmapButton::UIBitmapButton() // line 559-562
{
	m_bitmapWidth = 0;
	m_bitmapHeight = 0;
}


UIBitmapButton::~UIBitmapButton() // line 565-566
{
}


void UIBitmapButton::OnDraw() // line 592-609
{
	CBitmapRes* bitmapRes = ( m_state == BTN_NONE    ) ? (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp(m_normalBitmapName.c_str()))
	                      : ( m_state == BTN_DOWN    ) ? (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp(m_mouseonBitmapName.c_str()))
	                      : ( m_state == BTN_PRESSED ) ? (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp(m_pressedBitmapName.c_str()))
	                      :                              NULL; //NOTE: uninitialized in original code

	this->UIWindow::DrawBitmap(0, 0, bitmapRes, false);
}


void UIBitmapButton::SetBitmapName(const char* bitmapName, int buttonState) // line 569-589
{
	CBitmapRes* bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(bitmapName);
	if( bitmapRes == NULL )
		return;

	if( m_bitmapWidth < bitmapRes->m_width )
		m_bitmapWidth = bitmapRes->m_width;

	if( m_bitmapHeight < bitmapRes->m_height )
		m_bitmapHeight = bitmapRes->m_height;

	if( buttonState == BTN_NONE )
		m_normalBitmapName = bitmapName;
	else
	if( buttonState == BTN_DOWN )
		m_mouseonBitmapName = bitmapName;
	else
	if( buttonState == BTN_PRESSED )
		m_pressedBitmapName = bitmapName;
}


int UIBitmapButton::GetBitmapWidth()
{
	return m_bitmapWidth;
}


int UIBitmapButton::GetBitmapHeight()
{
	return m_bitmapHeight;
}


///////////////////////////////////////



UIEditCtrl::UIEditCtrl(void) // line 1217
{
	m_maxchar = 255;
	m_text.reserve(255);
	m_selectionCursor = 0;
	m_selectionOrigin = 0;
	m_maskchar = 0;
	m_isSingColorFrame = 1;
	m_r = 255;
	m_g = 255;
	m_b = 255;
	m_textR = 0;
	m_textG = 0;
	m_textB = 0;
	m_xOffset = 0;
	m_yOffset = 0;
}


UIEditCtrl::~UIEditCtrl(void) // line 1234
{
}


hook_method<void (UIEditCtrl::*)(int x, int y)> UIEditCtrl::_OnLBtnDown(SAKEXE, "UIEditCtrl::OnLBtnDown");
void UIEditCtrl::OnLBtnDown(int x, int y) // line 1239
{
	return (this->*_OnLBtnDown)(x, y);

	//TODO
}


hook_method<void (UIEditCtrl::*)(void)> UIEditCtrl::_OnDraw(SAKEXE, "UIEditCtrl::OnDraw");
void UIEditCtrl::OnDraw(void) // line 1319
{
	return (this->*_OnDraw)();

	//TODO
}


hook_method<void (UIEditCtrl::*)(void)> UIEditCtrl::_OnBeginEdit(SAKEXE, "UIEditCtrl::OnBeginEdit");
void UIEditCtrl::OnBeginEdit(void) // line 1260
{
	return (this->*_OnBeginEdit)();

	//TODO
}


hook_method<void (UIEditCtrl::*)(void)> UIEditCtrl::_OnFinishEdit(SAKEXE, "UIEditCtrl::OnFinishEdit");
void UIEditCtrl::OnFinishEdit(void) // line 1268
{
	return (this->*_OnFinishEdit)();

	//TODO
}


hook_method<void (UIEditCtrl::*)(const char* txt)> UIEditCtrl::_SetText(SAKEXE, "UIEditCtrl::SetText");
void UIEditCtrl::SetText(const char* txt) // line 1274
{
	return (this->*_SetText)(txt);

	m_text.replace(m_text.begin(), m_text.end(), txt, txt + strlen(txt));

	this->UIEditCtrl::SetTextByMaxChar();

	if( g_windowMgr.UIWindowMgr::GetFocusEdit() == this )
	{
		g_language->CLanguage::SetInput(m_text.c_str()); //inlined
	}

	if( g_windowMgr.UIWindowMgr::GetFocusEdit() == this )
	{
		g_language->CLanguage::SetSelection(0, g_language->CLanguage::GetInputSize());
	}
	else
	{
		m_selectionOrigin = 0;
		m_selectionCursor = m_text.size();
	}
}


hook_method<bool (UIEditCtrl::*)(void)> UIEditCtrl::_CanGetFocus(SAKEXE, "UIEditCtrl::CanGetFocus");
bool UIEditCtrl::CanGetFocus(void) // line 616 (UISys.h)
{
	return (this->*_CanGetFocus)();

	//TODO
}


hook_method<int (UIEditCtrl::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIEditCtrl::_SendMsg(SAKEXE, "UIEditCtrl::SendMsg");
int UIEditCtrl::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 1550
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	//TODO
}


//hook_method<void (UIEditCtrl::*)(int limit)> UIEditCtrl::_SetTextLimit(SAKEXE, "UIEditCtrl::SetTextLimit");
void UIEditCtrl::SetTextLimit(int limit) // line ????
{
//	return (this->*_SetTextLimit)(limit);

	m_maxchar = limit;
}


hook_method<void (UIEditCtrl::*)(int r, int g, int b)> UIEditCtrl::_SetTextColor(SERVER, "UIEditCtrl::SetTextColor");
void UIEditCtrl::SetTextColor(int r, int g, int b) // line 1302
{
	return (this->*_SetTextColor)(r, g, b);

	//TODO
}


hook_method<void (UIEditCtrl::*)(int r, int g, int b)> UIEditCtrl::_SetFrameColor(SAKEXE, "UIEditCtrl::SetFrameColor");
void UIEditCtrl::SetFrameColor(int r, int g, int b) // line 1311
{
	return (this->*_SetFrameColor)(r, g, b);

	//TODO
}


hook_method<void (UIEditCtrl::*)(void)> UIEditCtrl::_MakeSelect(SAKEXE, "UIEditCtrl::MakeSelect");
void UIEditCtrl::MakeSelect(void) // line 1243
{
	return (this->*_MakeSelect)();

	//TODO
}


hook_method<const char* (UIEditCtrl::*)(void)> UIEditCtrl::_GetText(SAKEXE, "UIEditCtrl::GetText");
const char* UIEditCtrl::GetText(void) // line 1287
{
	return (this->*_GetText)();

	//TODO
}


hook_method<int (UIEditCtrl::*)(void)> UIEditCtrl::_GetTextSize(SAKEXE, "UIEditCtrl::GetTextSize");
int UIEditCtrl::GetTextSize(void) // line 1294
{
	return (this->*_GetTextSize)();

	//TODO
}


hook_method<void (UIEditCtrl::*)(void)> UIEditCtrl::_SetTextByMaxChar(SAKEXE, "UIEditCtrl::SetTextByMaxChar");
void UIEditCtrl::SetTextByMaxChar(void) // line 1042
{
	return (this->*_SetTextByMaxChar)();

	//TODO
}


///////////////////////////////////////


UIEditCtrl2::UIEditCtrl2(void) // line 1568
{
}


UIEditCtrl2::~UIEditCtrl2(void) // line 1572
{
}


///////////////////////////////////////


UIBitmapEditCtrl::UIBitmapEditCtrl(void) // inlined
{
}


UIBitmapEditCtrl::~UIBitmapEditCtrl(void) // implicit
{
}


hook_method<void (UIBitmapEditCtrl::*)(void)> UIBitmapEditCtrl::_OnDraw(SAKEXE, "UIBitmapEditCtrl::OnDraw");
void UIBitmapEditCtrl::OnDraw(void) // line 1597
{
	return (this->*_OnDraw)();

	CBitmapRes* bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp(m_bitmapName.c_str()));
	this->UIWindow::DrawBitmap(0, 0, bitmapRes, false);
	m_yOffset = 3;
}


hook_method<void (UIBitmapEditCtrl::*)(const char* bitmapName)> UIBitmapEditCtrl::_SetBitmap(SAKEXE, "UIBitmapEditCtrl::SetBitmap");
void UIBitmapEditCtrl::SetBitmap(const char* bitmapName) // line 1606
{
	return (this->*_SetBitmap)(bitmapName);

	CBitmapRes* bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp(m_bitmapName.c_str()));
	m_bitmapName = bitmapName;
	m_w = bitmapRes->m_width;
	m_h = bitmapRes->m_height;
}


///////////////////////////////////////


hook_method<void (UIChatEditCtrl::*)(void)> UIChatEditCtrl::_StoreInHistory(SAKEXE, "UIChatEditCtrl::StoreInHistory");
void UIChatEditCtrl::StoreInHistory(void) // line 1801
{
	return (this->*_StoreInHistory)();

	//TODO
}


///////////////////////////////////////


UIWhisperEditCtrl::UIWhisperEditCtrl(void) // line 1618
{
	m_curHis = 0;
}


hook_method<void (UIWhisperEditCtrl::*)(void)> UIWhisperEditCtrl::_OnBeginEdit(SAKEXE, "UIWhisperEditCtrl::OnBeginEdit");
void UIWhisperEditCtrl::OnBeginEdit(void) // line 1623
{
	return (this->*_OnBeginEdit)();

	//TODO
}


hook_method<void (UIWhisperEditCtrl::*)(void)> UIWhisperEditCtrl::_OnFinishEdit(SAKEXE, "UIWhisperEditCtrl::OnFinishEdit");
void UIWhisperEditCtrl::OnFinishEdit(void) // line 1629
{
	return (this->*_OnFinishEdit)();

	//TODO
}


hook_method<void (UIWhisperEditCtrl::*)(const char* txt)> UIWhisperEditCtrl::_SetText(SAKEXE, "UIWhisperEditCtrl::SetText");
void UIWhisperEditCtrl::SetText(const char* txt) // line 1635
{
	return (this->*_SetText)(txt);

	this->UIEditCtrl::SetText(txt);
	if( strlen(txt) == 0 )
		m_curHis = m_hisChat.size();
}


hook_method<int (UIWhisperEditCtrl::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIWhisperEditCtrl::_SendMsg(SAKEXE, "UIWhisperEditCtrl::SendMsg");
int UIWhisperEditCtrl::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 1682
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	//TODO
}


hook_method<void (UIWhisperEditCtrl::*)(void)> UIWhisperEditCtrl::_StoreInHistory(SAKEXE, "UIWhisperEditCtrl::StoreInHistory");
void UIWhisperEditCtrl::StoreInHistory(void) // line 1641
{
	return (this->*_StoreInHistory)();

	//TODO
}


///////////////////////////////////////


UIResizer::UIResizer(void) // line 1826
{
	m_type = RT_LEFT;
	m_parentWidth = 0;
	m_parentHeight = 0;
	m_color = 0xFFFF00FF;
	m_backColor = 0xFFFF00FF;
}


hook_method<void (UIResizer::*)(void)> UIResizer::_OnDraw(SAKEXE, "UIResizer::OnDraw");
void UIResizer::OnDraw(void) // line 1835
{
	return (this->*_OnDraw)();

	if( m_bitmapName.size() != 0 )
	{
		CBitmapRes* bitmap = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp(m_bitmapName.c_str()));
		this->UIWindow::DrawBitmap(0, 0, bitmap, 0);
	}
	else
	{
		this->UIWindow::ClearDC(m_backColor);
		this->UIWindow::DrawBox(0, 0, m_w, 2, m_color);
	}
}


hook_method<void (UIResizer::*)(unsigned long color, unsigned long backColor)> UIResizer::_SetColor(SAKEXE, "?SetColor@UIResizer@@QAEXKK@Z");
void UIResizer::SetColor(unsigned long color, unsigned long backColor) // line 1846
{
	return (this->*_SetColor)(color, backColor);

	this->Invalidate();
	m_color = color;
	m_backColor = backColor;
}


hook_method<void (UIResizer::*)(const char* bitmapName)> UIResizer::_SetBitmap(SAKEXE, "UIResizer::SetBitmap");
void UIResizer::SetBitmap(const char* bitmapName) // line 1853
{
	return (this->*_SetBitmap)(bitmapName);

	m_bitmapName = bitmapName;
	CBitmapRes* bitmap = (CBitmapRes*)g_resMgr().CResMgr::Get(m_bitmapName.c_str());
	m_w = bitmap->m_width;
	m_h = bitmap->m_height;
}


hook_method<void (UIResizer::*)(RESIZERTYPE type)> UIResizer::_SetType(SAKEXE, "UIResizer::SetType");
void UIResizer::SetType(RESIZERTYPE type) // line 1861
{
	return (this->*_SetType)(type);

	m_type = type;
}


hook_method<void (UIResizer::*)(int x, int y)> UIResizer::_OnLBtnDown(SAKEXE, "UIResizer::OnLBtnDown");
void UIResizer::OnLBtnDown(int x, int y) // line 1866
{
	return (this->*_OnLBtnDown)(x, y);

	g_windowMgr.UIWindowMgr::SetCapture(this);

	m_startX = x;
	m_startY = y;

	if( m_parent != NULL )
	{
		m_parentWidth = m_parent->UIWindow::GetWidth();
		m_parentHeight = m_parent->UIWindow::GetHeight();
	}

	this->UIWindow::GetGlobalCoor(m_startX, m_startY);
}


hook_method<void (UIResizer::*)(int x, int y)> UIResizer::_OnMouseShape(SAKEXE, "UIResizer::OnMouseShape");
void UIResizer::OnMouseShape(int x, int y) // line 1878
{
	return (this->*_OnMouseShape)(x, y);

	if( g_windowMgr.UIWindowMgr::GetCapture() == this )
	{
		g_modeMgr.CModeMgr::GetCurMode()->CMode::SetCursorAction(2);
	}
	else
	if( x < 0 || x >= m_w || y < 0 || y > m_h )
	{
		if( g_windowMgr.UIWindowMgr::GetCapture() != this )
			g_modeMgr.CModeMgr::GetCurMode()->CMode::SetCursorAction(0);
	}
	else
	{
		g_modeMgr.CModeMgr::GetCurMode()->CMode::SetCursorAction(2);
	}
}


hook_method<void (UIResizer::*)(int x, int y)> UIResizer::_OnMouseHover(SAKEXE, "UIResizer::OnMouseHover");
void UIResizer::OnMouseHover(int x, int y) // line 1892
{
	return (this->*_OnMouseHover)(x, y);

	;
}


hook_method<void (UIResizer::*)(int x, int y)> UIResizer::_OnMouseMove(SAKEXE, "UIResizer::OnMouseMove");
void UIResizer::OnMouseMove(int x, int y) // line 1895
{
	return (this->*_OnMouseMove)(x, y);

	if( g_windowMgr.UIWindowMgr::GetCapture() != this )
		return;

	this->UIWindow::GetGlobalCoor(x, y);

	if( m_parent == NULL )
		return;

	int width = m_parentWidth;
	int height = m_parentHeight;
	int deltaX = x - m_startX;
	int deltaY = y - m_startY;

	switch( m_type )
	{
	case RT_LEFT:
		width -= deltaX;
		break;
	case RT_RIGHT:
		width += deltaX;
		break;
	case RT_UP:
		height -= deltaY;
		break;
	case RT_DOWN:
		height += deltaY;
		break;
	case RT_UPLEFT:
		width -= deltaX;
		height -= deltaY;
		break;
	case RT_UPRIGHT:
		width += deltaX;
		height -= deltaY;
		break;
	case RT_DOWNLEFT:
		width -= deltaX;
		height += deltaY;
		break;
	case RT_DOWNRIGHT:
		width += deltaX;
		height += deltaY;
		break;
	default:
		break;
	}

	m_parent->SendMsg(this, 14, m_type, width, height);
}


hook_method<void (UIResizer::*)(int x, int y)> UIResizer::_OnLBtnUp(SAKEXE, "UIResizer::OnLBtnUp");
void UIResizer::OnLBtnUp(int x, int y) // line 1944
{
	return (this->*_OnLBtnUp)(x, y);

	if( g_windowMgr.UIWindowMgr::GetCapture() != this )
		return;

	if( m_parent != NULL )
		m_parent->RefreshSnap();

	g_windowMgr.UIWindowMgr::ReleaseCapture();
}


///////////////////////////////////////


UIRadioBtn::UIRadioBtn(void) // line 2000
{
	m_state = 0;
	m_isEnabled = 1;
	m_id = 125;
}


UIRadioBtn::~UIRadioBtn(void) // line 2007
{
}


hook_method<void (UIRadioBtn::*)(void)> UIRadioBtn::_OnDraw(SAKEXE, "UIRadioBtn::OnDraw");
void UIRadioBtn::OnDraw(void) // line 2017
{
	return (this->*_OnDraw)();

	//TODO
}


hook_method<void (UIRadioBtn::*)(int x, int y)> UIRadioBtn::_OnLBtnDown(SAKEXE, "UIRadioBtn::OnLBtnDown");
void UIRadioBtn::OnLBtnDown(int x, int y) // line 2035
{
	return (this->*_OnLBtnDown)(x, y);

	//TODO
}


hook_method<int (UIRadioBtn::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIRadioBtn::_SendMsg(SAKEXE, "UIRadioBtn::SendMsg");
int UIRadioBtn::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 2041
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	//TODO
}


hook_method<void (UIRadioBtn::*)(const char* text)> UIRadioBtn::_SetText(SAKEXE, "UIRadioBtn::SetText");
void UIRadioBtn::SetText(const char* text) // line 2011
{
	return (this->*_SetText)(text);

	//TODO
}


///////////////////////////////////////


UIChatRoomTitle::UIChatRoomTitle(void) // line 2055
{
}


UIChatRoomTitle::~UIChatRoomTitle(void) // line 2059
{
}


///////////////////////////////////////


UIMerchantShopTitle::UIMerchantShopTitle(void) // line 2189
{
}


UIMerchantShopTitle::~UIMerchantShopTitle(void) // line 2193
{
}


///////////////////////////////////////
