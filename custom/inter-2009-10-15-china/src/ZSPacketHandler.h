#pragma once
#include "Common/Packet.h"
#include "NetLib/PacketHandler.h"
class CZServer;


class CZSPacketHandler : public CPacketHandler
{
	struct vtable_t
	{
		int (CZSPacketHandler::* OnProcess)(void);
		int (CPacketHandler::* OnRecvHook)(int byteTransferred, char* buf);
		void (CZSPacketHandler::* OnRecvOverflow)(int byteTransferred);
		void (CZSPacketHandler::* OnRecv)(int byteTransferred);
		void (CZSPacketHandler::* OnClose) (void);
		void (CPacketHandler::* SetLastError)(unsigned long lastError);
		void (CZSPacketHandler::* AddSendBytes)(int len);
		void (CPacketHandler::* SetQueue)(CPacketQueue* queue);
		void* (CZSPacketHandler::* scalar_deleting_destructor)(unsigned int flags);
	};

	/* this+0 */ public: //CPacketHandler baseclass_0;
	/* this+8 */ private: CZServer* m_zServer;

	public: CZSPacketHandler::CZSPacketHandler(void);
	public: virtual CZSPacketHandler::~CZSPacketHandler(void);
	public: void CZSPacketHandler::OnReqHostileGuild(int Len);
	public: void CZSPacketHandler::OnAllyGuild(int Len);
	public: void CZSPacketHandler::OnMakeGuild(int Len);
	public: void CZSPacketHandler::OnReqJoinGuild(int Len);
	public: void CZSPacketHandler::OnActorInit(int Len);
	public: virtual void CZSPacketHandler::OnRecvOverflow(int byteTransferred);
	public: virtual void CZSPacketHandler::OnRecv(int byteTransferred);
	public: virtual void CZSPacketHandler::OnClose(void);
	public: virtual int CZSPacketHandler::OnProcess(void);
	public: void CZSPacketHandler::SetMyOwner(CZServer* zServer);
	public: virtual void CZSPacketHandler::AddSendBytes(int len);
	private: int CZSPacketHandler::DispatchPacket(short Header, int packetSize);
	private: void CZSPacketHandler::OnZI_MEMORIALDUNGEON_SUBSCRIPTION(const PACKET_ZI_MEMORIALDUNGEON_SUBSCRIPTION& in_packet);
	private: void CZSPacketHandler::OnZI_INSTANTMAP_CREATE_RES(const PACKET_ZI_INSTANTMAP_CREATE_RES& in_packet);
	private: void CZSPacketHandler::OnZI_INSTANTMAP_ERROR(const PACKET_ZI_INSTANTMAP_ERROR& in_packet);
	private: void CZSPacketHandler::OnZI_PING(const PACKET_ZI_PING& in_packet);
	private: void CZSPacketHandler::OnZI_INSTANTMAP_ALLOW(const PACKET_ZI_INSTANTMAP_ALLOW& in_packet);
	private: void CZSPacketHandler::OnXX_DISCONNECT(const PACKET_XX_DISCONNECT& in_packet);
	private: void CZSPacketHandler::OnXX_CONNECT(const PACKET_XX_CONNECT& in_packet);
	private: void CZSPacketHandler::OnZI_PARTY_JOIN_REQ(const PACKET_ZI_PARTY_JOIN_REQ& in_packet);
	private: void CZSPacketHandler::OnZI_PARTY_JOIN_REQ_ACK(const PACKET_ZI_PARTY_JOIN_REQ_ACK& in_packet);
	private: void CZSPacketHandler::OnZI_MEMORIALDUNGEON_COMMAND(const PACKET_ZI_MEMORIALDUNGEON_COMMAND& in_packet);
	private: void CZSPacketHandler::OnZI_MEMORIALDUNGEON_VISA(const PACKET_ZI_MEMORIALDUNGEON_VISA& in_packet);
	private: void CZSPacketHandler::OnZI_REQ_LEAVE_GROUP(const PACKET_ZI_REQ_LEAVE_GROUP& in_packet);
	private: void CZSPacketHandler::OnZI_MEMORIALDUNGEON_OPENSTATE(const PACKET_ZI_MEMORIALDUNGEON_OPENSTATE& in_packet);
	private: void CZSPacketHandler::OnServerEntry(int p_Length);
	private: HOOKED void CZSPacketHandler::OnBroadCast(int len);
	private: void CZSPacketHandler::OnWhisper(const PACKET_ZI_WHISPER* in_pPacket);
	private: void CZSPacketHandler::OnWhisperAck(int len);
	private: void CZSPacketHandler::OnReqUserCount(int len);
	private: void CZSPacketHandler::OnVersion(int len);
	private: void CZSPacketHandler::OnLogon(int len);
	private: void CZSPacketHandler::OnExit(int len);
	private: void CZSPacketHandler::OnMapMove(int len);
	private: void CZSPacketHandler::OnServerMove(int Len);
	private: void CZSPacketHandler::OnMakeGroup(int len);
	private: void CZSPacketHandler::OnMakeGroup2(int len);
	private: void CZSPacketHandler::OnReqJoinGroup(int len);
	private: void CZSPacketHandler::OnJoinGroup(int len);
	private: void CZSPacketHandler::OnExpelGroupMember(int len);
	private: void CZSPacketHandler::OnChatParty(int len);
	private: void CZSPacketHandler::OnDisconnectAllPC(int len);
	private: void CZSPacketHandler::OnServerState(int len);
	private: void CZSPacketHandler::OnChangeExpOption(int len);
	private: void CZSPacketHandler::OnChangeExpOption2(int len);
	private: void CZSPacketHandler::OnLevelUp(int Len);
	private: void CZSPacketHandler::OnGuildPreload(int ZSID, unsigned short Len, char* buf);
	private: void CZSPacketHandler::OnChangeOwnerAgit(int Len);
	private: void CZSPacketHandler::OnDeleteRelatedGuild(int Len);
	private: void CZSPacketHandler::OnSpecialMove(int Len);
	private: void CZSPacketHandler::OnSpecialGIDMove(int Len);
	private: void CZSPacketHandler::OnReqDisorganizeGuild(int len);
	private: void CZSPacketHandler::OnDivorce(int len);
	private: void CZSPacketHandler::OnDeleteFriend(int Len);
	private: void CZSPacketHandler::OnAckReqAddFriends(int Len);
	private: void CZSPacketHandler::OnUpDateMakeRank(int Len);
	private: void CZSPacketHandler::OnMailGetList(int Len);
	private: void CZSPacketHandler::OnMailOpen(int Len);
	private: void CZSPacketHandler::OnMailDelete(int Len);
	private: void CZSPacketHandler::OnMailGetItem(int Len);
	private: void CZSPacketHandler::OnMailSend(int Len);
	private: void CZSPacketHandler::OnMailReturn(int Len);
	private: void CZSPacketHandler::OnEpisodeVersion(int Len);
	private: void CZSPacketHandler::OnAckProcessTime(int Len);
	private: void CZSPacketHandler::OnServerStateHanGame(int len);
	private: void CZSPacketHandler::OnGroupInfoChangeV2(int Len);
	private: void CZSPacketHandler::OnChangeGroupMaster(int Len);
	private: void CZSPacketHandler::OnSeekParty(int Len);
	private: void CZSPacketHandler::OnSeekPartyMember(int Len);
	private: void CZSPacketHandler::OnZIInterServerOrder(int Len);

private:
	static hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnReqHostileGuild;
	static hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnAllyGuild;
	static hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnMakeGuild;
	static hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnReqJoinGuild;
	static hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnActorInit;
	static hook_method<void (CZSPacketHandler::*)(int byteTransferred)> CZSPacketHandler::_OnRecvOverflow;
	static hook_method<void (CZSPacketHandler::*)(int byteTransferred)> CZSPacketHandler::_OnRecv;
	static hook_method<void (CZSPacketHandler::*)(void)> CZSPacketHandler::_OnClose;
	static hook_method<int (CZSPacketHandler::*)(void)> CZSPacketHandler::_OnProcess;
	static hook_method<void (CZSPacketHandler::*)(CZServer* zServer)> CZSPacketHandler::_SetMyOwner;
	static hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_AddSendBytes;
	static hook_method<int (CZSPacketHandler::*)(short Header, int packetSize)> CZSPacketHandler::_DispatchPacket;
	static hook_method<void (CZSPacketHandler::*)(const PACKET_ZI_MEMORIALDUNGEON_SUBSCRIPTION& in_packet)> CZSPacketHandler::_OnZI_MEMORIALDUNGEON_SUBSCRIPTION;
	static hook_method<void (CZSPacketHandler::*)(const PACKET_ZI_INSTANTMAP_CREATE_RES& in_packet)> CZSPacketHandler::_OnZI_INSTANTMAP_CREATE_RES;
	static hook_method<void (CZSPacketHandler::*)(const PACKET_ZI_INSTANTMAP_ERROR& in_packet)> CZSPacketHandler::_OnZI_INSTANTMAP_ERROR;
	static hook_method<void (CZSPacketHandler::*)(const PACKET_ZI_PING& in_packet)> CZSPacketHandler::_OnZI_PING;
	static hook_method<void (CZSPacketHandler::*)(const PACKET_ZI_INSTANTMAP_ALLOW& in_packet)> CZSPacketHandler::_OnZI_INSTANTMAP_ALLOW;
	static hook_method<void (CZSPacketHandler::*)(const PACKET_XX_DISCONNECT& in_packet)> CZSPacketHandler::_OnXX_DISCONNECT;
	static hook_method<void (CZSPacketHandler::*)(const PACKET_XX_CONNECT& in_packet)> CZSPacketHandler::_OnXX_CONNECT;
	static hook_method<void (CZSPacketHandler::*)(const PACKET_ZI_PARTY_JOIN_REQ& in_packet)> CZSPacketHandler::_OnZI_PARTY_JOIN_REQ;
	static hook_method<void (CZSPacketHandler::*)(const PACKET_ZI_PARTY_JOIN_REQ_ACK& in_packet)> CZSPacketHandler::_OnZI_PARTY_JOIN_REQ_ACK;
	static hook_method<void (CZSPacketHandler::*)(const PACKET_ZI_MEMORIALDUNGEON_COMMAND& in_packet)> CZSPacketHandler::_OnZI_MEMORIALDUNGEON_COMMAND;
	static hook_method<void (CZSPacketHandler::*)(const PACKET_ZI_MEMORIALDUNGEON_VISA& in_packet)> CZSPacketHandler::_OnZI_MEMORIALDUNGEON_VISA;
	static hook_method<void (CZSPacketHandler::*)(const PACKET_ZI_REQ_LEAVE_GROUP& in_packet)> CZSPacketHandler::_OnZI_REQ_LEAVE_GROUP;
	static hook_method<void (CZSPacketHandler::*)(const PACKET_ZI_MEMORIALDUNGEON_OPENSTATE& in_packet)> CZSPacketHandler::_OnZI_MEMORIALDUNGEON_OPENSTATE;
	static hook_method<void (CZSPacketHandler::*)(int p_Length)> CZSPacketHandler::_OnServerEntry;
	static hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnBroadCast;
	static hook_method<void (CZSPacketHandler::*)(const PACKET_ZI_WHISPER* in_pPacket)> CZSPacketHandler::_OnWhisper;
	static hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnWhisperAck;
	static hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnReqUserCount;
	static hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnVersion;
	static hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnLogon;
	static hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnExit;
	static hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnMapMove;
	static hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnServerMove;
	static hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnMakeGroup;
	static hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnMakeGroup2;
	static hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnReqJoinGroup;
	static hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnJoinGroup;
	static hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnExpelGroupMember;
	static hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnChatParty;
	static hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnDisconnectAllPC;
	static hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnServerState;
	static hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnChangeExpOption;
	static hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnChangeExpOption2;
	static hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnLevelUp;
	static hook_method<void (CZSPacketHandler::*)(int ZSID, unsigned short Len, char* buf)> CZSPacketHandler::_OnGuildPreload;
	static hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnChangeOwnerAgit;
	static hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnDeleteRelatedGuild;
	static hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnSpecialMove;
	static hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnSpecialGIDMove;
	static hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnReqDisorganizeGuild;
	static hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnDivorce;
	static hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnDeleteFriend;
	static hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnAckReqAddFriends;
	static hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnUpDateMakeRank;
	static hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnMailGetList;
	static hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnMailOpen;
	static hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnMailDelete;
	static hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnMailGetItem;
	static hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnMailSend;
	static hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnMailReturn;
	static hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnEpisodeVersion;
	static hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnAckProcessTime;
	static hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnServerStateHanGame;
	static hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnGroupInfoChangeV2;
	static hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnChangeGroupMaster;
	static hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnSeekParty;
	static hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnSeekPartyMember;
	static hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnZIInterServerOrder;
};