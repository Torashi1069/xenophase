#include "Enum.h"
#include "Globals.h" // g_guildInfo, g_session, g_baseDir3
#include "GameMode.h"
#include "ModeMgr.h"
#include "MsgStrings.h" // MsgStr()
#include "Base/ResMgr.h"
#include "Base/Util.h" // GetFileNames()
#include "Resource/Emblem.h"
#include "Window/UIComboBoxWnd.h"
#include "Window/UIFrameWnd2.h"
#include "Window/UIGuildInfoManageWnd.h"
#include "Window/UISys.h" // UIID::ID_CHANGE_GUILD_EMBLEM
#include <zlib/zlib.h>


UIGuildInfoManageWnd::UIGuildInfoManageWnd() // line 258-263 (UIGuildWnd.cpp)
{
	m_compressedEmblemBitmapFileImage = NULL;
	m_compressedEmblemBitmapFileImageSize = 0;
	m_gdid = g_guildInfo.m_gdid;
	m_emblemVersion = g_guildInfo.m_emblemVersion;
}


UIGuildInfoManageWnd::~UIGuildInfoManageWnd() // line 266-268 (UIGuildWnd.cpp)
{
	this->UIGuildInfoManageWnd::DeleteCompressedEmblemBitmapFileImage(); // inlined
}


void UIGuildInfoManageWnd::OnCreate(int cx, int cy) // line 271-326 (UIGuildWnd.cpp)
{
	this->UIGuildWnd::InitTabText();
	m_curAllyGuild = -1;
	m_curHostileGuild = -1;

	if( g_guildInfo.m_masterName == "" )
		g_modeMgr.CModeMgr::GetCurMode()->SendMsg(MM_REQ_GUILD_MENU, 0, 0, 0);

	g_guildInfo.m_isRequestInfo[0] = 1;
	g_modeMgr.CModeMgr::GetCurMode()->SendMsg(MM_REQ_GUILD_MENU, 0, 0, 0);

	this->UIGuildInfoManageWnd::SetEmblemResName(); // inlined
	if( !g_resMgr().CResMgr::IsExist(m_emblemResName.c_str()) )
		g_modeMgr.CModeMgr::GetCurMode()->SendMsg(MM_REQ_GUILD_EMBLEM_IMG, m_gdid, 0, 0);

	mystd::string pathName = "유저인터페이스\\";
	m_emblemChangeButton = new UIBitmapButton();
	m_emblemChangeButton->UIBitmapButton::SetBitmapName((pathName + "btn_edit" + ".bmp").c_str(), BTN_NONE);
	m_emblemChangeButton->UIBitmapButton::SetBitmapName((pathName + "btn_edit_a" + ".bmp").c_str(), BTN_DOWN);
	m_emblemChangeButton->UIBitmapButton::SetBitmapName((pathName + "btn_edit_b" + ".bmp").c_str(), BTN_PRESSED);
	m_emblemChangeButton->UIWindow::Create(m_emblemChangeButton->UIBitmapButton::GetBitmapWidth(), m_emblemChangeButton->UIBitmapButton::GetBitmapHeight());

	if( g_guildInfo.m_amIMaster )
		m_emblemChangeButton->Move(this->UIWindow::GetWidth() - m_emblemChangeButton->UIWindow::GetWidth() - 8, 69);
	else
		m_emblemChangeButton->Move(-200, -200);

	m_emblemChangeButton->UIWindow::SetId(ID_CHANGE_GUILD_EMBLEM);
	this->UIWindow::AddChild(m_emblemChangeButton);
}


void UIGuildInfoManageWnd::SetEmblemResName() // line 329-333 (UIGuildWnd.cpp)
{
	char emblemResName[256];
	g_session.CSession::GetEmblemFileName(emblemResName, m_gdid, m_emblemVersion);
	m_emblemResName = emblemResName;
}


void UIGuildInfoManageWnd::OnDraw() // line 336-471 (UIGuildWnd.cpp)
{
	this->UIGuildWnd::OnDraw();

	char text[1024];
	sprintf(text, "%s : %s", MsgStr(MSI_GUILDNAME), g_guildInfo.m_guildName.c_str());
	this->UIWindow::TextOutA(8, 49, text, 0, 0, 12, 0);
	sprintf(text, "%s : %d", MsgStr(MSI_GUILDLEVEL), g_guildInfo.m_guildLevel);
	this->UIWindow::TextOutA(8, 65, text, 0, 0, 12, 0);
	sprintf(text, "%s : %s", MsgStr(MSI_GUILD_MASTER_NAME), g_guildInfo.m_masterName.c_str());
	this->UIWindow::TextOutA(8, 81, text, 0, 0, 12, 0);
	sprintf(text, "%s : %d / %d", MsgStr(MSI_GUILD_NUM_MEMBER), g_guildInfo.m_numMember, g_guildInfo.m_numMaxMember);
	this->UIWindow::TextOutA(8, 97, text, 0, 0, 12, 0);
	sprintf(text, "%s : %d", MsgStr(MSI_GUILD_AVG_MEMBER_LEVEL), g_guildInfo.m_memberAvgLevel);
	this->UIWindow::TextOutA(8, 113, text, 0, 0, 12, 0);
	sprintf(text, "%s : %s", MsgStr(MSI_GUILD_MANAGE_LAND), g_guildInfo.m_manageLand.c_str());
	this->UIWindow::TextOutA(8, 129, text, 0, 0, 12, 0);
	sprintf(text, "%s", MsgStr(MSI_GUILD_FAIR));
	this->UIWindow::TextOutA(8, 161, text, 0, 0, 12, 0);
	sprintf(text, "%s : %d", MsgStr(MSI_GUILD_EXP), g_guildInfo.m_exp);
	this->UIWindow::TextOutA(200, 49, text, 0, 0, 12, 0);
	sprintf(text, "%s", MsgStr(MSI_GUILD_EMBLEM));
	this->UIWindow::TextOutA(200, 73, text, 0, 0, 12, 0);
	sprintf(text, "%s : %d", MsgStr(MSI_GUILD_POINT), g_guildInfo.m_point);
	this->UIWindow::TextOutA(200, 97, text, 0, 0, 12, 0);
	sprintf(text, "%s", MsgStr(MSI_ALLY_GUILD));
	this->UIWindow::TextOutA(200, 139, text, 0, 0, 12, 0);
	sprintf(text, "%s", MsgStr(MSI_HOSTILITY_GUILD));
	this->UIWindow::TextOutA(200, 213, text, 0, 0, 12, 0);

	unsigned long rr, gg, bb;

	g_skinMgr.CSkinMgr::GetColorChipColor(6, 2, rr, gg, bb);
	this->UIWindow::DrawBox(299, 64, 26, 26, RGB(rr,gg,bb));

	if( g_resMgr().CResMgr::IsExist(m_emblemResName.c_str()) )
	{
		CEmblemRes* emblemRes = (CEmblemRes*)g_resMgr().CResMgr::Get(m_emblemResName.c_str());
		if( emblemRes != NULL )
			this->UIWindow::DrawBitmap(300, 65, emblemRes->CEmblemRes::GetBitmap(), true);
	}

	g_skinMgr.CSkinMgr::GetColorChipColor(14, 6, rr, gg, bb);
	this->UIWindow::DrawBox(23, 188, 90, 90, RGB(rr,gg,bb));

	g_skinMgr.CSkinMgr::GetColorChipColor(6, 2, rr, gg, bb);
	this->UIWindow::DrawBox(24, 189, 88, 88, RGB(rr,gg,bb));

	g_skinMgr.CSkinMgr::GetColorChipColor(22, 2, rr, gg, bb);
	this->UIWindow::DrawBox(67, 189, 2, 88, RGB(rr,gg,bb));

	g_skinMgr.CSkinMgr::GetColorChipColor(22, 2, rr, gg, bb);
	this->UIWindow::DrawBox(24, 232, 88, 2, RGB(rr,gg,bb));

	g_skinMgr.CSkinMgr::GetColorChipColor(2, 2, rr, gg, bb);
	this->UIWindow::DrawBox(67 - (int)(g_guildInfo.m_honor * -0.42f), 232 - (int)(g_guildInfo.m_virtue * 0.42f), 2, 2, RGB(rr,gg,bb));

	this->UIWindow::TextOutA( 63, 176, "R", 0, 0, 12, 0);
	this->UIWindow::TextOutA( 11, 227, "V", 0, 0, 12, 0);
	this->UIWindow::TextOutA( 64, 281, "W", 0, 0, 12, 0);
	this->UIWindow::TextOutA(116, 227, "F", 0, 0, 12, 0);

	g_skinMgr.CSkinMgr::GetColorChipColor(14, 6, rr, gg, bb);
	this->UIWindow::DrawBox(200, 155, 168, 48, RGB(rr,gg,bb));

	mystd::list<RELATED_GUILD_INFORMATION>::iterator it;
	int y;
	int count;

	count = 0;
	for( it = g_guildInfo.m_relatedGuildInfoList.begin(), y = 157; it != g_guildInfo.m_relatedGuildInfoList.end() && y < 205; ++it, y += 16 )
	{
		RELATED_GUILD_INFORMATION& info = *it;

		if( info.relation == RELATED_GUILD_TYPE_ALLY )
		{
			if( count == m_curAllyGuild )
			{
				g_skinMgr.CSkinMgr::GetColorChipColor(6, 2, rr, gg, bb);
				this->UIWindow::DrawBox(204, y, 80, 16, RGB(rr,gg,bb));
			}

			this->UIWindow::TextOutA(204, y, info.GuildName.c_str(), 0, 0, 12, 0);
			++count;
		}
	}

	g_skinMgr.CSkinMgr::GetColorChipColor(14, 6, rr, gg, bb);
	this->UIWindow::DrawBox(200, 229, 168, 48, RGB(rr,gg,bb));

	count = 0;
	for( it = g_guildInfo.m_relatedGuildInfoList.begin(), y = 231; it != g_guildInfo.m_relatedGuildInfoList.end() && y < 279; ++it, y += 16 )
	{
		RELATED_GUILD_INFORMATION& info = *it;

		if( info.relation == RELATED_GUILD_TYPE_ENEMY )
		{
			if( count == m_curHostileGuild )
			{
				g_skinMgr.CSkinMgr::GetColorChipColor(6, 2, rr, gg, bb);
				this->UIWindow::DrawBox(204, y, 80, 16, RGB(rr,gg,bb));
			}

			this->UIWindow::TextOutA(204, y, info.GuildName.c_str(), 0, 0, 12, 0);
			++count;
		}
	}
}


void UIGuildInfoManageWnd::OnRBtnUp(int x, int y) // line 474-516 (UIGuildWnd.cpp)
{
	if( x > 200 && x < 288 )
	{
		if( y > 157 && y < 205 )
		{
			int numAlly = g_guildInfo.GuildInfo::GetNumRelatedGuild(RELATED_GUILD_TYPE_ALLY);
			m_curAllyGuild = -1;
			m_curHostileGuild = -1;

			if( numAlly != 0 )
			{
				m_curAllyGuild = (y - 157) / 16;
				if( numAlly > m_curAllyGuild )
					this->SendMsg(NULL, UM_MAKEMENU, 0, 0, 0);
			}

			this->Invalidate();
		}
		else
		if( y > 231 && y < 279 )
		{
			int numEnemy = g_guildInfo.GuildInfo::GetNumRelatedGuild(RELATED_GUILD_TYPE_ENEMY);
			m_curAllyGuild = -1;
			m_curHostileGuild = -1;

			if( numEnemy != 0 )
			{
				m_curHostileGuild = (y - 231) / 16;
				if( numEnemy > m_curHostileGuild )
					this->SendMsg(NULL, UM_MAKEMENU, 0, 0, 0);
			}

			this->Invalidate();
		}
	}
}


void UIGuildInfoManageWnd::OnLBtnDown(int x, int y) // line 521-523 (UIGuildWnd.cpp)
{
	this->UIGuildWnd::OnLBtnDown(x, y);
}


void UIGuildInfoManageWnd::RefreshEmblemList() // line 526-531 (UIGuildWnd.cpp)
{
	m_emblemList.clear();

	char path[256];
	sprintf(path, "%s\\emblem\\", g_baseDir3);
	GetFileNames(m_emblemList, path, "*.bmp");
}


void UIGuildInfoManageWnd::RefreshCompressedEmblemFileImage(const char* emblemBitmapFileName) // line 534-558 (UIGuildWnd.cpp)
{
	this->UIGuildInfoManageWnd::DeleteCompressedEmblemBitmapFileImage(); // inlined

	char emblemBitmapName[128];
	sprintf(emblemBitmapName, "..\\emblem\\%s", emblemBitmapFileName);

	CFile file;
	if( !file.CFile::Open(emblemBitmapName, 0) )
		return;

	const BYTE* buf = (const BYTE*)file.CFile::GetCurBuf(0);
	size_t size = file.CFile::GetLength();

	CBitmapRes emblemBitmap;
	if( !emblemBitmap.CBitmapRes::LoadFromBuffer(emblemBitmapFileName, buf, size) )
		return;
	if( emblemBitmap.m_width != 24 || emblemBitmap.m_height != 24 )
		return;

	m_compressedEmblemBitmapFileImageSize = size;
	m_compressedEmblemBitmapFileImage = new char[size];
	compress((BYTE*)m_compressedEmblemBitmapFileImage, &m_compressedEmblemBitmapFileImageSize, buf, size);
}


void UIGuildInfoManageWnd::DeleteCompressedEmblemBitmapFileImage() // line 561-567 (UIGuildWnd.cpp)
{
	if( m_compressedEmblemBitmapFileImage != NULL )
	{
		delete[] m_compressedEmblemBitmapFileImage;
		m_compressedEmblemBitmapFileImage = NULL;
		m_compressedEmblemBitmapFileImageSize = 0;
	}
}


int UIGuildInfoManageWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 570-745 (UIGuildWnd.cpp)
{
	/*
	signed int v24; // esi@27
	std::list<RELATED_GUILD_INFORMATION,std::allocator<RELATED_GUILD_INFORMATION> >::_Node *v25; // edx@27
	int v26; // edx@34
	signed int v28; // esi@37
	std::list<RELATED_GUILD_INFORMATION,std::allocator<RELATED_GUILD_INFORMATION> >::_Node *v29; // edx@37
	*/

	switch( message )
	{
	case UM_MAKEMENU:
	{
		m_menuItems.clear();

		if( g_windowMgr.UIWindowMgr::GetMenu() != NULL )
			g_windowMgr.UIWindowMgr::DeleteWindow(WID_MENUWND);

		if( g_guildInfo.m_amIMaster )
			m_menuItems.push_back(StringId(MsgStr(MSI_DELETE), 27));

		if( m_menuItems.size() == 0 )
			break;

		UIMenuWnd* wnd = (UIMenuWnd*)g_windowMgr.UIWindowMgr::MakeWindow(WID_MENUWND);
		for( size_t i = 0; i < m_menuItems.size(); ++i )
			wnd->SendMsg(NULL, UM_ADDITEM, (int)m_menuItems[i].itemName.c_str(), 0, 0);

		wnd->SendMsg(NULL, UM_SET_CALLER_WID, WID_GUILDINFOMANAGEWND, 0, 0);
		wnd->SendMsg(NULL, UM_ADJUSTSIZE, 0, 0, 0);

		int xpos = min(max(g_mouse.CMouse::GetXPos() + 1, 1), g_renderer->CRenderer::GetWidth() - wnd->UIWindow::GetWidth());
		int ypos = min(max(g_mouse.CMouse::GetYPos() + 1, 1), g_renderer->CRenderer::GetHeight() - wnd->UIWindow::GetHeight());
		wnd->Move(xpos, ypos);
	}
	break;
	case UM_MENU_SELECTED:
	{
		CGameMode* gameMode = g_modeMgr.CModeMgr::GetGameMode();
		if( m_menuItems[val1].id != 27 )
			break;

		if( m_curAllyGuild != -1 )
		{
			mystd::list<RELATED_GUILD_INFORMATION>::iterator it;
			int pos = 0;

			for( it = g_guildInfo.m_relatedGuildInfoList.begin(); it != g_guildInfo.m_relatedGuildInfoList.end() && pos < 3; ++it )
			{
				if( it->relation == RELATED_GUILD_TYPE_ALLY )
				{
					if( pos == m_curAllyGuild )
					{
						int GDID = it->GDID;
						if( GDID != 0 )
							gameMode->SendMsg(MM_REQ_DELETE_RELATED_GUILD, GDID, RELATED_GUILD_TYPE_ALLY, 0);

						break; // found.
					}

					++pos;
				}
			}
	
			break; // done.
		}

		if( m_curHostileGuild != -1 )
		{
			mystd::list<RELATED_GUILD_INFORMATION>::iterator it;
			int pos = 0;

			for( it = g_guildInfo.m_relatedGuildInfoList.begin(); it != g_guildInfo.m_relatedGuildInfoList.end() && pos < 3; ++it )
			{
				if( it->relation == RELATED_GUILD_TYPE_ENEMY )
				{
					if( pos == m_curHostileGuild )
					{
						int GDID = it->GDID;
						if( GDID != 0 )
							gameMode->SendMsg(MM_REQ_DELETE_RELATED_GUILD, GDID, RELATED_GUILD_TYPE_ENEMY, 0);

						break; // found.
					}
				}

				++pos;
			}

			break; // done.
		}
	}
	break;
	case UM_COMMAND:
	{
		switch( val1 )
		{
		case ID_CLOSE:
		{
			g_windowMgr.UIWindowMgr::DeleteWindow(WID_GUILDWND);
		}
		break;
		case ID_CHANGE_GUILD_EMBLEM:
		{
			if( g_windowMgr.UIWindowMgr::GetComboBoxWnd() != NULL )
				g_windowMgr.UIWindowMgr::DeleteWindow(WID_COMBOBOXWND);

			m_emblemList.clear();

			char path[256];
			sprintf(path, "%s\\emblem\\", g_baseDir3);
			GetFileNames(m_emblemList, path, "*.bmp");

			int nEmblems = m_emblemList.size();
			if( nEmblems == 0 )
				break;

			UIComboBoxWnd* wnd = (UIComboBoxWnd*)g_windowMgr.UIWindowMgr::MakeWindow(WID_COMBOBOXWND);

			for( mystd::list<mystd::string>::iterator it = m_emblemList.begin(); it != m_emblemList.end(); ++it )
				wnd->SendMsg(NULL, UM_ADDITEM, (int)it->c_str(), 0, 0);

			wnd->SendMsg(NULL, UM_SETCURITEM, 0, 0, 0);
			wnd->Resize(160, min(16*nEmblems,160));
			wnd->SendMsg(NULL, UM_SET_CALLER_WID, WID_GUILDINFOMANAGEWND, 0, 0);

			int x = this->UIWindow::GetWidth() - 163;
			int y = 86;
			this->UIWindow::GetGlobalCoor(x, y);
			wnd->Move(x + 1, y + 1);
		}
		break;
		};
	}
	break;
	case UM_COMBOBOX_SELECTED:
	{
		int position = (int)val1;

		if( m_emblemList.size() == 0 )
			break;

		// look up the emblem filename for this position
		mystd::list<mystd::string>::iterator it;
		int i;
		for( it = m_emblemList.begin(), i = 0; it != m_emblemList.end(); ++it, ++i )
			if( position == i )
				break; // found

		if( it == m_emblemList.end() )
			break; // position not found

		mystd::string bmpName = it->c_str();
		if( bmpName.size() == 0 )
			break;

		char emblemBitmapName[128];
		sprintf(emblemBitmapName, "..\\..\\emblem\\%s", bmpName.c_str());
		CBitmapRes* bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(emblemBitmapName);
		if( bitmapRes == NULL || bitmapRes->m_width != 24 || bitmapRes->m_height != 24 )
			break;

		this->UIGuildInfoManageWnd::RefreshCompressedEmblemFileImage(bmpName.c_str());
		g_modeMgr.CModeMgr::GetCurMode()->SendMsg(MM_SEND_GUILD_EMBLEM, (int)m_compressedEmblemBitmapFileImage, m_compressedEmblemBitmapFileImageSize, m_gdid);
		g_modeMgr.CModeMgr::GetCurMode()->SendMsg(MM_REQ_GUILD_EMBLEM_IMG, m_gdid, 0, 0);
	}
	break;
	case UM_REFRESH:
	{
		m_gdid = g_guildInfo.m_gdid;
		m_emblemVersion = g_guildInfo.m_emblemVersion;

		char buffer[128];
		g_session.CSession::GetEmblemFileName(buffer, g_guildInfo.m_gdid, g_guildInfo.m_emblemVersion);
		m_emblemResName = buffer;

		if( g_guildInfo.m_amIMaster )
		{
			m_emblemChangeButton->Move(this->UIWindow::GetWidth() - m_emblemChangeButton->UIWindow::GetWidth() - 8, 69);
			this->UIWindow::InvalidateChildren();
		}
		else
		{
			m_emblemChangeButton->Move(-200, -200);
			this->UIWindow::InvalidateChildren();
		}
	}
	break;
	default:
		return this->UIGuildWnd::SendMsg(sender, message, val1, val2, val3);
	};

	return 0;
}


int UIGuildInfoManageWnd::GetTab() // line ?? (UIGuildWnd.h)
{
	return 0;
}
