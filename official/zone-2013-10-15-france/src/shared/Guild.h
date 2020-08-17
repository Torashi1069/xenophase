#pragma once
#include "NetLib/MemoryMgr.h"


enum enumRELATEDGUILDTYPE
{
	RELATED_GUILD_TYPE_ALLY  = 0,
	RELATED_GUILD_TYPE_ENEMY = 1,
};


enum enumZENYMODIFYTYPE
{
	ZENY_MODIFYTYPE_SET    = 0,
	ZENY_MODIFYTYPE_GET    = 1,
	ZENY_MODIFYTYPE_UPDATE = 2,
};


enum enumZENYUPDATERESULT
{
	ZENY_UPDATE_SUCCESS      = 1,
	ZENY_UPDATE_FAIL_MINIMUM = 2,
	ZENY_UPDATE_FAIL_MAXIMUM = 3,
	ZENY_UPDATE_FAIL_PLAYER  = 4,
};


#pragma pack(push,1)
///

struct GUILDINFO
{
	/* this+  0 */ int GDID;
	/* this+  4 */ int Level;
	/* this+  8 */ char Name[24];
	/* this+ 32 */ char MName[24];
	/* this+ 56 */ int MaxUserNum;
	/* this+ 60 */ int UserNum;
	/* this+ 64 */ int Honor;
	/* this+ 68 */ int Virtue;
	/* this+ 72 */ int Type;
	/* this+ 76 */ int Class;
	/* this+ 80 */ int Money;
	/* this+ 84 */ int ArenaWin;
	/* this+ 88 */ int ArenaLose;
	/* this+ 92 */ int ArenaDrawn;
	/* this+ 96 */ char ManageLand[24];
	/* this+120 */ int Exp;
	/* this+124 */ int EmblemVersion;
	/* this+128 */ int Point;
	/* this+132 */ char Desc[80];
};


struct GUILDNOTICE
{
	/* this+ 0 */ int GDID;
	/* this+ 4 */ char Subject[60];
	/* this+64 */ char Notice[120];
};


struct GUILDMINFO
{
	/* this+  0 */ int GID;
	/* this+  4 */ char CharName[24];
	/* this+ 28 */ char AccountName[24];
	/* this+ 52 */ int Level;
	/* this+ 56 */ char Memo[50];
	/* this+106 */ int Service;
	/* this+110 */ int MemberExp;
	/* this+114 */ int GDID;
	/* this+118 */ int AID;
	/* this+122 */ int PositionID;
	/* this+126 */ short head;
	/* this+128 */ short headPalette;
	/* this+130 */ short sex;
	/* this+132 */ int job;
	/* this+136 */ int status;
};


struct GUILDALLYINFO
{
	/* this+ 0 */ int GDID;
	/* this+ 4 */ int OpponentGDID;
	/* this+ 8 */ char GuildName[24];
	/* this+32 */ int Relation; // enumRELATEDGUILDTYPE
};


struct GUILDBANISHINFO
{
	/* this+  0 */ int GDID;
	/* this+  4 */ char MemberName[24];
	/* this+ 28 */ char MemberAccount[24];
	/* this+ 52 */ char Reason[50];
	/* this+102 */ int GID;
	/* this+106 */ int AID;
};


struct GUILDMPOSITION
{
	/* this+ 0 */ int GDID;
	/* this+ 4 */ int Grade;
	/* this+ 8 */ char PosName[24];
	/* this+32 */ BOOL JoinRight;
	/* this+36 */ BOOL PenaltyRight;
	/* this+40 */ int PositionID;
	/* this+44 */ int Service;
};


/// @see PACKET_ZC_MEMBER_ADD, etc
struct GUILD_MEMBER_INFO
{
	/* this+ 0 */ int AID;
	/* this+ 4 */ int GID;
	/* this+ 8 */ short head;
	/* this+10 */ short headPalette;
	/* this+12 */ short sex;
	/* this+14 */ short job;
	/* this+16 */ short level;
	/* this+18 */ int contributionExp;
	/* this+22 */ int currentState;
	/* this+26 */ int positionID;
	/* this+30 */ char intro[50];
	/* this+80 */ char charname[24];
};


/// @see PACKET_ZI_REQ_CHANGE_MEMBERPOS, PACKET_IZ_ACK_CHANGE_MEMBERPOS
struct MEMBER_POSITION_INFO
{
	/* this+0 */ int AID;
	/* this+4 */ int GID;
	/* this+8 */ int positionID;
};


struct MEMBER_POSITION_ID_NAME_INFO
{
	/* this+0 */ int positionID;
	/* this+4 */ char posName[24];
};


struct GUILD_POSITION_INFO
{
	/* this+ 0 */ int positionID;
	/* this+ 4 */ int right;
	/* this+ 8 */ int ranking;
	/* this+12 */ int payRate;
};


/// @see PACKET_ZI_REQ_GUILD_POSITION_INFO, PACKET_IZ_ACK_GUILD_POSITION_INFO
struct GUILD_REG_POSITION_INFO
{
	/* this+ 0 */ int positionID;
	/* this+ 4 */ int right;
	/* this+ 8 */ int ranking;
	/* this+12 */ int payRate;
	/* this+16 */ char posName[24];
};


struct RELATED_GUILD_INFO
{
	/* this+0 */ int relation;
	/* this+4 */ int GDID;
	/* this+8 */ char guildname[24];
};


struct GUILD_BAN_INFO
{
	/* this+ 0 */ char charname[24];
	/* this+24 */ char account[24];
	/* this+48 */ char reason[40];
};

///
#pragma pack(pop)


class CGuild
{
public:
	BOOL FindBanishMember(int GID);
	void UpdateMemberStatus(int Stat, int GID, short job, int Level, short sex, short head, short headpal);
	void UpdateMemberJob_Level(int GID, int Job, int Level);
	void UpdateMemberChangePos(unsigned long GID, unsigned long PosID);
	void UpdateMemberPosition(unsigned long PositionID, char* Name, int Service, BOOL Join, BOOL Penalty);
	BOOL FindAllyGuild(unsigned long GDID);
	BOOL FindHostileGuild(unsigned long GDID);
	BOOL IsMaster(unsigned long GID);
	BOOL GetPosJoinRight(unsigned long PosID);
	BOOL GetPosPenaltyRight(unsigned long PosID);
	int GetAllyCount();
	int GetHostileCount();
	void GetGuildInfo(GUILDINFO& Guild);

public:
	CGuild();
	virtual ~CGuild();
	virtual void Init();

public:
	void DeleteMPosition();
	void DeleteBanishInfo();
	void DeleteMInfo();
	void DeleteAllyInfo();
	int DeleteFirstBanishInfo();
	void ClearAll();
	void SetGuildMasterName(char* Name);
	void SetGuildName(char* GName);
	void SetGuildInfo(GUILDINFO* Info);
	void SetGuildLevel(int Level);
	void SetMaxUserNum(int Num);
	void SetGuildExp(int Exp);
	void SetGDID(unsigned long GDID);
	void SetLevel(int ); //TODO
	void SetSkillPoint(int ); //TODO
	void SetSkillData(const BYTE* in_DataPtr, const int in_DataLength);
	int GetGuildMemberOnline();
	char* GetPosName(unsigned long PosID);
	char* GetMemberName(unsigned long GID);
	int GetMemberExp(unsigned long GID);
	int GetMemberLevel(unsigned long GID);
	int GetMemberClass(unsigned long GID);
	int GetGuildPosID(unsigned long GID);
	void GetGuildPosID(char* Buf, const int in_nMaxBufSize);
	BOOL isJoinRight(unsigned long GID);
	BOOL isPenaltyRight(unsigned long GID);
	void AddGuildMInfo(GUILDMINFO* pMember);
	void AddGuildAllyInfo(GUILDALLYINFO* Info);
	void AddGuildBanishInfo(GUILDBANISHINFO* Info);
	void AddGuildMPosition(GUILDMPOSITION* Info);
	int GetAverageLevel();
	int GetGuildMSize();
	int GetGuildMAllocSize(); //TODO
	BOOL FindMember(unsigned long GID);
	int GetGuildAllySize();
	int GetGuildBanishSize();
	int GetGuildMPosSize();
	int UpdateMoney(int Amount, int Type);
	GUILDMINFO* AllocGuildMInfo();
	GUILDALLYINFO* AllocGuildAllyInfo();
	GUILDBANISHINFO* AllocGuildBanishInfo();
	GUILDMPOSITION* AllocGuildMPosition();
	void DeleteGuildAllyInfo(unsigned long GDID, int Type);
	void DeleteGuildBanishInfo(unsigned long GID);
	void DeleteGuildMInfo(unsigned long GID);
	int AddGuildExp(unsigned long GID, int Exp);
	int GetServiceRate(unsigned long PositionID);
	void GetGuildMemberInfo(unsigned long GID, GUILD_MEMBER_INFO& Info);
	void GetGuildBanishInfo(char* Buf, const int in_nMaxBufSize);
	void GetGuildAllyInfo(char* Buf, const int in_nMaxBufSize);
	void GetGuildMPosition(char* Buf, const int in_nMaxBufSize);
	void InitGuildMInfo(GUILDMINFO* Guild, char* Name, char* Account, unsigned long AID, unsigned long GDID, unsigned long GID, int Position, int Stat, int Level, int Job, int head, int headpal, int sex);
	void InitGuildMInfo(GUILDMINFO* Guild, char* Name, char* Account, unsigned long AID, unsigned long GDID, unsigned long GID, int Position, int Stat, int Level, int Class);
	int GetGDID();
	int GetLevel();
	char* GetGuildName();
	char* GetMasterName();
	int GetMaxUserNum();
	int GetHonor();
	int GetVirtue();
	int GetType();
	int GetClass();
	int GetMoney();
	int GetArenaWin();
	int GetArenaLose();
	int GetArenaDrawn();
	char* GetManageLand();
	int GetExp();
	int GetPoint();
	char* GetDesc();
	char* GetNotice();
	char* GetNoticeSubject();
	void UpdateNotice(const unsigned long in_GuildID, std::string& in_Subject, std::string& in_Notice);
	void SetEmblemVersion(int Ver);
	void SetEmblemLoad(int ); //TODO
	char* GetEmblem(); //TODO
	int GetEmblemVersion();
	int IsEmblemLoad(); //TODO
	int GetEmblemSize(); //TODO

protected:
	/* this+   0 */ //const CGuild::`vftable';
	/* this+   4 */ int m_GDID;
	/* this+   8 */ int m_level;
	/* this+  12 */ char m_guildName[24];
	/* this+  36 */ char m_guildMasterName[24];
	/* this+  60 */ int m_maxUserNum;
	/* this+  64 */ int m_userNum;
	/* this+  68 */ int m_honor;
	/* this+  72 */ int m_virtue;
	/* this+  76 */ int m_type;
	/* this+  80 */ int m_class;
	/* this+  84 */ int m_money;
	/* this+  88 */ int m_arenaWin;
	/* this+  92 */ int m_arenaLose;
	/* this+  96 */ int m_arenaDrawn;
	/* this+ 100 */ char m_manageLand[24];
	/* this+ 124 */ int m_exp;
	/* this+ 128 */ int m_point;
	/* this+ 132 */ char m_desc[80];
	/* this+ 212 */ GUILDNOTICE m_guildNotice;
	/* this+ 396 */ char m_guildEmblem[3072];
	/* this+3468 */ int m_isEmblemLoad;
	/* this+3472 */ int m_emblemSize;
	/* this+3476 */ int m_emblemVersion;
	/* this+3480 */ std::vector<GUILDMINFO*> m_guildMInfo;
	/* this+3496 */ std::vector<GUILDALLYINFO*> m_guildAllyInfo;
	/* this+3512 */ std::vector<GUILDBANISHINFO*> m_guildBanishInfo;
	/* this+3528 */ std::vector<GUILDMPOSITION*> m_guildMPosition;
	/* this+3544 */ CMemoryMgr<GUILDMINFO> m_GuildMInfoMPool;
	/* this+3580 */ CMemoryMgr<GUILDALLYINFO> m_GuildAllyInfoMPool;
	/* this+3616 */ CMemoryMgr<GUILDBANISHINFO> m_GuildBanishInfoMPool;
	/* this+3652 */ CMemoryMgr<GUILDMPOSITION> m_GuildMPositionMPool;
	void SetMoney(int Money);
	int AddMoney(int Money);
	/* this+3688 */ int m_skillDataLength;
	/* this+3692 */ int m_skillPoint;
	/* this+3696 */ BYTE m_skillData[300];
};
