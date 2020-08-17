#include "Character.h"
#include "CharacterDB.h"
#include "CharacterLogDB.h"
#include "CharCipher.h"
#include "ForbiddenName.h"
#include "PreventNameList.h"
#include "StartMap.h"
#include "UserAuthenticate.h"
#include "UserList.h"
#include "UserProcess.h"
#include "UserVerify.h"
#include "ZoneServerInfoList.h"
#include "Common/MapInfoList.h"
#include "Common/Network.h"
#include "Common/Packet.h"
#include "Common/Reporter.h"
#include "Common/ServerInfoList.h"
#include "Network3/AsyncProcessMgr.h"
#include "Network3/Stream.h"
#include "Network3/StreamManager.h"
#include "enum.hpp"


static void DecryptTaiwanPassword(BYTE code[], int& password)
{
	unsigned long keybase[8] = {
		0x050B6F79,
		0x0202C179,
		0x00E20120,
		0x04FA43E3,
		0x0179B6C8,
		0x05973DF2,
		0x007D8D6B,
		0x08CB9ED9,
	};

	static BOOL initKey;
	if( !initKey )
	{
		crypton_set_key(keybase, sizeof(keybase));
		initKey = TRUE;
	}

	unsigned long decCode[4];
	crypton_decrypt((unsigned long*)code, decCode);
	password = decCode[0];
}


CUserProcess::CUserProcess()
{
	m_bAuthenticated = false;
}


CUserProcess::~CUserProcess()
{
}


bool CUserProcess::OnConnect()
{
	m_cs.Enter();
	m_bCharSelected = false;
	m_bAuthenticated = false;
	m_bAuthPending = false;
	m_dwAID = 0;
	memset(m_charInfo, 0, sizeof(m_charInfo));
//	m_iSelectedSlot = 0;
//	m_bytePanaltyCount = 0;
//	m_dwCharacterPassSeedValue = 0;
	m_cs.Leave();

	return g_bAccountConnected;
}


void CUserProcess::OnClose()
{
	static CUserVerify* pUserVerify = CSingleton<CUserVerify>::getSingletonPtr();

	if( !m_bCharSelected && m_dwAID != 0 && m_bAuthenticated )
	{
		g_UserList.CUserList::Delete(m_dwAID);
		pUserVerify->CUserVerify::DeleteUserVerify(m_dwAID);

		if( g_bUsingCharacterPassword )
			DeleteConnectCharacter(m_dwAID);

		PACKET_HA_CHAR_EXIT ha_char_exit;
		ha_char_exit.PacketType = HEADER_HA_CHAR_EXIT;
//		ha_char_exit.TotalUsingTime = 0;
		ha_char_exit.AID = m_dwAID;
		ha_char_exit.disconnectedType = HAMOVE;
		g_AccountStreamMgr.CStreamManager::Broadcast((char*)&ha_char_exit, sizeof(ha_char_exit));
	}

	__SUSER__ user;
	if( g_UserList.CUserList::Bring(m_dwAID, &user) )
	{
		user.m_pUserProcess = NULL;
		user.m_dwSessionID = 0;
		g_UserList.CUserList::Insert(m_dwAID, user);
	}

	m_cs.Enter();
	m_bAuthenticated = false;
	m_bCharSelected = false;
	m_dwAID = 0;
	memset(m_charInfo, 0, sizeof(m_charInfo));
	m_cs.Leave();
}


void CUserProcess::CloseForce(DWORD dwSessionID, DWORD dwTime)
{
	m_pStream->CStream::CloseOuter(dwSessionID, dwTime);
}


bool CUserProcess::OnRecv(char* buffer, int* len)
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
		int nPacketSize = this->CUserProcess::GetPacketSize(wPacketType);

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

		if( wPacketType == HEADER_CH_MAKE_CHAR
		||  wPacketType == HEADER_CH_DELETE_CHAR
		||  wPacketType == HEADER_CH_DELETE_CHAR2
		)
		{// complex work, defer to worker thread
			unsigned int pkt_index = dwSessionID;

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
		{// handle immediately
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
	if( wPacketType == HEADER_CH_ENTER )
		return this->CUserProcess::ProcessPacket_Enter(dwSessionID, pPacket);

	if( !m_bAuthenticated ) 
		return false;

	switch( wPacketType )
	{
	case HEADER_CZ_ACK_STORE_PASSWORD:
		return this->CUserProcess::ProcessPacket_Ack_Character_Password(dwSessionID, pPacket);
	break;
	case HEADER_CH_SELECT_CHAR:
		return this->CUserProcess::ProcessPacket_SelectCharacter(dwSessionID, pPacket);
	break;
	case HEADER_CH_MAKE_CHAR:
		return this->CUserProcess::ProcessPacket_MakeCharacter(dwSessionID, pPacket);
	break;
	case HEADER_CH_DELETE_CHAR:
		return this->CUserProcess::ProcessPacket_DeleteCharacter(dwSessionID, pPacket);
	break;
	case HEADER_CH_DELETE_CHAR2:
		return this->CUserProcess::ProcessPacket_DeleteCharacter2(dwSessionID, pPacket);
	break;
	case HEADER_PING:
		return this->CUserProcess::ProcessPacket_Ping(dwSessionID, pPacket);
	break;
	default:
		return false;
	break;
	};
}


bool CUserProcess::ProcessPacket_Enter(DWORD dwSessionID, char* pPacket)
{
	PACKET_CH_ENTER& Packet = *reinterpret_cast<PACKET_CH_ENTER*>(pPacket);

	static CServerInfoList* pServerInfoList = CSingleton<CServerInfoList>::getSingletonPtr();
	static CZoneServerInfoList* pZoneServerInfoList = CSingleton<CZoneServerInfoList>::getSingletonPtr();
	static int nSID = pServerInfoList->CServerInfoList::GetSID(g_dwLocalIP, SERVERTYPE_CHARACTER);

	if( m_bAuthPending )
		return false;

	m_cs.Enter();
	m_bAuthPending = true;
	m_cs.Leave();

	int nUserCount = pZoneServerInfoList->CZoneServerInfoList::GetTotalUserCount();

	__SUSERAUTHENTICATE__ UserAuthenticate;
	UserAuthenticate.m_dwSecurityCode = Packet.AuthCode;
	UserAuthenticate.m_dwSessionID = dwSessionID;
	UserAuthenticate.m_pUserProcess = this;
	UserAuthenticate.m_dwIP = m_dwIP;
	g_UserAuthenticate.CUserAuthenticate::Insert(Packet.AID, UserAuthenticate);

	PACKET_HA_LOGON ha_logon;
	memset(&ha_logon, 0, sizeof(ha_logon));
	ha_logon.PacketType = HEADER_HA_LOGON;
	ha_logon.AID = Packet.AID;
	ha_logon.AuthCode = Packet.AuthCode;
	ha_logon.IP = m_dwIP;
	ha_logon.Sex = ( Packet.Sex != SEX_FEMALE ) ? SEX_MALE : SEX_FEMALE;
	ha_logon.SID = nSID;
	ha_logon.userCount = nUserCount;
	g_AccountStreamMgr.CStreamManager::Broadcast((char*)&ha_logon, sizeof(ha_logon));

	return true;
}


bool CUserProcess::ProcessPacket_SelectCharacter(DWORD dwSessionID, char* pPacket)
{
	PACKET_CH_SELECT_CHAR& Packet = *reinterpret_cast<PACKET_CH_SELECT_CHAR*>(pPacket);

	static CMapInfoList* pMapInfoList = CSingleton<CMapInfoList>::getSingletonPtr();
	static CServerInfoList* pServerInfoList = CSingleton<CServerInfoList>::getSingletonPtr();
	static CZoneServerInfoList* pZoneServerInfoList = CSingleton<CZoneServerInfoList>::getSingletonPtr();
	static CCharacterDB* pCharacterDB = CSingleton<CCharacterDB>::getSingletonPtr();

	m_bCharSelected = true;

	int i;
	for( i = 0; i < MAX_CHARINFO_SLOT_COUNT; ++i )
		if( m_charInfo[i].m_nGID != 0 && m_charInfo[i].m_nSlotIndex == Packet.CharNum )
			break;

	if( i >= MAX_CHARINFO_SLOT_COUNT )
		return false;

	SCHARINFO charInfo;
	memcpy(&charInfo, &m_charInfo[i], sizeof(charInfo));

	if( g_bUsingCharacterPassword && IsConnectCharacter(charInfo.m_nAID, charInfo.m_nSlotIndex) != CONNECT_CHARACTER )
	{
		m_iSelectedSlot = i;
		m_bytePanaltyCount = 0;
		m_dwCharacterPassSeedValue = rand() % 100000000;

		PACKET_HC_REQUEST_CHARACTER_PASSWORD packetRequestCharacterPassword;
		packetRequestCharacterPassword.PacketType = HEADER_HC_REQUEST_CHARACTER_PASSWORD;
		packetRequestCharacterPassword.Result = ( pCharacterDB->CCharacterDB::CheckCharacterPassword(charInfo.m_nGID, -1) ) ? 0 : 1;
		packetRequestCharacterPassword.dwSeed = m_dwCharacterPassSeedValue;
		this->Send((char*)&packetRequestCharacterPassword, sizeof(packetRequestCharacterPassword), dwSessionID, false);

		return true;
	}

	int nSID = pMapInfoList->CMapInfoList::GetSID(charInfo.m_szMapName);
	if( nSID == -1 )
		return false;

	SZONESERVERINFO zoneserverInfo;
	if( !pZoneServerInfoList->CZoneServerInfoList::GetZoneServerInfo(nSID, &zoneserverInfo) )
		return false;

	__SUSER__ user;
	if( !g_UserList.CUserList::Get(m_dwAID, &user) )
		return false;

	user.m_nSelectedGID = charInfo.m_nGID;
	user.m_nSelectedSlotIndex = charInfo.m_nSlotIndex;
	user.m_nSID = nSID;
	user.m_dwIP = m_dwIP;
	g_UserList.CUserList::Insert(m_dwAID, user);

	PACKET_HC_NOTIFY_ZONESVR hc_notify_zone;
	hc_notify_zone.PacketType = HEADER_HC_NOTIFY_ZONESVR;
	hc_notify_zone.GID = charInfo.m_nGID;
	hc_notify_zone.addr.ip = zoneserverInfo.m_dwIP;
	hc_notify_zone.addr.port = (short)zoneserverInfo.m_nPort;
	memcpy(hc_notify_zone.mapName, charInfo.m_szMapName, sizeof(hc_notify_zone.mapName));
	this->Send((char*)&hc_notify_zone, sizeof(hc_notify_zone), dwSessionID, false);

	this->CProcess::CloseOuter(dwSessionID, 5000);
	return true;
}


bool CUserProcess::ProcessPacket_Ack_Character_Password(DWORD dwSessionID, char* pPacket)
{
	PACKET_CZ_ACK_STORE_PASSWORD& Packet = *reinterpret_cast<PACKET_CZ_ACK_STORE_PASSWORD*>(pPacket);

	static CCharacterDB* pCharacterDB = CSingleton<CCharacterDB>::getSingletonPtr();
	static CZoneServerInfoList* pZoneServerInfoList = CSingleton<CZoneServerInfoList>::getSingletonPtr();
	static CMapInfoList* pMapInfoList = CSingleton<CMapInfoList>::getSingletonPtr();

	int iPassword = 0;
	int iNewPassword = 0;
	DecryptTaiwanPassword(Packet.Password, iPassword);
	DecryptTaiwanPassword(Packet.NewPassword, iNewPassword);
	if( iPassword > 1 )
		iPassword -= m_dwCharacterPassSeedValue;
	iNewPassword -= m_dwCharacterPassSeedValue;

	PACKET_HC_REQUEST_CHARACTER_PASSWORD packetRequestCharacterPassword;
	packetRequestCharacterPassword.PacketType = HEADER_HC_REQUEST_CHARACTER_PASSWORD;
	packetRequestCharacterPassword.dwSeed = m_dwCharacterPassSeedValue;

	if( Packet.Type == 2 )
	{
		if( iNewPassword > 399999999 && iNewPassword < 900000000 )
		{
			if( pCharacterDB->CCharacterDB::UpdateCharacterPassword(m_charInfo[m_iSelectedSlot].m_nGID, iPassword, iNewPassword) )
				packetRequestCharacterPassword.Result = 2;
			else
				packetRequestCharacterPassword.Result = 3;
		}

		this->Send((char*)&packetRequestCharacterPassword, sizeof(packetRequestCharacterPassword), dwSessionID, false);

		return true;
	}

	if( Packet.Type != 3 )
		return true;

	if( !pCharacterDB->CCharacterDB::CheckCharacterPassword(m_charInfo[m_iSelectedSlot].m_nGID, iPassword) || iPassword <= 399999999 || iPassword >= 900000000 )
	{
		++m_bytePanaltyCount;

		if( m_bytePanaltyCount >= 3 )
		{
			packetRequestCharacterPassword.Result = 5;
			this->Send((char*)&packetRequestCharacterPassword, sizeof(packetRequestCharacterPassword), dwSessionID, false);

			this->CProcess::CloseOuter(dwSessionID, 2000);
		}
		else
		{
			packetRequestCharacterPassword.Result = 4;
			this->Send((char*)&packetRequestCharacterPassword, sizeof(packetRequestCharacterPassword), dwSessionID, false);
		}

		return true;
	}

	SCHARINFO charInfo;
	memcpy(&charInfo, &m_charInfo[m_iSelectedSlot], sizeof(charInfo));

	int nSID = pMapInfoList->CMapInfoList::GetSID(charInfo.m_szMapName);
	if( nSID == -1 )
		return false;

	SZONESERVERINFO zoneserverInfo;
	if( !pZoneServerInfoList->CZoneServerInfoList::GetZoneServerInfo(nSID, &zoneserverInfo) )
		return false;

	__SUSER__ user;
	if( !g_UserList.CUserList::Get(m_dwAID, &user) )
		return false;

	user.m_nSelectedGID = charInfo.m_nGID;
	user.m_nSelectedSlotIndex = charInfo.m_nSlotIndex;
	user.m_nSID = nSID;
	user.m_dwIP = m_dwIP;
	g_UserList.CUserList::Insert(m_dwAID, user);

	PACKET_HC_NOTIFY_ZONESVR hc_notify_zone;
	hc_notify_zone.PacketType = HEADER_HC_NOTIFY_ZONESVR;
	hc_notify_zone.GID = charInfo.m_nGID;
	hc_notify_zone.addr.ip = zoneserverInfo.m_dwIP;
	hc_notify_zone.addr.port = (short)zoneserverInfo.m_nPort;
	memcpy(hc_notify_zone.mapName, charInfo.m_szMapName, sizeof(hc_notify_zone.mapName));
	this->Send((char*)&hc_notify_zone, sizeof(hc_notify_zone), dwSessionID, false);

	this->CProcess::CloseOuter(dwSessionID, 5000);
	PutConnectCharacter(charInfo.m_nAID, charInfo.m_nSlotIndex);

	return true;
}


bool CUserProcess::ProcessPacket_MakeCharacter(DWORD dwSessionID, char* pPacket)
{
	PACKET_CH_MAKE_CHAR& Packet = *reinterpret_cast<PACKET_CH_MAKE_CHAR*>(pPacket);

	static CCharacterDB* pCharacterDB = CSingleton<CCharacterDB>::getSingletonPtr();
	static CPreventNameList* pPreventNameList = CSingleton<CPreventNameList>::getSingletonPtr();
	static CForbiddenName* pForbiddenName = CSingleton<CForbiddenName>::getSingletonPtr();

	if( pPreventNameList->CPreventNameList::IsPreventName((char*)Packet.name) == TRUE )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("REFUSE_MAKECHAR:IsPreventName [%s]\n", Packet.name);

		PACKET_HC_REFUSE_MAKECHAR hc_refuse_makechar;
		hc_refuse_makechar.PacketType = HEADER_HC_REFUSE_MAKECHAR;
		hc_refuse_makechar.ErrorCode = 0;
		this->Send((char*)&hc_refuse_makechar, sizeof(hc_refuse_makechar), dwSessionID, false);

		return true;
	}

	if( pForbiddenName->CForbiddenName::isForbidden((char*)Packet.name) )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("REFUSE_MAKECHAR:IsForbidden [%s]\n", Packet.name);

		PACKET_HC_REFUSE_MAKECHAR hc_refuse_makechar;
		hc_refuse_makechar.PacketType = HEADER_HC_REFUSE_MAKECHAR;
		hc_refuse_makechar.ErrorCode = 0;
		this->Send((char*)&hc_refuse_makechar, sizeof(hc_refuse_makechar), dwSessionID, false);

		return true;
	}

	int char_cnt = 0;
	for( int i = 0; i < MAX_CHARINFO_SLOT_COUNT; ++i )
	{
		if( m_charInfo[i].m_nGID == 0 )
			continue;

		if( m_charInfo[i].m_nSlotIndex == Packet.CharNum )
		{
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("REFUSE_MAKECHAR:Slot_Count [%s] : %d\n", Packet.name, Packet.CharNum);

			PACKET_HC_REFUSE_MAKECHAR hc_refuse_makechar;
			hc_refuse_makechar.PacketType = HEADER_HC_REFUSE_MAKECHAR;
			hc_refuse_makechar.ErrorCode = 0;
			this->Send((char*)&hc_refuse_makechar, sizeof(hc_refuse_makechar), dwSessionID, false);

			return true;
		}

		++char_cnt;
	}

	if( char_cnt >= MAX_CHARINFO_SLOT_COUNT )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("REFUSE_MAKECHAR:Over Character Slot_Count [%s] : %d\n", Packet.name, Packet.CharNum);

		PACKET_HC_REFUSE_MAKECHAR hc_refuse_makechar;
		hc_refuse_makechar.PacketType = HEADER_HC_REFUSE_MAKECHAR;
		hc_refuse_makechar.ErrorCode = 0;
		this->Send((char*)&hc_refuse_makechar, sizeof(hc_refuse_makechar), dwSessionID, false);

		return true;
	}

	if( Packet.CharNum >= MAX_CHARINFO_SLOT_COUNT )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("REFUSE_MAKECHAR:Over Character Slot_Count_1 [%s] : %d\n", Packet.name, Packet.CharNum);

		PACKET_HC_REFUSE_MAKECHAR hc_refuse_makechar;
		hc_refuse_makechar.PacketType = HEADER_HC_REFUSE_MAKECHAR;
		hc_refuse_makechar.ErrorCode = 0;
		this->Send((char*)&hc_refuse_makechar, sizeof(hc_refuse_makechar), dwSessionID, false);

		return true;
	}

	SCHARINFO charInfo = {};

	charInfo.m_nStr = Packet.Str;
	charInfo.m_nAgi = Packet.Agi;
	charInfo.m_nVit = Packet.Vit;
	charInfo.m_nInt = Packet.Int;
	charInfo.m_nDex = Packet.Dex;
	charInfo.m_nLuk = Packet.Luk;

	if( charInfo.m_nStr < 1 || charInfo.m_nStr > 9 ) charInfo.m_nStr = 5;
	if( charInfo.m_nAgi < 1 || charInfo.m_nAgi > 9 ) charInfo.m_nAgi = 5;
	if( charInfo.m_nVit < 1 || charInfo.m_nVit > 9 ) charInfo.m_nVit = 5;
	if( charInfo.m_nInt < 1 || charInfo.m_nInt > 9 ) charInfo.m_nInt = 5;
	if( charInfo.m_nDex < 1 || charInfo.m_nDex > 9 ) charInfo.m_nDex = 5;
	if( charInfo.m_nLuk < 1 || charInfo.m_nLuk > 9 ) charInfo.m_nLuk = 5;

	if( charInfo.m_nStr + charInfo.m_nInt != 10 ) { charInfo.m_nInt = 5; charInfo.m_nStr = 5; }
	if( charInfo.m_nAgi + charInfo.m_nLuk != 10 ) { charInfo.m_nLuk = 5; charInfo.m_nAgi = 5; }
	if( charInfo.m_nVit + charInfo.m_nDex != 10 ) { charInfo.m_nVit = 5; charInfo.m_nDex = 5; }

	charInfo.m_nAID = m_dwAID;
	charInfo.m_nSlotIndex = Packet.CharNum;
	memcpy(charInfo.m_szName, Packet.name, 24);

	if( strlen(charInfo.m_szName) > 24 )
	{
		PACKET_HC_REFUSE_MAKECHAR hc_refuse_makechar;
		hc_refuse_makechar.PacketType = HEADER_HC_REFUSE_MAKECHAR;
		hc_refuse_makechar.ErrorCode = 0;
		this->Send((char*)&hc_refuse_makechar, sizeof(hc_refuse_makechar), dwSessionID, false);

		return true;
	}

	charInfo.m_nHead = Packet.head;
	if( charInfo.m_nHead < 0 || charInfo.m_nHead >= 100 )
		charInfo.m_nHead = 1;

	charInfo.m_nHeadPalette = (BYTE)Packet.headPal;
	if( charInfo.m_nHeadPalette < 0 || charInfo.m_nHeadPalette >= 9 )
		charInfo.m_nHeadPalette = 0;

	_SSTARTMAP_ mapData;
	CSingleton<CStartMap>::getSingletonPtr()->CStartMap::GetRandomOne(mapData);
	memcpy(charInfo.m_szMapName, mapData.m_szMapName, sizeof(charInfo.m_szMapName));
	memcpy(charInfo.m_szRestartMapName, mapData.m_szRestartMapName, sizeof(charInfo.m_szRestartMapName));
	charInfo.m_nXPos = mapData.m_nXPos;
	charInfo.m_nYPos = mapData.m_nYPos;
	charInfo.m_nSxPos = mapData.m_nSxPos;
	charInfo.m_nSyPos = mapData.m_nSyPos;

	if( !pCharacterDB->CCharacterDB::MakeCharInfo(&charInfo) )
	{
		PACKET_HC_REFUSE_MAKECHAR hc_refuse_makechar;
		hc_refuse_makechar.PacketType = HEADER_HC_REFUSE_MAKECHAR;
		hc_refuse_makechar.ErrorCode = 0;
		this->Send((char*)&hc_refuse_makechar, sizeof(hc_refuse_makechar), dwSessionID, false);

		return true;
	}

	m_cs.Enter();
	memset(m_charInfo, 0, sizeof(m_charInfo));
	pCharacterDB->CCharacterDBBase::GetCharInfo(charInfo.m_nAID, m_charInfo, true);
	m_cs.Leave();

	m_cs.Enter();
	memset(&charInfo, 0, sizeof(charInfo));
	int i;
	for( i = 0; i < MAX_CHARINFO_SLOT_COUNT; ++i )
	{
		if( m_charInfo[i].m_nGID != 0 && m_charInfo[i].m_nSlotIndex == Packet.CharNum )
		{
			memcpy(&charInfo, &m_charInfo[i], sizeof(charInfo));
			break;
		}
	}
	m_cs.Leave();

	if( i >= MAX_CHARINFO_SLOT_COUNT )
		return false;

	PACKET_HC_ACCEPT_MAKECHAR hc_accept_makechar;
	hc_accept_makechar.PacketType = HEADER_HC_ACCEPT_MAKECHAR;
	MakeCHARACTER_INFO(&charInfo, &hc_accept_makechar.charinfo);
	this->Send((char*)&hc_accept_makechar, sizeof(hc_accept_makechar), dwSessionID, false);

	return true;
}


bool CUserProcess::ProcessPacket_DeleteCharacter2(DWORD dwSessionID, char* pPacket)
{
	PACKET_CH_DELETE_CHAR2& Packet = *reinterpret_cast<PACKET_CH_DELETE_CHAR2*>(pPacket);

	static CCharacterDB* pCharacterDB = CSingleton<CCharacterDB>::getSingletonPtr();

	__SUSER__ user;
	if( !g_UserList.CUserList::Get(m_dwAID, &user) )
		return false;

	if( strncmp(user.m_szEMail, Packet.key, min(strlen(user.m_szEMail), 50)) != 0 )
	{
		PACKET_HC_REFUSE_DELETECHAR hc_refuse_deletechar;
		hc_refuse_deletechar.PacketType = HEADER_HC_REFUSE_DELETECHAR;
		hc_refuse_deletechar.ErrorCode = 0;
		this->Send((char*)&hc_refuse_deletechar, sizeof(hc_refuse_deletechar), dwSessionID, false);

		return true;
	}

	static CCharacterLogDB* pCharLogDB = CSingleton<CCharacterLogDB>::getSingletonPtr();

	SCHARINFO charInfo;
	int i;
	for( i = 0; i < MAX_CHARINFO_SLOT_COUNT; ++i )
	{
		if( m_charInfo[i].m_nGID == Packet.GID )
		{
			memcpy(&charInfo, &m_charInfo[i], sizeof(charInfo));
			break;
		}
	}

	if( !pCharacterDB->CCharacterDBBase::DeleteCharInfo(Packet.GID) )
	{
		PACKET_HC_REFUSE_DELETECHAR hc_refuse_deletechar;
		hc_refuse_deletechar.PacketType = HEADER_HC_REFUSE_DELETECHAR;
		hc_refuse_deletechar.ErrorCode = 0;
		this->Send((char*)&hc_refuse_deletechar, sizeof(hc_refuse_deletechar), dwSessionID, false);

		return true;
	}

	m_cs.Enter();
	memset(m_charInfo, 0, sizeof(m_charInfo));
	pCharacterDB->CCharacterDBBase::GetCharInfo(m_dwAID, m_charInfo, true);
	m_cs.Leave();

	int nGRID = pCharacterDB->CCharacterDB::GetGroupID(Packet.GID);
	pCharacterDB->CCharacterDB::DeleteGroupMember(Packet.GID);
	if( nGRID != 0 )
		if( pCharacterDB->CCharacterDB::GetGroupMemberCount(nGRID) <= 0 )
			pCharacterDB->CCharacterDB::DeleteGroup(nGRID);

	PACKET_HC_ACCEPT_DELETECHAR hc_accept_deletechar;
	hc_accept_deletechar.PacketType = HEADER_HC_ACCEPT_DELETECHAR;
	this->Send((char*)&hc_accept_deletechar, sizeof(hc_accept_deletechar), dwSessionID, false);

	char szIP[16] = {};
	CSingleton<CNetwork>::getSingletonPtr()->CNetwork::GetTextIP(m_dwIP, szIP);
	pCharLogDB->CCharacterLogDB::DeleteCharaterLog(Packet.GID, m_dwAID, charInfo.m_szName, szIP);

	return true;
}


static BOOL Delete_GuildInfo(unsigned long GID)
{
	int PositionID = -1;
	if( CSingleton<CCharacterDB>::getSingletonPtr()->CCharacterDB::GetGuildMemberPositionID(GID, &PositionID) == TRUE )
	{
		CSingleton<CCharacterDB>::getSingletonPtr()->CCharacterDB::DeleteGuildMInfo(GID);

		if( PositionID == 0 )
		{
			int nGDID;
			if( CSingleton<CCharacterDB>::getSingletonPtr()->CCharacterDB::GetGuildIDByGID(GID, &nGDID) == TRUE )
				CSingleton<CCharacterDB>::getSingletonPtr()->CCharacterDB::DelegateGuildMaster(nGDID);
		}
	}

	return TRUE;
}


static BOOL Delete_GroupInfo(unsigned long GID, unsigned long AID)
{
	if( !CSingleton<CCharacterDB>::getSingletonPtr()->CCharacterDBBase::DeleteCharInfo(GID) )
		return FALSE;

	int nGRID = CSingleton<CCharacterDB>::getSingletonPtr()->CCharacterDB::GetGroupID(GID);
	CSingleton<CCharacterDB>::getSingletonPtr()->CCharacterDB::DeleteGroupMember(GID);

	if( nGRID != 0 )
		if( CSingleton<CCharacterDB>::getSingletonPtr()->CCharacterDB::GetGroupMemberCount(nGRID) <= 0 )
			CSingleton<CCharacterDB>::getSingletonPtr()->CCharacterDB::DeleteGroup(nGRID);

	return TRUE;
}


bool CUserProcess::ProcessPacket_DeleteCharacter(DWORD dwSessionID, char* pPacket)
{
	PACKET_CH_DELETE_CHAR& Packet = *reinterpret_cast<PACKET_CH_DELETE_CHAR*>(pPacket);

	static CCharacterDB* pCharacterDB = CSingleton<CCharacterDB>::getSingletonPtr();

	__SUSER__ user;
	if( !g_UserList.CUserList::Get(m_dwAID, &user) )
		return false;

	static CCharacterLogDB* pCharLogDB = CSingleton<CCharacterLogDB>::getSingletonPtr();

	SCHARINFO charInfo;
	int i;
	for( i = 0; i < MAX_CHARINFO_SLOT_COUNT; ++i )
	{
		if( m_charInfo[i].m_nGID == Packet.GID )
		{
			memcpy(&charInfo, &m_charInfo[i], sizeof(charInfo));
			break;
		}
	}

	int isIncorrectKey;
	if( strlen(user.m_szEMail) == strlen(Packet.key) )
		isIncorrectKey = strncmp(user.m_szEMail, Packet.key, min(strlen(user.m_szEMail), 40));
	else
		isIncorrectKey = 1;

	if( isIncorrectKey )
	{
		PACKET_HC_REFUSE_DELETECHAR hc_refuse_deletechar;
		hc_refuse_deletechar.PacketType = HEADER_HC_REFUSE_DELETECHAR;
		hc_refuse_deletechar.ErrorCode = 0;
		this->Send((char*)&hc_refuse_deletechar, sizeof(hc_refuse_deletechar), dwSessionID, false);

		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("ID:%s CharDelete Error (%d)\n", user.m_szID, isIncorrectKey);
		return true;
	}

	if( !Delete_GroupInfo(Packet.GID, m_dwAID) || !Delete_GuildInfo(Packet.GID) )
	{
		PACKET_HC_REFUSE_DELETECHAR hc_refuse_deletechar;
		hc_refuse_deletechar.PacketType = HEADER_HC_REFUSE_DELETECHAR;
		hc_refuse_deletechar.ErrorCode = 0;
		this->Send((char*)&hc_refuse_deletechar, sizeof(hc_refuse_deletechar), dwSessionID, false);

		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("ID:%s CharInfo Delete Error : %s\n", user.m_szID, user.m_szEMail);
		return true;
	}

	m_cs.Enter();
	memset(m_charInfo, 0, sizeof(m_charInfo));
	pCharacterDB->CCharacterDBBase::GetCharInfo(m_dwAID, m_charInfo, true);
	m_cs.Leave();

	PACKET_HC_ACCEPT_DELETECHAR hc_accept_deletechar;
	hc_accept_deletechar.PacketType = HEADER_HC_ACCEPT_DELETECHAR;
	this->Send((char*)&hc_accept_deletechar, sizeof(hc_accept_deletechar), dwSessionID, false);

	char szIP[16] = {};
	CSingleton<CNetwork>::getSingletonPtr()->CNetwork::GetTextIP(m_dwIP, szIP);
	pCharLogDB->CCharacterLogDB::DeleteCharaterLog(Packet.GID, m_dwAID, charInfo.m_szName, szIP);

	return true;
}


bool CUserProcess::ProcessPacket_Ping(DWORD dwSessionID, char* pPacket)
{
	PACKET_PING& Packet = *reinterpret_cast<PACKET_PING*>(pPacket);

	this->Send((char*)&Packet, sizeof(Packet), dwSessionID, false);

	return true;
}


void CUserProcess::OnLogonAck(PACKET_AH_LOGON_ACK* pLogonAck, DWORD dwSessionID)
{
	static CCharacterDB* pCharacterDB = CSingleton<CCharacterDB>::getSingletonPtr();
	static CUserVerify* pUserVerify = CSingleton<CUserVerify>::getSingletonPtr();

	if( m_dwSessionID != dwSessionID )
		return;

	if( pLogonAck->PacketType != HEADER_AH_LOGON_EXIST && pLogonAck->PacketType != HEADER_AH_LOGON_EXIST_PCBANG )
	{
		PACKET_HC_AID_RAW hc_aid;
		hc_aid.AID = pLogonAck->AID;
		this->Send((char*)&hc_aid, sizeof(hc_aid), m_dwSessionID, false);

		PACKET_HC_REFUSE_ENTER hc_refuse_enter;
		hc_refuse_enter.PacketType = HEADER_HC_REFUSE_ENTER;
		hc_refuse_enter.ErrorCode = 0;
		this->Send((char*)&hc_refuse_enter, sizeof(hc_refuse_enter), dwSessionID, false);

		this->CProcess::CloseOuter(dwSessionID, 5000);
		return;
	}

	m_cs.Enter();
	int CharacterCount = pCharacterDB->CCharacterDBBase::GetCharInfo(pLogonAck->AID, m_charInfo, true);
	m_cs.Leave();

	this->CUserProcess::ChangeDoNotSaveMap(CharacterCount);

	PACKET_HC_AID_RAW hc_aid;
	hc_aid.AID = pLogonAck->AID;
	this->Send((char*)&hc_aid, sizeof(hc_aid), m_dwSessionID, false);

	PACKET_HC_ACCEPT_ENTER hc_accept_enter;
	hc_accept_enter.PacketType = HEADER_HC_ACCEPT_ENTER;
	hc_accept_enter.PacketLength = sizeof(PACKET_HC_ACCEPT_ENTER) + CharacterCount * sizeof(CHARACTER_INFO);
	this->Send((char*)&hc_accept_enter, sizeof(hc_accept_enter), dwSessionID, false);

	pUserVerify->CUserVerify::UpdateUserVerify(pLogonAck->AID, 1200000);

	CHARACTER_INFO character_info = {};
	for( int i = 0; i < CharacterCount; ++i )
	{
		MakeCHARACTER_INFO(&m_charInfo[i], &character_info);
		this->Send((char*)&character_info, sizeof(character_info), dwSessionID, false);
	}

	m_dwAID = pLogonAck->AID;
	m_bAuthenticated = true;
}


bool CUserProcess::ChangeDoNotSaveMap(int nCount)
{
	if( nCount < 1 || nCount > MAX_CHARINFO_SLOT_COUNT )
		return false;

	static CMapInfoList* pMapInfoList = CSingleton<CMapInfoList>::getSingletonPtr();
	static CCharacterDB* pCharacterDB = CSingleton<CCharacterDB>::getSingletonPtr();

	bool result = false;

	for( int i = 0; i < nCount; ++i )
	{
		SCHARINFO& info = m_charInfo[i];

		int iMapType = pMapInfoList->CMapInfoList::GetMapType(info.m_szMapName);
		if( iMapType != MAPTYPE_AGIT )
			continue;

		result = true;

		m_cs.Enter();
		memset(info.m_szMapName, '\0', sizeof(info.m_szMapName));
		strncpy(info.m_szMapName, info.m_szRestartMapName, strlen(info.m_szRestartMapName));
		info.m_nXPos = info.m_nSxPos;
		info.m_nYPos = info.m_nSyPos;
		m_cs.Leave();

		pCharacterDB->CCharacterDB::UpdateCharStartMap(info.m_nGID);
	}

	return result;
}
