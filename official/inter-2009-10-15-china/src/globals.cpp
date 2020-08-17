#include "globals.hpp"


// global variables
char(& g_szCriticalLogFileName)[260] = *(char(*)[260])DetourFindFunction(SERVER, "g_szCriticalLogFileName"); // = "criticalError(Oct 15 2009).txt";
char(& g_szTraceLogFileName)[260] = *(char(*)[260])DetourFindFunction(SERVER, "g_szTraceLogFileName"); // = "TraceLog(Oct 15 2009).txt";
CZServerMgr& g_zServerMgr = *(CZServerMgr*)DetourFindFunction(SERVER, "g_zServerMgr");
DWORD& g_sleep = *(DWORD*)DetourFindFunction(SERVER, "g_sleep"); // = ?
int& g_MaxProcessTime = *(int*)DetourFindFunction(SERVER, "g_MaxProcessTime"); // = ?
int& g_SendChkProrcessTime = *(int*)DetourFindFunction(SERVER, "g_SendChkProrcessTime"); // = ?
CUserMgr& g_userMgr = *(CUserMgr*)DetourFindFunction(SERVER, "g_userMgr"); // = ?
int& g_userMgrUserCount = *(int*)DetourFindFunction(SERVER, "g_userMgrUserCount"); // = ?
int& g_userMgrFreeSize = *(int*)DetourFindFunction(SERVER, "g_userMgrFreeSize"); // = ?
CISAcceptHandler& _g_isAcceptHandler = *(CISAcceptHandler*)DetourFindFunction(SERVER, "_g_isAcceptHandler"); // = ?
CMGAcceptHandler& _g_isMGAcceptHandler = *(CMGAcceptHandler*)DetourFindFunction(SERVER, "_g_isMGAcceptHandler"); // = ?
int& g_isExtendDB = *(int*)DetourFindFunction(SERVER, "g_isExtendDB"); // = ?
void (__cdecl*& Trace)(const char* str, ...) = *(void(__cdecl **)(const char* str, ...))DetourFindFunction(SERVER, "Trace"); // = &TraceO;
CAcceptThread*& gcpAcceptThread = *(CAcceptThread**)DetourFindFunction(SERVER, "gcpAcceptThread"); // = ?
CAcceptThread*& gcpManagerAcceptThread = *(CAcceptThread**)DetourFindFunction(SERVER, "gcpManagerAcceptThread"); // = ?
CServerInfo& g_serverInfo = *(CServerInfo*)DetourFindFunction(SERVER, "g_serverInfo"); // = ?
bool& g_bOutput = *(bool*)DetourFindFunction(SERVER, "g_bOutput"); // = ?
int& g_bInterServerClose = *(int*)DetourFindFunction(SERVER, "g_bInterServerClose"); // = ?
CErrorLog& g_errorLogs = *(CErrorLog*)DetourFindFunction(SERVER, "g_errorLogs"); // = ?
LPCSTR& g_infFile = *(LPCSTR*)DetourFindFunction(SERVER, "g_infFile"); // = ".\\Inter.inf";
HWND& ghWnd = *(HWND*)DetourFindFunction(SERVER, "ghWnd"); // = ?
CMClientMgr& g_mServerMgr = *(CMClientMgr*)DetourFindFunction(SERVER, "g_mServerMgr"); // = ?
int& g_MServerSize = *(int*)DetourFindFunction(SERVER, "g_MServerSize"); // = ?
CPartyMgr& g_groupMgr = *(CPartyMgr*)DetourFindFunction(SERVER, "g_groupMgr"); // = ?
int& g_groupMgrGroupSize = *(int*)DetourFindFunction(SERVER, "g_groupMgrGroupSize"); // = ?
int& g_groupMgrFreeSize = *(int*)DetourFindFunction(SERVER, "g_groupMgrFreeSize"); // = ?
int& g_IGuildMgrGuildSize = *(int*)DetourFindFunction(SERVER, "g_IGuildMgrGuildSize"); // = ?
int& g_IGuildMgrFreeSize = *(int*)DetourFindFunction(SERVER, "g_IGuildMgrFreeSize"); // = ?
CMailCtrl& g_MailCtrl = *(CMailCtrl*)DetourFindFunction(SERVER, "g_MailCtrl"); // = ?
RTL_CRITICAL_SECTION& g_csTraceLog = *(RTL_CRITICAL_SECTION*)DetourFindFunction(SERVER, "g_csTraceLog"); // = ?
RTL_CRITICAL_SECTION& g_exception_symbol_cs = *(RTL_CRITICAL_SECTION*)DetourFindFunction(SERVER, "g_exception_symbol_cs"); // = ?
int& g_isGUILDWAR = *(int*)DetourFindFunction(SERVER, "g_isGUILDWAR"); // = 1;
int& g_MaxUser = *(int*)DetourFindFunction(SERVER, "g_MaxUser"); // = ?
int& g_MaxParty = *(int*)DetourFindFunction(SERVER, "g_MaxParty"); // = ?
int& g_MaxGuild = *(int*)DetourFindFunction(SERVER, "g_MaxGuild"); // = ?
int& g_isGuildAllSend = *(int*)DetourFindFunction(SERVER, "g_isGuildAllSend"); // = ?
int& g_bSetUserCounter = *(int*)DetourFindFunction(SERVER, "g_bSetUserCounter"); // = ?
int& g_isCriticalLog = *(int*)DetourFindFunction(SERVER, "g_isCriticalLog"); // = ?
int& g_isPacketLog = *(int*)DetourFindFunction(SERVER, "g_isPacketLog"); // = ?
int& g_isBroadCastLog = *(int*)DetourFindFunction(SERVER, "g_isBroadCastLog"); // = ?
CMapInfo& g_mapInfo = *(CMapInfo*)DetourFindFunction(SERVER, "g_mapInfo"); // = ?
mystd::map<int,int>& g_packetLenMap = *(mystd::map<int,int>*)DetourFindFunction(SERVER, "g_packetLenMap"); // = ?
CExpParameter& g_expParameter = *(CExpParameter*)DetourFindFunction(SERVER, "g_expParameter"); // = ?
CIGuildInfoDB& g_IGuildDB = *(CIGuildInfoDB*)DetourFindFunction(SERVER, "g_IGuildDB");
CIGuildSkillDB& g_IGuildSkillDB = *(CIGuildSkillDB*)DetourFindFunction(SERVER, "g_IGuildSkillDB");
CFriendDB& g_FriendDB = *(CFriendDB*)DetourFindFunction(SERVER, "g_FriendDB");
CMakerRankMgr& g_MakerRankMgr = *(CMakerRankMgr*)DetourFindFunction(SERVER, "g_MakerRankMgr");
unsigned long& g_FunctionUniqueCnt = *(unsigned long*)DetourFindFunction(SERVER, "g_FunctionUniqueCnt"); // = 0;
int& gViewMode = VTOR<int>(DetourFindFunction(SERVER, "gViewMode")); // = ?;
DWORD& g_SIDProcessTime = VTOR<DWORD>(DetourFindFunction(SERVER, "g_SIDProcessTime")); // = ?;
double& g_IZProcessTime = VTOR<double>(DetourFindFunction(SERVER, "g_IZProcessTime")); // = ?;
double& g_ZIProcessTime = VTOR<double>(DetourFindFunction(SERVER, "g_ZIProcessTime")); // = ?;
int& g_maxConnectClient = VTOR<int>(DetourFindFunction(SERVER, "g_maxConnectClient")); // = ?;
