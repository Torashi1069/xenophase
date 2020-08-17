#include "Client/InterServerClient/C2InterServerClient.h"
#include "Client/InterServerClient/C2InterServerClientPacketHandler.h"
#include "Common/Packet.h"
#include "Common/PacketLengthExMgr.h"
#include "Instant map/InstantMapMgr.h"
#include "shared/NCriticalErrorLog.h"


C2InterServerClientPacketHandler::C2InterServerClientPacketHandler()
{
	m_LastPacketRecvTM = timeGetTime();
}


C2InterServerClientPacketHandler::~C2InterServerClientPacketHandler()
{
}


DWORD C2InterServerClientPacketHandler::GetLastPacketRecvTM()
{
	return m_LastPacketRecvTM;
}


void C2InterServerClientPacketHandler::SetLastPacketRecvTM(DWORD in_LastPacketRecvTM)
{
	m_LastPacketRecvTM = in_LastPacketRecvTM;
}


void C2InterServerClientPacketHandler::OnClose()
{
}


int C2InterServerClientPacketHandler::OnProcess()
{
	for( int Cnt = 0; Cnt < 700; ++Cnt )
	{
		const int RecvQueueSize = m_recvQueue->CPacketQueue::GetSize();
		if( RecvQueueSize < sizeof(PACKET) )
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
			if( RecvQueueSize < sizeof(PACKETV) )
				return -1;

			int Header = 0;
			m_recvQueue->CPacketQueue::PeekData(sizeof(Header), (char*)&Header);

			size = Header >> 16;
			if( size < fpRet.second )
			{
				NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "variable packet size minimum guarantee. header(%d) packetSize(%d) min(%d)", Header, size, fpRet.second);
				C2InterServerClient::GetObj()->C2Client::AddDisconnectReqCnt(__FILE__, __LINE__);
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
			C2InterServerClient::GetObj()->C2Client::AddDisconnectReqCnt(__FILE__, __LINE__);
			return 0;
		}

		if( RecvQueueSize < size )
			return -1;

		int ret = this->DispatchPacket(Header, size);
		if( ret != -1 )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "InterServer DispatchPacket error- %d  Header:%d FreeSize=%d QueueSize:%d", size, Header, m_recvQueue->CPacketQueue::GetFreeSize(), m_recvQueue->CPacketQueue::GetSize());
			return ret;
		}

		m_LastPacketRecvTM = timeGetTime();
		m_OldHeader = Header;
		m_OldPacketSize = size;
	}

	return -1;
}


void C2InterServerClientPacketHandler::OnIZ_PING_LIVE(const PACKET_IZ_PING_LIVE& in_packet)
{
}


void C2InterServerClientPacketHandler::OnIZ_OTHER_ZONE_PC_SEND_MSG(const PACKET_IZ_OTHER_ZONE_PC_SEND_MSG& in_packet)
{
}


void C2InterServerClientPacketHandler::OnIZ_INSTANTMAP_ADD3(const PACKET_IZ_INSTANTMAP_ADD3& in_packet)
{
	CInstantMapMgr::GetObj()->CInstantMapMgr::Add(in_packet.ZSID, in_packet.mapName, in_packet.mapID, in_packet.mapType, in_packet.bPlayerEnter);
}


void C2InterServerClientPacketHandler::OnIZ_INSTANTMAP_REMOVE3(const PACKET_IZ_INSTANTMAP_REMOVE3& in_packet)
{
	CInstantMapMgr::GetObj()->CInstantMapMgr::Remove(in_packet.ZSID, in_packet.mapName, in_packet.mapID);
}


void C2InterServerClientPacketHandler::OnIZ_INSTANTMAP_PLAYER_ENTER3(const PACKET_IZ_INSTANTMAP_PLAYER_ENTER3& in_packet)
{
	CInstantMapMgr::GetObj()->CInstantMapMgr::SetPlayerEnter(in_packet.mapID, in_packet.bPlayerEnter);
}


void C2InterServerClientPacketHandler::OnIZ_RELAY_NOTIFY(const int packetSize, const char* buf)
{
}


int C2InterServerClientPacketHandler::DispatchPacket(short Header, int packetSize)
{
	switch( Header )
	{
	case HEADER_IZ_PING_LIVE:
	{
		PACKET_IZ_PING_LIVE packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->C2InterServerClientPacketHandler::OnIZ_PING_LIVE(packet);
	}
	break;
	case HEADER_IZ_OTHER_ZONE_PC_SEND_MSG:
	{
		PACKET_IZ_OTHER_ZONE_PC_SEND_MSG packet = {};
		m_recvQueue->CPacketQueue::GetData(packetSize, (char*)&packet);
		this->C2InterServerClientPacketHandler::OnIZ_OTHER_ZONE_PC_SEND_MSG(packet);
	}
	break;
	case HEADER_IZ_INSTANTMAP_ADD3:
	{
		PACKET_IZ_INSTANTMAP_ADD3 packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->C2InterServerClientPacketHandler::OnIZ_INSTANTMAP_ADD3(packet);
	}
	break;
	case HEADER_IZ_INSTANTMAP_REMOVE3:
	{
		PACKET_IZ_INSTANTMAP_REMOVE3 packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->C2InterServerClientPacketHandler::OnIZ_INSTANTMAP_REMOVE3(packet);
	}
	break;
	case HEADER_IZ_INSTANTMAP_PLAYER_ENTER3:
	{
		PACKET_IZ_INSTANTMAP_PLAYER_ENTER3 packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->C2InterServerClientPacketHandler::OnIZ_INSTANTMAP_PLAYER_ENTER3(packet);
	}
	break;
	case HEADER_IZ_RELAY_NOTIFY:
	{
		PACKET_IZ_RELAY_NOTIFY* pIZ_RELAY_NOTIFY = (PACKET_IZ_RELAY_NOTIFY*)_malloca(packetSize);
		if( pIZ_RELAY_NOTIFY == NULL )
			break;
		m_recvQueue->CPacketQueue::GetData(packetSize, (char*)pIZ_RELAY_NOTIFY);
		this->C2InterServerClientPacketHandler::OnIZ_RELAY_NOTIFY(packetSize, (char*)pIZ_RELAY_NOTIFY);
		_freea(pIZ_RELAY_NOTIFY);
	}
	break;
	default:
	{
		return this->CISvrIOPacketHandler::DispatchPacket(Header, packetSize);
	}
	break;
	};

	return -1;
}
