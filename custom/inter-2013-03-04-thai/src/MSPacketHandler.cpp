#include "IGuildMgr.h"
#include "InterServer.h"
#include "MServer.h"
#include "MServerLog.h"
#include "MSPacketHandler.h"
#include "ServerExpInfoMgr.h"
#include "Common/Packet.h"
#include "Common/PacketLengthExMgr.h"
#include "NetLib/AsyncStream.h"
#include "NetLib/PacketQueue.h"
#include "Zsvr/CZsvrMgr.h"
#include "shared/ErrorLog.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/ServerInfo.h"
#include "shared/NSystem/NIPAddr.h"


CMCPacketHandler::CMCPacketHandler()
{
}


CMCPacketHandler::~CMCPacketHandler()
{
}


void CMCPacketHandler::SetMyOwner(CMClient* mServer)
{
	this->OldHeader = 0;
	m_mServer = mServer;
}


void CMCPacketHandler::OnClose()
{
	m_mServer->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
}


int CMCPacketHandler::OnProcess()
{
	int count = 0;
	while( 1 )
	{
		if( m_recvQueue->CPacketQueue::GetSize() < sizeof(PACKET) )
			return -1;

		++count;
		if( count >= 40 )
			return -1;

		short Header = 0;
		m_recvQueue->CPacketQueue::PeekData(sizeof(Header), (char*)&Header);

		std::pair<CPacketLengthExMgr::enumFixedPacketRet,int> fpRet = g_packetLenMapEx.CPacketLengthExMgr::IsFixedPacket(Header);

		int size;
		if( fpRet.first == CPacketLengthExMgr::FIXED )
		{
			size = fpRet.second;
		}
		else
		if( fpRet.first == CPacketLengthExMgr::VARIABLE )
		{
			if( m_recvQueue->CPacketQueue::GetSize() < sizeof(PACKETV) )
				return -1;

			int Header2 = 0;
			m_recvQueue->CPacketQueue::PeekData(sizeof(Header2), (char*)&Header2);

			size = Header2 >> 16;
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

		if( size == 0 || size > 2000 )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "packetsize:%d Freesize:%d , Size:%d, header:%d, Oldheader:%d", size, m_recvQueue->CPacketQueue::GetFreeSize(), m_recvQueue->CPacketQueue::GetSize(), Header, this->OldHeader);
			return 0;
		}

		if( size > m_recvQueue->CPacketQueue::GetSize() )
			continue;

		int result = this->CMCPacketHandler::DispatchPacket(Header, size);
		if( result != -1 )
			return result;

		this->OldHeader = Header;
	}
}


int CMCPacketHandler::DispatchPacket(short Header, int packetSize)
{
	switch( Header )
	{
	case HEADER_MI_ENTER:
		this->CMCPacketHandler::OnMIEnter(packetSize);
	break;
	case HEADER_MI_REQ_SERVERSTATE:
		this->CMCPacketHandler::OnMIReqServerState(packetSize);
	break;
	case HEADER_MI_MSG:
	{
		std::vector<char> buffer(packetSize);
		PACKET_MI_MSG* packet = reinterpret_cast<PACKET_MI_MSG*>(&buffer.front());
		m_recvQueue->CPacketQueue::GetData(packetSize, (char*)packet);
		this->CMCPacketHandler::OnMI_MSG(packet);
	}
	break;
	case HEADER_MI_SHOTDOWN:
		this->CMCPacketHandler::OnMIShotDown(packetSize);
	break;
	case HEADER_MI_GET_GUILD_INFO:
		this->CMCPacketHandler::OnMIGetGuildInfo(packetSize);
	break;
	case HEADER_MI_GUILD_INFO_INIT:
		this->CMCPacketHandler::OnMIGuildInfoInit(packetSize);
	break;
	case HEADER_MI_ALLY_GUILD_INIT:
		this->CMCPacketHandler::OnMIAllyGuildInfoInit(packetSize);
	break;
	case HEADER_CONNECTION_CLOSED:
		return 0;
	break;
	case HEADER_MI_REQ_EDIT_EXP:
	{
		PACKET_MI_REQ_EDIT_EXP packet = {};
		m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);
		this->CMCPacketHandler::OnMI_REQ_EDIT_EXP(packet);
	}
	break;
	default:
		m_mServer->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Unknown Manager packetsize:%d Freesize:%d , Size:%d, header:%d", packetSize, m_recvQueue->CPacketQueue::GetFreeSize(), m_recvQueue->CPacketQueue::GetSize(), Header);
		return 0;
	break;
	};

	return -1;
}


void CMCPacketHandler::OnMIEnter(int len)
{
	PACKET_MI_ENTER packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	if( m_mServer->CMClient::CheckPasswd(packet.ID, packet.Password) )
	{
		m_mServer->CMClient::SetValid(TRUE);

		int len;
		char buf[256];
		g_serverInfo.CServerInfo::GetZServerIDList(g_serverInfo.CServerInfo::GetLocalServerID(), len, buf, sizeof(buf));

		PACKET_IM_SERVERLIST outpacket;
		outpacket.PacketType = HEADER_IM_SERVERLIST;
		outpacket.PacketLength = sizeof(outpacket) + len;
		m_mServer->Send(sizeof(outpacket), (char*)&outpacket);
		m_mServer->Send(len, buf);
	}
	else
	{
		PACKET_IM_CONTROLFAIL outpacket;
		outpacket.PacketType = HEADER_IM_CONTROLFAIL;
		outpacket.errorCode = 0;
		m_mServer->Send(sizeof(outpacket), (char*)&outpacket);

		m_mServer->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
	}

	PACKET_IM_ACK_EDIT_EXP out_packet = {};
	out_packet.PacketType = HEADER_IM_ACK_EDIT_EXP;
	out_packet.Result = PACKET_IM_ACK_EDIT_EXP::RESULT_SUCCESS;
	out_packet.Exp = CServerExpInfoMgr::GetObj()->CServerExpInfoMgr::GetExp();
	out_packet.Death = CServerExpInfoMgr::GetObj()->CServerExpInfoMgr::GetDeath();
	out_packet.Drop = CServerExpInfoMgr::GetObj()->CServerExpInfoMgr::GetDrop();
	m_mServer->Send(sizeof(out_packet), (char*)&out_packet);
}


void CMCPacketHandler::OnMIReqServerState(int len)
{
	m_mServer->CMClient::SetLastCommunicationTime(timeGetTime());

	PACKET_MI_REQ_SERVERSTATE packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	if( !m_mServer->CMClient::IsValid() )
	{
		m_mServer->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		return;
	}

	if( !CZsvrMgr::GetObj()->CZServerMgr::IsConnectedServer(packet.serverID) )
	{
		PACKET_IM_SERVERSTATE opacket;
		opacket.PacketType = HEADER_IM_SERVERSTATE;
		opacket.serverState.serverID = packet.serverID;
		opacket.serverState.packetNumber = packet.packetNumber;
		opacket.serverState.userCounter = 0;
		opacket.serverState.loopcountPerSec = -1;
		m_mServer->Send(sizeof(opacket), (char*)&opacket);
		return;
	}

	PACKET_IZ_REQ_SERVERSTATE outpacket;
	outpacket.PacketType = HEADER_IZ_REQ_SERVERSTATE;
	outpacket.packetNumber = packet.packetNumber;
	outpacket.monitorNum = m_mServer->CMClient::GetServerID();
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(packet.serverID, sizeof(outpacket), (char*)&outpacket);
}


void CMCPacketHandler::OnMI_MSG(const PACKET_MI_MSG* in_pPacket)
{
	int TextLen = in_pPacket->PacketLength - sizeof(*in_pPacket);
	if( TextLen < 9 || TextLen > 520 )
	{
		m_mServer->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		return;
	}

	std::vector<char> packet(sizeof(PACKET_IZ_BROADCAST));
	PACKET_IZ_BROADCAST& IZPacket = *reinterpret_cast<PACKET_IZ_BROADCAST*>(&packet.front());
	IZPacket.PacketType = HEADER_IZ_BROADCAST;
	IZPacket.PacketLen = sizeof(IZPacket) + TextLen;
	packet.insert(packet.end(), &in_pPacket->Text[0], &in_pPacket->Text[TextLen]);
	IZPacket.Text[TextLen-1] = '\0';
	CZsvrMgr::GetObj()->CZServerMgr::BroadCast(packet.size(), &packet.front());
}


void CMCPacketHandler::OnMIShotDown(int len)
{
	DWORD IP = m_mServer->CMClient::GetAsyncStream()->CAsyncStream::GetIP();

	BYTE abIp[4];
	memcpy(abIp, &IP, sizeof(abIp));

	char szIP[80];
	sprintf(szIP, "%d.%d.%d.%d", abIp[0], abIp[1], abIp[2], abIp[3]);
	g_errorLogs.CErrorLog::KillAllLog(szIP);

	PACKET_MI_SHOTDOWN packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	CIGuildMgr::GetObj()->CIGuildMgr::GuildAllSave();
	if( !m_mServer->CMClient::CheckPasswd(m_mServer->CMClient::GetID(), packet.password) )
		return; // auth rejected

	PACKET_IZ_DISCONNECT_ALL outpacket;
	outpacket.PacketType = HEADER_IZ_DISCONNECT_ALL;
	CZsvrMgr::GetObj()->CZServerMgr::BroadCast(sizeof(outpacket), (char*)&outpacket);
}


void CMCPacketHandler::OnMIGetGuildInfo(int len)
{
	PACKET_MI_GET_GUILD_INFO packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	PACKET_IM_REQ_GUILD_INFO ReqGuildInfo;
	CIGuildMgr::GetObj()->CIGuildMgr::GetGuildInfo(packet.GuildID, &ReqGuildInfo);
	m_mServer->Send(sizeof(ReqGuildInfo), (char*)&ReqGuildInfo);
}


void CMCPacketHandler::OnMIGuildInfoInit(int len)
{
	PACKET_MI_GUILD_INFO_INIT packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	PACKET_IM_RESULT_GUILD_INFO_INIT ResultGuildInfoInit;
	ResultGuildInfoInit.PacketType = HEADER_IM_RESULT_GUILD_INFO_INIT;
	ResultGuildInfoInit.Result = CIGuildMgr::GetObj()->CIGuildMgr::GuildInfoInit(packet.GuildID);
	m_mServer->Send(sizeof(ResultGuildInfoInit), (char*)&ResultGuildInfoInit);
}


void CMCPacketHandler::OnMIAllyGuildInfoInit(int len)
{
	PACKET_MI_ALLY_GUILD_INIT packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	PACKET_IM_REQ_ALLY_GUILD_INIT ReqAllyGuildInit;
	ReqAllyGuildInit.PacketType = HEADER_IM_REQ_ALLY_GUILD_INIT;
	ReqAllyGuildInit.Result = CIGuildMgr::GetObj()->CIGuildMgr::AllyGuildInfoInit(packet.GuildID);
	m_mServer->Send(sizeof(ReqAllyGuildInit), (char*)&ReqAllyGuildInit);
}


void CMCPacketHandler::OnMI_REQ_EDIT_EXP(const PACKET_MI_REQ_EDIT_EXP& in_packet)
{
	CMServerLog::GetObj()->CMServerLog::LogFmt("[EDD] %s request exp:%d death:%d drop:%d", NIPAddapter(NIPAddr(m_mServer->CMClient::GetIPaddr())), in_packet.Exp, in_packet.Death, in_packet.Drop);

	if( !CServerExpInfoMgr::GetObj()->CServerExpInfoMgr::IsAuthenticate(in_packet.ID, in_packet.Passwd) )
	{
		CMServerLog::GetObj()->CMServerLog::LogFmt("[EDD] %s auth fail", NIPAddapter(NIPAddr(m_mServer->CMClient::GetIPaddr())));

		PACKET_IM_ACK_EDIT_EXP out_packet = {};
		out_packet.PacketType = HEADER_IM_ACK_EDIT_EXP;
		out_packet.Result = PACKET_IM_ACK_EDIT_EXP::RESULT_FAIL_AUTH;
		m_mServer->Send(sizeof(out_packet), (char*)&out_packet);

		return;
	}

	if( !CServerExpInfoMgr::GetObj()->CServerExpInfoMgr::SetServerEXPInfo(in_packet.Exp, in_packet.Death, in_packet.Drop) )
	{
		CMServerLog::GetObj()->CMServerLog::LogFmt("[EDD] %s restrict", NIPAddapter(NIPAddr(m_mServer->CMClient::GetIPaddr())));

		PACKET_IM_ACK_EDIT_EXP out_packet = {};
		out_packet.PacketType = HEADER_IM_ACK_EDIT_EXP;
		out_packet.Result = PACKET_IM_ACK_EDIT_EXP::RESULT_FAIL_RESTRICT;
		m_mServer->Send(sizeof(out_packet), (char*)&out_packet);

		return;
	}

	CMServerLog::GetObj()->CMServerLog::LogFmt("[EDD] %s complete exp:%d death:%d drop:%d", NIPAddapter(NIPAddr(m_mServer->CMClient::GetIPaddr())), CServerExpInfoMgr::GetObj()->CServerExpInfoMgr::GetExp(), CServerExpInfoMgr::GetObj()->CServerExpInfoMgr::GetDeath(), CServerExpInfoMgr::GetObj()->CServerExpInfoMgr::GetDrop());

	CServerExpInfoMgr::GetObj()->CServerExpInfoMgr::CreateServerEXPFile(CServerExpInfoMgr::GetObj()->CServerExpInfoMgr::GetExp(), CServerExpInfoMgr::GetObj()->CServerExpInfoMgr::GetDeath(), CServerExpInfoMgr::GetObj()->CServerExpInfoMgr::GetDrop());

	PACKET_IM_ACK_EDIT_EXP out_packet = {};
	out_packet.PacketType = HEADER_IM_ACK_EDIT_EXP;
	out_packet.Result = PACKET_IM_ACK_EDIT_EXP::RESULT_SUCCESS;
	out_packet.Exp = CServerExpInfoMgr::GetObj()->CServerExpInfoMgr::GetExp();
	out_packet.Death = CServerExpInfoMgr::GetObj()->CServerExpInfoMgr::GetDeath();
	out_packet.Drop = CServerExpInfoMgr::GetObj()->CServerExpInfoMgr::GetDrop();
	m_mServer->Send(sizeof(out_packet), (char*)&out_packet);

	PACKET_IZ_REQ_EDIT_EXP out_packet_ = {};
	out_packet_.PacketType = HEADER_IZ_REQ_EDIT_EXP;
	out_packet_.monitornum = m_mServer->CMClient::GetServerID();
	CZsvrMgr::GetObj()->CZServerMgr::BroadCast(sizeof(out_packet_), (char*)&out_packet_);
}
