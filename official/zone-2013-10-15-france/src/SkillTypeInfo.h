#pragma once
#include "MSGpar.h"
class CCharacter;


class CSkillTypeInfo
{
public:
	CSkillTypeInfo();
	virtual ~CSkillTypeInfo();

public:
	virtual void Init() = 0;

	void SetName(const char* name);
	void SetSKID(unsigned short SKID);
	void SetType(int type); // enumSKILLTYPE
	void SetFlag(unsigned long flag); // enumSKILLFLAG
	void SetReferSKRNG(unsigned short SKID);
	void SetPattern(int pattern); // enumSKILLPATTERN

	char* GetName();
	unsigned short GetSKID();
	int GetType(); // enumSKILLTYPE
	int GetPattern(); // enumSKILLPATTERN
	virtual int GetGNDRange(short skLevel);
	unsigned long GetFlag(); // enumSKILLFLAG
	unsigned short GetReferSKRNG();

	BOOL IsEventSkill();
	void SetEventSkill(BOOL flag);

	bool IsNextLevelUpgradable(short level, char job);

	virtual short GetMaxLevel();
	virtual int OnMsg(CCharacter* sender, unsigned short receiver, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4);
	virtual short GetSPCost(short level);
	virtual BOOL IsAvailableJob(short job);
	virtual short GetAttackRange(int level);
	virtual short GetPreDelayTime(short level);
	virtual short GetPostDelayTM(short level);

	virtual unsigned long GetProperty();
	virtual void SetProperty(unsigned long property);

	int IsPossibleDispel();

	void SetAvailableJobLevel(int validJob, int joblevel);
	int GetAvailableJobLevel();
	int GetAvailableJobLevel_ValidJob();
	virtual short GetVersion();
	virtual bool IsEnableIgnoreMagicImmune(int skLevel);

	int GetSinglePostDelay(short skLevel);
	int GetGlobalPostDelay(short skLevel);
	void SetSinglePostDelay(short skLevel, int time);
	void SetGlobalPostDelay(short skLevel, int time);
	void SetCastFixedDelay(short skLevel, int time);
	int GetCastFixedDelay(short skLevel);
	void SetCastStatDelay(short skLevel, int time);
	int GetCastStatDelay(short skLevel);

	virtual BOOL IsSpellConditionGratify(CCharacter* in_cpSpellCH, CCharacter* in_cpTarget, const int in_Level, int& out_USESKILL_FAIL) const;

	virtual std::pair<bool,int> IsSpellConditionGratify2nd(CCharacter* in_cpSpellCH, CCharacter* in_cpTargetCH, const int in_Level, const int in_spcost) const;

protected:
	/* this+  0 */ //const CSkillTypeInfo::`vftable';
	/* this+  4 */ int m_singlePostDelay[10];
	/* this+ 44 */ int m_globalPostDelay[10];
	/* this+ 84 */ int m_castFixedDelay[10];
	/* this+124 */ int m_castStatDelay[10];
	/* this+164 */ unsigned long m_property;
	/* this+168 */ unsigned long m_flag; // enumSKILLFLAG
	/* this+172 */ unsigned short m_SKID;
	/* this+174 */ unsigned short m_referSKRNG;
	/* this+176 */ int m_pattern; // enumSKILLPATTERN
	/* this+180 */ BOOL m_isEventSkill;
	/* this+184 */ int m_type; // enumSKILLTYPE
	/* this+188 */ short m_attackRange;
	/* this+190 */ char m_name[24];
	/* this+216 */ int m_dispel;
	/* this+220 */ int m_joblevel;
	/* this+224 */ int m_joblevel_ValidJob;
	/* this+228 */ int m_GNDRange;
};
