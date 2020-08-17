#pragma once
#include "MakerRankMgr.h" // MAKER_RANKING
#include "shared/ODBC.h"


class CMakerRankDB : public CODBC
{
public:
	CMakerRankDB();
	~CMakerRankDB();

public:
	int UpdateMakerRank(unsigned long GID, char* charname, int type, int point);
	int GetMakerRank(unsigned long GID, int& point, int Type);
	int Get_TOP_MakerRank(int type, MAKER_RANKING* makerRank);
};
