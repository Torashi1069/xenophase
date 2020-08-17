#include "IGuildInfo.h"
#include "IGuildInfoDB.h"
#include "IGuildMgr.h"
#include "UserMgr.h"
#include "Common/Packet.h"
#include "globals.hpp"


unsigned short (&skillInfo)[15][2] = *(unsigned short(*)[15][2])DetourFindFunction(SERVER, "skillInfo"); // = { {10000,0}, {10001,0}, {10002,0}, {10003,0}, {10004,0}, {10005,0}, {10006,0}, {10007,0}, {10008,0}, {10009,0}, {10014,0}, {10010,0}, {10011,0}, {10012,0}, {10013,0} };


CIGuildInfo::CIGuildInfo(void) // line 60
{
	m_DBInfoChange = 0;
}


CIGuildInfo::~CIGuildInfo(void) // line 66
{
}


/// @patch change guild maxUserNum to 28 players (w/ GD_EXTENSION)
hook_method<int (CIGuildInfo::*)(int bNotify)> CIGuildInfo::_LoadSkill(SERVER, "CIGuildInfo::LoadSkill");
HOOKED int CIGuildInfo::LoadSkill(int bNotify)
{
//	return (this->*_LoadSkill)(bNotify);

	m_skillDataLength = g_IGuildSkillDB.CIGuildSkillDB::GetSkill(m_GDID, m_skillData, m_skillPoint);

	if( m_skillDataLength != 0 && m_skillDataLength != 60 )
	{
		memcpy(&m_skillData[20], &skillInfo[5], 40);
		m_skillDataLength = 60;
		this->CIGuildInfo::SaveSkillDB();
	}

	if( m_skillDataLength == 0 )
	{
		m_skillPoint = m_level - 1;
		g_IGuildSkillDB.CIGuildSkillDB::InsertSkill(m_GDID, m_skillPoint);

		memcpy(&m_skillData, &skillInfo, sizeof(skillInfo));
		m_skillDataLength = sizeof(skillInfo);
		this->CIGuildInfo::SaveSkillDB();
	}

	m_maxUserNum = 8 + 2 * *(WORD*)&m_skillData[18];

	if( bNotify )
		this->CIGuildInfo::NotifyGuildSkillInfo(-1);

	return 1;
}


hook_method<void (CIGuildInfo::*)(void)> CIGuildInfo::_SaveSkillDB(SERVER, "CIGuildInfo::SaveSkillDB");
void CIGuildInfo::SaveSkillDB(void)
{
	return (this->*_SaveSkillDB)();

	//TODO
}


hook_method<void (CIGuildInfo::*)(void)> CIGuildInfo::_Init(SERVER, "CIGuildInfo::Init");
void CIGuildInfo::Init(void) // line 71
{
	return (this->*_Init)();

	//TODO
}


hook_method<void (CIGuildInfo::*)(unsigned char TYPE, unsigned long ZSID, unsigned long AID, unsigned long GID, unsigned long GDID, int EmblemVer)> CIGuildInfo::_UpdateCharGDID(SERVER, "CIGuildInfo::UpdateCharGDID");
void CIGuildInfo::UpdateCharGDID(unsigned char TYPE, unsigned long ZSID, unsigned long AID, unsigned long GID, unsigned long GDID, int EmblemVer)
{
	return (this->*_UpdateCharGDID)(TYPE, ZSID, AID, GID, GDID, EmblemVer);

	//TODO
}


hook_method<void (CIGuildInfo::*)(unsigned long ZSID, unsigned long GID, unsigned long AID, char* Name, char* Account, unsigned char answer)> CIGuildInfo::_JoinGuild(SERVER, "CIGuildInfo::JoinGuild");
void CIGuildInfo::JoinGuild(unsigned long ZSID, unsigned long GID, unsigned long AID, char* Name, char* Account, unsigned char answer)
{
	return (this->*_JoinGuild)(ZSID, GID, AID, Name, Account, answer);

	unsigned long foundAID = CIGuildMgr::GetObj()->CIGuildMgr::SearchAIDMap(GID);
	if( foundAID == 0 )
		return;

	if( !answer )
	{
		PACKET_IZ_ACK_REQ_JOIN_GUILD Packet;
		Packet.PacketType = 10580;
		Packet.AID = foundAID;
		Packet.answer = 1;
		this->CIGuildInfo::Send(ZSID, sizeof(Packet), (char *)&Packet);
		return;
	}

	if( g_IGuildDB.CIGuildInfoDB::GetGDID(GID) )
	{
		PACKET_IZ_ACK_REQ_JOIN_GUILD Packet;
		Packet.PacketType = 10580;
		Packet.AID = foundAID;
		Packet.answer = 0;
		this->CIGuildInfo::Send(ZSID, sizeof(Packet), (char *)&Packet);
		return;
	}

	if( this->CGuild::GetGuildMSize() >= m_maxUserNum )
	{
		Trace("Member OverSize UserNum : %d, MaxUserNum: %d\n", this->CGuild::GetGuildMSize(), m_maxUserNum);

		PACKET_IZ_ACK_REQ_JOIN_GUILD Packet;
		Packet.PacketType = 10580;
		Packet.AID = AID;
		Packet.answer = 3;
		this->CIGuildInfo::Send(ZSID, sizeof(Packet), (char *)&Packet);
		return;
	}

	GUILDMINFO* member = this->CGuild::AllocGuildMInfo();
	if( member == NULL )
		return;

	USER_STRING_MAP_DATA* user = g_userMgr.CUserMgr::SearchUser(AID, GID);
	if( user == NULL )
		return;
	if( user->level <= 0 )
		return;

	memset(member, 0, sizeof(*member));
	this->CGuild::InitGuildMInfo(member, Name, Account, AID, m_GDID, GID, 19, 1, user->level, user->job, user->head, user->headpalette, user->sex);
	g_IGuildDB.CIGuildInfoDB::InsertGuildMember(*member);
	this->CGuild::AddGuildMInfo(member);

	PACKET_IZ_GUILD_MEMBER_ADD iz_guild_member_add;
	iz_guild_member_add.PacketType = 10599;
	iz_guild_member_add.GDID = m_GDID;
	memcpy(&iz_guild_member_add.Info, member, sizeof(iz_guild_member_add.Info));
	this->CIGuildInfo::Send(-1, sizeof(iz_guild_member_add), (char *)&iz_guild_member_add);

	this->CIGuildInfo::ChangeMemberInfo(ZSID, AID, GID, 1);
	this->CIGuildInfo::UpdateCharGDID(0, ZSID, AID, GID, m_GDID, m_emblemVersion);

	PACKET_IZ_ACK_REQ_JOIN_GUILD iz_ack_req_join_guild;
	iz_ack_req_join_guild.PacketType = 10580;
	iz_ack_req_join_guild.AID = AID;
	iz_ack_req_join_guild.ReqAID = foundAID;
	iz_ack_req_join_guild.GDID = m_GDID;
	iz_ack_req_join_guild.answer = 2;
	this->CIGuildInfo::Send(ZSID, sizeof(iz_ack_req_join_guild), (char *)&iz_ack_req_join_guild);
}


hook_method<void (CIGuildInfo::*)(int ZSID, short len, char* buf)> CIGuildInfo::_Send(SERVER, "CIGuildInfo::Send");
void CIGuildInfo::Send(int ZSID, short len, char* buf)
{
	return (this->*_Send)(ZSID, len, buf);

	//TODO
}


hook_method<void (CIGuildInfo::*)(unsigned long ZSID)> CIGuildInfo::_NotifyGuildSkillInfo(SERVER, "CIGuildInfo::NotifyGuildSkillInfo");
void CIGuildInfo::NotifyGuildSkillInfo(unsigned long ZSID)
{
	return (this->*_NotifyGuildSkillInfo)(ZSID);

	//TODO
}


hook_method<void (CIGuildInfo::*)(int bAllNotifyInfo)> CIGuildInfo::_SetAllNotifyInfo(SERVER, "CIGuildInfo::SetAllNotifyInfo");
void CIGuildInfo::SetAllNotifyInfo(int bAllNotifyInfo)
{
	return (this->*_SetAllNotifyInfo)(bAllNotifyInfo);

	//TODO
}


hook_method<int (CIGuildInfo::*)(unsigned long ZSID, unsigned long AID, unsigned long GID, int status)> CIGuildInfo::_ChangeMemberInfo(SERVER, "CIGuildInfo::ChangeMemberInfo");
int CIGuildInfo::ChangeMemberInfo(unsigned long ZSID, unsigned long AID, unsigned long GID, int status)
{
	return (this->*_ChangeMemberInfo)(ZSID, AID, GID, status);

	//TODO
}


hook_method<void (CIGuildInfo::*)(int bLevelUp)> CIGuildInfo::_OutPutGuildInfo(SERVER, "CIGuildInfo::OutPutGuildInfo");
void CIGuildInfo::OutPutGuildInfo(int bLevelUp) // line 1476
{
	return (this->*_OutPutGuildInfo)(bLevelUp);

	;
}// line 1595
