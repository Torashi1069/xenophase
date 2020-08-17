#pragma once
#include "SkillTypeInfo2.h"


class SK_NC_MAINFRAME : public CSkillTypeInfo2
{
public:
	virtual int OnMsg(CCharacter* sender, unsigned short receiver, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4);
	static int GetExpireOverHeatLimitPoint(CPC* in_cpPlayer);

private:
	int GetIncDEFamount(const int in_Level) const;
	int GetAdditionalMaxOverHeatLimitPoint(const int in_Level) const;
};
