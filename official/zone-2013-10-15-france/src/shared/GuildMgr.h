#pragma once
#include "shared/Guild.h"


class CGuildMgr
{
public:
	CGuild* SearchGuild(unsigned long GDID);

public:
	CGuildMgr();
	virtual ~CGuildMgr();
	virtual void Init();

public:
	void ClearGuildInfo();
	BOOL AddGuild(CGuild* guild);
	unsigned long GetGuildSize();

protected:
	/* this+0 */ //const CGuildMgr::`vftable';
	/* this+4 */ std::map<unsigned long,CGuild*> m_guildInfo;
};
