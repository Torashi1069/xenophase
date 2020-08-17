#pragma once
#include "Enum.h"
#include "SkillTypeInfo.h"


class SK_ROGUE : public CSkillTypeInfo
{
public:
	virtual void Init() = 0;
	virtual short GetMaxLevel();
	virtual BOOL IsAvailableJob(short job);
	virtual short GetSPCost(short level);
	virtual short GetPreDelayTime(short level);
};


class SK_RG_PLAGIARISM : public SK_ROGUE
{
public:
	union DATA
	{
	public:
		struct {
			/* this(bf)+0: 0 len(16) */ int SKID    : 16;
			/* this(bf)+0:16 len( 8) */ int SKLevel : 8;
			/* this(bf)+0:24 len( 8) */ int unused  : 8;
		} Imitation;

	private:
		int value;

	public:
		operator int() { return value; }
		DATA(const int in_value) { value = in_value; }
		DATA(const int in_SKID, const int in_SKLevel) { Imitation.SKID = in_SKID; Imitation.SKLevel = in_SKLevel; }
	};

public:
	virtual void Init();
	virtual int OnMsg(CCharacter* sender, unsigned short receiver, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4);
	virtual short GetMaxLevel();
};


class SK_DANCER : public CSkillTypeInfo
{
public:
	virtual void Init() = 0;
	virtual short GetMaxLevel();
	virtual BOOL IsAvailableJob(short job);
	virtual short GetSPCost(short level);
	virtual short GetPreDelayTime(short level);
};


class SK_DC_SCREAM : public SK_DANCER
{
public:
	virtual void Init();
	virtual int OnMsg(CCharacter* sender, unsigned short receiver, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4);
	virtual short GetMaxLevel();
	virtual short GetSPCost(short level);
};
