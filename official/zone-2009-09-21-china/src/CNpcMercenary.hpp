#pragma once
#include "NPC.h"
#include "PollTimer.h"
#include "struct.hpp"
#include "std/map"
#include "std/vector"
struct MSG_TYPE5_SIXDWORD;
class CSkillTypeInfo;


class CNpcMercenary : public CNPC
{
	enum
	{
		LIFE_TIME_SECOND = 1800,
		SK_BUFSIZE = 256,
		MAX_SKINFO_BUFF = 2048,
		LENGTH_TELEPORT_TO_OWNER = 15,
	};


	struct tagActiveSkillCount
	{
		enum
		{
			MAXCOUNT_SKIDTRAP = 10,
			MAXCOUNT_LANDMINE = 10,
			MAXCOUNT_SANDMAN = 10,
			MAXCOUNT_FREEZINGTRAP = 10,
		};

		/* this+0x0 */ int SKIDTRAP;
		/* this+0x4 */ int LANDMINE;
		/* this+0x8 */ int SANDMAN;
		/* this+0xC */ int FREEZINGTRAP;
	};

	class Teleport
	{
		/* this+0x0 */ private: CPollTimer m_timer;
		/* this+0x8 */ private: bool m_bActive;

		//public: void Init();
		//public: bool isCheckTime(const unsigned long);
		//public: void SetActive(const bool);
		//public: bool isActive();
	};

	class MERSkill
	{
		/* this+0x0 */ public: int m_SKID;
		/* this+0x4 */ public: int m_Level;
		/* this+0x8 */ public: int m_Type;

		//public: void MERSkill();
	};

	/* this+   0 */ public: //CNPC baseclass_0;
	/* this+1132 */ private: CNpcMercenary::tagActiveSkillCount m_ActiveSkillCount;
	/* this+1148 */ private: long m_ExpireTM;
	/* this+1152 */ private: int m_SKPoint;
	/* this+1156 */ private: int m_approval_monster_kill_counter;
	/* this+1160 */ private: int m_total_call_number;
	/* this+1164 */ private: int m_faith2;
	/* this+1168 */ private: bool m_bReady;
	/* this+1172 */ private: CPollTimer m_timerState;
	/* this+1180 */ private: unsigned long m_gageRefreshTime;
	/* this+1184 */ private: unsigned long m_AttReqLastTime;
	/* this+1188 */ private: unsigned long m_lastTargetAID;
	/* this+1192 */ private: bool m_bDevotion;
	/* this+1196 */ private: mystd::vector<ENEMY_INFO> m_enemyInfo;
	/* this+1212 */ private: CNpcMercenary::Teleport m_Teleport;
	/* this+1224 */ private: mystd::map<int,CNpcMercenary::MERSkill> m_Skill;

	typedef mystd::map<int,CNpcMercenary::MERSkill>::const_iterator SKILLCONTAINERITOR;

	public: void CNpcMercenary::PacketSend_ZC_MER_INIT(void);
	public: void CNpcMercenary::PacketSend_ZC_MER_SKILLINFO_LIST(void);
	//public: void CNpcMercenary::PacketSend_ZC_MER_SKILLINFO_UPDATE(const int, const bool);
	public: void CNpcMercenary::PacketSend_ZC_DEVOTIONLIST(unsigned long in_TagetAID, short in_Range);
	public: void CNpcMercenary::Send(const int in_Length, char* in_pBuffer);
	private: void CNpcMercenary::InitCore(void);
	private: void CNpcMercenary::OnTimer(void);
	public: bool CNpcMercenary::isEffectApply(const int in_EffectIdx);
	private: CNpcMercenary::MERSkill* CNpcMercenary::GetSkill(const int in_SKID);
	private: bool CNpcMercenary::IsSatisfySkill(const int in_Job, const int in_SKID);
	//private: void CNpcMercenary::ApplyPassiveSkill(const int, const int);
	private: void CNpcMercenary::ChkAllEnableSkill(void);
	public: bool CNpcMercenary::IsSkillUsable(const unsigned short in_SKID);
	public: bool CNpcMercenary::IsSkillEnable(const int in_SKID, const int in_Level, CCharacter* const in_pTargetCh);
	public: void CNpcMercenary::StartUseSkill(void);
	public: void CNpcMercenary::ReduceSPByUseSkill(int sp);
	public: bool CNpcMercenary::ParseEffectData(const int in_Length, const unsigned char* in_pData);
	public: int CNpcMercenary::GetEffectDBFmt(const unsigned char* io_pData, const int in_MaxLength);
	public: int CNpcMercenary::OnMsg(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4);
	public: void CNpcMercenary::OnADDSKILL(SKILLINFO* in_pSkill);
	public: void CNpcMercenary::OnATKSKILL_TOCHAR_MER(const int in_SKID, const int in_TargetAID, const MSG_TYPE4_FIVEDWORD* in_pData);
	public: void CNpcMercenary::OnGroundSkill_MER(const int in_SKID, const int in_TargetAID, const MSG_TYPE5_SIXDWORD* in_pData);
	public: void CNpcMercenary::UseSkillToCharacter_MER(const int in_SKID, const int in_TargetAID, const MSG_TYPE4_FIVEDWORD* in_pData);
	public: void CNpcMercenary::SPAttackSkillToCharacter_MER(const int in_SKID, const int in_TargetAID, const MSG_TYPE4_FIVEDWORD* in_pData);
	public: void CNpcMercenary::OperationSkillToSelf_MER(const int in_SKID, const int in_TargetAID, const MSG_TYPE4_FIVEDWORD* in_pData);
	public: void CNpcMercenary::OnADD_EXP(CCharacter* in_pSender, const int in_Exp);
	public: void CNpcMercenary::OnSHARE_EXP(CCharacter* in_pSender, const int in_Exp);
	public: void CNpcMercenary::OnADD_JOBEXP(CCharacter* in_pSender, const int in_JobExp, const int in_xPos, const int in_yPos);
	public: void CNpcMercenary::OnSHARE_JOBEXP(CCharacter* pSendeer, const int in_JobExp);
	public: void CNpcMercenary::OnKILLED(CCharacter* const in_pSender, CCharacter* const in_pTarget);
	public: void CNpcMercenary::OnHEAL_HP(const int in_modifyHP);
	public: void CNpcMercenary::OnHEAL_SP(const int in_modifySP);
	public: void CNpcMercenary::OnTIME_BODYSTATE(const unsigned long in_preDelayTime, const unsigned long in_maintainTime, const int in_state);
	public: void CNpcMercenary::OnTIME_HEALTHSTATE(const int firstTime, const int secondTime, const int state);
	public: void CNpcMercenary::OnDEVOTIONLIST_REMOVE(const int in_RemoveAID);
	public: void CNpcMercenary::OnBLESSING_FROM_ACOLYTE(CCharacter* sender, int par1, int par2, int par3);
	private: void CNpcMercenary::ChangeHP(const int in_ChangeValue);
	private: void CNpcMercenary::ChangeSP(const int in_ChangeValue);
	private: void CNpcMercenary::ChangeFAITH(const int in_ChangeValue);
	private: void CNpcMercenary::BroadcastHP(void);
	public: void CNpcMercenary::OnEmployTimeExpire(void);
	public: bool CNpcMercenary::isDevotion(void);
	public: void CNpcMercenary::SetBodyStateTimeInfo(unsigned long firstTime, unsigned long secondTime, int state);
	public: void CNpcMercenary::OnDead(unsigned long killer);
	public: int CNpcMercenary::UpdateParameterValue(unsigned short id, int value);
	public: bool CNpcMercenary::OpSKToChar_SKID_ML_DEVOTION(CCharacter* in_TargetCH, MSG_TYPE4_FIVEDWORD* in_pData);
	public: void CNpcMercenary::OpSKToSelf_SKID_ML_DEFENDER(const int in_SKlevel);
	public: void CNpcMercenary::NotifyParameter(unsigned short type, int count);
	public: void CNpcMercenary::ResetEffective_after_EFST_DEFENDER(void);
	public: void CNpcMercenary::OpSKToSelf_SKID_MER_MAGNIFICAT(const int in_SKLevel, const int in_EFST, const int in_EFST_time, const int in_EFST_value);
	public: int CNpcMercenary::GetAvoidableSuccessPercent(void);
	public: short CNpcMercenary::GetDefencePoint(void);
	public: short CNpcMercenary::GetStatusDef(void);
	public: int CNpcMercenary::GetModifiedValueByEnemySize(int value);
	public: int CNpcMercenary::IsInitingState(void);
	public: int CNpcMercenary::GetMaxSP(void);
	public: short CNpcMercenary::GetJob(void);
	public: int CNpcMercenary::GetSP(void);
	public: short CNpcMercenary::GetCRI(void);
	public: short CNpcMercenary::GetDEF(void);
	public: short CNpcMercenary::GetVitValue(void);
	public: short CNpcMercenary::GetDexValue(void);
	public: int CNpcMercenary::GetMagicAttPower(void);
	public: short CNpcMercenary::GetIntValue(void);
	public: short CNpcMercenary::GetMdef(void);
	public: static int __cdecl CNpcMercenary::GetTypicalJob(const int in_Job);
	public: int CNpcMercenary::GetTypicalJob(void);
	public: int CNpcMercenary::GetSKLevel(const int in_SKID);
	public: int CNpcMercenary::GetSKType(const int in_SKID);
	public: CPC* CNpcMercenary::GetOwner(void);
	public: int CNpcMercenary::GetDesX(void);
	public: int CNpcMercenary::GetDesY(void);
	public: int CNpcMercenary::GetCurX(void);
	public: int CNpcMercenary::GetCurY(void);
	public: unsigned long CNpcMercenary::GetAttackLastTime(void);
	public: void CNpcMercenary::SetAttackLastTime(const unsigned long in_time);
	public: int CNpcMercenary::GetSPCost(const int in_SKID, const int in_Level, CSkillTypeInfo* in_pSTI);
	public: int CNpcMercenary::GetSKCastingTM(CSkillTypeInfo* in_pSKTypeInfo, short in_skLevel, CCharacter* in_pTargetCh, int in_TargetXPos, int in_TargetYPos);
	public: int CNpcMercenary::GetRemainLifeSECOND(void);
	public: int CNpcMercenary::GetApprovalMonsterKillCounter(void);
	public: int CNpcMercenary::IsTarget(CCharacter* ch, unsigned long flag);
	public: void CNpcMercenary::OnProcess(void);
	public: void CNpcMercenary::Release(void);
	//public: void CNpcMercenary::SetReady(const bool);
	public: void CNpcMercenary::Approval_Monster_Kill(void);
	public: int CNpcMercenary::GetHPHealVelocity(void);
	public: int CNpcMercenary::GetSPHealVelocity(void);
	public: void CNpcMercenary::ProcAutoHPSPCharge(const unsigned long in_CurTimeMS);
	public: void CNpcMercenary::ReductionPredelay(int& io_SKCastingTM);
	public: void CNpcMercenary::SetLastTargetAID(const unsigned long in_AID);
	public: unsigned long CNpcMercenary::GetLastTargetAID(void);
	public: int CNpcMercenary::GetMoveHasteValue1(void);
	public: int CNpcMercenary::GetMoveHasteValue2(void);
	public: int CNpcMercenary::GetInvincibleTimeInfo(int skillID);
	private: void CNpcMercenary::SetInvincibleTimeInfo(unsigned long time, int skillID);
	public: void CNpcMercenary::InitEnemyInfo(void);
	public: ENEMY_INFO* CNpcMercenary::SearchEnemyInfo(unsigned long AID);
	public: void CNpcMercenary::InsertEnemyInfo(ENEMY_INFO* enemyInfo);
	public: void CNpcMercenary::UpdateEnemyInfo(void);
	//public: CPCBattleMercenary::TypicalJobInfo operator CPCBattleMercenary::TypicalJobInfo(void);
	//public: CMercenaryDBV2::DBINFO operator CMercenaryDBV2::DBINFO(void);
	//public: CNpcMercenary& operator=(const CNpcMercenary&);
	//public: CNpcMercenary& CNpcMercenary::operator=(const CPCBattleMercenary::TypicalJobInfo&);
	//public: CNpcMercenary& CNpcMercenary::operator=(const CMercenaryDBV2::DBINFO&);
	//public: void CNpcMercenary::CNpcMercenary(void);
	//public: void CNpcMercenary::~CNpcMercenary(void);
private:
	static hook_method<void (CNpcMercenary::*)(void)> CNpcMercenary::_PacketSend_ZC_MER_INIT;
	static hook_method<void (CNpcMercenary::*)(void)> CNpcMercenary::_PacketSend_ZC_MER_SKILLINFO_LIST;
	static hook_method<void (CNpcMercenary::*)(unsigned long in_TagetAID, short in_Range)> CNpcMercenary::_PacketSend_ZC_DEVOTIONLIST;
	static hook_method<void (CNpcMercenary::*)(const int in_Length, char* in_pBuffer)> CNpcMercenary::_Send;
	static hook_method<void (CNpcMercenary::*)(void)> CNpcMercenary::_InitCore;
	static hook_method<void (CNpcMercenary::*)(void)> CNpcMercenary::_OnTimer;
	static hook_method<bool (CNpcMercenary::*)(const int in_EffectIdx)> CNpcMercenary::_isEffectApply;
	static hook_method<CNpcMercenary::MERSkill* (CNpcMercenary::*)(const int in_SKID)> CNpcMercenary::_GetSkill;
	static hook_method<bool (CNpcMercenary::*)(const int in_Job, const int in_SKID)> CNpcMercenary::_IsSatisfySkill;
	static hook_method<void (CNpcMercenary::*)(void)> CNpcMercenary::_ChkAllEnableSkill;
	static hook_method<bool (CNpcMercenary::*)(const unsigned short in_SKID)> CNpcMercenary::_IsSkillUsable;
	static hook_method<bool (CNpcMercenary::*)(const int in_SKID, const int in_Level, CCharacter* const in_pTargetCh)> CNpcMercenary::_IsSkillEnable;
	static hook_method<void (CNpcMercenary::*)(void)> CNpcMercenary::_StartUseSkill;
	static hook_method<void (CNpcMercenary::*)(int sp)> CNpcMercenary::_ReduceSPByUseSkill;
	static hook_method<bool (CNpcMercenary::*)(const int in_Length, const unsigned char* in_pData)> CNpcMercenary::_ParseEffectData;
	static hook_method<int (CNpcMercenary::*)(const unsigned char* io_pData, const int in_MaxLength)> CNpcMercenary::_GetEffectDBFmt;
	static hook_method<int (CNpcMercenary::*)(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4)> CNpcMercenary::_OnMsg;
	static hook_method<void (CNpcMercenary::*)(SKILLINFO* in_pSkill)> CNpcMercenary::_OnADDSKILL;
	static hook_method<void (CNpcMercenary::*)(const int in_SKID, const int in_TargetAID, const MSG_TYPE4_FIVEDWORD* in_pData)> CNpcMercenary::_OnATKSKILL_TOCHAR_MER;
	static hook_method<void (CNpcMercenary::*)(const int in_SKID, const int in_TargetAID, const MSG_TYPE5_SIXDWORD* in_pData)> CNpcMercenary::_OnGroundSkill_MER;
	static hook_method<void (CNpcMercenary::*)(const int in_SKID, const int in_TargetAID, const MSG_TYPE4_FIVEDWORD* in_pData)> CNpcMercenary::_UseSkillToCharacter_MER;
	static hook_method<void (CNpcMercenary::*)(const int in_SKID, const int in_TargetAID, const MSG_TYPE4_FIVEDWORD* in_pData)> CNpcMercenary::_SPAttackSkillToCharacter_MER;
	static hook_method<void (CNpcMercenary::*)(const int in_SKID, const int in_TargetAID, const MSG_TYPE4_FIVEDWORD* in_pData)> CNpcMercenary::_OperationSkillToSelf_MER;
	static hook_method<void (CNpcMercenary::*)(CCharacter* in_pSender, const int in_Exp)> CNpcMercenary::_OnADD_EXP;
	static hook_method<void (CNpcMercenary::*)(CCharacter* in_pSender, const int in_Exp)> CNpcMercenary::_OnSHARE_EXP;
	static hook_method<void (CNpcMercenary::*)(CCharacter* in_pSender, const int in_JobExp, const int in_xPos, const int in_yPos)> CNpcMercenary::_OnADD_JOBEXP;
	static hook_method<void (CNpcMercenary::*)(CCharacter* pSendeer, const int in_JobExp)> CNpcMercenary::_OnSHARE_JOBEXP;
	static hook_method<void (CNpcMercenary::*)(CCharacter* const in_pSender, CCharacter* const in_pTarget)> CNpcMercenary::_OnKILLED;
	static hook_method<void (CNpcMercenary::*)(const int in_modifyHP)> CNpcMercenary::_OnHEAL_HP;
	static hook_method<void (CNpcMercenary::*)(const int in_modifySP)> CNpcMercenary::_OnHEAL_SP;
	static hook_method<void (CNpcMercenary::*)(const unsigned long in_preDelayTime, const unsigned long in_maintainTime, const int in_state)> CNpcMercenary::_OnTIME_BODYSTATE;
	static hook_method<void (CNpcMercenary::*)(const int firstTime, const int secondTime, const int state)> CNpcMercenary::_OnTIME_HEALTHSTATE;
	static hook_method<void (CNpcMercenary::*)(const int in_RemoveAID)> CNpcMercenary::_OnDEVOTIONLIST_REMOVE;
	static hook_method<void (CNpcMercenary::*)(CCharacter* sender, int par1, int par2, int par3)> CNpcMercenary::_OnBLESSING_FROM_ACOLYTE;
	static hook_method<void (CNpcMercenary::*)(const int in_ChangeValue)> CNpcMercenary::_ChangeHP;
	static hook_method<void (CNpcMercenary::*)(const int in_ChangeValue)> CNpcMercenary::_ChangeSP;
	static hook_method<void (CNpcMercenary::*)(const int in_ChangeValue)> CNpcMercenary::_ChangeFAITH;
	static hook_method<void (CNpcMercenary::*)(void)> CNpcMercenary::_BroadcastHP;
	static hook_method<void (CNpcMercenary::*)(void)> CNpcMercenary::_OnEmployTimeExpire;
	static hook_method<bool (CNpcMercenary::*)(void)> CNpcMercenary::_isDevotion;
	static hook_method<void (CNpcMercenary::*)(unsigned long firstTime, unsigned long secondTime, int state)> CNpcMercenary::_SetBodyStateTimeInfo;
	static hook_method<void (CNpcMercenary::*)(unsigned long killer)> CNpcMercenary::_OnDead;
	static hook_method<int (CNpcMercenary::*)(unsigned short id, int value)> CNpcMercenary::_UpdateParameterValue;
	static hook_method<bool (CNpcMercenary::*)(CCharacter* in_TargetCH, MSG_TYPE4_FIVEDWORD* in_pData)> CNpcMercenary::_OpSKToChar_SKID_ML_DEVOTION;
	static hook_method<void (CNpcMercenary::*)(const int in_SKlevel)> CNpcMercenary::_OpSKToSelf_SKID_ML_DEFENDER;
	static hook_method<void (CNpcMercenary::*)(unsigned short type, int count)> CNpcMercenary::_NotifyParameter;
	static hook_method<void (CNpcMercenary::*)(void)> CNpcMercenary::_ResetEffective_after_EFST_DEFENDER;
	static hook_method<void (CNpcMercenary::*)(const int in_SKLevel, const int in_EFST, const int in_EFST_time, const int in_EFST_value)> CNpcMercenary::_OpSKToSelf_SKID_MER_MAGNIFICAT;
	static hook_method<int (CNpcMercenary::*)(void)> CNpcMercenary::_GetAvoidableSuccessPercent;
	static hook_method<short (CNpcMercenary::*)(void)> CNpcMercenary::_GetDefencePoint;
	static hook_method<short (CNpcMercenary::*)(void)> CNpcMercenary::_GetStatusDef;
	static hook_method<int (CNpcMercenary::*)(int value)> CNpcMercenary::_GetModifiedValueByEnemySize;
	static hook_method<int (CNpcMercenary::*)(void)> CNpcMercenary::_IsInitingState;
	static hook_method<int (CNpcMercenary::*)(void)> CNpcMercenary::_GetMaxSP;
	static hook_method<short (CNpcMercenary::*)(void)> CNpcMercenary::_GetJob;
	static hook_method<int (CNpcMercenary::*)(void)> CNpcMercenary::_GetSP;
	static hook_method<short (CNpcMercenary::*)(void)> CNpcMercenary::_GetCRI;
	static hook_method<short (CNpcMercenary::*)(void)> CNpcMercenary::_GetDEF;
	static hook_method<short (CNpcMercenary::*)(void)> CNpcMercenary::_GetVitValue;
	static hook_method<short (CNpcMercenary::*)(void)> CNpcMercenary::_GetDexValue;
	static hook_method<int (CNpcMercenary::*)(void)> CNpcMercenary::_GetMagicAttPower;
	static hook_method<short (CNpcMercenary::*)(void)> CNpcMercenary::_GetIntValue;
	static hook_method<short (CNpcMercenary::*)(void)> CNpcMercenary::_GetMdef;
	static hook_method<static int (__cdecl *)(const int in_Job)> CNpcMercenary::_GetTypicalJob;
	static hook_method<int (CNpcMercenary::*)(void)> CNpcMercenary::_GetTypicalJob2;
	static hook_method<int (CNpcMercenary::*)(const int in_SKID)> CNpcMercenary::_GetSKLevel;
	static hook_method<int (CNpcMercenary::*)(const int in_SKID)> CNpcMercenary::_GetSKType;
	static hook_method<CPC* (CNpcMercenary::*)(void)> CNpcMercenary::_GetOwner;
	static hook_method<int (CNpcMercenary::*)(void)> CNpcMercenary::_GetDesX;
	static hook_method<int (CNpcMercenary::*)(void)> CNpcMercenary::_GetDesY;
	static hook_method<int (CNpcMercenary::*)(void)> CNpcMercenary::_GetCurX;
	static hook_method<int (CNpcMercenary::*)(void)> CNpcMercenary::_GetCurY;
	static hook_method<unsigned long (CNpcMercenary::*)(void)> CNpcMercenary::_GetAttackLastTime;
	static hook_method<void (CNpcMercenary::*)(const unsigned long in_time)> CNpcMercenary::_SetAttackLastTime;
	static hook_method<int (CNpcMercenary::*)(const int in_SKID, const int in_Level, CSkillTypeInfo* in_pSTI)> CNpcMercenary::_GetSPCost;
	static hook_method<int (CNpcMercenary::*)(CSkillTypeInfo* in_pSKTypeInfo, short in_skLevel, CCharacter* in_pTargetCh, int in_TargetXPos, int in_TargetYPos)> CNpcMercenary::_GetSKCastingTM;
	static hook_method<int (CNpcMercenary::*)(void)> CNpcMercenary::_GetRemainLifeSECOND;
	static hook_method<int (CNpcMercenary::*)(void)> CNpcMercenary::_GetApprovalMonsterKillCounter;
	static hook_method<int (CNpcMercenary::*)(CCharacter* ch, unsigned long flag)> CNpcMercenary::_IsTarget;
	static hook_method<void (CNpcMercenary::*)(void)> CNpcMercenary::_OnProcess;
	static hook_method<void (CNpcMercenary::*)(void)> CNpcMercenary::_Release;
	static hook_method<void (CNpcMercenary::*)(void)> CNpcMercenary::_Approval_Monster_Kill;
	static hook_method<int (CNpcMercenary::*)(void)> CNpcMercenary::_GetHPHealVelocity;
	static hook_method<int (CNpcMercenary::*)(void)> CNpcMercenary::_GetSPHealVelocity;
	static hook_method<void (CNpcMercenary::*)(const unsigned long in_CurTimeMS)> CNpcMercenary::_ProcAutoHPSPCharge;
	static hook_method<void (CNpcMercenary::*)(int& io_SKCastingTM)> CNpcMercenary::_ReductionPredelay;
	static hook_method<void (CNpcMercenary::*)(const unsigned long in_AID)> CNpcMercenary::_SetLastTargetAID;
	static hook_method<unsigned long (CNpcMercenary::*)(void)> CNpcMercenary::_GetLastTargetAID;
	static hook_method<int (CNpcMercenary::*)(void)> CNpcMercenary::_GetMoveHasteValue1;
	static hook_method<int (CNpcMercenary::*)(void)> CNpcMercenary::_GetMoveHasteValue2;
	static hook_method<int (CNpcMercenary::*)(int skillID)> CNpcMercenary::_GetInvincibleTimeInfo;
	static hook_method<void (CNpcMercenary::*)(unsigned long time, int skillID)> CNpcMercenary::_SetInvincibleTimeInfo;
	static hook_method<void (CNpcMercenary::*)(void)> CNpcMercenary::_InitEnemyInfo;
	static hook_method<ENEMY_INFO* (CNpcMercenary::*)(unsigned long AID)> CNpcMercenary::_SearchEnemyInfo;
	static hook_method<void (CNpcMercenary::*)(ENEMY_INFO* enemyInfo)> CNpcMercenary::_InsertEnemyInfo;
	static hook_method<void (CNpcMercenary::*)(void)> CNpcMercenary::_UpdateEnemyInfo;
};
