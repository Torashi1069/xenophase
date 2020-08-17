#pragma once
#include "ZGuildInfo.h"
#include "NetLib/MemoryMgr.h"
#include "shared/GuildMgr.h"


class CZGuildMgr : public CGuildMgr
{
public:
	CZGuildMgr();
	virtual ~CZGuildMgr();

public:
	void AddGuildExp(unsigned long GDID, unsigned long GID, int Exp);
	void SendPacket(const unsigned long in_GDID, const short in_PacketType, const int in_Len, const char* in_pBuffer);
	void MakeGuild(unsigned long GDID, GUILDINFO* Info);
	void Init(int Max_Guild);
	virtual void Init();
	virtual CGuild* AllocGuild();
	virtual void FreeGuild(CGuild* guild, BOOL disorganize);
	void AddAgitGuild(unsigned long GDID);
	void OnChangeAgitGuild(const char* mapName, unsigned long a, unsigned long b);
	int GetGuildSkillLevel(unsigned long GDID, unsigned short SKID);
	unsigned long GetFreeSize();
	unsigned long GetOffset();
	BOOL JoinInsertGID(unsigned long GDID, unsigned long GID);
	BOOL JoinChkeckGID(unsigned long GDID, unsigned long GID);
	BOOL isAgitGuild(unsigned long GDID);

protected:
	/* this+ 0 */ //CGuildMgr baseclass_0;
	/* this+20 */ CMemoryMgr<CZGuildInfo> m_zGuildMPool;
	/* this+56 */ std::set<unsigned long> m_set;
	/* this+72 */ int m_MaxGuildCounter;
};
