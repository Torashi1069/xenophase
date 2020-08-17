#pragma once
#include "structs.hpp"
#include "NetLib/MemoryMgr.h"
#include "std/vector"
#define GUILDSKILL_BUFSIZE 300


class CGuild
{
	struct vtable_t
	{
		void* (CGuild::* scalar_deleting_destructor)(unsigned int);
		void (CGuild::* Init)(void);
	};

	/* this+0x0   */ //const CGuild::`vftable'
	/* this+0x4   */ protected: int m_GDID;
	/* this+0x8   */ protected: int m_level;
	/* this+0xC   */ protected: char m_guildName[24];
	/* this+0x24  */ protected: char m_guildMasterName[24];
	/* this+0x3C  */ protected: int m_maxUserNum;
	/* this+0x40  */ protected: int m_userNum;
	/* this+0x44  */ protected: int m_honor;
	/* this+0x48  */ protected: int m_virtue;
	/* this+0x4C  */ protected: int m_type;
	/* this+0x50  */ protected: int m_class;
	/* this+0x54  */ protected: int m_money;
	/* this+0x58  */ protected: int m_arenaWin;
	/* this+0x5C  */ protected: int m_arenaLose;
	/* this+0x60  */ protected: int m_arenaDrawn;
	/* this+0x64  */ protected: char m_manageLand[24];
	/* this+0x7C  */ protected: int m_exp;
	/* this+0x80  */ protected: int m_emblemVersion;
	/* this+0x84  */ protected: int m_point;
	/* this+0x88  */ protected: char m_desc[80];
	/* this+0xD8  */ protected: int m_isEmblemLoad;
	/* this+0xDC  */ protected: int m_emblemSize;
	/* this+0xE0  */ protected: GUILDNOTICE m_guildNotice;
	/* this+0x198 */ protected: char m_guildEmblem[3072];
	/* this+0xD98 */ protected: mystd::vector<GUILDMINFO*> m_guildMInfo;
	/* this+0xDA8 */ protected: mystd::vector<GUILDALLYINFO*> m_guildAllyInfo;
	/* this+0xDB8 */ protected: mystd::vector<GUILDBANISHINFO*> m_guildBanishInfo;
	/* this+0xDC8 */ protected: mystd::vector<GUILDMPOSITION*> m_guildMPosition;
	/* this+0xDD8 */ protected: CMemoryMgr<GUILDMINFO> m_GuildMInfoMPool;
	/* this+0xE08 */ protected: CMemoryMgr<GUILDALLYINFO> m_GuildAllyInfoMPool;
	/* this+0xE38 */ protected: CMemoryMgr<GUILDBANISHINFO> m_GuildBanishInfoMPool;
	/* this+0xE68 */ protected: CMemoryMgr<GUILDMPOSITION> m_GuildMPositionMPool;
	/* this+0xE98 */ protected: int m_skillDataLength;
	/* this+0xE9C */ protected: int m_skillPoint;
	/* this+0xEA0 */ protected: unsigned char m_skillData[GUILDSKILL_BUFSIZE];

	//public: int CGuild::FindBanishMember(int);
	//public: void CGuild::UpdateMemberStatus(int, int, short, int, short, short, short);
	//public: void CGuild::UpdateMemberJob_Level(int, int, int);
	//public: void CGuild::UpdateMemberChangePos(unsigned long, unsigned long);
	//public: void CGuild::UpdateMemberPosition(unsigned long, char *, int, int, int);
	//public: int CGuild::FindAllyGuild(unsigned long);
	//public: int CGuild::FindHostileGuild(unsigned long);
	//public: int CGuild::IsMaster(unsigned long);
	public: int CGuild::GetPosJoinRight(unsigned long PosID);
	//public: int CGuild::GetPosPenaltyRight(unsigned long);
	//public: int CGuild::GetAllyCount();
	//public: int CGuild::GetHostileCount();
	//public: void CGuild::GetGuildInfo(struct GUILDINFO &);
	//public: void CGuild(const class CGuild &);
	public: CGuild::CGuild(void);
	public: virtual CGuild::~CGuild(void);
	public: virtual void CGuild::Init(void);
	//public: void CGuild::DeleteMPosition();
	//public: void CGuild::DeleteBanishInfo();
	//public: void CGuild::DeleteMInfo();
	//public: void CGuild::DeleteAllyInfo();
	//public: int CGuild::DeleteFirstBanishInfo();
	//public: void CGuild::ClearAll();
	//public: void CGuild::SetGuildMasterName(char *);
	//public: void CGuild::SetGuildName(char *);
	//public: void CGuild::SetGuildInfo(struct GUILDINFO *);
	//public: void CGuild::SetEmblemVersion(int);
	//public: void CGuild::SetGuildLevel(int);
	public: void CGuild::SetMaxUserNum(int Num);
	//public: void CGuild::SetGuildExp(int);
	//public: void CGuild::SetGDID(unsigned long);
	//public: void SetEmblemLoad(int);
	//public: void SetLevel(int);
	//public: void SetSkillPoint(int);
	//public: void CGuild::SetSkillData(const unsigned char *, const int);
	//public: int CGuild::GetGuildMemberOnline();
	//public: char * CGuild::GetPosName(unsigned long);
	//public: char * CGuild::GetMemberName(unsigned long);
	//public: int CGuild::GetMemberExp(unsigned long);
	//public: int CGuild::GetMemberLevel(unsigned long);
	//public: int CGuild::GetMemberClass(unsigned long);
	//public: void CGuild::GetGuildPosID(char *);
	public: int CGuild::GetGuildPosID(unsigned long GID);
	//public: int CGuild::isJoinRight(unsigned long);
	//public: int CGuild::isPenaltyRight(unsigned long);
	public: void CGuild::AddGuildMInfo(GUILDMINFO* Info);
	//public: void CGuild::AddGuildAllyInfo(struct GUILDALLYINFO *);
	//public: void CGuild::AddGuildBanishInfo(struct GUILDBANISHINFO *);
	//public: void CGuild::AddGuildMPosition(struct GUILDMPOSITION *);
	//public: int CGuild::GetAverageLevel();
	public: int CGuild::GetGuildMSize(void);
	//public: int GetGuildMAllocSize();
	//public: int CGuild::FindMember(unsigned long);
	//public: int CGuild::GetGuildAllySize();
	//public: int CGuild::GetGuildBanishSize();
	//public: int CGuild::GetGuildMPosSize();
	//public: int CGuild::UpdateMoney(int, int);
	public: GUILDMINFO* CGuild::AllocGuildMInfo(void);
	public: GUILDALLYINFO* CGuild::AllocGuildAllyInfo(void);
	public: GUILDBANISHINFO* CGuild::AllocGuildBanishInfo(void);
	public: GUILDMPOSITION* CGuild::AllocGuildMPosition(void);
	//public: void CGuild::DeleteGuildAllyInfo(unsigned long, int);
	//public: void CGuild::DeleteGuildBanishInfo(unsigned long);
	//public: void CGuild::DeleteGuildMInfo(unsigned long);
	//public: int CGuild::AddGuildExp(unsigned long, int);
	//public: int CGuild::GetServiceRate(unsigned long);
	//public: void CGuild::GetGuildMemberInfo(unsigned long, struct GUILD_MEMBER_INFO &);
	//public: void CGuild::GetGuildBanishInfo(char *);
	//public: void CGuild::GetGuildAllyInfo(char *);
	//public: void CGuild::GetGuildMPosition(char *);
	public: void CGuild::InitGuildMInfo(GUILDMINFO* Guild, char* Name, char* Account, unsigned long AID, unsigned long GDID, unsigned long GID, int Position, int Stat, int Level, int Class);
	public: void CGuild::InitGuildMInfo(GUILDMINFO* Guild, char* Name, char* Account, unsigned long AID, unsigned long GDID, unsigned long GID, int Position, int Stat, int Level, int Job, int head, int headpal, int sex);
	//public: int CGuild::GetGDID();
	//public: int CGuild::GetLevel();
	//public: char * CGuild::GetGuildName();
	//public: char * CGuild::GetMasterName();
	public: int CGuild::GetMaxUserNum(void);
	//public: int CGuild::GetHonor();
	//public: int CGuild::GetVirtue();
	//public: int CGuild::GetType();
	//public: int CGuild::GetClass();
	//public: int CGuild::GetMoney();
	//public: int CGuild::GetArenaWin();
	//public: int CGuild::GetArenaLose();
	//public: int CGuild::GetArenaDrawn();
	//public: char * CGuild::GetManageLand();
	//public: int CGuild::GetExp();
	//public: int CGuild::GetEmblemVersion();
	//public: int CGuild::GetPoint();
	//public: char * CGuild::GetDesc();
	//public: char * GetNotice();
	//public: char * GetNoticeSubject();
	//public: void CGuild::UpdateNotice(const unsigned long, class std::basic_string<char,std::char_traits<char>,std::allocator<char> > &, class std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
	//public: char * GetEmblem();
	//public: int IsEmblemLoad();
	//public: int GetEmblemSize();
	//protected: void CGuild::SetMoney(int);
	//protected: int CGuild::AddMoney(int);

private:
	static hook_method<int (CGuild::*)(unsigned long PosID)> CGuild::_GetPosJoinRight;
	static hook_method<void (CGuild::*)(void)> CGuild::_Init;
	static hook_method<void (CGuild::*)(int Num)> CGuild::_SetMaxUserNum;
	static hook_method<int (CGuild::*)(unsigned long GID)> CGuild::_GetGuildPosID;
	static hook_method<void (CGuild::*)(GUILDMINFO* Info)> CGuild::_AddGuildMInfo;
	static hook_method<int (CGuild::*)(void)> CGuild::_GetGuildMSize;
	static hook_method<GUILDMINFO* (CGuild::*)(void)> CGuild::_AllocGuildMInfo;
	static hook_method<GUILDALLYINFO* (CGuild::*)(void)> CGuild::_AllocGuildAllyInfo;
	static hook_method<GUILDBANISHINFO* (CGuild::*)(void)> CGuild::_AllocGuildBanishInfo;
	static hook_method<GUILDMPOSITION* (CGuild::*)(void)> CGuild::_AllocGuildMPosition;
	static hook_method<void (CGuild::*)(GUILDMINFO* Guild, char* Name, char* Account, unsigned long AID, unsigned long GDID, unsigned long GID, int Position, int Stat, int Level, int Class)> CGuild::_InitGuildMInfo;
	static hook_method<void (CGuild::*)(GUILDMINFO* Guild, char* Name, char* Account, unsigned long AID, unsigned long GDID, unsigned long GID, int Position, int Stat, int Level, int Job, int head, int headpal, int sex)> CGuild::_InitGuildMInfo2;
	static hook_method<int (CGuild::*)(void)> CGuild::_GetMaxUserNum;
};
