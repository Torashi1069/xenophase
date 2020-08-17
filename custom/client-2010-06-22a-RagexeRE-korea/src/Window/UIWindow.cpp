#include "Globals.h"
#include "Mode.h"
#include "ModeMgr.h"
#include "3dLib/DC.h"
#include "3dLib/Device.h"
#include "3dLib/DrawUtil.h"
#include "Resource/Bitmap.h"
#include "Window/UISys.h"
#include "Window/UIWindow.h"
#include "Window/UIWindowMgr.h"


UIWindow::UIWindow()
{
	m_x = 0;
	m_y = 0;
	m_w = 0;
	m_h = 0;
	m_parent = NULL;
	m_state = 0;
	m_stateCnt = 0;
	m_dc = NULL;
	///
	m_isDirty = TRUE;
	m_id = ID_NOTHING;
	m_show = TRUE;
	m_trans = 0xFF;
	m_transTarget = 0xFF;
	m_transTime = timeGetTime();
}


UIWindow::~UIWindow()
{
	this->UIWindow::Destroy(); //inlined
	g_windowMgr.UIWindowMgr::RemoveFromNameWaitingWindowList(this);
}


void UIWindow::Create(int cx, int cy)
{
	this->Resize(cx, cy); //inlined
	this->Invalidate();
	this->OnCreate(cx, cy);
	this->OnSize(cx, cy);
}


void UIWindow::Destroy()
{
	this->OnDestroy();

	if( m_dc != NULL )
	{
		delete m_dc;
		m_dc = NULL;
	}

	this->UIWindow::RemoveAllChildren(); //inlined
}


void UIWindow::AddChild(UIWindow* window)
{
	window->m_parent = this;
	m_children.push_back(window);
}


void UIWindow::RemoveChild(UIWindow* window)
{
	mystd::list<UIWindow*>::iterator it;

	for( it = m_children.begin(); it != m_children.end(); ++it )
		if( *it == window )
			break;

	if( it != m_children.end() )
		m_children.erase(it);

	delete window;
}


void UIWindow::RemoveAllChildren()
{
	for( mystd::list<UIWindow*>::iterator it = m_children.begin(); it != m_children.end(); ++it )
		delete *it;

	m_children.clear();
}


void UIWindow::ClearAllChildrenState()
{
	m_state = 0;
	this->Invalidate();

	for( mystd::list<UIWindow*>::iterator it = m_children.begin(); it != m_children.end(); ++it )
		(*it)->UIWindow::ClearAllChildrenState();
}


void UIWindow::InvalidateChildren()
{
	m_isDirty = TRUE;
	this->InvalidateWallPaper();

	for( mystd::list<UIWindow*>::iterator it = m_children.begin(); it != m_children.end(); ++it )
		if( (*it)->m_show )
			(*it)->UIWindow::InvalidateChildren();
}


void UIWindow::SetId(int id)
{
	m_id = id;
}


int UIWindow::GetId()
{
	return m_id;
}


BOOL UIWindow::IsFamily(UIWindow* window)
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


void UIWindow::Invalidate()
{
	m_isDirty = TRUE;
}


void UIWindow::InvalidateWallPaper()
{
}


UIWindow* UIWindow::HitTest(int x, int y)
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


void UIWindow::DoDraw(BOOL blitToParent)
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


void UIWindow::Resize(int cx, int cy)
{
	delete m_dc;
	m_dc = g_3dDevice.C3dDevice::CreateDCBuffer(cx, cy);
	m_w = cx;
	m_h = cy;

	this->Invalidate();
}


bool UIWindow::IsFrameWnd()
{
	return false;
}


bool UIWindow::IsUpdateNeed()
{
	return false;
}


void UIWindow::Move(int x, int y)
{
	m_x = x;
	m_y = y;
}


bool UIWindow::CanGetFocus()
{
	return false;
}


bool UIWindow::GetTransBoxInfo(BOXINFO* boxInfo)
{
	return false;
}


bool UIWindow::IsTransmitMouseInput()
{
	return false;
}


bool UIWindow::ShouldDoHitTest()
{
	return true;
}


void UIWindow::DragAndDrop(int x, int y, const DRAG_INFO* const dragInfo)
{
	g_modeMgr.CModeMgr::GetCurMode()->SendMsg(MM_CANCEL_DRAG, 0, 0, 0);
}


void UIWindow::StoreInfo()
{
}


void UIWindow::SaveOriginalPos()
{
}


void UIWindow::MoveDelta(int deltaDragX, int deltaDragY)
{
}


bool UIWindow::IsChildOf(UIWindow* win)
{
	UIWindow* p;

	for( p = m_parent; p != NULL; p = p->m_parent )
		if( p == win )
			break;

	return ( p != NULL );
}


UIWindow* UIWindow::GetNextSiblingOf(UIWindow* wnd)
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


UIWindow* UIWindow::GetPrevSiblingOf(UIWindow* wnd)
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


UIWindow* UIWindow::GetAncestor()
{
	UIWindow* result = this;

	for( UIWindow* i = m_parent; i != NULL; i = i->m_parent )
		result = i;

	return result;
}


void UIWindow::GetGlobalCoor(int& x, int& y)
{
	x += m_x;
	y += m_y;

	for( UIWindow* i = m_parent; i != NULL; i = i->m_parent )
	{
		x += i->m_x;
		y += i->m_y;
	}
}


BOOL UIWindow::IsShow()
{
	return m_show;
}


COLORREF UIWindow::GetColor()
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


void UIWindow::SetShow(BOOL visible)
{
	m_show = visible;
}


void UIWindow::OnCreate(int cx, int cy)
{
}


void UIWindow::OnDestroy()
{
}


void UIWindow::OnProcess()
{
}


void UIWindow::OnDraw()
{
}


void UIWindow::OnRun()
{
}


void UIWindow::OnSize(int cx, int cy)
{
}


void UIWindow::OnBeginEdit()
{
}


void UIWindow::OnFinishEdit()
{
}


void UIWindow::OnLBtnDown(int x, int y)
{
}


void UIWindow::OnLBtnDblClk(int x, int y)
{
}


void UIWindow::OnMouseMove(int x, int y)
{
}


void UIWindow::OnMouseHover(int x, int y)
{
}


void UIWindow::OnMouseShape(int x, int y)
{
	g_modeMgr.CModeMgr::GetCurMode()->CMode::SetCursorAction(0);
}


void UIWindow::OnLBtnUp(int x, int y)
{
}


void UIWindow::OnRBtnDown(int x, int y)
{
}


void UIWindow::OnRBtnUp(int x, int y)
{
}


void UIWindow::OnRBtnDblClk(int x, int y)
{
}


void UIWindow::OnWheel(int wheel)
{
}


void UIWindow::RefreshSnap()
{
}


int UIWindow::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3, int val4)
{
	switch( message )
	{
	case UM_DEFPUSH:
		if( m_parent != NULL )
			m_parent->SendMsg(this, UM_DEFPUSH, 0, 0, 0, 0);
	break;
	case UM_CANCELPUSH:
		if( m_parent != NULL )
			m_parent->SendMsg(this, UM_CANCELPUSH, 0, 0, 0, 0);
	break;
	};

	return 0;
}


int UIWindow::GetX()
{
	return m_x;
}


int UIWindow::GetY()
{
	return m_y;
}


int UIWindow::GetHeight()
{
	return m_h;
}


int UIWindow::GetWidth()
{
	return m_w;
}


bool UIWindow::GetTransBoxInfo2(BOXINFO* boxInfo)
{
	return false;
}


void UIWindow::DrawBoxScreen2()
{
}


void UIWindow::DrawBitmap(int x, int y, CBitmapRes* bitmap, bool drawOnlyNoTrans)
{
	if( m_dc == NULL || bitmap == NULL )
		return;

	m_dc->Update(x, y, bitmap->m_width, bitmap->m_height, bitmap->m_data, drawOnlyNoTrans);
}


void UIWindow::DrawBitmap_2(int a2, int x, int y, CBitmapRes* bitmap, bool a6, bool a7)
{
	if( m_dc == NULL || bitmap == NULL )
		return;

	if( a7 )
		bitmap->CBitmapRes::sub_4257C0_deldata2();

	bitmap->CBitmapRes::sub_4257F0(a2);

	if( bitmap->m_data2 != NULL )
		m_dc->Update(x, y, bitmap->m_width, bitmap->m_height, bitmap->m_data2, a6);
}


void UIWindow::TextOutA(int x, int y, const char* text, int textLen, int fontType, int fontHeight, COLORREF colorRef)
{
	if( textLen == 0 )
		textLen = strlen(text);

	DrawDC dc(m_dc);
	dc.DrawDC::SetFont(fontType, fontHeight, false);

	dc.DrawDC::SetTextColor(colorRef);
	dc.DrawDC::TextOutA(x, y, text, textLen);
}


void UIWindow::TextOutWithRightAlign(int x, int y, const char* text, int textLen, int fontType, int fontHeight, COLORREF colorRef)
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


void UIWindow::TextOutWithShadow(int x, int y, const char* text, int textLen, COLORREF colorText, COLORREF colorShadow, int fontType, int fontHeight)
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


void UIWindow::TextOutWithOutline(int x, int y, const char* text, int textLen, COLORREF colorText, COLORREF colorOutline, int fontType, int fontHeight, bool bold)
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


void UIWindow::TextOutWithOutlineVertical(int x, int y, const char* text, int textLen, COLORREF colorText, COLORREF colorOutline, int fontType, int fontHeight, bool bold)
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


void UIWindow::TextOutWithTwoColors(int x, int y, const char* text, COLORREF colorRef, COLORREF colorRef2, int textLen, int fontType, int fontHeight)
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


int UIWindow::GetTextWidth(const char* text, int textLen, int fontType, int fontHeight, bool bold)
{
	if( text == NULL )
		return 0;

	int len = ( textLen != 0 ) ? textLen : strlen(text);
	if( len == 0 )
		return 0;

	DrawDC dc(m_dc);
	dc.DrawDC::SetFont(fontType, fontHeight, bold);

	SIZE size;
	dc.DrawDC::GetTextExtentPoint32A(text, strlen(text), &size);

	return size.cx;
}


int UIWindow::GetTextHeight(const char* text, int textLen, int fontType, int fontHeight, bool bold)
{
	if( text == NULL )
		return 0;

	int len = ( textLen != 0 ) ? textLen : strlen(text);
	if( len == 0 )
		return 0;

	DrawDC dc(m_dc);
	dc.DrawDC::SetFont(fontType, fontHeight, bold);

	SIZE size;
	dc.DrawDC::GetTextExtentPoint32A(text, len, &size);

	return size.cy;
}


void UIWindow::ClearDC(COLORREF color)
{
	if( m_dc != NULL )
		m_dc->ClearSurface(NULL, color);
}


void UIWindow::ClearDCRect(COLORREF color, RECT& rect)
{
	if( m_dc != NULL )
		m_dc->ClearSurface(&rect, color);
}


void UIWindow::DrawBox(int x, int y, int cx, int cy, COLORREF color)
{
	RECT r;
	r.left = max(x, 0);
	r.top = max(y, 0);
	r.right = min(x + cx, m_w);
	r.bottom = min(y + cy, m_h);

	m_dc->ClearSurface(&r, color);
}


void UIWindow::DrawBorderLine(int x, int y, int w, int h, COLORREF color)
{
	this->UIWindow::DrawBox(x + 2    , y + 0    , w - 4, 1    , color);
	this->UIWindow::DrawBox(x + 1    , y + 1    , 1    , 1    , color);
	this->UIWindow::DrawBox(x + 0    , y + 2    , 1    , h - 4, color);
	this->UIWindow::DrawBox(x + 1    , y + h - 2, 1    , 1    , color);
	this->UIWindow::DrawBox(x + w - 2, y + 1    , 1    , 1    , color);
	this->UIWindow::DrawBox(x + w - 1, y + 2    , 1    , h - 4, color);
	this->UIWindow::DrawBox(x + 2    , y + h - 1, w - 4, 1    , color);
	this->UIWindow::DrawBox(x + w - 2, y + h - 2, 1    , 1    , color);
}


void UIWindow::DrawBorderLine_1px(int x, int y, int w, int h, COLORREF color)
{
	this->UIWindow::DrawBox(x        , y        , w, 1, color);
	this->UIWindow::DrawBox(x        , y        , 1, h, color);
	this->UIWindow::DrawBox(x + w - 1, y        , 1, h, color);
	this->UIWindow::DrawBox(x        , y + h - 1, w, 1, color);
}


void UIWindow::DrawTriangleDC(int x1, int y1, int x2, int y2, int x3, int y3, COLORREF color)
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


const char* UIWindow::InterpretColor(const char* color_text, COLORREF* colorRef)
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


const char* UIWindow::FindColorMark(const char* text, const char* text_end)
{
	if( text == NULL )
		return NULL;

	const char* result = text;

	while( text < text_end )
	{
		if( *result == '^' && (int)(text_end - result) >= 6 )
		{// potential color mark found
			int i;
			for( i = 1; i <= 6; ++i )
				if( !isHex(result[i]) )
					break; // not a color mark hex sequence

			if( i > 6 )
				break; // found.
		}

		result = CharNextExA((WORD)g_codePage, result, 0);
	}

	return result;
}
