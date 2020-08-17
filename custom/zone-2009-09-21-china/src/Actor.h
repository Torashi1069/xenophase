#pragma once
#include "Character.h"
#include "std/map"


class CActor : public CCharacter
{
public:
	struct vtable_t // const CActor::`vftable'
	{
		void* (CActor::* scalar_deleting_destructor)(unsigned int flags);
		int (CCharacter::* GetType)(void);
		void (CCharacter::* AddErrorCount)(const char* filename, int line, DWORD count, DWORD time);
		void (CCharacter::* AddErrorCount2)(DWORD count, DWORD time);
		void (CActor::* Init)(void);
		int (CCharacter::* GetWeaponProperty)(int position, int isArrowProperty);
		bool (CCharacter::* IsActor)(void);
		int (CCharacter::* IsItPossible)(int property);
		int (CCharacter::* IsSiegeMode)(void);
		unsigned long (CCharacter::* GetAccountID)(void); // __purecall

		int (CCharacter::* OnMsg)(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4);
		int (CCharacter::* GetParameterValue)(unsigned short id, int& value);
		int (CCharacter::* UpdateParameterValue)(unsigned short id, int value);
		void (CCharacter::* InsertCommand)(COMMAND_QUEUE* command); // __purecall
		void (CCharacter::* CheckCommandQueue)(void); // __purecall
		void (CCharacter::* DisableCommand)(unsigned long commandID);
		COMMAND_QUEUE* (CCharacter::* SearchCommand)(unsigned long commandID);
		int (CCharacter::* IsMyArea)(CCharacter* ch, int range); // __purecall
		unsigned long (CCharacter::* GetState)(void);
		int (CCharacter::* GetScale)(void);

		int (CCharacter::* IsTarget)(CCharacter* ch, unsigned long flag); // __purecall
		int (CCharacter::* IsDamageMotionPossible)(void);
		int (CCharacter::* IsRightProperty)(int property);
		int (CCharacter::* IsAvoidable)(int race, int _class, int level);
		int (CCharacter::* IsInitingState)(void);
		int (CCharacter::* IsLucky)(void);
		void (CCharacter::* OnShowEffect)(int effect);
		void (CCharacter::* OnShowEffect3)(int effect, int numdata);
		int (CCharacter::* GetEffectState)(void);
		void (CCharacter::* OnMsgFromItemServer)(unsigned long in_loc, CITZMsg* flag);

		void (CCharacter::* ReduceSPByUseSkill)(int sp);
		bool (CCharacter::* IsExistItem)(int itemID, int count, bool isExternalEffect);
		bool (CCharacter::* ConsumeItemByUseSkill)(int itemID, int count, bool isExternalEffect);
		short (CCharacter::* GetAttackSuccessPercent)(CCharacter* other, int isRangeAttack);
		int (CCharacter::* GetAttackFinalDamage)(ATTACK_INFO* info);
		int (CCharacter::* SkillAttack)(SKILLATTACK_MSG* msg, int plusATTPowerPercent, int plusATTSuccessPercent, const bool in_bHideSkill);
		short (CCharacter::* SplashAttack)(int val1, short xPos, short yPos, int type, int range, int rangeIn, unsigned long exceptAID, void* msgDataPtr, int val2, int count);
		int (CCharacter::* SplashAttack2)(int plusATTPower, PosInfo dest, int type, int halfWidth, int height, MSG_TYPE1_TWODWORD* msgData, int count, int plusHitPercent, PosInfo* specialSrc);
		int (CCharacter::* SetHandicapState)(int state, CCharacter* other, int percent, int preDelayTime, int delayTime, int isSpell, int isFixedDelayTime);
		int (CCharacter::* GetModifiedTargetItemDEF)(CCharacter* target);

		int (CCharacter::* GetModifiedTargetItemMDEF)(CCharacter* target);
		int (CCharacter::* SetEffective)(int index, int time, int val1, int val2, int val3, int isSendClient);
		int (CCharacter::* GetEffective)(int index, int enumVal);
		void (CCharacter::* UpdateEffective)(int index, int val, int enumVal);
		void (CCharacter::* ResetEffective)(int index, int val);
		bool (CCharacter::* IsEnableSetEffective)(int index, int time, int val);
		bool (CCharacter::* IsGroundEffective)(int index, int& SKID, bool& isPlaySolo);
		void (CCharacter::* ProcessGroundEffective)(int par1, int par2, bool par3);
		void (CCharacter::* ProcessCheckEffective)(int index, EFFECTIVE_INFO* info);
		void (CCharacter::* SetOnShowEFST)(int value);

		void (CCharacter::* SetOffShowEFST)(int value);
		void (CCharacter::* OnChangeStatusAmount)(int in_SKLevel, unsigned short in_EFST, unsigned long in_EFST_time, int in_EFST_value);
		void (CCharacter::* NotifyStatusAmount)(unsigned short type, int amount);
		char (CCharacter::* GetCampID)(void);
		void (CCharacter::* SetCampID)(char campID);
		const char* (CActor::* GetNamePtr)(void); // __purecall
		short (CActor::* GetHealthState)(void);
		void (CActor::* ResetHealthState)(short state); // __purecall
		void (CActor::* SetEffectStateTimeInfo)(unsigned long time, int state); // __purecall
		void (CActor::* ResetEffectState)(int state); // __purecall
	};

	/* this+  0 */ public: //CCharacter baseclass_0;
	/* this+232 */ protected: int m_BodyStateValue;
	/* this+236 */ protected: unsigned long m_BodyStateTime[3];
	/* this+248 */ protected: unsigned long m_HealthStateTime[8][2]; // [health state bit] => {start time, reset time}
	/* this+312 */ protected: unsigned long m_HealthStateValue[8]; // [health state bit] => health state value
	/* this+344 */ protected: mystd::map<int,unsigned long> m_effectStateTimeL; // enum eEffectiveState => reset time

	typedef mystd::map<int,unsigned long> EFFECTSTATEMAP_ITER;

	public: CActor::CActor(void);
	public: virtual CActor::~CActor(void);
	protected: virtual void CActor::Init(void);
	public: virtual const char* CActor::GetNamePtr(void) = 0;
	public: unsigned long CActor::GetHealthStateRemainMS(const int in_HealthState);
	public: unsigned long CActor::GetBodyStateRemainMS(const int in_BodyState);
	public: virtual short CActor::GetHealthState(void);
	public: virtual void CActor::ResetHealthState(short state) = 0;
	protected: virtual void CActor::SetEffectStateTimeInfo(unsigned long time, int state) = 0;
	protected: virtual void CActor::ResetEffectState(int state) = 0;
	//protected: void CActor::SetEffectState(int);
	public: int CActor::GetStateDBFmt(unsigned char* out_pData, const int in_MaxBytes);
	public: void CActor::SetStateDBFmt(const unsigned char* in_pData, const int in_Length);
	public: int CActor::GetPlusPropertyDamage(CCharacter* other, int property, int damage);
	public: int CActor::GetModifyAttackPowerByEffective_Variation(CCharacter* ch, int attackProperty, int in_damage);
	//public: int CActor::GetSkillSPCost(const int in_SkillID, const int in_SkillLevel, CSkillTypeInfo* in_cpSkillTypeInfo);
	protected: void CActor::GetForwardPosition(int xPos, int yPos, int destDir, int distance, PosInfo& result);
	protected: int CActor::GetDirection(PosInfo src, PosInfo dest);

private:
	static hook_method<void  (CActor::*)(void)> CActor::_Init;
	static hook_method<unsigned long (CActor::*)(const int in_HealthState)> CActor::_GetHealthStateRemainMS;
	static hook_method<unsigned long (CActor::*)(const int in_BodyState)> CActor::_GetBodyStateRemainMS;
	static hook_method<short (CActor::*)(void)> CActor::_GetHealthState;
	static hook_method<int   (CActor::*)(unsigned char* out_pData, const int in_MaxBytes)> CActor::_GetStateDBFmt;
	static hook_method<void  (CActor::*)(const unsigned char* in_pData, const int in_Length)> CActor::_SetStateDBFmt;
	static hook_method<int (CActor::*)(CCharacter* other, int property, int damage)> CActor::_GetPlusPropertyDamage;
	static hook_method<int (CActor::*)(CCharacter* ch, int attackProperty, int in_damage)> CActor::_GetModifyAttackPowerByEffective_Variation;
	static hook_method<void  (CActor::*)(int xPos, int yPos, int destDir, int distance, PosInfo& result)> CActor::_GetForwardPosition;
	static hook_method<int   (CActor::*)(PosInfo src, PosInfo dest)> CActor::_GetDirection;
};
