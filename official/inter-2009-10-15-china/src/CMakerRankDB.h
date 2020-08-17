#pragma once
#include "ODBC.h"


struct MAKER_RANKING
{
	/* this+ 0 */ unsigned long GID;
	/* this+ 4 */ char charname[24];
	/* this+28 */ int point;
};


class CMakerRankDB : public CODBC
{
	/* this+0 */ public: //CODBC baseclass_0;

	public: int CMakerRankDB::Get_TOP_MakerRank(int type, MAKER_RANKING* makerRank);
	public: CMakerRankDB::CMakerRankDB(void);
	public: virtual CMakerRankDB::~CMakerRankDB(void);

private:
	static hook_method<int (CMakerRankDB::*)(int type, MAKER_RANKING* makerRank)> CMakerRankDB::_Get_TOP_MakerRank;
};
