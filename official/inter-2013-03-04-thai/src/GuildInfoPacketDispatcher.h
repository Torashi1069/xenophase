#pragma once
class CIGuildInfo;


class CIGuildInfoPacketDispatcher
{
public:
	CIGuildInfoPacketDispatcher();
	virtual ~CIGuildInfoPacketDispatcher();

public:
	void OnAllyGuild(unsigned long GDID, short PacketType, unsigned short Len, char* buf);
	void OnChangeMaxUser(unsigned long GDID, short PacketType, unsigned short Len, char* buf);
	void OnGuildNotice(unsigned long GDID, short PacketType, unsigned short Len, char* buf);
	void OnRegisterGuildEmblem(unsigned long GDID, short PacketType, unsigned short Len, char* buf);
	void OnReqGuildPositionInfo(unsigned long GDID, short PacketType, unsigned short Len, char* buf);
	void OnReqChangePosition(unsigned long GDID, short PacketType, unsigned short Len, char* buf);
	void OnGuildSkillUpdate(unsigned long GDID, short PacketType, unsigned short Len, char* buf);
	void OnZI_LIST_JOIN_GUILD_INSERT_GID(char* buf); //TODO
	void OnAddExp(unsigned long GDID, short PacketType, unsigned short Len, char* buf);
	void OnGuildChat(unsigned long ZSID, unsigned long GDID, short PacketType, unsigned short Len, char* buf);
	void OnReqLeaveGuild(unsigned long ZSID, unsigned long GDID, short PacketType, unsigned short Len, char* buf);
	void OnReqBanGuild(unsigned long ZSID, unsigned long GDID, short PacketType, unsigned short Len, char* buf);
	void OnJoinGuild(unsigned long ZSID, unsigned long GDID, short PacketType, unsigned short Len, char* buf);
	void OnUpdateGuildZeny(unsigned long GDID, short PacketType, unsigned short Len, char* buf);
	void SetGuildInfo(CIGuildInfo* Info);

public:
	/* this+0 */ //const CIGuildInfoPacketDispatcher::`vftable';
	/* this+4 */ CIGuildInfo* m_guildInfo;

public:
	int OnProcess();
	int DispatchPacket(unsigned long ZSID, unsigned long GDID, short PacketType, unsigned short Len, char* buf);
};
