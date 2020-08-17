#pragma once
#include "GuildDB.h"
#include "std/map"
struct GUILDMINFO;


class CIGuildInfoDB : public CGuildDB
{
	/* this+0x0  */ //CGuildDB
	/* this+0x20 */ protected: mystd::map<int,char*> m_inputProcTable;

	//public: int CIGuildInfoDB::DeleteAllGuildMPosition(unsigned long);
	//public: int CIGuildInfoDB::DeleteAllGuildBanish(unsigned long);
	//public: int CIGuildInfoDB::DeleteAllGuildAllyInfo(unsigned long);
	//public: int CIGuildInfoDB::DeleteGuildMInfo(unsigned long);
	//public: int CIGuildInfoDB::DeleteGuildInfoDB(unsigned long);
	//public: int CIGuildInfoDB::DeleteGuildNotice(unsigned long);
	//public: int CIGuildInfoDB::DeleteGuildAllyInfo(unsigned long, unsigned long, int);
	//public: int CIGuildInfoDB::DeleteGuildBanishInfo(unsigned long, unsigned long);
	//public: int CIGuildInfoDB::DeleteGuildSkill(unsigned long);
	public: unsigned long CIGuildInfoDB::GetGDID(unsigned long GID);
	//public: void CIGuildInfoDB::CIGuildInfoDB();
	//public: void CIGuildInfoDB::~CIGuildInfoDB();
	//public: void CIGuildInfoDB::InitStoredProcTable();
	//public: int CIGuildInfoDB::MakeGuild(unsigned long, unsigned long, unsigned long &, char *, char *);
	//public: int CIGuildInfoDB::UpdateTableDWORD(unsigned long, unsigned long, int);
	//public: int CIGuildInfoDB::UpdateTableChar(unsigned long, char *, int);
	//public: int CIGuildInfoDB::UpdateGuildInfoDB(class CIGuildInfo &);
	//public: int CIGuildInfoDB::UpdateGuildMInfo(struct GUILDMINFO &);
	//public: int CIGuildInfoDB::UpdateMemberPos(unsigned long, struct GUILD_REG_POSITION_INFO &, int, int);
	//public: int CIGuildInfoDB::UpdateMemberChangePos(unsigned long, unsigned long, unsigned long);
	//public: int CIGuildInfoDB::UpdateGuildEmblem(unsigned long, unsigned long);
	//public: int CIGuildInfoDB::UpdateGuildNotice(unsigned long, char *, char *);
	//public: int CIGuildInfoDB::UpdateGuildMember(unsigned long, unsigned long, unsigned long, unsigned long, int, int);
	public: int CIGuildInfoDB::InsertGuildMember(GUILDMINFO& Guild);
	//public: int CIGuildInfoDB::InsertGuildNotice(unsigned long);
	//public: int CIGuildInfoDB::InsertGuildBanishInfo(struct GUILDBANISHINFO &);
	//public: int CIGuildInfoDB::InsertGuildAlly(struct GUILDALLYINFO &);
	//public: int CIGuildInfoDB::InsertGuildMPosition(struct GUILDMPOSITION &);
	//public: int CIGuildInfoDB::GetGuildInfoDB(unsigned long, struct GUILDINFO &);
	//public: int CIGuildInfoDB::GetGuildMInfoDB(unsigned long, int &, char *);
	//public: int CIGuildInfoDB::GetGuildAllyInfoDB(unsigned long, int &, char *);
	//public: int CIGuildInfoDB::GetGuildNoticeDB(unsigned long, struct GUILDNOTICE &);
	//public: int CIGuildInfoDB::GetGuildBanishInfoDB(unsigned long, int &, char *);
	//public: int CIGuildInfoDB::GetGuildMemberPositionDB(unsigned long, int &, char *);
	//public: int CIGuildInfoDB::GetGuildAgitDB(int &, int *);

private:
	static hook_method<unsigned long (CIGuildInfoDB::*)(unsigned long GID)> CIGuildInfoDB::_GetGDID;
	static hook_method<int (CIGuildInfoDB::*)(GUILDMINFO& Guild)> CIGuildInfoDB::_InsertGuildMember;
};


class CIGuildSkillDB : public CGuildDB
{
	/* this+0x0 */ //CGuildDB

	//public: void CIGuildSkillDB::CIGuildSkillDB();
	//public: void CIGuildSkillDB::~CIGuildSkillDB();
	//public: void LoadSkill();
	public: int CIGuildSkillDB::GetSkill(int GDID, unsigned char* data, int& SkillPoint);
	public: int CIGuildSkillDB::UpdateSkill(int GDID, char* data, int skillSize, int SkillPoint);
	public: void CIGuildSkillDB::InsertSkill(int GDID, int Point);

private:
	static hook_method<int (CIGuildSkillDB::*)(int GDID, unsigned char* data, int& SkillPoint)> CIGuildSkillDB::_GetSkill;
	static hook_method<int (CIGuildSkillDB::*)(int GDID, char* data, int skillSize, int SkillPoint)> CIGuildSkillDB::_UpdateSkill;
	static hook_method<void (CIGuildSkillDB::*)(int GDID, int Point)> CIGuildSkillDB::_InsertSkill;
};
