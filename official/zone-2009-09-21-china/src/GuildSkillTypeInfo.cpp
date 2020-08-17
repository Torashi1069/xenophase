#include "GuildSkillTypeInfo.h"
#include "enum.hpp"


hook_method<void (SK_GD_EXTENSION::*)(void)> SK_GD_EXTENSION::_Init(SERVER, "SK_GD_EXTENSION::Init");
void SK_GD_EXTENSION::Init(void) // line 83
{
	return (this->*_Init)();

	m_SKID = SKID_GD_EXTENSION;
	m_type = 0;
}


hook_method<int (SK_GD_EXTENSION::*)(CCharacter* sender, unsigned short receiver, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4)> SK_GD_EXTENSION::_OnMsg(SERVER, "SK_GD_EXTENSION::OnMsg");
int SK_GD_EXTENSION::OnMsg(CCharacter* sender, unsigned short receiver, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4) // line 89
{
	return (this->*_OnMsg)(sender, receiver, MsgID, skLevel, targetID, par3, par4);

	if( MsgID == 14 )
		return 4 * skLevel + 16;

	return 0;
}


hook_method<short (SK_GD_EXTENSION::*)(void)> SK_GD_EXTENSION::_GetMaxLevel(SERVER, "SK_GD_EXTENSION::GetMaxLevel");
short SK_GD_EXTENSION::GetMaxLevel(void) // line 47 (GuildSkillTypeInfo.h)
{
	return (this->*_GetMaxLevel)();

	return 10;
}


hook_method<int (SK_GD_EXTENSION::*)(short job)> SK_GD_EXTENSION::_IsAvailableJob(SERVER, "SK_GD_EXTENSION::IsAvailableJob");
int SK_GD_EXTENSION::IsAvailableJob(short job) // line 48 (GuildSkillTypeInfo.h)
{
	return (this->*_IsAvailableJob)(job);

	return 1;
}
