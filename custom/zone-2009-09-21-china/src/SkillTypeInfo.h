#pragma once
#include "MSGpar.hpp"
#include "enum.hpp"
class CCharacter;


class CSkillTypeInfo
{
	struct vtable_t //const CSkillTypeInfo::`vftable'
	{
		void* (CSkillTypeInfo::* scalar_deleting_destructor)(unsigned int flags);
		void (CSkillTypeInfo::* Init)(void); //__purecall
		int (CSkillTypeInfo::* GetGNDRange)(short skLevel);
		short (CSkillTypeInfo::GetMaxLevel)(void);
		int (CSkillTypeInfo::OnMsg)(CCharacter* sender, unsigned short receiver, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4);
		short (CSkillTypeInfo::GetSPCost)(short level);
		int (CSkillTypeInfo::IsAvailableJob)(short job);
		short (CSkillTypeInfo::GetAttackRange)(int level);
		short (CSkillTypeInfo::GetPreDelayTime)(short level);
		short (CSkillTypeInfo::GetPostDelayTM)(short level);
		unsigned long (CSkillTypeInfo::GetProperty)(void);
		void (CSkillTypeInfo::SetProperty)(unsigned long property);
		short (CSkillTypeInfo::GetVersion)(void);
		bool (CSkillTypeInfo::IsEnableIgnoreMagicImmune)(int skLevel);
		int (CSkillTypeInfo::IsSpellConditionGratify)(CCharacter* in_cpSpellCH, CCharacter* in_cpTargetCH, const int in_Level, int& out_USESKILL_FAIL);
	};

	/* this+  0 */ public: //const CSkillTypeInfo::`vftable';
	/* this+  4 */ protected: int m_singlePostDelay[10];
	/* this+ 44 */ protected: int m_globalPostDelay[10];
	/* this+ 84 */ protected: int m_castFixedDelay[10];
	/* this+124 */ protected: int m_castStatDelay[10];
	/* this+164 */ protected: unsigned long m_property;
	/* this+168 */ protected: unsigned long m_flag;
	/* this+172 */ protected: unsigned short m_SKID;
	/* this+174 */ protected: unsigned short m_referSKRNG;
	/* this+176 */ protected: int m_pattern;
	/* this+180 */ protected: int m_isEventSkill;
	/* this+184 */ protected: int m_type;
	/* this+188 */ protected: short m_attackRange;
	/* this+190 */ protected: char m_name[24];
	/* this+216 */ protected: int m_dispel;
	/* this+220 */ protected: int m_joblevel;
	/* this+224 */ protected: int m_joblevel_ValidJob;
	/* this+228 */ protected: int m_GNDRange;

	public: CSkillTypeInfo::CSkillTypeInfo(void);
	public: virtual CSkillTypeInfo::~CSkillTypeInfo(void);
	public: virtual void CSkillTypeInfo::Init(void) = 0;
	//public: void CSkillTypeInfo::SetName(const char *);
	public: void CSkillTypeInfo::SetSKID(unsigned short SKID);
	//public: void SetType(int);
	//public: void SetFlag(unsigned long);
	//public: void SetReferSKRNG(unsigned short);
	public: void CSkillTypeInfo::SetPattern(int pattern);
	public: char* CSkillTypeInfo::GetName(void);
	public: unsigned short CSkillTypeInfo::GetSKID(void);
	public: int CSkillTypeInfo::GetType(void);
	public: int CSkillTypeInfo::GetPattern(void);
	public: virtual int CSkillTypeInfo::GetGNDRange(short skLevel);
	//public: unsigned long GetFlag();
	//public: unsigned short GetReferSKRNG();
	public: int CSkillTypeInfo::IsEventSkill(void);
	public: void CSkillTypeInfo::SetEventSkill(int isEventSkill);
	public: bool CSkillTypeInfo::IsNextLevelUpgradable(short level, char job);
	public: virtual short CSkillTypeInfo::GetMaxLevel(void);
	public: virtual int CSkillTypeInfo::OnMsg(CCharacter* sender, unsigned short receiver, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4);
	public: virtual short CSkillTypeInfo::GetSPCost(short level);
	public: virtual int CSkillTypeInfo::IsAvailableJob(short job);
	public: virtual short CSkillTypeInfo::GetAttackRange(int level);
	public: virtual short CSkillTypeInfo::GetPreDelayTime(short level);
	public: virtual short CSkillTypeInfo::GetPostDelayTM(short level);
	public: virtual unsigned long CSkillTypeInfo::GetProperty(void);
	public: virtual void CSkillTypeInfo::SetProperty(unsigned long property);
	//public: int IsPossibleDispel();
	//public: void SetAvailableJobLevel(int, int);
	public: int CSkillTypeInfo::GetAvailableJobLevel(void);
	public: int CSkillTypeInfo::GetAvailableJobLevel_ValidJob(void);
	public: virtual short CSkillTypeInfo::GetVersion(void);
	public: virtual bool CSkillTypeInfo::IsEnableIgnoreMagicImmune(int skLevel);
	//public: int GetSinglePostDelay(short);
	//public: int GetGlobalPostDelay(short);
	//public: void CSkillTypeInfo::SetSinglePostDelay(short, int);
	//public: void CSkillTypeInfo::SetGlobalPostDelay(short, int);
	//public: void CSkillTypeInfo::SetCastFixedDelay(short, int);
	//public: int GetCastFixedDelay(short);
	//public: void CSkillTypeInfo::SetCastStatDelay(short, int);
	//public: int GetCastStatDelay(short);
	public: virtual int CSkillTypeInfo::IsSpellConditionGratify(CCharacter* in_cpSpellCH, CCharacter* in_cpTargetCH, const int in_Level, int& out_USESKILL_FAIL) const;

private:
	static hook_method<void (CSkillTypeInfo::*)(unsigned short SKID)> CSkillTypeInfo::_SetSKID;
	static hook_method<void (CSkillTypeInfo::*)(int pattern)> CSkillTypeInfo::_SetPattern;
	static hook_method<char* (CSkillTypeInfo::*)(void)> CSkillTypeInfo::_GetName;
	static hook_method<unsigned short (CSkillTypeInfo::*)(void)> CSkillTypeInfo::_GetSKID;
	static hook_method<int (CSkillTypeInfo::*)(void)> CSkillTypeInfo::_GetType;
	static hook_method<int (CSkillTypeInfo::*)(void)> CSkillTypeInfo::_GetPattern;
	static hook_method<int (CSkillTypeInfo::*)(short skLevel)> CSkillTypeInfo::_GetGNDRange;
	static hook_method<int (CSkillTypeInfo::*)(void)> CSkillTypeInfo::_IsEventSkill;
	static hook_method<void (CSkillTypeInfo::*)(int isEventSkill)> CSkillTypeInfo::_SetEventSkill;
	static hook_method<bool (CSkillTypeInfo::*)(short level, char job)> CSkillTypeInfo::_IsNextLevelUpgradable;
	static hook_method<short (CSkillTypeInfo::*)(void)> CSkillTypeInfo::_GetMaxLevel;
	static hook_method<int (CSkillTypeInfo::*)(CCharacter* sender, unsigned short receiver, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4)> CSkillTypeInfo::_OnMsg;
	static hook_method<short (CSkillTypeInfo::*)(short level)> CSkillTypeInfo::_GetSPCost;
	static hook_method<int (CSkillTypeInfo::*)(short job)> CSkillTypeInfo::_IsAvailableJob;
	static hook_method<short (CSkillTypeInfo::*)(int level)> CSkillTypeInfo::_GetAttackRange;
	static hook_method<short (CSkillTypeInfo::*)(short level)> CSkillTypeInfo::_GetPreDelayTime;
	static hook_method<short (CSkillTypeInfo::*)(short level)> CSkillTypeInfo::_GetPostDelayTM;
	static hook_method<unsigned long (CSkillTypeInfo::*)(void)> CSkillTypeInfo::_GetProperty;
	static hook_method<void (CSkillTypeInfo::*)(unsigned long property)> CSkillTypeInfo::_SetProperty;
	static hook_method<int (CSkillTypeInfo::*)(void)> CSkillTypeInfo::_GetAvailableJobLevel;
	static hook_method<int (CSkillTypeInfo::*)(void)> CSkillTypeInfo::_GetAvailableJobLevel_ValidJob;
	static hook_method<short (CSkillTypeInfo::*)(void)> CSkillTypeInfo::_GetVersion;
	static hook_method<bool (CSkillTypeInfo::*)(int skLevel)> CSkillTypeInfo::_IsEnableIgnoreMagicImmune;
	static hook_method<int (CSkillTypeInfo::*)(CCharacter* in_cpSpellCH, CCharacter* in_cpTargetCH, const int in_Level, int& out_USESKILL_FAIL) const> CSkillTypeInfo::_IsSpellConditionGratify;
};


class SK_KNIGHT : public CSkillTypeInfo
{
public:
//	void Init();
	short GetMaxLevel()                { return 10; }
	int IsAvailableJob(short job)      { return ( job == JT_KNIGHT ); } // line 846
	short GetSPCost(short level)       { return 0; }
	short GetPreDelayTime(short level) { return 0; }
};


class SK_KN_BOWLINGBASH : public SK_KNIGHT
{
public:
//	void Init();
	int OnMsg(CCharacter* sender, unsigned short receiver, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4);
	short GetPreDelayTime(short level) { return 700; }
	short GetSPCost(short level)       { return level + 12; } // line 915
};


class SK_PRIEST : public CSkillTypeInfo
{
public:
	//void Init();
	short GetMaxLevel()                { return 10; }
	int IsAvailableJob(short job)      { return ( job == JT_PRIEST ); } // line 954
	short GetSPCost(short level)       { return 0; }
	short GetPreDelayTime(short level) { return 0; }
};


class SK_PR_SANCTUARY : public SK_PRIEST
{
public:
	//void Init();
	int OnMsg(CCharacter* sender, unsigned short receiver, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4);
	short GetSPCost(short level)       { return 3 * level + 12; }
	short GetPreDelayTime(short level) { return 5000; }
};


// line 69 at [00104920] (offset 0x504920): GetSPCost(short level) { return 0; }
// line 1737 at [001051E0] (offset 0x5051E0): GetMaxLevel() { return 10; }
