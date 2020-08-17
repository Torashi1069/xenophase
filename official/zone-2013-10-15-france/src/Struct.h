#pragma once
#pragma pack(push,1)


struct EQUIPSLOTINFO
{
	/* this+0 */ unsigned short info[4];
};


struct REPAIRITEM_INFO
{
	/* this+0 */ short index;
	/* this+2 */ unsigned short ITID;
	/* this+4 */ unsigned char refiningLevel;
	/* this+5 */ EQUIPSLOTINFO slot;
};


struct CommonItemInfo
{
	/* this+ 0 */ unsigned short ITID;
	/* this+ 2 */ int count;
	/* this+ 6 */ unsigned short ServerItemType;
	/* this+ 8 */ unsigned short Type;
	/* this+10 */ bool IsIdentified;
	/* this+11 */ bool IsDamaged;
	/* this+12 */ unsigned char refiningLevel;
	/* this+13 */ EQUIPSLOTINFO slot;
	/* this+21 */ __int64 UniqueSerialNum;
	/* this+29 */ long HireExpireDate;
};


/// @see PACKET_ZC_PC_PURCHASE_ITEMLIST
struct PURCHASE_ITEM
{
	/* this+0 */ int price;
	/* this+4 */ int discountprice;
	/* this+8 */ unsigned char type;
	/* this+9 */ unsigned short ITID;
};


/// @see PACKET_ZC_PC_SELL_ITEMLIST
struct SELL_ITEM
{
	/* this+0 */ short index;
	/* this+2 */ int price;
	/* this+6 */ int overchargeprice;
};


/// @see PACKET_CZ_PC_PURCHASE_ITEMLIST
struct CZ_PURCHASE_ITEM
{
	/* this+0 */ short count;
	/* this+2 */ unsigned short ITID;
};


/// @see PACKET_CZ_PC_SELL_ITEMLIST
struct CZ_SELL_ITEM
{
	/* this+0 */ short index;
	/* this+2 */ short count;
};


/// @see PACKET_ZC_ENTER_ROOM
struct ROOM_MEMBER_DATA
{
	/* this+0 */ unsigned long role;
	/* this+4 */ char name[24];
};


struct CHARINFO_TO_CHARACTERDB
{
	/* this+  0 */ int exp;
	/* this+  4 */ int GuildID;
	/* this+  8 */ int money;
	/* this+ 12 */ int jobexp;
	/* this+ 16 */ int joblevel;
	/* this+ 20 */ int bodystate;
	/* this+ 24 */ int healthstate;
	/* this+ 28 */ int effectstate;
	/* this+ 32 */ int virtue;
	/* this+ 36 */ int honor;
	/* this+ 40 */ int hp;
	/* this+ 44 */ short maxhp;
	/* this+ 46 */ short sp;
	/* this+ 48 */ short maxsp;
	/* this+ 50 */ short xPos;
	/* this+ 52 */ short yPos;
	/* this+ 54 */ short speed;
	/* this+ 56 */ short jobpoint;
	/* this+ 58 */ short sxPos;
	/* this+ 60 */ short syPos;
	/* this+ 62 */ short job;
	/* this+ 64 */ short clevel;
	/* this+ 66 */ short sppoint;
	/* this+ 68 */ short head;
	/* this+ 70 */ short weapon;
	/* this+ 72 */ short accessory;
	/* this+ 74 */ short accessory2;
	/* this+ 76 */ short accessory3;
	/* this+ 78 */ short headpalette;
	/* this+ 80 */ short bodypalette;
	/* this+ 82 */ short cookMastery;
	/* this+ 84 */ char mapname[16];
	/* this+100 */ char restartMapName[16];
	/* this+116 */ unsigned char Str;
	/* this+117 */ unsigned char Agi;
	/* this+118 */ unsigned char Vit;
	/* this+119 */ unsigned char Int;
	/* this+120 */ unsigned char Dex;
	/* this+121 */ unsigned char Luk;
	/* this+122 */ unsigned char haircolor;
	/* this+123 */ struct tagParty { unsigned char Config; } Party;
	/* this+124 */ bool bOpenEquipmentWin;
	/* this+125 */ short font;
	/* this+127 */ char ZenyCheckSum[4];
	/* this+131 */ short robe;
};


struct CHARINFO_FROM_CHARACTERDB
{
	/* this+  0 */ int GID;
	/* this+  4 */ int exp;
	/* this+  8 */ int AID;
	/* this+ 12 */ int GuildID;
	/* this+ 16 */ int money;
	/* this+ 20 */ int jobexp;
	/* this+ 24 */ int joblevel;
	/* this+ 28 */ int bodystate;
	/* this+ 32 */ int healthstate;
	/* this+ 36 */ int effectstate;
	/* this+ 40 */ int virtue;
	/* this+ 44 */ int honor;
	/* this+ 48 */ int hp;
	/* this+ 52 */ short maxhp;
	/* this+ 54 */ short sp;
	/* this+ 56 */ short maxsp;
	/* this+ 58 */ short xPos;
	/* this+ 60 */ short yPos;
	/* this+ 62 */ short speed;
	/* this+ 64 */ short jobpoint;
	/* this+ 66 */ short sxPos;
	/* this+ 68 */ short syPos;
	/* this+ 70 */ short head;
	/* this+ 72 */ short weapon;
	/* this+ 74 */ short accessory;
	/* this+ 76 */ short accessory2;
	/* this+ 78 */ short accessory3;
	/* this+ 80 */ short headpalette;
	/* this+ 82 */ short bodypalette;
	/* this+ 84 */ short cookMastery;
	/* this+ 86 */ char name[24];
	/* this+110 */ char mapname[16];
	/* this+126 */ char restartMapName[16];
	/* this+142 */ short job;
	/* this+144 */ short clevel;
	/* this+146 */ short sppoint;
	/* this+148 */ char Str;
	/* this+149 */ char Agi;
	/* this+150 */ char Vit;
	/* this+151 */ char Int;
	/* this+152 */ char Dex;
	/* this+153 */ char Luk;
	/* this+154 */ char CharNum;
	/* this+155 */ unsigned char haircolor;
	/* this+156 */ struct tagParty { unsigned char Config; } Party;
	/* this+157 */ bool bOpenEquipmentWin;
	/* this+158 */ short font;
	/* this+160 */ char ZenyCheckSum[4];
	/* this+164 */ short robe;
};


struct SKILLINFO
{
	/* this+ 0 */ unsigned short SKID;
	/* this+ 2 */ int type;
	/* this+ 6 */ short level;
	/* this+ 8 */ short spcost;
	/* this+10 */ short attackRange;
	/* this+12 */ char skillName[24];
	/* this+36 */ bool upgradable;
};


struct ENEMY_INFO
{
	/* this+0 */ unsigned long AID;
	/* this+4 */ unsigned long attackinglastTime;
};


struct PosInfo
{
	/* this+0 */ int x;
	/* this+4 */ int y;
	/* this+8 */ int isCheckPos;
};


struct MSG_TYPE_SKILLDATA
{
	/* this+ 0 */ int SKID;
	/* this+ 4 */ int skLevel;
	/* this+ 8 */ int spCost;
	/* this+12 */ int xPos;
	/* this+16 */ int yPos;
//	MSG_TYPE_SKILLDATA(); //TODO
};


struct SORTED_PCLIST
{
	/* this+0 */ unsigned long AID;
	/* this+4 */ unsigned int limitTime;
	/* this+8 */ unsigned int val;
};


struct tagShortCutKey
{
	/* this+0 */ char isSkill;
	/* this+1 */ unsigned long ID;
	/* this+5 */ short count;
};


struct MSG_TYPE1_TWODWORD
{
	/* this+0 */ int data1;
	/* this+4 */ int data2;
};


struct MSG_TYPE2_THREEDWORD
{
	/* this+0 */ int data1;
	/* this+4 */ int data2;
	/* this+8 */ int data3;
};


struct MSG_TYPE3_FOURDWORD
{
	/* this+ 0 */ int data1;
	/* this+ 4 */ int data2;
	/* this+ 8 */ int data3;
	/* this+12 */ int data4;
};


struct MSG_TYPE4_FIVEDWORD
{
	/* this+ 0 */ int data1;
	/* this+ 4 */ int data2;
	/* this+ 8 */ int data3;
	/* this+12 */ int data4;
	/* this+16 */ int data5;
};


struct MSG_TYPE5_SIXDWORD
{
	/* this+ 0 */ int data1;
	/* this+ 4 */ int data2;
	/* this+ 8 */ int data3;
	/* this+12 */ int data4;
	/* this+16 */ int data5;
	/* this+20 */ int data6;
};


#pragma pack(pop)
