#include "CharacterMgr.h"
#include "SkillTypeInfoMgr.h"
#include "ZGuildInfo.h"
#include "ZGuildMgr.h"
#include "ZGuildPacketDispatcher.h"
#include "ZoneProcess.h"
#include "Common/Packet.h"


CZGuildInfoPacketDispatcher::CZGuildInfoPacketDispatcher()
{
}


CZGuildInfoPacketDispatcher::~CZGuildInfoPacketDispatcher()
{
}


int CZGuildInfoPacketDispatcher::OnProcess()
{
	return -1;
}


int CZGuildInfoPacketDispatcher::DispatchPacket(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)
{
	switch( PacketType )
	{
	case HEADER_IZ_MYGUILD_BASICINFO:
//	break; //FIXME: fall-through -> packet incompatible with handler
	case HEADER_IZ_ACK_LEAVE_GUILD:
		this->CZGuildInfoPacketDispatcher::OnAckLeaveGuild(GDID, PacketType, Len, Buf);
	break;
	case HEADER_IZ_REQ_DISORGANIZE_GUILD_RESULT:
		this->CZGuildInfoPacketDispatcher::OnDisOrganizeGuildResult(GDID, PacketType, Len, Buf);
	break;
	case HEADER_IZ_GUILDINFO_TOD:
		this->CZGuildInfoPacketDispatcher::GetGuildInfo(GDID, PacketType, Len, Buf);
	break;
	case HEADER_IZ_ACK_BAN_GUILD:
	case HEADER_IZ_ACK_BAN_GUILD_SSO: //FIXME: packet incompatible with handler
		this->CZGuildInfoPacketDispatcher::OnAckBanGuild(GDID, PacketType, Len, Buf);
	break;
	case HEADER_IZ_UPDATE_CHARSTAT:
		this->CZGuildInfoPacketDispatcher::OnUpdateCharStat(GDID, PacketType, Len, Buf);
	break;
	case HEADER_IZ_ADD_ALLY_GUILD:
		this->CZGuildInfoPacketDispatcher::OnAddAllyGuild(GDID, PacketType, Len, Buf);
	break;
	case HEADER_IZ_ADD_HOSTILE_GUILD:
		this->CZGuildInfoPacketDispatcher::OnAddHostileGuild(GDID, PacketType, Len, Buf);
	break;
	case HEADER_IZ_GUILD_NOTICE:
		this->CZGuildInfoPacketDispatcher::OnGuildNotice(GDID, PacketType, Len, Buf);
	break;
	case HEADER_IZ_GUILD_MEMBER_ADD:
		this->CZGuildInfoPacketDispatcher::OnGuildMemberAdd(GDID, PacketType, Len, Buf);
	break;
	case HEADER_IZ_DELETE_RELATED_GUILD:
		this->CZGuildInfoPacketDispatcher::OnDeleteRelatedGuild(GDID, PacketType, Len, Buf);
	break;
	case HEADER_IZ_ADD_EXP:
		this->CZGuildInfoPacketDispatcher::OnAddExp(GDID, PacketType, Len, Buf);
	break;
	case HEADER_IZ_GUILD_MEMBERINFO_FRAG:
		this->CZGuildInfoPacketDispatcher::OnGetMemberInfoFrag(GDID, PacketType, Len, Buf);
	break;
	case HEADER_IZ_GUILD_ZENY_UPDATE_ALL:
		this->CZGuildInfoPacketDispatcher::OnZenyUpdateAll(GDID, PacketType, Len, Buf);
	break;
	case HEADER_IZ_GUILD_CHANGEMAXUSER:
		this->CZGuildInfoPacketDispatcher::OnChangeMaxUser(GDID, PacketType, Len, Buf);
	break;
	case HEADER_IZ_FREE_GUILD:
		this->CZGuildInfoPacketDispatcher::OnFreeGuild(GDID, PacketType, Len, Buf);
	break;
	case HEADER_IZ_GUILD_MAP_CHANGE:
		this->CZGuildInfoPacketDispatcher::OnMapChange(GDID, PacketType, Len, Buf);
	break;
	//...
	case HEADER_IZ_GUILD_MEMBERINFO_TOD:
		this->CZGuildInfoPacketDispatcher::GetGuildMInfo(GDID, PacketType, Len, Buf);
	break;
	case HEADER_IZ_GUILD_ALLYINFO_TOD:
		this->CZGuildInfoPacketDispatcher::GetGuildAllyInfo(GDID, PacketType, Len, Buf);
	break;
	case HEADER_IZ_GUILD_BANISHINFO_TOD:
		this->CZGuildInfoPacketDispatcher::GetGuildBanishInfo(GDID, PacketType, Len, Buf);
	break;
	case HEADER_IZ_GUILD_MPOSITION_TOD:
		this->CZGuildInfoPacketDispatcher::GetGuildMPosition(GDID, PacketType, Len, Buf);
	break;
	case HEADER_IZ_ACK_GUILD_POSITION_INFO:
		this->CZGuildInfoPacketDispatcher::OnAckGuildPosition(GDID, PacketType, Len, Buf);
	break;
	case HEADER_IZ_ACK_CHANGE_MEMBERPOS:
		this->CZGuildInfoPacketDispatcher::OnAckChangeMemberPos(GDID, PacketType, Len, Buf);
	break;
	case HEADER_IZ_GUILD_CHAT:
		this->CZGuildInfoPacketDispatcher::OnGuildChat(GDID, PacketType, Len, Buf);
	break;
	case HEADER_IZ_GUILD_NOTIFYSKILLDATA:
		m_guildInfo->CZGuildInfo::OnNotifySkillData(Buf, Len);
	break;
	default:
	break;
	};

	return -1;
}


void CZGuildInfoPacketDispatcher::GetGuildInfo(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)
{
	PACKET_IZ_GUILDINFO_TOD* pPacket = reinterpret_cast<PACKET_IZ_GUILDINFO_TOD*>(Buf);

	GUILDINFO Guild;
	memcpy_s(&Guild, sizeof(Guild), &pPacket->Data, sizeof(pPacket->Data));

	int skLevel = m_guildInfo->CZGuildInfo::GetSkillLevel(SKID_GD_EXTENSION);
	if( skLevel >= 1 )
	{
		m_guildInfo->CGuild::SetMaxUserNum(4 * skLevel + 16);
		Guild.MaxUserNum = 4 * skLevel + 16;

		int MaxUserNum = g_skillTypeInfoMgr.CSkillTypeInfoMgr::SendMsg(NULL, SKID_GD_EXTENSION, SM_GETINFO_SKILL, skLevel, 0, 0, 0);
		if( Guild.MaxUserNum != MaxUserNum )
			Guild.MaxUserNum = MaxUserNum;
	}

	m_guildInfo->CGuild::SetGuildInfo(&Guild);
}


void CZGuildInfoPacketDispatcher::GetGuildMInfo(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)
{
	PACKET_IZ_GUILD_MEMBERINFO_TOD* pPacket = reinterpret_cast<PACKET_IZ_GUILD_MEMBERINFO_TOD*>(Buf);

	size_t InfoLen = Len - sizeof(PACKET_IZ_GUILD_MEMBERINFO_TOD);
	int Count = InfoLen / sizeof(GUILDMINFO);

	for( int i = 0; i < Count; ++i )
	{
		GUILDMINFO* Info = m_guildInfo->CGuild::AllocGuildMInfo();
		if( Info == NULL )
			continue;

		memcpy_s(Info, sizeof(*Info), &pPacket->Info[i], sizeof(pPacket->Info[i]));
		m_guildInfo->CGuild::AddGuildMInfo(Info);
	}
}


void CZGuildInfoPacketDispatcher::GetGuildAllyInfo(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)
{
	PACKET_IZ_GUILD_ALLYINFO_TOD* pPacket = reinterpret_cast<PACKET_IZ_GUILD_ALLYINFO_TOD*>(Buf);

	size_t InfoLen = Len - sizeof(PACKET_IZ_GUILD_ALLYINFO_TOD);
	int Count = InfoLen / sizeof(GUILDALLYINFO);

	for( int i = 0; i < Count; ++i )
	{
		GUILDALLYINFO* Info = m_guildInfo->CGuild::AllocGuildAllyInfo();
		if( Info == NULL )
			continue;

		memcpy_s(Info, sizeof(*Info), &pPacket->Info[i], sizeof(pPacket->Info[i]));
		m_guildInfo->CGuild::AddGuildAllyInfo(Info);
	}
}


void CZGuildInfoPacketDispatcher::GetGuildBanishInfo(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)
{
	PACKET_IZ_GUILD_BANISHINFO_TOD* pPacket = reinterpret_cast<PACKET_IZ_GUILD_BANISHINFO_TOD*>(Buf);

	size_t InfoLen = Len - sizeof(PACKET_IZ_ACK_BAN_GUILD);
	int Count = InfoLen / sizeof(GUILDBANISHINFO);

	for( int i = 0; i < Count; ++i )
	{
		if( m_guildInfo->CGuild::GetGuildBanishSize() >= 2 )
			m_guildInfo->CGuild::DeleteFirstBanishInfo();

		GUILDBANISHINFO* Info = m_guildInfo->CGuild::AllocGuildBanishInfo();
		if( Info == NULL )
			continue;

		memcpy_s(Info, sizeof(*Info), &pPacket->Info[i], sizeof(pPacket->Info[i]));
		m_guildInfo->CGuild::AddGuildBanishInfo(Info);
	}
}


void CZGuildInfoPacketDispatcher::GetGuildMPosition(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)
{
	PACKET_IZ_GUILD_MPOSITION_TOD* pPacket = reinterpret_cast<PACKET_IZ_GUILD_MPOSITION_TOD*>(Buf);

	size_t InfoLen = Len - sizeof(PACKET_IZ_GUILD_MPOSITION_TOD);
	int Count = InfoLen / sizeof(GUILDMPOSITION);

	for( int i = 0; i < Count; ++i )
	{
		GUILDMPOSITION* Info = m_guildInfo->CGuild::AllocGuildMPosition();
		if( Info == NULL )
			continue;

		memcpy_s(Info, sizeof(*Info), &pPacket->Info[i], sizeof(pPacket->Info[i]));
		m_guildInfo->CGuild::AddGuildMPosition(Info);
	}
}


void CZGuildInfoPacketDispatcher::OnAckBanGuild(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)
{
	PACKET_IZ_ACK_BAN_GUILD* pPacket = reinterpret_cast<PACKET_IZ_ACK_BAN_GUILD*>(Buf);

	PACKET_ZC_ACK_BAN_GUILD ZCPacket;
	ZCPacket.PacketType = HEADER_ZC_ACK_BAN_GUILD;
	memcpy_s(ZCPacket.reasonDesc, sizeof(ZCPacket.reasonDesc), pPacket->reasonDesc, sizeof(pPacket->reasonDesc));
	memcpy_s(ZCPacket.charName, sizeof(ZCPacket.charName), pPacket->charName, sizeof(pPacket->charName));
	memcpy_s(ZCPacket.account, sizeof(ZCPacket.account), pPacket->AccountName, sizeof(pPacket->AccountName));
	m_guildInfo->CZGuildInfo::BroadCast(sizeof(ZCPacket), (char*)&ZCPacket);

	m_guildInfo->CZGuildInfo::BanMember((char*)pPacket);
}


void CZGuildInfoPacketDispatcher::OnAckLeaveGuild(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)
{
	PACKET_IZ_ACK_LEAVE_GUILD* pPacket = reinterpret_cast<PACKET_IZ_ACK_LEAVE_GUILD*>(Buf);

	PACKET_ZC_ACK_LEAVE_GUILD ZCPacket;
	ZCPacket.PacketType = HEADER_ZC_ACK_LEAVE_GUILD;
	memcpy_s(ZCPacket.reasonDesc, sizeof(ZCPacket.reasonDesc), pPacket->reasonDesc, sizeof(pPacket->reasonDesc));
	memcpy_s(ZCPacket.charName, sizeof(ZCPacket.charName), pPacket->charName, sizeof(pPacket->charName));
	m_guildInfo->CZGuildInfo::BroadCast(sizeof(ZCPacket), (char*)&ZCPacket);

	m_guildInfo->CZGuildInfo::DeleteMember(pPacket->GID);
}


void CZGuildInfoPacketDispatcher::OnUpdateCharGDID(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)
{
	/*
	*/
}


void CZGuildInfoPacketDispatcher::OnUpdateCharStat(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)
{
	PACKET_IZ_UPDATE_CHARSTAT* pPacket = reinterpret_cast<PACKET_IZ_UPDATE_CHARSTAT*>(Buf);

	m_guildInfo->CGuild::UpdateMemberStatus(pPacket->status, pPacket->GID, pPacket->job, pPacket->Level, pPacket->sex, pPacket->head, pPacket->headPalette);

	PACKET_ZC_UPDATE_CHARSTAT2 ZCPacket;
	ZCPacket.PacketType = HEADER_ZC_UPDATE_CHARSTAT2;
	ZCPacket.AID = pPacket->AID;
	ZCPacket.GID = pPacket->GID;
	ZCPacket.status = pPacket->status;
	ZCPacket.sex = pPacket->sex;
	ZCPacket.head = pPacket->head;
	ZCPacket.headPalette = pPacket->headPalette;
	m_guildInfo->CZGuildInfo::BroadCast(sizeof(ZCPacket), (char*)&ZCPacket);
}


void CZGuildInfoPacketDispatcher::OnAddAllyGuild(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)
{
	PACKET_IZ_ADD_ALLY_GUILD* pPacket = reinterpret_cast<PACKET_IZ_ADD_ALLY_GUILD*>(Buf);

	if( pPacket->answer == 3 )
	{
		PACKET_ZC_ACK_REQ_ALLY_GUILD ZCPacket;
		ZCPacket.PacketType = HEADER_ZC_ACK_REQ_ALLY_GUILD;
		ZCPacket.answer = 3;
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, pPacket->AID, CM_SEND_PACKET, sizeof(ZCPacket), (int)&ZCPacket, 0, 0);
		return;
	}

	if( pPacket->answer == 0 )
	{
		PACKET_ZC_ACK_REQ_ALLY_GUILD ZCPacket;
		ZCPacket.PacketType = HEADER_ZC_ACK_REQ_ALLY_GUILD;
		ZCPacket.answer = 0;
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, pPacket->AID, CM_SEND_PACKET, sizeof(ZCPacket), (int)&ZCPacket, 0, 0);
		return;
	}

	GUILDALLYINFO* Info = m_guildInfo->CGuild::AllocGuildAllyInfo();
	if( Info == NULL )
		return;

	memcpy_s(Info, sizeof(*Info), &pPacket->Ally, sizeof(pPacket->Ally));
	m_guildInfo->CGuild::AddGuildAllyInfo(Info);

	PACKET_ZC_ACK_REQ_ALLY_GUILD ZCPacket;
	ZCPacket.PacketType = HEADER_ZC_ACK_REQ_ALLY_GUILD;
	ZCPacket.answer = pPacket->answer;
	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, pPacket->AID, CM_SEND_PACKET, sizeof(ZCPacket), (int)&ZCPacket, 0, 0);

	PACKET_ZC_ADD_RELATED_GUILD RelatedGuild;
	RelatedGuild.PacketType = HEADER_ZC_ADD_RELATED_GUILD;
	RelatedGuild.Info.relation = Info->Relation;
	RelatedGuild.Info.GDID = Info->OpponentGDID;
	memcpy_s(RelatedGuild.Info.guildname, sizeof(RelatedGuild.Info.guildname), Info->GuildName, sizeof(Info->GuildName));
	m_guildInfo->CZGuildInfo::BroadCast(sizeof(RelatedGuild), (char*)&RelatedGuild);
}


void CZGuildInfoPacketDispatcher::OnAddHostileGuild(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)
{
	PACKET_IZ_ADD_HOSTILE_GUILD* pPacket = reinterpret_cast<PACKET_IZ_ADD_HOSTILE_GUILD*>(Buf);

	GUILDALLYINFO* Info = m_guildInfo->CGuild::AllocGuildAllyInfo();
	if( Info == NULL )
		return;

	memcpy_s(Info, sizeof(*Info), &pPacket->Hostile, sizeof(pPacket->Hostile));
	m_guildInfo->CGuild::AddGuildAllyInfo(Info);

	PACKET_ZC_ACK_REQ_HOSTILE_GUILD ZCPacket;
	ZCPacket.PacketType = HEADER_ZC_ACK_REQ_HOSTILE_GUILD;
	ZCPacket.result = pPacket->answer;
	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, pPacket->AID, CM_SEND_PACKET, sizeof(ZCPacket), (int)&ZCPacket, 0, 0);

	PACKET_ZC_ADD_RELATED_GUILD RelatedGuild;
	RelatedGuild.PacketType = HEADER_ZC_ADD_RELATED_GUILD;
	RelatedGuild.Info.relation = Info->Relation;
	RelatedGuild.Info.GDID = Info->OpponentGDID;
	memcpy_s(RelatedGuild.Info.guildname, sizeof(RelatedGuild.Info.guildname), Info->GuildName, sizeof(Info->GuildName));
	m_guildInfo->CZGuildInfo::BroadCast(sizeof(RelatedGuild), (char*)&RelatedGuild);
}


void CZGuildInfoPacketDispatcher::OnDisOrganizeGuildResult(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)
{
	PACKET_IZ_REQ_DISORGANIZE_GUILD_RESULT* pPacket = reinterpret_cast<PACKET_IZ_REQ_DISORGANIZE_GUILD_RESULT*>(Buf);
	m_guildInfo->CZGuildInfo::DisOrganizeGuild((char*)pPacket);
}


void CZGuildInfoPacketDispatcher::OnAckGuildPosition(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)
{
	PACKET_IZ_ACK_GUILD_POSITION_INFO* pPacket = reinterpret_cast<PACKET_IZ_ACK_GUILD_POSITION_INFO*>(Buf);
	m_guildInfo->CZGuildInfo::GetGuildPosition((char*)pPacket, Len);
}


void CZGuildInfoPacketDispatcher::OnAckChangeMemberPos(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)
{
	PACKET_IZ_ACK_CHANGE_MEMBERPOS* pPacket = reinterpret_cast<PACKET_IZ_ACK_CHANGE_MEMBERPOS*>(Buf);
	m_guildInfo->CZGuildInfo::ChangeMemberPosition((char*)pPacket, Len);
}


void CZGuildInfoPacketDispatcher::OnGuildNotice(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)
{
	PACKET_IZ_GUILD_NOTICE* pPacket = reinterpret_cast<PACKET_IZ_GUILD_NOTICE*>(Buf);
	m_guildInfo->CZGuildInfo::GetGuildNotice((char*)pPacket);
}


void CZGuildInfoPacketDispatcher::OnGuildMemberAdd(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)
{
	PACKET_IZ_GUILD_MEMBER_ADD* pPacket = reinterpret_cast<PACKET_IZ_GUILD_MEMBER_ADD*>(Buf);
	m_guildInfo->CZGuildInfo::GuildMemberAdd((char*)pPacket);
}


void CZGuildInfoPacketDispatcher::OnDeleteRelatedGuild(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)
{
	PACKET_IZ_DELETE_RELATED_GUILD* pPacket = reinterpret_cast<PACKET_IZ_DELETE_RELATED_GUILD*>(Buf);
	m_guildInfo->CZGuildInfo::DeleteRelatedGuild((char*)pPacket);
}


void CZGuildInfoPacketDispatcher::OnGuildChat(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)
{
	PACKET_IZ_GUILD_CHAT* pPacket = reinterpret_cast<PACKET_IZ_GUILD_CHAT*>(Buf);
	m_guildInfo->CZGuildInfo::SendGuildChat(pPacket->Text, pPacket->PacketLength - sizeof(PACKET_IZ_GUILD_CHAT));
}


void CZGuildInfoPacketDispatcher::OnAddExp(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)
{
	PACKET_IZ_ADD_EXP* pPacket = reinterpret_cast<PACKET_IZ_ADD_EXP*>(Buf);
	m_guildInfo->CZGuildInfo::OnAddExp((char*)pPacket);
}


void CZGuildInfoPacketDispatcher::OnGetMemberInfoFrag(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)
{
	PACKET_IZ_GUILD_MEMBERINFO_FRAG* pPacket = reinterpret_cast<PACKET_IZ_GUILD_MEMBERINFO_FRAG*>(Buf);
	m_guildInfo->CZGuildInfo::OnGetMemberFrag((char*)pPacket);
}


void CZGuildInfoPacketDispatcher::OnZenyUpdateAll(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)
{
	PACKET_IZ_GUILD_ZENY_UPDATE_ALL* pPacket = reinterpret_cast<PACKET_IZ_GUILD_ZENY_UPDATE_ALL*>(Buf);
	m_guildInfo->CZGuildInfo::OnZenyUpdateAll(Buf);
}


void CZGuildInfoPacketDispatcher::OnChangeMaxUser(unsigned long GDID, short PacketType, unsigned short Len, char* buf)
{
	PACKET_IZ_GUILD_CHANGEMAXUSER* pPacket = reinterpret_cast<PACKET_IZ_GUILD_CHANGEMAXUSER*>(buf);
	m_guildInfo->CGuild::SetMaxUserNum(pPacket->maxNum);
}


void CZGuildInfoPacketDispatcher::OnFreeGuild(unsigned long GDID, short PacketType, unsigned short Len, char* buf)
{
	PACKET_IZ_FREE_GUILD* pPacket = reinterpret_cast<PACKET_IZ_FREE_GUILD*>(buf);
	g_ZGuildMgr.CZGuildMgr::FreeGuild(m_guildInfo, FALSE);
}


void CZGuildInfoPacketDispatcher::OnMapChange(unsigned long GDID, short PacketType, unsigned short Len, char* buf)
{
	PACKET_IZ_GUILD_MAP_CHANGE* pPacket = reinterpret_cast<PACKET_IZ_GUILD_MAP_CHANGE*>(buf);
	m_guildInfo->CZGuildInfo::MapChange(pPacket->AID, pPacket->mapName);
}


void CZGuildInfoPacketDispatcher::SetGuildInfo(CZGuildInfo* Info)
{
	m_guildInfo = Info;
}
