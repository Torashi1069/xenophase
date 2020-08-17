#include "CAgitMapRes.hpp"
#include "CharacterMgr.h"
#include "ISvrIOPacketHandler.h"
#include "CMakerRankMgr.hpp"
#include "MapResMgr.h"
#include "PC.h"
#include "ZGuildMgr.h"
#include "ISvrIO.h"
#include "ZoneProcess.h"
#include "ZSAcceptHandler.h"
#include "ErrorLog.h"
#include "Common/Packet.h"
#include "shared.h" // Trace
#include "globals.hpp"
#include "Custom/GlobalChat.h"


CISvrIOPacketHandler::CISvrIOPacketHandler(void) // line 53
{
	m_OldPacketSize = 0;
	m_OldHeader = 0;
}


CISvrIOPacketHandler::~CISvrIOPacketHandler(void) // line 59
{
}


hook_method<int (CISvrIOPacketHandler::*)(void)> CISvrIOPacketHandler::_OnProcess(SERVER, "CISvrIOPacketHandler::OnProcess");
int CISvrIOPacketHandler::OnProcess(void) // line 77
{
	return (this->*_OnProcess)();

	for( int i = 0; m_recvQueue->CPacketQueue::GetSize() >= 2 && i < 700; ++i )
	{
		int Header = 0;
		m_recvQueue->CPacketQueue::PeekData(2, (char*)&Header);

		int size;
		if( ::IsFixedPacket(Header) )
		{
			size = ::GetPacketSize(Header);
		}
		else
		{
			if( m_recvQueue->CPacketQueue::GetSize() < 4 )
				return -1;

			m_recvQueue->CPacketQueue::PeekData(4, (char*)&size);
			size = size >> 16;
		}

		if( size == 0 || size >= 20480 )
		{
			char buff[1024];
			sprintf(buff, "InterServer PacketSize error- %d  Header:%d FreeSize=%d QueueSize:%d", size, Header, m_recvQueue->CPacketQueue::GetFreeSize(), m_recvQueue->CPacketQueue::GetSize());
			g_errorLogs->CErrorLog::CriticalErrorLog(buff, 110, ".\\ISvrIOPacketHandler.cpp");
			sprintf(buff, "           m_OldHeader:%d    m_OldPacketSize:%d \n", m_OldHeader, m_OldPacketSize);
			g_errorLogs->CErrorLog::CriticalErrorLog(buff, 113, ".\\ISvrIOPacketHandler.cpp");
			m_recvQueue->CPacketQueue::Reset();
			return 0;
		}

		if( m_recvQueue->CPacketQueue::GetSize() >= size )
		{
			int result = this->CISvrIOPacketHandler::DispatchPacket(Header, size);
			if( result != -1 )
			{
				char buff[1024];
				sprintf(buff, "InterServer DispatchPacket error- %d  Header:%d FreeSize=%d QueueSize:%d\n", size, Header, m_recvQueue->CPacketQueue::GetFreeSize(), m_recvQueue->CPacketQueue::GetSize());
				g_errorLogs->CErrorLog::CriticalErrorLog(buff, 123, ".\\ISvrIOPacketHandler.cpp");
				return result;
			}
		}

		m_OldHeader = Header;
		m_OldPacketSize = size;
	}

	return -1;
}


hook_method<void (CISvrIOPacketHandler::*)(void)> CISvrIOPacketHandler::_OnClose(SERVER, "CISvrIOPacketHandler::OnClose");
void CISvrIOPacketHandler::OnClose(void) // line 63
{
	return (this->*_OnClose)();

	m_recvQueue->CPacketQueue::Reset();

	PACKET_XX_DISCONNECT packet;
	packet.PacketType = HEADER_XX_DISCONNECT;
	m_recvQueue->CPacketQueue::InsertData(sizeof(packet), (const char*)&packet);
}


hook_method<int (CISvrIOPacketHandler::*)(short Header, int packetSize)> CISvrIOPacketHandler::_DispatchPacket(SERVER, "CISvrIOPacketHandler::DispatchPacket");
int CISvrIOPacketHandler::DispatchPacket(short Header, int packetSize) // line 533
{
	return (this->*_DispatchPacket)(Header, packetSize);

	Trace("DispatchPacket start = %d\n", Header);

	switch( Header )
	{
	case HEADER_PING:
	{
		PACKET_PING ping;
		m_recvQueue->CPacketQueue::GetData(sizeof(ping), (char*)&ping);
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
	case HEADER_IZ_ACK_WHISPER:
		this->CISvrIOPacketHandler::OnWhisperAck(packetSize);
	break;
	case HEADER_IZ_USER_COUNT:
		this->CISvrIOPacketHandler::OnUserCount(packetSize);
	break;
	case HEADER_IZ_BROADCAST:
		this->CISvrIOPacketHandler::OnBroadCast(packetSize);
	break;
	case HEADER_IZ_ADD_MEMBER_TO_GROUP:
	case HEADER_IZ_ADD_MEMBER_TO_GROUP2:
		this->CISvrIOPacketHandler::OnAddMemberToGroup(packetSize);
	break;
	case HEADER_IZ_DELETE_MEMBER_FROM_GROUP:
		this->CISvrIOPacketHandler::OnDeleteMemberFromGroup(packetSize);
	break;
	case HEADER_IZ_ACK_MAKE_GROUP:
		this->CISvrIOPacketHandler::OnAckMakeGroup(packetSize);
	break;
	case HEADER_IZ_GROUP_LIST:
		this->CISvrIOPacketHandler::OnGroupList(packetSize);
	break;
	case HEADER_IZ_ACK_REQ_JOIN_GROUP:
		this->CISvrIOPacketHandler::OnAckReqJoinGroup(packetSize);
	break;
	case HEADER_IZ_REQ_JOIN_GROUP:
		this->CISvrIOPacketHandler::OnReqJoinGroup(packetSize);
	break;
	case HEADER_ZI_GRID_UPDATE:
		this->CISvrIOPacketHandler::OnGRIDUpdate(packetSize);
	break;
	case HEADER_IZ_CHAT_PARTY:
		this->CISvrIOPacketHandler::OnChatParty(packetSize);
	break;
	case HEADER_IZ_DISCONNECT_ALL:
		this->CISvrIOPacketHandler::OnDisconnectAll(packetSize);
	break;
	case HEADER_IZ_REQ_SERVERSTATE:
		this->CISvrIOPacketHandler::OnReqServerState(packetSize);
	break;
	case HEADER_IZ_DISCONNECT_CHARACTER:
		this->CISvrIOPacketHandler::OnDisconnectCharacter(packetSize);
	break;
	case HEADER_IZ_MOVE:
		this->CISvrIOPacketHandler::OnSpecialMove(packetSize);
	break;
	case HEADER_IZ_DIVORCE:
		this->CISvrIOPacketHandler::OnDivorce(packetSize);
	break;
	case HEADER_IZ_FRIENDS_LIST:
		this->CISvrIOPacketHandler::OnFriendsList(packetSize);
	break;
	case HEADER_IZ_FRIENDS_STATE:
		this->CISvrIOPacketHandler::OnFriendsState(packetSize);
	break;
	case HEADER_IZ_ADD_FRIENDS:
		this->CISvrIOPacketHandler::OnAddFriend(packetSize);
	break;
	case HEADER_IZ_DELETE_FRIENDS:
		this->CISvrIOPacketHandler::OnDeleteFriends(packetSize);
	break;
	case HEADER_IZ_RESULT_MAKE_GUILD:
		this->CISvrIOPacketHandler::OnResultGuildMake(packetSize);
	break;
	case HEADER_IZ_REQ_JOIN_GUILD:
		this->CISvrIOPacketHandler::OnReqJoinGuild(packetSize);
	break;
	case HEADER_IZ_ACK_REQ_JOIN_GUILD:
		this->CISvrIOPacketHandler::OnAckReqJoinGuild(packetSize);
	break;
	case HEADER_IZ_UPDATE_CHARGDID:
		this->CISvrIOPacketHandler::OnUpdateCharGDID(packetSize);
	break;
	case HEADER_IZ_GUILDINFO_TOD:
		this->CISvrIOPacketHandler::OnGuildInfo(packetSize);
	break;
	case HEADER_IZ_GUILD_CHANGEOWNER_AGIT:
		this->CISvrIOPacketHandler::OnChangeOwnerAgit(packetSize);
	break;
	case HEADER_IZ_MYGUILD_BASICINFO:
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
	{
		#pragma pack(push,1)
		struct TEMPHEADER {
			/* this+0 */ short PacketType;
			/* this+2 */ unsigned long GDID;
		} temp;
		#pragma pack(pop)
		m_recvQueue->CPacketQueue::PeekData(sizeof(temp), (char*)&temp);

		m_recvQueue->CPacketQueue::GetData(packetSize, m_PacketBuffer);
		g_ZGuildMgr->CZGuildMgr::SendPacket(temp.GDID, temp.PacketType, packetSize, m_PacketBuffer);
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
		#pragma pack(push,1)
		struct TEMPHEADER {
			/* this+0 */ short PacketType;
			/* this+2 */ unsigned short PacketLength;
			/* this+6 */ unsigned long GDID;
		} temp;
		#pragma pack(pop)
		m_recvQueue->CPacketQueue::PeekData(sizeof(temp), (char*)&temp);

		if( m_recvQueue->CPacketQueue::GetData(packetSize, m_PacketBuffer) == -1 )
		{
			char temp[256];
			sprintf(temp, "Error m_recvQueue->GetData Size = %d, QSize = %d, FSize = %d\n", -1, m_recvQueue->CPacketQueue::GetSize(), m_recvQueue->CPacketQueue::GetFreeSize());
			g_errorLogs->CErrorLog::CriticalErrorLog(temp, 839, ".\\ISvrIOPacketHandler.cpp");
			m_recvQueue->CPacketQueue::Reset();
		}
		g_ZGuildMgr->CZGuildMgr::SendPacket(temp.GDID, temp.PacketType, packetSize, m_PacketBuffer);
	}
	break;
	case HEADER_IZ_NOTIFY_MAKERRANK:
	{
		PACKET_IZ_NOTIFY_MAKERRANK packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		g_makerRankMgr->CMakerRankMgr::SetMakerRankList((char*)&packet);
	}
	break;
	case HEADER_IZ_MAIL_REQ_GET_LIST:
		this->CISvrIOPacketHandler::OnMailReqGetList(packetSize);
	break;
	case HEADER_IZ_MAIL_REQ_OPEN:
		this->CISvrIOPacketHandler::OnMailReqOpen(packetSize);
	break;
	case HEADER_IZ_MAIL_REQ_GET_ITEM:
		this->CISvrIOPacketHandler::OnMailReqGetItem(packetSize);
	break;
	case HEADER_IZ_MAIL_REQ_SEND:
		this->CISvrIOPacketHandler::OnMailReqSend(packetSize);
	break;
	case HEADER_IZ_MAIL_RECEIVE:
		this->CISvrIOPacketHandler::OnMailReceive(packetSize);
	break;
	case HEADER_IZ_ACK_MAIL_DELETE:
		this->CISvrIOPacketHandler::OnMailAckMailDelete(packetSize);
	break;
	case HEADER_IZ_ACK_MAIL_RETURN:
		this->CISvrIOPacketHandler::OnMailAckMailReturn(packetSize);
	break;
	case HEADER_IZ_ACK_LOGON:
		this->CISvrIOPacketHandler::OnAckLogon(packetSize);
	break;
	case HEADER_IZ_CHK_PROCESSTIME:
		this->CISvrIOPacketHandler::OnChkProcessTime(packetSize);
	break;
	case HEADER_IZ_REQ_GROUPINFO_CHANGE_V2:
		this->CISvrIOPacketHandler::OnReqGroupInfoChangeV2(packetSize);
	break;
	case HEADER_IZ_SEEK_PARTY:
		this->CISvrIOPacketHandler::OnSeekParty(packetSize);
	break;
	case HEADER_ZI_SEEK_PARTY_MEMBER:
		this->CISvrIOPacketHandler::OnSeekPartyMember(packetSize);
	break;
	case HEADER_IZ_GUILD_ZENY:
		;
	break;
	case HEADER_IZ_WHISPER:
		this->CISvrIOPacketHandler::OnWhisper(packetSize);
	break;
	default:
	{
		m_recvQueue->CPacketQueue::Reset();

		char temp[256];
		sprintf(temp, "Not Header ISvrIO Header:%d, packetSize:%d\n", Header, packetSize);
		g_errorLogs->CErrorLog::CriticalErrorLog(temp, 940, ".\\ISvrIOPacketHandler.cpp");
		sprintf(temp, "           m_OldHeader:%d    m_OldPacketSize:%d \n", m_OldHeader, m_OldPacketSize);
		g_errorLogs->CErrorLog::CriticalErrorLog(temp, 942, ".\\ISvrIOPacketHandler.cpp");
		Trace("not Header ISvrIO\n");
		return 0;
	}
	break;
	}

	Trace("DispatchPacket end\n", Header);
	return -1;
}


hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnWhisper(SERVER, "CISvrIOPacketHandler::OnWhisper");
void CISvrIOPacketHandler::OnWhisper(int len) // line 963
{
	return (this->*_OnWhisper)(len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnWhisperAck(SERVER, "CISvrIOPacketHandler::OnWhisperAck");
void CISvrIOPacketHandler::OnWhisperAck(int len) // line 976
{
	return (this->*_OnWhisperAck)(len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnUserCount(SERVER, "CISvrIOPacketHandler::OnUserCount");
void CISvrIOPacketHandler::OnUserCount(int len) // line 985
{
	return (this->*_OnUserCount)(len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnBroadCast(SERVER, "CISvrIOPacketHandler::OnBroadCast");
HOOKED void CISvrIOPacketHandler::OnBroadCast(int len) // line 993
{
//	return (this->*_OnBroadCast)(len);

	char buf[512]; //FIXME: trusts inter - no size checks, not zero terminated

	PACKET_IZ_BROADCAST& iz_broadcast = *(PACKET_IZ_BROADCAST*)buf;
	m_recvQueue->CPacketQueue::GetData(len, (char*)&iz_broadcast);

	if( iz_broadcast.Text[0] == '#' )
	{// global chat
		intif_parse_globalchat(iz_broadcast.Text);
		return;
	}

	PACKET_ZC_BROADCAST& zc_broadcast = *(PACKET_ZC_BROADCAST*)buf;
	zc_broadcast.PacketType = HEADER_ZC_BROADCAST;
	g_characterMgr->CCharacterMgr::BroadCast(len, (char*)&zc_broadcast);
}


hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnSpecialMove(SERVER, "CISvrIOPacketHandler::OnSpecialMove");
void CISvrIOPacketHandler::OnSpecialMove(int len) // line 1425
{
	return (this->*_OnSpecialMove)(len);

	PACKET_IZ_MOVE Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char*)&Packet);

	PACKET_ZI_MOVE ZIPacket;
	if( Packet.MoveType == SUMMONAID || Packet.MoveType == SUMMONGID || Packet.MoveType == SUMMONMARRY )
	{// warp target to specified location
		CPC* target = (CPC*)g_characterMgr->CCharacterMgr::FindCharacter(Packet.DestID, PC_TYPE);
		if( target == NULL )
			return;
		if( Packet.MoveType == SUMMONMARRY && target->GetState() == CHARACTER_STATE_DEAD )
			return;

		MS_MAPMOVE outpar;
		outpar.Set(Packet.MapName, Packet.DestX, Packet.DestY, 0);
		g_characterMgr->CCharacterMgr::SendMsg(target, target, CM_MAPMOVE, (int)&outpar, SUMMONGID, 0, 0);
	}
	else
	{// report target's location back so that it can be warped to
		CPC* target = (CPC*)g_characterMgr->CCharacterMgr::FindCharacter(Packet.DestID, PC_TYPE);
		if( target == NULL )
			return;

		ZIPacket.PacketType = HEADER_ZI_MOVE;
		ZIPacket.MoveType = SUMMONGID;
		ZIPacket.SrcID = target->GetAccountID();
		target->GetParameterValue(VAR_CURXPOS, ZIPacket.DestX);
		target->GetParameterValue(VAR_CURYPOS, ZIPacket.DestY);
		memcpy(ZIPacket.DestName, Packet.CharName, 24);
		g_characterMgr->CCharacterMgr::SendToIServer(sizeof(ZIPacket), (char*)&ZIPacket);
	}
}


hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnAddMemberToGroup(SERVER, "CISvrIOPacketHandler::OnAddMemberToGroup");
void CISvrIOPacketHandler::OnAddMemberToGroup(int len) // line 1004
{
	return (this->*_OnAddMemberToGroup)(len);

	PACKET_IZ_ADD_MEMBER_TO_GROUP2 packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
	g_characterMgr->CCharacterMgr::SendMsg(NULL, packet.receiverAID, CM_ADD_MEMBER_TO_GROUP, sizeof(packet), (int)&packet, 0, 0);
}


hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnDeleteMemberFromGroup(SERVER, "CISvrIOPacketHandler::OnDeleteMemberFromGroup");
void CISvrIOPacketHandler::OnDeleteMemberFromGroup(int len) // line 1020
{
	return (this->*_OnDeleteMemberFromGroup)(len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnAckMakeGroup(SERVER, "CISvrIOPacketHandler::OnAckMakeGroup");
void CISvrIOPacketHandler::OnAckMakeGroup(int len) // line 1029
{
	return (this->*_OnAckMakeGroup)(len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnGroupList(SERVER, "CISvrIOPacketHandler::OnGroupList");
void CISvrIOPacketHandler::OnGroupList(int len) // line 1038
{
	return (this->*_OnGroupList)(len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnAckReqJoinGroup(SERVER, "CISvrIOPacketHandler::OnAckReqJoinGroup");
void CISvrIOPacketHandler::OnAckReqJoinGroup(int len) // line 1055
{
	return (this->*_OnAckReqJoinGroup)(len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnReqJoinGroup(SERVER, "CISvrIOPacketHandler::OnReqJoinGroup");
void CISvrIOPacketHandler::OnReqJoinGroup(int len) // line 1064
{
	return (this->*_OnReqJoinGroup)(len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnGRIDUpdate(SERVER, "CISvrIOPacketHandler::OnGRIDUpdate");
void CISvrIOPacketHandler::OnGRIDUpdate(int len) // line 1073
{
	return (this->*_OnGRIDUpdate)(len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnChatParty(SERVER, "CISvrIOPacketHandler::OnChatParty");
void CISvrIOPacketHandler::OnChatParty(int len) // line 1082
{
	return (this->*_OnChatParty)(len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnDisconnectAll(SERVER, "CISvrIOPacketHandler::OnDisconnectAll");
void CISvrIOPacketHandler::OnDisconnectAll(int len) // line 1114
{
	return (this->*_OnDisconnectAll)(len);

	g_zsAcceptHandler->CZSAcceptHandler::SetAccpetable(0);
	g_IsDisconnectAll = true;

	PACKET_IZ_DISCONNECT_ALL packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	PACKET_SC_NOTIFY_BAN outpacket;
	outpacket.PacketType = HEADER_SC_NOTIFY_BAN;
	outpacket.ErrorCode = 0;
	g_characterMgr->CCharacterMgr::BroadCastExceptME(sizeof(outpacket), (char*)&outpacket, "gravity");

	char temp[256];
	sprintf(temp, "CCISvrIOPacketHandler :: OnDisconnectAll\n");
	g_errorLogs->CErrorLog::CriticalErrorLog(temp, 1138, ".\\ISvrIOPacketHandler.cpp");

	Trace("CCISvrIOPacketHandler :: OnDisconnectAll \n");
}


hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnReqServerState(SERVER, "CISvrIOPacketHandler::OnReqServerState");
void CISvrIOPacketHandler::OnReqServerState(int len) // line 1162
{
	return (this->*_OnReqServerState)(len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnResultGuildMake(SERVER, "CISvrIOPacketHandler::OnResultGuildMake");
void CISvrIOPacketHandler::OnResultGuildMake(int len) // line 1192
{
	return (this->*_OnResultGuildMake)(len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnReqJoinGuild(SERVER, "CISvrIOPacketHandler::OnReqJoinGuild");
void CISvrIOPacketHandler::OnReqJoinGuild(int Len) // line 1213
{
	return (this->*_OnReqJoinGuild)(Len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnAckReqJoinGuild(SERVER, "CISvrIOPacketHandler::OnAckReqJoinGuild");
void CISvrIOPacketHandler::OnAckReqJoinGuild(int Len) // line 1234
{
	return (this->*_OnAckReqJoinGuild)(Len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnUpdateCharGDID(SERVER, "CISvrIOPacketHandler::OnUpdateCharGDID");
void CISvrIOPacketHandler::OnUpdateCharGDID(int Len) // line 1259
{
	return (this->*_OnUpdateCharGDID)(Len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnGuildInfo(SERVER, "CISvrIOPacketHandler::OnGuildInfo");
void CISvrIOPacketHandler::OnGuildInfo(int Len) // line 1337
{
	return (this->*_OnGuildInfo)(Len);

	//TODO
}


//hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnAckGuildZeny(SERVER, "CISvrIOPacketHandler::OnAckGuildZeny");
void CISvrIOPacketHandler::OnAckGuildZeny(int len) // line ????
{
//	return (this->*_OnAckGuildZeny)(len);

	PACKET_IZ_GUILD_ZENY packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char *)&packet);

	if( packet.AID != 0 )
	{
		bool ret;

		CPC* pc = (CPC*)g_characterMgr->CCharacterMgr::FindCharacter(packet.AID, PC_TYPE);
		if( pc && pc->CPC::GetCharacterID() == packet.GID && pc->CPC::IsReadyToSave() )
		{
			PACKET_ZC_GUILD_ZENY_ACK buf;
			buf.PacketType = HEADER_ZC_GUILD_ZENY_ACK;
			buf.ret = packet.ret;
			if( packet.ret == 1 )
			{
				if( !pc->CPC::ModifyMoney(-packet.zeny) )
					buf.ret = 4;
			}
			pc->CPC::Send(sizeof(buf), (char*)&buf);
			ret = ( buf.ret == 4 );
		}
		else
		{
			ret = ( packet.ret == 1 );
		}

		if( ret )
		{
			PACKET_ZI_GUILD_ZENY out;
			out.PacketType = HEADER_ZI_GUILD_ZENY;
			out.GDID = packet.GDID;
			out.AID = -1;
			out.GID = 0;
			memset(out.mapName, 0, sizeof(out.mapName));
			out.type = 2;
			out.zeny = packet.zeny;
			g_characterMgr->CCharacterMgr::SendToIServer(sizeof(out), (char *)&out);
		}
	}
	else
	{
		CMapRes* mapres = g_mapResMgr->CMapResMgr::GetMapRes(packet.mapName);
		if( mapres && mapres->CMapRes::GetType() == MAPTYPE_AGIT )
			((CAgitMapRes *)mapres)->CAgitMapRes::OnRcvAckFromInter(packet.ret);
		else
			Trace("OnAckGuildZeny - no such agit:%s\n", packet.mapName);
	}
}


hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnDisconnectCharacter(SERVER, "CISvrIOPacketHandler::OnDisconnectCharacter");
void CISvrIOPacketHandler::OnDisconnectCharacter(int len) // line 1346
{
	return (this->*_OnDisconnectCharacter)(len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnChangeOwnerAgit(SERVER, "CISvrIOPacketHandler::OnChangeOwnerAgit");
void CISvrIOPacketHandler::OnChangeOwnerAgit(int len) // line 1498
{
	return (this->*_OnChangeOwnerAgit)(len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(int len)> CISvrIOPacketHandler::_OnDivorce(SERVER, "CISvrIOPacketHandler::OnDivorce");
void CISvrIOPacketHandler::OnDivorce(int len) // line 1507
{
	return (this->*_OnDivorce)(len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnFriendsList(SERVER, "CISvrIOPacketHandler::OnFriendsList");
void CISvrIOPacketHandler::OnFriendsList(int Len) // line 1524
{
	return (this->*_OnFriendsList)(Len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnFriendsState(SERVER, "CISvrIOPacketHandler::OnFriendsState");
void CISvrIOPacketHandler::OnFriendsState(int Len) // line 1544
{
	return (this->*_OnFriendsState)(Len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnAddFriend(SERVER, "CISvrIOPacketHandler::OnAddFriend");
void CISvrIOPacketHandler::OnAddFriend(int Len) // line 1557
{
	return (this->*_OnAddFriend)(Len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnDeleteFriends(SERVER, "CISvrIOPacketHandler::OnDeleteFriends");
void CISvrIOPacketHandler::OnDeleteFriends(int Len) // line 1575
{
	return (this->*_OnDeleteFriends)(Len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnMailReqGetList(SERVER, "CISvrIOPacketHandler::OnMailReqGetList");
void CISvrIOPacketHandler::OnMailReqGetList(int Len) // line 1589
{
	return (this->*_OnMailReqGetList)(Len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnMailReqOpen(SERVER, "CISvrIOPacketHandler::OnMailReqOpen");
void CISvrIOPacketHandler::OnMailReqOpen(int Len) // line 1620
{
	return (this->*_OnMailReqOpen)(Len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnMailReqGetItem(SERVER, "CISvrIOPacketHandler::OnMailReqGetItem");
void CISvrIOPacketHandler::OnMailReqGetItem(int Len) // line 1694
{
	return (this->*_OnMailReqGetItem)(Len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnMailReqSend(SERVER, "CISvrIOPacketHandler::OnMailReqSend");
void CISvrIOPacketHandler::OnMailReqSend(int Len) // line 1801
{
	return (this->*_OnMailReqSend)(Len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnMailReceive(SERVER, "CISvrIOPacketHandler::OnMailReceive");
void CISvrIOPacketHandler::OnMailReceive(int Len) // line 1815
{
	return (this->*_OnMailReceive)(Len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnMailAckMailDelete(SERVER, "CISvrIOPacketHandler::OnMailAckMailDelete");
void CISvrIOPacketHandler::OnMailAckMailDelete(int Len) // line 1831
{
	return (this->*_OnMailAckMailDelete)(Len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnMailAckMailReturn(SERVER, "CISvrIOPacketHandler::OnMailAckMailReturn");
void CISvrIOPacketHandler::OnMailAckMailReturn(int Len) // line 1854
{
	return (this->*_OnMailAckMailReturn)(Len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnAckLogon(SERVER, "CISvrIOPacketHandler::OnAckLogon");
void CISvrIOPacketHandler::OnAckLogon(int Len) // line 1881
{
	return (this->*_OnAckLogon)(Len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnChkProcessTime(SERVER, "CISvrIOPacketHandler::OnChkProcessTime");
void CISvrIOPacketHandler::OnChkProcessTime(int Len) // line 1895
{
	return (this->*_OnChkProcessTime)(Len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnReqGroupInfoChangeV2(SERVER, "CISvrIOPacketHandler::OnReqGroupInfoChangeV2");
void CISvrIOPacketHandler::OnReqGroupInfoChangeV2(int Len) // line 1910
{
	return (this->*_OnReqGroupInfoChangeV2)(Len);

	PACKET_IZ_REQ_GROUPINFO_CHANGE_V2 Packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(Packet), (char *)&Packet);
	g_characterMgr->CCharacterMgr::SendMsg(NULL, Packet.AID, CM_REQ_GROUPINFO_CHANGE_V2, sizeof(Packet), (int)&Packet, 0, 0);
}


hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnSeekParty(SERVER, "CISvrIOPacketHandler::OnSeekParty");
void CISvrIOPacketHandler::OnSeekParty(int Len) // line 1919
{
	return (this->*_OnSeekParty)(Len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(int Len)> CISvrIOPacketHandler::_OnSeekPartyMember(SERVER, "CISvrIOPacketHandler::OnSeekPartyMember");
void CISvrIOPacketHandler::OnSeekPartyMember(int Len) // line 1937
{
	return (this->*_OnSeekPartyMember)(Len);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(const PACKET_IZ_INSTANTMAP_CREATE_REQ& in_packet)> CISvrIOPacketHandler::_OnINSTANTMAP_CREATE_REQ(SERVER, "CISvrIOPacketHandler::OnINSTANTMAP_CREATE_REQ");
void CISvrIOPacketHandler::OnINSTANTMAP_CREATE_REQ(const PACKET_IZ_INSTANTMAP_CREATE_REQ& in_packet) // line 153
{
	return (this->*_OnINSTANTMAP_CREATE_REQ)(in_packet);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(const PACKET_IZ_INSTANTMAP_PLAYER_ENTER& in_packet)> CISvrIOPacketHandler::_OnINSTANTMAP_PLAYER_ENTER(SERVER, "CISvrIOPacketHandler::OnINSTANTMAP_PLAYER_ENTER");
void CISvrIOPacketHandler::OnINSTANTMAP_PLAYER_ENTER(const PACKET_IZ_INSTANTMAP_PLAYER_ENTER& in_packet) // line 177
{
	return (this->*_OnINSTANTMAP_PLAYER_ENTER)(in_packet);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(const PACKET_IZ_INSTNATMAP_DESTROY& in_packet)> CISvrIOPacketHandler::_OnINSTNATMAP_DESTROY(SERVER, "CISvrIOPacketHandler::OnINSTNATMAP_DESTROY");
void CISvrIOPacketHandler::OnINSTNATMAP_DESTROY(const PACKET_IZ_INSTNATMAP_DESTROY& in_packet) // line 140
{
	return (this->*_OnINSTNATMAP_DESTROY)(in_packet);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(const PACKET_XX_CONNECT& in_packet)> CISvrIOPacketHandler::_OnXX_CONNECT(SERVER, "CISvrIOPacketHandler::OnXX_CONNECT");
void CISvrIOPacketHandler::OnXX_CONNECT(const PACKET_XX_CONNECT& in_packet) // line 224
{
	return (this->*_OnXX_CONNECT)(in_packet);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(const PACKET_XX_DISCONNECT& in_packet)> CISvrIOPacketHandler::_OnXX_DISCONNECT(SERVER, "CISvrIOPacketHandler::OnXX_DISCONNECT");
void CISvrIOPacketHandler::OnXX_DISCONNECT(const PACKET_XX_DISCONNECT& in_packet) // line 190
{
	return (this->*_OnXX_DISCONNECT)(in_packet);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(const PACKET_IZ_MEMORIALDUNGEON_MSG& in_packet)> CISvrIOPacketHandler::_OnIZ_MEMORIALDUNGEON_MSG(SERVER, "CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_MSG");
void CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_MSG(const PACKET_IZ_MEMORIALDUNGEON_MSG& in_packet) // line 236
{
	return (this->*_OnIZ_MEMORIALDUNGEON_MSG)(in_packet);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(const PACKET_IZ_PARTY_JOIN_REQ& in_packet)> CISvrIOPacketHandler::_OnIZ_PARTY_JOIN_REQ(SERVER, "CISvrIOPacketHandler::OnIZ_PARTY_JOIN_REQ");
void CISvrIOPacketHandler::OnIZ_PARTY_JOIN_REQ(const PACKET_IZ_PARTY_JOIN_REQ& in_packet) // line 322-349
{
	return (this->*_OnIZ_PARTY_JOIN_REQ)(in_packet);

	CPC* targetPlayer = static_cast<CPC*>(g_characterMgr->CCharacterMgr::FindCharacter(in_packet.targetAID, PC_TYPE));
	if( targetPlayer == NULL )
	{
		Send_PACKET_ZI_PARTY_JOIN_REQ_ACK(in_packet.targetAID, in_packet.GRID, PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_UNKNOWN_CHARACTER);
		return; // target not found
	}

	if( targetPlayer->m_characterInfo.Party.Bit.bRefuseJoinMsg == 1 )
	{
		Send_PACKET_ZI_PARTY_JOIN_REQ_ACK(in_packet.targetAID, in_packet.GRID, PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_JOINMSG_REFUSE);
		return; // target auto-refused
	}

	if( targetPlayer->IsItPossible(MAPPROPERTY_NO_PARTY_FORMATION) == 1 )
	{
		Send_PACKET_ZI_PARTY_JOIN_REQ_ACK(in_packet.targetAID, in_packet.GRID, PACKET_ZC_PARTY_JOIN_REQ_ACK::ANSWER_INVALID_MAPPROPERTY);
		return; // target can't join party in this map
	}

	PACKET_ZC_PARTY_JOIN_REQ packet;
	memset(packet.groupName, 0, sizeof(packet.groupName));

	packet.GRID = in_packet.GRID;
	packet.PacketType = HEADER_ZC_PARTY_JOIN_REQ;
	memcpy(packet.groupName, in_packet.groupName, sizeof(packet.groupName));

	targetPlayer->CPC::Send(sizeof(packet), (char *)&packet);
}


hook_method<void (CISvrIOPacketHandler::*)(const PACKET_IZ_PARTY_JOIN_REQ_ACK& in_packet)> CISvrIOPacketHandler::_OnIZ_PARTY_JOIN_REQ_ACK(SERVER, "CISvrIOPacketHandler::OnIZ_PARTY_JOIN_REQ_ACK");
void CISvrIOPacketHandler::OnIZ_PARTY_JOIN_REQ_ACK(const PACKET_IZ_PARTY_JOIN_REQ_ACK& in_packet) // line 354-364
{
	return (this->*_OnIZ_PARTY_JOIN_REQ_ACK)(in_packet);

	CPC* player = static_cast<CPC*>(g_characterMgr->CCharacterMgr::FindCharacter(in_packet.requestAID, PC_TYPE));
	if( player != NULL )
		Sned_PACKET_ZC_PARTY_JOIN_REQ_ACK(player, in_packet.characterName, in_packet.answer);
}


hook_method<void (CISvrIOPacketHandler::*)(const PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO& in_packet)> CISvrIOPacketHandler::_OnIZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO(SERVER, "CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO");
void CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO(const PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO& in_packet) // line 367
{
	return (this->*_OnIZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO)(in_packet);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(const PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY& in_packet)> CISvrIOPacketHandler::_OnIZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY(SERVER, "CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY");
void CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY(const PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY& in_packet) // line 383
{
	return (this->*_OnIZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY)(in_packet);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(const PACKET_IZ_MEMORIALDUNGEON_INFO& in_packet)> CISvrIOPacketHandler::_OnIZ_MEMORIALDUNGEON_INFO(SERVER, "CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_INFO");
void CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_INFO(const PACKET_IZ_MEMORIALDUNGEON_INFO& in_packet) // line 398
{
	return (this->*_OnIZ_MEMORIALDUNGEON_INFO)(in_packet);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(const PACKET_IZ_MEMORIALDUNGEON_NOTIFY& in_packet)> CISvrIOPacketHandler::_OnIZ_MEMORIALDUNGEON_NOTIFY(SERVER, "CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_NOTIFY");
void CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_NOTIFY(const PACKET_IZ_MEMORIALDUNGEON_NOTIFY& in_packet) // line 415
{
	return (this->*_OnIZ_MEMORIALDUNGEON_NOTIFY)(in_packet);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(const PACKET_IZ_MEMORIALDUNGEON_SYNC& in_packet)> CISvrIOPacketHandler::_OnIZ_MEMORIALDUNGEON_SYNC(SERVER, "CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_SYNC");
void CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_SYNC(const PACKET_IZ_MEMORIALDUNGEON_SYNC& in_packet) // line 432
{
	return (this->*_OnIZ_MEMORIALDUNGEON_SYNC)(in_packet);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(const PACKET_IZ_MEMORIALDUNGEON_VISA& in_packet)> CISvrIOPacketHandler::_OnIZ_MEMORIALDUNGEON_VISA(SERVER, "CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_VISA");
void CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_VISA(const PACKET_IZ_MEMORIALDUNGEON_VISA& in_packet) // line 458
{
	return (this->*_OnIZ_MEMORIALDUNGEON_VISA)(in_packet);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(const PACKET_IZ_MEMORIALDUNGEON_COMMAND& in_packet)> CISvrIOPacketHandler::_OnIZ_MEMORIALDUNGEON_COMMAND(SERVER, "CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_COMMAND");
void CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_COMMAND(const PACKET_IZ_MEMORIALDUNGEON_COMMAND& in_packet) // line 501
{
	return (this->*_OnIZ_MEMORIALDUNGEON_COMMAND)(in_packet);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(const PACKET_IZ_MEMORIALDUNGEON_OPENSTATE& in_packet)> CISvrIOPacketHandler::_OnIZ_MEMORIALDUNGEON_OPENSTATE(SERVER, "CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_OPENSTATE");
void CISvrIOPacketHandler::OnIZ_MEMORIALDUNGEON_OPENSTATE(const PACKET_IZ_MEMORIALDUNGEON_OPENSTATE& in_packet) // line 483
{
	return (this->*_OnIZ_MEMORIALDUNGEON_OPENSTATE)(in_packet);

	//TODO
}


hook_method<void (CISvrIOPacketHandler::*)(const PACKET_IZ_LEAVE_GROUP& in_packet)> CISvrIOPacketHandler::_OnIZ_LEAVE_GROUP(SERVER, "CISvrIOPacketHandler::OnIZ_LEAVE_GROUP");
void CISvrIOPacketHandler::OnIZ_LEAVE_GROUP(const PACKET_IZ_LEAVE_GROUP& in_packet) // line 519
{
	return (this->*_OnIZ_LEAVE_GROUP)(in_packet);

	//TODO
}


hook_method<void (__cdecl*)(unsigned long in_TargetAID, unsigned long in_GRID, enum  PACKET_ZC_PARTY_JOIN_REQ_ACK::enumAnswer in_answer)> _Send_PACKET_ZI_PARTY_JOIN_REQ_ACK(SERVER, "Send_PACKET_ZI_PARTY_JOIN_REQ_ACK");
void __cdecl Send_PACKET_ZI_PARTY_JOIN_REQ_ACK(unsigned long in_TargetAID, unsigned long in_GRID, enum  PACKET_ZC_PARTY_JOIN_REQ_ACK::enumAnswer in_answer) // line 310-317
{
	return (_Send_PACKET_ZI_PARTY_JOIN_REQ_ACK)(in_TargetAID, in_GRID, in_answer);

	PACKET_ZI_PARTY_JOIN_REQ_ACK packet;
	packet.targetAID = in_TargetAID;
	packet.PacketType = HEADER_ZI_PARTY_JOIN_REQ_ACK;
	packet.GRID = in_GRID;
	packet.answer = in_answer;

	g_iSvrIO->CSvrIO::Send(sizeof(packet), (const char *)&packet);
}
