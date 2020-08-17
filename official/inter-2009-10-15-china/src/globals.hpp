#pragma once
#include "std/map"
class CZServerMgr;
class CUserMgr;
class CISAcceptHandler;
class CMGAcceptHandler;
class CAcceptThread;
class CServerInfo;
class CErrorLog;
class CMClientMgr;
class CPartyMgr;
class CMailCtrl;
class CMapInfo;
class CExpParameter;
class CIGuildInfoDB;
class CIGuildSkillDB;
class CFriendDB;
class CMakerRankMgr;


// global defines
#define MAX_FRIENDS_LIST 40


// global variables
extern char(& g_szCriticalLogFileName)[260];
extern char(& g_szTraceLogFileName)[260];
extern CZServerMgr& g_zServerMgr;
extern DWORD& g_sleep;
extern int& g_MaxProcessTime;
extern int& g_SendChkProrcessTime;
extern CUserMgr& g_userMgr;
extern int& g_userMgrUserCount;
extern int& g_userMgrFreeSize;
extern CISAcceptHandler& _g_isAcceptHandler;
extern CMGAcceptHandler& _g_isMGAcceptHandler;
extern int& g_isExtendDB;
extern void (__cdecl*& Trace)(const char* str, ...);
extern CAcceptThread*& gcpAcceptThread;
extern CAcceptThread*& gcpManagerAcceptThread;
extern CServerInfo& g_serverInfo;
extern int& g_isCriticalLog;
extern bool& g_bOutput;
extern int& g_bInterServerClose;
extern CErrorLog& g_errorLogs;
extern LPCSTR& g_infFile;
extern HWND& ghWnd;
extern CMClientMgr& g_mServerMgr;
extern int& g_MServerSize;
extern CPartyMgr& g_groupMgr;
extern int& g_groupMgrGroupSize;
extern int& g_groupMgrFreeSize;
extern int& g_IGuildMgrGuildSize;
extern int& g_IGuildMgrFreeSize;
extern CMailCtrl& g_MailCtrl;
extern RTL_CRITICAL_SECTION& g_csTraceLog;
extern RTL_CRITICAL_SECTION& g_exception_symbol_cs;
extern int& g_isGUILDWAR;
extern int& g_MaxUser;
extern int& g_MaxParty;
extern int& g_MaxGuild;
extern int& g_isGuildAllSend;
extern int& g_bSetUserCounter;
extern int& g_isCriticalLog;
extern int& g_isPacketLog;
extern int& g_isBroadCastLog;
extern CMapInfo& g_mapInfo;
extern mystd::map<int,int>& g_packetLenMap;
extern CExpParameter& g_expParameter;
extern CIGuildInfoDB& g_IGuildDB;
extern CIGuildSkillDB& g_IGuildSkillDB;
extern CFriendDB& g_FriendDB;
extern CMakerRankMgr& g_MakerRankMgr;
extern unsigned long& g_FunctionUniqueCnt;
extern int& gViewMode;
extern DWORD& g_SIDProcessTime;
extern double& g_IZProcessTime;
extern double& g_ZIProcessTime;
extern int& g_maxConnectClient;
