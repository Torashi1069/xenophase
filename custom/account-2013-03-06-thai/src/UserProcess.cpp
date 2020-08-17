#include "AccountDB.h"
#include "BlockTime.h"
#include "CharacterServerInfo.h"
#include "ConnectLog.h"
#include "PCBangBillingDB.h"
#include "TBlockTime.h"
#include "UserProcess.h"
#include "UserList.h"
#include "UserVerify.h"
#include "Common/EnterTraceLog.h"
#include "Common/InfoScript.h"
#include "Common/md5.h"
#include "Common/MemPool.h"
#include "Common/Network.h"
#include "Common/NOutputTextMgr.h"
#include "Common/Packet.h"
#include "Common/RandStr.h"
#include "Network3/AsyncProcessMgr.h"
#include "Network3/Stream.h"
#include "Network3/StreamManager.h"
#include "Enums.h"


/// locals
static CRandStr g_RandStr;
static CTBlockTime g_PassIncorrectBlock;


CUserProcess::CUserProcess()
{
	m_bRandStrSent = false;
}


CUserProcess::~CUserProcess()
{
}


bool CUserProcess::OnConnect()
{
	int n = rand() % 10000;
	memcpy(m_RandStr, g_RandStr[n], sizeof(m_RandStr));
	m_bRandStrSent = false;
	m_bCA_LOGIN_Received = false;
	return true;
}


void CUserProcess::OnClose()
{
}


void CUserProcess::OnIdle()
{
}


bool CUserProcess::OnRecv(char* buffer, int* len)
{
	DWORD dwSessionID = m_pStream->CStream::GetSessionID();
	if( dwSessionID == 0 )
		return false;

	int processed_len = 0;
	int total_len = *len;

	for( int cnt = 1; cnt < 5; ++cnt )
	{
		if( processed_len >= total_len )
			break;
		
		int remain = total_len - processed_len;
		if( remain < sizeof(PACKET) )
			break; // need more data.

		WORD wPacketType = reinterpret_cast<PACKET*>(buffer)->PacketType;
		int nPacketSize = this->CUserProcess::GetPacketSize(wPacketType);

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

		if( wPacketType == HEADER_CA_LOGIN3
		||  wPacketType == HEADER_CA_LOGIN )
		{
			ASYNCPACKET* pAsyncPacket = g_AsyncProcessMgr.AllocPacket();
			if( pAsyncPacket != NULL )
			{
				static unsigned int pkt_index;
				memset(pAsyncPacket, 0, sizeof(*pAsyncPacket));
				pAsyncPacket->dwSessionID = dwSessionID;
				pAsyncPacket->nPacketSize = nPacketSize;
				memcpy(pAsyncPacket->packet, buffer, nPacketSize);
				pAsyncPacket->pProcessPtr = this;
				pAsyncPacket->wPacketType = wPacketType;
				g_AsyncProcessMgr.CAsyncProcessMgr::PushPacket(pAsyncPacket, pkt_index);
				++pkt_index;
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


int CUserProcess::GetPacketSize(WORD wPacketType)
{
	std::map<int,int>::const_iterator it = g_packetLenMap.find(wPacketType);
	return ( it != g_packetLenMap.end() ) ? it->second : 0;
}


bool CUserProcess::ProcessPacket(DWORD dwSessionID, char* pPacket, WORD wPacketType, int nPacketSize)
{
	static CConnectLog* pConnectLog = CSingleton<CConnectLog>::getSingletonPtr();
	static CBlockTime* pBlockTime = CSingleton<CBlockTime>::getSingletonPtr();
	static CUserVerify* pUserVerify = CSingleton<CUserVerify>::getSingletonPtr();

	CAccountDB* pAccountDB = &g_AccountDB[m_dwIP % countof(g_AccountDB)];

	if( m_pStream->CStream::GetSessionID() != dwSessionID )
		return true;

	if( wPacketType == HEADER_CA_REQ_HASH )
		return this->CUserProcess::ProcessPacket_CA_REQ_HASH(dwSessionID, pPacket, wPacketType, nPacketSize);

	if( wPacketType == HEADER_CA_CONNECT_INFO_CHANGED )
		return this->CUserProcess::ProcessPacket_CA_CONNECT_INFO_CHANGED(pPacket);

#if defined(RFEXE) // [patch] plaintext login packet
	if( wPacketType == HEADER_CA_LOGIN ) // [patch] RF login packet
	{// client without dll
		char szIP[64];
		CNetwork::GetObj()->CNetwork::GetTextIP(m_dwIP, szIP);
		NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("Classic Login Packet - IP: %s\n", szIP);

		PACKET_AC_REFUSE_LOGIN ac_refuse_login;
		ac_refuse_login.PacketType = HEADER_AC_REFUSE_LOGIN;
		ac_refuse_login.ErrorCode = REFUSE_INVALID_VERSION;
		this->Send((char*)&ac_refuse_login, sizeof(ac_refuse_login), m_dwSessionID, false);

		this->CProcess::CloseOuter(dwSessionID, 5000);
		return true;
	}

	if( wPacketType != HEADER_CA_LOGIN_RF )
	{
		NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("HEADER_CA_LOGIN != wPacketType(%d)", wPacketType);
		return false;
	}

	PACKET_CA_LOGIN_RF& ca_login = *reinterpret_cast<PACKET_CA_LOGIN_RF*>(pPacket);

	ca_login.Passwd[sizeof(ca_login.Passwd)-1] = '\0';
#else
	if( wPacketType != HEADER_CA_LOGIN3 )
	{
		NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("HEADER_CA_LOGIN3 != wPacketType(%d)", wPacketType);
		return false;
	}

	PACKET_CA_LOGIN3& ca_login = *reinterpret_cast<PACKET_CA_LOGIN3*>(pPacket);

	if( !m_bRandStrSent )
		return false;
#endif

	ca_login.ID[sizeof(ca_login.ID)-1] = '\0';

	if( m_bCA_LOGIN_Received )
		return false;
	
	m_bCA_LOGIN_Received = true;
	if( ca_login.clienttype >= MAX_CLIENTTYPE )
		return false;

	SAUTHENTICATE authenticate = {};
	pAccountDB->CAccountDB::GetAuthenticateInfo(ca_login.ID, ca_login.clienttype, &authenticate);
	if( authenticate.m_dwAID == 0 )
	{
		PACKET_AC_REFUSE_LOGIN ac_refuse_login;
		ac_refuse_login.PacketType = HEADER_AC_REFUSE_LOGIN;
		ac_refuse_login.ErrorCode = REFUSE_INVALID_ID;
//		memset(ac_refuse_login.blockDate, '\0', sizeof(ac_refuse_login.blockDate)); //FIXME: uninitialized
		this->Send((char*)&ac_refuse_login, sizeof(ac_refuse_login), dwSessionID, false);

		this->CProcess::CloseOuter(dwSessionID, 5000);
		return true;
	}

	if( g_PassIncorrectBlock.CTBlockTime::IsBlock(authenticate.m_dwAID) )
		return false;

	ca_login.clienttype = CLIENTTYPE_THAI; // [patch] ignore client type
	if( ca_login.clienttype != CLIENTTYPE_THAI || g_nVersion[CLIENTTYPE_THAI] != ca_login.Version )
	{
		PACKET_AC_REFUSE_LOGIN ac_refuse_login;
		ac_refuse_login.PacketType = HEADER_AC_REFUSE_LOGIN;
		ac_refuse_login.ErrorCode = REFUSE_INVALID_VERSION;
//		memset(ac_refuse_login.blockDate, '\0', sizeof(ac_refuse_login.blockDate)); //FIXME: uninitialized
		this->Send((char*)&ac_refuse_login, sizeof(ac_refuse_login), dwSessionID, false);

		this->CProcess::CloseOuter(dwSessionID, 5000);
		g_PassIncorrectBlock.CTBlockTime::AddIncorrectCount(authenticate.m_dwAID, ca_login.ID, m_dwIP);
		return true;
	}

#if defined(RFEXE) // [patch] plaintext login packet
	pAccountDB->CAccountDB::AuthenticateUser(ca_login.ID, ca_login.Passwd, authenticate, ca_login.clienttype);
#else
	pAccountDB->CAccountDB::GetAuthenticateInfo(ca_login.ID, ca_login.clienttype, &authenticate);
	if( authenticate.m_dwResult == ACCEPT_ID_PASSWD )
	{
		MD5 md5;
		md5.MD5::init();
		md5.MD5::append((unsigned char*)m_RandStr, 16);
		size_t passwdLen = strlen(authenticate.m_passwd);
		if( passwdLen > 0 )
			md5.MD5::append((unsigned char*)authenticate.m_passwd, passwdLen);
		md5.MD5::finish((unsigned char*)m_PasswdMD5);

		if( strncmp(m_PasswdMD5, (char*)ca_login.PasswdMD5, 16) != 0 )
			authenticate.m_dwResult = REFUSE_INVALID_PASSWD;
	}
#endif

	if( authenticate.m_dwResult != ACCEPT_ID_PASSWD )
	{
		PACKET_AC_REFUSE_LOGIN ac_refuse_login = {};
		ac_refuse_login.PacketType = HEADER_AC_REFUSE_LOGIN;
		ac_refuse_login.ErrorCode = static_cast<unsigned char>(authenticate.m_dwResult);

		if( authenticate.m_dwConfirmed == 4 )
		{
			pAccountDB->CAccountDB::GetBlockDate(ca_login.ID, ac_refuse_login.blockDate);
			this->Send((char*)&ac_refuse_login, sizeof(ac_refuse_login), dwSessionID, false);
		}
		else
		if( authenticate.m_dwConfirmed == 3 )
		{
			this->Send((char*)&ac_refuse_login, sizeof(ac_refuse_login), dwSessionID, false);
		}
		else
		{
			char szErrorMessage[150] = {};
			pAccountDB->CAccountDB::GetIsConfirmedMsg(authenticate.m_dwConfirmed, szErrorMessage, sizeof(szErrorMessage));
			szErrorMessage[sizeof(szErrorMessage)-1] = '\0';

			PACKET_AC_NOTIFY_ERROR ac_notify_error;
			ac_notify_error.PacketType = HEADER_AC_NOTIFY_ERROR;
			ac_notify_error.PacketLength = sizeof(ac_notify_error) + strlen(szErrorMessage);
			this->Send((char*)&ac_notify_error, sizeof(ac_notify_error), dwSessionID, false);
			this->Send(szErrorMessage, strlen(szErrorMessage), dwSessionID, false);
		}

		this->CProcess::CloseOuter(dwSessionID, 6000);
		g_PassIncorrectBlock.CTBlockTime::AddIncorrectCount(authenticate.m_dwAID, ca_login.ID, m_dwIP);
		return true;
	}

	g_PassIncorrectBlock.CTBlockTime::SetIncorrectCount(authenticate.m_dwAID, 0);

	const char* szRestrictedIP = g_scriptRestriction.CInfoScript::GetInfo(ca_login.ID);
	if( szRestrictedIP != NULL && m_dwIP != CNetwork::GetObj()->CNetwork::GetDWORDIP(szRestrictedIP) )
	{
		char szIP1[40];
		CNetwork::GetObj()->CNetwork::GetTextIP(m_dwIP, szIP1);

		char szIP2[40];
		CNetwork::GetObj()->CNetwork::GetTextIP(CNetwork::GetObj()->CNetwork::GetDWORDIP(szRestrictedIP), szIP2);

		CEnterTraceLog::GetObj()->CEnterTraceLog::MessagePrint("IP %s is not allowd for %s(%s) to connect", szIP1, ca_login.ID, szIP2);
		return false;
	}

	if( pBlockTime->CBlockTime::IsBlock(authenticate.m_dwAID) == TRUE )
	{
		PACKET_SC_NOTIFY_BAN sc_notify_ban;
		sc_notify_ban.PacketType = HEADER_SC_NOTIFY_BAN;
		sc_notify_ban.ErrorCode = BAN_INFORMATION_REMAINED;
		this->Send((char*)&sc_notify_ban, sizeof(PACKET_SC_NOTIFY_BAN), dwSessionID, false);

		this->CProcess::CloseOuter(dwSessionID, 5000);
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
		CNetwork::GetObj()->CNetwork::GetTextIP(m_dwIP, szIP);
		CEnterTraceLog::GetObj()->CEnterTraceLog::MessagePrint("CRC Mismatch - AID: %d\tID: %s\tIP: %s\tCLIENT: %8.8X\tDLL: %8.8X\n", authenticate.m_dwAID, ca_login.ID, szIP, ca_login.exe_hash, ca_login.dll_hash);

		PACKET_AC_REFUSE_LOGIN ac_refuse_login;
		ac_refuse_login.PacketType = HEADER_AC_REFUSE_LOGIN;
		ac_refuse_login.ErrorCode = REFUSE_INVALID_VERSION;
		this->Send((char*)&ac_refuse_login, sizeof(ac_refuse_login), m_dwSessionID, false);

		this->CProcess::CloseOuter(dwSessionID, 5000);
		return true;
	}

	unsigned long server_ip = inet_addr(g_scrptConfig.CInfoScript::GetInfo("CHECK_SERVERIP"));
	if( ca_login.server_ip != server_ip )
	{// proxying?!
		char szIP1[64], szIP2[64];
		CNetwork::GetObj()->CNetwork::GetTextIP(m_dwIP, szIP1);
		CNetwork::GetObj()->CNetwork::GetTextIP(ca_login.server_ip, szIP2);
		CEnterTraceLog::GetObj()->CEnterTraceLog::MessagePrint("IP Adress Mismatch - AID: %d\tID: %s\tIP: %s\tCLIENTIP: %s\n", authenticate.m_dwAID, ca_login.ID, szIP1, szIP2);

		PACKET_AC_REFUSE_LOGIN ac_refuse_login;
		ac_refuse_login.PacketType = HEADER_AC_REFUSE_LOGIN;
		ac_refuse_login.ErrorCode = ACCEPT_ID_PASSWD;
		this->Send((char*)&ac_refuse_login, sizeof(ac_refuse_login), m_dwSessionID, false);

		this->CProcess::CloseOuter(dwSessionID, 5000);
		return true;
	}
	}; //SECURE
#endif

	SUSER_ user = {};
	if( g_userList.CUserList::Bring(authenticate.m_dwAID, &user) == TRUE )
	{// already online, reject login and kick existing session
		pUserVerify->CUserVerify::DeleteUserVerify(authenticate.m_dwAID);

		PACKET_AH_DISCONNECT ah_disconnect;
		ah_disconnect.PacketType = HEADER_AH_DISCONNECT;
		ah_disconnect.AID = authenticate.m_dwAID;
		ah_disconnect.reason = BAN_ANOTHER_LOGIN;
		g_CharSvrStreamMgr.CStreamManager::Broadcast((char*)&ah_disconnect, sizeof(ah_disconnect));

		PACKET_SC_NOTIFY_BAN sc_notify_ban;
		sc_notify_ban.PacketType = HEADER_SC_NOTIFY_BAN;
		sc_notify_ban.ErrorCode = BAN_INFORMATION_REMAINED;
		this->Send((char*)&sc_notify_ban, sizeof(PACKET_SC_NOTIFY_BAN), dwSessionID, false);

		this->CProcess::CloseOuter(dwSessionID, 5000);
		return true;
	}

	PACKET_AH_DISCONNECT ah_disconnect;
	ah_disconnect.PacketType = HEADER_AH_DISCONNECT;
	ah_disconnect.AID = authenticate.m_dwAID;
	ah_disconnect.reason = BAN_ANOTHER_LOGIN;
	g_CharSvrStreamMgr.CStreamManager::Broadcast((char*)&ah_disconnect, sizeof(ah_disconnect));

	SUSERINFO userinfo = {};
	if( !pAccountDB->CAccountDB::GetUserInfo(authenticate.m_dwAID, &userinfo) )
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, " GetUserInfo failed [AID %d][PacketType %d]", authenticate.m_dwAID, HEADER_CA_LOGIN3);

	user.m_nPresentSID = -1;
	user.m_nIsGameStarted = 0;
	user.m_nAID = authenticate.m_dwAID;
	user.m_nSex = userinfo.m_nSex;
	user.m_nIP = m_dwIP;
	user.m_nBirthDay = userinfo.m_nBirthdate;
	user.m_nState = 1;
	user.m_nSecurityCode = rand();
	strcpy_s(user.m_szID, sizeof(user.m_szID), ca_login.ID);
	strcpy_s(user.m_szEmail, sizeof(user.m_szEmail), userinfo.m_szEmail);
	strcpy_s(user.m_szPersonalNum, sizeof(user.m_szPersonalNum), userinfo.m_szPersonalNum);
	user.m_nAccountSID = g_LocalSID;

	//FIXME: 70 lines here were commented/optimized out (may involve the missing AmountRemain/QuantityRemain logic below)

	bool bIsPCBang = CPCBangBillingDB::GetObj()->CPCBangBillingDB::IsPCBangIP(user.m_nIP);
	if( CPCBangBillingDB::GetObj()->CPCBangBillingDB::GetIPBonusLimit(user.m_nIP) )
		user.m_isPCBang = 2;
	else
		user.m_isPCBang = bIsPCBang;

	char szIPBuf[16] = {};
	CNetwork::GetObj()->CNetwork::GetTextIP(user.m_nIP, szIPBuf);
	CEnterTraceLog::GetObj()->CEnterTraceLog::LogFile("NCASH_BillingLog.txt", "ID[%s], IP[%s], AmountRemain[%d], QuantityRemain[%d], isPCBang[%d]", user.m_szID, szIPBuf, 0, 0, user.m_isPCBang);

	g_userList.CUserList::Insert(authenticate.m_dwAID, user);

	userinfo.m_nIP = m_dwIP;
	pConnectLog->CConnectLog::AddConnectLog(ca_login.ID, userinfo.m_nIP, authenticate.m_dwAID, FALSE); // [patch] login/logout event logging

	pAccountDB->CAccountDB::UpdateUserInfo2(user.m_nAID, &userinfo); // [patch] update ip/lasttime column

#if !defined(RFEXE) // [patch] don't send billing packet
	PACKET_SC_BILLING_INFO sc_billing_info;
	sc_billing_info.PacketType = HEADER_SC_BILLING_INFO;
	sc_billing_info.dwAmountRemain = -2;
	sc_billing_info.dwQuantityRemain = -2;
//	sc_billing_info.dwReserved1 = 0; // FIXME: uninitialized
//	sc_billing_info.dwReserved2 = 0; // FIXME: uninitialized
	if( !user.m_bNotPaid )
		this->Send((char*)&sc_billing_info, sizeof(sc_billing_info), dwSessionID, false);
#endif

	int nCount = 0;
	SERVER_ADDR* ServerList = g_characterServerInfo[ca_login.clienttype].CCharacterServerInfo::GetCharacterServerInfo(&nCount);

	PACKET_AC_ACCEPT_LOGIN2 ac_accept_login;
	ac_accept_login.PacketType = HEADER_AC_ACCEPT_LOGIN; //NOTE: wrong packetType
	ac_accept_login.PacketLength = sizeof(ac_accept_login) + nCount * sizeof(SERVER_ADDR);
	ac_accept_login.AID = authenticate.m_dwAID;
	ac_accept_login.lastLoginIP = 0;
//	memset(ac_accept_login.lastLoginTime, '\0', sizeof(ac_accept_login.lastLoginTime)); // FIXME: uninitialized
	ac_accept_login.Sex = userinfo.m_nSex;
	ac_accept_login.userLevel = userinfo.m_nGrade;
	ac_accept_login.iAccountSID = g_LocalSID;
	ac_accept_login.AuthCode = user.m_nSecurityCode;

	// [patch] hide user count in charserver select screen
	std::vector<SERVER_ADDR> tmp(&ServerList[0], &ServerList[nCount]);
	for( int i = 0; i < nCount; ++i )
	{
		tmp[i].usercount = -1; // dummy value
		tmp[i].state = -1; // default handler won't print value
	}

	this->Send((char*)&ac_accept_login, sizeof(ac_accept_login), dwSessionID, false);
	this->Send((char*)&tmp.front(), nCount * sizeof(SERVER_ADDR), dwSessionID, false);

	this->CProcess::CloseOuter(dwSessionID, 8000);
	return true;
}


bool CUserProcess::ProcessPacket_CA_CONNECT_INFO_CHANGED(char* pPacket)
{
	PACKET_CA_CONNECT_INFO_CHANGED& Packet = *reinterpret_cast<PACKET_CA_CONNECT_INFO_CHANGED*>(pPacket);

	if( !g_bXmlFileUserCheck )
		return true;

	Packet.ID[sizeof(Packet.ID)-1] = '\0';
	CEnterTraceLog::GetObj()->CEnterTraceLog::MessagePrint("HEADER_CA_CONNECT_INFO_CHANGED id %s", Packet.ID);
	CEnterTraceLog::GetObj()->CEnterTraceLog::LogFile("bot.txt", "XML INFO CHANGED USER id: %s", Packet.ID);

	if( g_xmlFileUser.CInfoScript::GetInfo(Packet.ID) )
	{
		CEnterTraceLog::GetObj()->CEnterTraceLog::MessagePrint("exist");
		return true;
	}
	else
	{
		CEnterTraceLog::GetObj()->CEnterTraceLog::MessagePrint("not exist");
		return false;
	}
}


bool CUserProcess::ProcessPacket_CA_REQ_HASH(DWORD dwSessionID, char* pPacket, WORD wPacketType, int nPacketSize)
{
	PACKET_CA_REQ_HASH& Packet = *reinterpret_cast<PACKET_CA_REQ_HASH*>(pPacket);

	if( m_bRandStrSent )
		return false;

	char buf[100] = {};
	PACKET_AC_ACK_HASH& ac_ack_hash = *reinterpret_cast<PACKET_AC_ACK_HASH*>(buf);
	ac_ack_hash.PacketType = HEADER_AC_ACK_HASH;
	ac_ack_hash.PacketLength = sizeof(ac_ack_hash) + sizeof(m_RandStr);
	memcpy(ac_ack_hash.Data, m_RandStr, sizeof(m_RandStr));

	m_bRandStrSent = true;
	this->Send((char*)&ac_ack_hash, ac_ack_hash.PacketLength, dwSessionID, false);

	return true;
}
