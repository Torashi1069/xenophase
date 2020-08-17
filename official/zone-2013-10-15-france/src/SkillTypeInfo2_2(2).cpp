#include "CharacterMgr.h"
#include "SkillTypeInfo2_2(2).h"
#include "SkillTypeInfoMgr.h"
////////////////////////////////////////


short SK_ROGUE::GetMaxLevel() // (12.h)
{
	return 5;
}


BOOL SK_ROGUE::IsAvailableJob(short job) // (14.h)
{
	return ( job == JT_ROGUE );
}


short SK_ROGUE::GetSPCost(short level) // (15.h)
{
	return 0;
}


short SK_ROGUE::GetPreDelayTime(short level) // (16.h)
{
	return 0;
}


////////////////////////////////////////


void SK_RG_PLAGIARISM::Init() // 406-409 (404-407)
{
	m_SKID = SKID_RG_PLAGIARISM;
	m_type = SKILLTYPE_PASSIVE;
}


int SK_RG_PLAGIARISM::OnMsg(CCharacter* sender, unsigned short receiver, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4) // ??? (410-413)
{
	return this->CSkillTypeInfo::OnMsg(sender, receiver, MsgID, skLevel, targetID, par3, par4);
}


short SK_RG_PLAGIARISM::GetMaxLevel() // ??? (160.h)
{
	return 10;
}


////////////////////////////////////////


short SK_DANCER::GetMaxLevel() // (447.h)
{
	return 10;
}


BOOL SK_DANCER::IsAvailableJob(short job) // (449.h)
{
	return ( job == JT_DANCER );
}


short SK_DANCER::GetSPCost(short level) // (450.h)
{
	return 0;
}


short SK_DANCER::GetPreDelayTime(short level) // (451.h)
{
	return 0;
}


////////////////////////////////////////


void SK_DC_SCREAM::Init() // 1410-1413 (1430-1433)
{
	m_SKID = SKID_DC_SCREAM;
	m_type = SKILLTYPE_TOME;
}


int SK_DC_SCREAM::OnMsg(CCharacter* sender, unsigned short receiver, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4) // 1416-1433 (1436-1453)
{
	switch( MsgID )
	{
	case SM_USE_SKILL:
	{
		MSG_TYPE4_FIVEDWORD data;
		data.data1 = 50 * (skLevel + 5); // percent
		data.data2 = 0;
		data.data3 = 0;
		data.data4 = par3; // spCost
		data.data5 = skLevel;
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, sender, CM_OPERSKILL_TOSELF22_2, receiver, targetID, (int)&data, 0);
	}
	break;
	default:
	{
		this->CSkillTypeInfo::OnMsg(sender, receiver, MsgID, skLevel, targetID, par3, 0);
	}
	break;
	};

	return 0;
}


short SK_DC_SCREAM::GetMaxLevel() // (485.h)
{
	return 5;
}


short SK_DC_SCREAM::GetSPCost(short level) // (486.h)
{
	return 2 * level + 10;
}


////////////////////////////////////////
