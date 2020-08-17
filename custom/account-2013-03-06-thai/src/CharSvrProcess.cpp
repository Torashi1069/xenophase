#include "Account.h"
#include "CharacterServerInfo.h"
#include "CharSvrProcess.h"
#include "ConnectLog.h"
#include "PCBangBillingDB.h"
#include "UserList.h"
#include "UserVerify.h"
#include "Common/EnterTraceLog.h"
#include "Common/Network.h"
#include "Common/NOutputTextMgr.h"
#include "Common/Packet.h"
#include "Common/ServerInfoList.h"
#include "Network3/AsyncProcessMgr.h"
#include "Network3/Stream.h"
#include "Enums.h"


CCharSvrProcess::CCharSvrProcess()
{
	m_nSID = -1;
}


CCharSvrProcess::~CCharSvrProcess()
{
}


bool CCharSvrProcess::OnConnect()
{
	char szIP[100] = {};
	CNetwork::GetObj()->CNetwork::GetTextIP(m_dwIP, szIP);

	m_nSID = CSingleton<CServerInfoList>::getSingletonPtr()->CServerInfoList::GetSID(m_dwIP, SERVERTYPE_CHARACTER);

	SSERVERINFO ServerInfo = {};
	CSingleton<CServerInfoList>::getSingletonPtr()->CServerInfoList::GetServerInfo(&ServerInfo, m_nSID);

	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("CharSvr %s(sid %d, %s) connected\n", szIP, m_nSID, ServerInfo.m_szName);
	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CharSvr %s(sid %d, %s) connected\n", szIP, m_nSID, ServerInfo.m_szName);
	return true;
}


void CCharSvrProcess::OnClose()
{
	char szIP[100] = {};
	CNetwork::GetObj()->CNetwork::GetTextIP(m_dwIP, szIP);

	if( CSingleton<CServerInfoList>::getSingletonPtr()->CServerInfoList::GetIPType(m_dwIP) == SERVERTYPE_CHARACTER )
	{
		NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("CharSvr %s(sid %d) disconnected\n", szIP, m_nSID);
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CharSvr %s(sid %d) disconnected\n", szIP, m_nSID);
	}

	m_nSID = -1;
}


bool CCharSvrProcess::OnRecv(char* buffer, int* len)
{
	DWORD dwSessionID = m_pStream->CStream::GetSessionID();
	if( dwSessionID == 0 )
		return false;

	int processed_len = 0;
	int total_len = *len;

	while( processed_len < total_len )
	{
		int remain = total_len - processed_len;
		if( remain < sizeof(PACKET) )
			break; // need more data.

		WORD wPacketType = reinterpret_cast<PACKET*>(buffer)->PacketType;
		int nPacketSize = this->CCharSvrProcess::GetPacketSize(wPacketType);

		if( nPacketSize == 0 )
		{
			char szIP[100] = {};
			CNetwork::GetObj()->CNetwork::GetTextIP(m_dwIP, szIP);
			CEnterTraceLog::GetObj()->CEnterTraceLog::MessagePrint("not defined pkt %u from %s ", wPacketType, szIP);
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

		if( wPacketType == HEADER_HA_LOGON2
		||  wPacketType == HEADER_HA_LOGON
		||  wPacketType == HEADER_HA_CHAR_EXIT
		)
		{
			unsigned int pkt_index = 0;
			if( wPacketType == HEADER_HA_LOGON2 )
				pkt_index = reinterpret_cast<PACKET_HA_LOGON2*>(buffer)->AID;
			else
			if( wPacketType == HEADER_HA_LOGON )
				pkt_index = reinterpret_cast<PACKET_HA_LOGON*>(buffer)->AID;
			else
			if( wPacketType == HEADER_HA_CHAR_EXIT )
				pkt_index = reinterpret_cast<PACKET_HA_CHAR_EXIT*>(buffer)->AID;

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
				CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s - g_AsyncProcessMgr.AllocPacket() failed\n", __FUNCTION__);
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


int CCharSvrProcess::GetPacketSize(WORD wPacketType)
{
	std::map<int,int>::const_iterator it = g_packetLenMap.find(wPacketType);
	return ( it != g_packetLenMap.end() ) ? it->second : 0;
}


bool CCharSvrProcess::ProcessPacket(DWORD dwSessionID, char* pPacket, WORD wPacketType, int nPacketSize)
{
	static CUserVerify* pUserVerify = CSingleton<CUserVerify>::getSingletonPtr();

	switch( wPacketType )
	{
	case HEADER_SERVER_ENTRY:
	{
		PACKET_SERVER_ENTRY& sc_server_entry = *reinterpret_cast<PACKET_SERVER_ENTRY*>(pPacket);
	}
	break;
	case HEADER_HA_CHAR_EXIT:
	{
		PACKET_HA_CHAR_EXIT& ha_char_exit = *reinterpret_cast<PACKET_HA_CHAR_EXIT*>(pPacket);

		if( ha_char_exit.AID <= 0 || ha_char_exit.AID >= MAX_ACCOUNTID - 1 )
			break;

		SUSER_ user = {};
		if( g_userList.CUserList::Bring(ha_char_exit.AID, &user) == TRUE )
		{
			pUserVerify->CUserVerify::DeleteUserVerify(ha_char_exit.AID);
			CSingleton<CConnectLog>::getSingletonPtr()->CConnectLog::AddConnectLog(user.m_szID, user.m_nIP, user.m_nAID, TRUE); // [patch] login/logout event logging
		}
	}
	break;
	case HEADER_HA_PCINFOUPDATE:
	{
		PACKET_HA_PCINFOUPDATE& ha_pcinfoupdate = *reinterpret_cast<PACKET_HA_PCINFOUPDATE*>(pPacket);

		if( ha_pcinfoupdate.AID <= 0 || ha_pcinfoupdate.AID >= MAX_ACCOUNTID - 1 )
			break;

		pUserVerify->CUserVerify::UpdateUserVerify(ha_pcinfoupdate.AID, 1200000);
		IsFreeServerSID(m_nSID);
	}
	break;
	case HEADER_HA_LOGON2:
	case HEADER_HA_LOGON:
	{
		PACKET_HA_LOGON2& ha_logon = *reinterpret_cast<PACKET_HA_LOGON2*>(pPacket);

		g_characterServerInfo[CLIENTTYPE_THAI].CCharacterServerInfo::SetUserCount(ha_logon.SID, static_cast<WORD>(ha_logon.userCount));
		g_characterServerInfo[CLIENTTYPE_THAI_FREE].CCharacterServerInfo::SetUserCount(ha_logon.SID, static_cast<WORD>(ha_logon.userCount));

		SUSER_ user = {};
		if( g_userList.CUserList::Get(ha_logon.AID, &user) != TRUE || ha_logon.AuthCode != user.m_nSecurityCode || ha_logon.Sex != user.m_nSex )
		{
			PACKET_AH_LOGON_ACK ah_login_ack;
			ah_login_ack.PacketType = HEADER_AH_LOGON_NOTEXIST;
			ah_login_ack.AID = ha_logon.AID;
			this->Send((char*)&ah_login_ack, sizeof(ah_login_ack), dwSessionID, false);
			break;
		}

		pUserVerify->CUserVerify::UpdateUserVerify(ha_logon.AID, 1200000);

		if( user.m_nIsGameStarted == 1 )
		{
			CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "SendLoginAck aid %d", user.m_nAID);
		}
		else
		{
			user.m_nPresentSID = m_nSID;
			user.m_nIsGameStarted = 1;
			g_userList.CUserList::Insert(user.m_nAID, user);
		}

		this->CCharSvrProcess::SendLoginAck(user, dwSessionID);
	}
	break;
	case HEADER_HA_IPBONUS_LIMIT:
		this->CCharSvrProcess::OnIPBonusLicenseLimit(dwSessionID, pPacket);
	break;
	default:
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "not defined pkt from char %d", wPacketType);
		return false;
	break;
	};

	return true;
}


void CCharSvrProcess::SendLoginAck(SUSER_& user, DWORD dwSessionID)
{
	PACKET_AH_LOGON_ACK_PCBANG ah_login_ack;
	memset(&ah_login_ack, 0, sizeof(ah_login_ack));
	ah_login_ack.PacketType = HEADER_AH_LOGON_EXIST_PCBANG;
	ah_login_ack.AID = user.m_nAID;
	memcpy(ah_login_ack.PERSONALNUMBER, user.m_szPersonalNum, sizeof(ah_login_ack.PERSONALNUMBER));
	memcpy(ah_login_ack.emailAddress, user.m_szEmail, sizeof(user.m_szEmail));
	memcpy(ah_login_ack.ID, user.m_szID, sizeof(ah_login_ack.ID));
	_strlwr_s(ah_login_ack.ID, sizeof(ah_login_ack.ID));
	ah_login_ack.m_dwIP = user.m_nIP;
	ah_login_ack.m_nPCBangGrade = user.m_isPCBang;
	ah_login_ack.m_nPayTypeEx = user.m_nPayTypeEx;
	ah_login_ack.m_nConnectionArea = user.m_nConnectionArea;
	ah_login_ack.m_nConnectionState = user.m_nConnectionState;
	ah_login_ack.m_nEventNum = user.m_nEventNum;
	ah_login_ack.m_dwConnectionTime = static_cast<DWORD>(time(NULL));
	this->Send((char*)&ah_login_ack, sizeof(ah_login_ack), dwSessionID, false);
}


void CCharSvrProcess::SendLoginAck(DWORD dwAID)
{
	SUSER_ user;
	if( g_userList.CUserList::Get(dwAID, &user) == FALSE )
	{
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Error! g_userList.Get( %d, user ) failed", dwAID);
		return;
	}

	PACKET_AH_LOGON_ACK_PCBANG ah_login_ack;
	memset(&ah_login_ack, 0, sizeof(ah_login_ack));
	ah_login_ack.PacketType = HEADER_AH_LOGON_EXIST_PCBANG;
	ah_login_ack.AID = user.m_nAID;
	memcpy(ah_login_ack.PERSONALNUMBER, user.m_szPersonalNum, sizeof(ah_login_ack.PERSONALNUMBER));
	memcpy(ah_login_ack.emailAddress, user.m_szEmail, sizeof(user.m_szEmail));
	memcpy(ah_login_ack.ID, user.m_szID, sizeof(ah_login_ack.ID));
	_strlwr_s(ah_login_ack.ID, sizeof(ah_login_ack.ID));
	ah_login_ack.m_dwIP = user.m_nIP;
	ah_login_ack.m_nPCBangGrade = user.m_isPCBang;
	ah_login_ack.m_nPayTypeEx = user.m_nPayTypeEx;
	ah_login_ack.m_nConnectionArea = user.m_nConnectionArea;
	ah_login_ack.m_nConnectionState = user.m_nConnectionState;
	ah_login_ack.m_nEventNum = user.m_nEventNum;
	ah_login_ack.m_dwConnectionTime = static_cast<DWORD>(time(NULL));
	this->Send((char*)&ah_login_ack, sizeof(ah_login_ack), user.m_dwSessionID, false);
}


void CCharSvrProcess::OnIPBonusLicenseLimit(DWORD in_dwSessionID, char* in_pPacket)
{
	PACKET_HA_IPBONUS_LIMIT& Packet = *reinterpret_cast<PACKET_HA_IPBONUS_LIMIT*>(in_pPacket);

	if( Packet.reason == PACKET_HA_IPBONUS_LIMIT::enum_IPBONUS_LIMIT )
		CPCBangBillingDB::GetObj()->CPCBangBillingDB::SetIPBonusLimit(Packet.limitIP);
	else
	if( Packet.reason == PACKET_HA_IPBONUS_LIMIT::enum_IPBONUS_NOT_LIMIT )
		CPCBangBillingDB::GetObj()->CPCBangBillingDB::DeleteIPBonusLimit(Packet.limitIP);
}
