#pragma once
#include "Enums.h"


/// upper limit on AID values
#define MAX_ACCOUNTID 10000000


extern class CCompletionPort g_compltport;
extern class CStreamManager g_UserStreamMgr;
extern class CStreamManager g_CharSvrStreamMgr;
extern class CAsyncProcessMgr g_AsyncProcessMgr;
extern class CInfoScript g_xmlFileUser;
extern class CInfoScript g_scrptConfig;
extern class CInfoScript g_scriptRestriction;
extern class CScriptParser CharServerInfo;
extern class CUserList g_userList;
extern class CCharacterServerInfo g_characterServerInfo[MAX_CLIENTTYPE];
extern class CAccountDB g_AccountDB[5];
extern class CUserDB g_UserDB;
extern class CSakrayUserDB g_SakrayUserDB;
extern class CCertificate g_certificate;
extern class CBillingConnection g_Billing;
extern class CBillingDB g_BillingDB;
extern class CListedPCBangIPList gListedPCBangipLists;
extern class CSakrayAID g_SakrayAID;
extern int GAME_ID;
extern int g_nVersion[MAX_CLIENTTYPE];
extern char g_szModuleFileName[MAX_PATH];
extern int g_LocalSID;
extern bool g_bProcessPermit;
extern bool g_bXmlFileUserCheck;
extern bool gbUpdateThreadRun;
extern bool gbUpdateThreadEnd;


bool IsFreeServerSID(int nSID);
void __cdecl UpdateInfoThread(void* lpVoid);
