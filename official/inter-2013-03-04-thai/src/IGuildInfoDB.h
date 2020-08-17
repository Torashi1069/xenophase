#pragma once
#include "IGuildInfo.h"
#include "shared/GuildDB.h"


class CIGuildInfoDB : public CGuildDB
{
public:
	BOOL DeleteAllGuildMPosition(unsigned long GDID);
	BOOL DeleteAllGuildBanish(unsigned long GDID);
	BOOL DeleteAllGuildAllyInfo(unsigned long GDID);
	BOOL DeleteGuildMInfo(unsigned long GID);
	BOOL DeleteGuildInfoDB(unsigned long GDID);
	BOOL DeleteGuildNotice(unsigned long GDID);
	BOOL DeleteGuildAllyInfo(unsigned long GDID, unsigned long OpponentGDID, int Relation);
	BOOL DeleteGuildBanishInfo(unsigned long GDID, unsigned long GID);
	BOOL DeleteGuildSkill(unsigned long GDID);
	unsigned long GetGDID(unsigned long GID);

public:
	CIGuildInfoDB();
	virtual ~CIGuildInfoDB();

public:
	virtual void InitStoredProcTable();
	int MakeGuild(unsigned long AID, unsigned long GID, unsigned long& GDID, char* Name, char* GName);
	BOOL UpdateTableDWORD(unsigned long GDID, unsigned long Value, int ProcType);
	BOOL UpdateTableChar(unsigned long GDID, char* Value, int ProcType);
	int UpdateGuildInfoDB(CIGuildInfo& Guild);
	int UpdateGuildMInfo(GUILDMINFO& Guild);
	BOOL UpdateMemberPos(unsigned long GDID, GUILD_REG_POSITION_INFO& Guild, int Join, int Penalty);
	BOOL UpdateMemberChangePos(unsigned long GDID, unsigned long GID, unsigned long PosID);
	BOOL UpdateGuildEmblem(unsigned long GDID, unsigned long EmblemVer);
	BOOL UpdateGuildNotice(unsigned long GDID, char* Subject, char* Notice);
	BOOL UpdateGuildMember(unsigned long GDID, unsigned long GID, unsigned long Service, unsigned long Exp, int Level, int Class);
	int InsertGuildMember(GUILDMINFO& Guild);
	int InsertGuildNotice(unsigned long GDID);
	int InsertGuildBanishInfo(GUILDBANISHINFO& Guild);
	int InsertGuildAlly(GUILDALLYINFO& Guild);
	int InsertGuildMPosition(GUILDMPOSITION& Guild);
	BOOL GetGuildInfoDB(unsigned long GDID, GUILDINFO& Guild);
	int GetGuildMInfoDB(unsigned long GDID, int& buflen, char* buf);
	int GetGuildAllyInfoDB(unsigned long GDID, int& buflen, char* buf);
	BOOL GetGuildNoticeDB(unsigned long GDID, GUILDNOTICE& Guild);
	int GetGuildBanishInfoDB(unsigned long GDID, int& buflen, char* buf);
	int GetGuildMemberPositionDB(unsigned long GDID, int& buflen, char* buf);
	bool GetGuildAgitDB(std::set<unsigned long>& out_setAgitOwnerGDID);

protected:
	/* this+ 0 */ //CGuildDB baseclass_0;
	/* this+52 */ std::map<int,char*> m_inputProcTable;
};


class CIGuildSkillDB : public CGuildDB
{
public:
	CIGuildSkillDB();
	virtual ~CIGuildSkillDB();

public:
	void LoadSkill(); //TODO
	int GetSkill(int GDID, unsigned char* data, int& SkillPoint);
	BOOL UpdateSkill(int GDID, char* data, int skillSize, int SkillPoint);
	void InsertSkill(int GDID, int Point);
};
