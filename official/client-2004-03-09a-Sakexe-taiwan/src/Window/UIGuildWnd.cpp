#include "Globals.h" // g_guildInfo
#include "Mode.h"
#include "ModeMgr.h"
#include "MsgStrings.h"
#include "Base/ResMgr.h"
#include "Window/UIGuildWnd.h"


UIGuildWnd::UIGuildWnd() // inlined
{
	m_info = NULL;
	memset(m_tabText, 0, sizeof(m_tabText));
}


UIGuildWnd::~UIGuildWnd() // line 15 (UIGuildWnd.h)
{
}


void UIGuildWnd::InitTabText() // line 16-61
{
	if( m_tabText[0] != NULL )
		return; // already initialized

	if( g_guildInfo.m_guildTabBitmask == -1 )
		g_modeMgr.CModeMgr::GetCurMode()->SendMsg(118, 0, 0, 0);

	const char* tabName[6];
	tabName[0] = MsgStr(MSI_GUILDINFOMANAGE);
	tabName[1] = MsgStr(MSI_GUILDMEMBERMANAGE);
	tabName[2] = MsgStr(MSI_GUILDPOSITIONMANAGE);
	tabName[3] = MsgStr(MSI_GUILDSKILL);
	tabName[4] = MsgStr(MSI_GUILDBANISHEDMEMBER);
	tabName[5] = MsgStr(MSI_GUILDNOTICE);

	for( int i = 0; i < 6; ++i )
	{
		m_tabText[i] = new UIStaticText();
		m_tabText[i]->UIWindow::Create(62, 15);
		m_tabText[i]->UIStaticText::SetTextWithShorten(tabName[i]);
		m_tabText[i]->Move(3 + i * 66, 22);
		this->UIWindow::AddChild(m_tabText[i]);
	}

	int posX[3];
	posX[0] = m_w - 14;
	posX[1] = 0;
	posX[2] = 0;

	UIBitmapButton* wnd = new UIBitmapButton();
	mystd::string preBmpName2 = "유저인터페이스\\basic_interface\\sys_";
	wnd->UIBitmapButton::SetBitmapName((preBmpName2 + "close" + "_off.bmp").c_str(), BTN_NONE);
	wnd->UIBitmapButton::SetBitmapName((preBmpName2 + "close" + "_on.bmp").c_str(), BTN_DOWN);
	wnd->UIBitmapButton::SetBitmapName((preBmpName2 + "close" + "_on.bmp").c_str(), BTN_PRESSED);
	wnd->UIWindow::Create(wnd->UIBitmapButton::GetBitmapWidth(), wnd->UIBitmapButton::GetBitmapHeight());
	wnd->Move(posX[0], 3);
	wnd->UIWindow::SetId(ID_CLOSE);
	wnd->UIButton::SetToolTip("Alt+G");
	this->UIWindow::AddChild(wnd);
}


void UIGuildWnd::DrawTab(int curTab) // line 64-79
{
	unsigned long rr, gg, bb;
	g_skinMgr.CSkinMgr::GetColorChipColor(10, 2, rr, gg, bb);
	this->UIWindow::DrawBox(0, 17, m_w, 24, RGB(rr,gg,bb));

	for( int i = 0; i < 6; ++i )
	{
		if( curTab == i )
			g_skinMgr.CSkinMgr::GetColorChipColor(2, 2, rr, gg, bb);
		else
			g_skinMgr.CSkinMgr::GetColorChipColor(14, 6, rr, gg, bb);

		this->UIWindow::DrawBox(1 + 66 * i, 18, 64, 23, RGB(rr,gg,bb));
	}
}


void UIGuildWnd::OnDraw() // line 82-125
{
	this->UIGuildWnd::DrawTab(this->GetTab());

	CBitmapRes* bitmapRes;

	bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\titlebar_left.bmp"));
	this->UIWindow::DrawBitmap(0, 0, bitmapRes, false);

	bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\titlebar_right.bmp"));
	this->UIWindow::DrawBitmap(m_w - bitmapRes->m_width, 0, bitmapRes, false);

	int count = (m_w - 24) / 12 + ((m_w - 24) % 12 != 0);
	for( int i = 0; i < count; ++i )
	{
		bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\titlebar_mid.bmp"));
		this->UIWindow::DrawBitmap(12 + 12 * i, 0, bitmapRes, false);
	}

	unsigned long rr, gg, bb;

	g_skinMgr.CSkinMgr::GetColorChipColor(14, 6, rr, gg, bb);
	this->UIWindow::DrawBox(0, 41, m_w, m_h - 41, RGB(rr,gg,bb));

	g_skinMgr.CSkinMgr::GetColorChipColor(2, 2, rr, gg, bb);
	this->UIWindow::DrawBox(1, 41, m_w - 2, m_h - 41, RGB(rr,gg,bb));

	int count2 = (m_w - 42) / 21 + ((m_w - 42) % 21 != 0);
	for( int i = 0; i < count2; ++i )
	{
		bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\btnbar_mid2.bmp"));
		this->UIWindow::DrawBitmap(21 + 21 * i, m_h - bitmapRes->m_height, bitmapRes, false);
	}

	bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\btnbar_left2.bmp"));
	this->UIWindow::DrawBitmap(0, m_h - bitmapRes->m_height, bitmapRes, false);

	bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\btnbar_right2.bmp"));
	this->UIWindow::DrawBitmap(m_w - bitmapRes->m_width, m_h - bitmapRes->m_height, bitmapRes, false);
}


void UIGuildWnd::OnLBtnDown(int x, int y) // line 128-160
{
	if( y < 17 ) // title bar
		this->UIFrameWnd::OnLBtnDown(x, y);
	else
	if( y <= 41 ) // tab bar
	{
		int curtab = this->GetTab();
		this->GetTab(); // unused?

		int newtab = ( x <  66 ) ? 0
				   : ( x < 132 ) ? 1
				   : ( x < 198 ) ? 2
				   : ( x < 264 ) ? 3
				   : ( x < 330 ) ? 4
				   : ( x < 396 ) ? 5
				   :               6;

		if( newtab != curtab )
			this->SendMsg(NULL, UM_CHANGE_GUILD_TAB, newtab, 0, 0);
	}
}


void UIGuildWnd::StoreInfo() // line 163-171
{
	if( m_info == NULL )
		return;

	m_info->x = m_x;
	m_info->y = m_y;
	m_info->w = m_w;
	m_info->h = m_h;
	m_info->curTab = this->GetTab();
}


int UIGuildWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 174-252
{
	switch( message )
	{
	case UM_SETINFO:
	{
		GuildWndInfo* info = (GuildWndInfo*)val1;

		m_info = info;
		if( !m_info->GuildWndInfo::IsValidInfo() )
			m_info->GuildWndInfo::MakeDefault();

		this->Move(m_info->x, m_info->y);
	}
	break;
	case UM_REFRESH:
	{
		this->UIWindow::InvalidateChildren();
	}
	break;
	case UM_CHANGE_GUILD_TAB:
	{
		int tab = (int)val1;

		int bitmask[7];
		bitmask[0] = 0;
		bitmask[1] = 1;
		bitmask[2] = 2;
		bitmask[3] = 4;
		bitmask[4] = 16;
		bitmask[5] = 128;
		bitmask[6] = 64;

		switch( tab )
		{
		case 1:
		case 2:
		case 4:
		case 5:
			if( !(bitmask[tab] & g_guildInfo.m_guildTabBitmask) )
				return 0;
		break;
		case 6:
			return 0;
		break;
		default:
		break;
		}

		g_windowMgr.UIWindowMgr::DeleteWindow(WID_GUILDWND);

		switch( tab )
		{
		case 0: g_windowMgr.UIWindowMgr::MakeWindow(WID_GUILDINFOMANAGEWND); break;
		case 1: g_windowMgr.UIWindowMgr::MakeWindow(WID_GUILDMEMBERMANAGEWND); break;
		case 2: g_windowMgr.UIWindowMgr::MakeWindow(WID_GUILDPOSITIONMANAGEWND); break;
		case 3: g_windowMgr.UIWindowMgr::MakeWindow(WID_GUILDSKILLWND); break;
		case 4: g_windowMgr.UIWindowMgr::MakeWindow(WID_GUILDBANISHEDMEMBERWND); break;
		case 5: g_windowMgr.UIWindowMgr::MakeWindow(WID_GUILDNOTICEWND); break;
		case 6: g_windowMgr.UIWindowMgr::MakeWindow(WID_GUILDTOTALINFOWND); break;
		default: break;
		};
	}
	break;
	default:
		return this->UIFrameWnd::SendMsg(sender, message, val1, val2, val3);
	break;
	};

	return 0;
}


int UIGuildWnd::GetTab() // line ?? (UIGuildWnd.h)
{
	return 0;
}
