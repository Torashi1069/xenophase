#include "CMapPropertyCountPK.hpp"


CMapPropertyCountPK::CMapPropertyCountPK(void)
{
	m_winpointPool.CMemoryMgr<WINPOINT>::Init(256);
}


CMapPropertyCountPK::~CMapPropertyCountPK(void)
{
	this->CMapPropertyCountPK::Reset();
}


hook_method<bool (CMapPropertyCountPK::*)(unsigned long AID, int winpoint)> CMapPropertyCountPK::_UpdateWinPoint(SERVER, "CMapPropertyCountPK::UpdateWinPoint");
bool CMapPropertyCountPK::UpdateWinPoint(unsigned long AID, int winpoint)
{
	return (this->*_UpdateWinPoint)(AID, winpoint);

	//TODO
}


hook_method<bool (CMapPropertyCountPK::*)(unsigned long AID)> CMapPropertyCountPK::_DeleteWinPoint(SERVER, "CMapPropertyCountPK::DeleteWinPoint");
bool CMapPropertyCountPK::DeleteWinPoint(unsigned long AID)
{
	return (this->*_DeleteWinPoint)(AID);

	//TODO
}


hook_method<void (CMapPropertyCountPK::*)(void)> CMapPropertyCountPK::_Reset(SERVER, "CMapPropertyCountPK::Reset");
void CMapPropertyCountPK::Reset(void)
{
	return (this->*_Reset)();

	this->CMapPropertyCountPK::ClearWinpoint();
}


/* hook_method<int (CMapPropertyCountPK::*)(unsigned long AID)> CMapPropertyCountPK::_GetPCRanking(SERVER, "CMapPropertyCountPK::GetPCRanking");
int CMapPropertyCountPK::GetPCRanking(unsigned long AID)
{
	return (this->*_GetPCRanking)(AID);

	//TODO
} */


hook_method<void (CMapPropertyCountPK::*)(WINPOINT* p)> CMapPropertyCountPK::_DeleteFromList(SERVER, "CMapPropertyCountPK::DeleteFromList");
void CMapPropertyCountPK::DeleteFromList(WINPOINT* p)
{
	return (this->*_DeleteFromList)(p);

	//TODO
}


hook_method<mystd::list<WINPOINT*>::iterator (CMapPropertyCountPK::*)(int winpoint)> CMapPropertyCountPK::_UpperBound(SERVER, "CMapPropertyCountPK::UpperBound");
mystd::list<WINPOINT*>::iterator CMapPropertyCountPK::UpperBound(int winpoint)
{
	return (this->*_UpperBound)(winpoint);

	//TODO
}


hook_method<void (CMapPropertyCountPK::*)(void)> CMapPropertyCountPK::_BroadCastRankingInfo(SERVER, "CMapPropertyCountPK::BroadCastRankingInfo");
void CMapPropertyCountPK::BroadCastRankingInfo(void)
{
	return (this->*_BroadCastRankingInfo)();

	//TODO
}


hook_method<void (CMapPropertyCountPK::*)(void)> CMapPropertyCountPK::_ClearWinpoint(SERVER, "CMapPropertyCountPK::ClearWinpoint");
void CMapPropertyCountPK::ClearWinpoint(void)
{
	return (this->*_ClearWinpoint)();

	//TODO
}

