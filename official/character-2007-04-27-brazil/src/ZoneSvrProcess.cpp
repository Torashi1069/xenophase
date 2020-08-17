#include "Character.h"
#include "CharacterDB.h"
#include "enum.hpp"
#include "PremiumServiceDB.h"
#include "UserList.h"
#include "UserVerify.h"
#include "ZoneServerInfoList.h"
#include "ZoneSvrProcess.h"
#include "Common/GlobalInfoDB.h"
#include "Common/Network.h"
#include "Common/Packet.h"
#include "Common/Reporter.h"
#include "Network3/AsyncProcessMgr.h"
#include "Network3/Stream.h"
#include "Network3/StreamManager.h"


CZoneSvrProcess::CZoneSvrProcess()
{
}


CZoneSvrProcess::~CZoneSvrProcess()
{
}


bool CZoneSvrProcess::OnConnect()
{
	if( CSingleton<CGlobalInfoDB>::getSingletonPtr()->IsColumnPrivateAdded()
	||  CSingleton<CZoneServerInfoList>::getSingletonPtr()->CZoneServerInfoList::IsZoneServer(m_dwIP) )
	{
		char szIP[100];
		CSingleton<CNetwork>::getSingletonPtr()->CNetwork::GetTextIP(m_dwIP, szIP);
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("Zone server %s connected.\n", szIP);
		return true;
	}
	else
	{
		char szIP[100];
		CSingleton<CNetwork>::getSingletonPtr()->CNetwork::GetTextIP(m_dwIP, szIP);
		CSingleton<CReporter>::getSingletonPtr()->CReporter::MessagePrint("not zone server connected %s\n", szIP);
		return false;
	}
}


void CZoneSvrProcess::OnClose()
{
	char szIP[100];
	CSingleton<CNetwork>::getSingletonPtr()->CNetwork::GetTextIP(m_dwIP, szIP);
	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("Zone server %s disconnected.\n", szIP);
}


bool CZoneSvrProcess::OnRecv(char* buffer, int* len)
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
		int nPacketSize = this->CZoneSvrProcess::GetPacketSize(wPacketType);

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

		if( wPacketType == HEADER_ZH_MOVE_PVPWORLD )
		{
			ASYNCPACKET* pAsyncPacket = g_AsyncProcessMgr.CAsyncProcessMgr::AllocPacket();
			if( pAsyncPacket != NULL )
			{
				memset(pAsyncPacket, 0, sizeof(*pAsyncPacket));
				pAsyncPacket->dwSessionID = dwSessionID;
				pAsyncPacket->nPacketSize = nPacketSize;
				memcpy(pAsyncPacket->packet, buffer, nPacketSize);
				pAsyncPacket->pProcessPtr = this;
				pAsyncPacket->wPacketType = HEADER_ZH_MOVE_PVPWORLD;
				g_AsyncProcessMgr.CAsyncProcessMgr::PushPacket(pAsyncPacket, dwSessionID);
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


int CZoneSvrProcess::GetPacketSize(WORD wPacketType)
{
	std::map<int,int>::const_iterator it = g_packetLenMap.find(wPacketType);
	return ( it != g_packetLenMap.end() ) ? it->second : 0;
}


bool CZoneSvrProcess::ProcessPacket(DWORD dwSessionID, char* pPacket, WORD wPacketType, int nPacketSize)
{
	switch( wPacketType )
	{
	case HEADER_SERVER_ENTRY:
		return this->CZoneSvrProcess::ProcessPacket_ServerEntry(dwSessionID, pPacket);
	break;
	case HEADER_ZH_LOGON:
		return this->CZoneSvrProcess::ProcessPacket_Logon(dwSessionID, pPacket);
	break;
	case HEADER_ZH_CHAR_EXIT:
		return this->CZoneSvrProcess::ProcessPacket_CharExit(dwSessionID, pPacket);
	break;
	case HEADER_ZH_SAVECHARINFO:
		return this->CZoneSvrProcess::ProcessPacket_SaveCharInfo(dwSessionID, pPacket);
	break;
	case HEADER_ZH_MAPMOVE:
		return this->CZoneSvrProcess::ProcessPacket_MapMove(dwSessionID, pPacket);
	break;
	case HEADER_SAVE_USING_TIME:
		return this->CZoneSvrProcess::ProcessPacket_SaveUsingTime(dwSessionID, pPacket);
	break;
	case HEADER_ZH_RESTART:
		return this->CZoneSvrProcess::ProcessPacket_Restart(dwSessionID, pPacket);
	break;
	case HEADER_ZH_REQ_REMAINTIME:
		return this->CZoneSvrProcess::ProcessPacket_ReqRemainTime(dwSessionID, pPacket);
	break;
	case HEADER_ZH_MOVE_PVPWORLD:
		return this->CZoneSvrProcess::ProcessPacket_MoveToPVPWorld(dwSessionID, pPacket);
	break;
	default:
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("Header not found, sent from Zone Server %d\n", dwSessionID);
		return false;
	break;
	};
}


bool CZoneSvrProcess::ProcessPacket_ServerEntry(DWORD dwSessionID, char* pPacket)
{
	PACKET_SERVER_ENTRY& Packet = *reinterpret_cast<PACKET_SERVER_ENTRY*>(pPacket);

	return true;
}


bool CZoneSvrProcess::ProcessPacket_Logon(DWORD dwSessionID, char* pPacket)
{
	PACKET_ZH_LOGON& Packet = *reinterpret_cast<PACKET_ZH_LOGON*>(pPacket);

	static CZoneServerInfoList* pZoneServerInfoList = CSingleton<CZoneServerInfoList>::getSingletonPtr();
	static CUserVerify* pUserVerify = CSingleton<CUserVerify>::getSingletonPtr();

	int nSID = pZoneServerInfoList->CZoneServerInfoList::GetSID(m_dwIP);
	pZoneServerInfoList->CZoneServerInfoList::SetUserCount(nSID, Packet.curUser);

	__SUSER__ user;
	if( g_UserList.CUserList::Get(Packet.AID, &user) != TRUE
	||  Packet.AuthCode != user.m_dwSecurityCode
	||  Packet.GID != user.m_nSelectedGID
	||  nSID != user.m_nSID )
	{
		PACKET_HZ_LOGON_ACK hz_logon_ack;
		hz_logon_ack.PacketType = HEADER_HZ_LOGON_NOTEXIST;
		hz_logon_ack.AID = Packet.AID;
		this->Send((char*)&hz_logon_ack, sizeof(hz_logon_ack), dwSessionID, false);
		return true;
	}

	PACKET_HZ_LOGON_ACK hz_logon_ack = {};
	hz_logon_ack.PacketType = HEADER_HZ_LOGON_EXIST;
	hz_logon_ack.AID = Packet.AID;
	hz_logon_ack.GID = Packet.GID;
	memcpy(hz_logon_ack.ID, user.m_szID, sizeof(hz_logon_ack.ID));
	hz_logon_ack.TotalUsingTime = 0;
	hz_logon_ack.selectedCharNum = user.m_nSelectedSlotIndex;
	this->Send((char*)&hz_logon_ack, sizeof(hz_logon_ack), dwSessionID, false);

	pUserVerify->CUserVerify::UpdateUserVerify(Packet.AID, 1200000);

	static CPremiumServiceDB* pPremiumServiceDB = CSingleton<CPremiumServiceDB>::getSingletonPtr();

	char szIP[20] = {};
	CSingleton<CNetwork>::getSingletonPtr()->CNetwork::GetTextIP(user.m_dwIP, szIP);
	CSingleton<CReporter>::getSingletonPtr()->CReporter::MessagePrint("DWIP[%d] SZIP[%s]\n", user.m_dwIP, szIP);

	SExtraExp extraExp = {};
	if( pPremiumServiceDB->CPremiumServiceDB::GetExtraExpInfo(szIP, &extraExp) )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::MessagePrint("exp1(%f) exp2(%f) drp(%f)\n", extraExp.fExp1, extraExp.fExp2, extraExp.fdrp);

		PACKET_HZ_NOTIFY_PCBANG hz_notify_pcbang = {};
		hz_notify_pcbang.PacketTYPE = HEADER_HZ_NOTIFY_PCBANG;
		hz_notify_pcbang.AID = user.m_dwAID;
		hz_notify_pcbang.GID = Packet.GID;
		hz_notify_pcbang.isPCBang = 1;
		hz_notify_pcbang.PayTypeEx = user.m_nPayTypeEx;
		hz_notify_pcbang.ConnectionArea = user.m_nConnectionArea;
		hz_notify_pcbang.ConnectionState = user.m_nConnectionState;
		hz_notify_pcbang.EventNum = user.m_nEventNum;
		hz_notify_pcbang.ConnectionTime = user.m_dwConnectionTime;
		hz_notify_pcbang.ExpFactor = extraExp.fExp1;
		hz_notify_pcbang.ExpFactor2 = extraExp.fExp2;
		hz_notify_pcbang.DropFactor = extraExp.fdrp;
		this->Send((char*)&hz_notify_pcbang, sizeof(hz_notify_pcbang), dwSessionID, false);
	}

	return true;
}


bool CZoneSvrProcess::ProcessPacket_CharExit(DWORD dwSessionID, char* pPacket)
{
	PACKET_ZH_CHAR_EXIT& Packet = *reinterpret_cast<PACKET_ZH_CHAR_EXIT*>(pPacket);

	static CUserVerify* pUserVerify = CSingleton<CUserVerify>::getSingletonPtr();
	static CCharacterDB* pCharacterDB = CSingleton<CCharacterDB>::getSingletonPtr();

	__SUSER__ user = {};
	g_UserList.CUserList::Get(Packet.AID, &user);

	if( Packet.disconnetedType != 1 )
	{
		g_UserList.CUserList::Delete(Packet.AID);
		pUserVerify->CUserVerify::DeleteUserVerify(Packet.AID);
		DeleteConnectCharacter(Packet.AID);
	}

	if( Packet.disconnetedType == 0 )
	{
		PACKET_HA_CHAR_EXIT ha_char_exit;
		ha_char_exit.PacketType = HEADER_HA_CHAR_EXIT;
//		ha_char_exit.TotalUsingTime = 0; // FIXME
		ha_char_exit.AID = Packet.AID;
		ha_char_exit.disconnectedType = NORMAL_DISCONNECT;
		g_AccountStreamMgr.CStreamManager::Broadcast((char*)&ha_char_exit, sizeof(ha_char_exit));
	}

	return true;
}


bool CZoneSvrProcess::ProcessPacket_SaveCharInfo(DWORD dwSessionID, char* pPacket)
{
	PACKET_ZH_SAVECHARINFO& Packet = *reinterpret_cast<PACKET_ZH_SAVECHARINFO*>(pPacket);

	static CUserVerify* pUserVerify = CSingleton<CUserVerify>::getSingletonPtr();
	pUserVerify->CUserVerify::UpdateUserVerify(Packet.AID, 1200000);

	PACKET_HA_PCINFOUPDATE ha_pcinfoupdate;
	ha_pcinfoupdate.PacketType = HEADER_HA_PCINFOUPDATE;
	ha_pcinfoupdate.AID = Packet.AID;
	g_AccountStreamMgr.CStreamManager::Broadcast((char*)&ha_pcinfoupdate, sizeof(ha_pcinfoupdate));

	return true;
}


bool CZoneSvrProcess::ProcessPacket_MapMove(DWORD dwSessionID, char* pPacket)
{
	PACKET_ZH_MAPMOVE& Packet = *reinterpret_cast<PACKET_ZH_MAPMOVE*>(pPacket);

	__SUSER__ user;
	if( g_UserList.CUserList::Get(Packet.AID, &user) == TRUE )
	{
		user.m_nSID = Packet.ServerID;
		g_UserList.CUserList::Insert(Packet.AID, user);
	}

	PACKET_HZ_ACK_MAPMOVE hz_ack_mapmove;
	hz_ack_mapmove.PacketType = HEADER_HZ_ACK_MAPMOVE;
	hz_ack_mapmove.NID = Packet.NID;
	hz_ack_mapmove.AID = Packet.AID;
	this->Send((char*)&hz_ack_mapmove, sizeof(hz_ack_mapmove), dwSessionID, false);

	return true;
}


bool CZoneSvrProcess::ProcessPacket_Restart(DWORD dwSessionID, char* pPacket)
{
	PACKET_ZH_RESTART& Packet = *reinterpret_cast<PACKET_ZH_RESTART*>(pPacket);

	static CUserVerify* pUserVerify = CSingleton<CUserVerify>::getSingletonPtr();
	static CCharacterDB* pCharacterDB = CSingleton<CCharacterDB>::getSingletonPtr();

	__SUSER__ user = {};
	g_UserList.CUserList::Bring(Packet.AID, &user);
	pUserVerify->CUserVerify::DeleteUserVerify(Packet.AID);

	PACKET_HZ_ACK_RESTART hz_ack_restart;
	hz_ack_restart.PacketType = HEADER_HZ_ACK_RESTART;
	hz_ack_restart.AID = Packet.AID;
	this->Send((char*)&hz_ack_restart, sizeof(hz_ack_restart), dwSessionID, false);

	return true;
}


bool CZoneSvrProcess::ProcessPacket_SaveUsingTime(DWORD dwSessionID, char* pPacket)
{
	PACKET_SAVE_USING_TIME& Packet = *reinterpret_cast<PACKET_SAVE_USING_TIME*>(pPacket);

	return true;
}


bool CZoneSvrProcess::ProcessPacket_ReqRemainTime(DWORD dwSessionID, char* pPacket)
{
	PACKET_REQ_REMAINTIME& Packet = *reinterpret_cast<PACKET_REQ_REMAINTIME*>(pPacket);

	Packet.PacketType = HEADER_HA_REQ_REMAINTIME;
	g_AccountStreamMgr.CStreamManager::Broadcast((char*)&Packet, sizeof(Packet));

	return true;
}


bool CZoneSvrProcess::ProcessPacket_MoveToPVPWorld(DWORD dwSessionID, char* pPacket)
{
	PACKET_ZH_MOVE_PVPWORLD& Packet = *reinterpret_cast<PACKET_ZH_MOVE_PVPWORLD*>(pPacket);

	int nGID = Packet.GID;

	static CCharacterDB* charDB = CSingleton<CCharacterDB>::getSingletonPtr();
	static CPVPCharacterDB* pvpDB = CSingleton<CPVPCharacterDB>::getSingletonPtr();
	static CPvPPointDB* pointDB = CSingleton<CPvPPointDB>::getSingletonPtr();

	static LONG count;
	DWORD nowCount = InterlockedIncrement(&count) % 100;

	SCHARINFO charinfo;
	if( charDB->CCharacterDB::GetCharInfoByGID(nGID, &charinfo) != TRUE )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("Error(MoveToPVPWord): Can't read CHARINFO from GID(%d)", nGID);
		return true;
	}

	SCHARINFO pvpCharInfo[MAX_CHARINFO_SLOT_COUNT];
	int nCharInfo = pvpDB->CCharacterDBBase::GetCharInfo(charinfo.m_nAID, pvpCharInfo, true);
	for( int i = 0; i < nCharInfo; ++i )
		pvpDB->CCharacterDBBase::DeleteCharInfo(pvpCharInfo[i].m_nGID);

	size_t len1 = strlen(gLocalServerInfo.m_szName);
	size_t len2 = strlen(charinfo.m_szName);

	if( strlen(gLocalServerInfo.m_szName) > 16 )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("Error(MoveToPVPWord): Too long ServerName(%s)", gLocalServerInfo.m_szName);
		return true;
	}

	char temp[24];
	strcpy(&temp[0], gLocalServerInfo.m_szName);
	temp[len1] = '-';
	strncpy(&temp[len1 + 1], charinfo.m_szName, 22 - len1);
	size_t len = len2 + len1 + 1;
	if( len > 21 )
	{
		len = 21;
		if( temp[19] < 128 && temp[20] >= 128 )
			len = 20;
	}
	temp[len + 0] = char(nowCount / 10) + '0';
	temp[len + 1] = char(nowCount % 10) + '0';
	temp[len + 2] = '\0';

	strcpy(charinfo.m_szName, temp);
	strcpy(charinfo.m_szMapName, "prontera.gat");
	strcpy(charinfo.m_szRestartMapName, "prontera.gat");
	charinfo.m_nSxPos = 117;
	charinfo.m_nXPos = 117;
	charinfo.m_nSyPos = 96;
	charinfo.m_nYPos = 96;

	if( pvpDB->CPVPCharacterDB::CopyCharInfo(&charinfo) != TRUE )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("Error(MoveToPVPWord): Can't Copy CharInfo To PVPWorld(%s)/User that have same name exist", charinfo.m_szName);
		return true;
	}

	pvpDB->CCharacterDBBase::GetCharInfo(charinfo.m_nAID, pvpCharInfo, true);
	int pvpGID = pvpCharInfo[0].m_nGID;

	char SkillInfo[256] = {};
	SQLINTEGER SkillSize;
	if( charDB->CCharacterDB::GetSkill(nGID, SkillInfo, &SkillSize) == TRUE )
		pvpDB->CPVPCharacterDB::MakeSkill(pvpGID, SkillInfo, SkillSize);

	char ItemInfo[4000] = {};
	SQLINTEGER ItemSize;
	if( charDB->CCharacterDB::GetItem(nGID, ItemInfo, &ItemSize) == TRUE )
		pvpDB->CPVPCharacterDB::MakeItem(pvpGID, ItemInfo, ItemSize);

	if( pointDB->CPvPPointDB::InitPoint(charinfo.m_nAID, charinfo.m_szName) != TRUE )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("Error(MoveToPVPWord): Can't Initialize Point Table(%s)", charinfo.m_szName);
		return true;
	}

	return true;
}
