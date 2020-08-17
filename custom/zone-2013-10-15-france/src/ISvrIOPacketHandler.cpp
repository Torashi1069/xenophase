#include "ISvrIOPacketHandler.h"
#include "ZoneProcess.h"
#include "ZSAcceptHandler.h"
#include "Client/CharacterServerClient/C2CharacterServerClient.h"
#include "Client/InterServerClient/C2InterServerClient.h"
#include "Common/Packet.h"
#include "Common/PacketLengthExMgr.h"
#include "Instant map/InstantMapConfiguration.h"
#include "Instant map/InstantMapLib.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/NOutputTextMgr.h"
#include "shared/ServerInfo.h"


CISvrIOPacketHandler::CISvrIOPacketHandler()
: m_OldHeader(0), m_lastError(0), m_OldPacketSize(0)
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


void Send_PACKET_ZI_PARTY_JOIN_REQ_ACK(unsigned long in_TargetAID, unsigned long in_GRID, PACKET_ZC_PARTY_JOIN_REQ_ACK::enumAnswer in_answer)
{
	PACKET_ZI_PARTY_JOIN_REQ_ACK packet;
	packet.PacketType = HEADER_ZI_PARTY_JOIN_REQ_ACK;
	packet.targetAID = in_TargetAID;
	packet.GRID = in_GRID;
	packet.answer = in_answer;
	C2InterServerClient::GetObj()->C2InterServerClient::Send(sizeof(packet), (char*)&packet);
}


int CISvrIOPacketHandler::DispatchPacket(short Header, int packetSize)
{
	return 0;
	//TODO
}
