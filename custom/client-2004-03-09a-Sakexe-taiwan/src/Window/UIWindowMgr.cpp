#include "GameMode.h"
#include "Globals.h"
#include "ModeMgr.h"
#include "Session.h"
#include "3dLib/DrawUtil.h" // DrawBoxScreen()
#include "Base/ResMgr.h"
#include "Resource/Wave.h"
#include "Window/UIEquipWnd.h"
#include "Window/UIFrameWnd.h"
#include "Window/UIFrameWnd2.h"
#include "Window/UIGuildWnd.h"
#include "Window/UIItemWnd.h"
#include "Window/UIMessengerWnd.h"
#include "Window/UISelectCharWnd.h"
#include "Window/UIWhisperWnd.h"
#include "Window/UIRectInfo.h"
#include "Window/UISys.h"
#include "Window/UIWindowMgr.h"


UIWindowMgr::UIWindowMgr() // line 203-224
{
	this->UIWindowMgr::MakeWndPointerNull();
	m_lastMouseX = -1;
	m_lastMouseY = -1;
	m_wallpaperSurface = NULL;
	m_w = 0;
	m_h = 0;
	m_chatMsg = "";
	m_chatWndStatus = 1;
	m_chatWndHeight = 98;
	m_chatWndX = 0;
	m_chatWndY = 0;
	m_chatWndShow = 1;
	m_miniMapZoomFactor = 4.0;
	m_miniMapArgb = 0xAAFFFFFF;
	m_isDrawCompass = 1;
	m_chatWndWhisperCurHis = 0;
	m_chatWndCurHis = 0;
	m_isInvalidatedByForce = FALSE;
	m_conversionMode = (g_languageType == LanguageJapanese);
}


UIWindowMgr::~UIWindowMgr() // line 227-230
{
	this->UIWindowMgr::RemoveAllWindows();
	this->UIWindowMgr::DestroyDC(); // inlined
}


void UIWindowMgr::ClearDC(COLORREF color) // line 253-255
{
	this->UIWindowMgr::DestroyDC(); // inlined
}


void UIWindowMgr::DestroyDC() // line 245-250
{
	if( m_wallpaperSurface != NULL )
	{
		delete m_wallpaperSurface;
		m_wallpaperSurface = NULL;
	}
}


void UIWindowMgr::AddWindow(UIWindow* window) // line 258-260
{
	m_children.push_back(window);
}


void UIWindowMgr::AddWindowFront(UIWindow* window) // line 263-265
{
	m_children.push_front(window);
}


void UIWindowMgr::RemoveAllWindows() // line 328-340
{
	for( mystd::list<UIWindow*>::iterator it = m_children.begin(); it != m_children.end(); ++it )
	{
		UIWindow* wnd = *it;
		wnd->StoreInfo();
		delete wnd;
	}

	m_children.clear();
	m_quitWindow.clear();
	m_snapInfo.clear();

	this->UIWindowMgr::MakeWndPointerNull();
}


void UIWindowMgr::RemoveAllWindowsExceptChatWnd() // line 290-325
{
	if( m_chatWnd == NULL )
	{
		this->UIWindowMgr::RemoveAllWindows();
		return;
	}

	for( mystd::list<UIWindow*>::iterator it = m_children.begin(); it != m_children.end(); )
	{
		UIWindow* wnd = *it;

		if( wnd == m_chatWnd )
			++it;
		else
		{
			wnd->StoreInfo();
			delete wnd;
			it = m_children.erase(it);
		}
	}

	for( mystd::list<UIWindow*>::iterator it = m_quitWindow.begin(); it != m_quitWindow.end(); )
	{
		UIWindow* wnd = *it;

		if( wnd == m_chatWnd )
			++it;
		else
		{
			it = m_quitWindow.erase(it);
		}
	}

	for( mystd::map<UIWindow*, CSnapInfo>::iterator it = m_snapInfo.begin(); it != m_snapInfo.end(); )
	{
		UIWindow* wnd = it->first;

		if( wnd == m_chatWnd )
			++it;
		else
		{
			it = m_snapInfo.erase(it);
		}
	}

	UIChatWnd* chatWnd = m_chatWnd; // backup
	this->UIWindowMgr::MakeWndPointerNull();
	m_chatWnd = chatWnd; // restore
}


void UIWindowMgr::ClearAllWindowState() // line 547-554
{
	for( mystd::list<UIWindow*>::iterator it = m_children.begin(); it != m_children.end(); ++it )
		(*it)->UIWindow::ClearAllChildrenState();
}


void UIWindowMgr::HideChatWnd() // line 284-287
{
	if( m_chatWnd != NULL )
		m_chatWnd->SetShow(FALSE);
}


hook_method<int (UIWindowMgr::*)()> UIWindowMgr::_ProcessInput(SAKEXE, "UIWindowMgr::ProcessInput");
int UIWindowMgr::ProcessInput() // line 398-544
{
	return (this->*_ProcessInput)();

	//TODO
}


void UIWindowMgr::MakeTopLayer(UIWindow* window) // line 343-353
{
	mystd::list<UIWindow*>::iterator it;
	for( it = m_children.begin(); it != m_children.end(); ++it )
		if( *it == window )
			break;

	if( it == m_children.end() )
		return; // not found.

	m_children.erase(it);
	m_children.push_back(window);
}


void UIWindowMgr::InvalidateUpdateNeededUI() // line 366-376
{
	if( m_isInvalidatedByForce )
		return; // already invalidated

	m_isInvalidatedByForce = TRUE;

	for( mystd::list<UIWindow*>::iterator it = m_children.begin(); it != m_children.end(); ++it )
		if( (*it)->IsUpdateNeed() )
			(*it)->UIWindow::InvalidateChildren();
}


void UIWindowMgr::InvalidateAll() // line 356-363
{
	for( mystd::list<UIWindow*>::iterator it = m_children.begin(); it != m_children.end(); ++it )
		(*it)->UIWindow::InvalidateChildren();
}


void UIWindowMgr::InvalidateGuildWnd() // line 5571-5592
{
	//TODO
/*
	if( m_guildInfoManageWnd != NULL )
		m_guildInfoManageWnd->SendMsg(NULL, UM_REFRESH, 0, 0, 0);

	if( m_guildMemberManageWnd != NULL )
		m_guildMemberManageWnd->SendMsg(NULL, UM_REFRESH, 0, 0, 0);

	if( m_guildPositionManageWnd != NULL )
		m_guildPositionManageWnd->SendMsg(NULL, UM_REFRESH, 0, 0, 0);

	if( m_guildSkillWnd != NULL )
		m_guildSkillWnd->SendMsg(NULL, UM_REFRESH, 0, 0, 0);

	if( m_guildBanishedMemberWnd != NULL )
		m_guildBanishedMemberWnd->SendMsg(NULL, UM_REFRESH, 0, 0, 0);

	if( m_guildNoticeWnd != NULL )
		m_guildNoticeWnd->SendMsg(NULL, UM_REFRESH, 0, 0, 0);

	if( m_guildTotalInfoWnd != NULL )
		m_guildTotalInfoWnd->SendMsg(NULL, UM_REFRESH, 0, 0, 0);
*/
}


hook_method<void (UIWindowMgr::*)()> UIWindowMgr::_OnProcess(SAKEXE, "UIWindowMgr::OnProcess");
void UIWindowMgr::OnProcess() // line 557
{
	return (this->*_OnProcess)();

	//TODO
}


void UIWindowMgr::Render() // line 567-596
{
	m_isInvalidatedByForce = FALSE;

	if( m_wallpaperSurface != NULL )
		m_wallpaperSurface->DrawSurfaceStretch((g_3dDevice.C3dDevice::GetWidth() - m_w) / 2, (g_3dDevice.C3dDevice::GetHeight() - m_h) / 2, m_w, m_h);

	for( mystd::list<UIWindow*>::iterator it = m_children.begin(); it != m_children.end(); ++it )
	{
		UIWindow* wnd = *it;

		if( wnd->UIWindow::IsShow() == FALSE )
			continue; // skip hidden windows

		wnd->UIWindow::DoDraw(FALSE);

		BOXINFO boxInfo;
		if( wnd->GetTransBoxInfo(&boxInfo) )
			DrawBoxScreen(boxInfo.x, boxInfo.y, boxInfo.cx, boxInfo.cy, boxInfo.color);

		wnd->UIWindow::DrawSurface(); // @custom
	}
}


hook_method<void (UIWindowMgr::*)(UIWindow* wnd)> UIWindowMgr::_SetFocusEdit(SAKEXE, "UIWindowMgr::SetFocusEdit");
void UIWindowMgr::SetFocusEdit(UIWindow* wnd) // line 735
{
	return (this->*_SetFocusEdit)(wnd);

	//TODO
}


hook_method<UIWindow* (UIWindowMgr::*)()> UIWindowMgr::_GetFocusEdit(SAKEXE, "UIWindowMgr::GetFocusEdit");
UIWindow* UIWindowMgr::GetFocusEdit() // line 747
{
	return (this->*_GetFocusEdit)();

	return m_editWindow;
}


hook_method<void (UIWindowMgr::*)(UIWindow* window)> UIWindowMgr::_SetCapture(SAKEXE, "UIWindowMgr::SetCapture");
void UIWindowMgr::SetCapture(UIWindow* window) // line 751
{
	return (this->*_SetCapture)(window);

	m_captureWindow = window;
}


hook_method<UIWindow* (UIWindowMgr::*)()> UIWindowMgr::_GetCapture(SAKEXE, "UIWindowMgr::GetCapture");
UIWindow* UIWindowMgr::GetCapture() // line 757
{
	return (this->*_GetCapture)();

	return m_captureWindow;
}


hook_method<void (UIWindowMgr::*)()> UIWindowMgr::_ReleaseCapture(SAKEXE, "UIWindowMgr::ReleaseCapture");
void UIWindowMgr::ReleaseCapture() // line 762
{
	return (this->*_ReleaseCapture)();

	m_captureWindow = NULL;
}


hook_method<void (UIWindowMgr::*)(UIWindow* wnd)> UIWindowMgr::_PostQuit(SAKEXE, "UIWindowMgr::PostQuit");
void UIWindowMgr::PostQuit(UIWindow* wnd) // line 963
{
	return (this->*_PostQuit)(wnd);

	m_quitWindow.push_back(wnd);
}


hook_method<int (UIWindowMgr::*)(const char* msg, int type, int isDefYes, int changeMsg, unsigned long autoReturnTime)> UIWindowMgr::_ErrorMsg(SAKEXE, "UIWindowMgr::ErrorMsg");
int UIWindowMgr::ErrorMsg(const char* msg, int type, int isDefYes, int changeMsg, unsigned long autoReturnTime) // line 1105
{
	return (this->*_ErrorMsg)(msg, type, isDefYes, changeMsg, autoReturnTime);

	//TODO
}


hook_method<void (UIWindowMgr::*)(mystd::string wName)> UIWindowMgr::_DeleteWhisperWindow(SAKEXE, "UIWindowMgr::DeleteWhisperWindow");
void UIWindowMgr::DeleteWhisperWindow(mystd::string wName)
{
	return (this->*_DeleteWhisperWindow)(wName);

	//TODO
}


hook_method<void (UIWindowMgr::*)(UIWindow* wnd)> UIWindowMgr::_AddToNameWaitingWindowList(SAKEXE, "UIWindowMgr::AddToNameWaitingWindowList");
void UIWindowMgr::AddToNameWaitingWindowList(UIWindow* wnd) // line 5496
{
	return (this->*_AddToNameWaitingWindowList)(wnd);

	//TODO
}


hook_method<void (UIWindowMgr::*)(UIWindow* wnd)> UIWindowMgr::_RemoveFromNameWaitingWindowList(SAKEXE, "UIWindowMgr::RemoveFromNameWaitingWindowList");
void UIWindowMgr::RemoveFromNameWaitingWindowList(UIWindow* wnd) // line 5505
{
	return (this->*_RemoveFromNameWaitingWindowList)(wnd);

	//TODO
}


hook_method<void (UIWindowMgr::*)()> UIWindowMgr::_RefreshNameWaitingWindowList(SAKEXE, "UIWindowMgr::RefreshNameWaitingWindowList");
void UIWindowMgr::RefreshNameWaitingWindowList() // line 5512-5518
{
	return (this->*_RefreshNameWaitingWindowList)();

	//TODO
}


hook_method<bool (UIWindowMgr::*)(unsigned long virtualKey, int newKeydown)> UIWindowMgr::_ProcessPushButton(SAKEXE, "UIWindowMgr::ProcessPushButton");
bool UIWindowMgr::ProcessPushButton(unsigned long virtualKey, int newKeydown) // line 4505
{
	return (this->*_ProcessPushButton)(virtualKey, newKeydown);

	//TODO
}


hook_method<void (UIWindowMgr::*)()> UIWindowMgr::_RefreshItem(SAKEXE, "UIWindowMgr::RefreshItem");
void UIWindowMgr::RefreshItem() // line 890-895
{
	return (this->*_RefreshItem)();

	//TODO
}


hook_method<void (UIWindowMgr::*)()> UIWindowMgr::_MakeWndPointerNull(SAKEXE, "UIWindowMgr::MakeWndPointerNull");
void UIWindowMgr::MakeWndPointerNull() // line 103-200
{
	return (this->*_MakeWndPointerNull)();

	m_lastHitWindow = NULL;
	m_captureWindow = NULL;
	m_editWindow = NULL;
	m_modalWindow = NULL;
	m_chatWnd = NULL;
	m_loadingWnd = NULL;
	m_basicInfoWnd = NULL;
	m_itemWnd = NULL;
	m_equipWnd = NULL;
	m_statusWnd = NULL;
	m_optionWnd = NULL;
	m_minimapZoomWnd = NULL;
	m_itemDropCntWnd = NULL;
	m_sayDialogWnd = NULL;
	m_chooseWnd = NULL;
	m_itemIdentifyWnd = NULL;
	m_itemCompositionWnd = NULL;
	m_chooseWarpWnd = NULL;
	m_menu = NULL;
	m_comboBoxWnd = NULL;
	m_itemCollectionWnd = NULL;
	m_combinedCardItemCollectionWnd = NULL;
	m_itemParamChangeDisplayWnd = NULL;
	m_skillDescribeWnd = NULL;
	m_quitWnd = NULL;
	m_restartWnd = NULL;
	m_cardItemIllustWnd = NULL;
	m_notifyLevelUpWnd = NULL;
	m_notifyJobLevelUpWnd = NULL;
	m_itemShopWnd = NULL;
	m_itemPurchaseWnd = NULL;
	m_itemSellWnd = NULL;
	m_chooseSellBuyWnd = NULL;
	m_chatRoomMakeWnd = NULL;
	m_chatRoomChangeWnd = NULL;
	m_chatRoomWnd = NULL;
	m_passwordWnd = NULL;
	m_exchangeWnd = NULL;
	m_exchangeAcceptWnd = NULL;
	m_itemStoreWnd = NULL;
	m_skillListWnd = NULL;
	m_messengerGroupWnd = NULL;
	m_joinPartyAcceptWnd = NULL;
	m_CoupleAcceptWnd = NULL;
	m_BabyAcceptWnd = NULL;
	m_joinGuildAcceptWnd = NULL;
	m_allyGuildAcceptWnd = NULL;
	m_shortCutWnd = NULL;
	m_tipOfTheDayWnd = NULL;
	m_merchantItemWnd = NULL;
	m_merchantMirrorItemWnd = NULL;
	m_merchantShopMakeWnd = NULL;
	m_merchantItemShopWnd = NULL;
	m_merchantItemPurchaseWnd = NULL;
	m_merchantItemMyShopWnd = NULL;
	m_candidateWnd = NULL;
	m_compositionWnd = NULL;
	m_keyStrokeWnd = NULL;
	m_partySettingWnd = NULL;
	m_skillNameChangeWnd = NULL;
	m_npcEditDialogWnd = NULL;
	m_npcTextEditDialogWnd = NULL;
	m_detailLevelWnd = NULL;
	m_notifyItemObtainWnd = NULL;
	m_guildInfoManageWnd = NULL;
	m_guildMemberManageWnd = NULL;
	m_guildPositionManageWnd = NULL;
	m_guildSkillWnd = NULL;
	m_guildBanishedMemberWnd = NULL;
	m_guildNoticeWnd = NULL;
	m_guildTotalInfoWnd = NULL;
	m_whisperListWnd = NULL;
	m_friendOptionWnd = NULL;
	m_guildLeaveReasonDescWnd = NULL;
	m_guildBanReasonDescWnd = NULL;
	m_illustWnd = NULL;
	m_petInfoWnd = NULL;
	m_selectPetEggWnd = NULL;
	m_petTamingDeceiveWnd = NULL;
	m_makingArrowListWnd = NULL;
	m_selectCartWnd = NULL;
	m_emotionWnd = NULL;
	m_emotionListWnd = NULL;
}


void UIWindowMgr::AddFriendCharName(const char* friendCharName) // line 984
{
	mystd::vector<mystd::string>::iterator it;
	for( it = m_friendNames.begin(); it != m_friendNames.end(); ++it )
		if( *it == friendCharName )
			break;

	if( it == m_friendNames.end() )
	{// add to list
		m_friendNames.push_back(friendCharName);
	}

	if( m_whisperListWnd != NULL )
		m_whisperListWnd->SendMsg(NULL, UM_REFRESH, 0, 0, 0);
}


void UIWindowMgr::AddWhisperCharName(const char* whisperCharName) // line 1004
{
	if( m_chatWnd == NULL )
		return;

	UIWhisperEditCtrl* wc = m_chatWnd->m_whisperChat;

	mystd::vector<mystd::string>::iterator it;
	for( it = wc->m_hisChat.begin(); it != wc->m_hisChat.end(); ++wc )
		if( *it == whisperCharName )
			break;

	if( it == wc->m_hisChat.end() )
	{// add to list
		wc->m_hisChat.push_back(whisperCharName);

		if( wc->m_curHis >= int(wc->m_hisChat.size() - 1) ) // past old end position
			wc->m_curHis = int(wc->m_hisChat.size()); // move cursor to new end position
	}
}


hook_method<void (UIWindowMgr::*)(mystd::string whisperName)> UIWindowMgr::_DeleteFriendName(SAKEXE, "UIWindowMgr::DeleteFriendName");
void UIWindowMgr::DeleteFriendName(mystd::string whisperName) // line 5462
{
	return (this->*_DeleteFriendName)(whisperName);

	//TODO
}


BOOL UIWindowMgr::AddWhisperChatToWhisperWnd(const char* cName, const char* chatMsg, COLORREF color) // line 5535
{
	BOOL isFriendName = FALSE;
	for( mystd::vector<mystd::string>::iterator it = m_friendNames.begin(); it != m_friendNames.end(); ++it )
	{
		if( *it == cName )
		{
			isFriendName = true;
			break; // found.
		}
	}

	BOOL isMadeNewly = FALSE;
	if( g_session.m_isShowWhisperWnd && !isFriendName || g_session.m_isShowWhisperWnd_Friend && isFriendName )
	{// pop up new 1:1 chat window
		isMadeNewly = (BOOL)this->UIWindowMgr::SendMsg(UIM_MAKE_WHISPER_WINDOW, (int)cName, 0, 0);
		if( isMadeNewly )
		{
			if( g_resMgr().CResMgr::IsExist(whisperWindowOpenSound) )
				PlayWave(whisperWindowOpenSound, 0.0, 0.0, 0.0, 250, 40, 1.0);
		}
	}

	if( strcmp(cName, g_session.CSession::GetCharName()) == 0 )
		return FALSE; // ignore whisper to self

	if( g_session.m_isShowWhisperWnd && isMadeNewly )
		g_windowMgr.UIWindowMgr::AddWhisperCharName(cName);

	mystd::map<mystd::string,UIWindow*>::iterator it = m_whisperNameWindow.find(cName);
	if( it == m_whisperNameWindow.end() )
		return FALSE; // 1:1 chat window not found

	UIWindow* wnd = it->second;
	wnd->SendMsg(NULL, UM_ADDCHAT, (int)chatMsg, (int)color, 0);

	for( mystd::list<UIWindow*>::iterator it = m_children.begin(); it != m_children.end(); ++it )
	{
		if( *it == wnd )
		{// make 'wnd' the topmost window
			m_children.erase(it);
			m_children.push_back(wnd);
			break;
		}
	}

	return TRUE;
}


hook_method<void (UIWindowMgr::*)(const char* cName)> UIWindowMgr::_WriteWhisperChatToFile(SAKEXE, "UIWindowMgr::WriteWhisperChatToFile");
void UIWindowMgr::WriteWhisperChatToFile(const char* cName) // line 5563
{
	return (this->*_WriteWhisperChatToFile)(cName);

	//TODO
}


hook_method<bool (UIWindowMgr::*)(unsigned long virtualKey, int newKeydown)> UIWindowMgr::_ExcuteMsgInBattleMode(SAKEXE, "UIWindowMgr::ExcuteMsgInBattleMode");
bool UIWindowMgr::ExcuteMsgInBattleMode(unsigned long virtualKey, int newKeydown) // line 4369
{
	return (this->*_ExcuteMsgInBattleMode)(virtualKey, newKeydown);

	//TODO
}


hook_method<void (UIWindowMgr::*)()> UIWindowMgr::_SetTextAtBattleMode(SAKEXE, "UIWindowMgr::SetTextAtBattleMode");
void UIWindowMgr::SetTextAtBattleMode() // line 4497
{
	return (this->*_SetTextAtBattleMode)();

	//TODO
}


hook_method<void (UIWindowMgr::*)(CBitmapRes* bitmap)> UIWindowMgr::_SetWallpaper(SAKEXE, "UIWindowMgr::SetWallpaper");
void UIWindowMgr::SetWallpaper(CBitmapRes* bitmap) // line 612
{
	return (this->*_SetWallpaper)(bitmap);

	//TODO
}


hook_method<void (UIWindowMgr::*)(int x, int y, CBitmapRes* bitmap)> UIWindowMgr::_DrawBitmapToFrame(SAKEXE, "UIWindowMgr::DrawBitmapToFrame");
void UIWindowMgr::DrawBitmapToFrame(int x, int y, CBitmapRes* bitmap) // line 599
{
	return (this->*_DrawBitmapToFrame)(x, y, bitmap);

	//TODO
}


//hook_method<void (UIWindowMgr::*)(const char* msg)> UIWindowMgr::_SetChatMsg(SAKEXE, "UIWindowMgr::SetChatMsg");
void UIWindowMgr::SetChatMsg(const char* msg) // line ???
{
//	return (this->*_SetChatMsg)(msg);

	m_chatMsg = msg;
}


hook_method<void (UIWindowMgr::*)()> UIWindowMgr::_ClearChatMsg(SAKEXE, "UIWindowMgr::ClearChatMsg");
void UIWindowMgr::ClearChatMsg() // line 1463 (Window/UISys.h)
{
	return (this->*_ClearChatMsg)();

	m_chatMsg = "";
}


hook_method<const char* (UIWindowMgr::*)()> UIWindowMgr::_GetChatMsg(SAKEXE, "UIWindowMgr::GetChatMsg");
const char* UIWindowMgr::GetChatMsg() // line 1464 (Window/UISys.h)
{
	return (this->*_GetChatMsg)();

	return m_chatMsg.c_str();
}


hook_method<void (UIWindowMgr::*)()> UIWindowMgr::_InitFriendNameListFromRegistry(SAKEXE, "UIWindowMgr::InitFriendNameListFromRegistry");
void UIWindowMgr::InitFriendNameListFromRegistry() // line 1873
{
	return (this->*_InitFriendNameListFromRegistry)();

	//TODO
}


hook_method<void (UIWindowMgr::*)()> UIWindowMgr::_InitShortcutItemInfoFromReg(SAKEXE, "UIWindowMgr::InitShortcutItemInfoFromReg");
void UIWindowMgr::InitShortcutItemInfoFromReg() // line 1446
{
	return (this->*_InitShortcutItemInfoFromReg)();

	//TODO
}


hook_method<void (UIWindowMgr::*)()> UIWindowMgr::_InitUIRectInfoFromReg(SAKEXE, "UIWindowMgr::InitUIRectInfoFromReg");
void UIWindowMgr::InitUIRectInfoFromReg() // line 1197
{
	return (this->*_InitUIRectInfoFromReg)();

	//TODO
}


hook_method<void (UIWindowMgr::*)()> UIWindowMgr::_WriteUIRectInfoToReg(SAKEXE, "UIWindowMgr::WriteUIRectInfoToReg");
void UIWindowMgr::WriteUIRectInfoToReg() // line 1591
{
	return (this->*_WriteUIRectInfoToReg)();

	//TODO
}


hook_method<void (UIWindowMgr::*)()> UIWindowMgr::_WriteShorcutItemInfoToReg(SAKEXE, "UIWindowMgr::WriteShorcutItemInfoToReg");
void UIWindowMgr::WriteShorcutItemInfoToReg() // line 1548-1588
{
	return (this->*_WriteShorcutItemInfoToReg)();

	//TODO
}


hook_method<void (UIWindowMgr::*)()> UIWindowMgr::_InitSkillUseLevelInfoFromReg(SAKEXE, "UIWindowMgr::InitSkillUseLevelInfoFromReg");
void UIWindowMgr::InitSkillUseLevelInfoFromReg() // line 1801
{
	return (this->*_InitSkillUseLevelInfoFromReg)();

	//TODO
}


hook_method<void (UIWindowMgr::*)()> UIWindowMgr::_WriteSkillUseLevelInfoToReg(SAKEXE, "UIWindowMgr::WriteSkillUseLevelInfoToReg");
void UIWindowMgr::WriteSkillUseLevelInfoToReg() // line 1844-1867
{
	return (this->*_WriteSkillUseLevelInfoToReg)();

	//TODO
}


hook_method<void (UIWindowMgr::*)()> UIWindowMgr::_WriteFriendNameListToRegistry(SAKEXE, "UIWindowMgr::WriteFriendNameListToRegistry");
void UIWindowMgr::WriteFriendNameListToRegistry() // line 1960-2096
{
	return (this->*_WriteFriendNameListToRegistry)();

	//TODO
}


BOOL UIWindowMgr::IsFriendName(const char* cName) // line 5521-5531
{
	mystd::vector<mystd::string>::const_iterator it;
	for( it = m_friendNames.begin(); it != m_friendNames.end(); ++it )
		if( *it == cName )
			break;

	return ( it != m_friendNames.end() ) ? TRUE : FALSE;
}


int UIWindowMgr::SendMsg(int message, int val1, int val2, int val3) // 5318
{
	switch( message )
	{
	case UIM_MAKE_WHISPER_WINDOW:
	{
		mystd::string wName = (const char*)val1;

		if( m_whisperNameWindow.find(wName) != m_whisperNameWindow.end() )
			break;

		UIWhisperWnd* wnd = new UIWhisperWnd();
		wnd->UIWindow::Create(280, 120);
		m_children.push_back(wnd);
		wnd->SendMsg(NULL, UM_SETINFO, (int)&whisperWndInfo, 0, 0);
		wnd->SetShow(TRUE);
		wnd->m_whisperName = wName;

		if( m_whisperNameWindow.size() != 0 )
		{
			int size = 17 * m_whisperNameWindow.size();

			if( size + whisperWndInfo.x > 0 && size + whisperWndInfo.x + whisperWndInfo.w < g_renderer->CRenderer::GetWidth() - 17
			 && size + whisperWndInfo.y > 0 && size + whisperWndInfo.y + whisperWndInfo.h < g_renderer->CRenderer::GetHeight() - 17 )
				wnd->Move(size + whisperWndInfo.x, size + whisperWndInfo.y);
			else
			if( size > 0 && size + whisperWndInfo.w < g_renderer->CRenderer::GetWidth() - 17
			 && size > 0 && size + whisperWndInfo.h < g_renderer->CRenderer::GetHeight() - 17 )
				wnd->Move(size, size);
		}

		if( m_whisperNameWindow.find(wName) == m_whisperNameWindow.end() )
			m_whisperNameWindow[wName] = wnd;

		this->UIWindowMgr::AddWhisperCharName(wName.c_str());
		return 1;
	}
	break;
	case UIM_SAVE_CHAT_TO_FILE_FROM_CHATROOM:
		if( m_chatRoomWnd != NULL )
			m_chatRoomWnd->UIChatRoomWnd::WriteChatToFile();
	break;
	case UIM_SAVE_CHAT_TO_FILE:
		if( m_chatWnd != NULL )
			m_chatWnd->UIChatWnd::WriteChatToFile();
	break;
	case UIM_PUSH_INTO_CHATROOM:
		if( m_chatRoomWnd != NULL )
			m_chatRoomWnd->SendMsg(NULL, UM_ADDCHAT, val1, val2, 0);
	break;
	case UIM_PUSHINTOCHATHISTORY:
	{
		const char* msg = (const char*)val1;
		COLORREF colorRef = (COLORREF)val2;
		if( colorRef == 0x000000 )
			colorRef = 0xFFFFFF;

		if( m_chatWnd != NULL )
			m_chatWnd->SendMsg(NULL, UM_ADDCHAT, (int)msg, (int)colorRef, 0);
		else
		{
			mystd::vector<mystd::string> strings;
			CutString(msg, strings, '^');

			for( size_t i = 0; i < strings.size(); ++i )
			{
				StringAndColor sc;
				sc.String = strings[i];
				sc.Color = colorRef;

				m_chatWndHistory.push_back(sc);
			}
		}
	}
	break;
	case UIM_LOADINGPERCENT:
		if( m_loadingWnd != NULL )
			m_loadingWnd->SendMsg(NULL, UM_LOADINGPERCENT, val1, 0, 0);
	break;
	case UIM_OPENCHATWND:
		this->UIWindowMgr::ShowWindow(WID_CHATWND, 1);
		if( m_chatWnd != NULL )
			m_chatWnd->SendMsg(NULL, UM_OPENCHATWND, 0, 0, 0);
	break;
	case UIM_CHANGECHATWNDSTATUS:
		if( m_chatWnd != NULL )
			m_chatWnd->SendMsg(NULL, UM_CHANGESTATUS, val1, 0, 0);
	break;
	case UIM_IME_OPENCANDIDATE:
	case UIM_IME_CHANGECANDIDATE:
	{
		UIWindow* wnd = this->UIWindowMgr::MakeWindow(WID_CANDIDATEWND);
		wnd->SendMsg(NULL, UM_IME_SET_CANDIDATE, val1, val2, 0);
	}
	break;
	case UIM_IME_CLOSECANDIDATE:
		this->UIWindowMgr::DeleteWindow(WID_CANDIDATEWND);
	break;
	default:
	break;
	}

	return 0;
}


hook_method<UIFrameWnd* (UIWindowMgr::*)(WINDOWID windowId)> UIWindowMgr::_MakeWindow(SAKEXE, "UIWindowMgr::MakeWindow");
UIFrameWnd* UIWindowMgr::MakeWindow(WINDOWID windowId) // line 2909-4333
{
	return (this->*_MakeWindow)(windowId);

	UIFrameWnd* wnd = NULL;

	switch( windowId )
	{
	case WID_BASICINFOWND:
		wnd = m_basicInfoWnd;
		if( wnd == NULL )
		{
			wnd = m_basicInfoWnd = new UIBasicInfoWnd();
			wnd->UIWindow::Create(280, 34);
			wnd->Move(0, 0);
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&basicInfoWndInfo, 0, 0);
			g_snapMgr.CSnapMgr::AddSnapMasterObject(wnd);
		}

		wnd->SetShow(1);

		if( itemWndInfo.show )
			this->UIWindowMgr::MakeWindow(WID_ITEMWND);
		if( equipWndInfo.show )
			this->UIWindowMgr::MakeWindow(WID_EQUIPWND);
		if( statusWndInfo.show )
			this->UIWindowMgr::MakeWindow(WID_STATUSWND);
		if( optionWndInfo.show )
			this->UIWindowMgr::MakeWindow(WID_OPTIONWND);
		if( skillListWndInfo.show )
			this->UIWindowMgr::MakeWindow(WID_SKILLLISTWND);
		if( merchantItemWndInfo.show && IsEffectStatePushCart(g_session.m_effectState) )
			g_windowMgr.UIWindowMgr::MakeWindow(WID_MERCHANTITEMWND);
		if( g_modeMgr.CModeMgr::GetGameMode()->CGameMode::CanRotateView() )
			this->UIWindowMgr::MakeWindow(WID_MINIMAPZOOMWND);
		this->UIWindowMgr::ShowWindow(WID_CHATWND, m_chatWndShow);
		this->UIWindowMgr::ShowWindow(WID_SHORTCUTWND, shortCutWndInfo.show);
		this->UIWindowMgr::ShowWindow(WID_ITEMDROPCNTWND, 0);
		if( messengerGroupWndInfo.show )
			this->UIWindowMgr::MakeWindow(WID_MESSENGERWND);
		if( g_session.m_isLowSystemMemory && g_session.m_bAutoOpenDetailWindowIfLowMemory && g_registry.m_spriteMode == 2 && g_registry.m_textureMode == 2 )
			this->UIWindowMgr::MakeWindow(WID_DETAILLEVELWND);
	break;
	case WID_CHATWND:
		wnd = m_chatWnd;
		if( wnd == NULL )
		{
			wnd = m_chatWnd = new UIChatWnd();
			wnd->UIWindow::Create(600, m_chatWndHeight);
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SendMsg(NULL, 34, 0, 0, 0);
	break;
	case WID_SELECTSERVERWND:
		wnd = new UISelectServerWnd();
		wnd->UIWindow::Create(280, 200);
		wnd->Move(UIX(185), UICY(300) - 80);
		this->UIWindowMgr::AddWindow(wnd);
	break;
	case WID_LOGINWND:
		wnd = new UILoginWnd();
		wnd->UIWindow::Create(280, 120);
		wnd->Move(UIX(185), UICY(300));
		this->UIWindowMgr::AddWindow(wnd);
	break;
	case WID_NOTICEWND:
		wnd = new UINoticeWnd();
		wnd->UIWindow::Create(600, 400);
		wnd->Move(UIX(33), UIY(40));
		this->UIWindowMgr::AddWindow(wnd);
		return wnd;
	break;
/*
	case WID_MAKECHARWND:
		wnd = new UIMakeCharWnd();
		wnd->UIWindow::Create(576, 342);
		wnd->Move(UIX(33), UIY(65));
		this->UIWindowMgr::AddWindow(wnd);
		return wnd;
	break;
*/
	case WID_SELECTCHARWND:
		wnd = new UISelectCharWnd();
		wnd->UIWindow::Create(576, 342);
		wnd->Move(UIX(33), UIY(65));
		this->UIWindowMgr::AddWindow(wnd);
		stateId.clear();
		return wnd;
	break;
	case WID_ITEMWND:
		wnd = m_itemWnd;
		if( wnd == NULL )
		{
			wnd = m_itemWnd = new UIItemWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(0, 120);
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&itemWndInfo, 0, 0);
			g_snapMgr.CSnapMgr::AddSnapObject(wnd);
		}
		m_itemWnd->SetShow(1);
		itemWndInfo.show = 1;
	break;
	case WID_WAITWND:
		wnd = new UIWaitWnd();
		wnd->UIWindow::Create(280, 120);
		wnd->Move(UIX(185), UICY(300));
		this->UIWindowMgr::AddWindow(wnd);
	break;
	case WID_LOADINGWND:
		wnd = m_loadingWnd;
		if( wnd == NULL )
		{
			wnd = m_loadingWnd = new UILoadingWnd();
			if( g_serviceType == 4 )
			{
				wnd->UIWindow::Create(280, 120);
				wnd->Move(UIX(185), UICY(300));
			}
			else
			{
				wnd->UIWindow::Create(240, 15);
				wnd->Move(g_renderer->CRenderer::GetWidth() / 2 - 100, g_renderer->CRenderer::GetHeight() / 2 + 160);
			}
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_TOOLTIPWND:
		wnd = new UIToolTipWnd();
		wnd->UIWindow::Create(200, 120);
		wnd->Move(UIX(185), UICY(300));
		this->UIWindowMgr::AddWindow(wnd);
	break;
	case WID_SHORTCUTWND:
		wnd = m_shortCutWnd;
		if( wnd == NULL )
		{
			wnd = m_shortCutWnd = new UIShortCutWnd();
			wnd->UIWindow::Create(280, 34);
			wnd->Move(UIX(200), UICY(200));
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&shortCutWndInfo, 0, 0);
			g_snapMgr.CSnapMgr::AddSnapObject(wnd);
		}
	break;
	case WID_EQUIPWND:
		wnd = m_equipWnd;
		if( wnd == NULL )
		{
			wnd = m_equipWnd = new UIEquipWnd();
			wnd->UIWindow::Create(280, 147);
			wnd->Move(UIX(185), UICY(300));
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&equipWndInfo, 0, 0);
			g_snapMgr.CSnapMgr::AddSnapObject(wnd);
		}
		wnd->SetShow(1);
		equipWndInfo.show = 1;
	break;
	case WID_STATUSWND:
		wnd = m_statusWnd;
		if( wnd == NULL )
		{
			wnd = m_statusWnd = new UIStatusWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(UIX(185), UICY(300));
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&statusWndInfo, 0, 0);
			g_snapMgr.CSnapMgr::AddSnapObject(wnd);
		}
		wnd->SetShow(1);
		statusWndInfo.show = 1;
		this->UIWindowMgr::DeleteWindow(WID_NOTIFYLEVELUPWND);
	break;
	case WID_SKILLLISTWND:
		wnd = m_skillListWnd;
		if( wnd == NULL )
		{
			wnd = m_skillListWnd = new UISkillListWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(UIX(200), UICY(200));
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&skillListWndInfo, 0, 0);
		}
		wnd->SetShow(1);
		skillListWndInfo.show = 1;
		this->UIWindowMgr::DeleteWindow(WID_NOTIFYJOBLEVELUPWND);
	break;
/*
	case WID_ITEMSTOREWND:
		wnd = m_itemStoreWnd;
		if( m_itemStoreWnd == NULL )
		{
			wnd = m_itemStoreWnd = new UIItemStoreWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(UIX(200), UICY(200));
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&itemStoreWndInfo, 0, 0);
		}
		wnd->SetShow(1);
	break;
*/
	case WID_MESSENGERWND:
		if( this->messengerGroupWndInfo.radio != 0 )
			this->UIWindowMgr::MakeWindow(WID_MESSENGERGROUPWND);
		else
			this->UIWindowMgr::MakeWindow(WID_WHISPERLISTWND);
	break;
	case WID_MESSENGERGROUPWND:
		this->UIWindowMgr::DeleteWindow(WID_MESSENGERWND);
		wnd = m_messengerGroupWnd;
		if( wnd == NULL )
		{
			wnd = m_messengerGroupWnd = new UIMessengerGroupWnd();
			wnd->UIWindow::Create(140, 155);
			wnd->Move(UIX(200), UICY(200));
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&messengerGroupWndInfo, 0, 0);
		}
		wnd->SetShow(1);
		messengerGroupWndInfo.show = 1;
		messengerGroupWndInfo.radio = 1;
	break;
	case WID_WHISPERLISTWND:
		this->UIWindowMgr::DeleteWindow(WID_MESSENGERWND);
		wnd = m_whisperListWnd;
		if( wnd == NULL )
		{
			wnd = m_whisperListWnd = new UIWhisperListWnd();
			wnd->UIWindow::Create(194, 209);
			wnd->Move(0, 147);
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&messengerGroupWndInfo, 0, 0);
		}
		wnd->SetShow(1);
		messengerGroupWndInfo.show = 1;
		messengerGroupWndInfo.radio = 0;
	break;
/*
	case WID_MERCHANTSHOPMAKEWND:
//		wnd = m_merchantShopMakeWnd;
		if( wnd == NULL )
		{
//			wnd = m_merchantShopMakeWnd = new UIMerchantShopMakeWnd();
			wnd->UIWindow::Create(280, 220);
			wnd->Move(UIX(185), UICY(200));
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&merchantShopMakeWndInfo, 0, 0);
		}
		wnd->SetShow(1);
		this->UIWindowMgr::MakeWindow(WID_MERCHANTMIRRORITEMWND);
	break;
	case WID_MERCHANTMIRRORITEMWND:
//		wnd = m_merchantMirrorItemWnd;
		if( wnd == NULL )
		{
//			wnd = m_merchantMirrorItemWnd = new UIMerchantMirrorItemWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(UIX(0), UICY(120));
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&merchantMirrorItemWndInfo, 0, 0);
		}
		wnd->SetShow(1);
	break;
	case WID_MERCHANTITEMWND:
//		wnd = m_merchantItemWnd;
		if( wnd == NULL )
		{
//			wnd = m_merchantItemWnd = new UIMerchantItemWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(UIX(200), UICY(120));
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&merchantItemWndInfo, 0, 0);
		}
		wnd->SetShow(1);
		merchantItemWndInfo.show = 1;
	break;
	case WID_DETAILLEVELWND:
//		wnd = m_detailLevelWnd;
		if( wnd == NULL )
		{
//			wnd = m_detailLevelWnd = new UIDetailLevelWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(UIX(200), UICY(200));
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&detailLevelWndInfo, 0, 0);
		}
		wnd->SetShow(1);
	break;
*/
	case WID_NOTIFYITEMOBTAINWND:
		wnd = m_notifyItemObtainWnd;
		if( wnd == NULL )
		{
			wnd = m_notifyItemObtainWnd = new UINotifyItemObtainWnd();
			wnd->UIWindow::Create(180, 32);
			wnd->Move(UIX(220), 51);
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
/*
	case WID_NPCEDITDIALOGWND:
//		wnd = m_npcEditDialogWnd;
		if( wnd == NULL )
		{
//			wnd = m_npcEditDialogWnd = new UINpcEditDialogWnd();
			wnd->UIWindow::Create(176, 46);
			wnd->Move(UIX(200), UICY(200));
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_NPCTEXTEDITDIALOGWND:
//		wnd = m_npcTextEditDialogWnd;
		if( wnd == NULL )
		{
//			wnd = m_npcTextEditDialogWnd = new UINpcTextEditDialogWnd();
			wnd->UIWindow::Create(346, 46);
			wnd->Move(UIX(200), UICY(200));
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_SKILLNAMECHANGEWND:
//		wnd = m_skillNameChangeWnd;
		if( wnd == NULL )
		{
//			wnd = m_skillNameChangeWnd = new UISkillNameChangeWnd();
			wnd->UIWindow::Create(280, 48);
			wnd->Move(UIX(185), UIY(180));
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_GUILDWND:
		if( !guildWndInfo.GuildWndInfo::IsValidInfo() )
			guildWndInfo.GuildWndInfo::MakeDefault();

		switch( guildWndInfo.curTab )
		{
		case 0: wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_GUILDINFOMANAGEWND); break;
		case 1: wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_GUILDMEMBERMANAGEWND); break;
		case 2: wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_GUILDPOSITIONMANAGEWND); break;
		case 3: wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_GUILDSKILLWND); break;
		case 4: wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_GUILDBANISHEDMEMBERWND); break;
		case 5: wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_GUILDNOTICEWND); break;
		case 6: wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_GUILDTOTALINFOWND); break;
		default:
			break;
		}
	break;
	case WID_GUILDMEMBERMANAGEWND:
//		wnd = m_guildMemberManageWnd;
		if( wnd == NULL )
		{
//			wnd = m_guildMemberManageWnd = new UIGuildMemberManageWnd();
			wnd->UIWindow::Create(guildWndWidth, guildWndHeight);
			wnd->Move(0, 147);
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&guildWndInfo, 0, 0);
		}
		wnd->SetShow(1);
	break;
	case WID_GUILDPOSITIONMANAGEWND:
//		wnd = m_guildPositionManageWnd;
		if( wnd == NULL )
		{
//			wnd = m_guildPositionManageWnd = new UIGuildPositionManageWnd();
			wnd->UIWindow::Create(guildWndWidth, guildWndHeight);
			wnd->Move(0, 147);
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(0, 34, (int)&guildWndInfo, 0, 0);
		}
		wnd->SetShow(1);
	break;
	case WID_GUILDSKILLWND:
//		wnd = m_guildSkillWnd;
		if( wnd == NULL )
		{
//			wnd = m_guildSkillWnd = new UIGuildSkillWnd();
			wnd->UIWindow::Create(guildWndWidth, guildWndHeight);
			wnd->Move(0, 147);
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&guildWndInfo, 0, 0);
		}
		wnd->SetShow(1);
	break;
	case WID_GUILDBANISHEDMEMBERWND:
//		wnd = m_guildBanishedMemberWnd;
		if( wnd == NULL )
		{
//			wnd = m_guildBanishedMemberWnd = new UIGuildBanishedMemberWnd();
			wnd->UIWindow::Create(guildWndWidth, guildWndHeight);
			wnd->Move(0, 147);
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&guildWndInfo, 0, 0);
		}
		wnd->SetShow(1);
	break;
	case WID_GUILDNOTICEWND:
//		wnd = m_guildNoticeWnd;
		if( wnd == NULL )
		{
//			wnd = m_guildNoticeWnd = new UIGuildNoticeWnd();
			wnd->UIWindow::Create(guildWndWidth, guildWndHeight);
			wnd->Move(0, 147);
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&guildWndInfo, 0, 0);
		}
		wnd->SetShow(1);
	break;
	case WID_GUILDTOTALINFOWND:
//		wnd = m_guildTotalInfoWnd;
		if( wnd == NULL )
		{
//			wnd = m_guildTotalInfoWnd = new UIGuildTotalInfoWnd();
			wnd->UIWindow::Create(guildWndWidth, guildWndHeight);
			wnd->Move(0, 147);
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&guildWndInfo, 0, 0);
		}
		wnd->SetShow(1);
	break;
	case WID_GUILDINFOMANAGEWND:
//		wnd = m_guildInfoManageWnd;
		if( wnd == NULL )
		{
//			wnd = m_guildInfoManageWnd = new UIGuildInfoManageWnd();
			wnd->UIWindow::Create(guildWndWidth, guildWndHeight);
			wnd->Move(0, 147);
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&guildWndInfo, 0, 0);
		}
		wnd->SetShow(1);
	break;
	case WID_GUILDLEAVEREASONDESCWND:
//		wnd = m_guildLeaveReasonDescWnd;
		if( wnd == NULL )
		{
//			wnd = m_guildLeaveReasonDescWnd = new UIGuildLeaveReasonDescWnd();
			wnd->UIWindow::Create(280, 80);
			wnd->Move(UIX(200), UICY(120));
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_ILLUSTWND:
//		wnd = m_illustWnd;
		if( wnd != NULL )
		{
			wnd->SendMsg(NULL, 34, -1, 0, 0);
		}
		else
		{
//			wnd = m_illustWnd = new UIIllustWnd();
			wnd->UIWindow::Create(4, 4);
			wnd->Move(UIX(200), UICY(120));
			this->UIWindowMgr::AddWindowFront(wnd); //NOTE: check this
		}
		wnd->SetShow(1);
	break;
	case WID_GUILDBANREASONDESCWND:
//		wnd = m_guildBanReasonDescWnd;
		if( wnd == NULL )
		{
//			wnd = m_guildBanReasonDescWnd = new UIGuildBanReasonDescWnd();
			wnd->UIWindow::Create(280, 80);
			wnd->Move(UIX(200), UICY(120));
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_FRIENDOPTIONWND:
//		wnd = m_friendOptionWnd;
		if( wnd == NULL )
		{
//			wnd = m_friendOptionWnd = new UIFriendOptionWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(UIX(200), UICY(120));
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&friendOptionWndInfo, 0, 0);
		}
		wnd->SetShow(1);
	break;
*/
	case WID_PARTYSETTINGWND:
		wnd = m_partySettingWnd;
		if( wnd == NULL )
		{
			wnd = m_partySettingWnd = new UIPartySettingWnd();
			wnd->UIWindow::Create(280, 180);
			wnd->Move(UIX(200), UICY(120));
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&partySettingWndInfo, 0, 0);
		}
		wnd->SetShow(1);
	break;
/*
	case WID_COMPOSITIONWND:
//		wnd = m_compositionWnd;
		if( wnd == NULL )
		{
//			wnd = m_compositionWnd = new UICompositionWnd();
			wnd->UIWindow::Create(34, 34);
			wnd->Move(0, 0);
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_CANDIDATEWND:
//		wnd = m_candidateWnd;
		if( wnd == NULL )
		{
//			wnd = m_candidateWnd = new UICandidateWnd();
			if( m_conversionMode == 0 )
			{
				wnd->UIWindow::Create(292, 34);
				wnd->Move(g_renderer->CRenderer::GetWidth() - 292, g_renderer->CRenderer::GetHeight() - 34);
			}
			else
			{
				wnd->UIWindow::Create(120, 212);
				wnd->Move(g_renderer->CRenderer::GetWidth() - 120, g_renderer->CRenderer::GetHeight() - 212);
			}
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_TIPOFTHEDAYWND:
//		wnd = m_tipOfTheDayWnd;
		if( wnd == NULL )
		{
//			wnd = m_tipOfTheDayWnd = new UITipOfTheDayWnd();
			wnd->UIWindow::Create(280, 180);
			wnd->Move(UIX(200), UICY(120));
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_JOINGUILDACCEPTWND:
//		wnd = m_joinGuildAcceptWnd;
		if( wnd == NULL )
		{
//			wnd = m_joinGuildAcceptWnd = new UIJoinGuildAcceptWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(UIX(200), UICY(200));
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_ALLYGUILDACCEPTWND:
//		wnd = m_allyGuildAcceptWnd;
		if( wnd == NULL )
		{
//			wnd = m_allyGuildAcceptWnd = new UIAllyGuildAcceptWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(UIX(200), UICY(200));
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_JOINPARTYACCEPTWND:
//		wnd = m_joinPartyAcceptWnd;
		if( wnd == NULL )
		{
//			wnd = m_joinPartyAcceptWnd = new UIJoinPartyAcceptWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(UIX(200), UICY(200));
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_COUPLEACCEPTWND:
//		wnd = m_CoupleAcceptWnd;
		if( wnd == NULL )
		{
//			wnd = m_CoupleAcceptWnd = new UICoupleAcceptWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(UIX(200), UICY(200));
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_BABYACCEPTWND:
//		wnd = m_BabyAcceptWnd;
		if( wnd == NULL )
		{
//			wnd = m_BabyAcceptWnd = UIBabyAcceptWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(UIX(200), UICY(200));
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_EXCHANGEACCEPTWND:
//		wnd = m_exchangeAcceptWnd;
		if( wnd == NULL )
		{
//			wnd = m_exchangeAcceptWnd = new UIExchangeAcceptWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(UIX(200), UICY(200));
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&exchangeAcceptWndInfo, 0, 0);
		}
		wnd->SetShow(1);
	break;
	case WID_EXCHANGEWND:
//		wnd = m_exchangeWnd;
		if( wnd == NULL )
		{
//			wnd = m_exchangeWnd new UIExchangeWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(UIX(200), UICY(200));
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_PASSWORDWND:
//		wnd = m_passwordWnd;
		if( wnd == NULL )
		{
//			wnd = m_passwordWnd = new UIPasswordWnd();
			wnd->UIWindow::Create(176, 46);
			wnd->Move(UIX(200), UICY(200));
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
*/
	case WID_ITEMDROPCNTWND:
		wnd = m_itemDropCntWnd;
		if( wnd == NULL )
		{
			wnd = m_itemDropCntWnd = new UIItemDropCntWnd();
			wnd->UIWindow::Create(182, 46);
			wnd->Move(UIX(200), UICY(200));
			this->UIWindowMgr::AddWindow(wnd);
		}
	break;

	case WID_SAYDIALOGWND:
		wnd = m_sayDialogWnd;
		if( wnd == NULL )
		{
			wnd = m_sayDialogWnd = new UISayDialogWnd();
			wnd->UIWindow::Create(280, 180);
			wnd->Move(UIX(200), UICY(100));
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&sayDialogWndInfo, 0, 0);
		}
		wnd->SetShow(1);
	break;
/*
	case WID_CHATROOMWND:
//		wnd = m_chatRoomWnd;
		if( wnd == NULL )
		{
//			wnd = m_chatRoomWnd = new UIChatRoomWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(UIX(200), UICY(300));
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 53, (int)&chatRoomWndInfo, 0, 0);
		}
		wnd->SetShow(1);
	break;
	case WID_CHOOSEWARPWND:
//		wnd = m_chooseWarpWnd;
		if( wnd == NULL )
		{
//			wnd = m_chooseWarpWnd = new UIChooseWarpWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(UIX(200), UICY(300));
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_CHOOSEWND:
//		wnd = m_chooseWnd;
		if( wnd == NULL )
		{
//			wnd = m_chooseWnd = new UIChooseWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(UIX(200), UICY(300));
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&chooseWndInfo, 0, 0);
		}
		wnd->SetShow(1);
	break;
	case WID_ITEMCOMPOSITIONWND:
//		wnd = m_itemCompositionWnd;
		if( wnd == NULL )
		{
//			wnd = m_itemCompositionWnd = new UIItemCompositionWnd();
			wnd->UIWindow::Create(200, 200);
			wnd->Move(UIX(200), UICY(200));
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&itemCompositionWndInfo, 0, 0);
		}
		wnd->SetShow(1);
	break;
	case WID_ITEMIDENTIFYWND:
//		wnd = m_itemIdentifyWnd;
		if( wnd == NULL )
		{
//			wnd = m_itemIdentifyWnd = new UIItemIdentifyWnd();
			wnd->UIWindow::Create(200, 200);
			wnd->Move(UIX(200), UICY(200));
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&itemIdentifyWndInfo, 0, 0);
		}
		wnd->SetShow(1);
	break;
	case WID_COMBOBOXWND:
//		wnd = m_comboBoxWnd;
		if( wnd == NULL )
		{
//			wnd = m_comboBoxWnd = new UIComboBoxWnd();
			wnd->UIWindow::Create(16, 16);
			wnd->Move(UIX(200), UICY(300));
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
*/
	case WID_MENUWND:
		wnd = m_menu;
		if( wnd == NULL )
		{
			wnd = m_menu = new UIMenuWnd();
			wnd->UIWindow::Create(4, 4);
			wnd->Move(UIX(200), UICY(300));
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
/*
	case WID_OPTIONWND:
//		wnd = m_optionWnd;
		if( wnd == NULL )
		{
//			wnd = m_optionWnd = new UIOptionWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(UIX(185), UICY(300));
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&optionWndInfo, 0, 0);
			g_snapMgr.CSnapMgr::AddSnapObject(wnd);
		}
		wnd->SetShow(1);
		optionWndInfo.show = 1;
	break;
*/
	case WID_MINIMAPZOOMWND:
		wnd = m_minimapZoomWnd;
		if( wnd == NULL )
		{
			wnd = m_minimapZoomWnd = new UIMinimapZoomWnd();
			wnd->UIWindow::Create(12, 24);
			wnd->Move(g_renderer->CRenderer::GetWidth() - 29, 17);
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
/*
	case WID_CHATROOMCHANGEWND:
//		wnd = m_chatRoomChangeWnd;
		if( wnd == NULL )
		{
//			wnd = m_chatRoomChangeWnd = new UIChatRoomChangeWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(UIX(185), UICY(300));
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_CHATROOMMAKEWND:
//		wnd = m_chatRoomMakeWnd;
		if( wnd == NULL )
		{
//			wnd = m_chatRoomMakeWnd = new UIChatRoomMakeWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(UIX(185), UICY(300));
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_CHOOSESELLBUYWND:
//		wnd = m_chooseSellBuyWnd;
		if( wnd == NULL )
		{
//			wnd = m_chooseSellBuyWnd = new UIChooseSellBuyWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(UIX(185), UICY(300));
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_ITEMSELLWND:
//		wnd = m_itemSellWnd;
		if( wnd == NULL )
		{
//			wnd = m_itemSellWnd = new UIItemSellWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(300, 200);
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&itemSellWndInfo, 0, 0);
		}
		wnd->SetShow(1);
	break;
	case WID_MERCHANTITEMPURCHASEWND:
//		wnd = m_merchantItemPurchaseWnd;
		if( wnd == NULL )
		{
//			wnd = m_merchantItemPurchaseWnd = new UIMerchantItemPurchaseWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(300, 200);
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&merchantItemPurchaseWndInfo, 0, 0);
		}
		wnd->SetShow(1);
	break;
	case WID_ITEMPURCHASEWND:
//		wnd = m_itemPurchaseWnd;
		if( wnd == NULL )
		{
//			wnd = m_itemPurchaseWnd = new UIItemPurchaseWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(300, 200);
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&itemPurchaseWndInfo, 0, 0);
		}
		wnd->SetShow(1);
		this->UIWindowMgr::MakeWindow(WID_ITEMPARAMCHANGEDISPLAYWND);
	break;
	case WID_MERCHANTITEMMYSHOPWND:
//		wnd = m_merchantItemMyShopWnd;
		if( wnd == NULL )
		{
//			wnd = m_merchantItemMyShopWnd = new UIMerchantItemMyShopWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(0, 200);
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&merchantItemMyShopWndInfo, 0, 0);
		}
		wnd->SetShow(1);
	break;
	case WID_MERCHANTITEMSHOPWND:
//		wnd = m_merchantItemShopWnd;
		if( wnd == NULL )
		{
//			wnd = m_merchantItemShopWnd = new UIMerchantItemShopWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(0, 200);
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&merchantItemShopWndInfo, 0, 0);
		}
		wnd->SetShow(1);
	break;
	case WID_ITEMSHOPWND:
//		wnd = m_itemShopWnd;
		if( wnd == NULL )
		{
//			wnd = m_itemShopWnd = new UIItemShopWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(0, 200);
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&itemShopWndInfo, 0, 0);
		}
		wnd->SetShow(1);
	break;
	case WID_NOTIFYJOBLEVELUPWND:
//		wnd = m_notifyJobLevelUpWnd;
		if( wnd == NULL )
		{
//			wnd = m_notifyJobLevelUpWnd = new UINotifyJobLevelUpWnd();
			wnd->UIWindow::Create(43, 43);
			wnd->Move(0, g_renderer->CRenderer::GetHeight() - 43);
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_NOTIFYLEVELUPWND:
//		wnd = m_notifyLevelUpWnd;
		if( wnd == NULL )
		{
//			wnd = m_notifyLevelUpWnd = new UINotifyLevelUpWnd();
			wnd->UIWindow::Create(43, 43);
			wnd->Move(g_renderer->CRenderer::GetWidth() - 43, g_renderer->CRenderer::GetHeight() - 43);
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_CARDITEMILLUSTWND:
//		wnd = m_cardItemIllustWnd;
		if( wnd == NULL )
		{
//			wnd = m_cardItemIllustWnd = new UICardItemIllustWnd();
			wnd->UIWindow::Create(300, 417);
			wnd->Move(UIX(0), UICY(0));
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_RESTARTWND:
//		wnd = m_restartWnd;
		if( wnd == NULL )
		{
//			wnd = m_restartWnd = new UIRestartWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(UIX(185), UICY(300));
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
*/
	case WID_QUITWND:
		wnd = m_quitWnd;
		if( wnd == NULL )
		{
			wnd = m_quitWnd = new UIQuitWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(UIX(185), UICY(300));
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
/*
	case WID_SKILLDESCRIBEWND:
//		wnd = m_skillDescribeWnd;
		if( wnd == NULL )
		{
//			wnd = m_skillDescribeWnd = new UISkillDescribeWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(UIX(185), UICY(300) - 120);
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_ITEMPARAMCHANGEDISPLAYWND:
//		wnd = m_itemParamChangeDisplayWnd;
		if( wnd == NULL )
		{
//			wnd = m_itemParamChangeDisplayWnd = new UIItemParamChangeDisplayWnd();
			wnd->UIWindow::Create(280, 34);
			wnd->Move(UIX(185), UICY(300) - 34);
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&itemParamChangeDisplayWndInfo, 0, 0);
		}
		wnd->SetShow(1);
	break;
	case WID_COMBINEDCARDITEMCOLLECTIONWND:
//		wnd = m_combinedCardItemCollectionWnd;
		if( wnd == NULL )
		{
//			wnd = m_combinedCardItemCollectionWnd = new UICombinedCardItemCollectionWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(UIX(185), UICY(300));
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&combinedCardItemCollectionWndInfo, 0, 0);
		}
		wnd->SetShow(1);
	break;
*/
	case WID_ITEMCOLLECTIONWND:
		wnd = m_itemCollectionWnd;
		if( wnd == NULL )
		{
			wnd = m_itemCollectionWnd = new UIItemCollectionWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(UIX(185), UICY(300));
			this->UIWindowMgr::AddWindow(wnd);
			wnd->SendMsg(NULL, 34, (int)&itemCollectionWndInfo, 0, 0);
		}
		wnd->SetShow(1);
	break;
/*
	case WID_NOTICECONFIRMWND:
//		wnd = new UINoticeConfirmWnd();
		wnd->UIWindow::Create(280, 120);
		wnd->Move(UIX(185), UICY(300));
		this->UIWindowMgr::AddWindow(wnd);
	break;
	case WID_MONSTERINFOWND:
//		wnd = new UIMonsterInfoWnd();
		wnd->UIWindow::Create(400, 200);
		wnd->Move(0, 0);
		this->UIWindowMgr::AddWindow(wnd);
	break;
	case WID_MAKETARGETLISTWND:
//		wnd = m_metalListWnd;
		if( wnd == NULL )
		{
//			wnd = m_metalListWnd = new UIMakeTargetListWnd();
			wnd->UIWindow::Create(280, 150);
			wnd->Move(UIX(185), UICY(300) - 60);
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_MAKETARGETPROCESSWND:
//		wnd = m_metalProcessWnd;
		if( wnd == NULL )
		{
//			wnd = m_metalProcessWnd = new UIMakeTargetProcessWnd();
			wnd->UIWindow::Create(280, 150);
			wnd->Move(UIX(185), UICY(300) - 60);
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_MAKETARGETRESULTWND:
//		wnd = m_metalResultWnd;
		if( wnd == NULL )
		{
//			wnd = m_metalResultWnd = new UIMakeTargetResultWnd();
			wnd->UIWindow::Create(280, 120);
			wnd->Move(UIX(185), UICY(300) - 60);
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_TALKBOXTRAPINPUTWND:
//		wnd = new UITalkboxTrapInputWnd();
		wnd->UIWindow::Create(280, 120);
		wnd->Move(UIX(185), UICY(300) - 60);
		this->UIWindowMgr::AddWindow(wnd);
	break;
	case WID_KEYSTROKEWND:
//		wnd = m_keyStrokeWnd;
		if( wnd == NULL )
		{
//			wnd = m_keyStrokeWnd = new UIKeyStrokeWnd();
			wnd->UIWindow::Create(60, 18);
			wnd->Move(UIX(185), UICY(300) - 60);
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_EMOTIONWND:
//		wnd = m_emotionWnd;
		if( wnd == NULL )
		{
//			wnd = m_emotionWnd = new UIEmotionWnd();
			wnd->UIWindow::Create(375, 280);
			wnd->Move(UIX(185), UICY(300) - 60);
			wnd->SendMsg(NULL, 34, (int)&emotionWndInfo, 0, 0);
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_EMOTIONLISTWND:
//		wnd = m_emotionListWnd;
		if( wnd == NULL )
		{
//			wnd = m_emotionListWnd = new UIEmotionListWnd();
			wnd->UIWindow::Create(300, 300);
			wnd->Move(UIX(185), UICY(400) - 60);
			wnd->SendMsg(NULL, 34, (int)&emotionListWndInfo, 0, 0);
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_PETINFOWND:
		if( g_session.m_petJob == -1 )
			break;
//		wnd = m_petInfoWnd;
		if( wnd == NULL )
		{
//			wnd = m_petInfoWnd = new UIPetInfoWnd();
			wnd->UIWindow::Create(280, 160);
			wnd->Move(UIX(185), UICY(400) - 60);
			wnd->SendMsg(NULL, 34, (int)&petInfoWndInfo, 0, 0);
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_SELECTPETEGGWND:
//		wnd = m_selectPetEggWnd;
		if( wnd == NULL )
		{
//			wnd = m_selectPetEggWnd = new UIPetEggListWnd();
			wnd->UIWindow::Create(200, 200);
			wnd->Move(UIX(200), UICY(200));
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_PETTAMINGDECEIVEWND:
//		wnd = m_petTamingDeceiveWnd;
		if( wnd == NULL )
		{
//			wnd = m_petTamingDeceiveWnd = new UIPetTamingDeceiveWnd();
			wnd->UIWindow::Create(196, 256);
			wnd->Move(g_renderer->CRenderer::GetWidth() / 2 - 98, g_renderer->CRenderer::GetHeight() / 2 - 128);
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_MAKINGARROWLISTWND:
//		wnd = m_makingArrowListWnd;
		if( wnd == NULL )
		{
//			wnd = m_makingArrowListWnd = new UIMakingArrowListWnd();
			wnd->UIWindow::Create(200, 200);
			wnd->Move(UIX(200), UICY(200));
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_SELECTCARTWND:
//		wnd = m_selectCartWnd;
		if( wnd == NULL )
		{
//			wnd = m_selectCartWnd = new UISelectCartWnd();
			wnd->UIWindow::Create(372, 98);
			wnd->Move(UIX(200), UICY(200));
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_SPELLLISTWND:
//		wnd = m_spellListWnd;
		if( wnd == NULL )
		{
//			wnd = m_spellListWnd = new UISpellListWnd();
			wnd->UIWindow::Create(200, 200);
			wnd->Move(UIX(200), UICY(200));
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	case WID_GRAFFISTRBOXWND:
//		wnd = new UIGraffiStrboxWnd();
		wnd->UIWindow::Create(280, 120);
		wnd->Move(UIX(185), UICY(300) - 60);
		this->UIWindowMgr::AddWindow(wnd);
	break;
	case WID_SHOWNEEDITEMLISTWND:
//		wnd = m_showNeedItemListWnd;
		if( wnd == NULL )
		{
//			wnd = m_showNeedItemListWnd = new UIShowNeedItemListWnd();
			wnd->UIWindow::Create(200, 150);
			wnd->Move(UIX(200), UICY(200));
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
*/
	case WID_PROHIBITLISTWND:
		wnd = m_prohibitListWnd;
		if( wnd == NULL )
		{
			wnd = m_prohibitListWnd = new UIProhibitListWnd();
			wnd->UIWindow::Create(500, 400);
			wnd->Move(UIX(100), UICY(100));
			this->UIWindowMgr::AddWindow(wnd);
		}
		wnd->SetShow(1);
	break;
	default:
	break;
	}

	return wnd;
}


hook_method<UIWindow* (UIWindowMgr::*)(WINDOWID windowId)> UIWindowMgr::_QueryWindow(SAKEXE, "UIWindowMgr::QueryWindow");
UIWindow* UIWindowMgr::QueryWindow(WINDOWID windowId) // line 2099-2142
{
	return (this->*_QueryWindow)(windowId);

	//TODO
}


hook_method<bool (UIWindowMgr::*)(WINDOWID windowId)> UIWindowMgr::_DeleteWindow(SAKEXE, "UIWindowMgr::DeleteWindow");
bool UIWindowMgr::DeleteWindow(WINDOWID windowId) // line 2145-2860
{
	return (this->*_DeleteWindow)(windowId);

	//TODO
}


hook_method<bool (UIWindowMgr::*)(enum WINDOWID windowId, int show)> UIWindowMgr::_ShowWindow(SAKEXE, "UIWindowMgr::ShowWindow");
bool UIWindowMgr::ShowWindow(enum WINDOWID windowId, int show) // line 2863-2904
{
	return (this->*_ShowWindow)(windowId, show);

	//TODO
}


bool UIWindowMgr::IsModalStatus()
{
	return ( g_windowMgr.m_modalWindow != NULL );
}


hook_method<void (UIWindowMgr::*)(UIWindow* snapWindow)> UIWindowMgr::_UpdateSnapInfo(SAKEXE, "UIWindowMgr::UpdateSnapInfo");
void UIWindowMgr::UpdateSnapInfo(UIWindow* snapWindow) // line 91-93
{
	return (this->*_UpdateSnapInfo)(snapWindow);

	//TODO
}


hook_method<void (UIWindowMgr::*)(UIWindow* snapWindow, int& rdx, int& rdy, int mode)> UIWindowMgr::_GetDeltaSnap(SAKEXE, "UIWindowMgr::GetDeltaSnap");
void UIWindowMgr::GetDeltaSnap(UIWindow* snapWindow, int& rdx, int& rdy, int mode) // line 37-88
{
	return (this->*_GetDeltaSnap)(snapWindow, rdx, rdy, mode);

	//TODO
}


void UIWindowMgr::DeleteSnapInfo(UIWindow* window) // line 96-100
{
	mystd::map<UIWindow*,CSnapInfo>::iterator it = m_snapInfo.find(window);
	if( it == m_snapInfo.end() )
		return; // not found.

	m_snapInfo.erase(it);
}


void UIWindowMgr::SetSize(int cx, int cy) // line 233-238
{
	m_w = cx;
	m_h = cy;
	m_chatWndX = 0;
	m_chatWndY = cy - m_chatWndHeight;
}


bool UIWindowMgr::Drop(int dropX, int dropY, const DRAG_INFO* const dragInfo) // line 379-388
{
	for( mystd::list<UIWindow*>::reverse_iterator it = m_children.rbegin(); it != m_children.rend(); ++it )
	{
		UIWindow* wnd = (*it)->UIWindow::HitTest(dropX, dropY);
		if( wnd != NULL && wnd->UIWindow::IsShow() != FALSE )
		{
			int x, y;
			wnd->UIWindow::GetGlobalCoor(x, y); // inlined
			wnd->DragAndDrop(dropX - x, dropY - y, dragInfo);
			return true;
		}
	}

	return false;
}


UISayDialogWnd* UIWindowMgr::GetSayDialogWnd()
{
	return m_sayDialogWnd;
}


UIChooseWnd* UIWindowMgr::GetChooseWnd()
{
	return m_chooseWnd;
}


UIItemIdentifyWnd* UIWindowMgr::GetItemIdentifyWnd()
{
	return m_itemIdentifyWnd;
}


UIItemCompositionWnd* UIWindowMgr::GetItemCompositionWnd()
{
	return m_itemCompositionWnd;
}


UIStatusWnd* UIWindowMgr::GetStatusWnd()
{
	return m_statusWnd;
}


UIBasicInfoWnd* UIWindowMgr::GetBasicInfoWnd()
{
	return m_basicInfoWnd;
}


UIItemShopWnd* UIWindowMgr::GetItemShopWnd()
{
	return m_itemShopWnd;
}


UIItemPurchaseWnd* UIWindowMgr::GetItemPurchaseWnd()
{
	return m_itemPurchaseWnd;
}


UIItemSellWnd* UIWindowMgr::GetItemSellWnd()
{
	return m_itemSellWnd;
}


UIComboBoxWnd* UIWindowMgr::GetComboBoxWnd()
{
	return m_comboBoxWnd;
}


UIChatRoomWnd* UIWindowMgr::GetChatRoom() // line 1511 (Window/UISys.h)
{
	return m_chatRoomWnd;
}


UIExchangeWnd* UIWindowMgr::GetExchangeWnd() // line 1512 (Window/UISys.h)
{
	return m_exchangeWnd;
}


UIEquipWnd* UIWindowMgr::GetEquipWnd() // line 1513 (Window/UISys.h)
{
	return m_equipWnd;
}


UIChatWnd* UIWindowMgr::GetChatWnd()
{
	return m_chatWnd;
}


UIItemStoreWnd* UIWindowMgr::GetItemStoreWnd() // line 1515 (Window/UISys.h)
{
	return m_itemStoreWnd;
}


UISkillListWnd* UIWindowMgr::GetSkillListWnd()
{
	return m_skillListWnd;
}


UIItemWnd* UIWindowMgr::GetItemWnd() // line 1517 (Window/UISys.h)
{
	return m_itemWnd;
}


UIMessengerGroupWnd* UIWindowMgr::GetMessengerGroupWnd()
{
	return m_messengerGroupWnd;
}


UIMenuWnd* UIWindowMgr::GetMenu()
{
	return m_menu;
}


UIItemDropCntWnd* UIWindowMgr::GetItemDropCntWnd() // line 1520 (Window/UISys.h)
{
	return m_itemDropCntWnd;
}


UIMerchantItemWnd* UIWindowMgr::GetMerchantItemWnd()
{
	return m_merchantItemWnd;
}


UIMerchantShopMakeWnd* UIWindowMgr::GetMerchantShopMakeWnd()
{
	return m_merchantShopMakeWnd;
}


UIMerchantMirrorItemWnd* UIWindowMgr::GetMerchantMirrorItemWnd()
{
	return m_merchantMirrorItemWnd;
}


UIMerchantItemShopWnd* UIWindowMgr::GetMerchantItemShopWnd() // line 1524 (Window/UISys.h)
{
	return m_merchantItemShopWnd;
}


UIMerchantItemMyShopWnd* UIWindowMgr::GetMerchantItemMyShopWnd() // line 1525 (Window/UISys.h)
{
	return m_merchantItemMyShopWnd;
}


UIMerchantItemPurchaseWnd* UIWindowMgr::GetMerchantItemPurchaseWnd()
{
	return m_merchantItemPurchaseWnd;
}


UIShortCutWnd* UIWindowMgr::GetShortCutWnd()
{
	return m_shortCutWnd;
}


UIRestartWnd* UIWindowMgr::GetRestartWnd()
{
	return m_restartWnd;
}


UIOptionWnd* UIWindowMgr::GetOptionWnd()
{
	return m_optionWnd;
}

UIItemParamChangeDisplayWnd* UIWindowMgr::GetItemParamChangeDisplayWnd()
{
	return m_itemParamChangeDisplayWnd;
}


UICandidateWnd* UIWindowMgr::GetCandidateWnd()
{
	return m_candidateWnd;
}


UICompositionWnd* UIWindowMgr::GetCompositionWnd()
{
	return m_compositionWnd;
}


UIKeyStrokeWnd* UIWindowMgr::GetKeyStrokeWnd()
{
	return m_keyStrokeWnd;
}


UIPartySettingWnd* UIWindowMgr::GetPartySettingWnd()
{
	return m_partySettingWnd;
}


UIFriendOptionWnd* UIWindowMgr::GetFriendOptionWnd()
{
	return m_friendOptionWnd;
}


UIMakeTargetProcessWnd* UIWindowMgr::GetMakeTargetProcessWnd()
{
	return m_metalProcessWnd;
}


UIGuildInfoManageWnd* UIWindowMgr::GetGuildInfoManageWnd()
{
	return m_guildInfoManageWnd;
}


UIGuildMemberManageWnd* UIWindowMgr::GetGuildMemberManageWnd()
{
	return m_guildMemberManageWnd;
}


UIGuildPositionManageWnd* UIWindowMgr::GetGuildPositionManageWnd()
{
	return m_guildPositionManageWnd;
}


UIGuildSkillWnd* UIWindowMgr::GetGuildSkillWnd()
{
	return m_guildSkillWnd;
}


UIGuildBanishedMemberWnd* UIWindowMgr::GetGuildBanishedMemberWnd()
{
	return m_guildBanishedMemberWnd;
}


UIGuildNoticeWnd* UIWindowMgr::GetGuildNoticeWnd()
{
	return m_guildNoticeWnd;
}


UIGuildTotalInfoWnd* UIWindowMgr::GetGuildTotalInfoWnd()
{
	return m_guildTotalInfoWnd;
}


UIEmotionWnd* UIWindowMgr::GetEmotionWnd()
{
	return m_emotionWnd;
}


UIPetInfoWnd* UIWindowMgr::GetPetInfoWnd()
{
	return m_petInfoWnd;
}


UIPetTamingDeceiveWnd* UIWindowMgr::GetPetTamingDeceiveWnd()
{
	return m_petTamingDeceiveWnd;
}


UIMakingArrowListWnd* UIWindowMgr::GetMakingArrowListWnd()
{
	return m_makingArrowListWnd;
}


UISelectCartWnd* UIWindowMgr::GetSelectCartWnd()
{
	return m_selectCartWnd;
}


UIChatRoomWnd* UIWindowMgr::GetChatRoomWnd() // line 1557 (Window/UISys.h)
{
	return m_chatRoomWnd;
}


UIEmotionListWnd* UIWindowMgr::GetEmotionListWnd()
{
	return m_emotionListWnd;
}


UIChatRoomMakeWnd* UIWindowMgr::GetChatRoomMakeWnd()
{
	return m_chatRoomMakeWnd;
}


UIIllustWnd* UIWindowMgr::GetIllustWnd()
{
	return m_illustWnd;
}


UIWindow** UIWindowMgr::GetChatRoomWndPointer()
{
	return (UIWindow**)&m_chatRoomWnd;
}


UIWindow** UIWindowMgr::GetMessengerGroupWndPointer()
{
	return (UIWindow**)&m_messengerGroupWnd;
}


UIWindow** UIWindowMgr::GetSkillListWndPointer()
{
	return (UIWindow**)&m_skillListWnd;
}


UIWindow** UIWindowMgr::GetGuildMemberManageWndPointer()
{
	return (UIWindow**)&m_guildMemberManageWnd;
}


UIWindow** UIWindowMgr::GetWhisperListWndPointer()
{
	return (UIWindow**)&m_whisperListWnd;
}


UIWindow** UIWindowMgr::GetGuildInfoManageWndPointer()
{
	return (UIWindow**)&m_guildInfoManageWnd;
}


void UIWindowMgr::CreateDCA(int cx, int cy) // line 241-242
{
}


void UIWindowMgr::RemoveWindow(UIWindow* window) // line 268-281
{
	mystd::list<UIWindow*>::iterator it;
	for( it = m_children.begin(); it != m_children.end(); ++it )
		if( *it == window )
			break;

	if( it == m_children.end() )
		return; // not found.

	mystd::map<UIWindow*,CSnapInfo>::iterator itsnap = m_snapInfo.find(window);
	if( itsnap != m_snapInfo.end() )
		m_snapInfo.erase(itsnap);

	g_snapMgr.CSnapMgr::RemoveSnapObject(*it);
	(*it)->StoreInfo();
	delete *it;

	m_children.erase(it);
}


void UIWindowMgr::GetWindowPos(UIWindow* window, int* x, int* y) // line 949-960
{
	int cx = 0;
	int cy = 0;

	window->UIWindow::GetGlobalCoor(cx, cy); // inlined

	*x = cx;
	*y = cy;
}


void UIWindowMgr::AddWhisperWindow(mystd::string wName, UIWindow* whisperWindow) // line 5480-5485
{
	if( m_whisperNameWindow.find(wName) != m_whisperNameWindow.end() )
		return; // already exists.

	mystd::pair<mystd::map<mystd::string,UIWindow*>::iterator,bool> ib = m_whisperNameWindow.insert(mystd::pair<mystd::string,UIWindow*>(wName, NULL));
	ib.first->second = whisperWindow;
}


class hook_ptr<struct mystd::_Tree<class UIWindow *,struct mystd::pair<class UIWindow * const,class CSnapInfo>,struct mystd::map<class UIWindow *,class CSnapInfo,struct mystd::less<class UIWindow *>,class mystd::allocator<class CSnapInfo> >::_Kfn,struct mystd::less<class UIWindow *>,class mystd::allocator<class CSnapInfo> >::_Node *> mystd::_Tree<class UIWindow *,struct mystd::pair<class UIWindow * const,class CSnapInfo>,struct mystd::map<class UIWindow *,class CSnapInfo,struct mystd::less<class UIWindow *>,class mystd::allocator<class CSnapInfo> >::_Kfn,struct mystd::less<class UIWindow *>,class mystd::allocator<class CSnapInfo> >::_Nil(SAKEXE, "?_Nil@?$_Tree@PAVUIWindow@@U?$pair@QAVUIWindow@@VCSnapInfo@@@std@@U_Kfn@?$map@PAVUIWindow@@VCSnapInfo@@U?$less@PAVUIWindow@@@std@@V?$allocator@VCSnapInfo@@@4@@3@U?$less@PAVUIWindow@@@3@V?$allocator@VCSnapInfo@@@3@@std@@1PAU_Node@12@A");
class hook_val<unsigned int> mystd::_Tree<class UIWindow *,struct mystd::pair<class UIWindow * const,class CSnapInfo>,struct mystd::map<class UIWindow *,class CSnapInfo,struct mystd::less<class UIWindow *>,class mystd::allocator<class CSnapInfo> >::_Kfn,struct mystd::less<class UIWindow *>,class mystd::allocator<class CSnapInfo> >::_Nilrefs(SAKEXE, "?_Nilrefs@?$_Tree@PAVUIWindow@@U?$pair@QAVUIWindow@@VCSnapInfo@@@std@@U_Kfn@?$map@PAVUIWindow@@VCSnapInfo@@U?$less@PAVUIWindow@@@std@@V?$allocator@VCSnapInfo@@@4@@3@U?$less@PAVUIWindow@@@3@V?$allocator@VCSnapInfo@@@3@@std@@1IA");
class hook_ptr<struct mystd::_Tree<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,struct mystd::pair<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > const ,class UIWindow *>,struct mystd::map<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,class UIWindow *,struct mystd::less<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,class mystd::allocator<class UIWindow *> >::_Kfn,struct mystd::less<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,class mystd::allocator<class UIWindow *> >::_Node *> mystd::_Tree<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,struct mystd::pair<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > const ,class UIWindow *>,struct mystd::map<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,class UIWindow *,struct mystd::less<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,class mystd::allocator<class UIWindow *> >::_Kfn,struct mystd::less<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,class mystd::allocator<class UIWindow *> >::_Nil(SAKEXE, "?_Nil@?$_Tree@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAVUIWindow@@@2@U_Kfn@?$map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAVUIWi8e5c113c");
class hook_val<unsigned int> mystd::_Tree<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,struct mystd::pair<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > const ,class UIWindow *>,struct mystd::map<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,class UIWindow *,struct mystd::less<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,class mystd::allocator<class UIWindow *> >::_Kfn,struct mystd::less<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,class mystd::allocator<class UIWindow *> >::_Nilrefs(SAKEXE, "?_Nilrefs@?$_Tree@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAVUIWindow@@@2@U_Kfn@?$map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAV71d33f46");
