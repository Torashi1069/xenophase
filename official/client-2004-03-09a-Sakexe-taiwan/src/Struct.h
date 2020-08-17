#pragma once
#include "Enum.h"
#include "granny.h"
class CTexture;


struct CHAT_PROHIBIT_LOG
{
	/* this+ 0 */ unsigned long AID;
	/* this+ 4 */ unsigned long GID;
	/* this+ 8 */ unsigned long prohibitTime;
	/* this+12 */ unsigned long logDate;
	/* this+16 */ unsigned long logTime;
	/* this+20 */ char accountName[32];
	/* this+52 */ char charName[32];
	/* this+84 */ char serverName[32];
};


struct REQ_ACCOUNT_AID
{
	/* this+0 */ unsigned long AID;
	/* this+4 */ mystd::string accountName;
};


struct REQ_ACCOUNTNAME_INFO
{
	/* this+0 */ unsigned long AID;
	/* this+4 */ unsigned long reqTime;
};


struct FORCE_ANIM_TICK
{
	/* this+0 */ unsigned long AID;
	/* this+4 */ unsigned long tick;
};


struct FRIEND_INFO
{
	/* this+ 0 */ BOOL isValid;
	/* this+ 4 */ unsigned long AID;
	/* this+ 8 */ mystd::string characterName;
	/* this+24 */ mystd::string mapName;
	/* this+40 */ int role;
	/* this+44 */ int state;
	/* this+48 */ COLORREF color;

	FRIEND_INFO()
	{
	}

	FRIEND_INFO(BOOL isValid)
	{
		this->isValid = isValid;
	}
};


struct Registry
{
	/* this+0x0  */ GUID guidDevice;
	/* this+0x10 */ GUID guidDriver;
	/* this+0x20 */ char deviceName[40];
	/* this+0x48 */ unsigned long isFullScreenMode;
	/* this+0x4C */ unsigned long isLowResSprite;
	/* this+0x50 */ unsigned long useCompressedTexture;
	/* this+0x54 */ unsigned long isFogRender;
	/* this+0x58 */ unsigned long Width;
	/* this+0x5C */ unsigned long Height;
	/* this+0x60 */ unsigned long bitPerPixel;
	/* this+0x64 */ unsigned long deviceCnt;
	/* this+0x68 */ unsigned long modeCnt;
	/* this+0x6C */ unsigned long frameSkip;
	/* this+0x70 */ unsigned long filtering;
	/* this+0x74 */ unsigned long m_bUse3dSound;
	/* this+0x78 */ unsigned long m_soundOutPut;
	/* this+0x7C */ unsigned long m_soundDriver;
};


struct Registry2
{
	/* this+0x0  */ GUID m_guidDevice;
	/* this+0x10 */ GUID m_guidDriver;
	/* this+0x20 */ char m_deviceName[40];
	/* this+0x48 */ unsigned long m_isFullScreenMode;
	/* this+0x4C */ unsigned long m_width;
	/* this+0x50 */ unsigned long m_height;
	/* this+0x54 */ unsigned long m_bitPerPixel;
	/* this+0x58 */ unsigned long m_deviceCnt;
	/* this+0x5C */ unsigned long m_modeCnt;
	/* this+0x60 */ unsigned long m_isVoodoo;
	/* this+0x64 */ unsigned long m_spriteMode;
	/* this+0x68 */ unsigned long m_textureMode;
	/* this+0x6C */ unsigned long m_trilinearFilter;
	/* this+0x70 */ int m_soundMode;
	/* this+0x74 */ int m_speakerType;
	/* this+0x78 */ int m_digitalrateType;
	/* this+0x7C */ int m_numSampleType;
	/* this+0x80 */ int m_digitalbitsType;
	/* this+0x84 */ int m_useWaveout;
	/* this+0x88 */ char m_providerName[1024];
};


struct BOXINFO
{
	/* this+0x0  */ int x;
	/* this+0x4  */ int y;
	/* this+0x8  */ int cx;
	/* this+0xC  */ int cy;
	/* this+0x10 */ int drawEdge;
	/* this+0x14 */ int color;
	/* this+0x18 */ int color2;
};


struct DRAG_INFO
{
	/* this+ 0 */ enum ENUM_DRAGTYPE m_dragType;
	/* this+ 4 */ int m_dragItemIndex;
	/* this+ 8 */ int m_dragItemPrice;
	/* this+12 */ int m_dragItemRealPrice;
	/* this+16 */ int m_numDragItem;
	/* this+20 */ int m_slotNum;
	/* this+24 */ int m_dragItemType;
	/* this+28 */ int m_refiningLevel;
	/* this+32 */ bool m_isIdentified;
	/* this+36 */ mystd::string m_dragSprName;
	/* this+52 */ mystd::string m_dragItemName;
	/* this+68 */ mystd::string m_skillName;
	/* this+84 */ int m_skillUseLevel;
	/* this+88 */ int m_slot[4];
};


struct GrannyTexture
{
	/* this+0x0 */ const char* Name;
	/* this+0x4 */ CTexture* tex;
};


struct GrannyMesh
{
	/* this+0x0  */ granny_mesh* Mesh;
	/* this+0x4  */ granny_mesh_binding* Binding;
	/* this+0x8  */ granny_mesh_deformer* Deformer;
	/* this+0xC  */ unsigned short* VerIdx;
	/* this+0x10 */ unsigned char* Vertices;
	/* this+0x14 */ int TextureCount;
	/* this+0x18 */ GrannyTexture** TextureReferences;
};


struct GrannyModel
{
	/* this+0x0 */ granny_model_instance* GrannyInstance;
	/* this+0x4 */ granny_world_pose* WorldPose;
	/* this+0x8 */ int MeshCount;
	/* this+0xC */ GrannyMesh* Meshes;
};


struct GrannyScene
{
	/* this+0x0   */ granny_camera Camera;
	/* this+0x14C */ granny_file* LoadedFile;
	/* this+0x150 */ int TextureCount;
	/* this+0x154 */ GrannyTexture* Textures;
	/* this+0x158 */ int ModelCount;
	/* this+0x15C */ GrannyModel* Model;
	/* this+0x160 */ int MaxBoneCount;
	/* this+0x164 */ granny_local_pose* SharedLocalPose;
	/* this+0x168 */ int MaxMutableVertexBufferSize;
	/* this+0x16C */ int MaxMutableVertexBufferCount;
	/* this+0x170 */ int MutableVertexBufferIndex;
	/* this+0x174 */ granny_pnt332_vertex* MatVer;
	/* this+0x178 */ char BaseFileName[260];
};


struct SERVER_ADDR
{
	/* this+ 0 */ unsigned long ip;
	/* this+ 4 */ short port;
	/* this+ 6 */ unsigned char name[20];
	/* this+26 */ WORD usercount;
	/* this+28 */ WORD state; // enum SERVERSTATE
	/* this+30 */ WORD property; // enum SERVERPROPERTY
};


#pragma pack(push,1)
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
#pragma pack(pop)


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


struct accountInfo
{
	/* this+0x0  */ mystd::string display;
	/* this+0x10 */ mystd::string desc;
	/* this+0x20 */ mystd::string address;
	/* this+0x30 */ mystd::string port;
	/* this+0x40 */ int type;
	/* this+0x44 */ unsigned long version;
};


struct NamePair
{
	/* this+0x0  */ mystd::string cName;
	/* this+0x10 */ mystd::string pName;
	/* this+0x20 */ mystd::string gName;
	/* this+0x30 */ mystd::string rName;

	public: void NamePair::Clear(void)
	{
		this->cName.erase();
		this->pName.erase();
		this->gName.erase();
		this->rName.erase();
	}

	//public: unsigned char IsEmpty();
};


struct CellPos
{
	/* this+0x0 */ int x;
	/* this+0x4 */ int y;
};


struct ColorCellPos
{
	/* this+0x0 */ int x;
	/* this+0x4 */ int y;
	/* this+0x8 */ unsigned long color;
};


struct ColorCellPos2
{
	/* this+0x0  */ int x;
	/* this+0x4  */ int y;
	/* this+0x8  */ int type;
	/* this+0xC  */ unsigned long color;
	/* this+0x10 */ unsigned long startTime;
};


struct PLAY_WAVE_INFO
{
	/* this+0x0  */ mystd::string wavName;
	/* this+0x10 */ unsigned long nAID;
	/* this+0x14 */ unsigned long term;
	/* this+0x18 */ unsigned long endTick;
};


struct ChatRoomInfo
{
	/* this+0x0  */ mystd::string title;
	/* this+0x10 */ mystd::string pass;
	/* this+0x20 */ int roomType;
	/* this+0x24 */ int numPeople;
	/* this+0x28 */ int maxNumPeople;
	/* this+0x2C */ int roomId;
};


struct SKILL_USE_INFO
{
	/* this+0x0 */ enum ENUM_SKILL_USE_TYPE m_skillUseType;
	/* this+0x4 */ int m_skillId;
	/* this+0x8 */ int m_attackRange;
	/* this+0xC */ int m_useLevel;
};


struct SHOW_IMAGE_INFO
{
	/* this+0x0 */ int type;
	/* this+0x4 */ mystd::string imageName;
};


struct GUILD_POSITION_INFORMATION
{
	/* this+0x0  */ int ranking;
	/* this+0x4  */ int positionID;
	/* this+0x8  */ mystd::string posName;
	/* this+0x18 */ int rightOfJoin;
	/* this+0x1C */ int rightOfPunish;
	/* this+0x20 */ int payRate;
};


struct GUILD_MEMBER_INFORMATION
{
	/* this+0x0  */ unsigned long AID;
	/* this+0x4  */ unsigned long GID;
	/* this+0x8  */ mystd::string CharName;
	/* this+0x18 */ int HeadType;
	/* this+0x1C */ int HeadPalette;
	/* this+0x20 */ int Job;
	/* this+0x24 */ int Sex;
	/* this+0x28 */ int GPositionID;
	/* this+0x2C */ mystd::string GPositionName;
	/* this+0x3C */ int Level;
	/* this+0x40 */ mystd::string Memo;
	/* this+0x50 */ float Service;
	/* this+0x54 */ int MemberExp;
	/* this+0x58 */ int CurrentState;
};


struct RELATED_GUILD_INFORMATION
{
	/* this+0x0 */ int GDID;
	/* this+0x4 */ int relation; // enum RELATED_GUILD_TYPE
	/* this+0x8 */ mystd::string GuildName;
};


struct SGUILD_BANISH_INFO
{
	/* this+0x0  */ mystd::string MemberName;
	/* this+0x10 */ mystd::string MemberAccount;
	/* this+0x20 */ mystd::string Reason;
};


struct SGUILD_INFO
{
	/* this+0x0  */ int GDID;
	/* this+0x4  */ mystd::string GuildName;
	/* this+0x14 */ int Level;
	/* this+0x18 */ int UserNum;
	/* this+0x1C */ int MaxUserNum;
	/* this+0x20 */ int Ranking;
};


struct MEMBER_POSITION_INFORMATION
{
	/* this+0 */ int AID;
	/* this+4 */ int GID;
	/* this+8 */ int positionID;
};


struct StringAndColor
{
	/* this+0x0  */ mystd::string String;
	/* this+0x10 */ unsigned long Color;
};


struct COLOR
{
	union
	{
	struct
	{
	/* this+0x0 */ unsigned char b;
	/* this+0x1 */ unsigned char g;
	/* this+0x2 */ unsigned char r;
	/* this+0x3 */ unsigned char a;
	};
	/* this+0x0 */ unsigned long color;
	};
};


struct texCoor
{
	/* this+0x0 */ float u;
	/* this+0x4 */ float v;

	public: void Set(float u, float v)
	{
		this->u = u;
		this->v = v;
	}
};


struct ACTOR_COLOR
{
	/* this+0x0 */ unsigned char a;
	/* this+0x1 */ unsigned char r;
	/* this+0x2 */ unsigned char g;
	/* this+0x3 */ unsigned char b;
};


struct EQUIPSLOTINFO
{
	/* this+0 */ unsigned short info[4];
};


struct StringId
{
	/* this+ 0 */ mystd::string itemName;
	/* this+16 */ int id;

	public: StringId::StringId(void)
	{
	}

	public: StringId::StringId(const char* itemName, int id)
	{
		this->itemName = itemName;
		this->id = id;
	}
};


/// @see STANDENTRYSTRUCT::state
enum PCSTATE
{
	PCSTATE_STAND = 0,
	PCSTATE_DEAD  = 1,
	PCSTATE_SIT   = 2,
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
	/* this+ 48 */ int state; // enum PCSTATE
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

	//public: void STANDENTRYSTRUCT();
};


struct MOVEENTRYSTRUCT
{
	/* this+  0 */ unsigned long GID;
	/* this+  4 */ int job;
	/* this+  8 */ int sex;
	/* this+ 12 */ unsigned long moveStartTime;
	/* this+ 16 */ int sx;
	/* this+ 20 */ int sy;
	/* this+ 24 */ int cellX;
	/* this+ 28 */ int cellY;
	/* this+ 32 */ int dx;
	/* this+ 36 */ int dy;
	/* this+ 40 */ unsigned long speed;
	/* this+ 44 */ int head;
	/* this+ 48 */ int weapon;
	/* this+ 52 */ int accessory;
	/* this+ 56 */ unsigned long bodyState;
	/* this+ 60 */ unsigned long healthState;
	/* this+ 64 */ int effectState;
	/* this+ 68 */ int isPKModeON;
	/* this+ 72 */ int shield;
	/* this+ 76 */ int accessory2;
	/* this+ 80 */ int accessory3;
	/* this+ 84 */ int headpalette;
	/* this+ 88 */ int bodypalette;
	/* this+ 92 */ int headDir;
	/* this+ 96 */ unsigned long guildId;
	/* this+100 */ int guildEmblemVersion;
	/* this+104 */ int honor;
	/* this+108 */ int virtue;
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


struct ITEMSTANDENTRYSTRUCT
{
	/* this+ 0 */ char name[32];
	/* this+32 */ unsigned long ITAID;
	/* this+36 */ int x;
	/* this+40 */ int y;
	/* this+44 */ int subX;
	/* this+48 */ int subY;
	/* this+52 */ int isJumpEntry;
	/* this+56 */ int count;
	/* this+60 */ unsigned char isIdentified;
};


struct SHOP_ITEM
{
	/* this+ 0 */ int index;
	/* this+ 4 */ int price;
	/* this+ 8 */ int realPrice;
	/* this+12 */ int type;
	/* this+16 */ bool isIdentified;
	/* this+17 */ char itemName[32+1];
};


struct SKILLSTRUCT
{
	/* this+ 0 */ unsigned long skillId;
	/* this+ 4 */ unsigned long damage;
	/* this+ 8 */ unsigned long action;
	/* this+12 */ unsigned long targetGID;
	/* this+16 */ unsigned long startTime;
	/* this+20 */ int level;
	/* this+24 */ int count;
	/* this+28 */ int tCellX;
	/* this+32 */ int tCellY;
	/* this+36 */ int attackMT;
	/* this+40 */ int attackedMT;
};


struct SKILLSTANDENTRYSTRUCT
{
	/* this+ 0 */ unsigned long AID;
	/* this+ 4 */ unsigned long creatorAID;
	/* this+ 8 */ int job;
	/* this+12 */ int xPos;
	/* this+16 */ int yPos;
	/* this+20 */ bool isVisible;
};


struct UVRECT
{
	/* this+ 0 */ float u1;
	/* this+ 4 */ float v1;
	/* this+ 8 */ float u2;
	/* this+12 */ float v2;

	public: UVRECT(void)
	{
	}

	public: UVRECT(float u1, float v1, float u2, float v2)
	{
		this->u1 = u1;
		this->v1 = v1;
		this->u2 = u2;
		this->v2 = v2;
	}
};


struct viewSprite
{
	/* this+  0 */ int x;
	/* this+  4 */ int y;
	/* this+  8 */ mystd::string actName[5];
	/* this+ 88 */ mystd::string sprName[5];
	/* this+168 */ mystd::string imfName;
	/* this+184 */ int headPalette;
	/* this+188 */ int bodyPalette;
	/* this+192 */ mystd::string headPaletteName;
	/* this+208 */ mystd::string bodyPaletteName;
	/* this+224 */ int baseAction;
	/* this+228 */ int curAction;
	/* this+232 */ int curMotion;
};


struct GroundAttrPosInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int isRendered;
	/* this+12 */ unsigned long cellColor;

	public: GroundAttrPosInfo(void)
	{
		this->x = 0;
		this->y = 0;
		this->isRendered = 1;
		this->cellColor = 0xAA55FFFF;
	}
};


struct CONTACTNPC
{
	/* this+0 */ unsigned long nid;
	/* this+4 */ int job;
	/* this+8 */ int type;
};


struct GROUNDSKILLSTRUCT
{
	/* this+ 0 */ unsigned long skillId;
	/* this+ 4 */ unsigned long startTime;
	/* this+ 8 */ int cellX;
	/* this+12 */ int cellY;
	/* this+16 */ int level;
};
