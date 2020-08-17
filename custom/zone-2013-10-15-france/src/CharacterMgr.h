#pragma once
#include "Msg.h"
#include "MSGpar.h"
#include "NetLib/MemoryMgr.h"
class CCharacter;
class CPC;
class CNPC;
class CItem;
class CSkill;


enum enumCHARACTERMESSAGE
{
	CM_PICKUP                                     = 0,
	CM_THROW                                      = 1,
	CM_MAPMOVE                                    = 2,
	CM_REFUSE_ENTER                               = 3,
	CM_NOTIFY_BAN                                 = 4,
	CM_WARP_CHARACTER_BETWEENSERVER               = 5,
	CM_WARP_BETWEENSERVER                         = 6,
	CM_WHISPER                                    = 7,
	CM_WHISPER_ACK                                = 8,
	CM_RESTART_HSERVER                            = 9,
	CM_NOTIFY_MANNER_POINT_GIVEN                  = 10,
	CM_SUCCESSOFITEMREF                           = 11,
	CM_FAILUREOFITEMREF                           = 12,
	CM_ENABLEITEMMOVE                             = 13,
	CM_DISABLEITEMMOVE                            = 14,
	CM_DIALOG                                     = 15,
	CM_WAIT_DIALOG                                = 16,
	CM_CLOSE_DIALOG                               = 17,
	CM_MENU_LIST                                  = 18,
	CM_EXCHANGE_ITEM                              = 19,
	CM_CHECKPOINT                                 = 20,
	CM_SET_ITEM                                   = 21,
	CM_USER_COUNT                                 = 22,
	CM_PC_TOUCH_IN_NPC                            = 23,
	CM_REQ_NAME                                   = 24,
	CM_SEND_PACKET                                = 25,
	CM_FORCESEND_PACKET                           = 26,
	CM_PURCHASE_ITEM                              = 27,
	CM_CHAT                                       = 28,
	CM_DESTROY_ROOM                               = 29,
	CM_MULTICAST_DESTROY_ROOM                     = 30,
	CM_ROOM_NEWENTRY                              = 31,
	CM_MULTICAST_ROOM_NEWENTRY                    = 32,
	CM_SET_ROOMID                                 = 33,
	CM_EXCHANGE_ITEM_CANCEL                       = 34,
	CM_EXEC_EXCHANGE_ITEM                         = 35,
	CM_INIT_CACHEINFO_THEPC                       = 36,
	CM_CURRENT_STATE_LOG_NPC                      = 37,
	CM_SET_EFFFECTSTATE                           = 38,
	CM_CHANGE_MONEY                               = 39,
	CM_RESET_STAT                                 = 40,
	CM_RESET_SKILL                                = 41,
	CM_NOTIFY_INFOTOSECTION                       = 42,
	CM_NOTIFY_ITEMINFO_INMCSTORE                  = 43,
	CM_NOTIFY_STOREDITEM                          = 44,
	CM_CARTON                                     = 45,
	CM_CARTOFF                                    = 46,
	CM_ADD_MEMBER_TO_GROUP                        = 47,
	CM_DELETE_MEMBER_FROM_GROUP                   = 48,
	CM_ACK_MAKE_GROUP                             = 49,
	CM_GROUP_LIST                                 = 50,
	CM_GROUPINFO_CHANGE                           = 51,
	CM_ACK_REQ_JOIN_GROUP                         = 52,
	CM_REQ_JOIN_GROUP                             = 53,
	CM_NOTIFY_POSITION_PARTY                      = 54,
	CM_NOTIFY_POSITION_GUILD                      = 55,
	CM_NOTIFY_HP_PARTY                            = 56,
	CM_GRID_UPDATE                                = 57,
	CM_CHAT_PARTY                                 = 58,
	CM_DELETE_FROM_GROUPLIST                      = 59,
	CM_SAVE_ITEM                                  = 60,
	CM_ADD_EXP                                    = 61,
	CM_SHARE_EXP                                  = 62,
	CM_ADD_PARTYEXP                               = 63,
	CM_ADD_JOBEXP                                 = 64,
	CM_SHARE_JOBEXP                               = 65,
	CM_ADD_VIRTUE                                 = 66,
	CM_ADD_PARTYJOBEXP                            = 67,
	CM_ADD_MVPITEM                                = 68,
	CM_ADD_MVPEXP                                 = 69,
	CM_ADDSKILL                                   = 70,
	CM_TOUCHED_SKILLOBJECT                        = 71,
	CM_MOVE_STOP                                  = 72,
	CM_MOVE_STOP_FORCE                            = 73,
	CM_NUDE                                       = 74,
	CM_NZ_COMPASS                                 = 75,
	CM_DLG_WRITE                                  = 76,
	CM_INPUT_EDITDLG                              = 77,
	CM_INPUT_EDITDLGSTR                           = 78,
	CM_ZN_CLOSE_DIALOG                            = 79,
	CM_HEAL_BYPERCENT                             = 80,
	CM_SHOW_IMAGE                                 = 81,
	CM_CHANGEPALETTE                              = 82,
	CM_MYMONSTER_DEAD                             = 83,
	CM_ADD_MYMOB                                  = 84,
	CM_DISAPPEAR                                  = 85,
	CM_MAGICLOCKONED                              = 86,
	CM_PVP_PLUS_POINT                             = 87,
	CM_SKILL_LEVELUP                              = 88,
	CM_HP_PLUS                                    = 89,
	CM_SP_PLUS                                    = 90,
	CM_ATTACKSKILL_TOCHARACTER                    = 91,
	CM_SPATTACKSKILL_TOCHARACTER                  = 92,
	CM_OPERATIONSKILL_TOCHARACTER                 = 93,
	CM_OPERATIONSKILL_TOSELF                      = 94,
	CM_ATTSKILL_TOCHAR22_1                        = 95,
	CM_SPATTSKILL_TOCHAR22_1                      = 96,
	CM_OPERSKILL_TOCHAR22_1                       = 97,
	CM_OPERSKILL_TOSELF22_1                       = 98,
	CM_ATTSKILL_TOCHAR22_2                        = 99,
	CM_SPATTSKILL_TOCHAR22_2                      = 100,
	CM_OPERSKILL_TOCHAR22_2                       = 101,
	CM_OPERSKILL_TOSELF22_2                       = 102,
	CM_OPERSKILL_TO_GUILD                         = 103,
	CM_OPERSKILL_TO_RANGEGUILD                    = 104,
	CM_OPSKILL_TOSELF_MER                         = 105,
	CM_ATKSKILL_TOCHAR_MER                        = 106,
	CM_OPSKILL_TOCHAR_MER                         = 107,
	CM_OPSKILL_TOGROUND_MER                       = 108,
	CM_SKILL_BANUMSPLASHER                        = 109,
	CM_SKILL_EXPIRETIME                           = 110,
	CM_SKILL_UPDATEPARAMETER                      = 111,
	CM_HEAL_HP                                    = 112,
	CM_RANKINGINFO                                = 113,
	CM_NOTIFY_GROUNDSKILL                         = 114,
	CM_TIME_BODYSTATE                             = 115,
	CM_TIME_HEALTHSTATE                           = 116,
	CM_SETEFFECTIVE                               = 117,
	CM_RESETEFFECTIVE                             = 118,
	CM_EXT_SETEFFECTIVE                           = 119,
	CM_SKILL_GROUNDTYPE                           = 120,
	CM_SKILL_GROUNDTYPE22_1                       = 121,
	CM_SKILL_GROUNDTYPE22_2                       = 122,
	CM_CHANGE_STATUSPARM                          = 123,
	CM_AGI_CHANGE                                 = 124,
	CM_DEX_CHANGE                                 = 125,
	CM_INT_CHANGE                                 = 126,
	CM_LUK_CHANGE                                 = 127,
	CM_STR_CHANGE                                 = 128,
	CM_VIT_CHANGE                                 = 129,
	CM_TELEPORT_CHARACTER                         = 130,
	CM_WARP_CHARACTER                             = 131,
	CM_WARPPOSITION_REMEMBER                      = 132,
	CM_DECDEF_NPC                                 = 133,
	CM_BLESSING_FROM_ACOLYTE                      = 134,
	CM_CURE_FROM_ACOLYTE                          = 135,
	CM_SKILL_OWL                                  = 136,
	CM_SKILL_VULTURE                              = 137,
	CM_SKILL_INCCARRY                             = 138,
	CM_SKILL_VENDING                              = 139,
	CM_SKILL_ITEMIDENTIFY                         = 140,
	CM_SKILL_ADDIMITATION                         = 141,
	CM_USE_SKILL                                  = 142,
	CM_USE_GROUNDSKILL                            = 143,
	CM_SKILLOBJ_DECLIFECOUNT                      = 144,
	CM_RESET_EFFECTSTATE                          = 145,
	CM_SETINVINCIBLE                              = 146,
	CM_MODIFY_SKILLCOUNT                          = 147,
	CM_MODIFYDAMAGE_ATTACKED                      = 148,
	CM_SET_ATKPERCENT                             = 149,
	CM_SET_DEFPERCENT                             = 150,
	CM_GET_SKILLLEVEL                             = 151,
	CM_REFLECT_MAGIC                              = 152,
	CM_RESURRECTION                               = 153,
	CM_PUSH_SKILLOBJECT                           = 154,
	CM_ADD_ITEM                                   = 155,
	CM_ADD_RESERVED_EMPELIUM_ITEM                 = 156,
	CM_PET_DIE                                    = 157,
	CM_HOMUN_DIE                                  = 158,
	CM_MERCENARY_DIE                              = 159,
	CM_EMOTION                                    = 160,
	CM_NPCEVENTADDSKILL                           = 161,
	CM_NPCEVENTDELETESKILL                        = 162,
	CM_CHANGE_SPRITE                              = 163,
	CM_SHOWDIGIT                                  = 164,
	CM_AUTOSPELLLIST                              = 165,
	CM_PLAYSKILL_CANCEL                           = 166,
	CM_CLEAR_EVENT                                = 167,
	CM_AUTHORIZE_ITEM                             = 168,
	CM_DAMAGE_WEAPON                              = 169,
	CM_DAMAGE_ARMOR                               = 170,
	CM_PROCESSEFFECT_ATTACK                       = 171,
	CM_PROCESSEFFECT_KILL                         = 172,
	CM_GETMARRIED                                 = 173,
	CM_GETCOUNT_ITEMOFMYGID                       = 174,
	CM_REMOVE_ITEMOFMYGID                         = 175,
	CM_CREATE_ITEMOFMYGID                         = 176,
	CM_CREATE_ITEMOFOTHERGID                      = 177,
	CM_DAMAGE_EQUIPMENT                           = 178,
	CM_CHANGE_HAIRSTYLE                           = 179,
	CM_SHOWEFFECT                                 = 180,
	CM_SKILL_SG_KNOWLEDGE                         = 181,
	CM_SKILL_SG_DEVIL                             = 182,
	CM_SKILL_SG_FRIEND                            = 183,
	CM_UPDATE_PVPPOINT                            = 184,
	CM_SEND_DAMAGEPACKET                          = 185,
	CM_MOVED_SPITEM                               = 186,
	CM_GET_ENEMYAID                               = 187,
	CM_GET_CHARACTERID                            = 188,
	CM_GET_GRID_IFEXPSHARE                        = 189,
	CM_MERCE_PROPERTY                             = 190,
	CM_MERCE_FEED                                 = 191,
	CM_MOVE                                       = 192,
	CM_STOP                                       = 193,
	CM_MOVETO_MYOWNER                             = 194,
	CM_ATTACK_ENEMY                               = 195,
	CM_SAVE_CHARINFO                              = 196,
	CM_DELETE_CHARINFO                            = 197,
	CM_MERCE_SETDBINFO                            = 198,
	CM_OPENAUCTION                                = 199,
	CM_OPENMAILING                                = 200,
	CM_CONSUMESPECIALITEM                         = 201,
	CM_HUNTINGLIST                                = 202,
	CM_PLUS_HUNTINGLIST                           = 203,
	CM_SET_BOSS_IN_MAP                            = 204,
	CM_REQUEST_BOSSINFO                           = 205,
	CM_NOTIFY_BOSSINFO                            = 206,
	CM_REQ_ADD_BOSS_PCLIST                        = 207,
	CM_REQ_DEL_BOSS_PCLIST                        = 208,
	CM_SET_SCRIPT_EVENT_NO                        = 209,
	CM_OPEN_EDITDLGSTR                            = 210,
	CM_BAN                                        = 211,
	CM_UPDATE_SKILL_LIMIT_CNT                     = 212,
	CM_ADD_SPECIALZONELIST                        = 213,
	CM_DEL_SPECIALZONELIST                        = 214,
	CM_MERCE_DELETE                               = 215,
	CM_SET_MDEFPERCENT                            = 216,
	CM_RESET_DEFPERCENT                           = 217,
	CM_RESET_MDEFPERCENT                          = 218,
	CM_MERCE_TYPICALJOBINFO_CHANGED               = 219,
	CM_DEVOTIONLIST_REMOVE                        = 220,
	CM_NPCEVENT_RELOADMOBILEEVENT                 = 221,
	CM_KNOCKBACK                                  = 222,
	CM_KNOCKBACK_FORCE                            = 223,
	CM_KILLED                                     = 224,
	CM_QUEST_EVENTITEM                            = 225,
	CM_QUESTMISSION_HUNTINGLIST                   = 226,
	CM_NPCEVENT_RELOADMOBILEEVENT_EXCULUSIVE      = 227,
	CM_NPC_FORCE_USE_SKILL                        = 228,
	CM_MOVENPC_SPEEDCHANG                         = 229,
	CM_PROGRESSBAR                                = 230,
	CM_PROGRESSBAR_CANCEL                         = 231,
	CM_DLG_WRITE_STR                              = 232,
	CM_THIRDJOB_SKILL_ATTACK_TOCHARACTER          = 233,
	CM_THIRDJOB_SKILL_OPERATE_TOCHARACTER         = 234,
	CM_THIRDJOB_SKILL_TOGROUND                    = 235,
	CM_SKILL_ADDIMITATION3rd                      = 236,
	CM_INSTANTVAR_GET                             = 237,
	CM_INSTANTVAR_SET                             = 238,
	CM_INSTANTVAR_ADD                             = 239,
	CM_SET_EFFECTSTATE                            = 240,
	CM_SET_ITEM_PARTY                             = 241,
	CM_REQ_GROUPINFO_CHANGE_V2                    = 242,
	CM_SKILL_GROUNDTYPE_MER                       = 243,
	CM_ATTACKSKILL_TOCHARACTER_MER                = 244,
	CM_SPATTSKILL_TOCHAR22_2_MER                  = 245,
	CM_SPATTACKSKILL_TOCHARACTER_MER              = 246,
	CM_ATTSKILL_TOCHAR22_1_MER                    = 247,
	CM_OPERSKILL_TOSELF22_2_MER                   = 248,
	CM_ADD_HOMUN_RELATIONSHIP                     = 249,
	CM_CHECK_BATTLE_ENTER_STATE                   = 250,
	CM_MOVE_FROM_BATTLEFIELD                      = 251,
	CM_CHANGE_GROUP_MASTER                        = 252,
	CM_PLAY_BGM                                   = 253,
	CM_ELEMENTAL_DELETE                           = 254,
	CM_SKILL_BUYING_STORE                         = 255,
	CM_NOTIFY_ITEMINFO_INBUYUNG_STORE             = 256,
	CM_OPEN_SEARCH_STORE_INFO                     = 257,
	CM_MODIFY_FULLNESS                            = 258,
	CM_WHISPER_SSO                                = 259,
	CM_UNPACK_PACKAGEITEM                         = 260,
	CM_CREATE_MOB_TOMB                            = 261,
	CM_SHOWSCRIPT                                 = 262,
	CM_UPPEREXTENDEDJOB_SKILL_ATTACK_TOCHARACTER  = 263,
	CM_UPPEREXTENDEDJOB_SKILL_OPERATE_TOCHARACTER = 264,
	CM_UPPEREXTENDEDJOB_SKILL_TOGROUND            = 265,
	CM_CLEAR_DIALOG                               = 266,
	CM_NAVIGATION_ACTIVE                          = 267,
	CM_DIALOG2                                    = 268,
	CM_WAIT_DIALOG2                               = 269,
};


struct PC_INDEX_DATA
{
	/* this+0 */ int index;
	/* this+4 */ unsigned long connectionTime;
};


class CCharacterMgr
{
public:
//	bool InstantMapAdd(const int, const class CMapInfo &);
//	void InstantMapRemove(const int, const class std::basic_string<char,std::char_traits<char>,std::allocator<char> >);

public:
//	bool isOK() const;

private:
//	CCharacterMgr();
//	~CCharacterMgr();

public:
//	static bool CreateInstance();
//	static void DestroyInstance();
	static CCharacterMgr* GetObj(); /// @custom

private:
	/* static   */ static CCharacterMgr*& m_cpSelf; //TODO
	/* this+  4 */ bool m_bOK;

public:
//	void Init(int);
//	int AddCharacter(class CCharacter *);
//	void RemoveCharacter(class CCharacter *);
//	void Free(class CCharacter *);
//	class CItem * AllocItem();
//	class CItem * CreateItem(class CITP *, struct ITEM_INFO *);
//	class CItem * GetNeighborhoodItem(short, short, short, class CMapRes *);
//	class CSkill * AllocSkill();
//	class CSkill * CreateSkill3(const int, class CMapRes * const, const int, const int, const unsigned int, const char, const unsigned long, unsigned long, const short, const unsigned short, const int, const int, const int);
//	class CSkill * CreateSkill2(const unsigned int, const int, const int, class CMapRes * const, const int, const unsigned long, unsigned long, const short, const unsigned short, const int, const int, const int, const char);
private:
//	void ImplGetSkill(const int, const int, class std::vector<CSkill *,std::allocator<CSkill *> > &, class CMapRes *, class CCharacter *);
public:
//	class CSkill * GetSkillWithSKGroupUniqueID(const int, const int, const unsigned int, class CMapRes *);
//	class CSkill * GetSkill(int, int, int, class CMapRes *);
//	class CSkill * GetSkill(int, int, class CMapRes *);
//	int GetSkillList(int, int, class std::vector<CSkill *,std::allocator<CSkill *> > &, class CCharacter *, class CMapRes *);
//	bool IntersectionSkill(class CMapRes *, const int, const int, const int, const int);
//	void DestroyAllNPC();
//	class CNPC * AddNPC(void *, const unsigned long, const unsigned long);
	int GetMonsterCount();
	void SendMsgFromNPCServer(unsigned long senderAID, unsigned long receiverAID, CMsg* msg, unsigned long par1, unsigned long par2);
//	void SendToNPCServer(int, const char *);
//	void RegisterBossInMap(class CNPC *);
//	class CNPC * FindBossInMap(int);
//	bool CheckChashTraderNpc();
//	unsigned char GetNpcType(unsigned long);
//	void ClearBossInMap();
//	class CPC * AllocPC();
//	class CPC * FindPCByGID(unsigned long);
//	int FindPC(class CCharacter *);
//	int GetPCCountIntheMap(char *);
//	int GetPCFreeSize();
//	CPC* FindCharacterByIndex(const unsigned long, const int) const;
	CPC* FindCharacter(const char* characterName);
	CCharacter* FindCharacter(unsigned long AID, unsigned long Type);
//	unsigned long GetAID();
//	void PutAID(unsigned long);
//	class CCharacter * FastFindCharacter(unsigned long);
	int SendMsg(CCharacter* sender, unsigned long receiverID, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4);
	int SendMsg(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4);
//	void SendCommand(unsigned long, class CITZMsg *);
//	char * GetCharName(unsigned long);
//	void GetVar(unsigned long, class CMsg *, class CMsg *);
//	void GetVarFromPC(unsigned long, class CMsg *, class CMsg *);
//	void ProcessAllCharacter();
//	void Multicast(class CMapRes *, int, int, int, char *, int);
//	int GetCurPlayChar();
//	int GetCurValidPlayChar();
//	int GetCurDisconnectCountPlayChar();
//	void BroadCast(class CBroadCastFunc &);
//	void BroadCast(int, char *);
//	void BroadCastExceptME(int, char *, const char *);
	void SendToHServer(int len, const char* buf);
	void SendToIServer(int len, const char* buf);
//	class IVItEquipItem * GetEquipItem(unsigned long, unsigned long);
//	char * GetGuildName(unsigned long);
//	void AddWarpNpcList(class CMapRes *, class CNPC *);
//	void RemoveWarpNpcList(class CMapRes *, class CNPC *);
//	class std::vector<CNPC *,std::allocator<CNPC *> > GetWarpNpcList(class CMapRes *);
//	void Flush(int, int, int);
//	void ExpelOtherGuild(const int, const int);
//	int GetSkillSize();
//	int GetSkillObjCnt();
//	int GetSkillObjCapacity();
//	int GetItemObjCnt();
//	int GetItemObjCapacity();
//	void InitLotto();
//	short GetDistance(class CCharacter *, class CCharacter *);
//	int KickPlayerInMap(const int);
//	class CPC * GetOnePlayerInMap(const int);
//	void FinalDungeon_Skill(const class std::basic_string<char,std::char_traits<char>,std::allocator<char> >);
//	void FinalDungeon_Item(const class std::basic_string<char,std::char_traits<char>,std::allocator<char> >);
//	void FinalDungeon_Npc(const class std::basic_string<char,std::char_traits<char>,std::allocator<char> >);
//	void FinalDungeon_NpcEvent(const char *);

private:
//	CNPC* AllocNPC(unsigned char);
	CNPC* FindNPCByAID(unsigned long AID);
	CItem* SearchItem(unsigned long ITAID);
	CSkill* SearchSkill(unsigned long AID);
//	void AddPCToIndexInfo(unsigned long, int, unsigned long);
	CCharacter* SearchPCFromIndexInfo(unsigned long AID);
//	void DeletePCFromIndexInfo(unsigned long);
//	void OnDisconnect(class CPC *);
//	void OnDisconnect_STEP_NONE(class CPC *);
//	void OnDisconnect_STEP_REMOVE(class CPC *);
//	void OnDisconnect_STEP_ARRANGE(class CPC *);
//	void OnDisconnect_STEP_ASYNCDB_SAVE_REQUEST(class CPC * const);
//	void OnDisconnect_STEP_COMPLETE(class CPC *);
//	void OnDisconnect_STEP_ASYNCDB_SAVE_COMPLETE(class CPC *);
//	int IsSendable(class CPC *);

private:
	/* this+  8 */ CPC** m_PC;
	/* this+ 12 */ int m_PCCount;
	/* this+ 16 */ long m_curPlayChar;
	/* this+ 20 */ long m_curValidPlayChar;
	/* this+ 24 */ long m_curDisconnectCountPlayChar;
	/* this+ 28 */ BYTE m_pcMemoryPool[36]; //CMemoryMgr<CPC> m_pcMemoryPool; //TODO
	/* this+ 64 */ BYTE m_itemMemoryPool[36]; //CMemoryMgr<CItem> m_itemMemoryPool; //TODO
	/* this+100 */ BYTE m_skillMemoryPool[36]; //CMemoryMgr<CSkill> m_skillMemoryPool; //TODO
	/* this+136 */ std::map<unsigned long,CItem*> m_item;
	/* this+152 */ std::map<unsigned long,CSkill*> m_skill;
	/* this+168 */ std::map<int,CNPC*> m_npcMap;
	/* this+184 */ std::list<int> m_AIDPool;
	/* this+196 */ RTL_CRITICAL_SECTION m_csPC;
	/* this+220 */ std::map<unsigned long,PC_INDEX_DATA> m_pcNonclusteredIndex;
	typedef std::map<unsigned int,std::vector<unsigned int>> WARPNPCLIST;
	/* this+236 */ WARPNPCLIST m_WarpNPCList2nd;
	/* this+252 */ std::map<int,int> m_bossInMap;
};
