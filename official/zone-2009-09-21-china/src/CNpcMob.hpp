#pragma once
#include "NPC.h"
#include "PollTimer.h"
#include "struct.hpp"


class CNpcMob : public CNPC
{
	struct vtable_t // const CNpcMob::`vftable'
	{
		void* scalar_deleting_destructor; // void* CNpcMob::`scalar deleting destructor'(uint)
		int (CCharacter::* GetType)(void);
		void (CCharacter::* AddErrorCount)(const char*, int, unsigned long, unsigned long);
		void (CCharacter::* AddErrorCount2)(unsigned long, unsigned long);
		void (CNPC::* Init)(void);
		int (CCharacter::* GetWeaponProperty)(int, int);
		bool (CCharacter::* IsActor)(void);
		int (CCharacter::* IsItPossible)(int);
		int (CNPC::* IsSiegeMode)(void);
		unsigned long (CNPC::* GetAccountID)(void);

		int (CNpcMob::* OnMsg)(CCharacter *, CCharacter *, unsigned long, int, int, int, MSGpar::CVar);
		int (CNPC::* GetParameterValue)(unsigned short, int &);
		int (CNPC::* UpdateParameterValue)(unsigned short, int);
		void (CNPC::* InsertCommand)(COMMAND_QUEUE*);
		void (CNPC::* CheckCommandQueue)(void);
		void (CNPC::* DisableCommand)(unsigned long);
		COMMAND_QUEUE* (CNPC::* SearchCommand)(unsigned long);
		int (CNPC::* IsMyArea)(CCharacter*, int);
		unsigned long (CNPC::* GetState)(void);
		int (CNPC::* GetScale)(void);

		int (CNPC::* IsTarget)(CCharacter*, unsigned long);
		int (CNPC::* IsDamageMotionPossible)(void);
		int (CNPC::* IsRightProperty)(int);
		int (CNPC::* IsAvoidable)(int, int, int);
		int (CCharacter::* IsInitingState)(void);
		int (CCharacter::* IsLucky)(void);
		void (CNPC::* OnShowEffect)(int);
		void (CNPC::* OnShowEffect3)(int, int);
		int (CNPC::* GetEffectState)(void);
		void (CNPC::* OnMsgFromItemServer)(unsigned long, CITZMsg*);

		void (CCharacter::* ReduceSPByUseSkill)(int);
		bool (CCharacter::* IsExistItem)(int, int, bool);
		bool (CCharacter::* ConsumeItemByUseSkill)(int, int, bool);
		short (CNPC::* GetAttackSuccessPercent)(CCharacter *, int);
		int (CNPC::* GetAttackFinalDamage)(ATTACK_INFO *);
		int (CNPC::* SkillAttack)(SKILLATTACK_MSG*, int, int, const bool);
		short (CNPC::* SplashAttack)(int, short, short, int, int, int, unsigned long, void*, int, int);
		int (CNPC::* SplashAttack2)(int, PosInfo, int, int, int, MSG_TYPE1_TWODWORD*, int, int, PosInfo*);
		int (CNPC::* SetHandicapState)(int, CCharacter*, int, int, int, int, int);
		int (CCharacter::* GetModifiedTargetItemDEF)(CCharacter*);

		int (CCharacter::* GetModifiedTargetItemMDEF)(CCharacter*);
		int (CNPC::* SetEffective)(int, int, int, int, int, int);
		int (CCharacter::* GetEffective)(int, int);
		void (CCharacter::* UpdateEffective)(int, int, int);
		void (CNPC::* ResetEffective)(int, int);
		bool (CCharacter::* IsEnableSetEffective)(int, int, int);
		bool (CNPC::* IsGroundEffective)(int, int&, bool&);
		void (CNPC::* ProcessGroundEffective)(int, int, bool);
		void (CCharacter::* ProcessCheckEffective)(int, EFFECTIVE_INFO *);
		void (CNPC::* SetOnShowEFST)(int);

		void (CNPC::* SetOffShowEFST)(int);
		void (CNPC::* OnChangeStatusAmount)(int, unsigned short, unsigned long, int);
		void (CNPC::* NotifyStatusAmount)(unsigned short, int);
		char (CNPC::* GetCampID)(void);
		void (CNPC::* SetCampID)(char);
		const char* (CNPC::* GetNamePtr)(void);
		short (CNPC::* GetHealthState)(void);
		void (CNPC::* ResetHealthState)(short);
		void (CNPC::* SetEffectStateTimeInfo)(unsigned long, int);
		void (CNPC::* ResetEffectState)(int);

		void (CNPC::* SetEffectState)(int);
		void (CNpcMob::* Reset)(void);
		void (CNPC::* OnDead)(unsigned long);
		void (CNPC::* Send)(int, char *);
		void (CNPC::* SkillUseAck)(unsigned short, unsigned short, bool, unsigned char);
		void (CNpcMob::* OnProcess)(void);
		int (CNPC::* GetAttackPoint)(CCharacter *, unsigned short, int);
		int (CNPC::* GetSpeed)(void);
		int (CNPC::* GetAvoidableSuccessPercent)(void);
		short (CNPC::* GetStatusDef)(void);

		short (CNPC::* GetDefencePoint)(void);
		int (CNPC::* GetModifiedValueByEnemySize)(int);
		short (CNPC::* GetItemMagicDef)(void);
		short (CNPC::* GetStatusMagicDef)(void);
		int (CNPC::* GetMaxHP)(void);
		int (CNPC::* GetMaxSP)(void);
		short (CNPC::* GetDexValue)(void);
		short (CNPC::* GetIntValue)(void);
		int (CNPC::* IsRechargeTime)(void);
		void (CNPC::* ModifyAttackPowerByEffective)(CCharacter *, int, int &);

		int (CNPC::* GetSKLevel)(const int);
		bool (CNPC::* OpSKToChar_SKID_ML_DEVOTION)(CCharacter *, MSG_TYPE4_FIVEDWORD *);
		void (CNPC::* OpSKToSelf_SKID_ML_DEFENDER)(const int);
		void (CNPC::* OpSKToSelf_SKID_MER_MAGNIFICAT)(const int, const int, const int, const int);
		void (CNPC::* OpSKToSelf_SKID_MER_AUTOBERSERK)(void);
		void (CNPC::* NotifyParameter)(unsigned short, int);
		void (CNPC::* ResetEffective_after_EFST_DEFENDER)(void);
		int (CNPC::* GetEmblemVersion)(void);
		bool (CNPC::* ApplyStatusAmount)(unsigned short, int &);
		int (CNPC::* GetModifiedTargetStatusDEF)(CCharacter *);

		void (CNPC::* ApplyExtraDEF)(int &, CCharacter *);
		void (CNPC::* ApplyExtraMDEF)(int &);
		void (CNpcMob::* InitCore)(void);
		int (CNPC::* GetMagicAttPower)(void);
		short (CNPC::* GetAvoidPercent_Client)(void);
	};

	/* this+0x0   */ public: //CNPC baseclass_0;
	/* this+0x46C */ private: CPollTimer m_stateTimer;
	/* this+0x474 */ private: BOSS_INFO m_bossInfo;

	enum
	{
		BOSSREGEN_NOT_BOSS = 0x0,
		BOSSREGEN_NOT_YET = 0x1,
		BOSSREGEN_PERMIT = 0x2,
	};

	public: CNpcMob::CNpcMob(void);
	public: virtual CNpcMob::~CNpcMob(void);
	public: virtual int CNpcMob::OnMsg(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4);
	public: virtual void CNpcMob::Reset(void);
	public: virtual void CNpcMob::OnProcess(void);
	public: int CNpcMob::GetInvincibleTimeInfo(int skillID);
	public: int CNpcMob::ChkGndSkillDurability(void);
	public: void CNpcMob::SetEffectByGospel(CCharacter* ch);
	//public: void CNpcMob::ResetEffectByGospel(int);
	public: void CNpcMob::ResetEffectiveByDispel(void);
	public: int CNpcMob::GetMonsterDBDef(void);
	public: int CNpcMob::GetMonsterDBMdef(void);
	public: short CNpcMob::CheckBossEnableRegen(void);
	public: void CNpcMob::GetBossRegenSystemTime(unsigned long& hour, unsigned long& minute);
	public: bool CNpcMob::IsBossInMap(void);
	private: virtual void CNpcMob::InitCore(void);
	private: void CNpcMob::OnHealHP(int par1);
	private: void CNpcMob::OnDecreaseDef(CCharacter* sender, int par1);
	private: void CNpcMob::OnSetBossInMap(void);
	private: void CNpcMob::OnRequestBossInfo(CCharacter* sender);
	private: void CNpcMob::OnReqAddBossPCList(CCharacter* sender);
	private: void CNpcMob::OnReqDelBossPCList(CCharacter* sender);
	private: void CNpcMob::OnBlessingFromAcolyte(CCharacter* sender, int par1, int par2, int par3);
	private: void CNpcMob::OnCureFromAcolyte(void);
	private: void CNpcMob::OnResurrection(int healPercent);
	private: void CNpcMob::SetInvincibleTimeInfo(unsigned long time, int skillID);
	private: void CNpcMob::SetBodyStateTimeInfo(unsigned long firstTime, unsigned long secondTime, int state);
	private: void CNpcMob::SetHealthStateTimeInfo(int firstTime, int secondTime, int state);
	private: void CNpcMob::UpdateBossInfo(void);
	private: char* CNpcMob::GetBossInfo(bool isWithMsg);

private:
	static hook_method<int (CNpcMob::*)(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4)> CNpcMob::_OnMsg;
	static hook_method<void (CNpcMob::*)(void)> CNpcMob::_Reset;
	static hook_method<void (CNpcMob::*)(void)> CNpcMob::_OnProcess;
	static hook_method<int (CNpcMob::*)(int skillID)> CNpcMob::_GetInvincibleTimeInfo;
	static hook_method<int (CNpcMob::*)(void)> CNpcMob::_ChkGndSkillDurability;
	static hook_method<void (CNpcMob::*)(CCharacter* ch)> CNpcMob::_SetEffectByGospel;
	static hook_method<void (CNpcMob::*)(void)> CNpcMob::_ResetEffectiveByDispel;
	static hook_method<int (CNpcMob::*)(void)> CNpcMob::_GetMonsterDBDef;
	static hook_method<int (CNpcMob::*)(void)> CNpcMob::_GetMonsterDBMdef;
	static hook_method<short (CNpcMob::*)(void)> CNpcMob::_CheckBossEnableRegen;
	static hook_method<void (CNpcMob::*)(unsigned long& hour, unsigned long& minute)> CNpcMob::_GetBossRegenSystemTime;
	static hook_method<bool (CNpcMob::*)(void)> CNpcMob::_IsBossInMap;
	static hook_method<void (CNpcMob::*)(void)> CNpcMob::_InitCore;
	static hook_method<void (CNpcMob::*)(int par1)> CNpcMob::_OnHealHP;
	static hook_method<void (CNpcMob::*)(CCharacter* sender, int par1)> CNpcMob::_OnDecreaseDef;
	static hook_method<void (CNpcMob::*)(void)> CNpcMob::_OnSetBossInMap;
	static hook_method<void (CNpcMob::*)(CCharacter* sender)> CNpcMob::_OnRequestBossInfo;
	static hook_method<void (CNpcMob::*)(CCharacter* sender)> CNpcMob::_OnReqAddBossPCList;
	static hook_method<void (CNpcMob::*)(CCharacter* sender)> CNpcMob::_OnReqDelBossPCList;
	static hook_method<void (CNpcMob::*)(CCharacter* sender, int par1, int par2, int par3)> CNpcMob::_OnBlessingFromAcolyte;
	static hook_method<void (CNpcMob::*)(void)> CNpcMob::_OnCureFromAcolyte;
	static hook_method<void (CNpcMob::*)(int healPercent)> CNpcMob::_OnResurrection;
	static hook_method<void (CNpcMob::*)(unsigned long time, int skillID)> CNpcMob::_SetInvincibleTimeInfo;
	static hook_method<void (CNpcMob::*)(unsigned long firstTime, unsigned long secondTime, int state)> CNpcMob::_SetBodyStateTimeInfo;
	static hook_method<void (CNpcMob::*)(int firstTime, int secondTime, int state)> CNpcMob::_SetHealthStateTimeInfo;
	static hook_method<void (CNpcMob::*)(void)> CNpcMob::_UpdateBossInfo;
	static hook_method<char* (CNpcMob::*)(bool isWithMsg)> CNpcMob::_GetBossInfo;
};

