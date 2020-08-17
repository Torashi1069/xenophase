#include "GuildInfoPacketDispatcher.h"
#include "IGuildInfo.h"
#include "IGuildInfoDB.h"
#include "InterServer.h"
#include "Common/Packet.h"
#include "Zsvr/CZsvrMgr.h"
#include "shared/shared.h"


CIGuildInfoPacketDispatcher::CIGuildInfoPacketDispatcher()
{
}


CIGuildInfoPacketDispatcher::~CIGuildInfoPacketDispatcher()
{
}


void CIGuildInfoPacketDispatcher::SetGuildInfo(CIGuildInfo* Info)
{
	m_guildInfo = Info;
}


int CIGuildInfoPacketDispatcher::OnProcess()
{
	return -1;
}


int CIGuildInfoPacketDispatcher::DispatchPacket(unsigned long ZSID, unsigned long GDID, short PacketType, unsigned short Len, char* buf)
{
	switch( PacketType )
	{
	case HEADER_ZI_JOIN_GUILD:
	case HEADER_ZI_JOIN_GUILD_SSO:
		this->CIGuildInfoPacketDispatcher::OnJoinGuild(ZSID, GDID, PacketType, Len, buf);
	break;
	case HEADER_ZI_REQ_BAN_GUILD:
	case HEADER_ZI_REQ_BAN_GUILD_SSO:
		this->CIGuildInfoPacketDispatcher::OnReqBanGuild(ZSID, GDID, PacketType, Len, buf);
	break;
	case HEADER_ZI_GUILD_NOTICE:
		this->CIGuildInfoPacketDispatcher::OnGuildNotice(GDID, PacketType, Len, buf);
	break;
	case HEADER_ZI_GUILD_CHAT:
		this->CIGuildInfoPacketDispatcher::OnGuildChat(ZSID, GDID, PacketType, Len, buf);
	break;
	case HEADER_ZI_ADD_EXP:
		this->CIGuildInfoPacketDispatcher::OnAddExp(GDID, PacketType, Len, buf);
	break;
	case HEADER_ZI_GUILD_ZENY:
		this->CIGuildInfoPacketDispatcher::OnUpdateGuildZeny(GDID, PacketType, Len, buf);
	break;
	case HEADER_ZI_REQ_LEAVE_GUILD:
		this->CIGuildInfoPacketDispatcher::OnReqLeaveGuild(ZSID, GDID, PacketType, Len, buf);
	break;
	case HEADER_ZI_GUILD_CHANGEMAXUSER:
		this->CIGuildInfoPacketDispatcher::OnChangeMaxUser(GDID, PacketType, Len, buf);
	break;
	case HEADER_ZI_REGISTER_GUILD_EMBLEM_IMG:
		this->CIGuildInfoPacketDispatcher::OnRegisterGuildEmblem(GDID, PacketType, Len, buf);
	break;
	case HEADER_ZI_REQ_GUILD_POSITION_INFO:
		this->CIGuildInfoPacketDispatcher::OnReqGuildPositionInfo(GDID, PacketType, Len, buf);
	break;
	case HEADER_ZI_REQ_CHANGE_MEMBERPOS:
		this->CIGuildInfoPacketDispatcher::OnReqChangePosition(GDID, PacketType, Len, buf);
	break;
	case HEADER_ZI_GDSKILL_UPDATE:
		this->CIGuildInfoPacketDispatcher::OnGuildSkillUpdate(GDID, PacketType, Len, buf);
	break;
	default:
	break;
	};

	return -1;
}


void CIGuildInfoPacketDispatcher::OnJoinGuild(unsigned long ZSID, unsigned long GDID, short PacketType, unsigned short Len, char* buf)
{
	PACKET_ZI_JOIN_GUILD& ZIPacket = *reinterpret_cast<PACKET_ZI_JOIN_GUILD*>(buf);

    m_guildInfo->CIGuildInfo::JoinGuild(ZSID, ZIPacket.GID, ZIPacket.AID, ZIPacket.Name, ZIPacket.AccountName, ZIPacket.answer);
}


void CIGuildInfoPacketDispatcher::OnReqBanGuild(unsigned long ZSID, unsigned long GDID, short PacketType, unsigned short Len, char* buf)
{
	PACKET_ZI_REQ_BAN_GUILD& Packet = *reinterpret_cast<PACKET_ZI_REQ_BAN_GUILD*>(buf);

	m_guildInfo->CIGuildInfo::BanMember(&Packet);
}


void CIGuildInfoPacketDispatcher::OnReqLeaveGuild(unsigned long ZSID, unsigned long GDID, short PacketType, unsigned short Len, char* buf)
{
	m_guildInfo->CIGuildInfo::DeleteMember(ZSID, buf);
}


void CIGuildInfoPacketDispatcher::OnAllyGuild(unsigned long GDID, short PacketType, unsigned short Len, char* buf)
{
	PACKET_ZI_ALLY_GUILD& Packet = *reinterpret_cast<PACKET_ZI_ALLY_GUILD*>(buf);

	char Buf[6 * sizeof(GUILDALLYINFO)] = {};
	int buflen = 0;

	if( g_IGuildDB.CIGuildInfoDB::GetGuildAllyInfoDB(GDID, buflen, Buf) == 0 )
		return;

	int DbAllyCount = buflen / sizeof(GUILDALLYINFO);
	int AllyCount = 0;

	GUILDALLYINFO* AllyInfo = reinterpret_cast<GUILDALLYINFO*>(Buf);
	for( int i = 0; i < DbAllyCount; ++i )
	{
		GUILDALLYINFO* NewInfo = m_guildInfo->CGuild::AllocGuildAllyInfo();
		if( NewInfo == NULL )
			return;

		memcpy(NewInfo, &AllyInfo[i], sizeof(GUILDALLYINFO));

		if( NewInfo->OpponentGDID == 0 )
			++AllyCount;
	}

	if( AllyCount >= 3 )
	{
		Trace("동맹 길드가 3개를 넘었어용... ");
		return;
	}

	char OtherGName[24] = {};
	char MyGName[24] = {};
	g_IGuildDB.CGuildDB::GetTableChar(Packet.otherGDID, 1, OtherGName, 24);
	g_IGuildDB.CGuildDB::GetTableChar(GDID, 1, MyGName, 24);

	GUILDALLYINFO Guild;
	memcpy(Guild.GuildName, OtherGName, 24);
	Guild.OpponentGDID = Packet.otherGDID;
	Guild.GDID = GDID;
	Guild.Relation = RELATED_GUILD_TYPE_ALLY;
	g_IGuildDB.CIGuildInfoDB::InsertGuildAlly(Guild);

	Guild.GDID = Packet.otherGDID; // reuse struct
	Guild.OpponentGDID = GDID;
	Guild.Relation = RELATED_GUILD_TYPE_ALLY;
	g_IGuildDB.CIGuildInfoDB::InsertGuildAlly(Guild);
}


void CIGuildInfoPacketDispatcher::OnReqGuildPositionInfo(unsigned long GDID, short PacketType, unsigned short Len, char* buf)
{
	m_guildInfo->CIGuildInfo::OnReqGuildPositionInfo(buf, Len);
}


void CIGuildInfoPacketDispatcher::OnReqChangePosition(unsigned long GDID, short PacketType, unsigned short Len, char* buf)
{
	m_guildInfo->CIGuildInfo::OnReqChangePosition(buf, Len);
}


void CIGuildInfoPacketDispatcher::OnRegisterGuildEmblem(unsigned long GDID, short PacketType, unsigned short Len, char* buf)
{
	m_guildInfo->CIGuildInfo::RegisterGuildEmblem(buf, Len);
}


void CIGuildInfoPacketDispatcher::OnGuildNotice(unsigned long GDID, short PacketType, unsigned short Len, char* buf)
{
	m_guildInfo->CIGuildInfo::GetGuildNotice(buf);
}


void CIGuildInfoPacketDispatcher::OnGuildChat(unsigned long ZSID, unsigned long GDID, short PacketType, unsigned short Len, char* buf)
{
	PACKET_ZI_GUILD_CHAT& ZIPacket = *reinterpret_cast<PACKET_ZI_GUILD_CHAT*>(buf);
	int DataLen = ZIPacket.PacketLength - sizeof(ZIPacket);

	PACKET_IZ_GUILD_CHAT IZPacket;
	IZPacket.PacketType = HEADER_IZ_GUILD_CHAT;
	IZPacket.PacketLength = sizeof(IZPacket) + DataLen;
	IZPacket.GDID = ZIPacket.GDID;
	CZsvrMgr::GetObj()->CZServerMgr::BroadCast(sizeof(IZPacket), (char*)&IZPacket);
	CZsvrMgr::GetObj()->CZServerMgr::BroadCast(DataLen, (char*)IZPacket.Text);
}


void CIGuildInfoPacketDispatcher::OnAddExp(unsigned long GDID, short PacketType, unsigned short Len, char* buf)
{
	m_guildInfo->CIGuildInfo::OnAddExp(buf);
}


void CIGuildInfoPacketDispatcher::OnUpdateGuildZeny(unsigned long GDID, short PacketType, unsigned short Len, char* buf)
{
	m_guildInfo->CIGuildInfo::OnUpdateGuildZeny(buf);
}


void CIGuildInfoPacketDispatcher::OnGuildSkillUpdate(unsigned long GDID, short PacketType, unsigned short Len, char* buf)
{
	m_guildInfo->CIGuildInfo::OnGuildSkillUpdate(buf);
}


void CIGuildInfoPacketDispatcher::OnChangeMaxUser(unsigned long GDID, short PacketType, unsigned short Len, char* buf)
{
	PACKET_ZI_GUILD_CHANGEMAXUSER& ZIPacket = *reinterpret_cast<PACKET_ZI_GUILD_CHANGEMAXUSER*>(buf);

	int oldNum = m_guildInfo->CGuild::GetMaxUserNum();
	m_guildInfo->CGuild::SetMaxUserNum(ZIPacket.maxNum);

	if( g_IGuildDB.CIGuildInfoDB::UpdateGuildInfoDB(*m_guildInfo) == -1 )
	{
		m_guildInfo->CGuild::SetMaxUserNum(oldNum);
		m_guildInfo->CIGuildInfo::NotifyAllInfo(-1);
		return;
	}

	PACKET_IZ_GUILD_CHANGEMAXUSER IZPacket;
	IZPacket.PacketType = HEADER_IZ_GUILD_CHANGEMAXUSER;
	IZPacket.GDID = m_guildInfo->CGuild::GetGDID();
	IZPacket.maxNum = ZIPacket.maxNum;
	m_guildInfo->CIGuildInfo::Send(-1, sizeof(IZPacket), (char*)&IZPacket);
}
