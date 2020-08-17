#pragma once


#define MAX_FRIENDS_LIST 40
#define MAX_GUILD_MEMBER_LIST 56


extern class CIGuildInfoDB& g_IGuildDB;
extern class CIGuildSkillDB& g_IGuildSkillDB;
extern class CExpParameter& g_expParameter;
extern class CPartyMgr& g_groupMgr;
extern class CServerInfo& g_serverInfo;
extern class CUserMgr& g_userMgr;
extern class CMClient& g_mServer;
extern class CUserLogMgr& g_UserLogMgr;
extern class CUserLogDB& g_UserLogDB;
extern class CFriendDB& g_FriendDB;
extern class CMakerRankMgr& g_MakerRankMgr;
extern BOOL& g_SendChkProrcessTime;
extern DWORD& g_sleep;
extern BOOL& g_isGuildAllSend;
extern BOOL& g_bSetUserCounter;
extern BOOL& g_isPacketLog;
extern BOOL& g_isBroadCastLog;
extern int& g_FunctionUniqueCnt;
extern const char* const g_infFile;
extern const char CHARACTER_DSN_FILE[];
extern const char LOG_DSN_FILE[];
extern const char GLOBALINFO_DSN_FILE[];
extern const char SCRIPT_DSN_FILE[];
extern const char IPINFO_DSN_FILE[];


enum enumSETTING { SETTING_GUILDWAR = 0 };
BOOL IsSetting(unsigned int setting);
