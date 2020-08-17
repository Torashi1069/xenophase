#include "Account.h"
#include "CharacterServerInfo.h"
#include "CharSvrProcess.h"
#include "UserList.h"
#include "UserVerify.h"
#include "Common/Network.h"
#include "Common/Packet.h"
#include "Common/Reporter.h"
#include "Common/ServerInfoList.h"
#include "Network2/Stream.h"
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
	CSingleton<CNetwork>::getSingletonPtr()->CNetwork::GetTextIP(m_dwIP, szIP);

	if( CSingleton<CServerInfoList>::getSingletonPtr()->CServerInfoList::GetIPType(m_dwIP) != SERVERTYPE_CHARACTER )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::MessagePrint("not CharSvr %s(type %d) connected\n", szIP,  CSingleton<CServerInfoList>::getSingletonPtr()->CServerInfoList::GetIPType(m_dwIP));
		return false;
	}

	m_nSID = CSingleton<CServerInfoList>::getSingletonPtr()->CServerInfoList::GetSID(m_dwIP, SERVERTYPE_CHARACTER);

	SSERVERINFO ServerInfo;
	CSingleton<CServerInfoList>::getSingletonPtr()->CServerInfoList::GetServerInfo(&ServerInfo, m_nSID);

	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CharSvr %s(sid %d, %s) connected\n", szIP, m_nSID, ServerInfo.m_szName);
	return true;
}


void CCharSvrProcess::OnClose()
{
	char szIP[100] = {};
	CSingleton<CNetwork>::getSingletonPtr()->CNetwork::GetTextIP(m_dwIP, szIP);

	if( CSingleton<CServerInfoList>::getSingletonPtr()->CServerInfoList::GetIPType(m_dwIP) == SERVERTYPE_CHARACTER )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CharSvr %s(sid %d) disconnected\n", szIP, m_nSID);

	m_nSID = -1;
}


bool CCharSvrProcess::Process()
{
	DWORD dwSessionID = m_dwSessionID;
	if( dwSessionID == 0 )
		return true;

	int processed_len = 0;
	int total_len = m_pStream->m_RecvQueue.CCircleQueue::GetDataLength();

	while( 1 )
	{
		if( dwSessionID != m_pStream->CStream::GetSessionID() )
		{
			CSingleton<CReporter>::getSingletonPtr()->CReporter::MessagePrint("dwSessionID != m_pStream->GetSessionID()\n");
			break;
		}

		if( processed_len >= total_len )
			break; // done.

		int remain = total_len - processed_len;
		if( remain < 2 )
			break; // need more data.

		WORD wPacketType = 0;
		if( !m_pStream->m_RecvQueue.CCircleQueue::Peek(&wPacketType, 2) )
			break; // need more data.

		int nPacketSize = this->CCharSvrProcess::GetPacketSize(wPacketType);

		if( nPacketSize == 0 )
			return false;

		if( nPacketSize == -1 )
		{
			DWORD dwHeader = 0;
			if( !m_pStream->m_RecvQueue.CCircleQueue::Peek(&dwHeader, 4) )
				break; // need more data.

			nPacketSize = dwHeader >> 16;
		}

		char PacketBuffer[2048];
		if( nPacketSize > sizeof(PacketBuffer) )
			return false;

		if( !m_pStream->m_RecvQueue.CCircleQueue::Get(PacketBuffer, nPacketSize) )
			break; // need more data.

		processed_len += nPacketSize;

		if( !this->CCharSvrProcess::ProcessPacket(wPacketType, (WORD)nPacketSize, PacketBuffer) )
			return false;
	}

	return true;
}


int CCharSvrProcess::GetPacketSize(WORD wPacketType)
{
	std::map<int,int>::iterator it = g_packetLenMap.find(wPacketType);
	return ( it != g_packetLenMap.end() ) ? it->second : 0;
}


bool CCharSvrProcess::ProcessPacket(unsigned short wPacketType, unsigned short wPacketSize, char* pPacket)
{
	static CUserVerify* pUserVerify = CSingleton<CUserVerify>::getSingletonPtr();

	switch( wPacketType )
	{
	case HEADER_HA_LOGON:
		return this->CCharSvrProcess::ProcessPacket_LOGON(pPacket);
	case HEADER_HA_PCINFOUPDATE:
		return this->CCharSvrProcess::ProcessPacket_PCINFOUPDATE(pPacket);
	case HEADER_HA_CHAR_EXIT:
		return this->CCharSvrProcess::ProcessPacket_CHAR_EXIT(pPacket);
	case HEADER_HA_LOGON_SESSION:
		return this->CCharSvrProcess::ProcessPacket_LogOn_Session(pPacket);
	case HEADER_SERVER_ENTRY:
	case HEADER_HA_REQ_PACKETINFO:
	case HEADER_HA_REQ_REMAINTIME:
		CSingleton<CReporter>::getSingletonPtr()->CReporter::MessagePrint("no proc for this packet. wPacketType: %d", wPacketType);
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("no proc for this packet. wPacketType: %d", wPacketType);
	break;
	default:
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("Invalid packet from CharSvr - %d, %d\n", wPacketType, wPacketSize);
		return false;
	break;
	}

	return true;
}


bool CCharSvrProcess::ProcessPacket_LOGON(char* pPacket)
{
	static CUserVerify* pUserVerify = CSingleton<CUserVerify>::getSingletonPtr();
	PACKET_HA_LOGON& ha_logon = *reinterpret_cast<PACKET_HA_LOGON*>(pPacket);

	g_characterServerInfo[CLIENTTYPE_ENGLISH].CCharacterServerInfo::SetUserCount(ha_logon.SID, static_cast<WORD>(ha_logon.userCount));
	g_characterServerInfo[CLIENTTYPE_ENGLISH_SAKRAY].CCharacterServerInfo::SetUserCount(ha_logon.SID, static_cast<WORD>(ha_logon.userCount));

	SUSER_ user;
	if( g_userList.CUserList::Get(ha_logon.AID, &user) != TRUE || ha_logon.AuthCode != user.m_nSecurityCode || ha_logon.Sex != user.m_nSex )
	{
		PACKET_AH_LOGON_ACK ah_login_ack;
		ah_login_ack.PacketType = HEADER_AH_LOGON_NOTEXIST;
		ah_login_ack.AID = ha_logon.AID;
		this->Send((char*)&ah_login_ack, sizeof(ah_login_ack), m_dwSessionID, false);
	}
	else
	{
		pUserVerify->CUserVerify::UpdateUserVerify(ha_logon.AID, 1200000);

		PACKET_AH_LOGON_ACK ah_login_ack;
		ah_login_ack.PacketType = HEADER_AH_LOGON_EXIST;
		ah_login_ack.AID = user.m_nAID;
		memcpy(ah_login_ack.PERSONALNUMBER, user.m_szPersonalNum, sizeof(ah_login_ack.PERSONALNUMBER));
		memcpy(ah_login_ack.emailAddress, user.m_szEmail, sizeof(user.m_szEmail));
		memcpy(ah_login_ack.ID, user.m_szID, sizeof(ah_login_ack.ID));
		_strlwr(ah_login_ack.ID);
		this->Send((char*)&ah_login_ack, sizeof(ah_login_ack), m_dwSessionID, false);

		if( user.m_nIsGameStarted == 0 )
		{
			user.m_nIsGameStarted = 1;
			user.m_nPresentSID = m_nSID;
			g_userList.CUserList::Insert(user.m_nAID, user);
		}
	}

	return true;
}


bool CCharSvrProcess::ProcessPacket_LogOn_Session(char* pPacket)
{
	static CUserVerify* pUserVerify = CSingleton<CUserVerify>::getSingletonPtr();
	PACKET_HA_LOGON_SESSION& ha_logon_session = *reinterpret_cast<PACKET_HA_LOGON_SESSION*>(pPacket);

	g_characterServerInfo[CLIENTTYPE_ENGLISH].CCharacterServerInfo::SetUserCount(ha_logon_session.SID, static_cast<unsigned short>(ha_logon_session.userCount));
	g_characterServerInfo[CLIENTTYPE_ENGLISH_SAKRAY].CCharacterServerInfo::SetUserCount(ha_logon_session.SID, static_cast<unsigned short>(ha_logon_session.userCount));

	SUSER_ user;
	if( g_userList.CUserList::Get(ha_logon_session.AID, &user) != TRUE || ha_logon_session.AuthCode != user.m_nSecurityCode || ha_logon_session.Sex != user.m_nSex )
	{
		PACKET_AH_LOGON_ACK_SESSION ah_login_ack;
		ah_login_ack.PacketType = HEADER_AH_LOGON_NOTEXIST_SESSION;
		ah_login_ack.AID = ha_logon_session.AID;
		ah_login_ack.dwSessionID = ha_logon_session.dwSessionID;
		this->Send((char*)&ah_login_ack, sizeof(ah_login_ack), m_dwSessionID, false);
		return true;
	}
	else
	{
		pUserVerify->CUserVerify::UpdateUserVerify(ha_logon_session.AID, 1200000);

		PACKET_AH_LOGON_ACK_SESSION ah_login_ack;
		ah_login_ack.PacketType = HEADER_AH_LOGON_EXIST_SESSION;
		ah_login_ack.AID = user.m_nAID;
		ah_login_ack.dwSessionID = ha_logon_session.dwSessionID;
		memcpy(ah_login_ack.PERSONALNUMBER, user.m_szPersonalNum, sizeof(ah_login_ack.PERSONALNUMBER));
		memcpy(ah_login_ack.emailAddress, user.m_szEmail, sizeof(user.m_szEmail));
		memcpy(ah_login_ack.ID, user.m_szID, sizeof(ah_login_ack.ID));
		_strlwr(ah_login_ack.ID);
		this->Send((char*)&ah_login_ack, sizeof(ah_login_ack), m_dwSessionID, false);

		if( user.m_nIsGameStarted == 0 )
		{
			user.m_nIsGameStarted = 1;
			user.m_nPresentSID = m_nSID;
			g_userList.CUserList::Insert(user.m_nAID, user);
		}
	}

	return true;
}


bool CCharSvrProcess::ProcessPacket_PCINFOUPDATE(char* pPacket)
{
	static CUserVerify* pUserVerify = CSingleton<CUserVerify>::getSingletonPtr();
	PACKET_HA_PCINFOUPDATE& ha_pcinfoupdate = *reinterpret_cast<PACKET_HA_PCINFOUPDATE*>(pPacket);
	unsigned long AID = ha_pcinfoupdate.AID;

	if( AID <= 0 || AID >= 9999999 )
		return true;

	pUserVerify->CUserVerify::UpdateUserVerify(AID, 1200000);

	return true;
}


bool CCharSvrProcess::ProcessPacket_CHAR_EXIT(char* pPacket)
{
	PACKET_HA_CHAR_EXIT& ha_char_exit = *reinterpret_cast<PACKET_HA_CHAR_EXIT*>(pPacket);
	unsigned long AID = ha_char_exit.AID;

	if( AID <= 0 || AID >= 9999999 )
		return true;

	SUSER_ user;
	if( g_userList.CUserList::Bring(AID, &user) == TRUE )
		CSingleton<CUserVerify>::getSingletonPtr()->CUserVerify::DeleteUserVerify(AID);

	return true;
}
