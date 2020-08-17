#pragma once
#include "std/string"


struct CellPos
{
	/* this+0 */ int x;
	/* this+4 */ int y;
};


struct NamePair
{
	/* this+ 0 */ mystd::string cName;
	/* this+16 */ mystd::string pName;
	/* this+32 */ mystd::string gName;
	/* this+48 */ mystd::string rName;

	public: void NamePair::Clear(void)
	{
		this->cName.erase();
		this->pName.erase();
		this->gName.erase();
		this->rName.erase();
	}

	//public: unsigned char IsEmpty();
	//public: void NamePair::NamePair();
	//public: void NamePair::~NamePair();
};


struct StringAndColor
{
	/* this+ 0 */ mystd::string String;
	/* this+16 */ COLORREF Color;
};


struct Registry2
{
	/* this+  0 */ GUID m_guidDevice;
	/* this+ 16 */ GUID m_guidDriver;
	/* this+ 32 */ char m_deviceName[40];
	/* this+ 72 */ unsigned long m_isFullScreenMode;
	/* this+ 76 */ unsigned long m_width;
	/* this+ 80 */ unsigned long m_height;
	/* this+ 84 */ unsigned long m_bitPerPixel;
	/* this+ 88 */ unsigned long m_deviceCnt;
	/* this+ 92 */ unsigned long m_modeCnt;
	/* this+ 96 */ unsigned long m_isVoodoo;
	/* this+100 */ unsigned long m_spriteMode;
	/* this+104 */ unsigned long m_textureMode;
	/* this+108 */ unsigned long m_trilinearFilter;
	/* this+112 */ int m_soundMode;
	/* this+116 */ int m_speakerType;
	/* this+120 */ int m_digitalrateType;
	/* this+124 */ int m_numSampleType;
	/* this+128 */ int m_digitalbitsType;
	/* this+132 */ int m_useWaveout;
	/* this+136 */ char m_providerName[1024];
};


struct COLOR
{
	union
	{
	struct
	{
	/* this+0 */ unsigned char b;
	/* this+1 */ unsigned char g;
	/* this+2 */ unsigned char r;
	/* this+3 */ unsigned char a;
	};
	/* this+0 */ unsigned long color;
	};
};


struct BOXINFO
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int cx;
	/* this+12 */ int cy;
	/* this+16 */ int drawEdge;
	/* this+20 */ int color;
	/* this+24 */ int color2;
};


#pragma pack(push,1)
struct BILLING_INFO
{
	/* this+ 0 */ char dummy1;
	/* this+ 1 */ unsigned long code;
	/* this+ 5 */ unsigned long time1;
	/* this+ 9 */ unsigned long time2;
	/* this+13 */ char dummy2[7];
};
#pragma pack(pop)


struct SERVER_ADDR
{
	/* this+ 0 */ unsigned long ip;
	/* this+ 4 */ short port;
	/* this+ 6 */ unsigned char name[20];
	/* this+26 */ unsigned short usercount;
	/* this+28 */ unsigned short state;
	/* this+30 */ unsigned short property;
};


struct ZSERVER_ADDR
{
	/* this+0 */ unsigned long ip;
	/* this+4 */ short port;
};


struct CHARACTER_INFO
{
	/* this+  0 */ BYTE _dummy1[78];
	/* this+ 78 */ char name[24];
	/* this+102 */ BYTE _dummy2[6];
	/* this+108 */ unsigned char CharNum;
	/* this+109 */ BYTE _dummy3[3];
};


struct FRIEND_INFO
{
	/* this+ 0 */ BOOL isValid;
	/* this+ 4 */ int AID;
	/* this+ 8 */ int GID;
	/* this+12 */ mystd::string characterName;
	/* this+28 */ mystd::string mapName;
	/* this+44 */ int role;
	/* this+48 */ int state;
	/* this+52 */ COLORREF color;

	FRIEND_INFO()
	{
	}

	FRIEND_INFO(BOOL isValid)
	{
		this->isValid = isValid;
	}
};


struct TAG_CHARACTER_BLOCK_INFO
{
	/* this+0 */ unsigned int GID;
	/* this+4 */ char szExpireDate[20];
};


struct SKILL_USE_INFO
{
	/* this+ 0 */ enum ENUM_SKILL_USE_TYPE m_skillUseType;
	/* this+ 4 */ int m_skillId;
	/* this+ 8 */ int m_attackRange;
	/* this+12 */ int m_useLevel;
};


struct accountInfo
{
	/* this+ 0 */ mystd::string display;
	/* this+16 */ mystd::string desc;
	/* this+32 */ mystd::string balloon;
	/* this+48 */ mystd::string address;
	/* this+64 */ mystd::string port;
	/* this+80 */ int type;
	/* this+84 */ unsigned int version;
};


struct EQUIPSLOTINFO
{
	/* this+0 */ unsigned short info[4];
};


struct STANDENTRYSTRUCT
{
	/* this+  0 */ unsigned long GID;
	/* this+  4 */ int job;
	/* this+  8 */ int sex;
	/* this+ 12 */ int x;
	/* this+ 16 */ int y;
	/* this+ 20 */ int dir;
	/* this+ 24 */ unsigned long speed;
	/* this+ 28 */ int xSize;
	/* this+ 32 */ int ySize;
	/* this+ 36 */ int head;
	/* this+ 40 */ int weapon;
	/* this+ 44 */ int accessory;
	/* this+ 48 */ int state;
	/* this+ 52 */ unsigned long bodyState;
	/* this+ 56 */ unsigned long healthState;
	/* this+ 60 */ unsigned long effectState;
	/* this+ 64 */ int isPKModeON;
	/* this+ 68 */ int shield;
	/* this+ 72 */ int accessory2;
	/* this+ 76 */ int accessory3;
	/* this+ 80 */ int headpalette;
	/* this+ 84 */ int bodypalette;
	/* this+ 88 */ int headDir;
	/* this+ 92 */ unsigned long guildId;
	/* this+ 96 */ int guildEmblemVersion;
	/* this+100 */ int honor;
	/* this+104 */ int virtue;

	STANDENTRYSTRUCT()
	{
	//	GID = 0; // uninitialized
		job = 0;
		sex = 0;
		x = 0;
		y = 0;
		dir = 0;
		speed = 0;
		xSize = 0;
		ySize = 0;
	//	head = 0; // uninitialized
		weapon = 0;
		accessory = 0;
		state = 0;
		bodyState = 0;
		healthState = 0;
		effectState = 0;
		isPKModeON = 0;
		shield = 0;
		accessory2 = 0;
		accessory3 = 0;
		headpalette = 0;
		bodypalette = 0;
		headDir = 0;
		guildId = 0;
		guildEmblemVersion = 0;
		honor = 0;
		virtue = 0;
	}
};


struct ITEMSTANDENTRYSTRUCT
{
	/* this+ 0 */ char name[32];
	/* this+32 */ unsigned long ITAID;
	/* this+36 */ int x;
	/* this+40 */ int y;
	/* this+44 */ int subX;
	/* this+48 */ int subY;
	/* this+52 */ BOOL isJumpEntry;
	/* this+56 */ int count;
	/* this+60 */ bool isIdentified;
};
C_ASSERT( sizeof ITEMSTANDENTRYSTRUCT == 64 );


struct ACTSTRUCT
{
	/* this+ 0 */ unsigned long damage;
	/* this+ 4 */ unsigned long leftDamage;
	/* this+ 8 */ unsigned long action;
	/* this+12 */ unsigned long targetGID;
	/* this+16 */ unsigned long startTime;
	/* this+20 */ int count;
	/* this+24 */ int tCellX;
	/* this+28 */ int tCellY;
	/* this+32 */ int attackMT;
	/* this+36 */ int attackedMT;
};


struct MOVESTRUCT
{
	/* this+ 0 */ unsigned long startTime;
	/* this+ 4 */ int sx;
	/* this+ 8 */ int sy;
	/* this+12 */ int cellX;
	/* this+16 */ int cellY;
	/* this+20 */ int dx;
	/* this+24 */ int dy;
};
