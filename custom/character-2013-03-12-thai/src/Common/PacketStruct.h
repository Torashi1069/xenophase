#pragma once
#pragma pack(push,1)
///////////////////////////////////////


struct ZSERVER_ADDR
{
	/* this+0 */ unsigned long ip;
	/* this+4 */ short port;
};


struct CHARACTER_INFO
{
	/* this+  0 */ unsigned long GID;
	/* this+  4 */ int exp;
	/* this+  8 */ int money;
	/* this+ 12 */ int jobexp;
	/* this+ 16 */ int joblevel;
	/* this+ 20 */ int bodystate;
	/* this+ 24 */ int healthstate;
	/* this+ 28 */ int effectstate;
	/* this+ 32 */ int virtue;
	/* this+ 36 */ int honor;
	/* this+ 40 */ short jobpoint;
	/* this+ 42 */ int hp;
	/* this+ 46 */ int maxhp;
	/* this+ 50 */ short sp;
	/* this+ 52 */ short maxsp;
	/* this+ 54 */ short speed;
	/* this+ 56 */ short job;
	/* this+ 58 */ short head;
	/* this+ 60 */ short weapon;
	/* this+ 62 */ short level;
	/* this+ 64 */ short sppoint;
	/* this+ 66 */ short accessory;
	/* this+ 68 */ short shield;
	/* this+ 70 */ short accessory2;
	/* this+ 72 */ short accessory3;
	/* this+ 74 */ short headpalette;
	/* this+ 76 */ short bodypalette;
	/* this+ 78 */ unsigned char name[24];
	/* this+102 */ unsigned char Str;
	/* this+103 */ unsigned char Agi;
	/* this+104 */ unsigned char Vit;
	/* this+105 */ unsigned char Int;
	/* this+106 */ unsigned char Dex;
	/* this+107 */ unsigned char Luk;
	/* this+108 */ unsigned char CharNum;
	/* this+109 */ unsigned char haircolor;
	/* this+110 */ short bIsChangedCharName;
	/* this+112 */ int nRobe;
};


///////////////////////////////////////
#pragma pack(pop)
