#include "Globals.h"
#include "ItemInfo.h" // GetDesc()
#include "Session.h"
#include "SkillInfo.h"


CommonObject& SKILL_INFO::s_obj = VTOR< CommonObject >(SymDB::Add("SKILL_INFO::s_obj", SAKEXE, "SKILL_INFO::s_obj"));
mystd::vector<const char*>& SKILL_INFO::s_skillIdNameList = VTOR< mystd::vector<const char*> >(SymDB::Add("SKILL_INFO::s_skillIdNameList", SAKEXE, "SKILL_INFO::s_skillIdNameList"));
mystd::vector<const char*>& SKILL_INFO::s_guildSkillIdNameList = VTOR< mystd::vector<const char*> >(SymDB::Add("SKILL_INFO::s_guildSkillIdNameList", SAKEXE, "SKILL_INFO::s_guildSkillIdNameList"));
mystd::vector<int>& SKILL_INFO::s_isLevelUseSkillList = VTOR< mystd::vector<int> >(SymDB::Add("SKILL_INFO::s_isLevelUseSkillList", SAKEXE, "SKILL_INFO::s_isLevelUseSkillList"));
mystd::map<int,SKILL_DESC>& SKILL_INFO::s_skillDescMap = VTOR< mystd::map<int,SKILL_DESC> >(SymDB::Add("SKILL_INFO::s_skillDescMap", SAKEXE, "SKILL_INFO::s_skillDescMap"));
const char*& unknownSkill = VTOR< const char* >(SymDB::Add("unknownSkill", SAKEXE, "unknownSkill"));


SKILL_INFO::SKILL_INFO(void) // line ??
{
	m_isValid = 0;
	skillName = NULL;
}


SKILL_INFO::SKILL_INFO(int dummy) // line 19
{
	skillName = unknownSkill;
}//line 25


hook_method<const char* (SKILL_INFO::*)(void)> SKILL_INFO::_GetName(SERVER, "SKILL_INFO::GetName");
const char* SKILL_INFO::GetName(void) // line 33
{
	return (this->*_GetName)();

	return GetDesc(this->SKID,s_skillDescMap).displayName; // inlined
}


hook_method<mystd::vector<const char*>& (SKILL_INFO::*)(void)> SKILL_INFO::_GetDescription(SERVER, "SKILL_INFO::GetDescription");
mystd::vector<const char*>& SKILL_INFO::GetDescription(void) // line 38
{
	return (this->*_GetDescription)();

	return GetDesc(this->SKID,s_skillDescMap).descriptionName; // inlined
}


hook_method<const char* (SKILL_INFO::*)(void)> SKILL_INFO::_GetSkillIdName(SAKEXE, "SKILL_INFO::GetSkillIdName");
const char* SKILL_INFO::GetSkillIdName(void) // line 29
{
	return (this->*_GetSkillIdName)();

	return SKILL_INFO::GetSkillIdNameBySkillId(this->SKID); //inlined
}


hook_method<const mystd::vector<int>& (SKILL_INFO::*)(void)> SKILL_INFO::_LevelUseSpAmountList(SAKEXE, "SKILL_INFO::LevelUseSpAmountList");
const mystd::vector<int>& SKILL_INFO::LevelUseSpAmountList(void) // line 250
{
	return (this->*_LevelUseSpAmountList)();

	//TODO
}


hook_method<static int (__cdecl *)(const char* skillIdName, int findStart)> SKILL_INFO::_GetIdBySkillIdName(SAKEXE, "SKILL_INFO::GetIdBySkillIdName");
int __cdecl SKILL_INFO::GetIdBySkillIdName(const char* skillIdName, int findStart) // line 214
{
	return (SKILL_INFO::_GetIdBySkillIdName)(skillIdName, findStart);

	if( findStart >= SKID_UNKNOWN && findStart <= SKID_SN_SHARPSHOOTING && strcmp(skillIdName, s_skillIdNameList[findStart]) == 0 )
		return findStart;

	for( int i = 0; i < 5; ++i )
		if( strcmp(skillIdName, s_guildSkillIdNameList[i]) == 0 )
			return i + 10000;

	for( int i = 0; i < 383; ++i )
		if( strcmp(skillIdName, s_skillIdNameList[i]) == 0 )
			return i;

	return SKID_UNKNOWN;
}


hook_method<static void (__cdecl *)(void)> SKILL_INFO::_InitTable(SAKEXE, "SKILL_INFO::InitTable");
void __cdecl SKILL_INFO::InitTable(void) // line 277
{
	return (SKILL_INFO::_InitTable)();

	//TODO
}


hook_method<static void (__cdecl *)(void)> SKILL_INFO::_InitGuildTable(SAKEXE, "SKILL_INFO::InitGuildTable");
void __cdecl SKILL_INFO::InitGuildTable(void) // line 266
{
	return (SKILL_INFO::_InitGuildTable)();

	//TODO
}


hook_method<static void (__cdecl *)(void)> SKILL_INFO::_InitSkillInfoTables(SAKEXE, "SKILL_INFO::InitSkillInfoTables");
void __cdecl SKILL_INFO::InitSkillInfoTables(void) // line 46
{
	return (SKILL_INFO::_InitSkillInfoTables)();

	s_isLevelUseSkillList.clear();
	s_skillDescMap.clear();
	s_obj.Clear();

	if( s_skillIdNameList.size() != 383 )
		SKILL_INFO::InitTable();

	if( s_guildSkillIdNameList.size() != 5 )
	{
		s_guildSkillIdNameList.resize(5, "SKILL-UNKNOWN");
		s_guildSkillIdNameList[0] = "GD_APPROVAL";
		s_guildSkillIdNameList[1] = "GD_KAFRACONTRACT";
		s_guildSkillIdNameList[2] = "GD_GUARDRESEARCH";
		s_guildSkillIdNameList[3] = "GD_CHARISMA";
		s_guildSkillIdNameList[4] = "GD_EXTENSION";
	}

	mystd::vector<const char*> table;
	table.reserve(2048);

	s_obj.CommonObject::TokenFileToPCharList(table, "skillnametable.txt", false);
	for( mystd::vector<const char*>::iterator tableiter = table.begin(); tableiter != table.end(); tableiter += 2 )
	{
		const char* text = *tableiter;
		int skillID = SKILL_INFO::GetIdBySkillIdName(text, SKID_NV_BASIC); //inlined

		mystd::map<int,SKILL_DESC>::iterator it = s_skillDescMap.find(skillID);
		if( it == SKILL_INFO::s_skillDescMap.end() )
			it = s_skillDescMap.insert(mystd::pair<int,SKILL_DESC>(skillID,SKILL_DESC())).first;

		SKILL_DESC* desc = &it->second;
		desc->skillIdName = *(tableiter + 0);
		desc->displayName = *(tableiter + 1);
		g_session.CSession::RemoveUnderbar(desc->displayName, const_cast<char*>(desc->displayName));
	}

	s_obj.CommonObject::TokenFileToPCharList(table, "skilldesctable.txt", true);
	for( mystd::vector<const char*>::iterator tableiter = table.begin(); tableiter != table.end(); ++tableiter )
	{
		const char* text = *tableiter;
		int skillID = SKILL_INFO::GetIdBySkillIdName(text, SKID_NV_BASIC); //inlined

		if( skillID != SKID_UNKNOWN )
			continue;

		GetDesc(skillID,s_skillDescMap).descriptionName.push_back(text); // inlined
	}

	s_obj.CommonObject::TokenFileToPCharList(table, "leveluseskillspamount.txt", false);
	for( mystd::vector<const char*>::iterator tableiter = table.begin(); tableiter != table.end(); ++tableiter )
	{
		const char* text = *tableiter;
		int skillID = SKILL_INFO::GetIdBySkillIdName(text, SKID_NV_BASIC); //inlined

		if( skillID != SKID_UNKNOWN )
			continue;

		if( strcmp(text, "@") == 0 )
			continue;

		int spcost = atoi(text);
		GetDesc(skillID,s_skillDescMap).spUsage.push_back(spcost); // inlined
	}

	SKILL_DESC* desc = &GetDesc(SKID_UNKNOWN,s_skillDescMap); // inlined
	desc->descriptionName.push_back(unknownSkill);
	desc->displayName = unknownSkill;
	desc->spUsage.push_back(SKID_UNKNOWN);

	SKILL_INFO::s_isLevelUseSkillList.reserve(383);
	SKILL_DESC& rdesc = GetDesc(-1, s_skillDescMap);
	rdesc = *desc;

	for( int skillID = 0; skillID < 383; ++skillID )
	{
		int isExist = ( GetDesc(skillID,s_skillDescMap).spUsage.size() != 0 );
		s_isLevelUseSkillList.push_back(isExist);
	}
}


hook_method<static bool (__cdecl *)(int skillId)> SKILL_INFO::_IsGoodSkillForActor(SAKEXE, "SKILL_INFO::IsGoodSkillForActor");
bool __cdecl SKILL_INFO::IsGoodSkillForActor(int skillId) // line 127
{
	return (SKILL_INFO::_IsGoodSkillForActor)(skillId);

	switch( skillId )
	{
	case SKID_SM_RECOVERY:
	case SKID_AL_HEAL:
	case SKID_AL_INCAGI:
	case SKID_AL_BLESSING:
	case SKID_AL_CURE:
	case SKID_TF_DETOXIFY:
	case SKID_ALL_RESURRECTION:
	case SKID_PR_IMPOSITIO:
	case SKID_PR_SUFFRAGIUM:
	case SKID_PR_ASPERSIO:
	case SKID_PR_SLOWPOISON:
	case SKID_PR_STRECOVERY:
	case SKID_PR_KYRIE:
	case SKID_AS_ENCHANTPOISON:
	case SKID_AS_POISONREACT:
	case SKID_AM_POTIONPITCHER:
	case SKID_AM_CP_WEAPON:
	case SKID_AM_CP_SHIELD:
	case SKID_AM_CP_ARMOR:
	case SKID_AM_CP_HELM:
	case SKID_CR_DEVOTION:
	case SKID_CR_PROVIDENCE:
	case SKID_MO_ABSORBSPIRITS:
	case SKID_SA_FLAMELAUNCHER:
	case SKID_SA_FROSTWEAPON:
	case SKID_SA_LIGHTNINGLOADER:
	case SKID_SA_SEISMICWEAPON:
	case SKID_NPC_ARMORBRAKE:
		return true;
	default:
		return false;
	}
}


hook_method<static bool (__cdecl *)(int skillId)> SKILL_INFO::_IsSkillNotDelayed(SAKEXE, "SKILL_INFO::IsSkillNotDelayed");
bool __cdecl SKILL_INFO::IsSkillNotDelayed(int skillId) // line 166
{
	return (SKILL_INFO::_IsSkillNotDelayed)(skillId);

	switch( skillId )
	{
	case SKID_MG_NAPALMBEAT:
	case SKID_MG_SAFETYWALL:
	case SKID_MG_SOULSTRIKE:
	case SKID_MG_COLDBOLT:
	case SKID_MG_FROSTDIVER:
	case SKID_MG_STONECURSE:
	case SKID_MG_FIREBALL:
	case SKID_MG_FIREWALL:
	case SKID_MG_FIREBOLT:
	case SKID_MG_LIGHTNINGBOLT:
	case SKID_MG_THUNDERSTORM:
	case SKID_AL_WARP:
	case SKID_AL_INCAGI:
	case SKID_AL_DECAGI:
	case SKID_AL_CRUCIS:
	case SKID_AL_ANGELUS:
	case SKID_PR_TURNUNDEAD:
	case SKID_WZ_WATERBALL:
		return false;
	default:
		return true;
	}
}


hook_method<static const char* (__cdecl *)(int skillId)> SKILL_INFO::_GetSkillIdNameBySkillId(SAKEXE, "SKILL_INFO::GetSkillIdNameBySkillId");
const char* __cdecl SKILL_INFO::GetSkillIdNameBySkillId(int skillId) // line 193
{
	return (SKILL_INFO::_GetSkillIdNameBySkillId)(skillId);

	if( skillId >= SKID_NV_BASIC && skillId <= SKID_SN_SHARPSHOOTING )
		return s_skillIdNameList[skillId];
	else
	if( skillId >= SKID_GD_APPROVAL && skillId <= SKID_GD_EXTENSION )
		return s_guildSkillIdNameList[skillId - SKID_GD_APPROVAL];
	else
		return s_skillIdNameList[SKID_UNKNOWN];
}


hook_method<static const char* (__cdecl *)(int skillId)> SKILL_INFO::_GetSkillNameBySkillId(SAKEXE, "SKILL_INFO::GetSkillNameBySkillId");
const char* __cdecl SKILL_INFO::GetSkillNameBySkillId(int skillId) // line 206
{
	return (SKILL_INFO::_GetSkillNameBySkillId)(skillId);

	return GetDesc(skillId,s_skillDescMap).displayName; // inlined
}


hook_method<static int (__cdecl *)(int skillId)> SKILL_INFO::_IsLevelUseSkill(SAKEXE, "SKILL_INFO::IsLevelUseSkill");
int __cdecl SKILL_INFO::IsLevelUseSkill(int skillId) // line 260
{
	return (SKILL_INFO::_IsLevelUseSkill)(skillId);

	return s_isLevelUseSkillList[skillId];
}


class hook_ptr<struct mystd::_Tree<int,struct mystd::pair<int const ,struct SKILL_DESC>,struct mystd::map<int,struct SKILL_DESC,struct mystd::less<int>,class mystd::allocator<struct SKILL_DESC> >::_Kfn,struct mystd::less<int>,class mystd::allocator<struct SKILL_DESC> >::_Node *> mystd::_Tree<int,struct mystd::pair<int const ,struct SKILL_DESC>,struct mystd::map<int,struct SKILL_DESC,struct mystd::less<int>,class mystd::allocator<struct SKILL_DESC> >::_Kfn,struct mystd::less<int>,class mystd::allocator<struct SKILL_DESC> >::_Nil("mystd::_Tree<int,struct mystd::pair<int const ,struct SKILL_DESC>,struct mystd::map<int,struct SKILL_DESC,struct mystd::less<int>,class mystd::allocator<struct SKILL_DESC> >::_Kfn,struct mystd::less<int>,class mystd::allocator<struct SKILL_DESC> >::_Nil");
