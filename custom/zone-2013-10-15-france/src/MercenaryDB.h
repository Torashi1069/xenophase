#pragma once
#include "shared/ODBC.h"


struct HOMUN_DBINFO
{
	/* this+ 0 */ int exp;
	/* this+ 4 */ int bodystate;
	/* this+ 8 */ int healthstate;
	/* this+12 */ int effectstate;
	/* this+16 */ int fullness;
	/* this+20 */ int modified;
	/* this+24 */ float relation;
	/* this+28 */ short clevel;
	/* this+30 */ short job;
	/* this+32 */ short SKPoint;
	/* this+34 */ short hp;
	/* this+36 */ short maxhp;
	/* this+38 */ short sp;
	/* this+40 */ short maxsp;
	/* this+42 */ short accessory;
	/* this+44 */ short property;
	/* this+46 */ char name[24];
	/* this+70 */ unsigned char Str;
	/* this+71 */ unsigned char Agi;
	/* this+72 */ unsigned char Vit;
	/* this+73 */ unsigned char Int;
	/* this+74 */ unsigned char Dex;
	/* this+75 */ unsigned char Luk;
};


class CMerceDB : public CODBC
{
public:
	CMerceDB();
	virtual ~CMerceDB();

public:
	BOOL InsertHomunInfo(int GID, HOMUN_DBINFO* info);
	BOOL SaveHomunInfo(int GID, HOMUN_DBINFO* info);
	void DeleteHomunInfo(int GID);
};
