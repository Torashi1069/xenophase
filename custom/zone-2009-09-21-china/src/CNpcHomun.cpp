#include "CNpcHomun.hpp"


hook_method<int (CNpcHomun::*)(unsigned short id, int& value)> CNpcHomun::_GetParameterValue(SERVER, "CNpcHomun::GetParameterValue");
int CNpcHomun::GetParameterValue(unsigned short id, int& value)
{
	return (this->*_GetParameterValue)(id, value);

	//TODO
}


hook_method<int (CNpcHomun::*)(unsigned short id, int value)> CNpcHomun::_UpdateParameterValue(SERVER, "CNpcHomun::UpdateParameterValue");
int CNpcHomun::UpdateParameterValue(unsigned short id, int value)
{
	return (this->*_UpdateParameterValue)(id, value);

	//TODO
}


hook_method<int (CNpcHomun::*)(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4)> CNpcHomun::_OnMsg(SERVER, "CNpcHomun::OnMsg");
int CNpcHomun::OnMsg(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4)
{
	return (this->*_OnMsg)(sender, receiver, msgID, par1, par2, par3, par4);

	//TODO
}


hook_method<void (CNpcHomun::*)(void)> CNpcHomun::_OnProcess(SERVER, "CNpcHomun::OnProcess");
void CNpcHomun::OnProcess(void)
{
	return (this->*_OnProcess)();

	//TODO
}


hook_method<int (CNpcHomun::*)(CCharacter* ch, unsigned long flag)> CNpcHomun::_IsTarget(SERVER, "CNpcHomun::IsTarget");
int CNpcHomun::IsTarget(CCharacter* ch, unsigned long flag)
{
	return (this->*_IsTarget)(ch, flag);

	//TODO
}


hook_method<void (CNpcHomun::*)(void)> CNpcHomun::_OnTimerHomun(SERVER, "CNpcHomun::OnTimerHomun");
void CNpcHomun::OnTimerHomun(void)
{
	return (this->*_OnTimerHomun)();

	//TODO
}


hook_method<void (CNpcHomun::*)(char* name)> CNpcHomun::_OnReqRename(SERVER, "CNpcHomun::OnReqRename");
void CNpcHomun::OnReqRename(char* name)
{
	return (this->*_OnReqRename)(name);

	//TODO
}


hook_method<void (CNpcHomun::*)(HOMUN_DBINFO* info)> CNpcHomun::_SetCharInfo(SERVER, "CNpcHomun::SetCharInfo");
void CNpcHomun::SetCharInfo(HOMUN_DBINFO* info)
{
	return (this->*_SetCharInfo)(info);

	//TODO
}


hook_method<void (CNpcHomun::*)(void)> CNpcHomun::_InitProperty(SERVER, "CNpcHomun::InitProperty");
void CNpcHomun::InitProperty(void)
{
	return (this->*_InitProperty)();

	//TODO
}


hook_method<void (CNpcHomun::*)(DWORD dwTick)> CNpcHomun::_InitTimer(SERVER, "CNpcHomun::InitTimer");
void CNpcHomun::InitTimer(DWORD dwTick) // line 154-168
{
	return (this->*_InitTimer)(dwTick);

	m_timerF.CPollTimer::Init(dwTick, 60000);
	m_timerHunger.CPollTimer::Init(dwTick, 20000);
	m_timerState.CPollTimer::Init(dwTick, 350);
	m_characterTimeInfo.HPLastHealTime = dwTick;
	m_characterTimeInfo.SPLastHealTime = dwTick;
}


hook_method<void (CNpcHomun::*)(void)> CNpcHomun::_InitConditionTime(SERVER, "CNpcHomun::InitConditionTime");
void CNpcHomun::InitConditionTime(void)
{
	return (this->*_InitConditionTime)();

	//TODO
}


hook_method<void (CNpcHomun::*)(void)> CNpcHomun::_IsLevelUp(SERVER, "CNpcHomun::IsLevelUp");
void CNpcHomun::IsLevelUp(void)
{
	return (this->*_IsLevelUp)();

	//TODO
}


hook_method<void (CNpcHomun::*)(HOMUN_DBINFO* info)> CNpcHomun::_UpdateHomunDBInfo(SERVER, "CNpcHomun::UpdateHomunDBInfo");
void CNpcHomun::UpdateHomunDBInfo(HOMUN_DBINFO* info)
{
	return (this->*_UpdateHomunDBInfo)(info);

	//TODO
}


hook_method<void (CNpcHomun::*)(int state)> CNpcHomun::_SetModifiedState(SERVER, "CNpcHomun::SetModifiedState");
void CNpcHomun::SetModifiedState(int state)
{
	return (this->*_SetModifiedState)(state);

	//TODO
}


hook_method<void (CNpcHomun::*)(int state)> CNpcHomun::_ResetModifiedState(SERVER, "CNpcHomun::ResetModifiedState");
void CNpcHomun::ResetModifiedState(int state)
{
	return (this->*_ResetModifiedState)(state);

	//TODO
}


hook_method<int (CNpcHomun::*)(void)> CNpcHomun::_EvolutionHomun(SERVER, "CNpcHomun::EvolutionHomun");
int CNpcHomun::EvolutionHomun(void)
{
	return (this->*_EvolutionHomun)();

	//TODO
}


hook_method<int (CNpcHomun::*)(void)> CNpcHomun::_IsEvolutionType(SERVER, "CNpcHomun::IsEvolutionType");
int CNpcHomun::IsEvolutionType(void)
{
	return (this->*_IsEvolutionType)();

	//TODO
}


hook_method<void (CNpcHomun::*)(void)> CNpcHomun::_StartUseSkill(SERVER, "CNpcHomun::StartUseSkill");
void CNpcHomun::StartUseSkill(void)
{
	return (this->*_StartUseSkill)();

	//TODO
}


hook_method<int (CNpcHomun::*)(unsigned short SKID)> CNpcHomun::_IsSkillUsable(SERVER, "CNpcHomun::IsSkillUsable");
int CNpcHomun::IsSkillUsable(unsigned short SKID)
{
	return (this->*_IsSkillUsable)(SKID);

	//TODO
}


hook_method<int (CNpcHomun::*)(unsigned short SKID, int level, CCharacter* ch)> CNpcHomun::_IsSkillEnable(SERVER, "CNpcHomun::IsSkillEnable");
int CNpcHomun::IsSkillEnable(unsigned short SKID, int level, CCharacter* ch)
{
	return (this->*_IsSkillEnable)(SKID, level, ch);

	//TODO
}


hook_method<short (CNpcHomun::*)(unsigned short SKID)> CNpcHomun::_GetSKLevel(SERVER, "CNpcHomun::GetSKLevel");
short CNpcHomun::GetSKLevel(unsigned short SKID)
{
	return (this->*_GetSKLevel)(SKID);

	//TODO
}


hook_method<void (CNpcHomun::*)(unsigned short SKID)> CNpcHomun::_UpgradeSKLevel(SERVER, "CNpcHomun::UpgradeSKLevel");
void CNpcHomun::UpgradeSKLevel(unsigned short SKID)
{
	return (this->*_UpgradeSKLevel)(SKID);

	//TODO
}


hook_method<CPC* (CNpcHomun::*)(void)> CNpcHomun::_GetOwner(SERVER, "CNpcHomun::GetOwner");
CPC* CNpcHomun::GetOwner(void)
{
	return (this->*_GetOwner)();

	//TODO
}


hook_method<int (CNpcHomun::*)(void)> CNpcHomun::_GetSP(SERVER, "CNpcHomun::GetSP");
int CNpcHomun::GetSP(void)
{
	return (this->*_GetSP)();

	return m_characterInfo.sp;
}


hook_method<int (CNpcHomun::*)(void)> CNpcHomun::_GetMaxHP(SERVER, "CNpcHomun::GetMaxHP");
int CNpcHomun::GetMaxHP(void)
{
	return (this->*_GetMaxHP)();

	//TODO
}


hook_method<int (CNpcHomun::*)(void)> CNpcHomun::_GetMaxSP(SERVER, "CNpcHomun::GetMaxSP");
int CNpcHomun::GetMaxSP(void)
{
	return (this->*_GetMaxSP)();

	//TODO
}


hook_method<short (CNpcHomun::*)(void)> CNpcHomun::_GetStrValue(SERVER, "CNpcHomun::GetStrValue");
short CNpcHomun::GetStrValue(void)
{
	return (this->*_GetStrValue)();

	//TODO
}


hook_method<short (CNpcHomun::*)(void)> CNpcHomun::_GetDexValue(SERVER, "CNpcHomun::GetDexValue");
short CNpcHomun::GetDexValue(void)
{
	return (this->*_GetDexValue)();

	//TODO
}


hook_method<short (CNpcHomun::*)(void)> CNpcHomun::_GetVitValue(SERVER, "CNpcHomun::GetVitValue");
short CNpcHomun::GetVitValue(void)
{
	return (this->*_GetVitValue)();

	//TODO
}


hook_method<short (CNpcHomun::*)(void)> CNpcHomun::_GetIntValue(SERVER, "CNpcHomun::GetIntValue");
short CNpcHomun::GetIntValue(void)
{
	return (this->*_GetIntValue)();

	//TODO
}


hook_method<short (CNpcHomun::*)(void)> CNpcHomun::_GetAgiValue(SERVER, "CNpcHomun::GetAgiValue");
short CNpcHomun::GetAgiValue(void)
{
	return (this->*_GetAgiValue)();

	//TODO
}


/* hook_method<int (CNpcHomun::*)(void)> CNpcHomun::_GetLukValue(SERVER, "CNpcHomun::GetLukValue");
int CNpcHomun::GetLukValue(void)
{
	return (this->*_GetLukValue)();

	//TODO
} */


//hook_method<int (CNpcHomun::*)(void)> CNpcHomun::_GetFullness(SERVER, "CNpcHomun::GetFullness");
int CNpcHomun::GetFullness(void)
{
//	return (this->*_GetFullness)();

	return m_fullness;
}


//hook_method<int (CNpcHomun::*)(void)> CNpcHomun::_GetRelation(SERVER, "CNpcHomun::GetRelation");
int CNpcHomun::GetRelation(void)
{
//	return (this->*_GetRelation)();

	return (signed int)m_relation;
}


hook_method<void (CNpcHomun::*)(CCharacter* other, int& damage, int isMeleeATK, int isSKATK)> CNpcHomun::_ProcessEffect_ATK(SERVER, "CNpcHomun::ProcessEffect_ATK");
void CNpcHomun::ProcessEffect_ATK(CCharacter* other, int& damage, int isMeleeATK, int isSKATK)
{
	return (this->*_ProcessEffect_ATK)(other, damage, isMeleeATK, isSKATK);

	//TODO
}


hook_method<int (CNpcHomun::*)(int skillID)> CNpcHomun::_GetInvincibleTimeInfo(SERVER, "CNpcHomun::GetInvincibleTimeInfo");
int CNpcHomun::GetInvincibleTimeInfo(int skillID)
{
	return (this->*_GetInvincibleTimeInfo)(skillID);

	//TODO
}


hook_method<short (CNpcHomun::*)(void)> CNpcHomun::_GetJobType(SERVER, "CNpcHomun::GetJobType");
short CNpcHomun::GetJobType(void)
{
	return (this->*_GetJobType)();

	//TODO
}


hook_method<void (CNpcHomun::*)(unsigned short type, int amount)> CNpcHomun::_NotifyStatusAmount(SERVER, "CNpcHomun::NotifyStatusAmount");
void CNpcHomun::NotifyStatusAmount(unsigned short type, int amount)
{
	return (this->*_NotifyStatusAmount)(type, amount);

	//TODO
}


hook_method<bool (CNpcHomun::*)(unsigned short type, int& amount)> CNpcHomun::_ApplyStatusAmount(SERVER, "CNpcHomun::ApplyStatusAmount");
bool CNpcHomun::ApplyStatusAmount(unsigned short type, int& amount)
{
	return (this->*_ApplyStatusAmount)(type, amount);

	//TODO
}


hook_method<void (CNpcHomun::*)(void)> CNpcHomun::_InitCore(SERVER, "CNpcHomun::InitCore");
void CNpcHomun::InitCore(void)
{
	return (this->*_InitCore)();

	this->CNPC::InitCore();
	m_relation = 0.0;
	m_homunID = 0;
	m_modified = 0;
	m_fullness = 0;
	m_fullGrade = 0;
	m_SKPoint = 0;
	m_skill.clear();
	m_EXTInfo.DEF = 0;
	this->CNpcHomun::InitTimer(timeGetTime());
}


hook_method<int (CNpcHomun::*)(void)> CNpcHomun::_IsRechargeTime(SERVER, "CNpcHomun::IsRechargeTime");
int CNpcHomun::IsRechargeTime(void)
{
	return (this->*_IsRechargeTime)();

	//TODO
}


hook_method<int (CNpcHomun::*)(CCharacter* other, unsigned short SKID, int property)> CNpcHomun::_GetAttackPoint(SERVER, "CNpcHomun::GetAttackPoint");
int CNpcHomun::GetAttackPoint(CCharacter* other, unsigned short SKID, int property)
{
	return (this->*_GetAttackPoint)(other, SKID, property);

	//TODO
}


hook_method<int (CNpcHomun::*)(void)> CNpcHomun::_GetMagicAttPower(SERVER, "CNpcHomun::GetMagicAttPower");
int CNpcHomun::GetMagicAttPower(void)
{
	return (this->*_GetMagicAttPower)();

	//TODO
}


hook_method<short (CNpcHomun::*)(void)> CNpcHomun::_GetStatusDef(SERVER, "CNpcHomun::GetStatusDef");
short CNpcHomun::GetStatusDef(void)
{
	return (this->*_GetStatusDef)();

	//TODO
}


hook_method<short (CNpcHomun::*)(void)> CNpcHomun::_GetStatusMagicDef(SERVER, "CNpcHomun::GetStatusMagicDef");
short CNpcHomun::GetStatusMagicDef(void)
{
	return (this->*_GetStatusMagicDef)();

	//TODO
}


hook_method<short (CNpcHomun::*)(void)> CNpcHomun::_GetAvoidPercent_Client(SERVER, "CNpcHomun::GetAvoidPercent_Client");
short CNpcHomun::GetAvoidPercent_Client(void)
{
	return (this->*_GetAvoidPercent_Client)();

	//TODO
}


hook_method<void (CNpcHomun::*)(unsigned long dwTick)> CNpcHomun::_CheckState(SERVER, "CNpcHomun::CheckState");
void CNpcHomun::CheckState(unsigned long dwTick)
{
	return (this->*_CheckState)(dwTick);

	//TODO
}


hook_method<void (CNpcHomun::*)(int GID)> CNpcHomun::_SaveCharInfo(SERVER, "CNpcHomun::SaveCharInfo");
void CNpcHomun::SaveCharInfo(int GID)
{
	return (this->*_SaveCharInfo)(GID);

	//TODO
}


hook_method<void (CNpcHomun::*)(int GID)> CNpcHomun::_DeleteCharInfo(SERVER, "CNpcHomun::DeleteCharInfo");
void CNpcHomun::DeleteCharInfo(int GID)
{
	return (this->*_DeleteCharInfo)(GID);

	//TODO
}


hook_method<int (CNpcHomun::*)(unsigned char* buf, int len)> CNpcHomun::_ParseSkill(SERVER, "CNpcHomun::ParseSkill");
int CNpcHomun::ParseSkill(unsigned char* buf, int len)
{
	return (this->*_ParseSkill)(buf, len);

	//TODO
}


hook_method<int (CNpcHomun::*)(void)> CNpcHomun::_SaveSkill(SERVER, "CNpcHomun::SaveSkill");
int CNpcHomun::SaveSkill(void)
{
	return (this->*_SaveSkill)();

	//TODO
}


hook_method<int (CNpcHomun::*)(void)> CNpcHomun::_LoadSkill(SERVER, "CNpcHomun::LoadSkill");
int CNpcHomun::LoadSkill(void)
{
	return (this->*_LoadSkill)();

	//TODO
}


hook_method<int (CNpcHomun::*)(unsigned short SKID, HO_SKINFO* SKInfo, int SKData)> CNpcHomun::_AddSkill(SERVER, "CNpcHomun::AddSkill");
int CNpcHomun::AddSkill(unsigned short SKID, HO_SKINFO* SKInfo, int SKData)
{
	return (this->*_AddSkill)(SKID, SKInfo, SKData);

	//TODO
}


hook_method<HO_SKINFO* (CNpcHomun::*)(unsigned short SKID)> CNpcHomun::_GetSkill(SERVER, "CNpcHomun::GetSkill");
HO_SKINFO* CNpcHomun::GetSkill(unsigned short SKID)
{
	return (this->*_GetSkill)(SKID);

	//TODO
}


hook_method<void (CNpcHomun::*)(void)> CNpcHomun::_NotifyAllSKInfo(SERVER, "CNpcHomun::NotifyAllSKInfo");
void CNpcHomun::NotifyAllSKInfo(void)
{
	return (this->*_NotifyAllSKInfo)();

	//TODO
}


hook_method<int (CNpcHomun::*)(unsigned short SKID, short job)> CNpcHomun::_IsSatisfySkill(SERVER, "CNpcHomun::IsSatisfySkill");
int CNpcHomun::IsSatisfySkill(unsigned short SKID, short job)
{
	return (this->*_IsSatisfySkill)(SKID, job);

	//TODO
}


hook_method<void (CNpcHomun::*)(unsigned short SKID, int isForce)> CNpcHomun::_NotifySKInfo(SERVER, "CNpcHomun::NotifySKInfo");
void CNpcHomun::NotifySKInfo(unsigned short SKID, int isForce)
{
	return (this->*_NotifySKInfo)(SKID, isForce);

	//TODO
}


hook_method<void (CNpcHomun::*)(void)> CNpcHomun::_ChkAllEnableSkill(SERVER, "CNpcHomun::ChkAllEnableSkill");
void CNpcHomun::ChkAllEnableSkill(void)
{
	return (this->*_ChkAllEnableSkill)();

	//TODO
}


hook_method<void (CNpcHomun::*)(unsigned short SKID, short level)> CNpcHomun::_ApplyPassiveSkill(SERVER, "CNpcHomun::ApplyPassiveSkill");
void CNpcHomun::ApplyPassiveSkill(unsigned short SKID, short level)
{
	return (this->*_ApplyPassiveSkill)(SKID, level);

	//TODO
}


hook_method<void (CNpcHomun::*)(void)> CNpcHomun::_AddFinalSkill(SERVER, "CNpcHomun::AddFinalSkill");
void CNpcHomun::AddFinalSkill(void)
{
	return (this->*_AddFinalSkill)();

	//TODO
}


hook_method<void (CNpcHomun::*)(void)> CNpcHomun::_OnChangedHP(SERVER, "CNpcHomun::OnChangedHP");
void CNpcHomun::OnChangedHP(void)
{
	return (this->*_OnChangedHP)();

	//TODO
}


hook_method<void (CNpcHomun::*)(void)> CNpcHomun::_OnChangedSP(SERVER, "CNpcHomun::OnChangedSP");
void CNpcHomun::OnChangedSP(void)
{
	return (this->*_OnChangedSP)();

	//TODO
}


hook_method<void (CNpcHomun::*)(CPC* owner)> CNpcHomun::_OnFeed(SERVER, "CNpcHomun::OnFeed");
void CNpcHomun::OnFeed(CPC* owner)
{
	return (this->*_OnFeed)(owner);

	//TODO
}


hook_method<void (CNpcHomun::*)(CCharacter* sender, int exp, int par1)> CNpcHomun::_OnAddExp(SERVER, "CNpcHomun::OnAddExp");
void CNpcHomun::OnAddExp(CCharacter* sender, int exp, int par1)
{
	return (this->*_OnAddExp)(sender, exp, par1);

	//TODO
}


hook_method<void (CNpcHomun::*)(CCharacter* sender, int exp, int par1)> CNpcHomun::_OnShareExp(SERVER, "CNpcHomun::OnShareExp");
void CNpcHomun::OnShareExp(CCharacter* sender, int exp, int par1)
{
	return (this->*_OnShareExp)(sender, exp, par1);

	//TODO
}


hook_method<void (CNpcHomun::*)(int val)> CNpcHomun::_ModifyFullness(SERVER, "CNpcHomun::ModifyFullness");
void CNpcHomun::ModifyFullness(int val)
{
	return (this->*_ModifyFullness)(val);

	//TODO
}


hook_method<void (CNpcHomun::*)(float val)> CNpcHomun::_ModifyRelationship(SERVER, "CNpcHomun::ModifyRelationship");
void CNpcHomun::ModifyRelationship(float val)
{
	return (this->*_ModifyRelationship)(val);

	//TODO
}


hook_method<void (CNpcHomun::*)(char state, int data)> CNpcHomun::_SendStateHomun(SERVER, "CNpcHomun::SendStateHomun");
void CNpcHomun::SendStateHomun(char state, int data)
{
	return (this->*_SendStateHomun)(state, data);

	//TODO
}


hook_method<void (CNpcHomun::*)(void)> CNpcHomun::_SendProperty(SERVER, "CNpcHomun::SendProperty");
void CNpcHomun::SendProperty(void)
{
	return (this->*_SendProperty)();

	//TODO
}


hook_method<void (CNpcHomun::*)(unsigned long time, int skillID)> CNpcHomun::_SetInvincibleTimeInfo(SERVER, "CNpcHomun::SetInvincibleTimeInfo");
void CNpcHomun::SetInvincibleTimeInfo(unsigned long time, int skillID)
{
	return (this->*_SetInvincibleTimeInfo)(time, skillID);

	//TODO
}


hook_method<void (CNpcHomun::*)(unsigned long firstTime, unsigned long secondTime, int state)> CNpcHomun::_SetBodyStateTimeInfo(SERVER, "CNpcHomun::SetBodyStateTimeInfo");
void CNpcHomun::SetBodyStateTimeInfo(unsigned long firstTime, unsigned long secondTime, int state)
{
	return (this->*_SetBodyStateTimeInfo)(firstTime, secondTime, state);

	//TODO
}


hook_method<void (CNpcHomun::*)(int firstTime, int secondTime, int state)> CNpcHomun::_SetHealthStateTimeInfo(SERVER, "CNpcHomun::SetHealthStateTimeInfo");
void CNpcHomun::SetHealthStateTimeInfo(int firstTime, int secondTime, int state)
{
	return (this->*_SetHealthStateTimeInfo)(firstTime, secondTime, state);

	//TODO
}


hook_method<short (CNpcHomun::*)(void)> CNpcHomun::_GetATKPoint_Client(SERVER, "CNpcHomun::GetATKPoint_Client");
short CNpcHomun::GetATKPoint_Client(void)
{
	return (this->*_GetATKPoint_Client)();

	//TODO
}


hook_method<short (CNpcHomun::*)(void)> CNpcHomun::_GetCRI_Client(SERVER, "CNpcHomun::GetCRI_Client");
short CNpcHomun::GetCRI_Client(void)
{
	return (this->*_GetCRI_Client)();

	//TODO
}


hook_method<short (CNpcHomun::*)(void)> CNpcHomun::_GetDEF_Client(SERVER, "CNpcHomun::GetDEF_Client");
short CNpcHomun::GetDEF_Client(void)
{
	return (this->*_GetDEF_Client)();

	//TODO
}


hook_method<short (CNpcHomun::*)(void)> CNpcHomun::_GetATKTime_Client(SERVER, "CNpcHomun::GetATKTime_Client");
short CNpcHomun::GetATKTime_Client(void)
{
	return (this->*_GetATKTime_Client)();

	//TODO
}


//hook_method<short (CNpcHomun::*)(short val)> CNpcHomun::_GetRelationGrade(SERVER, "CNpcHomun::GetRelationGrade");
short CNpcHomun::GetRelationGrade(short val)
{
//	return (this->*_GetRelationGrade)(val);

	if( val > 900 )
		return 4;
	else if( val > 750 )
		return 3;
	else if( val > 250 )
		return 2;
	else if( val > 100 )
		return 1;
	else
		return 0;
}



hook_method<int (CNpcHomun::*)(int fullness)> CNpcHomun::_GetFullnessGrade(SERVER, "CNpcHomun::GetFullnessGrade");
int CNpcHomun::GetFullnessGrade(int fullness)
{
	return (this->*_GetFullnessGrade)(fullness);

	if( fullness > 75 )
		return (fullness > 90) + 3;
	else if( fullness > 25 )
		return 2;
	else if( fullness > 10 )
		return 1;
	else
		return 0;
}


hook_method<int (CNpcHomun::*)(void)> CNpcHomun::_GetRecoverSPD_HP(SERVER, "CNpcHomun::GetRecoverSPD_HP");
int CNpcHomun::GetRecoverSPD_HP(void)
{
	return (this->*_GetRecoverSPD_HP)();

	//TODO
}


hook_method<int (CNpcHomun::*)(void)> CNpcHomun::_GetRecoverSPD_SP(SERVER, "CNpcHomun::GetRecoverSPD_SP");
int CNpcHomun::GetRecoverSPD_SP(void)
{
	return (this->*_GetRecoverSPD_SP)();

	//TODO
}


hook_method<void (CNpcHomun::*)(void)> CNpcHomun::_UpdateStatusATKpower(SERVER, "CNpcHomun::UpdateStatusATKpower");
void CNpcHomun::UpdateStatusATKpower(void)
{
	return (this->*_UpdateStatusATKpower)();

	//TODO
}


hook_method<void (CNpcHomun::*)(void)> CNpcHomun::_UpgradeStatus_LevelUp(SERVER, "CNpcHomun::UpgradeStatus_LevelUp");
void CNpcHomun::UpgradeStatus_LevelUp(void)
{
	return (this->*_UpgradeStatus_LevelUp)();

	//TODO
}


hook_method<void (CNpcHomun::*)(int SKID, int AID, int SKData)> CNpcHomun::_OPSkillToSelf(SERVER, "CNpcHomun::OPSkillToSelf");
void CNpcHomun::OPSkillToSelf(int SKID, int AID, int SKData)
{
	return (this->*_OPSkillToSelf)(SKID, AID, SKData);

	//TODO
}


hook_method<void (CNpcHomun::*)(int SKID, int AID, int SKData)> CNpcHomun::_ATKSkillToChar(SERVER, "CNpcHomun::ATKSkillToChar");
void CNpcHomun::ATKSkillToChar(int SKID, int AID, int SKData)
{
	return (this->*_ATKSkillToChar)(SKID, AID, SKData);

	//TODO
}


hook_method<int (CNpcHomun::*)(CPC* owner, const MSG_TYPE4_FIVEDWORD& in_msg)> CNpcHomun::_SK_LIF_Heal(SERVER, "CNpcHomun::SK_LIF_Heal");
int CNpcHomun::SK_LIF_Heal(CPC* owner, const MSG_TYPE4_FIVEDWORD& in_msg)
{
	return (this->*_SK_LIF_Heal)(owner, in_msg);

	//TODO
}


hook_method<int (CNpcHomun::*)(CPC* owner, MSG_TYPE4_FIVEDWORD* msg)> CNpcHomun::_SK_LIF_Avoid(SERVER, "CNpcHomun::SK_LIF_Avoid");
int CNpcHomun::SK_LIF_Avoid(CPC* owner, MSG_TYPE4_FIVEDWORD* msg)
{
	return (this->*_SK_LIF_Avoid)(owner, msg);

	//TODO
}


hook_method<int (CNpcHomun::*)(CPC* owner, MSG_TYPE4_FIVEDWORD* msg)> CNpcHomun::_SK_LIF_Change(SERVER, "CNpcHomun::SK_LIF_Change");
int CNpcHomun::SK_LIF_Change(CPC* owner, MSG_TYPE4_FIVEDWORD* msg)
{
	return (this->*_SK_LIF_Change)(owner, msg);

	//TODO
}


hook_method<int (CNpcHomun::*)(CPC* owner)> CNpcHomun::_SK_AMI_Castle(SERVER, "CNpcHomun::SK_AMI_Castle");
int CNpcHomun::SK_AMI_Castle(CPC* owner)
{
	return (this->*_SK_AMI_Castle)(owner);

	//TODO
}


hook_method<int (CNpcHomun::*)(CPC* owner, MSG_TYPE4_FIVEDWORD* msg)> CNpcHomun::_SK_AMI_Defence(SERVER, "CNpcHomun::SK_AMI_Defence");
int CNpcHomun::SK_AMI_Defence(CPC* owner, MSG_TYPE4_FIVEDWORD* msg)
{
	return (this->*_SK_AMI_Defence)(owner, msg);

	//TODO
}


hook_method<int (CNpcHomun::*)(CPC* owner, MSG_TYPE4_FIVEDWORD* msg)> CNpcHomun::_SK_AMI_BloodLust(SERVER, "CNpcHomun::SK_AMI_BloodLust");
int CNpcHomun::SK_AMI_BloodLust(CPC* owner, MSG_TYPE4_FIVEDWORD* msg)
{
	return (this->*_SK_AMI_BloodLust)(owner, msg);

	//TODO
}


hook_method<int (CNpcHomun::*)(CPC* owner, MSG_TYPE4_FIVEDWORD* msg)> CNpcHomun::_SK_FLI_Fleet(SERVER, "CNpcHomun::SK_FLI_Fleet");
int CNpcHomun::SK_FLI_Fleet(CPC* owner, MSG_TYPE4_FIVEDWORD* msg)
{
	return (this->*_SK_FLI_Fleet)(owner, msg);

	//TODO
}


hook_method<int (CNpcHomun::*)(MSG_TYPE4_FIVEDWORD* msg)> CNpcHomun::_SK_FLI_Speed(SERVER, "CNpcHomun::SK_FLI_Speed");
int CNpcHomun::SK_FLI_Speed(MSG_TYPE4_FIVEDWORD* msg)
{
	return (this->*_SK_FLI_Speed)(msg);

	//TODO
}


hook_method<int (CNpcHomun::*)(CPC* owner, MSG_TYPE4_FIVEDWORD* msg)> CNpcHomun::_SK_VAN_Chaotic(SERVER, "CNpcHomun::SK_VAN_Chaotic");
int CNpcHomun::SK_VAN_Chaotic(CPC* owner, MSG_TYPE4_FIVEDWORD* msg)
{
	return (this->*_SK_VAN_Chaotic)(owner, msg);

	//TODO
}


hook_method<int (CNpcHomun::*)(CPC* owner, MSG_TYPE4_FIVEDWORD* msg)> CNpcHomun::_SK_VAN_Explosion(SERVER, "CNpcHomun::SK_VAN_Explosion");
int CNpcHomun::SK_VAN_Explosion(CPC* owner, MSG_TYPE4_FIVEDWORD* msg)
{
	return (this->*_SK_VAN_Explosion)(owner, msg);

	//TODO
}
