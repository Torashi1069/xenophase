#include "Character.h"
#include "CharacterDB.h"
#include "Enums.h"
#include "PremiumServiceDB.h"
#include "UserList.h"
#include "UserVerify.h"
#include "ZoneServerInfoList.h"
#include "ZoneSvrProcess.h"
#include "Common/DBProxy.h"
#include "Common/EnterTraceLog.h"
#include "Common/GlobalInfoDB.h"
#include "Common/Network.h"
#include "Common/NOutputTextMgr.h"
#include "Common/Packet.h"
#include "Common/PacketLengthExMgr.h"
#include "Network3/AsyncProcessMgr.h"
#include "Network3/Stream.h"
#include "Network3/StreamManager.h"


namespace {
std::vector<char> MakeHZ_PERSONAL_INFORMATION_THAI(__SUSER__& in_User, bool flag, CPremiumServiceDB* in_pPrmSvcDB)
{
	PACKET_HZ_PERSONAL_INFORMATION_THAI personal_packet = {};
	personal_packet.PacketType = HEADER_HZ_PERSONAL_INFORMATION_THAI;
	personal_packet.isPCBang = 0;
	personal_packet.PremiumType2 = 0;
	personal_packet.flag = flag;
	personal_packet.Exp = 100;
	personal_packet.Drop = 100;
	personal_packet.MaxStoreCnt = 300;
	personal_packet.AID = in_User.m_dwAID;

	PACKET_ZC_PERSONAL_INFOMATION::DETAIL_EXP_INFO pcInfo = { PACKET_ZC_PERSONAL_INFOMATION::DETAIL_EXP_INFO::DETAIL_PC_EXP_INFO };
	PACKET_ZC_PERSONAL_INFOMATION::DETAIL_EXP_INFO prmInfo = { PACKET_ZC_PERSONAL_INFOMATION::DETAIL_EXP_INFO::DETAIL_PRM_EXP_INFO };

	std::tr1::tuple<bool,float,float,float,int> ipbonusRet = in_pPrmSvcDB->CPremiumServiceDB::GetExp(in_User.m_dwAID, in_User.m_dwIP);
	std::tr1::tuple<bool,float,float,float> prmRet = in_pPrmSvcDB->CPremiumServiceDB::GetPremiumIPBonus(in_User.m_dwAID);

	if( std::tr1::get<0>(prmRet) == true )
	{
		prmInfo.Exp = int(std::tr1::get<1>(prmRet) * 100.0);
		prmInfo.Death = int(std::tr1::get<2>(prmRet) * 100.0);
		prmInfo.Drop = int(std::tr1::get<3>(prmRet) * 100.0);
		prmInfo.InfoType = PACKET_ZC_PERSONAL_INFOMATION::DETAIL_EXP_INFO::DETAIL_PRM_EXP_INFO;
		personal_packet.PremiumType2 = 1;
	}

	if( std::tr1::get<0>(ipbonusRet) == true && std::tr1::get<4>(ipbonusRet) > 0 )
	{
		pcInfo.Exp = int(std::tr1::get<1>(ipbonusRet) * 100.0);
		pcInfo.Death = int(std::tr1::get<2>(ipbonusRet) * 100.0);
		pcInfo.Drop = int(std::tr1::get<3>(ipbonusRet) * 100.0);
		pcInfo.InfoType = PACKET_ZC_PERSONAL_INFOMATION::DETAIL_EXP_INFO::DETAIL_PC_EXP_INFO;
		personal_packet.isPCBang = 1;
	}

	personal_packet.Exp += prmInfo.Exp + pcInfo.Exp;
	personal_packet.Death += pcInfo.Death + prmInfo.Death;
	personal_packet.Drop += pcInfo.Drop + prmInfo.Drop;

	if( gconfig.nServerType == 2 ) // premium
		personal_packet.MaxStoreCnt = 600;

	std::string ClientIP = CNetwork::GetObj()->CNetwork::GetTextIP(in_User.m_dwIP);
	CEnterTraceLog::GetObj()->CEnterTraceLog::LogFmt(__FILE__, __LINE__, INADDR_ANY, "Client IP %s, out %d %d %d, 창고갯수 %d, 서버타입 %d, prm %d %d %d pc %d %d %d, limit %d", ClientIP.c_str(), personal_packet.Exp, personal_packet.Death, personal_packet.Drop, personal_packet.MaxStoreCnt, gconfig.nServerType, prmInfo.Exp, prmInfo.Death, prmInfo.Drop, pcInfo.Exp, pcInfo.Death, pcInfo.Drop, std::tr1::get<4>(ipbonusRet));

	std::vector<char> result;
	result.insert(result.end(), (char*)&personal_packet, (char*)&personal_packet + sizeof(personal_packet));
	result.insert(result.end(), (char*)&pcInfo, (char*)&pcInfo + sizeof(pcInfo));
	result.insert(result.end(), (char*)&prmInfo, (char*)&prmInfo + sizeof(prmInfo));
	reinterpret_cast<PACKET_HZ_PERSONAL_INFORMATION_THAI*>(&result.front())->PacketLength = (short)result.size();

	return result;
}
};


CZoneSvrProcess::CZoneSvrProcess()
{
//	m_nZoneListenPort = 0;
	m_nBeforePKTHeader = 0;
	m_nBeforePKTRecvLength = 0;
	m_nBeforeOrgPKTSize = 0;
}


CZoneSvrProcess::~CZoneSvrProcess()
{
}


bool CZoneSvrProcess::OnConnect()
{
	char szIP[100];
	CNetwork::GetObj()->CNetwork::GetTextIP(m_dwIP, szIP);
	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Zone server %s connected.", szIP);
	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("Zone server %s connected.", CNetwork::GetObj()->CNetwork::GetTextIP(m_dwIP).c_str());

	return true;
}


void CZoneSvrProcess::OnClose()
{
	char szIP[20];
	CNetwork::GetObj()->CNetwork::GetTextIP(m_dwIP, szIP);
	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Zone server %s disconnected.", szIP);
	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("Zone server %s disconnected.", CNetwork::GetObj()->CNetwork::GetTextIP(m_dwIP).c_str());
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
		m_nBeforePKTRecvLength = *len;
		m_nBeforeOrgPKTSize = nPacketSize;
	}

	*len = processed_len;
	return true;
}


bool CZoneSvrProcess::ProcessPacket(DWORD dwSessionID, char* pPacket, WORD wPacketType, int nPacketSize)
{
	switch( wPacketType )
	{
	case HEADER_ZH_PING:
		return this->CZoneSvrProcess::ProcessPacket_ZH_PING(dwSessionID, pPacket);
	break;
	case HEADER_ZH_PING_LIVE:
		this->CZoneSvrProcess::OnZI_PING_LIVE(dwSessionID, *reinterpret_cast<const PACKET_ZH_PING_LIVE*>(pPacket));
		return true;
	break;
	case HEADER_HZ_PING: //!!???
		return true;
	break;
	case HEADER_ZH_ZSVR_INFO:
		return this->CZoneSvrProcess::ProcessPacket_ZH_ZSVR_INFO(dwSessionID, pPacket);
	break;
	case HEADER_SERVER_ENTRY:
		return this->CZoneSvrProcess::ProcessPacket_ServerEntry(dwSessionID, pPacket);
	break;
	case HEADER_ZH_LOGON:
		return this->CZoneSvrProcess::ProcessPacket_Logon(dwSessionID, pPacket);
	break;
	case HEADER_ZH_CHAR_EXIT:
		return this->CZoneSvrProcess::ProcessPacket_CharExit(dwSessionID, pPacket);
	break;
	case HEADER_ZH_CHAR_EXIT2:
		return this->CZoneSvrProcess::ProcessPacket_ZH_CHAR_EXIT2(dwSessionID, *reinterpret_cast<const PACKET_ZH_CHAR_EXIT2*>(pPacket));
	break;
	case HEADER_ZH_PLAYER_ALIVE:
		return this->CZoneSvrProcess::ProcessPacket_PLAYER_ALIVE(dwSessionID, pPacket);
	break;
	case HEADER_ZH_SAVECHARINFO:
		return this->CZoneSvrProcess::ProcessPacket_SaveCharInfo(dwSessionID, pPacket);
	break;
	case HEADER_ZH_MAPMOVE:
		return this->CZoneSvrProcess::ProcessPacket_MapMove(dwSessionID, pPacket);
	break;
	case HEADER_ZH_CASTLE_MAP_MOVE:
		return this->CZoneSvrProcess::ProcessPacket_CASTLE_MAP_MOVE(dwSessionID, pPacket);
	break;
	case HEADER_SAVE_USING_TIME:
		return this->CZoneSvrProcess::ProcessPacket_SaveUsingTime(dwSessionID, pPacket);
	break;
	case HEADER_ZH_RESTART:
		return this->CZoneSvrProcess::ProcessPacket_Restart(dwSessionID, pPacket);
	break;
	case HEADER_ZH_RESTART2:
		return this->CZoneSvrProcess::ProcessPacket_ZH_RESTART2(dwSessionID, *reinterpret_cast<const PACKET_ZH_RESTART2*>(pPacket));
	break;
	case HEADER_ZH_REQ_REMAINTIME:
		return this->CZoneSvrProcess::ProcessPacket_ReqRemainTime(dwSessionID, pPacket);
	break;
	case HEADER_ZH_MOVE_PVPWORLD:
		return this->CZoneSvrProcess::ProcessPacket_MoveToPVPWorld(dwSessionID, pPacket);
	break;
	case HEADER_ZH_USER_COUNT_ACK:
		return this->CZoneSvrProcess::ProcessPacket_ZONE_USER_COUNT_ACK(dwSessionID, pPacket);
	break;
	case HEADER_ZH_AUTH_REQ:
		return this->CZoneSvrProcess::ProcessPacket_ZH_CONNECTED_AUTH(dwSessionID, *reinterpret_cast<const PACKET_ZH_AUTH_REQ*>(pPacket));
	break;
	default:
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Header not found, sent from Zone Server %d\n", wPacketType);
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
	static CPremiumServiceDB* pPremiumServiceDB = CSingleton<CPremiumServiceDB>::getSingletonPtr();

	int nSID = pZoneServerInfoList->CZoneServerInfoList::GetSID(m_dwIP, m_nZoneListenPort); //FIXME: mixing private ip and public port
	pZoneServerInfoList->CZoneServerInfoList::SetUserCount(nSID, Packet.curUser);

	__SUSER__ user = {};
	if( g_UserList.CUserList::Get(Packet.AID, &user) != TRUE
	||  Packet.AuthCode != user.m_dwSecurityCode
	||  Packet.GID != user.m_nSelectedGID
	||  nSID != user.m_nSID )
	{
		PACKET_HZ_LOGON_ACK hz_logon_ack = {};
		hz_logon_ack.PacketType = HEADER_HZ_LOGON_NOTEXIST;
		hz_logon_ack.AID = Packet.AID;
		this->Send((char*)&hz_logon_ack, sizeof(hz_logon_ack), dwSessionID, false);
		return true;
	}

	PACKET_HZ_LOGON_ACK hz_logon_ack = {};
	hz_logon_ack.PacketType = HEADER_HZ_LOGON_EXIST;
	hz_logon_ack.AID = Packet.AID;
	hz_logon_ack.GID = Packet.GID;
	memcpy_s(hz_logon_ack.ID, 24, user.m_szID, 24-1);
	hz_logon_ack.TotalUsingTime = 0;
	hz_logon_ack.selectedCharNum = user.m_nSelectedSlotIndex;
	this->Send((char*)&hz_logon_ack, sizeof(hz_logon_ack), dwSessionID, false);

	std::vector<char> personal_packet = MakeHZ_PERSONAL_INFORMATION_THAI(user, !user.m_bMoveServerMap, pPremiumServiceDB);
	this->Send(&personal_packet.front(), personal_packet.size(), dwSessionID, false);

	user.m_bMoveServerMap = false;

	return true;
}


bool CZoneSvrProcess::ProcessPacket_CharExit(DWORD dwSessionID, char* pPacket)
{
	PACKET_ZH_CHAR_EXIT& in_pPacket = *reinterpret_cast<PACKET_ZH_CHAR_EXIT*>(pPacket);

	this->CZoneSvrProcess::OnZH_CHAR_EXIT(in_pPacket.AID, in_pPacket.disconnetedType, -1);
	return true;
}


bool CZoneSvrProcess::ProcessPacket_ZH_CHAR_EXIT2(const DWORD in_dwSessionID, const PACKET_ZH_CHAR_EXIT2& in_pPacket)
{
	this->CZoneSvrProcess::OnZH_CHAR_EXIT(in_pPacket.AID, in_pPacket.disconnetedType, in_pPacket.curUser);
	return true;
}


void CZoneSvrProcess::OnZH_CHAR_EXIT(const DWORD in_AID, const BYTE in_disconnetedType, const int in_TotalCnt)
{
	if( in_TotalCnt >= 0 )
	{
		int nZSID = CSingleton<CZoneServerInfoList>::getSingletonPtr()->CZoneServerInfoList::GetSID(m_dwIP, m_nZoneListenPort); //FIXME: mixing private ip and public port
		CSingleton<CZoneServerInfoList>::getSingletonPtr()->CZoneServerInfoList::SetUserCount(nZSID, in_TotalCnt);
	}

	if( in_disconnetedType != 1 )
	{
		g_UserList.CUserList::Delete(in_AID);
		CSingleton<CUserVerify>::getSingletonPtr()->CUserVerify::DeleteUserVerify(in_AID);
		DeleteConnectCharacter(in_AID);
	}

	if( in_disconnetedType == 0 )
	{
		PACKET_HA_CHAR_EXIT ha_char_exit;
		ha_char_exit.PacketType = HEADER_HA_CHAR_EXIT;
//		ha_char_exit.TotalUsingTime = 0; // FIXME
		ha_char_exit.AID = in_AID;
		ha_char_exit.disconnectedType = NORMAL_DISCONNECT;
		g_AccountStreamMgr.CStreamManager::Broadcast((char*)&ha_char_exit, sizeof(ha_char_exit));
	}

	static CPremiumServiceDB* pPremiumServiceDB = CSingleton<CPremiumServiceDB>::getSingletonPtr();
	pPremiumServiceDB->CPremiumServiceDB::DeletePCBonusLog(in_AID);

	__SUSER__ user = {};
	g_UserList.CUserList::Get(in_AID, &user);

	std::tr1::tuple<bool,int,int> ret = pPremiumServiceDB->CPremiumServiceDB::DeleteUserPcbonusEFSTList(in_AID, user.m_dwIP);
	if( std::tr1::get<0>(ret) == true && std::tr1::get<2>(ret) - std::tr1::get<1>(ret) >= 1 )
	{
		PACKET_HA_IPBONUS_LIMIT packet;
		packet.PacketType = HEADER_HA_IPBONUS_LIMIT;
		packet.reason = PACKET_HA_IPBONUS_LIMIT::enum_IPBONUS_NOT_LIMIT;
		packet.limitIP = user.m_dwIP;
		g_AccountStreamMgr.CStreamManager::Broadcast((char*)&packet, sizeof(packet));
	}
}


bool CZoneSvrProcess::ProcessPacket_SaveCharInfo(DWORD dwSessionID, char* pPacket)
{
	PACKET_ZH_SAVECHARINFO& Packet = *reinterpret_cast<PACKET_ZH_SAVECHARINFO*>(pPacket);

	static CUserVerify* pUserVerify = CSingleton<CUserVerify>::getSingletonPtr();
	pUserVerify->CUserVerify::UpdateUserVerify(Packet.AID, 1500000);

	PACKET_HA_PCINFOUPDATE ha_pcinfoupdate;
	ha_pcinfoupdate.PacketType = HEADER_HA_PCINFOUPDATE;
	ha_pcinfoupdate.AID = Packet.AID;
	g_AccountStreamMgr.CStreamManager::Broadcast((char*)&ha_pcinfoupdate, sizeof(ha_pcinfoupdate));

	return true;
}


bool CZoneSvrProcess::ProcessPacket_PLAYER_ALIVE(DWORD dwSessionID, char* pPacket)
{
	PACKET_ZH_PLAYER_ALIVE& Packet = *reinterpret_cast<PACKET_ZH_PLAYER_ALIVE*>(pPacket);

	static CUserVerify* pUserVerify = CSingleton<CUserVerify>::getSingletonPtr();
	pUserVerify->CUserVerify::UpdateUserVerify(Packet.AID, 1500000);

	PACKET_HA_PCINFOUPDATE ha_pcinfoupdate;
	ha_pcinfoupdate.PacketType = HEADER_HA_PCINFOUPDATE;
	ha_pcinfoupdate.AID = Packet.AID;
	g_AccountStreamMgr.CStreamManager::Broadcast((char*)&ha_pcinfoupdate, sizeof(ha_pcinfoupdate));

	return true;
}


bool CZoneSvrProcess::ProcessPacket_MapMove(DWORD dwSessionID, char* pPacket)
{
	PACKET_ZH_MAPMOVE& Packet = *reinterpret_cast<PACKET_ZH_MAPMOVE*>(pPacket);

	__SUSER__ user = {};
	if( g_UserList.CUserList::Get(Packet.AID, &user) == TRUE )
	{
		user.m_nSID = Packet.ServerID;
		g_UserList.CUserList::Insert(Packet.AID, user);
	}

	PACKET_HZ_ACK_MAPMOVE hz_ack_mapmove;
	hz_ack_mapmove.PacketType = HEADER_HZ_ACK_MAPMOVE;
	hz_ack_mapmove.AID = Packet.AID;
	hz_ack_mapmove.NID = Packet.NID;
	this->Send((char*)&hz_ack_mapmove, sizeof(hz_ack_mapmove), dwSessionID, false);

	return true;
}


bool CZoneSvrProcess::ProcessPacket_CASTLE_MAP_MOVE(DWORD dwSessionID, char* pPacket)
{
	PACKET_SAVE_USING_TIME& Packet = *reinterpret_cast<PACKET_SAVE_USING_TIME*>(pPacket);

	return true;
}


bool CZoneSvrProcess::ProcessPacket_Restart(DWORD dwSessionID, char* pPacket)
{
	PACKET_ZH_RESTART& Packet = *reinterpret_cast<PACKET_ZH_RESTART*>(pPacket);

	this->CZoneSvrProcess::OnZH_RESTART(dwSessionID, Packet.AID, -1);
	return true;
}


bool CZoneSvrProcess::ProcessPacket_ZH_RESTART2(const DWORD in_dwSessionID, const PACKET_ZH_RESTART2& in_pPacket) /// @custom
{
	this->CZoneSvrProcess::OnZH_RESTART(in_dwSessionID, in_pPacket.AID, in_pPacket.curUser);
	return true;
}


void CZoneSvrProcess::OnZH_RESTART(const DWORD in_dwSessionID, const DWORD in_AID, const int in_TotalCnt)
{
	if( in_TotalCnt >= 0 )
	{
		int nZSID = CSingleton<CZoneServerInfoList>::getSingletonPtr()->CZoneServerInfoList::GetSID(m_dwIP, m_nZoneListenPort); //FIXME: mixing private ip and public port
		CSingleton<CZoneServerInfoList>::getSingletonPtr()->CZoneServerInfoList::SetUserCount(nZSID, in_TotalCnt);
	}

	g_UserList.CUserList::Delete(in_AID);
	CSingleton<CUserVerify>::getSingletonPtr()->CUserVerify::DeleteUserVerify(in_AID);

	PACKET_HZ_ACK_RESTART hz_ack_restart;
	hz_ack_restart.PacketType = HEADER_HZ_ACK_RESTART;
	hz_ack_restart.AID = in_AID;
	this->Send((char*)&hz_ack_restart, sizeof(hz_ack_restart), in_dwSessionID, false);

	__SUSER__ user = {};
	g_UserList.CUserList::Get(in_AID, &user);

	static CPremiumServiceDB* pPremiumServiceDB = CSingleton<CPremiumServiceDB>::getSingletonPtr();
	std::tr1::tuple<bool,int,int> ret = pPremiumServiceDB->CPremiumServiceDB::DeleteUserPcbonusEFSTList(in_AID, user.m_dwIP);
	if( std::tr1::get<0>(ret) == true && std::tr1::get<2>(ret) - std::tr1::get<1>(ret) >= 1 )
	{
		PACKET_HA_IPBONUS_LIMIT packet;
		packet.PacketType = HEADER_HA_IPBONUS_LIMIT;
		packet.reason = PACKET_HA_IPBONUS_LIMIT::enum_IPBONUS_NOT_LIMIT;
		packet.limitIP = user.m_dwIP;
		g_AccountStreamMgr.CStreamManager::Broadcast((char*)&packet, sizeof(packet));
	}
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
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Error(MoveToPVPWord): Can't read CHARINFO from GID(%d)", nGID);
		return true;
	}

	SCHARINFO pvpCharInfo[MAX_CHARINFO_SLOT_COUNT];
	int nCharInfo = pvpDB->CCharacterDBBase::GetCharInfo(charinfo.m_nAID, pvpCharInfo, true, countof(pvpCharInfo));
	for( int i = 0; i < nCharInfo; ++i )
		pvpDB->CCharacterDBBase::DeleteCharInfo(pvpCharInfo[i].m_nGID);

	size_t len1 = strlen(gLocalServerInfo.m_szName);
	size_t len2 = strlen(charinfo.m_szName);

	if( len1 > 16 )
	{
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Error(MoveToPVPWord): Too long ServerName(%s)", gLocalServerInfo.m_szName);
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
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Error(MoveToPVPWord): Can't Copy CharInfo To PVPWorld(%s)/User that have same name exist", charinfo.m_szName);
		return true;
	}

	pvpDB->CCharacterDBBase::GetCharInfo(charinfo.m_nAID, pvpCharInfo, true, countof(pvpCharInfo));
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
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Error(MoveToPVPWord): Can't Initialize Point Table(%s)", charinfo.m_szName);
		return true;
	}

	return true;
}


bool CZoneSvrProcess::ProcessPacket_ZH_CONNECTED_AUTH(const DWORD in_dwSessionID, const PACKET_ZH_AUTH_REQ& in_pPacket)
{
	CZoneServerInfoList* pZoneServerInfoList = CSingleton<CZoneServerInfoList>::getSingletonPtr();
	int nZSID = CSingleton<CZoneServerInfoList>::getSingletonPtr()->CZoneServerInfoList::GetSID(in_pPacket.dwIP, in_pPacket.sPort); //FIXME: actual IP not validated

	if( nZSID != in_pPacket.ZSID )
	{
		NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("Zone Auth Failed. (ZSID:%d, ZoneListenPort:%d)", nZSID, in_pPacket.sPort);
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Zone Auth Failed. (ZSID:%d, ZoneListenPort:%d)", nZSID, in_pPacket.sPort);
		return false;
	}

	m_nZoneListenPort = in_pPacket.sPort; //FIXME: should just remember the SID instead

	if( !DBProxy<CGlobalInfoDB,4>::instance(0)->CGlobalInfoDB::IsColumnPrivateAdded() && !pZoneServerInfoList->CZoneServerInfoList::IsZoneServer(m_dwIP, m_nZoneListenPort) )
	{
		char szIP[100] = {};
		CNetwork::GetObj()->CNetwork::GetTextIP(m_dwIP, szIP);
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "not zone server connected %s\n", szIP);
		NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("not zone server connected %s\n", szIP);
		return false;
	}

	PACKET_HZ_AUTH_ACK hz_auth_ack;
	hz_auth_ack.PacketType = HEADER_HZ_AUTH_ACK;
	this->Send((char*)&hz_auth_ack, sizeof(hz_auth_ack), in_dwSessionID, false);

	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Zone Auth Completed. (ZSID:%d, Port:%d)", nZSID, in_pPacket.sPort);
	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("Zone Auth Completed. (ZSID:%d, Port:%d)", nZSID, in_pPacket.sPort);

	return true;
}


bool CZoneSvrProcess::ProcessPacket_ZH_PING(const DWORD dwSessionID, const char* pPacket)
{
	const PACKET_ZH_PING& Packet = *reinterpret_cast<const PACKET_ZH_PING*>(pPacket);

	return true;
}


void CZoneSvrProcess::OnZI_PING_LIVE(const DWORD in_dwSessionID, const PACKET_ZH_PING_LIVE& in_pPacket)
{
	PACKET_HZ_PING_LIVE hz_ping_live;
	hz_ping_live.PacketType = HEADER_HZ_PING_LIVE;
	this->Send((char*)&hz_ping_live, sizeof(hz_ping_live), in_dwSessionID, false);
}


bool CZoneSvrProcess::ProcessPacket_SaveUsingTime(DWORD dwSessionID, char* pPacket)
{
	PACKET_SAVE_USING_TIME& Packet = *reinterpret_cast<PACKET_SAVE_USING_TIME*>(pPacket);

	return true;
}


bool CZoneSvrProcess::ProcessPacket_ZONE_USER_COUNT_ACK(DWORD dwSessionID, char* pPacket)
{
	PACKET_ZH_USER_COUNT_ACK& Packet = *reinterpret_cast<PACKET_ZH_USER_COUNT_ACK*>(pPacket);

	int nZSID = CSingleton<CZoneServerInfoList>::getSingletonPtr()->CZoneServerInfoList::GetSID(m_dwIP, m_nZoneListenPort); //FIXME: mixing private ip and public port
	CSingleton<CZoneServerInfoList>::getSingletonPtr()->CZoneServerInfoList::SetUserCount(nZSID, Packet.UserCount);

	return true;
}


bool CZoneSvrProcess::ProcessPacket_ZH_ZSVR_INFO(const DWORD dwSessionID, const char* pPacket)
{
	const PACKET_ZH_USER_COUNT_ACK& Packet = *reinterpret_cast<const PACKET_ZH_USER_COUNT_ACK*>(pPacket);

	return true;
}
