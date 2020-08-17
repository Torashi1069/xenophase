#include "Account.h"
#include "CharacterServerInfo.h"
#include "UserCounter.h"
#include "WUCSPacket.h"
#include "WUCSSvrProcess.h"
#include "Common/Reporter.h"
#include "Network2/Stream.h"
#include "Enums.h"


CWUCSSvrClient::CWUCSSvrClient()
{
}


CWUCSSvrClient::~CWUCSSvrClient()
{
}


bool CWUCSSvrClient::OnConnect()
{
	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("WUCS Server Connected\n");
	CSingleton<CReporter>::getSingletonPtr()->CReporter::MessagePrint("WUCS Server Connected\n");

	PACKET_AW_REQ_CONNECT packet;
	packet.PacketType = HEADER_AW_REQ_CONNECT;
	packet.nCountryNUm = 14;
	packet.nServerNum = CSingleton<CUserCounter>::getSingletonPtr()->CUserCounter::GetServerNumber();
	strcpy(packet.szAccountName, CSingleton<CUserCounter>::getSingletonPtr()->CUserCounter::GetServerName());

	int iCharacterCount;
	SERVER_ADDR* info = g_characterServerInfo[CLIENTTYPE_ENGLISH].CCharacterServerInfo::GetCharacterServerInfo(&iCharacterCount);

	char charSvrNameBuf[720];
	int size = 0;

	for( int nIndex = 0; nIndex < iCharacterCount; ++nIndex )
	{
		const char* name = (const char*)info[nIndex].name;
		int len = strlen(name);

		charSvrNameBuf[size+0] = len + 1;
		strncpy(&charSvrNameBuf[size+1], name, len + 1);

		size += len + 2;
	}

	packet.dwPacketSize = sizeof(packet) + size;
	packet.nCharSvrCount = iCharacterCount;
	m_nCharSvrCount = iCharacterCount;

	this->Send((char*)&packet, sizeof(packet), m_pStream->CStream::GetSessionID(), false);
	if( size != 0 )
		this->Send(charSvrNameBuf, size, m_pStream->CStream::GetSessionID(), false);

	CSingleton<CUserCounter>::getSingletonPtr()->CUserCounter::SetProcess(this);
	return true;
}


void CWUCSSvrClient::OnClose()
{
}


bool CWUCSSvrClient::Process()
{
	int nCursor = 0;
	int nTotalLen = m_pStream->m_RecvQueue.CCircleQueue::GetDataLength();
	DWORD dwSessionID = m_pStream->CStream::GetSessionID();

	for( int cnt = 1; cnt < 100; ++cnt )
	{
		if( dwSessionID != m_pStream->CStream::GetSessionID() )
		{
			CSingleton<CReporter>::getSingletonPtr()->CReporter::MessagePrint("dwSessionID != m_pStream->GetSessionID()\n");
			return true;
		}

		if( nCursor >= nTotalLen || nTotalLen - nCursor < 2 )
			return true;

		WORD wPacketType = 0;
		if( !m_pStream->m_RecvQueue.CCircleQueue::Peek(&wPacketType, 2) )
			return true;

		WORD wPacketLen = this->CWUCSSvrClient::GetPacketSize(wPacketType);
		if( wPacketLen == 0 )
			return false;

		if( wPacketLen == -1 )
		{
			DWORD dwHeader = 0;
			if( !m_pStream->m_RecvQueue.CCircleQueue::Peek(&dwHeader, 4) )
				return true;

			wPacketLen = dwHeader >> 16;
		}

		char PacketBuffer[2048];
		if( wPacketLen > sizeof(PacketBuffer) )
			return false;

		if( !m_pStream->m_RecvQueue.CCircleQueue::Get(PacketBuffer, wPacketLen) )
			return true;

		nCursor += wPacketLen;

		if( !this->CWUCSSvrClient::ProcessPacket(wPacketType, wPacketLen, PacketBuffer) )
		{
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("Header not found, recv from WUCSvr %d\n", wPacketType);
			return false;
		}
	}

	return true;
}


int CWUCSSvrClient::GetPacketSize(unsigned short wPacketType)
{
	std::map<int,int>::const_iterator it = g_WUCSpacketLenMap.find(wPacketType);
	return ( it != g_WUCSpacketLenMap.end() ) ? it->second : 0;
}


bool CWUCSSvrClient::ProcessPacket(unsigned short wPacketType, unsigned short wPacketSize, char* pPacket)
{
	switch( wPacketType )
	{
	case HEADER_WA_RECV_COUNT_INFO_SUCCESS:
		break;
	case HEADER_WA_RECV_CHECK_LINE:
		this->CWUCSSvrClient::ProcessPacket_RecvCheckLine(wPacketType, wPacketSize, pPacket);
		break;
	default:
		return false;
	}

	return true;
}


bool CWUCSSvrClient::ProcessPacket_RecvCheckLine(unsigned short wPacketType, unsigned short wPacketSize, char* pPacket)
{
	PACKET_WA_RECV_CHECK_LINE& inpacket = *reinterpret_cast<PACKET_WA_RECV_CHECK_LINE*>(pPacket);
	PACKET_AW_COMPLETE_CHECK outpacket;
	outpacket.PacketType = HEADER_AW_COMPLETE_CHECK;
	outpacket.packetNum = inpacket.packetNum;
	outpacket.allTime = timeGetTime() - inpacket.dwSendTime;
	outpacket.dwRecvTime = inpacket.dwRecvTime;
	this->Send((char*)&outpacket, sizeof(outpacket), m_pStream->CStream::GetSessionID(), false);

	return true;
}


bool CWUCSSvrClient::SendAccUserCounter(unsigned long counter, const char* date, const char* time)
{
	PACKET_AW_SEND_ACC_SVR_USERCOUNT packet;
	packet.PacketType = HEADER_AW_SEND_ACC_SVR_USERCOUNT;
	packet.dwUser = counter;
	packet.nCharSvrCount = this->m_nCharSvrCount;
	strcpy(packet.szDate, date);
	strcpy(packet.szTime, time);
	this->Send((char*)&packet, sizeof(packet), m_pStream->CStream::GetSessionID(), false);

	return true;
}


bool CWUCSSvrClient::SendCharUserCounter(DWORD* userCounter)
{
	PACKET_AW_SEND_CHAR_SVR_USERCOUNT packet;
	packet.PacketType = HEADER_AW_SEND_CHAR_SVR_USERCOUNT;
	packet.dwPacketSize = static_cast<short>(sizeof(PACKET_AW_SEND_CHAR_SVR_USERCOUNT) + m_nCharSvrCount * sizeof(DWORD));

	this->Send((char*)&packet, sizeof(packet), m_pStream->CStream::GetSessionID(), false);
	this->Send((char*)userCounter, m_nCharSvrCount * sizeof(DWORD), m_pStream->CStream::GetSessionID(), false);

	return true;
}
