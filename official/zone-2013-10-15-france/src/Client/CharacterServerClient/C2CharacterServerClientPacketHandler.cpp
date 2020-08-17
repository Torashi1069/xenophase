#include "Client/CharacterServerClient/C2CharacterServerClient.h"
#include "Client/CharacterServerClient/C2CharacterServerClientPacketHandler.h"
#include "Common/Packet.h"
#include "Common/PacketLengthExMgr.h"
#include "shared/NCriticalErrorLog.h"


C2CharacterServerClientPacketHandler::C2CharacterServerClientPacketHandler()
{
	m_dwLastRecvPacketTM = timeGetTime();
}


C2CharacterServerClientPacketHandler::~C2CharacterServerClientPacketHandler()
{
}


DWORD C2CharacterServerClientPacketHandler::GetLastPacketRecvTM()
{
	return m_dwLastRecvPacketTM;
}


void C2CharacterServerClientPacketHandler::SetLastPacketRecvTM(const DWORD in_LastPacketRecvTM)
{
	m_dwLastRecvPacketTM = in_LastPacketRecvTM;
}


void C2CharacterServerClientPacketHandler::OnClose()
{
}


int C2CharacterServerClientPacketHandler::OnProcess()
{
	static int oldHeader;
	static int oldLen;

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
				C2CharacterServerClient::GetObj()->AddDisconnectReqCnt(__FILE__, __LINE__);
				return 0;
			}
		}
		else
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "unknown packet receive header(%d) oldHeader(%d) oldLen(%d)", Header, oldHeader, oldLen);
			return 0;
		}

		if( size == 0 || size >= 2048 )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "OnProcess PacketSize error %d", size);
			C2CharacterServerClient::GetObj()->AddDisconnectReqCnt(__FILE__, __LINE__);
			return 0;
		}

		if( RecvQueueSize < size )
			return -1;

		if( m_recvQueue->CPacketQueue::GetSize() >= size )
		{
			oldHeader = Header;
			oldLen = size;

			int ret = this->DispatchPacket(Header, size);
			if( ret != -1 )
			{
				NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "InterServer DispatchPacket error- %d  Header:%d FreeSize=%d QueueSize:%d", size, Header, m_recvQueue->CPacketQueue::GetFreeSize(), m_recvQueue->CPacketQueue::GetSize());
				return ret;
			}
		}

		m_dwLastRecvPacketTM = timeGetTime();
	}

	return -1;
}


void C2CharacterServerClientPacketHandler::OnHZ_PING_LIVE(PACKET_HZ_PING_LIVE& in_packet)
{
}


void C2CharacterServerClientPacketHandler::OnHZ_LOGON_KOR(const PACKET_HZ_LOGON_KOR& in_packet)
{
}


void C2CharacterServerClientPacketHandler::OnHZ_PERSONAL_INFORMATION_PHL(const PACKET_HZ_PERSONAL_INFORMATION_PHL* in_packet)
{
}


void C2CharacterServerClientPacketHandler::OnHZ_PERSONAL_INFORMATION_THAI(const PACKET_HZ_PERSONAL_INFORMATION_THAI* in_packet)
{
}


void C2CharacterServerClientPacketHandler::OnHZ_PERSONAL_INFORMATION_TW(const PACKET_HZ_PERSONAL_INFORMATION_TW* in_packet)
{
}


void C2CharacterServerClientPacketHandler::OnHZ_LOGON_INDONESIA(const PACKET_HZ_LOGON_INDONESIA& in_packet)
{
}


void C2CharacterServerClientPacketHandler::OnHZ_PERSONAL_INFORMATION_INDONESIA(const char* buf)
{
}


int C2CharacterServerClientPacketHandler::DispatchPacket(short in_nHeader, int in_nPacketSize)
{
	switch( in_nHeader )
	{
	case HEADER_HZ_PERSONAL_INFORMATION_INDONESIA:
	{
		PACKET_HZ_PERSONAL_INFORMATION_INDONESIA* pHZ_PERSONAL_INFORMATION_INDONESIA = (PACKET_HZ_PERSONAL_INFORMATION_INDONESIA*)_malloca(in_nPacketSize);
		if( pHZ_PERSONAL_INFORMATION_INDONESIA != NULL )
		{
			m_recvQueue->CPacketQueue::GetData(in_nPacketSize, (char*)pHZ_PERSONAL_INFORMATION_INDONESIA);
			this->C2CharacterServerClientPacketHandler::OnHZ_PERSONAL_INFORMATION_INDONESIA((char*)pHZ_PERSONAL_INFORMATION_INDONESIA);
			_freea(pHZ_PERSONAL_INFORMATION_INDONESIA);
		}
	}
//	break; //FIXME: missing break causes unintended fall-through
	case HEADER_HZ_LOGON_INDONESIA:
	{
		PACKET_HZ_LOGON_INDONESIA packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->C2CharacterServerClientPacketHandler::OnHZ_LOGON_INDONESIA(packet);
	}
	break;
	case HEADER_HZ_PING_LIVE:
	{
		PACKET_HZ_PING_LIVE packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->C2CharacterServerClientPacketHandler::OnHZ_PING_LIVE(packet);
	}
	break;
	case HEADER_HZ_LOGON_KOR:
	{
		PACKET_HZ_LOGON_KOR packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->C2CharacterServerClientPacketHandler::OnHZ_LOGON_KOR(packet);
	}
	break;
	case HEADER_HZ_PERSONAL_INFORMATION_PHL:
	{
		std::vector<char> packetbuffer(in_nPacketSize);
		PACKET_HZ_PERSONAL_INFORMATION_PHL* packet = reinterpret_cast<PACKET_HZ_PERSONAL_INFORMATION_PHL*>(&packetbuffer.front());
		m_recvQueue->CPacketQueue::GetData(in_nPacketSize, (char*)packet);
		this->C2CharacterServerClientPacketHandler::OnHZ_PERSONAL_INFORMATION_PHL(packet);
	}
	break;
	case HEADER_HZ_PERSONAL_INFORMATION_THAI:
	{
		std::vector<char> packetbuffer(in_nPacketSize);
		PACKET_HZ_PERSONAL_INFORMATION_THAI* packet = reinterpret_cast<PACKET_HZ_PERSONAL_INFORMATION_THAI*>(&packetbuffer.front());
		m_recvQueue->CPacketQueue::GetData(in_nPacketSize, (char*)packet);
		this->C2CharacterServerClientPacketHandler::OnHZ_PERSONAL_INFORMATION_THAI(packet);
	}
	break;
	case HEADER_HZ_PERSONAL_INFORMATION_TW:
	{
		PACKET_HZ_PERSONAL_INFORMATION_TW* pHZ_PERSONAL_INFORMATION_TW = (PACKET_HZ_PERSONAL_INFORMATION_TW*)_malloca(in_nPacketSize);
		if( pHZ_PERSONAL_INFORMATION_TW != NULL )
		{
			m_recvQueue->CPacketQueue::GetData(in_nPacketSize, (char*)pHZ_PERSONAL_INFORMATION_TW);
			this->C2CharacterServerClientPacketHandler::OnHZ_PERSONAL_INFORMATION_TW(pHZ_PERSONAL_INFORMATION_TW);
			_freea(pHZ_PERSONAL_INFORMATION_TW);
		}
	}

	default:
		return this->CHSvrIOPacketHandler::DispatchPacket(in_nHeader, in_nPacketSize);
	break;
	};

	return -1;
}
