#include "Guild.h"


CGuild::CGuild(void)
{
	m_GuildMInfoMPool.CMemoryMgr<GUILDMINFO>::Init(56);
	m_GuildAllyInfoMPool.CMemoryMgr<GUILDALLYINFO>::Init(6);
	m_GuildBanishInfoMPool.CMemoryMgr<GUILDBANISHINFO>::Init(2);
	m_GuildMPositionMPool.CMemoryMgr<GUILDMPOSITION>::Init(20);
}


CGuild::~CGuild(void)
{
}


/* hook_method<int (CGuild::*)(int GID)> CGuild::_FindBanishMember(SERVER, "CGuild::FindBanishMember");
int CGuild::FindBanishMember(int GID)
{
	return (this->*_FindBanishMember)(GID);

	//TODO
} */


hook_method<void (CGuild::*)(int Stat, int GID, short job, int Level, short sex, short head, short headpal)> CGuild::_UpdateMemberStatus(SERVER, "CGuild::UpdateMemberStatus");
void CGuild::UpdateMemberStatus(int Stat, int GID, short job, int Level, short sex, short head, short headpal)
{
	return (this->*_UpdateMemberStatus)(Stat, GID, job, Level, sex, head, headpal);

	//TODO
}


/* hook_method<void (CGuild::*)(int GID, int Job, int Level)> CGuild::_UpdateMemberJob_Level(SERVER, "CGuild::UpdateMemberJob_Level");
void CGuild::UpdateMemberJob_Level(int GID, int Job, int Level)
{
	return (this->*_UpdateMemberJob_Level)(GID, Job, Level);

	//TODO
} */


hook_method<void (CGuild::*)(unsigned long PositionID, char* Name, int Service, int Join, int Penalty)> CGuild::_UpdateMemberPosition(SERVER, "CGuild::UpdateMemberPosition");
void CGuild::UpdateMemberPosition(unsigned long PositionID, char* Name, int Service, int Join, int Penalty)
{
	return (this->*_UpdateMemberPosition)(PositionID, Name, Service, Join, Penalty);

	//TODO
}


hook_method<int (CGuild::*)(unsigned long GDID)> CGuild::_FindAllyGuild(SERVER, "CGuild::FindAllyGuild");
int CGuild::FindAllyGuild(unsigned long GDID)
{
	return (this->*_FindAllyGuild)(GDID);

	//TODO
}


hook_method<int (CGuild::*)(unsigned long GDID)> CGuild::_FindHostileGuild(SERVER, "CGuild::FindHostileGuild");
int CGuild::FindHostileGuild(unsigned long GDID)
{
	return (this->*_FindHostileGuild)(GDID);

	// TODO
}


hook_method<int (CGuild::*)(unsigned long GID)> CGuild::_IsMaster(SERVER, "CGuild::IsMaster");
int CGuild::IsMaster(unsigned long GID)
{
	return (this->*_IsMaster)(GID);

	//TODO
}


hook_method<int (CGuild::*)(unsigned long PosID)> CGuild::_GetPosJoinRight(SERVER, "CGuild::GetPosJoinRight");
int CGuild::GetPosJoinRight(unsigned long PosID)
{
	return (this->*_GetPosJoinRight)(PosID);

	//TODO
}


hook_method<int (CGuild::*)(unsigned long PosID)> CGuild::_GetPosPenaltyRight(SERVER, "CGuild::GetPosPenaltyRight");
int CGuild::GetPosPenaltyRight(unsigned long PosID)
{
	return (this->*_GetPosPenaltyRight)(PosID);

	//TODO
}


hook_method<int (CGuild::*)(void)> CGuild::_GetAllyCount(SERVER, "CGuild::GetAllyCount");
int CGuild::GetAllyCount(void)
{
	return (this->*_GetAllyCount)();

	//TODO
}

hook_method<int (CGuild::*)(void)> CGuild::_GetHostileCount(SERVER, "CGuild::GetHostileCount");
int CGuild::GetHostileCount(void)
{
	return (this->*_GetHostileCount)();

	//TODO
}


/* hook_method<void (CGuild::*)(GUILDINFO* Info)> CGuild::_GetGuildInfo(SERVER, "CGuild::GetGuildInfo");
void CGuild::GetGuildInfo(GUILDINFO* Info)
{
	return (this->*_GetGuildInfo)(Info);

	//TODO
} */


hook_method<void (CGuild::*)(void)> CGuild::_Init(SERVER, "CGuild::Init");
void CGuild::Init(void)
{
	return (this->*_Init)();

	m_GDID = 0;
	m_level = 1;
	m_guildName[0] = '\0';
	m_guildMasterName[0] = '\0';
	m_maxUserNum = 16;
	m_userNum = 0;
	m_honor = 0;
	m_virtue = 0;
	m_type = 0;
	m_class = 0;
	m_money = 0;
	m_arenaWin = 0;
	m_arenaLose = 0;
	m_arenaDrawn = 0;
	m_manageLand[0] = '\0';
	m_exp = 0;
	m_emblemVersion = 0;
	m_point = 0;
	m_desc[0] = '\0';
	m_isEmblemLoad = 0;
	m_emblemSize = 0;
//	m_guildNotice.GDID = 0; // FIXME:uninitialized
	m_guildNotice.Subject[0] = '\0';
	m_guildNotice.Notice[0] = '\0';
	m_guildEmblem[0] = '\0';
	m_skillDataLength = 0;
	m_skillPoint = 0;
}


hook_method<void (CGuild::*)(void)> CGuild::_DeleteMPosition(SERVER, "CGuild::DeleteMPosition");
void CGuild::DeleteMPosition(void)
{
	return (this->*_DeleteMPosition)();

	//TODO
}


hook_method<void (CGuild::*)(void)> CGuild::_DeleteBanishInfo(SERVER, "CGuild::DeleteBanishInfo");
void CGuild::DeleteBanishInfo(void)
{
	return (this->*_DeleteBanishInfo)();

	//TODO
}


hook_method<void (CGuild::*)(void)> CGuild::_DeleteMInfo(SERVER, "CGuild::DeleteMInfo");
void CGuild::DeleteMInfo(void)
{
	return (this->*_DeleteMInfo)();

	//TODO
}


hook_method<void (CGuild::*)(void)> CGuild::_DeleteAllyInfo(SERVER, "CGuild::DeleteAllyInfo");
void CGuild::DeleteAllyInfo(void)
{
	return (this->*_DeleteAllyInfo)();

	//TODO
}


hook_method<int (CGuild::*)(void)> CGuild::_DeleteFirstBanishInfo(SERVER, "CGuild::DeleteFirstBanishInfo");
int CGuild::DeleteFirstBanishInfo(void)
{
	return (this->*_DeleteFirstBanishInfo)();

	//TODO
}


hook_method<void (CGuild::*)(void)> CGuild::_ClearAll(SERVER, "CGuild::ClearAll");
void CGuild::ClearAll(void)
{
	return (this->*_ClearAll)();

	//TODO
}


/* hook_method<void (CGuild::*)(char* Name)> CGuild::_SetGuildMasterName(SERVER, "CGuild::SetGuildMasterName");
void CGuild::SetGuildMasterName(char* Name)
{
	return (this->*_SetGuildMasterName)(Name);

	//TODO
} */


/* hook_method<void (CGuild::*)(char* GName)> CGuild::_SetGuildName(SERVER, "CGuild::SetGuildName");
void CGuild::SetGuildName(char* GName)
{
	return (this->*_SetGuildName)(GName);

	//TODO
} */


hook_method<void (CGuild::*)(GUILDINFO* Info)> CGuild::_SetGuildInfo(SERVER, "CGuild::SetGuildInfo");
void CGuild::SetGuildInfo(GUILDINFO* Info)
{
	return (this->*_SetGuildInfo)(Info);

	//TODO
}



//hook_method<void (CGuild::*)(int Ver)> CGuild::_SetEmblemVersion(SERVER, "CGuild::SetEmblemVersion");
void CGuild::SetEmblemVersion(int Ver)
{
//	return (this->*_SetEmblemVersion)(Ver);

	m_emblemVersion = Ver;
}


//hook_method<void (CGuild::*)(int Num)> CGuild::_SetMaxUserNum(SERVER, "CGuild::SetMaxUserNum");
void CGuild::SetMaxUserNum(int Num)
{
//	return (this->*_SetMaxUserNum)(Num);

	m_maxUserNum = Num;
}


//hook_method<void (CGuild::*)(unsigned long GDID)> CGuild::_SetGDID(SERVER, "CGuild::SetGDID");
void CGuild::SetGDID(unsigned long GDID)
{
//	return (this->*_SetGDID)(GDID);

	m_GDID = GDID;
}


//hook_method<void (CGuild::*)(const unsigned char* in_DataPtr, const int in_DataLength)> CGuild::_SetSkillData(SERVER, "CGuild::SetSkillData");
void CGuild::SetSkillData(const unsigned char* in_DataPtr, const int in_DataLength)
{
//	return (this->*_SetSkillData)(in_DataPtr, in_DataLength);

	if ( in_DataLength > 300 )
		return;

	memcpy(m_skillData, in_DataPtr, in_DataLength);
	m_skillDataLength = in_DataLength;
}


hook_method<int (CGuild::*)(void)> CGuild::_GetGuildMemberOnline(SERVER, "CGuild::GetGuildMemberOnline");
int CGuild::GetGuildMemberOnline(void)
{
	return (this->*_GetGuildMemberOnline)();

	//TODO
}


hook_method<char* (CGuild::*)(unsigned long PosID)> CGuild::_GetPosName(SERVER, "CGuild::GetPosName");
char* CGuild::GetPosName(unsigned long PosID)
{
	return (this->*_GetPosName)(PosID);

	//TODO
}


/* hook_method<char* (CGuild::*)(unsigned long GID)> CGuild::_GetMemberName(SERVER, "CGuild::GetMemberName");
char* CGuild::GetMemberName(unsigned long GID)
{
	return (this->*_GetMemberName)(GID);

	//TODO
} */


/* hook_method<int (CGuild::*)(unsigned long GID)> CGuild::_GetMemberExp(SERVER, "CGuild::GetMemberExp");
int CGuild::GetMemberExp(unsigned long GID)
{
	return (this->*_GetMemberExp)(GID);

	//TODO
} */


/* hook_method<int (CGuild::*)(unsigned long GID)> CGuild::_GetMemberLevel(SERVER, "CGuild::GetMemberLevel");
int CGuild::GetMemberLevel(unsigned long GID)
{
	return (this->*_GetMemberLevel)(GID);

	//TODO
} */


/* hook_method<int (CGuild::*)(unsigned long GID)> CGuild::_GetMemberClass(SERVER, "CGuild::GetMemberClass");
int CGuild::GetMemberClass(unsigned long GID)
{
	return (this->*_GetMemberClass)(GID);

	//TODO
} */


hook_method<void (CGuild::*)(char* Buf)> CGuild::_GetGuildPosID(SERVER, "?GetGuildPosID@CGuild@@QAEXPAD@Z");
void CGuild::GetGuildPosID(char* Buf)
{
	return (this->*_GetGuildPosID)(Buf);

	//TODO
}


hook_method<int (CGuild::*)(unsigned long GID)> CGuild::_GetGuildPosID2(SERVER, "?GetGuildPosID@CGuild@@QAEHK@Z");
int CGuild::GetGuildPosID(unsigned long GID)
{
	return (this->*_GetGuildPosID2)(GID);

	//TODO
}


hook_method<int (CGuild::*)(unsigned long GID)> CGuild::_isJoinRight(SERVER, "CGuild::isJoinRight");
int CGuild::isJoinRight(unsigned long GID)
{
	return (this->*_isJoinRight)(GID);

	//TODO
}


hook_method<int (CGuild::*)(unsigned long GID)> CGuild::_isPenaltyRight(SERVER, "CGuild::isPenaltyRight");
int CGuild::isPenaltyRight(unsigned long GID)
{
	return (this->*_isPenaltyRight)(GID);

	//TODO
}


hook_method<void (CGuild::*)(GUILDMINFO* Info)> CGuild::_AddGuildMInfo(SERVER, "CGuild::AddGuildMInfo");
void CGuild::AddGuildMInfo(GUILDMINFO* Info)
{
	return (this->*_AddGuildMInfo)(Info);

	//TODO
}


hook_method<void (CGuild::*)(GUILDALLYINFO* Info)> CGuild::_AddGuildAllyInfo(SERVER, "CGuild::AddGuildAllyInfo");
void CGuild::AddGuildAllyInfo(GUILDALLYINFO* Info)
{
	return (this->*_AddGuildAllyInfo)(Info);

	//TODO
}


hook_method<void (CGuild::*)(GUILDBANISHINFO* Info)> CGuild::_AddGuildBanishInfo(SERVER, "CGuild::AddGuildBanishInfo");
void CGuild::AddGuildBanishInfo(GUILDBANISHINFO* Info)
{
	return (this->*_AddGuildBanishInfo)(Info);

	//TODO
}


hook_method<void (CGuild::*)(GUILDMPOSITION* Info)> CGuild::_AddGuildMPosition(SERVER, "CGuild::AddGuildMPosition");
void CGuild::AddGuildMPosition(GUILDMPOSITION* Info)
{
	return (this->*_AddGuildMPosition)(Info);

	//TODO
}


hook_method<int (CGuild::*)(void)> CGuild::_GetAverageLevel(SERVER, "CGuild::GetAverageLevel");
int CGuild::GetAverageLevel(void)
{
	return (this->*_GetAverageLevel)();

	//TODO
}


hook_method<int (CGuild::*)(void)> CGuild::_GetGuildMSize(SERVER, "CGuild::GetGuildMSize");
int CGuild::GetGuildMSize(void)
{
	return (this->*_GetGuildMSize)();

	//TODO
}


/* hook_method<int (CGuild::*)(void)> CGuild::_GetGuildMAllocSize(SERVER, "CGuild::GetGuildMAllocSize");
int CGuild::GetGuildMAllocSize(void)
{
	return (this->*_GetGuildMAllocSize)();

	//TODO
} */


hook_method<int (CGuild::*)(unsigned long GID)> CGuild::_FindMember(SERVER, "CGuild::FindMember");
int CGuild::FindMember(unsigned long GID)
{
	return (this->*_FindMember)(GID);

	//TODO
}


hook_method<int (CGuild::*)(void)> CGuild::_GetGuildAllySize(SERVER, "CGuild::GetGuildAllySize");
int CGuild::GetGuildAllySize(void)
{
	return (this->*_GetGuildAllySize)();

	//TODO
}


hook_method<int (CGuild::*)(void)> CGuild::_GetGuildBanishSize(SERVER, "CGuild::GetGuildBanishSize");
int CGuild::GetGuildBanishSize(void)
{
	return (this->*_GetGuildBanishSize)();

	//TODO
}


hook_method<int (CGuild::*)(void)> CGuild::_GetGuildMPosSize(SERVER, "CGuild::GetGuildMPosSize");
int CGuild::GetGuildMPosSize(void)
{
	return (this->*_GetGuildMPosSize)();

	//TODO
}


/* hook_method<int (CGuild::*)(int Amount, int Type)> CGuild::_UpdateMoney(SERVER, "CGuild::UpdateMoney");
int CGuild::UpdateMoney(int Amount, int Type)
{
	return (this->*_UpdateMoney)(Amount, Type);

	//TODO
} */


hook_method<GUILDMINFO* (CGuild::*)(void)> CGuild::_AllocGuildMInfo(SERVER, "CGuild::AllocGuildMInfo");
GUILDMINFO* CGuild::AllocGuildMInfo(void)
{
	return (this->*_AllocGuildMInfo)();

	//TODO
}


hook_method<GUILDALLYINFO* (CGuild::*)(void)> CGuild::_AllocGuildAllyInfo(SERVER, "CGuild::AllocGuildAllyInfo");
GUILDALLYINFO* CGuild::AllocGuildAllyInfo(void)
{
	return (this->*_AllocGuildAllyInfo)();

	//TODO
}


hook_method<GUILDBANISHINFO* (CGuild::*)(void)> CGuild::_AllocGuildBanishInfo(SERVER, "CGuild::AllocGuildBanishInfo");
GUILDBANISHINFO* CGuild::AllocGuildBanishInfo(void)
{
	return (this->*_AllocGuildBanishInfo)();

	//TODO
}


hook_method<GUILDMPOSITION* (CGuild::*)(void)> CGuild::_AllocGuildMPosition(SERVER, "CGuild::AllocGuildMPosition");
GUILDMPOSITION* CGuild::AllocGuildMPosition(void)
{
	return (this->*_AllocGuildMPosition)();

	//TODO
}


hook_method<void (CGuild::*)(unsigned long GDID, int Type)> CGuild::_DeleteGuildAllyInfo(SERVER, "CGuild::DeleteGuildAllyInfo");
void CGuild::DeleteGuildAllyInfo(unsigned long GDID, int Type)
{
	return (this->*_DeleteGuildAllyInfo)(GDID, Type);

	//TODO
}


/* hook_method<void (CGuild::*)(unsigned long GID)> CGuild::_DeleteGuildBanishInfo(SERVER, "CGuild::DeleteGuildBanishInfo");
void CGuild::DeleteGuildBanishInfo(unsigned long GID)
{
	return (this->*_DeleteGuildBanishInfo)(GID);

	//TODO
} */


/* hook_method<void (CGuild::*)(unsigned long GID)> CGuild::_DeleteGuildMInfo(SERVER, "CGuild::DeleteGuildMInfo");
void CGuild::DeleteGuildMInfo(unsigned long GID)
{
	return (this->*_DeleteGuildMInfo)(GID);

	//TODO
} */


hook_method<int (CGuild::*)(unsigned long GID, int Exp)> CGuild::_AddGuildExp(SERVER, "CGuild::AddGuildExp");
int CGuild::AddGuildExp(unsigned long GID, int Exp)
{
	return (this->*_AddGuildExp)(GID, Exp);

	//TODO
}


hook_method<int (CGuild::*)(unsigned long PositionID)> CGuild::_GetServiceRate(SERVER, "CGuild::GetServiceRate");
int CGuild::GetServiceRate(unsigned long PositionID)
{
	return (this->*_GetServiceRate)(PositionID);

	//TODO
}


//hook_method<void (CGuild::*)(unsigned long GID, GUILD_MEMBER_INFO& Info)> CGuild::_GetGuildMemberInfo(SERVER, "CGuild::GetGuildMemberInfo");
void CGuild::GetGuildMemberInfo(unsigned long GID, GUILD_MEMBER_INFO& Info)
{
//	return (this->*_GetGuildMemberInfo)(GID, Info);

	for( mystd::vector<GUILDMINFO*>::iterator it = m_guildMInfo.begin(); it != m_guildMInfo.end(); ++it )
	{
		if( (*it)->GID == GID )
		{
			Info.AID = (*it)->AID;
			strncpy(Info.charname, (*it)->CharName, 0x18u);
			Info.contributionExp = (*it)->MemberExp;
			Info.currentState = (*it)->status;
			Info.GID = (*it)->GID;
			Info.head = (*it)->head;
			Info.headPalette = (*it)->headPalette;
			strncpy(Info.intro, (*it)->Memo, 0x32u);
			Info.job = LOWORD((*it)->job);
			Info.level = LOWORD((*it)->Level);
			Info.positionID = (*it)->PositionID;
			Info.sex = (*it)->sex;
			return;
		}
	}
}


hook_method<void (CGuild::*)(char* Buf)> CGuild::_GetGuildBanishInfo(SERVER, "CGuild::GetGuildBanishInfo");
void CGuild::GetGuildBanishInfo(char* Buf)
{
	return (this->*_GetGuildBanishInfo)(Buf);

	//TODO
}


hook_method<void (CGuild::*)(char* Buf)> CGuild::_GetGuildAllyInfo(SERVER, "CGuild::GetGuildAllyInfo");
void CGuild::GetGuildAllyInfo(char* Buf)
{
	return (this->*_GetGuildAllyInfo)(Buf);

	for( mystd::vector<GUILDALLYINFO*>::const_iterator it = m_guildAllyInfo.begin(); it != m_guildAllyInfo.end(); ++it )
	{
		RELATED_GUILD_INFO Info;
		strncpy(Info.guildname, (*it)->GuildName, sizeof(Info.guildname));
		Info.GDID = (*it)->OpponentGDID;
		Info.relation = (*it)->Relation;

		memcpy(Buf, &Info, sizeof(Info));
		Buf += sizeof(Info);
	}
}


hook_method<void (CGuild::*)(char* Buf)> CGuild::_GetGuildMPosition(SERVER, "CGuild::GetGuildMPosition");
void CGuild::GetGuildMPosition(char* Buf)
{
	return (this->*_GetGuildMPosition)(Buf);

	//TODO
}


/* hook_method<void (CGuild::*)(GUILDMINFO* Guild, char* Name, char* Account, unsigned long AID, unsigned long GDID, unsigned long GID, int Position, int Stat, int Level, int Class)> CGuild::_InitGuildMInfo(SERVER, "?InitGuildMInfo@CGuild@@QAEXPAUGUILDMINFO@@PAD1KKKHHHH@Z");
void CGuild::InitGuildMInfo(GUILDMINFO* Guild, char* Name, char* Account, unsigned long AID, unsigned long GDID, unsigned long GID, int Position, int Stat, int Level, int Class)
{
	return (this->*_InitGuildMInfo)(Guild, Name, Account, AID, GDID, GID, Position, Stat, Level, Class);

	//TODO
} */


hook_method<void (CGuild::*)(GUILDMINFO* Guild, char* Name, char* Account, unsigned long AID, unsigned long GDID, unsigned long GID, int Position, int Stat, int Level, int Job, int head, int headpal, int sex)> CGuild::_InitGuildMInfo2(SERVER, "?InitGuildMInfo@CGuild@@QAEXPAUGUILDMINFO@@PAD1KKKHHHHHHH@Z");
void CGuild::InitGuildMInfo(GUILDMINFO* Guild, char* Name, char* Account, unsigned long AID, unsigned long GDID, unsigned long GID, int Position, int Stat, int Level, int Job, int head, int headpal, int sex)
{
	return (this->*_InitGuildMInfo2)(Guild, Name, Account, AID, GDID, GID, Position, Stat, Level, Job, head, headpal, sex);

	//TODO
}


//hook_method<int (CGuild::*)(void)> CGuild::_GetGDID(SERVER, "CGuild::GetGDID");
int CGuild::GetGDID(void)
{
//	return (this->*_GetGDID)();

	return m_GDID;
}


//hook_method<int (CGuild::*)(void)> CGuild::_GetLevel(SERVER, "CGuild::GetLevel");
int CGuild::GetLevel(void)
{
//	return (this->*_GetLevel)();

	return m_level;
}


//hook_method<char* (CGuild::*)(void)> CGuild::_GetGuildName(SERVER, "CGuild::GetGuildName");
char* CGuild::GetGuildName(void)
{
//	return (this->*_GetGuildName)();

	return m_guildName;
}


//hook_method<char* (CGuild::*)(void)> CGuild::_GetMasterName(SERVER, "CGuild::GetMasterName");
char* CGuild::GetMasterName(void)
{
//	return (this->*_GetMasterName)();

	return m_guildMasterName;
}

//hook_method<int (CGuild::*)(void)> CGuild::_GetMaxUserNum(SERVER, "CGuild::GetMaxUserNum");
int CGuild::GetMaxUserNum(void)
{
//	return (this->*_GetMaxUserNum)();

	return m_maxUserNum;
}


//hook_method<int (CGuild::*)(void)> CGuild::_GetHonor(SERVER, "CGuild::GetHonor");
int CGuild::GetHonor(void)
{
//	return (this->*_GetHonor)();

	return m_honor;
}


//hook_method<int (CGuild::*)(void)> CGuild::_GetVirtue(SERVER, "CGuild::GetVirtue");
int CGuild::GetVirtue(void)
{
//	return (this->*_GetVirtue)();

	return m_virtue;
}


/* hook_method<int (CGuild::*)(void)> CGuild::_GetType(SERVER, "CGuild::GetType");
int CGuild::GetType(void)
{
	return (this->*_GetType)();

	//TODO
} */


/* hook_method<int (CGuild::*)(void)> CGuild::_GetClass(SERVER, "CGuild::GetClass");
int CGuild::GetClass(void)
{
	return (this->*_GetClass)();

	//TODO
} */


//hook_method<int (CGuild::*)(void)> CGuild::_GetMoney(SERVER, "CGuild::GetMoney");
int CGuild::GetMoney(void)
{
//	return (this->*_GetMoney)();

	return m_money;
}


/* hook_method<int (CGuild::*)(void)> CGuild::_GetArenaWin(SERVER, "CGuild::GetArenaWin");
int CGuild::GetArenaWin(void)
{
	return (this->*_GetArenaWin)();

	//TODO
} */


/* hook_method<int (CGuild::*)(void)> CGuild::_GetArenaLose(SERVER, "CGuild::GetArenaLose");
int CGuild::GetArenaLose(void)
{
	return (this->*_GetArenaLose)();

	//TODO
} */


/* hook_method<int (CGuild::*)(void)> CGuild::_GetArenaDrawn(SERVER, "CGuild::GetArenaDrawn");
int CGuild::GetArenaDrawn(void)
{
	return (this->*_GetArenaDrawn)();

	//TODO
} */


//hook_method<char* (CGuild::*)(void)> CGuild::_GetManageLand(SERVER, "CGuild::GetManageLand");
char* CGuild::GetManageLand(void)
{
//	return (this->*_GetManageLand)();

	return m_manageLand;
}


//hook_method<int (CGuild::*)(void)> CGuild::_GetExp(SERVER, "CGuild::GetExp");
int CGuild::GetExp(void)
{
//	return (this->*_GetExp)();

	return m_exp;
}


//hook_method<int (CGuild::*)(void)> CGuild::_GetEmblemVersion(SERVER, "CGuild::GetEmblemVersion");
int CGuild::GetEmblemVersion(void)
{
//	return (this->*_GetEmblemVersion)();

	return m_emblemVersion;
}


//hook_method<int (CGuild::*)(void)> CGuild::_GetPoint(SERVER, "CGuild::GetPoint");
int CGuild::GetPoint(void)
{
//	return (this->*_GetPoint)();

	return m_point;
}


/* hook_method<char* (CGuild::*)(void)> CGuild::_GetDesc(SERVER, "CGuild::GetDesc");
char* CGuild::GetDesc(void)
{
	return (this->*_GetDesc)();

	//TODO
} */


//hook_method<char* (CGuild::*)(void)> CGuild::_GetNotice(SERVER, "CGuild::GetNotice");
char* CGuild::GetNotice(void)
{
//	return (this->*_GetNotice)();

	return m_guildNotice.Notice;
}


//hook_method<char* (CGuild::*)(void)> CGuild::_GetNoticeSubject(SERVER, "CGuild::GetNoticeSubject");
char* CGuild::GetNoticeSubject(void)
{
//	return (this->*_GetNoticeSubject)();

	return m_guildNotice.Subject;
}


/* hook_method<void (CGuild::*)(const unsigned long in_GuildID, mystd::string& in_Subject, mystd::string& in_Notice)> CGuild::_UpdateNotice(SERVER, "CGuild::UpdateNotice");
void CGuild::UpdateNotice(const unsigned long in_GuildID, mystd::string& in_Subject, mystd::string& in_Notice)
{
	return (this->*_UpdateNotice)(in_GuildID, in_Subject, in_Notice);

	//TODO
} */


//hook_method<char* (CGuild::*)(void)> CGuild::_GetEmblem(SERVER, "CGuild::GetEmblem");
char* CGuild::GetEmblem(void)
{
//	return (this->*_GetEmblem)();

	return m_guildEmblem;
}


//hook_method<int (CGuild::*)(void)> CGuild::_IsEmblemLoad(SERVER, "CGuild::IsEmblemLoad");
int CGuild::IsEmblemLoad(void)
{
//	return (this->*_IsEmblemLoad)();

	return m_isEmblemLoad;
}


//hook_method<int (CGuild::*)(void)> CGuild::_GetEmblemSize(SERVER, "CGuild::GetEmblemSize");
int CGuild::GetEmblemSize(void)
{
//	return (this->*_GetEmblemSize)();

	return m_emblemSize;
}


//hook_method<void (CGuild::*)(int Money)> CGuild::_SetMoney(SERVER, "CGuild::SetMoney");
void CGuild::SetMoney(int Money)
{
//	return (this->*_SetMoney)(Money);

	m_money = Money;
}


//hook_method<int (CGuild::*)(int Money)> CGuild::_AddMoney(SERVER, "CGuild::AddMoney");
int CGuild::AddMoney(int Money)
{
//	return (this->*_AddMoney)(Money);

	m_money += Money;
	return m_money;
}
