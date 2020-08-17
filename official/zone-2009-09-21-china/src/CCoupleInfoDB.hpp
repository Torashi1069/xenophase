#pragma once
#include "ODBC.h"
#include "struct.hpp"
class CPC;


class CCoupleInfoDB : public CODBC
{
public:
	public: CCoupleInfoDB::CCoupleInfoDB(void);
	public: virtual CCoupleInfoDB::~CCoupleInfoDB(void);
	public: int CCoupleInfoDB::MakeCouple(CPC* male, CPC* female, CoupleInfo& info);
	public: int CCoupleInfoDB::DeleteCouple(CPC* pc, int type);
	public: int CCoupleInfoDB::GetCoupleInfo(CPC* pc, int type, CoupleInfo& info);

private:
	static hook_method<int (CCoupleInfoDB::*)(CPC* male, CPC* female, CoupleInfo& info)> CCoupleInfoDB::_MakeCouple;
	static hook_method<int (CCoupleInfoDB::*)(CPC* pc, int type)> CCoupleInfoDB::_DeleteCouple;
	static hook_method<int (CCoupleInfoDB::*)(CPC* pc, int type, CoupleInfo& info)> CCoupleInfoDB::_GetCoupleInfo;
};
