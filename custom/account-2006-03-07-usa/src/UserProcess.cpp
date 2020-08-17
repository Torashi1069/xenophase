#include "Account.h"
#include "AccountDB.h"
#include "BlockIPManager.h"
#include "CharacterServerInfo.h"
#include "ConnectLog.h"
#include "UserList.h"
#include "UserProcess.h"
#include "UserVerify.h"
#include "Common/BlockTime.h"
#include "Common/InfoScript.h"
#include "Common/Network.h"
#include "Common/Packet.h"
#include "Common/Reporter.h"
#include "Network2/StreamManager.h"
#include "Enums.h"


CUserProcess::CUserProcess()
{
}


CUserProcess::~CUserProcess()
{
}


bool CUserProcess::OnConnect()
{
	if( CSingleton<CBlockIPManager>::getSingletonPtr()->CBlockIPManager::IsPermanentBlock(m_dwIP) )
		return false;

	if( CSingleton<CBlockIPManager>::getSingletonPtr()->CBlockIPManager::IsBlock(m_dwIP) )
		return false;

	return true;
}


void CUserProcess::OnClose()
{
}


bool CUserProcess::Process()
{
	int processed_len = 0;
	int total_len = m_pStream->m_RecvQueue.CCircleQueue::GetDataLength();
	DWORD dwSessionID = m_pStream->CStream::GetSessionID();

	int cnt;
	for( cnt = 1; cnt < 5; ++cnt )
	{
		if( dwSessionID != m_pStream->CStream::GetSessionID() )
			break;

		if( processed_len >= total_len )
			break; // done.

		int remain = total_len - processed_len;
		if( remain < 2 )
			break; // need more data.

		WORD wPacketType = 0;
		if( !m_pStream->m_RecvQueue.CCircleQueue::Peek(&wPacketType, 2) )
			break;

		int nPacketSize = this->CUserProcess::GetPacketSize(wPacketType);

		if( nPacketSize == 0 )
		{
			char szIP[100] = {};
			CSingleton<CNetwork>::getSingletonPtr()->CNetwork::GetTextIP(m_dwIP, szIP);
			CSingleton<CReporter>::getSingletonPtr()->CReporter::MessagePrint("not defined pkt from %s  ", szIP);
			return false;
		}

		if( nPacketSize == -1 )
		{
			DWORD dwHeader = 0;
			if( !m_pStream->m_RecvQueue.CCircleQueue::Peek(&dwHeader, 4) )
				break; // need more data.

			nPacketSize = dwHeader >> 16;
		}

		char PacketBuffer[1024];
		if( nPacketSize > sizeof(PacketBuffer) )
			return false;

		if( !m_pStream->m_RecvQueue.CCircleQueue::Get(PacketBuffer, nPacketSize) )
			break; // need more data.

		processed_len += nPacketSize;

		if( !this->CUserProcess::ProcessPacket(wPacketType, (WORD)nPacketSize, PacketBuffer) )
			return false;
	}

	if( cnt >= 5 )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::MessagePrint("\n######### cnt %d\n", cnt);

	return true;
}


int CUserProcess::GetPacketSize(WORD wPacketType)
{
	std::map<int,int>::iterator it = g_packetLenMap.find(wPacketType);
	return ( it != g_packetLenMap.end() ) ? it->second : 0;
}


bool CUserProcess::ProcessPacket(WORD wPacketType, WORD wPacketSize, char* pPacket)
{
	static CConnectLog* pConnectLog = CSingleton<CConnectLog>::getSingletonPtr();
	static CBlockTime* pBlockTime = CSingleton<CBlockTime>::getSingletonPtr();
	static CUserVerify* pUserVerify = CSingleton<CUserVerify>::getSingletonPtr();

	CAccountDB* db = &g_AccountDB[abs((int)m_dwIP % countof(g_AccountDB))];

	if( wPacketType == HEADER_CA_CONNECT_INFO_CHANGED )
	{
		if( !g_bXmlFileUserCheck )
			return true;

		PACKET_CA_CONNECT_INFO_CHANGED& packet = *reinterpret_cast<PACKET_CA_CONNECT_INFO_CHANGED*>(pPacket);
		packet.ID[23] = '\0';
		CSingleton<CReporter>::getSingletonPtr()->CReporter::MessagePrint("HEADER_CA_CONNECT_INFO_CHANGED id %s\n", packet.ID);

		if( g_xmlFileUser.CInfoScript::GetInfo((char*)packet.ID) )
		{
			CSingleton<CReporter>::getSingletonPtr()->CReporter::MessagePrint("exist\n");
			return true;
		}
		else
		{
			CSingleton<CReporter>::getSingletonPtr()->CReporter::MessagePrint("not exist\n");
			return false;
		}
	}

#ifdef RFEXE
	if( wPacketType == HEADER_CA_LOGIN )
	{// client without dll
		char szIP[64];
		CSingleton<CNetwork>::getSingletonPtr()->CNetwork::GetTextIP(m_dwIP, szIP);
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("Classic Login Packet - IP: %s\n", szIP);

		PACKET_AC_REFUSE_LOGIN ac_refuse_login;
		ac_refuse_login.PacketType = HEADER_AC_REFUSE_LOGIN;
		ac_refuse_login.ErrorCode = REFUSE_INVALID_VERSION;
		this->Send((char*)&ac_refuse_login, sizeof(ac_refuse_login), m_dwSessionID, false);

		this->CProcess::Close(5000);
		return true;
	}

	if( wPacketType != HEADER_CA_LOGIN_RF )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::MessagePrint("HEADER_CA_LOGIN_RF != wPacketType\n");
		return false;
	}
#else
	if( wPacketType != HEADER_CA_LOGIN )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::MessagePrint("HEADER_CA_LOGIN != wPacketType\n");
		return false;
	}
#endif

#ifdef RFEXE
	PACKET_CA_LOGIN_RF& ca_login = *reinterpret_cast<PACKET_CA_LOGIN_RF*>(pPacket);
#else
	PACKET_CA_LOGIN& ca_login = *reinterpret_cast<PACKET_CA_LOGIN*>(pPacket);
#endif

	ca_login.ID[sizeof(ca_login.ID)-1] = '\0';
	ca_login.Passwd[sizeof(ca_login.Passwd)-1] = '\0';

	if( ca_login.clienttype >= countof(g_characterServerInfo) )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::MessagePrint("ca_login.clienttype %d\n", ca_login.clienttype);
		return false;
	}

	if( db->CAccountDB::GetAID((char*)ca_login.ID) == 0 )
	{
		PACKET_AC_REFUSE_LOGIN ac_refuse_login;
		ac_refuse_login.PacketType = HEADER_AC_REFUSE_LOGIN;
		ac_refuse_login.ErrorCode = REFUSE_INVALID_ID;
//		memset(ac_refuse_login.blockDate, '\0', sizeof(ac_refuse_login.blockDate)); //FIXME: uninitialized
		this->Send((char*)&ac_refuse_login, sizeof(ac_refuse_login), m_dwSessionID, false);

		this->CProcess::Close(5000);
		return true;
	}

	if( (ca_login.clienttype != CLIENTTYPE_ENGLISH && ca_login.clienttype != CLIENTTYPE_ENGLISH_SAKRAY) || g_nVersion[ca_login.clienttype] != ca_login.Version )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::MessagePrint("%s ) g_nVersion[ca_login.clienttype] != ca_login.Version\n", ca_login.ID);

		PACKET_AC_REFUSE_LOGIN ac_refuse_login;
		ac_refuse_login.PacketType = HEADER_AC_REFUSE_LOGIN;
		ac_refuse_login.ErrorCode = REFUSE_INVALID_VERSION;
		this->Send((char*)&ac_refuse_login, sizeof(ac_refuse_login), m_dwSessionID, false);

		this->CProcess::Close(5000);
		return true;
	}

	SAUTHENTICATE authenticate = {};
	db->CAccountDB::AuthenticateUser((char*)ca_login.ID, (char*)ca_login.Passwd, authenticate, ca_login.clienttype);

	if( authenticate.m_dwResult != ACCEPT_ID_PASSWD )
	{
		if( authenticate.m_dwResult == REFUSE_INVALID_PASSWD )
			CSingleton<CBlockIPManager>::getSingletonPtr()->CBlockIPManager::IncreaseIncorrectCount((char*)ca_login.ID, authenticate.m_dwAID, m_dwIP, 1);

		PACKET_AC_REFUSE_LOGIN ac_refuse_login;
		ac_refuse_login.PacketType = HEADER_AC_REFUSE_LOGIN;
		ac_refuse_login.ErrorCode = static_cast<BYTE>(authenticate.m_dwResult);
		this->Send((char*)&ac_refuse_login, sizeof(ac_refuse_login), m_dwSessionID, false);

		this->CProcess::Close(5000);
		return true;
	}

	if( pBlockTime->CBlockTime::IsBlock(authenticate.m_dwAID) == TRUE )
	{
		PACKET_SC_NOTIFY_BAN sc_notify_ban;
		sc_notify_ban.PacketType = HEADER_SC_NOTIFY_BAN;
		sc_notify_ban.ErrorCode = BAN_INFORMATION_REMAINED;
		this->Send((char*)&sc_notify_ban, sizeof(sc_notify_ban), m_dwSessionID, false);

		this->CProcess::Close(5000);
		return true;
	}

	pBlockTime->CBlockTime::UpdateBlockTime(authenticate.m_dwAID, 7500); // [patch] reduced account lockout time
	
#ifdef RFEXE
	if( atoi(g_scrptConfig.CInfoScript::GetInfo("SECURE")) == 1 )
	{
	unsigned long exe_hash = strtoul(g_scrptConfig.CInfoScript::GetInfo("EXE_HASH"), NULL, 16);
	unsigned long dll_hash = strtoul(g_scrptConfig.CInfoScript::GetInfo("DLL_HASH"), NULL, 16);
	if( ca_login.exe_hash != exe_hash || ca_login.dll_hash != dll_hash )
	{// correct packet but wrong checksum - probably old version
		char szIP[64];
		CSingleton<CNetwork>::getSingletonPtr()->CNetwork::GetTextIP(m_dwIP, szIP);
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CRC Mismatch - AID: %d\tID: %s\tIP: %s\tCLIENT: %8.8X\tDLL: %8.8X\n", authenticate.m_dwAID, ca_login.ID, szIP, ca_login.exe_hash, ca_login.dll_hash);

		PACKET_AC_REFUSE_LOGIN ac_refuse_login;
		ac_refuse_login.PacketType = HEADER_AC_REFUSE_LOGIN;
		ac_refuse_login.ErrorCode = REFUSE_INVALID_VERSION;
		this->Send((char*)&ac_refuse_login, sizeof(ac_refuse_login), m_dwSessionID, false);

		this->CProcess::Close(5000);
		return true;
	}

	unsigned long server_ip = inet_addr(g_scrptConfig.CInfoScript::GetInfo("CHECK_SERVERIP"));
	if( ca_login.server_ip != server_ip )
	{// proxying?!
		char szIP1[64], szIP2[64];
		CSingleton<CNetwork>::getSingletonPtr()->CNetwork::GetTextIP(m_dwIP, szIP1);
		CSingleton<CNetwork>::getSingletonPtr()->CNetwork::GetTextIP(ca_login.server_ip, szIP2);
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("IP Adress Mismatch - AID: %d\tID: %s\tIP: %s\tCLIENTIP: %s\n", authenticate.m_dwAID, ca_login.ID, szIP1, szIP2);

		PACKET_AC_REFUSE_LOGIN ac_refuse_login;
		ac_refuse_login.PacketType = HEADER_AC_REFUSE_LOGIN;
		ac_refuse_login.ErrorCode = ACCEPT_ID_PASSWD;
		this->Send((char*)&ac_refuse_login, sizeof(ac_refuse_login), m_dwSessionID, false);

		this->CProcess::Close(5000);
		return true;
	}
	}; //SECURE
#endif

	SUSER_ user;
	if( g_userList.CUserList::Bring(authenticate.m_dwAID, &user) == TRUE )
	{
		pUserVerify->CUserVerify::DeleteUserVerify(authenticate.m_dwAID);

		PACKET_AH_DISCONNECT ah_disconnect;
		ah_disconnect.PacketType = HEADER_AH_DISCONNECT;
		ah_disconnect.AID = authenticate.m_dwAID;
		ah_disconnect.reason = BAN_ANOTHER_LOGIN;
		g_CharSvrStreamMgr.CStreamManager::Broadcast((char*)&ah_disconnect, sizeof(ah_disconnect));

		PACKET_SC_NOTIFY_BAN sc_notify_ban;
		sc_notify_ban.PacketType = HEADER_SC_NOTIFY_BAN;
		sc_notify_ban.ErrorCode = BAN_INFORMATION_REMAINED;
		this->Send((char*)&sc_notify_ban, sizeof(sc_notify_ban), m_dwSessionID, false);

		this->CProcess::Close(5000);
		return true;
	}

	SUSERINFO userinfo = {};
	db->CAccountDB::GetUserInfo(authenticate.m_dwAID, &userinfo);

	user.m_nState = 1;
	user.m_nSecurityCode = rand();
	user.m_nAID = authenticate.m_dwAID;
	strcpy(user.m_szID, (char*)ca_login.ID);
	strcpy(user.m_szPersonalNum, userinfo.m_szPersonalNum);
	strcpy(user.m_szEmail, userinfo.m_szEmail);
	user.m_nSex = userinfo.m_nSex;
	user.m_nIP = m_dwIP;
	user.m_nPresentSID = -1;
	user.m_nIsGameStarted = 0;
	g_userList.CUserList::Insert(authenticate.m_dwAID, user);

	userinfo.m_nIP = m_dwIP;
	pConnectLog->CConnectLog::AddConnectLog((char*)ca_login.ID, userinfo.m_nIP, authenticate.m_dwAID, FALSE); // [patch] login/logout event logging

	db->CAccountDB::UpdateUserInfo2(user.m_nAID, &userinfo); // [patch] update ip/lasttime column

	int nCount = 0;
	SERVER_ADDR* addrs = g_characterServerInfo[ca_login.clienttype].CCharacterServerInfo::GetCharacterServerInfo(&nCount);

	// [patch] hide user count in charserver select screen
	std::vector<SERVER_ADDR> tmp(&addrs[0], &addrs[nCount]);
	for( int i = 0; i < nCount; ++i )
	{
		tmp[i].usercount = -1; // dummy value
		tmp[i].state = -1; // default handler won't print value
	}

	PACKET_AC_ACCEPT_LOGIN ac_accept_login;
	ac_accept_login.PacketType = HEADER_AC_ACCEPT_LOGIN;
	ac_accept_login.PacketLength = sizeof(PACKET_AC_ACCEPT_LOGIN) + nCount * sizeof(SERVER_ADDR);
	ac_accept_login.AuthCode = user.m_nSecurityCode;
	ac_accept_login.AID = authenticate.m_dwAID;
	ac_accept_login.userLevel = userinfo.m_nGrade;
	ac_accept_login.lastLoginIP = 0;
//	memset(ac_accept_login.lastLoginTime, '\0', sizeof(ac_accept_login.lastLoginTime)); //FIXME: uninitialized
	ac_accept_login.Sex = userinfo.m_nSex;
	this->Send((char*)&ac_accept_login, sizeof(ac_accept_login), m_dwSessionID, false);
	this->Send((char*)&tmp.front(), nCount * sizeof(SERVER_ADDR), m_dwSessionID, false);

	pUserVerify->CUserVerify::UpdateUserVerify(authenticate.m_dwAID, 1200000);
	CSingleton<CBlockIPManager>::getSingletonPtr()->CBlockIPManager::ClearIncorrectCount(m_dwIP);

	this->CProcess::Close(8000);
	return true;
}
