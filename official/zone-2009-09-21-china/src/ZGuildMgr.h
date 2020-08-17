#pragma once
#include "GuildMgr.h"
#include "ZGuildInfo.h"
#include "NetLib/MemoryMgr.h"
#include "std/set"


class CZGuildMgr : public CGuildMgr
{
	struct vtable_t // const CZGuildMgr::`vftable'
	{
		void* (CZGuildMgr::* scalar_deleting_destructor)(unsigned int flags);
		void (CZGuildMgr::* Init)(void);
		CGuild* (CZGuildMgr::* AllocGuild)(void);
		void (CZGuildMgr::* FreeGuild)(CGuild* guild, int disorganize);
	};

	/* this+ 0 */ public: //CGuildMgr baseclass_0;
	/* this+16 */ protected: CMemoryMgr<CZGuildInfo> m_zGuildMPool;
	/* this+64 */ protected: mystd::set<unsigned long> m_set;
	/* this+76 */ protected: int m_MaxGuildCounter;

	public: CZGuildMgr::CZGuildMgr(void);
	public: virtual CZGuildMgr::~CZGuildMgr(void);
	public: void CZGuildMgr::AddGuildExp(unsigned long GDID, unsigned long GID, int Exp);
	public: void CZGuildMgr::SendPacket(unsigned long GDID, short PacketType, int Len, char* buf);
	public: void CZGuildMgr::MakeGuild(unsigned long GDID, GUILDINFO* Info);
	public: virtual void CZGuildMgr::Init(void);
	public: void CZGuildMgr::Init(int Max_Guild);
	public: virtual CGuild* CZGuildMgr::AllocGuild(void);
	public: virtual void CZGuildMgr::FreeGuild(CGuild* guild, int disorganize);
	public: void CZGuildMgr::AddAgitGuild(unsigned long GDID);
	public: void CZGuildMgr::OnChangeAgitGuild(const char* mapName, unsigned long a, unsigned long b);
	public: int CZGuildMgr::GetGuildSkillLevel(unsigned long GDID, unsigned short SKID);
	public: unsigned long CZGuildMgr::GetFreeSize(void);
	public: unsigned long CZGuildMgr::GetOffset(void);
	public: int CZGuildMgr::JoinInsertGID(unsigned long GDID, unsigned long GID);
	public: int CZGuildMgr::JoinChkeckGID(unsigned long GDID, unsigned long GID);
	public: int CZGuildMgr::isAgitGuild(unsigned long GDID);
	private: void CZGuildMgr::GetGuildEmblem(char* buf, unsigned short Len);
	private: void CZGuildMgr::GetFileNames(mystd::list<mystd::string>& fileNameList, const char* path, const char* szFileName_wildcard);

private:
	static hook_method<void (CZGuildMgr::*)(unsigned long GDID, unsigned long GID, int Exp)> CZGuildMgr::_AddGuildExp;
	static hook_method<void (CZGuildMgr::*)(unsigned long GDID, short PacketType, int Len, char* buf)> CZGuildMgr::_SendPacket;
	static hook_method<void (CZGuildMgr::*)(unsigned long GDID, GUILDINFO* Info)> CZGuildMgr::_MakeGuild;
	static hook_method<void (CZGuildMgr::*)(void)> CZGuildMgr::_Init;
	static hook_method<void (CZGuildMgr::*)(int Max_Guild)> CZGuildMgr::_Init2;
	static hook_method<CGuild* (CZGuildMgr::*)(void)> CZGuildMgr::_AllocGuild;
	static hook_method<void (CZGuildMgr::*)(CGuild* guild, int disorganize)> CZGuildMgr::_FreeGuild;
	static hook_method<void (CZGuildMgr::*)(unsigned long GDID)> CZGuildMgr::_AddAgitGuild;
	static hook_method<void (CZGuildMgr::*)(const char* mapName, unsigned long a, unsigned long b)> CZGuildMgr::_OnChangeAgitGuild;
	static hook_method<int (CZGuildMgr::*)(unsigned long GDID, unsigned short SKID)> CZGuildMgr::_GetGuildSkillLevel;
	static hook_method<unsigned long (CZGuildMgr::*)(void)> CZGuildMgr::_GetFreeSize;
	static hook_method<unsigned long (CZGuildMgr::*)(void)> CZGuildMgr::_GetOffset;
	static hook_method<int (CZGuildMgr::*)(unsigned long GDID, unsigned long GID)> CZGuildMgr::_JoinInsertGID;
	static hook_method<int (CZGuildMgr::*)(unsigned long GDID, unsigned long GID)> CZGuildMgr::_JoinChkeckGID;
	static hook_method<int (CZGuildMgr::*)(unsigned long GDID)> CZGuildMgr::_isAgitGuild;
	static hook_method<void (CZGuildMgr::*)(char* buf, unsigned short Len)> CZGuildMgr::_GetGuildEmblem;
	static hook_method<void (CZGuildMgr::*)(mystd::list<mystd::string>& fileNameList, const char* path, const char* szFileName_wildcard)> CZGuildMgr::_GetFileNames;
};
