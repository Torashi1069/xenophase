#include "AccountProcess.h"
#include "Character.h"
#include "CZsvrStreamMgr.h"
#include "PremiumServiceDB.h"
#include "PremiumServiceInfo.h"
#include "UserAuthenticate.h"
#include "UserList.h"
#include "UserProcess.h"
#include "UserVerify.h"
#include "Common/EnterTraceLog.h"
#include "Common/Network.h"
#include "Common/NOutputTextMgr.h"
#include "Common/NSyncObject.h"
#include "Common/Packet.h"
#include "Common/PacketLengthExMgr.h"
#include "Common/ServerInfoList.h"
#include "Network3/AsyncProcessMgr.h"
#include "Network3/Stream.h"
#include "Network3/StreamManager.h"
#include "Enums.h" // enumBANTYPE


int GetAge(char* pszPersonalNumber)
{
	if( strlen(pszPersonalNumber) < 6 )
		return 0;

	int nYear = 0, nMonth = 0, nDay = 0;
	sscanf(pszPersonalNumber, "%2d%2d%2d", &nYear, &nMonth, &nDay);

	time_t curTime = time(NULL);
	tm* t = localtime(&curTime);

	if( nYear <= t->tm_year % 100 )
		nYear += 2000;
	else
		nYear += 1900;

	int nAge = 1900 + t->tm_year - nYear;
	return nAge;
}


CAccountProcess::CAccountProcess()
{
	m_nBeforePKTHeader = 0;
	m_nBeforePKTRecvLength = 0;
	m_nBeforeOrgPKTSize = 0;
}


CAccountProcess::~CAccountProcess()
{
}


bool CAccountProcess::OnConnect()
{
	char szIP[100] = {};
	CNetwork::GetObj()->CNetwork::GetTextIP(m_dwIP, szIP);
	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("account server[%s] connected.", CNetwork::GetObj()->CNetwork::GetTextIP(m_dwIP).c_str());
	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "account server[%s]  connected", szIP);

	g_bAccountConnected = true;
	return true;
}


void CAccountProcess::OnClose()
{
	g_bAccountConnected = false;

	char szIP[100] = {};
	CNetwork::GetObj()->CNetwork::GetTextIP(m_dwIP, szIP);
	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "account server %s disconnected\n", szIP);
	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("account server[%s] disconnected.", CNetwork::GetObj()->CNetwork::GetTextIP(m_dwIP).c_str());
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
		std::pair<CPacketLengthExMgr::enumFixedPacketRet,int> ret = g_packetLenMapEx.CPacketLengthExMgr::IsFixedPacket(wPacketType);

		int nPacketSize;
		if( ret.first == CPacketLengthExMgr::FIXED )
		{
			nPacketSize = ret.second;
		}
		else
		if( ret.first == CPacketLengthExMgr::VARIABLE )
		{
			if( remain < sizeof(PACKETV) )
				break; // need more data.

			nPacketSize = reinterpret_cast<PACKETV*>(buffer)->PacketLength;
			if( nPacketSize < ret.second )
				return false; // invalid data?
		}
		else
		{
			CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "recv not defined [pkt: %d] [len: %d] [BeforePKT: %d] [BeforePKTRecvSize: %d] [BeforePKTOrgSize: %d]", wPacketType, total_len, m_nBeforePKTHeader, m_nBeforePKTRecvLength, m_nBeforeOrgPKTSize);
			return false; // unknown packet.
		}

		if( nPacketSize > 1024 || nPacketSize < 2 )
			return false; // invalid data?

		if( nPacketSize > remain )
			break; // need more data.

		if( wPacketType == HEADER_AH_LOGON_EXIST
		||  wPacketType == HEADER_AH_LOGON_EXIST_SESSION
		||  wPacketType == HEADER_AH_LOGON_EXIST_PCBANG
		||	wPacketType == HEADER_AH_LOGON_EXIST_PCBANG_HAN
		||  wPacketType == HEADER_AH_LOGON_ACK_EXTEND_BILLING_INFO
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
			else
			if( wPacketType == HEADER_AH_LOGON_EXIST_PCBANG_HAN )
				pkt_index = reinterpret_cast<PACKET_AH_LOGON_ACK_PCBANG*>(buffer)->AID;
			else
			if( wPacketType == HEADER_AH_LOGON_ACK_EXTEND_BILLING_INFO )
				pkt_index = reinterpret_cast<PACKET_AH_LOGON_ACK_EXTEND_BILLING_INFO*>(buffer)->AID;

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
			{
				CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "ProcessPacket Failed. [PKTType: %d], [PKTSize: %d]", wPacketType, nPacketSize);
				return false;
			}
		}

		processed_len += nPacketSize;
		buffer += nPacketSize;

		m_nBeforePKTHeader = wPacketType;
		m_nBeforePKTRecvLength = total_len;
		m_nBeforeOrgPKTSize = nPacketSize;
	}

	*len = processed_len;
	return true;
}


bool CAccountProcess::ProcessPacket(DWORD dwSessionID, char* pPacket, WORD wPacketType, int nPacketSize)
{
	switch( wPacketType )
	{
	case HEADER_AH_LOGON_EXIST:
	case HEADER_AH_LOGON_EXIST_PCBANG:
	case HEADER_AH_LOGON_EXIST_PCBANG_HAN:
	case HEADER_AH_LOGON_ACK_EXTEND_BILLING_INFO:
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
	case HEADER_AH_NOTIFY_PCBANG_PLAYING_TIME:
		return this->CAccountProcess::ProcessPacket_notify_pcbang_playing_time(dwSessionID, pPacket);
	break;
	case HEADER_AH_DISPATCH_PREMIUM_INFO:
		return this->CAccountProcess::ProcessPacket_DispatchPremiumInfo(dwSessionID, pPacket);
	break;
	case HEADER_AH_UPDATE_PCBANG_CNT:
		return this->CAccountProcess::ProcessPacket_UpDatePcBangCnt(dwSessionID, pPacket);
	break;
	case HEADER_AH_DISPATCH_PREMIUM_INFO_CHN:
		return this->CAccountProcess::ProcessPacket_AH_DISPATCH_PREMIUM_INFO_CHN(dwSessionID, pPacket);
	break;
	default:
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Header not found, sent from Account Server %d\n", wPacketType);
		return false;
	break;
	};
}


bool CAccountProcess::ProcessPacket_Billing_Ack(DWORD dwSessionID, char* pPacket)
{
	PACKET_AH_BILLING_ACK& Packet = *reinterpret_cast<PACKET_AH_BILLING_ACK*>(pPacket);

	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "This Message Never Recv CharSvr Check Account\n");

	return true;
}


bool CAccountProcess::ProcessPacket_LogonPermit(DWORD dwSessionID, char* pPacket)
{
	PACKET_AH_LOGON_ACK& Packet = *reinterpret_cast<PACKET_AH_LOGON_ACK*>(pPacket);

	__SUSERAUTHENTICATE__ userAuthenticate;
	if( !g_UserAuthenticate.CUserAuthenticate::Bring(Packet.AID, &userAuthenticate) )
		return true;

	if( g_bEnableAdultCheck && GetAge(Packet.PERSONALNUMBER) < 18 )
	{
		PACKET_SC_NOTIFY_BAN sc_notify_ban;
		sc_notify_ban.PacketType = HEADER_SC_NOTIFY_BAN;
		sc_notify_ban.ErrorCode = BAN_UNDER_AGE;

		if( userAuthenticate.m_pUserProcess != NULL )
		{
			userAuthenticate.m_pUserProcess->Send((char*)&Packet.AID, sizeof(Packet.AID), userAuthenticate.m_dwSessionID, false);
			userAuthenticate.m_pUserProcess->Send((char*)&sc_notify_ban, sizeof(sc_notify_ban), userAuthenticate.m_dwSecurityCode, false);
			userAuthenticate.m_pUserProcess->CUserProcess::CloseForce(userAuthenticate.m_dwSessionID, 5000);

			PACKET_HA_CHAR_EXIT ha_char_exit;
			ha_char_exit.PacketType = HEADER_HA_CHAR_EXIT;
			ha_char_exit.TotalUsingTime = 0;
			ha_char_exit.AID = Packet.AID;
			ha_char_exit.disconnectedType = NORMAL_DISCONNECT;
			g_AccountStreamMgr.CStreamManager::Broadcast((char*)&ha_char_exit, sizeof(ha_char_exit));
		}

		return true;
	}

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
	memcpy(user.m_szPersonalNumber, Packet.PERSONALNUMBER, 24);
	memcpy(user.m_szEMail, Packet.emailAddress, 40);
	memcpy(user.m_szID, Packet.ID, 24);
	user.m_dwAID = Packet.AID;

	if( Packet.PacketType == HEADER_AH_LOGON_EXIST_PCBANG || Packet.PacketType == HEADER_AH_LOGON_EXIST_PCBANG_HAN )
	{
		PACKET_AH_LOGON_ACK_PCBANG& Packet = *reinterpret_cast<PACKET_AH_LOGON_ACK_PCBANG*>(pPacket);
		user.m_dwIP = Packet.m_dwIP;
		user.m_nPCBangGrade = Packet.m_nPCBangGrade;
		user.m_bIsPCBang = ( user.m_nPCBangGrade > 0 );
		user.m_nPayTypeEx = Packet.m_nPayTypeEx;
		user.m_nConnectionArea = Packet.m_nConnectionArea;
		user.m_nConnectionState = Packet.m_nConnectionState;
		user.m_nEventNum = Packet.m_nEventNum;
		user.m_dwConnectionTime = Packet.m_dwConnectionTime;
		memcpy(user.m_szCharDelKey, Packet.m_szCharDelKey, 24); user.m_szCharDelKey[24] = '\0';
	}

	if( Packet.PacketType != HEADER_AH_LOGON_RUS )
	{
		if( Packet.PacketType == HEADER_AH_LOGON_ACK_EXTEND_BILLING_INFO )
		{
			PACKET_AH_LOGON_ACK_EXTEND_BILLING_INFO& Packet = *reinterpret_cast<PACKET_AH_LOGON_ACK_EXTEND_BILLING_INFO*>(pPacket);
			user.m_wRateType = Packet.wRateType;
			user.m_dwPERSONGRADE = Packet.dwPERSONGRADE;
		}
		else
		if( Packet.PacketType == HEADER_AH_LOGON_EXIST_PCBANG )
		{
			PACKET_AH_LOGON_ACK_PCBANG& Packet = *reinterpret_cast<PACKET_AH_LOGON_ACK_PCBANG*>(pPacket);
			user.m_wRateType = Packet.m_nPayTypeEx;
		}
	}

	g_UserList.CUserList::Insert(Packet.AID, user);
	static CUserVerify* pUserVerify = CSingleton<CUserVerify>::getSingletonPtr();
	pUserVerify->CUserVerify::UpdateUserVerify(Packet.AID, 1500000);
	userAuthenticate.m_pUserProcess->CUserProcess::OnLogonAck(pPacket, userAuthenticate.m_dwSessionID, Packet.AID);

	return true;
}


bool CAccountProcess::ProcessPacket_LogonPermit_Session(DWORD dwSessionID, char* pPacket)
{
	PACKET_AH_LOGON_ACK_SESSION& Packet = *reinterpret_cast<PACKET_AH_LOGON_ACK_SESSION*>(pPacket);

	__SUSERAUTHENTICATE__ userAuthenticate;
	if( !g_UserAuthenticate.CUserAuthenticate::Bring(Packet.AID, &userAuthenticate) )
		return true;

	if( g_bEnableAdultCheck && GetAge(Packet.PERSONALNUMBER) < 18 )
	{
		PACKET_SC_NOTIFY_BAN sc_notify_ban;
		sc_notify_ban.PacketType = HEADER_SC_NOTIFY_BAN;
		sc_notify_ban.ErrorCode = BAN_UNDER_AGE;

		if( userAuthenticate.m_pUserProcess != NULL )
		{
			userAuthenticate.m_pUserProcess->Send((char*)&Packet.AID, sizeof(Packet.AID), userAuthenticate.m_dwSessionID, false);
			userAuthenticate.m_pUserProcess->Send((char*)&sc_notify_ban, sizeof(sc_notify_ban), userAuthenticate.m_dwSessionID, false);
			userAuthenticate.m_pUserProcess->CUserProcess::CloseForce(userAuthenticate.m_dwSessionID, 5000);
		}

		return true;
	}

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
	user.m_dwAID = Packet.AID;
	memcpy(user.m_szEMail, Packet.emailAddress, 50);
	memcpy(user.m_szID, Packet.ID, 24);
	memcpy(user.m_szPersonalNumber, Packet.PERSONALNUMBER, 24-1);
	g_UserList.CUserList::Insert(Packet.AID, user);

	if( userAuthenticate.m_pUserProcess != NULL )
	{
		PACKET_AH_LOGON_ACK tmpPacket;
		tmpPacket.AID = Packet.AID;
		memcpy(tmpPacket.emailAddress, Packet.emailAddress, sizeof(tmpPacket.emailAddress));
		memcpy(tmpPacket.ID, Packet.ID, sizeof(tmpPacket.ID));
		memcpy(tmpPacket.PERSONALNUMBER, Packet.PERSONALNUMBER, sizeof(tmpPacket.PERSONALNUMBER));
		tmpPacket.TotalUsingTime = Packet.TotalUsingTime;
		tmpPacket.PacketType = ( Packet.PacketType == HEADER_AH_LOGON_EXIST_SESSION ) ? HEADER_AH_LOGON_EXIST : HEADER_AH_LOGON_NOTEXIST;

		userAuthenticate.m_pUserProcess->CUserProcess::OnLogonAck(&tmpPacket, userAuthenticate.m_dwSessionID, dwSessionID);
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
		userAuthenticate.m_pUserProcess->CUserProcess::OnLogonAck(&Packet, userAuthenticate.m_dwSessionID, 0);

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

		userAuthenticate.m_pUserProcess->CUserProcess::OnLogonAck(&tmpPacket, userAuthenticate.m_dwSessionID, 0);
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

	__SUSERAUTHENTICATE__ UserAuthenticate = {};
	BOOL bRetUserAuthe = g_UserAuthenticate.CUserAuthenticate::Bring(Packet.AID, &UserAuthenticate);

	__SUSER__ user = {};
	BOOL bRetUserBring = g_UserList.CUserList::Bring(Packet.AID, &user);

	if( !bRetUserAuthe && !bRetUserBring )
		return true;

	if( gconfig.nServerType == 0 || gconfig.nServerType == 2 )
	{
		if( Packet.reason == BAN_PAY_OUT )
			return true;

		if( Packet.reason == BAN_PAY_CHANGE )
		{
			if( user.m_wRateType != 1 )
				return true;

			if( gconfig.nPremium_User_Slot > user.m_nSelectedSlotIndex )
			{
				if( user.m_nSID > 0 )
				{
					PACKET_HZ_NOTIFY_PCBANG hz_notify_pcbang = {};
					hz_notify_pcbang.PacketType = HEADER_HZ_NOTIFY_PCBANG;
					hz_notify_pcbang.AID = user.m_dwAID;
					hz_notify_pcbang.GID = user.m_nSelectedGID;
					hz_notify_pcbang.isPCBang = 1;
					hz_notify_pcbang.PayType = user.m_nPayTypeEx;
					hz_notify_pcbang.ConnectionArea = user.m_nConnectionArea;
					hz_notify_pcbang.ConnectionState = user.m_nConnectionState;
					hz_notify_pcbang.EventNum = user.m_nEventNum;
					hz_notify_pcbang.ConnectionTime = user.m_dwConnectionTime;
					hz_notify_pcbang.ExpFactor = 1.0f;
					hz_notify_pcbang.ExpFactor2 = 0.05f;
					hz_notify_pcbang.DropFactor = 1.0f;

					if( user.m_bIsPCBang )
					{
						static CPremiumServiceDB* pPremiumServiceDB = CSingleton<CPremiumServiceDB>::getSingletonPtr();
						if( pPremiumServiceDB->CPremiumServiceDB::Get(user.m_dwIP) )
						{
							hz_notify_pcbang.ExpFactor = pPremiumServiceDB->m_defaultExp.fExp1;
							hz_notify_pcbang.ExpFactor2 = pPremiumServiceDB->m_defaultExp.fExp2;
							hz_notify_pcbang.DropFactor = pPremiumServiceDB->m_defaultExp.fdrp;
						}
					}

					g_ZoneSvrStreamMgr.CStreamManager::Broadcast((char*)&hz_notify_pcbang, sizeof(hz_notify_pcbang));
				}

				user.m_wRateType = 0;
				user.m_bIsPCBang = false;
				g_UserList.CUserList::Insert(Packet.AID, user);
				return true;
			}
		}
	}

	PACKET_SC_NOTIFY_BAN sc_notify_ban;
	sc_notify_ban.PacketType = HEADER_SC_NOTIFY_BAN;
	sc_notify_ban.ErrorCode = Packet.reason;

	switch( sc_notify_ban.ErrorCode )
	{
	case BAN_IP_OVERFLOW:
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "ProcessPacket_Disconnect - %s  reason: BAN_IP_OVERFLOW(%d)\n", user.m_szID, Packet.reason);
	break;
	case BAN_PAY_OUT:
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "ProcessPacket_Disconnect - %s  reason: BAN_PAY_OUT(%d)\n", user.m_szID, Packet.reason);
	break;
	case BAN_PAY_SUSPEND:
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "ProcessPacket_Disconnect - %s  reason: BAN_PAY_SUSPEND(%d)\n", user.m_szID, Packet.reason);
	break;
	case BAN_PAY_CHANGE:
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "ProcessPacket_Disconnect - %s  reason: BAN_PAY_CHANGE(%d)\n", user.m_szID, Packet.reason);
		sc_notify_ban.ErrorCode = BAN_PAY_OUT;
	break;
	case BAN_PAY_WRONGIP:
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "ProcessPacket_Disconnect - %s  reason: BAN_PAY_WRONGIP(%d)\n", user.m_szID, Packet.reason);
	break;
	case BAN_PAY_PNGAMEROOM:
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "ProcessPacket_Disconnect - %s  reason: BAN_PAY_PNGAMEROOM(%d)\n", user.m_szID, Packet.reason);
	break;
	case BAN_NOT_SETTLED:
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "ProcessPacket_Disconnect - %s  reason: BAN_NOT_SETTLED(%d)\n", user.m_szID, Packet.reason);
	break;
	case BAN_PC_IP_UNFAIR:
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "ProcessPacket_Disconnect - %s  reason: BAN_PC_IP_UNFAIR(%d)\n", user.m_szID, Packet.reason);
	break;
	case BAN_UNFAIR:
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "ProcessPacket_Disconnect - %s  reason: BAN_UNFAIR(%d)\n", user.m_szID, Packet.reason);
	break;
	case BAN_SHUTDOWN_TEENAGER:
//	case BAN_PLANNED_TIME_SHUTDOWN: //FIXME
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "ProcessPacket_Disconnect - %s  reason: (BAN_SHUTDOWN_TEENAGER || BAN_PLANNED_TIME_SHUTDOWN) - (%d)\n", user.m_szID, Packet.reason);
	break;
	case BAN_BILLING_SERVER_ERROR:
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "ProcessPacket_Disconnect - %s  reason: BAN_BILLING_SERVER_ERROR(%d)\n", user.m_szID, Packet.reason);
	break;
	default:
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "ProcessPacket_Disconnect - %s  default [%d] \n", user.m_szID, Packet.reason);
	break;
	};

	if( bRetUserAuthe )
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

	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Recv - ACC ProcessPacket_ack_LimitInfo\n");
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


bool CAccountProcess::ProcessPacket_DispatchPremiumInfo(DWORD dwSessionID, char* pPacket)
{
	PACKET_AH_DISPATCH_PREMIUM_INFO& ah_dispatch_premium_info = *reinterpret_cast<PACKET_AH_DISPATCH_PREMIUM_INFO*>(pPacket);

	if( ah_dispatch_premium_info.reason != 1 )
		return true;

	__SUSER__ user = {};
	if( !g_UserList.CUserList::Bring(ah_dispatch_premium_info.AID, &user) )
		return true;

	user.m_nPCBangGrade = ah_dispatch_premium_info.wPCBangGrade;
	user.m_dwPERSONGRADE = ah_dispatch_premium_info.dwPERSONGRADE;

	PACKET_HZ_PERSONAL_INFORMATION packet = {};
	packet.PacketType = HEADER_HZ_PERSONAL_INFORMATION;
	packet.ExpFactor += 1.0f;
	packet.ExpFactor2 += 1.0f;
	packet.DropFactor += 1.0f;

	PERSONAL_PREMIUM_INFO::PREMIUM_SVC_INFO prmInfo;
	CPremiumServiceInfo::GetObj()->CPremiumServiceInfo::GetInfo(ah_dispatch_premium_info.dwPERSONGRADE, &prmInfo);

	packet.AID = user.m_dwAID;
	packet.GID = user.m_nSelectedGID;
	packet.isPCBang = 1;
	packet.PayType = user.m_nPayTypeEx;
	packet.ConnectionArea = user.m_nConnectionArea;
	packet.ConnectionState = user.m_nConnectionState;
	packet.EventNum = user.m_nEventNum;
	packet.ConnectionTime = user.m_dwConnectionTime;
	packet.ExpFactor = prmInfo.fExp;
	packet.ExpFactor2 = prmInfo.fDeath;
	packet.DropFactor = prmInfo.fDrop;
//	packet.PremiumType = 0;
//	packet.PremiumType2 = 0;
//	packet.SpareType4 = 0;
	packet.MaxStoreCnt = prmInfo.nMaxStoreCnt;

	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "HZ_PERSONAL_INFORMATION: AID(%d) e1(%.2f) e2(%.2f) d(%.2f) IsPCBang(%d) PrmType(%d) PrmType2(%d)", user.m_dwAID, prmInfo.fExp, prmInfo.fDeath, prmInfo.fDrop, 1, packet.PremiumType, packet.PremiumType2);
	g_ZoneSvrStreamMgr.CStreamManager::Broadcast((char*)&packet, sizeof(packet));
	g_UserList.CUserList::Insert(ah_dispatch_premium_info.AID, user);

	return true;
}


bool CAccountProcess::ProcessPacket_notify_pcbang_playing_time(DWORD dwSessionID, char* pPacket)
{
	PACKET_AH_NOTIFY_PCBANG_PLAYING_TIME& Packet = *reinterpret_cast<PACKET_AH_NOTIFY_PCBANG_PLAYING_TIME*>(pPacket);
	
	return true;
}


bool CAccountProcess::ProcessPacket_UpDatePcBangCnt(DWORD dwSessionID, char* pPacket)
{
	return true;
}


bool CAccountProcess::ProcessPacket_AH_DISPATCH_PREMIUM_INFO_CHN(DWORD dwSessionID, char* pPacket)
{
	return true;
}
