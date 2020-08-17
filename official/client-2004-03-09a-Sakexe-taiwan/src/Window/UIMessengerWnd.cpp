#include "Globals.h"
#include "Mode.h"
#include "ModeMgr.h"
#include "MsgStrings.h"
#include "Base/ResMgr.h"
#include "Window/UIMessengerWnd.h"
#include "Window/UIScrollBar.h"


UIMessengerGroupWnd::UIMessengerGroupWnd() // line 11-18
{
	m_info = NULL;
	m_scrollBar = NULL;
	m_viewOffset = 0;
	m_vertScrEnabled = FALSE;
	m_itemHorzNum = 1;
	m_itemVertNum = 5;
}


UIMessengerGroupWnd::~UIMessengerGroupWnd() // line 21-22
{
}


void UIMessengerGroupWnd::OnCreate(int cx, int cy) // line 25-118
{
	m_scrollBar = new UIScrollBar();
	m_scrollBar->UIScrollBar::Create(m_w - 15, 17, 1, m_h - 58);
	this->UIWindow::AddChild(m_scrollBar);

	m_curRadioBtn = 1;

	const char* texts[2];
	texts[0] = MsgStr(MSI_FRIEND);
	texts[1] = MsgStr(MSI_PARTY);

	int createWidth[2];
	createWidth[0] = 48;
	createWidth[1] = 13 + this->UIWindow::GetTextWidth(MsgStr(MSI_PARTY), 0, 0, 12, false);

	int states[2];
	states[0] = 0;
	states[1] = 1;

	for( int i = 0; i < 2; ++i )
	{
		m_radioBtns[i] = new UIRadioBtn();
		m_radioBtns[i]->UIWindow::Create(createWidth[i], 12);
		m_radioBtns[i]->Move(4 + i * 60, m_h - 16);
		m_radioBtns[i]->UIRadioBtn::SetText(texts[i]);
		m_radioBtns[i]->SendMsg(this, 13, states[i], 0, 0);
		this->UIWindow::AddChild(m_radioBtns[i]);
	}

	const char* titleText[2];
	titleText[0] = MsgStr(MSI_FRIEND);
	titleText[1] = MsgStr(MSI_PARTY);

	char buf[64];
	if( m_curRadioBtn == 0 || g_session.m_partyName.size() != 0 )
	{
		sprintf(buf, "%s(%s)", titleText[m_curRadioBtn], g_session.m_partyName.c_str());
	}
	else
	{
		sprintf(buf, "%s", titleText[m_curRadioBtn]);
	}

	m_titleText = new UIStaticText();
	m_titleText->UIWindow::Create(m_w - 32, 15);
	m_titleText->UIStaticText::SetTextWithShorten(buf);
	m_titleText->Move(16, 2);
	m_titleText->m_drawTwice = 1;
	this->UIWindow::AddChild(m_titleText);

	int ids2[3];
	ids2[0] = ID_CLOSE;
	ids2[1] = 0;
	ids2[2] = 0;

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
	m_sysButton->UIWindow::SetId(ids2[0]);
	m_sysButton->UIButton::SetToolTip("Alt+Z");
	this->UIWindow::AddChild(m_sysButton);

	mystd::string pathName;
	pathName = "유저인터페이스\\basic_interface\\";

	const char* buttonName[5][3];
	buttonName[0][0] = "mesbtn_01";
	buttonName[0][1] = "mesbtn_01_a";
	buttonName[0][2] = "mesbtn_01_b";
	buttonName[1][0] = "mesbtn_02";
	buttonName[1][1] = "mesbtn_02_a";
	buttonName[1][2] = "mesbtn_02_b";
	buttonName[2][0] = "mesbtn_03";
	buttonName[2][1] = "mesbtn_03_a";
	buttonName[2][2] = "mesbtn_03_b";
	buttonName[3][0] = "mesbtn_04";
	buttonName[3][1] = "mesbtn_04_a";
	buttonName[3][2] = "mesbtn_04_b";
	buttonName[4][0] = "mesbtn_05";
	buttonName[4][1] = "mesbtn_05_a";
	buttonName[4][2] = "mesbtn_05_b";

	int ids[5];
	ids[0] = 141;
	ids[1] = 142;
	ids[2] = 143;
	ids[3] = 144;
	ids[4] = 145;

	const char* toolTip[5];
	toolTip[0] = MsgStr(MSI_MSG);
	toolTip[1] = MsgStr(MSI_1ON1);
	toolTip[2] = MsgStr(MSI_CHARACTER_INFO);
	toolTip[3] = MsgStr(MSI_PARTY_SETTING);
	toolTip[4] = MsgStr(MSI_EXPEL);

	int disabled[5];
	disabled[0] = 1;
	disabled[2] = 1;
	disabled[1] = 0;
	disabled[3] = 0;
	disabled[4] = 0;

	for( int i = 0; i < 5; ++i )
	{
		m_button[i] = new UIBitmapButton();
		m_button[i]->UIBitmapButton::SetBitmapName((pathName + buttonName[i][0] + ".bmp").c_str(), BTN_NONE);
		m_button[i]->UIBitmapButton::SetBitmapName((pathName + buttonName[i][1] + ".bmp").c_str(), BTN_DOWN);
		m_button[i]->UIBitmapButton::SetBitmapName((pathName + buttonName[i][2] + ".bmp").c_str(), BTN_PRESSED);
		m_button[i]->UIWindow::Create(m_button[i]->UIBitmapButton::GetBitmapWidth(), m_button[i]->UIBitmapButton::GetBitmapHeight());
		m_button[i]->Move(5 + i * 26, m_h - 40);
		m_button[i]->UIWindow::SetId(ids[i]);
		m_button[i]->UIButton::SetToolTip(toolTip[i]);
		m_button[i]->UIButton::SetDiabled(disabled[i]);
		this->UIWindow::AddChild(m_button[i]);
	}

	m_resizer = new UIResizer();
	m_resizer->UIWindow::Create(16, 16);
	m_resizer->UIResizer::SetType(RT_DOWNRIGHT);
	m_resizer->UIResizer::SetBitmap("유저인터페이스\\btn_resize.bmp");
	m_resizer->Move(m_w - 15, m_h - 15);
	m_resizer->UIResizer::SetColor(0xFFFF00FF, 0xFFFF00FF);
	this->UIWindow::AddChild(m_resizer);

	this->SendMsg(NULL, 23, 0, 0, 0);
}


FRIEND_INFO UIMessengerGroupWnd::GetItemInfoBySequence(int sequence) // line 121-131
{
	mystd::list<FRIEND_INFO>::iterator it;
	int i;

	for( it = m_itemList.begin(), i = 0; it != m_itemList.end(); ++it, ++i )
		if( i == sequence )
			break;

	if( it == m_itemList.end() )
		return FRIEND_INFO(FALSE);

	return *it;
}


FRIEND_INFO UIMessengerGroupWnd::GetItemInfo(int x, int y) // line 134-169
{
	if( x < 1 || x >= m_w - 20 || y < 17 || y >= 17 + 18 * m_itemVertNum )
		return FRIEND_INFO(FALSE);

	mystd::list<FRIEND_INFO>::iterator it;
	int curItem = 0;
	int drawCount = 0;
	int yCell = (y - 17) / 18;

	for( it = m_itemList.begin(); it != m_itemList.end(); ++it )
	{
		if( curItem >= m_viewOffset * m_itemHorzNum )
		{
			if( drawCount == yCell * m_itemHorzNum )
				break;

			++drawCount;
		}

		++curItem;
	}

	if( it == m_itemList.end() )
	{
		m_curItem = -1;
		return FRIEND_INFO(FALSE);
	}

	char text[80];
	sprintf(text, "%s", it->characterName.c_str());

	if( x <= 20 || x >= 26 + this->UIWindow::GetTextWidth(text, 0, 0, 12, false) )
	{
		m_curItem = -1;
		return FRIEND_INFO(FALSE);
	}

	m_curItem = curItem;
	return *it;
}


hook_method<void (UIMessengerGroupWnd::*)(int x, int y)> UIMessengerGroupWnd::_OnLBtnDown(SAKEXE, "UIMessengerGroupWnd::OnLBtnDown");
void UIMessengerGroupWnd::OnLBtnDown(int x, int y) // line 172-183
{
	return (this->*_OnLBtnDown)(x, y);

	//TODO
}


void UIMessengerGroupWnd::OnRBtnUp(int x, int y) // line 186-195
{
	int prevItem = m_curItem;
	FRIEND_INFO info = this->UIMessengerGroupWnd::GetItemInfo(x, y);

	if( m_curItem != prevItem )
		this->Invalidate();

	if( m_curItem != -1 )
		this->SendMsg(NULL, 49, 0, 0, 0);
}


void UIMessengerGroupWnd::OnLBtnDblClk(int x, int y) // line 198-200
{
	this->SendMsg(NULL, 6, 142, 0, 0);
}


void UIMessengerGroupWnd::OnWheel(int wheel) // line 203-213
{
	if( !m_vertScrEnabled )
		return;

	int pos = m_itemVertNum - 1;
	if( pos >= 3 )
		pos = 3;

	if( wheel >= 0 )
		pos = -pos;

	this->SendMsg(m_scrollBar, UM_SCROLLVERT, pos, 0, 0);
}


hook_method<void (UIMessengerGroupWnd::*)(void)> UIMessengerGroupWnd::_RecalcScrbarPos(SAKEXE, "UIMessengerGroupWnd::RecalcScrbarPos");
void UIMessengerGroupWnd::RecalcScrbarPos(void) // line 216-243
{
	return (this->*_RecalcScrbarPos)();

	//TODO
}


hook_method<void (UIMessengerGroupWnd::*)(void)> UIMessengerGroupWnd::_OnDraw(SAKEXE, "UIMessengerGroupWnd::OnDraw");
void UIMessengerGroupWnd::OnDraw(void) // line 246-366
{
	return (this->*_OnDraw)();

	//TODO
}


void UIMessengerGroupWnd::StoreInfo(void) // line 377-384
{
	if( m_info != NULL )
	{
		m_info->w = m_w;
		m_info->h = m_h;
		m_info->x = m_x;
		m_info->y = m_y;
	}
}


hook_method<int (UIMessengerGroupWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIMessengerGroupWnd::_SendMsg(SAKEXE, "UIMessengerGroupWnd::SendMsg");
int UIMessengerGroupWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 387-707
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	switch( message )
	{
	case 34:
	{
		m_info = (MessengerGroupWndInfo*)val1;
		if( !m_info->MessengerGroupWndInfo::IsValidInfo() )
			m_info->MessengerGroupWndInfo::MakeDefault();
		this->SendMsg(NULL, 14, 7, m_info->w, m_info->h);
		this->Move(m_info->x, m_info->y);
		return 0;
	}

	case 23:
	{
		m_itemList.clear();

		if( m_curRadioBtn == 0 )
		{
			for( int i = 0; i < g_session.CSession::GetNumFriend(); ++i )
			{
				FRIEND_INFO info = g_session.CSession::GetFriendInfoBySequence(i);
				if( info.isValid )
					m_itemList.push_back(info);
			}
		}
		else
		if( m_curRadioBtn == 1 )
		{
			for( int i = 0; i < g_session.CSession::GetNumParty(); ++i )
			{
				FRIEND_INFO info = g_session.CSession::GetPartyInfoBySequence(i);
				if( info.isValid )
					m_itemList.push_back(info);
			}
		}

		m_curItem = -1;
		this->UIMessengerGroupWnd::RecalcScrbarPos();
		this->Invalidate();

		const char* titleText[2] = { MsgStr(MSI_FRIEND), MsgStr(MSI_PARTY) };
		char buf[64];

		if( m_curRadioBtn == 0 || g_session.m_partyName.size() != 0 )
			sprintf(buf, "%s(%s)", titleText[m_curRadioBtn], g_session.m_partyName.c_str());
		else
			sprintf(buf, "%s", titleText[m_curRadioBtn]);

		m_titleText->UIStaticText::SetTextWithShorten(buf);
		return 0;
	}

	case 49:
	{
		m_menuItems.clear();
		if( g_windowMgr.UIWindowMgr::GetMenu() != NULL )
			g_windowMgr.UIWindowMgr::DeleteWindow(WID_MENUWND);

		if( m_curItem != -1 )
		{
			FRIEND_INFO info = this->UIMessengerGroupWnd::GetItemInfoBySequence(m_curItem);
			if( info.isValid )
			{
				m_menuItems.push_back(StringId(MsgStr(MSI_SEE_INFORMATION_OF_CHARACTER),3));

				if( info.characterName != g_session.CSession::GetCharName() )
					m_menuItems.push_back(StringId(MsgStr(MSI_OPEN_1ON1_WINDOW),7));

				if( info.characterName == g_session.CSession::GetCharName() )
					m_menuItems.push_back(StringId(MsgStr(MSI_LEAVE_PARTY),9));
				else
				if( g_session.m_amIPartyMaster && info.characterName != g_session.CSession::GetCharName() )
					m_menuItems.push_back(StringId(MsgStr(MSI_EXPEL),0));
			}
		}

		if( m_menuItems.size() == 0 )
			return 0;

		UIFrameWnd* wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_MENUWND);
		for( size_t i = 0; i < m_menuItems.size(); ++i )
			wnd->SendMsg(NULL, 31, (int)m_menuItems[i].itemName.c_str(), 0, 0);

		wnd->SendMsg(NULL, 83, 34, 0, 0);
		wnd->SendMsg(NULL, 30, 0, 0, 0);

		int newX = g_mouse.CMouse::GetXPos() + 1;
		int newY = g_mouse.CMouse::GetYPos() + 1;
		if( newX < 1 )
			newX = 1;
		if( newX > g_renderer->CRenderer::GetWidth() - wnd->UIWindow::GetWidth() )
			newX = g_renderer->CRenderer::GetWidth() - wnd->UIWindow::GetWidth();
		if( newY < 1 )
			newY = 1;
		if( newY > g_renderer->CRenderer::GetHeight() - wnd->UIWindow::GetHeight() )
			newY = g_renderer->CRenderer::GetHeight() - wnd->UIWindow::GetHeight();

		wnd->Move(newX, newY);
		return 0;
	}

	case 48:
	{
		FRIEND_INFO info = this->UIMessengerGroupWnd::GetItemInfoBySequence(m_curItem);
		if( info.isValid )
		{
			switch( m_menuItems[val1].id )
			{
			case 6: this->SendMsg(NULL, 6, 141, 0, 0); break;
			case 7: this->SendMsg(NULL, 6, 142, 0, 0); break;
			case 3: this->SendMsg(NULL, 6, 143, 0, 0); break;
			case 0: this->SendMsg(NULL, 6, 145, 0, 0); break;
			case 9: this->SendMsg(NULL, 6, 146, 0, 0); break;
			default:
				break;
			}
		}
		return 0;
	}

	case 6:
		switch( val1 )
		{
		case 141:
			if( m_curItem != -1 )
			{
				FRIEND_INFO info = this->UIMessengerGroupWnd::GetItemInfoBySequence(m_curItem);
			}
		break;
		case 142:
			if( m_curItem != -1 )
			{
				FRIEND_INFO info = this->UIMessengerGroupWnd::GetItemInfoBySequence(m_curItem);
				if( info.isValid )
				{
					if( info.characterName != g_session.CSession::GetCharName() ) //TODO: verify
						g_windowMgr.UIWindowMgr::SendMsg(UIM_MAKE_WHISPER_WINDOW, (int)info.characterName.c_str(), 0, 0);
				}
			}
		break;
		case 143:
			if( m_curItem == -1 )
			{
				FRIEND_INFO info = this->UIMessengerGroupWnd::GetItemInfoBySequence(m_curItem);
				if( info.isValid )
					g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_NOTSUPPORTEDYET), 0, 1, 0, 0);
			}
		break;
		case 144:
			if( !g_windowMgr.UIWindowMgr::DeleteWindow(WID_PARTYSETTINGWND) && g_session.CSession::GetNumParty() != 0 && m_curRadioBtn == 1 )
				g_windowMgr.UIWindowMgr::MakeWindow(WID_PARTYSETTINGWND);
		break;
		case 145:
			if( m_curItem != -1 )
			{
				FRIEND_INFO info = this->UIMessengerGroupWnd::GetItemInfoBySequence(m_curItem);
				if( info.isValid )
				{
					if( info.characterName != g_session.CSession::GetCharName() )
						if( g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_DO_YOU_REALLY_WANT_EXPEL), 2, 0, 0, 0) == 97 )
							g_modeMgr.CModeMgr::GetCurMode()->SendMsg(68, (int)info.characterName.c_str(), 0, 0);
				}
			}
		break;
		case 146:
			if( m_curItem != -1 )
			{
				FRIEND_INFO info = this->UIMessengerGroupWnd::GetItemInfoBySequence(m_curItem);
				if( info.isValid )
				{
					if( info.characterName == g_session.CSession::GetCharName() )
						if( g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_DO_YOU_REALLY_WANT_LEAVE), 2, 0, 0, 0) == 97 )
							g_modeMgr.CModeMgr::GetCurMode()->SendMsg(67, 0, 0, 0);
				}
			}
		break;
		case ID_CLOSE:
			g_windowMgr.UIWindowMgr::DeleteWindow(WID_MESSENGERWND);
		break;
		case 125:
			if( sender == m_radioBtns[0] )
			{
				m_info->radio = 0;
				g_windowMgr.UIWindowMgr::DeleteWindow(WID_MESSENGERWND);
				g_windowMgr.UIWindowMgr::MakeWindow(WID_MESSENGERWND);
			}
		break;
		default:
		break;
		}

		return 0;

	case 7:
	case 9:
	case 10:
	{
		int oldOffset = m_viewOffset;

		if( message == 9 )
			m_viewOffset -= m_itemVertNum - 1;
		else
		if( message == 10 )
			m_viewOffset += m_itemVertNum - 1;
		else
			m_viewOffset += val1;

		if( oldOffset != m_viewOffset )
		{
			this->UIMessengerGroupWnd::RecalcScrbarPos();
			this->Invalidate();
		}

		return m_viewOffset - oldOffset;
	}

	case 14:
	{
		if( val1 != 7 )
			return 0;

		int newX = ( val2 < 140 ) ? 140 : ( val2 > 230 ) ? 230 : val2;
		int newY = ( val3 < 155 ) ? 155 : ( val3 > 209 ) ? 209 : val3;
		int newWidth = 140 + (newX - 140) / 18 * 18;
		int newHeight = 155 + (newY - 155) / 18 * 18;

		if( newWidth != m_w || newHeight != m_h )
		{
			m_viewOffset = 0;
			this->Resize(newWidth, newHeight);

			m_resizer->Move(m_w - 15, m_h - 15);

			m_scrollBar->Move(m_w - 15, 17);
			m_scrollBar->Resize(m_scrollBar->UIWindow::GetWidth(), m_h - 58);

			for( int i = 0; i < countof(m_radioBtns); ++i )
				m_radioBtns[i]->Move(4 + 60 * i, m_h - 16);

			m_sysButton->Move(m_w - 14, 3);

			for( int i = 0; i < countof(m_button); ++i )
				m_button[i]->Move(5 + 26 * i, m_h - 40);

			m_itemVertNum = 5 + (m_h - 155) / 18;

			const char* titleText[2] = { MsgStr(MSI_FRIEND), MsgStr(MSI_PARTY) };
			char buf[64];

			if( m_curRadioBtn == 0 || g_session.m_partyName.size() != 0 )
				sprintf(buf, "%s(%s)", titleText[m_curRadioBtn], g_session.m_partyName.c_str());
			else
				sprintf(buf, "%s", titleText[m_curRadioBtn]);

			m_titleText->Resize(m_w - 32, 12);
			m_titleText->UIStaticText::SetTextWithShorten(buf);
			m_titleText->Move(16, 3);

			this->UIMessengerGroupWnd::RecalcScrbarPos();
		}

		g_windowMgr.UIWindowMgr::UpdateSnapInfo(this);
		return 0;
	}

	default:
		return this->UIFrameWnd::SendMsg(sender, message, val1, val2, val3);
	}
}


////////////////////////////////////////


UIWhisperListWnd::UIWhisperListWnd() // line 713-715
{
	m_info = NULL;
}


UIWhisperListWnd::~UIWhisperListWnd() // line 718-719
{
}


hook_method<void (UIWhisperListWnd::*)(int cx, int cy)> UIWhisperListWnd::_OnCreate(SAKEXE, "UIWhisperListWnd::OnCreate");
void UIWhisperListWnd::OnCreate(int cx, int cy) // line 722-811
{
	return (this->*_OnCreate)(cx, cy);

	//TODO
}


hook_method<void (UIWhisperListWnd::*)(void)> UIWhisperListWnd::_OnDraw(SAKEXE, "UIWhisperListWnd::OnDraw");
void UIWhisperListWnd::OnDraw() // line 814-910
{
	return (this->*_OnDraw)();

	//TODO
}


void UIWhisperListWnd::OnLBtnDblClk(int x, int y) // line 913-915
{
	this->SendMsg(NULL, 71, 0, 0, 0);
}


void UIWhisperListWnd::OnLBtnDown(int x, int y) // line 918-928
{
	if( y >= 17 )
	{
		int oldItem = m_curItem;
		m_curItem = this->UIWhisperListWnd::GetCurItem(x, y);

		if( oldItem != m_curItem )
			this->Invalidate();
	}
	else
	{
		this->UIFrameWnd::OnLBtnDown(x, y);
	}
}


void UIWhisperListWnd::OnRBtnUp(int x, int y) // line 931-937
{
	int oldItem = m_curItem;
	m_curItem = this->UIWhisperListWnd::GetCurItem(x, y);

	if( oldItem != m_curItem )
		this->Invalidate();

	this->SendMsg(this, 49, 0, 0, 0);
}


void UIWhisperListWnd::StoreInfo() // line 940-947
{
	if( m_info != NULL )
	{
		m_info->w = m_w;
		m_info->h = m_h;
		m_info->x = m_x;
		m_info->y = m_y;
	}
}


hook_method<int (UIWhisperListWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIWhisperListWnd::_SendMsg(SAKEXE, "UIWhisperListWnd::SendMsg");
int UIWhisperListWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 950-1200
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3);

	//TODO
}


hook_method<void (UIWhisperListWnd::*)(void)> UIWhisperListWnd::_DeleteCurWhisperName(SAKEXE, "UIWhisperListWnd::DeleteCurWhisperName");
void UIWhisperListWnd::DeleteCurWhisperName(void) // line 1203-1229
{
	return (this->*_DeleteCurWhisperName)();

	//TODO
}


hook_method<void (UIWhisperListWnd::*)(int wheel)> UIWhisperListWnd::_OnWheel(SAKEXE, "UIWhisperListWnd::OnWheel");
void UIWhisperListWnd::OnWheel(int wheel) // line 1232-1242
{
	return (this->*_OnWheel)(wheel);

	//TODO
}


hook_method<void (UIWhisperListWnd::*)(void)> UIWhisperListWnd::_RecalcScrbarPos(SAKEXE, "UIWhisperListWnd::RecalcScrbarPos");
void UIWhisperListWnd::RecalcScrbarPos(void) // line 1245-1272
{
	return (this->*_RecalcScrbarPos)();

	//TODO
}


hook_method<int (UIWhisperListWnd::*)(int x, int y)> UIWhisperListWnd::_GetCurItem(SAKEXE, "UIWhisperListWnd::GetCurItem");
int UIWhisperListWnd::GetCurItem(int x, int y) // line 1275-1302
{
	return (this->*_GetCurItem)(x, y);

	//TODO
}


////////////////////////////////////////


UIFriendOptionWnd::UIFriendOptionWnd() // line 1307-1309
{
	m_info = NULL;
}


UIFriendOptionWnd::~UIFriendOptionWnd() // line 1312-1313
{
}


void UIFriendOptionWnd::OnCreate(int cx, int cy) // line 1316-1364
{
	int width1 = 12 + this->UIWindow::GetTextWidth(MsgStr(MSI_AUTOOPEN_1ON1_WINDOW), 0, 0, 12, false);
	if( width1 >= m_w - 15 )
		width1 = m_w - 15;

	m_showWhisperWndCheckBox = new UICheckBox();
	m_showWhisperWndCheckBox->UIWindow::Create(width1, 12);
	m_showWhisperWndCheckBox->UICheckBox::SetBitmap2("유저인터페이스\\checkbox_1.bmp", "유저인터페이스\\checkbox_0.bmp", MsgStr(MSI_AUTOOPEN_1ON1_WINDOW));
	m_showWhisperWndCheckBox->Move(6, 21);
	m_showWhisperWndCheckBox->UICheckBox::SetCheck(g_session.m_isShowWhisperWnd);
	this->UIWindow::AddChild(m_showWhisperWndCheckBox);

	int width2 = 12 + this->UIWindow::GetTextWidth(MsgStr(MSI_AUTOOPENWHISPERLISTWND_FRIEND), 0, 0, 12, false);
	if( width2 >= m_w - 15 )
		width2 = m_w - 15;

	m_showFriendWhisperWndCheckBox = new UICheckBox();
	m_showFriendWhisperWndCheckBox->UIWindow::Create(width2, 12);
	m_showFriendWhisperWndCheckBox->UICheckBox::SetBitmap2("유저인터페이스\\checkbox_1.bmp", "유저인터페이스\\checkbox_0.bmp", MsgStr(MSI_AUTOOPENWHISPERLISTWND_FRIEND));
	m_showFriendWhisperWndCheckBox->Move(6, 37);
	m_showFriendWhisperWndCheckBox->UICheckBox::SetCheck(g_session.m_isShowWhisperWnd_Friend);
	this->UIWindow::AddChild(m_showFriendWhisperWndCheckBox);

	int width3 = 12 + this->UIWindow::GetTextWidth(MsgStr(MSI_WHISPER_OPEN_SOUND), 0, 0, 12, false);
	if( width3 >= m_w - 15 )
		width3 = m_w - 15;

	m_playWhisperOpenSoundCheckBox = new UICheckBox();
	m_playWhisperOpenSoundCheckBox->UIWindow::Create(width3, 12);
	m_playWhisperOpenSoundCheckBox->UICheckBox::SetBitmap2("유저인터페이스\\checkbox_1.bmp", "유저인터페이스\\checkbox_0.bmp", MsgStr(MSI_WHISPER_OPEN_SOUND));
	m_playWhisperOpenSoundCheckBox->Move(6, 53);
	m_playWhisperOpenSoundCheckBox->UICheckBox::SetCheck(g_session.m_isPlayWhisperOpenSound);
	this->UIWindow::AddChild(m_playWhisperOpenSoundCheckBox);

	int ids2[3];
	ids2[0] = ID_CLOSE;
	ids2[1] = 0;
	ids2[2] = 0;

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
	m_sysButton->UIWindow::SetId(ids2[0]);
	m_sysButton->UIButton::SetToolTip("Alt+I");
	this->UIWindow::AddChild(m_sysButton);
}


void UIFriendOptionWnd::OnDraw() // line 1367-1419
{
	CBitmapRes* bitmapRes;
	unsigned long rr, gg, bb;

	bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\titlebar_left.bmp"));
	this->UIWindow::DrawBitmap(0, 0, bitmapRes, false);

	bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\titlebar_right.bmp"));
	this->UIWindow::DrawBitmap(m_w - bitmapRes->m_width, 0, bitmapRes, false);

	for( int i = 0; i < (m_w - 24) / 12 + ((m_w - 24) % 12 != 0); ++i )
	{
		bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\titlebar_mid.bmp"));
		this->UIWindow::DrawBitmap(12 + i * 12, 0, bitmapRes, false);
	}

	this->UIWindow::TextOutA(5, 3, MsgStr(MSI_FRIEND_SETTING), 0, 0, 12, 0xFFFFFF);
	this->UIWindow::TextOutA(4, 2, MsgStr(MSI_FRIEND_SETTING), 0, 0, 12, 0x000000);

	g_skinMgr.CSkinMgr::GetColorChipColor(14, 6, rr, gg, bb);
	this->UIWindow::DrawBox(0, 17, m_w, m_h - 17, RGB(rr, gg, bb));

	g_skinMgr.CSkinMgr::GetColorChipColor(2, 2, rr, gg, bb);
	this->UIWindow::DrawBox(1, 17, m_w - 2, m_h - 17, RGB(rr,gg,bb));

	bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\btnbar_left2.bmp"));
	this->UIWindow::DrawBitmap(0, m_h - bitmapRes->m_height, bitmapRes, false);

	bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\btnbar_right2.bmp"));
	this->UIWindow::DrawBitmap(m_w - bitmapRes->m_width, m_h - bitmapRes->m_height, bitmapRes, false);

	for( int i = 0; i < (m_w - 42) / 21 + ((m_w - 42) % 21 != 0); ++i )
	{
		bitmapRes = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp("유저인터페이스\\basic_interface\\btnbar_mid2.bmp"));
		this->UIWindow::DrawBitmap(21 + i * 21, m_h - bitmapRes->m_height, bitmapRes, false);
	}
}


int UIFriendOptionWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 1432-1469
{
	switch( message )
	{
	case UM_COMMAND:
	{
		UIID id = (UIID)val1;

		switch( id )
		{
		case ID_CLOSE:
		{
			g_windowMgr.UIWindowMgr::DeleteWindow(WID_FRIENDOPTIONWND);
		}
		break;
		case ID_CHECK:
		{
			BOOL flag = (BOOL)val2;

			if( m_showWhisperWndCheckBox == sender )
				g_session.m_isShowWhisperWnd = flag;
			else
			if( m_showFriendWhisperWndCheckBox == sender )
				g_session.m_isShowWhisperWnd_Friend = flag;
			else
			if( m_playWhisperOpenSoundCheckBox == sender )
				g_session.m_isPlayWhisperOpenSound = flag;
		}
		break;
		};
	}
	break;
	case UM_SETINFO:
	{
		FriendOptionWndInfo* info = (FriendOptionWndInfo*)val1;

		m_info = info;
		if( !m_info->FriendOptionWndInfo::IsValidInfo() )
			m_info->FriendOptionWndInfo::MakeDefault();

		this->Move(m_info->x, m_info->y);
	}
	break;
	default:
	{
		return this->UIFrameWnd::SendMsg(sender, message, val1, val2, val3);
	}
	break;
	};

	return 0;
}


void UIFriendOptionWnd::StoreInfo() // line 1422-1429
{
	if( m_info != NULL )
	{
		m_info->w = m_w;
		m_info->h = m_h;
		m_info->x = m_x;
		m_info->y = m_y;
	}
}
