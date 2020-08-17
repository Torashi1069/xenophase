#pragma once
#include "SkillTypeInfo.h"


class SK_GD_EXTENSION : public CSkillTypeInfo
{
	struct vtable_t //const SK_GD_EXTENSION::`vftable'
	{
		void* (SK_GD_EXTENSION::* scalar_deleting_destructor)(unsigned int flags);
		void (SK_GD_EXTENSION::* Init)(void);
		int (CSkillTypeInfo::* GetGNDRange)(short skLevel);
		short (SK_GD_EXTENSION::* GetMaxLevel)(void);
		int (SK_GD_EXTENSION::* OnMsg)(CCharacter* sender, unsigned short receiver, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4);
		short (CSkillTypeInfo::* GetSPCost)(short level);
		int (SK_GD_EXTENSION::* IsAvailableJob)(short job);
		short (CSkillTypeInfo::* GetAttackRange)(int level);
		short (CSkillTypeInfo::* GetPreDelayTime)(short level);
		short (CSkillTypeInfo::* GetPostDelayTM)(short level);
		unsigned long (CSkillTypeInfo::* GetProperty)(void);
		void (CSkillTypeInfo::* SetProperty)(unsigned long property);
		short (CSkillTypeInfo::* GetVersion)(void);
		bool (CSkillTypeInfo::* IsEnableIgnoreMagicImmune)(int skLevel);
		int (CSkillTypeInfo::* IsSpellConditionGratify)(CCharacter* in_cpSpellCH, CCharacter* in_cpTargetCH, const int in_Level, int& out_USESKILL_FAIL);
	};

	/* this+0 */ public: //CSkillTypeInfo baseclass_0;

	public: virtual void SK_GD_EXTENSION::Init(void);
	public: virtual int SK_GD_EXTENSION::OnMsg(CCharacter* sender, unsigned short receiver, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4);
	public: virtual short SK_GD_EXTENSION::GetMaxLevel(void);
	public: virtual int SK_GD_EXTENSION::IsAvailableJob(short job);
	public: virtual SK_GD_EXTENSION::~SK_GD_EXTENSION(void) {};

private:
	static hook_method<void (SK_GD_EXTENSION::*)(void)> SK_GD_EXTENSION::_Init;
	static hook_method<int (SK_GD_EXTENSION::*)(CCharacter* sender, unsigned short receiver, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4)> SK_GD_EXTENSION::_OnMsg;
	static hook_method<short (SK_GD_EXTENSION::*)(void)> SK_GD_EXTENSION::_GetMaxLevel;
	static hook_method<int (SK_GD_EXTENSION::*)(short job)> SK_GD_EXTENSION::_IsAvailableJob;
};
