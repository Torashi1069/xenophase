#include "CharacterMgr.h"
#include "SkillTypeInfo2_2(1).h"
#include "globals.hpp"
#include "struct.hpp"


////////////////////////////////////////


hook_method<short (SK_MONK::*)(void)> SK_MONK::_GetMaxLevel(SERVER, "SK_MONK::GetMaxLevel");
short SK_MONK::GetMaxLevel(void) // line ???
{
	return (this->*_GetMaxLevel)();

	return 10;
}


hook_method<int (SK_MONK::*)(short job)> SK_MONK::_IsAvailableJob(SERVER, "SK_MONK::IsAvailableJob");
int SK_MONK::IsAvailableJob(short job) // line 139 (SkillTypeInfo2_2(1).h)
{
	return (this->*_IsAvailableJob)(job);

	return ( job == JT_MONK );
}


hook_method<short (SK_MONK::*)(short level)> SK_MONK::_GetSPCost(SERVER, "SK_MONK::GetSPCost");
short SK_MONK::GetSPCost(short level) // line ???
{
	return (this->*_GetSPCost)(level);

	return 0;
}


hook_method<short (SK_MONK::*)(short level)> SK_MONK::_GetPreDelayTime(SERVER, "SK_MONK::GetPreDelayTime");
short SK_MONK::GetPreDelayTime(short level) // line ???
{
	return (this->*_GetPreDelayTime)(level);

	return 0;
}


////////////////////////////////////////


hook_method<void (SK_MO_TRIPLEATTACK::*)(void)> SK_MO_TRIPLEATTACK::_Init(SERVER, "SK_MO_TRIPLEATTACK::Init");
void SK_MO_TRIPLEATTACK::Init(void) // line 486
{
	return (this->*_Init)();

	m_SKID = SKID_MO_TRIPLEATTACK;
	m_type = 0;
	m_pattern = 1;
}


hook_method<int (SK_MO_TRIPLEATTACK::*)(CCharacter* sender, unsigned short receiver, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4)> SK_MO_TRIPLEATTACK::_OnMsg(SERVER, "SK_MO_TRIPLEATTACK::OnMsg");
int SK_MO_TRIPLEATTACK::OnMsg(CCharacter* sender, unsigned short receiver, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4) // line 492
{
	return (this->*_OnMsg)(sender, receiver, MsgID, skLevel, targetID, par3, par4);

	if( MsgID == 12 )
	{
		if( targetID != 0 )
		{
			MSG_TYPE4_FIVEDWORD data;
			data.data1 = 100 + 20 * skLevel;
			data.data5 = skLevel;
			data.data2 = 2;
			data.data3 = 3;
			data.data4 = par3;
			g_characterMgr->CCharacterMgr::SendMsg(NULL, sender, CM_ATTSKILL_TOCHAR22_1, receiver, targetID, (int)&data, 0);
		}
	}
	else
	{
		this->CSkillTypeInfo::OnMsg(sender, receiver, MsgID, skLevel, targetID, par3, 0);
	}

	return 0;
}


////////////////////////////////////////


hook_method<short (SK_HIGHWIZARD::*)(void)> SK_HIGHWIZARD::_GetMaxLevel(SERVER, "SK_HIGHWIZARD::GetMaxLevel");
short SK_HIGHWIZARD::GetMaxLevel(void) // line ???
{
	return (this->*_GetMaxLevel)();

	return 10;
}


hook_method<int (SK_HIGHWIZARD::*)(short job)> SK_HIGHWIZARD::_IsAvailableJob(SERVER, "SK_HIGHWIZARD::IsAvailableJob");
int SK_HIGHWIZARD::IsAvailableJob(short job) // line 829 (SkillTypeInfo2_2(1).h)
{
	return (this->*_IsAvailableJob)(job);

	return ( job == JT_WIZARD_H );
}


hook_method<short (SK_HIGHWIZARD::*)(short level)> SK_HIGHWIZARD::_GetSPCost(SERVER, "SK_HIGHWIZARD::GetSPCost");
short SK_HIGHWIZARD::GetSPCost(short level) // line ???
{
	return (this->*_GetSPCost)(level);

	return 0;
}


hook_method<short (SK_HIGHWIZARD::*)(short level)> SK_HIGHWIZARD::_GetPreDelayTime(SERVER, "SK_HIGHWIZARD::GetPreDelayTime");
short SK_HIGHWIZARD::GetPreDelayTime(short level) // line ???
{
	return (this->*_GetPreDelayTime)(level);

	return 0;
}


////////////////////////////////////////


hook_method<void (SK_HW_MAGICPOWER::*)(void)> SK_HW_MAGICPOWER::_Init(SERVER, "SK_HW_MAGICPOWER::Init");
void SK_HW_MAGICPOWER::Init(void) // line 2458
{
	return (this->*_Init)();

	m_SKID = SKID_HW_MAGICPOWER;
	m_type = 4;
}


hook_method<int (SK_HW_MAGICPOWER::*)(CCharacter* sender, unsigned short receiver, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4)> SK_HW_MAGICPOWER::_OnMsg(SERVER, "SK_HW_MAGICPOWER::OnMsg");
int SK_HW_MAGICPOWER::OnMsg(CCharacter* sender, unsigned short receiver, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4) // line 2463
{
	return (this->*_OnMsg)(sender, receiver, MsgID, skLevel, targetID, par3, par4);

	if( MsgID == 12 )
	{
		MSG_TYPE4_FIVEDWORD data;
		data.data1 = 5 * skLevel;
		data.data2 = 30000;
		data.data3 = 1;
		data.data4 = par3;
		data.data5 = skLevel;
		g_characterMgr->CCharacterMgr::SendMsg(NULL, sender, CM_OPERSKILL_TOSELF22_1, receiver, targetID, (int)&data, 0);
	}
	else
	{
		this->CSkillTypeInfo::OnMsg(sender, receiver, MsgID, skLevel, targetID, par3, 0);
	}

	return 0;
}


hook_method<short (SK_HW_MAGICPOWER::*)(short level)> SK_HW_MAGICPOWER::_GetSPCost(SERVER, "SK_HW_MAGICPOWER::GetSPCost");
short SK_HW_MAGICPOWER::GetSPCost(short level) // line ????
{
	return (this->*_GetSPCost)(level);

	return 10 + 4 * level;
}


////////////////////////////////////////
