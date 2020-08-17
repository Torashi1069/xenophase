#pragma once
#include "Enums.h" // MAX_CLIENTTYPE


extern class CWUCSStreamManager g_WUCSClient;
extern class CStreamManager g_UserStreamMgr;
extern class CStreamManager g_CharSvrStreamMgr;
extern class CInfoScript g_xmlFileUser;
extern class CInfoScript g_scrptConfig;
extern class CInfoScript g_scriptRestriction;
extern class CUserList g_userList;
extern class CCharacterServerInfo g_characterServerInfo[MAX_CLIENTTYPE];
extern class CAccountDB g_AccountDB[3];
extern class CUserDB g_UserDB;
extern class CCertificate g_certificate;
extern class CBillingConnection g_Billing;
extern class CBillingDB g_BillingDB;
extern int g_GameID[3];
extern int g_nVersion[MAX_CLIENTTYPE];
extern bool g_bProcessPermit;
extern bool g_bXmlFileUserCheck;
