#include "std/map"
#include "std/string"
#include "globals.hpp"
#include "MapTypePropertyMgr.h"
#include "CStatpointPerLevel.hpp"
struct FLAG_INFO;


// global variables
hook_val<double[10]> g_ProcessTimeList(SERVER, "g_ProcessTimeList");  //XREF: WinMain(), WndProc()
hook_val<double[2]> g_NpcProcessTimeList(SERVER, "g_NpcProcessTimeList");
hook_val<long> g_curTime(SERVER, "g_curTime");
hook_val<double> g_ProcessTime(SERVER, "g_ProcessTime");              //XREF: WinMain(), WndProc()
hook_val<double> g_MaxProcessTime(SERVER, "g_MaxProcessTime");        //XREF: WinMain(), WndProc()
hook_val<int> g_loopCountPerSec(SERVER, "g_loopCountPerSec");         //XREF: WinMain(), CISvrIOPacketHandler::OnReqServerState()
hook_val<int> g_isMobileEventOn(SERVER, "g_isMobileEventOn");
hook_val<int> g_isGameGuardOn(SERVER, "g_isGameGuardOn");
hook_val<int> g_isGameGuardInitTime(SERVER, "g_isGameGuardInitTime");
hook_val<int> g_characterServerPort(SERVER, "g_characterServerPort"); //XREF: WinMain(), InitFromRoInf()
hook_val<HWND> g_hWnd(SERVER, "g_hWnd");                              //XREF: WinMain(), InitInstance()
hook_val<bool> g_IsNpcSvrOn(SERVER, "g_IsNpcSvrOn");                  //XREF: WinMain(), WndProc()
hook_val<char[256]> g_dbPWD(SERVER, "g_dbPWD");
hook_val<char[256]> g_GlobaldbPWD(SERVER, "g_GlobaldbPWD");           //XREF: WinMain(), InitFromRoInf(), CMonParameterMgr::Init(), CITPMgr::Init(), CExpParameter::Init()
hook_val<unsigned long[8]> g_tick(SERVER, "g_tick");                  //XREF: CCharacterMgr::ProcessAllCharacter(), OutputStat()
hook_val<int> g_isCriticalLog(SERVER, "g_isCriticalLog");
hook_val<bool> g_IsDisconnectAll(SERVER, "g_IsDisconnectAll");        //XREF: CCharacterMgr::ProcessAllCharacter(), CISvrIOPacketHandler::OnDisconnectAll()
hook_val<int> g_isNpcSkip(SERVER, "g_isNpcSkip");                     //XREF: WinMain(), InitFromRoInf()
hook_val<int> g_lottoCheck(SERVER, "g_lottoCheck");                   //XREF: WinMain(), InitFromRoInf()
hook_val<int> g_storePasswordCheck(SERVER, "g_storePasswordCheck");   //XREF: WinMain(), InitFromRoInf(), CPC::OnMsg(), CPCPacketHandler::DispatchPacket()
hook_val<int> g_cashShopPasswordCheck(SERVER, "g_cashShopPasswordCheck"); //XREF: WinMain(), InitFromRoInf(), CNPCStateUpdater::OnCashTradeStart()
hook_val<char[260]> g_szCriticalLogFileName(SERVER, "g_szCriticalLogFileName"); // = "criticalError(Sep 21 2009).txt";
hook_val<char[260]> g_szTraceLogFileName(SERVER, "g_szTraceLogFileName"); // = "TraceLog(Sep 21 2009).txt";
hook_val<const char[9]> g_infFile(SERVER, "g_infFile"); // = ".\\RO.inf";
hook_val<const int> SECTION_SIZE(SERVER, "SECTION_SIZE"); // = 40;
hook_val<HANDLE> g_completionPort(SERVER, "g_completionPort");        //XREF: StartCompletionProactor(), CAsyncStream::Open()
hook_val<void*> ggGlobal(SERVER, "?ggGlobal@@3U__unnamed@@A"); // some badly identified gameguard data structure?
hook_val<int> g_ForeignCode(SERVER, "g_ForeignCode");
hook_val<int> g_isSendMailOn(SERVER, "g_isSendMailOn");               // XREF: InitFromRoInf(), CPCPacketHandler::OnMailSend(), CPCPacketHandler::OnMailReturn()
hook_val<int> g_MaxZenyStore(SERVER, "g_MaxZenyStore");               //XREF: InitFromRoInf(), CPCItemInventoryMgr::PurchaseItemFromMCStore(), CPCItemInventoryMgr::OnReqOpenMCStore()
hook_val<int> g_MaxZenyStoreLog(SERVER, "g_MaxZenyStoreLog");         //XREF: InitFromRoInf(), CPCItemInventoryMgr::PurchaseItemFromMCStore()
hook_val<int> g_ZenyChecksum(SERVER, "g_ZenyChecksum");
hook_val<int> g_ZoneInterLoginValue(SERVER, "g_ZoneInterLoginValue");
hook_val<int> g_ZoneInterLoginError(SERVER, "g_ZoneInterLoginError");
hook_val<int> SPEEDHACK_DETECTETIME(SERVER, "SPEEDHACK_DETECTETIME"); // = 30000;
hook_val<int> g_maxSkill(SERVER, "g_maxSkill");
hook_val<int> g_npcMemorySize(SERVER, "g_npcMemorySize");
hook_val<int> g_bPremium_Service(SERVER, "g_bPremium_Service");
hook_val<int> g_gameGuardSwitch(SERVER, "g_gameGuardSwitch");
hook_val<int> g_isKillerSystem(SERVER, "g_isKillerSystem");
hook_val<int> g_isGuildDelete(SERVER, "g_isGuildDelete");
hook_val<int> g_isGuildEmergencyCall(SERVER, "g_isGuildEmergencyCall");
hook_val<int> g_Free_Server(SERVER, "g_Free_Server");
hook_val<int> g_SimpleCashShop(SERVER, "g_SimpleCashShop");
hook_val<int> g_siegeV15On(SERVER, "g_siegeV15On");
hook_val<int> g_empelium_hp(SERVER, "g_empelium_hp");
hook_val<int> g_StoreMaxItemSize(SERVER, "g_StoreMaxItemSize");
hook_val<__int64> g_KillerExpireTime(SERVER, "g_KillerExpireTime");
hook_val<int> g_isEventMonsterOn(SERVER, "g_isEventMonsterOn");
hook_val<int> g_isPacketLog(SERVER, "g_isPacketLog");
hook_val<int> g_castleMapMoveCheck(SERVER, "g_castleMapMoveCheck"); // = ?
hook_val<int> g_EventLog(SERVER, "g_EventLog"); // = ?
hook_val<int> g_AMTterm(SERVER, "g_AMTterm"); // = ?
hook_val<HINSTANCE> g_hInst(SERVER, "g_hInst"); // = ?;
hook_val<int[8][2]> g_backpedalTable(SERVER, "g_backpedalTable"); // = { {0,1}, {-1,1}, {-1,0}, {-1,-1}, {0,-1}, {1,-1}, {1,0}, {1,1} };
mystd::map<int,int>& g_packetLenMap = VTOR<mystd::map<int,int>>(SymDB::Find("g_packetLenMap")); // = ?;

// global functions
hook_func<void (__cdecl *)(EQUIPSLOTINFO* des, EQUIPSLOTINFO* src)> CopyEquipItemSlotInfo(SERVER, "CopyEquipItemSlotInfo");
hook_func<void (__cdecl *)(char* dest, const char* src)> SetMapName(SERVER, "SetMapName"); // npcevent.cpp
hook_func<int (__cdecl *)(void)> GetLocalServerID(SERVER, "GetLocalServerID"); // zoneprocess.cpp
hook_func<void (__cdecl *)(char* szString)> TrimLeft(SERVER, "TrimLeft"); // npcevent.cpp
hook_func<void (__cdecl *)(char* szString)> TrimRight(SERVER, "TrimRight"); // npcevent.cpp
hook_func<bool (__cdecl *)(void)> AddDSN(SERVER, "AddDSN"); // zoneprocess.cpp
hook_func<void (__cdecl *)(const char* encBuf, char* decBuf)> Decrypt(SERVER, "Decrypt"); // shared/shared.cpp
hook_func<int (__cdecl *)(unsigned int setting)> IsSetting(SERVER, "IsSetting"); // zoneprocess/zoneprocess.cpp
hook_func<mystd::pair<bool,mystd::string> (__cdecl *)(void)> startup(SERVER, "`anonymous namespace'::startup"); // zoneprocess/zoneprocess.cpp
hook_func<int (__cdecl *)(void)> cleanup(SERVER, "`anonymous namespace'::cleanup"); // zoneprocess/zoneprocess.cpp
hook_func<void (__cdecl *)(unsigned int tick)> OutputStat(SERVER, "OutputStat"); // zoneprocess/zoneprocess.cpp
hook_func<unsigned __int32 (__cdecl *)(const char* a1, int a2)> InitGameguardAuth(SERVER, "_InitGameguardAuth"); // external
hook_func<void (__cdecl *)(void)> CleanupGameguardAuth(SERVER, "_CleanupGameguardAuth"); // external
hook_func<unsigned long (__cdecl *)(struct _GG_AUTH_PROTOCOL* pBlock)> UnloadAuthProtocol(SERVER, "?UnloadAuthProtocol@@YAKPAU_GG_AUTH_PROTOCOL@@@Z");
hook_func<int (__cdecl *)(unsigned char* dest, unsigned long* destLen, unsigned const char* source, unsigned long sourceLen, int level)> compress2(SERVER, "compress2");
hook_func<int (__cdecl *)(unsigned char* dest, unsigned long* destLen, unsigned const char* source, unsigned long sourceLen)> uncompress(SERVER, "uncompress");

// global objects
hook_val<CDBScriptInfo> g_dbScriptInfo(SERVER, "g_dbScriptInfo");
hook_val<CCharacterMgr> g_characterMgr(SERVER, "g_characterMgr");
hook_val<CZoneScript> g_zoneScript(SERVER, "g_zoneScript");
hook_val<CMonParameterMgr> g_monParameter(SERVER, "g_monParameter");
hook_val<CFSMMgr> g_fsmMgr(SERVER, "g_fsmMgr");
hook_val<CITPMgr> g_itpMgr(SERVER, "g_itpMgr");
hook_val<CItemLog> g_itemLog(SERVER, "g_itemLog");
hook_val<CHSvrIO> g_hSvrIO(SERVER, "g_hSvrIO");
hook_val<CZSAcceptHandler> g_zsAcceptHandler(SERVER, "g_zsAcceptHandler");
hook_val<CErrorLog> g_errorLogs(SERVER, "g_errorLogs");
hook_val<CMVPInfo> g_mvpInfo(SERVER, "g_mvpInfo");
hook_val<CMapInfo> g_mapInfo(SERVER, "g_mapInfo");
hook_val<CNpcSvr> g_npcSvr(SERVER, "g_npcSvr");
hook_val<CPathData> g_pathData(SERVER, "g_pathData");
hook_val<CPathData> g_pathDataNpc(SERVER, "g_pathDataNpc");
hook_val<CStatpointPerLevel> g_statpointPerLevel(SERVER, "g_statpointPerLevel");
hook_val<CItemList> g_metalItemList(SERVER, "g_metalItemList");
hook_val<CItemList> g_weaponItemList(SERVER, "g_weaponItemList");
hook_val<CItemList> g_potionItemList(SERVER, "g_potionItemList");
hook_val<CExpParameter> g_expParameter(SERVER, "g_expParameter");
hook_val<CMaxHpSp> g_maxHpSp(SERVER, "g_maxHpSp");
hook_val<CAgitDB> g_AgitDB(SERVER, "g_AgitDB");
hook_val<CServerInfo> g_serverInfo(SERVER, "g_serverInfo");
hook_val<CNPCAddSkillInfo> g_npcAddSkillInfo(SERVER, "g_npcAddSkillInfo");
hook_val<CISvrIO> g_iSvrIO(SERVER, "g_iSvrIO");
hook_val<CCharMTInfo> g_charMTInfo(SERVER, "g_charMTInfo");
hook_val<CLogRecorder> g_logRecorder(SERVER, "g_logRecorder");
hook_val<CMakingLog> g_makingLog(SERVER, "g_makingLog");
hook_val<CGuildDB> g_ZGuildDB(SERVER, "g_ZGuildDB");
hook_val<CZGuildMgr> g_ZGuildMgr(SERVER, "g_ZGuildMgr");
hook_val<CImportantItem> g_importantItem(SERVER, "g_importantItem");
hook_val<CAuctionCtrl> g_AuctionCtrl(SERVER, "g_AuctionCtrl");
hook_val<CMapResMgr> g_mapResMgr(SERVER, "g_mapResMgr");
hook_val<CScriptEventMgr> g_scriptEventMgr(SERVER, "g_scriptEventMgr");
hook_val<CQuestEventMgr> g_questEventMgr(SERVER, "g_questEventMgr");
hook_val<CRefiningLog> g_refiningLog(SERVER, "g_refiningLog");
hook_val<CPvPScoreDB> g_pvpScoreDB(SERVER, "g_pvpScoreDB");
hook_val<CCharInfoDB> g_charInfoDB(SERVER, "g_charInfoDB");
hook_val<CPetDB> g_petDB(SERVER, "g_petDB");
hook_val<CMerceDB> g_merceDB(SERVER, "g_merceDB");
hook_val<CPCSkillDB> g_pcSkillDB(SERVER, "g_pcSkillDB");
hook_val<CCoupleInfoDB> g_coupleInfoDB(SERVER, "g_coupleInfoDB");
hook_val<CFamilyInfoDB> g_familyInfoDB(SERVER, "g_familyInfoDB");
hook_val<CMakerRankDB> g_makerRankDB(SERVER, "g_makerRankDB");
hook_val<CPKInfoMgr> g_PKInfoMgr(SERVER, "g_PKInfoMgr");
hook_val<CSkillTypeInfoMgr> g_skillTypeInfoMgr(SERVER, "g_skillTypeInfoMgr");
hook_val<CItemReuseLimit> g_itemReuseLimit(SERVER, "g_itemReuseLimit");
hook_val<CRoomMgr> g_roomMgr(SERVER, "g_roomMgr");
hook_val<CBuffInfoMgr> g_buffInfoMgr(SERVER, "g_buffInfoMgr");
hook_val<CSkillLog> g_skillLog(SERVER, "g_skillLog");
hook_val<CStatusLog> g_statusLog(SERVER, "g_statusLog");
hook_val<CCompositionLog> g_compositionLog(SERVER, "g_compositionLog");
hook_val<CPresentLog> g_presentLog(SERVER, "g_presentLog");
hook_val<CHomunLog> g_homunLog(SERVER, "g_homunLog");
hook_val<CMercenaryLog> g_MercenaryLog(SERVER, "g_MercenaryLog");
hook_val<CPetLog> g_petLog(SERVER, "g_petLog");
hook_val<CStatusPlusInfoByJLV> g_StatusPlusnfoByJLV(SERVER, "g_StatusPlusnfoByJLV");
hook_val<CLottoDB> g_lottoDB(SERVER, "g_lottoDB");
hook_val<CStorePasswordDB> g_storePasswordDB(SERVER, "g_storePasswordDB");
hook_val<CMEventDB> g_MEventDB(SERVER, "g_MEventDB");
hook_val<CPEventDB> g_PEventDB(SERVER, "g_PEventDB");
hook_val<CGlobalVarDB> g_globalVarDB(SERVER, "g_globalVarDB");
hook_val<CJobCodeForItem> g_jobCodeForItem(SERVER, "g_jobCodeForItem");
hook_val<CSpecialItemMgr> g_specialItmMgr(SERVER, "g_specialItmMgr");
hook_val<CPetDefaultValue> g_petDefaultValue(SERVER, "g_petDefaultValue");
hook_val<CSummonMonsterTable> g_summonMonsterTable(SERVER, "g_summonMonsterTable");
hook_val<CMakerRankMgr> g_makerRankMgr(SERVER, "g_makerRankMgr");
hook_val<CProcessTimeChecker> g_BodyItemLoadProcssTime(SERVER, "g_BodyItemLoadProcssTime");
hook_val<CProcessTimeChecker> g_StoreItemLoadProcssTime(SERVER, "g_StoreItemLoadProcssTime");
hook_val<CTestButton> ToggleButtonCriticalLog(SERVER, "ToggleButtonCriticalLog"); // (HMENU(20));
hook_val<CTestButton> ToggleButtonTraceLog(SERVER, "ToggleButtonTraceLog"); // (HMENU(21));
