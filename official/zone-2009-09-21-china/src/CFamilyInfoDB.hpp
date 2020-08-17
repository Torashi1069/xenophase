#pragma once
#include "ODBC.h"
#include "struct.hpp"
class CPC;


class CFamilyInfoDB : public CODBC
{
public:
	public: CFamilyInfoDB::CFamilyInfoDB(void);
	public: virtual CFamilyInfoDB::~CFamilyInfoDB(void);
	public: int CFamilyInfoDB::MakeFamily(unsigned long father, unsigned long mother, unsigned long baby, FamilyInfo& info);
	public: int CFamilyInfoDB::MakeFamily(CPC* father, CPC* mother, CPC* baby, FamilyInfo& info);
	public: int CFamilyInfoDB::GetFamilyInfo(CPC* pc, int type, FamilyInfo& info);
	public: int CFamilyInfoDB::GetFamilyByFather(unsigned long GID, FamilyInfo& info);
	public: int CFamilyInfoDB::GetFamilyByMother(unsigned long GID, FamilyInfo& info);
	public: int CFamilyInfoDB::GetFamilyByBaby(unsigned long GID, FamilyInfo& info);
	public: int CFamilyInfoDB::DeleteFamily(CPC* pc, int type);

private:
	static hook_method<int (CFamilyInfoDB::*)(unsigned long father, unsigned long mother, unsigned long baby, FamilyInfo& info)> CFamilyInfoDB::_MakeFamily;
	static hook_method<int (CFamilyInfoDB::*)(CPC* father, CPC* mother, CPC* baby, FamilyInfo& info)> CFamilyInfoDB::_MakeFamily2;
	static hook_method<int (CFamilyInfoDB::*)(CPC* pc, int type, FamilyInfo& info)> CFamilyInfoDB::_GetFamilyInfo;
	static hook_method<int (CFamilyInfoDB::*)(unsigned long GID, FamilyInfo& info)> CFamilyInfoDB::_GetFamilyByFather;
	static hook_method<int (CFamilyInfoDB::*)(unsigned long GID, FamilyInfo& info)> CFamilyInfoDB::_GetFamilyByMother;
	static hook_method<int (CFamilyInfoDB::*)(unsigned long GID, FamilyInfo& info)> CFamilyInfoDB::_GetFamilyByBaby;
	static hook_method<int (CFamilyInfoDB::*)(CPC* pc, int type)> CFamilyInfoDB::_DeleteFamily;
};
