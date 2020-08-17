#include "enum.hpp"
#include "CNpcMob.hpp"


CNpcMob::CNpcMob(void)
{
	m_type = NPC_MOB_TYPE;
	m_bossInfo.BOSS_INFO::Init(m_pathInfo.m_moveInfo.xPos, m_pathInfo.m_moveInfo.yPos);
}


CNpcMob::~CNpcMob(void)
{
}


hook_method<int (CNpcMob::*)(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4)> CNpcMob::_OnMsg(SERVER, "CNpcMob::OnMsg");
int CNpcMob::OnMsg(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4)
{
	return (this->*_OnMsg)(sender, receiver, msgID, par1, par2, par3, par4);

	//TODO
}


hook_method<void (CNpcMob::*)(void)> CNpcMob::_Reset(SERVER, "CNpcMob::Reset");
void CNpcMob::Reset(void)
{
	return (this->*_Reset)();

	//TODO
}


hook_method<void (CNpcMob::*)(void)> CNpcMob::_OnProcess(SERVER, "CNpcMob::OnProcess");
void CNpcMob::OnProcess(void)
{
	return (this->*_OnProcess)();

	if( m_characterInfo.isValid )
	{
		this->CheckCommandQueue();

		if( m_currentState != DEAD_ST )
		{
			m_npcUpdater.CNPCUpdater::CheckMove();

			if( m_stateTimer.CPollTimer::CheckTimeout(timeGetTime()) )
				m_npcUpdater.CNPCUpdater::CheckState();

			if( m_npcSkill.CNPCSkill::OnProcess() )
			{
				mystd::vector<ClientCache*>& cache = m_neighborCache.CNeighborCache::GetListPoint();
				if( cache.size() > 0 )
					m_npcStateUpdater.CNPCStateUpdater::CheckInput();
			}
		}
	}
	else
	{
		if( m_currentState == DEAD_ST )
		{
			if( !m_npcSkill.CNPCSkill::OnProcess() )
				m_npcStateUpdater.CNPCStateUpdater::CheckInput();
		}
	}

	this->CNpcMob::UpdateBossInfo();
}


hook_method<int (CNpcMob::*)(int skillID)> CNpcMob::_GetInvincibleTimeInfo(SERVER, "CNpcMob::GetInvincibleTimeInfo");
int CNpcMob::GetInvincibleTimeInfo(int skillID)
{
	return (this->*_GetInvincibleTimeInfo)(skillID);

	//TODO
}


hook_method<int (CNpcMob::*)(void)> CNpcMob::_ChkGndSkillDurability(SERVER, "CNpcMob::ChkGndSkillDurability");
int CNpcMob::ChkGndSkillDurability(void)
{
	return (this->*_ChkGndSkillDurability)();

	return ( m_npcSkill.m_sanctuaryCnt > 0 );
}


/* hook_method<void (CNpcMob::*)(CCharacter* ch)> CNpcMob::_SetEffectByGospel(SERVER, "CNpcMob::SetEffectByGospel");
void CNpcMob::SetEffectByGospel(CCharacter* ch)
{
	return (this->*_SetEffectByGospel)(ch);

	//TODO
} */


hook_method<void (CNpcMob::*)(void)> CNpcMob::_ResetEffectiveByDispel(SERVER, "CNpcMob::ResetEffectiveByDispel");
void CNpcMob::ResetEffectiveByDispel(void)
{
	return (this->*_ResetEffectiveByDispel)();

	//TODO
}


//hook_method<int (CNpcMob::*)(void)> CNpcMob::_GetMonsterDBDef(SERVER, "CNpcMob::GetMonsterDBDef");
int CNpcMob::GetMonsterDBDef(void)
{
//	return (this->*_GetMonsterDBDef)();

	return m_characterInfo.def;
}


//hook_method<int (CNpcMob::*)(void)> CNpcMob::_GetMonsterDBMdef(SERVER, "CNpcMob::GetMonsterDBMdef");
int CNpcMob::GetMonsterDBMdef(void)
{
//	return (this->*_GetMonsterDBMdef)();

	return m_characterInfo.mdef;
}


hook_method<short (CNpcMob::*)(void)> CNpcMob::_CheckBossEnableRegen(SERVER, "CNpcMob::CheckBossEnableRegen");
short CNpcMob::CheckBossEnableRegen(void)
{
	return (this->*_CheckBossEnableRegen)();

	//TODO
}


//hook_method<void (CNpcMob::*)(unsigned long& hour, unsigned long& minute)> CNpcMob::_GetBossRegenSystemTime(SERVER, "CNpcMob::GetBossRegenSystemTime");
void CNpcMob::GetBossRegenSystemTime(unsigned long& hour, unsigned long& minute)
{
//	return (this->*_GetBossRegenSystemTime)(hour, minute);

	hour = m_bossInfo.regenSystemTime.wHour;
	minute = m_bossInfo.regenSystemTime.wMinute;
}


//hook_method<bool (CNpcMob::*)(void)> CNpcMob::_IsBossInMap(SERVER, "CNpcMob::IsBossInMap");
bool CNpcMob::IsBossInMap(void)
{
//	return (this->*_IsBossInMap)();

	return m_bossInfo.isBossInMap;
}


hook_method<void (CNpcMob::*)(void)> CNpcMob::_InitCore(SERVER, "CNpcMob::InitCore");
void CNpcMob::InitCore(void)
{
	return (this->*_InitCore)();

	//TODO
}


hook_method<void (CNpcMob::*)(int par1)> CNpcMob::_OnHealHP(SERVER, "CNpcMob::OnHealHP");
void CNpcMob::OnHealHP(int par1)
{
	return (this->*_OnHealHP)(par1);

	//TODO
}


hook_method<void (CNpcMob::*)(CCharacter* sender, int par1)> CNpcMob::_OnDecreaseDef(SERVER, "CNpcMob::OnDecreaseDef");
void CNpcMob::OnDecreaseDef(CCharacter* sender, int par1)
{
	return (this->*_OnDecreaseDef)(sender, par1);

	//TODO
}


hook_method<void (CNpcMob::*)(void)> CNpcMob::_OnSetBossInMap(SERVER, "CNpcMob::OnSetBossInMap");
void CNpcMob::OnSetBossInMap(void)
{
	return (this->*_OnSetBossInMap)();

	//TODO
}


hook_method<void (CNpcMob::*)(CCharacter* sender)> CNpcMob::_OnRequestBossInfo(SERVER, "CNpcMob::OnRequestBossInfo");
void CNpcMob::OnRequestBossInfo(CCharacter* sender)
{
	return (this->*_OnRequestBossInfo)(sender);

	//TODO
}


hook_method<void (CNpcMob::*)(CCharacter* sender)> CNpcMob::_OnReqAddBossPCList(SERVER, "CNpcMob::OnReqAddBossPCList");
void CNpcMob::OnReqAddBossPCList(CCharacter* sender)
{
	return (this->*_OnReqAddBossPCList)(sender);

	//TODO
}


hook_method<void (CNpcMob::*)(CCharacter* sender)> CNpcMob::_OnReqDelBossPCList(SERVER, "CNpcMob::OnReqDelBossPCList");
void CNpcMob::OnReqDelBossPCList(CCharacter* sender)
{
	return (this->*_OnReqDelBossPCList)(sender);

	//TODO
}


hook_method<void (CNpcMob::*)(CCharacter* sender, int par1, int par2, int par3)> CNpcMob::_OnBlessingFromAcolyte(SERVER, "CNpcMob::OnBlessingFromAcolyte");
void CNpcMob::OnBlessingFromAcolyte(CCharacter* sender, int par1, int par2, int par3)
{
	return (this->*_OnBlessingFromAcolyte)(sender, par1, par2, par3);

	//TODO
}


hook_method<void (CNpcMob::*)(void)> CNpcMob::_OnCureFromAcolyte(SERVER, "CNpcMob::OnCureFromAcolyte");
void CNpcMob::OnCureFromAcolyte(void)
{
	return (this->*_OnCureFromAcolyte)();

	//TODO
}


//hook_method<void (CNpcMob::*)(int healPercent)> CNpcMob::_OnResurrection(SERVER, "CNpcMob::OnResurrection");
void CNpcMob::OnResurrection(int healPercent)
{
//	return (this->*_OnResurrection)(healPercent);

	return;
}


hook_method<void (CNpcMob::*)(unsigned long time, int skillID)> CNpcMob::_SetInvincibleTimeInfo(SERVER, "CNpcMob::SetInvincibleTimeInfo");
void CNpcMob::SetInvincibleTimeInfo(unsigned long time, int skillID)
{
	return (this->*_SetInvincibleTimeInfo)(time, skillID);

	//TODO
}


hook_method<void (CNpcMob::*)(unsigned long firstTime, unsigned long secondTime, int state)> CNpcMob::_SetBodyStateTimeInfo(SERVER, "CNpcMob::SetBodyStateTimeInfo");
void CNpcMob::SetBodyStateTimeInfo(unsigned long firstTime, unsigned long secondTime, int state)
{
	return (this->*_SetBodyStateTimeInfo)(firstTime, secondTime, state);

	//TODO
}


hook_method<void (CNpcMob::*)(int firstTime, int secondTime, int state)> CNpcMob::_SetHealthStateTimeInfo(SERVER, "CNpcMob::SetHealthStateTimeInfo");
void CNpcMob::SetHealthStateTimeInfo(int firstTime, int secondTime, int state)
{
	return (this->*_SetHealthStateTimeInfo)(firstTime, secondTime, state);

	//TODO
}


hook_method<void (CNpcMob::*)(void)> CNpcMob::_UpdateBossInfo(SERVER, "CNpcMob::UpdateBossInfo");
void CNpcMob::UpdateBossInfo(void)
{
	return (this->*_UpdateBossInfo)();

	//TODO
}


hook_method<char* (CNpcMob::*)(bool isWithMsg)> CNpcMob::_GetBossInfo(SERVER, "CNpcMob::GetBossInfo");
char* CNpcMob::GetBossInfo(bool isWithMsg)
{
	return (this->*_GetBossInfo)(isWithMsg);

	//TODO
}
