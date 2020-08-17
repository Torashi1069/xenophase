#include "CharacterMgr.h"
#include "CCoupleInfoDB.hpp"
#include "CFamilyInfoDB.hpp"
#include "HSvrIO.h"
#include "HSvrIOPacketHandler.h"
#include "CMakerRankMgr.hpp"
#include "MapResMgr.h"
#include "CMerceDB.hpp"
#include "CStatusPlusInfoByJLV.hpp"
#include "ErrorLog.h"
#include "InstantMapLib.h"
#include "MapInfo.h"
#include "AsyncDBWork/LogonPermitADBWork.h"
#include "AsyncDBWork/NAsyncDBMgr.h"
#include "AsyncDBWork/NAsyncDBWork.h"
#include "Common/Packet.h"
#include "shared.h" // Trace


CHSvrIOPacketHandler::CHSvrIOPacketHandler(void) // line 61
{
}


CHSvrIOPacketHandler::~CHSvrIOPacketHandler(void) // line 65
{
}


hook_method<int (CHSvrIOPacketHandler::*)(void)> CHSvrIOPacketHandler::_OnProcess(SERVER, "CHSvrIOPacketHandler::OnProcess");
int CHSvrIOPacketHandler::OnProcess(void) // line 83
{
	return (this->*_OnProcess)();

	for( int i = 0; m_recvQueue->CPacketQueue::GetSize() >= 4 && i < 70; ++i )
	{
		int Header = 0;
		m_recvQueue->CPacketQueue::PeekData(2, (char*)&Header);

		int size;
		if( ::IsFixedPacket(Header) )
		{
			size = ::GetPacketSize(Header);
		}
		else
		{
			if( m_recvQueue->CPacketQueue::GetSize() < 4 )
				return -1;

			m_recvQueue->CPacketQueue::PeekData(4, (char*)&size);
			size = size >> 16;
		}

		if( size == 0 || size >= 2048 )
		{
			char buff[1024];
			sprintf(buff, "OnProcess PacketSize error %d\n", size);
			g_errorLogs->CErrorLog::CriticalErrorLog(buff, 110, ".\\HSvrIOPacketHandler.cpp");
			return 0;
		}

		if( m_recvQueue->CPacketQueue::GetSize() >= size )
		{
			int result = this->CHSvrIOPacketHandler::DispatchPacket(Header, size);
			if( result != -1 )
				return result;
		}
	}

	return -1;
}


hook_method<void (CHSvrIOPacketHandler::*)(void)> CHSvrIOPacketHandler::_OnClose(SERVER, "CHSvrIOPacketHandler::OnClose");
void CHSvrIOPacketHandler::OnClose(void) // line 75
{
	return (this->*_OnClose)();

	g_hSvrIO->CSvrIO::OnClose();
}


hook_method<void (CHSvrIOPacketHandler::*)(int len)> CHSvrIOPacketHandler::_OnLogonPermit(SERVER, "?OnLogonPermit@CHSvrIOPacketHandler@@AAEXH@Z");
void CHSvrIOPacketHandler::OnLogonPermit(int len) // line 496
{
	return (this->*_OnLogonPermit)(len);

	PACKET_HZ_LOGON_ACK packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char *)&packet);

	if( g_characterMgr->CCharacterMgr::FindCharacter(packet.AID, PC_TYPE) == NULL )
	{
		Trace("없는 아이디 인증 했음..%d\n", packet.AID);
		return;
	}

	NAsyncDBWork* work = new CLogonPermitADBWork(packet.AID, packet.GID, packet.selectedCharNum, packet.ID, packet.TotalUsingTime);
	if( work == NULL )
		return;

	if( !NAsyncDBMgr::GetObj()->NAsyncDBMgr::RequestWork(work) )
		delete work;

}


hook_func<void (__cdecl *)(CPC* const in_pToPlayer)> _SendPacket_ZC_ACCEPT_ENTER2(SERVER, "SendPacket_ZC_ACCEPT_ENTER2");
void __cdecl SendPacket_ZC_ACCEPT_ENTER2(CPC* const in_pToPlayer) // line 548
{
	return (_SendPacket_ZC_ACCEPT_ENTER2)(in_pToPlayer);

	PACKET_ZC_ACCEPT_ENTER2 packet;
	packet.PacketType = HEADER_ZC_ACCEPT_ENTER2;
	packet.startTime = in_pToPlayer->m_characterTimeInfo.connectedTime;
	packet.xSize = in_pToPlayer->m_characterInfo.xSize;
	packet.ySize = in_pToPlayer->m_characterInfo.ySize;
	EncodePosDir(in_pToPlayer->m_pathInfo.m_moveInfo.xPos, in_pToPlayer->m_pathInfo.m_moveInfo.xPos, in_pToPlayer->m_pathInfo.m_moveInfo.dir, packet.PosDir);
	packet.font = in_pToPlayer->m_characterInfo.font;

	in_pToPlayer->CPC::ForceSend(sizeof(packet), (char *)&packet);
}


hook_method<void (CHSvrIOPacketHandler::*)(CPC* const in_pPlayer, const unsigned long in_AID, const unsigned long in_GID, const char* in_IDstr, const unsigned long in_TotalUsingTime, const int in_selectedCharNum, CLogonPermitADBWork* const in_cpADBWork)> CHSvrIOPacketHandler::_OnLogonPermit2(SERVER, "?OnLogonPermit@CHSvrIOPacketHandler@@QAEXQAVCPC@@KKPBDKHQAVCLogonPermitADBWork@@@Z");
void CHSvrIOPacketHandler::OnLogonPermit(CPC* const in_pPlayer, const unsigned long in_AID, const unsigned long in_GID, const char* in_IDstr, const unsigned long in_TotalUsingTime, const int in_selectedCharNum, CLogonPermitADBWork* const in_cpADBWork) // line 575
{
	return (this->*_OnLogonPermit2)(in_pPlayer, in_AID, in_GID, in_IDstr, in_TotalUsingTime, in_selectedCharNum, in_cpADBWork);

	if( in_pPlayer == NULL )
	{
		char Buf[256];
		sprintf(Buf, "OnLogonPermit : in_pPlayer = NULL");
		g_errorLogs->CErrorLog::CriticalErrorLog(Buf, 581, ".\\HSvrIOPacketHandler.cpp");
		return;
	}

	in_pPlayer->m_pcBattle.m_Mercenary = in_cpADBWork->m_MercenaryData.m_Owner;
	if( in_pPlayer->m_pcBattle.m_Mercenary.CPCBattleMercenary::isCall() )
	{
		memcpy(&in_pPlayer->m_pcBattle.m_Mercenary.m_ProxyDB.m_Info, &in_cpADBWork->m_MercenaryData.m_Info, sizeof(in_pPlayer->m_pcBattle.m_Mercenary.m_ProxyDB.m_Info));

		in_pPlayer->m_pcBattle.m_Mercenary.m_ProxyDB.m_EffectLength = in_cpADBWork->m_MercenaryData.m_EffectLength;
		memcpy(in_pPlayer->m_pcBattle.m_Mercenary.m_ProxyDB.m_EffectData, in_cpADBWork->m_MercenaryData.m_EffectData, in_cpADBWork->m_MercenaryData.m_EffectLength);

		in_pPlayer->m_pcBattle.m_Mercenary.m_ProxyDB.m_StateLength = in_cpADBWork->m_MercenaryData.m_StateLength;
		memcpy(in_pPlayer->m_pcBattle.m_Mercenary.m_ProxyDB.m_StateData, in_cpADBWork->m_MercenaryData.m_StateData, in_cpADBWork->m_MercenaryData.m_StateLength);

		in_pPlayer->m_pcBattle.m_Mercenary.m_ProxyDB.m_bLoad = true;
	}

	CMapRes* map = g_mapResMgr->CMapResMgr::GetMapRes(in_cpADBWork->m_CharacterInfo.m_data.mapname);
	if( map == NULL || map->isInstantMap() && !g_mapInfo->CMapInfo::GetPlayerEnter(in_cpADBWork->m_CharacterInfo.m_data.mapname) )
	{
		if( InstantMap::IsInstantMap(in_cpADBWork->m_CharacterInfo.m_data.mapname) )
		{
			in_pPlayer->AddErrorCount(".\\HSvrIOPacketHandler.cpp", 672, 4, timeGetTime());
			in_pPlayer->m_isValid = 0;
			return;
		}

		map = g_mapResMgr->CMapResMgr::GetFirstMap();
		if( map == NULL )
		{
			in_pPlayer->AddErrorCount(".\\HSvrIOPacketHandler.cpp", 680, 4, timeGetTime());
			MessageBoxA(NULL, "error zone server include more than one map", NULL, MB_OK);
			return;
		}

		memcpy(in_cpADBWork->m_CharacterInfo.m_data.mapname, map->CMapRes::GetName(), sizeof(in_cpADBWork->m_CharacterInfo.m_data.mapname));
	}

	memcpy(in_pPlayer->m_characterInfo.mapName, in_cpADBWork->m_CharacterInfo.m_data.mapname, sizeof(in_pPlayer->m_characterInfo.mapName));
	in_pPlayer->m_mapRes = map;
	in_pPlayer->m_characterInfo.mapID = map->CMapRes::GetID();
	if ( !map->CMapRes::IsMovableCell(in_cpADBWork->m_CharacterInfo.m_data.xPos, in_cpADBWork->m_CharacterInfo.m_data.yPos) )
	{
		int xtemp, ytemp;
		map->CMapRes::GetRandomPos(xtemp, ytemp);
		in_cpADBWork->m_CharacterInfo.m_data.xPos = xtemp;
		in_cpADBWork->m_CharacterInfo.m_data.yPos = ytemp;
	}

	in_pPlayer->m_pcClientUpdater.CPCClientUpdater::SetAccountName(in_IDstr);
	in_pPlayer->m_characterTimeInfo.TotalUsingTime = in_TotalUsingTime;
	in_pPlayer->m_isValid = 1;
	in_pPlayer->m_characterInfo.job = in_cpADBWork->m_CharacterInfo.m_data.job;
	in_pPlayer->m_characterInfo.speed = in_cpADBWork->m_CharacterInfo.m_data.speed;
	in_pPlayer->m_pcClientUpdater.CPCClientUpdater::SetCharacterName(in_cpADBWork->m_CharacterInfo.m_data.name);
	in_pPlayer->m_characterPInfo.effectState = ( in_cpADBWork->m_CharacterInfo.m_data.effectstate >= 0 ) ? in_cpADBWork->m_CharacterInfo.m_data.effectstate : 0;
	in_pPlayer->m_characterInfo.exp = in_cpADBWork->m_CharacterInfo.m_data.exp;
	in_pPlayer->m_characterInfo.hp = ( in_cpADBWork->m_CharacterInfo.m_data.hp >= 0 ) ? in_cpADBWork->m_CharacterInfo.m_data.hp : 1;
	in_pPlayer->m_characterInfo.sp = in_cpADBWork->m_CharacterInfo.m_data.sp;
	in_pPlayer->m_characterInfo.clevel = in_cpADBWork->m_CharacterInfo.m_data.clevel;
	in_pPlayer->m_characterInfo.sppoint = in_cpADBWork->m_CharacterInfo.m_data.sppoint;
	in_pPlayer->m_characterInfo.jobpoint = in_cpADBWork->m_CharacterInfo.m_data.jobpoint;
	in_pPlayer->m_characterInfo.Str = in_cpADBWork->m_CharacterInfo.m_data.Str;
	in_pPlayer->m_characterInfo.Agi = in_cpADBWork->m_CharacterInfo.m_data.Agi;
	in_pPlayer->m_characterInfo.Vit = in_cpADBWork->m_CharacterInfo.m_data.Vit;
	in_pPlayer->m_characterInfo.Int = in_cpADBWork->m_CharacterInfo.m_data.Int;
	in_pPlayer->m_characterInfo.Dex = in_cpADBWork->m_CharacterInfo.m_data.Dex;
	in_pPlayer->m_characterInfo.Luk = in_cpADBWork->m_CharacterInfo.m_data.Luk;
	in_pPlayer->m_characterInfo.neverDie = in_cpADBWork->m_CharacterInfo.m_data.virtue;

	STATUS* status;
	if( CPC::GetCategorySecondJob(in_pPlayer->m_characterInfo.job) != JT_SUPERNOVICE || in_pPlayer->m_characterInfo.neverDie || in_cpADBWork->m_CharacterInfo.m_data.joblevel < 70 )
	{
		status = g_StatusPlusnfoByJLV->CStatusPlusInfoByJLV::GetResultPlusStatusInfo(in_cpADBWork->m_CharacterInfo.m_data.job, in_cpADBWork->m_CharacterInfo.m_data.joblevel);
	}
	else
	{
		status = g_StatusPlusnfoByJLV->CStatusPlusInfoByJLV::GetResultPlusStatusInfo(in_cpADBWork->m_CharacterInfo.m_data.job, 100);
	}

	in_pPlayer->m_plusStatusByJob.Dex = status->Dex;
	in_pPlayer->m_plusStatusByJob.Str = status->Str;
	in_pPlayer->m_plusStatusByJob.Int = status->Int;
	in_pPlayer->m_plusStatusByJob.Luk = status->Luk;
	in_pPlayer->m_plusStatusByJob.Agi = status->Agi;
	in_pPlayer->m_plusStatusByJob.Vit = status->Vit;
	in_pPlayer->m_characterInfo.money = max(0, in_cpADBWork->m_CharacterInfo.m_data.money);
	in_pPlayer->m_characterInfo.jobexp = in_cpADBWork->m_CharacterInfo.m_data.jobexp;
	in_pPlayer->m_characterInfo.virtue = 0;
	in_pPlayer->m_characterInfo.haircolor = in_cpADBWork->m_CharacterInfo.m_data.haircolor;
	in_pPlayer->m_characterInfo.head = in_cpADBWork->m_CharacterInfo.m_data.head;
	in_pPlayer->m_characterInfo.joblevel = in_cpADBWork->m_CharacterInfo.m_data.joblevel;
	in_pPlayer->m_characterPInfo.bodyState = in_cpADBWork->m_CharacterInfo.m_data.bodystate;
	in_pPlayer->m_characterPInfo.healthState = in_cpADBWork->m_CharacterInfo.m_data.healthstate;
	in_pPlayer->m_characterInfo.sxPos = in_cpADBWork->m_CharacterInfo.m_data.sxPos;
	in_pPlayer->m_characterInfo.syPos = in_cpADBWork->m_CharacterInfo.m_data.syPos;
	in_pPlayer->m_characterInfo.headpalette = in_cpADBWork->m_CharacterInfo.m_data.headpalette;
	in_pPlayer->m_characterInfo.bodypalette = in_cpADBWork->m_CharacterInfo.m_data.bodypalette;
	in_pPlayer->m_characterInfo.cookMastery = in_cpADBWork->m_CharacterInfo.m_data.cookMastery;
	in_pPlayer->m_characterPInfo.effectState = in_cpADBWork->m_CharacterInfo.m_data.effectstate;
	in_pPlayer->m_characterInfo.honor = in_cpADBWork->m_CharacterInfo.m_data.honor;

	if( g_ZenyChecksum != 0 )
	{
		char ZenyCheckSum[4];
		*(DWORD*)ZenyCheckSum = *(DWORD*)in_cpADBWork->m_CharacterInfo.m_data.ZenyCheckSum;

		if( in_cpADBWork->m_CharacterInfo.m_data.money != 0 )
		{
			int CheckMoney = *(DWORD*)ZenyCheckSum ^ in_pPlayer->m_characterInfo.characterID ^ 0x294029;
			if( CheckMoney != in_cpADBWork->m_CharacterInfo.m_data.money )
			{
				if( g_ZenyChecksum == 1 )
				{
					in_pPlayer->AddErrorCount(".\\HSvrIOPacketHandler.cpp", 816, 4, timeGetTime());
					in_pPlayer->m_isValid = 0;
					g_errorLogs->CErrorLog::CriticalErrorLogFmt(".\\HSvrIOPacketHandler.cpp", 818, "Error _ZENY_CHECKSUM (GID=%d), %d, %d", in_pPlayer->m_characterInfo.characterID, CheckMoney, in_cpADBWork->m_CharacterInfo.m_data.money);
				}
			}
		}
	}

	memcpy(in_pPlayer->m_characterInfo.restartMapName, in_cpADBWork->m_CharacterInfo.m_data.restartMapName, sizeof(in_pPlayer->m_characterInfo.restartMapName));
	in_pPlayer->m_characterInfo.targetMapName[0] = 0;
	in_pPlayer->m_pcClientUpdater.CPCClientUpdater::InitPosition(in_cpADBWork->m_CharacterInfo.m_data.xPos, in_cpADBWork->m_CharacterInfo.m_data.yPos, 0);
	in_pPlayer->m_pcClientUpdater.CPCClientUpdater::SetParameterPointValue();
	in_pPlayer->m_characterInfo.font = in_cpADBWork->m_CharacterInfo.m_data.font;

	in_pPlayer->CPC::ForceSend(sizeof(in_AID), (char *)&in_AID);
	SendPacket_ZC_ACCEPT_ENTER2(in_pPlayer);

	FamilyInfo familyInfo;
	memset(&familyInfo, 0, sizeof(familyInfo));
	if( g_familyInfoDB->CFamilyInfoDB::GetFamilyInfo(in_pPlayer, in_pPlayer->m_characterInfo.sex, familyInfo) == 1 )
		in_pPlayer->CPC::SetFamilyInfo(&familyInfo, 0);

	char buffer[20];
	itoa(in_pPlayer->m_characterInfo.characterID, buffer, 10);
	in_pPlayer->CCharacter::OnMsgFromItemServer((const int)"ChatLog", (CITZMsg*)buffer);

	in_pPlayer->m_pcClientUpdater.CPCClientUpdater::SetSendable(1);

	if( !in_pPlayer->m_pcSkill.CPCSkill::LoadSkill(in_cpADBWork->m_SkillData.m_Length, in_cpADBWork->m_SkillData.m_Data) )
	{
		g_errorLogs->CErrorLog::CriticalErrorLogFmt(".\\HSvrIOPacketHandler.cpp", 984, "Parse Error Skill (GID=%d)", in_pPlayer->CPC::GetCharacterID());
		in_pPlayer->AddErrorCount(".\\HSvrIOPacketHandler.cpp", 985, 4, timeGetTime());
		in_pPlayer->m_isValid = 0;
		return;
	}

	if( !in_pPlayer->m_pcitemInventoryMgr.CPCItemInventoryMgr::ParseDBFmtBodyItemData(in_cpADBWork->m_BodyItemInfo.m_length, in_cpADBWork->m_BodyItemInfo.m_Data) )
	{
		g_errorLogs->CErrorLog::CriticalErrorLogFmt(".\\HSvrIOPacketHandler.cpp", 992, "Parse Error BodyItemData(GID=%d)", in_pPlayer->CPC::GetCharacterID());
		in_pPlayer->AddErrorCount(".\\HSvrIOPacketHandler.cpp", 993, 4, timeGetTime());
		in_pPlayer->m_isValid = 0;
		return;
	}

	if( !in_pPlayer->m_questEvent.CPCQuestEvent::AsyncDBComplete_LoadQuestEvent(
		in_cpADBWork->m_questData.m_questEvent_Data,
		in_cpADBWork->m_questData.m_questEvent_Length,
		in_cpADBWork->m_questData.m_quest_hunt_Data,
		in_cpADBWork->m_questData.m_quest_hunt_Length,
		in_cpADBWork->m_questData.m_quest_time_Data,
		in_cpADBWork->m_questData.m_quest_time_Length,
		in_cpADBWork->m_questData.m_completeQuest_Data,
		in_cpADBWork->m_questData.m_completeQuest_Length) )
	{
		g_errorLogs->CErrorLog::CriticalErrorLogFmt(".\\HSvrIOPacketHandler.cpp", 1003, "Parse Error QuestEventData(GID=%d)", in_pPlayer->CPC::GetCharacterID());
		in_pPlayer->AddErrorCount(".\\HSvrIOPacketHandler.cpp", 1004, 4, timeGetTime());
		in_pPlayer->m_isValid = 0;
		return;
	}

	CoupleInfo info;
	int ret = g_coupleInfoDB->CCoupleInfoDB::GetCoupleInfo(in_pPlayer, in_pPlayer->m_characterInfo.sex, info);
	if( ret == 1 )
		in_pPlayer->CPC::SetCoupleInfo(&info, 0);
	else
	if( ret != -1 )
		in_pPlayer->CPC::DeleteMarriagering();
	else
	{
		g_errorLogs->CErrorLog::CriticalErrorLog("Load GetCoupleInfo Fail\n", 1036, ".\\HSvrIOPacketHandler.cpp");
		in_pPlayer->AddErrorCount(".\\HSvrIOPacketHandler.cpp", 1037, 4, timeGetTime());
		in_pPlayer->m_isValid = 0;
	}

	g_makerRankMgr->CMakerRankMgr::GetMakerRank(in_pPlayer->CPC::GetCharacterID(), in_pPlayer->m_makerRankPoint, CPC::GetCategorySecondJob(in_pPlayer->m_characterInfo.job));
	in_pPlayer->CPC::SetPlusMakerPower();
	in_pPlayer->CPC::GetPKInfo();
	in_pPlayer->m_mannerPoint.MannerPointInfo::LoadMPInfo();
	in_pPlayer->CActor::SetStateDBFmt(in_cpADBWork->m_StateData.m_Data, in_cpADBWork->m_StateData.m_Length);
	in_pPlayer->CPC::LoadEffectiveInfo(in_cpADBWork->m_EffectiveData.m_Data2, in_cpADBWork->m_EffectiveData.m_Length);
	in_pPlayer->CPC::LoadHuntingList();
	in_pPlayer->CPC::LoadTimeList();

	HOMUN_DBINFO DBInfo;
	if( g_merceDB->CMerceDB::GetHomunInfo(in_GID, &DBInfo) )
		in_pPlayer->m_pcBattle.CPCBattle::SetHomunDBInfo(&DBInfo);

	in_pPlayer->CPC::SetBattleFieldInfo(in_cpADBWork->m_battleFieldData.m_campID, in_cpADBWork->m_battleFieldData.m_x, in_cpADBWork->m_battleFieldData.m_y, false);

	if( g_isMobileEventOn == 1 )
		in_pPlayer->CPC::InitMobileEvent();

	in_pPlayer->m_pcClientUpdater.CPCClientUpdater::SetSendable(0);
	in_pPlayer->m_characterTimeInfo.LastNPCEventAnswerTime = 0;

	PACKET_ZI_LOGON zipacket;
	zipacket.PacketType = HEADER_ZI_LOGON;
	zipacket.AID = in_AID;
	zipacket.GID = in_pPlayer->m_pcClientUpdater.CPCClientUpdater::GetCharacterID();
	zipacket.sex = in_pPlayer->m_characterInfo.sex;
	zipacket.head = in_cpADBWork->m_CharacterInfo.m_data.head;
	zipacket.headpalette = in_cpADBWork->m_CharacterInfo.m_data.headpalette;
	zipacket.level = in_cpADBWork->m_CharacterInfo.m_data.clevel;
	zipacket.job = in_cpADBWork->m_CharacterInfo.m_data.job;
	memcpy(zipacket.accountName, in_IDstr, sizeof(zipacket.accountName));
	memcpy(zipacket.charName, in_cpADBWork->m_CharacterInfo.m_data.name, sizeof(zipacket.charName));
	memcpy(zipacket.mapName, in_cpADBWork->m_CharacterInfo.m_data.mapname, sizeof(zipacket.mapName));
	g_characterMgr->CCharacterMgr::SendToIServer(sizeof(zipacket), (const char *)&zipacket);

	++g_ZoneInterLoginValue;

	in_pPlayer->CPC::GameGuardInit();
	in_pPlayer->CPC::SendShortCutKeyInfo();

	in_pPlayer->m_characterInfo.Party.Config = in_cpADBWork->m_CharacterInfo.m_data.Party.Config;

	PACKET_ZC_PARTY_CONFIG packet;
	packet.PacketType = HEADER_ZC_PARTY_CONFIG;
	packet.bRefuseJoinMsg = in_cpADBWork->m_CharacterInfo.m_data.Party.Config & 1;
	in_pPlayer->CPC::ForceSend(sizeof(packet), (char *)&packet);

	in_pPlayer->m_characterInfo.bOpenEquipmentWin = in_cpADBWork->m_CharacterInfo.m_data.bOpenEquipmentWin;

	PACKET_ZC_CONFIG_NOTIFY packet_;
	packet_.PacketType = HEADER_ZC_CONFIG_NOTIFY;
	packet_.bOpenEquipmentWin = in_pPlayer->m_characterInfo.bOpenEquipmentWin;
	in_pPlayer->CPC::ForceSend(sizeof(packet_), (char *)&packet_);
}


hook_method<int (CHSvrIOPacketHandler::*)(short Header, int packetSize)> CHSvrIOPacketHandler::_DispatchPacket(SERVER, "CHSvrIOPacketHandler::DispatchPacket");
int CHSvrIOPacketHandler::DispatchPacket(short Header, int packetSize) // line 188
{
	return (this->*_DispatchPacket)(Header, packetSize);

	switch( Header )
	{
	case HEADER_PING:
	{
		PACKET_PING ping;
		m_recvQueue->CPacketQueue::GetData(sizeof(ping), (char*)&ping);
	}
	break;
	case HEADER_HZ_CHAR_NAME_CHANGED:
	{
		PACKET_HZ_CHAR_NAME_CHANGED in_packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(in_packet), (char*)&in_packet);
		this->CHSvrIOPacketHandler::OnHZ_CHAR_NAME_CHANGED(in_packet);
	}
	break;
	case HEADER_HZ_PING:
	{
		PACKET_HZ_PING in_packet;
		m_recvQueue->CPacketQueue::GetData(sizeof(in_packet), (char*)&in_packet);
		this->CHSvrIOPacketHandler::OnHZ_PING(in_packet);
	}
	break;
	case HEADER_HZ_INFO_REMAINTIME:
		this->CHSvrIOPacketHandler::OnInfoRemainTime(packetSize);
	break;
	case HEADER_HZ_RES_REMAINTIME:
		this->CHSvrIOPacketHandler::OnResRemainTime(packetSize);
	break;
	case HEADER_HZ_LOGON_NOTEXIST:
		this->CHSvrIOPacketHandler::OnLogonRefuse(packetSize);
	break;
	case HEADER_HZ_DISCONNECT:
		this->CHSvrIOPacketHandler::OnDisconnect(packetSize, HEADER_HZ_DISCONNECT);
	break;
	case HEADER_HZ_DISCONNECT_RIGHTNOW:
		this->CHSvrIOPacketHandler::OnDisconnect(packetSize, HEADER_HZ_DISCONNECT_RIGHTNOW);
	break;
	case HEADER_HZ_ACK_MAPMOVE:
		this->CHSvrIOPacketHandler::OnMapMove(packetSize);
	break;
	case HEADER_HZ_ACK_RESTART:
		this->CHSvrIOPacketHandler::OnHServerRestart(packetSize);
	break;
	case HEADER_HZ_NOTIFY_PCBANG:
		this->CHSvrIOPacketHandler::OnNotifyPCBang(packetSize);
	break;
	case HEADER_HZ_NOTIFY_PCBANG_PLAYING_TIME:
		this->CHSvrIOPacketHandler::OnNotifyPCBangPlayingTime(packetSize);
	break;
	case HEADER_HZ_LOGON_EXIST:
		this->CHSvrIOPacketHandler::OnLogonPermit(packetSize);
	break;
	default:
		m_recvQueue->CPacketQueue::Reset();

		char temp[256];
		sprintf(temp, "Not Header HSvrIO Header:%d, packetSize:%d\n", Header, packetSize);
		g_errorLogs->CErrorLog::CriticalErrorLog(temp, 261, ".\\HSvrIOPacketHandler.cpp");
		Trace("not Header HSvrIO\n");
		return 0;
	}

	return -1;
}


hook_method<void (CHSvrIOPacketHandler::*)(int len, int type)> CHSvrIOPacketHandler::_OnDisconnect(SERVER, "CHSvrIOPacketHandler::OnDisconnect");
void CHSvrIOPacketHandler::OnDisconnect(int len, int type) // line 313
{
	return (this->*_OnDisconnect)(len, type);

	PACKET_HZ_DISCONNECT packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char*)&packet);

	Trace("PACKET_HZ_DISCONNECT\t%d \n", type);
	g_characterMgr->CCharacterMgr::SendMsg(NULL, packet.AID, 4, packet.reason, type, 0, 0);
}


hook_method<void (CHSvrIOPacketHandler::*)(int len)> CHSvrIOPacketHandler::_OnLogonRefuse(SERVER, "CHSvrIOPacketHandler::OnLogonRefuse");
void CHSvrIOPacketHandler::OnLogonRefuse(int len) // line 281-305
{
	return (this->*_OnLogonRefuse)(len);

	Trace("PACKET_HZ_LOGON_ACK\t\n");
	PACKET_HZ_LOGON_ACK packet;
	m_recvQueue->CPacketQueue::GetData(sizeof(packet), (char *)&packet);

	CPC* pc= static_cast<CPC*>(g_characterMgr->CCharacterMgr::FindCharacter(packet.AID, PC_TYPE));
	if( pc )
	{
		Trace("Logon Refuse\n");
		pc->CPC::ForceSend(sizeof(packet.AID), (char *)&packet.AID);
		pc->AddErrorCount(".\\HSvrIOPacketHandler.cpp", 290, 4, timeGetTime());
		g_errorLogs->CErrorLog::CriticalErrorLog("Logon Refuse\n", 291, ".\\HSvrIOPacketHandler.cpp");
	}

	g_characterMgr->CCharacterMgr::SendMsg(0, packet.AID, CM_REFUSE_ENTER, 0, 0, 0, 0);
}


hook_method<void (CHSvrIOPacketHandler::*)(int len)> CHSvrIOPacketHandler::_OnMapMove(SERVER, "CHSvrIOPacketHandler::OnMapMove");
void CHSvrIOPacketHandler::OnMapMove(int len) // line 328
{
	return (this->*_OnMapMove)(len);

	//TODO
}


hook_method<void (CHSvrIOPacketHandler::*)(int len)> CHSvrIOPacketHandler::_OnHServerRestart(SERVER, "CHSvrIOPacketHandler::OnHServerRestart");
void CHSvrIOPacketHandler::OnHServerRestart(int len) // line 358
{
	return (this->*_OnHServerRestart)(len);

	//TODO
}


hook_method<void (CHSvrIOPacketHandler::*)(int len)> CHSvrIOPacketHandler::_OnInfoRemainTime(SERVER, "CHSvrIOPacketHandler::OnInfoRemainTime");
void CHSvrIOPacketHandler::OnInfoRemainTime(int len) // line 134
{
	return (this->*_OnInfoRemainTime)(len);

	//TODO
}


hook_method<void (CHSvrIOPacketHandler::*)(int len)> CHSvrIOPacketHandler::_OnResRemainTime(SERVER, "CHSvrIOPacketHandler::OnResRemainTime");
void CHSvrIOPacketHandler::OnResRemainTime(int len) // line 156
{
	return (this->*_OnResRemainTime)(len);

	//TODO
}


hook_method<void (CHSvrIOPacketHandler::*)(int len)> CHSvrIOPacketHandler::_OnNotifyPCBang(SERVER, "CHSvrIOPacketHandler::OnNotifyPCBang");
void CHSvrIOPacketHandler::OnNotifyPCBang(int len) // line 376
{
	return (this->*_OnNotifyPCBang)(len);

	//TODO
}


hook_method<void (CHSvrIOPacketHandler::*)(const PACKET_HZ_PING& in_packet)> CHSvrIOPacketHandler::_OnHZ_PING(SERVER, "CHSvrIOPacketHandler::OnHZ_PING");
void CHSvrIOPacketHandler::OnHZ_PING(const PACKET_HZ_PING& in_packet) // line 177
{
	return (this->*_OnHZ_PING)(in_packet);

	g_hSvrIO->CSvrIO::Send(sizeof(in_packet), (const char*)&in_packet);
}


hook_method<void (CHSvrIOPacketHandler::*)(int len)> CHSvrIOPacketHandler::_OnNotifyPCBangPlayingTime(SERVER, "CHSvrIOPacketHandler::OnNotifyPCBangPlayingTime");
void CHSvrIOPacketHandler::OnNotifyPCBangPlayingTime(int len) // line 1205
{
	return (this->*_OnNotifyPCBangPlayingTime)(len);

	//TODO
}


//hook_method<void (CHSvrIOPacketHandler::*)(const PACKET_HZ_CHAR_NAME_CHANGED& in_Packet)> CHSvrIOPacketHandler::_OnHZ_CHAR_NAME_CHANGED(SERVER, "CHSvrIOPacketHandler::OnHZ_CHAR_NAME_CHANGED");
void CHSvrIOPacketHandler::OnHZ_CHAR_NAME_CHANGED(const PACKET_HZ_CHAR_NAME_CHANGED& in_Packet) // line ???
{
//	return (this->*_OnHZ_CHAR_NAME_CHANGED)(in_Packet);

	;
}
