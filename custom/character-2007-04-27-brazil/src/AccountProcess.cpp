#include "AccountProcess.h"
#include "Character.h"
#include "UserAuthenticate.h"
#include "UserList.h"
#include "UserProcess.h"
#include "UserVerify.h"
#include "Common/Network.h"
#include "Common/Packet.h"
#include "Common/Reporter.h"
#include "Common/ServerInfoList.h"
#include "Network3/AsyncProcessMgr.h"
#include "Network3/Stream.h"
#include "Network3/StreamManager.h"
#include "enum.hpp"


CAccountProcess::CAccountProcess()
{
}


CAccountProcess::~CAccountProcess()
{
}


bool CAccountProcess::OnConnect()
{
	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("account server connected\n");

	g_bAccountConnected = true;
	return true;
}


void CAccountProcess::OnClose()
{
	g_bAccountConnected = false;

	char szIP[100] = {};
	CSingleton<CNetwork>::getSingletonPtr()->CNetwork::GetTextIP(m_dwIP, szIP);
	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("account server %s disconnected\n", szIP);
}


bool CAccountProcess::OnRecv(char* buffer, int* len)
{
	DWORD dwSessionID = m_pStream->CStream::GetSessionID();
	if( dwSessionID == 0 )
		return false;

	int total_len = *len;
	int processed_len = 0;

	while( processed_len < total_len )
	{
		int remain = total_len - processed_len;
		if( remain < sizeof(PACKET) )
			break; // need more data.

		WORD wPacketType = reinterpret_cast<PACKET*>(buffer)->PacketType;
		int nPacketSize = this->CAccountProcess::GetPacketSize(wPacketType);

		if( nPacketSize == 0 )
		{
			char szIP[100] = {};
			CSingleton<CNetwork>::getSingletonPtr()->CNetwork::GetTextIP(m_dwIP, szIP);
			CSingleton<CReporter>::getSingletonPtr()->CReporter::MessagePrint("%s - not defined pkt %u from %s ", __FUNCTION__, wPacketType, szIP);
			return false;
		}

		if( nPacketSize == -1 )
		{
			if( remain < sizeof(PACKETV) )
				break; // need more data.

			nPacketSize = reinterpret_cast<PACKETV*>(buffer)->PacketLength;
			if( nPacketSize < sizeof(PACKETV) )
				return false; // invalid data?
		}

		if( nPacketSize > 1024 || nPacketSize < 2 )
			return false; // invalid data?

		if( nPacketSize > remain )
			break; // need more data.

		if( wPacketType == HEADER_AH_LOGON_EXIST
		||  wPacketType == HEADER_AH_LOGON_EXIST_SESSION
		||  wPacketType == HEADER_AH_LOGON_EXIST_PCBANG
		)
		{
			unsigned int pkt_index = 0;
			if( wPacketType == HEADER_AH_LOGON_EXIST )
				pkt_index = reinterpret_cast<PACKET_AH_LOGON_ACK*>(buffer)->AID;
			else
			if( wPacketType == HEADER_AH_LOGON_EXIST_SESSION )
				pkt_index = reinterpret_cast<PACKET_AH_LOGON_ACK_SESSION*>(buffer)->AID;
			else
			if( wPacketType == HEADER_AH_LOGON_EXIST_PCBANG )
				pkt_index = reinterpret_cast<PACKET_AH_LOGON_ACK_PCBANG*>(buffer)->AID;

			ASYNCPACKET* pAsyncPacket = g_AsyncProcessMgr.CAsyncProcessMgr::AllocPacket();
			if( pAsyncPacket != NULL )
			{
				memset(pAsyncPacket, 0, sizeof(*pAsyncPacket));
				pAsyncPacket->dwSessionID = dwSessionID;
				pAsyncPacket->nPacketSize = nPacketSize;
				memcpy(pAsyncPacket->packet, buffer, nPacketSize);
				pAsyncPacket->pProcessPtr = this;
				pAsyncPacket->wPacketType = wPacketType;
				g_AsyncProcessMgr.CAsyncProcessMgr::PushPacket(pAsyncPacket, pkt_index);
			}
			else
			{
				CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("%s - g_AsyncProcessMgr.AllocPacket() failed\n", __FUNCTION__);
			}
		}
		else
		{
			if( !this->ProcessPacket(dwSessionID, buffer, wPacketType, nPacketSize) )
				return false;
		}

		processed_len += nPacketSize;
		buffer += nPacketSize;
	}

	*len = processed_len;
	return true;
}


int CAccountProcess::GetPacketSize(WORD wPacketType)
{
	std::map<int,int>::const_iterator it = g_packetLenMap.find(wPacketType);
	return ( it != g_packetLenMap.end() ) ? it->second : 0;
}


bool CAccountProcess::ProcessPacket(DWORD dwSessionID, char* pPacket, WORD wPacketType, int nPacketSize)
{
	switch( wPacketType )
	{
	case HEADER_AH_LOGON_EXIST:
	case HEADER_AH_LOGON_EXIST_PCBANG:
		return this->CAccountProcess::ProcessPacket_LogonPermit(dwSessionID, pPacket);
	break;
	case HEADER_AH_BILLING_ACK:
		return this->CAccountProcess::ProcessPacket_Billing_Ack(dwSessionID, pPacket);
	break;
	case HEADER_AH_LOGON_NOTEXIST:
		return this->CAccountProcess::ProcessPacket_LogonRefuse(dwSessionID, pPacket);
	break;
	case HEADER_AH_LOGON_EXIST_SESSION:
		return this->CAccountProcess::ProcessPacket_LogonPermit_Session(dwSessionID, pPacket);
	break;
	case HEADER_AH_LOGON_NOTEXIST_SESSION:
		return this->CAccountProcess::ProcessPacket_LogonRefuse_Session(dwSessionID, pPacket);
	break;
	case HEADER_AH_DISCONNECT:
	case HEADER_AH_DISCONNECT_RIGHTNOW:
		return this->CAccountProcess::ProcessPacket_Disconnect(dwSessionID, pPacket);
	break;
	case HEADER_AH_ACK_PACKETINFO:
		return this->CAccountProcess::ProcessPacket_AckPacketInfo(dwSessionID, pPacket);
	break;
	case HEADER_COLLECTORDEAD:
		return this->CAccountProcess::ProcessPacket_CollectDead(dwSessionID, pPacket);
	break;
	case HEADER_AH_INFO_REMAINTIME:
		return this->CAccountProcess::ProcessPacket_Info_Remain_Time(dwSessionID, pPacket);
	break;
	case HEADER_AH_RES_REMAINTIME:
		return this->CAccountProcess::ProcessPacket_res_remain_time(dwSessionID, pPacket);
	break;
	case HEADER_AH_ACK_PLAYING_LIMITINFO:
		return this->CAccountProcess::ProcessPacket_ack_LimitInfo(dwSessionID, pPacket);
	break;
	default:
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("Header not found, sent from Account Server %d\n", wPacketType);
		return false;
	break;
	};
}


bool CAccountProcess::ProcessPacket_Billing_Ack(DWORD dwSessionID, char* pPacket)
{
	PACKET_AH_BILLING_ACK& Packet = *reinterpret_cast<PACKET_AH_BILLING_ACK*>(pPacket);

	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("This Message Never Recv CharSvr Check Account\n");

	return true;
}


bool CAccountProcess::ProcessPacket_LogonPermit(DWORD dwSessionID, char* pPacket)
{
	PACKET_AH_LOGON_ACK& Packet = *reinterpret_cast<PACKET_AH_LOGON_ACK*>(pPacket);

	__SUSERAUTHENTICATE__ userAuthenticate;
	if( !g_UserAuthenticate.CUserAuthenticate::Bring(Packet.AID, &userAuthenticate) )
		return true;

	__SUSER__ user = {};
	if( g_UserList.CUserList::Bring(Packet.AID, &user) )
	{
		PACKET_SC_NOTIFY_BAN sc_notify_ban;
		sc_notify_ban.PacketType = HEADER_SC_NOTIFY_BAN;
		sc_notify_ban.ErrorCode = BAN_ANOTHER_LOGIN;

		if( user.m_pUserProcess != NULL )
		{
			user.m_pUserProcess->m_bAuthenticated = false;
			user.m_pUserProcess->Send((char*)&sc_notify_ban, sizeof(sc_notify_ban), user.m_dwSessionID, false);
			user.m_pUserProcess->CUserProcess::CloseForce(user.m_dwSessionID, 5000);
		}
	}

	PACKET_HZ_DISCONNECT hz_disconnect;
	hz_disconnect.PacketType = HEADER_HZ_DISCONNECT_RIGHTNOW;
	hz_disconnect.AID = Packet.AID;
//	hz_disconnect.reason = ?; //FIXME
	g_ZoneSvrStreamMgr.CStreamManager::Broadcast((char*)&hz_disconnect, sizeof(hz_disconnect));

	memset(&user, 0, sizeof(user));
	user.m_nSID = -1;
	user.m_dwSecurityCode = userAuthenticate.m_dwSecurityCode;
	user.m_pUserProcess = userAuthenticate.m_pUserProcess;
	user.m_dwSessionID = userAuthenticate.m_dwSessionID;
	memcpy(user.m_szPersonalNumber, Packet.PERSONALNUMBER, 24-1);
	memcpy(user.m_szEMail, Packet.emailAddress, 40);
	memcpy(user.m_szID, Packet.ID, 24);
	user.m_dwAID = Packet.AID;

	if( Packet.PacketType == HEADER_AH_LOGON_EXIST_PCBANG )
	{
		PACKET_AH_LOGON_ACK_PCBANG& Packet = *reinterpret_cast<PACKET_AH_LOGON_ACK_PCBANG*>(pPacket);
		user.m_dwIP = Packet.m_dwIP;
		user.m_bIsPCBang = Packet.m_bIsPCBang;
		user.m_nPayTypeEx = Packet.m_nPayTypeEx;
		user.m_nConnectionArea = Packet.m_nConnectionArea;
		user.m_nConnectionState = Packet.m_nConnectionState;
		user.m_nEventNum = Packet.m_nEventNum;
		user.m_dwConnectionTime = Packet.m_dwConnectionTime;
	}

	g_UserList.CUserList::Insert(Packet.AID, user);
	user.m_pUserProcess->CUserProcess::OnLogonAck(&Packet, user.m_dwSessionID);

	return true;
}


bool CAccountProcess::ProcessPacket_LogonPermit_Session(DWORD dwSessionID, char* pPacket)
{
	PACKET_AH_LOGON_ACK_SESSION& Packet = *reinterpret_cast<PACKET_AH_LOGON_ACK_SESSION*>(pPacket);

	__SUSERAUTHENTICATE__ userAuthenticate;
	if( !g_UserAuthenticate.CUserAuthenticate::Bring(Packet.AID, &userAuthenticate) )
		return true;

	__SUSER__ user = {};
	if( g_UserList.CUserList::Bring(Packet.AID, &user) )
	{
		PACKET_SC_NOTIFY_BAN sc_notify_ban;
		sc_notify_ban.PacketType = HEADER_SC_NOTIFY_BAN;
		sc_notify_ban.ErrorCode = BAN_ANOTHER_LOGIN;

		if( user.m_pUserProcess != NULL )
		{
			user.m_pUserProcess->m_bAuthenticated = false;
			user.m_pUserProcess->Send((char*)&sc_notify_ban, sizeof(sc_notify_ban), user.m_dwSessionID, false);
			user.m_pUserProcess->CUserProcess::CloseForce(user.m_dwSessionID, 5000);
		}
	}

	PACKET_HZ_DISCONNECT hz_disconnect;
	hz_disconnect.PacketType = HEADER_HZ_DISCONNECT_RIGHTNOW;
	hz_disconnect.AID = Packet.AID;
//	hz_disconnect.reason = ?; //FIXME
	g_ZoneSvrStreamMgr.CStreamManager::Broadcast((char*)&hz_disconnect, sizeof(hz_disconnect));

	memset(&user, 0, sizeof(user));
	user.m_nSID = -1;
	user.m_dwSecurityCode = userAuthenticate.m_dwSecurityCode;
	user.m_pUserProcess = userAuthenticate.m_pUserProcess;
	user.m_dwSessionID = userAuthenticate.m_dwSessionID;
	memcpy(user.m_szEMail, Packet.emailAddress, 50);
	memcpy(user.m_szID, Packet.ID, 24);
	memcpy(user.m_szPersonalNumber, Packet.PERSONALNUMBER, 24-1);
	g_UserList.CUserList::Insert(Packet.AID, user);

	if( user.m_pUserProcess != NULL )
	{
		PACKET_AH_LOGON_ACK tmpPacket;
		tmpPacket.AID = Packet.AID;
		memcpy(tmpPacket.emailAddress, Packet.emailAddress, sizeof(tmpPacket.emailAddress));
		memcpy(tmpPacket.ID, Packet.ID, sizeof(tmpPacket.ID));
		memcpy(tmpPacket.PERSONALNUMBER, Packet.PERSONALNUMBER, sizeof(tmpPacket.PERSONALNUMBER));
		tmpPacket.TotalUsingTime = Packet.TotalUsingTime;
		tmpPacket.PacketType = ( Packet.PacketType == HEADER_AH_LOGON_EXIST_SESSION ) ? HEADER_AH_LOGON_EXIST : HEADER_AH_LOGON_NOTEXIST;

		user.m_pUserProcess->CUserProcess::OnLogonAck(&tmpPacket, user.m_dwSessionID);
	}

	return true;
}


bool CAccountProcess::ProcessPacket_LogonRefuse(DWORD dwSessionID, char* pPacket)
{
	PACKET_AH_LOGON_ACK& Packet = *reinterpret_cast<PACKET_AH_LOGON_ACK*>(pPacket);

	__SUSERAUTHENTICATE__ userAuthenticate;
	if( !g_UserAuthenticate.CUserAuthenticate::Bring(Packet.AID, &userAuthenticate) )
		return true;

	if( userAuthenticate.m_pUserProcess != NULL )
		userAuthenticate.m_pUserProcess->CUserProcess::OnLogonAck(&Packet, userAuthenticate.m_dwSessionID);

	return true;
}


bool CAccountProcess::ProcessPacket_LogonRefuse_Session(DWORD dwSessionID, char* pPacket)
{
	PACKET_AH_LOGON_ACK_SESSION& Packet = *reinterpret_cast<PACKET_AH_LOGON_ACK_SESSION*>(pPacket);

	__SUSERAUTHENTICATE__ userAuthenticate;
	if( !g_UserAuthenticate.CUserAuthenticate::Bring(Packet.AID, &userAuthenticate) )
		return true;

	if( userAuthenticate.m_pUserProcess != NULL )
	{
		PACKET_AH_LOGON_ACK tmpPacket;
		tmpPacket.AID = Packet.AID;
		memcpy(tmpPacket.emailAddress, Packet.emailAddress, sizeof(tmpPacket.emailAddress));
		memcpy(tmpPacket.ID, Packet.ID, sizeof(tmpPacket.ID));
		memcpy(tmpPacket.PERSONALNUMBER, Packet.PERSONALNUMBER, sizeof(tmpPacket.PERSONALNUMBER));
		tmpPacket.TotalUsingTime = Packet.TotalUsingTime;
		tmpPacket.PacketType = ( Packet.PacketType == HEADER_AH_LOGON_EXIST_SESSION ) ? HEADER_AH_LOGON_EXIST : HEADER_AH_LOGON_NOTEXIST;

		userAuthenticate.m_pUserProcess->CUserProcess::OnLogonAck(&tmpPacket, userAuthenticate.m_dwSessionID);
	}

	return true;
}


bool CAccountProcess::ProcessPacket_Disconnect(DWORD dwSessionID, char* pPacket)
{
	PACKET_AH_DISCONNECT& Packet = *reinterpret_cast<PACKET_AH_DISCONNECT*>(pPacket);

	PACKET_HZ_DISCONNECT hz_dissconnect;
	hz_dissconnect.AID = Packet.AID;
	hz_dissconnect.reason = Packet.reason;
	hz_dissconnect.PacketType = ( Packet.PacketType == HEADER_AH_DISCONNECT_RIGHTNOW ) ? HEADER_HZ_DISCONNECT_RIGHTNOW : HEADER_HZ_DISCONNECT;
	g_ZoneSvrStreamMgr.CStreamManager::Broadcast((char*)&hz_dissconnect, sizeof(hz_dissconnect));

	static CUserVerify* pUserVerify = CSingleton<CUserVerify>::getSingletonPtr();
	pUserVerify->CUserVerify::DeleteUserVerify(Packet.AID);

	if( g_bUsingCharacterPassword )
		DeleteConnectCharacter(Packet.AID);

	__SUSERAUTHENTICATE__ UserAuthenticate;
	BOOL bRetUserAuthe = g_UserAuthenticate.CUserAuthenticate::Bring(Packet.AID, &UserAuthenticate);

	__SUSER__ user;
	BOOL bRetUserBring = g_UserList.CUserList::Bring(Packet.AID, &user);

	if( !bRetUserAuthe && !bRetUserBring )
		return true;

	PACKET_SC_NOTIFY_BAN sc_notify_ban;
	sc_notify_ban.PacketType = HEADER_SC_NOTIFY_BAN;

	switch( Packet.reason )
	{
	case BAN_NOT_SETTLED:
	case BAN_IP_OVERFLOW:
	case BAN_PAY_OUT:
	case BAN_PAY_SUSPEND:
	case BAN_PAY_CHANGE:
	case BAN_PAY_WRONGIP:
	case BAN_PAY_PNGAMEROOM:
	case BAN_PC_IP_UNFAIR:
		sc_notify_ban.ErrorCode = Packet.reason;
	break;
	default:
		sc_notify_ban.ErrorCode = BAN_ANOTHER_LOGIN;
	break;
	};

	if( bRetUserAuthe ) // [patch] fix kick code to also disconnect people on character server
	{
		if( UserAuthenticate.m_pUserProcess != NULL )
		{
			UserAuthenticate.m_pUserProcess->Send((char*)&sc_notify_ban, sizeof(sc_notify_ban), UserAuthenticate.m_dwSessionID, false);
			UserAuthenticate.m_pUserProcess->CProcess::CloseOuter(UserAuthenticate.m_dwSessionID, 5000);
		}
	}
	else
	if( bRetUserBring )
	{
		if( user.m_pUserProcess != NULL )
		{
			user.m_pUserProcess->Send((char*)&sc_notify_ban, sizeof(sc_notify_ban), user.m_dwSessionID, false);
			user.m_pUserProcess->CProcess::CloseOuter(user.m_dwSessionID, 5000);
		}
	}

	return true;
}


bool CAccountProcess::ProcessPacket_Info_Remain_Time(DWORD dwSessionID, char* pPacket)
{
	PACKET_INFO_REMAINTIME& Packet = *reinterpret_cast<PACKET_INFO_REMAINTIME*>(pPacket);

	Packet.PacketType = HEADER_HZ_INFO_REMAINTIME;
	g_ZoneSvrStreamMgr.CStreamManager::Broadcast((char*)&Packet, sizeof(Packet));

	return true;
}


bool CAccountProcess::ProcessPacket_res_remain_time(DWORD dwSessionID, char* pPacket)
{
	PACKET_RES_REMAINTIME& Packet = *reinterpret_cast<PACKET_RES_REMAINTIME*>(pPacket);

	Packet.PacketType = HEADER_HZ_RES_REMAINTIME;
	g_ZoneSvrStreamMgr.CStreamManager::Broadcast((char*)&Packet, sizeof(Packet));

	return true;
}


bool CAccountProcess::ProcessPacket_AckPacketInfo(DWORD dwSessionID, char* pPacket)
{
	PACKET_AH_ACK_PACKETINFO& Packet = *reinterpret_cast<PACKET_AH_ACK_PACKETINFO*>(pPacket);

	return true;
}


bool CAccountProcess::ProcessPacket_ack_LimitInfo(DWORD dwSessionID, char* pPacket)
{
	PACKET_AH_ACK_PLAYING_LIMITINFO& Packet = *reinterpret_cast<PACKET_AH_ACK_PLAYING_LIMITINFO*>(pPacket);

	return true;
}


bool CAccountProcess::ProcessPacket_CollectDead(DWORD dwSessionID, char* pPacket)
{
	PACKET_COLLECTORDEAD& Packet = *reinterpret_cast<PACKET_COLLECTORDEAD*>(pPacket);

	static CServerInfoList* pServerInfoList = CSingleton<CServerInfoList>::getSingletonPtr();

	SSERVERINFO serverInfo;
	int nLocalSID = pServerInfoList->CServerInfoList::GetSID(g_dwLocalIP, SERVERTYPE_NONE);
	pServerInfoList->CServerInfoList::GetServerInfo(&serverInfo, nLocalSID);

	if( Packet.ServerID == serverInfo.m_nSID )
		g_ZoneSvrStreamMgr.CStreamManager::Broadcast((char*)&Packet, sizeof(Packet));

	return true;
}
