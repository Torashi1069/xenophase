#pragma once
#include "shared/ODBC.h"


struct MAKER_RANKING
{
	/* this+ 0 */ unsigned long GID;
	/* this+ 4 */ char charname[24];
	/* this+28 */ int point;
};


class CMakerRankDB : public CODBC
{
public:
	int Get_TOP_MakerRank(int type, MAKER_RANKING* makerRank);

public:
	CMakerRankDB();
	virtual ~CMakerRankDB();
};
