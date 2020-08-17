#include "Enum.h"
#include "Globals.h"
#include "Mode.h"
#include "ModeMgr.h"
#include "MsgStrings.h"
#include "Base/Res.h"
#include "Resource/Bitmap.h"
#include "Window/UIResizer.h"
#include "Window/UIWindowMgr.h"


UIResizer::UIResizer()
{
	m_type = RT_LEFT;
	m_parentWidth = 0;
	m_parentHeight = 0;
	m_color = 0xFFFF00FF;
	m_backColor = 0xFFFF00FF;
}


void UIResizer::OnDraw()
{
	if( m_bitmapName.size() != 0 )
	{
		CBitmapRes* bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp(m_bitmapName.c_str()));
		this->UIWindow::DrawBitmap(0, 0, bitmapRes, false);
	}
	else
	{
		this->UIWindow::ClearDC(m_backColor);
		this->UIWindow::DrawBox(0, 0, m_w, 2, m_color);
	}
}


void UIResizer::OnLBtnDown(int x, int y)
{
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


void UIResizer::OnMouseMove(int x, int y)
{
	if( g_windowMgr.UIWindowMgr::GetCapture() != this )
		return;

	this->UIWindow::GetGlobalCoor(x, y);

	if( m_parent == NULL )
		return;

	int dx = x - m_startX;
	int dy = y - m_startY;
	int rx = m_parentWidth;
	int ry = m_parentHeight;

	switch( m_type )
	{
	case RT_LEFT:
		rx -= dx;
	break;
	case RT_RIGHT:
		rx += dx;
	break;
	case RT_UPLEFT:
		rx -= dx;
		ry -= dy;
	break;
	case RT_UPRIGHT:
		rx += dx;
		ry -= dy;
	break;
	case RT_UP:
		ry -= dy;
	break;
	case RT_DOWNLEFT:
		rx -= dx;
		ry += dy;
	break;
	case RT_DOWNRIGHT:
		rx += dx;
		ry += dy;
	break;
	case RT_DOWN:
		ry += dy;
	break;
	default:
	break;
	};

	m_parent->SendMsg(this, UM_RESIZE, m_type, rx, ry, 0);
}


void UIResizer::OnLBtnUp(int x, int y)
{
	if( g_windowMgr.UIWindowMgr::GetCapture() != this )
		return;

	if( m_parent != NULL )
		m_parent->RefreshSnap();
	g_windowMgr.UIWindowMgr::ReleaseCapture();
}


void UIResizer::OnMouseHover(int x, int y)
{
}


void UIResizer::OnMouseShape(int x, int y)
{
	if( g_windowMgr.UIWindowMgr::GetCapture() == this )
		g_modeMgr.CModeMgr::GetCurMode()->CMode::SetCursorAction(2);
	else
	if( x >= 0 && x < m_w && y >= 0 && y <= m_h )
		g_modeMgr.CModeMgr::GetCurMode()->CMode::SetCursorAction(2);
	else
	if( g_windowMgr.UIWindowMgr::GetCapture() != this )
		g_modeMgr.CModeMgr::GetCurMode()->CMode::SetCursorAction(0);
}


void UIResizer::SetBitmap(const char* bitmapName)
{
	m_bitmapName = bitmapName;

	const char* bitmapPath = ( g_serviceType == ServiceKorea ) ? m_bitmapName.c_str() : UIBmp(m_bitmapName.c_str());
	CBitmapRes* bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(bitmapPath);
	m_w = bitmapRes->m_width;
	m_h = bitmapRes->m_height;
}


void UIResizer::SetType(RESIZERTYPE type)
{
	m_type = type;
}


void UIResizer::SetColor(COLORREF color, COLORREF backColor)
{
	this->Invalidate();
	m_color = color;
	m_backColor = backColor;
}
