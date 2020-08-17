#pragma once
#include "ItemInfo.h"


struct SKILL_DESC
{
	/* this+ 0 */ const char* skillIdName;
	/* this+ 4 */ const char* displayName;
	/* this+ 8 */ mystd::vector<const char*> descriptionName;
	/* this+24 */ mystd::vector<int> spUsage;

	public: SKILL_DESC::SKILL_DESC(void) // line 16
	{
		skillIdName = NULL;
		displayName = NULL;
	}
};


struct SKILL_INFO
{
	/* this+ 0 */ int m_isValid;
	/* this+ 4 */ int SKID;
	/* this+ 8 */ int type; // enum SKILLTYPE
	/* this+12 */ int level;
	/* this+16 */ int spcost;
	/* this+20 */ int upgradable;
	/* this+24 */ int attackRange;
	/* this+28 */ const char* skillName;
	/* static  */ static CommonObject& s_obj;
	/* static  */ static mystd::vector<const char*>& s_skillIdNameList;
	/* static  */ static mystd::vector<const char*>& s_guildSkillIdNameList;
	/* static  */ static mystd::vector<int>& s_isLevelUseSkillList;
	/* static  */ static mystd::map<int,SKILL_DESC>& s_skillDescMap;

	public: SKILL_INFO::SKILL_INFO(void);
	public: SKILL_INFO::SKILL_INFO(int dummy);
	public: const char* SKILL_INFO::GetName(void);
	public: mystd::vector<const char*>& SKILL_INFO::GetDescription(void);
	public: const char* SKILL_INFO::GetSkillIdName(void);
	public: const mystd::vector<int>& SKILL_INFO::LevelUseSpAmountList(void);
	protected: static int __cdecl SKILL_INFO::GetIdBySkillIdName(const char* skillIdName, int findStart);
	protected: static void __cdecl SKILL_INFO::InitTable(void);
	protected: static void __cdecl SKILL_INFO::InitGuildTable(void);
	public: static void __cdecl SKILL_INFO::InitSkillInfoTables(void);
	public: static bool __cdecl SKILL_INFO::IsGoodSkillForActor(int skillId);
	public: static bool __cdecl SKILL_INFO::IsSkillNotDelayed(int skillId);
	public: static const char* __cdecl SKILL_INFO::GetSkillIdNameBySkillId(int skillId);
	public: static const char* __cdecl SKILL_INFO::GetSkillNameBySkillId(int skillId);
	public: static int __cdecl SKILL_INFO::IsLevelUseSkill(int skillId);

private:
	static hook_method<const char* (SKILL_INFO::*)(void)> SKILL_INFO::_GetName;
	static hook_method<mystd::vector<const char*>& (SKILL_INFO::*)(void)> SKILL_INFO::_GetDescription;
	static hook_method<const char* (SKILL_INFO::*)(void)> SKILL_INFO::_GetSkillIdName;
	static hook_method<const mystd::vector<int>& (SKILL_INFO::*)(void)> SKILL_INFO::_LevelUseSpAmountList;
	static hook_method<static int (__cdecl *)(const char* skillIdName, int findStart)> SKILL_INFO::_GetIdBySkillIdName;
	static hook_method<static void (__cdecl *)(void)> SKILL_INFO::_InitTable;
	static hook_method<static void (__cdecl *)(void)> SKILL_INFO::_InitGuildTable;
	static hook_method<static void (__cdecl *)(void)> SKILL_INFO::_InitSkillInfoTables;
	static hook_method<static bool (__cdecl *)(int skillId)> SKILL_INFO::_IsGoodSkillForActor;
	static hook_method<static bool (__cdecl *)(int skillId)> SKILL_INFO::_IsSkillNotDelayed;
	static hook_method<static const char* (__cdecl *)(int skillId)> SKILL_INFO::_GetSkillIdNameBySkillId;
	static hook_method<static const char* (__cdecl *)(int skillId)> SKILL_INFO::_GetSkillNameBySkillId;
	static hook_method<static int (__cdecl *)(int skillId)> SKILL_INFO::_IsLevelUseSkill;
};
