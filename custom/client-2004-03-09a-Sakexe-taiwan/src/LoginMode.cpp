#include "Globals.h"
#include "LoginMode.h"
#include "ModeMgr.h"
#include "MsgStrings.h" // UIBmp()
#include "Packet.h"
#include "Base/FindHack.h" // WinMainNpKeyStartEncryption(), WinMainNpKeyStopEncryption()
#include "Base/ResMgr.h"
#include "Device/Connection.h"
#include "Device/md5.h"
#include "Device/Sound.h" // CloseStream(), EndDigitalSound()
#include "Device/Timer.h" //SkipSceneRendering()
#include "Framework/Locale.h" // GetLicenceText()
#include "Window/UIFrameWnd.h"
#include "Window/UIFrameWnd2.h"
#include "WinMain.h" // CheckSystemMessage()
#include <ShellAPI.h> // ShellExecuteA()


CLoginMode::CLoginMode(void) // line 55
{
	m_fadeInCount = 1;
	m_syncRequestTime = timeGetTime() + 12000;
	m_multiLang = g_multiLang;
	g_multiLang = 0;
}


CLoginMode::~CLoginMode(void) // line 63
{
	g_multiLang = m_multiLang;
}


hook_method<void (CLoginMode::*)(const char* modeName)> CLoginMode::_OnInit(SAKEXE, "CLoginMode::OnInit");
void CLoginMode::OnInit(const char* modeName) // line 68
{
	return (this->*_OnInit)(modeName);

	m_logoShowTime = 0;
	CloseStream();
	g_mouse.CMouse::ResetButtonState();
	m_charParam[0] = 5;
	m_charParam[1] = 5;
	m_charParam[2] = 5;
	m_charParam[3] = 5;
	m_charParam[4] = 5;
	m_charParam[5] = 5;
	m_charParam[6] = 0;
	m_charParam[7] = 1;
	m_makingCharName[0] = '\0';
	m_emaiAddress[0] = '\0';
	m_wallPaperBmpName = "유저인터페이스\\bgi_temp.bmp";
	m_loopCond = TRUE;
	m_nextSubMode = -1;
	m_nextSubMode = -1;
	m_subMode = g_loginStartMode;
	m_subModeCnt = 0;
	this->OnChangeState(g_loginStartMode);
	g_loginStartMode = 3;
	g_isStopByLogin = 1;
	g_session.CSession::InitWithClear();
	g_guildInfo.GuildInfo::Init();
	g_session.CSession::PreLoadAlwaysNeededRes();
	if( !g_session.m_bgmIsPaused )
		PlayStream("bgm\\01.mp3");
	memset(&m_billingInfo, 0, sizeof(m_billingInfo));
	WinMainNpKeyStartEncryption();
}


hook_method<int (CLoginMode::*)(void)> CLoginMode::_OnRun(SAKEXE, "CLoginMode::OnRun");
int CLoginMode::OnRun(void) // line 101
{
	return (this->*_OnRun)();

	while( m_loopCond )
	{
		if( g_sysQuit )
			break;

		if( !g_windowMgr.UIWindowMgr::IsModalStatus() )
		{
			if( m_nextSubMode != -1 )
			{
				m_subMode = m_nextSubMode;
				m_subModeCnt = 0;
				m_nextSubMode = -1;
				this->OnChangeState(m_subMode);
			}
		}

		this->OnUpdate();
		++m_subModeCnt;
	};

	this->CMode::RunFadeOut(0);
	return 1;
}


hook_method<void (CLoginMode::*)(void)> CLoginMode::_OnExit(SAKEXE, "CLoginMode::OnExit");
void CLoginMode::OnExit(void) // line 193
{
	return (this->*_OnExit)();

	EndDigitalSound();
	g_resMgr().CResMgr::UnloadUnlockedRes();
	g_renderer->CRenderer::ReleaseCacheSurfaces();
	WinMainNpKeyStopEncryption();
}


hook_method<void (CLoginMode::*)(void)> CLoginMode::_OnUpdate(SAKEXE, "CLoginMode::OnUpdate");
void CLoginMode::OnUpdate(void) // line 132
{
	return (this->*_OnUpdate)();

	if( g_session.CSession::IsKorean() && m_logoShowTime != 0 )
	{
		if( timeGetTime() < m_logoShowTime )
		{
			g_mouse.CMouse::ReadState();
			goto rendering;
		}

		m_wallPaperBmpName = "유저인터페이스\\bgi_temp.bmp";
		CBitmapRes* bmp = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp(m_wallPaperBmpName.c_str()));
		g_windowMgr.UIWindowMgr::SetWallpaper(bmp);

		UIFrameWnd* wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_LOGINWND);
		if( !g_hideAccountList )
			wnd->SendMsg(NULL, 88, 0, 0, 0);

		m_logoShowTime = 0;
		m_fadeInCount = 1;
	}

	CheckSystemMessage();
	this->CLoginMode::PollNetworkStatus();

	if( g_serviceType == ServiceKorea || g_serviceType == ServiceAmerica )
		this->CLoginMode::CheckPingTime();

	g_mouse.CMouse::ReadState();
	g_windowMgr.UIWindowMgr::ProcessInput();
	this->CMode::ProcessKeyBoard();

	if( m_loopCond )
	{
		this->CLoginMode::OnProcessState(m_subMode);
		this->CMode::ProcessHelpBalloon();
	}

	if( g_activatedNow != 0 )
	{
		g_activatedNow = 0;

		if( g_3dDevice.C3dDevice::IsFullscreen() )
		{
			g_3dDevice.C3dDevice::RestoreSurfaces();
			g_windowMgr.UIWindowMgr::InvalidateAll();
			CBitmapRes* bmp = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp(m_wallPaperBmpName.c_str()));
			g_windowMgr.UIWindowMgr::SetWallpaper(bmp);
		}
	}

rendering:
	if( g_isAppActive || !g_3dDevice.C3dDevice::IsFullscreen() )
	{
		if( SkipSceneRendering() )
		{
			g_renderer->CRenderer::Clear(1);
			g_windowMgr.UIWindowMgr::OnProcess();
			g_windowMgr.UIWindowMgr::Render();
			this->CMode::DrawMouseCursor();
			this->CMode::ProcessFadeIn();
			if( g_renderer->CRenderer::DrawScene() )
				g_renderer->CRenderer::Flip(1);
		}

		this->CMode::ScreenShot();
	}
}


hook_method<int (CLoginMode::*)(int messageId, int val1, int val2, int val3)> CLoginMode::_SendMsg(SAKEXE, "CLoginMode::SendMsg");
int CLoginMode::SendMsg(int messageId, int val1, int val2, int val3) // line 638
{
	return (this->*_SendMsg)(messageId, val1, val2, val3);

	switch( messageId )
	{
	case MM_COMMAND:
		switch( val1 )
		{
		case 10004:
			m_nextSubMode = 7;
		break;
		case 10010:
			m_nextSubMode = 11;
		break;
		case 10001:
			m_nextSubMode = 8;
		break;
		case 10002:
			m_nextSubMode = 9;
		break;
		case 10006:
			if( m_subMode == 7 )
			{
				g_windowMgr.UIWindowMgr::RemoveAllWindows();
				g_connection.CConnection::Disconnect();
				m_nextSubMode = 6;
			}
		break;
		default:
		break;
		}
		return 0;
	break;
	case MM_SOCKETERROR:
		g_connection.CConnection::Disconnect();
		if( g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_UNABLE_TO_CONNECT_SERVER), 0, 1, 1, 0) != 178 )
		{
			g_mustPumpOutReceiveQueue = FALSE;
			m_nextSubMode = 3;
		}
		return 0;
	break;
	case MM_QUERYCHARICTORINFO:
		for( int i = 0; i < m_numChar; ++i )
			if( m_charInfo[i].CharNum == val1 )
				return (int)&m_charInfo[i];
		return 0;
	break;
	case MM_GOTOIDENTRY:
		g_mustPumpOutReceiveQueue = FALSE;
		m_nextSubMode = 3;
		return 0;
	break;
	case LMM_CONNECT_TO_ACSVR:
		m_nextSubMode = 4;
		return 0;
	break;
	case LMM_SELECTSVR:
	{
		m_serverSelected = val1;
		if( val1 == -1 )
			return 0;

		if( m_serverInfo[m_serverSelected].state == SERVERSTATE_PAY )
		{
			g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_CANT_CONNECT_TO_PAY_SERVER), 0, 1, 0, 0);
			m_nextSubMode = 6;
			return 0;
		}

		ServerAddress addr;
		unsigned long ip = m_serverInfo[m_serverSelected].ip;
		sprintf(addr.ip, "%d.%d.%d.%d", BYTE(ip >> 0), BYTE(ip >> 8), BYTE(ip >> 16), BYTE(ip >> 24));
		addr.port = m_serverInfo[m_serverSelected].port;
		memcpy(&g_charServerAddr, &addr, sizeof(g_charServerAddr));

		g_session.m_selectedServerName = (char*)m_serverInfo[m_serverSelected].name;
		g_session.m_lastServerName = (char*)m_serverInfo[m_serverSelected].name;

		g_session.CSession::InitExListWithRegistry();
		g_bOldServer = 0;
		m_nextSubMode = 5;
		return 0;
	}
	break;
	case LMM_SENDCHARINFO:
		m_nextSubMode = 10;
		return 0;
	break;
	case LMM_CANCEL:
		if( m_subMode == 6 )
		{
			g_connection.CConnection::Disconnect();
			g_mustPumpOutReceiveQueue = FALSE;
			m_nextSubMode = 3;
		}
		return 0;
	break;
	case LMM_PASSWORD:
		strcpy(m_userPassword, (const char*)val1);
		return 0;
	break;
	case LMM_ID:
		strcpy(m_userId, (const char*)val1);
		strcpy(g_session.m_aName, (const char*)val1);
		return 0;
	break;
	case LMM_SELECT_CHARACTER:
		g_session.m_charSlot = g_charInfo.CharNum;
		g_windowMgr.UIWindowMgr::InitShortcutItemInfoFromReg();
		g_windowMgr.UIWindowMgr::InitSkillUseLevelInfoFromReg();
		g_windowMgr.UIWindowMgr::InitFriendNameListFromRegistry();

		for( int i = 0; i < m_numChar; ++i )
		{
			if( g_charInfo.CharNum == m_charInfo[i].CharNum )
			{
				g_session.m_charNum = m_charInfo[i].CharNum;
				g_session.CSession::SetJob(m_charInfo[i].job); //inlined
				g_session.CSession::SetGid(m_charInfo[i].GID); //inlined
				g_session.CSession::SetSpeed(m_charInfo[i].speed); //inlined
				g_session.CSession::SetLevel(m_charInfo[i].level); //inlined
				g_session.CSession::SetSkillPoint(m_charInfo[i].sppoint); //inlined
				g_session.CSession::SetPoint(m_charInfo[i].jobpoint); //inlined
				g_session.CSession::SetStr(m_charInfo[i].Str); //inlined
				g_session.CSession::SetAgi(m_charInfo[i].Agi); //inlined
				g_session.CSession::SetVit(m_charInfo[i].Vit); //inlined
				g_session.CSession::SetInt(m_charInfo[i].Int); //inlined
				g_session.CSession::SetDex(m_charInfo[i].Dex); //inlined
				g_session.CSession::SetLuk(m_charInfo[i].Luk); //inlined
				g_session.CSession::SetExp(m_charInfo[i].exp); //inlined
				g_session.CSession::SetHp(m_charInfo[i].hp); //inlined
				g_session.CSession::SetMaxhp(m_charInfo[i].maxhp); //inlined
				g_session.CSession::SetSp(m_charInfo[i].sp); //inlined
				g_session.CSession::SetMaxsp(m_charInfo[i].maxsp); //inlined
				g_session.CSession::SetGold(m_charInfo[i].money); //inlined
				g_session.CSession::SetJobexp(m_charInfo[i].jobexp); //inlined
				g_session.CSession::SetVirtue(m_charInfo[i].virtue); //inlined
				g_session.CSession::SetHonor(m_charInfo[i].honor); //inlined
				g_session.CSession::SetJoblevel(m_charInfo[i].joblevel); //inlined
				g_session.m_haircolor   = m_charInfo[i].haircolor;
				g_session.m_head        = m_charInfo[i].head;
				g_session.m_weapon      = m_charInfo[i].weapon;
				g_session.m_accessory   = m_charInfo[i].accessory;
				g_session.m_shield      = m_charInfo[i].shield;
				g_session.m_bodyPalette = m_charInfo[i].bodypalette;
				g_session.m_headPalette = m_charInfo[i].headpalette;
				g_session.m_accessory2  = m_charInfo[i].accessory2;
				g_session.m_accessory3  = m_charInfo[i].accessory3;
				g_session.m_bodyState   = m_charInfo[i].bodystate;
				g_session.m_healthState = m_charInfo[i].healthstate;
				g_session.m_effectState = m_charInfo[i].effectstate;

				break; //found.
			}
		}
		return 0;
	break;
	case LMM_GOTO_LOGIN:
		g_connection.CConnection::Disconnect();
		g_mustPumpOutReceiveQueue = FALSE;
		m_nextSubMode = 3;
		return 0;
	break;
	case LMM_SET_EMAIL_ADDRESS:
		g_windowMgr.UIWindowMgr::InvalidateAll();
		strcpy(m_emaiAddress, (const char*)val1);
		return 0;
	break;
	case LMM_GET_EMAIL_ADDRESS:
		return (int)m_emaiAddress;
	break;
	case LMM_GET_MAKING_CHAR_NAME:
		return (int)m_makingCharName;
	break;
	case LMM_SET_MAKING_CHAR_NAME:
		strcpy(m_makingCharName, (const char*)val1);
		return 0;
	break;
	case LMM_GET_CHAR_PARAM:
		return (int)m_charParam;
	break;
	case LMM_SET_CHAR_PARAM:
		for( int i = 0; i < 8; ++i )
			m_charParam[i] = ((int*)val1)[i];
		return 0;
	break;
	case LMM_GOTOSELECTACCOUNT:
		if( val2 == 111 )
			g_modeMgr.CModeMgr::GetCurMode()->SendMsg(2, 0, 0, 0);
		else
			m_nextSubMode = 2;
		return 0;
	break;
	case LMM_SELECTACCOUNT:
		SelectClientInfo(val1);
		m_nextSubMode = 3;
		return 0;
	break;
	case LMM_GET_BILLING_INFO:
	{
		char* buf = (char*)val1;

		switch( m_billingInfo.code )
		{
		case 100:
		{
			unsigned long t = m_billingInfo.time1;
			int minutes = t / 60;
			sprintf(buf, MsgStr(MSI_BILLING_100), minutes);
		}
		break;
		case 200:
		{
			unsigned long t = m_billingInfo.time1;
			int seconds = t % 60;
			int minutes = t / 60 % 60;
			int hours   = t / 60 / 60;
			sprintf(buf, MsgStr(MSI_BILLING_200), hours, minutes, seconds);
		}
		break;
		case 300:
		{
			sprintf(buf, MsgStr(MSI_BILLING_300));
		}
		break;
		case 400:
		{
			unsigned long t = m_billingInfo.time2 - m_billingInfo.time1;
			int seconds = t % 60;
			int minutes = t / 60 % 60;
			int hours   = t / 60 / 60;
			sprintf(buf, MsgStr(MSI_BILLING_400), hours, minutes, seconds);
		}
		break;
		case 500:
		{
			if( m_billingInfo.time1 != 0 )
			{
				unsigned long t = m_billingInfo.time1;
				int seconds = t % 60;
				int minutes = t / 60 % 60;
				int hours   = t / 60 / 60;
				sprintf(buf, MsgStr(MSI_BILLING_500), hours, minutes, seconds);
			}
			else
			{
				unsigned long t = m_billingInfo.time2;
				int seconds = t % 60;
				int minutes = t / 60 % 60;
				int hours   = t / 60 / 60;
				sprintf(buf, MsgStr(MSI_BILLING_501), hours, minutes, seconds);
			}
		}
		break;
		case 600:
			sprintf(buf, MsgStr(MSI_BILLING_600));
		break;
		case 700:
			sprintf(buf, MsgStr(MSI_BILLING_700));
		break;
		case 800:
			sprintf(buf, MsgStr(MSI_BILLING_800));
		break;
		default:
			sprintf(buf, MsgStr(MSI_CHARACTER_INFO));
		break;
		}
		return 0;
	}
	break;
	default:
		return this->CMode::SendMsg(messageId, val1, val2, val3);
	break;
	}
}


hook_method<void (CLoginMode::*)(void)> CLoginMode::_PreLoadAlwaysNeededRes(SERVER, "CLoginMode::PreLoadAlwaysNeededRes");
void CLoginMode::PreLoadAlwaysNeededRes(void) // line 97
{
	return (this->*_PreLoadAlwaysNeededRes)();

	g_session.CSession::PreLoadAlwaysNeededRes();
}


hook_method<void (CLoginMode::*)(int state)> CLoginMode::_OnChangeState(SAKEXE, "CLoginMode::OnChangeState");
void CLoginMode::OnChangeState(int state) // line 200
{
	return (this->*_OnChangeState)(state);

	m_subModeStartTime = timeGetTime();
	g_windowMgr.UIWindowMgr::RemoveAllWindows();
	m_isConnected = 1;

	UIFrameWnd* wnd;
	switch( state )
	{
	case 0:
	{
		if( g_serviceType == ServiceJapan )
		{
			m_nextSubMode = 2;
			return;
		}

		m_wallPaperBmpName = "유저인터페이스\\login_interface\\warning.bmp";
		g_windowMgr.UIWindowMgr::SetWallpaper((CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp(m_wallPaperBmpName.c_str())));
		wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_NOTICECONFIRMWND);
		wnd->SendMsg(NULL, 80, 10018, 0, 0);
	}
	return;
	case 1:
	{
		m_wallPaperBmpName = "유저인터페이스\\bgi_temp.bmp";
		g_windowMgr.UIWindowMgr::SetWallpaper((CBitmapRes *)g_resMgr().CResMgr::Get(UIBmp(m_wallPaperBmpName.c_str())));
		wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_SAYDIALOGWND);
		wnd->Resize(400, 300);
		wnd->Move((g_renderer->GetWidth() - 640) / 2 + 120, (g_renderer->GetHeight() - 480) / 2 + 90);
		wnd->SendMsg(NULL, 85, 111, (int)"btn_disagree", 0);
		wnd->SendMsg(NULL, 85, 128, (int)"btn_agree", 0);
		wnd->SendMsg(NULL, 26, (int)GetLicenceText(), 0, 58);
		wnd->SendMsg(NULL, 80, 10018, 0, 0);
	}
	return;
	case 2:
	{
		if( !this->CLoginMode::InitAccountInfo() )
		{
			this->SendMsg(30, 0, 0, 0);
			return;
		}

		m_wallPaperBmpName = "유저인터페이스\\bgi_temp.bmp";
		g_windowMgr.UIWindowMgr::SetWallpaper((CBitmapRes *)g_resMgr().CResMgr::Get(UIBmp(m_wallPaperBmpName.c_str())));
		wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_SELECTSERVERWND);
		wnd->SendMsg(NULL, 80, 10019, (int)"NUMACCOUNT", 0);
		for( mystd::vector<accountInfo>::iterator i = m_accountInfo.begin(); i != m_accountInfo.end(); ++i )
			((UISelectServerWnd*)wnd)->m_serverList->AddItem(i->display.c_str());
		wnd->SendMsg(NULL, 40, 0, 0, 0);
		wnd->SendMsg(NULL, 89, 0, 0, 0);
	}
	return;
	case 3:
	{
		m_logoShowTime = 0;
		m_wallPaperBmpName = "유저인터페이스\\bgi_temp.bmp";
		g_windowMgr.UIWindowMgr::SetWallpaper((CBitmapRes *)g_resMgr().CResMgr::Get(UIBmp(m_wallPaperBmpName.c_str())));
		wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_LOGINWND);
		if( !g_hideAccountList )
			wnd->SendMsg(NULL, 88, 0, 0, 0);
	}
	return;
	case 6:
	{
		m_wallPaperBmpName = "유저인터페이스\\bgi_temp.bmp";
		g_windowMgr.UIWindowMgr::SetWallpaper((CBitmapRes *)g_resMgr().CResMgr::Get(UIBmp(m_wallPaperBmpName.c_str())));

		wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_SELECTSERVERWND);
		UISelectServerWnd* selectServerWnd = (UISelectServerWnd*)wnd;
		wnd->SendMsg(0, 80, 10003, (int)"NUMSERVER", 0);

		for( int i = 0; i < m_numServer; ++i )
		{
			SERVER_ADDR& s = m_serverInfo[i];
			char p[64] = {};

			if( s.property == SERVERPROPERTY_NEW )
				sprintf(p, MsgStr(MSI_SERVER_PROPERTY_NEW));

			sprintf(p + strlen(p), (char*)s.name); //FIXME: uncontrolled format string vulnerability

			switch( s.state )
			{
			case SERVERSTATE_NORMAL : sprintf(p + strlen(p), MsgStr(MSI_SERVER_USER_COUNT), s.usercount); break;
			case SERVERSTATE_INSPECT: sprintf(p + strlen(p), MsgStr(MSI_SERVER_INSPECTING), s.usercount); break;
			case SERVERSTATE_ADULT  : sprintf(p + strlen(p), MsgStr(MSI_SERVER_PROPERTY_ADULT), s.usercount); break;
			case SERVERSTATE_PAY    : sprintf(p + strlen(p), MsgStr(MSI_SERVER_PROPERTY_PAY), s.usercount); break;
			case SERVERSTATE_FREE   : sprintf(p + strlen(p), MsgStr(MSI_SERVER_PROPERTY_FREE), s.usercount); break;
			default: break;
			}

			selectServerWnd->m_serverList->AddItem(p);
		}

		selectServerWnd->SendMsg(NULL, 40, 0, 0, 0);
	}
	return;
	case 7:
	{
		g_session.m_petJob = -1;
		g_session.CSession::SetEquipArrowIndwx(0);
		m_wallPaperBmpName = "유저인터페이스\\bgi_temp.bmp";
		g_windowMgr.UIWindowMgr::SetWallpaper((CBitmapRes *)g_resMgr().CResMgr::Get(UIBmp(m_wallPaperBmpName.c_str())));
		g_windowMgr.UIWindowMgr::MakeWindow(WID_SELECTCHARWND);
	}
	return;
	case 8:
	{
		m_wallPaperBmpName = "유저인터페이스\\bgi_temp.bmp";
		g_windowMgr.UIWindowMgr::SetWallpaper((CBitmapRes *)g_resMgr().CResMgr::Get(UIBmp(m_wallPaperBmpName.c_str())));
		g_windowMgr.UIWindowMgr::MakeWindow(WID_MAKECHARWND);
	}
	return;
	case 4:
	{
		m_wallPaperBmpName = "유저인터페이스\\bgi_temp.bmp";
		g_windowMgr.UIWindowMgr::SetWallpaper((CBitmapRes *)g_resMgr().CResMgr::Get(UIBmp(m_wallPaperBmpName.c_str())));

		ServerAddress addr;
		strcpy(addr.ip, g_accountAddr);
		addr.port = atoi(g_accountPort);

		m_isConnected = g_connection.CConnection::Connect(&addr);
		if( !m_isConnected )
		{
			g_connection.CConnection::Disconnect();
			if( g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_SERVER_CONNECTION_FAILED), 1, 1, 1, 0) != 178 )
			{
				g_mustPumpOutReceiveQueue = FALSE;
				m_nextSubMode = 3;
			}
			return;
		}

		if( !g_passwordEncrypt )
		{
			PACKET_CA_LOGIN packet;
			packet.PacketType = HEADER_CA_LOGIN;
			packet.Version = g_version;
			memcpy(packet.ID, m_userId, sizeof(packet.ID));
			memcpy(packet.Passwd, m_userPassword, sizeof(packet.Passwd));
			packet.clienttype = GetAccountType();
			g_connection.CRagConnection::SendPacket(g_connection.CRagConnection::GetPacketSize(HEADER_CA_LOGIN), (const char*)&packet);
		}
		else
		{
			PACKET_CA_REQ_HASH packet;
			packet.PacketType = HEADER_CA_REQ_HASH;
			g_connection.CRagConnection::SendPacket(g_connection.CRagConnection::GetPacketSize(HEADER_CA_REQ_HASH), (const char*)&packet);
		}

		wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_WAITWND);
		((UIWaitWnd *)wnd)->UIWaitWnd::SetMsg(MsgStr(MSI_WAITING_RESPONSE_FROM_SERVER), 16, 1);
	}
	return;
	case 5:
	{
		m_wallPaperBmpName = "유저인터페이스\\bgi_temp.bmp";
		g_windowMgr.UIWindowMgr::SetWallpaper((CBitmapRes *)g_resMgr().CResMgr::Get(UIBmp(m_wallPaperBmpName.c_str())));

		g_connection.CConnection::Disconnect();
		m_isConnected = g_connection.CConnection::Connect(&g_charServerAddr);
		if( !m_isConnected )
		{
			g_connection.CConnection::Disconnect();
			if( g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_SERVER_CONNECTION_FAILED), 1, 1, 1, 0) != 178 )
			{
				g_mustPumpOutReceiveQueue = FALSE;
				m_nextSubMode = 3;
			}
			return;
		}

		g_mustPumpOutReceiveQueue = TRUE;

		PACKET_CH_ENTER packet;
		packet.PacketType = HEADER_CH_ENTER;
		packet.AID = g_session.GetAid();
		packet.AuthCode = g_session.m_authCode;
		packet.userLevel = g_session.m_userLevel;
		packet.clientType = 0;
		packet.Sex = g_session.CSession::GetSex();
		g_connection.CRagConnection::SendPacket(g_connection.CRagConnection::GetPacketSize(HEADER_CH_ENTER), (const char*)&packet);

		wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_WAITWND);
		((UIWaitWnd *)wnd)->UIWaitWnd::SetMsg(MsgStr(MSI_WAITING_RESPONSE_FROM_SERVER), 16, 1);
	}
	return;
	case 10:
	{
		m_wallPaperBmpName = "유저인터페이스\\bgi_temp.bmp";
		g_windowMgr.UIWindowMgr::SetWallpaper((CBitmapRes *)g_resMgr().CResMgr::Get(UIBmp(m_wallPaperBmpName.c_str())));

		PACKET_CH_MAKE_CHAR packet;
		packet.PacketType = HEADER_CH_MAKE_CHAR;
		memcpy(packet.name, g_charInfo.name, sizeof(packet.name));
		packet.Str = g_charInfo.Str;
		packet.Agi = g_charInfo.Agi;
		packet.Vit = g_charInfo.Vit;
		packet.Int = g_charInfo.Int;
		packet.Dex = g_charInfo.Dex;
		packet.Luk = g_charInfo.Luk;
		packet.CharNum = g_charInfo.CharNum;
		packet.headPal = g_charInfo.headpalette;
		packet.head = g_charInfo.head;
		g_connection.CRagConnection::SendPacket(g_connection.CRagConnection::GetPacketSize(HEADER_CH_MAKE_CHAR), (const char*)&packet);

		wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_WAITWND);
		((UIWaitWnd *)wnd)->UIWaitWnd::SetMsg(MsgStr(MSI_MAKING_CHARACTER), 17, 1);
	}
	return;
	case 11:
	{
		m_wallPaperBmpName = "유저인터페이스\\bgi_temp.bmp";
		g_windowMgr.UIWindowMgr::SetWallpaper((CBitmapRes *)g_resMgr().CResMgr::Get(UIBmp(m_wallPaperBmpName.c_str())));

		PACKET_CH_DELETE_CHAR packet;
		packet.PacketType = HEADER_CH_DELETE_CHAR;
		packet.GID = this->SendMsg(8, g_charInfo.CharNum, 0, 0);
		strncpy(packet.key, m_emaiAddress, sizeof(packet.key));
		if( g_serviceType == ServiceKorea && m_emaiAddress[7] != '\0' )
			m_emaiAddress[0] = '\0';
		Trace("%s", m_emaiAddress);
		g_connection.CRagConnection::SendPacket(g_connection.CRagConnection::GetPacketSize(HEADER_CH_DELETE_CHAR), (const char*)&packet);

		wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_WAITWND);
		((UIWaitWnd *)wnd)->UIWaitWnd::SetMsg(MsgStr(MSI_DELETING_CHARACTER), 17, 1);
	}
	return;
	case 9:
	{
		m_wallPaperBmpName = "유저인터페이스\\bgi_temp.bmp";
		g_windowMgr.UIWindowMgr::SetWallpaper((CBitmapRes *)g_resMgr().CResMgr::Get(UIBmp(m_wallPaperBmpName.c_str())));

		PACKET_CH_SELECT_CHAR packet;
		packet.PacketType = HEADER_CH_SELECT_CHAR;
		packet.CharNum = g_charInfo.CharNum;
		g_connection.CRagConnection::SendPacket(g_connection.CRagConnection::GetPacketSize(HEADER_CH_SELECT_CHAR), (const char*)&packet);

		wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_WAITWND);
		((UIWaitWnd *)wnd)->UIWaitWnd::SetMsg(MsgStr(MSI_WAITING_RESPONSE_FROM_SERVER), 16, 1);
	}
	return;
	case 12:
	{
		m_wallPaperBmpName = "유저인터페이스\\bgi_temp.bmp";
		g_windowMgr.UIWindowMgr::SetWallpaper((CBitmapRes *)g_resMgr().CResMgr::Get(UIBmp(m_wallPaperBmpName.c_str())));

		m_isConnected = g_connection.CConnection::Connect(&g_zoneServerAddr);
		if( !m_isConnected )
		{
			g_connection.CConnection::Disconnect();
			if( g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_SERVER_CONNECTION_FAILED), 1, 1, 1, 0) != 178 )
			{
				g_mustPumpOutReceiveQueue = FALSE;
				m_nextSubMode = 3;
			}
			return;
		}

		g_mustPumpOutReceiveQueue = TRUE;

		Trace("PACKET_CZ_ENTER");
		PACKET_CZ_ENTER packet;
		packet.PacketType = HEADER_CZ_ENTER;
		packet.clientTime = timeGetTime();
		packet.AuthCode = g_session.m_authCode;
		packet.AID = g_session.GetAid();
		packet.GID = g_session.GetGid();
		packet.Sex = g_session.CSession::GetSex();
		g_connection.CRagConnection::SendPacket(g_connection.CRagConnection::GetPacketSize(HEADER_CZ_ENTER), (const char *)&packet);

		g_connection.CConnection::SetBlock(1);
		wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_WAITWND);
		((UIWaitWnd *)wnd)->UIWaitWnd::SetMsg(MsgStr(MSI_WAITING_RESPONSE_FROM_SERVER), 16, 1);
	}
	return;
	default:
	{
	}
	return;
	};
}


hook_method<void (CLoginMode::*)(void)> CLoginMode::_PollNetworkStatus(SAKEXE, "CLoginMode::PollNetworkStatus");
void CLoginMode::PollNetworkStatus(void) // line 553
{
	return (this->*_PollNetworkStatus)();

	if( !g_connection.CConnection::Poll() )
		g_modeMgr.CModeMgr::GetCurMode()->SendMsg(MM_SOCKETERROR, 0, 0, 0);

	if( g_mustPumpOutReceiveQueue == TRUE )
	{
		int aid;
		if( g_connection.CConnection::Recv((char*)&aid, sizeof(aid), true) )
			g_mustPumpOutReceiveQueue = FALSE;

		return;
	}

	char buf[2048];
	while( g_connection.CRagConnection::RecvPacket(buf) )
	{
		switch( g_connection.CRagConnection::GetPacketType(buf) )
		{
		case HEADER_AC_ACCEPT_LOGIN     : this->CLoginMode::Ac_Accept_Login(buf);      break;
		case HEADER_AC_REFUSE_LOGIN     : this->CLoginMode::Ac_Refuse_Login(buf);      break;
		case HEADER_HC_ACCEPT_ENTER     : this->CLoginMode::Hc_Accept_Enter(buf);      break;
		case HEADER_HC_REFUSE_ENTER     : this->CLoginMode::Hc_Refuse_Enter(buf);      break;
		case HEADER_HC_ACCEPT_MAKECHAR  : this->CLoginMode::Hc_Accept_Makechar(buf);   break;
		case HEADER_HC_REFUSE_MAKECHAR  : this->CLoginMode::Hc_Refuse_Makechar(buf);   break;
		case HEADER_HC_ACCEPT_DELETECHAR: this->CLoginMode::Hc_Accept_Deletechar(buf); break;
		case HEADER_HC_REFUSE_DELETECHAR: this->CLoginMode::Hc_Refuse_Deletechar(buf); break;
		case HEADER_HC_NOTIFY_ZONESVR   : this->CLoginMode::Hc_Notify_Zonesvr(buf);    break;
		case HEADER_ZC_ACCEPT_ENTER     : this->CLoginMode::Zc_Accept_Enter(buf);      return;
		case HEADER_ZC_REFUSE_ENTER     : this->CLoginMode::Zc_Refuse_Enter(buf);      break;
		case HEADER_SC_NOTIFY_BAN       : this->CLoginMode::Sc_Notify_Ban(buf);        break;
		case HEADER_PING                :                                              break;
		case HEADER_SC_BILLING_INFO     : this->CLoginMode::Sc_Billing_Info(buf);      break;
		case HEADER_AC_ASK_PNGAMEROOM   : this->CLoginMode::Ac_Ask_Pngameroom(buf);    break;
		case HEADER_SC_ACK_ENCRYPTION   : this->CLoginMode::Sc_Ack_Encryption(buf);    break;
		case HEADER_AC_ACK_HASH         : this->CLoginMode::Ac_Ack_Hash(buf);          break;
		case HEADER_AC_NOTIFY_ERROR     : this->CLoginMode::Ac_Notify_Error(buf);      break;
		default:
			g_connection.CConnection::ResetQueue();
			break;
		};
	}
}


hook_method<void (CLoginMode::*)(int state)> CLoginMode::_OnProcessState(SAKEXE, "CLoginMode::OnProcessState");
void CLoginMode::OnProcessState(int state) // line 475
{
	return (this->*_OnProcessState)(state);

	switch( state )
	{
	case 4:
		if( timeGetTime() <= m_subModeStartTime + 15000 )
			return;
	break;
	case 5:
		if( timeGetTime() <= m_subModeStartTime + 15000 )
			return;
	break;
	case 12:
		if( timeGetTime() <= m_subModeStartTime + 15000 )
			return;
	break;
	default:
		return;
	break;
	}

	g_connection.CConnection::Disconnect();

	if( g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_SERVER_CONNECTION_FAILED), 1, 1, 1, 0) != 178 )
	{
		g_mustPumpOutReceiveQueue = FALSE;
		m_nextSubMode = 3;
	}
}


hook_method<void (CLoginMode::*)(int state)> CLoginMode::_OnRenderState(SAKEXE, "CLoginMode::OnRenderState");
void CLoginMode::OnRenderState(int state) // line 527
{
	return (this->*_OnRenderState)(state);

	;
}


hook_method<void (CLoginMode::*)(void)> CLoginMode::_OpenSettlePage(SAKEXE, "CLoginMode::OpenSettlePage");
void CLoginMode::OpenSettlePage(void) // line 532
{
	return (this->*_OpenSettlePage)();

	switch( g_serviceType )
	{
	case ServiceChina:
		ShellExecuteA(g_hMainWnd, "open", "http://ro.gameflier.com.cn/regist/registgame.html", 0, 0, 1);
	break;
	case ServiceTaiwan:
		ShellExecuteA(g_hMainWnd, "open", "http://billing.gameflier.com/step_by_step.htm", 0, 0, 1);
	break;
	default:
		ShellExecuteA(g_hMainWnd, "open", MsgStr(MSI_SETTLE_WEB_URL), 0, 0, 1);
	break;
	case ServiceAmerica:
	case ServiceJapan:
		return;
	break;
	}
}


hook_method<void (CLoginMode::*)(void)> CLoginMode::_CheckPingTime(SAKEXE, "CLoginMode::CheckPingTime");
void CLoginMode::CheckPingTime(void) // line 117
{
	return (this->*_CheckPingTime)();

	if( m_subMode != 7 && m_subMode != 8 && m_subMode != 11 )
		return;

	if( timeGetTime() <= m_syncRequestTime )
		return; // not yet

	Trace("CharServer Ping !");
	m_syncRequestTime = timeGetTime() + 12000;

	PACKET_PING p;
	p.PacketType = HEADER_PING;
	p.AID = g_session.CSession::GetAid();
	g_connection.CRagConnection::SendPacket(g_connection.CRagConnection::GetPacketSize(HEADER_PING), (const char*)&p);
}


hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Ac_Accept_Login(SAKEXE, "CLoginMode::Ac_Accept_Login");
void CLoginMode::Ac_Accept_Login(const char* buf) // line 900
{
	return (this->*_Ac_Accept_Login)(buf);

	PACKET_AC_ACCEPT_LOGIN& packet = *(PACKET_AC_ACCEPT_LOGIN*)buf;
	g_session.m_authCode = packet.AuthCode;
	g_session.SetAid(packet.AID);
	g_session.m_userLevel = packet.userLevel;
	g_session.m_lastLoginIP = packet.lastLoginIP;
	memcpy(g_session.m_lastLoginTime, packet.lastLoginTime, sizeof(packet.lastLoginTime));
	g_session.m_lastLoginTime[26] = '\0';
	g_session.CSession::SetSex(packet.Sex);
	g_session.CSession::SetTextType(g_session.m_isShowNameTypeOld, g_session.m_isShowNameTypeOld);
	m_numServer = (packet.PacketLength - sizeof(packet)) / sizeof(SERVER_ADDR);
	memcpy(m_serverInfo, buf + sizeof(packet), m_numServer * sizeof(SERVER_ADDR));

	g_connection.CConnection::Disconnect();

	if( g_sendUDPPacket )
	{
		SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);
		if( s != INVALID_SOCKET )
		{
			hostent* he = gethostbyname("roconnect.dnip.net");
			if( he != NULL )
			{
				sockaddr_in servAddr;
				servAddr.sin_family = AF_INET;
				servAddr.sin_addr.s_addr = *(unsigned long *)*he->h_addr_list;
				servAddr.sin_port = htons(6000);
				sendto(s, buf, packet.PacketLength, 0, (const struct sockaddr *)&servAddr, sizeof(servAddr));
			}

			closesocket(s);
		}
	}

	m_nextSubMode = 6;
}


hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Ac_Refuse_Login(SAKEXE, "CLoginMode::Ac_Refuse_Login");
void CLoginMode::Ac_Refuse_Login(const char* buf) // line 946
{
	return (this->*_Ac_Refuse_Login)(buf);

	PACKET_AC_REFUSE_LOGIN& packet = *(PACKET_AC_REFUSE_LOGIN*)buf;

	g_connection.CConnection::Disconnect();

	switch( packet.ErrorCode )
	{
	case REFUSE_INVALID_ID:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_INCORRECT_USERID), 0, 1, 0, 0);
	break;
	case REFUSE_INVALID_PASSWD:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_INCORRECT_LOGIN_PASSWORD), 0, 1, 0, 0);
	break;
	case REFUSE_ID_EXPIRED:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_ID_EXPIRED), 0, 1, 0, 0);
	break;
	case REFUSE_NOT_CONFIRMED:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_ID_EMAIL_CONFIRM_NEEDED), 0, 1, 0, 0);
	break;
	case REFUSE_INVALID_VERSION:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_INVALID_VERSION), 0, 1, 0, 0);
		this->SendMsg(MM_QUIT, 0, 0, 0);
	break;
	case REFUSE_DELETED_ACCOUNT:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_DELETED_ACCOUNT), 0, 1, 0, 0);
		this->SendMsg(MM_QUIT, 0, 0, 0);
	break;
	case REFUSE_BLOCK_TEMPORARY:
	{
		char refuseString[256];
		packet.blockDate[sizeof(packet.blockDate)-1] = '\0';
		sprintf(refuseString, MsgStr(MSI_LOGIN_REFUSE_BLOCKED_UNTIL), packet.blockDate);
		g_windowMgr.UIWindowMgr::ErrorMsg(refuseString, 0, 1, 0, 0);
	}
	break;
	case REFUSE_BILLING_NOT_READY:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_ACCOUNT_BUSY), 0, 1, 0, 0);
	break;
	case REFUSE_NONSAKRAY_ID_BLOCKED:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_REFUSE_NONSAKRAY_ID_BLOCKED), 0, 1, 0, 0);
	break;
	case REFUSE_BAN_BY_DBA:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_REFUSE_BAN_BY_DBA), 0, 1, 0, 0);
	break;
	case REFUSE_EMAIL_NOT_CONFIRMED:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_REFUSE_EMAIL_NOT_CONFIRMED), 0, 1, 0, 0);
	break;
	case REFUSE_BAN_BY_GM:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_REFUSE_BAN_BY_GM), 0, 1, 0, 0);
	break;
	case REFUSE_TEMP_BAN_FOR_DBWORK:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_REFUSE_TEMP_BAN_FOR_DBWORK), 0, 1, 0, 0);
	break;
	case REFUSE_SELF_LOCK:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_REFUSE_SELF_LOCK), 0, 1, 0, 0);
	break;
	case REFUSE_NOT_PERMITTED_GROUP:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_REFUSE_NOT_PERMITTED_GROUP), 0, 1, 0, 0);
	break;
	case REFUSE_WAIT_FOR_SAKRAY_ACTIVE:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_REFUSE_WAIT_FOR_SAKRAY_ACTIVE), 0, 1, 0, 0);
	break;
	default:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_ACCESS_DENIED), 0, 1, 0, 0);
	break;
	}

	g_mustPumpOutReceiveQueue = FALSE;
	m_nextSubMode = 3;
};


hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Hc_Accept_Enter(SAKEXE, "CLoginMode::Hc_Accept_Enter");
void CLoginMode::Hc_Accept_Enter(const char* buf) // line 1013
{
	return (this->*_Hc_Accept_Enter)(buf);

	PACKET_HC_ACCEPT_ENTER& packet = *(PACKET_HC_ACCEPT_ENTER*)buf;

	m_numChar = (packet.PacketLength - sizeof(packet)) / sizeof(CHARACTER_INFO);
	memcpy(m_charInfo, packet.Chars, m_numChar * sizeof(CHARACTER_INFO));

	m_nextSubMode = 7;
};


hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Hc_Refuse_Enter(SAKEXE, "CLoginMode::Hc_Refuse_Enter");
void CLoginMode::Hc_Refuse_Enter(const char* buf) // line 1058
{
	return (this->*_Hc_Refuse_Enter)(buf);

	PACKET_HC_REFUSE_ENTER& packet = *(PACKET_HC_REFUSE_ENTER*)buf;

	g_connection.CConnection::Disconnect();

	if( packet.ErrorCode == 1 )
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_ID_MISMATCH), 0, 1, 1, 0);
	else
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_ACCESS_DENIED), 0, 1, 0, 0);

	g_mustPumpOutReceiveQueue = FALSE;
	m_nextSubMode = 3;
};


hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Hc_Accept_Makechar(SAKEXE, "CLoginMode::Hc_Accept_Makechar");
void CLoginMode::Hc_Accept_Makechar(const char* buf) // line 1078
{
	return (this->*_Hc_Accept_Makechar)(buf);

	PACKET_HC_ACCEPT_MAKECHAR& packet = *(PACKET_HC_ACCEPT_MAKECHAR*)buf;

	memcpy(&g_charInfo, &packet.charinfo, sizeof(g_charInfo));
	memcpy(&m_charInfo[m_numChar], &packet.charinfo, sizeof(m_charInfo[m_numChar]));
	m_numChar++;

	m_nextSubMode = 7;
};


hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Hc_Refuse_Makechar(SAKEXE, "CLoginMode::Hc_Refuse_Makechar");
void CLoginMode::Hc_Refuse_Makechar(const char* buf) // line 1090
{
	return (this->*_Hc_Refuse_Makechar)(buf);

	PACKET_HC_REFUSE_MAKECHAR& packet = *(PACKET_HC_REFUSE_MAKECHAR*)buf;

	MSGSTRINGID id = ( packet.ErrorCode == 0 ) ? MSI_CHARACTER_NAME_ALREADY_EXISTS
	               : ( packet.ErrorCode == 1 ) ? MSI_LIMIT_AGE
	               :                             MSI_CHARACTER_CREATION_DENIED;

	g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(id), 0, 1, 0, 0);

	m_nextSubMode = 7;
};


hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Hc_Accept_Deletechar(SAKEXE, "CLoginMode::Hc_Accept_Deletechar");
void CLoginMode::Hc_Accept_Deletechar(const char* buf) // line 1109
{
	return (this->*_Hc_Accept_Deletechar)(buf);

	PACKET_HC_ACCEPT_DELETECHAR& packet = *(PACKET_HC_ACCEPT_DELETECHAR*)buf;

	CHARACTER_INFO tmpInfo[9];
	int j = 0;

	for( int i = 0; i < m_numChar; ++i )
	{
		if( m_charInfo[i].CharNum != g_charInfo.CharNum )
		{
			memcpy(&tmpInfo[j], &m_charInfo[i], sizeof(CHARACTER_INFO));
			++j;
		}
	}

	m_numChar--;
	memcpy(m_charInfo, tmpInfo, m_numChar * sizeof(CHARACTER_INFO));

	m_nextSubMode = 7;
};


hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Hc_Refuse_Deletechar(SAKEXE, "CLoginMode::Hc_Refuse_Deletechar");
void CLoginMode::Hc_Refuse_Deletechar(const char* buf) // line 1125
{
	return (this->*_Hc_Refuse_Deletechar)(buf);

	PACKET_HC_REFUSE_DELETECHAR& packet = *(PACKET_HC_REFUSE_DELETECHAR*)buf;

	MSGSTRINGID id = ( packet.ErrorCode != 0         ) ? MSI_CANNOT_DELETE_CHARACTER
	               : ( g_serviceType != ServiceKorea ) ? MSI_CANNOT_DELETE_CHARACTER_EMAIL
	               :                                     MSI_CANNOT_DELETE_CHARACTER_PEOPLE_REG_NUMBER;

	g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(id), 0, 1, 0, 0);

	m_nextSubMode = 7;
};


hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Hc_Notify_Zonesvr(SAKEXE, "CLoginMode::Hc_Notify_Zonesvr");
void CLoginMode::Hc_Notify_Zonesvr(const char* buf) // line 1142
{
	return (this->*_Hc_Notify_Zonesvr)(buf);

	PACKET_HC_NOTIFY_ZONESVR& packet = *(PACKET_HC_NOTIFY_ZONESVR*)buf;

	g_session.CSession::SetGid(packet.GID);

	char mapName[16+1];
	mapName[sizeof(mapName)-1] = '\0';
	memcpy(mapName, packet.mapName, sizeof(packet.mapName));

	mystd::string curMap = mapName;
	curMap.resize(curMap.size() - 4);
	strcpy(g_session.m_curMap, curMap.c_str());

	strcpy(g_zoneServerAddr.ip, inet_ntoa(*(in_addr*)&packet.addr.ip));
	g_zoneServerAddr.port = packet.addr.port;

	g_connection.CConnection::Disconnect();

	m_nextSubMode = 12;
};


hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Zc_Accept_Enter(SAKEXE, "CLoginMode::Zc_Accept_Enter");
void CLoginMode::Zc_Accept_Enter(const char* buf) // line 1168
{
	return (this->*_Zc_Accept_Enter)(buf);

	PACKET_ZC_ACCEPT_ENTER& packet = *(PACKET_ZC_ACCEPT_ENTER*)buf;

	g_session.CSession::SetServerTime(packet.startTime);

	int x, y, dir;
	DecodePosDir(packet.PosDir, x, y, dir);
	g_session.CSession::SetPlayerPosDir(x, y, dir);

	char curMap[35];
	sprintf(curMap, "%s.rsw", g_session.m_curMap);
	g_modeMgr.CModeMgr::Switch(MT_GAME, curMap);

	UIWaitWnd* wnd = (UIWaitWnd *) g_windowMgr.UIWindowMgr::MakeWindow(WID_WAITWND);
	wnd->UIWaitWnd::SetMsg(MsgStr(MSI_PLEASE_BE_PATIENT), 17, 1);

	g_connection.CConnection::SetBlock(0);

	if( g_pingLog )
	{
		FILE* fp = fopen("PingLog.txt", "at");
		if( fp != NULL )
		{
			time_t currentTime;
			time(&currentTime);

			fprintf(fp, "\n");
			fprintf(fp, "server:%s\n", g_session.m_selectedServerName.c_str());
			fprintf(fp, "ip:%s\n", g_zoneServerAddr.ip);
			fprintf(fp, "map:%s.gat\n", g_session.m_curMap);
			fprintf(fp, "time:%s\n\n", ctime(&currentTime));
			fclose(fp);
		}

		g_pingLogList.clear();
		g_pingLogStart = 0;
	}
};


hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Zc_Refuse_Enter(SAKEXE, "CLoginMode::Zc_Refuse_Enter");
void CLoginMode::Zc_Refuse_Enter(const char* buf) // line 1202
{
	return (this->*_Zc_Refuse_Enter)(buf);

	PACKET_ZC_REFUSE_ENTER& packet = *(PACKET_ZC_REFUSE_ENTER*)buf;

	g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_ACCESS_DENIED), 0, 1, 0, 0);
	g_connection.CConnection::Disconnect();

	g_mustPumpOutReceiveQueue = FALSE;
	m_nextSubMode = 3;
};


hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Sc_Notify_Ban(SAKEXE, "CLoginMode::Sc_Notify_Ban");
void CLoginMode::Sc_Notify_Ban(const char* buf) // line 1212
{
	return (this->*_Sc_Notify_Ban)(buf);

	PACKET_SC_NOTIFY_BAN& packet = *(PACKET_SC_NOTIFY_BAN*)buf;

	g_connection.CConnection::Disconnect();

	switch( packet.ErrorCode )
	{
	case BAN_SERVER_SHUTDOWN:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_SERVER_OFF), 0, 1, 1, 0);
	break;
	case BAN_ANOTHER_LOGIN:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_DOUBLE_LOGIN_PROHIBITED), 0, 1, 1, 0);
	break;
	case BAN_DETECTED_SPEEDHACK:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_SPEEDHACK), 0, 1, 1, 0);
	break;
	case BAN_PC_OVERFLOW:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_PC_OVERFLOW), 0, 1, 1, 0);
	break;
	case BAN_UNDER_AGE:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_UNDER_AGE), 0, 1, 1, 0);
	break;
	case BAN_NOT_SETTLED:
		if( g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_NOT_SETTLED), 2, 1, 1, 0) == 97 )
		{
			g_modeMgr.CModeMgr::Quit();
			this->CLoginMode::OpenSettlePage(); //inlined
		}
	break;
	case BAN_ACCOUNT_BUSY:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_ACCOUNT_BUSY), 0, 1, 1, 0);
	break;
	case BAN_INFORMATION_REMAINED:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_INFORMATION_REMAINED), 0, 1, 1, 0);
	break;
	case BAN_IP_OVERFLOW:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_BAN_IP_OVERFLOW), 0, 1, 1, 0);
	break;
	case BAN_PAY_OUT:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_BAN_PAY_OUT), 0, 1, 1, 0);
	break;
	case BAN_PAY_SUSPEND:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_BAN_PAY_SUSPEND), 0, 1, 1, 0);
	break;
	case BAN_PAY_CHANGE:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_BAN_PAY_CHANGE), 0, 1, 1, 0);
	break;
	case BAN_PAY_WRONGIP:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_BAN_PAY_WRONGIP), 0, 1, 1, 0);
	break;
	case BAN_PAY_PNGAMEROOM:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_BAN_PAY_PNGAMEROOM), 0, 1, 1, 0);
	break;
	case BAN_JAPAN_REFUSE1:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_BAN_JAPAN_REFUSE1), 0, 1, 1, 0);
	break;
	case BAN_JAPAN_REFUSE2:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_BAN_JAPAN_REFUSE2), 0, 1, 1, 0);
	break;
	case BAN_INFORMATION_REMAINED_ANOTHER_ACCOUNT:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_BAN_INFORMATION_REMAINED_ANOTHER_ACCOUNT), 0, 1, 1, 0);
	break;
	default:
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_BANNED), 0, 1, 1, 0);
	break;
	}

	g_mustPumpOutReceiveQueue = FALSE;
	m_nextSubMode = 3;
};


hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Sc_Billing_Info(SAKEXE, "CLoginMode::Sc_Billing_Info");
void CLoginMode::Sc_Billing_Info(const char* buf) // line 1286
{
	return (this->*_Sc_Billing_Info)(buf);

	PACKET_SC_BILLING_INFO& packet = *(PACKET_SC_BILLING_INFO*)buf;

	char buffer[256];
	int val1 = (int)packet.dwAmountRemain; //Prepaid voucher (minutes)
	int val2 = (int)packet.dwQuantityRemain; //Time limit voucher (minutes)

	if( val1 == -2 && val2 == -2 )
	{
		sprintf(buffer, "%s\n", MsgStr(MSI_BILLING_FREE_USER));
	}
	else
	if( val1 == -1 && val2 == -1 )
	{
		sprintf(buffer, "%s\n", MsgStr(MSI_BILLING_INTERNET_CAFE));
	}
	else
	if( val1 != 0 && val2 != 0 )
	{
		int days1 = val1 / 60 / 24;
		int hours1 = val1 / 60 % 24;
		int minutes1 = val1 % 60;
		int hours2 = val2 / 60;
		int minutes2 = val2 % 60;
		sprintf(buffer, MsgStr(MSI_BILLING_BOTH), days1, hours1, minutes1, hours2, minutes2);
	}
	else
	if( val1 != 0 )
	{
		int days = val1 / 60 / 24;
		int hours = val1 / 60 % 24;
		int minutes = val1 % 60;
		sprintf(&buffer[0], "%s\n", MsgStr(MSI_BILLING_100));
		sprintf(&buffer[strlen(buffer)], MsgStr(MSI_BILLING_DAY_HOUR_MINUTES), days, hours, minutes);
	}
	else
	if( val2 != 0 )
	{
		int hours = val2 / 60;
		int minutes = val2 % 60;
		sprintf(&buffer[0], "%s\n", MsgStr(MSI_BILLING_800));
		sprintf(&buffer[strlen(buffer)], MsgStr(MSI_BILLING_HOUR_MINUTES), hours, minutes);
	}
	else
	{
		sprintf(buffer, "\n");
	}

	m_subModeStartTime = timeGetTime() + 90000;
	g_windowMgr.UIWindowMgr::ErrorMsg(buffer, 0, 1, 1, 0);
};


hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Ac_Ask_Pngameroom(SAKEXE, "CLoginMode::Ac_Ask_Pngameroom");
void CLoginMode::Ac_Ask_Pngameroom(const char* buf) // line 1315
{
	return (this->*_Ac_Ask_Pngameroom)(buf);

	PACKET_AC_ASK_PNGAMEROOM& packet = *(PACKET_AC_ASK_PNGAMEROOM*)buf;

	if( g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_ASK_PNGAMEROOM), 2, 1, 0, 0) == 97 )
	{
		PACKET_CA_REPLY_PNGAMEROOM p;
		p.PacketType = HEADER_CA_REPLY_PNGAMEROOM;
		p.Permission = 1;
		g_connection.CRagConnection::SendPacket(g_connection.CRagConnection::GetPacketSize(HEADER_CA_REPLY_PNGAMEROOM), (const char *)&p);
	}
	else
	{
		g_connection.CConnection::Disconnect();
		g_mustPumpOutReceiveQueue = FALSE;
		m_nextSubMode = 3;
	}
};


hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Sc_Ack_Encryption(SAKEXE, "CLoginMode::Sc_Ack_Encryption");
void CLoginMode::Sc_Ack_Encryption(const char* buf) // line 1337
{
	return (this->*_Sc_Ack_Encryption)(buf);

	ErrorMsg("No Packet Encryption !!!");
};


hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Ac_Ack_Hash(SAKEXE, "CLoginMode::Ac_Ack_Hash");
void CLoginMode::Ac_Ack_Hash(const char* buf) // line 1341
{
	return (this->*_Ac_Ack_Hash)(buf);

	PACKET_AC_ACK_HASH& packet = *(PACKET_AC_ACK_HASH*)buf;

	MD5 hash;
	hash.MD5::init();

	if( g_passwordEncrypt2 )
	{
		hash.MD5::append((unsigned char*)m_userPassword, strlen(m_userPassword));
		hash.MD5::append((unsigned char*)packet.Hash, packet.PacketLength - sizeof(packet));
	}
	else
	{
		hash.MD5::append((unsigned char*)packet.Hash, packet.PacketLength - sizeof(packet));
		hash.MD5::append((unsigned char*)m_userPassword, strlen(m_userPassword));
	}

	PACKET_CA_LOGIN2 p;
	p.PacketType = HEADER_CA_LOGIN2;
	p.Version = g_version;
	memcpy(p.ID, m_userId, sizeof(p.ID));
	hash.MD5::finish(p.PasswdMD5);
	p.clienttype = GetAccountType();
	g_connection.CRagConnection::SendPacket(g_connection.CRagConnection::GetPacketSize(p.PacketType), (const char *)&p);

	UIWaitWnd* wnd = (UIWaitWnd*)g_windowMgr.UIWindowMgr::MakeWindow(WID_WAITWND);
	wnd->UIWaitWnd::SetMsg(MsgStr(MSI_WAITING_RESPONSE_FROM_SERVER), 16, 1);
};


hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Ac_Notify_Error(SAKEXE, "CLoginMode::Ac_Notify_Error");
void CLoginMode::Ac_Notify_Error(const char* buf) // line 1370
{
	return (this->*_Ac_Notify_Error)(buf);

	PACKET_AC_NOTIFY_ERROR& packet = *(PACKET_AC_NOTIFY_ERROR*)buf;
	mystd::string error = packet.Text;
	g_windowMgr.UIWindowMgr::ErrorMsg(error.c_str(), 0, 1, 1, 0);
	g_mustPumpOutReceiveQueue = FALSE;
	m_nextSubMode = 3;
};


hook_method<bool (CLoginMode::*)(void)> CLoginMode::_InitAccountInfo(SAKEXE, "CLoginMode::InitAccountInfo");
bool CLoginMode::InitAccountInfo(void) // line 1383
{
	return (this->*_InitAccountInfo)();

	if( m_accountInfo.size() == 0 )
	{
		XMLElement* info = GetClientInfo();
		if( info == NULL )
			return false;

		XMLElement* conn = info->XMLElement::FindChild("connection");
		if( conn == NULL )
			return false;

		while( conn != NULL )
		{
			accountInfo info;

			XMLElement* disp = conn->XMLElement::FindChild("display");
			if( disp != NULL )
				info.display = disp->XMLElement::GetContents();

			XMLElement* desc = conn->XMLElement::FindChild("desc");
			if( desc != NULL )
				info.desc = desc->XMLElement::GetContents();

			m_accountInfo.push_back(info);

			conn = conn->XMLElement::FindNext("connection");
		}
	}

	return ( g_hideAccountList == false );
}


hook_func<int (__cdecl *)(void)> _GetAccountType(SAKEXE, "GetAccountType");
int __cdecl GetAccountType(void) // line 1411
{
	return (_GetAccountType)();

	if( g_serverType == ServerSakray )
	{
		switch( g_serviceType )
		{
		case ServiceAmerica   : return CLIENTTYPE_ENGLISH_SAKRAY;
		case ServiceJapan     : return CLIENTTYPE_JAPAN_SAKRAY;
		case ServiceChina     : return CLIENTTYPE_LOCAL;
		case ServiceTaiwan    : return CLIENTTYPE_TAIWAN;
		case ServiceThai      : return CLIENTTYPE_THAI_SAKRAY;
		case ServiceIndonesia : return CLIENTTYPE_INDONESIA_SAKRAY;
		case ServicePhilippine: return CLIENTTYPE_PHILIPPINE_SAKRAY;
		case ServiceMalaysia  : return CLIENTTYPE_MALAYSIA;
		case ServiceSingapore : return CLIENTTYPE_SINGAPORE;
		case ServiceGermany   : return CLIENTTYPE_GERMANY;
		default               : return CLIENTTYPE_SAKRAY;
		}
	}
	else
	{
		switch( g_serviceType )
		{
		case ServiceAmerica   : return CLIENTTYPE_ENGLISH;
		case ServiceJapan     : return CLIENTTYPE_JAPAN;
		case ServiceChina     : return CLIENTTYPE_LOCAL;
		case ServiceTaiwan    : return CLIENTTYPE_TAIWAN;
		case ServiceThai      : return CLIENTTYPE_THAI;
		case ServiceIndonesia : return CLIENTTYPE_INDONESIA;
		case ServicePhilippine: return CLIENTTYPE_PHILIPPINE;
		case ServiceMalaysia  : return CLIENTTYPE_MALAYSIA;
		case ServiceSingapore : return CLIENTTYPE_SINGAPORE;
		case ServiceGermany   : return CLIENTTYPE_GERMANY;
		default               : return CLIENTTYPE_KOREAN;
		}
	}
}
