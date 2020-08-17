#pragma once
#include "Common/Packet.h"
#include "NetLib/PacketHandler.h"


class CISvrIOPacketHandler : public CPacketHandler
{
public:
	CISvrIOPacketHandler();
	virtual ~CISvrIOPacketHandler();

public:
	virtual int OnProcess();
	virtual void SetLastError(DWORD lastError);

private:
	/* this+ 0 */ //CPacketHandler baseclass_0;
	/* this+ 8 */ int m_OldHeader;
	/* this+12 */ unsigned short m_OldPacketSize;
	/* this+16 */ DWORD m_lastError;

private:
	virtual int DispatchPacket(short Header, int packetSize);
	void OnWhisper(int len);
	void OnWhisper_2(int len);
	void OnWhisperAck(int len);
	void OnUserCount(int len);
	void OnIZ_BROADCAST(const PACKET_IZ_BROADCAST* in_pPacket);
	void OnSpecialMove(int len);
	void OnAddMemberToGroup(int len);
	void OnDeleteMemberFromGroup(int len);
	void OnAckMakeGroup(int len);
	void OnGroupList(int len);
	void OnAckReqJoinGroup(int len);
	void OnReqJoinGroup(int len);
	void OnGRIDUpdate(int len);
	void OnChatParty(int len);
	void OnDisconnectAll(int len);
	void OnReqServerState(int len);
	void OnResultGuildMake(int len);
	void OnReqJoinGuild(int Len);
	void OnReqJoinGuild2(const PACKET_IZ_REQ_JOIN_GUILD2& in_packet);
	void OnAckReqJoinGuild(int Len);
	void OnUpdateCharGDID(int Len);
	void OnGuildInfo(int Len);
	void OnAckGuildZeny(int Len); //TODO
	void OnDisconnectCharacter(int len);
	void OnChangeOwnerAgit(int len);
	void OnDivorce(int len);
	void OnFriendsList(int Len);
	void OnFriendsState(int Len);
	void OnAddFriend(int Len);
	void OnDeleteFriends(int Len);
	void OnMailReqGetList(int Len);
	void OnMailReqOpen(int Len);
	void OnMailReqGetItem(int Len);
	void OnMailReqSend(int Len);
	void OnMailReceive(int Len);
	void OnMailAckMailDelete(int Len);
	void OnMailAckMailReturn(int Len);
	void OnAckLogon(int Len);
	void OnChkProcessTime(int Len);
	void OnReqGroupInfoChangeV2(int Len);
	void OnChangeGroupMaster(int len);
	void OnSeekParty(int Len);
	void OnSeekPartyMember(int Len);
	void OnIZ_MEMORIALDUNGEON_SYNC2(const int in_nPacketSize);
	void OnIZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO2(const int in_nPacketSize);
	void OnIZ_MEMORIALDUNGEON_INFO2(const int in_nPacketSize);
	void OnIZ_MEMORIALDUNGEON_MSG2(const int in_nPacketSize);
	void OnINSTANTMAP_CREATE_REQ(const PACKET_IZ_INSTANTMAP_CREATE_REQ& in_packet);
	void OnINSTANTMAP_PLAYER_ENTER(const PACKET_IZ_INSTANTMAP_PLAYER_ENTER& in_packet);
	void OnINSTNATMAP_DESTROY(const PACKET_IZ_INSTNATMAP_DESTROY& in_packet);
	void OnXX_CONNECT(const PACKET_XX_CONNECT& in_packet);
	void OnXX_DISCONNECT(const PACKET_XX_DISCONNECT& in_packet);
	void OnIZ_MEMORIALDUNGEON_MSG(const PACKET_IZ_MEMORIALDUNGEON_MSG& in_packet);
	void OnIZ_PARTY_JOIN_REQ(const PACKET_IZ_PARTY_JOIN_REQ& in_packet);
	void OnIZ_PARTY_JOIN_REQ_ACK(const PACKET_IZ_PARTY_JOIN_REQ_ACK& in_packet);
	void OnIZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO(const PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO& in_packet);
	void OnIZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY(const PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY& in_packet);
	void OnIZ_MEMORIALDUNGEON_INFO(const PACKET_IZ_MEMORIALDUNGEON_INFO& in_packet);
	void OnIZ_MEMORIALDUNGEON_NOTIFY(const PACKET_IZ_MEMORIALDUNGEON_NOTIFY& in_packet);
	void OnIZ_MEMORIALDUNGEON_SYNC(const PACKET_IZ_MEMORIALDUNGEON_SYNC& in_packet);
	void OnIZ_MEMORIALDUNGEON_VISA(const PACKET_IZ_MEMORIALDUNGEON_VISA& in_packet);
	void OnIZ_MEMORIALDUNGEON_COMMAND(const PACKET_IZ_MEMORIALDUNGEON_COMMAND& in_packet);
	void OnIZ_MEMORIALDUNGEON_OPENSTATE(const PACKET_IZ_MEMORIALDUNGEON_OPENSTATE& in_packet);
	void OnIZ_BROADCASTING_SPECIAL_ITEM_OBTAIN(const std::vector<BYTE>& in_packet);
	void OnIZ_LEAVE_GROUP(const PACKET_IZ_LEAVE_GROUP& in_packet);
	void OnIZ_GPK_DYNCODE_RELOAD(const PACKET_IZ_GPK_DYNCODE_RELOAD& in_packet);
	void OnIZ_IRMAIL_NOTIFY(const PACKET_IZ_IRMAIL_NOTIFY& in_packet);
	void OnIZ_AUTH_ACK(const PACKET_IZ_AUTH_ACK& in_packet);
	void OnIZ_INFO_ENTRY_QUEUE_APPLY(const PACKET_IZ_INFO_ENTRY_QUEUE_APPLY& in_packet);
	void OnIZ_NOTIFY_ENTRY_QUEUE_APPLY(const PACKET_IZ_NOTIFY_ENTRY_QUEUE_APPLY* in_packet);
	void OnIZ_RESULT_ENTRY_QUEUE_APPLY(const PACKET_IZ_RESULT_ENTRY_QUEUE_APPLY& in_packet);
	void OnIZ_NOTIFY_ENTRY_QUEUE_CANCEL(const PACKET_IZ_NOTIFY_ENTRY_QUEUE_CANCEL& in_packet);
	void OnIZ_RESULT_ENTRY_QUEUE_CANCEL(const PACKET_IZ_RESULT_ENTRY_QUEUE_CANCEL& in_packet);
	void OnIZ_ENTRY_QUEUE_ADMISSION(const PACKET_IZ_ENTRY_QUEUE_ADMISSION& in_packet);
	void OnIZ_NOTIFY_ENTRY_QUEUE_ADMISSION_ACCEPT(const PACKET_IZ_NOTIFY_ENTRY_QUEUE_ADMISSION_ACCEPT& in_packet);
	void OnIZ_RESULT_ENTRY_QUEUE_ADMISSION_ACCEPT(const PACKET_IZ_RESULT_ENTRY_QUEUE_ADMISSION_ACCEPT& in_packet);
	void OnIZ_NOTIFY_ENTRY_QUEUE_ADMISSION_REFUSE(const PACKET_IZ_NOTIFY_ENTRY_QUEUE_ADMISSION_REFUSE& in_packet);
	void OnIZ_RESULT_ENTRY_QUEUE_ADMISSION_REFUSE(const PACKET_IZ_RESULT_ENTRY_QUEUE_ADMISSION_REFUSE& in_packet);
	void OnIZ_LOBBY_ADMISSION(const PACKET_IZ_LOBBY_ADMISSION& in_packet);
	void OnIZ_LOBBY_ADMISSION_V2(const PACKET_IZ_LOBBY_ADMISSION_V2& in_packet);
	void OnIZ_NOTIFY_LOBBY_ADMISSION_ACCEPT(const PACKET_IZ_NOTIFY_LOBBY_ADMISSION_ACCEPT& in_packet);
	void OnIZ_RESULT_LOBBY_ADMISSION_ACCEPT(const PACKET_IZ_RESULT_LOBBY_ADMISSION_ACCEPT& in_packet);
	void OnIZ_NOTIFY_LOBBY_ADMISSION_REFUSE(const PACKET_IZ_NOTIFY_LOBBY_ADMISSION_REFUSE& in_packet);
	void OnIZ_RESULT_LOBBY_ADMISSION_REFUSE(const PACKET_IZ_RESULT_LOBBY_ADMISSION_REFUSE& in_packet);
	void OnIZ_ENTRY_QUEUE_LOGOUT(const PACKET_IZ_ENTRY_QUEUE_LOGOUT& in_packet);
	void OnIZ_ENTRY_QUEUE_MOVE_ROOM(const PACKET_IZ_ENTRY_QUEUE_MOVE_ROOM& in_packet);
	void OnIZ_LOBBY_MOVE_ROOM(const PACKET_IZ_LOBBY_MOVE_ROOM& in_packet);
	void OnIZ_ENTRY_QUEUE_RANKING(const PACKET_IZ_ENTRY_QUEUE_RANKING& in_packet);
	void OnIZ_NOTIFY_ENTRY_QUEUE_RANKING(const PACKET_IZ_NOTIFY_ENTRY_QUEUE_RANKING& in_packet);
	void OnIZ_NOTIFY_MAKERRANK(const PACKET_IZ_NOTIFY_MAKERRANK& in_packet);
	void OnIZ_SET_EFFECT_HIGH_RANKER(const PACKET_IZ_SET_EFFECT_HIGH_RANKER& in_packet);
	void OnIZ_RESET_EFFECT_HIGH_RANKER(const PACKET_IZ_RESET_EFFECT_HIGH_RANKER& in_packet);

private:
	/* this+20 */ char m_PacketBuffer[15*1024];

	friend class C2InterServerClientPacketHandler;
};


void Send_PACKET_ZI_PARTY_JOIN_REQ_ACK(unsigned long in_TargetAID, unsigned long in_GRID, PACKET_ZC_PARTY_JOIN_REQ_ACK::enumAnswer in_answer);
void DisconnectAll();
