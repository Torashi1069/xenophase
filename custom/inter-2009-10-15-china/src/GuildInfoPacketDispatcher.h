#pragma once
class CIGuildInfo;


class CIGuildInfoPacketDispatcher
{
	/* this+0 */ public: //const CIGuildInfoPacketDispatcher::`vftable';
	/* this+4 */ public: CIGuildInfo* m_guildInfo;

	public: CIGuildInfoPacketDispatcher::CIGuildInfoPacketDispatcher(void);
	public: virtual CIGuildInfoPacketDispatcher::~CIGuildInfoPacketDispatcher(void);
	public: void CIGuildInfoPacketDispatcher::OnAllyGuild(unsigned long GDID, short PacketType, unsigned short Len, char* buf);
	public: void CIGuildInfoPacketDispatcher::OnChangeMaxUser(unsigned long GDID, short PacketType, unsigned short Len, char* buf);
	public: void CIGuildInfoPacketDispatcher::OnGuildNotice(unsigned long GDID, short PacketType, unsigned short Len, char* buf);
	public: void CIGuildInfoPacketDispatcher::OnRegisterGuildEmblem(unsigned long GDID, short PacketType, unsigned short Len, char* buf);
	public: void CIGuildInfoPacketDispatcher::OnReqGuildPositionInfo(unsigned long GDID, short PacketType, unsigned short Len, char* buf);
	public: void CIGuildInfoPacketDispatcher::OnReqChangePosition(unsigned long GDID, short PacketType, unsigned short Len, char* buf);
	public: void CIGuildInfoPacketDispatcher::OnGuildSkillUpdate(unsigned long GDID, short PacketType, unsigned short Len, char* buf);
	public: void CIGuildInfoPacketDispatcher::OnAddExp(unsigned long GDID, short PacketType, unsigned short Len, char* buf);
	public: void CIGuildInfoPacketDispatcher::OnGuildChat(unsigned long ZSID, unsigned long GDID, short PacketType, unsigned short Len, char* buf);
	public: void CIGuildInfoPacketDispatcher::OnReqLeaveGuild(unsigned long ZSID, unsigned long GDID, short PacketType, unsigned short Len, char* buf);
	public: void CIGuildInfoPacketDispatcher::OnReqBanGuild(unsigned long ZSID, unsigned long GDID, short PacketType, unsigned short Len, char* buf);
	public: void CIGuildInfoPacketDispatcher::OnJoinGuild(unsigned long ZSID, unsigned long GDID, short PacketType, unsigned short Len, char* buf);
	public: void CIGuildInfoPacketDispatcher::OnUpdateGuildZeny(unsigned long GDID, short PacketType, unsigned short Len, char* buf);
	public: void CIGuildInfoPacketDispatcher::SetGuildInfo(CIGuildInfo* Info);
	public: int CIGuildInfoPacketDispatcher::OnProcess(void);
	public: int CIGuildInfoPacketDispatcher::DispatchPacket(unsigned long ZSID, unsigned long GDID, short PacketType, unsigned short Len, char* buf);

private:
	static hook_method<void (CIGuildInfoPacketDispatcher::*)(unsigned long GDID, short PacketType, unsigned short Len, char* buf)> CIGuildInfoPacketDispatcher::_OnAllyGuild;
	static hook_method<void (CIGuildInfoPacketDispatcher::*)(unsigned long GDID, short PacketType, unsigned short Len, char* buf)> CIGuildInfoPacketDispatcher::_OnChangeMaxUser;
	static hook_method<void (CIGuildInfoPacketDispatcher::*)(unsigned long GDID, short PacketType, unsigned short Len, char* buf)> CIGuildInfoPacketDispatcher::_OnGuildNotice;
	static hook_method<void (CIGuildInfoPacketDispatcher::*)(unsigned long GDID, short PacketType, unsigned short Len, char* buf)> CIGuildInfoPacketDispatcher::_OnRegisterGuildEmblem;
	static hook_method<void (CIGuildInfoPacketDispatcher::*)(unsigned long GDID, short PacketType, unsigned short Len, char* buf)> CIGuildInfoPacketDispatcher::_OnReqGuildPositionInfo;
	static hook_method<void (CIGuildInfoPacketDispatcher::*)(unsigned long GDID, short PacketType, unsigned short Len, char* buf)> CIGuildInfoPacketDispatcher::_OnReqChangePosition;
	static hook_method<void (CIGuildInfoPacketDispatcher::*)(unsigned long GDID, short PacketType, unsigned short Len, char* buf)> CIGuildInfoPacketDispatcher::_OnGuildSkillUpdate;
	static hook_method<void (CIGuildInfoPacketDispatcher::*)(unsigned long GDID, short PacketType, unsigned short Len, char* buf)> CIGuildInfoPacketDispatcher::_OnAddExp;
	static hook_method<void (CIGuildInfoPacketDispatcher::*)(unsigned long ZSID, unsigned long GDID, short PacketType, unsigned short Len, char* buf)> CIGuildInfoPacketDispatcher::_OnGuildChat;
	static hook_method<void (CIGuildInfoPacketDispatcher::*)(unsigned long ZSID, unsigned long GDID, short PacketType, unsigned short Len, char* buf)> CIGuildInfoPacketDispatcher::_OnReqLeaveGuild;
	static hook_method<void (CIGuildInfoPacketDispatcher::*)(unsigned long ZSID, unsigned long GDID, short PacketType, unsigned short Len, char* buf)> CIGuildInfoPacketDispatcher::_OnReqBanGuild;
	static hook_method<void (CIGuildInfoPacketDispatcher::*)(unsigned long ZSID, unsigned long GDID, short PacketType, unsigned short Len, char* buf)> CIGuildInfoPacketDispatcher::_OnJoinGuild;
	static hook_method<void (CIGuildInfoPacketDispatcher::*)(unsigned long GDID, short PacketType, unsigned short Len, char* buf)> CIGuildInfoPacketDispatcher::_OnUpdateGuildZeny;
	static hook_method<void (CIGuildInfoPacketDispatcher::*)(CIGuildInfo* Info)> CIGuildInfoPacketDispatcher::_SetGuildInfo;
	static hook_method<int (CIGuildInfoPacketDispatcher::*)(void)> CIGuildInfoPacketDispatcher::_OnProcess;
	static hook_method<int (CIGuildInfoPacketDispatcher::*)(unsigned long ZSID, unsigned long GDID, short PacketType, unsigned short Len, char* buf)> CIGuildInfoPacketDispatcher::_DispatchPacket;
};
