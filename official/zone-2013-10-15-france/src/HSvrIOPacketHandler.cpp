#include "HSvrIOPacketHandler.h"
#include "ZoneProcess.h"
#include "ZSAcceptHandler.h"
#include "Client/CharacterServerClient/C2CharacterServerClient.h"
#include "Client/InterServerClient/C2InterServerClient.h"
#include "Common/Packet.h"
#include "Common/PacketLengthExMgr.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/ServerInfo.h"


CHSvrIOPacketHandler::CHSvrIOPacketHandler()
{
	m_OverPopulationCheckTM = timeGetTime();
	m_bOverPopulation = false;
}


CHSvrIOPacketHandler::~CHSvrIOPacketHandler()
{
}


int CHSvrIOPacketHandler::OnProcess()
{
	int count = 0;
	while( 1 )
	{
		if( m_recvQueue->CPacketQueue::GetSize() < 4 ) //FIXME
			return -1;
		
		++count;
		if( count >= 70 )
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

		if( size == 0 || size >= 2048 )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "OnProcess PacketSize error %d", size);
			return 0;
		}

		if( m_recvQueue->CPacketQueue::GetSize() >= size )
		{
			int Type = this->DispatchPacket(Header, size);
			if( Type != -1 )
				return Type;
		}
	}
}


void CHSvrIOPacketHandler::OnXX_CONNECT()
{
	C2CharacterServerClient::GetObj()->C2CharacterServerClient::SetAuth(false);

	BOOL bAcceptable = ( C2CharacterServerClient::GetObj()->C2CharacterServerClient::isAuth() && C2InterServerClient::GetObj()->C2InterServerClient::isAuth() );
	g_zsAcceptHandler.CZSAcceptHandler::SetAccpetable(bAcceptable);

	PACKET_ZH_AUTH_REQ packet;
	packet.PacketType = HEADER_ZH_AUTH_REQ;
	packet.dwIP = g_serverInfo.CServerInfo::GetLocalIP();
	packet.sPort = g_serverInfo.CServerInfo::GetLocalPort();
	packet.ZSID = g_serverInfo.CServerInfo::GetLocalServerID();
	C2CharacterServerClient::GetObj()->C2CharacterServerClient::Send(sizeof(packet), (char*)&packet);
}


hook_func<int (CHSvrIOPacketHandler::*)(short Header, int packetSize)> CHSvrIOPacketHandler__DispatchPacket(EXEPATH(), "CHSvrIOPacketHandler::DispatchPacket");
int CHSvrIOPacketHandler::DispatchPacket(short Header, int packetSize)
{
	return (this->*CHSvrIOPacketHandler__DispatchPacket)(Header, packetSize);
	//TODO
}
