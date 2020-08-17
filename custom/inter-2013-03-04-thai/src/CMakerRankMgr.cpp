#include "CMakerRankMgr.h"
#include "Common/Packet.h"
#include "Zsvr/CZsvrMgr.h"


CMakerRankMgr::CMakerRankMgr()
{
	memset(m_BlackSmith, 0, sizeof(m_BlackSmith));
	memset(m_Alchemist, 0, sizeof(m_Alchemist));
	memset(m_Taekwon, 0, sizeof(m_Taekwon));
	memset(m_Killer, 0, sizeof(m_Killer));
}


CMakerRankMgr::~CMakerRankMgr()
{
}


BOOL CMakerRankMgr::Setup()
{
	m_MakerRankDB.CMakerRankDB::Get_TOP_MakerRank(CMakerRankMgr::TYPE_BLACKSMITH, m_BlackSmith);
	m_MakerRankDB.CMakerRankDB::Get_TOP_MakerRank(CMakerRankMgr::TYPE_ALCHEMIST, m_Alchemist);
	m_MakerRankDB.CMakerRankDB::Get_TOP_MakerRank(CMakerRankMgr::TYPE_TAEKWON, m_Taekwon);
	m_MakerRankDB.CMakerRankDB::Get_TOP_MakerRank(CMakerRankMgr::TYPE_KILLER, m_Killer);
	this->CMakerRankMgr::Sort(CMakerRankMgr::TYPE_BLACKSMITH);
	this->CMakerRankMgr::Sort(CMakerRankMgr::TYPE_ALCHEMIST);
	this->CMakerRankMgr::Sort(CMakerRankMgr::TYPE_TAEKWON);
	this->CMakerRankMgr::Sort(CMakerRankMgr::TYPE_KILLER);

	return TRUE;
}


BOOL CMakerRankMgr::Init(const char* FileDsn, const char* PASS)
{
	return m_MakerRankDB.CODBC::Init(FileDsn, PASS);
}


void CMakerRankMgr::SendZoneMakerRanking(int Type)
{
	PACKET_IZ_NOTIFY_MAKERRANK Packet;
	Packet.PacketType = HEADER_IZ_NOTIFY_MAKERRANK;
	Packet.type = Type;

	if( Type == CMakerRankMgr::TYPE_BLACKSMITH )
	{
		for( int i = 0; i < 10; ++i )
		{
			Packet.GID[i] = m_BlackSmith[i].GID;
			memcpy(Packet.charname[i], m_BlackSmith[i].charname, sizeof(m_BlackSmith[i].charname));
			Packet.point[i] = m_BlackSmith[i].point;
		}

		CZsvrMgr::GetObj()->CZServerMgr::BroadCast(sizeof(Packet), (char*)&Packet);
	}
	else
	if( Type == CMakerRankMgr::TYPE_ALCHEMIST )
	{
		for( int i = 0; i < 10; ++i )
		{
			Packet.GID[i] = m_Alchemist[i].GID;
			memcpy(Packet.charname[i], m_Alchemist[i].charname, sizeof(m_Alchemist[i].charname));
			Packet.point[i] = m_Alchemist[i].point;
		}

		CZsvrMgr::GetObj()->CZServerMgr::BroadCast(sizeof(Packet), (char*)&Packet);
	}
	else
	if( Type == CMakerRankMgr::TYPE_TAEKWON )
	{
		for( int i = 0; i < 10; ++i )
		{
			Packet.GID[i] = m_Taekwon[i].GID;
			memcpy(Packet.charname[i], m_Taekwon[i].charname, sizeof(m_Taekwon[i].charname));
			Packet.point[i] = m_Taekwon[i].point;
		}

		CZsvrMgr::GetObj()->CZServerMgr::BroadCast(sizeof(Packet), (char*)&Packet);
	}
	else
	if( Type == CMakerRankMgr::TYPE_KILLER )
	{
		for( int i = 0; i < 10; ++i )
		{
			Packet.GID[i] = m_Killer[i].GID;
			memcpy(Packet.charname[i], m_Killer[i].charname, sizeof(m_Killer[i].charname));
			Packet.point[i] = m_Killer[i].point;
		}

		CZsvrMgr::GetObj()->CZServerMgr::BroadCast(sizeof(Packet), (char*)&Packet);
	}
}


void CMakerRankMgr::UpdateMakeRank(int Type, unsigned long GID, char* Name, int Point)
{
	if( Type == CMakerRankMgr::TYPE_BLACKSMITH )
	{
		BOOL bFound = FALSE;

		for( int i = 0; i < 10; ++i )
		{
			if( m_BlackSmith[i].GID == GID )
			{
				memcpy(m_BlackSmith[i].charname, Name, sizeof(m_BlackSmith[i].charname));
				m_BlackSmith[i].point = Point;
				bFound = true;
			}
		}

		if( !bFound )
		{
			m_BlackSmith[10].GID = GID;
			memcpy(m_BlackSmith[10].charname, Name, sizeof(m_BlackSmith[10].charname));
			m_BlackSmith[10].point = Point;
		}
	}
	else
	if( Type == CMakerRankMgr::TYPE_ALCHEMIST )
	{
		BOOL bFound = FALSE;

		for( int i = 0; i < 10; ++i )
		{
			if( m_Alchemist[i].GID == GID )
			{
				memcpy(m_Alchemist[i].charname, Name, sizeof(m_Alchemist[i].charname));
				m_Alchemist[i].point = Point;
				bFound = true;
			}
		}

		if( !bFound )
		{
			m_Alchemist[10].GID = GID;
			memcpy(m_Alchemist[10].charname, Name, sizeof(m_Alchemist[10].charname));
			m_Alchemist[10].point = Point;
		}
	}
	else
	if( Type == CMakerRankMgr::TYPE_TAEKWON )
	{
		BOOL bFound = FALSE;

		for( int i = 0; i < 10; ++i )
		{
			if( m_Taekwon[i].GID == GID )
			{
				memcpy(m_Taekwon[i].charname, Name, sizeof(m_Taekwon[i].charname));
				m_Taekwon[i].point = Point;
				bFound = true;
			}
		}

		if( !bFound )
		{
			m_Taekwon[10].GID = GID;
			memcpy(m_Taekwon[10].charname, Name, sizeof(m_Taekwon[10].charname));
			m_Taekwon[10].point = Point;
		}
	}
	else
	if( Type == CMakerRankMgr::TYPE_KILLER )
	{
		BOOL bFound = FALSE;

		for( int i = 0; i < 10; ++i )
		{
			if( m_Killer[i].GID == GID )
			{
				memcpy(m_Killer[i].charname, Name, sizeof(m_Killer[i].charname));
				m_Killer[i].point = Point;
				bFound = true;
			}
		}

		if( !bFound )
		{
			m_Killer[10].GID = GID;
			memcpy(m_Killer[10].charname, Name, sizeof(m_Killer[10].charname));
			m_Killer[10].point = Point;
		}
	}
	else
	{
		return;
	}

	this->CMakerRankMgr::Sort(Type);
	this->CMakerRankMgr::SendZoneMakerRanking(Type);
}


static int __cdecl SortRanking(const void* pOne, const void* pTwo)
{
	const MAKER_RANKING* p2 = reinterpret_cast<const MAKER_RANKING*>(pTwo);
	const MAKER_RANKING* p1 = reinterpret_cast<const MAKER_RANKING*>(pOne);
	return p2->point - p1->point;
}


void CMakerRankMgr::Sort(int Type)
{
	if( Type == CMakerRankMgr::TYPE_BLACKSMITH )
		qsort(m_BlackSmith, countof(m_BlackSmith)-1, sizeof(MAKER_RANKING), &SortRanking);
	else
	if( Type == CMakerRankMgr::TYPE_ALCHEMIST )
		qsort(m_Alchemist, countof(m_Alchemist)-1, sizeof(MAKER_RANKING), &SortRanking);
	else
	if( Type == CMakerRankMgr::TYPE_TAEKWON )
		qsort(m_Taekwon, countof(m_Taekwon)-1, sizeof(MAKER_RANKING), &SortRanking);
	else
	if( Type == CMakerRankMgr::TYPE_KILLER )
		qsort(m_Killer, countof(m_Killer)-1, sizeof(MAKER_RANKING), &SortRanking);
}
