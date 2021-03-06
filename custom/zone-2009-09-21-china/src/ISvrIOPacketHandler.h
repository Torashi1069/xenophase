#pragma once
#include "NetLib/PacketHandler.h"
struct PACKET_IZ_INSTANTMAP_CREATE_REQ;
struct PACKET_IZ_INSTANTMAP_PLAYER_ENTER;
struct PACKET_IZ_INSTNATMAP_DESTROY;
struct PACKET_XX_CONNECT;
struct PACKET_XX_DISCONNECT;
struct PACKET_IZ_MEMORIALDUNGEON_MSG;
struct PACKET_IZ_PARTY_JOIN_REQ;
struct PACKET_IZ_PARTY_JOIN_REQ_ACK;
struct PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO;
struct PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY;
struct PACKET_IZ_MEMORIALDUNGEON_INFO;
struct PACKET_IZ_MEMORIALDUNGEON_NOTIFY;
struct PACKET_IZ_MEMORIALDUNGEON_SYNC;
struct PACKET_IZ_MEMORIALDUNGEON_VISA;
struct PACKET_IZ_MEMORIALDUNGEON_COMMAND;
struct PACKET_IZ_MEMORIALDUNGEON_OPENSTATE;
struct PACKET_IZ_LEAVE_GROUP;


class CISvrIOPacketHandler : public CPacketHandler
{
	struct vtable_t
	{
		int (CISvrIOPacketHandler::* OnProcess)(void);
		int (CPacketHandler::* OnRecvHook)(int byteTransferred, char* buf);
		void (CPacketHandler::* OnRecvOverflow)(int byteTransferred);
		void (CPacketHandler::* OnRecv)(int byteTransferred);
		void (CISvrIOPacketHandler::* OnClose)(void);
		void (CPacketHandler::* AddSendBytes)(int len);
		void (CPacketHandler::* SetQueue)(CPacketQueue* queue);
		void* (CISvrIOPacketHandler::* scalar_deleting_destructor)(unsigned int __flags);
	};

	/* this+ 0 */ public: //CPacketHandler baseclass_0;
	/* this+ 8 */ private: int m_OldHeader;
	/* this+12 */ private: unsigned short m_OldPacketSize;
	/* this+14 */ private: char m_PacketBuffer[15*1024];

	public: CISvrIOPacketHandler::CISvrIOPacketHandler(void);
	public: virtual CISvrIOPacketHandler::~CISvrIOPacketHandler(void);
	public: virtual int CISvrIOPacketHandler::OnProcess(void);
	public: virtual void CISvrIOPacketHandler::OnClose(void);
	private: int CISvrIOPacketHandler::DispatchPacket(short Header, int packetSize);
	private: void CISvrIOPacketHandler::OnWhisper(int len);
	private: void CISvrIOPacketHandler::OnWhisperAck(int len);
	private: void CISvrIOPacketHandler::OnUserCount(int len);
	private: HOOKED void CISvrIOPacketHandler::OnBroadCast(int len);
	private: void CISvrIOPacketHandler::OnSpecialMove(int len);
	private: void CISvrIOPacketHandler::OnAddMemberToGroup(int len);
	private: void CISvrIOPacketHandler::OnDeleteMemberFromGroup(int len);
	private: void CISvrIOPacketHandler::OnAckMakeGroup(int len);
	private: void CISvrIOPacketHandler::OnGroupList(int len);
	private: void CISvrIOPacketHandler::OnAckReqJoinGroup(int len);
	private: void CISvrIOPacketHandler::OnReqJoinGroup(int len);
	private: void CISvrIOPacketHandler::OnGRIDUpdate(int len);
	private: void CISvrIOPacketHandler::OnChatParty(int len);
	private: void CISvrIOPacketHandler::OnDisconnectAll(int len);
	private: void CISvrIOPacketHandler::OnReqServerState(int len);
	private: void CISvrIOPacketHandler::OnResultGuildMake(int len);
	private: void CISvrIOPacketHandler::OnReqJoinGuild(int Len);
	private: void CISvrIOPacketHandler::OnAckReqJoinGuild(int Len);
	private: void CISvrIOPacketHandler::OnUpdateCharGDID(int Len);
	private: void CISvrIOPacketHandler::OnGuildInfo(int Len);
	private: void CISvrIOPacketHandler::OnAckGuildZeny(int len);
	private: void CISvrIOPacketHandler::OnDisconnectCharacter(int len);
	private: void CISvrIOPacketHandler::OnChangeOwnerAgit(int len);
	private: void CISvrIOPacketHandler::OnDivorce(int len);
	private: void CISvrIOPacketHandler::OnFriendsList(int Len);
	private: void CISvrIOPacketHandler::OnFriendsState(int Len);
	private: void CISvrIOPacketHandler::OnAddFriend(int Len);
	private: void CISvrIOPacketHandler::OnDeleteFriends(int Len);
	private: void CISvrIOPacketHandler::OnMailReqGetList(int Len);
	private: void CISvrIOPacketHandler::OnMailReqOpen(int Len);
	private: void CISvrIOPacketHandler::OnMailReqGetItem(int Len);
	private: void CISvrIOPacketHandler::OnMailReqSend(int Len);
	private: void CISvrIOPacketHandler::OnMailReceive(int Len);
	private: void CISvrIOPacketHandler::OnMailAckMailDelete(int Len);
	private: void CISvrIOPacketHandler::OnMailAckMailReturn(int Len);
	private: void CISvrIOPacketHandler::OnAckLogon(int Len);
	private: void CISvrIOPacketHandler::OnChkProcessTime(int Len);
	private: void CISvrIOPacketHandler::OnReqGroupInfoChangeV2(int Len);
	private: void CISvrIOPacketHandler::OnSeekParty(int Len);
	private: void CISvrIOPacketHandler::OnSeekPartyMember(int Len);
	private: void CISvrIOPacketHandler::OnINSTANTMAP_CREATE_REQ(const PACKET_IZ_INSTANTMAP_CREATE_REQ& in_packet);
	private: void CISvrIOPacketHandler::OnINSTANTMAP_PLAYER_ENTER(const PACKET_IZ_INSTANTMAP_PLAYER_ENTER& in_packet);
	private: void CISvrIOPacketHandler::OnINSTNATMAP_DESTROY(const PACKET_IZ_INSTNATMAP_DESTROY& in_packet);
	private: void CISvrIOPacketHandler::OnXX_CONNECT(const PACKET_XX_CONNECT& in_packet);
	private: void CISvrIOPacketHandler::OnXX_DISCONNECT(const PACKET_XX_DISCONNECT& in_packet);
	private: void CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_MSG(const PACKET_IZ_MEMORIALDUNGEON_MSG& in_packet);
	private: void CISvrIOPacketHandler::OnIZ_PARTY_JOIN_REQ(const PACKET_IZ_PARTY_JOIN_REQ& in_packet);
	private: void CISvrIOPacketHandler::OnIZ_PARTY_JOIN_REQ_ACK(const PACKET_IZ_PARTY_JOIN_REQ_ACK& in_packet);
	private: void CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO(const PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO& in_packet);
	private: void CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY(const PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY& in_packet);
	private: void CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_INFO(const PACKET_IZ_MEMORIALDUNGEON_INFO& in_packet);
	private: void CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_NOTIFY(const PACKET_IZ_MEMORIALDUNGEON_NOTIFY& in_packet);
	private: void CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_SYNC(const PACKET_IZ_MEMORIALDUNGEON_SYNC& in_packet);
	private: void CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_VISA(const PACKET_IZ_MEMORIALDUNGEON_VISA& in_packet);
	private: void CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_COMMAND(const PACKET_IZ_MEMORIALDUNGEON_COMMAND& in_packet);
	private: void CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_OPENSTATE(const PACKET_IZ_MEMORIALDUNGEON_OPENSTATE& in_packet);
	private: void CISvrIOPacketHandler::OnIZ_LEAVE_GROUP(const PACKET_IZ_LEAVE_GROUP& in_packet);

private:
	static hook_method<int (CISvrIOPacketHandler::*)(void)> CISvrIOPacketHandler::_OnProcess;
	static hook_method<void (CISvrIOPacketHandler::*)(void)> CISvrIOPacketHandler::_OnClose;
	static hook_method<int (CISvrIOPacketHandler::*)(short Header, int packetSize)> CISvrIOPacketHandler::_DispatchPacket;
	static hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnWhisper;
	static hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnWhisperAck;
	static hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnUserCount;
	static hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnBroadCast;
	static hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnSpecialMove;
	static hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnAddMemberToGroup;
	static hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnDeleteMemberFromGroup;
	static hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnAckMakeGroup;
	static hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnGroupList;
	static hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnAckReqJoinGroup;
	static hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnReqJoinGroup;
	static hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnGRIDUpdate;
	static hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnChatParty;
	static hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnDisconnectAll;
	static hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnReqServerState;
	static hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnResultGuildMake;
	static hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnReqJoinGuild;
	static hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnAckReqJoinGuild;
	static hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnUpdateCharGDID;
	static hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnGuildInfo;
	static hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnAckGuildZeny;
	static hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnDisconnectCharacter;
	static hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnChangeOwnerAgit;
	static hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnDivorce;
	static hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnFriendsList;
	static hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnFriendsState;
	static hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnAddFriend;
	static hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnDeleteFriends;
	static hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnMailReqGetList;
	static hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnMailReqOpen;
	static hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnMailReqGetItem;
	static hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnMailReqSend;
	static hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnMailReceive;
	static hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnMailAckMailDelete;
	static hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnMailAckMailReturn;
	static hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnAckLogon;
	static hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnChkProcessTime;
	static hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnReqGroupInfoChangeV2;
	static hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnSeekParty;
	static hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnSeekPartyMember;
	static hook_method<void (CISvrIOPacketHandler::*)(const PACKET_IZ_INSTANTMAP_CREATE_REQ& in_packet)> CISvrIOPacketHandler::_OnINSTANTMAP_CREATE_REQ;
	static hook_method<void (CISvrIOPacketHandler::*)(const PACKET_IZ_INSTANTMAP_PLAYER_ENTER& in_packet)> CISvrIOPacketHandler::_OnINSTANTMAP_PLAYER_ENTER;
	static hook_method<void (CISvrIOPacketHandler::*)(const PACKET_IZ_INSTNATMAP_DESTROY& in_packet)> CISvrIOPacketHandler::_OnINSTNATMAP_DESTROY;
	static hook_method<void (CISvrIOPacketHandler::*)(const PACKET_XX_CONNECT& in_packet)> CISvrIOPacketHandler::_OnXX_CONNECT;
	static hook_method<void (CISvrIOPacketHandler::*)(const PACKET_XX_DISCONNECT& in_packet)> CISvrIOPacketHandler::_OnXX_DISCONNECT;
	static hook_method<void (CISvrIOPacketHandler::*)(const PACKET_IZ_MEMORIALDUNGEON_MSG& in_packet)> CISvrIOPacketHandler::_OnIZ_MEMORIALDUNGEON_MSG;
	static hook_method<void (CISvrIOPacketHandler::*)(const PACKET_IZ_PARTY_JOIN_REQ& in_packet)> CISvrIOPacketHandler::_OnIZ_PARTY_JOIN_REQ;
	static hook_method<void (CISvrIOPacketHandler::*)(const PACKET_IZ_PARTY_JOIN_REQ_ACK& in_packet)> CISvrIOPacketHandler::_OnIZ_PARTY_JOIN_REQ_ACK;
	static hook_method<void (CISvrIOPacketHandler::*)(const PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO& in_packet)> CISvrIOPacketHandler::_OnIZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO;
	static hook_method<void (CISvrIOPacketHandler::*)(const PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY& in_packet)> CISvrIOPacketHandler::_OnIZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY;
	static hook_method<void (CISvrIOPacketHandler::*)(const PACKET_IZ_MEMORIALDUNGEON_INFO& in_packet)> CISvrIOPacketHandler::_OnIZ_MEMORIALDUNGEON_INFO;
	static hook_method<void (CISvrIOPacketHandler::*)(const PACKET_IZ_MEMORIALDUNGEON_NOTIFY& in_packet)> CISvrIOPacketHandler::_OnIZ_MEMORIALDUNGEON_NOTIFY;
	static hook_method<void (CISvrIOPacketHandler::*)(const PACKET_IZ_MEMORIALDUNGEON_SYNC& in_packet)> CISvrIOPacketHandler::_OnIZ_MEMORIALDUNGEON_SYNC;
	static hook_method<void (CISvrIOPacketHandler::*)(const PACKET_IZ_MEMORIALDUNGEON_VISA& in_packet)> CISvrIOPacketHandler::_OnIZ_MEMORIALDUNGEON_VISA;
	static hook_method<void (CISvrIOPacketHandler::*)(const PACKET_IZ_MEMORIALDUNGEON_COMMAND& in_packet)> CISvrIOPacketHandler::_OnIZ_MEMORIALDUNGEON_COMMAND;
	static hook_method<void (CISvrIOPacketHandler::*)(const PACKET_IZ_MEMORIALDUNGEON_OPENSTATE& in_packet)> CISvrIOPacketHandler::_OnIZ_MEMORIALDUNGEON_OPENSTATE;
	static hook_method<void (CISvrIOPacketHandler::*)(const PACKET_IZ_LEAVE_GROUP& in_packet)> CISvrIOPacketHandler::_OnIZ_LEAVE_GROUP;
};


extern void __cdecl Send_PACKET_ZI_PARTY_JOIN_REQ_ACK(unsigned long in_TargetAID, unsigned long in_GRID, enum  PACKET_ZC_PARTY_JOIN_REQ_ACK::enumAnswer in_answer);
