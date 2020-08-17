#include "Globals.h" // g_baseDir3
#include "Mode.h"
#include "ModeMgr.h"
#include "MsgStrings.h"
#include "Base/ResMgr.h"
#include "Window/UIChatHisBox2.h"
#include "Window/UIControl2.h"
#include "Window/UIFrameWnd2.h"
#include "Window/UIWhisperWnd.h"
#include "Window/UISys.h"


UIWhisperWnd::UIWhisperWnd() // line 7891-7893 (UIFrameWnd2.cpp)
{
	m_info = NULL;
}


UIWhisperWnd::~UIWhisperWnd() // line 7896-7897 (UIFrameWnd2.cpp)
{
}


void UIWhisperWnd::OnCreate(int cx, int cy) // line 7900-7946 (UIFrameWnd2.cpp)
{
	m_defPushId = ID_OK;
	this->UIWindow::Create(16, 16);

	m_resizer = new UIResizer();
	m_resizer->UIResizer::SetType(RT_DOWNRIGHT);
	m_resizer->UIResizer::SetBitmap("유저인터페이스\\btn_resize.bmp");
	m_resizer->Move(m_w - 15, m_h - 15);
	m_resizer->UIResizer::SetColor(0xFFFF00FF, 0xFFFF00FF);
	this->UIWindow::AddChild(m_resizer);

	m_chatEdit = new UIChatEditCtrl();
	m_chatEdit->UIWindow::Create(m_w - 30, 16);
	m_chatEdit->Move(3, m_h - 18);
	m_chatEdit->UIEditCtrl::SetTextLimit(70);
	m_chatEdit->UIEditCtrl::SetFrameColor(242, 242, 242);
	this->UIWindow::AddChild(m_chatEdit);

	g_windowMgr.UIWindowMgr::SetFocusEdit(m_chatEdit);

	m_listBox = new UIChatHisBox2();
	m_listBox->Create2(0, 0, m_w - 2, m_h - 38, false);
	m_listBox->Move(1, 17);
	m_listBox->UIWindow::SetId(ID_OK);
	this->UIWindow::AddChild(m_listBox);

	int posX[3];
	posX[0] = m_w - 14;
	posX[1] = 0;
	posX[2] = 0;

	const char* buttonName2[8];
	buttonName2[0] = "close";
	buttonName2[1] = NULL;
	buttonName2[2] = NULL;
	buttonName2[3] = NULL;
	buttonName2[4] = NULL;
	buttonName2[5] = NULL;
	buttonName2[6] = NULL;
	buttonName2[7] = NULL;

	mystd::string preBmpName2;
	preBmpName2 = "유저인터페이스\\basic_interface\\sys_";

	m_sysButton = new UIBitmapButton();
	m_sysButton->UIBitmapButton::SetBitmapName((preBmpName2 + buttonName2[0] + "_off.bmp").c_str(), BTN_NONE);
	m_sysButton->UIBitmapButton::SetBitmapName((preBmpName2 + buttonName2[0] + "_on.bmp").c_str(), BTN_DOWN);
	m_sysButton->UIBitmapButton::SetBitmapName((preBmpName2 + buttonName2[0] + "_on.bmp").c_str(), BTN_PRESSED);
	m_sysButton->UIWindow::Create(m_sysButton->UIBitmapButton::GetBitmapWidth(), m_sysButton->UIBitmapButton::GetBitmapHeight());
	m_sysButton->Move(posX[0], 3);
	m_sysButton->UIWindow::SetId(ID_CLOSE);
	m_sysButton->UIButton::SetToolTip("/q");
	this->UIWindow::AddChild(m_sysButton);
}


void UIWhisperWnd::OnDraw() // line 7949-7990 (UIFrameWnd2.cpp)
{
	CBitmapRes* bitmapRes;
	unsigned long rr, gg, bb;

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

	g_skinMgr.CSkinMgr::GetColorChipColor(20, 6, rr, gg, bb);
	this->UIWindow::DrawBox(0, 17, 1, m_h - 38, RGB(rr,gg,bb));
	this->UIWindow::DrawBox(m_w - 1, 17, 1, m_h - 38, RGB(rr,gg,bb));
	this->UIWindow::DrawBox(m_w - m_w * 56 / 280 - 2, 17, 1, m_h - 38, RGB(rr,gg,bb));

	bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\btnbar_left.bmp"));
	this->UIWindow::DrawBitmap(0, m_h - bitmapRes->m_width, bitmapRes, false);

	bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\btnbar_right.bmp"));
	this->UIWindow::DrawBitmap(m_w - bitmapRes->m_width, m_h - 21, bitmapRes, false);

	int count2 = (m_w - 42) / 21 + ((m_w - 42) % 21 != 0);
	for( int i = 0; i < count2; ++i )
	{
		bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\btnbar_mid.bmp"));
		this->UIWindow::DrawBitmap(21 + 21 * i, m_h - bitmapRes->m_height, bitmapRes, false);
	}

	char title[128];
	sprintf(title, "With  %s", m_whisperName.c_str());
	this->UIWindow::TextOutA(10, 3, "With", 0, 0, 12, 0xFFFFFF);
	this->UIWindow::TextOutA(9, 2, title, 0, 0, 12, 0x000000);
}


void UIWhisperWnd::OnRBtnUp(int x, int y) // line 8009-8011 (UIFrameWnd2.cpp)
{
	this->SendMsg(NULL, UM_MAKEMENU, 0, 0, 0);
}


int UIWhisperWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 8067-8231 (UIFrameWnd2.cpp)
{
	switch( message )
	{
	case UM_SETINFO:
	{
		WhisperWndInfo* info = (WhisperWndInfo*)val1;

		m_info = info;
		if( !m_info->WhisperWndInfo::IsValidInfo() )
			m_info->WhisperWndInfo::MakeDefault();

		this->SendMsg(NULL, UM_RESIZE, 7, m_info->w, m_info->h);
		this->Move(m_info->x, m_info->y);
	}
	break;
	case UM_COMMAND:
	{
		UIID id = (UIID)val1;

		switch( id )
		{
		case ID_OK:
		{
			char chatBuf[256];
			strcpy(chatBuf, m_chatEdit->UIEditCtrl::GetText());

			m_chatEdit->UIChatEditCtrl::StoreInHistory();
			g_windowMgr.UIWindowMgr::SetFocusEdit(m_chatEdit);

			if( strlen(chatBuf) == 0 )
				break;

			if( g_serviceType == ServiceAmerica && !g_session.CSession::IsOnlyEnglish(chatBuf) )
			{
				g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_ENGLISHONLY), 0x0000FF, 0);
				break;
			}

			if( m_whisperName.size() != 0 && chatBuf[0] != '/' )
			{// simple message
				g_windowMgr.UIWindowMgr::SetChatMsg(chatBuf);
				g_modeMgr.CModeMgr::GetCurMode()->SendMsg(MM_WHISPERMSG, (int)m_whisperName.c_str(), 0, 0);
			}
			else
			{// talktype
				TALKTYPE talkType;
				mystd::string param[3];
				int pos = g_session.CSession::GetTalkType(chatBuf, &talkType, param);
				if( pos != -1 )
					g_windowMgr.UIWindowMgr::SetChatMsg(chatBuf + pos);

				if( talkType == TT_REQ_EXIT_ROOM )
					g_windowMgr.UIWindowMgr::PostQuit(this);
				else
				if( talkType == TT_REQ_SAVE_CHAT )
					this->UIWhisperWnd::WriteChatToFile();
				else
				{// other talktypes
					g_modeMgr.CModeMgr::GetCurMode()->SendMsg(MM_PROCESS_TALK_TYPE, (int)talkType, (int)param, 0);
				}
			}
		}
		break;
		case ID_CLOSE:
		{
			g_windowMgr.UIWindowMgr::PostQuit(this);
		}
		break;
		};
	}
	break;
	case UM_MENU_SELECTED:
	{
		if( m_menuItems[val1].id == 11 )
			this->UIWhisperWnd::WriteChatToFile();
	}
	break;
	case UM_MAKEMENU:
	{
		m_menuItems.clear();

		if( g_windowMgr.UIWindowMgr::GetMenu() != NULL )
			g_windowMgr.UIWindowMgr::DeleteWindow(WID_MENUWND);

		m_menuItems.push_back(StringId(MsgStr(MSI_WRITE_CHAT_TO_FILE), 11));

		if( !g_windowMgr.UIWindowMgr::IsFriendName(m_whisperName.c_str()) )
			m_menuItems.push_back(StringId(MsgStr(MSI_ADD_TO_FRIEND_CHAR_LIST), 21));

		g_modeMgr.CModeMgr::GetCurMode()->SendMsg(MM_INITWHISPERMENU, (int)m_whisperName.c_str(), 0, 0);

		if( m_menuItems.size() == 0 )
			break;

		UIMenuWnd* menuWnd = (UIMenuWnd*)g_windowMgr.UIWindowMgr::MakeWindow(WID_MENUWND);

		for( size_t i = 0; i < m_menuItems.size(); ++i )
			menuWnd->SendMsg(NULL, UM_ADDITEM, (int)m_menuItems[i].itemName.c_str(), 0, 0);

		menuWnd->SendMsg(NULL, UM_ADJUSTSIZE, 0, 0, 0);

		int x = g_mouse.CMouse::GetXPos() + 1;
		int y = g_mouse.CMouse::GetYPos() + 1;
		if( x < 1 )
			x = 1;
		if( x > g_renderer->CRenderer::GetWidth() - menuWnd->UIWindow::GetWidth() )
			x = g_renderer->CRenderer::GetWidth() - menuWnd->UIWindow::GetWidth();
		if( y < 1 )
			y = 1;
		if( y > g_renderer->CRenderer::GetHeight() - menuWnd->UIWindow::GetHeight() )
			y = g_renderer->CRenderer::GetHeight() - menuWnd->UIWindow::GetHeight();

		menuWnd->Move(x, y);
	}
	break;
	case UM_ADDCHAT:
	{
		const char* chatMsg = (const char*)val1;
		COLORREF color = (COLORREF)val2;

		mystd::vector<mystd::string> strings;
		CutString(chatMsg, strings, m_w * 80 / 640);

		for( int i = 0; strings[i].size() != 0; ++i )
			m_listBox->AddItem(strings[i].c_str(), color);
	}
	break;
	case UM_PAGEUPPUSH:
	{
		if( m_listBox->UIListBox::IsVertScrEnabled() )
			m_listBox->SendMsg(NULL, UM_SCROLLVERTPAGEUP, 0, 0, 0);
	}
	break;
	case UM_PAGEDOWNPUSH:
	{
		if( m_listBox->UIListBox::IsVertScrEnabled() )
			m_listBox->SendMsg(NULL, UM_SCROLLVERTPAGEDOWN, 0, 0, 0);
	}
	break;
	case UM_RESIZE:
	{
		int unknown = (int)val1;
		int w = (int)val2;
		int h = (int)val3;

		if( unknown == 7 )
		{
			if( w > 512 ) w = 512;
			if( h > 384 ) h = 384;
			if( w < 280 ) w = 280;
			if( h < 120 ) h = 120;

			int aligned_w = 280 + (w - 280) / 32 * 32;
			int aligned_h = 120 + (h - 120) / 32 * 32;

			if( aligned_w != m_w || aligned_h != m_h )
			{
				this->Resize(aligned_w, aligned_h);
				m_resizer->Move(m_w - 15, m_h - 15);
				m_chatEdit->Resize(m_w - 30, 16);
				m_chatEdit->Move(3, m_h - 18);
				m_listBox->Resize(m_w - 2, m_h - 38);
				m_listBox->Move(1, 17);
				m_sysButton->Move(m_w - 14, 3);
			}

			g_windowMgr.UIWindowMgr::UpdateSnapInfo(this);
		}
	}
	break;
	default:
		return this->UIFrameWnd::SendMsg(sender, message, val1, val2, val3);
	break;
	};

	return 0;
}


void UIWhisperWnd::StoreInfo() // line 7998-8006 (UIFrameWnd2.cpp)
{
	if( m_info != NULL )
	{
		m_info->w = m_w;
		m_info->h = m_h;
		m_info->x = m_x;
		m_info->y = m_y;
	}

	g_windowMgr.UIWindowMgr::DeleteWhisperWindow(m_whisperName);
}


void UIWhisperWnd::Move(int x, int y) // line 7993-7995 (UIFrameWnd2.cpp)
{
	this->UIFrameWnd::Move(x, y);
}


void UIWhisperWnd::WriteChatToFile() // line 8014-8036 (UIFrameWnd2.cpp)
{
	char tmp[2048];

	sprintf(tmp, "%s\\Whisper", g_baseDir3);
	if( access(tmp, 0) != 0 && _mkdir(tmp) != 0 )
		return; // directory setup failed.

	mystd::string whisperName = m_whisperName;
	for( size_t i = 0; i < whisperName.size(); ++i )
	{
		char c = whisperName[i];
		if( c == '\\' || c == '/' || c == ':' || c == '*' || c == '?' || c == '"' || c == '<' || c == '>' || c == '|' )
			whisperName[i] = '_';
	}

	int i = 0;
	sprintf(tmp, "%s\\Whisper\\%s.txt", g_baseDir3, whisperName.c_str());

	while( access(tmp, 0) == 0 )
	{
		++i;
		sprintf(tmp, "%s\\Whisper\\%s%03d.txt", g_baseDir3, whisperName.c_str(), i);
	}

	if( !m_listBox->UIChatHisBox::WriteChatToFile(tmp) )
		return; // write failed.

	mystd::string chatStoreMsg = (mystd::string)tmp + " is Saved.";
	g_windowMgr.UIWindowMgr::SendMsg(UIM_OPENCHATWND, 0, 0, 0);
	g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)chatStoreMsg.c_str(), 0x00FF00, 0);
}
