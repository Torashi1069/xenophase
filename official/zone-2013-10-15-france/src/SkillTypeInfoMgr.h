#pragma once
#include "MSGpar.h"
#include "SkillTypeBaseInfo.h"
class CCharacter;


enum enumSKILLTYPEINFOMESSAGE
{
	SM_REQ_EXCHANGE_ITEM    = 0,
	SM_REQ_EMOTION          = 1,
	SM_REQ_SIT              = 2,
	SM_REQ_CHATROOM         = 3,
	SM_REQ_MAKEPARTY        = 4,
	SM_REQ_SHOUT            = 5,
	SM_REQ_PK               = 6,
	SM_REQ_GIVE_MANNERPOINT = 7,
	SM_GET_PLUSATTPOWER     = 8,
	SM_LEVEL_UP             = 9,
	SM_GET_PLUSHEALVELOCITY = 10,
	SM_GET_PLUSSPVELOCITY   = 11,
	SM_USE_SKILL            = 12,
	SM_RESET_SKILL          = 13,
	SM_GETINFO_SKILL        = 14,
	SM_GETINFO_SKILL1       = 15,
	SM_GETINFO_SKILL2       = 16,
	SM_GET_POSTDELAY        = 17,
	SM_JOINPARTY            = 18,
};


enum enumSKILLPATTERN
{
	SKILLPATT_NONE         = 0,
	SKILLPATT_DIRECTATTACK = 1,
	SKILLPATT_ATTACKSPELL  = 2,
};


enum enumSKILLCLASS
{
	SKCLASS_NORMAL    = 0,
	SKCLASS_HOMUN     = 1,
	SKCLASS_GUILD     = 2,
	SKCLASS_MERCE2    = 3,
	SKCLASS_ELEMENTAL = 4,
};


enum enumSKILLTYPE
{
	SKILLTYPE_PASSIVE     = 0,
	SKILLTYPE_TOCHARACTER = 1,
	SKILLTYPE_TOGROUND    = 2,
	SKILLTYPE_TOME        = 4,
	SKILLTYPE_TOITEM      = 8,
	SKILLTYPE_TOALL       = 16,
	SKILLTYPE_TOSKILL     = 32,
};


enum enumSKILLCATEGORY
{
	SKILL_TRAP               = 0,
	SKILL_BOLT               = 1,
	SKILL_PLAYING            = 2,
	SKILL_PASSIVE_RESET      = 3,
	SKILL_TYPE2_1            = 4,
	SKILL_TYPE2_2            = 5,
	SKILL_MADOGEAR           = 6,
	SKILL_IGNORE_BY_HOVERING = 7,
	SKILL_TRAP_DAMAGE        = 8,
	SKILL_EDP_PENALTY        = 9,
	SKILL_WUGATTACK          = 10,
};


enum enumSKILLFLAG
{
	SKFLAG_NODISPEL                        = 0x1,
	SKFLAG_QUESTSKILL                      = 0x2,
	SKFLAG_NOREDUCT                        = 0x4,
	SKFLAG_CASTING_DISTANCE                = 0x8,
	SKFLAG_UNABLE_TOBOSS                   = 0x10,
	SKFLAG_APPLY_PLUSRNG                   = 0x20,
	SKFLAG_IGNORE_SAFETYWALL               = 0x40,
	SKFLAG_PLUS_TRAP_RANGE_RA_RESEARCHTRAP = 0x80,
	SKFLAG_DISTINCT_DAMAGE_FORMULA         = 0x100,
};


class CSkillTypeInfoMgr : public CSkillTypeBaseInfo
{
public:
	CSkillTypeInfoMgr();
	virtual ~CSkillTypeInfoMgr();

public:
	void Init();
	void Reset();
	unsigned short GetSKID(const char* skName) const;
	void LoadSKInfoFromDB();
	int SendMsg(CCharacter* sender, int SKID, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4);
	CSkillTypeInfo* SearchSkillTypeInfo(const unsigned short in_SKID) const;
	short GetSkillSPCost(unsigned short SKID, short sklevel);
	char* GetSkillName(unsigned short SKID);
	bool IsNextLevelUpgradable(unsigned short SKID, short curlevel, short job);
	int IsChangeStatusSkill(unsigned short SKID); //TODO
	int GetIndexGroundSkill(unsigned short SKID); //TODO
	int GetSkillPattern(unsigned short skillID); // enumSKILLPATTERN
	int GetSKClass(const int in_SKID) const; // enumSKILLCLASS
	void AddSkill(CCharacter* sender, short job);
	void AddSkill_Homun(CCharacter* sender, short job);
	void AddSkill_Merce(CCharacter* sender, short job);
	int GetType(unsigned short SKID); // enumSKILLTYPE
	short GetAttackRange(unsigned short SKID, int level);
	int GetProperty(unsigned short SkillID);
	void RegisterSkillName(char* ); // not implemented
	BOOL IsAvailableJob(short job, unsigned short SKID);
	short IsAvailable_Merce(short job, unsigned short SKID);
	BOOL IsConditionalSkill(short job, unsigned short SKID);
	BOOL IsConditionSkill_HO(short job, unsigned short SKID);
	BOOL IsGuildSkill(int SKID);
	std::map<unsigned short,int>* GetLowerSkillTreeInfo(short job, unsigned short SKID);
	void InheritFirstJobSkill(short secondJob, short firstJob);
	void InheritPreJobSkill_HO(short nextJob, short preJob);
	std::map<unsigned short,std::map<unsigned short,int>>* GetAllAvailableSkill(short job);
	BOOL IsSkillCategory(unsigned short SKID, int type); // enumSKILLCATEGORY
	short GetPostDelayTM(unsigned short SKID, short level);
	unsigned long GetFlag(unsigned short SKID); // enumSKILLFLAG
	bool InitSkillScript();
	void LoadSkillDelay(const char* fileName, void (CSkillTypeInfo::* func)(short skLevel, int time));
	int GetSkillSinglePostDelay(unsigned short SKID, int skLevel);
	int GetSkillGlobalPostDelay(unsigned short SKID, int skLevel);
	bool GetSkillTypeInfo2_SkillData(unsigned short SKID, unsigned long tokenType, short skLevel, int& value);

private:
	void LoadSkillTree(const char* fileName);
	BOOL LoadGDSkillTree();
	BOOL LoadSKTree_Homun(const char* fileName);
	BOOL LoadSKTree_Merce(const char* fileName);

private:
	/* this+ 0 */ //CSkillTypeBaseInfo baseclass_0;
	/* this+36 */ std::map<short,std::map<unsigned short,std::map<unsigned short,int>>> m_skillTreeInfo;
	/* this+52 */ std::map<unsigned short,std::map<unsigned short,int>> m_GDSkillTreeInfo;
	/* this+68 */ std::map<short,std::map<unsigned short,std::map<unsigned short,int>>> m_SKTree_Homun;
	/* this+84 */ std::map<short,std::map<unsigned short,int>> m_SKTree_Merce;

public:
	int GetCLevel_SKTreeHomun(const short in_HomunJob, const unsigned short in_SKID);

private:
	struct SKID_CLEVEL
	{
		/* this+0 */ unsigned short SKID;
		/* this+2 */ short cLevel;

		SKID_CLEVEL(const unsigned short in_SKID, const short in_cLevel) : SKID(in_SKID), cLevel(in_cLevel) { }
	};

	typedef std::multimap<short,SKID_CLEVEL> SKTREE_BYCLEVEL_CONTAINER;
	/* this+100 */ SKTREE_BYCLEVEL_CONTAINER m_SKTree_Homun_ByCLevel;
};
