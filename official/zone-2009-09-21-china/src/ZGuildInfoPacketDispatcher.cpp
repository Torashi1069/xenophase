#include "CSkillTypeInfoMgr.hpp"
#include "ZGuildInfo.h"
#include "ZGuildInfoPacketDispatcher.h"
#include "Common/Packet.h"
#include "shared.h"


CZGuildInfoPacketDispatcher::CZGuildInfoPacketDispatcher(void) // line 16
{
}


CZGuildInfoPacketDispatcher::~CZGuildInfoPacketDispatcher(void) // line 20
{
}


hook_method<void (CZGuildInfoPacketDispatcher::*)(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)> CZGuildInfoPacketDispatcher::_OnDeleteRelatedGuild(SERVER, "CZGuildInfoPacketDispatcher::OnDeleteRelatedGuild");
void CZGuildInfoPacketDispatcher::OnDeleteRelatedGuild(unsigned long GDID, short PacketType, unsigned short Len, char* Buf) // line 608
{
	return (this->*_OnDeleteRelatedGuild)(GDID, PacketType, Len, Buf);

	m_guildInfo->CZGuildInfo::DeleteRelatedGuild(Buf);
}


hook_method<void (CZGuildInfoPacketDispatcher::*)(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)> CZGuildInfoPacketDispatcher::_OnGuildNotice(SERVER, "CZGuildInfoPacketDispatcher::OnGuildNotice");
void CZGuildInfoPacketDispatcher::OnGuildNotice(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)
{
	return (this->*_OnGuildNotice)(GDID, PacketType, Len, Buf);

	m_guildInfo->CZGuildInfo::GetGuildNotice(Buf);
}


hook_method<void (CZGuildInfoPacketDispatcher::*)(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)> CZGuildInfoPacketDispatcher::_GetGuildInfo(SERVER, "CZGuildInfoPacketDispatcher::GetGuildInfo");
void CZGuildInfoPacketDispatcher::GetGuildInfo(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)
{
	return (this->*_GetGuildInfo)(GDID, PacketType, Len, Buf);

	PACKET_IZ_GUILDINFO_TOD& Packet = *(PACKET_IZ_GUILDINFO_TOD*)Buf;

	GUILDINFO Guild;
	memcpy(&Guild, &Packet.Data, sizeof(Guild));

	int lv = m_guildInfo->CZGuildInfo::GetSkillLevel(SKID_GD_EXTENSION);
	if( lv >= 1 )
	{
		m_guildInfo->CGuild::SetMaxUserNum(4 * lv + 16);
		Guild.MaxUserNum = 4 * lv + 16;
		int maxusernum = g_skillTypeInfoMgr->CSkillTypeInfoMgr::SendMsg(0, SKID_GD_EXTENSION, 14, lv, 0, 0, 0);
		if( Guild.MaxUserNum != maxusernum )
			Guild.MaxUserNum = maxusernum;
	}

	m_guildInfo->CGuild::SetGuildInfo(&Guild);
	Trace("%s Guild 로딩 완료\n", Guild.Name); // "%s Guild loaded\n"
}


hook_method<int (CZGuildInfoPacketDispatcher::*)(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)> CZGuildInfoPacketDispatcher::_DispatchPacket(SERVER, "CZGuildInfoPacketDispatcher::DispatchPacket");
int CZGuildInfoPacketDispatcher::DispatchPacket(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)
{
	return (this->*_DispatchPacket)(GDID, PacketType, Len, Buf);

	//TODO
}
