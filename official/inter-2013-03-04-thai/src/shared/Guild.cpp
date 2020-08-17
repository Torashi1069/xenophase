#include "InterServer.h"
#include "shared/Guild.h"


CGuild::CGuild()
{
	m_GuildMInfoMPool.CMemoryMgr2<GUILDMINFO>::Init(MAX_GUILD_MEMBER_LIST);
	m_GuildAllyInfoMPool.CMemoryMgr2<GUILDALLYINFO>::Init(6);
	m_GuildBanishInfoMPool.CMemoryMgr2<GUILDBANISHINFO>::Init(2);
	m_GuildMPositionMPool.CMemoryMgr2<GUILDMPOSITION>::Init(20);
}


CGuild::~CGuild()
{
}


void CGuild::SetGuildInfo(GUILDINFO* Info)
{
	m_GDID = Info->GDID;
	m_level = Info->Level;
	strcpy(m_guildName, Info->Name);
	strcpy(m_guildMasterName, Info->MName);
	m_maxUserNum = Info->MaxUserNum;
	m_honor = Info->Honor;
	m_virtue = Info->Virtue;
	m_type = Info->Type;
	m_class = Info->Class;
	m_money = Info->Money;
	m_arenaWin = Info->ArenaWin;
	m_arenaLose = Info->ArenaLose;
	m_arenaDrawn = Info->ArenaDrawn;
	strcpy(m_manageLand, Info->ManageLand);
	m_exp = ( Info->Exp >= 0 ) ? Info->Exp : INT_MAX;
	m_emblemVersion = Info->EmblemVersion;
	m_point = Info->Point;
	strcpy(m_desc, Info->Desc);
}


void CGuild::Init()
{
	m_guildName[0] = '\0';
	m_guildMasterName[0] = '\0';
	m_GDID = 0;
	m_arenaDrawn = 0;
	m_arenaLose = 0;
	m_arenaWin = 0;
	m_class = 0;
	m_desc[0] = '\0';
	m_exp = 0;
	m_emblemVersion = 0;
	m_isEmblemLoad = 0;
	m_guildEmblem[0] = '\0';
	m_emblemSize = 0;
	m_honor = 0;
	m_level = 1;
	m_manageLand[0] = '\0';
	m_maxUserNum = 16;
	m_userNum = 0;
	m_money = 0;
	m_point = 0;
	m_type = 0;
	m_virtue = 0;
	m_guildNotice.Notice[0] = '\0';
	m_guildNotice.Subject[0] = '\0';
//	m_guildNotice.GDID = 0;
	m_skillDataLength = 0;
	m_skillPoint = 0;
//	memset(m_skillData, 0, sizeof(m_skillData));
//	this->CGuild::ClearAll();
}


void CGuild::SetGuildName(char* GName)
{
	if( strlen(GName) >= countof(m_guildName) )
		return;

	strcpy(m_guildName, GName);
}


void CGuild::SetGuildMasterName(char* Name)
{
	if( strlen(Name) >= countof(m_guildMasterName) )
		return;

	strcpy(m_guildMasterName, Name);
}


void CGuild::ClearAll()
{
	this->CGuild::DeleteAllyInfo();
	this->CGuild::DeleteMInfo();
	this->CGuild::DeleteBanishInfo();
	this->CGuild::DeleteMPosition();
	m_GDID = 0;
}


void CGuild::DeleteAllyInfo()
{
	for( std::vector<GUILDALLYINFO*>::iterator iter = m_guildAllyInfo.begin(); iter != m_guildAllyInfo.end(); iter = m_guildAllyInfo.erase(iter) )
		m_GuildAllyInfoMPool.CMemoryMgr2<GUILDALLYINFO>::Free(*iter);

	m_GuildAllyInfoMPool.CMemoryMgr2<GUILDALLYINFO>::Reset();
	m_guildAllyInfo.clear();
}


void CGuild::DeleteMInfo()
{
	for( std::vector<GUILDMINFO*>::iterator iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); iter = m_guildMInfo.erase(iter) )
		m_GuildMInfoMPool.CMemoryMgr2<GUILDMINFO>::Free(*iter);

	m_GuildMInfoMPool.CMemoryMgr2<GUILDMINFO>::Reset();
	m_guildMInfo.clear();
}


void CGuild::DeleteBanishInfo()
{
	for( std::vector<GUILDBANISHINFO*>::iterator iter = m_guildBanishInfo.begin(); iter != m_guildBanishInfo.end(); iter = m_guildBanishInfo.erase(iter) )
		m_GuildBanishInfoMPool.CMemoryMgr2<GUILDBANISHINFO>::Free(*iter);
}


void CGuild::DeleteMPosition()
{
	for( std::vector<GUILDMPOSITION*>::iterator iter = m_guildMPosition.begin(); iter != m_guildMPosition.end(); iter = m_guildMPosition.erase(iter) )
		m_GuildMPositionMPool.CMemoryMgr2<GUILDMPOSITION>::Free(*iter);
}


void CGuild::DeleteGuildMInfo(unsigned long GID)
{
	for( std::vector<GUILDMINFO*>::iterator iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
	{
		if( (*iter)->GID == GID )
		{
			m_GuildMInfoMPool.CMemoryMgr2<GUILDMINFO>::Free(*iter);
			m_guildMInfo.erase(iter);
			break;
		}
	}
}


void CGuild::DeleteGuildAllyInfo(unsigned long GDID, int Type)
{
	for( std::vector<GUILDALLYINFO*>::iterator iter = m_guildAllyInfo.begin(); iter != m_guildAllyInfo.end(); ++iter )
	{
		if( (*iter)->OpponentGDID == GDID && (*iter)->Relation == Type )
		{
			m_GuildAllyInfoMPool.CMemoryMgr2<GUILDALLYINFO>::Free(*iter);
			m_guildAllyInfo.erase(iter);
			break;
		}
	}
}


void CGuild::DeleteGuildBanishInfo(unsigned long GID)
{
	for( std::vector<GUILDBANISHINFO*>::iterator iter = m_guildBanishInfo.begin(); iter != m_guildBanishInfo.end(); ++iter )
	{
		if( (*iter)->GID == GID )
		{
			m_GuildBanishInfoMPool.CMemoryMgr2<GUILDBANISHINFO>::Free(*iter);
			m_guildBanishInfo.erase(iter);
			break;
		}
	}
}


void CGuild::AddGuildAllyInfo(GUILDALLYINFO* Info)
{
	if( Info == NULL )
		return;

	m_guildAllyInfo.push_back(Info);
}


void CGuild::AddGuildBanishInfo(GUILDBANISHINFO* Info)
{
	if( Info == NULL )
		return;

	m_guildBanishInfo.push_back(Info);
}


void CGuild::AddGuildMPosition(GUILDMPOSITION* Info)
{
	if( Info == NULL )
		return;

	m_guildMPosition.push_back(Info);
}


GUILDMINFO* CGuild::AllocGuildMInfo()
{
	return m_GuildMInfoMPool.CMemoryMgr2<GUILDMINFO>::Alloc();
}


GUILDALLYINFO* CGuild::AllocGuildAllyInfo()
{
	return m_GuildAllyInfoMPool.CMemoryMgr2<GUILDALLYINFO>::Alloc();
}


GUILDBANISHINFO* CGuild::AllocGuildBanishInfo()
{
	return m_GuildBanishInfoMPool.CMemoryMgr2<GUILDBANISHINFO>::Alloc();
}


GUILDMPOSITION* CGuild::AllocGuildMPosition()
{
	return m_GuildMPositionMPool.CMemoryMgr2<GUILDMPOSITION>::Alloc();
}


void CGuild::InitGuildMInfo(GUILDMINFO* Guild, char* Name, char* Account, unsigned long AID, unsigned long GDID, unsigned long GID, int Position, int Stat, int Level, int Class)
{
	Guild->AID = AID;
	strncpy(Guild->CharName, Name, countof(Guild->CharName));
	Guild->GDID = GDID;
	Guild->GID = GID;
	Guild->PositionID = Position;
	Guild->MemberExp = 0;
	Guild->Memo[0] = '\0';
	Guild->Service = 0;
	Guild->Level = Level;
	Guild->status = Stat;
	strncpy(Guild->AccountName, Account, countof(Guild->AccountName));
}


void CGuild::InitGuildMInfo(GUILDMINFO* Guild, char* Name, char* Account, unsigned long AID, unsigned long GDID, unsigned long GID, int Position, int Stat, int Level, int Job, int head, int headpal, int sex)
{
	Guild->AID = AID;
	strncpy(Guild->CharName, Name, countof(Guild->CharName));
	Guild->GDID = GDID;
	Guild->GID = GID;
	Guild->PositionID = Position;
	Guild->MemberExp = 0;
	Guild->Memo[0] = '\0';
	Guild->Service = 0;
	Guild->Level = Level;
	Guild->head = head;
	Guild->headPalette = headpal;
	Guild->sex = sex;
	Guild->status = Stat;
	Guild->job = Job;
	strncpy(Guild->AccountName, Account, countof(Guild->AccountName));
}


void CGuild::GetGuildInfo(GUILDINFO& Guild)
{
	Guild.ArenaDrawn = m_arenaDrawn;
	Guild.ArenaLose = m_arenaLose;
	Guild.ArenaWin = m_arenaWin;
	Guild.Class = m_class;
	strcpy(Guild.Desc, m_desc);
	Guild.Exp = m_exp;
	Guild.GDID = m_GDID;
	Guild.Honor = m_honor;
	Guild.Level = m_level;
	strcpy(Guild.ManageLand, m_manageLand);
	Guild.MaxUserNum = m_maxUserNum;
	strcpy(Guild.MName, m_guildMasterName);
	Guild.Money = m_money;
	strcpy(Guild.Name, m_guildName);
	Guild.Point = m_point;
	Guild.Type = m_type;
	Guild.UserNum = m_userNum;
	Guild.Virtue = m_virtue;
	Guild.EmblemVersion = m_emblemVersion;
}


int CGuild::GetGuildMSize()
{
	return m_guildMInfo.size();
}


int CGuild::GetGuildAllySize()
{
	return m_guildAllyInfo.size();
}


int CGuild::GetGuildMPosSize()
{
	return m_guildMPosition.size();
}


int CGuild::GetGuildBanishSize()
{
	return m_guildBanishInfo.size();
}


void CGuild::GetGuildMemberInfo(unsigned long GID, GUILD_MEMBER_INFO& Info)
{
	for( std::vector<GUILDMINFO*>::iterator iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
	{
		if( (*iter)->GID == GID )
		{
			Info.AID = (*iter)->AID;
			strncpy(Info.charname, (*iter)->CharName, countof(Info.charname));
			Info.contributionExp = (*iter)->MemberExp;
			Info.currentState = (*iter)->status;
			Info.GID = (*iter)->GID;
			Info.head = (*iter)->head;
			Info.headPalette = (*iter)->headPalette;
			strncpy(Info.intro, (*iter)->Memo, countof(Info.intro));
			Info.job = LOWORD((*iter)->job);
			Info.level = LOWORD((*iter)->Level);
			Info.positionID = (*iter)->PositionID;
			Info.sex = (*iter)->sex;
		}
	}
}


void CGuild::GetGuildBanishInfo(char* Buf, const int in_nMaxBufSize)
{
	int offset = 0;
	for( std::vector<GUILDBANISHINFO*>::iterator iter = m_guildBanishInfo.begin(); iter != m_guildBanishInfo.end(); ++iter )
	{
		GUILD_BAN_INFO Info;
		strncpy(Info.account, (*iter)->MemberAccount, countof(Info.account));
		strncpy(Info.charname, (*iter)->MemberName, countof(Info.charname));
		strncpy(Info.reason, (*iter)->Reason, countof(Info.reason));
		memcpy_s(Buf + offset, in_nMaxBufSize - offset, &Info, sizeof(Info));
		offset += sizeof(Info);
	}
}


void CGuild::GetGuildAllyInfo(char* Buf, const int in_nMaxBufSize)
{
	int offset = 0;
	for( std::vector<GUILDALLYINFO*>::iterator iter = m_guildAllyInfo.begin(); iter != m_guildAllyInfo.end(); ++iter )
	{
		RELATED_GUILD_INFO Info;
		strncpy(Info.guildname, (*iter)->GuildName, countof(Info.guildname));
		Info.GDID = (*iter)->OpponentGDID;
		Info.relation = (*iter)->Relation;
		memcpy_s(Buf + offset, in_nMaxBufSize - offset, &Info, sizeof(Info));
		offset += sizeof(Info);
	}
}


void CGuild::GetGuildMPosition(char* Buf, const int in_nMaxBufSize)
{
	int offset = 0;
	for( std::vector<GUILDMPOSITION*>::iterator iter = m_guildMPosition.begin(); iter != m_guildMPosition.end(); ++iter )
	{
		GUILD_POSITION_INFO Info;
		Info.payRate = (*iter)->Service;
		Info.positionID = (*iter)->PositionID;
		Info.ranking = (*iter)->Grade;
		Info.right = 0;
		if( (*iter)->JoinRight )
			Info.right |= 0x01;
		if( (*iter)->PenaltyRight )
			Info.right |= 0x10;
		memcpy_s(Buf + offset, in_nMaxBufSize - offset, &Info, sizeof(Info));
		offset += sizeof(Info);
	}
}


int CGuild::GetServiceRate(unsigned long PositionID)
{
	for( std::vector<GUILDMPOSITION*>::iterator iter = m_guildMPosition.begin(); iter != m_guildMPosition.end(); ++iter )
		if( (*iter)->PositionID == PositionID )
			return (*iter)->Service;

	return 0;
}


void CGuild::GetGuildPosID(char* Buf, const int in_nMaxBufSize)
{
	int offset = 0;
	for( std::vector<GUILDMPOSITION*>::iterator iter = m_guildMPosition.begin(); iter != m_guildMPosition.end(); ++iter )
	{
		MEMBER_POSITION_ID_NAME_INFO Info;
		Info.positionID = (*iter)->PositionID;
		strncpy(Info.posName, (*iter)->PosName, countof(Info.posName));
		memcpy_s(Buf + offset, in_nMaxBufSize - offset, &Info, sizeof(Info));
		offset += sizeof(Info);
	}
}


int CGuild::GetGuildMemberOnline()
{
	int Count = 0;

	for( std::vector<GUILDMINFO*>::iterator iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
		if( (*iter)->status == 1 )
			++Count;

	return Count;
}


void CGuild::GetGuildMemberOnlineList(std::list<std::pair<unsigned long,unsigned long>>& out_listAID)
{
	for( std::vector<GUILDMINFO*>::iterator iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
		if( (*iter)->status == 1 )
			out_listAID.push_back(std::pair<const unsigned long,unsigned long>((*iter)->AID, (*iter)->GID));
}


int CGuild::GetAllyCount()
{
	int Count = 0;

	for( std::vector<GUILDALLYINFO*>::iterator iter = m_guildAllyInfo.begin(); iter != m_guildAllyInfo.end(); ++iter )
		if( (*iter)->Relation == RELATED_GUILD_TYPE_ALLY )
			++Count;

	return Count;
}


int CGuild::GetHostileCount()
{
	int Count = 0;

	for( std::vector<GUILDALLYINFO*>::iterator iter = m_guildAllyInfo.begin(); iter != m_guildAllyInfo.end(); ++iter )
		if( (*iter)->Relation == RELATED_GUILD_TYPE_ENEMY )
			++Count;

	return Count;
}


BOOL CGuild::FindAllyGuild(unsigned long GDID)
{
	for( std::vector<GUILDALLYINFO*>::iterator iter = m_guildAllyInfo.begin(); iter != m_guildAllyInfo.end(); ++iter )
		if( (*iter)->Relation == RELATED_GUILD_TYPE_ALLY && (*iter)->OpponentGDID == GDID )
			return TRUE;

	return FALSE;
}


BOOL CGuild::FindHostileGuild(unsigned long GDID)
{
	for( std::vector<GUILDALLYINFO*>::iterator iter = m_guildAllyInfo.begin(); iter != m_guildAllyInfo.end(); ++iter )
		if( (*iter)->Relation == RELATED_GUILD_TYPE_ENEMY && (*iter)->OpponentGDID == GDID )
			return TRUE;

	return FALSE;
}


void CGuild::UpdateMemberStatus(int Stat, int GID, short job, int Level, short sex, short head, short headpal)
{
	for( std::vector<GUILDMINFO*>::iterator iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
	{
		if( (*iter)->GID == GID )
		{
			(*iter)->status = Stat;
			(*iter)->sex = sex;
			(*iter)->head = head;
			(*iter)->headPalette = headpal;
			(*iter)->job = job;
			(*iter)->Level = Level;
			break;
		}
	}
}


void CGuild::UpdateMemberJob_Level(int GID, int Job, int Level)
{
	for( std::vector<GUILDMINFO*>::iterator iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
	{
		if( (*iter)->GID == GID )
		{
			(*iter)->job = Job;
			(*iter)->Level = Level;
			break;
		}
	}
}


BOOL CGuild::FindBanishMember(int GID)
{
	for( std::vector<GUILDBANISHINFO*>::iterator iter = m_guildBanishInfo.begin(); iter != m_guildBanishInfo.end(); ++iter )
		if( (*iter)->GID == GID )
			return TRUE;

	return FALSE;
}


void CGuild::UpdateMemberPosition(unsigned long PositionID, char* Name, int Service, BOOL Join, BOOL Penalty)
{
	for( std::vector<GUILDMPOSITION*>::iterator iter = m_guildMPosition.begin(); iter != m_guildMPosition.end(); ++iter )
	{
		if( (*iter)->PositionID == PositionID )
		{
			(*iter)->Service = Service;
			(*iter)->JoinRight = Join;
			(*iter)->PenaltyRight = Penalty;
			strncpy((*iter)->PosName, Name, countof((*iter)->PosName));
			return;
		}
	}
}


int CGuild::GetGuildPosID(unsigned long GID)
{
	for( std::vector<GUILDMINFO*>::iterator iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
		if( (*iter)->GID == GID )
			return (*iter)->PositionID;

	return 20-1;
}


void CGuild::UpdateMemberChangePos(unsigned long GID, unsigned long PosID)
{
	for( std::vector<GUILDMINFO*>::iterator iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
	{
		if( (*iter)->GID == GID )
		{
			(*iter)->PositionID = PosID;
			return;
		}
	}
}


BOOL CGuild::IsMaster(unsigned long GID)
{
	for( std::vector<GUILDMINFO*>::iterator iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
		if( (*iter)->GID == GID )
			return ( (*iter)->PositionID == 0 );

	return FALSE;
}


int CGuild::GetMemberExp(unsigned long GID)
{
	for( std::vector<GUILDMINFO*>::iterator iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
		if( (*iter)->GID == GID )
			return (*iter)->MemberExp;

	return 0;
}


int CGuild::GetMemberLevel(unsigned long GID)
{
	for( std::vector<GUILDMINFO*>::iterator iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
		if( (*iter)->GID == GID )
			return (*iter)->Level;

	return 0;
}


int CGuild::GetMemberClass(unsigned long GID)
{
	for( std::vector<GUILDMINFO*>::iterator iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
		if( (*iter)->GID == GID )
			return (*iter)->job;

	return 0;
}


char* CGuild::GetMemberName(unsigned long GID)
{
	for( std::vector<GUILDMINFO*>::iterator iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
		if( (*iter)->GID == GID )
			return (*iter)->CharName;

	return NULL;
}


BOOL CGuild::GetPosJoinRight(unsigned long PosID)
{
	for( std::vector<GUILDMPOSITION*>::iterator iter = m_guildMPosition.begin(); iter != m_guildMPosition.end(); ++iter )
		if( (*iter)->PositionID == PosID )
			return (*iter)->JoinRight;

	return FALSE;
}


char* CGuild::GetPosName(unsigned long PosID)
{
	for( std::vector<GUILDMPOSITION*>::iterator iter = m_guildMPosition.begin(); iter != m_guildMPosition.end(); ++iter )
		if( (*iter)->PositionID == PosID )
			return (*iter)->PosName;

	return NULL;
}


BOOL CGuild::GetPosPenaltyRight(unsigned long PosID)
{
	for( std::vector<GUILDMPOSITION*>::iterator iter = m_guildMPosition.begin(); iter != m_guildMPosition.end(); ++iter )
		if( (*iter)->PositionID == PosID )
			return (*iter)->PenaltyRight;

	return FALSE;
}


int CGuild::GetAverageLevel()
{
	int sum = 0;

	for( std::vector<GUILDMINFO*>::iterator iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
		sum += (*iter)->Level;

	if( m_guildMInfo.size() == 0 )
		return 0; // avoid divide-by-zero

	return sum / m_guildMInfo.size();
}


int CGuild::DeleteFirstBanishInfo()
{
	std::vector<GUILDBANISHINFO*>::iterator iter = m_guildBanishInfo.begin();
	if( iter == m_guildBanishInfo.end() )
		return 0;

	int GID = (*iter)->GID;
	m_GuildBanishInfoMPool.CMemoryMgr2<GUILDBANISHINFO>::Free(*iter);
	m_guildBanishInfo.erase(iter);
	return GID;
}


int CGuild::UpdateMoney(int Amount, int Type)
{
	switch( Type )
	{
	case ZENY_MODIFYTYPE_SET:
	{
		m_money = Amount;
		return ZENY_UPDATE_SUCCESS;
	}
	break;
	case ZENY_MODIFYTYPE_GET:
	{
		return ZENY_UPDATE_FAIL_MINIMUM;
	}
	break;
	case ZENY_MODIFYTYPE_UPDATE:
	{
		m_money += Amount;

		if( m_money < 0 )
		{
			m_money -= Amount;
			return ZENY_UPDATE_FAIL_MINIMUM;
		}

		if( m_money > 20000000 )
		{
			m_money -= Amount;
			return ZENY_UPDATE_FAIL_MAXIMUM;
		}

		return ZENY_UPDATE_SUCCESS;
	}
	break;
	default:
	{
		return ZENY_UPDATE_FAIL_MINIMUM;
	}
	break;
	};
}


BOOL CGuild::FindMember(unsigned long GID)
{
	for( std::vector<GUILDMINFO*>::iterator iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
		if( (*iter)->GID == GID )
			return TRUE;

	return FALSE;
}


BOOL CGuild::isJoinRight(unsigned long GID)
{
	for( std::vector<GUILDMINFO*>::iterator iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
	{
		if( (*iter)->GID == GID )
		{
			if( (*iter)->PositionID == 0 )
				return TRUE; // guildmaster

			return this->CGuild::GetPosJoinRight((*iter)->PositionID);
		}
	}

	return FALSE;
}


BOOL CGuild::isPenaltyRight(unsigned long GID)
{
	for( std::vector<GUILDMINFO*>::iterator iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
	{
		if( (*iter)->GID == GID )
		{
			if( (*iter)->PositionID == 0 )
				return TRUE; // guildmaster

			return this->CGuild::GetPosPenaltyRight((*iter)->PositionID);
		}
	}

	return FALSE;
}


void CGuild::UpdateNotice(const unsigned long in_GuildID, std::string& in_Subject, std::string& in_Notice)
{
	m_guildNotice.GDID = in_GuildID;
	strncpy(m_guildNotice.Subject, in_Subject.c_str(), countof(m_guildNotice.Subject));
	strncpy(m_guildNotice.Notice, in_Notice.c_str(), countof(m_guildNotice.Notice));
}


void CGuild::SetSkillData(const BYTE* in_DataPtr, const int in_DataLength)
{
	if( in_DataLength > sizeof(m_skillData) )
		return;

	memcpy(m_skillData, in_DataPtr, in_DataLength);
	m_skillDataLength = in_DataLength;
}


int CGuild::AddGuildExp(unsigned long GID, int Exp)
{
	m_exp = (int)min(INT_MAX, (__int64)m_exp + (__int64)Exp);

	for( std::vector<GUILDMINFO*>::iterator iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
	{
		if( (*iter)->GID == GID )
		{
			(*iter)->MemberExp = (int)min(INT_MAX, (__int64)(*iter)->MemberExp + (__int64)Exp);
			break;
		}
	}

	return m_exp;
}


void CGuild::AddGuildMInfo(GUILDMINFO* pMember)
{
	if( pMember == NULL )
		return;

	if( pMember->MemberExp < 0 )
		pMember->MemberExp = INT_MAX;

	this->CGuild::DeleteGuildMInfo(pMember->GID);
	m_guildMInfo.push_back(pMember);
}


void CGuild::SetEmblemVersion(int Ver)
{
	m_emblemVersion = Ver;
}


void CGuild::SetGuildLevel(int Level)
{
	m_level = Level;
}


void CGuild::SetMaxUserNum(int Num)
{
	m_maxUserNum = Num;
}


void CGuild::SetGuildExp(int Exp)
{
	m_exp = Exp;
}


void CGuild::SetGDID(unsigned long GDID)
{
	m_GDID = GDID;
}


int CGuild::GetGDID()
{
	return m_GDID;
}


int CGuild::GetLevel()
{
	return m_level;
}


char* CGuild::GetGuildName()
{
	return m_guildName;
}


char* CGuild::GetMasterName()
{
	return m_guildMasterName;
}


int CGuild::GetMaxUserNum()
{
	return m_maxUserNum;
}


int CGuild::GetHonor()
{
	return m_honor;
}


int CGuild::GetVirtue()
{
	return m_virtue;
}


int CGuild::GetType()
{
	return m_type;
}


int CGuild::GetClass()
{
	return m_class;
}


int CGuild::GetMoney()
{
	return m_money;
}


int CGuild::GetArenaWin()
{
	return m_arenaWin;
}


int CGuild::GetArenaLose()
{
	return m_arenaLose;
}


int CGuild::GetArenaDrawn()
{
	return m_arenaDrawn;
}


char* CGuild::GetManageLand()
{
	return m_manageLand;
}


int CGuild::GetExp()
{
	return m_exp;
}


int CGuild::GetEmblemVersion()
{
	return m_emblemVersion;
}


int CGuild::GetPoint()
{
	return m_point;
}


char* CGuild::GetDesc()
{
	return m_desc;
}


char* CGuild::GetNotice()
{
	return m_guildNotice.Notice;
}


char* CGuild::GetNoticeSubject()
{
	return m_guildNotice.Subject;
}


void CGuild::SetMoney(int Money)
{
	m_money = Money;
}


int CGuild::AddMoney(int Money)
{
	m_money += Money;
	return m_money;
}
