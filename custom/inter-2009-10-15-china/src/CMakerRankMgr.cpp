#include "CMakerRankMgr.h"


CMakerRankMgr::CMakerRankMgr(void) // line 14
{
	///NOTE: original code only memset first 11 fields
	memset(m_BlackSmith, 0, sizeof(m_BlackSmith));
	memset(m_Alchemist, 0, sizeof(m_Alchemist));
	memset(m_Taekwon, 0, sizeof(m_Taekwon));
	memset(m_Killer, 0, sizeof(m_Killer));
	memset(m_Gangsi, 0, sizeof(m_Gangsi));
	memset(m_DeathKnight, 0, sizeof(m_DeathKnight));
	memset(m_Collector, 0, sizeof(m_Collector));
}


CMakerRankMgr::~CMakerRankMgr(void) // line 26
{
}


hook_method<int (CMakerRankMgr::*)(const char* DSN, const char* UID, const char* PASS, const char* DB, unsigned char type)> CMakerRankMgr::_Init(SERVER, "CMakerRankMgr::Init");
int CMakerRankMgr::Init(const char* DSN, const char* UID, const char* PASS, const char* DB, unsigned char type) // line 59
{
	return (this->*_Init)(DSN, UID, PASS, DB, type);

	//TODO
}


hook_method<int (CMakerRankMgr::*)(void)> CMakerRankMgr::_Setup(SERVER, "CMakerRankMgr::Setup");
int CMakerRankMgr::Setup(void) // line 31
{
	return (this->*_Setup)();

	//TODO
}


hook_method<void (CMakerRankMgr::*)(int Type)> CMakerRankMgr::_SendZoneMakerRanking(SERVER, "CMakerRankMgr::SendZoneMakerRanking");
void CMakerRankMgr::SendZoneMakerRanking(int Type) // line 64
{
	return (this->*_SendZoneMakerRanking)(Type);

	//TODO
}


hook_method<void (CMakerRankMgr::*)(int Type, unsigned long GID, char* Name, int Point)> CMakerRankMgr::_UpdateMakeRank(SERVER, "CMakerRankMgr::UpdateMakeRank");
void CMakerRankMgr::UpdateMakeRank(int Type, unsigned long GID, char* Name, int Point) // line 149
{
	return (this->*_UpdateMakeRank)(Type, GID, Name, Point);

	//TODO
}


hook_method<void (CMakerRankMgr::*)(int Type)> CMakerRankMgr::_Sort(SERVER, "CMakerRankMgr::Sort");
void CMakerRankMgr::Sort(int Type) // line 283
{
	return (this->*_Sort)(Type);

	//TODO
}
