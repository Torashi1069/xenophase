#include "CFamilyInfoDB.hpp"


CFamilyInfoDB::CFamilyInfoDB(void)
{
}


CFamilyInfoDB::~CFamilyInfoDB(void)
{
}


hook_method<int (CFamilyInfoDB::*)(unsigned long father, unsigned long mother, unsigned long baby, FamilyInfo& info)> CFamilyInfoDB::_MakeFamily(SERVER, "?MakeFamily@CFamilyInfoDB@@QAEHKKKAAUFamilyInfo@@@Z");
int CFamilyInfoDB::MakeFamily(unsigned long father, unsigned long mother, unsigned long baby, FamilyInfo& info)
{
	return (this->*_MakeFamily)(father, mother, baby, info);

	//TODO
}


/* hook_method<int (CFamilyInfoDB::*)(CPC* father, CPC* mother, CPC* baby, FamilyInfo& info)> CFamilyInfoDB::_MakeFamily2(SERVER, "?MakeFamily@CFamilyInfoDB@@QAEHPAVCPC@@00AAUFamilyInfo@@@Z");
int CFamilyInfoDB::MakeFamily(CPC* father, CPC* mother, CPC* baby, FamilyInfo& info)
{
	return (this->*_MakeFamily2)(father, mother, baby, info);

	//TODO
} */


hook_method<int (CFamilyInfoDB::*)(CPC* pc, int type, FamilyInfo& info)> CFamilyInfoDB::_GetFamilyInfo(SERVER, "CFamilyInfoDB::GetFamilyInfo");
int CFamilyInfoDB::GetFamilyInfo(CPC* pc, int type, FamilyInfo& info)
{
	return (this->*_GetFamilyInfo)(pc, type, info);

	//TODO
}


hook_method<int (CFamilyInfoDB::*)(unsigned long GID, FamilyInfo& info)> CFamilyInfoDB::_GetFamilyByFather(SERVER, "CFamilyInfoDB::GetFamilyByFather");
int CFamilyInfoDB::GetFamilyByFather(unsigned long GID, FamilyInfo& info)
{
	return (this->*_GetFamilyByFather)(GID, info);

	//TODO
}


hook_method<int (CFamilyInfoDB::*)(unsigned long GID, FamilyInfo& info)> CFamilyInfoDB::_GetFamilyByMother(SERVER, "CFamilyInfoDB::GetFamilyByMother");
int CFamilyInfoDB::GetFamilyByMother(unsigned long GID, FamilyInfo& info)
{
	return (this->*_GetFamilyByMother)(GID, info);

	//TODO
}


hook_method<int (CFamilyInfoDB::*)(unsigned long GID, FamilyInfo& info)> CFamilyInfoDB::_GetFamilyByBaby(SERVER, "CFamilyInfoDB::GetFamilyByBaby");
int CFamilyInfoDB::GetFamilyByBaby(unsigned long GID, FamilyInfo& info)
{
	return (this->*_GetFamilyByBaby)(GID, info);

	//TODO
}


/* hook_method<int (CFamilyInfoDB::*)(CPC* pc, int type)> CFamilyInfoDB::_DeleteFamily(SERVER, "CFamilyInfoDB::DeleteFamily");
int CFamilyInfoDB::DeleteFamily(CPC* pc, int type)
{
	return (this->*_DeleteFamily)(pc, type);

	//TODO
} */
