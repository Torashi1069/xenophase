#pragma once
#include "SkillTypeInfo.h"


class SK_MONK : public CSkillTypeInfo
{
	/* this+0 */ public: //CSkillTypeInfo baseclass_0;

	//public: void Init();
	public: short SK_MONK::GetMaxLevel(void); // line ???
	public: virtual int SK_MONK::IsAvailableJob(short job); // line 139
	public: short SK_MONK::GetSPCost(short level); // line ???
	public: short SK_MONK::GetPreDelayTime(short level); // line ???

private:
	static hook_method<short (SK_MONK::*)(void)> SK_MONK::_GetMaxLevel;
	static hook_method<int (SK_MONK::*)(short job)> SK_MONK::_IsAvailableJob;
	static hook_method<short (SK_MONK::*)(short level)> SK_MONK::_GetSPCost;
	static hook_method<short (SK_MONK::*)(short level)> SK_MONK::_GetPreDelayTime;
};


class SK_MO_TRIPLEATTACK : public SK_MONK
{
	/* this+0 */ public: //SK_MONK baseclass_0;

	public: virtual void SK_MO_TRIPLEATTACK::Init(void);
	public: virtual int SK_MO_TRIPLEATTACK::OnMsg(CCharacter* sender, unsigned short receiver, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4);

private:
	static hook_method<void (SK_MO_TRIPLEATTACK::*)(void)> SK_MO_TRIPLEATTACK::_Init;
	static hook_method<int (SK_MO_TRIPLEATTACK::*)(CCharacter* sender, unsigned short receiver, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4)> SK_MO_TRIPLEATTACK::_OnMsg;
};


class SK_HIGHWIZARD : public CSkillTypeInfo
{
	struct vtable_t
	{
		//TODO
	};

	/* this+0 */ public: //CSkillTypeInfo baseclass_0;

	//public: void Init();
	public: short SK_HIGHWIZARD::GetMaxLevel(void);
	public: int SK_HIGHWIZARD::IsAvailableJob(short job); // line 829
	public: short SK_HIGHWIZARD::GetSPCost(short level);
	public: short SK_HIGHWIZARD::GetPreDelayTime(short level);

private:
	static hook_method<short (SK_HIGHWIZARD::*)(void)> SK_HIGHWIZARD::_GetMaxLevel;
	static hook_method<int (SK_HIGHWIZARD::*)(short job)> SK_HIGHWIZARD::_IsAvailableJob;
	static hook_method<short (SK_HIGHWIZARD::*)(short level)> SK_HIGHWIZARD::_GetSPCost;
	static hook_method<short (SK_HIGHWIZARD::*)(short level)> SK_HIGHWIZARD::_GetPreDelayTime;
};


class SK_HW_MAGICPOWER : public SK_HIGHWIZARD
{
	struct vtable_t
	{
		//TODO
	};

	/* this+0 */ public: //SK_HIGHWIZARD baseclass_0;

	public: void SK_HW_MAGICPOWER::Init(void);
	public: int SK_HW_MAGICPOWER::OnMsg(CCharacter* sender, unsigned short receiver, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4);
	public: short SK_HW_MAGICPOWER::GetSPCost(short level);

private:
	static hook_method<void (SK_HW_MAGICPOWER::*)(void)> SK_HW_MAGICPOWER::_Init;
	static hook_method<int (SK_HW_MAGICPOWER::*)(CCharacter* sender, unsigned short receiver, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4)> SK_HW_MAGICPOWER::_OnMsg;
	static hook_method<short (SK_HW_MAGICPOWER::*)(short level)> SK_HW_MAGICPOWER::_GetSPCost;
};
