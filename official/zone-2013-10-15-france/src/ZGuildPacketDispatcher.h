#pragma once
class CZGuildInfo; // #include "ZGuildInfo.h"


class CZGuildInfoPacketDispatcher
{
public:
	CZGuildInfoPacketDispatcher();
	virtual ~CZGuildInfoPacketDispatcher();

public:
	void OnGetMemberInfoFrag(unsigned long GDID, short PacketType, unsigned short Len, char* Buf);
	void OnAddExp(unsigned long GDID, short PacketType, unsigned short Len, char* Buf);
	void OnGuildChat(unsigned long GDID, short PacketType, unsigned short Len, char* Buf);
	void OnDeleteRelatedGuild(unsigned long GDID, short PacketType, unsigned short Len, char* Buf);
	void OnGuildMemberAdd(unsigned long GDID, short PacketType, unsigned short Len, char* Buf);
	void OnGuildNotice(unsigned long GDID, short PacketType, unsigned short Len, char* Buf);
	void OnAckChangeMemberPos(unsigned long GDID, short PacketType, unsigned short Len, char* Buf);
	void OnAckGuildPosition(unsigned long GDID, short PacketType, unsigned short Len, char* Buf);
	void OnDisOrganizeGuildResult(unsigned long GDID, short PacketType, unsigned short Len, char* Buf);
	void OnAddAllyGuild(unsigned long GDID, short PacketType, unsigned short Len, char* Buf);
	void OnAddHostileGuild(unsigned long GDID, short PacketType, unsigned short Len, char* Buf);
	void OnUpdateCharGDID(unsigned long GDID, short PacketType, unsigned short Len, char* Buf);
	void OnUpdateCharStat(unsigned long GDID, short PacketType, unsigned short Len, char* Buf);
	void OnZenyUpdateAll(unsigned long GDID, short PacketType, unsigned short Len, char* Buf);
	void OnChangeMaxUser(unsigned long GDID, short PacketType, unsigned short Len, char* buf);
	void OnFreeGuild(unsigned long GDID, short PacketType, unsigned short Len, char* buf);
	void OnAckLeaveGuild(unsigned long GDID, short PacketType, unsigned short Len, char* Buf);
	void OnAckBanGuild(unsigned long GDID, short PacketType, unsigned short Len, char* Buf);
	void GetGuildBanishInfo(unsigned long GDID, short PacketType, unsigned short Len, char* Buf);
	void GetGuildMPosition(unsigned long GDID, short PacketType, unsigned short Len, char* Buf);
	void GetGuildInfo(unsigned long GDID, short PacketType, unsigned short Len, char* Buf);
	void GetGuildMInfo(unsigned long GDID, short PacketType, unsigned short Len, char* Buf);
	void GetGuildAllyInfo(unsigned long GDID, short PacketType, unsigned short Len, char* Buf);
	void SetGuildInfo(CZGuildInfo* Info);
	void OnMapChange(unsigned long GDID, short PacketType, unsigned short Len, char* buf);
	int OnProcess();
	int DispatchPacket(unsigned long GDID, short PacketType, unsigned short Len, char* Buf);

public:
	/* this+0 */ //const CZGuildInfoPacketDispatcher::`vftable';
	/* this+4 */ CZGuildInfo* m_guildInfo;
};
