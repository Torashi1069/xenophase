#include "MsgStrings.h"
#include "Session.h"
#include "3dLib/Device.h"
#include "3dLib/Texture.h"
#include "Resource/Bitmap.h"
#include "Resource/Wave.h"
#include "Window/UISys.h"
#include "Window/UIWindow.h"
#include "Window/UIWindowMgr.h"


UIWindowMgr& g_windowMgr = VTOR<UIWindowMgr>(SymDB::Find("g_windowMgr"));


hook_func<void (UIWindowMgr::*)(void)> UIWindowMgr::_DestroyDC("UIWindowMgr::DestroyDC");
void UIWindowMgr::DestroyDC(void)
{
	return (this->*_DestroyDC)();

	//TODO
}


void UIWindowMgr::AddWindow(UIWindow* window)
{
	m_children.push_back(window);
}


void UIWindowMgr::AddWindowFront(UIWindow* window)
{
	m_children.push_front(window);
}


hook_func<int (UIWindowMgr::*)(void)> UIWindowMgr::_ProcessInput("UIWindowMgr::ProcessInput");
int UIWindowMgr::ProcessInput(void)
{
	return (this->*_ProcessInput)();

	//TODO
}


hook_func<void (UIWindowMgr::*)(void)> UIWindowMgr::_OnProcess("UIWindowMgr::OnProcess");
void UIWindowMgr::OnProcess(void)
{
	return (this->*_OnProcess)();

	//TODO
}


hook_func<bool (UIWindowMgr::*)(unsigned long virtualKey, int a2, int a3)> UIWindowMgr::_ProcessPushButton("UIWindowMgr::ProcessPushButton");
bool UIWindowMgr::ProcessPushButton(unsigned long virtualKey, int a2, int a3)
{
	return (this->*_ProcessPushButton)(virtualKey, a2, a3);

	//TODO
}


hook_func<UIFrameWnd* (UIWindowMgr::*)(WINDOWID windowId)> UIWindowMgr::_MakeWindow("UIWindowMgr::MakeWindow");
UIFrameWnd* UIWindowMgr::MakeWindow(WINDOWID windowId)
{
	return (this->*_MakeWindow)(windowId);

	//TODO
}


hook_func<UIWindow* (UIWindowMgr::*)(WINDOWID windowId)> UIWindowMgr::_QueryWindow("UIWindowMgr::QueryWindow");
UIWindow* UIWindowMgr::QueryWindow(WINDOWID windowId)
{
	return (this->*_QueryWindow)(windowId);

	//TODO
}


hook_func<bool (UIWindowMgr::*)(WINDOWID windowId)> UIWindowMgr::_DeleteWindow("UIWindowMgr::DeleteWindow");
bool UIWindowMgr::DeleteWindow(WINDOWID windowId)
{
	return (this->*_DeleteWindow)(windowId);

	//TODO
}


hook_func<bool (UIWindowMgr::*)(WINDOWID windowId, int show)> UIWindowMgr::_ShowWindow("UIWindowMgr::ShowWindow");
bool UIWindowMgr::ShowWindow(WINDOWID windowId, int show)
{
	return (this->*_ShowWindow)(windowId, show);

	//TODO
}


//hook_func<bool (UIWindowMgr::*)(void)> UIWindowMgr::_IsModalStatus("UIWindowMgr::IsModalStatus");
bool UIWindowMgr::IsModalStatus(void)
{
//	return (this->*_IsModalStatus)();

	return ( m_modalWindow != NULL );
}


//hook_func<UIBasicInfoWnd* (UIWindowMgr::*)(void)> UIWindowMgr::_GetBasicInfoWnd("UIWindowMgr::GetBasicInfoWnd");
UIBasicInfoWnd* UIWindowMgr::GetBasicInfoWnd(void)
{
//	return (this->*_GetBasicInfoWnd)();

	return m_basicInfoWnd;
}


hook_func<void (UIWindowMgr::*)(int cx, int cy)> UIWindowMgr::_SetSize("UIWindowMgr::SetSize");
void UIWindowMgr::SetSize(int cx, int cy)
{
	return (this->*_SetSize)(cx, cy);

	//TODO
}


hook_func<void (UIWindowMgr::*)(void)> UIWindowMgr::_InitUIRectInfoFromReg("UIWindowMgr::InitUIRectInfoFromReg");
void UIWindowMgr::InitUIRectInfoFromReg(void)
{
	return (this->*_InitUIRectInfoFromReg)();

	//TODO
}


hook_func<void (UIWindowMgr::*)(void)> UIWindowMgr::_WriteUIRectInfoToReg("UIWindowMgr::WriteUIRectInfoToReg");
void UIWindowMgr::WriteUIRectInfoToReg(void)
{
	return (this->*_WriteUIRectInfoToReg)();

	//TODO
}


hook_func<void (UIWindowMgr::*)(void)> UIWindowMgr::_RemoveAllWindows("UIWindowMgr::RemoveAllWindows");
void UIWindowMgr::RemoveAllWindows(void)
{
	return (this->*_RemoveAllWindows)();

	//TODO
}


hook_func<void (UIWindowMgr::*)(void)> UIWindowMgr::_RemoveAllWindowsExceptChatWnd("UIWindowMgr::RemoveAllWindowsExceptChatWnd");
void UIWindowMgr::RemoveAllWindowsExceptChatWnd(void)
{
	return (this->*_RemoveAllWindowsExceptChatWnd)();

	//TODO
}


hook_func<void (UIWindowMgr::*)(UIWindow* wnd)> UIWindowMgr::_RemoveFromNameWaitingWindowList("UIWindowMgr::RemoveFromNameWaitingWindowList");
void UIWindowMgr::RemoveFromNameWaitingWindowList(UIWindow* wnd)
{
	return (this->*_RemoveFromNameWaitingWindowList)(wnd);

	//TODO
}


hook_func<void (UIWindowMgr::*)(CBitmapRes* bitmap)> UIWindowMgr::_SetWallpaper("UIWindowMgr::SetWallpaper");
void UIWindowMgr::SetWallpaper(CBitmapRes* bitmap)
{
	return (this->*_SetWallpaper)(bitmap);

	if( bitmap != NULL )
	{
		if( m_wallpaperSurface == NULL )
			m_wallpaperSurface = g_3dDevice.C3dDevice::CreateWallPaper(bitmap->m_width, bitmap->m_height);

		if( m_wallpaperSurface != NULL )
			m_wallpaperSurface->Update(0, 0, bitmap->m_width, bitmap->m_height, bitmap->m_data, 0, 0);
	}
	else
	{
		if( m_wallpaperSurface != NULL )
		{
			delete m_wallpaperSurface;
			m_wallpaperSurface = NULL;
		}
	}
}


hook_func<int (UIWindowMgr::*)(const char* msg, int type, int isDefYes, int changeMsg, unsigned int autoReturnTime, const char* a7)> UIWindowMgr::_ErrorMsg("UIWindowMgr::ErrorMsg");
int UIWindowMgr::ErrorMsg(const char* msg, int type, int isDefYes, int changeMsg, unsigned int autoReturnTime, const char* a7)
{
	return (this->*_ErrorMsg)(msg, type, isDefYes, changeMsg, autoReturnTime, a7);
}


hook_func<int (UIWindowMgr::*)(int message, int val1, int val2, int val3, int val4)> UIWindowMgr::_SendMsg("UIWindowMgr::SendMsg");
int UIWindowMgr::SendMsg(int message, int val1, int val2, int val3, int val4)
{
	return (this->*_SendMsg)(message, val1, val2, val3, val4);
}


hook_func<void (UIWindowMgr::*)(UIWindow* wnd)> UIWindowMgr::_PostQuit("UIWindowMgr::PostQuit");
void UIWindowMgr::PostQuit(UIWindow* wnd)
{
	return (this->*_PostQuit)(wnd);
}


hook_val<char*> whisperWindowOpenSound("whisperWindowOpenSound"); // = "..\\..\\BGM\\Msg_NewMsg.wav";
BOOL UIWindowMgr::AddWhisperChatToWhisperWnd(const char* cName, const char* chatMsg, COLORREF color)
{
	BOOL isFriendName = g_session.CSession::IsFriendName(cName);

	BOOL isMadeNewly = FALSE;
	if( g_session.m_isShowWhisperWnd && !isFriendName )
	{
		if( g_session.CSession::IsGuildMember(cName) )
		{
			isMadeNewly = this->UIWindowMgr::SendMsg(UIM_MAKE_WHISPER_WINDOW, (int)cName, (int)"GuildMember", 0, 0);
		}
		else
		if( g_session.CSession::IsCheatName(cName) )
		{
			g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_ID_WARNING), 0x00FFFF, 0, 0);
			isMadeNewly = this->UIWindowMgr::SendMsg(UIM_MAKE_WHISPER_WINDOW, (int)cName, 0, 0, 0);
		}
		else
		if( g_session.CSession::IsCheatGuildName(cName) )
		{
			g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_ID_WARNING_GUILD), 0x00FFFF, 0, 0);
			isMadeNewly = this->UIWindowMgr::SendMsg(UIM_MAKE_WHISPER_WINDOW, (int)cName, 0, 0, 0);
		}
		else
		{
			isMadeNewly = this->UIWindowMgr::SendMsg(UIM_MAKE_WHISPER_WINDOW, (int)cName, 0, 0, 0);
		}
	}
	else
	if( g_session.m_isShowWhisperWnd_Friend && isFriendName )
	{
		isMadeNewly = this->UIWindowMgr::SendMsg(UIM_MAKE_WHISPER_WINDOW, (int)cName, (int)MsgStr(MSI_FRIEND), 0, 0);
	}

	if( isMadeNewly )
	{
		if( g_resMgr().CResMgr::IsExist(whisperWindowOpenSound) )
		{
			PlayWave(whisperWindowOpenSound, 0.0, 0.0, 0.0, 250, 40, 1.0);
		}
		else
		if( g_session.m_isPlayWhisperOpenSound )
		{
			PlayWave("버튼소리.wav", 0.0, 0.0, 0.0, 250, 40, 1.0);
		}
	}

	//FIXME: approximate decompilation
	if( strcmp(cName, g_session.CSession::GetCharName()) == 0 )
		return FALSE; // ignore whisper to self

	if( g_session.m_isShowWhisperWnd && isMadeNewly )
		g_windowMgr.UIWindowMgr::AddWhisperCharName(cName);

	mystd::map<mystd::string,UIWindow*>::iterator it = m_whisperNameWindow.find(cName);
	if( it == m_whisperNameWindow.end() )
		return FALSE; // 1:1 chat window not found

	UIWindow* wnd = it->second;
	wnd->SendMsg(NULL, UM_ADDCHAT, (int)chatMsg, color, 2, 0);

	if( m_roMapWnd == NULL )
	{
		for( mystd::list<UIWindow*>::iterator it = m_children.begin(); it != m_children.end(); ++it )
		{
			if( *it == wnd )
			{// make 'wnd' the topmost window
				m_children.erase(it);
				m_children.push_back(wnd);
				break;
			}
		}
	}

	return TRUE;
}


hook_func<void (UIWindowMgr::*)(const char* whisperCharName)> UIWindowMgr::_AddWhisperCharName("UIWindowMgr::AddWhisperCharName");
void UIWindowMgr::AddWhisperCharName(const char* whisperCharName)
{
	return (this->*_AddWhisperCharName)(whisperCharName);
}


hook_func<void (UIWindowMgr::*)(UIWindow* snapWindow, int& rdx, int& rdy, int mode)> UIWindowMgr::_GetDeltaSnap("UIWindowMgr::GetDeltaSnap");
void UIWindowMgr::GetDeltaSnap(UIWindow* snapWindow, int& rdx, int& rdy, int mode)
{
	return (this->*_GetDeltaSnap)(snapWindow, rdx, rdy, mode);
}


hook_func<void (UIWindowMgr::*)(UIWindow* snapWindow)> UIWindowMgr::_UpdateSnapInfo("UIWindowMgr::UpdateSnapInfo");
void UIWindowMgr::UpdateSnapInfo(UIWindow* snapWindow)
{
	return (this->*_UpdateSnapInfo)(snapWindow);
}


UIWindow* UIWindowMgr::GetCapture()
{
	return m_captureWindow;
}


void UIWindowMgr::SetCapture(UIWindow* window)
{
	m_captureWindow = window;
}


void UIWindowMgr::ReleaseCapture()
{
	m_captureWindow = NULL;
}


bool UIWindowMgr::IsNoEscWindow(WINDOWID windowId)
{
	switch( windowId )
	{
	case WID_141:
	case WID_145:
	{
		UIWindow* wnd = g_windowMgr.UIWindowMgr::QueryWindow(windowId);
		if( wnd != NULL && wnd->UIWindow::IsShow() )
			return false;
		return true;
	}
	case WID_BASICINFOWND:
	case WID_CHATWND:
	case WID_SELECTSERVERWND:
	case WID_LOGINWND:
	case WID_MAKECHARWND:
	case WID_SELECTCHARWND:
	case WID_WAITWND:
	case WID_LOADINGWND:
	case WID_9:
	case WID_STATUSWND:
	case WID_MINIMAPZOOMWND:
	case WID_15:
	case WID_SAYDIALOGWND:
	case WID_CHOOSEWND:
	case WID_MENUWND:
	case WID_20:
	case WID_NOTIFYLEVELUPWND:
	case WID_ITEMPURCHASEWND:
	case WID_COMBOBOXWND:
	case WID_CHATROOMWND:
	case WID_29:
	case WID_EXCHANGEWND:
	case WID_EXCHANGEACCEPTWND:
	case WID_ITEMSTOREWND:
	case WID_MESSENGERGROUPWND:
	case WID_JOINPARTYACCEPTWND:
	case WID_SHORTCUTWND:
	case WID_CHOOSEWARPWND:
	case WID_MERCHANTMIRRORITEMWND:
	case WID_MERCHANTITEMMYSHOPWND:
	case WID_NOTIFYJOBLEVELUPWND:
	case WID_50:
	case WID_NPCEDITDIALOGWND:
	case WID_GUILDINFOMANAGEWND:
	case WID_GUILDMEMBERMANAGEWND:
	case WID_GUILDPOSITIONMANAGEWND:
	case WID_GUILDSKILLWND:
	case WID_GUILDBANISHEDMEMBERWND:
	case WID_GUILDNOTICEWND:
	case WID_GUILDTOTALINFOWND:
	case WID_JOINGUILDACCEPTWND:
	case WID_ITEMIDENTIFYWND:
	case WID_ITEMCOMPOSITIONWND:
	case WID_MAKETARGETLISTWND:
	case WID_80:
	case WID_81:
	case WID_82:
	case WID_SELECTPETEGGWND:
	case WID_91:
	case WID_MAKINGARROWLISTWND:
	case WID_95:
	case WID_SPELLLISTWND:
	case WID_NPCTEXTEDITDIALOGWND:
	case WID_101:
	case WID_COUPLEACCEPTWND:
	case WID_BABYACCEPTWND:
	case WID_ITEMREPAIRWND:
	case WID_JOINFRIENDACCEPTWND:
	case WID_WEAPONREFINEWND:
	case WID_115:
	case WID_116:
	case WID_123:
	case WID_124:
	case WID_127:
	case WID_128:
	case WID_SUBCHATWND_ST:
	case WID_SUBCHATWND_BT:
	case WID_133:
	case WID_136:
	case WID_138:
	case WID_142:
	case WID_144:
	case WID_154:
	case WID_HOTKEYWND:
	case WID_RELOADLUASCRIPTWND:
	case WID_QUIKSLOTWND:
	case WID_164:
	case WID_174:
	case WID_175:
	case WID_177:
	case WID_178:
	case WID_179:
	case WID_BUTTONS_OF_BASICWND:
		return true;
	break;
	default:
		return false;
	break;
	}
}


void UIWindowMgr::AddToEscList(WINDOWID windowId)
{
	if( !this->UIWindowMgr::IsNoEscWindow(windowId) )
		this->UIWindowMgr::RemoveFromEscList(windowId);

	m_WindowEscList.push_front(windowId);
}


void UIWindowMgr::RemoveFromEscList(WINDOWID windowId)
{
	if( this->UIWindowMgr::IsNoEscWindow(windowId) )
		return;

	for( mystd::list<WINDOWID>::iterator it = m_WindowEscList.begin(); it != m_WindowEscList.end(); ++it )
	{
		if( windowId == *it )
		{
			m_WindowEscList.erase(it);
			break;
		}
	}
}


hook_ptr<struct mystd::_Tree<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,struct mystd::pair<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > const ,class UIWindow *>,struct mystd::map<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,class UIWindow *,struct mystd::less<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,class mystd::allocator<class UIWindow *> >::_Kfn,struct mystd::less<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,class mystd::allocator<class UIWindow *> >::_Node *> mystd::_Tree<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,struct mystd::pair<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > const ,class UIWindow *>,struct mystd::map<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,class UIWindow *,struct mystd::less<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,class mystd::allocator<class UIWindow *> >::_Kfn,struct mystd::less<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,class mystd::allocator<class UIWindow *> >::_Nil("std::map<std::string,UIWindow*>::_Nil");
