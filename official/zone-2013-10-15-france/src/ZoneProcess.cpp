#include "AgitMapRes.h"
#include "CDisconnectLog.h"
#include "CharacterMgr.h"
#include "CProcessMgr.h"
#include "CThreadAffinityMgr.h"
#include "CZoneProcessConfigMgr.h"
#include "CZoneProcessLocalConfigMgr.h"
#include "CZsvrSchedulerIdentity.h"
#include "Enum.h"
#include "GlobalVarDB.h"
#include "GVar.h"
#include "ISvrIOPacketHandler.h"
#include "ItemLog.h"
#include "MapResMgr.h"
#include "NNetworkMgr.h"
#include "ObjectRecycleMgr.h"
#include "Path.h"
#include "TestButton.h"
#include "ZGuildInfoDB.h"
#include "ZGuildMgr.h"
#include "ZoneProcess.h"
#include "ZoneProcessStuff.h"
#include "ZSAcceptHandler.h"
#include "Client/CharacterServerClient/C2CharacterServerClient.h"
#include "Client/InterServerClient/C2InterServerClient.h"
#include "shared/CProgrammerSupportLog.h"
#include "shared/MyMiniDumpUnhandledExceptionHandler.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/NOutputTextMgr.h"
#include "shared/NTraceLog.h"
#include "shared/ServerInfo.h"
#include "shared/shared.h"
#include "shared/N3System/N3DataTransferMgr.h"
#include "shared/N3System/N3MessageMgr.h"


/// singleton instances //TODO
CObjectRecycleMgr<class CNpcElemental>*& CObjectRecycleMgr<CNpcElemental>::m_cpSelf = VTOR<CObjectRecycleMgr<CNpcElemental>*>(DetourFindFunction(EXEPATH(), "CObjectRecycleMgr<CNpcElemental>::m_cpSelf"));


/// globals
CBuffInfoMgr& g_buffInfoMgr = VTOR<CBuffInfoMgr>(DetourFindFunction(EXEPATH(), "g_buffInfoMgr"));
CMercenaryLog& g_MercenaryLog = VTOR<CMercenaryLog>(DetourFindFunction(EXEPATH(), "g_MercenaryLog"));
CScriptEventMgr& g_scriptEventMgr = VTOR<CScriptEventMgr>(DetourFindFunction(EXEPATH(), "g_scriptEventMgr"));
CMapResMgr& g_mapResMgr = VTOR<CMapResMgr>(DetourFindFunction(EXEPATH(), "g_mapResMgr"));
CZSAcceptHandler& g_zsAcceptHandler = VTOR<CZSAcceptHandler>(DetourFindFunction(EXEPATH(), "g_zsAcceptHandler"));
CFSMMgr& g_fsmMgr = VTOR<CFSMMgr>(DetourFindFunction(EXEPATH(), "g_fsmMgr"));
CRoomMgr& g_roomMgr = VTOR<CRoomMgr>(DetourFindFunction(EXEPATH(), "g_roomMgr"));
CLog& g_errorLog = VTOR<CLog>(DetourFindFunction(EXEPATH(), "g_errorLog"));
CMonParameterMgr& g_monParameter = VTOR<CMonParameterMgr>(DetourFindFunction(EXEPATH(), "g_monParameter"));
CMVPInfo& g_mvpInfo = VTOR<CMVPInfo>(DetourFindFunction(EXEPATH(), "g_mvpInfo"));
CITPMgr& g_itpMgr = VTOR<CITPMgr>(DetourFindFunction(EXEPATH(), "g_itpMgr"));
CExpParameter& g_expParameter = VTOR<CExpParameter>(DetourFindFunction(EXEPATH(), "g_expParameter"));
CCharInfoDB& g_charInfoDB = VTOR<CCharInfoDB>(DetourFindFunction(EXEPATH(), "g_charInfoDB"));
CPCSkillDB& g_pcSkillDB = VTOR<CPCSkillDB>(DetourFindFunction(EXEPATH(), "g_pcSkillDB"));
CMerceDB& g_merceDB = VTOR<CMerceDB>(DetourFindFunction(EXEPATH(), "g_merceDB"));
CStatusPlusInfoByJLV& g_StatusPlusnfoByJLV = VTOR<CStatusPlusInfoByJLV>(DetourFindFunction(EXEPATH(), "g_StatusPlusnfoByJLV"));
CZoneScript& g_zoneScript = VTOR<CZoneScript>(DetourFindFunction(EXEPATH(), "g_zoneScript"));
CItemList& g_metalItemList = VTOR<CItemList>(DetourFindFunction(EXEPATH(), "g_metalItemList"));
CItemList& g_weaponItemList = VTOR<CItemList>(DetourFindFunction(EXEPATH(), "g_weaponItemList"));
CItemList& g_potionItemList = VTOR<CItemList>(DetourFindFunction(EXEPATH(), "g_potionItemList"));
CZGuildMgr& g_ZGuildMgr = VTOR<CZGuildMgr>(DetourFindFunction(EXEPATH(), "g_ZGuildMgr"));
CZGuildInfoDB& g_ZGuildDB = VTOR<CZGuildInfoDB>(DetourFindFunction(EXEPATH(), "g_ZGuildDB"));
CPvPScoreDB& g_pvpScoreDB = VTOR<CPvPScoreDB>(DetourFindFunction(EXEPATH(), "g_pvpScoreDB"));
CAgitDB& g_AgitDB = VTOR<CAgitDB>(DetourFindFunction(EXEPATH(), "g_AgitDB"));
CImportantItem& g_importantItem = VTOR<CImportantItem>(DetourFindFunction(EXEPATH(), "g_importantItem"));
CStackDumpLog& g_stackdumpLog = VTOR<CStackDumpLog>(DetourFindFunction(EXEPATH(), "g_stackdumpLog"));
CQuestEventMgr& g_questEventMgr = VTOR<CQuestEventMgr>(DetourFindFunction(EXEPATH(), "g_questEventMgr"));
CQuestArlimi& g_questArlimi = VTOR<CQuestArlimi>(DetourFindFunction(EXEPATH(), "g_questArlimi"));
CTestButton& ToggleButtonCriticalLog = VTOR<CTestButton>(DetourFindFunction(EXEPATH(), "ToggleButtonCriticalLog")); // = CTestButton((HMENU)20);
CTestButton& ToggleButtonTraceLog = VTOR<CTestButton>(DetourFindFunction(EXEPATH(), "ToggleButtonTraceLog")); // = CTestButton((HMENU)21);
CTestButton& ToggleButtonKillZone = VTOR<CTestButton>(DetourFindFunction(EXEPATH(), "ToggleButtonKillZone")); // = CTestButton((HMENU)25);
CTestButton& ToggleButtonDisconnectLog = VTOR<CTestButton>(DetourFindFunction(EXEPATH(), "ToggleButtonDisconnectLog")); // = CTestButton((HMENU)26);
CItemLog& g_itemLog = VTOR<CItemLog>(DetourFindFunction(EXEPATH(), "g_itemLog"));
CChangeMaterialLog& g_ChagneMaterialLog = VTOR<CChangeMaterialLog>(DetourFindFunction(EXEPATH(), "g_ChagneMaterialLog"));
CPetDefaultValue& g_petDefaultValue = VTOR<CPetDefaultValue>(DetourFindFunction(EXEPATH(), "g_petDefaultValue"));
CPetDB& g_petDB = VTOR<CPetDB>(DetourFindFunction(EXEPATH(), "g_petDB"));
CNPCAddSkillInfo& g_npcAddSkillInfo = VTOR<CNPCAddSkillInfo>(DetourFindFunction(EXEPATH(), "g_npcAddSkillInfo"));
CMEventDB& g_MEventDB = VTOR<CMEventDB>(DetourFindFunction(EXEPATH(), "g_MEventDB"));
CPEventDB& g_PEventDB = VTOR<CPEventDB>(DetourFindFunction(EXEPATH(), "g_PEventDB"));
CGlobalVarDB& g_globalVarDB = VTOR<CGlobalVarDB>(DetourFindFunction(EXEPATH(), "g_globalVarDB"));
CJobCodeForItem& g_jobCodeForItem = VTOR<CJobCodeForItem>(DetourFindFunction(EXEPATH(), "g_jobCodeForItem"));
CBotMngr& g_botMngr = VTOR<CBotMngr>(DetourFindFunction(EXEPATH(), "g_botMngr"));
CMakerRankDB& g_makerRankDB = VTOR<CMakerRankDB>(DetourFindFunction(EXEPATH(), "g_makerRankDB"));
CMakerRankMgr& g_makerRankMgr = VTOR<CMakerRankMgr>(DetourFindFunction(EXEPATH(), "g_makerRankMgr"));
CPKInfoMgr& g_PKInfoMgr = VTOR<CPKInfoMgr>(DetourFindFunction(EXEPATH(), "g_PKInfoMgr"));
CStorePasswordDB& g_storePasswordDB = VTOR<CStorePasswordDB>(DetourFindFunction(EXEPATH(), "g_storePasswordDB"));
CLottoDB& g_lottoDB = VTOR<CLottoDB>(DetourFindFunction(EXEPATH(), "g_lottoDB"));
CAuctionCtrl& g_AuctionCtrl = VTOR<CAuctionCtrl>(DetourFindFunction(EXEPATH(), "g_AuctionCtrl"));
CStatpointPerLevel& g_statpointPerLevel = VTOR<CStatpointPerLevel>(DetourFindFunction(EXEPATH(), "g_statpointPerLevel"));
CDBScriptInfo& g_dbScriptInfo = VTOR<CDBScriptInfo>(DetourFindFunction(EXEPATH(), "g_dbScriptInfo"));
CPathData& g_pathData = VTOR<CPathData>(DetourFindFunction(EXEPATH(), "g_pathData"));
CPathData& g_pathDataNpc = VTOR<CPathData>(DetourFindFunction(EXEPATH(), "g_pathDataNpc"));
HINSTANCE& g_hInst = VTOR<HINSTANCE>(DetourFindFunction(EXEPATH(), "g_hInst"));
HWND& g_hWnd = VTOR<HWND>(DetourFindFunction(EXEPATH(), "g_hWnd"));
time_t& g_curTime = VTOR<time_t>(DetourFindFunction(EXEPATH(), "g_curTime"));
int& g_ZoneInterLoginValue = VTOR<int>(DetourFindFunction(EXEPATH(), "g_ZoneInterLoginValue"));
int& g_ZoneInterLoginError = VTOR<int>(DetourFindFunction(EXEPATH(), "g_ZoneInterLoginError"));
int& g_loopCountPerSec = VTOR<int>(DetourFindFunction(EXEPATH(), "g_loopCountPerSec"));
bool& g_IsDisconnectAll = VTOR<bool>(DetourFindFunction(EXEPATH(), "g_IsDisconnectAll"));
char(& g_dbPWD)[256] = VTOR<char[256]>(DetourFindFunction(EXEPATH(), "g_dbPWD"));
char(& g_GlobaldbPWD)[256] = VTOR<char[256]>(DetourFindFunction(EXEPATH(), "g_GlobaldbPWD"));
BOOL& g_isNEWHPSP = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_isNEWHPSP")); // = TRUE;
BOOL& g_isMANNER_POINT = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_isMANNER_POINT")); // = TRUE;
BOOL& g_isKillerSystem = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_isKillerSystem"));
__int64& g_KillerExpireTime = VTOR<__int64>(DetourFindFunction(EXEPATH(), "g_KillerExpireTime"));
int& g_characterServerPort = VTOR<int>(DetourFindFunction(EXEPATH(), "g_characterServerPort"));
BOOL& g_isNpcSkip = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_isNpcSkip"));
int& SPEEDHACK_DETECTETIME = VTOR<int>(DetourFindFunction(EXEPATH(), "SPEEDHACK_DETECTETIME"));
BOOL& g_IsAbleDrop = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_IsAbleDrop")); // = TRUE;
int& g_deadExpPenalty = VTOR<int>(DetourFindFunction(EXEPATH(), "g_deadExpPenalty"));
int& g_deadEquipItemPenalty = VTOR<int>(DetourFindFunction(EXEPATH(), "g_deadEquipItemPenalty"));
BOOL& g_siegeV15On = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_siegeV15On"));
BOOL& g_isMobileEventOn = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_isMobileEventOn"));
int& g_AMTterm = VTOR<int>(DetourFindFunction(EXEPATH(), "g_AMTterm"));
int& g_maxSkill = VTOR<int>(DetourFindFunction(EXEPATH(), "g_maxSkill"));
BOOL& g_isPacketLog = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_isPacketLog"));
BOOL g_reqUserCount = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_reqUserCount")); // = TRUE;
int& g_extensionDropTime = VTOR<int>(DetourFindFunction(EXEPATH(), "g_extensionDropTime"));
int& g_MaxZenyStore = VTOR<int>(DetourFindFunction(EXEPATH(), "g_MaxZenyStore"));
int& g_MaxZenyStoreLog = VTOR<int>(DetourFindFunction(EXEPATH(), "g_MaxZenyStoreLog"));
int& g_BotDenyManner = VTOR<int>(DetourFindFunction(EXEPATH(), "g_BotDenyManner"));
BOOL& g_isGuildDelete = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_isGuildDelete")); // = TRUE;
BOOL& g_isGuildEmergencyCall = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_isGuildEmergencyCall")); // = TRUE;
char(& g_dataPath)[MAX_PATH] = VTOR<char[MAX_PATH]>(DetourFindFunction(EXEPATH(), "g_dataPath"));
char(& g_npcDataPath)[MAX_PATH] = VTOR<char[MAX_PATH]>(DetourFindFunction(EXEPATH(), "g_npcDataPath"));
char(& g_remoteAccount)[MAX_PATH] = VTOR<char[MAX_PATH]>(DetourFindFunction(EXEPATH(), "g_remoteAccount"));
char(& g_remotePassword)[MAX_PATH] = VTOR<char[MAX_PATH]>(DetourFindFunction(EXEPATH(), "g_remotePassword"));
DWORD& g_storePasswordPanaltyTime = VTOR<DWORD>(DetourFindFunction(EXEPATH(), "g_storePasswordPanaltyTime"));
DWORD& g_storePasswordPanaltyCount = VTOR<DWORD>(DetourFindFunction(EXEPATH(), "g_storePasswordPanaltyCount"));
BOOL& g_storePasswordCheck = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_storePasswordCheck"));
BOOL& g_lottoCheck = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_lottoCheck"));
int& g_compositionLogVersion = VTOR<int>(DetourFindFunction(EXEPATH(), "g_compositionLogVersion"));
DWORD& g_cashShopPasswordPanaltyTime = VTOR<DWORD>(DetourFindFunction(EXEPATH(), "g_cashShopPasswordPanaltyTime"));
DWORD& g_cashShopPasswordPanaltyCount = VTOR<DWORD>(DetourFindFunction(EXEPATH(), "g_cashShopPasswordPanaltyCount"));
BOOL& g_cashShopPasswordCheck = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_cashShopPasswordCheck"));
BOOL& g_castleMapMoveCheck = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_castleMapMoveCheck"));
BOOL& g_isGameGuardOn = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_isGameGuardOn"));
int& g_isGameGuardCheckTime = VTOR<int>(DetourFindFunction(EXEPATH(), "g_isGameGuardCheckTime"));
int& g_isGameGuardInitTime = VTOR<int>(DetourFindFunction(EXEPATH(), "g_isGameGuardInitTime"));
short& g_isGameGuardLogLevel = VTOR<short>(DetourFindFunction(EXEPATH(), "g_isGameGuardLogLevel"));
BOOL& g_gameGuardSwitch = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_gameGuardSwitch"));
int& g_empelium_hp = VTOR<int>(DetourFindFunction(EXEPATH(), "g_empelium_hp"));
BOOL& g_isEventMonsterOn = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_isEventMonsterOn"));
BOOL& g_isSendMailOn = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_isSendMailOn"));
BOOL& g_isAddMailItem = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_isAddMailItem"));
BOOL& g_EventLog = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_EventLog"));
unsigned long& g_BootyItem = VTOR<unsigned long>(DetourFindFunction(EXEPATH(), "g_BootyItem"));
int& g_ForeignCode = VTOR<int>(DetourFindFunction(EXEPATH(), "g_ForeignCode"));
int& g_freeServer = VTOR<int>(DetourFindFunction(EXEPATH(), "g_freeServer"));
int& g_npcDisappear = VTOR<int>(DetourFindFunction(EXEPATH(), "g_npcDisappear"));
BOOL& g_Free_Server = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_Free_Server"));
int& g_teleportSPCost = VTOR<int>(DetourFindFunction(EXEPATH(), "g_teleportSPCost")); // = 500;
BOOL& g_ZenyChecksum = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_ZenyChecksum"));
int& g_StoreMaxItemSize = VTOR<int>(DetourFindFunction(EXEPATH(), "g_StoreMaxItemSize"));
BOOL& g_bPremium_Service = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_bPremium_Service"));
short g_mEventMaxCount = VTOR<short>(DetourFindFunction(EXEPATH(), "g_mEventMaxCount")); // = 10;
BOOL& g_wrIteNpcEventLog = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_wrIteNpcEventLog"));
int(& g_backpedalTable)[8][2] = VTOR<int[8][2]>(DetourFindFunction(EXEPATH(), "g_backpedalTable")); // = { {0,1}, {-1,1}, {-1,0}, {-1,-1}, {0,-1}, {1,-1}, {1,0}, {1,1} };
const char g_infFile[] = ".\\RO.inf";
const char CHARACTER_DSN_FILE[] = "character.dsn";
const char LOG_DSN_FILE[] = "log.dsn";
const char GLOBALINFO_DSN_FILE[] = "globalinfo.dsn";
const char SCRIPT_DSN_FILE[] = "script.dsn";
const char IPINFO_DSN_FILE[] = "ipinfo.dsn";
const char CASHSHOT_DSN_FILE[] = "cashshop.dsn";

/// locals
static int& MaxOutputLineCnt = VTOR<int>(DetourFindFunction(EXEPATH(), "MaxOutputLineCnt")); // = -1;


/// forward declarations
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


const char* GetCharDBPwd()
{
	return g_dbPWD;
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	g_hInst = hInstance;

	WNDCLASSEXA wc;
	wc.cbSize = sizeof(wc);
	wc.style = CS_CLASSDC | CS_DBLCLKS;
	wc.lpfnWndProc = &WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandleA(NULL);
	wc.hIcon = NULL;
	wc.hCursor = NULL;
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "Ragnarok";
	wc.hIconSm = NULL;
	RegisterClassExA(&wc);

	char temp[256];
	sprintf_s(temp, countof(temp), "RO - INTERNATIONAL SC%d.%d.%d", 14, 2, 1);

	std::string windowName;
	windowName.append(temp, strlen(temp));

	char buf[256];
	sprintf_s(buf, countof(buf), "%s (%s)", windowName.c_str(), __DATE__" "__TIME__);

	g_hWnd = CreateWindowExA(0, "Ragnarok", buf, WS_OVERLAPPEDWINDOW, 100, 100, 700, 700, GetDesktopWindow(), NULL, wc.hInstance, NULL);
	if( g_hWnd == NULL )
	{
		MessageBoxA(NULL, "failed window", "error", MB_OK);
		return FALSE;
	}

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);
	SetTimer(g_hWnd, 0, 1000, NULL);

	return TRUE;
}


static void UnderPaint(HDC in_hdc, int in_nX, int in_nY)
{
	if( CCharacterMgr::GetObj() == NULL || C2InterServerClient::GetObj() == NULL )
		return;

	char buf[256] = {};

	int Valid = CCharacterMgr::GetObj()->CCharacterMgr::GetCurValidPlayChar();
	int Dis = CCharacterMgr::GetObj()->CCharacterMgr::GetCurDisconnectCountPlayChar();
	int Enter = CCharacterMgr::GetObj()->CCharacterMgr::GetCurPlayChar() - CCharacterMgr::GetObj()->CCharacterMgr::GetCurValidPlayChar() - CCharacterMgr::GetObj()->CCharacterMgr::GetCurDisconnectCountPlayChar();
	_snprintf_s(buf, countof(buf), _TRUNCATE, "User Cnt: %d / %d : ( Valid(%d) + Dis(%d) + Enter(%d) )", CCharacterMgr::GetObj()->CCharacterMgr::GetCurPlayChar(), CGVar::GetObj()->CGVar::GetMaxCharacterCount(), Valid, Dis, Enter);
	TextOutA(in_hdc, in_nX, in_nY + 16, buf, strlen(buf));

	_snprintf_s(buf, countof(buf), _TRUNCATE, "NPC Cnt: %d (visible + hidden)", CCharacterMgr::GetObj()->CCharacterMgr::GetMonsterCount());
	TextOutA(in_hdc, in_nX, in_nY + 32, buf, strlen(buf));

	_snprintf_s(buf, countof(buf), _TRUNCATE, "Map Object(Chracter) Cnt: %d (hidden not inclusive) ", g_mapResMgr.CMapResMgr::GetTotalSectionSize());
	TextOutA(in_hdc, in_nX, in_nY + 48, buf, strlen(buf));

	_snprintf_s(buf, countof(buf), _TRUNCATE, "Skill Object Cnt: %d/%d  ", CCharacterMgr::GetObj()->CCharacterMgr::GetSkillObjCnt(), CCharacterMgr::GetObj()->CCharacterMgr::GetSkillObjCapacity());
	TextOutA(in_hdc, in_nX, in_nY + 64, buf, strlen(buf));

	_snprintf_s(buf, countof(buf), _TRUNCATE, "Item Object Cnt: %d/%d  ", CCharacterMgr::GetObj()->CCharacterMgr::GetItemObjCnt(), CCharacterMgr::GetObj()->CCharacterMgr::GetItemObjCapacity());
	TextOutA(in_hdc, in_nX, in_nY + 80, buf, strlen(buf));

	_snprintf_s(buf, countof(buf), _TRUNCATE, "Item Log Cnt: %d/%d  ", g_itemLog.CDatabaseLog<SITEMLOG*>::GetSize(), CItemLog::KEEP_OBJECT_MAXCNT);
	TextOutA(in_hdc, in_nX, in_nY + 96, buf, strlen(buf));

	_snprintf_s(buf, countof(buf), _TRUNCATE, "Guild Count:%d Free Size:%d  OffSet : %d", g_ZGuildMgr.CGuildMgr::GetGuildSize(), g_ZGuildMgr.CZGuildMgr::GetFreeSize(), g_ZGuildMgr.CZGuildMgr::GetOffset());
	TextOutA(in_hdc, in_nX, in_nY + 112, buf, strlen(buf));

	_snprintf_s(buf, countof(buf), _TRUNCATE, "Zone Login - Inter Login : %d , Zone-Inter Login Error : %d ", g_ZoneInterLoginValue, g_ZoneInterLoginError);
	TextOutA(in_hdc, in_nX, in_nY + 128, buf, strlen(buf));

	_snprintf_s(buf, countof(buf), _TRUNCATE, "Zone ProcessTime / Max ProcessTime  : %d / %d ", (int)g_ProcessTime, (int)g_MaxProcessTime);
	TextOutA(in_hdc, in_nX, in_nY + 144, buf, strlen(buf));

	_snprintf_s(buf, countof(buf), _TRUNCATE, "Auth Inter(%d) Char(%d)", C2InterServerClient::GetObj()->C2InterServerClient::isAuth(), C2CharacterServerClient::GetObj()->C2CharacterServerClient::isAuth());
	TextOutA(in_hdc, in_nX, in_nY + 160, buf, strlen(buf));
}


static void TopPaint(HDC in_hdc, int in_nX, int in_nY)
{
	char buf[256] = {};
	int ZSID = ( &g_serverInfo != NULL ) ? g_serverInfo.CServerInfo::GetLocalServerID() : 0; //TODO: inlining
	sprintf_s(buf, countof(buf), "Path : %s ZSID(%d)", GetRootPath(), ZSID);

	COLORREF oldColor = GetTextColor(in_hdc);
	SetTextColor(in_hdc, RGB(255,100,255));
	TextOutA(in_hdc, in_nX, in_nY + 16, buf, strlen(buf));
	SetTextColor(in_hdc, oldColor);

	if( !g_zsAcceptHandler.CZSAcceptHandler::GetAcceptable() )
	{
		COLORREF oldColor = GetTextColor(in_hdc);
		SetTextColor(in_hdc, RGB(255,0,0));
		TextOutA(in_hdc, in_nX, in_nY + 32, "Client Accept FALSE ! ! !", strlen("Client Accept FALSE ! ! !"));
		SetTextColor(in_hdc, oldColor);
	}
}


static void BottonMessagePaint(HDC in_hdc)
{
	char buf[256] = {};

	sprintf_s(buf, countof(buf), ( NCriticalErrorLog::GetObj()->NFileLog::GetOutput() ) ? "yes" : "no");
	TextOutA(in_hdc, ToggleButtonCriticalLog.CTestButton::GetX() + ToggleButtonCriticalLog.CTestButton::GetWidth() + 5, ToggleButtonCriticalLog.CTestButton::GetY(), buf, strlen(buf));

	sprintf_s(buf, countof(buf), ( Trace == &TraceF ) ? "yes" : "no");
	TextOutA(in_hdc, ToggleButtonTraceLog.CTestButton::GetX() + ToggleButtonTraceLog.CTestButton::GetWidth() + 5, ToggleButtonTraceLog.CTestButton::GetY(), buf, strlen(buf));

	sprintf_s(buf, countof(buf), "%s", ( CDisconnectLog::GetObj() != NULL && CDisconnectLog::GetObj()->NFileLog::GetOutput() ) ? "yes" : "no");
	TextOutA(in_hdc, ToggleButtonDisconnectLog.CTestButton::GetX() + ToggleButtonDisconnectLog.CTestButton::GetWidth() + 5, ToggleButtonDisconnectLog.CTestButton::GetY() + 2, buf, strlen(buf));
}


static void OnWM_PAINT(HWND in_hWnd)
{
	PAINTSTRUCT ps = {};
	BeginPaint(in_hWnd, &ps);

	RECT rect = {};
	GetClientRect(in_hWnd, &rect);

	FillRect(ps.hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	BottonMessagePaint(ps.hdc);
	TopPaint(ps.hdc, 10, 0);

	if( NOutputTextMgr::GetObj() != NULL )
	{
		MaxOutputLineCnt = NOutputTextMgr::GetObj()->NOutputTextMgr::GetMaxLineCnt();
		for( int Cnt = 0, y = 400; y > 160; ++Cnt, y -= 16 )
		{
			std::string msg = NOutputTextMgr::GetObj()->NOutputTextMgr::GetText(MaxOutputLineCnt - Cnt);
			if( msg.size() == 0 )
				break;

			TextOutA(ps.hdc, 10, y, msg.c_str(), msg.size());
		}
	}

	UnderPaint(ps.hdc, 10, 416);
	EndPaint(in_hWnd, &ps);
}


static void OnWM_CREATE(HWND in_hWnd, WPARAM in_wParam, LPARAM in_lParam)
{
	CREATESTRUCTA* cs = reinterpret_cast<CREATESTRUCTA*>(in_lParam);
	int x = LOWORD(GetDialogBaseUnits());
	int y = HIWORD(GetDialogBaseUnits());

	ToggleButtonCriticalLog.CTestButton::OnCreate(in_hWnd, cs->hInstance, x + 400, y + 22, 80, 21, "critical log");
	ToggleButtonTraceLog.CTestButton::OnCreate(in_hWnd, cs->hInstance, x + 400, y + 44, 80, 21, "trace log");
	ToggleButtonKillZone.CTestButton::OnCreate(in_hWnd, cs->hInstance, x + 400, y + 66, 80, 21, "KillZone");
	ToggleButtonDisconnectLog.CTestButton::OnCreate(in_hWnd, cs->hInstance, x + 400, y + 88, 120, 21, "Disconnect Log");
}


static void OnWM_COMMAND(HWND in_hWnd, WPARAM in_wParam, LPARAM in_lParam)
{
	unsigned short command = (unsigned short)in_wParam;
	switch( command )
	{
	case 20: // ToggleButtonCriticalLog
	{
		NCriticalErrorLog::GetObj()->NFileLog::SetOutput(!NCriticalErrorLog::GetObj()->NFileLog::GetOutput());
		InvalidateRect(in_hWnd, NULL, FALSE);
	}
	break;
	case 21: // ToggleButtonTraceLog
	{
		Trace = ( Trace == &TraceF ) ? &TraceN : &TraceF;
		InvalidateRect(in_hWnd, NULL, FALSE);
	}
	break;
	case 25: // ToggleButtonKillZone
	{
		DisconnectAll();
	}
	break;
	case 26: // ToggleButtonDisconnectLog
	{
		CDisconnectLog::GetObj()->NFileLog::SetOutput(!CDisconnectLog::GetObj()->NFileLog::GetOutput());
	}
	break;
	};
}


static void OnWM_TIMER(HWND in_hWnd)
{
	if( NOutputTextMgr::GetObj() == NULL )
		return;

	if( MaxOutputLineCnt != NOutputTextMgr::GetObj()->NOutputTextMgr::GetMaxLineCnt() )
		InvalidateRect(in_hWnd, NULL, TRUE);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case WM_CREATE:
		OnWM_CREATE(hWnd, wParam, lParam);
	break;
	case WM_DESTROY:
		PostQuitMessage(EXIT_SUCCESS);
	break;
	case WM_PAINT:
		OnWM_PAINT(hWnd);
	break;
	case WM_COMMAND:
		OnWM_COMMAND(hWnd, wParam, lParam);
	break;
	case WM_TIMER:
		OnWM_TIMER(hWnd);
	break;
	case WM_RBUTTONDOWN:
		InvalidateRect(hWnd, NULL, TRUE);
	break;
	case WM_USER+300:
		OutputDebugLog(00000000); //TODO: unknown value
	break;
	};

	return DefWindowProcA(hWnd, msg, wParam, lParam);
}


bool InitFromRoInf()
{
	int logOption = GetPrivateProfileIntA("ETC", "LOG", 0, g_infFile);
	InitializeSharedLib(00000000, logOption); //TODO: uknown value

	char encBuf[128] = {};
	char encBuf2[128] = {};
	GetPrivateProfileStringA("ETC", "DB", "", encBuf, countof(encBuf), g_infFile);
	GetPrivateProfileStringA("ETC", "GLOBAL_DB", encBuf, encBuf2, countof(encBuf2), g_infFile);
	Decrypt(encBuf, (unsigned char*)g_dbPWD);
	Decrypt(encBuf2, (unsigned char*)g_GlobaldbPWD);

	if( !GetPrivateProfileIntA("SETTING", "NEWHPSP", TRUE, g_infFile) )
		g_isNEWHPSP = FALSE;

	if( !GetPrivateProfileIntA("SETTING", "MANNER_POINT", TRUE, g_infFile) )
		g_isMANNER_POINT = FALSE;

	g_isKillerSystem = GetPrivateProfileIntA("SETTING", "KILLER_SYSTEM", FALSE, g_infFile);

	g_KillerExpireTime = 600000000i64 * GetPrivateProfileIntA("SETTING", "KILLER_EXPIRE_TIME", 1440, g_infFile);

	g_characterServerPort = GetPrivateProfileIntA("VERSION", "ASERVER_PORT", 0, g_infFile);

	g_isNpcSkip = GetPrivateProfileIntA("ETC", "NPC_SKIP", FALSE, g_infFile);

	GetPrivateProfileIntA("ETC", "ENCRYPT", 0, g_infFile);

	SPEEDHACK_DETECTETIME = GetPrivateProfileIntA("ETC", "SPEEDHACK", 20000, g_infFile);

	g_IsAbleDrop = GetPrivateProfileIntA("ETC", "ITEMDROP", TRUE, g_infFile);

	g_deadExpPenalty = GetPrivateProfileIntA("ETC", "DEAD_EXP", 1, g_infFile);

	g_deadEquipItemPenalty = GetPrivateProfileIntA("ETC", "DEAD_EQUIPITEM", 5, g_infFile);

	char siegeTime[64];
	GetPrivateProfileStringA("SIEGE", "TIME", "", siegeTime, 64, g_infFile);
	if( siegeTime[0] != '\0' )
	{
		int siegeDuration = GetPrivateProfileIntA("SIEGE", "PERIOD", 2, g_infFile);
		if( !CAgitMapRes::SetSiegeTime(siegeTime, siegeDuration) )
		{
			MessageBoxA(NULL, "SIEGE TIME invalid format", NULL, MB_OK);
			return false;
		}
	}

	char siegev15_Time[64] = {};
	GetPrivateProfileStringA("SIEGE_V15", "TIME", "", siegev15_Time, countof(siegev15_Time), g_infFile);
	if( siegev15_Time[0] != '\0' )
	{
		int siegev15_Duration = GetPrivateProfileIntA("SIEGE_V15", "PERIOD", 2, g_infFile);
		if( CAgitMapRes::SetSiegeTime_v15(siegev15_Time, siegev15_Duration) == true )
			g_siegeV15On = TRUE;
	}

	g_isMobileEventOn = GetPrivateProfileIntA("ETC", "MOBILE_EVENT", FALSE, g_infFile);

	g_AMTterm = GetPrivateProfileIntA("ETC", "ATTACK_MOTION_TIME_TERM", 100, g_infFile);

	g_maxSkill = GetPrivateProfileIntA("ETC", "MAX_SKILL", 2000, g_infFile);

	BOOL isCriticalLog = GetPrivateProfileIntA("ETC", "CRITICAL_LOG", FALSE, g_infFile);
	NCriticalErrorLog::GetObj()->NFileLog::SetOutput(isCriticalLog != FALSE);

	g_isPacketLog = GetPrivateProfileIntA("ETC", "PACKET_LOG", FALSE, g_infFile);

	g_reqUserCount = GetPrivateProfileIntA("ETC", "REQ_USER_COUNT", TRUE, g_infFile);

	g_extensionDropTime = GetPrivateProfileIntA("ETC", "DELAY_ITEM_TIME", 0, g_infFile);

	g_MaxZenyStore = GetPrivateProfileIntA("ETC", "MAX_STORE", 99990000, g_infFile);

	g_MaxZenyStoreLog = GetPrivateProfileIntA("ETC", "MAX_STORE_LOG", INT_MAX, g_infFile);

	g_BotDenyManner = GetPrivateProfileIntA("ETC", "BOT_MANNER", 3000, g_infFile);

	g_isGuildDelete = GetPrivateProfileIntA("ETC", "GUILD_DISORGANIZATION", TRUE, g_infFile);

	g_isGuildEmergencyCall = GetPrivateProfileIntA("ETC", "GUILD_EMERGENCY_CALL", TRUE, g_infFile);

	GetPrivateProfileStringA("ZONE_PATH", "DATA_PATH", "", g_dataPath, countof(g_dataPath), g_infFile);
	GetPrivateProfileStringA("ZONE_PATH", "NPC_DATA_PATH", "", g_npcDataPath, countof(g_npcDataPath), g_infFile);
	g_pathData.CPathData::Init(g_dataPath);
	g_pathDataNpc.CPathData::Init(( strlen(g_npcDataPath) != 0 ) ? g_npcDataPath : g_dataPath);

	if( CPath::IsRemotePath(g_dataPath) )
	{
		GetPrivateProfileStringA("ZONE_PATH", "REMOTE_ACCOUNT", "", g_remoteAccount, countof(g_remoteAccount), g_infFile);
		GetPrivateProfileStringA("ZONE_PATH", "REMOTE_PASSWORD", "", g_remotePassword, countof(g_remotePassword), g_infFile);

		int err = CPath::AddConnection(g_dataPath, g_remoteAccount, g_remotePassword);
		if( err != NO_ERROR )
		{
			char temp[256];
			sprintf_s(temp, countof(temp), "CPath::AddConnection\n%s\n,%s\n,%s failed %d\n", g_dataPath, g_remoteAccount, g_remotePassword, err);
			MessageBoxA(NULL, temp, "zoneserver error", MB_ICONEXCLAMATION);
			return false;
		}

		SetEnvironmentVariableA("_NT_SYMBOL_PATH", g_dataPath);
	}

	g_storePasswordPanaltyTime = 60 * GetPrivateProfileIntA("STORE_PASSWORD", "STORE_PASSWORD_PANALTY_TIME", 1, g_infFile);

	g_storePasswordPanaltyCount = GetPrivateProfileIntA("STORE_PASSWORD", "STORE_PASSWORD_PANALTY_COUNT", 10, g_infFile);

	g_storePasswordCheck = GetPrivateProfileIntA("STORE_PASSWORD", "STORE_PASSWORD_CHECK", FALSE, g_infFile);

	g_lottoCheck = GetPrivateProfileIntA("ETC", "LOTTO", FALSE, g_infFile);

	g_compositionLogVersion = GetPrivateProfileIntA("ETC", "COMPOSITION_LOG", 1, g_infFile);

	g_cashShopPasswordPanaltyTime = 60 * GetPrivateProfileIntA("CASHSHOP_PASSWORD", "CASHSHOP_PASSWORD_PANALTY_TIME", 1, g_infFile);

	g_cashShopPasswordPanaltyCount = GetPrivateProfileIntA("CASHSHOP_PASSWORD", "CASHSHOP_PASSWORD_PANALTY_COUNT", 10, g_infFile);

	g_cashShopPasswordCheck = GetPrivateProfileIntA("CASHSHOP_PASSWORD", "CASHSHOP_PASSWORD_CHECK", FALSE, g_infFile);

	g_castleMapMoveCheck = GetPrivateProfileIntA("ETC", "CASTLE_MAP_MOVE_CHECK", FALSE, g_infFile);

	g_isGameGuardOn = GetPrivateProfileIntA("ETC", "GAME_GUARD", FALSE, g_infFile);

	g_isGameGuardCheckTime = GetPrivateProfileIntA("ETC", "GAME_GUARD_TIME_MINUTE", 0, g_infFile);

	g_isGameGuardInitTime = GetPrivateProfileIntA("ETC", "GAME_GUARD_INIT_TIME_SECOND", 0, g_infFile);

	g_isGameGuardLogLevel = GetPrivateProfileIntA("ETC", "GAME_GUARD_LOG_LEVEL", 0, g_infFile);

	if( g_isGameGuardCheckTime <= 0 || g_isGameGuardCheckTime > 5 )
		g_isGameGuardCheckTime = 5;
	g_isGameGuardCheckTime *= 60000;

	if( g_isGameGuardInitTime < 20 || (g_isGameGuardInitTime *= 1000, g_isGameGuardInitTime > g_isGameGuardCheckTime) ) //TODO: cleanup
		g_isGameGuardInitTime = g_isGameGuardCheckTime;

	g_gameGuardSwitch = GetPrivateProfileIntA("ETC", "GAMEGUARD_ONOFF_SYSTEM", FALSE, g_infFile);

	g_empelium_hp = GetPrivateProfileIntA("ETC", "AGIT_EMPLIUM_HP_SETTING", 1, g_infFile);

	g_isEventMonsterOn = GetPrivateProfileIntA("ETC", "EVENT_MONSTER", FALSE, g_infFile);

	g_isSendMailOn = GetPrivateProfileIntA("ETC", "SEND_MAIL", TRUE, g_infFile);

	g_isAddMailItem = GetPrivateProfileIntA("ETC", "ADD_MAIL_ITEM", TRUE, g_infFile);

	g_EventLog = GetPrivateProfileIntA("ETC", "EVENT_LOG", FALSE, g_infFile);

	g_BootyItem = GetPrivateProfileIntA("ETC", "BOOTY_ITEM", 0, g_infFile);

	g_ForeignCode = GetPrivateProfileIntA("FOREIGN", "FOREIGN_CODE", 0, g_infFile);

	g_freeServer = GetPrivateProfileIntA("ETC", "KOREA_FREE_SERVER", 0, g_infFile);

	g_npcDisappear = GetPrivateProfileIntA("ETC", "NPC_DISAPPEAR", 0, g_infFile);

	g_Free_Server = GetPrivateProfileIntA("ETC", "FREE_SERVER", FALSE, g_infFile);

	if( g_Free_Server == TRUE )
		g_teleportSPCost = GetPrivateProfileIntA("ETC", "SKILL_TELEPORT_SP", 500, g_infFile);

	InitRefinerySuccessPercent();

	g_ZenyChecksum = GetPrivateProfileIntA("ETC", "ZENY_CHECKSUM", FALSE, g_infFile);

	g_StoreMaxItemSize = GetPrivateProfileIntA("ETC", "MAX_STROR_SIZE", 300, g_infFile);

	g_bPremium_Service = GetPrivateProfileIntA("ETC", "PREMIUM_SERVICE", FALSE, g_infFile);
	if( g_bPremium_Service == TRUE )
		g_StoreMaxItemSize = 600;

	if( (int)GetPrivateProfileIntA("ETC", "MEVENT_MAX_COUNT", 10, g_infFile) > 15 )
		g_mEventMaxCount = 15;

	g_wrIteNpcEventLog = GetPrivateProfileIntA("ETC", "WRITE_NPC_EVENT_LOG", FALSE, g_infFile);

	return true;
}


namespace {
////////////////////////////////////////
class lcApp
{
public:
	std::pair<bool,std::string> Startup();
	void Cleanup();

public:
	lcApp();
	virtual ~lcApp();

private:
	/* this+4 */ HANDLE m_hMutex;
	/* this+8 */ UINT m_wTimerRes;
};


lcApp::lcApp()
{
	m_hMutex = NULL;
	m_wTimerRes = 0;
}


lcApp::~lcApp()
{
}


std::pair<bool,std::string> lcApp::Startup()
{
	if( !CZsvrSchedulerIdentity::CreateInstance() )
		return std::pair<bool,std::string>(false, "CZsvrSchedulerIdentity::CreateInstance()");

	if( !CProgrammerSupportLog::CreateInstance() )
		return std::pair<bool,std::string>(false, "CProgrammerSupportLog::CreateInstance()");

	TIMECAPS tc = {};
	if( !timeGetDevCaps(&tc, sizeof(tc)) )
	{
		m_wTimerRes = min(max(1, tc.wPeriodMin), tc.wPeriodMax);
		timeBeginPeriod(m_wTimerRes);
	}

	if( !CThreadAffinityMgr::CreateInstance() )
		return std::pair<bool,std::string>(false, "CThreadAffinityMgr::CreateInstance()");

	if( !InitFromRoInf() )
		return std::pair<bool,std::string>(false, "InitFromRoInf()");

	if( !CZoneProcessConfigMgr::CreateInstance() )
		return std::pair<bool,std::string>(false, "CZoneProcessConfigMgr::CreateInstance()");

	if( !CZoneProcessLocalConfigMgr::CreateInstance() )
		return std::pair<bool,std::string>(false, "CZoneProcessLocalConfigMgr::CreateInstance()");

	if( !CZoneProcessLocalConfigMgr::GetObj()->CZoneProcessLocalConfigMgr::Init() )
		return std::pair<bool,std::string>(false, "InstanceCZoneProcessLocalConfigMgr()->Init()");

	char modulePath[MAX_PATH] = {};
	GetModuleFileNameA(NULL, modulePath, countof(modulePath));

	for( size_t i = 0; i < strlen(modulePath); ++i )
		if( modulePath[i] == '\\' || modulePath[i] == ':' || modulePath[i] == '.' )
			modulePath[i] = ' ';

	m_hMutex = CreateMutexA(NULL, FALSE, modulePath);

	if( WaitForSingleObject(m_hMutex, 0) != WAIT_OBJECT_0 )
		return std::pair<bool,std::string>(false, "Another Zone Server is Still Executing");

	if( !CGVar::CreateInstance() )
		return std::pair<bool,std::string>(false, "CGvar Init faile zoneserver error");

	g_curTime = time(NULL);
	g_serverInfo.CServerInfo::Init(GLOBALINFO_DSN_FILE, g_GlobaldbPWD, ZONEPROCESSSERVERTYPE, CZoneProcessLocalConfigMgr::GetObj()->CZoneProcessLocalConfigMgr::GetZSID());

	if( !NNetworkMgr::CreateInstance() )
		return std::pair<bool,std::string>(false, "NNetworkMgr::CreateInstance()");

	return std::pair<bool,std::string>(true, "good");
}


void lcApp::Cleanup()
{
	NNetworkMgr::DestroyInstance();

	if( m_hMutex != NULL )
	{
		CloseHandle(m_hMutex);
		m_hMutex = NULL;
	}

	CZoneProcessLocalConfigMgr::DestroyInstance();
	CZoneProcessConfigMgr::DestroyInstance();
	CGVar::DestoryInstance();
	CThreadAffinityMgr::DestroyInstance();
	if( m_wTimerRes != 0 ) timeEndPeriod(m_wTimerRes);
	CProgrammerSupportLog::DestroyInstance();
	CZsvrSchedulerIdentity::DestroyInstance();
}
////////////////////////////////////////
}; // namespace


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if( !CMyMiniDumpUnhandledExceptionHandler::CreateInstance(NULL) )
		return 0;

	if( !NCriticalErrorLog::CreateInstance() )
		return 0;

	if( !NTraceLog::CreateInstance() )
		return 0;

	NTraceLog::GetObj()->NFileLog::SetOutput(true);

	if( !N3MessageMgr::CreateInstance() )
		return 0;

	if( !N3DataTransferMgr::CreateInstance() )
		return 0;

	ZoneServerIdentity();

	if( !NOutputTextMgr::CreateInstance() )
		return 0;

	if( !CProcessMgr::CreateInstance() )
		return 0;

	if( !InitInstance(hInstance, nCmdShow) )
	{
		MessageBoxA(NULL, "failed init window", NULL, MB_OK);
		return 0;
	}

	lcApp* app = new(std::nothrow) lcApp();
	if( app == NULL )
		return 0;

	std::pair<bool,std::string> ret = app->lcApp::Startup();
	if( !ret.first )
	{
		MessageBoxA(NULL, ret.second.c_str(), "Startup()", MB_OK);
		return 0;
	}

	if( !CProcessMgr::GetObj()->CProcessMgr::Start() )
	{
		MessageBoxA(NULL, "Start Fail", "InsanceCProcessMgr", MB_OK);
		return 0;
	}

	MSG msg = {};
	while( msg.message != WM_QUIT )
	{
		if( PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE) )
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
		else
		{
			WaitMessage();
		}
	}

	CProcessMgr::GetObj()->CProcessMgr::Stop();
	app->lcApp::Cleanup();
	delete app;
	CProcessMgr::DestroyInstance();
	NOutputTextMgr::DestroyInstance();
	N3MessageMgr::DestroyInstance();
	N3DataTransferMgr::DestroyInstance();
	NTraceLog::DestroyInstance();
	NCriticalErrorLog::DestroyInstance();
	CMyMiniDumpUnhandledExceptionHandler::DestroyInstance();

	ExitProcess(EXIT_SUCCESS);
}


namespace HELP_HEALTHSTATE
{
////////////////////////////////////////
std::vector<int> GetHealthStateList()
{
	std::vector<int> HealthStateList;
	HealthStateList.push_back(HEALTHSTATE_POISON);
	HealthStateList.push_back(HEALTHSTATE_CURSE);
	HealthStateList.push_back(HEALTHSTATE_SILENCE);
	HealthStateList.push_back(HEALTHSTATE_CONFUSION);
	HealthStateList.push_back(HEALTHSTATE_BLIND);
	HealthStateList.push_back(HEALTHSTATE_ANGELUS);
	HealthStateList.push_back(HEALTHSTATE_BLOODING);
	HealthStateList.push_back(HEALTHSTATE_HEAVYPOISON);
	HealthStateList.push_back(HEALTHSTATE_FEAR);
	return HealthStateList;
}


std::vector<int> GetMyHealthStateList(const int in_state)
{
	static std::vector<int> HealthStateList = GetHealthStateList();

	std::vector<int> MyHealthStateList;
	for( std::vector<int>::const_iterator iter = HealthStateList.begin(); iter != HealthStateList.end(); ++iter )
	{
		int state = *iter;

		if( in_state & state )
			MyHealthStateList.push_back(state);
	}

	return MyHealthStateList;
}
////////////////////////////////////////
}; // namespace HELP_HEALTHSTATE
