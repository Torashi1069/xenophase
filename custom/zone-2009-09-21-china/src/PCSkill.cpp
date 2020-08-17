#include "CharacterMgr.h"
#include "CITP.hpp"
#include "CITPMgr.hpp"
#include "PC.h"
#include "PCSkill.h"
#include "CSkillTypeInfoMgr.hpp"
#include "ZoneProcess.h"
#include "Common/Packet.h"
#include "shared.h"
#include "enum.hpp"


CPCSkill::CPCSkill(void) // line 39
{
}


CPCSkill::~CPCSkill(void) // line 43
{
}


hook_method<void (CPCSkill::*)(unsigned short SKID, int level, int type)> CPCSkill::_AddSkillFromNPCEvent(SERVER, "CPCSkill::AddSkillFromNPCEvent");
void CPCSkill::AddSkillFromNPCEvent(unsigned short SKID, int level, int type)
{
	return (this->*_AddSkillFromNPCEvent)(SKID, level, type);

	//TODO
}


hook_method<void (CPCSkill::*)(unsigned short SKID, int isDisposable)> CPCSkill::_DeleteSkill(SERVER, "CPCSkill::DeleteSkill");
void CPCSkill::DeleteSkill(unsigned short SKID, int isDisposable)
{
	return (this->*_DeleteSkill)(SKID, isDisposable);

	//TODO
}


hook_method<PC_SKILL_INFO* (CPCSkill::*)(unsigned short SKID, int isFixedSkill)> CPCSkill::_GetSkill(SERVER, "CPCSkill::GetSkill");
PC_SKILL_INFO* CPCSkill::GetSkill(unsigned short SKID, int isFixedSkill)
{
	return (this->*_GetSkill)(SKID, isFixedSkill);

	//TODO
}


hook_method<int (CPCSkill::*)(const int in_Length, const unsigned char* in_pData)> CPCSkill::_LoadSkill(SERVER, "CPCSkill::LoadSkill");
int CPCSkill::LoadSkill(const int in_Length, const unsigned char* in_pData)
{
	return (this->*_LoadSkill)(in_Length, in_pData);

	//TODO
}


hook_method<int (CPCSkill::*)(void)> CPCSkill::_SaveSkill(SERVER, "CPCSkill::SaveSkill");
int CPCSkill::SaveSkill(void)
{
	return (this->*_SaveSkill)();

	//TODO
}


hook_method<void (CPCSkill::*)(void)> CPCSkill::_NotifyAllSkillInfo(SERVER, "CPCSkill::NotifyAllSkillInfo");
void CPCSkill::NotifyAllSkillInfo(void) // line 1623
{
	return (this->*_NotifyAllSkillInfo)();

	PACKET_ZC_SKILLINFO_LIST outpacket;
	outpacket.PacketType = HEADER_ZC_SKILLINFO_LIST;
	outpacket.PacketLength = sizeof(outpacket);

	char buf[3072];
	short count = 0;

	if( m_skill.begin() == m_skill.end() )
		return;

	for( mystd::map<unsigned short,PC_SKILL_INFO>::iterator it = m_skill.begin(); it != m_skill.end(); ++it )
	{
		const unsigned short SKID = it->first;
		const PC_SKILL_INFO& pcsi = it->second;

		PC_SKILL_INFO pcSkillInfo;
		memcpy(&pcSkillInfo, &pcsi, sizeof(pcSkillInfo));

		if( SKID == SKID_SYS_FIRSTJOBLV || SKID == SKID_SYS_SECONDJOBLV )
			continue;

		CSkillTypeInfo* info = g_skillTypeInfoMgr->CSkillTypeInfoMgr::SearchSkillTypeInfo(SKID);
		if( info == NULL )
			continue;

		SKILLINFO skillInfo;
		memcpy(skillInfo.skillName, info->CSkillTypeInfo::GetName(), sizeof(skillInfo.skillName));
		skillInfo.SKID = SKID;
		skillInfo.level = ( pcSkillInfo.type == 1 ) ? pcSkillInfo.disposableLevel
		                : ( pcSkillInfo.type == 4 ) ? pcSkillInfo.imitationLevel
		                :                             pcSkillInfo.level;
		skillInfo.spcost = info->GetSPCost(skillInfo.level);
		skillInfo.type = info->CSkillTypeInfo::GetType();
		skillInfo.attackRange = this->CPCSkill::GetSkillRange(skillInfo.SKID, skillInfo.level);
		skillInfo.upgradable = false;

		if( SKID == SKID_AC_SHOWER || SKID == SKID_AC_DOUBLE || SKID == SKID_HT_BLITZBEAT || SKID == SKID_AC_CHARGEARROW || SKID == SKID_HT_POWER )
		{
			skillInfo.attackRange += m_pc->m_characterInfo.plusAttRange;
			Trace("%s range: %d\n", info->CSkillTypeInfo::GetName(), skillInfo.attackRange);
		}

		if( pcSkillInfo.type == 0 )
		{
			if( this->CPCSkill::IsConditionalSkill(skillInfo.SKID) == 1 )
			{
				if( this->CPCSkill::IsEnableSkill(skillInfo.SKID, m_pc->m_characterInfo.job) == 1 )
					skillInfo.upgradable = info->CSkillTypeInfo::IsNextLevelUpgradable(skillInfo.level, static_cast<char>(m_pc->m_characterInfo.job));
			}
			else
			if( info->CSkillTypeInfo::IsEventSkill() )
			{
				skillInfo.upgradable = false;
			}
			else
			{
				skillInfo.upgradable = ( skillInfo.level < info->GetMaxLevel() );
			}
		}

		memcpy(&buf[count], &skillInfo, sizeof(skillInfo));
		count += sizeof(skillInfo);

		if( count > sizeof(buf) )
		{
			Trace("[Warning] ** 스킬수가 너무 많음! 직업의 스킬수 줄여야 ** \n", count);
			count -= sizeof(skillInfo);
			break;
		}
	}

	if( count < sizeof(buf) )
	{
		outpacket.PacketLength += count;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_SEND_PACKET, sizeof(outpacket), (int)&outpacket, 0, 0);
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_SEND_PACKET, count, (int)&buf, 0, 0);
	}

	if( count > sizeof(buf) )
		m_pc->AddErrorCount(".\\PCSkill.cpp", 1690, 4, timeGetTime());
}


hook_method<int (CPCSkill::*)(unsigned short skillID)> CPCSkill::_IsConditionalSkill(SERVER, "CPCSkill::IsConditionalSkill");
int CPCSkill::IsConditionalSkill(unsigned short skillID) // line 147
{
	return (this->*_IsConditionalSkill)(skillID);

	return g_skillTypeInfoMgr->CSkillTypeInfoMgr::IsConditionalSkill(m_pc->m_characterInfo.job, skillID);
}


hook_method<int (CPCSkill::*)(unsigned short skillID, short job)> CPCSkill::_IsEnableSkill(SERVER, "CPCSkill::IsEnableSkill");
int CPCSkill::IsEnableSkill(unsigned short skillID, short job) // line 1697
{
	return (this->*_IsEnableSkill)(skillID, job);

	CSkillTypeInfo* info = g_skillTypeInfoMgr->CSkillTypeInfoMgr::SearchSkillTypeInfo(skillID);
	if( info == NULL )
		return 0;

	int joblevel;
	m_pc->GetParameterValue(VAR_JOBLEVEL, joblevel);

	if( joblevel < info->CSkillTypeInfo::GetAvailableJobLevel() )
		return 0;
	
	mystd::map<unsigned short,int>* reqs = g_skillTypeInfoMgr->CSkillTypeInfoMgr::GetLowerSkillTreeInfo(job, skillID);
	if( reqs == NULL )
		return 0;

	for( mystd::map<unsigned short,int>::const_iterator req = reqs->begin(); req != reqs->end(); ++req )
		if( this->CPCSkill::GetSkillLevel(req->first, 1) < req->second )
			return 0;

	return 1;
}


hook_method<void (CPCSkill::*)(unsigned short SKID, int level)> CPCSkill::_AddSkillImitation(SERVER, "CPCSkill::AddSkillImitation");
void CPCSkill::AddSkillImitation(unsigned short SKID, int level) // line 184 (PCSkill2_2(2).cpp)
{
	return (this->*_AddSkillImitation)(SKID, level);

	//TODO
}


hook_method<int (CPCSkill::*)(unsigned short itemID)> CPCSkill::_AM_IsMakableItemBySkill(SERVER, "CPCSkill::AM_IsMakableItemBySkill");
int CPCSkill::AM_IsMakableItemBySkill(unsigned short itemID) // line 266 (PCSkill2_2(2).cpp)
{
	return (this->*_AM_IsMakableItemBySkill)(itemID);

	//TODO
}


hook_method<int (CPCSkill::*)(unsigned short itemID )> CPCSkill::_AM_IsMakableItemByItem(SERVER, "CPCSkill::AM_IsMakableItemByItem");
int CPCSkill::AM_IsMakableItemByItem(unsigned short itemID ) // line 303 (PCSkill2_2(2).cpp)
{
	return (this->*_AM_IsMakableItemByItem)(itemID);

	//TODO
}


hook_method<int (CPCSkill::*)(unsigned short itemID, unsigned long type, int number, MAKABLEITEM_INFO* info)> CPCSkill::_AM_ManufactureItem(SERVER, "CPCSkill::AM_ManufactureItem");
int CPCSkill::AM_ManufactureItem(unsigned short itemID, unsigned long type, int number, MAKABLEITEM_INFO* info)
{
	return (this->*_AM_ManufactureItem)(itemID, type, number, info);

	//TODO
}


hook_method<short (CPCSkill::*)(unsigned short SKID, int isFixedSkill)> CPCSkill::_GetSkillLevel(SERVER, "CPCSkill::GetSkillLevel");
short CPCSkill::GetSkillLevel(unsigned short SKID, int isFixedSkill)
{
	return (this->*_GetSkillLevel)(SKID, isFixedSkill);

	//TODO
}


hook_method<int (CPCSkill::*)(unsigned short SKID)> CPCSkill::_GetSkillType(SERVER, "CPCSkill::GetSkillType");
int CPCSkill::GetSkillType(unsigned short SKID) // line 1105
{
	return (this->*_GetSkillType)(SKID);

	//TODO
}


hook_method<short (CPCSkill::*)(unsigned short SKID, short level)> CPCSkill::_GetSkillRange(SERVER, "CPCSkill::GetSkillRange");
short CPCSkill::GetSkillRange(unsigned short SKID, short level)
{
	return (this->*_GetSkillRange)(SKID, level);

	//TODO
}


hook_method<int (CPCSkill::*)(char xnum)> CPCSkill::_GetWarpInfoXpos(SERVER, "CPCSkill::GetWarpInfoXpos");
int CPCSkill::GetWarpInfoXpos(char xnum)
{
	return (this->*_GetWarpInfoXpos)(xnum);

	//TODO
}


hook_method<void (CPCSkill::*)(void)> CPCSkill::_LoadStarPlaceInfo(SERVER, "CPCSkill::LoadStarPlaceInfo");
void CPCSkill::LoadStarPlaceInfo(void)
{
	return (this->*_LoadStarPlaceInfo)();

	//TODO
}


hook_method<void (CPCSkill::*)(void)> CPCSkill::_UpdateWarpInfo(SERVER, "CPCSkill::UpdateWarpInfo");
void CPCSkill::UpdateWarpInfo(void)
{
	return (this->*_UpdateWarpInfo)();

	//TODO
}


hook_method<void (CPCSkill::*)(char* mapName, short num)> CPCSkill::_UpdateStarPlace(SERVER, "CPCSkill::UpdateStarPlace");
void CPCSkill::UpdateStarPlace(char* mapName, short num)
{
	return (this->*_UpdateStarPlace)(mapName, num);

	//TODO
}


hook_method<int (CPCSkill::*)(WARPPORTAL_INFO* warpinfo)> CPCSkill::_GetWarpInfo(SERVER, "CPCSkill::GetWarpInfo");
int CPCSkill::GetWarpInfo(WARPPORTAL_INFO* warpinfo)
{
	return (this->*_GetWarpInfo)(warpinfo);

	memset(warpinfo, 0, sizeof(*warpinfo));

	int i = 0;

	while( i < countof(warpinfo->mapName) && i < (int)m_warpInfo.size() )
	{
		memcpy(warpinfo->mapName[i], m_warpInfo[i].mapName, sizeof(warpinfo->mapName[i]));
		warpinfo->xPos[i] = m_warpInfo[i].xPos;
		warpinfo->yPos[i] = m_warpInfo[i].yPos;
		++i;
	}

	return i;
}


hook_method<short (CPCSkill::*)(void)> CPCSkill::_GetWarpXPos(SERVER, "CPCSkill::GetWarpXPos");
short CPCSkill::GetWarpXPos(void)
{
	return (this->*_GetWarpXPos)();

	return m_warpXPos;
}


hook_method<short (CPCSkill::*)(void)> CPCSkill::_GetWarpYPos(SERVER, "CPCSkill::GetWarpYPos");
short CPCSkill::GetWarpYPos(void)
{
	return (this->*_GetWarpYPos)();

	return m_warpYPos;
}


hook_method<void (CPCSkill::*)(short xPos)> CPCSkill::_SetWarpXPos(SERVER, "CPCSkill::SetWarpXPos");
void CPCSkill::SetWarpXPos(short xPos)
{
	return (this->*_SetWarpXPos)(xPos);

	m_warpXPos = xPos;
}


hook_method<void (CPCSkill::*)(short yPos)> CPCSkill::_SetWarpYPos(SERVER, "CPCSkill::SetWarpYPos");
void CPCSkill::SetWarpYPos(short yPos)
{
	return (this->*_SetWarpYPos)(yPos);

	m_warpYPos = yPos;
}


hook_method<void (CPCSkill::*)(unsigned short SKID, unsigned long type, int level)> CPCSkill::_UpdateSkillType(SERVER, "CPCSkill::UpdateSkillType");
void CPCSkill::UpdateSkillType(unsigned short SKID, unsigned long type, int level)
{
	return (this->*_UpdateSkillType)(SKID, type, level);

	PC_SKILL_INFO* info = this->CPCSkill::GetSkill(SKID, 0);
	if( info != NULL )
	{
		info->type = type;
		info->disposableLevel = level;
	}
}


hook_method<void (CPCSkill::*)(int index, int count)> CPCSkill::_SetFireWallCount(SERVER, "CPCSkill::SetFireWallCount");
void CPCSkill::SetFireWallCount(int index, int count)
{
	return (this->*_SetFireWallCount)(index, count);

	//TODO
}


hook_method<int (CPCSkill::*)(unsigned short itemID)> CPCSkill::_IsMakableItemBySkill(SERVER, "CPCSkill::IsMakableItemBySkill");
int CPCSkill::IsMakableItemBySkill(unsigned short itemID)
{
	return (this->*_IsMakableItemBySkill)(itemID);

	//TODO
}


hook_method<int (CPCSkill::*)(unsigned short itemID)> CPCSkill::_IsMakableItemByItem(SERVER, "CPCSkill::IsMakableItemByItem");
int CPCSkill::IsMakableItemByItem(unsigned short itemID)
{
	return (this->*_IsMakableItemByItem)(itemID);

	//TODO
}


hook_method<int (CPCSkill::*)(unsigned short itemID, unsigned long type, MAKABLEITEM_INFO* info)> CPCSkill::_ManufactureItem(SERVER, "CPCSkill::ManufactureItem");
int CPCSkill::ManufactureItem(unsigned short itemID, unsigned long type, MAKABLEITEM_INFO* info)
{
	return (this->*_ManufactureItem)(itemID, type, info);

	CITP* itp = g_itpMgr->CITPMgr::GetITP(itemID);
	if( itp == NULL )
		return 0;

	int jobLevel;
	m_pc->GetParameterValue(VAR_JOBLEVEL, jobLevel);

	int percent; // NOTE: promille, actually
	percent = m_pc->CPC::GetDexValue() + m_pc->CPC::GetLukValue() + GetServerRandom(1,100) + 2 * jobLevel;

	int itemType  = itp->GetType();
	int itemLevel = itp->GetItemLevel();
	int itemClass = itp->GetClass();

	if( itp->IsWeapon() )
	{
		percent += 10 * this->CPCSkill::GetSkillLevel(SKID_BS_WEAPONRESEARCH, 0);

		if( itemLevel < 4 && itemLevel != 0 )
			percent += 100 * 4 / itemLevel;

		if( itemClass == 1 )
			percent += 50 * this->CPCSkill::GetSkillLevel(SKID_BS_DAGGER, 0);
		else
		if( itemClass == 2 )
			percent += 50 * this->CPCSkill::GetSkillLevel(SKID_BS_SWORD, 0);
		else
		if( itemClass == 3 )
			percent += 50 * this->CPCSkill::GetSkillLevel(SKID_BS_TWOHANDSWORD, 0);
		else
		if( itemClass == 4 || itemClass == 5 )
			percent += 50 * this->CPCSkill::GetSkillLevel(SKID_BS_SPEAR, 0);
		else
		if( itemClass == 6 || itemClass == 7 )
			percent += 50 * this->CPCSkill::GetSkillLevel(SKID_BS_AXE, 0);
		else
		if( itemClass == 8 || itemClass == 9 )
			percent += 50 * this->CPCSkill::GetSkillLevel(SKID_BS_MACE, 0);
		else
		if( itemClass == 12 )
			percent += 50 * this->CPCSkill::GetSkillLevel(SKID_BS_KNUCKLE, 0);

		int anvilInfo[8];
		anvilInfo[0] = ITID_EMPERIUM_ANVIL;
		anvilInfo[1] = 100;
		anvilInfo[2] = ITID_GOLDEN_ANVIL;
		anvilInfo[3] = 50;
		anvilInfo[4] = ITID_ORIDECON_ANVIL;
		anvilInfo[5] = 25;
		anvilInfo[6] = ITID_ANVIL;
		anvilInfo[7] = 0;

		for( int i = 0; i < countof(anvilInfo)/2; ++i )
		{
			if( m_pc->CPC::GetItemCount(anvilInfo[2 * i]) >= 1 )
			{
				percent += anvilInfo[2 * i + 1];
				break;
			}
		}

		int item;
		item = info->material_ID[0];
		if( item >= ITID_FLAME_HEART && item <= ITID_GREAT_NATURE )
			percent -= 250;
		else
		if( item == 1000 )
			percent -= 150;

		item = info->material_ID[1];
		if( item >= ITID_FLAME_HEART && item <= ITID_GREAT_NATURE )
			percent -= 250;
		else
		if( item == 1000 )
			percent -= 150;

		item = info->material_ID[2];
		if( item >= ITID_FLAME_HEART && item <= ITID_GREAT_NATURE )
			percent -= 250;
		else
		if( item == 1000 )
			percent -= 150;

		int job = m_pc->m_characterInfo.job;
		if( job >= JT_NOVICE_B && job <= JT_SUPERNOVICE_B )
			percent = percent * 70 / 100;
	}

	Trace("percent: %d\n", percent);

	switch( itemID )
	{
	case ITID_HOLY_WATER:
		m_pc->CPC::ConsumeItemForSkill(ITID_EMPTY_BOTTLE, 1);
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 0, 1, 0);
	break;
	case ITID_IRON:
		m_pc->CPC::ConsumeItemForSkill(ITID_IRON_ORE, 1);
		percent += 400 + 50 * this->CPCSkill::GetSkillLevel(SKID_BS_IRON, 0);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 0, 1, 0);
	break;
	case ITID_STEEL:
		m_pc->CPC::ConsumeItemForSkill(ITID_IRON, 5);
		m_pc->CPC::ConsumeItemForSkill(ITID_COAL, 1);
		percent += 300 + 50 * this->CPCSkill::GetSkillLevel(SKID_BS_STEEL, 0);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 0, 1, 0);
	break;
	case ITID_STAR_CRUMB:
		m_pc->CPC::ConsumeItemForSkill(ITID_SPARKLING_DUST, 10);
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 0, 1, 0);
	break;
	case ITID_FLAME_HEART:
		m_pc->CPC::ConsumeItemForSkill(ITID_BOODY_RED, 10);
		percent += 100 + 50 * this->CPCSkill::GetSkillLevel(SKID_BS_ENCHANTEDSTONE, 0);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 0, 1, 0);
	break;
	case ITID_MISTIC_FROZEN:
		m_pc->CPC::ConsumeItemForSkill(ITID_CRYSTAL_BLUE, 10);
		percent += 100 + 50 * this->CPCSkill::GetSkillLevel(SKID_BS_ENCHANTEDSTONE, 0);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 0, 1, 0);
	break;
	case ITID_ROUGH_WIND:
		m_pc->CPC::ConsumeItemForSkill(ITID_WIND_OF_VERDURE, 10);
		percent += 100 + 50 * this->CPCSkill::GetSkillLevel(SKID_BS_ENCHANTEDSTONE, 0);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 0, 1, 0);
	break;
	case ITID_GREAT_NATURE:
		m_pc->CPC::ConsumeItemForSkill(ITID_YELLOW_LIVE, 10);
		percent += 100 + 50 * this->CPCSkill::GetSkillLevel(SKID_BS_ENCHANTEDSTONE, 0);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 0, 1, 0);
	break;
	case ITID_SWORD:
		m_pc->CPC::ConsumeItemForSkill(ITID_IRON, 2);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_FALCHION:
		m_pc->CPC::ConsumeItemForSkill(ITID_IRON, 30);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_BLADE:
		m_pc->CPC::ConsumeItemForSkill(ITID_IRON, 45);
		m_pc->CPC::ConsumeItemForSkill(ITID_TOOTH_OF_BAT, 25);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_LAPIER:
		m_pc->CPC::ConsumeItemForSkill(ITID_STEEL, 20);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_SCIMITER:
		m_pc->CPC::ConsumeItemForSkill(ITID_STEEL, 35);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_RING_POMMEL_SABER:
		m_pc->CPC::ConsumeItemForSkill(ITID_STEEL, 40);
		m_pc->CPC::ConsumeItemForSkill(ITID_CLAW_OF_VOLVES, 50);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_TSURUGI:
		m_pc->CPC::ConsumeItemForSkill(ITID_ORIDECON, 8);
		m_pc->CPC::ConsumeItemForSkill(ITID_STEEL, 15);
		m_pc->CPC::ConsumeItemForSkill(ITID_DARK_RED_JEWEL, 1);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_SABER:
		m_pc->CPC::ConsumeItemForSkill(ITID_ORIDECON, 8);
		m_pc->CPC::ConsumeItemForSkill(ITID_STEEL, 5);
		m_pc->CPC::ConsumeItemForSkill(ITID_WHITE_JEWEL, 1);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_HAEDONGGUM:
		m_pc->CPC::ConsumeItemForSkill(ITID_ORIDECON, 8);
		m_pc->CPC::ConsumeItemForSkill(ITID_STEEL, 10);
		m_pc->CPC::ConsumeItemForSkill(ITID_GOLDEN_JEWEL, 1);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_FLAMBERGE:
		m_pc->CPC::ConsumeItemForSkill(ITID_ORIDECON, 16);
		m_pc->CPC::ConsumeItemForSkill(ITID_CARDINAL_JEWEL_, 1);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_KNIFE:
		m_pc->CPC::ConsumeItemForSkill(ITID_IRON, 1);
		m_pc->CPC::ConsumeItemForSkill(ITID_JELLOPY, 10);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_CUTTER:
		m_pc->CPC::ConsumeItemForSkill(ITID_IRON, 25);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_MAIN_GAUCHE:
		m_pc->CPC::ConsumeItemForSkill(ITID_IRON, 50);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_DIRK:
		m_pc->CPC::ConsumeItemForSkill(ITID_STEEL, 17);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_DAGGER:
		m_pc->CPC::ConsumeItemForSkill(ITID_STEEL, 30);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_STILETTO:
		m_pc->CPC::ConsumeItemForSkill(ITID_STEEL, 40);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_GLADIUS:
		m_pc->CPC::ConsumeItemForSkill(ITID_ORIDECON, 4);
		m_pc->CPC::ConsumeItemForSkill(ITID_STEEL, 40);
		m_pc->CPC::ConsumeItemForSkill(ITID_BLUE_JEWEL, 1);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_DAMASCUS:
		m_pc->CPC::ConsumeItemForSkill(ITID_ORIDECON, 4);
		m_pc->CPC::ConsumeItemForSkill(ITID_STEEL, 60);
		m_pc->CPC::ConsumeItemForSkill(ITID_BLUISH_GREEN_JEWEL, 1);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_KATANA:
		m_pc->CPC::ConsumeItemForSkill(ITID_IRON, 35);
		m_pc->CPC::ConsumeItemForSkill(ITID_HORRENDOUS_MOUTH, 15);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_SLAYER:
		m_pc->CPC::ConsumeItemForSkill(ITID_STEEL, 25);
		m_pc->CPC::ConsumeItemForSkill(ITID_DECAYED_NAIL, 20);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_BASTARD_SWORD:
		m_pc->CPC::ConsumeItemForSkill(ITID_STEEL, 45);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_TWO_HAND_SWORD:
		m_pc->CPC::ConsumeItemForSkill(ITID_ORIDECON, 12);
		m_pc->CPC::ConsumeItemForSkill(ITID_STEEL, 10);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_BROAD_SWORD:
		m_pc->CPC::ConsumeItemForSkill(ITID_ORIDECON, 12);
		m_pc->CPC::ConsumeItemForSkill(ITID_STEEL, 20);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_CLAYMORE:
		m_pc->CPC::ConsumeItemForSkill(ITID_ORIDECON, 16);
		m_pc->CPC::ConsumeItemForSkill(ITID_STEEL, 20);
		m_pc->CPC::ConsumeItemForSkill(ITID_CRYSTAL_JEWEL___, 1);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_AXE:
		m_pc->CPC::ConsumeItemForSkill(ITID_IRON, 10);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_KNUCKLE_DUSTER:
		m_pc->CPC::ConsumeItemForSkill(ITID_STEEL, 50);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_HORA:
		m_pc->CPC::ConsumeItemForSkill(ITID_STEEL, 65);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_FIST:
		m_pc->CPC::ConsumeItemForSkill(ITID_ORIDECON, 4);
		m_pc->CPC::ConsumeItemForSkill(ITID_CARDINAL_JEWEL, 10);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_CLAW:
		m_pc->CPC::ConsumeItemForSkill(ITID_ORIDECON, 8);
		m_pc->CPC::ConsumeItemForSkill(ITID_GOLDEN_JEWEL, 10);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_FINGER:
		m_pc->CPC::ConsumeItemForSkill(ITID_ORIDECON, 4);
		m_pc->CPC::ConsumeItemForSkill(ITID_WHITE_JEWEL, 10);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_WAGHNAKH:
		m_pc->CPC::ConsumeItemForSkill(ITID_IRON, 160);
		m_pc->CPC::ConsumeItemForSkill(ITID_SCARLET_JEWEL, 1);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_BATTLE_AXE:
		m_pc->CPC::ConsumeItemForSkill(ITID_IRON, 110);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_HAMMER:
		m_pc->CPC::ConsumeItemForSkill(ITID_STEEL, 30);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_BUSTER:
		m_pc->CPC::ConsumeItemForSkill(ITID_ORIDECON, 4);
		m_pc->CPC::ConsumeItemForSkill(ITID_STEEL, 20);
		m_pc->CPC::ConsumeItemForSkill(ITID_ORCISH_CUSPID, 30);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_TWO_HANDED_AXE:
		m_pc->CPC::ConsumeItemForSkill(ITID_ORIDECON, 8);
		m_pc->CPC::ConsumeItemForSkill(ITID_STEEL, 10);
		m_pc->CPC::ConsumeItemForSkill(ITID_VIOLET_JEWEL, 1);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_CLUB:
		m_pc->CPC::ConsumeItemForSkill(ITID_IRON, 3);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_MACE:
		m_pc->CPC::ConsumeItemForSkill(ITID_IRON, 30);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_SMASHER:
		m_pc->CPC::ConsumeItemForSkill(ITID_STEEL, 20);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_FLAIL:
		m_pc->CPC::ConsumeItemForSkill(ITID_STEEL, 33);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_CHAIN:
		m_pc->CPC::ConsumeItemForSkill(ITID_STEEL, 45);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_MORNING_STAR:
		m_pc->CPC::ConsumeItemForSkill(ITID_STEEL, 85);
		m_pc->CPC::ConsumeItemForSkill(ITID_CRYSTAL_JEWEL, 1);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_SWORD_MACE:
		m_pc->CPC::ConsumeItemForSkill(ITID_STEEL, 100);
		m_pc->CPC::ConsumeItemForSkill(ITID_SHARP_SCALE, 20);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_STUNNER:
		m_pc->CPC::ConsumeItemForSkill(ITID_STEEL, 120);
		m_pc->CPC::ConsumeItemForSkill(ITID_VOUCHER_OF_ORCISH_HERO, 1);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_JAVELIN:
		m_pc->CPC::ConsumeItemForSkill(ITID_IRON, 3);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_SPEAR:
		m_pc->CPC::ConsumeItemForSkill(ITID_IRON, 35);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_PIKE:
		m_pc->CPC::ConsumeItemForSkill(ITID_IRON, 70);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_GUISARME:
		m_pc->CPC::ConsumeItemForSkill(ITID_STEEL, 25);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_GLAIVE:
		m_pc->CPC::ConsumeItemForSkill(ITID_STEEL, 40);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_PARTIZAN:
		m_pc->CPC::ConsumeItemForSkill(ITID_STEEL, 55);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_TRIDENT:
		m_pc->CPC::ConsumeItemForSkill(ITID_ORIDECON, 8);
		m_pc->CPC::ConsumeItemForSkill(ITID_STEEL, 10);
		m_pc->CPC::ConsumeItemForSkill(ITID_SKYBLUE_JEWEL, 5);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_HALBERD:
		m_pc->CPC::ConsumeItemForSkill(ITID_ORIDECON, 12);
		m_pc->CPC::ConsumeItemForSkill(ITID_STEEL, 10);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	case ITID_LANCE:
		m_pc->CPC::ConsumeItemForSkill(ITID_ORIDECON, 12);
		m_pc->CPC::ConsumeItemForSkill(ITID_CARDINAL_JEWEL, 3);
		m_pc->CPC::ConsumeItemForSkill(ITID_EVIL_HORN, 2);
		if( GetServerRandom(0,20000) % 1000 >= percent )
			return 0;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pc, CM_ADD_ITEM, itemID, 1, (int)info, 0);
	break;
	default:
		if( !this->CPCSkill::AM_ManufactureItem(itemID, type, 1, 0) )
			return 0;
	break;
	}

	return 1;
}


hook_method<void (CPCSkill::*)(const unsigned long in_skAID)> CPCSkill::_DeletePlayingSkill(SERVER, "CPCSkill::DeletePlayingSkill");
void CPCSkill::DeletePlayingSkill(const unsigned long in_skAID)
{
	return (this->*_DeletePlayingSkill)(in_skAID);

	//TODO
}


hook_method<void (CPCSkill::*)(void)> CPCSkill::_DestroyPlayingSkill(SERVER, "CPCSkill::DestroyPlayingSkill");
void CPCSkill::DestroyPlayingSkill(void)
{
	return (this->*_DestroyPlayingSkill)();

	//TODO
}


hook_method<void (CPCSkill::*)(int x, int y)> CPCSkill::_SetPosPlayingSkill(SERVER, "CPCSkill::SetPosPlayingSkill");
void CPCSkill::SetPosPlayingSkill(int x, int y)
{
	return (this->*_SetPosPlayingSkill)(x, y);

	//TODO
}


hook_method<void (CPCSkill::*)(void)> CPCSkill::_DisappearPlayingSkill(SERVER, "CPCSkill::DisappearPlayingSkill");
void CPCSkill::DisappearPlayingSkill(void)
{
	return (this->*_DisappearPlayingSkill)();

	//TODO
}


hook_method<void (CPCSkill::*)(void)> CPCSkill::_UpdateSpiritsInfo(SERVER, "CPCSkill::UpdateSpiritsInfo");
void CPCSkill::UpdateSpiritsInfo(void) // line 32-54
{
	return (this->*_UpdateSpiritsInfo)();

	// TODO
}


//hook_method<unsigned long (CPCSkill::*)(void)> CPCSkill::_GetSKIDFromAbracadabra(SERVER, "CPCSkill::GetSKIDFromAbracadabra");
unsigned long CPCSkill::GetSKIDFromAbracadabra(void)
{
//	return (this->*_GetSKIDFromAbracadabra)();

	return m_abracadabraSKID;
}


//hook_method<void (CPCSkill::*)(unsigned long SKID)> CPCSkill::_SetSKIDFromAbracadabra(SERVER, "CPCSkill::SetSKIDFromAbracadabra");
void CPCSkill::SetSKIDFromAbracadabra(unsigned long SKID)
{
//	return (this->*_SetSKIDFromAbracadabra)(SKID);

	m_abracadabraSKID = SKID;
}


hook_method<void (CPCSkill::*)(unsigned long SKID, int count)> CPCSkill::_SetLimitedSkill(SERVER, "CPCSkill::SetLimitedSkill");
void CPCSkill::SetLimitedSkill(unsigned long SKID, int count)
{
	return (this->*_SetLimitedSkill)(SKID, count);

	//TODO
}


hook_method<void (CPCSkill::*)(CZGuildInfo* pGuild)> CPCSkill::_SetMasterSkill(SERVER, "CPCSkill::SetMasterSkill");
void CPCSkill::SetMasterSkill(CZGuildInfo* pGuild)
{
	return (this->*_SetMasterSkill)(pGuild);

	//TODO
}


//hook_method<mystd::deque<WARP_POSITION>* (CPCSkill::*)(void)> CPCSkill::_GetWarpPosInfo(SERVER, "CPCSkill::GetWarpPosInfo");
mystd::deque<WARP_POSITION>* CPCSkill::GetWarpPosInfo(void) // line ???
{
//	return (this->*_GetWarpPosInfo)();

	return &m_warpInfo;
}
