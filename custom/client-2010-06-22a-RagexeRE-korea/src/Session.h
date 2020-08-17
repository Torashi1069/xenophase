#pragma once
#include "Lua.h"
#include "Enum.h"
#include "Struct.h"
#include "std/utility"
#include "std/vector"
#include "std/string"
class CGameActor;
struct ITEM_INFO;


#pragma pack(push,1)
class CSession
{
public:
	/* this+    0 */ BYTE dummy_0[3848];
	/* this+ 3848 */ mystd::string m_selectedServerName;
	/* this+ 3864 */ BYTE dummy_3864[16];
	/* this+ 3880 */ int m_diffTime;
	/* this+ 3884 */ char m_curMap[20];
	/* this+ 3904 */ int m_numLatePacket;
	/* this+ 3908 */ BYTE dummy_3908[24];
	/* this+ 3932 */ char m_cName[64];
	/* this+ 3996 */ BYTE dummy_3996[64];
	/* this+ 4060 */ TAG_CHARACTER_BLOCK_INFO m_charBlockInfo2[42];
	/* this+ 5068 */ BYTE dummy_5068[4]; // padding?
	/* this+ 5072 */ int m_sex;
	/* this+ 5076 */ BYTE dummy_5076[4];
	/* this+ 5080 */ int m_authCode;
	/* this+ 5084 */ unsigned long m_userLevel;
	/* this+ 5088 */ DWORD m_lastLoginIP;
	/* this+ 5092 */ char m_lastLoginTime[40];
	/* this+ 5132 */ int m_head;
	/* this+ 5136 */ int m_weapon;
	/* this+ 5140 */ int m_shield;
	/* this+ 5144 */ int m_bodyPalette;
	/* this+ 5148 */ int m_headPalette;
	/* this+ 5152 */ int m_accessory;
	/* this+ 5156 */ int m_accessory2;
	/* this+ 5160 */ int m_accessory3;
	/* this+ 5164 */ int m_bodyState;
	/* this+ 5168 */ int m_healthState;
	/* this+ 5172 */ int m_effectState;
	/* this+ 5176 */ int m_posX;
	/* this+ 5180 */ int m_posY;
	/* this+ 5184 */ int m_dir;
	/* this+ 5188 */ BYTE dummy_5188[56];
	/* this+ 5244 */ int m_isShowWhisperWnd;
	/* this+ 5248 */ int m_isPlayWhisperOpenSound;
	/* this+ 5252 */ int m_isShowWhisperWnd_Friend;
	/* this+ 5256 */ BYTE dummy_5256[36];
	/* this+ 5292 */ mystd::vector<const char*> m_newPcSexNameTable;
	/* this+ 5308 */ BYTE dummy_5308[128];
	/* this+ 5436 */ mystd::vector<const char*> m_jobNameTable;
	/* this+ 5452 */ BYTE dummy_5452[76];
	/* this+ 5528 */ unsigned long m_petGID;
	/* this+ 5532 */ BYTE dummy_5532[36];
	/* this+ 5568 */ int m_petAcc;
	/* this+ 5572 */ int m_petJob;
	/* this+ 5576 */ BYTE dummy_5576[4];
	/* this+ 5580 */ int m_petHungry;
	/* this+ 5584 */ int m_petFriendly;
	/* this+ 5588 */ int m_petEggIndex;
	/* this+ 5592 */ BYTE dummy_5592[4];
	/* this+ 5596 */ int m_petEmotionTable[5][5][7]; // [hungryState][friendlyState][action?]
	/* this+ 6296 */ BYTE dummy_6296[524];
	/* this+ 6820 */ unsigned long m_aid;
	/* this+ 6824 */ unsigned long m_gid;
	/* this+ 6828 */ BYTE dummy_6828[380];
	/* this+ 7208 */ mystd::list<FRIEND_INFO> m_partyList;
	/* this+ 7220 */ mystd::list<FRIEND_INFO> m_friendList;
	/* this+ 7232 */ BYTE dummy_7232[3688];
	/* this+10920 */ mystd::vector<mystd::pair<const char*,TALKTYPE>> m_talkTypeTable;
	/* this+10936 */ BYTE dummy_10936[952];
	/* this+11888 */ int m_isQ2begin;
	/* this+11892 */ BOOL m_isNoTalkMsg;
	/* this+11896 */ BOOL m_isNoTalkMsg2;
	/* this+11900 */ BYTE dummy_11900[66];
	/* this+11966 */ bool m_isCheckToPcbang;
	/* this+11967 */ BYTE dummy_11967[1];
	/* this+11968 */ int m_SelectAccountNumber;
	/* this+11972 */ BYTE dummy_11972[172];
	/* this+12144 */ DWORD m_playingTime;
	/* this+12148 */ BYTE dummy_12148[76];
	/* this+12224 */ unsigned long m_homunGID;
	/* this+12228 */ BYTE dummy_12228[140];
	/* this+12368 */ BOOL m_homunAlive;
	/* this+12372 */ BYTE dummy_12372[20];
	/* this+12392 */ unsigned long m_merGID;
	/* this+12396 */ BYTE dummy_12396[136];
	/* this+12532 */ BOOL m_merAlive;
	/* this+12536 */ BYTE dummy_12536[172];
	/* this+12708 */ int m_StateInfoOn;
	/* this+12712 */ BYTE dummy_12712[4];
	/* this+12716 */ int m_numChar;
	/* this+12720 */ int field_31B0_TotalSlotNum;
	/* this+12724 */ int field_31B4_PremiumStartSlot;
	/* this+12728 */ int field_31B8_PremiumEndSlot;
	/* this+12732 */ int m_nCharBlockInfoCount;
	/* this+12736 */ CLua* m_lua;
	/* this+12740 */ int m_DrawList[100];
	/* this+13140 */ //TODO

	public: void CSession::Init(void);
	public: void CSession::Create(void);
	public: void CSession::InitTalkTypeTable(void);
	public: int CSession::GetTalkType(const char* chatBuf, TALKTYPE* talkType, mystd::string param[3]);
	public: char* CSession::GetAccessoryActName(int job, int* head, int sex, int accessory, char* buf);
	public: void CSession::ChangeXorValue(void);
	public: void CSession::InvalidateBasicWnd(void);
	public: TALKTYPE CSession::GetNoParamTalkType(const char* command);
	public: void CSession::InitPetTalkTable(void);
	public: void CSession::WriteOptionToLuaFile(void);
	public: void CSession::ClearEquipItem(void);
	public: void CSession::ClearEquipItemInInventory(void);
	public: BOOL CSession::IsPetEgg(int itemId);
	public: void CSession::SetItem(ITEM_INFO* itemInfo);
	public: bool CSession::AddItem(ITEM_INFO* itemInfo);
	public: void CSession::DecItem(unsigned long index, int numItem);
	public: bool CSession::AddEquipItem(ITEM_INFO* itemInfo);
	public: bool CSession::AddStoreItem(ITEM_INFO* itemInfo);
	public: BOOL CSession::IsMerOrHomun(int job);
	public: bool CSession::IsMyHomunGID(int GID);
	public: bool CSession::IsMyMerGID(int GID);
	public: BOOL CSession::IsPc(int job);
	public: BOOL CSession::IsThisPC(int job);
	public: char* CSession::GetPetAccActName(int accId);
	public: int CSession::IsSiegeMode();
	public: int CSession::IsGuardian(int job);
	public: void CSession::SetServerTime(DWORD startTime);
	public: void CSession::UpdateServerTime(unsigned long startTime);
	public: void CSession::SetPlayerPosDir(int x, int y, int dir);
	public: BOOL CSession::IsAttack(int act);
	public: int CSession::GetPetHungryState(int Hunger);
	public: int CSession::GetPetFriendlyState(int Friendly);
	public: int CSession::GetPetTalkNumber(int job, int act, int hungry);
	public: void CSession::GetMonsterTalkInfo(int job, int stateId, int arg1, char* speak, unsigned long gid);
	BOOL IsFriendName(const char* cName);
	BOOL IsGuildMember(const char* cName);
	BOOL IsCheatName(const char* cName);
	BOOL IsCheatGuildName(const char* cName);
	const char* GetCharName();
	void SetCharName(const char* cName);
	BOOL CompareTwoNames(const char* cName1, const char* cName2);
	const char* GetItemResName_WithId(const char* itemName, BOOL isIdentified);
	void GetItemBitmapFileName(const char* itemName, char* buf, BOOL isIdentified);
	void GetSkillActionInfo2(int skillId, int& beginEffectId, int& motionType, int property, int sjob);
	BOOL IsPartyMember(int AID, bool bCheckOnline);
	BOOL IsMonster(CGameActor* pActor);
	void GetMonsterSkillInfo(const char* Name, int skillId, int& act, int& loopType);
	BOOL IsMer(int job);
	int GetOptionValue(const char* szOptionName, int nDefault);
	unsigned long GetAid();
	unsigned long GetGid();
	void SetAid(unsigned long aid);
	void SetGid(unsigned long gid);

public:
	static hook_func<void (CSession::*)(void)> CSession::_Init;
	static hook_func<void (CSession::*)(void)> CSession::_Create;
	static hook_func<void (CSession::*)(void)> CSession::_InitTalkTypeTable;
	static hook_func<int (CSession::*)(const char* chatBuf, TALKTYPE* talkType, mystd::string param[3])> CSession::_GetTalkType;
	static hook_func<char* (CSession::*)(int job, int* head, int sex, int accessory, char* buf)> CSession::_GetAccessoryActName;
	static hook_func<void (CSession::*)(void)> CSession::_ChangeXorValue;
	static hook_func<void (CSession::*)(void)> CSession::_InvalidateBasicWnd;
	static hook_func<TALKTYPE (CSession::*)(const char* command)> CSession::_GetNoParamTalkType;
	static hook_func<void (CSession::*)(void)> CSession::_InitPetTalkTable;
	static hook_func<void (CSession::*)(void)> CSession::_WriteOptionToLuaFile;
	static hook_func<void (CSession::*)(void)> CSession::_ClearEquipItem;
	static hook_func<void (CSession::*)(void)> CSession::_ClearEquipItemInInventory;
	static hook_func<BOOL (CSession::*)(int itemId)> CSession::_IsPetEgg;
	static hook_func<void (CSession::*)(ITEM_INFO* itemInfo)> CSession::_SetItem;
	static hook_func<bool (CSession::*)(ITEM_INFO* itemInfo)> CSession::_AddItem;
	static hook_func<void (CSession::*)(unsigned long index, int numItem)> CSession::_DecItem;
	static hook_func<bool (CSession::*)(ITEM_INFO* itemInfo)> CSession::_AddEquipItem;
	static hook_func<bool (CSession::*)(ITEM_INFO* itemInfo)> CSession::_AddStoreItem;
	static hook_func<void (CSession::*)(unsigned long startTime)> CSession::_UpdateServerTime;
	static hook_func<int (CSession::*)(int job, int act, int hungry)> CSession::_GetPetTalkNumber;
	static hook_func<void (CSession::*)(int job, int stateId, int arg1, char* speak, unsigned long gid)> CSession::_GetMonsterTalkInfo;
	static hook_func<BOOL (CSession::*)(const char* cName)> CSession::_IsGuildMember;
	static hook_func<BOOL (CSession::*)(const char* cName)> CSession::_IsCheatGuildName;
	static hook_func<BOOL (CSession::*)(const char* cName1, const char* cName2)> CSession::_CompareTwoNames;
	static hook_func<void (CSession::*)(int skillId, int& beginEffectId, int& motionType, int property, int sjob)> CSession::_GetSkillActionInfo2;
	static hook_func<void (CSession::*)(const char* Name, int skillId, int& act, int& loopType)> CSession::_GetMonsterSkillInfo;
	static hook_func<int (CSession::*)(const char* szOptionName, int nDefault)> CSession::_GetOptionValue;
};
C_ASSERT( sizeof CSession == 13140 ); //TODO
#pragma pack(pop)


extern CSession& g_session;


bool __cdecl IsEffectStateBurrow(unsigned long effectState);
bool __cdecl IsEffectStateHiding(unsigned long effectState);
bool __cdecl IsEffectStateSpecialHiding(unsigned int effectState);
bool __cdecl IsEffectStateOrcFace(unsigned long effectState);
bool __cdecl IsEffectStateFootPrint(unsigned long effectState);
