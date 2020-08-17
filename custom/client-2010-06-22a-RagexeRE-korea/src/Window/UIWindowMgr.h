#pragma once
#include "Window/UISys.h"
#include "std/list"
class CBitmapRes;
class CSurface;
class UIAuctionWnd;
class UIBasicInfoWnd;
class UIExchangeWnd;
class UIFrameWnd;
class UIItemStoreWnd;
class UIMailListWnd;
class UIMenuWnd;
class UIMailViewWnd;
class UIRoMapWnd;
class UIShortCutWnd;
class UIWindow;
enum WINDOWID;


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
	WID_8_ITEMWND                     = 8,
	WID_9                             = 9,
	WID_EQUIPWND                      = 10,
	WID_STATUSWND                     = 11,
	WID_ITEMCOLLECTIONWND             = 12,
	WID_13_OPTIONWND                  = 13,
	WID_MINIMAPZOOMWND                = 14,
	WID_15                            = 15,
	WID_SAYDIALOGWND                  = 16,
	WID_CHOOSEWND                     = 17,
	WID_MENUWND                       = 18,
	WID_19                            = 19,
	WID_20                            = 20,
	WID_NOTIFYLEVELUPWND              = 21,
	WID_ITEMSHOPWND                   = 22,
	WID_ITEMPURCHASEWND               = 23,
	WID_ITEMSELLWND                   = 24,
	WID_CHOOSESELLBUYWND              = 25,
	WID_COMBOBOXWND                   = 26,
	WID_CHATROOMMAKEWND               = 27,
	WID_CHATROOMWND                   = 28,
	WID_29                            = 29,
	WID_CHATROOMCHANGEWND             = 30,
	WID_EXCHANGEWND                   = 31,
	WID_EXCHANGEACCEPTWND             = 32,
	WID_ITEMSTOREWND                  = 33,
	WID_MESSENGERGROUPWND             = 34,
	WID_JOINPARTYACCEPTWND            = 35,
	WID_SHORTCUTWND                   = 36,
	WID_SKILLLISTWND                  = 37,
	WID_38_TIPOFTHEDAYWND             = 38,
	WID_CHOOSEWARPWND                 = 39,
	WID_MERCHANTITEMWND               = 40,
	WID_MERCHANTSHOPMAKEWND           = 41,
	WID_MERCHANTMIRRORITEMWND         = 42,
	WID_MERCHANTITEMSHOPWND           = 43,
	WID_MERCHANTITEMPURCHASEWND       = 44,
	WID_MERCHANTITEMMYSHOPWND         = 45,
	WID_46                            = 46,
	WID_47                            = 47,
	WID_48                            = 48,
	WID_NOTIFYJOBLEVELUPWND           = 49,
	WID_50                            = 50,
	WID_51                            = 51,
	WID_52                            = 52,
	WID_PARTYSETTINGWND               = 53,
	WID_54                            = 54,
	WID_55                            = 55,
	WID_NPCEDITDIALOGWND              = 56,
	WID_DETAILLEVELWND                = 57,
	WID_58                            = 58,
	WID_GUILDWND                      = 59,
	WID_GUILDINFOMANAGEWND            = 60,
	WID_GUILDMEMBERMANAGEWND          = 61,
	WID_GUILDPOSITIONMANAGEWND        = 62,
	WID_GUILDSKILLWND                 = 63,
	WID_GUILDBANISHEDMEMBERWND        = 64,
	WID_GUILDNOTICEWND                = 65,
	WID_GUILDTOTALINFOWND             = 66,
	WID_67                            = 67,
	WID_68                            = 68,
	WID_69_MESSENGERWND               = 69,
	WID_JOINGUILDACCEPTWND            = 70,
	WID_71                            = 71,
	WID_ALLYGUILDACCEPTWND            = 72,
	WID_ITEMIDENTIFYWND               = 73,
	WID_ITEMCOMPOSITIONWND            = 74,
	WID_75                            = 75,
	WID_76                            = 76,
	WID_MONSTERINFOWND                = 77,
	WID_ILLUSTWND                     = 78,
	WID_MAKETARGETLISTWND             = 79,
	WID_80                            = 80,
	WID_81                            = 81,
	WID_82                            = 82,
	WID_83                            = 83,
	WID_84                            = 84,
	WID_85                            = 85,
	WID_B6_EMOTIONWND                 = 86,
	WID_87_EMOTIONLISTWND             = 87,
	WID_88_PETINFOWND                 = 88,
	WID_89                            = 89,
	WID_SELECTPETEGGWND               = 90,
	WID_91                            = 91,
	WID_92                            = 92,
	WID_NOTICEWND                     = 93,
	WID_MAKINGARROWLISTWND            = 94,
	WID_95                            = 95,
	WID_96                            = 96,
	WID_97                            = 97,
	WID_98                            = 98,
	WID_SPELLLISTWND                  = 99,
	WID_NPCTEXTEDITDIALOGWND          = 100,
	WID_101                           = 101,
	WID_102                           = 102,
	WID_PROHIBITLISTWND               = 103,
	WID_COUPLEACCEPTWND               = 104,
	WID_BABYACCEPTWND                 = 105,
	WID_106                           = 106,
	WID_ITEMREPAIRWND                 = 107,
	WID_108                           = 108,
	WID_JOINFRIENDACCEPTWND           = 109,
	WID_110                           = 110,
	WID_WEAPONREFINEWND               = 111,
	WID_112                           = 112,
	WID_HOMUNINFOWND                  = 113,
	WID_HOMUNSKILLLISTWND             = 114,
	WID_115                           = 115,
	WID_116                           = 116,
	WID_MAILLISTWND                   = 117,
	WID_MAILVIEWWND                   = 118,
	WID_STARPLACE_ACCEPTWND           = 119,
	WID_AUCTIONWND                    = 120,
	WID_121                           = 121,
	WID_122                           = 122,
	WID_123                           = 123,
	WID_124                           = 124,
	WID_125_MERINFOWND                = 125,
	WID_126                           = 126,
	WID_127                           = 127,
	WID_128                           = 128,
	WID_129                           = 129,
	WID_SUBCHATWND_ST                 = 130,
	WID_SUBCHATWND_BT                 = 131,
	WID_132                           = 132,
	WID_133                           = 133,
	WID_134_QUESTWND                  = 134,
	WID_135_QUEST_DETAIL_WND          = 135,
	WID_136                           = 136,
	WID_MEMORIAL_DUN_WND              = 137,
	WID_138                           = 138,
	WID_139                           = 139,
	WID_140                           = 140,
	WID_141                           = 141,
	WID_142                           = 142,
	WID_143                           = 143,
	WID_144                           = 144,
	WID_145                           = 145,
	WID_146                           = 146,
	WID_147                           = 147,
	WID_148                           = 148,
	WID_149                           = 149,
	WID_150                           = 150,
	WID_151                           = 151,
	WID_152                           = 152,
	WID_153                           = 153,
	WID_154                           = 154,
	WID_155                           = 155,
	WID_HOTKEYWND                     = 156,
	WID_JOINTO_BATTLEFIELDWND         = 157,
	WID_RELOADLUASCRIPTWND            = 158,
	WID_QUIKSLOTWND                   = 159,
	WID_160                           = 160,
	WID_161                           = 161,
	WID_162                           = 162,
	WID_163                           = 163,
	WID_164                           = 164,
	WID_BATTLEFIELD_DESCRIBEWND       = 165,
	WID_BATTLEFIELD_STATUSWND         = 166,
	WID_BATTLEFIELD_HELPWND           = 167,
	WID_168                           = 168,
	WID_169                           = 169,
	WID_170                           = 170,
	WID_171                           = 171,
	WID_172                           = 172,
	WID_173                           = 173,
	WID_174                           = 174,
	WID_175                           = 175,
	WID_176                           = 176,
	WID_177                           = 177,
	WID_178                           = 178,
	WID_179                           = 179,
	WID_180                           = 180,
	WID_SEARCH_STORE_INFO             = 181,
	WID_BUTTONS_OF_BASICWND           = 182,
	WID_SHOWINFO_TESTLAYER            = 183,
};


class UIWindowMgr
{
public:
	/* this+   0 */ BYTE dummy_0[28];
	/* this+  28 */ mystd::list<WINDOWID> m_WindowEscList;
	/* this+  40 */ UIID m_LastClickedUIID;
	/* this+  44 */ BYTE dummy_44[320];
	/* this+ 364 */ DWORD field_16C;
	/* this+ 368 */ DWORD field_170;
	/* this+ 372 */ BYTE dummy_174[4];
	/* this+ 376 */ mystd::list<UIWindow*> m_children;
	/* this+ 388 */ BYTE dummy_388[40];
	/* this+ 428 */ UIWindow* m_captureWindow;
	/* this+ 432 */ BYTE dummy_432[4];
	/* this+ 436 */ UIWindow* m_modalWindow;
	/* this+ 440 */ BYTE dummy_1B8[32];
	/* this+ 472 */ UIBasicInfoWnd* m_basicInfoWnd;
	/* this+ 476 */ BYTE dummy_1DC[8];
	/* this+ 484 */ UIShortCutWnd* m_shortCutWnd;
	/* this+ 488 */ BYTE dummy_1E8[32];
	/* this+ 520 */ UIMenuWnd* m_menu;
	/* this+ 524 */ BYTE dummy_20C[88];
	/* this+ 612 */ UIExchangeWnd* m_exchangeWnd;
	/* this+ 616 */ BYTE dummy_268[4];
	/* this+ 620 */ UIItemStoreWnd* m_itemStoreWnd;
	/* this+ 624 */ BYTE dummy_270[284];
	/* this+ 908 */ UIMailListWnd* m_mailListWnd;
	/* this+ 912 */ UIMailViewWnd* m_mailViewWnd;
	/* this+ 916 */ UIAuctionWnd* m_auctionWnd;
	/* this+ 920 */ BYTE dummy_398[40];
	/* this+ 960 */ bool m_chatWndStickOn;
	/* this+ 961 */ bool m_onStSubChat;
	/* this+ 962 */ bool m_onBtSubChat;
	/* this+ 963 */ BYTE gap_963[1];
	/* this+ 964 */ BYTE dummy_964[8];
	/* this+ 972 */ UIRoMapWnd* m_roMapWnd;
	/* this+ 976 */ BYTE dummy_976[40];
	/* this+1016 */ int m_modalResult;
	/* this+1020 */ CSurface* m_wallpaperSurface;
	/* this+1024 */ int m_w;
	/* this+1028 */ int m_h;
	/* this+1032 */ BYTE dummy_408[88];
	/* this+1120 */ mystd::string m_chatMsg;
	/* this+1136 */ BYTE dummy_1136[12];
	/* this+1148 */ mystd::map<mystd::string,UIWindow*> m_whisperNameWindow;
	/* this+1164 */ //TODO

	public: void UIWindowMgr::DestroyDC(void);
	public: void UIWindowMgr::AddWindow(UIWindow* window);
	public: void UIWindowMgr::AddWindowFront(UIWindow* window);
	public: int UIWindowMgr::ProcessInput(void);
	public: void UIWindowMgr::OnProcess(void);
	public: bool UIWindowMgr::ProcessPushButton(unsigned long virtualKey, int a2, int a3);
	public: UIFrameWnd* UIWindowMgr::MakeWindow(WINDOWID windowId);
	UIWindow* QueryWindow(WINDOWID windowId);
	public: bool UIWindowMgr::DeleteWindow(WINDOWID windowId);
	public: bool UIWindowMgr::ShowWindow(WINDOWID windowId, int show);
	public: bool UIWindowMgr::IsModalStatus(void); /// @inlined
	public: UIBasicInfoWnd* UIWindowMgr::GetBasicInfoWnd(void);
	public: void UIWindowMgr::SetSize(int cx, int cy);
	public: void UIWindowMgr::InitUIRectInfoFromReg(void);
	public: void UIWindowMgr::WriteUIRectInfoToReg(void);
	public: void UIWindowMgr::RemoveAllWindows(void);
	public: void UIWindowMgr::RemoveAllWindowsExceptChatWnd(void);
	public: void UIWindowMgr::RemoveFromNameWaitingWindowList(UIWindow* wnd);
	public: void UIWindowMgr::SetWallpaper(CBitmapRes* bitmap);
	public: int UIWindowMgr::ErrorMsg(const char* msg, int type, int isDefYes, int changeMsg, unsigned int autoReturnTime, const char* a7);
	public: int UIWindowMgr::SendMsg(int message, int val1, int val2, int val3, int val4);
	public: void UIWindowMgr::PostQuit(UIWindow* wnd);
	BOOL AddWhisperChatToWhisperWnd(const char* cName, const char* chatMsg, COLORREF color);
	void AddWhisperCharName(const char* whisperCharName);
	void GetDeltaSnap(UIWindow* snapWindow, int& rdx, int& rdy, int mode);
	void UpdateSnapInfo(UIWindow* snapWindow);
	UIWindow* GetCapture();
	void SetCapture(UIWindow* window);
	void ReleaseCapture();
	bool IsNoEscWindow(WINDOWID windowId); //TODO
	void AddToEscList(WINDOWID windowId); //TODO
	void RemoveFromEscList(WINDOWID windowId); //TODO

public:
	static hook_func<void (UIWindowMgr::*)(void)> UIWindowMgr::_DestroyDC;
	static hook_func<int (UIWindowMgr::*)(void)> UIWindowMgr::_ProcessInput;
	static hook_func<void (UIWindowMgr::*)(void)> UIWindowMgr::_OnProcess;
	static hook_func<bool (UIWindowMgr::*)(unsigned long virtualKey, int a2, int a3)> UIWindowMgr::_ProcessPushButton;
	static hook_func<UIFrameWnd* (UIWindowMgr::*)(WINDOWID windowId)> UIWindowMgr::_MakeWindow;
	static hook_func<UIWindow* (UIWindowMgr::*)(WINDOWID windowId)> UIWindowMgr::_QueryWindow;
	static hook_func<bool (UIWindowMgr::*)(WINDOWID windowId)> UIWindowMgr::_DeleteWindow;
	static hook_func<bool (UIWindowMgr::*)(WINDOWID windowId, int show)> UIWindowMgr::_ShowWindow;
	static hook_func<bool (UIWindowMgr::*)(void)> UIWindowMgr::_IsModalStatus;
	static hook_func<UIBasicInfoWnd* (UIWindowMgr::*)(void)> UIWindowMgr::_GetBasicInfoWnd;
	static hook_func<void (UIWindowMgr::*)(int cx, int cy)> UIWindowMgr::_SetSize;
	static hook_func<void (UIWindowMgr::*)(void)> UIWindowMgr::_InitUIRectInfoFromReg;
	static hook_func<void (UIWindowMgr::*)(void)> UIWindowMgr::_WriteUIRectInfoToReg;
	static hook_func<void (UIWindowMgr::*)(void)> UIWindowMgr::_RemoveAllWindows;
	static hook_func<void (UIWindowMgr::*)(void)> UIWindowMgr::_RemoveAllWindowsExceptChatWnd;
	static hook_func<void (UIWindowMgr::*)(UIWindow* wnd)> UIWindowMgr::_RemoveFromNameWaitingWindowList;
	static hook_func<void (UIWindowMgr::*)(CBitmapRes* bitmap)> UIWindowMgr::_SetWallpaper;
	static hook_func<int (UIWindowMgr::*)(const char* msg, int type, int isDefYes, int changeMsg, unsigned int autoReturnTime, const char* a7)> UIWindowMgr::_ErrorMsg;
	static hook_func<int (UIWindowMgr::*)(int message, int val1, int val2, int val3, int val4)> UIWindowMgr::_SendMsg;
	static hook_func<void (UIWindowMgr::*)(UIWindow* wnd)> UIWindowMgr::_PostQuit;
	static hook_func<void (UIWindowMgr::*)(const char* whisperCharName)> UIWindowMgr::_AddWhisperCharName;
	static hook_func<void (UIWindowMgr::*)(UIWindow* snapWindow, int& rdx, int& rdy, int mode)> UIWindowMgr::_GetDeltaSnap;
	static hook_func<void (UIWindowMgr::*)(UIWindow* snapWindow)> UIWindowMgr::_UpdateSnapInfo;
};
C_ASSERT( sizeof UIWindowMgr == 1164 ); //TODO


extern UIWindowMgr& g_windowMgr;
