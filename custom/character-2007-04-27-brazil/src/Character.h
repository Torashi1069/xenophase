#pragma once


/// Maximum supported number of character slots per account.
#define MAX_CHARINFO_SLOT_COUNT 15 // [patch] more character slots


extern class CStreamManager g_ZoneSvrStreamMgr;
extern class CStreamManager g_AccountStreamMgr;
extern class CStreamManager g_UserStreamMgr;
extern class CAsyncProcessMgr g_AsyncProcessMgr;
extern class CInfoScript g_characterConfig;
extern class CUserList g_UserList;
extern class CUserAuthenticate g_UserAuthenticate;
extern struct SSERVERINFO gLocalServerInfo;
extern DWORD g_dwLocalIP;
extern bool g_bProcessPermit;
extern bool g_bUsingCharacterPassword;
extern bool g_bAccountConnected;
extern char g_szTime[1024];


void MakeCHARACTER_INFO(struct SCHARINFO* pCharInfo, struct CHARACTER_INFO* pCharacter_Info_target);


enum AuthenticateConnectCharacter
{
	NOT_CONNECT_CHARACTER = 0,
	CONNECT_CHARACTER     = 1,
};

void PutConnectCharacter(int iAID, int iSlot);
enum AuthenticateConnectCharacter IsConnectCharacter(int iAID, int iSlot);
void DeleteConnectCharacter(int iAID);
