#include "CMakerRankMgr.hpp"


hook_method<void (CMakerRankMgr::*)(int type)> CMakerRankMgr::_ResetMakerRankList(SERVER, "CMakerRankMgr::ResetMakerRankList");
void CMakerRankMgr::ResetMakerRankList(int type)
{
	return (this->*_ResetMakerRankList)(type);

	//TODO
}


/* hook_method<void (CMakerRankMgr::*)(int type)> CMakerRankMgr::_SortMakerRankList(SERVER, "CMakerRankMgr::SortMakerRankList");
void CMakerRankMgr::SortMakerRankList(int type)
{
	return (this->*_SortMakerRankList)(type);

	//TODO
} */


/* hook_method<void (CMakerRankMgr::*)(int type)> CMakerRankMgr::_Get_TOP_MakerRank(SERVER, "CMakerRankMgr::Get_TOP_MakerRank");
void CMakerRankMgr::Get_TOP_MakerRank(int type)
{
	return (this->*_Get_TOP_MakerRank)(type);

	//TODO
} */


hook_method<int (CMakerRankMgr::*)(CPC* pc, int type, int value, int& point)> CMakerRankMgr::_UpdateMakerRank(SERVER, "CMakerRankMgr::UpdateMakerRank");
int CMakerRankMgr::UpdateMakerRank(CPC* pc, int type, int value, int& point)
{
	return (this->*_UpdateMakerRank)(pc, type, value, point);

	//TODO
}


hook_method<void (CMakerRankMgr::*)(unsigned long GID, int& point, int JobType)> CMakerRankMgr::_GetMakerRank(SERVER, "CMakerRankMgr::GetMakerRank");
void CMakerRankMgr::GetMakerRank(unsigned long GID, int& point, int JobType)
{
	return (this->*_GetMakerRank)(GID, point, JobType);

	//TODO
}


hook_method<int (CMakerRankMgr::*)(unsigned long GID, int type)> CMakerRankMgr::_GetMakerPower(SERVER, "CMakerRankMgr::GetMakerPower");
int CMakerRankMgr::GetMakerPower(unsigned long GID, int type)
{
	return (this->*_GetMakerPower)(GID, type);

	//TODO
}


hook_method<void (CMakerRankMgr::*)(char* buf)> CMakerRankMgr::_SetMakerRankList(SERVER, "CMakerRankMgr::SetMakerRankList");
void CMakerRankMgr::SetMakerRankList(char* buf)
{
	return (this->*_SetMakerRankList)(buf);

	//TODO
}


hook_method<int (CMakerRankMgr::*)(CPC* pc)> CMakerRankMgr::_GetRankFromTop10(SERVER, "CMakerRankMgr::GetRankFromTop10");
int CMakerRankMgr::GetRankFromTop10(CPC* pc)
{
	return (this->*_GetRankFromTop10)(pc);

	//TODO
}
