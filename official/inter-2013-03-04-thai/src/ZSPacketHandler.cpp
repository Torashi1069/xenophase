#include "CEntryQueueMgr.h"
#include "CMakerRankMgr.h"
#include "IGuildMgr.h"
#include "InterServer.h"
#include "Party.h"
#include "PartyMgr.h"
#include "ServerExpInfoMgr.h"
#include "UserMgr.h"
#include "ZServer.h"
#include "ZSPacketHandler.h"
#include "Common/Packet.h"
#include "Common/PacketLengthExMgr.h"
#include "Instant Map/InstantMap.h"
#include "Instant Map/InstantMapMgr.h"
#include "Memorial Dungeon/MemorialDungeonMgr.h"
#include "ServerManager/CMsvrMgr.h"
#include "Zsvr/CZsvrMgr.h"
#include "shared/N3System/N3MessageMgr.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/NMemoryHelper.h"
#include "shared/NOutputTextMgr.h"
#include "shared/ServerInfo.h"
#include "shared/VarLenPacketPtr.h"


CZSPacketHandler::CZSPacketHandler()
{
	m_LastPacketRecvTM = timeGetTime();
}


CZSPacketHandler::~CZSPacketHandler()
{
}


unsigned int CZSPacketHandler::GetLastPacketRecvTM()
{
	return m_LastPacketRecvTM;
}


void CZSPacketHandler::SetLastPacketRecvTM(unsigned int in_LastPacketRecvTM)
{
	m_LastPacketRecvTM = in_LastPacketRecvTM;
}


void CZSPacketHandler::AddSendBytes(int byteTransferred)
{
}


void CZSPacketHandler::SetMyOwner(CZServer* zServer)
{
	m_zServer = zServer;
}


void CZSPacketHandler::OnRecvOverflow(int byteTransferred)
{
}


void CZSPacketHandler::OnRecv(int byteTransferred)
{
}


void CZSPacketHandler::OnClose()
{
	PACKET_XX_DISCONNECT packet;
	packet.PacketType = HEADER_XX_DISCONNECT;
	m_recvQueue->CPacketQueue::resetANDinsert(sizeof(packet), (char*)&packet);
}


int CZSPacketHandler::OnProcess()
{
	const int ReceiveBytes = m_recvQueue->CPacketQueue::GetSize();
	if( ReceiveBytes < 2 )
		return -1;

	char PacketBuffer[4] = {};
	m_recvQueue->CPacketQueue::PeekData((ReceiveBytes < 4) ? 2 : 4, PacketBuffer);

	short Header = reinterpret_cast<PACKET*>(PacketBuffer)->PacketType;
	unsigned short packetSize;

	std::pair<CPacketLengthExMgr::enumFixedPacketRet,int> fpRet = g_packetLenMapEx.CPacketLengthExMgr::IsFixedPacket(Header);
	if( fpRet.first == CPacketLengthExMgr::FIXED )
	{
		packetSize = (unsigned short)fpRet.second;
	}
	else
	if( fpRet.first == CPacketLengthExMgr::VARIABLE )
	{
		if( ReceiveBytes < 4 )
			return -1;

		packetSize = reinterpret_cast<PACKETV*>(PacketBuffer)->PacketLength;
		if( packetSize < fpRet.second )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "variable packet size minimum guarantee. header(%d) packetSize(%d) min(%d)", Header, packetSize, fpRet.second);
			return 0; // malformed packet.
		}
	}
	else
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "unknown packet receive header(%d)", Header);
		return 0;
	}

	if( packetSize == 0 || packetSize > 65500 )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "packetsize:%d, Freesize:%d, Size:%d, header:%d", packetSize, m_recvQueue->CPacketQueue::GetFreeSize(), m_recvQueue->CPacketQueue::GetSize(), Header);
		return 0;
	}

	if( packetSize > ReceiveBytes )
		return -1;

	const int Ret = this->CZSPacketHandler::DispatchPacket(Header, packetSize);
	if( Ret != -1 )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "packetsize:%d, Freesize:%d, Size:%d, header:%d", packetSize, m_recvQueue->CPacketQueue::GetFreeSize(), m_recvQueue->CPacketQueue::GetSize(), Header);
		return Ret;
	}

	m_LastPacketRecvTM = timeGetTime();

	return -1;
}


int CZSPacketHandler::DispatchPacket(short Header, int packetSize)
{
	switch( Header )
	{
	case HEADER_ZI_MEMORIALDUNGEON_DESTROY:
	{
		PACKET_ZI_MEMORIALDUNGEON_DESTROY packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_MEMORIALDUNGEON_DESTROY(packet);
	}
	break;
	case HEADER_ZI_INFO_ENTRY_QUEUE_APPLY:
	{
		PACKET_ZI_INFO_ENTRY_QUEUE_APPLY* pZI_INFO_ENTRY_QUEUE_APPLY = (PACKET_ZI_INFO_ENTRY_QUEUE_APPLY*)_malloca(packetSize);
		m_recvQueue->CPacketQueue::GetData(packetSize, (char*)pZI_INFO_ENTRY_QUEUE_APPLY);
		this->CZSPacketHandler::OnZI_INFO_ENTRY_QUEUE_APPLY(pZI_INFO_ENTRY_QUEUE_APPLY);
		_freea(pZI_INFO_ENTRY_QUEUE_APPLY);
	}
	break;
	case HEADER_ZI_REQ_ENTRY_QUEUE_APPLY:
	{
		PACKET_ZI_REQ_ENTRY_QUEUE_APPLY packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_REQ_ENTRY_QUEUE_APPLY(packet);
	}
	break;
	case HEADER_ZI_RESULT_ENTRY_QUEUE_APPLY:
	{
		PACKET_ZI_RESULT_ENTRY_QUEUE_APPLY packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_RESULT_ENTRY_QUEUE_APPLY(packet);
	}
	break;
	case HEADER_ZI_REQ_ENTRY_QUEUE_CANCEL:
	{
		PACKET_ZI_REQ_ENTRY_QUEUE_CANCEL packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_REQ_ENTRY_QUEUE_CANCEL(packet);
	}
	break;
	case HEADER_ZI_RESULT_ENTRY_QUEUE_CANCEL:
	{
		PACKET_ZI_RESULT_ENTRY_QUEUE_CANCEL packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_RESULT_ENTRY_QUEUE_CANCEL(packet);
	}
	break;
	case HEADER_ZI_ENTRY_QUEUE_ADMISSION:
	{
		PACKET_ZI_ENTRY_QUEUE_ADMISSION packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_ENTRY_QUEUE_ADMISSION(packet);
	}
	break;
	case HEADER_ZI_ENTRY_QUEUE_ADMISSION_ACCEPT:
	{
		PACKET_ZI_ENTRY_QUEUE_ADMISSION_ACCEPT packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_ENTRY_QUEUE_ADMISSION_ACCEPT(packet);
	}
	break;
	case HEADER_ZI_RESULT_ENTRY_QUEUE_ADMISSION_ACCEPT:
	{
		PACKET_ZI_RESULT_ENTRY_QUEUE_ADMISSION_ACCEPT packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_RESULT_ENTRY_QUEUE_ADMISSION_ACCEPT(packet);
	}
	break;
	case HEADER_ZI_ENTRY_QUEUE_ADMISSION_REFUSE:
	{
		PACKET_ZI_ENTRY_QUEUE_ADMISSION_REFUSE packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_ENTRY_QUEUE_ADMISSION_REFUSE(packet);
	}
	break;
	case HEADER_ZI_RESULT_ENTRY_QUEUE_ADMISSION_REFUSE:
	{
		PACKET_ZI_RESULT_ENTRY_QUEUE_ADMISSION_REFUSE packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_RESULT_ENTRY_QUEUE_ADMISSION_REFUSE(packet);
	}
	break;
	case HEADER_ZI_LOBBY_ADMISSION:
	{
		PACKET_ZI_LOBBY_ADMISSION packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_LOBBY_ADMISSION(packet);
	}
	break;
	case HEADER_ZI_LOBBY_ADMISSION_V2:
	{
		PACKET_ZI_LOBBY_ADMISSION_V2 packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_LOBBY_ADMISSION_V2(packet);
	}
	break;
	case HEADER_ZI_LOBBY_ADMISSION_ACCEPT:
	{
		PACKET_ZI_LOBBY_ADMISSION_ACCEPT packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_LOBBY_ADMISSION_ACCEPT(packet);
	}
	break;
	case HEADER_ZI_RESULT_LOBBY_ADMISSION_ACCEPT:
	{
		PACKET_ZI_RESULT_LOBBY_ADMISSION_ACCEPT packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_RESULT_LOBBY_ADMISSION_ACCEPT(packet);
	}
	break;
	case HEADER_ZI_LOBBY_ADMISSION_REFUSE:
	{
		PACKET_ZI_LOBBY_ADMISSION_REFUSE packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_LOBBY_ADMISSION_REFUSE(packet);
	}
	break;
	case HEADER_ZI_RESULT_LOBBY_ADMISSION_REFUSE:
	{
		PACKET_ZI_RESULT_LOBBY_ADMISSION_REFUSE packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_RESULT_LOBBY_ADMISSION_REFUSE(packet);
	}
	break;
	case HEADER_ZI_ENTRY_QUEUE_MOVE_ROOM:
	{
		PACKET_ZI_ENTRY_QUEUE_MOVE_ROOM packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_ENTRY_QUEUE_MOVE_ROOM(packet);
	}
	break;
	case HEADER_ZI_LOBBY_MOVE_ROOM:
	{
		PACKET_ZI_LOBBY_MOVE_ROOM packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_LOBBY_MOVE_ROOM(packet);
	}
	break;
	case HEADER_ZI_ENTRY_QUEUE_NAME:
	{
		PACKET_ZI_ENTRY_QUEUE_NAME* pZI_ENTRY_QUEUE_NAME = (PACKET_ZI_ENTRY_QUEUE_NAME*)_malloca(packetSize);
		m_recvQueue->CPacketQueue::GetData(packetSize, (char*)pZI_ENTRY_QUEUE_NAME);
		this->CZSPacketHandler::OnZI_ENTRY_QUEUE_NAME(pZI_ENTRY_QUEUE_NAME);
		_freea(pZI_ENTRY_QUEUE_NAME);
	}
	break;
	case HEADER_ZI_ENTRY_QUEUE_DELETE_GID:
	{
		PACKET_ZI_ENTRY_QUEUE_DELETE_GID packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_ENTRY_QUEUE_DELETE_GID(packet);
	}
	break;
	case HEADER_ZI_ENTRY_QUEUE_RANKING:
	{
		PACKET_ZI_ENTRY_QUEUE_RANKING packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_ENTRY_QUEUE_RANKING(packet);
	}
	break;
	case HEADER_ZI_JOB_CHANGE:
	{
		PACKET_ZI_JOB_CHANGE packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_JOB_CHANGE(packet);
	}
	break;
	case HEADER_ZI_NOTIFY_ENTRY_QUEUE_RANKING:
	{
		PACKET_ZI_NOTIFY_ENTRY_QUEUE_RANKING packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_NOTIFY_ENTRY_QUEUE_RANKING(packet);
	}
	break;
	case HEADER_ZI_BROADCASTING_SPECIAL_ITEM_OBTAIN:
	{
		std::vector<BYTE> packet(packetSize);
		m_recvQueue->CPacketQueue::GetData(packetSize, (char*)&packet[0]);
		this->CZSPacketHandler::OnZI_BROADCASTING_SPECIAL_ITEM_OBTAIN(packet);
	}
	break;
	case HEADER_ZI_MEMORIALDUNGEON_OPENSTATE:
	{
		PACKET_ZI_MEMORIALDUNGEON_OPENSTATE packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_MEMORIALDUNGEON_OPENSTATE(packet);
	}
	break;
	case HEADER_ZI_MEMORIALDUNGEON_VISA:
	{
		PACKET_ZI_MEMORIALDUNGEON_VISA packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_MEMORIALDUNGEON_VISA(packet);
	}
	break;
	case HEADER_ZI_MEMORIALDUNGEON_COMMAND:
	{
		PACKET_ZI_MEMORIALDUNGEON_COMMAND packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_MEMORIALDUNGEON_COMMAND(packet);
	}
	break;
	case HEADER_ZI_PARTY_JOIN_REQ_ACK:
	{
		PACKET_ZI_PARTY_JOIN_REQ_ACK packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_PARTY_JOIN_REQ_ACK(packet);
	}
	break;
	case HEADER_ZI_PARTY_JOIN_REQ:
	{
		PACKET_ZI_PARTY_JOIN_REQ packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_PARTY_JOIN_REQ(packet);
	}
	break;
	case HEADER_XX_CONNECT:
	{
		PACKET_XX_CONNECT packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnXX_CONNECT(packet);
	}
	break;
	case HEADER_XX_DISCONNECT:
	{
		PACKET_XX_DISCONNECT packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnXX_DISCONNECT(packet);
	}
	break;
	case HEADER_ZI_INSTANTMAP_ALLOW:
	{
		PACKET_ZI_INSTANTMAP_ALLOW packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_INSTANTMAP_ALLOW(packet);
	}
	break;
	case HEADER_ZI_PING:
	{
		PACKET_ZI_PING packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_PING(packet);
	}
	break;
	case HEADER_ZI_PING_LIVE:
	{
		PACKET_ZI_PING_LIVE packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_PING_LIVE(packet);
	}
	break;
	case HEADER_ZI_STATEINFO:
	{
		PACKET_ZI_STATEINFO packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_STATEINFO(packet);
	}
	break;
	case HEADER_ZI_INSTANTMAP_ERROR:
	{
		PACKET_ZI_INSTANTMAP_ERROR packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_INSTANTMAP_ERROR(packet);
	}
	break;
	case HEADER_ZI_INSTANTMAP_CREATE_RES:
	{
		PACKET_ZI_INSTANTMAP_CREATE_RES packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_INSTANTMAP_CREATE_RES(packet);
	}
	break;
	case HEADER_ZI_MEMORIALDUNGEON_SUBSCRIPTION:
	{
		PACKET_ZI_MEMORIALDUNGEON_SUBSCRIPTION packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_MEMORIALDUNGEON_SUBSCRIPTION(packet);
	}
	break;
	case HEADER_ZI_MEMORIALDUNGEON_SUBSCRIPTION2:
	{
		this->CZSPacketHandler::OnZI_MEMORIALDUNGEON_SUBSCRIPTION2(packetSize);
	}
	break;
	case HEADER_ZI_GPK_DYNCODE_RELOAD:
	{
		PACKET_ZI_GPK_DYNCODE_RELOAD packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_GPK_DYNCODE_RELOAD(packet);
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
		m_recvQueue->CPacketQueue::GetData(packetSize, PacketBuffer);

		PACKET_ZI_WHISPER* pZI_WHISPER = (PACKET_ZI_WHISPER*)PacketBuffer;
		this->CZSPacketHandler::OnWhisper(pZI_WHISPER);
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
		PACKET_ZI_REQ_LEAVE_GROUP packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CZSPacketHandler::OnZI_REQ_LEAVE_GROUP(packet);
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
	case HEADER_ZI_SERVERSTATE_CHANNELING:
	{
		this->CZSPacketHandler::OnServerStateChanneling(packetSize);
	}
	break;
	case HEADER_ZI_MOVE:
	{
		this->CZSPacketHandler::OnSpecialMove(packetSize);
	}
	break;
	case HEADER_ZI_MOVE_2:
	{
		this->CZSPacketHandler::OnSpecialMove_SSO(packetSize);
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
	case HEADER_ZI_REQ_MAKE_GUILD_SSO:
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
	case HEADER_ZI_REQ_BAN_GUILD_SSO:
	case HEADER_ZI_JOIN_GUILD_SSO:
	case HEADER_ZI_LIST_JOIN_GUILD_INSERT_GID:
	{
		__pragma(pack(push,1)) struct TEMPHEADER { short PacketType; unsigned long GDID; } temp; __pragma(pack(pop))
		m_recvQueue->CPacketQueue::PeekData(sizeof(temp), (char*)&temp);

		char buf[10240] = {};
		m_recvQueue->CPacketQueue::GetData(packetSize, buf);

		CIGuildMgr::GetObj()->CIGuildMgr::SendPacket(m_zServer->CZServer::GetZServerID(), temp.PacketType, temp.GDID, packetSize, buf);
	}
	break;
	case HEADER_ZI_GUILD_PRELOAD:
	{
		__pragma(pack(push,1)) struct TEMPHEADER { short PacketType; unsigned short PacketLength; unsigned long GDID; } temp; __pragma(pack(pop))
		m_recvQueue->CPacketQueue::PeekData(sizeof(temp), (char*)&temp);

		char buf[10240] = {};
		m_recvQueue->CPacketQueue::GetData(packetSize, buf);

//		this->CZSPacketHandler::OnGuildPreload(???, buf);
	}
	break;
	case HEADER_ZI_REGISTER_GUILD_EMBLEM_IMG:
	case HEADER_ZI_REQ_CHANGE_MEMBERPOS:
	case HEADER_ZI_REQ_GUILD_POSITION_INFO:
	case HEADER_ZI_GUILD_CHAT:
	case HEADER_ZI_GDSKILL_UPDATE:
	{
		__pragma(pack(push,1)) struct TEMPHEADER { short PacketType; unsigned short PacketLength; unsigned long GDID; } temp; __pragma(pack(pop))
		m_recvQueue->CPacketQueue::PeekData(sizeof(temp), (char*)&temp);

		char buf[10240] = {};
		m_recvQueue->CPacketQueue::GetData(packetSize, buf);
		CIGuildMgr::GetObj()->CIGuildMgr::SendPacket(m_zServer->CZServer::GetZServerID(), temp.PacketType, temp.GDID, packetSize, buf);
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
	case HEADER_ZI_GROUPINFO_CHANGE_V2:
	{
		this->CZSPacketHandler::OnGroupInfoChangeV2(packetSize);
	}
	break;
	case HEADER_ZI_CHANGE_GROUP_MASTER:
	{
		this->CZSPacketHandler::OnChangeGroupMaster(packetSize);
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
	case HEADER_ZI_PARTY_BOOKING_NOTIFY_INSERT:
	{
		this->CZSPacketHandler::OnBroadcastPartyBookingPacket(HEADER_IZ_PARTY_BOOKING_NOTIFY_INSERT, sizeof(PACKET_IZ_PARTY_BOOKING_NOTIFY_INSERT));
	}
	break;
	case HEADER_ZI_PARTY_BOOKING_NOTIFY_DELETE:
	{
		this->CZSPacketHandler::OnBroadcastPartyBookingPacket(HEADER_IZ_PARTY_BOOKING_NOTIFY_DELETE, sizeof(PACKET_IZ_PARTY_BOOKING_NOTIFY_DELETE));
	}
	break;
	case HEADER_ZI_PARTY_BOOKING_NOTIFY_UPDATE:
	{
		this->CZSPacketHandler::OnBroadcastPartyBookingPacket(HEADER_IZ_PARTY_BOOKING_NOTIFY_UPDATE, sizeof(PACKET_ZI_PARTY_BOOKING_NOTIFY_UPDATE));
	}
	break;
	case HEADER_ZI_OTHER_ZONE_PC_SEND_MSG:
	{
		PACKET_ZI_OTHER_ZONE_PC_SEND_MSG packet = {};
		m_recvQueue->CPacketQueue::GetData(packetSize, (char*)&packet);
		this->CZSPacketHandler::OnOTHER_ZONE_PC_SEND_MSG(packet);
	}
	break;
	case HEADER_CONNECTION_CLOSED:
	{
		return 0;
	}
	break;
	default:
	{
		m_zServer->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		m_recvQueue->CPacketQueue::Reset();
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "ZSPacketHandler not header:%d:%d, freesize:%d, recvQueuesize:%d", Header, m_zServer->CZServer::GetZServerID(), m_recvQueue->CPacketQueue::GetFreeSize(), m_recvQueue->CPacketQueue::GetSize());
		return 0;
	}
	break;
	};

	return -1;
}


void CZSPacketHandler::OnZI_BROADCASTING_SPECIAL_ITEM_OBTAIN(const std::vector<unsigned char>& in_packet)
{
	const PACKET_ZI_BROADCASTING_SPECIAL_ITEM_OBTAIN& zi_packet = *reinterpret_cast<const PACKET_ZI_BROADCASTING_SPECIAL_ITEM_OBTAIN*>(&in_packet.front());
	PACKET_IZ_BROADCASTING_SPECIAL_ITEM_OBTAIN& iz_packet = *reinterpret_cast<PACKET_IZ_BROADCASTING_SPECIAL_ITEM_OBTAIN*>(const_cast<PACKET_ZI_BROADCASTING_SPECIAL_ITEM_OBTAIN*>(&zi_packet));
	iz_packet.PacketType = HEADER_IZ_BROADCASTING_SPECIAL_ITEM_OBTAIN;
	CZsvrMgr::GetObj()->CZServerMgr::BroadCast(iz_packet.PacketLength, (char*)&iz_packet);
}


void CZSPacketHandler::OnBroadcastPartyBookingPacket(const short in_IZPacketType, const short in_PacketSize)
{
	char Packet[256] = {};
	m_recvQueue->CPacketQueue::GetData(in_PacketSize, Packet);

	memcpy(Packet, &in_IZPacketType, sizeof(short));
	CZsvrMgr::GetObj()->CZServerMgr::BroadCast(in_PacketSize, Packet);
}


void CZSPacketHandler::OnZI_GPK_DYNCODE_RELOAD(const PACKET_ZI_GPK_DYNCODE_RELOAD& in_packet)
{
}


void CZSPacketHandler::OnVersion(int len)
{
	PACKET_ZI_VERSION packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "ZoneProcess Connected:%d", m_zServer->CZServer::GetZServerID());
}


void CZSPacketHandler::OnServerEntry(int p_Length)
{
	PACKET_SERVER_ENTRY server_entry;
	m_recvQueue->CPacketQueue::GetData(p_Length, (char*)&server_entry);
}


void CZSPacketHandler::OnBroadCast(int len)
{
	if( len > 500 )
		return;

	char buf[512];
	m_recvQueue->CPacketQueue::GetData(len, buf);
	PACKET_ZI_BROADCAST* pZI_BROADCAST = reinterpret_cast<PACKET_ZI_BROADCAST*>(buf);

	short header = HEADER_IZ_BROADCAST;
	memcpy(&pZI_BROADCAST->PacketType, &header, sizeof(short));
	CZsvrMgr::GetObj()->CZServerMgr::BroadCast(len, buf);

	if( g_isBroadCastLog == TRUE )
	{
		char szBuffer[512];
		wsprintfA(szBuffer, " BroadCastLog = %s \n", &pZI_BROADCAST->PacketLength); //FIXME: deprecated API //FIXME: wrong offset

		FILE* fp = fopen("BroadCastLog.log", "a");
		if( fp != NULL )
		{
			fprintf(fp, "%s", szBuffer);
			fclose(fp);
		}
	}
}


void CZSPacketHandler::OnWhisperAck(int len)
{
	PACKET_ZI_ACK_WHISPER packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	unsigned long AID;
	int ZSID = g_userMgr.CUserMgr::SearchUserServerID(packet.sender, AID);
	if( ZSID == -1 )
		return;

	PACKET_IZ_ACK_WHISPER outpacket;
	outpacket.PacketType = HEADER_IZ_ACK_WHISPER;
	outpacket.senderAID = packet.senderAID;
	outpacket.result = packet.result;
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(outpacket), (char*)&outpacket);
}


void CZSPacketHandler::OnReqDisorganizeGuild(int len)
{
	PACKET_ZI_REQ_DISORGANIZE_GUILD Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	CIGuildMgr::GetObj()->CIGuildMgr::OnReqDisorganizeGuild(m_zServer->CZServer::GetZServerID(), Packet.GDID, Packet.AID, Packet.GID);
}


void CZSPacketHandler::OnReqUserCount(int len)
{
	PACKET_ZI_REQ_USER_COUNT packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	if( g_bSetUserCounter == TRUE )
	{
		PACKET_IZ_USER_COUNT outpacket;
		outpacket.PacketType = HEADER_IZ_USER_COUNT;
		outpacket.AID = packet.AID;
		outpacket.count = g_userMgr.CUserMgr::GetUserCount();
		m_zServer->Send(sizeof(m_zServer), (char*)&outpacket);
	}
}


void CZSPacketHandler::OnLogon(int len)
{
	PACKET_ZI_LOGON packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	USER_STRING_MAP_DATA data = {};
	data.AID = packet.AID;
	data.GID = packet.GID;
	data.ServerID = m_zServer->CZServer::GetZServerID();
	data.sex = packet.sex;
	data.job = packet.job;
	data.level = packet.level;
	data.head = packet.head;
	data.headpalette = packet.headpalette;
	data.GRID = 0;
	memcpy(data.mapName, packet.mapName, 16);
	memcpy(data.accountName, packet.accountName, 24);
	memcpy(data.characterName, packet.charName, 24);
	data.FriendNumber = 0;

	if( g_userMgr.CUserMgr::AddUser(m_zServer->CZServer::GetZServerID(), &data) )
	{
		USER_STRING_MAP_DATA* pUser = g_userMgr.CUserMgr::SearchUser(packet.AID, packet.GID);
		if( pUser != NULL )
		{
			m_zServer->CZServer::AddPlayer(pUser->mapName);
			CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::OnNewbie(m_zServer->CZServer::GetHsvrID(), pUser->GID, pUser->AID, pUser->GRID, pUser->mapName);
		}
	}
}


void CZSPacketHandler::OnActorInit(int Len)
{
	PACKET_ZI_ACTOR_INIT Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);
}


void CZSPacketHandler::OnExit(int len)
{
	PACKET_ZI_EXIT packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	USER_STRING_MAP_DATA* pUser = g_userMgr.CUserMgr::SearchUser(packet.AID, packet.GID);
	if( pUser != NULL )
	{
		m_zServer->CZServer::RemovePlayer(pUser->mapName);
		CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::OnLeave(pUser->GID, pUser->AID, pUser->mapName);
	}

	g_userMgr.CUserMgr::DeleteUser(m_zServer->CZServer::GetZServerID(), packet.charName);
	CEntryQueueMgr::GetObj()->CEntryQueueMgr::LogOut(packet.GID);
}


void CZSPacketHandler::OnMakeGroup(int len)
{
	PACKET_ZI_MAKE_GROUP packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	if( g_groupMgr.CPartyMgr::SearchMember(packet.GID) != 0 )
		return; // already in a party.

	unsigned long GRID;
	unsigned char result = (unsigned char)g_groupMgr.CPartyMgr::MakeGroup(packet.AID, packet.GID, GRID, packet.groupName);

	PACKET_IZ_ACK_MAKE_GROUP outpacket;
	outpacket.PacketType = HEADER_IZ_ACK_MAKE_GROUP;
	outpacket.AID = packet.AID;
	outpacket.GRID = GRID;
	memcpy(outpacket.groupName, packet.groupName, 24);
	outpacket.result = result;
	m_zServer->Send(sizeof(outpacket), (char*)&outpacket);
}


void CZSPacketHandler::OnMakeGroup2(int len)
{
	PACKET_ZI_MAKE_GROUP2 packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	if( g_groupMgr.CPartyMgr::SearchMember(packet.GID) != 0 )
		return; // already in a party.

	unsigned long GRID;
	unsigned char result = (unsigned char)g_groupMgr.CPartyMgr::MakeGroup2(packet.AID, packet.GID, GRID, packet.groupName, packet.ItemPickupRule, packet.ItemDivisionRule);

	PACKET_IZ_ACK_MAKE_GROUP outpacket;
	outpacket.PacketType = HEADER_IZ_ACK_MAKE_GROUP;
	outpacket.AID = packet.AID;
	outpacket.GRID = GRID;
	memcpy(outpacket.groupName, packet.groupName, 24);
	outpacket.result = result;
	m_zServer->Send(sizeof(outpacket), (char*)&outpacket);
}


void CZSPacketHandler::OnReqJoinGroup(int len)
{
	PACKET_ZI_REQ_JOIN_GROUP packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	USER_STRING_MAP_DATA* pUser = g_userMgr.CUserMgr::SearchUser(packet.receiverAID, 0);
	if( pUser == NULL )
		return;

	if( g_groupMgr.CPartyMgr::SearchMember(pUser->GID) )
	{
		PACKET_IZ_ACK_REQ_JOIN_GROUP outpacket;
		outpacket.PacketType = HEADER_IZ_ACK_REQ_JOIN_GROUP;
		outpacket.AID = packet.senderAID;
		memcpy(outpacket.characterName, pUser->characterName, 24);
		outpacket.answer = PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_ALREADY_OTHERGROUPM;
		m_zServer->Send(sizeof(outpacket), (char*)&outpacket);
		return;
	}

	CParty* cpParty = g_groupMgr.CPartyMgr::SearchGroup(packet.GRID);
	if( cpParty == NULL )
		return;

	if( cpParty->CParty::GetMemberCount() >= g_groupMgr.CPartyMgr::GetMaxMemberNum() )
	{
		PACKET_IZ_ACK_REQ_JOIN_GROUP outpacket;
		outpacket.PacketType = HEADER_IZ_ACK_REQ_JOIN_GROUP;
		outpacket.AID = packet.senderAID;
		memcpy(outpacket.characterName, pUser->characterName, 24);
		outpacket.answer = PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_MEMBER_OVERSIZE;
		m_zServer->Send(sizeof(outpacket), (char*)&outpacket);
		return;
	}

	PACKET_IZ_REQ_JOIN_GROUP outpacket;
	outpacket.PacketType = HEADER_IZ_REQ_JOIN_GROUP;
	outpacket.AID = packet.receiverAID;
	outpacket.GRID = packet.GRID;
	g_groupMgr.CPartyMgr::GetGroupName(packet.GRID, outpacket.groupName);
	g_userMgr.CUserMgr::SendMsg(packet.receiverAID, sizeof(outpacket), (char*)&outpacket);
}


void CZSPacketHandler::OnChangeExpOption(int len)
{
	PACKET_ZI_CHANGE_EXPOPTION packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	CParty* cpParty = g_groupMgr.CPartyMgr::SearchGroup(packet.GRID);
	if( cpParty == NULL )
		return;

	if( packet.expOption == EXP_SHARED && !cpParty->CParty::IsExpSharable() )
	{
		cpParty->CParty::NotifyUpdateExpOption(packet.AID, EXP_CHANGE_IMPOSSIBLE);
		return;
	}

	cpParty->CParty::UpdateExpOption(packet.expOption, true);
}


void CZSPacketHandler::OnChangeExpOption2(int len)
{
	PACKET_ZI_CHANGE_EXPOPTION packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	CParty* cpParty = g_groupMgr.CPartyMgr::SearchGroup(packet.GRID);
	if( cpParty == NULL )
		return;

	cpParty->CParty::UpdateExpOption(packet.expOption, true);
}


void CZSPacketHandler::OnJoinGroup(int len)
{
	PACKET_ZI_JOIN_GROUP packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	USER_STRING_MAP_DATA* pUser = g_userMgr.CUserMgr::SearchUser(packet.senderAID, 0);
	if( pUser == NULL )
		return;

	unsigned long MasterAID = g_groupMgr.CPartyMgr::GetGroupOwner(packet.GRID);
	if( MasterAID == NULL )
		return;

	PACKET_IZ_ACK_REQ_JOIN_GROUP outpacket;
	outpacket.PacketType = HEADER_IZ_ACK_REQ_JOIN_GROUP;
	outpacket.AID = MasterAID;
	memcpy(outpacket.characterName, pUser->characterName, 24);

	if( packet.answer != 1 || pUser->GRID != 0 )
	{
		outpacket.answer = 1;
	}
	else
	{
		int result = g_groupMgr.CPartyMgr::InsertNewMember(packet.senderAID, packet.GRID);
		if( result != 0 )
		{
			outpacket.answer = result;
			if( result == 1 )
				outpacket.answer = 2;
		}
	}

	g_userMgr.CUserMgr::SendMsg(MasterAID, sizeof(outpacket), (char*)&outpacket);

	if( outpacket.answer == 2 )
	{
		CParty* cpParty = g_groupMgr.CPartyMgr::SearchGroup(packet.GRID);
		if( cpParty != NULL )
		{
			cpParty->CParty::NotifyUpdateExpOption(pUser->AID, cpParty->CParty::GetGroupEXPOption());
		}

		g_groupMgr.CPartyMgr::NotifyGroupMembers(packet.senderAID, packet.GRID);
	}
}


void CZSPacketHandler::OnZI_MEMORIALDUNGEON_OPENSTATE(const PACKET_ZI_MEMORIALDUNGEON_OPENSTATE& in_packet)
{
	if( in_packet.Request == PACKET_ZI_MEMORIALDUNGEON_OPENSTATE::REQUEST_OPEN )
		CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::Open();
	else
	if( in_packet.Request == PACKET_ZI_MEMORIALDUNGEON_OPENSTATE::REQUEST_CLOSE )
		CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::Close();

	PACKET_IZ_MEMORIALDUNGEON_OPENSTATE packet = {};
	packet.PacketType = HEADER_IZ_MEMORIALDUNGEON_OPENSTATE;
	packet.bOpen = CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::isOpen();
	packet.ToAID = in_packet.RequestAID;
	packet.ToGID = in_packet.RequestGID;
	m_zServer->Send(sizeof(packet), (char*)&packet);
}


void CZSPacketHandler::OnZI_REQ_LEAVE_GROUP(const PACKET_ZI_REQ_LEAVE_GROUP& in_packet)
{
	if( g_groupMgr.CPartyMgr::LeaveGroup(in_packet.AID, in_packet.GID) != true )
		return;

	PACKET_IZ_LEAVE_GROUP packet = {};
	packet.PacketType = 10715;
	packet.AID = in_packet.AID;
	packet.GID = in_packet.GID;
	m_zServer->Send(sizeof(packet), (char*)&packet);
}


void CZSPacketHandler::OnExpelGroupMember(int len)
{
	PACKET_ZI_REQ_EXPEL_GROUP_MEMBER packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	g_groupMgr.CPartyMgr::ExpelGroupMember(packet.AID, packet.GRID, packet.characterName);
}


void CZSPacketHandler::OnMapMove(int len)
{
	PACKET_ZI_MAPMOVE packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	USER_STRING_MAP_DATA* pUser = g_userMgr.CUserMgr::SearchUser(packet.AID, 0);
	if( pUser == NULL )
		return;

	std::string previous_mapName = pUser->mapName;
	memcpy(pUser->mapName, packet.mapName, 16);
	m_zServer->CZServer::RemovePlayer(previous_mapName);
	m_zServer->CZServer::AddPlayer(pUser->mapName);
	CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::OnLeave(pUser->GID, pUser->AID, previous_mapName);
	CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::OnEnter(pUser->GRID, pUser->GID, pUser->AID, pUser->mapName);

	g_groupMgr.CPartyMgr::MapMove2(pUser->GRID, pUser->AID, pUser->mapName);
}


void CZSPacketHandler::OnChatParty(int len)
{
	if( len > 500 )
		return;

	PACKET_ZI_CHAT_PARTY packet;
	char buf[512];
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
	m_recvQueue->CPacketQueue::GetData(len - sizeof(packet), buf);

	CParty* cpParty = g_groupMgr.CPartyMgr::SearchGroup(packet.GRID);
	if( cpParty == NULL )
		return;

	cpParty->CParty::OnChat(packet.AID, len - sizeof(packet), buf);
}


void CZSPacketHandler::OnDisconnectAllPC(int len)
{
	PACKET_ZI_DISCONNECT_ALL packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	PACKET_IZ_DISCONNECT_ALL outpacket;
	outpacket.PacketType = HEADER_IZ_DISCONNECT_ALL;
	CZsvrMgr::GetObj()->CZServerMgr::BroadCast(sizeof(outpacket), (char*)&outpacket);
}


void CZSPacketHandler::OnServerState(int len)
{
	PACKET_ZI_SERVERSTATE packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	PACKET_IM_SERVERSTATE outpacket;
	outpacket.PacketType = HEADER_IM_SERVERSTATE;
	memcpy(&outpacket.serverState, &packet.state, sizeof(IM_SERVER_STATE));
	CMsvrMgr::GetObj()->CMClientMgr::SendMsgToMServer(packet.monitorNum, sizeof(outpacket), (char*)&outpacket);
}


void CZSPacketHandler::OnServerStateHanGame(int len)
{
	PACKET_ZI_SERVERSTATE_HAN_GAME packet; //NOTE: copy-paste mistake / OOB write in official code
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	PACKET_IM_SERVERSTATE_HAN_GAME outpacket;
	outpacket.PacketType = HEADER_IM_SERVERSTATE_HAN_GAME;
	memcpy(&outpacket.serverState, &packet.state, sizeof(IM_SERVER_STATE_HAN_GAME));
	CMsvrMgr::GetObj()->CMClientMgr::SendMsgToMServer(packet.monitorNum, sizeof(outpacket), (char*)&outpacket);
}


void CZSPacketHandler::OnServerStateChanneling(const int in_PacketLength)
{
	PACKET_ZI_SERVERSTATE_CHANNELING Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	PACKET_IM_SERVERSTATE_CHANNELING OutPacket;
	OutPacket.PacketType = HEADER_IM_SERVERSTATE_CHANNELING;
	memcpy(&OutPacket.serverState, &Packet.state, sizeof(IM_SERVER_STATE_CHANNELING));
	CMsvrMgr::GetObj()->CMClientMgr::SendMsgToMServer(Packet.monitorNum, sizeof(OutPacket), (char*)&OutPacket);
}


void CZSPacketHandler::OnMakeGuild(int Len)
{
	PACKET_ZI_REQ_MAKE_GUILD Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	unsigned long GDID = 0;
	CIGuildMgr::GetObj()->CIGuildMgr::MakeGuild(m_zServer->CZServer::GetZServerID(), Packet.AID, Packet.GID, GDID, Packet.MName, Packet.GName, Packet.AccountName);
}


void CZSPacketHandler::OnReqJoinGuild(int Len)
{
	PACKET_ZI_REQ_JOIN_GUILD Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	CIGuildMgr::GetObj()->CIGuildMgr::ReqJoinGuild(m_zServer->CZServer::GetZServerID(), Packet.AID, Packet.GID, Packet.myGID, Packet.myAID);
}


void CZSPacketHandler::OnAllyGuild(int Len)
{
	char Buf[3072];
	m_recvQueue->CPacketQueue::GetData(Len, Buf);
	PACKET_ZI_ALLY_GUILD& Packet = *reinterpret_cast<PACKET_ZI_ALLY_GUILD*>(Buf);

	CIGuildMgr::GetObj()->CIGuildMgr::AllyGuild(m_zServer->CZServer::GetZServerID(), Packet.GDID, (char*)&Packet);
}


void CZSPacketHandler::OnReqHostileGuild(int Len)
{
	char Buf[216];
	m_recvQueue->CPacketQueue::GetData(Len, Buf);
	PACKET_ZI_REQ_HOSTILE_GUILD& Packet = *reinterpret_cast<PACKET_ZI_REQ_HOSTILE_GUILD*>(Buf);

	CIGuildMgr::GetObj()->CIGuildMgr::HostileGuild(Packet.GDID, (char*)&Packet);
}


void CZSPacketHandler::OnLevelUp(int Len)
{
	char Buf[1024];
	m_recvQueue->CPacketQueue::GetData(Len, Buf);
	PACKET_ZI_CHAR_LEVEL_UP& Packet = *reinterpret_cast<PACKET_ZI_CHAR_LEVEL_UP*>(Buf);

	USER_STRING_MAP_DATA* pUser = g_userMgr.CUserMgr::SearchUser(Packet.AID, Packet.GID);
	if( pUser == NULL )
		return;

	++pUser->level;
}


void CZSPacketHandler::OnGuildPreload(int ZSID, unsigned short Len, char* buf)
{
}


void CZSPacketHandler::OnChangeOwnerAgit(int Len)
{
	PACKET_ZI_GUILD_CHANGEOWNER_AGIT in;
	m_recvQueue->CPacketQueue::GetData(sizeof(in), (char*)&in);

	CIGuildMgr::GetObj()->CIGuildMgr::OnChangeAgitGuild(in.oldGDID, in.newGDID);

	PACKET_IZ_GUILD_CHANGEOWNER_AGIT out;
	out.PacketType = HEADER_IZ_GUILD_CHANGEOWNER_AGIT;
	out.oldGDID = in.oldGDID;
	out.newGDID = in.newGDID;
	memcpy(out.mapName, in.mapName, 16);
	CZsvrMgr::GetObj()->CZServerMgr::BroadCast(sizeof(out), (char*)&out);
}


void CZSPacketHandler::OnDeleteRelatedGuild(int Len)
{
	PACKET_ZI_REQ_DELETE_RELATED_GUILD Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	CIGuildMgr::GetObj()->CIGuildMgr::OnDeleteRelatedGuild(Packet.GDID, Packet.OpponentGDID, Packet.Relation, FALSE);
}


void CZSPacketHandler::OnSpecialMove_SSO(const int len)
{
	PACKET_ZI_MOVE_2 Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	int DestX = Packet.DestX;
	int DestY = Packet.DestY;
	int MoveType = Packet.MoveType;
	unsigned long SrcID = Packet.SrcID;

	PACKET_IZ_MOVE IZPacket;
	IZPacket.PacketType = HEADER_IZ_MOVE;
	IZPacket.MoveType = MoveType;

	USER_STRING_MAP_DATA* data = g_userMgr.CUserMgr::SearchUser(Packet.SrcID, 0);
	if( data == NULL )
		return;

	if( MoveType == SHIFTAID )
	{
		USER_STRING_MAP_DATA* data2 = g_userMgr.CUserMgr::SearchUser(Packet.DestAID, Packet.DestGID);
		if( data2 == NULL )
			return;

		IZPacket.DestID = data2->AID;
		IZPacket.SrcID = SrcID;
		memcpy(IZPacket.CharName, data->characterName, 24);

		if( g_serverInfo.CServerInfo::isSameServerSet(m_zServer->CZServer::GetZServerID(), data2->ServerID) )
			CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(data2->ServerID, sizeof(IZPacket), (char*)&IZPacket);
	}
	else
	if( MoveType == SHIFTGID )
	{
		USER_STRING_MAP_DATA* data2 = g_userMgr.CUserMgr::SearchUserByName(Packet.DestName, 0);
		if( data2 == NULL )
			return;

		IZPacket.DestID = data2->AID;
		IZPacket.SrcID = SrcID;
		memcpy(IZPacket.CharName, data->characterName, 24);

		if( g_serverInfo.CServerInfo::isSameServerSet(m_zServer->CZServer::GetZServerID(), data2->ServerID) )
			CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(data2->ServerID, sizeof(IZPacket), (char*)&IZPacket);
	}
	else
	if( MoveType == SUMMONAID )
	{
		USER_STRING_MAP_DATA* data2 = g_userMgr.CUserMgr::SearchUser(Packet.DestAID, Packet.DestGID);
		if( data2 == NULL )
			return;

		IZPacket.DestX = DestX;
		IZPacket.DestY = DestY;
		memcpy(IZPacket.MapName, data->mapName, 16);
		IZPacket.DestID = data2->AID;

		if( g_serverInfo.CServerInfo::isSameServerSet(m_zServer->CZServer::GetZServerID(), data2->ServerID) )
			CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(data2->ServerID, sizeof(IZPacket), (char*)&IZPacket);
	}
	else
	if( MoveType == SUMMONGID )
	{
		USER_STRING_MAP_DATA* data2 = g_userMgr.CUserMgr::SearchUserByName(Packet.DestName, 0);
		if( data2 == NULL )
			return;

		IZPacket.DestX = DestX;
		IZPacket.DestY = DestY;
		memcpy(IZPacket.MapName, data->mapName, 16);
		IZPacket.DestID = data2->AID;

		if( g_serverInfo.CServerInfo::isSameServerSet(m_zServer->CZServer::GetZServerID(), data2->ServerID) )
			CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(data2->ServerID, sizeof(IZPacket), (char*)&IZPacket);
	}
}


void CZSPacketHandler::OnSpecialMove(int Len)
{
	PACKET_ZI_MOVE Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	int DestX = Packet.DestX;
	int DestY = Packet.DestY;
	int MoveType = Packet.MoveType;
	unsigned long SrcID = Packet.SrcID;

	PACKET_IZ_MOVE IZPacket;
	IZPacket.PacketType = HEADER_IZ_MOVE;
	IZPacket.MoveType = MoveType;

	USER_STRING_MAP_DATA* data = g_userMgr.CUserMgr::SearchUser(Packet.SrcID, 0);
	if( data == NULL )
		return;

	if( MoveType == SHIFTAID )
	{
		USER_STRING_MAP_DATA* data = g_userMgr.CUserMgr::SearchUserByAccount(Packet.DestName, 0);
		if( data == NULL )
			return;

		IZPacket.DestID = data->AID;
		IZPacket.SrcID = SrcID;
		memcpy(IZPacket.CharName, data->characterName, 24);

		if( g_serverInfo.CServerInfo::isSameServerSet(m_zServer->CZServer::GetZServerID(), data->ServerID) )
			CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(data->ServerID, sizeof(IZPacket), (char*)&IZPacket);
	}
	else
	if( MoveType == SHIFTGID )
	{
		USER_STRING_MAP_DATA* data = g_userMgr.CUserMgr::SearchUserByName(Packet.DestName, 0);
		if( data == NULL )
			return;

		IZPacket.DestID = data->AID;
		IZPacket.SrcID = SrcID;
		memcpy(IZPacket.CharName, data->characterName, 24);

		if( g_serverInfo.CServerInfo::isSameServerSet(m_zServer->CZServer::GetZServerID(), data->ServerID) )
			CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(data->ServerID, sizeof(IZPacket), (char*)&IZPacket);
	}
	else
	if( MoveType == SUMMONAID )
	{
		USER_STRING_MAP_DATA* data2 = g_userMgr.CUserMgr::SearchUserByName(Packet.DestName, 0);
		if( data2 == NULL )
			return;

		IZPacket.DestX = DestX;
		IZPacket.DestY = DestY;
		memcpy(IZPacket.MapName, data->mapName, 16);
		IZPacket.DestID = data2->AID;

		if( g_serverInfo.CServerInfo::isSameServerSet(m_zServer->CZServer::GetZServerID(), data2->ServerID) )
			CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(data2->ServerID, sizeof(IZPacket), (char*)&IZPacket);
	}
	else
	if( MoveType == SUMMONGID )
	{
		USER_STRING_MAP_DATA* data2 = g_userMgr.CUserMgr::SearchUserByAccount(Packet.DestName, 0);
		if( data2 == NULL )
			return;

		IZPacket.DestX = DestX;
		IZPacket.DestY = DestY;
		memcpy(IZPacket.MapName, data->mapName, 16);
		IZPacket.DestID = data2->AID;

		if( g_serverInfo.CServerInfo::isSameServerSet(m_zServer->CZServer::GetZServerID(), data2->ServerID) )
			CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(data2->ServerID, sizeof(IZPacket), (char*)&IZPacket);
	}
}


void CZSPacketHandler::OnSpecialGIDMove(int Len)
{
	PACKET_ZI_MOVE_GID Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	int DestX = Packet.DestX;
	int DestY = Packet.DestY;
	int MoveType = Packet.MoveType;
	unsigned long SrcID = Packet.SrcID;

	PACKET_IZ_MOVE IZPacket;
	IZPacket.PacketType = HEADER_IZ_MOVE;
	IZPacket.MoveType = Packet.MoveType;

	USER_STRING_MAP_DATA* data = g_userMgr.CUserMgr::SearchUser(Packet.SrcID, 0);
	if( data == NULL )
		return;

	if( MoveType == SHIFTAID )
	{
		USER_STRING_MAP_DATA* data2 = g_userMgr.CUserMgr::SearchUserByAccount(Packet.DestName, Packet.DestGID);
		if( data2 == NULL )
			return;

		IZPacket.DestID = data2->AID;
		IZPacket.SrcID = SrcID;
		memcpy(IZPacket.CharName, data->characterName, 24);

		if( g_serverInfo.CServerInfo::isSameServerSet(m_zServer->CZServer::GetZServerID(), data2->ServerID) )
			CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(data2->ServerID, sizeof(IZPacket), (char*)&IZPacket);
	}
	else
	if( MoveType == SHIFTGID )
	{
		USER_STRING_MAP_DATA* data2 = g_userMgr.CUserMgr::SearchUserByName(Packet.DestName, Packet.DestGID);
		if( data2 == NULL )
			return;

		IZPacket.DestID = data2->AID;
		IZPacket.SrcID = SrcID;
		memcpy(IZPacket.CharName, data->characterName, 24);

		if( g_serverInfo.CServerInfo::isSameServerSet(m_zServer->CZServer::GetZServerID(), data2->ServerID) )
			CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(data2->ServerID, sizeof(IZPacket), (char*)&IZPacket);
	}
	else
	if( MoveType == SUMMONAID )
	{
		USER_STRING_MAP_DATA* data2 = g_userMgr.CUserMgr::SearchUserByAccount(Packet.DestName, Packet.DestGID);
		if( data2 == NULL )
			return;

		IZPacket.DestX = DestX;
		IZPacket.DestY = DestY;
		memcpy(IZPacket.MapName, data->mapName, 16);
		IZPacket.DestID = data2->AID;

		if( g_serverInfo.CServerInfo::isSameServerSet(m_zServer->CZServer::GetZServerID(), data2->ServerID) )
			CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(data2->ServerID, sizeof(IZPacket), (char*)&IZPacket);
	}
	else
	if( MoveType == SUMMONGID || MoveType == SUMMONMARRY )
	{
		USER_STRING_MAP_DATA* data2 = g_userMgr.CUserMgr::SearchUserByName(Packet.DestName, Packet.DestGID);
		if( data2 == NULL )
			return;

		IZPacket.DestX = DestX;
		IZPacket.DestY = DestY;
		memcpy(IZPacket.MapName, data->mapName, 16);
		IZPacket.DestID = data2->AID;

		if( g_serverInfo.CServerInfo::isSameServerSet(m_zServer->CZServer::GetZServerID(), data2->ServerID) )
			CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(data2->ServerID, sizeof(IZPacket), (char*)&IZPacket);
	}
}


void CZSPacketHandler::OnDivorce(int len)
{
	PACKET_ZI_DIVORCE Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	USER_STRING_MAP_DATA* pUser = g_userMgr.CUserMgr::SearchUserByName(Packet.name, Packet.GID);
	if( pUser == NULL )
		return;

	PACKET_IZ_DIVORCE SendPacket = {};
	SendPacket.PacketType = HEADER_IZ_DIVORCE;
	SendPacket.GID = Packet.GID;
	memcpy(SendPacket.name, Packet.name, 24);
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(pUser->ServerID, sizeof(SendPacket), (char*)&SendPacket);
}


void CZSPacketHandler::OnDeleteFriend(int Len)
{
	PACKET_ZI_DELETE_FRIENDS Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	g_userMgr.CUserMgr::DeleteFriend(Packet.AID, Packet.FriendAID, Packet.FriendGID);
}


void CZSPacketHandler::OnAckReqAddFriends(int Len)
{
	PACKET_ZI_ACK_REQ_ADD_FRIENDS Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	g_userMgr.CUserMgr::AddFriend(Packet.AckAID, Packet.AckGID, Packet.ReqAID, Packet.ReqGID);
}


void CZSPacketHandler::OnServerMove(int Len)
{
	PACKET_ZI_MOVE_SERVER packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	USER_STRING_MAP_DATA* pUser = g_userMgr.CUserMgr::SearchUser(packet.AID, packet.GID);
	if( pUser != NULL )
	{
		m_zServer->CZServer::RemovePlayer(pUser->mapName);
		CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::OnLeave(pUser->GID, pUser->AID, pUser->mapName);
	}

	g_userMgr.CUserMgr::MoveServerUser(m_zServer->CZServer::GetZServerID(), packet.AID, packet.GID, packet.charName);
}


void CZSPacketHandler::OnUpDateMakeRank(int Len)
{
	PACKET_ZI_UPDATE_MAKERRANK Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	g_MakerRankMgr.CMakerRankMgr::UpdateMakeRank(Packet.type, Packet.GID, Packet.charname, Packet.point);
}


void CZSPacketHandler::OnEpisodeVersion(int Len)
{
	PACKET_ZI_EPISODE_VERSION packet;
	m_recvQueue->CPacketQueue::GetData(10, (char*)&packet);

	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "ZoneProcess Connected:%d", m_zServer->CZServer::GetZServerID());
}


void CZSPacketHandler::OnAckProcessTime(int Len)
{
	time_t the_time;
	time_t Time = time(&the_time);

	PACKET_ZI_ACK_CHK_PROCESSTIME packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	double IZProcessTime = difftime(packet.ZoneProcessTime, packet.InterProcessTime);
	double ZIProcessTime = difftime(Time, packet.ZoneProcessTime);

	static double g_IZProcessTime;
	static double g_ZIProcessTime;
	static unsigned long g_SIDProcessTime;

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


void CZSPacketHandler::OnWhisper(const PACKET_ZI_WHISPER* in_pPacket)
{
	const char* pWhisper = in_pPacket->Text;
	unsigned short nWhisperLen = in_pPacket->PacketLength - sizeof(PACKET_ZI_WHISPER);

	unsigned long AID = 0;
	int ZSID = g_userMgr.CUserMgr::SearchUserServerID(in_pPacket->receiver, AID);
	if( ZSID == -1 )
	{
		PACKET_IZ_ACK_WHISPER opFrom;
		opFrom.PacketType = HEADER_IZ_ACK_WHISPER;
		opFrom.senderAID = in_pPacket->senderAID;
		opFrom.result = WHISPER_SEND_FAILED_PC_ABSENCE;
		m_zServer->Send(sizeof(opFrom), (char*)&opFrom);
		return;
	}

	PACKET_IZ_WHISPER opTo;
	opTo.PacketType = HEADER_IZ_WHISPER;
	opTo.PacketLength = sizeof(PACKET_IZ_WHISPER) + nWhisperLen;
	opTo.receiverAID = AID;
	opTo.senderAID = in_pPacket->senderAID;
	memcpy(opTo.sender, in_pPacket->sender, 24);
	memcpy(opTo.senderAccountName, in_pPacket->senderAccountName, 24);
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(PACKET_IZ_WHISPER), (char*)&opTo);
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, nWhisperLen, pWhisper);
}


void CZSPacketHandler::OnZI_MEMORIALDUNGEON_DESTROY(const PACKET_ZI_MEMORIALDUNGEON_DESTROY& in_packet)
{
}


void CZSPacketHandler::OnZI_MEMORIALDUNGEON_SUBSCRIPTION(const PACKET_ZI_MEMORIALDUNGEON_SUBSCRIPTION& in_packet)
{
	const_cast<PACKET_ZI_MEMORIALDUNGEON_SUBSCRIPTION&>(in_packet).Name[countof(in_packet.Name)-1] = '\0';
	const_cast<PACKET_ZI_MEMORIALDUNGEON_SUBSCRIPTION&>(in_packet).NickName[countof(in_packet.NickName)-1] = '\0';

	CParty* cpParty = g_groupMgr.CPartyMgr::SearchGroup(in_packet.GRID);
	if( cpParty == NULL || in_packet.AID != cpParty->CParty::GetMaster() )
	{
		PACKET_IZ_MEMORIALDUNGEON_MSG packet = {};
		packet.PacketType = HEADER_IZ_MEMORIALDUNGEON_MSG;
		packet.Notify = PACKET_IZ_MEMORIALDUNGEON_MSG::MEMORIALDUNGEON_SUBSCRIPTION_ERROR_UNKNOWN;
		memcpy(packet.MemorialDungeonName, in_packet.Name, 60+1);
		packet.MemorialDungeonName[countof(packet.MemorialDungeonName)-1] = '\0';
		packet.AID = in_packet.AID;
		packet.GID = in_packet.GID;
		m_zServer->Send(sizeof(packet), (char*)&packet);
		return;
	}

	CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::Subscription(m_zServer->CZServer::GetHsvrID(), in_packet.AID, in_packet.GID, in_packet.Name, in_packet.NickName, in_packet.GRID, cpParty->CParty::GetGroupName());
}


void CZSPacketHandler::OnZI_INSTANTMAP_CREATE_RES(const PACKET_ZI_INSTANTMAP_CREATE_RES& in_packet)
{
	CInstantMap::InstantMap_MSGwparam_TARGETZSVR_CREATE_RESPONSE* response = new(std::nothrow) CInstantMap::InstantMap_MSGwparam_TARGETZSVR_CREATE_RESPONSE(in_packet.mapName, in_packet.mapID, in_packet.bSuccess);
	if( response == NULL )
		return;

	N3MessageMgr::GetObj()->N3MessageMgr::Post(in_packet.hRequestN2Obj, N3MSGID(CInstantMap,MSG_TARGETZSVR_CREATE_RESPONSE2), reinterpret_cast<unsigned int>(response), 0);
}


void CZSPacketHandler::OnZI_INSTANTMAP_ERROR(const PACKET_ZI_INSTANTMAP_ERROR& in_packet)
{
	N3MessageMgr::GetObj()->N3MessageMgr::Post(in_packet.hRequestN2Obj, N3MSGID(CInstantMap,MSG_ERROR_FOUND_FROMZSVR2), in_packet.mapID, in_packet.why);
	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "인스턴트맵: 존서버(%d)에서 오류를 넘겨주었다.", m_zServer->CZServer::GetZServerID());
}


void CZSPacketHandler::OnZI_PING(const PACKET_ZI_PING& in_packet)
{
	m_zServer->m_UsedMemoryKBytes = in_packet.UsedKBytesMemory;
	m_zServer->m_TotalNPCNum = in_packet.NumTotalNPC;
}


void CZSPacketHandler::OnXX_DISCONNECT(const PACKET_XX_DISCONNECT& in_packet)
{
	CEntryQueueMgr::GetObj()->CEntryQueueMgr::DisconnectZSVR(m_zServer->CZServer::GetZServerID());
	CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::DisconnectZSVR(m_zServer->CZServer::GetZServerID());
	m_zServer->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "정상종료 : %d", m_zServer->CZServer::GetZServerID());
}


void CZSPacketHandler::OnZI_INSTANTMAP_ALLOW(const PACKET_ZI_INSTANTMAP_ALLOW& in_packet)
{
	if( in_packet.bAllow == true )
	{
		if( m_zServer->m_InstantMapBlockCnt > 0 )
			--m_zServer->m_InstantMapBlockCnt;
	}
	else
	{
		++m_zServer->m_InstantMapBlockCnt;
	}
}


void CZSPacketHandler::OnXX_CONNECT(const PACKET_XX_CONNECT& in_packet)
{
	PACKET_IZ_AUTH_ACK packet;
	packet.PacketType = HEADER_IZ_AUTH_ACK;
	m_zServer->Send(sizeof(packet), (char*)&packet);

	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("ZSVR(%d) auth... complete", m_zServer->CZServer::GetZServerID());
	CInstantMapMgr::GetObj()->CInstantMapMgr::NotifyAllInstantMap(m_zServer->CZServer::GetZServerID(), m_zServer->CZServer::GetRegisteredMgrFUCnt());
	CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::NotifyAllMemorialDunbeon(m_zServer->CZServer::GetZServerID(), m_zServer->CZServer::GetRegisteredMgrFUCnt());

	PACKET_IZ_REQ_EDIT_EXP out_packet = {};
	out_packet.PacketType = HEADER_IZ_REQ_EDIT_EXP;
	out_packet.monitornum = g_mServer.CMClient::GetServerID();
	out_packet.Exp = CServerExpInfoMgr::GetObj()->CServerExpInfoMgr::GetExp();
	out_packet.Death = CServerExpInfoMgr::GetObj()->CServerExpInfoMgr::GetDeath();
	out_packet.Drop = CServerExpInfoMgr::GetObj()->CServerExpInfoMgr::GetDrop();
	m_zServer->Send(sizeof(out_packet), (char*)&out_packet);
}


static void Send_PACKET_IZ_PARTY_JOIN_REQ_ACK(unsigned long in_ZSID, const char* in_pTargetCharName, unsigned long in_RequestAID, PACKET_ZC_PARTY_JOIN_REQ_ACK::enumAnswer in_answer) // 3218-3228
{
	PACKET_IZ_PARTY_JOIN_REQ_ACK packet = {};
	packet.PacketType = HEADER_IZ_PARTY_JOIN_REQ_ACK;
	strncpy(packet.characterName, in_pTargetCharName, 24);
	packet.requestAID = in_RequestAID;
	packet.answer = in_answer;
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(in_ZSID, sizeof(packet), (char*)&packet);
}


void CZSPacketHandler::OnZI_PARTY_JOIN_REQ(const PACKET_ZI_PARTY_JOIN_REQ& in_packet)
{
	USER_STRING_MAP_DATA* pTargetPlayer = g_userMgr.CUserMgr::SearchUserByName(in_packet.TargetCharName, 0);
	if( pTargetPlayer == NULL )
	{
		Send_PACKET_IZ_PARTY_JOIN_REQ_ACK(m_zServer->CZServer::GetZServerID(), in_packet.TargetCharName, in_packet.senderAID, PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_UNKNOWN_CHARACTER);
		return;
	}

	if( g_groupMgr.CPartyMgr::SearchMember(pTargetPlayer->GID) )
	{
		Send_PACKET_IZ_PARTY_JOIN_REQ_ACK(m_zServer->CZServer::GetZServerID(), in_packet.TargetCharName, in_packet.senderAID, PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_ALREADY_OTHERGROUPM);
		return;
	}

	CParty* cpParty = g_groupMgr.CPartyMgr::SearchGroup(in_packet.GRID);
	if( cpParty == NULL )
		return;

	if( cpParty->CParty::GetMemberCount() >= g_groupMgr.CPartyMgr::GetMaxMemberNum() )
	{
		Send_PACKET_IZ_PARTY_JOIN_REQ_ACK(m_zServer->CZServer::GetZServerID(), in_packet.TargetCharName, in_packet.senderAID, PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_MEMBER_OVERSIZE);
		return;
	}

	PACKET_IZ_PARTY_JOIN_REQ packet = {};
	packet.PacketType = HEADER_IZ_PARTY_JOIN_REQ;
	packet.targetAID = pTargetPlayer->AID;
	packet.GRID = in_packet.GRID;
	g_groupMgr.CPartyMgr::GetGroupName(in_packet.GRID, packet.groupName);
	g_userMgr.CUserMgr::SendMsg(packet.targetAID, sizeof(packet), (char*)&packet);
}


void CZSPacketHandler::OnZI_PARTY_JOIN_REQ_ACK(const PACKET_ZI_PARTY_JOIN_REQ_ACK& in_packet)
{
	CParty* cpParty = g_groupMgr.CPartyMgr::SearchGroup(in_packet.GRID);
	if( cpParty == NULL )
		return;

	USER_STRING_MAP_DATA* pUser = g_userMgr.CUserMgr::SearchUser(in_packet.targetAID, 0);
	if( pUser == NULL )
		return;

	PACKET_ZC_PARTY_JOIN_REQ_ACK::enumAnswer answer = in_packet.answer;
	if( answer == PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_JOIN_ACCEPT )
	{
		CPartyMgr::enumResultINM resultINM = g_groupMgr.CPartyMgr::InsertNewMemberV2(cpParty, pUser);
		if( resultINM == CPartyMgr::RESULTINM_OVERSIZE_MEMBER )
			answer = PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_MEMBER_OVERSIZE;
		else
		if( resultINM == CPartyMgr::RESULTINM_DUPLICATE_AID )
			answer = PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_DUPLICATE;
		else
		if( resultINM != CPartyMgr::RESULTINM_SUCCESS )
			answer = PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_UNKNOWN_ERROR;
		else
		{
			cpParty->CParty::NotifyUpdateExpOption(pUser->AID, cpParty->CParty::GetGroupEXPOption());
			cpParty->CParty::NotifyGroupMembers(pUser->AID);
			CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::OnNewbie(m_zServer->CZServer::GetHsvrID(), pUser->GID, pUser->AID, cpParty->CParty::GetGroupID(), pUser->mapName);
		}
	}

	Send_PACKET_IZ_PARTY_JOIN_REQ_ACK(g_userMgr.CUserMgr::SearchUserServerID(cpParty->CParty::GetMaster()), pUser->characterName, cpParty->CParty::GetMaster(), answer);
}


void CZSPacketHandler::OnZI_MEMORIALDUNGEON_COMMAND(const PACKET_ZI_MEMORIALDUNGEON_COMMAND& in_packet)
{
	if( in_packet.Command == PACKET_CZ_MEMORIALDUNGEON_COMMAND::COMMAND_MEMORIALDUNGEON_DESTROY_FORCE )
	{
		CParty* cpParty = g_groupMgr.CPartyMgr::SearchGroup(in_packet.partyName);
		if( cpParty == NULL )
			return;

		CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::Command(cpParty->CParty::GetGroupID(), in_packet.Command);
	}
	else
	{
		USER_STRING_MAP_DATA* pUser = g_userMgr.CUserMgr::SearchUser(in_packet.AID, in_packet.GID);
		if( pUser == NULL )
			return;
		
		CParty* cpParty = g_groupMgr.CPartyMgr::SearchGroup(pUser->GRID);
		if( cpParty == NULL )
			return;

		CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::Command(pUser->GRID, in_packet.Command);
	}
}


void CZSPacketHandler::OnZI_MEMORIALDUNGEON_VISA(const PACKET_ZI_MEMORIALDUNGEON_VISA& in_packet)
{
	USER_STRING_MAP_DATA* pUser = g_userMgr.CUserMgr::SearchUser(in_packet.AID, in_packet.GID);
	if( pUser == NULL )
		return;

	CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::Visa(in_packet.GID, in_packet.AID, pUser->GRID);
}


void CZSPacketHandler::OnGroupInfoChangeV2(int Len)
{
	PACKET_ZI_GROUPINFO_CHANGE_V2 packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	CParty* cpParty = g_groupMgr.CPartyMgr::SearchGroup(packet.GRID);
	if( cpParty == NULL )
		return;

	unsigned long MasterAID = cpParty->CParty::GetMaster();
	if( MasterAID != packet.MasterAID )
		return;

	GROUP_INFO GroupInfo;

	if( packet.FamilyGroup == 1 )
	{
		GroupInfo.expOption = packet.expOption;
	}
	else
	if( packet.expOption == EXP_SHARED )
	{
		if( cpParty->CParty::IsExpSharable() )
		{
			cpParty->CParty::UpdateExpOption(1, false);
			GroupInfo.expOption = EXP_SHARED;
		}
		else
		{
			GroupInfo.expOption = EXP_CHANGE_IMPOSSIBLE;
		}
	}
	else
	{
		GroupInfo.expOption = EXP_NOTSHARED;
	}

	GroupInfo.ItemDivisionRule = packet.ItemDivisionRule;
	GroupInfo.ItemPickupRule = packet.ItemPickupRule;

	cpParty->CParty::ChangeGroupInfo(GroupInfo);
}


void CZSPacketHandler::OnChangeGroupMaster(int Len)
{
	PACKET_ZI_CHANGE_GROUP_MASTER packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	CParty* cpParty = g_groupMgr.CPartyMgr::SearchGroup(packet.GRID);
	if( cpParty == NULL )
		return;

	cpParty->CParty::OnChangeGroupMaster(packet.MasterAID, packet.AID);
}


void CZSPacketHandler::OnSeekParty(int Len)
{
	PACKET_ZI_SEEK_PARTY packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	PACKET_IZ_SEEK_PARTY ouputpacket;
	ouputpacket.PacketType = HEADER_IZ_SEEK_PARTY;
	memcpy(ouputpacket.Name, packet.Name, 24);
	ouputpacket.Job = packet.Job;
	ouputpacket.Level = packet.Level;
	memcpy(ouputpacket.mapName, packet.mapName, 16);
	ouputpacket.Option = packet.Option;
	CZsvrMgr::GetObj()->CZServerMgr::BroadCast(sizeof(ouputpacket), (char*)&ouputpacket);
}


void CZSPacketHandler::OnSeekPartyMember(int Len)
{
	PACKET_ZI_SEEK_PARTY_MEMBER packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	PACKET_IZ_SEEK_PARTY_MEMBER ouputpacket;
	ouputpacket.PacketType = HEADER_IZ_SEEK_PARTY_MEMBER;
	memcpy(ouputpacket.Name, packet.Name, 24);
	ouputpacket.Job = packet.Job;
	ouputpacket.Level = packet.Level;
	memcpy(ouputpacket.mapName, packet.mapName, 16);
	ouputpacket.Option = packet.Option;
	CZsvrMgr::GetObj()->CZServerMgr::BroadCast(sizeof(ouputpacket), (char*)&ouputpacket);
}


void CZSPacketHandler::OnZI_INFO_ENTRY_QUEUE_APPLY(const PACKET_ZI_INFO_ENTRY_QUEUE_APPLY* in_pPacket)
{
	if( in_pPacket->Result == 1 )
	{
		PACKET_IZ_INFO_ENTRY_QUEUE_APPLY outPacket = {};
		outPacket.PacketType = HEADER_IZ_INFO_ENTRY_QUEUE_APPLY;
		outPacket.GID = -1;
		strncpy_s(outPacket.EntryQueueName, countof(outPacket.EntryQueueName), in_pPacket->EntryQueueName, _TRUNCATE);
		outPacket.Ranking = in_pPacket->Ranking;

		if( (in_pPacket->PacketLength - sizeof(PACKET_ZI_INFO_ENTRY_QUEUE_APPLY)) % sizeof(in_pPacket->Info[0]) != 0 )
			return;

		int nCount = (in_pPacket->PacketLength - sizeof(PACKET_ZI_INFO_ENTRY_QUEUE_APPLY)) / sizeof(in_pPacket->Info[0]);
		for( int i = 0; i < nCount; ++i )
		{
			const AID_GID_INFO* Info = &in_pPacket->Info[i];

			int ZSID = g_userMgr.CUserMgr::SearchUserServerID(Info->GID, Info->AID);
			if( ZSID != 0 )
			{
				outPacket.GID = Info->GID;
				CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(outPacket), (char*)&outPacket);
			}
		}
	}
	else
	{
		if( (in_pPacket->PacketLength - sizeof(PACKET_ZI_INFO_ENTRY_QUEUE_APPLY)) % sizeof(in_pPacket->Info[0]) != 0 )
			return;

		int nCount = in_pPacket->PacketLength - sizeof(PACKET_ZI_INFO_ENTRY_QUEUE_APPLY) / sizeof(in_pPacket->Info[0]);
		for( int i = 0; i < nCount; ++i )
		{
			const AID_GID_INFO* Info = &in_pPacket->Info[i];

			CEntryQueueMgr::GetObj()->CEntryQueueMgr::DelApplicant(Info->GID);
		}
	}
}


void CZSPacketHandler::OnZI_REQ_ENTRY_QUEUE_APPLY(const PACKET_ZI_REQ_ENTRY_QUEUE_APPLY& in_packet)
{
	USER_STRING_MAP_DATA* pUser = g_userMgr.CUserMgr::SearchUser(in_packet.AID, in_packet.GID);
	if( pUser == NULL )
	{
		m_zServer->CZServer::SendIZResultEntryQueueApply(in_packet.GID, EQ_RECONNECT_INTER_SERVER, in_packet.EntryQueueName);
		return;
	}

	std::string out_EntryQueueName;
	if( CEntryQueueMgr::GetObj()->CEntryQueueMgr::IsApplicant(in_packet.GID, out_EntryQueueName) == true )
	{
		if( out_EntryQueueName == in_packet.EntryQueueName )
		{
			m_zServer->CZServer::SendIZResultEntryQueueApply(in_packet.GID, EQ_DUPLICATION, in_packet.EntryQueueName);
			return;
		}
		else
		{
			m_zServer->CZServer::SendIZResultEntryQueueApply(in_packet.GID, EQ_INVALID_NAME, in_packet.EntryQueueName);
			return;
		}
	}

	int ZSID = CEntryQueueMgr::GetObj()->CEntryQueueMgr::GetZSID(in_packet.EntryQueueName);
	if( ZSID == -1 )
	{
		m_zServer->CZServer::SendIZResultEntryQueueApply(in_packet.GID, EQ_INVALID_NAME, in_packet.EntryQueueName);
		return;
	}

	if( in_packet.ApplyType == PACKET_ZI_REQ_ENTRY_QUEUE_APPLY::SOLO )
	{
		CEntryQueueMgr::GetObj()->CEntryQueueMgr::AddApplicant(in_packet.GID, in_packet.AID, in_packet.EntryQueueName);

		CVarLenPacketPtr<PACKET_IZ_NOTIFY_ENTRY_QUEUE_APPLY,36> packetPtr;
		packetPtr->PacketType = HEADER_IZ_NOTIFY_ENTRY_QUEUE_APPLY;
		packetPtr->AID = in_packet.AID;
		packetPtr->GID = in_packet.GID;
		strncpy_s(packetPtr->EntryQueueName, countof(packetPtr->EntryQueueName), in_packet.EntryQueueName, _TRUNCATE);
		packetPtr->ApplyType = in_packet.ApplyType;
		ENTRY_QUEUE_APPLY_INFO EntryQueueApply(pUser->AID, pUser->GID, pUser->characterName, pUser->job, pUser->level);
		packetPtr.add((BYTE*)&EntryQueueApply, sizeof(EntryQueueApply));
		packetPtr->PacketLength = static_cast<short>(packetPtr.size());
		CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, packetPtr->PacketLength, packetPtr);
	}
	else
	if( in_packet.ApplyType == PACKET_ZI_REQ_ENTRY_QUEUE_APPLY::PARTY )
	{
		CParty* cpParty = g_groupMgr.CPartyMgr::SearchGroup(pUser->GRID);
		if( cpParty == NULL )
			return;

		if( in_packet.AID != cpParty->CParty::GetMaster() )
		{
			m_zServer->CZServer::SendIZResultEntryQueueApply(in_packet.GID, EQ_NOT_MASTER, in_packet.EntryQueueName);
			return;
		}

		std::list<unsigned long> listGID;
		cpParty->CParty::GetPartyMemberOnlineList(listGID);

		if( listGID.size() == 0 )
			return;

		for( std::list<unsigned long>::iterator iter = listGID.begin(); iter != listGID.end(); ++iter )
		{
			unsigned long memberGID = *iter;

			if( CEntryQueueMgr::GetObj()->CEntryQueueMgr::IsApplicant(memberGID, out_EntryQueueName) == true )
			{
				m_zServer->CZServer::SendIZResultEntryQueueApply(in_packet.GID, EQ_DUPLICATION, in_packet.EntryQueueName);
				return;
			}
		}

		if( cpParty->CParty::IsBattleFieldMapLocation() == true )
		{
			m_zServer->CZServer::SendIZResultEntryQueueApply(in_packet.GID, EQ_LOCATION_BATTLEFIELD, in_packet.EntryQueueName);
			return;
		}

		cpParty->CParty::SendIZBroadcastEntryQueueApply(ZSID, in_packet.AID, in_packet.GID, in_packet.EntryQueueName, in_packet.ApplyType);
	}
	else
	if( in_packet.ApplyType == PACKET_ZI_REQ_ENTRY_QUEUE_APPLY::GUILD )
	{
		CGuild* cpGuild = CIGuildMgr::GetObj()->CGuildMgr::SearchGuild(in_packet.GDID);
		if( cpGuild == NULL )
			return;

		if( !cpGuild->CGuild::IsMaster(in_packet.GID) )
		{
			m_zServer->CZServer::SendIZResultEntryQueueApply(in_packet.GID, EQ_NOT_MASTER, in_packet.EntryQueueName);
			return;
		}

		std::list<std::pair<unsigned long,unsigned long>> listAID;
		cpGuild->CGuild::GetGuildMemberOnlineList(listAID);

		if( listAID.size() == 0 )
			return;

		for( std::list<std::pair<unsigned long,unsigned long>>::iterator iter = listAID.begin(); iter != listAID.end(); ++iter )
		{
			unsigned long memberGID = iter->second;

			if( CEntryQueueMgr::GetObj()->CEntryQueueMgr::IsApplicant(memberGID, out_EntryQueueName) == true )
			{
				m_zServer->CZServer::SendIZResultEntryQueueApply(in_packet.GID, EQ_DUPLICATION, in_packet.EntryQueueName);
				return;
			}
		}

		for( std::list<std::pair<unsigned long,unsigned long>>::iterator iter = listAID.begin(); iter != listAID.end(); ++iter )
		{
			unsigned long memberAID = iter->first;
			unsigned long memberGID = iter->second;

			USER_STRING_MAP_DATA* pMember = g_userMgr.CUserMgr::SearchUser(memberAID, memberGID);
			if( pMember != NULL )
			{
				if( CEntryQueueMgr::GetObj()->CEntryQueueMgr::IsBattleFieldMap(pMember->mapName) == true )
				{
					m_zServer->CZServer::SendIZResultEntryQueueApply(in_packet.GID, EQ_LOCATION_BATTLEFIELD, in_packet.EntryQueueName);
					return;
				}
			}
		}

		CVarLenPacketPtr<PACKET_IZ_NOTIFY_ENTRY_QUEUE_APPLY,3600> packetPtr;
		packetPtr->PacketType = HEADER_IZ_NOTIFY_ENTRY_QUEUE_APPLY;
		packetPtr->AID = in_packet.AID;
		packetPtr->GID = in_packet.GID;
		strncpy_s(packetPtr->EntryQueueName, countof(packetPtr->EntryQueueName), in_packet.EntryQueueName, _TRUNCATE);
		packetPtr->ApplyType = in_packet.ApplyType;

		for( std::list<std::pair<unsigned long,unsigned long>>::iterator iter = listAID.begin(); iter != listAID.end(); ++iter )
		{
			unsigned long memberAID = iter->first;
			unsigned long memberGID = iter->second;

			USER_STRING_MAP_DATA* pMember = g_userMgr.CUserMgr::SearchUser(memberAID, memberGID);
			if( pMember != NULL )
			{
				ENTRY_QUEUE_APPLY_INFO EntryQueueApply(pMember->AID, pMember->GID, pMember->characterName, pMember->job, pMember->level);
				packetPtr.add((BYTE*)&EntryQueueApply, sizeof(EntryQueueApply));
				CEntryQueueMgr::GetObj()->CEntryQueueMgr::AddApplicant(pMember->GID, pMember->AID, in_packet.EntryQueueName);
			}
		}

		if( packetPtr.size() > sizeof(PACKET_IZ_NOTIFY_ENTRY_QUEUE_APPLY) )
		{
			packetPtr->PacketLength = static_cast<short>(packetPtr.size());
			CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, packetPtr->PacketLength, packetPtr);
		}
	}
}


void CZSPacketHandler::OnZI_RESULT_ENTRY_QUEUE_APPLY(const PACKET_ZI_RESULT_ENTRY_QUEUE_APPLY& in_packet)
{
	int ZSID = g_userMgr.CUserMgr::SearchUserServerID(in_packet.GID, in_packet.AID);
	if( ZSID == 0 )
		return;

	if( in_packet.Result != EQ_SUCCESS )
		CEntryQueueMgr::GetObj()->CEntryQueueMgr::DelApplicant(in_packet.GID);

	PACKET_IZ_RESULT_ENTRY_QUEUE_APPLY outPacket = {};
	outPacket.PacketType = HEADER_IZ_RESULT_ENTRY_QUEUE_APPLY;
	outPacket.GID = in_packet.GID;
	outPacket.Result = in_packet.Result;
	strncpy_s(outPacket.EntryQueueName, countof(outPacket.EntryQueueName), in_packet.EntryQueueName, _TRUNCATE);
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(outPacket), (char*)&outPacket);
}


void CZSPacketHandler::OnZI_REQ_ENTRY_QUEUE_CANCEL(const PACKET_ZI_REQ_ENTRY_QUEUE_CANCEL& in_packet)
{
	std::string out_EntryQueueName;
	if( !CEntryQueueMgr::GetObj()->CEntryQueueMgr::IsApplicant(in_packet.GID, out_EntryQueueName) )
		return;

	int ZSID = CEntryQueueMgr::GetObj()->CEntryQueueMgr::GetZSID(out_EntryQueueName);
	if( out_EntryQueueName != in_packet.EntryQueueName || ZSID == -1 )
	{
		PACKET_IZ_RESULT_ENTRY_QUEUE_CANCEL outPacket = {};
		outPacket.PacketType = HEADER_IZ_RESULT_ENTRY_QUEUE_CANCEL;
		outPacket.GID = in_packet.GID;
		outPacket.Result = EQ_INVALID_NAME;
		strncpy_s(outPacket.EntryQueueName, countof(outPacket.EntryQueueName), in_packet.EntryQueueName, _TRUNCATE);
		m_zServer->Send(sizeof(outPacket), (char*)&outPacket);
		return;
	}

	PACKET_IZ_NOTIFY_ENTRY_QUEUE_CANCEL outPacket = {};
	outPacket.PacketType = HEADER_IZ_NOTIFY_ENTRY_QUEUE_CANCEL;
	outPacket.AID = in_packet.AID;
	outPacket.GID = in_packet.GID;
	strncpy_s(outPacket.EntryQueueName, countof(outPacket.EntryQueueName), in_packet.EntryQueueName, _TRUNCATE);
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(outPacket), (char*)&outPacket);
}


void CZSPacketHandler::OnZI_RESULT_ENTRY_QUEUE_CANCEL(const PACKET_ZI_RESULT_ENTRY_QUEUE_CANCEL& in_packet)
{
	if( in_packet.Result == 1 )
		CEntryQueueMgr::GetObj()->CEntryQueueMgr::DelApplicant(in_packet.GID);

	int ZSID = g_userMgr.CUserMgr::SearchUserServerID(in_packet.GID, in_packet.AID);
	if( ZSID == 0 )
		return;

	PACKET_IZ_RESULT_ENTRY_QUEUE_CANCEL outPacket = {};
	outPacket.PacketType = HEADER_IZ_RESULT_ENTRY_QUEUE_CANCEL;
	outPacket.GID = in_packet.GID;
	outPacket.Result = in_packet.Result;
	strncpy_s(outPacket.EntryQueueName, countof(outPacket.EntryQueueName), in_packet.EntryQueueName, _TRUNCATE);
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(outPacket), (char*)&outPacket);
}


void CZSPacketHandler::OnZI_ENTRY_QUEUE_ADMISSION(const PACKET_ZI_ENTRY_QUEUE_ADMISSION& in_packet)
{
	int ZSID = g_userMgr.CUserMgr::SearchUserServerID(in_packet.GID, in_packet.AID);
	if( ZSID == 0 )
	{
		CEntryQueueMgr::GetObj()->CEntryQueueMgr::LogOut(in_packet.GID);
		return;
	}

	PACKET_IZ_ENTRY_QUEUE_ADMISSION outPacket = {};
	outPacket.PacketType = HEADER_IZ_ENTRY_QUEUE_ADMISSION;
	outPacket.GID = in_packet.GID;
	strncpy_s(outPacket.EntryQueueName, countof(outPacket.EntryQueueName), in_packet.EntryQueueName, _TRUNCATE);
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(outPacket), (char*)&outPacket);
}


void CZSPacketHandler::OnZI_ENTRY_QUEUE_ADMISSION_ACCEPT(const PACKET_ZI_ENTRY_QUEUE_ADMISSION_ACCEPT& in_packet)
{
	int ZSID = CEntryQueueMgr::GetObj()->CEntryQueueMgr::GetZSID(in_packet.EntryQueueName);
	if( ZSID == -1 )
	{
		PACKET_IZ_RESULT_ENTRY_QUEUE_ADMISSION_ACCEPT outPacket = {};
		outPacket.PacketType = HEADER_IZ_RESULT_ENTRY_QUEUE_ADMISSION_ACCEPT;
		outPacket.GID = in_packet.GID;
		outPacket.Result = EQ_INVALID_NAME;
		strncpy_s(outPacket.EntryQueueName, countof(outPacket.EntryQueueName), in_packet.EntryQueueName, _TRUNCATE);
		m_zServer->Send(sizeof(outPacket), (char*)&outPacket);
		return;
	}

	PACKET_IZ_NOTIFY_ENTRY_QUEUE_ADMISSION_ACCEPT outPacket = {};
	outPacket.PacketType = HEADER_IZ_NOTIFY_ENTRY_QUEUE_ADMISSION_ACCEPT;
	outPacket.AID = in_packet.AID;
	outPacket.GID = in_packet.GID;
	strncpy_s(outPacket.EntryQueueName, countof(outPacket.EntryQueueName), in_packet.EntryQueueName, _TRUNCATE);
	strncpy_s(outPacket.mapName, countof(outPacket.mapName), in_packet.mapName, _TRUNCATE);
	outPacket.xPos = in_packet.xPos;
	outPacket.yPos = in_packet.yPos;
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(outPacket), (char*)&outPacket);
}


void CZSPacketHandler::OnZI_RESULT_ENTRY_QUEUE_ADMISSION_ACCEPT(const PACKET_ZI_RESULT_ENTRY_QUEUE_ADMISSION_ACCEPT& in_packet)
{
	int ZSID = g_userMgr.CUserMgr::SearchUserServerID(in_packet.GID, in_packet.AID);
	if( ZSID == 0 )
		return;

	PACKET_IZ_RESULT_ENTRY_QUEUE_ADMISSION_ACCEPT outPacket = {};
	outPacket.PacketType = HEADER_IZ_RESULT_ENTRY_QUEUE_ADMISSION_ACCEPT;
	outPacket.GID = in_packet.GID;
	outPacket.Result = in_packet.Result;
	strncpy_s(outPacket.EntryQueueName, countof(outPacket.EntryQueueName), in_packet.EntryQueueName, _TRUNCATE);
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(outPacket), (char*)&outPacket);
}


void CZSPacketHandler::OnZI_ENTRY_QUEUE_ADMISSION_REFUSE(const PACKET_ZI_ENTRY_QUEUE_ADMISSION_REFUSE& in_packet)
{
	int ZSID = CEntryQueueMgr::GetObj()->CEntryQueueMgr::GetZSID(in_packet.EntryQueueName);
	if( ZSID == -1 )
	{
		PACKET_IZ_RESULT_ENTRY_QUEUE_ADMISSION_REFUSE outPacket = {};
		outPacket.PacketType = HEADER_IZ_RESULT_ENTRY_QUEUE_ADMISSION_REFUSE;
		outPacket.GID = in_packet.GID;
		outPacket.Result = EQ_INVALID_NAME;
		strncpy_s(outPacket.EntryQueueName, countof(outPacket.EntryQueueName), in_packet.EntryQueueName, _TRUNCATE);
		m_zServer->Send(31, (char*)&outPacket);
		return;
	}

	PACKET_IZ_NOTIFY_ENTRY_QUEUE_ADMISSION_REFUSE outPacket = {};
	outPacket.PacketType = HEADER_IZ_NOTIFY_ENTRY_QUEUE_ADMISSION_REFUSE;
	outPacket.AID = in_packet.AID;
	outPacket.GID = in_packet.GID;
	strncpy_s(outPacket.EntryQueueName, countof(outPacket.EntryQueueName), in_packet.EntryQueueName, _TRUNCATE);
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(outPacket), (char*)&outPacket);
}


void CZSPacketHandler::OnZI_RESULT_ENTRY_QUEUE_ADMISSION_REFUSE(const PACKET_ZI_RESULT_ENTRY_QUEUE_ADMISSION_REFUSE& in_packet)
{
	if( in_packet.Result == 1 )
		CEntryQueueMgr::GetObj()->CEntryQueueMgr::DelApplicant(in_packet.GID);

	int ZSID = g_userMgr.CUserMgr::SearchUserServerID(in_packet.GID, in_packet.AID);
	if( ZSID == 0 )
		return;

	PACKET_IZ_RESULT_ENTRY_QUEUE_ADMISSION_REFUSE outPacket = {};
	outPacket.PacketType = HEADER_IZ_RESULT_ENTRY_QUEUE_ADMISSION_REFUSE;
	outPacket.GID = in_packet.GID;
	outPacket.Result = in_packet.Result;
	strncpy_s(outPacket.EntryQueueName, countof(outPacket.EntryQueueName), in_packet.EntryQueueName, _TRUNCATE);
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(outPacket), (char*)&outPacket);
}


void CZSPacketHandler::OnZI_LOBBY_ADMISSION(const PACKET_ZI_LOBBY_ADMISSION& in_packet)
{
	int ZSID = g_userMgr.CUserMgr::SearchUserServerID(in_packet.GID, in_packet.AID);
	if( ZSID == 0 )
	{
		CEntryQueueMgr::GetObj()->CEntryQueueMgr::LogOut(in_packet.GID);
		return;
	}

	PACKET_IZ_LOBBY_ADMISSION outPacket = {};
	outPacket.PacketType = HEADER_IZ_LOBBY_ADMISSION;
	outPacket.GID = in_packet.GID;
	strncpy_s(outPacket.EntryQueueName, countof(outPacket.EntryQueueName), in_packet.EntryQueueName, _TRUNCATE);
	strncpy_s(outPacket.LobbyName, countof(outPacket.LobbyName), in_packet.LobbyName, _TRUNCATE);
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(outPacket), (char*)&outPacket);
}


void CZSPacketHandler::OnZI_LOBBY_ADMISSION_V2(const PACKET_ZI_LOBBY_ADMISSION_V2& in_packet)
{
	int ZSID = g_userMgr.CUserMgr::SearchUserServerID(in_packet.GID, in_packet.AID);
	if( ZSID == 0 )
	{
		CEntryQueueMgr::GetObj()->CEntryQueueMgr::LogOut(in_packet.GID);
		return;
	}

	PACKET_IZ_LOBBY_ADMISSION_V2 outPacket = {};
	outPacket.PacketType = HEADER_IZ_LOBBY_ADMISSION_V2;
	outPacket.GID = in_packet.GID;
	strncpy_s(outPacket.EntryQueueName, countof(outPacket.EntryQueueName), in_packet.EntryQueueName, _TRUNCATE);
	strncpy_s(outPacket.LobbyName, countof(outPacket.LobbyName), in_packet.LobbyName, _TRUNCATE);
	outPacket.CampCode = in_packet.CampCode;
	outPacket.xPos = in_packet.xPos;
	outPacket.yPos = in_packet.yPos;
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(outPacket), (char*)&outPacket);
}


void CZSPacketHandler::OnZI_LOBBY_ADMISSION_ACCEPT(const PACKET_ZI_LOBBY_ADMISSION_ACCEPT& in_packet)
{
	int ZSID = CEntryQueueMgr::GetObj()->CEntryQueueMgr::GetZSID(in_packet.LobbyName);
	if( ZSID == -1 )
	{
		PACKET_IZ_RESULT_LOBBY_ADMISSION_ACCEPT outPacket = {};
		outPacket.PacketType = HEADER_IZ_RESULT_LOBBY_ADMISSION_ACCEPT;
		outPacket.GID = in_packet.GID;
		outPacket.Result = EQ_INVALID_NAME;
		strncpy_s(outPacket.EntryQueueName, countof(outPacket.EntryQueueName), in_packet.EntryQueueName, _TRUNCATE);
		strncpy_s(outPacket.LobbyName, countof(outPacket.LobbyName), in_packet.LobbyName, _TRUNCATE);
		m_zServer->Send(sizeof(outPacket), (char*)&outPacket);
		return;
	}

	PACKET_IZ_NOTIFY_LOBBY_ADMISSION_ACCEPT outPacket = {};
	outPacket.PacketType = HEADER_IZ_NOTIFY_LOBBY_ADMISSION_ACCEPT;
	outPacket.AID = in_packet.AID;
	outPacket.GID = in_packet.GID;
	strncpy_s(outPacket.EntryQueueName, countof(outPacket.EntryQueueName), in_packet.EntryQueueName, _TRUNCATE);
	strncpy_s(outPacket.LobbyName, countof(outPacket.LobbyName), in_packet.LobbyName, _TRUNCATE);
	strncpy_s(outPacket.mapName, countof(outPacket.mapName), in_packet.mapName, _TRUNCATE);
	outPacket.xPos = in_packet.xPos;
	outPacket.yPos = in_packet.yPos;
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(outPacket), (char*)&outPacket);
}


void CZSPacketHandler::OnZI_RESULT_LOBBY_ADMISSION_ACCEPT(const PACKET_ZI_RESULT_LOBBY_ADMISSION_ACCEPT& in_packet)
{
	int ZSID = g_userMgr.CUserMgr::SearchUserServerID(in_packet.GID, in_packet.AID);
	if( ZSID == 0 )
		return;

	PACKET_IZ_RESULT_LOBBY_ADMISSION_ACCEPT outPacket = {};
	outPacket.PacketType = HEADER_IZ_RESULT_LOBBY_ADMISSION_ACCEPT;
	outPacket.GID = in_packet.GID;
	outPacket.Result = in_packet.Result;
	strncpy_s(outPacket.EntryQueueName, countof(outPacket.EntryQueueName), in_packet.EntryQueueName, _TRUNCATE);
	strncpy_s(outPacket.LobbyName, countof(outPacket.LobbyName), in_packet.LobbyName, _TRUNCATE);
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(outPacket), (char*)&outPacket);
}


void CZSPacketHandler::OnZI_LOBBY_ADMISSION_REFUSE(const PACKET_ZI_LOBBY_ADMISSION_REFUSE& in_packet)
{
	int ZSID = CEntryQueueMgr::GetObj()->CEntryQueueMgr::GetZSID(in_packet.LobbyName);
	if( ZSID == -1 )
	{
		PACKET_IZ_RESULT_LOBBY_ADMISSION_REFUSE outPacket = {};
		outPacket.PacketType = HEADER_IZ_RESULT_LOBBY_ADMISSION_REFUSE;
		outPacket.GID = in_packet.GID;
		outPacket.Result = EQ_INVALID_NAME;
		strncpy_s(outPacket.EntryQueueName, countof(outPacket.EntryQueueName), in_packet.EntryQueueName, _TRUNCATE);
		strncpy_s(outPacket.LobbyName, countof(outPacket.LobbyName), in_packet.LobbyName, _TRUNCATE);
		m_zServer->Send(sizeof(outPacket), (char*)&outPacket);
		return;
	}

	PACKET_IZ_NOTIFY_LOBBY_ADMISSION_REFUSE outPacket = {};
	outPacket.PacketType = HEADER_IZ_NOTIFY_LOBBY_ADMISSION_REFUSE;
	outPacket.AID = in_packet.AID;
	outPacket.GID = in_packet.GID;
	strncpy_s(outPacket.EntryQueueName, countof(outPacket.LobbyName), in_packet.EntryQueueName, _TRUNCATE);
	strncpy_s(outPacket.LobbyName, countof(outPacket.LobbyName), in_packet.LobbyName, _TRUNCATE);
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(outPacket), (char*)&outPacket);
}


void CZSPacketHandler::OnZI_RESULT_LOBBY_ADMISSION_REFUSE(const PACKET_ZI_RESULT_LOBBY_ADMISSION_REFUSE& in_packet)
{
	if( in_packet.Result == 1 )
		CEntryQueueMgr::GetObj()->CEntryQueueMgr::DelApplicant(in_packet.GID);

	int ZSID = g_userMgr.CUserMgr::SearchUserServerID(in_packet.GID, in_packet.AID);
	if( ZSID == NULL )
		return;

	PACKET_IZ_RESULT_LOBBY_ADMISSION_REFUSE outPacket = {};
	outPacket.PacketType = HEADER_IZ_RESULT_LOBBY_ADMISSION_REFUSE;
	outPacket.GID = in_packet.GID;
	outPacket.Result = in_packet.Result;
	strncpy_s(outPacket.EntryQueueName, countof(outPacket.EntryQueueName), in_packet.EntryQueueName, _TRUNCATE);
	strncpy_s(outPacket.LobbyName, countof(outPacket.LobbyName), in_packet.LobbyName, _TRUNCATE);
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(outPacket), (char*)&outPacket);
}


void CZSPacketHandler::OnZI_ENTRY_QUEUE_MOVE_ROOM(const PACKET_ZI_ENTRY_QUEUE_MOVE_ROOM& in_packet)
{
	int ZSID = g_userMgr.CUserMgr::SearchUserServerID(in_packet.GID, in_packet.AID);
	if( ZSID == 0 )
		return;

	PACKET_IZ_ENTRY_QUEUE_MOVE_ROOM outPacket = {};
	outPacket.PacketType = HEADER_IZ_ENTRY_QUEUE_MOVE_ROOM;
	outPacket.GID = in_packet.GID;
	strncpy_s(outPacket.mapName, countof(outPacket.mapName), in_packet.mapName, _TRUNCATE);
	outPacket.xPos = in_packet.xPos;
	outPacket.yPos = in_packet.yPos;
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(outPacket), (char*)&outPacket);
}


void CZSPacketHandler::OnZI_LOBBY_MOVE_ROOM(const PACKET_ZI_LOBBY_MOVE_ROOM& in_packet)
{
	int ZSID = g_userMgr.CUserMgr::SearchUserServerID(in_packet.GID, in_packet.AID);
	if( ZSID == 0 )
		return;

	PACKET_IZ_LOBBY_MOVE_ROOM outPacket = {};
	outPacket.PacketType = HEADER_IZ_LOBBY_MOVE_ROOM;
	outPacket.GID = in_packet.GID;
	strncpy_s(outPacket.mapName, countof(outPacket.mapName), in_packet.mapName, _TRUNCATE);
	outPacket.xPos = in_packet.xPos;
	outPacket.yPos = in_packet.yPos;
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(outPacket), (char*)&outPacket);
}


void CZSPacketHandler::OnZI_ENTRY_QUEUE_NAME(const PACKET_ZI_ENTRY_QUEUE_NAME* in_pPacket)
{
	if( (in_pPacket->PacketLength - sizeof(PACKET_ZI_ENTRY_QUEUE_NAME)) % sizeof(in_pPacket->EntryQueueName[0]) != 0 )
		return;

	int nCount = (in_pPacket->PacketLength - sizeof(PACKET_ZI_ENTRY_QUEUE_NAME)) / sizeof(in_pPacket->EntryQueueName[0]);

	for( int i = 0; i < nCount; ++i )
		CEntryQueueMgr::GetObj()->CEntryQueueMgr::AddEntryQueue(in_pPacket->EntryQueueName[i], m_zServer->CZServer::GetZServerID());
}


void CZSPacketHandler::OnZI_ENTRY_QUEUE_DELETE_GID(const PACKET_ZI_ENTRY_QUEUE_DELETE_GID& in_packet)
{
	CEntryQueueMgr::GetObj()->CEntryQueueMgr::DelApplicant(in_packet.GID);
}


void CZSPacketHandler::OnZI_ENTRY_QUEUE_RANKING(const PACKET_ZI_ENTRY_QUEUE_RANKING& in_packet)
{
	int ZSID = CEntryQueueMgr::GetObj()->CEntryQueueMgr::GetZSID(in_packet.EntryQueueName);
	if( ZSID == -1 )
		return;

	PACKET_IZ_ENTRY_QUEUE_RANKING outPacket = {};
	outPacket.PacketType = HEADER_IZ_ENTRY_QUEUE_RANKING;
	outPacket.AID = in_packet.AID;
	outPacket.GID = in_packet.GID;
	strncpy_s(outPacket.EntryQueueName, countof(outPacket.EntryQueueName), in_packet.EntryQueueName, _TRUNCATE);
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(outPacket), (char*)&outPacket);
}


void CZSPacketHandler::OnZI_NOTIFY_ENTRY_QUEUE_RANKING(const PACKET_ZI_NOTIFY_ENTRY_QUEUE_RANKING& in_packet)
{
	int ZSID = g_userMgr.CUserMgr::SearchUserServerID(in_packet.GID, in_packet.AID);
	if( ZSID == 0 )
		return;

	PACKET_IZ_NOTIFY_ENTRY_QUEUE_RANKING outPacket = {};
	outPacket.PacketType = HEADER_IZ_NOTIFY_ENTRY_QUEUE_RANKING;
	outPacket.GID = in_packet.GID;
	strncpy_s(outPacket.EntryQueueName, countof(outPacket.EntryQueueName), in_packet.EntryQueueName, _TRUNCATE);
	outPacket.Ranking = in_packet.Ranking;
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(outPacket), (char*)&outPacket);
}


void CZSPacketHandler::OnZI_JOB_CHANGE(const PACKET_ZI_JOB_CHANGE& in_packet)
{
	USER_STRING_MAP_DATA* pUser = g_userMgr.CUserMgr::SearchUser(in_packet.AID, in_packet.GID);
	if( pUser == NULL )
		return;

	pUser->job = in_packet.job;
}


void CZSPacketHandler::OnZI_MEMORIALDUNGEON_SUBSCRIPTION2(const int in_nPacketSize)
{
	char buf[1024] = {};
	if( m_recvQueue->CPacketQueue::GetData(in_nPacketSize, buf) == -1 )
		return;

	PACKET_ZI_MEMORIALDUNGEON_SUBSCRIPTION2* zi_subscription_packet = reinterpret_cast<PACKET_ZI_MEMORIALDUNGEON_SUBSCRIPTION2*>(buf);
	size_t nMDNameLength = zi_subscription_packet->PacketLength - sizeof(PACKET_ZI_MEMORIALDUNGEON_SUBSCRIPTION2);
	zi_subscription_packet->NickName[countof(zi_subscription_packet->NickName)-1] = '\0';
	zi_subscription_packet->MemorialDungeonName[nMDNameLength] = '\0';

	CParty* cpParty = g_groupMgr.CPartyMgr::SearchGroup(zi_subscription_packet->GRID);
	if( cpParty == NULL || zi_subscription_packet->AID != cpParty->CParty::GetMaster() )
	{
		void* pPacketBuffer = _malloca(sizeof(PACKET_IZ_MEMORIALDUNGEON_MSG2) + nMDNameLength);
		if( pPacketBuffer == NULL )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Stack Memory Buffer is NULL.");
			return;
		}

		NMemoryHelper mHelper(pPacketBuffer, sizeof(PACKET_IZ_MEMORIALDUNGEON_MSG2) + nMDNameLength);
		PACKET_IZ_MEMORIALDUNGEON_MSG2* iz_msg_packet = (PACKET_IZ_MEMORIALDUNGEON_MSG2*)mHelper.NMemoryHelper::Get(sizeof(PACKET_IZ_MEMORIALDUNGEON_MSG2));
		iz_msg_packet->PacketType = HEADER_IZ_MEMORIALDUNGEON_MSG2;
		iz_msg_packet->AID = zi_subscription_packet->AID;
		iz_msg_packet->GID = zi_subscription_packet->GID;
		iz_msg_packet->Notify = PACKET_IZ_MEMORIALDUNGEON_MSG2::MEMORIALDUNGEON_SUBSCRIPTION_ERROR_UNKNOWN;
		if( nMDNameLength > 0 )
			memcpy_s(mHelper.NMemoryHelper::Get(nMDNameLength), nMDNameLength, zi_subscription_packet->MemorialDungeonName, nMDNameLength); //NOTE: compiled out in official code due to some mistake
		iz_msg_packet->PacketLength = WORD(mHelper.NMemoryHelper::GetUsedBytes());
		m_zServer->Send(iz_msg_packet->PacketLength, (char*)&iz_msg_packet);

		_freea(pPacketBuffer);
		return;
	}

	CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::Subscription(m_zServer->CZServer::GetHsvrID(), zi_subscription_packet->AID, zi_subscription_packet->GID, zi_subscription_packet->MemorialDungeonName, zi_subscription_packet->NickName, zi_subscription_packet->GRID, cpParty->CParty::GetGroupName());
}


void CZSPacketHandler::OnZI_PING_LIVE(const PACKET_ZI_PING_LIVE& in_packet)
{
}


void CZSPacketHandler::OnZI_STATEINFO(const PACKET_ZI_STATEINFO& in_packet)
{
	m_zServer->m_UsedMemoryKBytes = in_packet.UsedKBytesMemory;
	m_zServer->m_TotalNPCNum = in_packet.NumTotalNPC;
}


void CZSPacketHandler::OnOTHER_ZONE_PC_SEND_MSG(const PACKET_ZI_OTHER_ZONE_PC_SEND_MSG& in_packet)
{
}
