#pragma once


/// Maximum supported number of character slots per account.
#define MAX_CHARINFO_SLOT_COUNT 18


extern class CZsvrStreamMgr g_ZoneSvrStreamMgr;
extern class CStreamManager g_AccountStreamMgr;
extern class CUserStreamMgr g_UserStreamMgr;
extern class CAsyncProcessMgr g_AsyncProcessMgr;
extern class CCharacterConfig g_characterConfig;
extern class CUserList g_UserList;
extern class CUserAuthenticate g_UserAuthenticate;
extern struct SSERVERINFO gLocalServerInfo;
extern DWORD g_dwLocalIP;
extern bool g_bProcessPermit;
extern bool g_bUsingCharacterPassword;
extern bool g_bAccountConnected;
extern bool g_bEnableDelChar;
extern bool g_bEnableMakeChar;
extern int g_bEnableAdultCheck;
extern DWORD g_dwUSERKEEP_BY_CH_PING;


struct sConfig
{
	/* this+ 0 */ bool b_IsThirdJob;
	/* this+ 4 */ int nServerType;
	/* this+ 8 */ int nMax_User_Slot;
	/* this+12 */ int nNoraml_User_Slot;
	/* this+16 */ int nPremium_User_Slot;
	/* this+20 */ int nBillUser_Slot;
	/* this+24 */ int nProducibleSlot;
	/* this+28 */ int nEnable_PremiumService;
	/* this+32 */ bool bEnbale_AddPacket_KoreaBillinfo;
	/* this+33 */ bool bEnable_AddPacket_PayTypeinfo;
	/* this+34 */ bool bEnable_KoreaChangeName;
};
extern struct sConfig gconfig;


void MakeCHARACTER_INFO(const struct SCHARINFO* pCharInfo, struct CHARACTER_INFO* pCharacter_Info_target);


enum AuthenticateConnectCharacter
{
	NOT_CONNECT_CHARACTER = 0,
	CONNECT_CHARACTER     = 1,
};

void PutConnectCharacter(int iAID, int iSlot);
enum AuthenticateConnectCharacter IsConnectCharacter(int iAID, int iSlot);
void DeleteConnectCharacter(int iAID);
