#pragma once
#include "SkillTypeInfo.h"


class CSkillTypeInfo2 : public CSkillTypeInfo
{
public:
	CSkillTypeInfo2();
	virtual ~CSkillTypeInfo2();

public:
	virtual void Init();
	virtual short GetMaxLevel();
	virtual int OnMsg(CCharacter* sender, unsigned short receiver, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4);
	virtual short GetAttackRange(int level);
	virtual short GetVersion();
	virtual short GetSPCost(short level);
	virtual short GetPreDelayTime(short level);
	virtual short GetPostDelayTM(short level);
	void SetMaxLevel(int level);
	int GetHitPercent(int level);
	int GetATKPercent(int level) const;
	int GetData(int type, int level) const;
	int GetSplashRange(int level);
	void GetSplashRange(int level, int& halfWidth, int& height);
	void* GetInfo(unsigned long tokenType) const;

public:
	/* this+  0 */ //CSkillTypeInfo baseclass_0;
	/* this+232 */ unsigned char m_maxLevel;
	/* this+236 */ std::map<unsigned long,void*> m_infoMap;
};
