#pragma once
#include "GuildMgr.h"
#include "IGuildInfo.h"
#include "NetLib/MemoryMgr.h"
#include "std/list"
#include "std/map"
#include "std/set"


class CIGuildMgr : public CGuildMgr
{
	struct vtable_t // const CIGuildMgr::`vftable'
	{
		void* (CIGuildMgr::* vector_deleting_destructor)(unsigned int);
		void (CGuildMgr::* Init)(void);
		void (CIGuildMgr::* Init2)(int);
		CGuild* (CIGuildMgr::* AllocGuild)(void);
	};

	/* this+0x0  */ //CGuildMgr
	/* this+0x10 */ protected: unsigned long m_lastSaveTime;
	/* this+0x14 */ protected: CMemoryMgr<CIGuildInfo> m_iGuildMPool;
	/* this+0x44 */ protected: mystd::map<unsigned long,unsigned long> m_guildAIDQueue;
	/* this+0x50 */ protected: mystd::set<unsigned long> m_AgitOwnerGuildIDList;
	/* this+0x5C */ protected: mystd::list<unsigned long> m_GarbageGDID;
	/* static    */ private: static hook_ptr<CIGuildMgr*> m_cpSelf;
	/* this+0x68 */ private: bool m_bOK;

	//typedef mystd::set<unsigned long>::const_iterator AGIT_OWNER_GUILDID_CONTANIER_ITER;

	public: virtual void CIGuildMgr::Init(int MaxGuild);
	public: virtual CGuild* CIGuildMgr::AllocGuild(void);
	public: void CIGuildMgr::LogonUserA(unsigned long ZSID, unsigned long GID, unsigned long AID);
	//public: void CIGuildMgr::ChangeZoneServer(unsigned long, unsigned long, unsigned long, unsigned long);
	//public: void CIGuildMgr::AllyGuild(unsigned long, unsigned long, char *);
	//public: void CIGuildMgr::HostileGuild(unsigned long, char *);
	//public: void CIGuildMgr::OnDeleteRelatedGuild(unsigned long, unsigned long, int, int);
	//public: void CIGuildMgr::OnReqDisorganizeGuild(unsigned long, int, int, int);
	public: void CIGuildMgr::GuildAllSave(void);
	public: void CIGuildMgr::ExitUser(unsigned long ZSID, unsigned long AID, unsigned long GID);
	//public: void CIGuildMgr::ServerMoveUser(unsigned long, unsigned long, unsigned long, int);
	//public: void CIGuildMgr::MapMove(unsigned long, char *);
	public: void CIGuildMgr::ReqJoinGuild(unsigned long ZSID, unsigned long AID, unsigned long GID, unsigned long MyGID, unsigned long MyAID);
	//public: int CIGuildMgr::MakeGuild(unsigned long, unsigned long, unsigned long, unsigned long &, char *, char *, char *);
	public: CIGuildInfo* CIGuildMgr::LoadGuild(unsigned long GDID, int bNotify);
	public: void CIGuildMgr::SendPacket(unsigned long ZSID, short PacketType, unsigned long GDID, int Len, char* buf);
	public: void CIGuildMgr::ProcessAllGuild(void);
	//public: void CIGuildMgr::FreeGuild(class CIGuildInfo *, int);
	//public: void CIGuildMgr::RemoveGuildInfo(unsigned long);
	public: unsigned long CIGuildMgr::SearchAIDMap(unsigned long GID);
	public: HOOKED unsigned long CIGuildMgr::GetFreeSize(void);
	//public: void CIGuildMgr::OnChangeAgitGuild(unsigned long, unsigned long);
	public: void CIGuildMgr::GetGuildAgitDB(void);
	//public: void CIGuildMgr::SendGuildMakeResult(unsigned long, unsigned long, unsigned long, int);
	//public: void CIGuildMgr::InitZServerGuild(unsigned long, class std::list<unsigned long,std::allocator<unsigned long> > *);
	//public: void CIGuildMgr::NotifyGuild(unsigned long, unsigned long);
	public: void CIGuildMgr::OutPutGuildInfo(unsigned long GDID);
	//public: int CIGuildMgr::GetGuildInfo(unsigned long, struct PACKET_IM_REQ_GUILD_INFO *);
	//public: int CIGuildMgr::GuildInfoInit(unsigned long);
	//public: int CIGuildMgr::AllyGuildInfoInit(unsigned long);
	//private: bool CIGuildMgr::isOK();
	private: bool CIGuildMgr::Create(void);
	private: void CIGuildMgr::Destroy(void);
	private: CIGuildMgr::CIGuildMgr(void);
	private: virtual CIGuildMgr::~CIGuildMgr(void);
	public: static bool __cdecl CIGuildMgr::CreateInstance(void);
	public: static void __cdecl CIGuildMgr::DestroyInstance(void);
	public: static CIGuildMgr* CIGuildMgr::GetObj(void);

private:
	static hook_method<void (CIGuildMgr::*)(int MaxGuild)> CIGuildMgr::_Init;
	static hook_method<CGuild* (CIGuildMgr::*)(void)> CIGuildMgr::_AllocGuild;
	static hook_method<void (CIGuildMgr::*)(unsigned long ZSID, unsigned long GID, unsigned long AID)> CIGuildMgr::_LogonUserA;
	static hook_method<void (CIGuildMgr::*)(void)> CIGuildMgr::_GuildAllSave;
	static hook_method<void (CIGuildMgr::*)(unsigned long ZSID, unsigned long AID, unsigned long GID)> CIGuildMgr::_ExitUser;
	static hook_method<void (CIGuildMgr::*)(unsigned long ZSID, unsigned long AID, unsigned long GID, unsigned long MyGID, unsigned long MyAID)> CIGuildMgr::_ReqJoinGuild;
	static hook_method<CIGuildInfo* (CIGuildMgr::*)(unsigned long GDID, int bNotify)> CIGuildMgr::_LoadGuild;
	static hook_method<void (CIGuildMgr::*)(unsigned long ZSID, short PacketType, unsigned long GDID, int Len, char* buf)> CIGuildMgr::_SendPacket;
	static hook_method<void (CIGuildMgr::*)(void)> CIGuildMgr::_ProcessAllGuild;
	static hook_method<unsigned long (CIGuildMgr::*)(unsigned long GID)> CIGuildMgr::_SearchAIDMap;
	static hook_method<unsigned long (CIGuildMgr::*)(void)> CIGuildMgr::_GetFreeSize;
	static hook_method<void (CIGuildMgr::*)(void)> CIGuildMgr::_GetGuildAgitDB;
	static hook_method<void (CIGuildMgr::*)(unsigned long GDID)> CIGuildMgr::_OutPutGuildInfo;
	static hook_method<bool (CIGuildMgr::*)(void)> CIGuildMgr::_Create;
	static hook_method<void (CIGuildMgr::*)(void)> CIGuildMgr::_Destroy;
	static hook_method<static bool (__cdecl *)(void)> CIGuildMgr::_CreateInstance;
	static hook_method<static void (__cdecl *)(void)> CIGuildMgr::_DestroyInstance;
};
