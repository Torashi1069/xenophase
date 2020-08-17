#include "CharacterMgr.h"
#include "Enum.h"
#include "Path.h"
#include "PC.h"
#include "SkillScriptHandler.h"
#include "SkillTypeInfo2_2(2).h"
#include "SkillTypeInfo3rd2_ShadowChaser.h"
#include "SkillTypeInfoMgr.h"
#include "Struct.h" // MSG_TYPE_SKILLDATA
#include "ZoneProcess.h"
#include "shared/NCriticalErrorLog.h"
////////////////////////////////////////


hook_func<int (SK_SC_REPRODUCE::*)(CCharacter* sender, unsigned short SKID, int MsgID, int skLevel, int targetID, int spCost, MSGpar::CVar par4)> SK_SC_REPRODUCE__OnMsg(EXEPATH(), "SK_SC_REPRODUCE::OnMsg");
int SK_SC_REPRODUCE::OnMsg(CCharacter* sender, unsigned short SKID, int MsgID, int skLevel, int targetID, int spCost, MSGpar::CVar par4)
{
	return (this->*SK_SC_REPRODUCE__OnMsg)(sender, SKID, MsgID, skLevel, targetID, spCost, par4);
	//TODO
}


int SK_SC_REPRODUCE::GetLifeSupportSpCost(const int in_Level)
{
	static STRUCT_SK_INTVALUE* LifeSupportSpCostTbl = reinterpret_cast<STRUCT_SK_INTVALUE*>(this->CSkillTypeInfo2::GetInfo(FUNC_SKILLDATA1));
	return LifeSupportSpCostTbl->value[in_Level - 1];
}


////////////////////////////////////////


int SK_SC_AUTOSHADOWSPELL::OnMsg(CCharacter* in_cpSender, unsigned short in_SKID, int in_MsgID, int in_par1, int in_par2, int in_par3, MSGpar::CVar in_par4) // ???
{
	switch( in_MsgID )
	{
	case SM_USE_SKILL:
	{
		MSG_TYPE_SKILLDATA skilldata;
		skilldata.SKID = in_SKID;
		skilldata.skLevel = in_par1;
		skilldata.spCost = in_par3;
		skilldata.xPos = 0;
		skilldata.yPos = 0;
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, in_cpSender, CM_THIRDJOB_SKILL_OPERATE_TOCHARACTER, in_SKID, in_par2, (int)&skilldata, 0);
	}
	break;
	default:
	{
		this->CSkillTypeInfo::OnMsg(in_cpSender, in_SKID, in_MsgID, in_par1, in_par2, in_par3, in_par4);
	}
	break;
	};

	return 0;
}


int SK_SC_AUTOSHADOWSPELL::GetLifeTM(const int in_Level) const // 1449-1454
{
	static STRUCT_SK_INTVALUE* LifeTMTbl = reinterpret_cast<STRUCT_SK_INTVALUE*>(this->CSkillTypeInfo2::GetInfo(FUNC_SKILLDATA1));
	return LifeTMTbl->value[in_Level - 1];
}


int SK_SC_AUTOSHADOWSPELL::GetAutoSpellMiliPercent(const int in_Level) const // 1457-1462
{
	static STRUCT_SK_INTVALUE* AutoSpellMiliPercentTbl = reinterpret_cast<STRUCT_SK_INTVALUE*>(this->CSkillTypeInfo2::GetInfo(FUNC_SKILLDATA2));
	return AutoSpellMiliPercentTbl->value[in_Level - 1];
}


int SK_SC_AUTOSHADOWSPELL::GetAutoSpellLevel(const int in_Level, const int in_ImitationSKLevel) const // 1465-1471
{
	static STRUCT_SK_INTVALUE* AutoSpellLevelTbl = reinterpret_cast<STRUCT_SK_INTVALUE*>(this->CSkillTypeInfo2::GetInfo(FUNC_SKILLDATA3));
	return min(AutoSpellLevelTbl->value[in_Level - 1], in_ImitationSKLevel);
}


bool SK_SC_AUTOSHADOWSPELL::IsAllowSkill(CPC* in_pPlayer, const unsigned short in_SKID) const // 1474-1489
{
	SKILLLISTCONTAINER::const_iterator it;
	for( it = m_SkillList.begin(); it != m_SkillList.end(); ++it )
		if( *it == in_SKID )
			break;
	if( it == m_SkillList.end() )
		return false;

	PC_SKILL_INFO* skillInfo = in_pPlayer->m_pcSkill.CPCSkill::GetSkill(in_SKID, FALSE);
	if( skillInfo == NULL )
		return false;
	
	if( skillInfo->type != IMITATION_SKILL )
		return false;
	
	if( skillInfo->imitationLevel <= 0 )
		return false;
	
	CSkillTypeInfo* skillTypeInfo = g_skillTypeInfoMgr.CSkillTypeInfoMgr::SearchSkillTypeInfo(in_SKID);
	if( skillTypeInfo == NULL )
		return false;

	if( skillTypeInfo->CSkillTypeInfo::GetType() == SKILLTYPE_PASSIVE )
		return false;

	return true;
}


std::vector<int> SK_SC_AUTOSHADOWSPELL::GetImitationSKlist(CPC* in_pPlayer) const // 1492-1514
{
	std::vector<int> result;

	PC_SKILL_INFO* cpRG_PLAGIARISM = in_pPlayer->m_pcSkill.CPCSkill::GetSkill(SKID_RG_PLAGIARISM, FALSE);
	if( cpRG_PLAGIARISM != NULL )
	{
		SK_RG_PLAGIARISM::DATA PLAGIARISM = cpRG_PLAGIARISM->Data;
		unsigned short SKID = PLAGIARISM.Imitation.SKID;
		int SKLevel = PLAGIARISM.Imitation.SKLevel;

		if( SKID != 0 && SKLevel > 0 && this->SK_SC_AUTOSHADOWSPELL::IsAllowSkill(in_pPlayer, SKID) )
			result.push_back(SKID);
	}

	PC_SKILL_INFO* cpSC_REPRODUCE = in_pPlayer->m_pcSkill.CPCSkill::GetSkill(SKID_SC_REPRODUCE, FALSE);
	if( cpSC_REPRODUCE != NULL )
	{
		SK_SC_REPRODUCE::DATA REPRODUCE = cpSC_REPRODUCE->Data;
		unsigned short SKID = REPRODUCE.Imitation.SKID;
		int SKLevel = REPRODUCE.Imitation.SKLevel;

		if( SKID != 0 && SKLevel > 0 && this->SK_SC_AUTOSHADOWSPELL::IsAllowSkill(in_pPlayer, SKID) )
			result.push_back(SKID);
	}

	return result;
}


bool SK_SC_AUTOSHADOWSPELL::LoadAllowSkillListFile() // 1517-1553
{
	lua_State* L = luaL_newstate();
	if( L == NULL )
		return false;

	if( luaL_loadfile(L, g_pathData.CPathData::SetFileName("AutoShadowSpellList.lua")) || lua_pcall(L, 0, 0, 0) )
	{
		MessageBoxA(NULL, lua_tolstring(L, -1, NULL), "AutoShadowSpellList.lua", MB_OK);
		lua_close(L);
		return false;
	}

	lua_getfield(L, LUA_GLOBALSINDEX, "SC_AUTOSHADOWSPELL_SKILL_LIST");
	if( lua_type(L, -1) != LUA_TTABLE )
		return false;

	lua_pushnil(L);

	while( lua_next(L, -2) )
	{
		const char* skName = lua_tolstring(L, -1, 0);
		lua_settop(L, -2);

		int SKID = g_skillTypeInfoMgr.CSkillTypeInfoMgr::GetSKID(skName);
		if( SKID == 0 )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "skill name(%s) not found ", skName);
			lua_close(L);
			return false;
		}

		m_SkillList.push_back(SKID);
	}

	lua_close(L);
	return true;
}


////////////////////////////////////////
