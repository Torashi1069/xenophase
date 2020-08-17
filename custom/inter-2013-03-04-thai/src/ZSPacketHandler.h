#pragma once
#include "Common/Packet.h"
#include "NetLib/PacketHandler.h"
#include "NetLib/PacketQueue.h"
class CZServer;


class CZSPacketHandler : public CPacketHandler
{
public:
	unsigned int GetLastPacketRecvTM();
	void SetLastPacketRecvTM(unsigned int in_LastPacketRecvTM);
	void OnReqHostileGuild(int Len);
	void OnAllyGuild(int Len);
	void OnMakeGuild(int Len);
	void OnReqJoinGuild(int Len);
	void OnActorInit(int Len);

public:
	CZSPacketHandler();
	virtual ~CZSPacketHandler();
	virtual void OnRecvOverflow(int byteTransferred);
	virtual void OnRecv(int byteTransferred);
	virtual void OnClose();
	virtual int OnProcess();
	void SetMyOwner(CZServer* zServer);
	virtual void AddSendBytes(int byteTransferred);

private:
	int DispatchPacket(short Header, int packetSize);
	void OnZI_MEMORIALDUNGEON_SUBSCRIPTION2(const int in_nPacketSize);
	void OnZI_PING_LIVE(const PACKET_ZI_PING_LIVE& in_packet);
	void OnZI_STATEINFO(const PACKET_ZI_STATEINFO& in_packet);
	void OnZI_MEMORIALDUNGEON_DESTROY(const PACKET_ZI_MEMORIALDUNGEON_DESTROY& in_packet);
	void OnZI_MEMORIALDUNGEON_SUBSCRIPTION(const PACKET_ZI_MEMORIALDUNGEON_SUBSCRIPTION& in_packet);
	void OnZI_INSTANTMAP_CREATE_RES(const PACKET_ZI_INSTANTMAP_CREATE_RES& in_packet);
	void OnZI_INSTANTMAP_ERROR(const PACKET_ZI_INSTANTMAP_ERROR& in_packet);
	void OnZI_PING(const PACKET_ZI_PING& in_packet);
	void OnZI_INSTANTMAP_ALLOW(const PACKET_ZI_INSTANTMAP_ALLOW& in_packet);
	void OnXX_DISCONNECT(const PACKET_XX_DISCONNECT& in_packet);
	void OnXX_CONNECT(const PACKET_XX_CONNECT& in_packet);
	void OnZI_PARTY_JOIN_REQ(const PACKET_ZI_PARTY_JOIN_REQ& in_packet);
	void OnZI_PARTY_JOIN_REQ_ACK(const PACKET_ZI_PARTY_JOIN_REQ_ACK& in_packet);
	void OnZI_MEMORIALDUNGEON_COMMAND(const PACKET_ZI_MEMORIALDUNGEON_COMMAND& in_packet);
	void OnZI_MEMORIALDUNGEON_VISA(const PACKET_ZI_MEMORIALDUNGEON_VISA& in_packet);
	void OnZI_REQ_LEAVE_GROUP(const PACKET_ZI_REQ_LEAVE_GROUP& in_packet);
	void OnZI_MEMORIALDUNGEON_OPENSTATE(const PACKET_ZI_MEMORIALDUNGEON_OPENSTATE& in_packet);
	void OnZI_BROADCASTING_SPECIAL_ITEM_OBTAIN(const std::vector<unsigned char>& in_packet);
	void OnBroadcastPartyBookingPacket(const short in_IZPacketType, const short in_PacketSize);
	void OnZI_GPK_DYNCODE_RELOAD(const PACKET_ZI_GPK_DYNCODE_RELOAD& in_packet);
	void OnZI_INFO_ENTRY_QUEUE_APPLY(const PACKET_ZI_INFO_ENTRY_QUEUE_APPLY* in_pPacket);
	void OnZI_REQ_ENTRY_QUEUE_APPLY(const PACKET_ZI_REQ_ENTRY_QUEUE_APPLY& in_packet);
	void OnZI_RESULT_ENTRY_QUEUE_APPLY(const PACKET_ZI_RESULT_ENTRY_QUEUE_APPLY& in_packet);
	void OnZI_REQ_ENTRY_QUEUE_CANCEL(const PACKET_ZI_REQ_ENTRY_QUEUE_CANCEL& in_packet);
	void OnZI_RESULT_ENTRY_QUEUE_CANCEL(const PACKET_ZI_RESULT_ENTRY_QUEUE_CANCEL& in_packet);
	void OnZI_ENTRY_QUEUE_ADMISSION(const PACKET_ZI_ENTRY_QUEUE_ADMISSION& in_packet);
	void OnZI_ENTRY_QUEUE_ADMISSION_ACCEPT(const PACKET_ZI_ENTRY_QUEUE_ADMISSION_ACCEPT& in_packet);
	void OnZI_RESULT_ENTRY_QUEUE_ADMISSION_ACCEPT(const PACKET_ZI_RESULT_ENTRY_QUEUE_ADMISSION_ACCEPT& in_packet);
	void OnZI_ENTRY_QUEUE_ADMISSION_REFUSE(const PACKET_ZI_ENTRY_QUEUE_ADMISSION_REFUSE& in_packet);
	void OnZI_RESULT_ENTRY_QUEUE_ADMISSION_REFUSE(const PACKET_ZI_RESULT_ENTRY_QUEUE_ADMISSION_REFUSE& in_packet);
	void OnZI_LOBBY_ADMISSION(const PACKET_ZI_LOBBY_ADMISSION& in_packet);
	void OnZI_LOBBY_ADMISSION_V2(const PACKET_ZI_LOBBY_ADMISSION_V2& in_packet);
	void OnZI_LOBBY_ADMISSION_ACCEPT(const PACKET_ZI_LOBBY_ADMISSION_ACCEPT& in_packet);
	void OnZI_RESULT_LOBBY_ADMISSION_ACCEPT(const PACKET_ZI_RESULT_LOBBY_ADMISSION_ACCEPT& in_packet);
	void OnZI_LOBBY_ADMISSION_REFUSE(const PACKET_ZI_LOBBY_ADMISSION_REFUSE& in_packet);
	void OnZI_RESULT_LOBBY_ADMISSION_REFUSE(const PACKET_ZI_RESULT_LOBBY_ADMISSION_REFUSE& in_packet);
	void OnZI_ENTRY_QUEUE_MOVE_ROOM(const PACKET_ZI_ENTRY_QUEUE_MOVE_ROOM& in_packet);
	void OnZI_LOBBY_MOVE_ROOM(const PACKET_ZI_LOBBY_MOVE_ROOM& in_packet);
	void OnZI_ENTRY_QUEUE_NAME(const PACKET_ZI_ENTRY_QUEUE_NAME* in_pPacket);
	void OnZI_ENTRY_QUEUE_DELETE_GID(const PACKET_ZI_ENTRY_QUEUE_DELETE_GID& in_packet);
	void OnZI_ENTRY_QUEUE_RANKING(const PACKET_ZI_ENTRY_QUEUE_RANKING& in_packet);
	void OnZI_NOTIFY_ENTRY_QUEUE_RANKING(const PACKET_ZI_NOTIFY_ENTRY_QUEUE_RANKING& in_packet);
	void OnZI_JOB_CHANGE(const PACKET_ZI_JOB_CHANGE& in_packet);
	void OnServerEntry(int p_Length);
	void OnBroadCast(int len);
	void OnWhisper(const PACKET_ZI_WHISPER* in_pPacket);
	void OnOTHER_ZONE_PC_SEND_MSG(const PACKET_ZI_OTHER_ZONE_PC_SEND_MSG& in_packet);
	void OnWhisperAck(int len);
	void OnReqUserCount(int len);
	void OnVersion(int len);
	void OnLogon(int len);
	void OnExit(int len);
	void OnMapMove(int len);
	void OnServerMove(int Len);
	void OnMakeGroup(int len);
	void OnMakeGroup2(int len);
	void OnReqJoinGroup(int len);
	void OnJoinGroup(int len);
	void OnZI_REQ_JOIN_GUILD2(const PACKET_ZI_REQ_JOIN_GUILD2& in_packet); //TODO
	void OnExpelGroupMember(int len);
	void OnChatParty(int len);
	void OnDisconnectAllPC(int len);
	void OnServerState(int len);
	void OnServerStateChanneling(const int in_PacketLength);
	void OnChangeExpOption(int len);
	void OnChangeExpOption2(int len);
	void OnLevelUp(int Len);
	void OnGuildPreload(int ZSID, unsigned short Len, char* buf);
	void OnChangeOwnerAgit(int Len);
	void OnDeleteRelatedGuild(int Len);
	void OnSpecialMove(int Len);
	void OnSpecialMove_SSO(const int len);
	void OnSpecialGIDMove(int Len);
	void OnReqDisorganizeGuild(int len);
	void OnDivorce(int len);
	void OnDeleteFriend(int Len);
	void OnAckReqAddFriends(int Len);
	void OnUpDateMakeRank(int Len);
	void OnEpisodeVersion(int Len);
	void OnAckProcessTime(int Len);
	void OnServerStateHanGame(int len);
	void OnGroupInfoChangeV2(int Len);
	void OnChangeGroupMaster(int Len);
	void OnSeekParty(int Len);
	void OnSeekPartyMember(int Len);

private:
	/* this+ 0 */ //CPacketHandler baseclass_0;
	/* this+ 8 */ CZServer* m_zServer;
	/* this+12 */ unsigned int m_LastPacketRecvTM;
};
