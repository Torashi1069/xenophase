#include "CharacterMgr.h"
#include "MapResMgr.h"
#include "ZGuildInfo.h"
#include "Common/Packet.h"
#include "globals.hpp"
#include "shared.h" // Trace()


CZGuildInfo::CZGuildInfo(void) // line 21
{
	MemberFragNum = 0;
	m_JoinGID = 0;
}


CZGuildInfo::~CZGuildInfo(void) // line 28
{
	m_isEmblemLoad = 0;
	m_emblemSize = 0;
}


hook_method<void (CZGuildInfo::*)(void)> CZGuildInfo::_Init(SERVER, "CZGuildInfo::Init");
void CZGuildInfo::Init(void) // line 35
{
	return (this->*_Init)();

	//TODO
}


hook_method<void (CZGuildInfo::*)(void)> CZGuildInfo::_LoadEmblem(SERVER, "CZGuildInfo::LoadEmblem");
void CZGuildInfo::LoadEmblem(void) // line 623
{
	return (this->*_LoadEmblem)();

	//TODO
}


hook_method<void (CZGuildInfo::*)(char* Buf)> CZGuildInfo::_OnAddExp(SERVER, "CZGuildInfo::OnAddExp");
void CZGuildInfo::OnAddExp(char* Buf) // line 528
{
	return (this->*_OnAddExp)(Buf);

	//TODO
}


hook_method<void (CZGuildInfo::*)(char* Buf)> CZGuildInfo::_OnGetMemberFrag(SERVER, "CZGuildInfo::OnGetMemberFrag");
void CZGuildInfo::OnGetMemberFrag(char* Buf) // line 555
{
	return (this->*_OnGetMemberFrag)(Buf);

	//TODO
}


hook_method<void (CZGuildInfo::*)(char* Buf)> CZGuildInfo::_DeleteRelatedGuild(SERVER, "CZGuildInfo::DeleteRelatedGuild");
void CZGuildInfo::DeleteRelatedGuild(char* Buf) // line 505
{
	return (this->*_DeleteRelatedGuild)(Buf);

	PACKET_IZ_DELETE_RELATED_GUILD& packet = *(PACKET_IZ_DELETE_RELATED_GUILD*)Buf;

	this->CGuild::DeleteGuildAllyInfo(packet.OpponentGDID, packet.Relation);

	PACKET_ZC_DELETE_RELATED_GUILD ZCPacket;
	ZCPacket.PacketType = HEADER_ZC_DELETE_RELATED_GUILD;
	ZCPacket.OpponentGDID = packet.OpponentGDID;
	ZCPacket.Relation = packet.Relation;
	this->CZGuildInfo::BroadCast(sizeof(ZCPacket), (char*)&ZCPacket);

	Trace("DeleteRelatedGuild (%d, %d) Relation:%d\n", m_GDID, packet.OpponentGDID, packet.Relation);

	if( packet.Relation == 0 )
		g_mapResMgr->CMapResMgr::OnDeleteRelated(m_GDID, packet.OpponentGDID);
}


hook_method<int  (CZGuildInfo::*)(char* Buf)> CZGuildInfo::_GetGuildMInfo(SERVER, "CZGuildInfo::GetGuildMInfo");
int CZGuildInfo::GetGuildMInfo(char* Buf) // line 462
{
	return (this->*_GetGuildMInfo)(Buf);

	GUILD_MEMBER_INFO* p = (GUILD_MEMBER_INFO*)Buf;
	for( mystd::vector<GUILDMINFO*>::iterator it = m_guildMInfo.begin(); it != m_guildMInfo.end(); ++it )
	{
		GUILDMINFO* g = *it;

		GUILD_MEMBER_INFO Info;
		Info.AID = g->AID;
		Info.GID = g->GID;
		Info.head = g->head;
		Info.headPalette = g->headPalette;
		Info.sex = g->sex;
		Info.job = static_cast<short>(g->job);
		Info.level = static_cast<short>(g->Level);
		Info.contributionExp = g->MemberExp;
		Info.currentState = g->status;
		Info.positionID = g->PositionID;
		memcpy(Info.intro, g->Memo, sizeof(Info.intro));
		memcpy(Info.charname, g->CharName, sizeof(Info.charname));

		memcpy(p, &Info, sizeof(*p));
		++p;
	}

	return 1;
}


hook_method<void (CZGuildInfo::*)(unsigned long AID)> CZGuildInfo::_SendGuildNotice(SERVER, "CZGuildInfo::SendGuildNotice");
void CZGuildInfo::SendGuildNotice(unsigned long AID) // line 386
{
	return (this->*_SendGuildNotice)(AID);

	PACKET_ZC_GUILD_NOTICE NoticePacket;
	NoticePacket.PacketType = HEADER_ZC_GUILD_NOTICE;
	memcpy(NoticePacket.notice, m_guildNotice.Notice, sizeof(NoticePacket.notice));
	memcpy(NoticePacket.subject, m_guildNotice.Subject, sizeof(NoticePacket.subject));

	g_characterMgr->CCharacterMgr::SendMsg(NULL, AID, CM_SEND_PACKET, sizeof(NoticePacket), (int)&NoticePacket, 0, 0);
}


hook_method<void (CZGuildInfo::*)(char* buf)> CZGuildInfo::_GetGuildNotice(SERVER, "CZGuildInfo::GetGuildNotice");
void CZGuildInfo::GetGuildNotice(char* buf) // line 369
{
	return (this->*_GetGuildNotice)(buf);

	PACKET_IZ_GUILD_NOTICE& packet = *(PACKET_IZ_GUILD_NOTICE*)buf;

	m_guildNotice.GDID = packet.GDID;
	memcpy(m_guildNotice.Subject, packet.subject, sizeof(m_guildNotice.Subject));
	memcpy(m_guildNotice.Notice, packet.notice, sizeof(m_guildNotice.Notice));

	PACKET_ZC_GUILD_NOTICE NoticePacket;
	NoticePacket.PacketType = HEADER_ZC_GUILD_NOTICE;
	memcpy(NoticePacket.subject, m_guildNotice.Subject, sizeof(NoticePacket.subject));
	memcpy(NoticePacket.notice, m_guildNotice.Notice, sizeof(NoticePacket.notice));
	this->CZGuildInfo::BroadCast(sizeof(NoticePacket), (char *)&NoticePacket);
}


hook_method<void (CZGuildInfo::*)(int Len, char* Buf)> CZGuildInfo::_BroadCast(SERVER, "CZGuildInfo::BroadCast");
void CZGuildInfo::BroadCast(int Len, char* Buf) // line 107
{
	return (this->*_BroadCast)(Len, Buf);

	for( mystd::vector<GUILDMINFO*>::iterator i = m_guildMInfo.begin(); i != m_guildMInfo.end(); ++i )
		if( (*i)->status == 1 )
			g_characterMgr->CCharacterMgr::SendMsg(NULL, (*i)->AID, CM_SEND_PACKET, Len, (int)Buf, 0, 0);
}


hook_method<void (CZGuildInfo::*)(unsigned long AID)> CZGuildInfo::_NotifySkillInfo(SERVER, "CZGuildInfo::NotifySkillInfo");
void CZGuildInfo::NotifySkillInfo(unsigned long AID) // line 679
{
	return (this->*_NotifySkillInfo)(AID);

	//TODO
}


hook_method<void (CZGuildInfo::*)(char* Buf, unsigned short Len)> CZGuildInfo::_OnNotifySkillData(SERVER, "CZGuildInfo::OnNotifySkillData");
void CZGuildInfo::OnNotifySkillData(char* Buf, unsigned short Len) // line 726
{
	return (this->*_OnNotifySkillData)(Buf, Len);

	PACKET_IZ_GUILD_NOTIFYSKILLDATA& packet = *(PACKET_IZ_GUILD_NOTIFYSKILLDATA*)Buf;
	int count = (Len - sizeof(packet)) / 4;

	m_skill.clear();
	int nPointsUsed = 0;

	for( int i = 0; i < count; ++i )
	{
		WORD id = packet.Skill[i].id;
		WORD lv = packet.Skill[i].lv;
		nPointsUsed += lv;
		m_skill[id] = lv;
	}

	m_skillPoint = m_level - nPointsUsed - 1;

	if( m_skillPoint < 0 )
	{// should not happen, so reset everything
		for( mystd::map<unsigned short, unsigned short>::iterator it = m_skill.begin(); it != m_skill.end(); ++it )
			it->second = 0;

		m_skillPoint = m_level - 1;
		m_maxUserNum = 16;
	}

	for( mystd::vector<GUILDMINFO*>::iterator k = m_guildMInfo.begin(); k != m_guildMInfo.end(); ++k )
		if( (*k)->status == 1 )
			if( packet.isForceSend != 0 )
				this->CZGuildInfo::NotifySkillInfo((*k)->AID);
}


hook_method<int (CZGuildInfo::*)(unsigned short SKID)> CZGuildInfo::_GetSkillLevel(SERVER, "CZGuildInfo::GetSkillLevel");
int CZGuildInfo::GetSkillLevel(unsigned short SKID) // line 835
{
	return (this->*_GetSkillLevel)(SKID);

	mystd::map<unsigned short,unsigned short>::const_iterator it = m_skill.find(SKID);
	return ( it != m_skill.end() ) ? it->second : 0;
}


hook_method<int (CZGuildInfo::*)(void)> CZGuildInfo::_GetJoinGID(SERVER, "CZGuildInfo::GetJoinGID");
int CZGuildInfo::GetJoinGID(void) // line 900
{
	return (this->*_GetJoinGID)();

	return m_JoinGID;
}
