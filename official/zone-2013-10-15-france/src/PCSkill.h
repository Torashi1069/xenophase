#pragma once
#include "Struct.h"
#include "ZoneProcess.h"
class CPC;
class CZGuildInfo;


struct PC_SKILL_INFO
{
	PC_SKILL_INFO()
	{
		this->level = 0;
//		this->type = ?;
		this->typeBefore = -1;
		this->disposableLevel = 0;
		this->orgDispLevel = 0;
		this->imitationLevel = 0;
		this->count = 0;
		this->skillUseType = -1;
		this->BlockUseTM = 0;
		this->bDBupdateWhenLogout = false;
		this->Data = 0;
	}

	/* this+ 0 */ int level;
	/* this+ 4 */ int type; // enumPCSKILLTYPE
	/* this+ 8 */ int typeBefore;
	/* this+12 */ int disposableLevel;
	/* this+16 */ int orgDispLevel;
	/* this+20 */ int imitationLevel;
	/* this+24 */ int count;
	/* this+28 */ short skillUseType;
	/* this+32 */ unsigned long BlockUseTM;
	/* this+36 */ bool bDBupdateWhenLogout;
	/* this+40 */ int Data;
};


struct MONSTER_CREATED_BYSKILL
{
	/* this+0 */ unsigned short SKID;
	/* this+4 */ int monsterJob;
	/* this+8 */ short count;
};


struct DYNAMIC_SKILLINFO
{
	/* this+0 */ unsigned short SKID;
	/* this+4 */ int orgDispLevel;
};


struct PLAY_SKILLINFO
{
	/* this+0 */ unsigned long skAID;
	/* this+4 */ PosInfo deltaPos;
};


struct PARAMETER
{
	/* this+0 */ int varType;
	/* this+4 */ int amount;
};


struct WARPPORTAL_INFO
{
	/* this+ 0 */ char mapName[3][16];
	/* this+48 */ short xPos[3];
	/* this+54 */ short yPos[3];
};


class CPCSkill
{
public:
	CPCSkill();
	virtual ~CPCSkill();
	void Init(const bool in_bChangeJob);
	void Reset(const bool in_bChangeJob);
	BOOL AddSkill(unsigned short SKID, PC_SKILL_INFO* skInfo, SKILLINFO* skillData, const bool in_bNeedDBwork);
//	void AddSkillFromItemServer(unsigned short , int , unsigned long , int );
//	void DeleteSkillFromItemServer(unsigned short , int );
//	void AddSkillFromNPCEvent(unsigned short , int , int );
	void DeleteSkill(unsigned short SKID, BOOL isDisposable);
	PC_SKILL_INFO* GetSkill(unsigned short SKID, BOOL isFixedSkill);
//	int SendSkillSelectList(const std::vector<int>& , const PACKET_ZC_SKILL_SELECT_REQUEST::enumWHY );
//	bool LoadSkill3rd(std::vector<CLogonPermitADBWork::CSkill3rdData::tagSkill>& );
//	bool LoadSkill3rd_Parse(std::vector<CLogonPermitADBWork::CSkill3rdData::tagSkill>& );
//	bool LoadSkill3rd_Correction();
//	void UpgradSkill3rdLevel(const int );
//	void UpgradSkill3rdLevelAfter(const int );
//	void GetSkill3rdDBFormat(std::vector<CSaveAllADBWork::CSkill3rdData::tagSkill>& );
//	void NotifyPostDelaySkillList();
	void ApplyPassiveSkill(unsigned short SKID, unsigned short level);
//	void NotifySkillInfo(unsigned short , bool , int );
//	void NotifyAllSkillInfo();
	void NotifySkillInfoDelete(const int in_SKID) const;
//	void NotifySkillInfo_FakeType(unsigned short , int );
//	void CheckAllEnableSkill();
	BOOL IsConditionalSkill(unsigned short skillID);
//	int IsEnableSkill(unsigned short , short );
//	int IsEncoreSkill();
//	int AM_IsMakableItemBySkill(unsigned short );
//	int AM_IsMakableItemByItem(unsigned short );
//	int AM_ManufactureItem(unsigned short , unsigned long , int , MAKABLEITEM_INFO* );
	void SetMyOwner(CPC* pc);
	short GetSkillLevel(unsigned short SKID, BOOL isFixedSkill);
//	int GetSkillLevel2(unsigned short , int );
	int GetSkillType(unsigned short SKID); // enumPCSKILLTYPE
	short GetSkillRange(unsigned short SKID, short level);
//	void UpdateAvailableInfo(unsigned short , bool );
	int GetWarpInfoXpos(char xnum);
	void LoadWarpInfo();
	void LoadStarPlaceInfo();
	void UpdateStarPlace(char* mapName, short num);
	int GetWarpInfo(WARPPORTAL_INFO* warpinfo);
//	short GetWarpXPos();
//	short GetWarpYPos();
//	void SetWarpXPos(short );
//	void SetWarpYPos(short );
//	int SearchWarpList(char* , short& , short& , int );
//	void SetWarpExpireTime(unsigned long );
//	void SetWarpSize(int );
//	unsigned long GetWarpExpireTime();
//	int GetWarpSize();
//	void PushWarpPosition(short , short , char* );
//	int GetPlusItemWeight();
	void SetPlusItemWeight(int weight);
//	int GetDiscountPercent();
//	int GetOverChargePercent();
//	int GetSkillSize();
//	void UpdateSkillType(unsigned short , unsigned long , int );
//	int GetTotalFirstJobSkillLevel();
//	int GetTotalSecondJobSkillLevel();
//	int GetTotalThirdJobSkillLevel();
//	void ResetFirstJobSkillLevel();
//	void ResetSecondJobSkillLevel();
//	void ResetThirdJobSkillLevel();
//	void ResetAllSkillLevelExceptNoviceSkill();
//	int GetTotalSkillLevelExceptNoviceSkill();
//	int IsSecondSkill(unsigned short );
//	static bool IsSecondSkill(const int , const int );
//	int IsFirstSkill(unsigned short );
//	static bool IsFirstSkill(const int , const int );
//	static int IsThirdSkill(unsigned short );
//	void SetFireWallCount(int , int );
//	int GetFireWallIndex();
//	int GetPassiveSkillPlusAttackPower(CITP* , CCharacter* , const int );
//	int GetPassiveSkillPlusMeleeAttackPowerbyPercent(CITP* , CCharacter* , const int );
//	int GetPassiveSkillPlusAttackPowerbyPercent(CITP* , CCharacter* , const int );
//	int IsMakableItemBySkill(unsigned short );
//	int IsMakableItemByItem(unsigned short );
//	int ManufactureItem(unsigned short , unsigned long , MAKABLEITEM_INFO* );
//	void SetTalkBoxcontents(char* );
//	char* GetTalkBoxcontents();
//	void SetContents(unsigned short , char* );
//	char* GetContents(unsigned short );
//	void AddPlayingSkill(const unsigned long , const int , const int );
//	void DeletePlayingSkill(const unsigned long );
	void SetPartnerAID(unsigned long AID);
	void SetWeaponMasterAID(unsigned long AID);
	unsigned long GetPartnerAID();
	unsigned long GetWeaponMasterAID();
//	unsigned short GetEncoreSKID();
//	int GetEncoreSkLevel();
	void DestroyPlayingSkill();
//	void SetPosPlayingSkill(int , int );
//	void DisappearPlayingSkill();
//	int IsSkillLoaded();
	short GetNumOfSpirits();
	void ResetSpirits();
//	void AddSpirits(short );
//	void MinusSpirits(short );
//	void UpdateSpiritsInfo();
	unsigned long GetSKIDFromAbracadabra();
	void SetSKIDFromAbracadabra(unsigned long SKID);
//	void SetLimitedSkill(unsigned long , int );
//	int GetLimitedSkillNum(unsigned long );
//	void ResetAllPostdelaySkill();
//	void SetPostdelaySkill(unsigned long , unsigned long );
//	int IsEndPostdelaySkill(unsigned long );
//	void SetMasterSkill(CZGuildInfo* );
//	void ResetMasterSkill();
//	void ApplyGDPassiveSkill(CPC* );
//	int GetLimitNumByCannibalize(int );
//	std::deque<WARP_POSITION>* GetWarpPosInfo();
	void UpdatePlusItemWeightBySkill();
//	MONSTER_CREATED_BYSKILL* GetMonsterCreatedBySkill(unsigned short );
//	int UpdateMonsterCreatedBySkill(unsigned short , int , int );

private:
	void UpdateWarpList(char* mapName, short xPos, short yPos);
//	void ApplyPassiveSkillByReset(unsigned short );

private:
	/* this+  0 */ //const CPCSkill::`vftable';
	/* this+  4 */ int m_plusItemWeight;
	/* this+  8 */ int m_plusItemWeightBySkill;
	/* this+ 12 */ short m_warpXPos;
	/* this+ 14 */ short m_warpYPos;
	/* this+ 16 */ unsigned long m_warpExpireTime;
	/* this+ 20 */ int m_warpSize;
	/* this+ 24 */ char m_talkBoxContents[80];
	/* this+104 */ char m_graffitiContents[80];
	/* this+184 */ CPC* m_pc;
	/* this+188 */ int m_sanctuaryCnt;
	/* this+192 */ int m_stormGustCnt;
	/* this+196 */ int m_fireWallCount[3];
	/* this+208 */ MONSTER_CREATED_BYSKILL m_monsterCreatedBySkill[3];
	/* this+244 */ int m_playSkillCount;
	/* this+248 */ int m_warpCount;
	/* this+252 */ unsigned short m_encoreSKID;
	/* this+254 */ unsigned short m_encoreSkLevel;
	/* this+256 */ unsigned long m_partnerAID;
	/* this+260 */ unsigned long m_playStartedTime;
	/* this+264 */ unsigned long m_graffitiAID;
	/* this+268 */ unsigned long m_weaponMasterAID;
	/* this+272 */ int m_isEncoreSkill;
	typedef std::map<unsigned short,PC_SKILL_INFO> SKILL_CONTAINER;
	/* this+276 */ std::map<unsigned short,PC_SKILL_INFO> m_skill;
	/* this+292 */ std::map<unsigned short,PC_SKILL_INFO> m_disposableSkill;
	/* this+308 */ std::vector<DYNAMIC_SKILLINFO> m_dynamicSkill;
	/* this+324 */ std::deque<WARP_POSITION> m_warpInfo;
	/* this+348 */ std::vector<PLAY_SKILLINFO> m_playSkillList;
	/* this+364 */ std::map<unsigned short,PARAMETER> m_GDMasterParamList;
	/* this+380 */ unsigned short m_spellCastingSKID;
	/* this+382 */ short m_spellCastingSKLevel;
	/* this+384 */ std::list<unsigned long> m_specialZoneList;
	/* this+396 */ int m_isSkillLoaded;
	/* this+400 */ std::list<unsigned long> m_spiritsTime;
	/* this+412 */ int m_skillCondition;
	/* this+416 */ unsigned long m_abracadabraSKID;
	/* this+420 */ int m_bCallPartner;
	/* this+424 */ std::map<unsigned long,int> m_limitedSkill;

	struct MILLENNIUMSHIELD
	{
		/* this+0 */ int hp;
		/* this+4 */ unsigned long time;
	};

	/* this+440 */ std::list<MILLENNIUMSHIELD> m_millenniumShieldList;
	/* this+452 */ std::list<unsigned long> m_forceOfVanguard;
	/* this+464 */ std::list<unsigned long> m_cursedCircleAIDList;

private:
//	void AddMillenniumShield(int );
//	void UpdateMillenniumShield();
	void NotifyMillenniumShieldCount(bool option);
//	void ResetForceOfVanguard();
	void AddForceOfVanguard(const unsigned short in_Count);
//	void UpdateForceOfVanguard();
	void NotifyForceOfVanguardCount();

public:
	void ResetMillenniumShield();
//	bool DamageToMillenniumShield(int );
//	int GetNumOfMillenniumShield();
//	int GetNumOfForceOfVanguard();
//	void AddSkillImitation3rd(unsigned short , int , const unsigned short );

public:
	/* this+476 */ std::vector<unsigned short> m_SkillFakeTypeList;
//	void ResetSkillFakeTypeList();

public:
	void SetWarpInfo(const WARPPORTAL_INFO& in_WarpInfo);
	void SetStarPlaceInfo(const WARPPORTAL_INFO& in_WarpInfo);

	friend class CPC; // m_spellCastingSKID, m_spellCastingSKLevel
};
