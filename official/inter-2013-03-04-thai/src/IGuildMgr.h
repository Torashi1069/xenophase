#pragma once
#include "IGuildInfo.h"
#include "NetLib/MemoryMgr.h"
#include "shared/GuildMgr.h"
struct PACKET_IM_REQ_GUILD_INFO;


class CIGuildMgr : public CGuildMgr
{
public:
	virtual void Init(int MaxGuild);
	virtual CGuild* AllocGuild();
	void LogonUser(unsigned long ZSID, unsigned long GID, unsigned long AID);
	void ChangeZoneServer(unsigned long OldZSID, unsigned long NewZSID, unsigned long GID, unsigned long AID);
	void AllyGuild(unsigned long ZSID, unsigned long GDID, char* buf);
	void HostileGuild(unsigned long GDID, char* buf);
	void OnDeleteRelatedGuild(unsigned long GDID, unsigned long OpponentGDID, int Relation, BOOL bDisOrganize);
	void OnReqDisorganizeGuild(unsigned long ZSID, int GDID, int AID, int GID);
	void GuildAllSave();
	void ExitUser(unsigned long ZSID, unsigned long AID, unsigned long GID);
	void ServerMoveUser(unsigned long ZSID, unsigned long AID, unsigned long GID, BOOL isOnLine);
	void MapMove(unsigned long AID, char* mapName);
	void ReqJoinGuild(unsigned long ZSID, unsigned long AID, unsigned long GID, unsigned long MyGID, unsigned long MyAID);
	int MakeGuild(unsigned long ZSID, unsigned long AID, unsigned long GID, unsigned long& GDID, char* Name, char* GName, char* AccountName);
	CIGuildInfo* LoadGuild(unsigned long GDID, BOOL bNotify);
	void SendPacket(unsigned long ZSID, short PacketType, unsigned long GDID, int Len, char* buf);
	void ProcessAllGuild();
	void FreeGuild(CIGuildInfo* guild, BOOL disorganize);
	void RemoveGuildInfo(unsigned long GDID);
	unsigned long SearchAIDMap(unsigned long GID);
	unsigned long GetFreeSize();
	void OnChangeAgitGuild(unsigned long OldGID, unsigned long NewGID);
	void GetGuildAgitDB();
	void SendGuildMakeResult(unsigned long ZSID, unsigned long AID, unsigned long GID, int Result);
	void InitZServerGuild(unsigned long ZSID, std::list<unsigned long>* GDIDList);
	void NotifyGuild(unsigned long ZSID, unsigned long GDID);
	void OutPutGuildInfo(unsigned long GDID);
	BOOL GetGuildInfo(unsigned long GDID, PACKET_IM_REQ_GUILD_INFO* pPacket);
	BOOL GuildInfoInit(unsigned long GDID);
	BOOL AllyGuildInfoInit(unsigned long GDID);

protected:
	/* this+ 36 */ DWORD m_lastSaveTime;
	/* this+ 40 */ CMemoryMgr<CIGuildInfo> m_iGuildMPool;
	/* this+ 80 */ std::map<unsigned long,unsigned long> m_guildAIDQueue;
	typedef std::set<unsigned long> AGIT_OWNER_GUILDID_CONTANIER;
	typedef std::set<unsigned long>::iterator AGIT_OWNER_GUILDID_CONTANIER_ITER;
	/* this+112 */ AGIT_OWNER_GUILDID_CONTANIER m_AgitOwnerGuildIDList;
	/* this+144 */ std::list<unsigned long> m_GarbageGDID;
private:
	/* static   */ static CIGuildMgr*& m_cpSelf; //TODO
	/* this+172 */ private: bool m_bOK;

private:
	bool isOK() const;
	bool Create();
	void Destroy();

private:
	CIGuildMgr();
	virtual ~CIGuildMgr();

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CIGuildMgr* GetObj(); /// @custom
};
