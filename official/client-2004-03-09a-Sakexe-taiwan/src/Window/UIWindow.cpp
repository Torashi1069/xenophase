#include "Globals.h"
#include "Mode.h"
#include "ModeMgr.h"
#include "3dLib/DrawUtil.h"
#include "Window/UIWindow.h"
#include "Window/UISys.h"
#include "Window/UIWindowMgr.h"


UIWindow::UIWindow() // line 142-160 (Window/UISys.cpp)
{
	m_x = 0;
	m_y = 0;
	m_w = 0;
	m_h = 0;
	m_parent = NULL;
//	m_children.clear();
	m_state = 0;
	m_stateCnt = 0;
	m_dc = NULL;
	m_isDirty = TRUE;
	m_id = ID_NOTHING;
	m_show = TRUE;
	m_trans = 0xFF;
	m_transTarget = 0xFF;
	m_transTime = timeGetTime();
}


UIWindow::~UIWindow() // line 163-168 (Window/UISys.cpp)
{
	this->UIWindow::Destroy(); //inlined
	g_windowMgr.UIWindowMgr::RemoveFromNameWaitingWindowList(this);
}


void UIWindow::Create(int cx, int cy) // line 220-224 (Window/UISys.cpp)
{
	this->Resize(cx, cy); //inlined
	this->Invalidate();
	this->OnCreate(cx, cy);
	this->OnSize(cx, cy);
}


void UIWindow::Destroy() // line 238-245 (Window/UISys.cpp)
{
	this->OnDestroy();

	if( m_dc != NULL )
	{
		delete m_dc;
		m_dc = NULL;
	}

	this->UIWindow::RemoveAllChildren(); //inlined
}


void UIWindow::AddChild(UIWindow* window) // line 186-189 (Window/UISys.cpp)
{
	window->m_parent = this;
	m_children.push_back(window);
}


void UIWindow::RemoveChild(UIWindow* window) // line 192-198 (Window/UISys.cpp)
{
	mystd::list<UIWindow*>::iterator it;

	for( it = m_children.begin(); it != m_children.end(); ++it )
		if( *it == window )
			break;

	if( it != m_children.end() )
		m_children.erase(it);

	delete window;
}


void UIWindow::RemoveAllChildren() // line 201-207 (Window/UISys.cpp)
{
	for( mystd::list<UIWindow*>::iterator it = m_children.begin(); it != m_children.end(); ++it )
		delete *it;

	m_children.clear();
}


void UIWindow::ClearAllChildrenState() // line 210-217 (Window/UISys.cpp)
{
	m_state = 0;
	this->Invalidate();

	for( mystd::list<UIWindow*>::iterator it = m_children.begin(); it != m_children.end(); ++it )
		(*it)->UIWindow::ClearAllChildrenState();
}


void UIWindow::InvalidateChildren() // line 326-333 (Window/UISys.cpp)
{
	m_isDirty = TRUE;
	this->InvalidateWallPaper();

	for( mystd::list<UIWindow*>::iterator it = m_children.begin(); it != m_children.end(); ++it )
		(*it)->UIWindow::InvalidateChildren();
}


void UIWindow::SetId(int id) // line ???-???
{
	m_id = id;
}


int UIWindow::GetId() // line ???-???
{
	return m_id;
}


BOOL UIWindow::IsFamily(UIWindow* window) // line 248-259 (Window/UISys.cpp)
{
	if( window == NULL )
		return FALSE;

	if( window == this )
		return TRUE;

	mystd::list<UIWindow*>::iterator it;

	for( it = m_children.begin(); it != m_children.end(); ++it )
		if( (*it)->UIWindow::IsFamily(window) )
			break;

	return ( it != m_children.end() ) ? TRUE : FALSE;
}


void UIWindow::Invalidate() // line 321-323 (Window/UISys.cpp)
{
	m_isDirty = TRUE;
}


void UIWindow::InvalidateWallPaper() // line 115 (Window/UISys.h)
{
}


UIWindow* UIWindow::HitTest(int x, int y) // line 708-725 (Window/UISys.cpp)
{
	if( !this->ShouldDoHitTest() || m_show == FALSE || x < m_x || x >= m_x + m_w || y < m_y || y >= m_y + m_h )
		return NULL;

	UIWindow* result = this;

	for( mystd::list<UIWindow*>::reverse_iterator it = m_children.rbegin(); it != m_children.rend(); ++it )
	{
		result = (*it)->UIWindow::HitTest(x - m_x, y - m_y);
		if( result != NULL )
			break; // found.
	}

	return result;
}


void UIWindow::DoDraw(BOOL blitToParent) // line 686-705 (Window/UISys.cpp)
{
	if( m_isDirty )
	{
		this->OnDraw();
		m_isDirty = FALSE;
		blitToParent = TRUE;
	}

	for( mystd::list<UIWindow*>::iterator it = m_children.begin(); it != m_children.end(); ++it )
		(*it)->UIWindow::DoDraw(blitToParent);

	if( blitToParent && m_parent != NULL )
		m_parent->m_dc->CopyRect(m_x, m_y, m_w, m_h, m_dc);
}


void UIWindow::Resize(int cx, int cy) // line 227-235 (Window/UISys.cpp)
{
	delete m_dc;
	m_dc = g_3dDevice.C3dDevice::CreateDCBuffer(cx, cy);
	m_w = cx;
	m_h = cy;

	this->Invalidate();
}


bool UIWindow::IsFrameWnd() // line 119 (Window/UISys.h)
{
	return false;
}


bool UIWindow::IsUpdateNeed() // line 120 (Window/UISys.h)
{
	return false;
}


void UIWindow::Move(int x, int y) // line 298-301 (Window/UISys.cpp)
{
	m_x = x;
	m_y = y;
}


bool UIWindow::CanGetFocus() // line 122 (Window/UISys.h)
{
	return false;
}


bool UIWindow::GetTransBoxInfo(BOXINFO* boxInfo) // line 123 (Window/UISys.h)
{
	return false;
}


bool UIWindow::IsTransmitMouseInput() // line 124 (Window/UISys.h)
{
	return false;
}


bool UIWindow::ShouldDoHitTest() // line 125 (Window/UISys.h)
{
	return true;
}


void UIWindow::DragAndDrop(int x, int y, const DRAG_INFO* const dragInfo) // line 171-174 (Window/UISys.cpp)
{
	g_modeMgr.CModeMgr::GetCurMode()->SendMsg(MM_CANCEL_DRAG, 0, 0, 0);
}


void UIWindow::StoreInfo() // line 127 (Window/UISys.h)
{
}


void UIWindow::SaveOriginalPos() // line 128 (Window/UISys.h)
{
}


void UIWindow::MoveDelta(int deltaDragX, int deltaDragY) // line 129 (Window/UISys.h)
{
}


bool UIWindow::IsChildOf(UIWindow* win) // line 336-343 (Window/UISys.cpp)
{
	UIWindow* p;

	for( p = m_parent; p != NULL; p = p->m_parent )
		if( p == win )
			break;

	return ( p != NULL );
}


UIWindow* UIWindow::GetNextSiblingOf(UIWindow* wnd) // line 262-277 (Window/UISys.cpp)
{
	mystd::list<UIWindow*>::iterator it;

	// find the window in the list of children
	for( it = m_children.begin(); it != m_children.end(); ++it )
		if( *it == wnd && (*it)->CanGetFocus() )
			break; // found.

	if( it == m_children.end() )
		return NULL;

	// find the following active sibling
	for( ++it; it != m_children.end(); ++it )
		if( (*it)->CanGetFocus() )
			break; // found.

	if( it == m_children.end() )
		return NULL;

	return *it;
}


UIWindow* UIWindow::GetPrevSiblingOf(UIWindow* wnd) // line 280-295 (Window/UISys.cpp)
{
	mystd::list<UIWindow*>::reverse_iterator it;

	// find the window in the list of children
	for( it = m_children.rbegin(); it != m_children.rend(); ++it )
		if( *it == wnd && (*it)->CanGetFocus() )
			break; // found.

	if( it == m_children.rend() )
		return NULL;

	// find the preceding active sibling
	for( ++it; it != m_children.rend(); ++it )
		if( (*it)->CanGetFocus() )
			break; // found.

	if( it == m_children.rend() )
		return NULL;

	return *it;
}


UIWindow* UIWindow::GetAncestor() // line 177-183 (Window/UISys.cpp)
{
	UIWindow* result = this;

	for( UIWindow* i = m_parent; i != NULL; i = i->m_parent )
		result = i;

	return result;
}


void UIWindow::GetGlobalCoor(int& x, int& y) // line 309-318 (Window/UISys.cpp)
{
	x += m_x;
	y += m_y;

	for( UIWindow* i = m_parent; i != NULL; i = i->m_parent )
	{
		x += i->m_x;
		y += i->m_y;
	}
}


BOOL UIWindow::IsShow() // line ???-???
{
	return m_show;
}


COLORREF UIWindow::GetColor() // line 748-760 (Window/UISys.cpp)
{
	if( m_trans < m_transTarget )
	{
		if( m_transTarget < m_trans + ((timeGetTime() - m_transTime) >> 4) )
		{
			m_trans = m_transTarget;
		}
		else
		{
			m_trans += (timeGetTime() - m_transTime) >> 4;
		}
	}
	else
	if( m_trans > m_transTarget )
	{
		if( m_transTarget > m_trans - ((timeGetTime() - m_transTime) >> 4) )
		{
			m_trans = m_transTarget;
		}
		else
		{
			m_trans -= (timeGetTime() - m_transTime) >> 4;
		}
	}

	return (m_trans << 24) + 0x00FFFFFF;
}


void UIWindow::SetShow(BOOL visible) // line 138 (Window/UISys.h)
{
	m_show = visible;
}


void UIWindow::OnCreate(int cx, int cy) // line 139 (Window/UISys.h)
{
}


void UIWindow::OnDestroy() // line 140 (Window/UISys.h)
{
}


void UIWindow::OnProcess() // line 141 (Window/UISys.h)
{
}


void UIWindow::OnDraw() // line 142 (Window/UISys.h)
{
}


void UIWindow::OnDraw2() // line 143 (Window/UISys.h)
{
}


void UIWindow::OnRun() // line 144 (Window/UISys.h)
{
}


void UIWindow::OnSize(int cx, int cy) // line 145 (Window/UISys.h)
{
}


void UIWindow::OnBeginEdit() // line 146 (Window/UISys.h)
{
}


void UIWindow::OnFinishEdit() // line 147 (Window/UISys.h)
{
}


void UIWindow::OnLBtnDown(int x, int y) // line 148 (Window/UISys.h)
{
}


void UIWindow::OnLBtnDblClk(int x, int y) // line 149 (Window/UISys.h)
{
}


void UIWindow::OnMouseMove(int x, int y) // line 150 (Window/UISys.h)
{
}


void UIWindow::OnMouseHover(int x, int y) // line 151 (Window/UISys.h)
{
}


void UIWindow::OnMouseShape(int x, int y) // line 304-306 (Window/UISys.cpp)
{
	g_modeMgr.CModeMgr::GetCurMode()->CMode::SetCursorAction(0);
}


void UIWindow::OnLBtnUp(int x, int y) // line 153 (Window/UISys.h)
{
}


void UIWindow::OnRBtnDown(int x, int y) // line 154 (Window/UISys.h)
{
}


void UIWindow::OnRBtnUp(int x, int y) // line 155 (Window/UISys.h)
{
}


void UIWindow::OnRBtnDblClk(int x, int y) // line 156 (Window/UISys.h)
{
}


void UIWindow::OnWheel(int wheel) // line 157 (Window/UISys.h)
{
}


void UIWindow::RefreshSnap() // line 158 (Window/UISys.h)
{
}


int UIWindow::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 728-745 (Window/UISys.cpp)
{
	switch( message )
	{
	case UM_DEFPUSH:
		if( m_parent != NULL )
			m_parent->SendMsg(this, UM_DEFPUSH, 0, 0, 0);
	break;
	case UM_CANCELPUSH:
		if( m_parent != NULL )
			m_parent->SendMsg(this, UM_CANCELPUSH, 0, 0, 0);
	break;
	};

	return 0;
}


int UIWindow::GetX() // line ???-???
{
	return m_x;
}


int UIWindow::GetY() // line ???-???
{
	return m_y;
}


int UIWindow::GetHeight() // line ???-???
{
	return m_h;
}


int UIWindow::GetWidth() // line ???-???
{
	return m_w;
}


void UIWindow::DrawSurface() // @custom
{
	m_dc->DrawSurface(m_x, m_y, m_w, m_h, this->GetColor());
}


void UIWindow::DrawBitmap(int x, int y, CBitmapRes* bitmap, bool drawOnlyNoTrans) // line 346-351 (Window/UISys.cpp)
{
	if( m_dc == NULL || bitmap == NULL )
		return;

	m_dc->Update(x, y, bitmap->m_width, bitmap->m_height, bitmap->m_data, drawOnlyNoTrans);
}


void UIWindow::TextOutA(int x, int y, const char* text, int textLen, int fontType, int fontHeight, COLORREF colorRef) // line 404-414 (Window/UISys.cpp)
{
	if( textLen == 0 )
		textLen = strlen(text);

	DrawDC dc(m_dc);
	dc.DrawDC::SetFont(fontType, fontHeight, false);

	dc.DrawDC::SetTextColor(colorRef);
	dc.DrawDC::TextOutA(x, y, text, textLen);
}


void UIWindow::TextOutWithRightAlign(int x, int y, const char* text, int textLen, int fontType, int fontHeight, COLORREF colorRef) // line 417-431 (Window/UISys.cpp)
{
	if( textLen == 0 )
		textLen = strlen(text);

	DrawDC dc(m_dc);
	dc.DrawDC::SetFont(fontType, fontHeight, false);

	SIZE size;
	dc.DrawDC::GetTextExtentPoint32A(text, strlen(text), &size);

	dc.DrawDC::SetTextColor(colorRef);
	dc.DrawDC::TextOutA(x - size.cx, y, text, textLen);
}


void UIWindow::TextOutWithDecoration(int x, int y, const char* text, int textLen, COLORREF* colorRef, int fontType, int fontHeight) // line 434-464 (Window/UISys.cpp)
{

	if( textLen == 0 )
		textLen = strlen(text);

	DrawDC dc(m_dc);
	dc.DrawDC::SetFont(fontType, fontHeight, false);

	const char* p = text;
	const char* text_end = &text[textLen];
	while( p < text_end )
	{
		// skip color markup
		p = this->UIWindow::InterpretColor(p, colorRef);

		// select text up to next color mark
		const char* nextp = this->UIWindow::FindColorMark(p, text_end);

		if( nextp == p )
			continue;

		dc.DrawDC::SetTextColor(*colorRef);
		dc.DrawDC::TextOutA(x, y, p, nextp - p);

		SIZE size;
		dc.DrawDC::GetTextExtentPoint32A(p, nextp - p, &size);

		x += size.cx;
		p = nextp;
	}
}


void UIWindow::TextOutWithShadow(int x, int y, const char* text, int textLen, COLORREF colorText, COLORREF colorShadow, int fontType, int fontHeight) // line 467-480 (Window/UISys.cpp)
{
	if( textLen == 0 )
		textLen = strlen(text);

	DrawDC dc(m_dc);
	dc.DrawDC::SetFont(fontType, fontHeight, false);

	dc.DrawDC::SetTextColor(colorShadow);
	dc.DrawDC::TextOutA(x + 1, y + 1, text, textLen);

	dc.DrawDC::SetTextColor(colorText);
	dc.DrawDC::TextOutA(x, y, text, textLen);
}


void UIWindow::TextOutWithOutline(int x, int y, const char* text, int textLen, COLORREF colorText, COLORREF colorOutline, int fontType, int fontHeight, bool bold) // line 483-499 (Window/UISys.cpp)
{
	if( textLen == 0 )
		textLen = strlen(text);

	DrawDC dc(m_dc);
	dc.DrawDC::SetFont(fontType, fontHeight, bold);

	dc.DrawDC::SetTextColor(colorOutline);
	dc.DrawDC::TextOutA(x - 1, y, text, textLen);
	dc.DrawDC::TextOutA(x + 1, y, text, textLen);
	dc.DrawDC::TextOutA(x, y - 1, text, textLen);
	dc.DrawDC::TextOutA(x, y + 1, text, textLen);

	dc.DrawDC::SetTextColor(colorText);
	dc.DrawDC::TextOutA(x, y, text, textLen);
}


void UIWindow::TextOutVertical(int x, int y, const char* text, int textLen, int fontType, int fontHeight, COLORREF colorRef) // line 502-533 (Window/UISys.cpp)
{
	if( textLen == 0 )
		textLen = strlen(text);

	DrawDC dc(m_dc);
	dc.DrawDC::SetFont(fontType, fontHeight, false);
	dc.DrawDC::SetTextColor(colorRef);

	int maxWidth = 0;
	const char* textEnd = &text[textLen];

	const char* p = text;
	while( p < textEnd )
	{
		const char* nextp = CharNextExA((WORD)g_codePage, p, 0);

		SIZE size;
		dc.DrawDC::GetTextExtentPoint32A(p, nextp - p, &size);

		if( maxWidth <= size.cx )
			maxWidth = size.cx;

		p = nextp;
	}

	const char* p2 = text;
	while( p2 < textEnd )
	{
		const char* nextp = CharNextExA((WORD)g_codePage, p2, 0);

		SIZE size;
		dc.DrawDC::GetTextExtentPoint32A(p2, nextp - p2, &size);

		dc.DrawDC::TextOutA(x + (maxWidth - size.cx) / 2, y, p2, nextp - p2);
		y += size.cy;

		p2 = nextp;
	}
}


void UIWindow::TextOutWithOutlineVertical(int x, int y, const char* text, int textLen, COLORREF colorText, COLORREF colorOutline, int fontType, int fontHeight, bool bold) // line 536-556 (Window/UISys.cpp)
{
	if( textLen == 0 )
		textLen = strlen(text);

	DrawDC dc(m_dc);
	dc.DrawDC::SetFont(fontType, fontHeight, bold);

	SIZE size;
	dc.DrawDC::GetTextExtentPoint32A(text, textLen, &size);

	dc.DrawDC::SetTextColor(colorOutline);
	dc.DrawDC::TextOutA(size.cy + x - 1, y, text, textLen);
	dc.DrawDC::TextOutA(size.cy + x + 1, y, text, textLen);
	dc.DrawDC::TextOutA(size.cy + x, y - 1, text, textLen);
	dc.DrawDC::TextOutA(size.cy + x, y + 1, text, textLen);

	dc.DrawDC::SetTextColor(colorText);
	dc.DrawDC::TextOutA(size.cy + x, y, text, textLen);
}


void UIWindow::TextOutWithTwoColors(int x, int y, const char* text, COLORREF colorRef, COLORREF colorRef2, int textLen, int fontType, int fontHeight) // line 560-573 (Window/UISys.cpp)
{
	if( textLen == 0 )
		textLen = strlen(text);

	DrawDC dc(m_dc);
	dc.DrawDC::SetFont(fontType, fontHeight, false);

	dc.DrawDC::SetTextColor(colorRef);
	dc.DrawDC::TextOutA(x, y, text, textLen);

	dc.DrawDC::SetTextColor(colorRef2);
	dc.DrawDC::TextOutA(x - 1, y, text, textLen);
}


int UIWindow::GetTextWidth(const char* text, int textLen, int fontType, int fontHeight, bool bold) // line 576-592 (Window/UISys.cpp)
{
	if( text == NULL )
		return 0;

	if( textLen == 0 )
		textLen = strlen(text);

	DrawDC dc(m_dc);
	dc.DrawDC::SetFont(fontType, fontHeight, bold);

	SIZE size;
	dc.DrawDC::GetTextExtentPoint32A(text, textLen, &size);

	return size.cx;
}


int UIWindow::GetTextHeight(const char* text, int textLen, int fontType, int fontHeight, bool bold) // line 595-611 (Window/UISys.cpp)
{
	if( text == NULL )
		return 0;

	if( textLen == 0 )
		textLen = strlen(text);

	DrawDC dc(m_dc);
	dc.DrawDC::SetFont(fontType, fontHeight, bold);

	SIZE size;
	dc.DrawDC::GetTextExtentPoint32A(text, textLen, &size);

	return size.cy;
}


int UIWindow::GetTextHeightVertical(const char* text, int textLen, int fontType, int fontHeight, bool bold) // line 614-638 (Window/UISys.cpp)
{
	if( text == NULL )
		return 0;

	if( textLen == 0 )
		textLen = strlen(text);

	DrawDC dc(m_dc);
	dc.DrawDC::SetFont(fontType, fontHeight, bold);

	int result = 0;

	const char* p = text;
	const char* textEnd = &text[textLen];
	while( p < textEnd )
	{
		const char* nextp = CharNextExA((WORD)g_codePage, p, 0);

		SIZE size;
		dc.DrawDC::GetTextExtentPoint32A(p, nextp - p, &size);

		result += size.cy;
		p = nextp;
	}

	return result;
}


void UIWindow::ClearDC(COLORREF color) // line 641-645 (Window/UISys.cpp)
{
	if( m_dc != NULL )
		m_dc->ClearSurface(NULL, color);
}


void UIWindow::ClearDCRect(COLORREF color, RECT& rect) // line 648-652 (Window/UISys.cpp)
{
	if( m_dc != NULL )
		m_dc->ClearSurface(&rect, color);
}


void UIWindow::DrawBox(int x, int y, int cx, int cy, COLORREF color) // line 679-683 (Window/UISys.cpp)
{
	RECT r;
	r.left = max(x, 0);
	r.top = max(y, 0);
	r.right = min(x + cx, m_w);
	r.bottom = min(y + cy, m_h);

	m_dc->ClearSurface(&r, color);
}


void UIWindow::DrawTriangleDC(int x1, int y1, int x2, int y2, int x3, int y3, COLORREF color) // line 655-676 (Window/UISys.cpp)
{
	HDC hdc;
	if( !m_dc->GetDC(&hdc) )
		return;

	tagPOINT point[3] = { x1, y1, x2, y2, x3, y3 };
	HRGN hrgn = CreatePolygonRgn(point, countof(point), WINDING);
	HBRUSH hbrush = CreateSolidBrush(color);
	FillRgn(hdc, hrgn, hbrush);
	DeleteObject(hrgn);
	DeleteObject(hbrush);

	m_dc->ReleaseDC(hdc);
}


static BYTE hex_table[256] = {
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9,   0,   0,   0,   0,   0,   0,
	  0, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  0, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
};


const char* UIWindow::InterpretColor(const char* color_text, COLORREF* colorRef) // line 373-390 (Window/UISys.cpp)
{
	if( color_text == NULL )
		return color_text;

	if( *color_text != '^' )
		return color_text;

	BYTE r = (hex_table[color_text[1]] << 4) + (hex_table[color_text[2]] << 0);
	BYTE g = (hex_table[color_text[3]] << 4) + (hex_table[color_text[4]] << 0);
	BYTE b = (hex_table[color_text[5]] << 4) + (hex_table[color_text[6]] << 0);
	*colorRef = RGB(r, g, b);

	return color_text + 7;
}


const char* UIWindow::FindColorMark(const char* text, const char* text_end) // line 393-401 (Window/UISys.cpp)
{
	if( text == NULL )
		return NULL;

	const char* result = text;

	while( result < text_end )
	{
		if( *result == '^' )
			break; // found.

		result = CharNextExA((WORD)g_codePage, result, 0);
	}

	return result;
}
