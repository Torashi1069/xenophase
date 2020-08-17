#pragma once
class CZGuildInfo;


class CZGuildInfoPacketDispatcher
{
	/* this+0 */ public: //const CZGuildInfoPacketDispatcher::`vftable';
	/* this+4 */ public: CZGuildInfo* m_guildInfo;

	public: CZGuildInfoPacketDispatcher::CZGuildInfoPacketDispatcher(void);
	public: virtual CZGuildInfoPacketDispatcher::~CZGuildInfoPacketDispatcher(void);
	//public: void CZGuildInfoPacketDispatcher::OnGetMemberInfoFrag(unsigned long, short, unsigned short, char *);
	//public: void CZGuildInfoPacketDispatcher::OnAddExp(unsigned long, short, unsigned short, char *);
	//public: void CZGuildInfoPacketDispatcher::OnGuildChat(unsigned long, short, unsigned short, char *);
	public: void CZGuildInfoPacketDispatcher::OnDeleteRelatedGuild(unsigned long GDID, short PacketType, unsigned short Len, char* Buf);
	//public: void CZGuildInfoPacketDispatcher::OnGuildMemberAdd(unsigned long, short, unsigned short, char *);
	public: void CZGuildInfoPacketDispatcher::OnGuildNotice(unsigned long GDID, short PacketType, unsigned short Len, char* Buf);
	//public: void CZGuildInfoPacketDispatcher::OnGetGuildEmblem(unsigned long, short, unsigned short, char *);
	//public: void CZGuildInfoPacketDispatcher::OnAckChangeMemberPos(unsigned long, short, unsigned short, char *);
	//public: void CZGuildInfoPacketDispatcher::OnAckGuildPosition(unsigned long, short, unsigned short, char *);
	//public: void CZGuildInfoPacketDispatcher::OnDisOrganizeGuildResult(unsigned long, short, unsigned short, char *);
	//public: void CZGuildInfoPacketDispatcher::OnAddAllyGuild(unsigned long, short, unsigned short, char *);
	//public: void CZGuildInfoPacketDispatcher::OnAddHostileGuild(unsigned long, short, unsigned short, char *);
	//public: void CZGuildInfoPacketDispatcher::OnUpdateCharGDID(unsigned long, short, unsigned short, char *);
	//public: void CZGuildInfoPacketDispatcher::OnUpdateCharStat(unsigned long, short, unsigned short, char *);
	//public: void CZGuildInfoPacketDispatcher::OnZenyUpdateAll(unsigned long, short, unsigned short, char *);
	//public: void CZGuildInfoPacketDispatcher::OnChangeMaxUser(unsigned long, short, unsigned short, char *);
	//public: void CZGuildInfoPacketDispatcher::OnFreeGuild(unsigned long, short, unsigned short, char *);
	//public: void CZGuildInfoPacketDispatcher::OnAckLeaveGuild(unsigned long, short, unsigned short, char *);
	//public: void CZGuildInfoPacketDispatcher::OnAckBanGuild(unsigned long, short, unsigned short, char *);
	//public: void CZGuildInfoPacketDispatcher::GetGuildBanishInfo(unsigned long, short, unsigned short, char *);
	//public: void CZGuildInfoPacketDispatcher::GetGuildMPosition(unsigned long, short, unsigned short, char *);
	public: HOOKED void CZGuildInfoPacketDispatcher::GetGuildInfo(unsigned long GDID, short PacketType, unsigned short Len, char* Buf);
	//public: void CZGuildInfoPacketDispatcher::GetGuildMInfo(unsigned long, short, unsigned short, char *);
	//public: void CZGuildInfoPacketDispatcher::GetGuildAllyInfo(unsigned long, short, unsigned short, char *);
	//public: void CZGuildInfoPacketDispatcher::SetGuildInfo(CZGuildInfo *);
	//public: void CZGuildInfoPacketDispatcher::OnMapChange(unsigned long, short, unsigned short, char *);
	//public: int CZGuildInfoPacketDispatcher::OnProcess();
	public: int CZGuildInfoPacketDispatcher::DispatchPacket(unsigned long GDID, short PacketType, unsigned short Len, char* Buf);

private:
	static hook_method<void (CZGuildInfoPacketDispatcher::*)(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)> CZGuildInfoPacketDispatcher::_OnDeleteRelatedGuild;
	static hook_method<void (CZGuildInfoPacketDispatcher::*)(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)> CZGuildInfoPacketDispatcher::_OnGuildNotice;
	static hook_method<void (CZGuildInfoPacketDispatcher::*)(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)> CZGuildInfoPacketDispatcher::_GetGuildInfo;
	static hook_method<int (CZGuildInfoPacketDispatcher::*)(unsigned long GDID, short PacketType, unsigned short Len, char* Buf)> CZGuildInfoPacketDispatcher::_DispatchPacket;
};
