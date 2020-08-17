#pragma once


#define DYN_MINIMUM_AID 1
#define DYN_MAXIMUM_AID 50000
#define NPC_MINIMUM_AID 50001
#define NPC_MAXIMUM_AID 99999
#define PC_MINIMUM_AID  100000
#define PC_MINIMUM_GID  100000


/// from ZoneProcess.cpp
extern class CBuffInfoMgr& g_buffInfoMgr;
extern class CMercenaryLog& g_MercenaryLog;
extern class CScriptEventMgr& g_scriptEventMgr;
extern class CMapResMgr& g_mapResMgr;
extern class CZSAcceptHandler& g_zsAcceptHandler;
extern class CFSMMgr& g_fsmMgr;
extern class CRoomMgr& g_roomMgr;
extern class CLog& g_errorLog;
extern class CMonParameterMgr& g_monParameter;
extern class CMVPInfo& g_mvpInfo;
extern class CITPMgr& g_itpMgr;
extern class CExpParameter& g_expParameter;
extern class CCharInfoDB& g_charInfoDB;
extern class CPCSkillDB& g_pcSkillDB;
extern class CMerceDB& g_merceDB;
extern class CStatusPlusInfoByJLV& g_StatusPlusnfoByJLV;
extern class CZoneScript& g_zoneScript;
extern class CItemList& g_metalItemList;
extern class CItemList& g_weaponItemList;
extern class CItemList& g_potionItemList;
extern class CZGuildMgr& g_ZGuildMgr;
extern class CZGuildInfoDB& g_ZGuildDB;
extern class CPvPScoreDB& g_pvpScoreDB;
extern class CAgitDB& g_AgitDB;
extern class CImportantItem& g_importantItem;
extern class CStackDumpLog& g_stackdumpLog;
extern class CQuestEventMgr& g_questEventMgr;
extern class CQuestArlimi& g_questArlimi;
extern class CTestButton& ToggleButtonCriticalLog;
extern class CTestButton& ToggleButtonTraceLog;
extern class CTestButton& ToggleButtonKillZone;
extern class CTestButton& ToggleButtonDisconnectLog;
extern class CItemLog& g_itemLog;
extern class CChangeMaterialLog& g_ChagneMaterialLog;
extern class CPetDefaultValue& g_petDefaultValue;
extern class CPetDB& g_petDB;
extern class CNPCAddSkillInfo& g_npcAddSkillInfo;
extern class CMEventDB& g_MEventDB;
extern class CPEventDB& g_PEventDB;
extern class CGlobalVarDB& g_globalVarDB;
extern class CJobCodeForItem& g_jobCodeForItem;
extern class CBotMngr& g_botMngr;
extern class CMakerRankDB& g_makerRankDB;
extern class CMakerRankMgr& g_makerRankMgr;
extern class CPKInfoMgr& g_PKInfoMgr;
extern class CStorePasswordDB& g_storePasswordDB;
extern class CLottoDB& g_lottoDB;
extern class CAuctionCtrl& g_AuctionCtrl;
extern class CStatpointPerLevel& g_statpointPerLevel;
extern class CDBScriptInfo& g_dbScriptInfo;
extern class CPathData& g_pathData;
extern class CPathData& g_pathDataNpc;
/// from CProcessMgr.cpp
extern class CNpcSvr& g_npcSvr;
extern class CNewLogRecoder& g_logRecorder;
extern class CSpecialItemMgr& g_specialItmMgr;
extern class CCharMTInfo& g_charMTInfo;
extern class CSkillTypeInfoMgr& g_skillTypeInfoMgr;
extern class CUserBlockMgr& g_UserBlockMgr;
extern class CMakingLog& g_makingLog;
extern class CRefiningLog& g_refiningLog;
extern class CSkillLog& g_skillLog;
extern class CStatusLog& g_statusLog;
extern class CCompositionLog& g_compositionLog;
extern class CPresentLog& g_presentLog;
extern class CHomunLog& g_homunLog;
extern class CGMWhisperLog& g_gmWhisperLog;
/// from ITPMgr.cpp
extern class CItemListV2& g_NotDisappearAfterUsingItemList;
extern class CBuyingStoreItemList& g_BuyingStoreItemList;

extern HINSTANCE& g_hInst;
extern HWND& g_hWnd;
extern time_t& g_curTime;
extern int& g_ZoneInterLoginValue;
extern int& g_ZoneInterLoginError;
extern int& g_loopCountPerSec;
extern bool& g_IsDisconnectAll;
extern char(& g_dbPWD)[256];
extern char(& g_GlobaldbPWD)[256];
extern BOOL& g_isNEWHPSP;
extern BOOL& g_isMANNER_POINT;
extern BOOL& g_isKillerSystem;
extern __int64& g_KillerExpireTime;
extern int& g_characterServerPort;
extern BOOL& g_isNpcSkip;
extern int& SPEEDHACK_DETECTETIME;
extern BOOL& g_IsAbleDrop;
extern int& g_deadExpPenalty;
extern int& g_deadEquipItemPenalty;
extern BOOL& g_siegeV15On;
extern BOOL& g_isMobileEventOn;
extern int& g_AMTterm;
extern int& g_maxSkill;
extern BOOL& g_isPacketLog;
extern BOOL g_reqUserCount;
extern int& g_extensionDropTime;
extern int& g_MaxZenyStore;
extern int& g_MaxZenyStoreLog;
extern int& g_BotDenyManner;
extern BOOL& g_isGuildDelete;
extern BOOL& g_isGuildEmergencyCall;
extern char(& g_dataPath)[MAX_PATH];
extern char(& g_npcDataPath)[MAX_PATH];
extern char(& g_remoteAccount)[MAX_PATH];
extern char(& g_remotePassword)[MAX_PATH];
extern DWORD& g_storePasswordPanaltyTime;
extern DWORD& g_storePasswordPanaltyCount;
extern BOOL& g_storePasswordCheck;
extern BOOL& g_lottoCheck;
extern int& g_compositionLogVersion;
extern DWORD& g_cashShopPasswordPanaltyTime;
extern DWORD& g_cashShopPasswordPanaltyCount;
extern BOOL& g_cashShopPasswordCheck;
extern BOOL& g_castleMapMoveCheck;
extern BOOL& g_isGameGuardOn;
extern int& g_isGameGuardCheckTime;
extern int& g_isGameGuardInitTime;
extern short& g_isGameGuardLogLevel;
extern BOOL& g_gameGuardSwitch;
extern int& g_empelium_hp;
extern BOOL& g_isEventMonsterOn;
extern BOOL& g_isSendMailOn;
extern BOOL& g_isAddMailItem;
extern BOOL& g_EventLog;
extern unsigned long& g_BootyItem;
extern int& g_ForeignCode;
extern int& g_freeServer;
extern int& g_npcDisappear;
extern BOOL& g_Free_Server;
extern int& g_teleportSPCost;
extern BOOL& g_ZenyChecksum;
extern int& g_StoreMaxItemSize;
extern BOOL& g_bPremium_Service;
extern short g_mEventMaxCount;
extern BOOL& g_wrIteNpcEventLog;
extern int(& g_backpedalTable)[8][2];
/// from CProcessMgr.cpp
extern double& g_ProcessTime;
extern double& g_MaxProcessTime;

extern const char g_infFile[];
extern const char CHARACTER_DSN_FILE[];
extern const char LOG_DSN_FILE[];
extern const char GLOBALINFO_DSN_FILE[];
extern const char SCRIPT_DSN_FILE[];
extern const char IPINFO_DSN_FILE[];
extern const char CASHSHOT_DSN_FILE[];


const char* GetCharDBPwd();
namespace HELP_HEALTHSTATE {
std::vector<int> GetHealthStateList();
std::vector<int> GetMyHealthStateList(const int in_state);
}; // namespace


struct MS_MAPMOVE
{
	void Set(const char* map, short x, short y, unsigned long npcAID)
	{
		strcpy(this->mapName, map);
		this->xPos = x;
		this->yPos = y;
		this->AID = npcAID;
	}

	/* this+0 */ unsigned long AID;
	/* this+4 */ short xPos;
	/* this+6 */ short yPos;
	/* this+8 */ char mapName[16];
};


struct MS_NAVIGATIONINFO
{
	void Set(const char* map, const unsigned char FindType, const unsigned char SetType, const bool isHide, const short x, const short y, const char* mobName)
	{
		strcpy(this->mapName, map);
		this->FindType = FindType;
		this->SetType = SetType;
		this->isHide = isHide;
		this->xPos = x;
		this->yPos = y;
		strcpy(this->mobName, mobName);
	}

	/* this+ 0 */ char mapName[16];
	/* this+16 */ unsigned char FindType;
	/* this+17 */ unsigned char SetType;
	/* this+18 */ bool isHide;
	/* this+20 */ short xPos;
	/* this+22 */ short yPos;
	/* this+24 */ char mobName[24];
};


struct SKILLATTACK_MSG
{
	SKILLATTACK_MSG()
	{
		this->skLevel = 0;
		this->msgtype = 0;
		this->srcAID = 0;
		this->par1 = 0;
		this->isDivide = 0;
		this->count = 1;
		this->isEnableDirectPath = true;
		this->finalDamage = 0;
		this->bSilenceSkill = false;
		this->Property = -1;
	}

	short GetType()
	{
		return this->msgtype;
	}

	void SetType(short type)
	{
		this->msgtype = type;
	}

	/* this+ 0 */ unsigned long targetAID;
	/* this+ 4 */ unsigned short SKID;
	/* this+ 8 */ unsigned long srcAID;
	/* this+12 */ short level;
	/* this+14 */ short count;
	/* this+16 */ short xPos;
	/* this+18 */ short yPos;
	/* this+20 */ short msgtype;
	/* this+24 */ int par1;
	/* this+28 */ unsigned char actionType; // enumACTIONTYPE
	/* this+32 */ int isDivide;
	/* this+36 */ short skLevel;
	/* this+38 */ bool isEnableDirectPath;
	/* this+40 */ int finalDamage;
	/* this+44 */ bool bSilenceSkill;
	/* this+45 */ char Property;
};


struct WARP_POSITION
{
	WARP_POSITION()
	{
		this->xPos = 0;
		this->yPos = 0;
		memset(this->mapName, '\0', sizeof(this->mapName));
	}

	WARP_POSITION(const WARP_POSITION& in_rhs)
	{
		this->xPos = in_rhs.xPos;
		this->yPos = in_rhs.yPos;
		strcpy_s(this->mapName, countof(this->mapName), in_rhs.mapName);
	}

	/* this+0 */ short xPos;
	/* this+2 */ short yPos;
	/* this+4 */ char mapName[16];
};


struct HO_SKINFO
{
	HO_SKINFO()
	{
		this->level = 0;
//		this->type = 0;
		this->count = 0;
		this->BlockUseTM = 0;
		this->bDBupdateWhenLogout = false;
	}

	/* this+ 0 */ int level;
	/* this+ 4 */ int type;
	/* this+ 8 */ int count;
	/* this+12 */ DWORD BlockUseTM;
	/* this+16 */ bool bDBupdateWhenLogout;
};


struct AmountValue
{
	/* this+0 */ DWORD time;
	/* this+4 */ int resetAmount;

	AmountValue(DWORD _time, int _resetAmount)
	{
		time = _time;
		resetAmount = _resetAmount;
	}
};
