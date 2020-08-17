#include "AgitMapRes.h"
#include "CharacterMgr.h"
#include "CharInfoDB.h"
#include "Enum.h"
#include "ISvrIOPacketHandler.h"
#include "ItemLog.h"
#include "MakerRankMgr.h"
#include "MapResMgr.h"
#include "MapTypeProperty.h"
#include "PC.h"
#include "PCPacketHandler.h"
#include "ZGuildMgr.h"
#include "ZoneProcess.h"
#include "ZSAcceptHandler.h"
#include "ZoneProcessStuff.h"
#include "Client/CharacterServerClient/C2CharacterServerClient.h"
#include "Client/InterServerClient/C2InterServerClient.h"
#include "Common/MsgStrings.h" // MSI_*
#include "Common/Packet.h"
#include "Common/PacketLengthExMgr.h"
#include "Instant map/InstantMapConfiguration.h"
#include "Instant map/InstantMapLib.h"
#include "Instant map/InstantMapMgr.h"
#include "Memorial Dungeon/MemorialDungeonMgr.h"
#include "shared/Client.h" // PC_TYPE
#include "shared/NCriticalErrorLog.h"
#include "shared/NOutputTextMgr.h"
#include "shared/ServerInfo.h"
#include "shared/shared.h"


CISvrIOPacketHandler::CISvrIOPacketHandler()
: m_OldHeader(0), m_OldPacketSize(0), m_lastError(0)
{
}


CISvrIOPacketHandler::~CISvrIOPacketHandler()
{
}


void CISvrIOPacketHandler::SetLastError(DWORD lastError)
{
	m_lastError = lastError;
}


int CISvrIOPacketHandler::OnProcess()
{
	int count = 0;
	while( 1 )
	{
		if( m_recvQueue->CPacketQueue::GetSize() < sizeof(PACKET) )
			return -1;

		++count;
		if( count >= 700 )
			return -1;

		short Header = 0;
		m_recvQueue->CPacketQueue::PeekData(sizeof(Header), (char*)&Header);

		std::pair<CPacketLengthExMgr::enumFixedPacketRet,int> fpRet = g_packetLenMapEx.CPacketLengthExMgr::IsFixedPacket(Header);

		unsigned short size;
		if( fpRet.first == CPacketLengthExMgr::FIXED )
		{
			size = fpRet.second;
		}
		else
		if( fpRet.first == CPacketLengthExMgr::VARIABLE )
		{
			if( m_recvQueue->CPacketQueue::GetSize() < sizeof(PACKETV) )
				return -1;

			int Header = 0;
			m_recvQueue->CPacketQueue::PeekData(sizeof(Header), (char*)&Header);

			size = Header >> 16;
			if( size < fpRet.second )
			{
				NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "variable packet size minimum guarantee. header(%d) packetSize(%d) min(%d)", Header, size, fpRet.second);
				return 0;
			}
		}
		else
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "unknown packet receive header(%d)", Header);
			return 0;
		}

		if( size == 0 || size >= 20480 )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "InterServer PacketSize error- %d  Header:%d FreeSize=%d QueueSize:%d", size, Header, m_recvQueue->CPacketQueue::GetFreeSize(), m_recvQueue->CPacketQueue::GetSize());
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "m_OldHeader:%d  m_OldPacketSize:%d", m_OldHeader, m_OldPacketSize);
			m_recvQueue->CPacketQueue::Reset();
			return 0;
		}

		if( m_recvQueue->CPacketQueue::GetSize() >= size )
		{
			int Type = this->DispatchPacket(Header, size);
			if( Type != -1 )
			{
				NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "InterServer DispatchPacket error- %d  Header:%d FreeSize=%d QueueSize:%d", size, Header, m_recvQueue->CPacketQueue::GetFreeSize(), m_recvQueue->CPacketQueue::GetSize());
				return Type;
			}
		}

		m_OldHeader = Header;
		m_OldPacketSize = size;
	}
}


int CISvrIOPacketHandler::DispatchPacket(short Header, int packetSize)
{
	switch( Header )
	{
	case HEADER_PING:
	{
		PACKET_PING ping;
		m_recvQueue->CPacketQueue::GetData(sizeof(ping), (char*)&ping);
	}
	break;
	case HEADER_IZ_ENTRY_QUEUE_RANKING:
	{
		PACKET_IZ_ENTRY_QUEUE_RANKING packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_ENTRY_QUEUE_RANKING(packet);
	}
	break;
	case HEADER_IZ_NOTIFY_ENTRY_QUEUE_RANKING:
	{
		PACKET_IZ_NOTIFY_ENTRY_QUEUE_RANKING packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_NOTIFY_ENTRY_QUEUE_RANKING(packet);
	}
	break;
	case HEADER_IZ_ENTRY_QUEUE_LOGOUT:
	{
		PACKET_IZ_ENTRY_QUEUE_LOGOUT packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_ENTRY_QUEUE_LOGOUT(packet);
	}
	break;
	case HEADER_IZ_ENTRY_QUEUE_MOVE_ROOM:
	{
		PACKET_IZ_ENTRY_QUEUE_MOVE_ROOM packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_ENTRY_QUEUE_MOVE_ROOM(packet);
	}
	break;
	case HEADER_IZ_LOBBY_MOVE_ROOM:
	{
		PACKET_IZ_LOBBY_MOVE_ROOM packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_LOBBY_MOVE_ROOM(packet);
	}
	break;
	case HEADER_IZ_INFO_ENTRY_QUEUE_APPLY:
	{
		PACKET_IZ_INFO_ENTRY_QUEUE_APPLY packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_INFO_ENTRY_QUEUE_APPLY(packet);
	}
	break;
	case HEADER_IZ_NOTIFY_ENTRY_QUEUE_APPLY:
	{
		PACKET_IZ_NOTIFY_ENTRY_QUEUE_APPLY* pIZ_NOTIFY_ENTRY_QUEUE_APPLY = (PACKET_IZ_NOTIFY_ENTRY_QUEUE_APPLY*)_malloca(packetSize);
		m_recvQueue->CPacketQueue::GetData(packetSize, (char*)pIZ_NOTIFY_ENTRY_QUEUE_APPLY);
		this->CISvrIOPacketHandler::OnIZ_NOTIFY_ENTRY_QUEUE_APPLY(pIZ_NOTIFY_ENTRY_QUEUE_APPLY);
		_freea(pIZ_NOTIFY_ENTRY_QUEUE_APPLY);
	}
	break;
	case HEADER_IZ_RESULT_ENTRY_QUEUE_APPLY:
	{
		PACKET_IZ_RESULT_ENTRY_QUEUE_APPLY packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_RESULT_ENTRY_QUEUE_APPLY(packet);
	}
	break;
	case HEADER_IZ_NOTIFY_ENTRY_QUEUE_CANCEL:
	{
		PACKET_IZ_NOTIFY_ENTRY_QUEUE_CANCEL packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_NOTIFY_ENTRY_QUEUE_CANCEL(packet);
	}
	break;
	case HEADER_IZ_RESULT_ENTRY_QUEUE_CANCEL:
	{
		PACKET_IZ_RESULT_ENTRY_QUEUE_CANCEL packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_RESULT_ENTRY_QUEUE_CANCEL(packet);
	}
	break;
	case HEADER_IZ_ENTRY_QUEUE_ADMISSION:
	{
		PACKET_IZ_ENTRY_QUEUE_ADMISSION packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_ENTRY_QUEUE_ADMISSION(packet);
	}
	break;
	case HEADER_IZ_NOTIFY_ENTRY_QUEUE_ADMISSION_ACCEPT:
	{
		PACKET_IZ_NOTIFY_ENTRY_QUEUE_ADMISSION_ACCEPT packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_NOTIFY_ENTRY_QUEUE_ADMISSION_ACCEPT(packet);
	}
	break;
	case HEADER_IZ_RESULT_ENTRY_QUEUE_ADMISSION_ACCEPT:
	{
		PACKET_IZ_RESULT_ENTRY_QUEUE_ADMISSION_ACCEPT packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_RESULT_ENTRY_QUEUE_ADMISSION_ACCEPT(packet);
	}
	break;
	case HEADER_IZ_NOTIFY_ENTRY_QUEUE_ADMISSION_REFUSE:
	{
		PACKET_IZ_NOTIFY_ENTRY_QUEUE_ADMISSION_REFUSE packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_NOTIFY_ENTRY_QUEUE_ADMISSION_REFUSE(packet);
	}
	break;
	case HEADER_IZ_RESULT_ENTRY_QUEUE_ADMISSION_REFUSE:
	{
		PACKET_IZ_RESULT_ENTRY_QUEUE_ADMISSION_REFUSE packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_RESULT_ENTRY_QUEUE_ADMISSION_REFUSE(packet);
	}
	break;
	case HEADER_IZ_LOBBY_ADMISSION:
	{
		PACKET_IZ_LOBBY_ADMISSION packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_LOBBY_ADMISSION(packet);
	}
	break;
	case HEADER_IZ_LOBBY_ADMISSION_V2:
	{
		PACKET_IZ_LOBBY_ADMISSION_V2 packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_LOBBY_ADMISSION_V2(packet);
	}
	break;
	case HEADER_IZ_NOTIFY_LOBBY_ADMISSION_ACCEPT:
	{
		PACKET_IZ_NOTIFY_LOBBY_ADMISSION_ACCEPT packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_NOTIFY_LOBBY_ADMISSION_ACCEPT(packet);
	}
	break;
	case HEADER_IZ_RESULT_LOBBY_ADMISSION_ACCEPT:
	{
		PACKET_IZ_RESULT_LOBBY_ADMISSION_ACCEPT packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_RESULT_LOBBY_ADMISSION_ACCEPT(packet);
	}
	break;
	case HEADER_IZ_NOTIFY_LOBBY_ADMISSION_REFUSE:
	{
		PACKET_IZ_NOTIFY_LOBBY_ADMISSION_REFUSE packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_NOTIFY_LOBBY_ADMISSION_REFUSE(packet);
	}
	break;
	case HEADER_IZ_RESULT_LOBBY_ADMISSION_REFUSE:
	{
		PACKET_IZ_RESULT_LOBBY_ADMISSION_REFUSE packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_RESULT_LOBBY_ADMISSION_REFUSE(packet);
	}
	break;
	case HEADER_IZ_AUTH_ACK:
	{
		PACKET_IZ_AUTH_ACK packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_AUTH_ACK(packet);
	}
	break;
	case HEADER_IZ_IRMAIL_NOTIFY:
	{
		PACKET_IZ_IRMAIL_NOTIFY packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_IRMAIL_NOTIFY(packet);
	}
	break;
	case HEADER_IZ_BROADCASTING_SPECIAL_ITEM_OBTAIN:
	{
		std::vector<BYTE> packet(packetSize);
		m_recvQueue->CPacketQueue::GetData(packetSize, (char*)&packet.front());
		this->CISvrIOPacketHandler::OnIZ_BROADCASTING_SPECIAL_ITEM_OBTAIN(packet);
	}
	break;
	case HEADER_IZ_MEMORIALDUNGEON_OPENSTATE:
	{
		PACKET_IZ_MEMORIALDUNGEON_OPENSTATE packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_OPENSTATE(packet);
	}
	break;
	case HEADER_IZ_LEAVE_GROUP:
	{
		PACKET_IZ_LEAVE_GROUP packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_LEAVE_GROUP(packet);
	}
	break;
	case HEADER_IZ_MEMORIALDUNGEON_COMMAND:
	{
		PACKET_IZ_MEMORIALDUNGEON_COMMAND packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_COMMAND(packet);
	}
	break;
	case HEADER_IZ_MEMORIALDUNGEON_VISA:
	{
		PACKET_IZ_MEMORIALDUNGEON_VISA packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_VISA(packet);
	}
	break;
	case HEADER_IZ_MEMORIALDUNGEON_SYNC:
	{
		PACKET_IZ_MEMORIALDUNGEON_SYNC packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_SYNC(packet);
	}
	break;
	case HEADER_IZ_MEMORIALDUNGEON_SYNC2:
	{
		this->CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_SYNC2(packetSize);
	}
	break;
	case HEADER_IZ_MEMORIALDUNGEON_NOTIFY:
	{
		PACKET_IZ_MEMORIALDUNGEON_NOTIFY packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_NOTIFY(packet);
	}
	break;
	case HEADER_IZ_MEMORIALDUNGEON_INFO:
	{
		PACKET_IZ_MEMORIALDUNGEON_INFO packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_INFO(packet);
	}
	break;
	case HEADER_IZ_MEMORIALDUNGEON_INFO2:
	{
		this->CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_INFO2(packetSize);
	}
	break;
	case HEADER_IZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY:
	{
		PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY(packet);
	}
	break;
	case HEADER_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO:
	{
		PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO(packet);
	}
	break;
	case HEADER_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO2:
	{
		this->CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO2(packetSize);
	}
	break;
	case HEADER_IZ_PARTY_JOIN_REQ_ACK:
	{
		PACKET_IZ_PARTY_JOIN_REQ_ACK packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_PARTY_JOIN_REQ_ACK(packet);
	}
	break;
	case HEADER_IZ_PARTY_JOIN_REQ:
	{
		PACKET_IZ_PARTY_JOIN_REQ packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_PARTY_JOIN_REQ(packet);
	}
	break;
	case HEADER_IZ_MEMORIALDUNGEON_MSG:
	{
		PACKET_IZ_MEMORIALDUNGEON_MSG packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_MSG(packet);
	}
	break;
	case HEADER_IZ_MEMORIALDUNGEON_MSG2:
	{
		this->CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_MSG2(packetSize);
	}
	break;
	case HEADER_XX_CONNECT:
	{
		PACKET_XX_CONNECT packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnXX_CONNECT(packet);
	}
	break;
	case HEADER_XX_DISCONNECT:
	{
		PACKET_XX_DISCONNECT packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnXX_DISCONNECT(packet);
	}
	break;
	case HEADER_IZ_INSTNATMAP_DESTROY:
	{
		PACKET_IZ_INSTNATMAP_DESTROY packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnINSTNATMAP_DESTROY(packet);
	}
	break;
	case HEADER_IZ_INSTANTMAP_PLAYER_ENTER:
	{
		PACKET_IZ_INSTANTMAP_PLAYER_ENTER packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnINSTANTMAP_PLAYER_ENTER(packet);
	}
	break;
	case HEADER_IZ_INSTANTMAP_CREATE_REQ:
	{
		PACKET_IZ_INSTANTMAP_CREATE_REQ packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnINSTANTMAP_CREATE_REQ(packet);
	}
	break;
	case HEADER_IZ_WHISPER:
	{
		this->CISvrIOPacketHandler::OnWhisper(packetSize);
	}
	break;
	case HEADER_IZ_WHISPER_2:
	{
		this->CISvrIOPacketHandler::OnWhisper_2(packetSize);
	}
	break;
	case HEADER_IZ_ACK_WHISPER:
	{
		this->CISvrIOPacketHandler::OnWhisperAck(packetSize);
	}
	break;
	case HEADER_IZ_USER_COUNT:
	{
		this->CISvrIOPacketHandler::OnUserCount(packetSize);
	}
	break;
	case HEADER_IZ_BROADCAST:
	{
		std::vector<char> buffer(packetSize);
		PACKET_IZ_BROADCAST& packet = *reinterpret_cast<PACKET_IZ_BROADCAST*>(&buffer.front());
		m_recvQueue->CPacketQueue::GetData(packetSize, (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_BROADCAST(&packet);
	}
	break;
	case HEADER_IZ_ADD_MEMBER_TO_GROUP:
	case HEADER_IZ_ADD_MEMBER_TO_GROUP2:
	{
		this->CISvrIOPacketHandler::OnAddMemberToGroup(packetSize);
	}
	break;
	case HEADER_IZ_DELETE_MEMBER_FROM_GROUP:
	{
		this->CISvrIOPacketHandler::OnDeleteMemberFromGroup(packetSize);
	}
	break;
	case HEADER_IZ_ACK_MAKE_GROUP:
	{
		this->CISvrIOPacketHandler::OnAckMakeGroup(packetSize);
	}
	break;
	case HEADER_IZ_GROUP_LIST:
	{
		this->CISvrIOPacketHandler::OnGroupList(packetSize);
	}
	break;
	case HEADER_IZ_ACK_REQ_JOIN_GROUP:
	{
		this->CISvrIOPacketHandler::OnAckReqJoinGroup(packetSize);
	}
	break;
	case HEADER_IZ_REQ_JOIN_GROUP:
	{
		this->CISvrIOPacketHandler::OnReqJoinGroup(packetSize);
	}
	break;
	case HEADER_ZI_GRID_UPDATE:
	{
		this->CISvrIOPacketHandler::OnGRIDUpdate(packetSize);
	}
	break;
	case HEADER_IZ_CHAT_PARTY:
	{
		this->CISvrIOPacketHandler::OnChatParty(packetSize);
	}
	break;
	case HEADER_IZ_DISCONNECT_ALL:
	{
		this->CISvrIOPacketHandler::OnDisconnectAll(packetSize);
	}
	break;
	case HEADER_IZ_REQ_SERVERSTATE:
	{
		this->CISvrIOPacketHandler::OnReqServerState(packetSize);
	}
	break;
	case HEADER_IZ_DISCONNECT_CHARACTER:
	{
		this->CISvrIOPacketHandler::OnDisconnectCharacter(packetSize);
	}
	break;
	case HEADER_IZ_MOVE:
	{
		this->CISvrIOPacketHandler::OnSpecialMove(packetSize);
	}
	break;
	case HEADER_IZ_DIVORCE:
	{
		this->CISvrIOPacketHandler::OnDivorce(packetSize);
	}
	break;
	case HEADER_IZ_FRIENDS_LIST:
	{
		this->CISvrIOPacketHandler::OnFriendsList(packetSize);
	}
	break;
	case HEADER_IZ_FRIENDS_STATE:
	{
		this->CISvrIOPacketHandler::OnFriendsState(packetSize);
	}
	break;
	case HEADER_IZ_ADD_FRIENDS:
	{
		this->CISvrIOPacketHandler::OnAddFriend(packetSize);
	}
	break;
	case HEADER_IZ_DELETE_FRIENDS:
	{
		this->CISvrIOPacketHandler::OnDeleteFriends(packetSize);
	}
	break;
	case HEADER_IZ_RESULT_MAKE_GUILD:
	{
		this->CISvrIOPacketHandler::OnResultGuildMake(packetSize);
	}
	break;
	case HEADER_IZ_REQ_JOIN_GUILD:
	{
		this->CISvrIOPacketHandler::OnReqJoinGuild(packetSize);
	}
	break;
	case HEADER_IZ_ACK_REQ_JOIN_GUILD:
	{
		this->CISvrIOPacketHandler::OnAckReqJoinGuild(packetSize);
	}
	break;
	case HEADER_IZ_UPDATE_CHARGDID:
	{
		this->CISvrIOPacketHandler::OnUpdateCharGDID(packetSize);
	}
	break;
	case HEADER_IZ_GUILDINFO_TOD:
	{
		this->CISvrIOPacketHandler::OnGuildInfo(packetSize);
	}
	break;
	case HEADER_IZ_REQ_JOIN_GUILD2:
	{
		PACKET_IZ_REQ_JOIN_GUILD2 packet = {};
		m_recvQueue->CPacketQueue::GetData(packetSize, (char*)&packet);
		this->CISvrIOPacketHandler::OnReqJoinGuild2(packet);
	}
	break;
	case HEADER_IZ_GUILD_CHANGEOWNER_AGIT:
	{
		this->CISvrIOPacketHandler::OnChangeOwnerAgit(packetSize);
	}
	break;
	case HEADER_IZ_ACK_LEAVE_GUILD:
	case HEADER_IZ_ACK_BAN_GUILD:
	case HEADER_IZ_REQ_DISORGANIZE_GUILD_RESULT:
	case HEADER_IZ_UPDATE_CHARSTAT:
	case HEADER_IZ_GUILD_NOTICE:
	case HEADER_IZ_ACK_REQ_ALLY_GUILD:
	case HEADER_IZ_ADD_ALLY_GUILD:
	case HEADER_IZ_ADD_HOSTILE_GUILD:
	case HEADER_IZ_GUILD_MEMBER_ADD:
	case HEADER_IZ_DELETE_RELATED_GUILD:
	case HEADER_IZ_ADD_EXP:
	case HEADER_IZ_GUILD_MEMBERINFO_FRAG:
	case HEADER_IZ_GUILD_ZENY_UPDATE_ALL:
	case HEADER_IZ_GUILD_CHANGEMAXUSER:
	case HEADER_IZ_FREE_GUILD:
	case HEADER_IZ_GUILD_MAP_CHANGE:
	case HEADER_IZ_ACK_BAN_GUILD_SSO:
	case HEADER_IZ_GET_GUILD_EMBLEM_IMG2:
	case HEADER_IZ_MYGUILD_BASICINFO:
	{
		__pragma(pack(push,1)) struct TEMPHEADER { short PacketType; unsigned long GDID; } temp; __pragma(pack(pop))
		m_recvQueue->CPacketQueue::PeekData(sizeof(temp), (char*)&temp);

		m_recvQueue->CPacketQueue::GetData(packetSize, m_PacketBuffer);
		g_ZGuildMgr.CZGuildMgr::SendPacket(temp.GDID, temp.PacketType, packetSize, m_PacketBuffer);
	}
	break;
	case HEADER_IZ_ACK_MYGUILD_MEMBER_INFO:
	case HEADER_IZ_ACK_MYGUILD_POSITION:
	case HEADER_IZ_ACK_MYGUILD_BANISH:
	case HEADER_IZ_ACK_MYGUILD_LIST:
	case HEADER_IZ_GET_GUILD_EMBLEM_IMG:
	case HEADER_IZ_MEMBERMGR_INFO:
	case HEADER_IZ_ACK_CHANGE_MEMBERPOS:
	case HEADER_IZ_ACK_OPEN_MEMBER_INFO:
	case HEADER_IZ_ACK_GUILD_POSITION_INFO:
	case HEADER_IZ_SKILL_INFO:
	case HEADER_IZ_BAN_LIST:
	case HEADER_IZ_OTHER_GUILD_LIST:
	case HEADER_IZ_GUILD_LIST_TOD:
	case HEADER_IZ_GUILD_MEMBERINFO_TOD:
	case HEADER_IZ_GUILD_ALLYINFO_TOD:
	case HEADER_IZ_GUILD_BANISHINFO_TOD:
	case HEADER_IZ_GUILD_MPOSITION_TOD:
	case HEADER_IZ_GUILD_NOTICE_TOD:
	case HEADER_IZ_GUILD_CHAT:
	case HEADER_IZ_GUILD_NOTIFYSKILLDATA:
	{
		__pragma(pack(push,1)) struct TEMPHEADER { short PacketType; unsigned short PacketLength; unsigned long GDID; } temp; __pragma(pack(pop))
		m_recvQueue->CPacketQueue::PeekData(sizeof(temp), (char*)&temp);

		if( m_recvQueue->CPacketQueue::GetData(packetSize, m_PacketBuffer) == -1 )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Error m_recvQueue->GetData Size = %d, QSize = %d, FSize = %d", -1, m_recvQueue->CPacketQueue::GetSize(), m_recvQueue->CPacketQueue::GetFreeSize());
			m_recvQueue->CPacketQueue::Reset();
		}

		g_ZGuildMgr.CZGuildMgr::SendPacket(temp.GDID, temp.PacketType, packetSize, m_PacketBuffer);
	}
	break;
	case HEADER_IZ_GUILD_ZENY:
	{
//		this->CISvrIOPacketHandler::OnAckGuildZeny(packetSize);
	}
	break;
	case HEADER_IZ_NOTIFY_MAKERRANK:
	{
		char buffer[512];
		PACKET_IZ_NOTIFY_MAKERRANK& packet = *reinterpret_cast<PACKET_IZ_NOTIFY_MAKERRANK*>(buffer);
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_NOTIFY_MAKERRANK(packet);
	}
	break;
	case HEADER_IZ_MAIL_REQ_GET_LIST:
	{
		this->CISvrIOPacketHandler::OnMailReqGetList(packetSize);
	}
	break;
	case HEADER_IZ_MAIL_REQ_OPEN:
	{
		this->CISvrIOPacketHandler::OnMailReqOpen(packetSize);
	}
	break;
	case HEADER_IZ_MAIL_REQ_GET_ITEM:
	{
		this->CISvrIOPacketHandler::OnMailReqGetItem(packetSize);
	}
	break;
	case HEADER_IZ_MAIL_REQ_SEND:
	{
		this->CISvrIOPacketHandler::OnMailReqSend(packetSize);
	}
	break;
	case HEADER_IZ_MAIL_RECEIVE:
	{
		this->CISvrIOPacketHandler::OnMailReceive(packetSize);
	}
	break;
	case HEADER_IZ_ACK_MAIL_DELETE:
	{
		this->CISvrIOPacketHandler::OnMailAckMailDelete(packetSize);
	}
	break;
	case HEADER_IZ_ACK_MAIL_RETURN:
	{
		this->CISvrIOPacketHandler::OnMailAckMailReturn(packetSize);
	}
	break;
	case HEADER_IZ_ACK_LOGON:
	{
		this->CISvrIOPacketHandler::OnAckLogon(packetSize);
	}
	break;
	case HEADER_IZ_CHK_PROCESSTIME:
	{
		this->CISvrIOPacketHandler::OnChkProcessTime(packetSize);
	}
	break;
	case HEADER_IZ_REQ_GROUPINFO_CHANGE_V2:
	{
		this->CISvrIOPacketHandler::OnReqGroupInfoChangeV2(packetSize);
	}
	break;
	case HEADER_IZ_CHANGE_GROUP_MASTER:
	{
		this->CISvrIOPacketHandler::OnChangeGroupMaster(packetSize);
	}
	break;
	case HEADER_IZ_SEEK_PARTY:
	{
		this->CISvrIOPacketHandler::OnSeekParty(packetSize);
	}
	break;
	case HEADER_ZI_SEEK_PARTY_MEMBER:
	{
		this->CISvrIOPacketHandler::OnSeekPartyMember(packetSize);
	}
	break;
	case HEADER_IZ_GPK_DYNCODE_RELOAD:
	{
		PACKET_IZ_GPK_DYNCODE_RELOAD packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_GPK_DYNCODE_RELOAD(packet);
	}
	break;
	case HEADER_IZ_SET_EFFECT_HIGH_RANKER:
	{
		PACKET_IZ_SET_EFFECT_HIGH_RANKER packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_SET_EFFECT_HIGH_RANKER(packet);
	}
	break;
	case HEADER_IZ_RESET_EFFECT_HIGH_RANKER:
	{
		PACKET_IZ_RESET_EFFECT_HIGH_RANKER packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CISvrIOPacketHandler::OnIZ_RESET_EFFECT_HIGH_RANKER(packet);
	}
	break;
	default:
	{
		m_recvQueue->CPacketQueue::Reset();
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Not Header ISvrIO Header:%d, packetSize:%d", Header, packetSize);
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "m_OldHeader:%d m_OldPacketSize:%d", m_OldHeader, m_OldPacketSize);
		return 0;
	}
	break;
	};

	return -1;
}


void CISvrIOPacketHandler::OnINSTNATMAP_DESTROY(const PACKET_IZ_INSTNATMAP_DESTROY& in_packet)
{
	char mapName[16];
	memcpy_s(mapName, sizeof(mapName), in_packet.mapName, sizeof(in_packet.mapName));
	mapName[countof(mapName)-1] = '\0';

	CInstantMapMgr::GetObj()->CInstantMapMgr::RequestDestory(in_packet.mapID, mapName);
}


void CISvrIOPacketHandler::OnINSTANTMAP_CREATE_REQ(const PACKET_IZ_INSTANTMAP_CREATE_REQ& in_packet)
{
	char mapName[16];
	memcpy_s(mapName, sizeof(mapName), in_packet.mapName, sizeof(in_packet.mapName));
	mapName[countof(mapName)-1] = '\0';

	if( !CInstantMapMgr::GetObj()->CInstantMapMgr::RequestCreate(in_packet.hRequestN2Obj, in_packet.mapID, mapName, in_packet.mapType) )
	{
		InstantMap::SendPacket_ZI_INSTANTMAP_CREATE_RES(in_packet.hRequestN2Obj, in_packet.mapName, in_packet.mapID, false); //FIXME: passing unsanitized mapname
		return;
	}
}


void CISvrIOPacketHandler::OnINSTANTMAP_PLAYER_ENTER(const PACKET_IZ_INSTANTMAP_PLAYER_ENTER& in_packet)
{
}


void CISvrIOPacketHandler::OnXX_DISCONNECT(const PACKET_XX_DISCONNECT& in_packet)
{
	BOOL bAcceptable = ( C2CharacterServerClient::GetObj()->C2CharacterServerClient::isAuth() && C2InterServerClient::GetObj()->C2InterServerClient::isAuth() );

	g_zsAcceptHandler.CZSAcceptHandler::SetAccpetable(bAcceptable);
	CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::DisconnectISVR();
	CInstantMapMgr::GetObj()->CInstantMapMgr::DisconnectISVR();

	PACKET_ZC_ISVR_DISCONNECT packet;
	packet.PacketType = HEADER_ZC_ISVR_DISCONNECT;
	CCharacterMgr::GetObj()->CCharacterMgr::BroadCast(sizeof(packet), (char*)&packet);
}


void CISvrIOPacketHandler::OnXX_CONNECT(const PACKET_XX_CONNECT& in_packet)
{
	BOOL bAcceptable = ( C2CharacterServerClient::GetObj()->C2CharacterServerClient::isAuth() && C2InterServerClient::GetObj()->C2InterServerClient::isAuth() );
	g_zsAcceptHandler.CZSAcceptHandler::SetAccpetable(bAcceptable); 

	PACKET_ZI_AUTH_REQ packet;
	packet.PacketType = HEADER_ZI_AUTH_REQ;
	packet.dwIP = g_serverInfo.CServerInfo::GetLocalIP();
	packet.sPort = g_serverInfo.CServerInfo::GetLocalPort();
	packet.ZSID = g_serverInfo.CServerInfo::GetLocalServerID();
	C2InterServerClient::GetObj()->C2InterServerClient::Send(sizeof(packet), (char*)&packet);

	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("inter server auth... try(send)");

	PACKET_ZI_VERSION InterVersion;
	InterVersion.PacketType = HEADER_ZI_VERSION;
	InterVersion.Version = 4;
	C2InterServerClient::GetObj()->C2InterServerClient::Send(sizeof(InterVersion), (char*)&InterVersion);

	PACKET_ZI_EPISODE_VERSION EpisodeVersion;
	EpisodeVersion.PacketType = HEADER_ZI_EPISODE_VERSION;
	EpisodeVersion.Episode_Ver = 14;
	EpisodeVersion.Minor_Ver = 2;
	C2InterServerClient::GetObj()->C2InterServerClient::Send(sizeof(EpisodeVersion), (char*)&EpisodeVersion);

	if( CInstantMapConfiguration::GetObj()->CInstantMapConfiguration::IsAllow() == true )
		InstantMap::Send_PACKET_ZI_INSTANTMAP_ALLOW(true, PACKET_ZI_INSTANTMAP_ALLOW::WHY_ZSVR_SETTING);
}


void CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_MSG(const PACKET_IZ_MEMORIALDUNGEON_MSG& in_packet)
{
	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(in_packet.AID, PC_TYPE);
	if( pc == NULL || in_packet.GID != pc->CPC::GetCharacterID() )
		return;

	if( in_packet.Notify == PACKET_IZ_MEMORIALDUNGEON_MSG::MEMORIALDUNGEON_SUBSCRIPTION_ERROR_CLOSE )
	{
		PACKET_ZC_MSG packet;
		packet.PacketType = HEADER_ZC_MSG;
		packet.msg = MSI_MEMORIAL_DUN_CLOSE;
		pc->Send(sizeof(packet), (char*)&packet);
	}
	else
	{
		char MemorialDungeonName[60+1] = {};
		memcpy_s(MemorialDungeonName, sizeof(MemorialDungeonName), in_packet.MemorialDungeonName, sizeof(in_packet.MemorialDungeonName)-1);
		size_t MemorialDungeonNameLen = strlen(MemorialDungeonName) + 1;

		char buffer[1024] = {};
		PACKET_ZC_FORMATSTRING_MSG& packet = *reinterpret_cast<PACKET_ZC_FORMATSTRING_MSG*>(buffer);
		packet.PacketType = HEADER_ZC_FORMATSTRING_MSG;
		memcpy_s(packet.Text, sizeof(buffer) - sizeof(PACKET_ZC_FORMATSTRING_MSG), MemorialDungeonName, MemorialDungeonNameLen);
		packet.PacketLength = sizeof(PACKET_ZC_FORMATSTRING_MSG) + MemorialDungeonNameLen;

		switch( in_packet.Notify )
		{
		case PACKET_IZ_MEMORIALDUNGEON_MSG::MEMORIALDUNGEON_SUBSCRIPTION_ERROR_UNKNOWN  : packet.msg = MSI_MDUNGEON_SUBSCRIPTION_ERROR_UNKNOWN;   break;
		case PACKET_IZ_MEMORIALDUNGEON_MSG::MEMORIALDUNGEON_SUBSCRIPTION_ERROR_DUPLICATE: packet.msg = MSI_MDUNGEON_SUBSCRIPTION_ERROR_DUPLICATE; break;
		case PACKET_IZ_MEMORIALDUNGEON_MSG::MEMORIALDUNGEON_SUBSCRIPTION_ERROR_RIGHT    : packet.msg = MSI_MDUNGEON_SUBSCRIPTION_ERROR_RIGHT;     break;
		case PACKET_IZ_MEMORIALDUNGEON_MSG::MEMORIALDUNGEON_SUBSCRIPTION_ERROR_EXIST    : packet.msg = MSI_MDUNGEON_SUBSCRIPTION_ERROR_EXIST;     break;
		case PACKET_IZ_MEMORIALDUNGEON_MSG::MEMORIALDUNGEON_SUBSCRIPTION_CANCEL_FAIL    : packet.msg = MSI_MDUNGEON_SUBSCRIPTION_CANCEL_FAIL;     break;
		case PACKET_IZ_MEMORIALDUNGEON_MSG::MEMORIALDUNGEON_SUBSCRIPTION_CANCEL_SUCCESS : packet.msg = MSI_MDUNGEON_SUBSCRIPTION_CANCEL_SUCCESS;  break;
		case PACKET_IZ_MEMORIALDUNGEON_MSG::MEMORIALDUNGEON_CREATE_FAIL                 : packet.msg = MSI_MDUNGEON_CREATE_FAIL;                  break;
		default:
			return;
		};

		pc->Send(packet.PacketLength, (char*)&packet);
	}
}


void CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_MSG2(const int in_nPacketSize)
{
	char buf[1024] = {};
	if( m_recvQueue->CPacketQueue::GetData(in_nPacketSize, buf) == -1 )
		return;

	PACKET_IZ_MEMORIALDUNGEON_MSG2& in_packet = *reinterpret_cast<PACKET_IZ_MEMORIALDUNGEON_MSG2*>(buf);
	size_t MemorialDungeonNameLen = in_packet.PacketLength - sizeof(PACKET_IZ_MEMORIALDUNGEON_MSG2) + 1;
	in_packet.MemorialDungeonName[MemorialDungeonNameLen] = '\0';

	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(in_packet.AID, PC_TYPE);
	if( pc == NULL )
		return;

	if( in_packet.GID != pc->CPC::GetCharacterID() )
		return;

	if( in_packet.Notify == PACKET_IZ_MEMORIALDUNGEON_MSG2::MEMORIALDUNGEON_SUBSCRIPTION_ERROR_CLOSE )
	{
		PACKET_ZC_MSG packet;
		packet.PacketType = HEADER_ZC_MSG;
		packet.msg = MSI_MEMORIAL_DUN_CLOSE;
		pc->Send(sizeof(packet), (char*)&packet);
	}
	else
	{
		char buffer[1024] = {};
		PACKET_ZC_FORMATSTRING_MSG& packet = *reinterpret_cast<PACKET_ZC_FORMATSTRING_MSG*>(buffer);
		packet.PacketType = HEADER_ZC_FORMATSTRING_MSG;
		memcpy_s(packet.Text, MemorialDungeonNameLen, in_packet.MemorialDungeonName, MemorialDungeonNameLen);
		packet.PacketLength = sizeof(PACKET_ZC_FORMATSTRING_MSG) + MemorialDungeonNameLen;

		switch( in_packet.Notify )
		{
		case PACKET_IZ_MEMORIALDUNGEON_MSG2::MEMORIALDUNGEON_SUBSCRIPTION_ERROR_UNKNOWN  : packet.msg = MSI_MDUNGEON_SUBSCRIPTION_ERROR_UNKNOWN;   break;
		case PACKET_IZ_MEMORIALDUNGEON_MSG2::MEMORIALDUNGEON_SUBSCRIPTION_ERROR_DUPLICATE: packet.msg = MSI_MDUNGEON_SUBSCRIPTION_ERROR_DUPLICATE; break;
		case PACKET_IZ_MEMORIALDUNGEON_MSG2::MEMORIALDUNGEON_SUBSCRIPTION_ERROR_RIGHT    : packet.msg = MSI_MDUNGEON_SUBSCRIPTION_ERROR_RIGHT;     break;
		case PACKET_IZ_MEMORIALDUNGEON_MSG2::MEMORIALDUNGEON_SUBSCRIPTION_ERROR_EXIST    : packet.msg = MSI_MDUNGEON_SUBSCRIPTION_ERROR_EXIST;     break;
		case PACKET_IZ_MEMORIALDUNGEON_MSG2::MEMORIALDUNGEON_SUBSCRIPTION_CANCEL_FAIL    : packet.msg = MSI_MDUNGEON_SUBSCRIPTION_CANCEL_FAIL;     break;
		case PACKET_IZ_MEMORIALDUNGEON_MSG2::MEMORIALDUNGEON_SUBSCRIPTION_CANCEL_SUCCESS : packet.msg = MSI_MDUNGEON_SUBSCRIPTION_CANCEL_SUCCESS;  break;
		case PACKET_IZ_MEMORIALDUNGEON_MSG2::MEMORIALDUNGEON_CREATE_FAIL                 : packet.msg = MSI_MDUNGEON_CREATE_FAIL;                  break;
		default:
			return;
		};

		pc->Send(packet.PacketLength, (char*)buffer);
	}
}


void Send_PACKET_ZI_PARTY_JOIN_REQ_ACK(unsigned long in_TargetAID, unsigned long in_GRID, PACKET_ZC_PARTY_JOIN_REQ_ACK::enumAnswer in_answer)
{
	PACKET_ZI_PARTY_JOIN_REQ_ACK packet;
	packet.PacketType = HEADER_ZI_PARTY_JOIN_REQ_ACK;
	packet.targetAID = in_TargetAID;
	packet.GRID = in_GRID;
	packet.answer = in_answer;
	C2InterServerClient::GetObj()->C2InterServerClient::Send(sizeof(packet), (char*)&packet);
}


void CISvrIOPacketHandler::OnIZ_PARTY_JOIN_REQ(const PACKET_IZ_PARTY_JOIN_REQ& in_packet)
{
	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(in_packet.targetAID, PC_TYPE);
	if( pc == NULL )
	{
		Send_PACKET_ZI_PARTY_JOIN_REQ_ACK(in_packet.targetAID, in_packet.GRID, PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_UNKNOWN_CHARACTER);
		return;
	}

	if( pc->m_characterInfo.Party.Bit.bRefuseJoinMsg )
	{
		Send_PACKET_ZI_PARTY_JOIN_REQ_ACK(in_packet.targetAID, in_packet.GRID, PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_JOINMSG_REFUSE);
		return;
	}

	if( pc->IsItPossible(MAPPROPERTY_NO_PARTY_FORMATION) == TRUE )
	{
		Send_PACKET_ZI_PARTY_JOIN_REQ_ACK(in_packet.targetAID, in_packet.GRID, PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_INVALID_MAPPROPERTY);
		return;
	}

	PACKET_ZC_PARTY_JOIN_REQ packet = {};
	packet.PacketType = HEADER_ZC_PARTY_JOIN_REQ;
	packet.GRID = in_packet.GRID;
	memcpy_s(packet.groupName, sizeof(packet.groupName), in_packet.groupName, sizeof(in_packet.groupName));
	pc->Send(sizeof(packet), (char*)&packet);
}


void CISvrIOPacketHandler::OnIZ_PARTY_JOIN_REQ_ACK(const PACKET_IZ_PARTY_JOIN_REQ_ACK& in_packet)
{
	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(in_packet.requestAID, PC_TYPE);
	if( pc == NULL )
		return;

	Sned_PACKET_ZC_PARTY_JOIN_REQ_ACK(pc, in_packet.characterName, in_packet.answer);
}


void CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO(const PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO& in_packet)
{
	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(in_packet.AID, PC_TYPE);
	if( pc == NULL )
		return;

	if( in_packet.GID != pc->CPC::GetCharacterID() )
		return;

	PACKET_ZC_MEMORIALDUNGEON_SUBSCRIPTION_INFO packet = {};
	packet.PacketType = HEADER_ZC_MEMORIALDUNGEON_SUBSCRIPTION_INFO;
	memcpy_s(packet.MemorialDungeonName, sizeof(packet.MemorialDungeonName), in_packet.MemorialDungeonName, sizeof(in_packet.MemorialDungeonName));
	packet.PriorityOrderNum = in_packet.PriorityOrderNum;
	pc->CPC::ForceSend(sizeof(packet), (char*)&packet);
}


void CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO2(const int in_nPacketSize)
{
	char buf[1024] = {};
	if( m_recvQueue->CPacketQueue::GetData(in_nPacketSize, buf) == -1 )
		return;

	PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO2& in_packet = *reinterpret_cast<PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO2*>(buf);
	size_t MemorialDungeonNameLen = in_packet.PacketLength - sizeof(PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO2);
	in_packet.MemorialDungeonName[MemorialDungeonNameLen] = '\0';

	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(in_packet.AID, PC_TYPE);
	if( pc == NULL )
		return;

	if( in_packet.GID != pc->CPC::GetCharacterID() )
		return;

	PACKET_ZC_MEMORIALDUNGEON_SUBSCRIPTION_INFO packet = {};
	packet.PacketType = HEADER_ZC_MEMORIALDUNGEON_SUBSCRIPTION_INFO;
	if( MemorialDungeonNameLen >= sizeof(packet.MemorialDungeonName) )
		MemorialDungeonNameLen = sizeof(packet.MemorialDungeonName);
	memcpy_s(packet.MemorialDungeonName, sizeof(packet.MemorialDungeonName), in_packet.MemorialDungeonName, MemorialDungeonNameLen);
	packet.PriorityOrderNum = in_packet.PriorityOrderNum;
	pc->CPC::ForceSend(sizeof(packet), (char*)&packet);
}


void CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY(const PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY& in_packet)
{
	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(in_packet.AID, PC_TYPE);
	if( pc == NULL )
		return;

	if( in_packet.GID != pc->CPC::GetCharacterID() )
		return;

	PACKET_ZC_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY packet = {};
	packet.PacketType = HEADER_ZC_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY;
	packet.PriorityOrderNum = in_packet.PriorityOrderNum;
	pc->CPC::ForceSend(sizeof(packet), (char*)&packet);
}


void CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_INFO(const PACKET_IZ_MEMORIALDUNGEON_INFO& in_packet)
{
	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(in_packet.AID, PC_TYPE);
	if( pc == NULL )
		return;

	if( in_packet.GID != pc->CPC::GetCharacterID() )
		return;

	PACKET_ZC_MEMORIALDUNGEON_INFO packet = {};
	packet.PacketType = HEADER_ZC_MEMORIALDUNGEON_INFO;
	memcpy_s(packet.MemorialDungeonName, sizeof(packet.MemorialDungeonName), in_packet.MemorialDungeonName, sizeof(in_packet.MemorialDungeonName));
	packet.DestroyDate = in_packet.DestroyDate;
	packet.EnterTimeOutDate = in_packet.EnterTimeOutDate;
	pc->CPC::ForceSend(sizeof(packet), (char*)&packet);
}


void CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_INFO2(const int in_nPacketSize)
{
	char buf[1024] = {};
	if( m_recvQueue->CPacketQueue::GetData(in_nPacketSize, buf) == -1 )
		return;

	PACKET_IZ_MEMORIALDUNGEON_INFO2& in_packet = *reinterpret_cast<PACKET_IZ_MEMORIALDUNGEON_INFO2*>(buf);
	size_t MemorialDungeonNameLen = in_packet.PacketLength - sizeof(PACKET_IZ_MEMORIALDUNGEON_INFO2);
	buf[in_packet.PacketLength] = '\0';

	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(*(unsigned int *)&buf[8], PC_TYPE);
	if( pc == NULL )
		return;

	if( in_packet.GID != pc->CPC::GetCharacterID() )
		return;

	PACKET_ZC_MEMORIALDUNGEON_INFO packet = {};
	packet.PacketType = HEADER_ZC_MEMORIALDUNGEON_INFO;
	if( MemorialDungeonNameLen >= sizeof(packet.MemorialDungeonName) )
		MemorialDungeonNameLen = sizeof(packet.MemorialDungeonName);
	memcpy_s(packet.MemorialDungeonName, sizeof(packet.MemorialDungeonName), in_packet.MemorialDungeonName, MemorialDungeonNameLen);
	packet.DestroyDate = in_packet.DestroyDate;
	packet.EnterTimeOutDate = in_packet.EnterTimeOutDate;
	pc->CPC::ForceSend(sizeof(packet), (char*)&packet);
}


void CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_NOTIFY(const PACKET_IZ_MEMORIALDUNGEON_NOTIFY& in_packet)
{
	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(in_packet.AID, PC_TYPE);
	if( pc == NULL )
		return;

	if( in_packet.GID != pc->CPC::GetCharacterID() )
		return;

	PACKET_ZC_MEMORIALDUNGEON_NOTIFY packet = {};
	packet.PacketType = HEADER_ZC_MEMORIALDUNGEON_NOTIFY;
	packet.Type = in_packet.Type;
	packet.EnterLimitDate = in_packet.EnterLimitDate;
	pc->CPC::ForceSend(sizeof(packet), (char*)&packet);
}


void CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_SYNC(const PACKET_IZ_MEMORIALDUNGEON_SYNC& in_packet)
{
	if( in_packet.Event == PACKET_IZ_MEMORIALDUNGEON_SYNC::EVENT_CREATE )
	{
		CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::Add(in_packet.ExistZSID, in_packet.MemorialDungeonName, in_packet.hPartyID, in_packet.partyName, in_packet.hMemorialDungeonID, in_packet.Factor);
	}
	else
	if( in_packet.Event == PACKET_IZ_MEMORIALDUNGEON_SYNC::EVENT_DESTROY )
	{
		CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::Remove(in_packet.hPartyID);
	}
	else
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "unknown event found");
		return;
	}
}


void CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_VISA(const PACKET_IZ_MEMORIALDUNGEON_VISA& in_packet)
{
	MS_MAPMOVE par1 = {};
	par1.MS_MAPMOVE::Set(in_packet.mapName, in_packet.x, in_packet.y, in_packet.AID);

	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, in_packet.AID, CM_MAPMOVE, (int)&par1, VT_OUTOFSIGHT, 0, 0);
}


void CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_OPENSTATE(const PACKET_IZ_MEMORIALDUNGEON_OPENSTATE& in_packet)
{
	CMemorialDungeonMgr::enumOpenState OpenState = ( in_packet.bOpen == true) ? CMemorialDungeonMgr::OPENSTATE_OPEN : CMemorialDungeonMgr::OPENSTATE_CLOSE;
	CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::SetOpenState(OpenState);

	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(in_packet.ToAID, PC_TYPE);
	if( pc == NULL )
		return;

	if( in_packet.ToGID != pc->CPC::GetCharacterID() )
		return;

	PACKET_ZC_MSG packet;
	packet.PacketType = HEADER_ZC_MSG;
	if( in_packet.bOpen == false )
		packet.msg = MSI_MEMORIAL_DUN_CLOSE;
	else
		packet.msg = MSI_MEMORIAL_DUN_OPEN;
	pc->Send(sizeof(packet), (char*)&packet);
}


void CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_COMMAND(const PACKET_IZ_MEMORIALDUNGEON_COMMAND& in_packet)
{
	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(in_packet.AID, PC_TYPE);
	if( pc == NULL )
		return;

	if( in_packet.GID != pc->CPC::GetCharacterID() )
		return;

	switch( in_packet.Command )
	{
	case PACKET_IZ_MEMORIALDUNGEON_COMMAND::COMMAND_PLAYER_KICK:
		pc->CPC::ForceMapMove_To_RestartMap();
	break;
	};
}


void CISvrIOPacketHandler::OnIZ_LEAVE_GROUP(const PACKET_IZ_LEAVE_GROUP& in_packet)
{
	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(in_packet.AID, PC_TYPE);
	if( pc == NULL )
		return;

	if( in_packet.GID != pc->CPC::GetCharacterID() )
		return;

	memset(pc->m_characterInfo.partyID, '\0', sizeof(pc->m_characterInfo.partyID));
	pc->CPC::ResetGroupMember();
}


void CISvrIOPacketHandler::OnIZ_BROADCASTING_SPECIAL_ITEM_OBTAIN(const std::vector<BYTE>& in_packet)
{
	PACKET_IZ_BROADCASTING_SPECIAL_ITEM_OBTAIN& packet = *reinterpret_cast<PACKET_IZ_BROADCASTING_SPECIAL_ITEM_OBTAIN*>(const_cast<BYTE*>(&in_packet.front()));
	packet.PacketType = HEADER_ZC_BROADCASTING_SPECIAL_ITEM_OBTAIN;
	CCharacterMgr::GetObj()->CCharacterMgr::BroadCast(packet.PacketLength, (char*)&packet);
}


void CISvrIOPacketHandler::OnIZ_AUTH_ACK(const PACKET_IZ_AUTH_ACK& in_packet)
{
	C2InterServerClient::GetObj()->C2InterServerClient::SetAuth(true);
	g_zsAcceptHandler.CZSAcceptHandler::SetAccpetable(( C2CharacterServerClient::GetObj()->C2CharacterServerClient::isAuth() != false ));

	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("inter server auth... ok(i:%d,h:%d)", C2InterServerClient::GetObj()->C2InterServerClient::isAuth(), C2InterServerClient::GetObj()->C2InterServerClient::isAuth()); //FIXME: copy-paste mistake
	InvalidateRect(g_hWnd, NULL, FALSE);
}


void CISvrIOPacketHandler::OnWhisper(int len)
{
	PACKET_IZ_WHISPER packet;
	char buf[256];
	m_recvQueue->CPacketQueue::GetData(sizeof(PACKET_IZ_WHISPER), (char*)&packet);
	m_recvQueue->CPacketQueue::GetData(len - sizeof(PACKET_IZ_WHISPER), (char*)buf);

	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, packet.receiverAID, CM_WHISPER, (int)&packet, len - sizeof(PACKET_IZ_WHISPER), (int)buf, 0);
}


void CISvrIOPacketHandler::OnWhisper_2(int len)
{
	PACKET_IZ_WHISPER_2 packet;
	char buf[256];
	m_recvQueue->CPacketQueue::GetData(sizeof(PACKET_IZ_WHISPER_2), (char*)&packet);
	m_recvQueue->CPacketQueue::GetData(len - sizeof(PACKET_IZ_WHISPER_2), buf);

	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, packet.receiverAID, CM_WHISPER_SSO, (int)&packet, len - sizeof(PACKET_IZ_WHISPER_2), (int)buf, 0);
}


void CISvrIOPacketHandler::OnWhisperAck(int len)
{
	PACKET_IZ_ACK_WHISPER packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, packet.senderAID, CM_WHISPER_ACK, packet.result, 0, 0, 0);
}


void CISvrIOPacketHandler::OnUserCount(int len)
{
	PACKET_IZ_USER_COUNT packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, packet.AID, CM_USER_COUNT, packet.count, 0, 0, 0);
}


void CISvrIOPacketHandler::OnIZ_BROADCAST(const PACKET_IZ_BROADCAST* in_pPacket)
{
	int TextSize = in_pPacket->PacketLen - sizeof(PACKET_IZ_BROADCAST);
	if( TextSize < 1 || TextSize > 512 )
	{
		this->OnClose();
		return;
	}

	std::vector<char> buffer(sizeof(PACKET_ZC_BROADCAST));
	buffer.insert(buffer.end(), in_pPacket->Text, in_pPacket->Text + TextSize);
	PACKET_ZC_BROADCAST* packet = reinterpret_cast<PACKET_ZC_BROADCAST*>(&buffer.front());
	packet->Text[TextSize-1] = '\0';
	packet->PacketType = HEADER_ZC_BROADCAST;
	packet->PacketLength = buffer.size();
	CCharacterMgr::GetObj()->CCharacterMgr::BroadCast(packet->PacketLength, (char*)packet);
}


void CISvrIOPacketHandler::OnAddMemberToGroup(int len)
{
	PACKET_IZ_ADD_MEMBER_TO_GROUP2 packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(m_recvQueue), (char*)&packet);

	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, packet.receiverAID, CM_ADD_MEMBER_TO_GROUP, sizeof(packet), (int)&packet, 0, 0);
}


void CISvrIOPacketHandler::OnDeleteMemberFromGroup(int len)
{
	PACKET_IZ_DELETE_MEMBER_FROM_GROUP packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, packet.receiverAID, CM_DELETE_MEMBER_FROM_GROUP, sizeof(packet), (int)&packet, 0, 0);
}


void CISvrIOPacketHandler::OnAckMakeGroup(int len)
{
	PACKET_IZ_ACK_MAKE_GROUP packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, packet.AID, CM_ACK_MAKE_GROUP, sizeof(packet), (int)&packet, 0, 0);
}


void CISvrIOPacketHandler::OnGroupList(int len)
{
	PACKET_IZ_GROUP_LIST packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	if( packet.PacketLength > 2048 )
		packet.PacketLength = 2048;

	char buf[2048];
	char DataSize = packet.PacketLength - sizeof(PACKET_IZ_GROUP_LIST);
	m_recvQueue->CPacketQueue::GetData(DataSize, buf);

	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, packet.AID, CM_GROUP_LIST, DataSize, (int)buf, (int)packet.groupName, 0);
}


void CISvrIOPacketHandler::OnAckReqJoinGroup(int len)
{
	PACKET_IZ_ACK_REQ_JOIN_GROUP packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, packet.AID, CM_ACK_REQ_JOIN_GROUP, sizeof(packet), (int)&packet, 0, 0);
}


void CISvrIOPacketHandler::OnReqJoinGroup(int len)
{
	PACKET_IZ_REQ_JOIN_GROUP packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, packet.AID, CM_REQ_JOIN_GROUP, sizeof(packet), (int)&packet, 0, 0);
}


void CISvrIOPacketHandler::OnGRIDUpdate(int len)
{
	PACKET_ZI_GRID_UPDATE packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, packet.AID, CM_GRID_UPDATE, sizeof(packet), (int)&packet, 0, 0);
}


void CISvrIOPacketHandler::OnChatParty(int len)
{
	PACKET_IZ_CHAT_PARTY packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	char buf[512];
	char TextSize = len - sizeof(PACKET_IZ_CHAT_PARTY);
	m_recvQueue->CPacketQueue::GetData(TextSize, buf);

	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, packet.receiverAID, CM_CHAT_PARTY, packet.senderAID, TextSize, (int)buf, 0);
}


void DisconnectAll()
{
	g_zsAcceptHandler.CZSAcceptHandler::SetAccpetable(FALSE);
	g_IsDisconnectAll = true;

	PACKET_SC_NOTIFY_BAN outpacket;
	outpacket.PacketType = HEADER_SC_NOTIFY_BAN;
	outpacket.ErrorCode = 0; // BAN_UNFAIR
	CCharacterMgr::GetObj()->CCharacterMgr::BroadCastExceptME(sizeof(outpacket), (char*)&outpacket, "gravity");

	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "DisconnectAll()");
	shutdownlog();
}


void CISvrIOPacketHandler::OnDisconnectAll(int len)
{
	PACKET_IZ_DISCONNECT_ALL packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	DisconnectAll();
}


void CISvrIOPacketHandler::OnReqServerState(int len)
{
	PACKET_IZ_REQ_SERVERSTATE packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	PACKET_ZI_SERVERSTATE outpacket;
	outpacket.PacketType = HEADER_ZI_SERVERSTATE;
	outpacket.monitorNum = packet.monitorNum;
	outpacket.state.serverID = g_serverInfo.CServerInfo::GetLocalServerID();
	outpacket.state.packetNumber = packet.packetNumber;
	outpacket.state.userCounter = CCharacterMgr::GetObj()->CCharacterMgr::GetCurValidPlayChar();
	outpacket.state.loopcountPerSec = g_loopCountPerSec;
	C2InterServerClient::GetObj()->C2InterServerClient::Send(sizeof(outpacket), (char*)&outpacket);
}


void CISvrIOPacketHandler::OnResultGuildMake(int len)
{
	PACKET_IZ_RESULT_MAKE_GUILD Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	PACKET_ZC_RESULT_MAKE_GUILD ZCPacket;
	ZCPacket.PacketType = HEADER_ZC_RESULT_MAKE_GUILD;
	ZCPacket.result = Packet.result;
	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, Packet.AID, CM_SEND_PACKET, sizeof(ZCPacket), (int)&ZCPacket, 0, 0);

	if( ZCPacket.result != 0 )
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, Packet.AID, CM_ADD_RESERVED_EMPELIUM_ITEM, 0, 0, 0, 0);
}


void CISvrIOPacketHandler::OnReqJoinGuild(int Len)
{
	PACKET_IZ_REQ_JOIN_GUILD Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	PACKET_ZC_REQ_JOIN_GUILD ZCPacket;
	ZCPacket.PacketType = HEADER_ZC_REQ_JOIN_GUILD;
	ZCPacket.GDID = Packet.GDID;
	memcpy_s(ZCPacket.guildName, sizeof(ZCPacket.guildName), Packet.guildName, sizeof(Packet.guildName));
	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, Packet.AID, CM_SEND_PACKET, sizeof(ZCPacket), (int)&ZCPacket, 0, 0);

	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(Packet.AID, PC_TYPE);
	if( pc == NULL )
		return;

	int GID = 0;
	pc->GetParameterValue(VAR_CHARACTERID, GID);
	g_ZGuildMgr.CZGuildMgr::JoinInsertGID(Packet.GDID, GID);
}


void CISvrIOPacketHandler::OnReqJoinGuild2(const PACKET_IZ_REQ_JOIN_GUILD2& in_packet)
{
}


void CISvrIOPacketHandler::OnAckReqJoinGuild(int Len)
{
	PACKET_IZ_ACK_REQ_JOIN_GUILD Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	PACKET_ZC_ACK_REQ_JOIN_GUILD ZCPacket;
	ZCPacket.PacketType = HEADER_ZC_ACK_REQ_JOIN_GUILD;
	ZCPacket.answer = Packet.answer;

	if( Packet.AID != 0 )
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, Packet.AID, CM_SEND_PACKET, sizeof(ZCPacket), (int)&ZCPacket, 0, 0);

	if( Packet.ReqAID != 0 )
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, Packet.ReqAID, CM_SEND_PACKET, sizeof(ZCPacket), (int)&ZCPacket, 0, 0);

	CZGuildInfo* guildInfo = (CZGuildInfo*)g_ZGuildMgr.CGuildMgr::SearchGuild(Packet.GDID);
	if( guildInfo != NULL )
		guildInfo->CZGuildInfo::SendGuildNotice(Packet.AID);
}


void CISvrIOPacketHandler::OnUpdateCharGDID(int Len)
{
	PACKET_IZ_UPDATE_CHARGDID Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(m_recvQueue), (char*)&Packet);

	if( g_ZGuildMgr.CGuildMgr::SearchGuild(Packet.GDID) == NULL )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CISvrIOPacketHandler :: OnUpdateCharGDID GDID == NULL");
		return;
	}

	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(Packet.AID, PC_TYPE);
	if( pc == NULL )
		return;

	pc->UpdateParameterValue(VAR_GDID, Packet.GDID);

	PACKET_ZC_UPDATE_GDID ZCPacket;
	ZCPacket.PacketType = HEADER_ZC_UPDATE_GDID;
	ZCPacket.GDID = Packet.GDID;
	ZCPacket.emblemVersion = Packet.emblemVer;
	ZCPacket.right = Packet.right;
	ZCPacket.isMaster = Packet.isMaster;
	ZCPacket.InterSID = Packet.InterSID;
	memcpy_s(ZCPacket.GName, sizeof(ZCPacket.GName), Packet.GuildName, sizeof(Packet.GuildName));
	pc->CPC::ForceSend(sizeof(ZCPacket), (char*)&ZCPacket);
}


void CISvrIOPacketHandler::OnGuildInfo(int Len)
{
	PACKET_IZ_GUILDINFO_TOD Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	g_ZGuildMgr.CZGuildMgr::MakeGuild(Packet.GDID, &Packet.Data);
}


void CISvrIOPacketHandler::OnDisconnectCharacter(int len)
{
	PACKET_IZ_DISCONNECT_CHARACTER packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(packet.AID, PC_TYPE);
	if( pc == NULL )
		return;

	PACKET_SC_NOTIFY_BAN outpacket = {};
	outpacket.PacketType = HEADER_SC_NOTIFY_BAN;
	outpacket.ErrorCode = 0; // BAN_UNFAIR
	pc->Send(sizeof(outpacket), (char*)&outpacket);

	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Disconnect Character for double login from inter: AID:%d", packet.AID);
	pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
}


void CISvrIOPacketHandler::OnAckGuildZeny(int Len)
{
	PACKET_IZ_GUILD_ZENY packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	if( packet.AID == 0 )
	{
		CMapRes* mapRes = g_mapResMgr.CMapResMgr::GetMapRes(packet.mapName);
		if( mapRes == NULL || mapRes->CMapRes::GetType() != MAPTYPE_AGIT )
		{
			Trace("OnAckGuildZeny - no such agit:%s\n", packet.mapName);
			return;
		}

		static_cast<CAgitMapRes*>(mapRes)->CAgitMapRes::OnRcvAckFromInter(packet.ret);
		return;
	}

	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(packet.AID, PC_TYPE);
	if( pc != NULL && pc->CPC::GetCharacterID() == packet.GID && pc->CPC::IsReadyToSave() )
	{
		PACKET_ZC_GUILD_ZENY_ACK out;
		out.PacketType = HEADER_ZC_GUILD_ZENY_ACK;
		out.ret = packet.ret;

		if( packet.ret == ZENY_UPDATE_SUCCESS && !pc->CPC::ModifyMoney(-packet.zeny) )
			out.ret = ZENY_UPDATE_FAIL_PLAYER;

		pc->CPC::Send(sizeof(out), (char*)&out);

		if( out.ret != ZENY_UPDATE_FAIL_PLAYER )
			return;
	}
	else
	{
		if( packet.ret != ZENY_UPDATE_SUCCESS )
			return;
	}

	PACKET_ZI_GUILD_ZENY out;
	out.PacketType = HEADER_ZI_GUILD_ZENY;
	memset(out.mapName, '\0', sizeof(out.mapName));
	out.GDID = packet.GDID;
	out.AID = -1;
	out.GID = 0;
	out.type = 2; //TODO
	out.zeny = packet.zeny;
	CCharacterMgr::GetObj()->CCharacterMgr::SendToIServer(sizeof(out), (const char*)&out);
}


void CISvrIOPacketHandler::OnSpecialMove(int len)
{
	PACKET_IZ_MOVE Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	int MoveType = Packet.MoveType;
	if( Packet.MoveType == SUMMONAID || Packet.MoveType == SUMMONGID || Packet.MoveType == SUMMONMARRY )
	{
		CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(Packet.DestID, PC_TYPE);
		if( pc == NULL )
			return;

		if( MoveType != SUMMONMARRY || pc->GetState() != CHARACTER_STATE_DEAD )
		{
			MS_MAPMOVE outpar;
			memcpy_s(outpar.mapName, sizeof(outpar.mapName), Packet.MapName, sizeof(Packet.MapName));
			CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(pc, pc, CM_MAPMOVE, (int)&outpar, VT_TELEPORT, 0, 0);
		}
	}
	else
	{
		CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(Packet.DestID, PC_TYPE);
		if( pc == NULL )
			return;

		PACKET_ZI_MOVE ZIPacket;
		ZIPacket.PacketType = HEADER_ZI_MOVE;
		ZIPacket.MoveType = SUMMONGID;
		ZIPacket.SrcID = pc->GetAccountID();
		pc->GetParameterValue(VAR_CURXPOS, ZIPacket.DestX);
		pc->GetParameterValue(VAR_CURYPOS, ZIPacket.DestY);
		memcpy_s(ZIPacket.DestName, sizeof(ZIPacket.DestName), Packet.CharName, sizeof(Packet.CharName));
		CCharacterMgr::GetObj()->CCharacterMgr::SendToIServer(sizeof(ZIPacket), (char*)&ZIPacket);
	}
}


void CISvrIOPacketHandler::OnChangeOwnerAgit(int len)
{
	PACKET_IZ_GUILD_CHANGEOWNER_AGIT packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	CAgitMapRes::OnNotifyFromInter(packet.mapName, packet.newGDID);
}


void CISvrIOPacketHandler::OnDivorce(int len)
{
	PACKET_IZ_DIVORCE Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(Packet.name);
	if( pc == NULL )
		return;

	if( !pc->m_marriageInfo.bMarried )
		return;

	pc->CPC::DeleteMarriagering();
	pc->CPC::NotifyDivorce(pc->m_marriageInfo.partnerGID, pc->m_marriageInfo.partnerName);
}


void CISvrIOPacketHandler::OnFriendsList(int Len)
{
	PACKET_IZ_FRIENDS_LIST Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	char Data[4096];
	int DataLen = Packet.PacketLength - sizeof(PACKET_IZ_FRIENDS_LIST);
	m_recvQueue->CPacketQueue::GetData(DataLen, Data);

	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(Packet.AID, PC_TYPE);
	if( pc == NULL )
		return;

	PACKET_ZC_FRIENDS_LIST SendPacket;
	SendPacket.PacketType = HEADER_ZC_FRIENDS_LIST;
	SendPacket.PacketLength = sizeof(PACKET_ZC_FRIENDS_LIST) + DataLen;
	pc->CPC::ForceSend(sizeof(PACKET_ZC_FRIENDS_LIST), (char*)&SendPacket);
	pc->CPC::ForceSend(DataLen, Data);
}


void CISvrIOPacketHandler::OnFriendsState(int Len)
{
	PACKET_IZ_FRIENDS_STATE Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(Packet.AID, PC_TYPE);
	if( pc == NULL )
		return;

	PACKET_ZC_FRIENDS_STATE SendPacket;
	SendPacket.PacketType = HEADER_ZC_FRIENDS_STATE;
	SendPacket.AID = Packet.FriendAID;
	SendPacket.GID = Packet.FriendGID;
	SendPacket.State = Packet.State;
	pc->CPC::ForceSend(sizeof(SendPacket), (char*)&SendPacket);
}


void CISvrIOPacketHandler::OnAddFriend(int Len)
{
	PACKET_IZ_ADD_FRIENDS Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(Packet.AID, PC_TYPE);
	if( pc == NULL )
		return;

	PACKET_ZC_ADD_FRIENDS_LIST SendPacket;
	SendPacket.PacketType = HEADER_ZC_ADD_FRIENDS_LIST;
	SendPacket.Result = Packet.Result;
	SendPacket.AID = Packet.FriendAID;
	SendPacket.GID = Packet.FriendGID;
	memcpy_s(SendPacket.Name, sizeof(SendPacket.Name), Packet.Name, sizeof(Packet.Name));
	pc->Send(sizeof(SendPacket), (char*)&SendPacket);
}


void CISvrIOPacketHandler::OnDeleteFriends(int Len)
{
	PACKET_IZ_DELETE_FRIENDS Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(Packet.AID, PC_TYPE);
	if( pc == NULL )
		return;

	PACKET_ZC_DELETE_FRIENDS SendPacket;
	SendPacket.PacketType = HEADER_ZC_DELETE_FRIENDS;
	SendPacket.AID = Packet.FriendAID;
	SendPacket.GID = Packet.FriendGID;
	pc->Send(sizeof(SendPacket), (char*)&SendPacket);
}


void CISvrIOPacketHandler::OnMailReqGetList(int Len)
{
	PACKET_IZ_MAIL_REQ_GET_LIST Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	int DataLen = Packet.PacketLength - sizeof(PACKET_IZ_MAIL_REQ_GET_LIST);
	if( DataLen >= 8000 )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "OnMailReqGetList %d", DataLen);
		m_recvQueue->CPacketQueue::RemoveData(DataLen);
		return;
	}

	char Data[8000];
	m_recvQueue->CPacketQueue::GetData(DataLen, Data);

	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(Packet.AID, PC_TYPE);
	if( pc == NULL )
		return;

	PACKET_ZC_MAIL_REQ_GET_LIST SendPacket;
	SendPacket.PacketType = HEADER_ZC_MAIL_REQ_GET_LIST;
	SendPacket.PacketLength = sizeof(PACKET_ZC_MAIL_REQ_GET_LIST) + DataLen;
	SendPacket.MailNumber = Packet.MailNumber;
	pc->Send(sizeof(SendPacket), (char*)&SendPacket);
	pc->Send(DataLen, Data);
}


void CISvrIOPacketHandler::OnMailReqOpen(int Len)
{
	PACKET_IZ_MAIL_REQ_OPEN Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	int TextSize = Packet.PacketLength - sizeof(PACKET_IZ_MAIL_REQ_OPEN);
	if( TextSize >= 4096 )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "OnMailReqOpen  TextSize >= 4096 : AID:%d", Packet.AID);
		m_recvQueue->CPacketQueue::RemoveData(TextSize);
		return;
	}

	char Text[4096];
	m_recvQueue->CPacketQueue::GetData(TextSize, Text);

	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(Packet.AID, PC_TYPE);
	if( pc == NULL )
		return;

	if( TextSize >= 200 )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "OnMailReqOpen  TextSize >= 200 : AID:%d", Packet.AID);
		pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		return;
	}

	Text[TextSize] = '\0';
	++TextSize;

	PACKET_ZC_MAIL_REQ_OPEN SendPacket;
	SendPacket.PacketType = HEADER_ZC_MAIL_REQ_OPEN;
	SendPacket.PacketLength = sizeof(PACKET_ZC_MAIL_REQ_OPEN) + TextSize;
	SendPacket.MailID = Packet.MailID;
	memcpy_s(SendPacket.Header, sizeof(SendPacket.Header), Packet.Header, sizeof(Packet.Header));
	memcpy_s(SendPacket.FromName, sizeof(SendPacket.FromName), Packet.FromName, sizeof(Packet.FromName));
	SendPacket.Money = Packet.Money;
	SendPacket.DeleteTime = Packet.DeleteTime;

	CommonItemInfo ItemInfo;
	if( Packet.ItemLen != 0 && CPCItemInventoryMgr::DBValueParser(&ItemInfo, Packet.ItemInfo, Packet.ItemLen) == TRUE )
	{
		SendPacket.ITID = ItemInfo.ITID;
		SendPacket.Type = ItemInfo.Type;
		SendPacket.count = ItemInfo.count;
		SendPacket.IsIdentified = ItemInfo.IsIdentified;
		SendPacket.IsDamaged = ItemInfo.IsDamaged;
		SendPacket.refiningLevel = ItemInfo.refiningLevel;
		memcpy_s(&SendPacket.slot, sizeof(SendPacket.slot), &ItemInfo.slot, sizeof(ItemInfo.slot));
	}
	else
	{
		SendPacket.ITID = 0;
	}

	pc->CPC::SetLastOpenMailName(Packet.FromName);
	pc->Send(sizeof(PACKET_ZC_MAIL_REQ_OPEN), (char*)&SendPacket);
	pc->Send(TextSize, Text);
}


void CISvrIOPacketHandler::OnMailReqGetItem(int Len)
{
	PACKET_IZ_MAIL_REQ_GET_ITEM Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(Packet.AID, PC_TYPE);
	if( pc == NULL )
		return;

	unsigned long AID;
	unsigned long GID;
	if( !g_charInfoDB.CCharInfoDB::GetCharacterID(Packet.FromName, AID, GID) )
	{
		AID = 0;
		GID = 0;
	}

	CommonItemInfo ItemInfo = {};
	if( Packet.Money + pc->m_characterInfo.CharacterInfo::GetMoney() <= INT_MAX
		&& (Packet.ItemLen == 0
		|| CPCItemInventoryMgr::DBValueParser(&ItemInfo, Packet.ItemInfo, Packet.ItemLen) == TRUE
		&& pc->CPC::isBodyAddMailItem(ItemInfo.ITID, ItemInfo.ServerItemType, ItemInfo.count, ItemInfo.slot, ItemInfo.UniqueSerialNum)
		&& pc->CPC::PutInventoryBinaryItem(Packet.ItemInfo, Packet.ItemLen)) )
	{
		if( Packet.Money != 0 || ItemInfo.ITID != 0 )
		{
			g_itemLog.CItemLog::AddMailReceiveLog(Len, pc, AID, GID, Packet.FromName, &ItemInfo, Packet.Money);
			if( Packet.Money != 0 )
				pc->CPC::ModifyMoney(Packet.Money);
		}

		PACKET_ZC_MAIL_REQ_GET_ITEM SendPacket;
		SendPacket.PacketType = HEADER_ZC_MAIL_REQ_GET_ITEM;
		SendPacket.Result = PACKET_ZC_MAIL_REQ_GET_ITEM::RESULT_TRUE;
		pc->Send(sizeof(SendPacket), (char*)&SendPacket);
	}
	else
	{
		char Text[200];
		strcpy(Text, "   Mail ");
		size_t TextSize = strlen(Text);
		Text[0] = TextSize; //NOTE: pascal-style string length?
		memset(Text + TextSize, 13, '\0'); // ???

		PACKET_ZI_MAIL_SEND ZIPacket;
		ZIPacket.PacketType = HEADER_ZI_MAIL_SEND;
		ZIPacket.PacketLength = sizeof(ZIPacket) + TextSize + 13;
		ZIPacket.AID = pc->GetAccountID();
		ZIPacket.GID = pc->CPC::GetCharacterID();
		strcpy(ZIPacket.Header, "MAIL Error");
		memcpy_s(ZIPacket.ItemInfo, sizeof(ZIPacket.ItemInfo), Packet.ItemInfo, sizeof(Packet.ItemInfo));
		ZIPacket.ItemLen = Packet.ItemLen;
		strcpy(ZIPacket.SendName, "MailManager");
		ZIPacket.SendAID = 0;
		if( AID == 0 && GID == 0 )
		{
			strcpy(ZIPacket.SendName, "MailManager"); //NOTE: why do this when aborting?
			return;
		}
		strcpy(ZIPacket.SendName, Packet.FromName);
		ZIPacket.SendAID = AID;
		ZIPacket.Money = Packet.Money;
		CCharacterMgr::GetObj()->CCharacterMgr::SendToIServer(sizeof(PACKET_ZI_MAIL_SEND), (char*)&ZIPacket);
		CCharacterMgr::GetObj()->CCharacterMgr::SendToIServer(TextSize + 13, Text);

		PACKET_ZC_MAIL_REQ_GET_ITEM SendPacket;
		SendPacket.PacketType = HEADER_ZC_MAIL_REQ_GET_ITEM;
		SendPacket.Result = PACKET_ZC_MAIL_REQ_GET_ITEM::RESULT_ITEM_OVER_FALSE;
		pc->Send(sizeof(SendPacket), (char*)&SendPacket);
	}
}


void CISvrIOPacketHandler::OnMailReqSend(int Len)
{
	PACKET_IZ_MAIL_REQ_SEND Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	PACKET_ZC_MAIL_REQ_SEND SendPacket;
	SendPacket.PacketType = HEADER_ZC_MAIL_REQ_SEND;
	SendPacket.Result = PACKET_ZC_MAIL_REQ_SEND::RESULT_SUCCESS;

	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(Packet.AID, PC_TYPE);
	if( pc == NULL )
		return;

	pc->Send(sizeof(SendPacket), (char*)&SendPacket);
}


void CISvrIOPacketHandler::OnMailReceive(int Len)
{
	PACKET_IZ_MAIL_RECEIVE Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	PACKET_ZC_MAIL_RECEIVE SendPacket;
	SendPacket.PacketType = HEADER_ZC_MAIL_RECEIVE;
	SendPacket.MailID = Packet.MailID;
	memcpy_s(SendPacket.Header, sizeof(SendPacket.Header), Packet.Header, sizeof(Packet.Header));
	memcpy_s(SendPacket.FromName, sizeof(SendPacket.FromName), Packet.FromName, sizeof(Packet.FromName));

	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(Packet.AID, PC_TYPE);
	if( pc == NULL )
		return;

	pc->Send(sizeof(SendPacket), (char*)&SendPacket);
}


void CISvrIOPacketHandler::OnMailAckMailDelete(int Len)
{
	PACKET_IZ_ACK_MAIL_DELETE Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	PACKET_ZC_ACK_MAIL_DELETE SendPacket;
	SendPacket.PacketType = HEADER_ZC_ACK_MAIL_DELETE;
	SendPacket.MailID = Packet.MailID;
	SendPacket.Result = ( Packet.Result == PACKET_IZ_ACK_MAIL_DELETE::RESULT_TRUE ) ? PACKET_ZC_ACK_MAIL_DELETE::RESULT_TRUE : PACKET_ZC_ACK_MAIL_DELETE::RESULT_FALSE;

	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(Packet.AID, PC_TYPE);
	if( pc == NULL )
		return;

	pc->Send(sizeof(SendPacket), (char*)&SendPacket);
}


void CISvrIOPacketHandler::OnMailAckMailReturn(int Len)
{
	PACKET_IZ_ACK_MAIL_RETURN Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	PACKET_ZC_ACK_MAIL_RETURN SendPacket;
	SendPacket.PacketType = HEADER_ZC_ACK_MAIL_RETURN;
	SendPacket.MailID = Packet.MailID;
	SendPacket.Result = Packet.Result;

	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(Packet.AID, PC_TYPE);
	if( pc == NULL )
		return;

	if( Packet.Result == PACKET_IZ_ACK_MAIL_RETURN::TYPE_TRUE )
	{
		CommonItemInfo ItemInfo;
		CPCItemInventoryMgr::DBValueParser(&ItemInfo, Packet.ItemInfo, Packet.ItemLen);

		unsigned long AID;
		unsigned long GID;
		g_charInfoDB.CCharInfoDB::GetCharacterID(Packet.FromName, AID, GID);

		g_itemLog.CItemLog::AddMailSendLog(0, ITEMLOG_MAIL_RETURN, pc, Packet.AID, Packet.GID, Packet.FromName, &ItemInfo, Packet.Money);
	}

	pc->Send(sizeof(SendPacket), (char*)&SendPacket);
}


void CISvrIOPacketHandler::OnAckLogon(int Len)
{
	PACKET_IZ_ACK_LOGON Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	if( CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(Packet.AID, PC_TYPE) != NULL )
		--g_ZoneInterLoginValue;
	else
		++g_ZoneInterLoginError;
}


void CISvrIOPacketHandler::OnChkProcessTime(int Len)
{
	PACKET_IZ_CHK_PROCESSTIME Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	PACKET_ZI_ACK_CHK_PROCESSTIME SendPacket;
	SendPacket.PacketType = HEADER_ZI_ACK_CHK_PROCESSTIME;
	SendPacket.InterProcessTime = Packet.InterProcessTime;
	time_t the_time;
	SendPacket.ZoneProcessTime = time(&the_time);
	CCharacterMgr::GetObj()->CCharacterMgr::SendToIServer(sizeof(SendPacket), (char*)&SendPacket);
}


void CISvrIOPacketHandler::OnReqGroupInfoChangeV2(int Len)
{
	PACKET_IZ_REQ_GROUPINFO_CHANGE_V2 Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, Packet.AID, CM_REQ_GROUPINFO_CHANGE_V2, sizeof(Packet), (int)&Packet, 0, 0);
}


void CISvrIOPacketHandler::OnChangeGroupMaster(int len)
{
	PACKET_IZ_CHANGE_GROUP_MASTER Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, Packet.receiverAID, CM_CHANGE_GROUP_MASTER, Packet.OldMasterAID, 0, 0, 0);
}


void CISvrIOPacketHandler::OnSeekParty(int Len)
{
	PACKET_IZ_SEEK_PARTY Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	PACKET_ZC_SEEK_PARTY ouputpacket;
	ouputpacket.PacketType = HEADER_ZC_SEEK_PARTY;
	memcpy_s(ouputpacket.Name, sizeof(ouputpacket.Name), Packet.Name, sizeof(Packet.Name));
	ouputpacket.Job = Packet.Job;
	ouputpacket.Level = Packet.Level;
	memcpy_s(ouputpacket.mapName, sizeof(ouputpacket.mapName), Packet.mapName, sizeof(Packet.mapName));
	ouputpacket.Option = Packet.Option;
	CCharacterMgr::GetObj()->CCharacterMgr::BroadCast(sizeof(ouputpacket), (char*)&ouputpacket);
}


void CISvrIOPacketHandler::OnSeekPartyMember(int Len)
{
	PACKET_IZ_SEEK_PARTY_MEMBER Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	PACKET_ZC_SEEK_PARTY_MEMBER ouputpacket;
	ouputpacket.PacketType = HEADER_ZC_SEEK_PARTY_MEMBER;
	memcpy_s(ouputpacket.Name, sizeof(ouputpacket.Name), Packet.Name, sizeof(Packet.Name));
	ouputpacket.Job = Packet.Job;
	ouputpacket.Level = Packet.Level;
	memcpy_s(ouputpacket.mapName, sizeof(ouputpacket.mapName), Packet.mapName, sizeof(Packet.mapName));
	ouputpacket.Option = Packet.Option;
	CCharacterMgr::GetObj()->CCharacterMgr::BroadCast(sizeof(ouputpacket), (char*)&ouputpacket);
}


void CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_SYNC2(const int in_nPacketSize)
{
	char buf[1024] = {};
	if( m_recvQueue->CPacketQueue::GetData(in_nPacketSize, buf) == -1 )
		return;

	PACKET_IZ_MEMORIALDUNGEON_SYNC2& in_packet = *reinterpret_cast<PACKET_IZ_MEMORIALDUNGEON_SYNC2*>(buf);
	size_t MemorialDungeonNameLen = in_packet.PacketLength - sizeof(PACKET_IZ_MEMORIALDUNGEON_SYNC2);
	in_packet.MemorialDungeonName[MemorialDungeonNameLen] = '\0';

	if( in_packet.Event == PACKET_IZ_MEMORIALDUNGEON_SYNC2::EVENT_CREATE )
	{
		CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::Add(in_packet.ExistZSID, in_packet.MemorialDungeonName, in_packet.hPartyID, in_packet.partyName, in_packet.hMemorialDungeonID, in_packet.Factor);
	}
	else
	if( in_packet.Event == PACKET_IZ_MEMORIALDUNGEON_SYNC2::EVENT_DESTROY )
	{
		CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::Remove(in_packet.hPartyID);
	}
	else
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "unknown event found");
		return;
	}
}


void CISvrIOPacketHandler::OnIZ_NOTIFY_MAKERRANK(const PACKET_IZ_NOTIFY_MAKERRANK& in_packet)
{
	char* buf = const_cast<char*>(reinterpret_cast<const char*>(&in_packet));
	g_makerRankMgr.CMakerRankMgr::SetMakerRankList(buf);
}


void CISvrIOPacketHandler::OnIZ_GPK_DYNCODE_RELOAD(const PACKET_IZ_GPK_DYNCODE_RELOAD& in_packet)
{
}


void CISvrIOPacketHandler::OnIZ_IRMAIL_NOTIFY(const PACKET_IZ_IRMAIL_NOTIFY& in_packet)
{
}


void CISvrIOPacketHandler::OnIZ_INFO_ENTRY_QUEUE_APPLY(const PACKET_IZ_INFO_ENTRY_QUEUE_APPLY& in_packet)
{
}


void CISvrIOPacketHandler::OnIZ_NOTIFY_ENTRY_QUEUE_APPLY(const PACKET_IZ_NOTIFY_ENTRY_QUEUE_APPLY* in_packet)
{
}


void CISvrIOPacketHandler::OnIZ_RESULT_ENTRY_QUEUE_APPLY(const PACKET_IZ_RESULT_ENTRY_QUEUE_APPLY& in_packet)
{
}


void CISvrIOPacketHandler::OnIZ_NOTIFY_ENTRY_QUEUE_CANCEL(const PACKET_IZ_NOTIFY_ENTRY_QUEUE_CANCEL& in_packet)
{
}


void CISvrIOPacketHandler::OnIZ_RESULT_ENTRY_QUEUE_CANCEL(const PACKET_IZ_RESULT_ENTRY_QUEUE_CANCEL& in_packet)
{
}


void CISvrIOPacketHandler::OnIZ_ENTRY_QUEUE_ADMISSION(const PACKET_IZ_ENTRY_QUEUE_ADMISSION& in_packet)
{
}


void CISvrIOPacketHandler::OnIZ_NOTIFY_ENTRY_QUEUE_ADMISSION_ACCEPT(const PACKET_IZ_NOTIFY_ENTRY_QUEUE_ADMISSION_ACCEPT& in_packet)
{
}


void CISvrIOPacketHandler::OnIZ_RESULT_ENTRY_QUEUE_ADMISSION_ACCEPT(const PACKET_IZ_RESULT_ENTRY_QUEUE_ADMISSION_ACCEPT& in_packet)
{
}


void CISvrIOPacketHandler::OnIZ_NOTIFY_ENTRY_QUEUE_ADMISSION_REFUSE(const PACKET_IZ_NOTIFY_ENTRY_QUEUE_ADMISSION_REFUSE& in_packet)
{
}


void CISvrIOPacketHandler::OnIZ_RESULT_ENTRY_QUEUE_ADMISSION_REFUSE(const PACKET_IZ_RESULT_ENTRY_QUEUE_ADMISSION_REFUSE& in_packet)
{
}


void CISvrIOPacketHandler::OnIZ_LOBBY_ADMISSION(const PACKET_IZ_LOBBY_ADMISSION& in_packet)
{
}


void CISvrIOPacketHandler::OnIZ_LOBBY_ADMISSION_V2(const PACKET_IZ_LOBBY_ADMISSION_V2& in_packet)
{
}


void CISvrIOPacketHandler::OnIZ_NOTIFY_LOBBY_ADMISSION_ACCEPT(const PACKET_IZ_NOTIFY_LOBBY_ADMISSION_ACCEPT& in_packet)
{
}


void CISvrIOPacketHandler::OnIZ_RESULT_LOBBY_ADMISSION_ACCEPT(const PACKET_IZ_RESULT_LOBBY_ADMISSION_ACCEPT& in_packet)
{
}


void CISvrIOPacketHandler::OnIZ_NOTIFY_LOBBY_ADMISSION_REFUSE(const PACKET_IZ_NOTIFY_LOBBY_ADMISSION_REFUSE& in_packet)
{
}


void CISvrIOPacketHandler::OnIZ_RESULT_LOBBY_ADMISSION_REFUSE(const PACKET_IZ_RESULT_LOBBY_ADMISSION_REFUSE& in_packet)
{
}


void CISvrIOPacketHandler::OnIZ_ENTRY_QUEUE_LOGOUT(const PACKET_IZ_ENTRY_QUEUE_LOGOUT& in_packet)
{
}


void CISvrIOPacketHandler::OnIZ_ENTRY_QUEUE_MOVE_ROOM(const PACKET_IZ_ENTRY_QUEUE_MOVE_ROOM& in_packet)
{
}


void CISvrIOPacketHandler::OnIZ_LOBBY_MOVE_ROOM(const PACKET_IZ_LOBBY_MOVE_ROOM& in_packet)
{
}


void CISvrIOPacketHandler::OnIZ_ENTRY_QUEUE_RANKING(const PACKET_IZ_ENTRY_QUEUE_RANKING& in_packet)
{
}


void CISvrIOPacketHandler::OnIZ_NOTIFY_ENTRY_QUEUE_RANKING(const PACKET_IZ_NOTIFY_ENTRY_QUEUE_RANKING& in_packet)
{
}


void CISvrIOPacketHandler::OnIZ_SET_EFFECT_HIGH_RANKER(const PACKET_IZ_SET_EFFECT_HIGH_RANKER& in_packet)
{
}


void CISvrIOPacketHandler::OnIZ_RESET_EFFECT_HIGH_RANKER(const PACKET_IZ_RESET_EFFECT_HIGH_RANKER& in_packet)
{
}
