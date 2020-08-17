#include "ErrorLog.h"
#include "PartyMgr.h"
#include "IGuildMgr.h"
#include "Memorial Dungeon/MemorialDungeonMgr.h"
#include "ServerInfo.h"
#include "UserMgr.h"
#include "ZServer.h"
#include "ZServerMgr.h"
#include "ZSPacketHandler.h"
#include "Common/Packet.h"
#include "enums.hpp"
#include "globals.hpp"


CZSPacketHandler::CZSPacketHandler(void)
{
}


CZSPacketHandler::~CZSPacketHandler(void)
{
}


hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnReqHostileGuild(SERVER, "CZSPacketHandler::OnReqHostileGuild");
void CZSPacketHandler::OnReqHostileGuild(int Len)
{
	return (this->*_OnReqHostileGuild)(Len);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnAllyGuild(SERVER, "CZSPacketHandler::OnAllyGuild");
void CZSPacketHandler::OnAllyGuild(int Len)
{
	return (this->*_OnAllyGuild)(Len);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnMakeGuild(SERVER, "CZSPacketHandler::OnMakeGuild");
void CZSPacketHandler::OnMakeGuild(int Len)
{
	return (this->*_OnMakeGuild)(Len);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnReqJoinGuild(SERVER, "CZSPacketHandler::OnReqJoinGuild");
void CZSPacketHandler::OnReqJoinGuild(int Len)
{
	return (this->*_OnReqJoinGuild)(Len);

	PACKET_ZI_REQ_JOIN_GUILD Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	CIGuildMgr::GetObj()->CIGuildMgr::ReqJoinGuild(m_zServer->CZServer::GetZServerID(), Packet.AID, Packet.GID, Packet.myGID, Packet.myAID);
}


hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnActorInit(SERVER, "CZSPacketHandler::OnActorInit");
void CZSPacketHandler::OnActorInit(int Len)
{
	return (this->*_OnActorInit)(Len);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(int byteTransferred)> CZSPacketHandler::_OnRecvOverflow(SERVER, "CZSPacketHandler::OnRecvOverflow");
void CZSPacketHandler::OnRecvOverflow(int byteTransferred)
{
	return (this->*_OnRecvOverflow)(byteTransferred);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(int byteTransferred)> CZSPacketHandler::_OnRecv(SERVER, "CZSPacketHandler::OnRecv");
void CZSPacketHandler::OnRecv(int byteTransferred)
{
	return (this->*_OnRecv)(byteTransferred);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(void)> CZSPacketHandler::_OnClose(SERVER, "CZSPacketHandler::OnClose");
void CZSPacketHandler::OnClose(void)
{
	return (this->*_OnClose)();

	//TODO
}


hook_method<int (CZSPacketHandler::*)(void)> CZSPacketHandler::_OnProcess(SERVER, "CZSPacketHandler::OnProcess");
int CZSPacketHandler::OnProcess(void)
{
	return (this->*_OnProcess)();

	int queueSize = m_recvQueue->CPacketQueue::GetSize();
	if( queueSize < 2 )
		return -1;

	char PacketBuffer[4];
	m_recvQueue->CPacketQueue::PeekData((queueSize < 4) ? 2 : 4, PacketBuffer);

	short Header = reinterpret_cast<PACKET*>(PacketBuffer)->PacketType;
	WORD packetSize = ( IsFixedPacket(Header) ) ? GetPacketSize(Header) : reinterpret_cast<PACKETV*>(PacketBuffer)->PacketLength;

	if( packetSize == 0 || packetSize > 65500 )
	{
		g_errorLogs.CErrorLog::CriticalErrorLogFmt(".\\ZSPacketHandler.cpp", 117, "packetsize:%d, Freesize:%d, Size:%d, header:%d", packetSize, m_recvQueue->CPacketQueue::GetFreeSize(), m_recvQueue->CPacketQueue::GetSize(), Header);
		return 0;
	}

	if( queueSize < packetSize )
		return -1;
		
	int ret = this->CZSPacketHandler::DispatchPacket(Header, packetSize);
	if( ret != -1 )
	{
		g_errorLogs.CErrorLog::CriticalErrorLogFmt(".\\ZSPacketHandler.cpp", 145, "packetsize:%d, Freesize:%d, Size:%d, header:%d", packetSize, m_recvQueue->CPacketQueue::GetFreeSize(), m_recvQueue->CPacketQueue::GetSize(), Header);
		return ret;
	}

	return -1;
}


hook_method<void (CZSPacketHandler::*)(CZServer* zServer)> CZSPacketHandler::_SetMyOwner(SERVER, "CZSPacketHandler::SetMyOwner");
void CZSPacketHandler::SetMyOwner(CZServer* zServer)
{
	return (this->*_SetMyOwner)(zServer);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_AddSendBytes(SERVER, "CZSPacketHandler::AddSendBytes");
void CZSPacketHandler::AddSendBytes(int len)
{
	return (this->*_AddSendBytes)(len);

	//TODO
}


hook_method<int (CZSPacketHandler::*)(short Header, int packetSize)> CZSPacketHandler::_DispatchPacket(SERVER, "CZSPacketHandler::DispatchPacket");
int CZSPacketHandler::DispatchPacket(short Header, int packetSize) // line 316-778
{
	return (this->*_DispatchPacket)(Header, packetSize);

	switch( Header )
	{
	case HEADER_ZI_MEMORIALDUNGEON_OPENSTATE:
	{
		PACKET_ZI_MEMORIALDUNGEON_OPENSTATE Packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);
		this->CZSPacketHandler::OnZI_MEMORIALDUNGEON_OPENSTATE(Packet);
	}
	break;
	case HEADER_ZI_MEMORIALDUNGEON_VISA:
	{
		PACKET_ZI_MEMORIALDUNGEON_VISA Packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);
		this->CZSPacketHandler::OnZI_MEMORIALDUNGEON_VISA(Packet);
	}
	break;
	case HEADER_ZI_MEMORIALDUNGEON_COMMAND:
	{
		PACKET_ZI_MEMORIALDUNGEON_COMMAND Packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);
		this->CZSPacketHandler::OnZI_MEMORIALDUNGEON_COMMAND(Packet);
	}
	break;
	case HEADER_ZI_PARTY_JOIN_REQ_ACK:
	{
		PACKET_ZI_PARTY_JOIN_REQ_ACK Packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);
		this->CZSPacketHandler::OnZI_PARTY_JOIN_REQ_ACK(Packet);
	}
	break;
	case HEADER_ZI_PARTY_JOIN_REQ:
	{
		PACKET_ZI_PARTY_JOIN_REQ Packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);
		this->CZSPacketHandler::OnZI_PARTY_JOIN_REQ(Packet);
	}
	break;
	case HEADER_XX_CONNECT:
	{
		PACKET_XX_CONNECT Packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);
		this->CZSPacketHandler::OnXX_CONNECT(Packet);
	}
	break;
	case HEADER_XX_DISCONNECT:
	{
		PACKET_XX_DISCONNECT Packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);
		this->CZSPacketHandler::OnXX_DISCONNECT(Packet);
	}
	break;
	case HEADER_ZI_INSTANTMAP_ALLOW:
	{
		PACKET_ZI_INSTANTMAP_ALLOW Packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);
		this->CZSPacketHandler::OnZI_INSTANTMAP_ALLOW(Packet);
	}
	break;
	case HEADER_ZI_PING:
	{
		PACKET_ZI_PING Packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);
		this->CZSPacketHandler::OnZI_PING(Packet);
	}
	break;
	case HEADER_ZI_INSTANTMAP_ERROR:
	{
		PACKET_ZI_INSTANTMAP_ERROR Packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);
		this->CZSPacketHandler::OnZI_INSTANTMAP_ERROR(Packet);
	}
	break;
	case HEADER_ZI_INSTANTMAP_CREATE_RES:
	{
		PACKET_ZI_INSTANTMAP_CREATE_RES Packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);
		this->CZSPacketHandler::OnZI_INSTANTMAP_CREATE_RES(Packet);
	}
	break;
	case HEADER_ZI_MEMORIALDUNGEON_SUBSCRIPTION:
	{
		PACKET_ZI_MEMORIALDUNGEON_SUBSCRIPTION Packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);
		this->CZSPacketHandler::OnZI_MEMORIALDUNGEON_SUBSCRIPTION(Packet);
	}
	break;
	case HEADER_ZI_VERSION:
	{
		this->CZSPacketHandler::OnVersion(packetSize);
	}
	break;
	case HEADER_ZI_CHAR_LEVEL_UP:
	{
		this->CZSPacketHandler::OnLevelUp(packetSize);
	}
	break;
	case HEADER_SERVER_ENTRY:
	{
		this->CZSPacketHandler::OnServerEntry(packetSize);
	}
	break;
	case HEADER_ZI_WHISPER:
	{
		char PacketBuffer[sizeof(PACKET_ZI_WHISPER) + 256 + 1];
		if( packetSize > sizeof(PacketBuffer)-1 )
			break;

		PACKET_ZI_WHISPER& Packet = *(PACKET_ZI_WHISPER*)PacketBuffer;
		m_recvQueue->CPacketQueue::GetData(packetSize, PacketBuffer);
		this->CZSPacketHandler::OnWhisper(&Packet);
	}
	break;
	case HEADER_ZI_ACK_WHISPER:
	{
		this->CZSPacketHandler::OnWhisperAck(packetSize);
	}
	break;
	case HEADER_ZI_REQ_USER_COUNT:
	{
		this->CZSPacketHandler::OnReqUserCount(packetSize);
	}
	break;
	case HEADER_ZI_BROADCAST:
	{
		this->CZSPacketHandler::OnBroadCast(packetSize);
	}
	break;
	case HEADER_ZI_LOGON:
	{
		this->CZSPacketHandler::OnLogon(packetSize);
	}
	break;
	case HEADER_ZI_EXIT:
	{
		this->CZSPacketHandler::OnExit(packetSize);
	}
	break;
	case HEADER_ZI_MAKE_GROUP:
	{
		this->CZSPacketHandler::OnMakeGroup(packetSize);
	}
	break;
	case HEADER_ZI_MAKE_GROUP2:
	{
		this->CZSPacketHandler::OnMakeGroup2(packetSize);
	}
	break;
	case HEADER_ZI_REQ_JOIN_GROUP:
	{
		this->CZSPacketHandler::OnReqJoinGroup(packetSize);
	}
	break;
	case HEADER_ZI_CHANGE_EXPOPTION:
	{
		this->CZSPacketHandler::OnChangeExpOption(packetSize);
	}
	break;
	case HEADER_ZI_CHANGE_EXPOPTION2:
	{
		this->CZSPacketHandler::OnChangeExpOption2(packetSize);
	}
	break;
	case HEADER_ZI_JOIN_GROUP:
	{
		this->CZSPacketHandler::OnJoinGroup(packetSize);
	}
	break;
	case HEADER_ZI_REQ_LEAVE_GROUP:
	{
		PACKET_ZI_REQ_LEAVE_GROUP Packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);
		this->CZSPacketHandler::OnZI_REQ_LEAVE_GROUP(Packet);
	}
	break;
	case HEADER_ZI_REQ_EXPEL_GROUP_MEMBER:
	{
		this->CZSPacketHandler::OnExpelGroupMember(packetSize);
	}
	break;
	case HEADER_ZI_MAPMOVE:
	{
		this->CZSPacketHandler::OnMapMove(packetSize);
	}
	break;
	case HEADER_ZI_CHAT_PARTY:
	{
		this->CZSPacketHandler::OnChatParty(packetSize);
	}
	break;
	case HEADER_ZI_DISCONNECT_ALL:
	{
		this->CZSPacketHandler::OnDisconnectAllPC(packetSize);
	}
	break;
	case HEADER_ZI_SERVERSTATE:
	{
		this->CZSPacketHandler::OnServerState(packetSize);
	}
	break;
	case HEADER_ZI_SERVERSTATE_HAN_GAME:
	{
		this->CZSPacketHandler::OnServerStateHanGame(packetSize);
	}
	break;
	case HEADER_ZI_MOVE:
	{
		this->CZSPacketHandler::OnSpecialMove(packetSize);
	}
	break;
	case HEADER_ZI_MOVE_GID:
	{
		this->CZSPacketHandler::OnSpecialGIDMove(packetSize);
	}
	break;
	case HEADER_ZI_DIVORCE:
	{
		this->CZSPacketHandler::OnDivorce(packetSize);
	}
	break;
	case HEADER_ZI_REQ_JOIN_GUILD:
	{
		this->CZSPacketHandler::OnReqJoinGuild(packetSize);
	}
	break;
	case HEADER_ZI_ALLY_GUILD:
	{
		this->CZSPacketHandler::OnAllyGuild(packetSize);
	}
	break;
	case HEADER_ZI_REQ_MAKE_GUILD:
	{
		this->CZSPacketHandler::OnMakeGuild(packetSize);
	}
	break;
	case HEADER_ZI_REQ_HOSTILE_GUILD:
	{
		this->CZSPacketHandler::OnReqHostileGuild(packetSize);
	}
	break;
	case HEADER_ZI_ACTOR_INIT:
	{
		this->CZSPacketHandler::OnActorInit(packetSize);
	}
	break;
	case HEADER_ZI_GUILD_CHANGEOWNER_AGIT:
	{
		this->CZSPacketHandler::OnChangeOwnerAgit(packetSize);
	}
	break;
	case HEADER_ZI_REQ_DELETE_RELATED_GUILD:
	{
		this->CZSPacketHandler::OnDeleteRelatedGuild(packetSize);
	}
	break;
	case HEADER_ZI_REQ_DISORGANIZE_GUILD:
	{
		this->CZSPacketHandler::OnReqDisorganizeGuild(packetSize);
	}
	break;
	case HEADER_ZI_REQ_LEAVE_GUILD:
	case HEADER_ZI_REQ_BAN_GUILD:
	case HEADER_ZI_JOIN_GUILD:
	case HEADER_ZI_GUILD_NOTICE:
	case HEADER_ZI_ADD_EXP:
	case HEADER_ZI_GUILD_ZENY:
	case HEADER_ZI_GUILD_CHANGEMAXUSER:
	{
		#pragma pack(push,1)
		struct TEMPHEADER {
			/* this+0 */ short PacketType;
			/* this+2 */ unsigned long GDID;
		} temp;
		#pragma pack(pop)
		m_recvQueue->CPacketQueue::PeekData(sizeof(temp), (char*)&temp);

		char PacketBuffer[10240] = {};
		m_recvQueue->CPacketQueue::GetData(packetSize, PacketBuffer);
		CIGuildMgr::GetObj()->CIGuildMgr::SendPacket(m_zServer->CZServer::GetZServerID(), temp.PacketType, temp.GDID, packetSize, PacketBuffer);
	}
	break;
	case HEADER_ZI_GUILD_PRELOAD:
	{
		#pragma pack(push,1)
		struct TEMPHEADER {
			/* this+0 */ short PacketType;
			/* this+2 */ unsigned short PacketLength;
			/* this+4 */ unsigned long GDID;
		} temp;
		#pragma pack(pop)
		m_recvQueue->CPacketQueue::PeekData(sizeof(temp), (char*)&temp);

		char PacketBuffer[10240] = {};
		m_recvQueue->CPacketQueue::GetData(packetSize, PacketBuffer);
		//NOTE: packet not used
	}
	break;
	case HEADER_ZI_REGISTER_GUILD_EMBLEM_IMG:
	case HEADER_ZI_REQ_CHANGE_MEMBERPOS:
	case HEADER_ZI_REQ_GUILD_POSITION_INFO:
	case HEADER_ZI_GUILD_CHAT:
	case HEADER_ZI_GDSKILL_UPDATE:
	{
		#pragma pack(push,1)
		struct TEMPHEADER {
			/* this+0 */ short PacketType;
			/* this+2 */ unsigned short PacketLength;
			/* this+4 */ unsigned long GDID;
		} temp;
		#pragma pack(pop)
		m_recvQueue->CPacketQueue::PeekData(sizeof(temp), (char*)&temp);

		char PacketBuffer[10240] = {};
		m_recvQueue->CPacketQueue::GetData(packetSize, PacketBuffer);
		CIGuildMgr::GetObj()->CIGuildMgr::SendPacket(m_zServer->CZServer::GetZServerID(), temp.PacketType, temp.GDID, packetSize, PacketBuffer);
	}
	break;
	case HEADER_ZI_DELETE_FRIENDS:
	{
		this->CZSPacketHandler::OnDeleteFriend(packetSize);
	}
	break;
	case HEADER_ZI_ACK_REQ_ADD_FRIENDS:
	{
		this->CZSPacketHandler::OnAckReqAddFriends(packetSize);
	}
	break;
	case HEADER_ZI_MOVE_SERVER:
	{
		this->CZSPacketHandler::OnServerMove(packetSize);
	}
	break;
	case HEADER_ZI_UPDATE_MAKERRANK:
	{
		this->CZSPacketHandler::OnUpDateMakeRank(packetSize);
	}
	break;
	case HEADER_ZI_MAIL_GET_LIST:
	{
		this->CZSPacketHandler::OnMailGetList(packetSize);
	}
	break;
	case HEADER_ZI_MAIL_OPEN:
	{
		this->CZSPacketHandler::OnMailOpen(packetSize);
	}
	break;
	case HEADER_ZI_MAIL_DELETE:
	{
		this->CZSPacketHandler::OnMailDelete(packetSize);
	}
	break;
	case HEADER_ZI_MAIL_GET_ITEM:
	{
		this->CZSPacketHandler::OnMailGetItem(packetSize);
	}
	break;
	case HEADER_ZI_MAIL_SEND:
	{
		this->CZSPacketHandler::OnMailSend(packetSize);
	}
	break;
	case HEADER_ZI_REQ_MAIL_RETURN:
	{
		this->CZSPacketHandler::OnMailReturn(packetSize);
	}
	break;
	case HEADER_ZI_EPISODE_VERSION:
	{
		this->CZSPacketHandler::OnEpisodeVersion(packetSize);
	}
	break;
	case HEADER_ZI_ACK_CHK_PROCESSTIME:
	{
		this->CZSPacketHandler::OnAckProcessTime(packetSize);
	}
	break;
	case HEADER_ZI_SEEK_PARTY:
	{
		this->CZSPacketHandler::OnSeekParty(packetSize);
	}
	break;
	case HEADER_ZI_SEEK_PARTY_MEMBER:
	{
		this->CZSPacketHandler::OnSeekPartyMember(packetSize);
	}
	break;
	case HEADER_ZI_INTERSERVER_ORDER:
	{
		this->CZSPacketHandler::OnZIInterServerOrder(packetSize);
	}
	break;
	case HEADER_CONNECTION_CLOSED:
	{
		return 0;
	}
	break;
	default:
	{
		m_zServer->AddErrorCount(".\\ZSPacketHandler.cpp", 765, 4, timeGetTime());
		m_recvQueue->CPacketQueue::Reset();
		Trace("헤더가 아님.\n");

		char buf[256];
		sprintf(buf, "ZSPacketHandler not header:%d:%d, freesize:%d, recvQueuesize:%d\n", Header, m_zServer->CZServer::GetZServerID(), m_recvQueue->CPacketQueue::GetFreeSize(), m_recvQueue->CPacketQueue::GetSize());
		g_errorLogs.CErrorLog::CriticalErrorLog(buf, 771, ".\\ZSPacketHandler.cpp");
		return 0;
	}
	break;
	}

	return -1;
}


hook_method<void (CZSPacketHandler::*)(const PACKET_ZI_MEMORIALDUNGEON_SUBSCRIPTION& in_packet)> CZSPacketHandler::_OnZI_MEMORIALDUNGEON_SUBSCRIPTION(SERVER, "CZSPacketHandler::OnZI_MEMORIALDUNGEON_SUBSCRIPTION");
void CZSPacketHandler::OnZI_MEMORIALDUNGEON_SUBSCRIPTION(const PACKET_ZI_MEMORIALDUNGEON_SUBSCRIPTION& in_packet) // line 1887-1916
{
	return (this->*_OnZI_MEMORIALDUNGEON_SUBSCRIPTION)(in_packet);
	
	const_cast<PACKET_ZI_MEMORIALDUNGEON_SUBSCRIPTION&>(in_packet).Name[sizeof(in_packet.Name) - 1] = '\0'; // FIXME don't use const if it's gonna be modified...
	const_cast<PACKET_ZI_MEMORIALDUNGEON_SUBSCRIPTION&>(in_packet).NickName[sizeof(in_packet.NickName) - 1] = '\0'; // FIXME don't use const if it's gonna be modified...

	CParty* party = InstanceCPartyMgr()->CPartyMgr::SearchGroup(in_packet.GRID);
	if( party != NULL && in_packet.AID == party->CParty::GetMaster() )
	{
		CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::Subscription(in_packet.AID, in_packet.GID, in_packet.Name, in_packet.NickName, in_packet.GRID, party->CParty::GetGroupName());
	}
	else
	{
		PACKET_IZ_MEMORIALDUNGEON_MSG packet; memset(&packet, 0, sizeof(packet));
		packet.PacketType = HEADER_IZ_MEMORIALDUNGEON_MSG;
		packet.Notify = PACKET_IZ_MEMORIALDUNGEON_MSG::MEMORIALDUNGEON_SUBSCRIPTION_ERROR_UNKNOWN;
		memcpy(packet.MemorialDungeonName, in_packet.Name, sizeof(packet.MemorialDungeonName)); packet.MemorialDungeonName[sizeof(packet.MemorialDungeonName) - 1] = '\0';
		packet.AID = in_packet.AID;
		packet.GID = in_packet.GID;

		m_zServer->CZServer::GetAsyncStream()->CAsyncStream::Send(sizeof(packet), (const char*)&packet);
	}
}


hook_method<void (CZSPacketHandler::*)(const PACKET_ZI_INSTANTMAP_CREATE_RES& in_packet)> CZSPacketHandler::_OnZI_INSTANTMAP_CREATE_RES(SERVER, "CZSPacketHandler::OnZI_INSTANTMAP_CREATE_RES");
void CZSPacketHandler::OnZI_INSTANTMAP_CREATE_RES(const PACKET_ZI_INSTANTMAP_CREATE_RES& in_packet)
{
	return (this->*_OnZI_INSTANTMAP_CREATE_RES)(in_packet);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(const PACKET_ZI_INSTANTMAP_ERROR& in_packet)> CZSPacketHandler::_OnZI_INSTANTMAP_ERROR(SERVER, "CZSPacketHandler::OnZI_INSTANTMAP_ERROR");
void CZSPacketHandler::OnZI_INSTANTMAP_ERROR(const PACKET_ZI_INSTANTMAP_ERROR& in_packet)
{
	return (this->*_OnZI_INSTANTMAP_ERROR)(in_packet);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(const PACKET_ZI_PING& in_packet)> CZSPacketHandler::_OnZI_PING(SERVER, "CZSPacketHandler::OnZI_PING");
void CZSPacketHandler::OnZI_PING(const PACKET_ZI_PING& in_packet)
{
	return (this->*_OnZI_PING)(in_packet);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(const PACKET_ZI_INSTANTMAP_ALLOW& in_packet)> CZSPacketHandler::_OnZI_INSTANTMAP_ALLOW(SERVER, "CZSPacketHandler::OnZI_INSTANTMAP_ALLOW");
void CZSPacketHandler::OnZI_INSTANTMAP_ALLOW(const PACKET_ZI_INSTANTMAP_ALLOW& in_packet)
{
	return (this->*_OnZI_INSTANTMAP_ALLOW)(in_packet);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(const PACKET_XX_DISCONNECT& in_packet)> CZSPacketHandler::_OnXX_DISCONNECT(SERVER, "CZSPacketHandler::OnXX_DISCONNECT");
void CZSPacketHandler::OnXX_DISCONNECT(const PACKET_XX_DISCONNECT& in_packet)
{
	return (this->*_OnXX_DISCONNECT)(in_packet);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(const PACKET_XX_CONNECT& in_packet)> CZSPacketHandler::_OnXX_CONNECT(SERVER, "CZSPacketHandler::OnXX_CONNECT");
void CZSPacketHandler::OnXX_CONNECT(const PACKET_XX_CONNECT& in_packet)
{
	return (this->*_OnXX_CONNECT)(in_packet);

	//TODO
}


hook_method<void (__cdecl*)(const unsigned int in_ZSID, const char *in_pTargetCharName, const unsigned int in_RequestAID, PACKET_ZC_PARTY_JOIN_REQ_ACK::enumAnswer in_answer)> _Send_PACKET_IZ_PARTY_JOIN_REQ_ACK(SERVER, "Send_PACKET_IZ_PARTY_JOIN_REQ_ACK");
static void __cdecl Send_PACKET_IZ_PARTY_JOIN_REQ_ACK(const unsigned int in_ZSID, const char* in_pTargetCharName, const unsigned int in_RequestAID, PACKET_ZC_PARTY_JOIN_REQ_ACK::enumAnswer in_answer) // line 2011-2021
{
	return (*_Send_PACKET_IZ_PARTY_JOIN_REQ_ACK)(in_ZSID,in_pTargetCharName,in_RequestAID,in_answer);

	PACKET_IZ_PARTY_JOIN_REQ_ACK packet;
	packet.requestAID = 0;
	memset(packet.characterName, 0, sizeof(packet.characterName));

	packet.PacketType = HEADER_IZ_PARTY_JOIN_REQ_ACK;
	strncpy(packet.characterName, in_pTargetCharName, sizeof(packet.characterName));
	packet.requestAID = in_RequestAID;
	packet.answer = in_answer;

	g_zServerMgr.CZServerMgr::SendMsgToZServer(in_ZSID, sizeof(packet), (const char*)&packet);
}


hook_method<void (CZSPacketHandler::*)(const PACKET_ZI_PARTY_JOIN_REQ& in_packet)> CZSPacketHandler::_OnZI_PARTY_JOIN_REQ(SERVER, "CZSPacketHandler::OnZI_PARTY_JOIN_REQ");
void CZSPacketHandler::OnZI_PARTY_JOIN_REQ(const PACKET_ZI_PARTY_JOIN_REQ& in_packet) // line 2026-2066
{
	return (this->*_OnZI_PARTY_JOIN_REQ)(in_packet);

	USER_STRING_MAP_DATA* user = g_userMgr.CUserMgr::SearchUserByName((char*)in_packet.TargetCharName, 0);
	if( user == NULL )
	{
		Send_PACKET_IZ_PARTY_JOIN_REQ_ACK(m_zServer->CZServer::GetZServerID(), in_packet.TargetCharName, in_packet.senderAID, PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_UNKNOWN_CHARACTER);
		return; // user not found
	}

	if( InstanceCPartyMgr()->CPartyMgr::SearchMember(user->GID) != 0 )
	{
		Send_PACKET_IZ_PARTY_JOIN_REQ_ACK(m_zServer->CZServer::GetZServerID(), in_packet.TargetCharName, in_packet.senderAID, PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_ALREADY_OTHERGROUPM);
		return; // already in another party
	}

	CParty* party = InstanceCPartyMgr()->CPartyMgr::SearchGroup(in_packet.GRID);
	if( party == NULL )
		return; // party not found // FIXME no reply

	if( party->CParty::GetMemberCount() >= InstanceCPartyMgr()->GetMaxMemberNum() )
	{
		Send_PACKET_IZ_PARTY_JOIN_REQ_ACK(m_zServer->CZServer::GetZServerID(), in_packet.TargetCharName, in_packet.senderAID, PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_MEMBER_OVERSIZE);
		return; // party is full
	}

	PACKET_IZ_PARTY_JOIN_REQ packet;
	packet.targetAID = 0;
	packet.GRID = 0;
	memset(packet.groupName, 0, sizeof(packet.groupName));

	packet.PacketType = HEADER_IZ_PARTY_JOIN_REQ;
	packet.targetAID = user->AID;
	packet.GRID = in_packet.GRID;
	InstanceCPartyMgr()->CPartyMgr::GetGroupName(in_packet.GRID, packet.groupName);
	g_userMgr.CUserMgr::SendMsg(packet.targetAID, sizeof(packet), (char *)&packet);
}


hook_method<void (CZSPacketHandler::*)(const PACKET_ZI_PARTY_JOIN_REQ_ACK& in_packet)> CZSPacketHandler::_OnZI_PARTY_JOIN_REQ_ACK(SERVER, "CZSPacketHandler::OnZI_PARTY_JOIN_REQ_ACK");
void CZSPacketHandler::OnZI_PARTY_JOIN_REQ_ACK(const PACKET_ZI_PARTY_JOIN_REQ_ACK& in_packet) // line 2070-2129
{
	return (this->*_OnZI_PARTY_JOIN_REQ_ACK)(in_packet);

	CParty* party = InstanceCPartyMgr()->CPartyMgr::SearchGroup(in_packet.GRID);
	if( party != NULL )
		return; // party not found

	USER_STRING_MAP_DATA* user = g_userMgr.CUserMgr::SearchUser(in_packet.targetAID, 0);
	if( user == NULL )
		return; // user not found

	if( in_packet.answer == PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_JOIN_ACCEPT )
	{
		PACKET_ZC_PARTY_JOIN_REQ_ACK::enumAnswer answer;
		switch( InstanceCPartyMgr()->CPartyMgr::InsertNewMemberV2(party, user) )
		{
		case CPartyMgr::RESULTINM_OVERSIZE_MEMBER:
			answer = PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_MEMBER_OVERSIZE;
		break;
		case CPartyMgr::RESULTINM_DUPLICATE_AID:
			answer = PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_DUPLICATE;
		break;
		case CPartyMgr::RESULTINM_SUCCESS:
			answer = PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_JOIN_ACCEPT;
			party->CParty::GetGroupID(); //nop
			party->CParty::NotifyUpdateExpOption(user->AID, party->CParty::GetGroupEXPOption());
			party->CParty::NotifyGroupMembers(user->AID);
			CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::OnNewbie(user->GID, user->AID, party->CParty::GetGroupID(), user->mapName);
		break;
		default:
			answer = PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_UNKNOWN_ERROR;
		break;
		}
		Send_PACKET_IZ_PARTY_JOIN_REQ_ACK(g_userMgr.CUserMgr::SearchUserServerID(party->CParty::GetMaster()), user->characterName, party->CParty::GetMaster(), answer);
	}
}


hook_method<void (CZSPacketHandler::*)(const PACKET_ZI_MEMORIALDUNGEON_COMMAND& in_packet)> CZSPacketHandler::_OnZI_MEMORIALDUNGEON_COMMAND(SERVER, "CZSPacketHandler::OnZI_MEMORIALDUNGEON_COMMAND");
void CZSPacketHandler::OnZI_MEMORIALDUNGEON_COMMAND(const PACKET_ZI_MEMORIALDUNGEON_COMMAND& in_packet) // line 2132-2149
{
	return (this->*_OnZI_MEMORIALDUNGEON_COMMAND)(in_packet);

	if( in_packet.Command == PACKET_CZ_MEMORIALDUNGEON_COMMAND::COMMAND_MEMORIALDUNGEON_DESTROY_FORCE )
	{
		CParty* party = InstanceCPartyMgr()->CPartyMgr::SearchGroup(in_packet.partyName);
		if( party == NULL )
			return; // party not found

		CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::Command(party->CParty::GetGroupID(), in_packet.Command);
	}
	else
	{
		USER_STRING_MAP_DATA* user = g_userMgr.CUserMgr::SearchUser(in_packet.AID, in_packet.GID);
		if( user == NULL )
			return; // user not found

		if( InstanceCPartyMgr()->CPartyMgr::SearchGroup(user->GRID) == NULL )
			return; // party not found

		CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::Command(user->GRID, in_packet.Command);
	}
}


hook_method<void (CZSPacketHandler::*)(const PACKET_ZI_MEMORIALDUNGEON_VISA& in_packet)> CZSPacketHandler::_OnZI_MEMORIALDUNGEON_VISA(SERVER, "CZSPacketHandler::OnZI_MEMORIALDUNGEON_VISA");
void CZSPacketHandler::OnZI_MEMORIALDUNGEON_VISA(const PACKET_ZI_MEMORIALDUNGEON_VISA& in_packet)
{
	return (this->*_OnZI_MEMORIALDUNGEON_VISA)(in_packet);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(const PACKET_ZI_REQ_LEAVE_GROUP& in_packet)> CZSPacketHandler::_OnZI_REQ_LEAVE_GROUP(SERVER, "CZSPacketHandler::OnZI_REQ_LEAVE_GROUP");
void CZSPacketHandler::OnZI_REQ_LEAVE_GROUP(const PACKET_ZI_REQ_LEAVE_GROUP& in_packet) // line 1225-1235
{
	return (this->*_OnZI_REQ_LEAVE_GROUP)(in_packet);

	if( !InstanceCPartyMgr()->CPartyMgr::LeaveGroup(in_packet.AID, in_packet.GID) )
		return; // failed to leave group

	PACKET_IZ_LEAVE_GROUP packet;
	packet.AID = 0;
	packet.GID = 0;

	packet.PacketType = HEADER_IZ_LEAVE_GROUP;
	packet.AID = in_packet.AID;
	packet.GID = in_packet.GID;
	m_zServer->GetAsyncStream()->CAsyncStream::Send(sizeof(packet), (const char *)&packet);
}


hook_method<void (CZSPacketHandler::*)(const PACKET_ZI_MEMORIALDUNGEON_OPENSTATE& in_packet)> CZSPacketHandler::_OnZI_MEMORIALDUNGEON_OPENSTATE(SERVER, "CZSPacketHandler::OnZI_MEMORIALDUNGEON_OPENSTATE");
void CZSPacketHandler::OnZI_MEMORIALDUNGEON_OPENSTATE(const PACKET_ZI_MEMORIALDUNGEON_OPENSTATE& in_packet)
{
	return (this->*_OnZI_MEMORIALDUNGEON_OPENSTATE)(in_packet);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(int p_Length)> CZSPacketHandler::_OnServerEntry(SERVER, "CZSPacketHandler::OnServerEntry");
void CZSPacketHandler::OnServerEntry(int p_Length)
{
	return (this->*_OnServerEntry)(p_Length);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnBroadCast(SERVER, "CZSPacketHandler::OnBroadCast");
void CZSPacketHandler::OnBroadCast(int len)
{
	return (this->*_OnBroadCast)(len);

	if( len > 500 )
		return; //FIXME: flush buffer?

	char buf[512];

	PACKET_ZI_BROADCAST& zi_broadcast = *(PACKET_ZI_BROADCAST*)buf;
	m_recvQueue->CPacketQueue::GetData(len, (char*)&zi_broadcast);

	PACKET_IZ_BROADCAST& iz_broadcast = *(PACKET_IZ_BROADCAST*)buf;
	iz_broadcast.PacketType = HEADER_IZ_BROADCAST;
	g_zServerMgr.CZServerMgr::BroadCast(len, (char*)&iz_broadcast);

	if( g_isBroadCastLog == 1 )
	{
		char szBuffer[512];
		sprintf(szBuffer, " BroadCastLog = %s \n", &buf[2]); //FIXME: wrong offset
		FILE* fp = fopen("BroadCastLog.log", "a");
		if( fp )
		{
			fprintf(fp, "%s", szBuffer);
			fclose(fp);
		}
	}
}


hook_method<void (CZSPacketHandler::*)(const PACKET_ZI_WHISPER* in_pPacket)> CZSPacketHandler::_OnWhisper(SERVER, "CZSPacketHandler::OnWhisper");
void CZSPacketHandler::OnWhisper(const PACKET_ZI_WHISPER* in_pPacket)
{
	return (this->*_OnWhisper)(in_pPacket);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnWhisperAck(SERVER, "CZSPacketHandler::OnWhisperAck");
void CZSPacketHandler::OnWhisperAck(int len)
{
	return (this->*_OnWhisperAck)(len);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnReqUserCount(SERVER, "CZSPacketHandler::OnReqUserCount");
void CZSPacketHandler::OnReqUserCount(int len)
{
	return (this->*_OnReqUserCount)(len);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnVersion(SERVER, "CZSPacketHandler::OnVersion");
void CZSPacketHandler::OnVersion(int len)
{
	return (this->*_OnVersion)(len);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnLogon(SERVER, "CZSPacketHandler::OnLogon");
void CZSPacketHandler::OnLogon(int len) // line 935-973
{
	return (this->*_OnLogon)(len);

	PACKET_ZI_LOGON packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char *)&packet);

	USER_STRING_MAP_DATA data; memset(&data, 0, sizeof(data));
	data.AID = packet.AID;
	data.GID = packet.GID;
	data.ServerID = m_zServer->CZServer::GetZServerID();
	data.sex = packet.sex;
	data.job = packet.job;
	data.level = packet.level;
	data.head = packet.head;
	data.headpalette = packet.headpalette;
	memcpy(data.mapName, packet.mapName, sizeof(data.mapName));
	memcpy(data.accountName, packet.accountName, sizeof(data.accountName));
	memcpy(data.characterName, packet.charName, sizeof(data.characterName));
	data.GRID = 0;
	data.FriendNumber = 0;

	if( g_userMgr.CUserMgr::AddUser(m_zServer->CZServer::GetZServerID(), &data) == 0 )
		return; // failed to add user

	USER_STRING_MAP_DATA* user = g_userMgr.CUserMgr::SearchUser(packet.AID, packet.GID);
	if( user == NULL )
		return; // user not found

	m_zServer->CZServer::AddPlayer(user->mapName);
	CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::OnNewbie(user->GID, user->AID, user->GRID, user->mapName);
}


hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnExit(SERVER, "CZSPacketHandler::OnExit");
void CZSPacketHandler::OnExit(int len)
{
	return (this->*_OnExit)(len);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnMapMove(SERVER, "CZSPacketHandler::OnMapMove");
void CZSPacketHandler::OnMapMove(int len) // line 1259-1281
{
	return (this->*_OnMapMove)(len);

	PACKET_ZI_MAPMOVE packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char *)&packet);

	USER_STRING_MAP_DATA* user = g_userMgr.CUserMgr::SearchUser(packet.AID, 0);
	if( user == NULL )
		return; // user not found

	mystd::string previous_mapName = user->mapName;
	m_zServer->CZServer::RemovePlayer(previous_mapName);

	memcpy(user->mapName, packet.mapName, sizeof(user->mapName));
	m_zServer->CZServer::AddPlayer(user->mapName);

	CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::OnLeave(user->GID, user->AID, previous_mapName);
	CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::OnEnter(user->GRID, user->GID, user->AID, user->mapName);

	InstanceCPartyMgr()->CPartyMgr::MapMove2(user->GRID, user->AID, user->mapName);
}


hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnServerMove(SERVER, "CZSPacketHandler::OnServerMove");
void CZSPacketHandler::OnServerMove(int Len)
{
	return (this->*_OnServerMove)(Len);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnMakeGroup(SERVER, "CZSPacketHandler::OnMakeGroup");
void CZSPacketHandler::OnMakeGroup(int len) // line 1012
{
	return (this->*_OnMakeGroup)(len);

	PACKET_ZI_MAKE_GROUP packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	if ( InstanceCPartyMgr()->CPartyMgr::SearchMember(packet.GID) != 0 )
		return; // already in a party

	unsigned long GRID;
	unsigned long result = InstanceCPartyMgr()->CPartyMgr::MakeGroup(packet.AID, packet.GID, GRID, packet.groupName);

	Trace("PACKET_ZI_MAKE_GROUP\t\n");

	PACKET_IZ_ACK_MAKE_GROUP outpacket;
	outpacket.PacketType = HEADER_IZ_ACK_MAKE_GROUP;
	outpacket.AID = packet.AID;
	memcpy(outpacket.groupName, packet.groupName, sizeof(outpacket.groupName));
	outpacket.GRID = GRID;
	outpacket.result = (unsigned char)result;

	m_zServer->CZServer::GetAsyncStream()->CAsyncStream::Send(sizeof(outpacket), (const char*)&outpacket);
}


hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnMakeGroup2(SERVER, "CZSPacketHandler::OnMakeGroup2");
void CZSPacketHandler::OnMakeGroup2(int len) // line 1034
{
	return (this->*_OnMakeGroup2)(len);

	PACKET_ZI_MAKE_GROUP2 packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	if ( InstanceCPartyMgr()->CPartyMgr::SearchMember(packet.GID) != 0 )
		return; // already in a party

	unsigned long GRID;
	unsigned long result = InstanceCPartyMgr()->CPartyMgr::MakeGroup2(packet.AID, packet.GID, GRID, packet.groupName, packet.ItemPickupRule, packet.ItemDivisionRule);

	Trace("PACKET_ZI_MAKE_GROUP\t\n");

	PACKET_IZ_ACK_MAKE_GROUP outpacket;
	outpacket.PacketType = HEADER_IZ_ACK_MAKE_GROUP;
	outpacket.AID = packet.AID;
	memcpy(outpacket.groupName, packet.groupName, sizeof(outpacket.groupName));
	outpacket.GRID = GRID;
	outpacket.result = (unsigned char)result;

	m_zServer->CZServer::GetAsyncStream()->CAsyncStream::Send(sizeof(outpacket), (const char*)&outpacket);
}


hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnReqJoinGroup(SERVER, "CZSPacketHandler::OnReqJoinGroup");
void CZSPacketHandler::OnReqJoinGroup(int len) // line 1057
{
	return (this->*_OnReqJoinGroup)(len);

	Trace("PACKET_ZI_REQ_JOIN_GROUP\n");

	PACKET_ZI_REQ_JOIN_GROUP packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char *)&packet);

	USER_STRING_MAP_DATA* user = g_userMgr.CUserMgr::SearchUser(packet.receiverAID, 0);
	if( user == NULL )
		return; // target user not found

	if( InstanceCPartyMgr()->CPartyMgr::SearchMember(user->GID) != 0 )
	{
		PACKET_IZ_ACK_REQ_JOIN_GROUP outpacket;
		outpacket.PacketType = HEADER_IZ_ACK_REQ_JOIN_GROUP;
		outpacket.AID = packet.senderAID;
		memcpy(outpacket.characterName, user->characterName, sizeof(outpacket.characterName));
		outpacket.answer = 0;

		Trace("Already Joined\n");
		m_zServer->CZServer::GetAsyncStream()->CAsyncStream::Send(sizeof(outpacket), (const char*)&outpacket);
		return; // target user is already in a party
	}

	CParty* party = InstanceCPartyMgr()->CPartyMgr::SearchGroup(packet.GRID);
	if( party == NULL )
		return; // party not found

	if( party->CParty::GetMemberCount() >= InstanceCPartyMgr()->GetMaxMemberNum() )
	{
		PACKET_IZ_ACK_REQ_JOIN_GROUP outpacket;
		outpacket.PacketType = HEADER_IZ_ACK_REQ_JOIN_GROUP;
		outpacket.AID = packet.senderAID;
		memcpy(outpacket.characterName, user->characterName, sizeof(outpacket.characterName));
		outpacket.answer = 3;

		m_zServer->CZServer::GetAsyncStream()->CAsyncStream::Send(sizeof(outpacket), (const char*)&outpacket);
		Trace("Group Member OverFlow\n");
		return; // party is full
	}

	PACKET_IZ_REQ_JOIN_GROUP outpacket;
	outpacket.PacketType = HEADER_IZ_REQ_JOIN_GROUP;
	outpacket.AID = packet.receiverAID;
	outpacket.GRID = packet.GRID;
	InstanceCPartyMgr()->CPartyMgr::GetGroupName(packet.GRID, outpacket.groupName);

	g_userMgr.CUserMgr::SendMsg(packet.receiverAID, sizeof(outpacket), (char*)&outpacket);
	Trace("PACKET_IZ_REQ_JOIN_GROUP  Packet has Sent\n");
}


hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnJoinGroup(SERVER, "CZSPacketHandler::OnJoinGroup");
void CZSPacketHandler::OnJoinGroup(int len) // line 1134
{
	return (this->*_OnJoinGroup)(len);

	Trace("PACKET_ZI_JOIN_GROUP\n");

	PACKET_ZI_JOIN_GROUP packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char *)&packet);

	USER_STRING_MAP_DATA* user = g_userMgr.CUserMgr::SearchUser(packet.senderAID, 0);
	if( user == NULL )
		return; // target user not found

	unsigned long ownerAID = InstanceCPartyMgr()->CPartyMgr::GetGroupOwner(packet.GRID);
	if( ownerAID == 0 )
		return; // party owner not found

	PACKET_IZ_ACK_REQ_JOIN_GROUP outpacket;
	outpacket.AID = ownerAID;
	outpacket.PacketType = HEADER_IZ_ACK_REQ_JOIN_GROUP;
	memcpy(outpacket.characterName, user->characterName, sizeof(outpacket.characterName));
	if( packet.answer == 1 && user->GRID == 0 )
	{
		int answer = InstanceCPartyMgr()->CPartyMgr::InsertNewMember(packet.senderAID, packet.GRID);
		if( answer != 0 )
		{
			outpacket.answer = (unsigned char)answer;
			if( answer == 1 ) // FIXME CPartyMgr::InsertNewMember returns 1 on some errors (party not found, user not found, failed to add member to party) and on success from CPartyDB::InsertMember
				outpacket.answer = 2;
		}
		// FIXME outpacket.answer is uninitialized garbage if answer == 0 (error in CPartyDB::InsertMember)
	}
	else
	{
		outpacket.answer = 1;
	}

	g_userMgr.CUserMgr::SendMsg(ownerAID, sizeof(outpacket), (char *)&outpacket);
	if( outpacket.answer == 2 )
	{
		Trace("PACKET_ZI_GRID_UPDATE4\n");

		CParty* party = InstanceCPartyMgr()->CPartyMgr::SearchGroup(packet.GRID);
		if( party != NULL )
		{
			unsigned long expOption = party->CParty::GetGroupEXPOption();
			party->CParty::NotifyUpdateExpOption(user->AID, expOption);
		}
		InstanceCPartyMgr()->CPartyMgr::NotifyGroupMembers(packet.senderAID, packet.GRID);
	}
}


hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnExpelGroupMember(SERVER, "CZSPacketHandler::OnExpelGroupMember");
void CZSPacketHandler::OnExpelGroupMember(int len) // line 1250
{
	return (this->*_OnExpelGroupMember)(len);

	Trace("PACKET_ZI_REQ_EXPEL_GROUP_MEMBER \n");

	PACKET_ZI_REQ_EXPEL_GROUP_MEMBER packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char *)&packet);

	InstanceCPartyMgr()->CPartyMgr::ExpelGroupMember(packet.AID, packet.GRID, packet.characterName);
}


hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnChatParty(SERVER, "CZSPacketHandler::OnChatParty");
void CZSPacketHandler::OnChatParty(int len) // line 1284
{
	return (this->*_OnChatParty)(len);

	PACKET_ZI_CHAT_PARTY packet;
	char buf[PACKET_ZI_CHAT_PARTY::MAX_MESSAGE_SIZE];

	if( len > sizeof(buf) - sizeof(packet) ) // FIXME they probably wanted to add the sizes (can handle 24 more bytes, two times the size of packet)
		return; // message is too long

	Trace("PACKET_ZI_CHAT_PARTY\n");

	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char *)&packet);
	m_recvQueue->CPacketQueue::GetData(len - sizeof(packet), buf);

	CParty* party = InstanceCPartyMgr()->CPartyMgr::SearchGroup(packet.GRID);
	if( party != NULL )
		party->CParty::OnChat(packet.AID, len - sizeof(packet), buf);
}


hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnDisconnectAllPC(SERVER, "CZSPacketHandler::OnDisconnectAllPC");
void CZSPacketHandler::OnDisconnectAllPC(int len)
{
	return (this->*_OnDisconnectAllPC)(len);

	PACKET_ZI_DISCONNECT_ALL packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	PACKET_IZ_DISCONNECT_ALL outpacket;
	outpacket.PacketType = HEADER_IZ_DISCONNECT_ALL;
	g_zServerMgr.CZServerMgr::BroadCast(sizeof(outpacket), (char*)&outpacket);
}


hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnServerState(SERVER, "CZSPacketHandler::OnServerState");
void CZSPacketHandler::OnServerState(int len)
{
	return (this->*_OnServerState)(len);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnChangeExpOption(SERVER, "CZSPacketHandler::OnChangeExpOption");
void CZSPacketHandler::OnChangeExpOption(int len) // line 1102-1119
{
	return (this->*_OnChangeExpOption)(len);

	PACKET_ZI_CHANGE_EXPOPTION packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	CParty* party = InstanceCPartyMgr()->CPartyMgr::SearchGroup(packet.GRID);
	if( party == NULL )
		return; // party not found

	unsigned long ownerAID = party->CParty::GetMaster();
	if( ownerAID != packet.AID )
		return; // not the party owner

	if( packet.expOption == 1 )
	{
		if( party->CParty::IsExpSharable() )
			party->CParty::UpdateExpOption(packet.expOption);
		else
			party->CParty::NotifyUpdateExpOption(packet.AID, 2); // can't share exp due to level difference
	}
	else
	{
		party->CParty::UpdateExpOption(packet.expOption);
	}
}


hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnChangeExpOption2(SERVER, "CZSPacketHandler::OnChangeExpOption2");
void CZSPacketHandler::OnChangeExpOption2(int len) // line 1123-1131
{
	return (this->*_OnChangeExpOption2)(len);

	PACKET_ZI_CHANGE_EXPOPTION packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	CParty* party = InstanceCPartyMgr()->CPartyMgr::SearchGroup(packet.GRID);
	if( party == NULL )
		return; // party not found

	unsigned long ownerAID = party->CParty::GetMaster();
	if( ownerAID == packet.AID )
		return; // not the party owner

	party->CParty::UpdateExpOption(packet.expOption);
}


hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnLevelUp(SERVER, "CZSPacketHandler::OnLevelUp");
void CZSPacketHandler::OnLevelUp(int Len)
{
	return (this->*_OnLevelUp)(Len);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(int ZSID, unsigned short Len, char* buf)> CZSPacketHandler::_OnGuildPreload(SERVER, "CZSPacketHandler::OnGuildPreload");
void CZSPacketHandler::OnGuildPreload(int ZSID, unsigned short Len, char* buf)
{
	return (this->*_OnGuildPreload)(ZSID, Len, buf);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnChangeOwnerAgit(SERVER, "CZSPacketHandler::OnChangeOwnerAgit");
void CZSPacketHandler::OnChangeOwnerAgit(int Len)
{
	return (this->*_OnChangeOwnerAgit)(Len);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnDeleteRelatedGuild(SERVER, "CZSPacketHandler::OnDeleteRelatedGuild");
void CZSPacketHandler::OnDeleteRelatedGuild(int Len)
{
	return (this->*_OnDeleteRelatedGuild)(Len);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnSpecialMove(SERVER, "CZSPacketHandler::OnSpecialMove");
void CZSPacketHandler::OnSpecialMove(int Len) // line 1442-1515
{
	return (this->*_OnSpecialMove)(Len);

	PACKET_ZI_MOVE Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	PACKET_IZ_MOVE IZPacket;
	IZPacket.MoveType = Packet.MoveType;
	IZPacket.PacketType = HEADER_IZ_MOVE;

	USER_STRING_MAP_DATA* srcUser = g_userMgr.CUserMgr::SearchUser(Packet.SrcID, 0);
	if( srcUser == NULL )
		return;

	switch( Packet.MoveType )
	{
	case SHIFTAID:
	{
		USER_STRING_MAP_DATA* destUser = g_userMgr.CUserMgr::SearchUserByAccount(Packet.DestName, 0);
		if( destUser == NULL )
			break;

		IZPacket.DestID = destUser->AID;
		IZPacket.SrcID = Packet.SrcID;
		memcpy(IZPacket.CharName, srcUser->characterName, 24);

		if( g_serverInfo.CServerInfo::isSameServerSet(m_zServer->CZServer::GetZServerID(), destUser->ServerID) )
			g_zServerMgr.CZServerMgr::SendMsgToZServer(destUser->ServerID, sizeof(IZPacket), (char*)&IZPacket);
	}
	break;
	case SHIFTGID:
	{
		USER_STRING_MAP_DATA* destUser = g_userMgr.CUserMgr::SearchUserByName(Packet.DestName, 0);
		if( destUser == NULL )
			break;

		IZPacket.DestID = destUser->AID;
		IZPacket.SrcID = Packet.SrcID;
		memcpy(IZPacket.CharName, srcUser->characterName, 24);

		if( g_serverInfo.CServerInfo::isSameServerSet(m_zServer->CZServer::GetZServerID(), destUser->ServerID) )
			g_zServerMgr.CZServerMgr::SendMsgToZServer(destUser->ServerID, sizeof(IZPacket), (char*)&IZPacket);
	}
	break;
	case SUMMONAID:
	{
		USER_STRING_MAP_DATA* destUser = g_userMgr.CUserMgr::SearchUserByAccount(Packet.DestName, 0);
		if( destUser == NULL )
			break;

		IZPacket.DestX = Packet.DestX;
		IZPacket.DestY = Packet.DestY;
		memcpy(IZPacket.MapName, srcUser->mapName, 16);
		IZPacket.DestID = destUser->AID;

		if( g_serverInfo.CServerInfo::isSameServerSet(m_zServer->CZServer::GetZServerID(), destUser->ServerID) )
			g_zServerMgr.CZServerMgr::SendMsgToZServer(destUser->ServerID, sizeof(IZPacket), (char*)&IZPacket);
	}
	break;
	case SUMMONGID:
	{
		USER_STRING_MAP_DATA* destUser = g_userMgr.CUserMgr::SearchUserByName(Packet.DestName, 0);
		if( destUser == NULL )
			break;

		IZPacket.DestX = Packet.DestX;
		IZPacket.DestY = Packet.DestY;
		memcpy(IZPacket.MapName, srcUser->mapName, 16);
		IZPacket.DestID = destUser->AID;

		if( g_serverInfo.CServerInfo::isSameServerSet(m_zServer->CZServer::GetZServerID(), destUser->ServerID) )
			g_zServerMgr.CZServerMgr::SendMsgToZServer(destUser->ServerID, sizeof(IZPacket), (char*)&IZPacket);
	}
	break;
	default:
	break;
	}
}


hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnSpecialGIDMove(SERVER, "CZSPacketHandler::OnSpecialGIDMove");
void CZSPacketHandler::OnSpecialGIDMove(int Len)
{
	return (this->*_OnSpecialGIDMove)(Len);

	PACKET_ZI_MOVE_GID Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	PACKET_IZ_MOVE IZPacket;
	IZPacket.MoveType = Packet.MoveType;
	IZPacket.PacketType = HEADER_IZ_MOVE;

	USER_STRING_MAP_DATA* srcUser = g_userMgr.CUserMgr::SearchUser(Packet.SrcID, 0);
	if( srcUser == NULL )
		return;

	switch( Packet.MoveType )
	{
	case SHIFTAID:
	{
		USER_STRING_MAP_DATA* destUser = g_userMgr.CUserMgr::SearchUserByAccount(Packet.DestName, Packet.DestGID);
		if( destUser == NULL )
			break;

		IZPacket.DestID = destUser->AID;
		IZPacket.SrcID = Packet.SrcID;
		memcpy(IZPacket.CharName, srcUser->characterName, 24);

		if( g_serverInfo.CServerInfo::isSameServerSet(m_zServer->CZServer::GetZServerID(), destUser->ServerID) )
			g_zServerMgr.CZServerMgr::SendMsgToZServer(destUser->ServerID, sizeof(IZPacket), (char*)&IZPacket);
	}
	break;
	case SHIFTGID:
	{
		USER_STRING_MAP_DATA* destUser = g_userMgr.CUserMgr::SearchUserByName(Packet.DestName, Packet.DestGID);
		if( destUser == NULL )
			break;

		IZPacket.DestID = destUser->AID;
		IZPacket.SrcID = Packet.SrcID;
		memcpy(IZPacket.CharName, srcUser->characterName, 24);

		if( g_serverInfo.CServerInfo::isSameServerSet(m_zServer->CZServer::GetZServerID(), destUser->ServerID) )
			g_zServerMgr.CZServerMgr::SendMsgToZServer(destUser->ServerID, sizeof(IZPacket), (char*)&IZPacket);
	}
	break;
	case SUMMONAID:
	{
		USER_STRING_MAP_DATA* destUser = g_userMgr.CUserMgr::SearchUserByAccount(Packet.DestName, Packet.DestGID);
		if( destUser == NULL )
			break;

		IZPacket.DestX = Packet.DestX;
		IZPacket.DestY = Packet.DestY;
		memcpy(IZPacket.MapName, srcUser->mapName, 16);
		IZPacket.DestID = destUser->AID;

		if( g_serverInfo.CServerInfo::isSameServerSet(m_zServer->CZServer::GetZServerID(), destUser->ServerID) )
			g_zServerMgr.CZServerMgr::SendMsgToZServer(destUser->ServerID, sizeof(IZPacket), (char*)&IZPacket);
	}
	break;
	case SUMMONGID:
	{
		USER_STRING_MAP_DATA* destUser = g_userMgr.CUserMgr::SearchUserByName(Packet.DestName, Packet.DestGID);
		if( destUser == NULL )
			break;

		IZPacket.DestX = Packet.DestX;
		IZPacket.DestY = Packet.DestY;
		memcpy(IZPacket.MapName, srcUser->mapName, 16);
		IZPacket.DestID = destUser->AID;

		if( g_serverInfo.CServerInfo::isSameServerSet(m_zServer->CZServer::GetZServerID(), destUser->ServerID) )
			g_zServerMgr.CZServerMgr::SendMsgToZServer(destUser->ServerID, sizeof(IZPacket), (char*)&IZPacket);
	}
	break;
	case SUMMONMARRY:
	{
		USER_STRING_MAP_DATA* destUser = g_userMgr.CUserMgr::SearchUserByName(Packet.DestName, Packet.DestGID);
		if( destUser == NULL )
			break;

		IZPacket.DestX = Packet.DestX;
		IZPacket.DestY = Packet.DestY;
		memcpy(IZPacket.MapName, srcUser->mapName, 16);
		IZPacket.DestID = destUser->AID;

		if( g_serverInfo.CServerInfo::isSameServerSet(m_zServer->CZServer::GetZServerID(), destUser->ServerID) )
			g_zServerMgr.CZServerMgr::SendMsgToZServer(destUser->ServerID, sizeof(IZPacket), (char*)&IZPacket);
	}
	break;
	default:
		return;
	}
}


hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnReqDisorganizeGuild(SERVER, "CZSPacketHandler::OnReqDisorganizeGuild");
void CZSPacketHandler::OnReqDisorganizeGuild(int len)
{
	return (this->*_OnReqDisorganizeGuild)(len);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnDivorce(SERVER, "CZSPacketHandler::OnDivorce");
void CZSPacketHandler::OnDivorce(int len)
{
	return (this->*_OnDivorce)(len);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnDeleteFriend(SERVER, "CZSPacketHandler::OnDeleteFriend");
void CZSPacketHandler::OnDeleteFriend(int Len)
{
	return (this->*_OnDeleteFriend)(Len);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnAckReqAddFriends(SERVER, "CZSPacketHandler::OnAckReqAddFriends");
void CZSPacketHandler::OnAckReqAddFriends(int Len)
{
	return (this->*_OnAckReqAddFriends)(Len);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnUpDateMakeRank(SERVER, "CZSPacketHandler::OnUpDateMakeRank");
void CZSPacketHandler::OnUpDateMakeRank(int Len)
{
	return (this->*_OnUpDateMakeRank)(Len);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnMailGetList(SERVER, "CZSPacketHandler::OnMailGetList");
void CZSPacketHandler::OnMailGetList(int Len)
{
	return (this->*_OnMailGetList)(Len);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnMailOpen(SERVER, "CZSPacketHandler::OnMailOpen");
void CZSPacketHandler::OnMailOpen(int Len)
{
	return (this->*_OnMailOpen)(Len);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnMailDelete(SERVER, "CZSPacketHandler::OnMailDelete");
void CZSPacketHandler::OnMailDelete(int Len)
{
	return (this->*_OnMailDelete)(Len);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnMailGetItem(SERVER, "CZSPacketHandler::OnMailGetItem");
void CZSPacketHandler::OnMailGetItem(int Len)
{
	return (this->*_OnMailGetItem)(Len);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnMailSend(SERVER, "CZSPacketHandler::OnMailSend");
void CZSPacketHandler::OnMailSend(int Len)
{
	return (this->*_OnMailSend)(Len);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnMailReturn(SERVER, "CZSPacketHandler::OnMailReturn");
void CZSPacketHandler::OnMailReturn(int Len)
{
	return (this->*_OnMailReturn)(Len);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnEpisodeVersion(SERVER, "CZSPacketHandler::OnEpisodeVersion");
void CZSPacketHandler::OnEpisodeVersion(int Len)
{
	return (this->*_OnEpisodeVersion)(Len);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnAckProcessTime(SERVER, "CZSPacketHandler::OnAckProcessTime");
void CZSPacketHandler::OnAckProcessTime(int Len) // line 1779
{
	return (this->*_OnAckProcessTime)(Len);

	PACKET_ZI_ACK_CHK_PROCESSTIME packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	double IZProcessTime = difftime(packet.ZoneProcessTime, packet.InterProcessTime);
	double ZIProcessTime = difftime(time(NULL), packet.ZoneProcessTime);

	if( IZProcessTime > g_IZProcessTime )
	{
		g_IZProcessTime = IZProcessTime;
		g_SIDProcessTime = m_zServer->CZServer::GetZServerID();
	}

	if( ZIProcessTime > g_ZIProcessTime )
	{
		g_ZIProcessTime = ZIProcessTime;
		g_SIDProcessTime = m_zServer->CZServer::GetZServerID();
	}
}


hook_method<void (CZSPacketHandler::*)(int len)> CZSPacketHandler::_OnServerStateHanGame(SERVER, "CZSPacketHandler::OnServerStateHanGame");
void CZSPacketHandler::OnServerStateHanGame(int len)
{
	return (this->*_OnServerStateHanGame)(len);

	//TODO
}


hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnGroupInfoChangeV2(SERVER, "CZSPacketHandler::OnGroupInfoChangeV2");
void CZSPacketHandler::OnGroupInfoChangeV2(int Len) // line 2161-2189
{
	return (this->*_OnGroupInfoChangeV2)(Len);

	PACKET_ZI_GROUPINFO_CHANGE_V2 packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	CParty* party = InstanceCPartyMgr()->CPartyMgr::SearchGroup(packet.GRID);
	if( party == NULL )
		return; // party not found

	if( party->CParty::GetMaster() != packet.MasterAID )
		return; // wrong owner

	GROUP_INFO GroupInfo;
	if( packet.FamilyGroup == 1 )
	{
		GroupInfo.expOption = packet.expOption;
	}
	else if( packet.expOption == 1 )
	{
		if( party->CParty::IsExpSharable() )
		{
			party->CParty::UpdateExpOption(1);
			GroupInfo.expOption = 1;
		}
		else
		{
			GroupInfo.expOption = 2;
		}
	}
	else
	{
		GroupInfo.expOption = 0;
	}

	GroupInfo.ItemPickupRule = packet.ItemPickupRule;
	GroupInfo.ItemDivisionRule = packet.ItemDivisionRule;
	party->CParty::ChangeGroupInfo(GroupInfo);
}


hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnChangeGroupMaster(SERVER, "CZSPacketHandler::OnChangeGroupMaster");
void CZSPacketHandler::OnChangeGroupMaster(int Len) // line 2193-2201
{
	return (this->*_OnChangeGroupMaster)(Len);

	PACKET_ZI_CHANGE_GROUP_MASTER packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	CParty* party = InstanceCPartyMgr()->CPartyMgr::SearchGroup(packet.GRID);
	if( party == NULL )
		return; // party not found

	party->CParty::OnChangeGroupMaster(packet.MasterAID, packet.AID);
}


hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnSeekParty(SERVER, "CZSPacketHandler::OnSeekParty");
void CZSPacketHandler::OnSeekParty(int Len) // line 2204-2218
{
	return (this->*_OnSeekParty)(Len);

	PACKET_ZI_SEEK_PARTY packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	PACKET_IZ_SEEK_PARTY ouputpacket;
	ouputpacket.PacketType = HEADER_IZ_SEEK_PARTY;
	memcpy(ouputpacket.Name, packet.Name, sizeof(ouputpacket.Name));
	ouputpacket.Level = packet.Job;
	ouputpacket.Job = packet.Job;
	memcpy(ouputpacket.mapName, packet.mapName, sizeof(ouputpacket.mapName));
	ouputpacket.Option = packet.Option;
	g_zServerMgr.CZServerMgr::BroadCast(sizeof(ouputpacket), (const char *)&ouputpacket);
}


hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnSeekPartyMember(SERVER, "CZSPacketHandler::OnSeekPartyMember");
void CZSPacketHandler::OnSeekPartyMember(int Len) // line 2221-2235
{
	return (this->*_OnSeekPartyMember)(Len);

	PACKET_ZI_SEEK_PARTY_MEMBER packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	PACKET_IZ_SEEK_PARTY_MEMBER ouputpacket;
	ouputpacket.PacketType = HEADER_IZ_SEEK_PARTY_MEMBER;
	memcpy(ouputpacket.Name, packet.Name, sizeof(ouputpacket.Name));
	ouputpacket.Level = packet.Job;
	ouputpacket.Job = packet.Job;
	memcpy(ouputpacket.mapName, packet.mapName, sizeof(ouputpacket.mapName));
	ouputpacket.Option = packet.Option;
	g_zServerMgr.CZServerMgr::BroadCast(sizeof(ouputpacket), (const char *)&ouputpacket);
}


hook_method<void (CZSPacketHandler::*)(int Len)> CZSPacketHandler::_OnZIInterServerOrder(SERVER, "CZSPacketHandler::OnZIInterServerOrder");
void CZSPacketHandler::OnZIInterServerOrder(int Len)
{
	return (this->*_OnZIInterServerOrder)(Len);

	//TODO
}
