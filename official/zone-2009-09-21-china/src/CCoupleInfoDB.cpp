#include "CCoupleInfoDB.hpp"


CCoupleInfoDB::CCoupleInfoDB(void)
{
}


CCoupleInfoDB::~CCoupleInfoDB(void)
{
}


hook_method<int (CCoupleInfoDB::*)(CPC* male, CPC* female, CoupleInfo& info)> CCoupleInfoDB::_MakeCouple(SERVER, "CCoupleInfoDB::MakeCouple");
int CCoupleInfoDB::MakeCouple(CPC* male, CPC* female, CoupleInfo& info)
{
	return (this->*_MakeCouple)(male, female, info);

	//TODO
}


hook_method<int (CCoupleInfoDB::*)(CPC* pc, int type)> CCoupleInfoDB::_DeleteCouple(SERVER, "CCoupleInfoDB::DeleteCouple");
int CCoupleInfoDB::DeleteCouple(CPC* pc, int type)
{
	return (this->*_DeleteCouple)(pc, type);

	//TODO
}


hook_method<int (CCoupleInfoDB::*)(CPC* pc, int type, CoupleInfo& info)> CCoupleInfoDB::_GetCoupleInfo(SERVER, "CCoupleInfoDB::GetCoupleInfo");
int CCoupleInfoDB::GetCoupleInfo(CPC* pc, int type, CoupleInfo& info)
{
	return (this->*_GetCoupleInfo)(pc, type, info);

	//TODO
}
