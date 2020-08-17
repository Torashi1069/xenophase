#include "MsgStrings.h"
#include "Session.h"
#include "Skin.h"
#include "SnapMgr.h"
#include "Base/Res.h"
#include "Resource/Bitmap.h"
#include "Window/UIFrameWnd.h"
#include "Window/UISys.h"
#include "Window/UIWindowMgr.h"


UIFrameWnd::UIFrameWnd()
{
	m_defPushId = ID_NOTHING;
	m_defCancelPushId = ID_NOTHING;
	m_startGlobalX = 0;
	m_startGlobalY = 0;
}


UIFrameWnd::~UIFrameWnd()
{
}


void UIFrameWnd::OnLBtnDown(int x, int y)
{
	if( this == NULL )
		return; // ???

	if( g_windowMgr.m_LastClickedUIID != m_id )
	{
		g_windowMgr.UIWindowMgr::AddToEscList((WINDOWID)m_id); //FIXME: semantic mismatch
		g_windowMgr.m_LastClickedUIID = (UIID)m_id;
	}

	g_windowMgr.UIWindowMgr::SetCapture(this);

	int gx = x;
	int gy = y;
	this->UIWindow::GetGlobalCoor(gx, gy);

	m_startGlobalX = gx;
	m_startGlobalY = gy;
	m_orgX = m_x;
	m_orgY = m_y;
	m_transTarget = 0x80;
	m_transTime = timeGetTime();

	g_snapMgr.CSnapMgr::BeginMove(this);
}


void UIFrameWnd::OnMouseMove(int x, int y)
{
}


void UIFrameWnd::Move(int x, int y)
{
	m_x = x;
	m_y = y;
	this->RefreshSnap();
}


void UIFrameWnd::OnMouseHover(int x, int y)
{
	if( g_windowMgr.UIWindowMgr::GetCapture() != this )
		return;

	int gx = x;
	int gy = y;
	this->UIWindow::GetGlobalCoor(gx, gy);

	int dx = gx - m_startGlobalX;
	int dy = gy - m_startGlobalY;

	if( g_snapMgr.CSnapMgr::IsRegisteredToSnap(this) )
	{
		this->MoveDelta(dx, dy);

		int rdx, rdy;
		g_windowMgr.UIWindowMgr::GetDeltaSnap(this, rdx, rdy, 0);

		int dragx = dx;
		int dragy = dy;
		g_snapMgr.CSnapMgr::GetDeltaDrag(this, dragx, dragy);

		if( abs(dragx) < abs(rdx) ) dragx = rdx;
		if( abs(dragy) < abs(rdy) ) dragy = rdy;

		this->MoveDelta(dx + dragx, dy + dragy);
		g_windowMgr.UIWindowMgr::UpdateSnapInfo(this);
		g_snapMgr.CSnapMgr::MoveDelta(this, dx + dragx, dy + dragy);
	}
	else
	{
		this->Move(m_orgX + dx, m_orgY + dy);
	}
}


void UIFrameWnd::OnLBtnUp(int x, int y)
{
	if( g_windowMgr.UIWindowMgr::GetCapture() != this )
		return;

	g_windowMgr.m_LastClickedUIID = (UIID)-1;
	m_transTarget = 0xFF;
	m_transTime = timeGetTime();
	g_windowMgr.UIWindowMgr::ReleaseCapture();
	g_snapMgr.CSnapMgr::EndMove(this);
}


bool UIFrameWnd::IsFrameWnd()
{
	return true;
}


void UIFrameWnd::SaveOriginalPos()
{
	m_orgX = m_x;
	m_orgY = m_y;
}


void UIFrameWnd::MoveDelta(int deltaDragX, int deltaDragY)
{
	m_x = deltaDragX + m_orgX;
	m_y = deltaDragY + m_orgY;
}


int UIFrameWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3, int val4)
{
	switch( message )
	{
	case UM_DEFPUSH:
		if( m_defPushId != 0 )
			this->SendMsg(this, UM_COMMAND, m_defPushId, 0, 0, 0);
	break;
	case UM_CANCELPUSH:
		if( m_defCancelPushId != 0 )
			this->SendMsg(this, UM_COMMAND, m_defCancelPushId, 0, 0, 0);
	break;
	default:
		return this->UIWindow::SendMsg(sender, message, val1, val2, val3, val4);
	break;
	};

	return 0;
}


void UIFrameWnd::RefreshSnap()
{
	int rdx, rdy;
	g_windowMgr.UIWindowMgr::GetDeltaSnap(this, rdx, rdy, 0);

	m_x += rdx;
	m_y += rdy;

	g_windowMgr.UIWindowMgr::UpdateSnapInfo(this);
}


void UIFrameWnd::DrawItem(int x, int y, const ITEM_INFO& iteminfo, bool forceidentified)
{
	this->UIFrameWnd::DrawItem(x, y, iteminfo.m_itemName.c_str(), (iteminfo.m_isIdentified || forceidentified));
}


void UIFrameWnd::DrawItem(int x, int y, const char* itemName, bool identified)
{
	char text[128];
	g_session.CSession::GetItemBitmapFileName(itemName, text, identified);

	CBitmapRes* bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(text);
	if( bitmapRes != NULL )
		this->UIWindow::DrawBitmap(x, y, bitmapRes, true);
}


void UIFrameWnd::DrawItemWithCount(int x, int y, const ITEM_INFO& iteminfo, bool forceidentified, bool boldtext)
{
	this->UIFrameWnd::DrawItem(x, y, iteminfo, forceidentified);

	if( iteminfo.m_num == 0 )
		return;

	char text[16];
	sprintf(text, "%d", iteminfo.m_num);

	if( boldtext )
	{
		this->UIWindow::TextOutA(x + 16, y + 20, text, 0, 0, 11, 0x000000);
	}
	else
	{
		short dx = 14;
		if( iteminfo.m_num >= 1000 )
			dx = 0;

		this->UIWindow::TextOutA(x + dx + 1, y + 15, text, 0, 0, 11, 0xFFFFFF);
		this->UIWindow::TextOutA(x + dx - 1, y + 15, text, 0, 0, 11, 0xFFFFFF);
		this->UIWindow::TextOutA(x + dx + 0, y + 16, text, 0, 0, 11, 0xFFFFFF);
		this->UIWindow::TextOutA(x + dx + 0, y + 14, text, 0, 0, 11, 0xFFFFFF);
		this->UIWindow::TextOutA(x + dx + 0, y + 15, text, 0, 0, 11, 0x000000);
	}
}


void UIFrameWnd::DrawItemFrame(int x, int y)
{
	CBitmapRes* bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\itemwin_mid.bmp"));
	this->UIWindow::DrawBitmap(x, y, bitmapRes, false);
}


void UIFrameWnd::DrawLatticeFrame(int x, int y, int width, int height)
{
	CBitmapRes* bitmapRes;

	if( width == 0 )
		width = m_w;

	if( height == 0 )
		height = m_h;

	int xnum = (width - 28) / 14 + ((width - 28) % 14 != 0);
	int ynum = (height - 28) / 14 + ((height - 28) % 14 != 0);

	for( int i = 0; i < xnum; ++i )
	{
		bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\sysbox_mu.bmp"));
		this->UIWindow::DrawBitmap(x + 14 + i * 14, y, bitmapRes, false);
	}

	bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\sysbox_lu.bmp"));
	this->UIWindow::DrawBitmap(x, y, bitmapRes, false);

	bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\sysbox_ru.bmp"));
	this->UIWindow::DrawBitmap(x + width - bitmapRes->m_width, y, bitmapRes, false);

	for( int i = 0; i < ynum; ++i )
	{
		bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\sysbox_lm.bmp"));
		this->UIWindow::DrawBitmap(x, y + 14 + i * 14, bitmapRes, false);
	}

	for( int i = 0; i < ynum; ++i )
	{
		bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\sysbox_rm.bmp"));
		this->UIWindow::DrawBitmap(x + width - bitmapRes->m_width, y + 14 + i * 14, bitmapRes, false);
	}

	for( int i = 0; i < xnum; ++ i )
	{
		bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\sysbox_md.bmp"));
		this->UIWindow::DrawBitmap(x + 14 + i * 14, y + height - bitmapRes->m_height, bitmapRes, false);
	}

	bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\sysbox_ld.bmp"));
	this->UIWindow::DrawBitmap(x, height + y - bitmapRes->m_height, bitmapRes, false);

	bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\sysbox_rd.bmp"));
	this->UIWindow::DrawBitmap(x + width - bitmapRes->m_width, y + height - bitmapRes->m_height, bitmapRes, false);

	unsigned long rr, gg, bb;
	g_skinMgr.CSkinMgr::GetColorChipColor(2, 2, rr, gg, bb);
	this->UIWindow::DrawBox(x + 14, y + 14, width - 28, height - 28, RGB(rr,gg,bb));
}
