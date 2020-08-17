#include "CharacterMgr.h"
#include "MakerRankDB.h"
#include "MakerRankMgr.h"
#include "PC.h"
#include "ZoneProcess.h"
#include "shared/shared.h"


CMakerRankMgr::CMakerRankMgr()
{
}


CMakerRankMgr::~CMakerRankMgr()
{
}


void CMakerRankMgr::ResetMakerRankList(int type)
{
	m_MakerRankList[type].clear();
	memset(&m_MakerRank[type], 0, sizeof(m_MakerRank[type]));
}


void CMakerRankMgr::Get_TOP_MakerRank(int type)
{
	this->CMakerRankMgr::ResetMakerRankList(type);
	g_makerRankDB.CMakerRankDB::Get_TOP_MakerRank(type, m_MakerRank[type]);
	this->CMakerRankMgr::SortMakerRankList(type);
}


BOOL CMakerRankMgr::UpdateMakerRank(CPC* pc, int type, int value, int& point)
{
	if( pc == NULL )
		return FALSE;

	int p;
	if( type == BLACKSMITH_VERSION )
	{
		if( value == 1 )
		{
			p = 1;
			point += p;
		}
		else
		if( value == 2 )
		{
			p = 25;
			point += p;
		}
		else
		if( value == 3 )
		{
			p = 1000;
			point += p;
		}
		else
		if( value == 5 )
		{
			p = 10;
			point += p;
		}
		else
		{
			return FALSE;
		}
	}
	else
	if( type == ALCHEMIST_VERSION )
	{
		if( value == 3 )
		{
			p = 1;
			point += p;
		}
		else
		if( value == 5 )
		{
			p = 3;
			point += p;
		}
		else
		if( value == 7 )
		{
			p = 10;
			point += p;
		}
		else
		if( value == 10 )
		{
			p = 50;
			point += p;
		}
		else
		if( value >= 100 )
		{
			p = value - 100;
			point += p;
		}
		else
		{
			return FALSE;
		}
	}
	else
	if( type == TAEKWON_VERSION )
	{
		p = 1;
		point += p;
	}
	else
	if( type == KILLER_VERSION )
	{
		p = value;
		//NOTE: no increment
	}
	else
	if( type == GANGSI_VERSION || type == DEATHKNIGHT_VERSION || type == COLLECTOR_VERSION )
	{
		p = value;
		point += p;
	}
	else
	{
		return FALSE;
	}

	unsigned long GID = pc->CPC::GetCharacterID();
	char charname[24];
	memcpy_s(charname, sizeof(charname), pc->m_characterInfo.characterName, sizeof(pc->m_characterInfo.characterName));

	if( g_makerRankDB.CMakerRankDB::UpdateMakerRank(GID, charname, type, point) != 1 )
	{
		Trace("길드 랭킹 저장 에러 GID = %d, CharName = %s, Type = %d, Point = %d \n", GID, charname, type, point);
		return FALSE;
	}

	if( type <= KILLER_VERSION )
	{
		PACKET_ZC_BLACKSMITH_POINT packet;

		if( type == BLACKSMITH_VERSION )
			packet.PacketType = HEADER_ZC_BLACKSMITH_POINT;
		else
		if( type == ALCHEMIST_VERSION )
			packet.PacketType = HEADER_ZC_ALCHEMIST_POINT;
		else
		if( type == TAEKWON_VERSION )
			packet.PacketType = HEADER_ZC_TAEKWON_POINT;
		else
		if( type == KILLER_VERSION )
			packet.PacketType = HEADER_ZC_KILLER_POINT;

		packet.TotalPoint = point;
		packet.Point = p;
		pc->Send(sizeof(packet), (const char*)&packet);
	}
	else
	{
		PACKET_ZC_GANGSI_POINT packet;

		packet.PacketType = HEADER_ZC_GANGSI_POINT;
		if( type == GANGSI_VERSION )
			packet.PacketSwitch = JT_GANGSI;
		else
		if( type == DEATHKNIGHT_VERSION )
			packet.PacketSwitch = JT_DEATHKNIGHT;
		else
		if( type == COLLECTOR_VERSION )
			packet.PacketSwitch = JT_COLLECTOR;

		packet.TotalPoint = point;
		packet.Point = p;
		pc->Send(sizeof(packet), (const char*)&packet);
	}

	if( point > m_MakerRank[type][MAKERRANKPOS_MAX-1].point )
	{
		PACKET_ZI_UPDATE_MAKERRANK ZIPacket;
		ZIPacket.PacketType = HEADER_ZI_UPDATE_MAKERRANK;
		ZIPacket.type = type;
		ZIPacket.GID = GID;
		ZIPacket.point = point;
		memcpy_s(ZIPacket.charname, sizeof(ZIPacket.charname), charname, sizeof(charname));
		CCharacterMgr::GetObj()->CCharacterMgr::SendToIServer(sizeof(ZIPacket), (const char*)&ZIPacket);
	}

	return TRUE;
}


void CMakerRankMgr::GetMakerRank(unsigned long GID, int& point, int JobType)
{
	int type;
	if( JobType == JT_BLACKSMITH )
		type = BLACKSMITH_VERSION;
	else
	if( JobType == JT_ALCHEMIST )
		type = ALCHEMIST_VERSION;
	else
	if( JobType == JT_TAEKWON )
		type = TAEKWON_VERSION;
	else
	{
		return;
	}

	g_makerRankDB.CMakerRankDB::GetMakerRank(GID, point, type);
}


void CMakerRankMgr::SortMakerRankList(int type)
{
	for( int i = 0; i < MAKERRANKPOS_MAX; ++i )
	{
		if( m_MakerRank[type][i].GID == 0 )
			continue;

		MAKERINFO info;
		memcpy(info.charname, m_MakerRank[type][i].charname, 24);
		info.point = m_MakerRank[type][i].point;
		info.rank = i;

		m_MakerRankList[type].insert(std::pair<unsigned long const,MAKERINFO>(m_MakerRank[type][i].GID, info));
	}
}


int CMakerRankMgr::GetMakerPower(unsigned long GID, int type)
{
	std::map<unsigned long,MAKERINFO>::iterator iter = m_MakerRankList[type].find(GID);
	if( iter == m_MakerRankList[type].end() )
		return 0;

	if( type == BLACKSMITH_VERSION )
		return 10;
	else
	if( type == ALCHEMIST_VERSION )
		return 50;
	else
	{
		return 1;
	}
}


void CMakerRankMgr::SetMakerRankList(char* buf)
{
	PACKET_IZ_NOTIFY_MAKERRANK packet;
	memcpy_s(&packet, sizeof(packet), buf, sizeof(PACKET_IZ_NOTIFY_MAKERRANK));

	if( packet.type > MAKERRANKTYPE_MAX ) //FIXME: off-by-one
		return;

	this->CMakerRankMgr::ResetMakerRankList(packet.type);

	for( int i = 0; i < MAKERRANKPOS_MAX; ++i )
	{
		if( packet.GID[i] == 0 )
			break;

		m_MakerRank[packet.type][i].GID = packet.GID[i];
		memcpy_s(m_MakerRank[packet.type][i].charname, sizeof(m_MakerRank[packet.type][i].charname), packet.charname[i], sizeof(packet.charname[i]));
		m_MakerRank[packet.type][i].point = packet.point[i];

		MAKERINFO info;
		info.rank = i;
		memcpy_s(info.charname, sizeof(info.charname), packet.charname[i], sizeof(packet.charname[i]));
		info.point = packet.point[i];

		m_MakerRankList[packet.type].insert(std::pair<unsigned long const,MAKERINFO>(packet.GID[i], info));
	}
}


int CMakerRankMgr::GetRankFromTop10(CPC* pc)
{
	if( pc == NULL )
		return 0;

	int job = CPC::GetCategorySecondJob(pc->m_characterInfo.job);

	int type;
	if( job == JT_BLACKSMITH )
		type = BLACKSMITH_VERSION;
	else
	if( job == JT_ALCHEMIST )
		type = ALCHEMIST_VERSION;
	else
	if( job == JT_TAEKWON )
		type = TAEKWON_VERSION;
	else
	{
		return 0;
	}

	unsigned long GID = pc->CPC::GetCharacterID();

	unsigned long i;
	for( i = 0; i < MAKERRANKPOS_MAX; ++i )
		if( GID == m_MakerRank[type][i].GID )
			break; // found.

	if( i >= MAKERRANKPOS_MAX )
		return 0; // not found.

	return i + 1;
}
