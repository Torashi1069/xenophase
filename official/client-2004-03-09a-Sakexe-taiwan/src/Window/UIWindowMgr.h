#pragma once
#include "Enum.h"
#include "Struct.h"
#include "3dLib/Texture.h"
#include "Resource/Bitmap.h"
#include "Window/UIFrameWnd.h"
#include "Window/UISys.h"
class UILoadingWnd;
class UIMinimapZoomWnd;
class UIStatusWnd;
class UIChatWnd;
class UIItemWnd;
class UIBasicInfoWnd;
class UIEquipWnd;
class UIOptionWnd;
class UIShortCutWnd;
class UIItemDropCntWnd;
class UISayDialogWnd;
class UIChooseWnd;
class UIItemIdentifyWnd;
class UIItemCompositionWnd;
class UIChooseWarpWnd;
class UIMenuWnd;
class UIComboBoxWnd;
class UIItemCollectionWnd;
class UICombinedCardItemCollectionWnd;
class UIItemParamChangeDisplayWnd;
class UISkillDescribeWnd;
class UIQuitWnd;
class UIRestartWnd;
class UICardItemIllustWnd;
class UINotifyLevelUpWnd;
class UINotifyJobLevelUpWnd;
class UIItemShopWnd;
class UIItemPurchaseWnd;
class UIItemSellWnd;
class UIChooseSellBuyWnd;
class UIChatRoomMakeWnd;
class UIChatRoomChangeWnd;
class UIChatRoomWnd;
class UIPasswordWnd;
class UIExchangeWnd;
class UIExchangeAcceptWnd;
class UIItemStoreWnd;
class UISkillListWnd;
class UIMessengerGroupWnd;
class UIJoinPartyAcceptWnd;
class UICoupleAcceptWnd;
class UIBabyAcceptWnd;
class UIJoinGuildAcceptWnd;
class UIAllyGuildAcceptWnd;
class UITipOfTheDayWnd;
class UIMerchantItemWnd;
class UIMerchantMirrorItemWnd;
class UIMerchantShopMakeWnd;
class UIMerchantItemShopWnd;
class UIMerchantItemMyShopWnd;
class UIMerchantItemPurchaseWnd;
class UIPartySettingWnd;
class UISkillNameChangeWnd;
class UINpcEditDialogWnd;
class UINpcTextEditDialogWnd;
class UIDetailLevelWnd;
class UINotifyItemObtainWnd;
class UIGuildInfoManageWnd;
class UIGuildMemberManageWnd;
class UIGuildPositionManageWnd;
class UIGuildSkillWnd;
class UIGuildBanishedMemberWnd;
class UIGuildNoticeWnd;
class UIGuildTotalInfoWnd;
class UIWhisperListWnd;
class UIFriendOptionWnd;
class UIGuildLeaveReasonDescWnd;
class UIGuildBanReasonDescWnd;
class UIIllustWnd;
class UIMakeTargetListWnd;
class UIMakeTargetProcessWnd;
class UIMakeTargetResultWnd;
class UIEmotionWnd;
class UIEmotionListWnd;
class UIProhibitListWnd;
class UIPetInfoWnd;
class UIPetEggListWnd;
class UIPetTamingDeceiveWnd;
class UIMakingArrowListWnd;
class UISelectCartWnd;
class UISpellListWnd;
class UIShowNeedItemListWnd;
class UICandidateWnd;
class UICompositionWnd;
class UIKeyStrokeWnd;


/// @see UIWindowMgr::SendMsg()
enum UIMGRMESSAGE
{
	UIM_CREATESTATUSWND                   = 0,
	UIM_PUSHINTOCHATHISTORY               = 1,
	UIM_CHANGECHATWNDSTATUS               = 2,
	UIM_OPENCHATWND                       = 3,
	UIM_LOADINGPERCENT                    = 4,
	UIM_PUSH_INTO_CHATROOM                = 5,
	UIM_SAVE_CHAT_TO_FILE                 = 6,
	UIM_SAVE_CHAT_TO_FILE_FROM_CHATROOM   = 7,
	UIM_IME_OPENCANDIDATE                 = 8,
	UIM_IME_CHANGECANDIDATE               = 9,
	UIM_IME_CLOSECANDIDATE                = 10,
	UIM_IME_STARTCOMPOSITION              = 11,
	UIM_IME_COMPSTR                       = 12,
	UIM_IME_ENDCOMPOSITION                = 13,
	UIM_MAKE_WHISPER_WINDOW               = 14,
	UIM_CURSOR_CHANGE_ACTION              = 15,
	UIM_CURSOR_CHANGE_MOTION              = 16,
	UIM_REPORT_CHAT_TO_FILE               = 17,
	UIM_REPORT_CHAT_TO_FILE_FROM_CHATROOM = 18,
	UIM_CLOSE_GRON_MESSENGER              = 19,
	UIM_PUSHINTOCHATHISTORY2              = 20,
};


/// @see UIWindowMgr::MakeWindow()
enum WINDOWID
{
	WID_BASICINFOWND                  = 0,
	WID_CHATWND                       = 1,
	WID_SELECTSERVERWND               = 2,
	WID_LOGINWND                      = 3,
	WID_MAKECHARWND                   = 4,
	WID_SELECTCHARWND                 = 5,
	WID_WAITWND                       = 6,
	WID_LOADINGWND                    = 7,
	WID_ITEMWND                       = 8,
	WID_TOOLTIPWND                    = 9,
	WID_EQUIPWND                      = 10,
	WID_STATUSWND                     = 11,
	WID_ITEMCOLLECTIONWND             = 12,
	WID_OPTIONWND                     = 13,
	WID_MINIMAPZOOMWND                = 14,
	WID_ITEMDROPCNTWND                = 15,
	WID_SAYDIALOGWND                  = 16,
	WID_CHOOSEWND                     = 17,
	WID_MENUWND                       = 18,
	WID_RESTARTWND                    = 19,
	WID_NOTICECONFIRMWND              = 20,
	WID_NOTIFYLEVELUPWND              = 21,
	WID_ITEMSHOPWND                   = 22,
	WID_ITEMPURCHASEWND               = 23,
	WID_ITEMSELLWND                   = 24,
	WID_CHOOSESELLBUYWND              = 25,
	WID_COMBOBOXWND                   = 26,
	WID_CHATROOMMAKEWND               = 27,
	WID_CHATROOMWND                   = 28,
	WID_PASSWORDWND                   = 29,
	WID_CHATROOMCHANGEWND             = 30,
	WID_EXCHANGEWND                   = 31,
	WID_EXCHANGEACCEPTWND             = 32,
	WID_ITEMSTOREWND                  = 33,
	WID_MESSENGERGROUPWND             = 34,
	WID_JOINPARTYACCEPTWND            = 35,
	WID_SHORTCUTWND                   = 36,
	WID_SKILLLISTWND                  = 37,
	WID_TIPOFTHEDAYWND                = 38,
	WID_CHOOSEWARPWND                 = 39,
	WID_MERCHANTITEMWND               = 40,
	WID_MERCHANTSHOPMAKEWND           = 41,
	WID_MERCHANTMIRRORITEMWND         = 42,
	WID_MERCHANTITEMSHOPWND           = 43,
	WID_MERCHANTITEMPURCHASEWND       = 44,
	WID_MERCHANTITEMMYSHOPWND         = 45,
	WID_SKILLDESCRIBEWND              = 46,
	WID_CARDITEMILLUSTWND             = 47,
	WID_QUITWND                       = 48,
	WID_NOTIFYJOBLEVELUPWND           = 49,
	WID_ITEMPARAMCHANGEDISPLAYWND     = 50,
	WID_CANDIDATEWND                  = 51,
	WID_COMPOSITIONWND                = 52,
	WID_PARTYSETTINGWND               = 53,
	WID_EMAILADDRESSWND               = 54,
	WID_SKILLNAMECHANGEWND            = 55,
	WID_NPCEDITDIALOGWND              = 56,
	WID_DETAILLEVELWND                = 57,
	WID_NOTIFYITEMOBTAINWND           = 58,
	WID_GUILDWND                      = 59,
	WID_GUILDINFOMANAGEWND            = 60,
	WID_GUILDMEMBERMANAGEWND          = 61,
	WID_GUILDPOSITIONMANAGEWND        = 62,
	WID_GUILDSKILLWND                 = 63,
	WID_GUILDBANISHEDMEMBERWND        = 64,
	WID_GUILDNOTICEWND                = 65,
	WID_GUILDTOTALINFOWND             = 66,
	WID_WHISPERLISTWND                = 67,
	WID_FRIENDOPTIONWND               = 68,
	WID_MESSENGERWND                  = 69,
	WID_JOINGUILDACCEPTWND            = 70,
	WID_WEBBROWSERWND                 = 71,
	WID_ALLYGUILDACCEPTWND            = 72,
	WID_ITEMIDENTIFYWND               = 73,
	WID_ITEMCOMPOSITIONWND            = 74,
	WID_GUILDLEAVEREASONDESCWND       = 75,
	WID_GUILDBANREASONDESCWND         = 76,
	WID_MONSTERINFOWND                = 77,
	WID_ILLUSTWND                     = 78,
	WID_MAKETARGETLISTWND             = 79,
	WID_MAKETARGETPROCESSWND          = 80,
	WID_MAKETARGETRESULTWND           = 81,
	WID_COMBINEDCARDITEMCOLLECTIONWND = 82,
	WID_CALCULATORWND                 = 83,
	WID_TALKBOXTRAPINPUTWND           = 84,
	WID_KEYSTROKEWND                  = 85,
	WID_EMOTIONWND                    = 86,
	WID_EMOTIONLISTWND                = 87,
	WID_PETINFOWND                    = 88,
	WID_TOPRANKWND                    = 89,
	WID_SELECTPETEGGWND               = 90,
	WID_PETTAMINGDECEIVEWND           = 91,
	WID_CNTWND                        = 92,
	WID_NOTICEWND                     = 93,
	WID_MAKINGARROWLISTWND            = 94,
	WID_SELECTCARTWND                 = 95,
	WID_MINIGAMEWND                   = 96,
	WID_SELECTMINIGAMEWND             = 97,
	WID_MINIGAMESCOREWND              = 98,
	WID_SPELLLISTWND                  = 99,
	WID_NPCTEXTEDITDIALOGWND          = 100,
	WID_GRAFFISTRBOXWND               = 101,
	WID_SHOWNEEDITEMLISTWND           = 102,
	WID_PROHIBITLISTWND               = 103,
	WID_COUPLEACCEPTWND               = 104,
	WID_BABYACCEPTWND                 = 105,
	WID_LAST                          = 106,
};


class UIWindowMgr
{
public:
	UIWindowMgr();
	virtual ~UIWindowMgr();
	void ClearDC(COLORREF color);
	void DestroyDC();
	void AddWindow(UIWindow* window);
	void AddWindowFront(UIWindow* window);
	void RemoveAllWindows();
	void RemoveAllWindowsExceptChatWnd();
	void ClearAllWindowState();
	void HideChatWnd();
	int ProcessInput();
	void MakeTopLayer(UIWindow* window);
	void InvalidateUpdateNeededUI();
	void InvalidateAll();
	void InvalidateGuildWnd();
	public: void UIWindowMgr::OnProcess();
	void Render();
	//public: void UIWindowMgr::FinishEdit();
	public: void UIWindowMgr::SetFocusEdit(UIWindow* wnd);
	//public: void UIWindowMgr::SetFocusEditNext();
	//public: void UIWindowMgr::SetFocusEditPrev();
	//public: void UIWindowMgr::SetFocusEditFirst();
	//public: void UIWindowMgr::SetFocusEditLast();
	//public: unsigned char UIWindowMgr::IsFirstFocusEdit(class UIWindow *);
	//public: unsigned char UIWindowMgr::IsLastFocusEdit(class UIWindow *);
	public: UIWindow* UIWindowMgr::GetFocusEdit();
	public: void UIWindowMgr::SetCapture(UIWindow* window);
	public: UIWindow* UIWindowMgr::GetCapture();
	public: void UIWindowMgr::ReleaseCapture();
	//public: class UIWindow* UIWindowMgr::HitTest(int, int);
	public: void UIWindowMgr::PostQuit(UIWindow* wnd);
	//public: int UIWindowMgr::DoModal(class UIWindow *);
	public: int UIWindowMgr::ErrorMsg(const char* msg, int type, int isDefYes, int changeMsg, unsigned long autoReturnTime);
	//public: int MGScoreMsg(unsigned long, int, int, int, unsigned long);
	//public: int UIWindowMgr::ErrorMsgAutoreturn(const char *, unsigned long);
	//public: int UIWindowMgr::EmailAddress();
	public: void UIWindowMgr::DeleteWhisperWindow(mystd::string wName);
	public: void UIWindowMgr::AddToNameWaitingWindowList(UIWindow* wnd);
	public: void UIWindowMgr::RemoveFromNameWaitingWindowList(UIWindow* wnd);
	public: void UIWindowMgr::RefreshNameWaitingWindowList();
	//public: void SetModalResult(int);
	public: bool UIWindowMgr::ProcessPushButton(unsigned long virtualKey, int newKeydown);
	//public: void UIWindowMgr::DefPushButton();
	//public: void UIWindowMgr::CancelPushButton();
	//public: void UIWindowMgr::ToggleButton(int);
	//public: void UIWindowMgr::PageUpButton();
	//public: void UIWindowMgr::PageDownButton();
	//public: void UIWindowMgr::UpButton();
	//public: void UIWindowMgr::DownButton();
	//public: void UIWindowMgr::LeftButton();
	//public: void UIWindowMgr::RightButton();
	//public: void UIWindowMgr::DeleteButton();
	public: void UIWindowMgr::RefreshItem();
	public: void UIWindowMgr::MakeWndPointerNull();
	public: void UIWindowMgr::AddWhisperCharName(const char* whisperCharName);
	public: void UIWindowMgr::AddFriendCharName(const char* friendCharName);
	public: void UIWindowMgr::DeleteFriendName(mystd::string whisperName);
	public: BOOL UIWindowMgr::AddWhisperChatToWhisperWnd(const char* cName, const char* chatMsg, COLORREF color);
	public: void UIWindowMgr::WriteWhisperChatToFile(const char* cName);
	public: bool UIWindowMgr::ExcuteMsgInBattleMode(unsigned long virtualKey, int newKeydown);
	public: void UIWindowMgr::SetTextAtBattleMode();
	public: void UIWindowMgr::SetWallpaper(CBitmapRes* bitmap);
	//public: void DrawBitmap(int, int, class CBitmapRes *);
	public: void UIWindowMgr::DrawBitmapToFrame(int x, int y, CBitmapRes* bitmap);
	//public: int GetWallpaperLeft();
	//public: int GetWallpaperTop();
	public: void UIWindowMgr::SetChatMsg(const char* msg);
	public: void UIWindowMgr::ClearChatMsg();
	public: const char* UIWindowMgr::GetChatMsg();
	//public: void UIWindowMgr::ProcessShortcutMessage(int);
	//public: void UIWindowMgr::StoreChatWndStatus();
	//public: void UIWindowMgr::RestoreChatWndStatus();
	public: void UIWindowMgr::InitFriendNameListFromRegistry();
	public: void UIWindowMgr::InitShortcutItemInfoFromReg();
	public: void UIWindowMgr::InitUIRectInfoFromReg();
	public: void UIWindowMgr::WriteUIRectInfoToReg();
	public: void UIWindowMgr::WriteShorcutItemInfoToReg();
	public: void UIWindowMgr::InitSkillUseLevelInfoFromReg();
	public: void UIWindowMgr::WriteSkillUseLevelInfoToReg();
	public: void UIWindowMgr::WriteFriendNameListToRegistry();
	//public: void UIWindowMgr::MakeDefaultUIRectInfo();
	//public: void UIWindowMgr::EditFocusToChatWnd();
	//public: void UIWindowMgr::FindFocusEditAndSetFocus();
	//public: mystd::vector<mystd::string>& UIWindowMgr::GetFriendCharNameList();
	BOOL IsFriendName(const char* cName);
	int SendMsg(int message, int val1, int val2, int val3);
	UIFrameWnd* MakeWindow(WINDOWID windowId);
	UIWindow* QueryWindow(WINDOWID windowId);
	bool DeleteWindow(WINDOWID windowId);
	bool ShowWindow(WINDOWID windowId, int show);
	bool IsModalStatus();
	void UpdateSnapInfo(UIWindow* snapWindow);
	void GetDeltaSnap(UIWindow* snapWindow, int& rdx, int& rdy, int mode);
	void DeleteSnapInfo(UIWindow* window);
//	int GetHeight();
//	int GetWidth();
	void SetSize(int cx, int cy);
	bool Drop(int dropX, int dropY, const DRAG_INFO* const dragInfo);
//	bool IsMinimapVisible();
public:
	UISayDialogWnd* GetSayDialogWnd();
	UIChooseWnd* GetChooseWnd();
	UIItemIdentifyWnd* GetItemIdentifyWnd();
	UIItemCompositionWnd* GetItemCompositionWnd();
	UIStatusWnd* GetStatusWnd();
	UIBasicInfoWnd* GetBasicInfoWnd();
	UIItemShopWnd* GetItemShopWnd();
	UIItemPurchaseWnd* GetItemPurchaseWnd();
	UIItemSellWnd* GetItemSellWnd();
	UIComboBoxWnd* GetComboBoxWnd();
	UIChatRoomWnd* GetChatRoom();
	UIExchangeWnd* GetExchangeWnd();
	UIEquipWnd* GetEquipWnd();
	UIChatWnd* GetChatWnd();
	UIItemStoreWnd* GetItemStoreWnd();
	UISkillListWnd* GetSkillListWnd();
	UIItemWnd* GetItemWnd();
	UIMessengerGroupWnd* GetMessengerGroupWnd();
	UIMenuWnd* GetMenu();
	UIItemDropCntWnd* GetItemDropCntWnd();
	UIMerchantItemWnd* GetMerchantItemWnd();
	UIMerchantShopMakeWnd* GetMerchantShopMakeWnd();
	UIMerchantMirrorItemWnd* GetMerchantMirrorItemWnd();
	UIMerchantItemShopWnd* GetMerchantItemShopWnd();
	UIMerchantItemMyShopWnd* GetMerchantItemMyShopWnd();
	UIMerchantItemPurchaseWnd* GetMerchantItemPurchaseWnd();
	UIShortCutWnd* GetShortCutWnd();
	UIRestartWnd* GetRestartWnd();
	UIOptionWnd* GetOptionWnd();
	UIItemParamChangeDisplayWnd* GetItemParamChangeDisplayWnd();
	UICandidateWnd* GetCandidateWnd();
	UICompositionWnd* GetCompositionWnd();
	UIKeyStrokeWnd* GetKeyStrokeWnd();
	UIPartySettingWnd* GetPartySettingWnd();
	UIFriendOptionWnd* GetFriendOptionWnd();
	UIMakeTargetProcessWnd* GetMakeTargetProcessWnd();
	UIGuildInfoManageWnd* GetGuildInfoManageWnd();
	UIGuildMemberManageWnd* GetGuildMemberManageWnd();
	UIGuildPositionManageWnd* GetGuildPositionManageWnd();
	UIGuildSkillWnd* GetGuildSkillWnd();
	UIGuildBanishedMemberWnd* GetGuildBanishedMemberWnd();
	UIGuildNoticeWnd* GetGuildNoticeWnd();
	UIGuildTotalInfoWnd* GetGuildTotalInfoWnd();
	UIEmotionWnd* GetEmotionWnd();
	UIPetInfoWnd* GetPetInfoWnd();
	UIPetTamingDeceiveWnd* GetPetTamingDeceiveWnd();
	UIMakingArrowListWnd* GetMakingArrowListWnd();
	UISelectCartWnd* GetSelectCartWnd();
	UIChatRoomWnd* GetChatRoomWnd();
	UIEmotionListWnd* GetEmotionListWnd();
	UIChatRoomMakeWnd* GetChatRoomMakeWnd();
	UIIllustWnd* GetIllustWnd();

	UIWindow** GetChatRoomWndPointer();
	UIWindow** GetMessengerGroupWndPointer();
	UIWindow** GetSkillListWndPointer();
	UIWindow** GetGuildMemberManageWndPointer();
	UIWindow** GetWhisperListWndPointer();
	UIWindow** GetGuildInfoManageWndPointer();

private:
	void CreateDCA(int cx, int cy);
	void RemoveWindow(UIWindow* window);
	void GetWindowPos(UIWindow* window, int* x, int* y);
	void AddWhisperWindow(mystd::string wName, UIWindow* whisperWindow);

public:
	/* this+   0 */ //const UIWindowMgr::`vftable';
	/* this+   4 */ int m_chatWndX;
	/* this+   8 */ int m_chatWndY;
	/* this+  12 */ int m_chatWndHeight;
	/* this+  16 */ int m_chatWndShow;
	/* this+  20 */ int m_chatWndStatus;
	/* this+  24 */ float m_miniMapZoomFactor;
	/* this+  28 */ unsigned long m_miniMapArgb;
	/* this+  32 */ int m_isDrawCompass;
	/* this+  36 */ int m_isDragAll;
	/* this+  40 */ int m_conversionMode;
private:
	/* this+  44 */ mystd::list<UIWindow*> m_children;
	/* this+  56 */ mystd::list<UIWindow*> m_quitWindow;
	/* this+  68 */ mystd::list<UIWindow*> m_nameWaitingList;
	/* this+  80 */ mystd::map<UIWindow*, CSnapInfo> m_snapInfo;
	/* this+  96 */ UIWindow* m_captureWindow;
	/* this+ 100 */ UIWindow* m_editWindow;
	/* this+ 104 */ UIWindow* m_modalWindow;
	/* this+ 108 */ UIWindow* m_lastHitWindow;
	/* this+ 112 */ UILoadingWnd* m_loadingWnd;
	/* this+ 116 */ UIMinimapZoomWnd* m_minimapZoomWnd;
	/* this+ 120 */ UIStatusWnd* m_statusWnd;
	/* this+ 124 */ UIChatWnd* m_chatWnd;
	/* this+ 128 */ UIItemWnd* m_itemWnd;
	/* this+ 132 */ UIBasicInfoWnd* m_basicInfoWnd;
	/* this+ 136 */ UIEquipWnd* m_equipWnd;
	/* this+ 140 */ UIOptionWnd* m_optionWnd;
	/* this+ 144 */ UIShortCutWnd* m_shortCutWnd;
	/* this+ 148 */ UIItemDropCntWnd* m_itemDropCntWnd;
	/* this+ 152 */ UISayDialogWnd* m_sayDialogWnd;
	/* this+ 156 */ UIChooseWnd* m_chooseWnd;
	/* this+ 160 */ UIItemIdentifyWnd* m_itemIdentifyWnd;
	/* this+ 164 */ UIItemCompositionWnd* m_itemCompositionWnd;
	/* this+ 168 */ UIChooseWarpWnd* m_chooseWarpWnd;
	/* this+ 172 */ UIMenuWnd* m_menu;
	/* this+ 176 */ UIComboBoxWnd* m_comboBoxWnd;
	/* this+ 180 */ UIItemCollectionWnd* m_itemCollectionWnd;
	/* this+ 184 */ UICombinedCardItemCollectionWnd* m_combinedCardItemCollectionWnd;
	/* this+ 188 */ UIItemParamChangeDisplayWnd* m_itemParamChangeDisplayWnd;
	/* this+ 192 */ UISkillDescribeWnd* m_skillDescribeWnd;
	/* this+ 196 */ UIQuitWnd* m_quitWnd;
	/* this+ 200 */ UIRestartWnd* m_restartWnd;
	/* this+ 204 */ UICardItemIllustWnd* m_cardItemIllustWnd;
	/* this+ 208 */ UINotifyLevelUpWnd* m_notifyLevelUpWnd;
	/* this+ 212 */ UINotifyJobLevelUpWnd* m_notifyJobLevelUpWnd;
	/* this+ 216 */ UIItemShopWnd* m_itemShopWnd;
	/* this+ 220 */ UIItemPurchaseWnd* m_itemPurchaseWnd;
	/* this+ 224 */ UIItemSellWnd* m_itemSellWnd;
	/* this+ 228 */ UIChooseSellBuyWnd* m_chooseSellBuyWnd;
	/* this+ 232 */ UIChatRoomMakeWnd* m_chatRoomMakeWnd;
	/* this+ 236 */ UIChatRoomChangeWnd* m_chatRoomChangeWnd;
	/* this+ 240 */ UIChatRoomWnd* m_chatRoomWnd;
	/* this+ 244 */ UIPasswordWnd* m_passwordWnd;
	/* this+ 248 */ UIExchangeWnd* m_exchangeWnd;
	/* this+ 252 */ UIExchangeAcceptWnd* m_exchangeAcceptWnd;
	/* this+ 256 */ UIItemStoreWnd* m_itemStoreWnd;
	/* this+ 260 */ UISkillListWnd* m_skillListWnd;
	/* this+ 264 */ UIMessengerGroupWnd* m_messengerGroupWnd;
	/* this+ 268 */ UIJoinPartyAcceptWnd* m_joinPartyAcceptWnd;
	/* this+ 272 */ UICoupleAcceptWnd* m_CoupleAcceptWnd;
	/* this+ 276 */ UIBabyAcceptWnd* m_BabyAcceptWnd;
	/* this+ 280 */ UIJoinGuildAcceptWnd* m_joinGuildAcceptWnd;
	/* this+ 284 */ UIAllyGuildAcceptWnd* m_allyGuildAcceptWnd;
	/* this+ 288 */ UITipOfTheDayWnd* m_tipOfTheDayWnd;
	/* this+ 292 */ UIMerchantItemWnd* m_merchantItemWnd;
	/* this+ 296 */ UIMerchantMirrorItemWnd* m_merchantMirrorItemWnd;
	/* this+ 300 */ UIMerchantShopMakeWnd* m_merchantShopMakeWnd;
	/* this+ 304 */ UIMerchantItemShopWnd* m_merchantItemShopWnd;
	/* this+ 308 */ UIMerchantItemMyShopWnd* m_merchantItemMyShopWnd;
	/* this+ 312 */ UIMerchantItemPurchaseWnd* m_merchantItemPurchaseWnd;
	/* this+ 316 */ UIPartySettingWnd* m_partySettingWnd;
	/* this+ 320 */ UISkillNameChangeWnd* m_skillNameChangeWnd;
	/* this+ 324 */ UINpcEditDialogWnd* m_npcEditDialogWnd;
	/* this+ 328 */ UINpcTextEditDialogWnd* m_npcTextEditDialogWnd;
	/* this+ 332 */ UIDetailLevelWnd* m_detailLevelWnd;
	/* this+ 336 */ UINotifyItemObtainWnd* m_notifyItemObtainWnd;
	/* this+ 340 */ UIGuildInfoManageWnd* m_guildInfoManageWnd;
	/* this+ 344 */ UIGuildMemberManageWnd* m_guildMemberManageWnd;
	/* this+ 348 */ UIGuildPositionManageWnd* m_guildPositionManageWnd;
	/* this+ 352 */ UIGuildSkillWnd* m_guildSkillWnd;
	/* this+ 356 */ UIGuildBanishedMemberWnd* m_guildBanishedMemberWnd;
	/* this+ 360 */ UIGuildNoticeWnd* m_guildNoticeWnd;
	/* this+ 364 */ UIGuildTotalInfoWnd* m_guildTotalInfoWnd;
	/* this+ 368 */ UIWhisperListWnd* m_whisperListWnd;
	/* this+ 372 */ UIFriendOptionWnd* m_friendOptionWnd;
	/* this+ 376 */ UIGuildLeaveReasonDescWnd* m_guildLeaveReasonDescWnd;
	/* this+ 380 */ UIGuildBanReasonDescWnd* m_guildBanReasonDescWnd;
	/* this+ 384 */ UIIllustWnd* m_illustWnd;
	/* this+ 388 */ UIMakeTargetListWnd* m_metalListWnd;
	/* this+ 392 */ UIMakeTargetProcessWnd* m_metalProcessWnd;
	/* this+ 396 */ UIMakeTargetResultWnd* m_metalResultWnd;
	/* this+ 400 */ UIEmotionWnd* m_emotionWnd;
	/* this+ 404 */ UIEmotionListWnd* m_emotionListWnd;
	/* this+ 408 */ UIProhibitListWnd* m_prohibitListWnd;
	/* this+ 412 */ UIPetInfoWnd* m_petInfoWnd;
	/* this+ 416 */ UIPetEggListWnd* m_selectPetEggWnd;
	/* this+ 420 */ UIPetTamingDeceiveWnd* m_petTamingDeceiveWnd;
	/* this+ 424 */ UIMakingArrowListWnd* m_makingArrowListWnd;
	/* this+ 428 */ UISelectCartWnd* m_selectCartWnd;
	/* this+ 432 */ UISpellListWnd* m_spellListWnd;
	/* this+ 436 */ UIShowNeedItemListWnd* m_showNeedItemListWnd;
	/* this+ 440 */ UICandidateWnd* m_candidateWnd;
	/* this+ 444 */ UICompositionWnd* m_compositionWnd;
	/* this+ 448 */ UIKeyStrokeWnd* m_keyStrokeWnd;
	/* this+ 452 */ int m_lastMouseX;
	/* this+ 456 */ int m_lastMouseY;
	/* this+ 460 */ int m_modalResult;
	/* this+ 464 */ CSurface* m_wallpaperSurface;
	/* this+ 468 */ int m_w;
	/* this+ 472 */ int m_h;
	/* this+ 476 */ mystd::string m_wallPaperBmpName;
	/* this+ 492 */ mystd::list<StringAndColor> m_chatWndHistory;
	/* this+ 504 */ mystd::list<mystd::string> m_chatWndMyTalk;
	/* this+ 516 */ mystd::list<mystd::string> m_chatWndWhisper;
	/* this+ 528 */ mystd::string m_chatMsg;
	/* this+ 544 */ int m_chatWndCurHis;
	/* this+ 548 */ int m_chatWndWhisperCurHis;
	/* this+ 552 */ BOOL m_isInvalidatedByForce;
	/* this+ 556 */ mystd::map<mystd::string,UIWindow*> m_whisperNameWindow;
	/* this+ 572 */ mystd::vector<mystd::string> m_friendNames;
	/* this+ 588 */ BasicInfoWndInfo basicInfoWndInfo;
	/* this+ 604 */ ItemWndInfo itemWndInfo;
	/* this+ 644 */ StatusWndInfo statusWndInfo;
	/* this+ 668 */ EquipWndInfo equipWndInfo;
	/* this+ 692 */ OptionWndInfo optionWndInfo;
	/* this+ 716 */ ShortenItemWndInfo shortenItemWndInfo;
	/* this+ 736 */ ShortenSkillWndInfo shortenSkillWndInfo;
	/* this+ 752 */ SayDialogWndInfo sayDialogWndInfo;
	/* this+ 768 */ ChooseWndInfo chooseWndInfo;
	/* this+ 784 */ ChatRoomWndInfo chatRoomWndInfo;
	/* this+ 800 */ ItemStoreWndInfo itemStoreWndInfo;
	/* this+ 816 */ ItemShopWndInfo itemShopWndInfo;
	/* this+ 832 */ ItemSellWndInfo itemSellWndInfo;
	/* this+ 848 */ ItemPurchaseWndInfo itemPurchaseWndInfo;
	/* this+ 864 */ MessengerGroupWndInfo messengerGroupWndInfo;
	/* this+ 888 */ ShortCutWndInfo shortCutWndInfo;
	/* this+ 908 */ ExchangeAcceptWndInfo exchangeAcceptWndInfo;
	/* this+ 924 */ SkillListWndInfo skillListWndInfo;
	/* this+ 944 */ MerchantItemWndInfo merchantItemWndInfo;
	/* this+ 964 */ MerchantMirrorItemWndInfo merchantMirrorItemWndInfo;
	/* this+ 980 */ MerchantShopMakeWndInfo merchantShopMakeWndInfo;
	/* this+ 996 */ MerchantItemShopWndInfo merchantItemShopWndInfo;
	/* this+1012 */ MerchantItemMyShopWndInfo merchantItemMyShopWndInfo;
	/* this+1028 */ MerchantItemPurchaseWndInfo merchantItemPurchaseWndInfo;
	/* this+1044 */ ItemCollectionWndInfo itemCollectionWndInfo;
	/* this+1060 */ CombinedCardItemCollectionWndInfo combinedCardItemCollectionWndInfo;
	/* this+1076 */ ItemParamChangeDisplayWndInfo itemParamChangeDisplayWndInfo;
	/* this+1092 */ PartySettingWndInfo partySettingWndInfo;
	/* this+1108 */ DetailLevelWndInfo detailLevelWndInfo;
	/* this+1124 */ GuildWndInfo guildWndInfo;
	/* this+1144 */ WhisperWndInfo whisperWndInfo;
	/* this+1160 */ WhisperListWndInfo whisperListWndInfo;
	/* this+1180 */ FriendOptionWndInfo friendOptionWndInfo;
	/* this+1196 */ ItemCompositionWndInfo itemCompositionWndInfo;
	/* this+1212 */ ItemIdentifyWndInfo itemIdentifyWndInfo;
	/* this+1228 */ EmotionWndInfo emotionWndInfo;
	/* this+1244 */ EmotionListWndInfo emotionListWndInfo;
	/* this+1260 */ PetInfoWndInfo petInfoWndInfo;

private:
	static hook_method<int (UIWindowMgr::*)()> UIWindowMgr::_ProcessInput;
	static hook_method<void (UIWindowMgr::*)()> UIWindowMgr::_OnProcess;
	static hook_method<void (UIWindowMgr::*)(UIWindow* wnd)> UIWindowMgr::_SetFocusEdit;
	static hook_method<UIWindow* (UIWindowMgr::*)()> UIWindowMgr::_GetFocusEdit;
	static hook_method<void (UIWindowMgr::*)(UIWindow* window)> UIWindowMgr::_SetCapture;
	static hook_method<UIWindow* (UIWindowMgr::*)()> UIWindowMgr::_GetCapture;
	static hook_method<void (UIWindowMgr::*)()> UIWindowMgr::_ReleaseCapture;
	static hook_method<void (UIWindowMgr::*)(UIWindow* wnd)> UIWindowMgr::_PostQuit;
	static hook_method<int (UIWindowMgr::*)(const char* msg, int type, int isDefYes, int changeMsg, unsigned long autoReturnTime)> UIWindowMgr::_ErrorMsg;
	static hook_method<void (UIWindowMgr::*)(mystd::string wName)> UIWindowMgr::_DeleteWhisperWindow;
	static hook_method<void (UIWindowMgr::*)(UIWindow* wnd)> UIWindowMgr::_AddToNameWaitingWindowList;
	static hook_method<void (UIWindowMgr::*)(UIWindow* wnd)> UIWindowMgr::_RemoveFromNameWaitingWindowList;
	static hook_method<void (UIWindowMgr::*)()> UIWindowMgr::_RefreshNameWaitingWindowList;
	static hook_method<bool (UIWindowMgr::*)(unsigned long virtualKey, int newKeydown)> UIWindowMgr::_ProcessPushButton;
	static hook_method<void (UIWindowMgr::*)()> UIWindowMgr::_RefreshItem;
	static hook_method<void (UIWindowMgr::*)()> UIWindowMgr::_MakeWndPointerNull;
	static hook_method<void (UIWindowMgr::*)(mystd::string whisperName)> UIWindowMgr::_DeleteFriendName;
	static hook_method<void (UIWindowMgr::*)(const char* cName)> UIWindowMgr::_WriteWhisperChatToFile;
	static hook_method<bool (UIWindowMgr::*)(unsigned long virtualKey, int newKeydown)> UIWindowMgr::_ExcuteMsgInBattleMode;
	static hook_method<void (UIWindowMgr::*)()> UIWindowMgr::_SetTextAtBattleMode;
	static hook_method<void (UIWindowMgr::*)(CBitmapRes* bitmap)> UIWindowMgr::_SetWallpaper;
	static hook_method<void (UIWindowMgr::*)(int x, int y, CBitmapRes* bitmap)> UIWindowMgr::_DrawBitmapToFrame;
	static hook_method<void (UIWindowMgr::*)(const char* msg)> UIWindowMgr::_SetChatMsg;
	static hook_method<void (UIWindowMgr::*)()> UIWindowMgr::_ClearChatMsg;
	static hook_method<const char* (UIWindowMgr::*)()> UIWindowMgr::_GetChatMsg;
	static hook_method<void (UIWindowMgr::*)()> UIWindowMgr::_InitFriendNameListFromRegistry;
	static hook_method<void (UIWindowMgr::*)()> UIWindowMgr::_InitShortcutItemInfoFromReg;
	static hook_method<void (UIWindowMgr::*)()> UIWindowMgr::_InitUIRectInfoFromReg;
	static hook_method<void (UIWindowMgr::*)()> UIWindowMgr::_WriteUIRectInfoToReg;
	static hook_method<void (UIWindowMgr::*)()> UIWindowMgr::_WriteShorcutItemInfoToReg;
	static hook_method<void (UIWindowMgr::*)()> UIWindowMgr::_InitSkillUseLevelInfoFromReg;
	static hook_method<void (UIWindowMgr::*)()> UIWindowMgr::_WriteSkillUseLevelInfoToReg;
	static hook_method<void (UIWindowMgr::*)()> UIWindowMgr::_WriteFriendNameListToRegistry;

	static hook_method<UIFrameWnd* (UIWindowMgr::*)(WINDOWID windowId)> UIWindowMgr::_MakeWindow;
	static hook_method<UIWindow* (UIWindowMgr::*)(WINDOWID windowId)> UIWindowMgr::_QueryWindow;
	static hook_method<bool (UIWindowMgr::*)(WINDOWID windowId)> UIWindowMgr::_DeleteWindow;
	static hook_method<bool (UIWindowMgr::*)(WINDOWID windowId, int show)> UIWindowMgr::_ShowWindow;
	static hook_method<void (UIWindowMgr::*)(UIWindow* snapWindow)> UIWindowMgr::_UpdateSnapInfo;
	static hook_method<void (UIWindowMgr::*)(UIWindow* snapWindow, int& rdx, int& rdy, int mode)> UIWindowMgr::_GetDeltaSnap;
};
