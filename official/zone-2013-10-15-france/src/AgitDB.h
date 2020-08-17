#pragma once
#include "shared/ODBC.h"


struct AGIT_DBINFO
{
	/* this+ 0 */ char mapName[16];
	/* this+16 */ char agitName[24];
	/* this+40 */ int guildID;
	/* this+44 */ int economy;
	/* this+48 */ int defense;
	/* this+52 */ int triggerE;
	/* this+56 */ int triggerD;
	/* this+60 */ time_t nextTime;
	/* this+64 */ time_t payTime;
	/* this+68 */ time_t createTime;
	/* this+72 */ unsigned char visibleC;
	/* this+73 */ unsigned char visibleG[8];
};


class CAgitDB : public CODBC
{
public:
	CAgitDB();
	virtual ~CAgitDB();

public:
	int Update(const char* mapName, AGIT_DBINFO* pInfo);
	int Get(std::vector<AGIT_DBINFO*>& vt);
};
