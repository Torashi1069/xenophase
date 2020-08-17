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
	/* this+ 42 */ short hp;
	/* this+ 44 */ short maxhp;
	/* this+ 46 */ short sp;
	/* this+ 48 */ short maxsp;
	/* this+ 50 */ short speed;
	/* this+ 52 */ short job;
	/* this+ 54 */ short head;
	/* this+ 56 */ short weapon;
	/* this+ 58 */ short level;
	/* this+ 60 */ short sppoint;
	/* this+ 62 */ short accessory;
	/* this+ 64 */ short shield;
	/* this+ 66 */ short accessory2;
	/* this+ 68 */ short accessory3;
	/* this+ 70 */ short headpalette;
	/* this+ 72 */ short bodypalette;
	/* this+ 74 */ unsigned char name[24];
	/* this+ 98 */ unsigned char Str;
	/* this+ 99 */ unsigned char Agi;
	/* this+100 */ unsigned char Vit;
	/* this+101 */ unsigned char Int;
	/* this+102 */ unsigned char Dex;
	/* this+103 */ unsigned char Luk;
	/* this+104 */ unsigned char CharNum;
	/* this+105 */ unsigned char haircolor;
};


///////////////////////////////////////
#pragma pack(pop)
