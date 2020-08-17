#include "CNpcMercenary.hpp"


hook_method<void (CNpcMercenary::*)(void)> CNpcMercenary::_PacketSend_ZC_MER_INIT(SERVER, "CNpcMercenary::PacketSend_ZC_MER_INIT");
void CNpcMercenary::PacketSend_ZC_MER_INIT(void)
{
	return (this->*_PacketSend_ZC_MER_INIT)();

	//TODO
}


hook_method<void (CNpcMercenary::*)(void)> CNpcMercenary::_PacketSend_ZC_MER_SKILLINFO_LIST(SERVER, "CNpcMercenary::PacketSend_ZC_MER_SKILLINFO_LIST");
void CNpcMercenary::PacketSend_ZC_MER_SKILLINFO_LIST(void)
{
	return (this->*_PacketSend_ZC_MER_SKILLINFO_LIST)();

	//TODO
}


hook_method<void (CNpcMercenary::*)(unsigned long in_TagetAID, short in_Range)> CNpcMercenary::_PacketSend_ZC_DEVOTIONLIST(SERVER, "CNpcMercenary::PacketSend_ZC_DEVOTIONLIST");
void CNpcMercenary::PacketSend_ZC_DEVOTIONLIST(unsigned long in_TagetAID, short in_Range)
{
	return (this->*_PacketSend_ZC_DEVOTIONLIST)(in_TagetAID, in_Range);

	//TODO
}


hook_method<void (CNpcMercenary::*)(const int in_Length, char* in_pBuffer)> CNpcMercenary::_Send(SERVER, "CNpcMercenary::Send");
void CNpcMercenary::Send(const int in_Length, char* in_pBuffer)
{
	return (this->*_Send)(in_Length, in_pBuffer);

	//TODO
}


hook_method<void (CNpcMercenary::*)(void)> CNpcMercenary::_InitCore(SERVER, "CNpcMercenary::InitCore");
void CNpcMercenary::InitCore(void)
{
	return (this->*_InitCore)();

	//TODO
}


hook_method<void (CNpcMercenary::*)(void)> CNpcMercenary::_OnTimer(SERVER, "CNpcMercenary::OnTimer");
void CNpcMercenary::OnTimer(void)
{
	return (this->*_OnTimer)();

	//TODO
}


/* hook_method<bool (CNpcMercenary::*)(const int in_EffectIdx)> CNpcMercenary::_isEffectApply(SERVER, "CNpcMercenary::isEffectApply");
bool CNpcMercenary::isEffectApply(const int in_EffectIdx)
{
	return (this->*_isEffectApply)(in_EffectIdx);

	//TODO
} */


hook_method<CNpcMercenary::MERSkill* (CNpcMercenary::*)(const int in_SKID)> CNpcMercenary::_GetSkill(SERVER, "CNpcMercenary::GetSkill");
CNpcMercenary::MERSkill* CNpcMercenary::GetSkill(const int in_SKID)
{
	return (this->*_GetSkill)(in_SKID);

	//TODO
}


/* hook_method<bool (CNpcMercenary::*)(const int in_Job, const int in_SKID)> CNpcMercenary::_IsSatisfySkill(SERVER, "CNpcMercenary::IsSatisfySkill");
bool CNpcMercenary::IsSatisfySkill(const int in_Job, const int in_SKID)
{
	return (this->*_IsSatisfySkill)(in_Job, in_SKID);

	//TODO
} */


/* hook_method<void (CNpcMercenary::*)(void)> CNpcMercenary::_ChkAllEnableSkill(SERVER, "CNpcMercenary::ChkAllEnableSkill");
void CNpcMercenary::ChkAllEnableSkill(void)
{
	return (this->*_ChkAllEnableSkill)();

	//TODO
} */


hook_method<bool (CNpcMercenary::*)(const unsigned short in_SKID)> CNpcMercenary::_IsSkillUsable(SERVER, "CNpcMercenary::IsSkillUsable");
bool CNpcMercenary::IsSkillUsable(const unsigned short in_SKID)
{
	return (this->*_IsSkillUsable)(in_SKID);

	//TODO
}


hook_method<bool (CNpcMercenary::*)(const int in_SKID, const int in_Level, CCharacter* const in_pTargetCh)> CNpcMercenary::_IsSkillEnable(SERVER, "CNpcMercenary::IsSkillEnable");
bool CNpcMercenary::IsSkillEnable(const int in_SKID, const int in_Level, CCharacter* const in_pTargetCh)
{
	return (this->*_IsSkillEnable)(in_SKID, in_Level, in_pTargetCh);

	//TODO
}


hook_method<void (CNpcMercenary::*)(void)> CNpcMercenary::_StartUseSkill(SERVER, "CNpcMercenary::StartUseSkill");
void CNpcMercenary::StartUseSkill(void)
{
	return (this->*_StartUseSkill)();

	//TODO
}


hook_method<void (CNpcMercenary::*)(int sp)> CNpcMercenary::_ReduceSPByUseSkill(SERVER, "CNpcMercenary::ReduceSPByUseSkill");
void CNpcMercenary::ReduceSPByUseSkill(int sp)
{
	return (this->*_ReduceSPByUseSkill)(sp);

	//TODO
}


hook_method<bool (CNpcMercenary::*)(const int in_Length, const unsigned char* in_pData)> CNpcMercenary::_ParseEffectData(SERVER, "CNpcMercenary::ParseEffectData");
bool CNpcMercenary::ParseEffectData(const int in_Length, const unsigned char* in_pData)
{
	return (this->*_ParseEffectData)(in_Length, in_pData);

	//TODO
}


hook_method<int (CNpcMercenary::*)(const unsigned char* io_pData, const int in_MaxLength)> CNpcMercenary::_GetEffectDBFmt(SERVER, "CNpcMercenary::GetEffectDBFmt");
int CNpcMercenary::GetEffectDBFmt(const unsigned char* io_pData, const int in_MaxLength)
{
	return (this->*_GetEffectDBFmt)(io_pData, in_MaxLength);

	//TODO
}


hook_method<int (CNpcMercenary::*)(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4)> CNpcMercenary::_OnMsg(SERVER, "CNpcMercenary::OnMsg");
int CNpcMercenary::OnMsg(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4)
{
	return (this->*_OnMsg)(sender, receiver, msgID, par1, par2, par3, par4);

	//TODO
}


hook_method<void (CNpcMercenary::*)(SKILLINFO* in_pSkill)> CNpcMercenary::_OnADDSKILL(SERVER, "CNpcMercenary::OnADDSKILL");
void CNpcMercenary::OnADDSKILL(SKILLINFO* in_pSkill)
{
	return (this->*_OnADDSKILL)(in_pSkill);

	//TODO
}


hook_method<void (CNpcMercenary::*)(const int in_SKID, const int in_TargetAID, const MSG_TYPE4_FIVEDWORD* in_pData)> CNpcMercenary::_OnATKSKILL_TOCHAR_MER(SERVER, "CNpcMercenary::OnATKSKILL_TOCHAR_MER");
void CNpcMercenary::OnATKSKILL_TOCHAR_MER(const int in_SKID, const int in_TargetAID, const MSG_TYPE4_FIVEDWORD* in_pData)
{
	return (this->*_OnATKSKILL_TOCHAR_MER)(in_SKID, in_TargetAID, in_pData);

	//TODO
}


hook_method<void (CNpcMercenary::*)(const int in_SKID, const int in_TargetAID, const MSG_TYPE5_SIXDWORD* in_pData)> CNpcMercenary::_OnGroundSkill_MER(SERVER, "CNpcMercenary::OnGroundSkill_MER");
void CNpcMercenary::OnGroundSkill_MER(const int in_SKID, const int in_TargetAID, const MSG_TYPE5_SIXDWORD* in_pData)
{
	return (this->*_OnGroundSkill_MER)(in_SKID, in_TargetAID, in_pData);

	//TODO
}


hook_method<void (CNpcMercenary::*)(const int in_SKID, const int in_TargetAID, const MSG_TYPE4_FIVEDWORD* in_pData)> CNpcMercenary::_UseSkillToCharacter_MER(SERVER, "CNpcMercenary::UseSkillToCharacter_MER");
void CNpcMercenary::UseSkillToCharacter_MER(const int in_SKID, const int in_TargetAID, const MSG_TYPE4_FIVEDWORD* in_pData)
{
	return (this->*_UseSkillToCharacter_MER)(in_SKID, in_TargetAID, in_pData);

	//TODO
}


hook_method<void (CNpcMercenary::*)(const int in_SKID, const int in_TargetAID, const MSG_TYPE4_FIVEDWORD* in_pData)> CNpcMercenary::_SPAttackSkillToCharacter_MER(SERVER, "CNpcMercenary::SPAttackSkillToCharacter_MER");
void CNpcMercenary::SPAttackSkillToCharacter_MER(const int in_SKID, const int in_TargetAID, const MSG_TYPE4_FIVEDWORD* in_pData)
{
	return (this->*_SPAttackSkillToCharacter_MER)(in_SKID, in_TargetAID, in_pData);

	//TODO
}


hook_method<void (CNpcMercenary::*)(const int in_SKID, const int in_TargetAID, const MSG_TYPE4_FIVEDWORD* in_pData)> CNpcMercenary::_OperationSkillToSelf_MER(SERVER, "CNpcMercenary::OperationSkillToSelf_MER");
void CNpcMercenary::OperationSkillToSelf_MER(const int in_SKID, const int in_TargetAID, const MSG_TYPE4_FIVEDWORD* in_pData)
{
	return (this->*_OperationSkillToSelf_MER)(in_SKID, in_TargetAID, in_pData);

	//TODO
}


hook_method<void (CNpcMercenary::*)(CCharacter* in_pSender, const int in_Exp)> CNpcMercenary::_OnADD_EXP(SERVER, "CNpcMercenary::OnADD_EXP");
void CNpcMercenary::OnADD_EXP(CCharacter* in_pSender, const int in_Exp)
{
	return (this->*_OnADD_EXP)(in_pSender, in_Exp);

	//TODO
}


hook_method<void (CNpcMercenary::*)(CCharacter* in_pSender, const int in_Exp)> CNpcMercenary::_OnSHARE_EXP(SERVER, "CNpcMercenary::OnSHARE_EXP");
void CNpcMercenary::OnSHARE_EXP(CCharacter* in_pSender, const int in_Exp)
{
	return (this->*_OnSHARE_EXP)(in_pSender, in_Exp);

	//TODO
}


hook_method<void (CNpcMercenary::*)(CCharacter* in_pSender, const int in_JobExp, const int in_xPos, const int in_yPos)> CNpcMercenary::_OnADD_JOBEXP(SERVER, "CNpcMercenary::OnADD_JOBEXP");
void CNpcMercenary::OnADD_JOBEXP(CCharacter* in_pSender, const int in_JobExp, const int in_xPos, const int in_yPos)
{
	return (this->*_OnADD_JOBEXP)(in_pSender, in_JobExp, in_xPos, in_yPos);

	//TODO
}


hook_method<void (CNpcMercenary::*)(CCharacter* pSendeer, const int in_JobExp)> CNpcMercenary::_OnSHARE_JOBEXP(SERVER, "CNpcMercenary::OnSHARE_JOBEXP");
void CNpcMercenary::OnSHARE_JOBEXP(CCharacter* pSendeer, const int in_JobExp)
{
	return (this->*_OnSHARE_JOBEXP)(pSendeer, in_JobExp);

	//TODO
}


hook_method<void (CNpcMercenary::*)(CCharacter* const in_pSender, CCharacter* const in_pTarget)> CNpcMercenary::_OnKILLED(SERVER, "CNpcMercenary::OnKILLED");
void CNpcMercenary::OnKILLED(CCharacter* const in_pSender, CCharacter* const in_pTarget)
{
	return (this->*_OnKILLED)(in_pSender, in_pTarget);

	//TODO
}


hook_method<void (CNpcMercenary::*)(const int in_modifyHP)> CNpcMercenary::_OnHEAL_HP(SERVER, "CNpcMercenary::OnHEAL_HP");
void CNpcMercenary::OnHEAL_HP(const int in_modifyHP)
{
	return (this->*_OnHEAL_HP)(in_modifyHP);

	//TODO
}


hook_method<void (CNpcMercenary::*)(const int in_modifySP)> CNpcMercenary::_OnHEAL_SP(SERVER, "CNpcMercenary::OnHEAL_SP");
void CNpcMercenary::OnHEAL_SP(const int in_modifySP)
{
	return (this->*_OnHEAL_SP)(in_modifySP);

	//TODO
}


hook_method<void (CNpcMercenary::*)(const unsigned long in_preDelayTime, const unsigned long in_maintainTime, const int in_state)> CNpcMercenary::_OnTIME_BODYSTATE(SERVER, "CNpcMercenary::OnTIME_BODYSTATE");
void CNpcMercenary::OnTIME_BODYSTATE(const unsigned long in_preDelayTime, const unsigned long in_maintainTime, const int in_state)
{
	return (this->*_OnTIME_BODYSTATE)(in_preDelayTime, in_maintainTime, in_state);

	//TODO
}


hook_method<void (CNpcMercenary::*)(const int firstTime, const int secondTime, const int state)> CNpcMercenary::_OnTIME_HEALTHSTATE(SERVER, "CNpcMercenary::OnTIME_HEALTHSTATE");
void CNpcMercenary::OnTIME_HEALTHSTATE(const int firstTime, const int secondTime, const int state)
{
	return (this->*_OnTIME_HEALTHSTATE)(firstTime, secondTime, state);

	//TODO
}


hook_method<void (CNpcMercenary::*)(const int in_RemoveAID)> CNpcMercenary::_OnDEVOTIONLIST_REMOVE(SERVER, "CNpcMercenary::OnDEVOTIONLIST_REMOVE");
void CNpcMercenary::OnDEVOTIONLIST_REMOVE(const int in_RemoveAID)
{
	return (this->*_OnDEVOTIONLIST_REMOVE)(in_RemoveAID);

	//TODO
}


hook_method<void (CNpcMercenary::*)(CCharacter* sender, int par1, int par2, int par3)> CNpcMercenary::_OnBLESSING_FROM_ACOLYTE(SERVER, "CNpcMercenary::OnBLESSING_FROM_ACOLYTE");
void CNpcMercenary::OnBLESSING_FROM_ACOLYTE(CCharacter* sender, int par1, int par2, int par3)
{
	return (this->*_OnBLESSING_FROM_ACOLYTE)(sender, par1, par2, par3);

	//TODO
}


hook_method<void (CNpcMercenary::*)(const int in_ChangeValue)> CNpcMercenary::_ChangeHP(SERVER, "CNpcMercenary::ChangeHP");
void CNpcMercenary::ChangeHP(const int in_ChangeValue)
{
	return (this->*_ChangeHP)(in_ChangeValue);

	//TODO
}


hook_method<void (CNpcMercenary::*)(const int in_ChangeValue)> CNpcMercenary::_ChangeSP(SERVER, "CNpcMercenary::ChangeSP");
void CNpcMercenary::ChangeSP(const int in_ChangeValue)
{
	return (this->*_ChangeSP)(in_ChangeValue);

	//TODO
}


hook_method<void (CNpcMercenary::*)(const int in_ChangeValue)> CNpcMercenary::_ChangeFAITH(SERVER, "CNpcMercenary::ChangeFAITH");
void CNpcMercenary::ChangeFAITH(const int in_ChangeValue)
{
	return (this->*_ChangeFAITH)(in_ChangeValue);

	//TODO
}


hook_method<void (CNpcMercenary::*)(void)> CNpcMercenary::_BroadcastHP(SERVER, "CNpcMercenary::BroadcastHP");
void CNpcMercenary::BroadcastHP(void)
{
	return (this->*_BroadcastHP)();

	//TODO
}


hook_method<void (CNpcMercenary::*)(void)> CNpcMercenary::_OnEmployTimeExpire(SERVER, "CNpcMercenary::OnEmployTimeExpire");
void CNpcMercenary::OnEmployTimeExpire(void)
{
	return (this->*_OnEmployTimeExpire)();

	//TODO
}


//hook_method<bool (CNpcMercenary::*)(void)> CNpcMercenary::_isDevotion(SERVER, "CNpcMercenary::isDevotion");
bool CNpcMercenary::isDevotion(void)
{
//	return (this->*_isDevotion)();

	return m_bDevotion;
}


hook_method<void (CNpcMercenary::*)(unsigned long firstTime, unsigned long secondTime, int state)> CNpcMercenary::_SetBodyStateTimeInfo(SERVER, "CNpcMercenary::SetBodyStateTimeInfo");
void CNpcMercenary::SetBodyStateTimeInfo(unsigned long firstTime, unsigned long secondTime, int state)
{
	return (this->*_SetBodyStateTimeInfo)(firstTime, secondTime, state);

	//TODO
}


hook_method<void (CNpcMercenary::*)(unsigned long killer)> CNpcMercenary::_OnDead(SERVER, "CNpcMercenary::OnDead");
void CNpcMercenary::OnDead(unsigned long killer)
{
	return (this->*_OnDead)(killer);

	//TODO
}


hook_method<int (CNpcMercenary::*)(unsigned short id, int value)> CNpcMercenary::_UpdateParameterValue(SERVER, "CNpcMercenary::UpdateParameterValue");
int CNpcMercenary::UpdateParameterValue(unsigned short id, int value)
{
	return (this->*_UpdateParameterValue)(id, value);

	//TODO
}


hook_method<bool (CNpcMercenary::*)(CCharacter* in_TargetCH, MSG_TYPE4_FIVEDWORD* in_pData)> CNpcMercenary::_OpSKToChar_SKID_ML_DEVOTION(SERVER, "CNpcMercenary::OpSKToChar_SKID_ML_DEVOTION");
bool CNpcMercenary::OpSKToChar_SKID_ML_DEVOTION(CCharacter* in_TargetCH, MSG_TYPE4_FIVEDWORD* in_pData)
{
	return (this->*_OpSKToChar_SKID_ML_DEVOTION)(in_TargetCH, in_pData);

	//TODO
}


hook_method<void (CNpcMercenary::*)(const int in_SKlevel)> CNpcMercenary::_OpSKToSelf_SKID_ML_DEFENDER(SERVER, "CNpcMercenary::OpSKToSelf_SKID_ML_DEFENDER");
void CNpcMercenary::OpSKToSelf_SKID_ML_DEFENDER(const int in_SKlevel)
{
	return (this->*_OpSKToSelf_SKID_ML_DEFENDER)(in_SKlevel);

	//TODO
}


hook_method<void (CNpcMercenary::*)(unsigned short type, int count)> CNpcMercenary::_NotifyParameter(SERVER, "CNpcMercenary::NotifyParameter");
void CNpcMercenary::NotifyParameter(unsigned short type, int count)
{
	return (this->*_NotifyParameter)(type, count);

	//TODO
}


hook_method<void (CNpcMercenary::*)(void)> CNpcMercenary::_ResetEffective_after_EFST_DEFENDER(SERVER, "CNpcMercenary::ResetEffective_after_EFST_DEFENDER");
void CNpcMercenary::ResetEffective_after_EFST_DEFENDER(void)
{
	return (this->*_ResetEffective_after_EFST_DEFENDER)();

	//TODO
}


hook_method<void (CNpcMercenary::*)(const int in_SKLevel, const int in_EFST, const int in_EFST_time, const int in_EFST_value)> CNpcMercenary::_OpSKToSelf_SKID_MER_MAGNIFICAT(SERVER, "CNpcMercenary::OpSKToSelf_SKID_MER_MAGNIFICAT");
void CNpcMercenary::OpSKToSelf_SKID_MER_MAGNIFICAT(const int in_SKLevel, const int in_EFST, const int in_EFST_time, const int in_EFST_value)
{
	return (this->*_OpSKToSelf_SKID_MER_MAGNIFICAT)(in_SKLevel, in_EFST, in_EFST_time, in_EFST_value);

	//TODO
}


hook_method<int (CNpcMercenary::*)(void)> CNpcMercenary::_GetAvoidableSuccessPercent(SERVER, "CNpcMercenary::GetAvoidableSuccessPercent");
int CNpcMercenary::GetAvoidableSuccessPercent(void)
{
	return (this->*_GetAvoidableSuccessPercent)();

	//TODO
}


hook_method<short (CNpcMercenary::*)(void)> CNpcMercenary::_GetDefencePoint(SERVER, "CNpcMercenary::GetDefencePoint");
short CNpcMercenary::GetDefencePoint(void)
{
	return (this->*_GetDefencePoint)();

	//TODO
}


hook_method<short (CNpcMercenary::*)(void)> CNpcMercenary::_GetStatusDef(SERVER, "CNpcMercenary::GetStatusDef");
short CNpcMercenary::GetStatusDef(void)
{
	return (this->*_GetStatusDef)();

	//TODO
}


hook_method<int (CNpcMercenary::*)(int value)> CNpcMercenary::_GetModifiedValueByEnemySize(SERVER, "CNpcMercenary::GetModifiedValueByEnemySize");
int CNpcMercenary::GetModifiedValueByEnemySize(int value)
{
	return (this->*_GetModifiedValueByEnemySize)(value);

	//TODO
}


hook_method<int (CNpcMercenary::*)(void)> CNpcMercenary::_IsInitingState(SERVER, "CNpcMercenary::IsInitingState");
int CNpcMercenary::IsInitingState(void)
{
	return (this->*_IsInitingState)();

	//TODO
}


hook_method<int (CNpcMercenary::*)(void)> CNpcMercenary::_GetMaxSP(SERVER, "CNpcMercenary::GetMaxSP");
int CNpcMercenary::GetMaxSP(void)
{
	return (this->*_GetMaxSP)();

	//TODO
}


hook_method<short (CNpcMercenary::*)(void)> CNpcMercenary::_GetJob(SERVER, "CNpcMercenary::GetJob");
short CNpcMercenary::GetJob(void)
{
	return (this->*_GetJob)();

	//TODO
}


hook_method<int (CNpcMercenary::*)(void)> CNpcMercenary::_GetSP(SERVER, "CNpcMercenary::GetSP");
int CNpcMercenary::GetSP(void)
{
	return (this->*_GetSP)();

	//TODO
}


hook_method<short (CNpcMercenary::*)(void)> CNpcMercenary::_GetCRI(SERVER, "CNpcMercenary::GetCRI");
short CNpcMercenary::GetCRI(void)
{
	return (this->*_GetCRI)();

	//TODO
}


hook_method<short (CNpcMercenary::*)(void)> CNpcMercenary::_GetDEF(SERVER, "CNpcMercenary::GetDEF");
short CNpcMercenary::GetDEF(void)
{
	return (this->*_GetDEF)();

	//TODO
}


//hook_method<short (CNpcMercenary::*)(void)> CNpcMercenary::_GetVitValue(SERVER, "CNpcMercenary::GetVitValue");
short CNpcMercenary::GetVitValue(void)
{
//	return (this->*_GetVitValue)();

	return m_characterInfo.Vit + m_characterInfo.VitAmount;
}


hook_method<short (CNpcMercenary::*)(void)> CNpcMercenary::_GetDexValue(SERVER, "CNpcMercenary::GetDexValue");
short CNpcMercenary::GetDexValue(void)
{
	return (this->*_GetDexValue)();

	//TODO
}


hook_method<int (CNpcMercenary::*)(void)> CNpcMercenary::_GetMagicAttPower(SERVER, "CNpcMercenary::GetMagicAttPower");
int CNpcMercenary::GetMagicAttPower(void)
{
	return (this->*_GetMagicAttPower)();

	//TODO
}


hook_method<short (CNpcMercenary::*)(void)> CNpcMercenary::_GetIntValue(SERVER, "CNpcMercenary::GetIntValue");
short CNpcMercenary::GetIntValue(void)
{
	return (this->*_GetIntValue)();

	//TODO
}


hook_method<short (CNpcMercenary::*)(void)> CNpcMercenary::_GetMdef(SERVER, "CNpcMercenary::GetMdef");
short CNpcMercenary::GetMdef(void)
{
	return (this->*_GetMdef)();

	//TODO
}


hook_method<static int (__cdecl *)(const int in_Job)> CNpcMercenary::_GetTypicalJob(SERVER, "?GetTypicalJob@CNpcMercenary@@SAHH@Z");
int __cdecl CNpcMercenary::GetTypicalJob(const int in_Job)
{
	return (CNpcMercenary::_GetTypicalJob)(in_Job);

	switch( in_Job )
	{
	case JT_MER_ARCHER01:
	case JT_MER_ARCHER02:
	case JT_MER_ARCHER03:
	case JT_MER_ARCHER04:
	case JT_MER_ARCHER05:
	case JT_MER_ARCHER06:
	case JT_MER_ARCHER07:
	case JT_MER_ARCHER08:
	case JT_MER_ARCHER09:
	case JT_MER_ARCHER10:
		return JT_MER_ARCHER01;
	break;

	case JT_MER_LANCER01:
	case JT_MER_LANCER02:
	case JT_MER_LANCER03:
	case JT_MER_LANCER04:
	case JT_MER_LANCER05:
	case JT_MER_LANCER06:
	case JT_MER_LANCER07:
	case JT_MER_LANCER08:
	case JT_MER_LANCER09:
	case JT_MER_LANCER10:
		return JT_MER_LANCER01;
	break;

	case JT_MER_SWORDMAN01:
	case JT_MER_SWORDMAN02:
	case JT_MER_SWORDMAN03:
	case JT_MER_SWORDMAN04:
	case JT_MER_SWORDMAN05:
	case JT_MER_SWORDMAN06:
	case JT_MER_SWORDMAN07:
	case JT_MER_SWORDMAN08:
	case JT_MER_SWORDMAN09:
	case JT_MER_SWORDMAN10:
		return JT_MER_SWORDMAN01;
	break;

	default:
		return JT_MER_MONSTER;
	break;
	}
}


hook_method<int (CNpcMercenary::*)(void)> CNpcMercenary::_GetTypicalJob2(SERVER, "?GetTypicalJob@CNpcMercenary@@QBEHXZ");
int CNpcMercenary::GetTypicalJob(void)
{
	return (this->*_GetTypicalJob2)();

	//TODO
}


hook_method<int (CNpcMercenary::*)(const int in_SKID)> CNpcMercenary::_GetSKLevel(SERVER, "CNpcMercenary::GetSKLevel");
int CNpcMercenary::GetSKLevel(const int in_SKID)
{
	return (this->*_GetSKLevel)(in_SKID);

	//TODO
}


hook_method<int (CNpcMercenary::*)(const int in_SKID)> CNpcMercenary::_GetSKType(SERVER, "CNpcMercenary::GetSKType");
int CNpcMercenary::GetSKType(const int in_SKID)
{
	return (this->*_GetSKType)(in_SKID);

	//TODO
}


hook_method<CPC* (CNpcMercenary::*)(void)> CNpcMercenary::_GetOwner(SERVER, "CNpcMercenary::GetOwner");
CPC* CNpcMercenary::GetOwner(void)
{
	return (this->*_GetOwner)();

	//TODO
}


//hook_method<int (CNpcMercenary::*)(void)> CNpcMercenary::_GetDesX(SERVER, "CNpcMercenary::GetDesX");
int CNpcMercenary::GetDesX(void)
{
//	return (this->*_GetDesX)();

	return m_pathInfo.m_moveInfo.dxPos;
}


//hook_method<int (CNpcMercenary::*)(void)> CNpcMercenary::_GetDesY(SERVER, "CNpcMercenary::GetDesY");
int CNpcMercenary::GetDesY(void)
{
//	return (this->*_GetDesY)();

	return m_pathInfo.m_moveInfo.dyPos;
}


//hook_method<int (CNpcMercenary::*)(void)> CNpcMercenary::_GetCurX(SERVER, "CNpcMercenary::GetCurX");
int CNpcMercenary::GetCurX(void)
{
//	return (this->*_GetCurX)();

	return m_pathInfo.m_moveInfo.xPos;
}


//hook_method<int (CNpcMercenary::*)(void)> CNpcMercenary::_GetCurY(SERVER, "CNpcMercenary::GetCurY");
int CNpcMercenary::GetCurY(void)
{
//	return (this->*_GetCurY)();

	return m_pathInfo.m_moveInfo.yPos;
}


hook_method<unsigned long (CNpcMercenary::*)(void)> CNpcMercenary::_GetAttackLastTime(SERVER, "CNpcMercenary::GetAttackLastTime");
unsigned long CNpcMercenary::GetAttackLastTime(void)
{
	return (this->*_GetAttackLastTime)();

	//TODO
}


hook_method<void (CNpcMercenary::*)(const unsigned long in_time)> CNpcMercenary::_SetAttackLastTime(SERVER, "CNpcMercenary::SetAttackLastTime");
void CNpcMercenary::SetAttackLastTime(const unsigned long in_time)
{
	return (this->*_SetAttackLastTime)(in_time);

	//TODO
}


hook_method<int (CNpcMercenary::*)(const int in_SKID, const int in_Level, CSkillTypeInfo* in_pSTI)> CNpcMercenary::_GetSPCost(SERVER, "CNpcMercenary::GetSPCost");
int CNpcMercenary::GetSPCost(const int in_SKID, const int in_Level, CSkillTypeInfo* in_pSTI)
{
	return (this->*_GetSPCost)(in_SKID, in_Level, in_pSTI);

	//TODO
}


hook_method<int (CNpcMercenary::*)(CSkillTypeInfo* in_pSKTypeInfo, short in_skLevel, CCharacter* in_pTargetCh, int in_TargetXPos, int in_TargetYPos)> CNpcMercenary::_GetSKCastingTM(SERVER, "CNpcMercenary::GetSKCastingTM");
int CNpcMercenary::GetSKCastingTM(CSkillTypeInfo* in_pSKTypeInfo, short in_skLevel, CCharacter* in_pTargetCh, int in_TargetXPos, int in_TargetYPos)
{
	return (this->*_GetSKCastingTM)(in_pSKTypeInfo, in_skLevel, in_pTargetCh, in_TargetXPos, in_TargetYPos);

	//TODO
}


hook_method<int (CNpcMercenary::*)(void)> CNpcMercenary::_GetRemainLifeSECOND(SERVER, "CNpcMercenary::GetRemainLifeSECOND");
int CNpcMercenary::GetRemainLifeSECOND(void)
{
	return (this->*_GetRemainLifeSECOND)();

	//TODO
}


//hook_method<int (CNpcMercenary::*)(void)> CNpcMercenary::_GetApprovalMonsterKillCounter(SERVER, "CNpcMercenary::GetApprovalMonsterKillCounter");
int CNpcMercenary::GetApprovalMonsterKillCounter(void)
{
//	return (this->*_GetApprovalMonsterKillCounter)();

	return m_approval_monster_kill_counter;
}


hook_method<int (CNpcMercenary::*)(CCharacter* ch, unsigned long flag)> CNpcMercenary::_IsTarget(SERVER, "CNpcMercenary::IsTarget");
int CNpcMercenary::IsTarget(CCharacter* ch, unsigned long flag)
{
	return (this->*_IsTarget)(ch, flag);

	//TODO
}


hook_method<void (CNpcMercenary::*)(void)> CNpcMercenary::_OnProcess(SERVER, "CNpcMercenary::OnProcess");
void CNpcMercenary::OnProcess(void)
{
	return (this->*_OnProcess)();

	//TODO
}


hook_method<void (CNpcMercenary::*)(void)> CNpcMercenary::_Release(SERVER, "CNpcMercenary::Release");
void CNpcMercenary::Release(void)
{
	return (this->*_Release)();

	//TODO
}



hook_method<void (CNpcMercenary::*)(void)> CNpcMercenary::_Approval_Monster_Kill(SERVER, "CNpcMercenary::Approval_Monster_Kill");
void CNpcMercenary::Approval_Monster_Kill(void)
{
	return (this->*_Approval_Monster_Kill)();

	//TODO
}


hook_method<int (CNpcMercenary::*)(void)> CNpcMercenary::_GetHPHealVelocity(SERVER, "CNpcMercenary::GetHPHealVelocity");
int CNpcMercenary::GetHPHealVelocity(void)
{
	return (this->*_GetHPHealVelocity)();

	//TODO
}


hook_method<int (CNpcMercenary::*)(void)> CNpcMercenary::_GetSPHealVelocity(SERVER, "CNpcMercenary::GetSPHealVelocity");
int CNpcMercenary::GetSPHealVelocity(void)
{
	return (this->*_GetSPHealVelocity)();

	//TODO
}


hook_method<void (CNpcMercenary::*)(const unsigned long in_CurTimeMS)> CNpcMercenary::_ProcAutoHPSPCharge(SERVER, "CNpcMercenary::ProcAutoHPSPCharge");
void CNpcMercenary::ProcAutoHPSPCharge(const unsigned long in_CurTimeMS)
{
	return (this->*_ProcAutoHPSPCharge)(in_CurTimeMS);

	//TODO
}


hook_method<void (CNpcMercenary::*)(int& io_SKCastingTM)> CNpcMercenary::_ReductionPredelay(SERVER, "CNpcMercenary::ReductionPredelay");
void CNpcMercenary::ReductionPredelay(int& io_SKCastingTM)
{
	return (this->*_ReductionPredelay)(io_SKCastingTM);

	//TODO
}


//hook_method<void (CNpcMercenary::*)(const unsigned long in_AID)> CNpcMercenary::_SetLastTargetAID(SERVER, "CNpcMercenary::SetLastTargetAID");
void CNpcMercenary::SetLastTargetAID(const unsigned long in_AID)
{
//	return (this->*_SetLastTargetAID)(in_AID);

	m_lastTargetAID = in_AID;
}


/* hook_method<unsigned long (CNpcMercenary::*)(void)> CNpcMercenary::_GetLastTargetAID(SERVER, "CNpcMercenary::GetLastTargetAID");
unsigned long CNpcMercenary::GetLastTargetAID(void)
{
	return (this->*_GetLastTargetAID)();

	//TODO
} */


hook_method<int (CNpcMercenary::*)(void)> CNpcMercenary::_GetMoveHasteValue1(SERVER, "CNpcMercenary::GetMoveHasteValue1");
int CNpcMercenary::GetMoveHasteValue1(void)
{
	return (this->*_GetMoveHasteValue1)();

	//TODO
}


hook_method<int (CNpcMercenary::*)(void)> CNpcMercenary::_GetMoveHasteValue2(SERVER, "CNpcMercenary::GetMoveHasteValue2");
int CNpcMercenary::GetMoveHasteValue2(void)
{
	return (this->*_GetMoveHasteValue2)();

	//TODO
}


hook_method<int (CNpcMercenary::*)(int skillID)> CNpcMercenary::_GetInvincibleTimeInfo(SERVER, "CNpcMercenary::GetInvincibleTimeInfo");
int CNpcMercenary::GetInvincibleTimeInfo(int skillID)
{
	return (this->*_GetInvincibleTimeInfo)(skillID);

	//TODO
}


hook_method<void (CNpcMercenary::*)(unsigned long time, int skillID)> CNpcMercenary::_SetInvincibleTimeInfo(SERVER, "CNpcMercenary::SetInvincibleTimeInfo");
void CNpcMercenary::SetInvincibleTimeInfo(unsigned long time, int skillID)
{
	return (this->*_SetInvincibleTimeInfo)(time, skillID);

	//TODO
}


hook_method<void (CNpcMercenary::*)(void)> CNpcMercenary::_InitEnemyInfo(SERVER, "CNpcMercenary::InitEnemyInfo");
void CNpcMercenary::InitEnemyInfo(void)
{
	return (this->*_InitEnemyInfo)();

	//TODO
}


hook_method<ENEMY_INFO* (CNpcMercenary::*)(unsigned long AID)> CNpcMercenary::_SearchEnemyInfo(SERVER, "CNpcMercenary::SearchEnemyInfo");
ENEMY_INFO* CNpcMercenary::SearchEnemyInfo(unsigned long AID)
{
	return (this->*_SearchEnemyInfo)(AID);

	//TODO
}


hook_method<void (CNpcMercenary::*)(ENEMY_INFO* enemyInfo)> CNpcMercenary::_InsertEnemyInfo(SERVER, "CNpcMercenary::InsertEnemyInfo");
void CNpcMercenary::InsertEnemyInfo(ENEMY_INFO* enemyInfo)
{
	return (this->*_InsertEnemyInfo)(enemyInfo);

	//TODO
}


hook_method<void (CNpcMercenary::*)(void)> CNpcMercenary::_UpdateEnemyInfo(SERVER, "CNpcMercenary::UpdateEnemyInfo");
void CNpcMercenary::UpdateEnemyInfo(void)
{
	return (this->*_UpdateEnemyInfo)();

	//TODO
}
