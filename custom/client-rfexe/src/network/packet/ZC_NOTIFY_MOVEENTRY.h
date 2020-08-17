struct PROTO_ZC_NOTIFY_MOVEENTRY
{
	short PacketType;
	short PacketLength;
	int PacketVersion; // 1:basic, 2:w/objecttype
	unsigned char objecttype; // OBJECTTYPE::*_TYPE
	unsigned long GID;
	short speed;
	short bodyState;
	short healthState;
	int effectState;
	short job;
	short head;
	int weapon;
	short accessory;
	unsigned long moveStartTime;
	short accessory2;
	short accessory3;
	short headpalette;
	short bodypalette;
	short headDir;
	short robe;
	unsigned long GUID;
	short GEmblemVer;
	short honor;
	int virtue;
	bool isPKModeON;
	unsigned char sex;
	unsigned char MoveData[6];
	unsigned char xSize;
	unsigned char ySize;
	short clevel;
	short font;
	char CName[];
};


struct PACKET_ZC_NOTIFY_MOVEENTRY
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ short speed;
	/* this+ 8 */ short bodyState;
	/* this+10 */ short healthState;
	/* this+12 */ short effectState;
	/* this+14 */ short job;
	/* this+16 */ short head;
	/* this+18 */ short weapon;
	/* this+20 */ short accessory;
	/* this+22 */ unsigned long moveStartTime;
	/* this+26 */ short shield;
	/* this+28 */ short accessory2;
	/* this+30 */ short accessory3;
	/* this+32 */ short headpalette;
	/* this+34 */ short bodypalette;
	/* this+36 */ short headDir;
	/* this+38 */ unsigned long GUID;
	/* this+42 */ short GEmblemVer;
	/* this+44 */ short honor;
	/* this+46 */ short virtue;
	/* this+48 */ bool isPKModeON;
	/* this+49 */ unsigned char sex;
	/* this+50 */ unsigned char MoveData[6];
	/* this+56 */ unsigned char xSize;
	/* this+57 */ unsigned char ySize;
	/* this+58 */ short clevel;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_MOVEENTRY> in(p);
		TPacket<PROTO_ZC_NOTIFY_MOVEENTRY,char> out((size_t)0);

		out->PacketType = PacketType;
		out->PacketLength = out.size(); // adapt
		out->PacketVersion = 1;
		out->objecttype = 4; // OBJECTTYPE::UNKNOWN_TYPE // adapt // broken
		out->GID = in->GID;
		out->speed = in->speed;
		out->bodyState = in->bodyState;
		out->healthState = in->healthState;
		out->effectState = in->effectState; // adapt
		out->job = in->job;
		out->head = in->head;
		out->weapon = in->weapon | (in->shield << 16); // adapt // TODO: is this right?
		out->accessory = in->accessory;
		out->moveStartTime = in->moveStartTime;
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->headDir = in->headDir;
		out->robe = 0; // adapt
		out->GUID = in->GUID;
		out->GEmblemVer = in->GEmblemVer;
		out->honor = in->honor;
		out->virtue = in->virtue; // adapt
		out->isPKModeON = in->isPKModeON;
		out->sex = in->sex;
		memcpy(out->MoveData, in->MoveData, 6);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->clevel = in->clevel;
		out->font = 0; // adapt
		memset(out->CName, 0, out.count()); // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_MOVEENTRY,char> in(p);
		TPacket<PACKET_ZC_NOTIFY_MOVEENTRY> out;

		out->PacketType = PacketType;
//		out->PacketLength = out.size(); // adapt
//		out->objecttype = in->objecttype; // adapt
		out->GID = in->GID;
		out->speed = in->speed;
		out->bodyState = in->bodyState;
		out->healthState = in->healthState;
		out->effectState = static_cast<short>(in->effectState); // adapt
		out->job = in->job;
		out->head = in->head;
		out->weapon = LOWORD(in->weapon); // adapt
		out->accessory = in->accessory;
		out->moveStartTime = in->moveStartTime;
		out->shield = HIWORD(in->weapon); // adapt
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->headDir = in->headDir;
//		out->robe = in->robe; // adapt
		out->GUID = in->GUID;
		out->GEmblemVer = in->GEmblemVer;
		out->honor = in->honor;
		out->virtue = min(in->virtue, SHRT_MAX); // adapt //TODO: cap negative values too?
		out->isPKModeON = in->isPKModeON;
		out->sex = in->sex;
		memcpy(out->MoveData, in->MoveData, 6);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->clevel = in->clevel;
//		out->font = in->font; // adapt
//		memcpy(out->CName, in->CName, out.count()); // adapt

		return out;
	}
};


struct PACKET_ZC_NOTIFY_MOVEENTRY2
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ short speed;
	/* this+ 8 */ short bodyState;
	/* this+10 */ short healthState;
	/* this+12 */ short effectState;
	/* this+14 */ short job;
	/* this+16 */ short head;
	/* this+18 */ int weapon;
	/* this+22 */ short accessory;
	/* this+24 */ unsigned long moveStartTime;
	/* this+28 */ short accessory2;
	/* this+30 */ short accessory3;
	/* this+32 */ short headpalette;
	/* this+34 */ short bodypalette;
	/* this+36 */ short headDir;
	/* this+38 */ unsigned long GUID;
	/* this+42 */ short GEmblemVer;
	/* this+44 */ short honor;
	/* this+46 */ short virtue;
	/* this+48 */ bool isPKModeON;
	/* this+49 */ unsigned char sex;
	/* this+50 */ unsigned char MoveData[6];
	/* this+56 */ unsigned char xSize;
	/* this+57 */ unsigned char ySize;
	/* this+58 */ short clevel;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_MOVEENTRY2> in(p);
		TPacket<PROTO_ZC_NOTIFY_MOVEENTRY,char> out((size_t)0);

		out->PacketType = PacketType;
		out->PacketLength = out.size(); // adapt
		out->PacketVersion = 1;
		out->objecttype = 4; // OBJECTTYPE::UNKNOWN_TYPE // adapt // broken
		out->GID = in->GID;
		out->speed = in->speed;
		out->bodyState = in->bodyState;
		out->healthState = in->healthState;
		out->effectState = in->effectState; // adapt
		out->job = in->job;
		out->head = in->head;
		out->weapon = in->weapon;
		out->accessory = in->accessory;
		out->moveStartTime = in->moveStartTime;
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->headDir = in->headDir;
		out->robe = 0; // adapt
		out->GUID = in->GUID;
		out->GEmblemVer = in->GEmblemVer;
		out->honor = in->honor;
		out->virtue = in->virtue; // adapt
		out->isPKModeON = in->isPKModeON;
		out->sex = in->sex;
		memcpy(out->MoveData, in->MoveData, 6);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->clevel = in->clevel;
		out->font = 0; // adapt
		memset(out->CName, 0, out.count()); // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_MOVEENTRY,char> in(p);
		TPacket<PACKET_ZC_NOTIFY_MOVEENTRY2> out;

		out->PacketType = PacketType;
//		out->PacketLength = out.size(); // adapt
//		out->objecttype = in->objecttype; // adapt
		out->GID = in->GID;
		out->speed = in->speed;
		out->bodyState = in->bodyState;
		out->healthState = in->healthState;
		out->effectState = static_cast<short>(in->effectState); // adapt
		out->job = in->job;
		out->head = in->head;
		out->weapon = in->weapon;
		out->accessory = in->accessory;
		out->moveStartTime = in->moveStartTime;
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->headDir = in->headDir;
//		out->robe = in->robe; // adapt
		out->GUID = in->GUID;
		out->GEmblemVer = in->GEmblemVer;
		out->honor = in->honor;
		out->virtue = min(in->virtue, SHRT_MAX); // adapt //TODO: cap negative values too?
		out->isPKModeON = in->isPKModeON;
		out->sex = in->sex;
		memcpy(out->MoveData, in->MoveData, 6);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->clevel = in->clevel;
//		out->font = in->font; // adapt
//		memcpy(out->CName, in->CName, out.count()); // adapt

		return out;
	}
};


struct PACKET_ZC_NOTIFY_MOVEENTRY3
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned char objecttype;
	/* this+ 3 */ unsigned long GID;
	/* this+ 7 */ short speed;
	/* this+ 9 */ short bodyState;
	/* this+11 */ short healthState;
	/* this+13 */ int effectState;
	/* this+17 */ short job;
	/* this+19 */ short head;
	/* this+21 */ int weapon;
	/* this+25 */ short accessory;
	/* this+27 */ unsigned long moveStartTime;
	/* this+31 */ short accessory2;
	/* this+33 */ short accessory3;
	/* this+35 */ short headpalette;
	/* this+37 */ short bodypalette;
	/* this+39 */ short headDir;
	/* this+41 */ unsigned long GUID;
	/* this+45 */ short GEmblemVer;
	/* this+47 */ short honor;
	/* this+49 */ int virtue;
	/* this+53 */ bool isPKModeON;
	/* this+54 */ unsigned char sex;
	/* this+55 */ unsigned char MoveData[6];
	/* this+61 */ unsigned char xSize;
	/* this+62 */ unsigned char ySize;
	/* this+63 */ short clevel;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_MOVEENTRY3> in(p);
		TPacket<PROTO_ZC_NOTIFY_MOVEENTRY,char> out((size_t)0);

		out->PacketType = PacketType;
		out->PacketLength = out.size(); // adapt
		out->PacketVersion = 2;
		out->objecttype = in->objecttype;
		out->GID = in->GID;
		out->speed = in->speed;
		out->bodyState = in->bodyState;
		out->healthState = in->healthState;
		out->effectState = in->effectState;
		out->job = in->job;
		out->head = in->head;
		out->weapon = in->weapon;
		out->accessory = in->accessory;
		out->moveStartTime = in->moveStartTime;
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->headDir = in->headDir;
		out->robe = 0; // adapt
		out->GUID = in->GUID;
		out->GEmblemVer = in->GEmblemVer;
		out->honor = in->honor;
		out->virtue = in->virtue;
		out->isPKModeON = in->isPKModeON;
		out->sex = in->sex;
		memcpy(out->MoveData, in->MoveData, 6);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->clevel = in->clevel;
		out->font = 0; // adapt
		memset(out->CName, 0, out.count()); // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_MOVEENTRY> in(p);
		if( in->PacketVersion < 2 ) return NULL;
		TPacket<PACKET_ZC_NOTIFY_MOVEENTRY3> out;

		out->PacketType = PacketType;
//		out->PacketLength = out.size(); // adapt
		out->objecttype = in->objecttype;
		out->GID = in->GID;
		out->speed = in->speed;
		out->bodyState = in->bodyState;
		out->healthState = in->healthState;
		out->effectState = in->effectState;
		out->job = in->job;
		out->head = in->head;
		out->weapon = in->weapon;
		out->accessory = in->accessory;
		out->moveStartTime = in->moveStartTime;
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->headDir = in->headDir;
//		out->robe = in->robe; // adapt
		out->GUID = in->GUID;
		out->GEmblemVer = in->GEmblemVer;
		out->honor = in->honor;
		out->virtue = in->virtue;
		out->isPKModeON = in->isPKModeON;
		out->sex = in->sex;
		memcpy(out->MoveData, in->MoveData, 6);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->clevel = in->clevel;
//		out->font = in->font; // adapt
//		memcpy(out->CName, in->CName, out.count()); // adapt

		return out;
	}
};


struct PACKET_ZC_NOTIFY_MOVEENTRY4
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned char objecttype;
	/* this+ 3 */ unsigned long GID;
	/* this+ 7 */ short speed;
	/* this+ 9 */ short bodyState;
	/* this+11 */ short healthState;
	/* this+13 */ int effectState;
	/* this+17 */ short job;
	/* this+19 */ short head;
	/* this+21 */ int weapon;
	/* this+25 */ short accessory;
	/* this+27 */ unsigned long moveStartTime;
	/* this+31 */ short accessory2;
	/* this+33 */ short accessory3;
	/* this+35 */ short headpalette;
	/* this+37 */ short bodypalette;
	/* this+39 */ short headDir;
	/* this+41 */ unsigned long GUID;
	/* this+45 */ short GEmblemVer;
	/* this+47 */ short honor;
	/* this+49 */ int virtue;
	/* this+53 */ bool isPKModeON;
	/* this+54 */ unsigned char sex;
	/* this+55 */ unsigned char MoveData[6];
	/* this+61 */ unsigned char xSize;
	/* this+62 */ unsigned char ySize;
	/* this+63 */ short clevel;
	/* this+65 */ short font;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_MOVEENTRY4> in(p);
		TPacket<PROTO_ZC_NOTIFY_MOVEENTRY,char> out((size_t)0);

		out->PacketType = PacketType;
		out->PacketLength = out.size(); // adapt
		out->PacketVersion = 2;
		out->objecttype = in->objecttype;
		out->GID = in->GID;
		out->speed = in->speed;
		out->bodyState = in->bodyState;
		out->healthState = in->healthState;
		out->effectState = in->effectState;
		out->job = in->job;
		out->head = in->head;
		out->weapon = in->weapon;
		out->accessory = in->accessory;
		out->moveStartTime = in->moveStartTime;
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->headDir = in->headDir;
		out->robe = 0; // adapt
		out->GUID = in->GUID;
		out->GEmblemVer = in->GEmblemVer;
		out->honor = in->honor;
		out->virtue = in->virtue;
		out->isPKModeON = in->isPKModeON;
		out->sex = in->sex;
		memcpy(out->MoveData, in->MoveData, 6);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->clevel = in->clevel;
		out->font = in->font;
		memset(out->CName, 0, out.count()); // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_MOVEENTRY,char> in(p);
		if( in->PacketVersion < 2 ) return NULL;
		TPacket<PACKET_ZC_NOTIFY_MOVEENTRY4> out;

		out->PacketType = PacketType;
//		out->PacketLength = out.size(); // adapt
		out->objecttype = in->objecttype;
		out->GID = in->GID;
		out->speed = in->speed;
		out->bodyState = in->bodyState;
		out->healthState = in->healthState;
		out->effectState = in->effectState;
		out->job = in->job;
		out->head = in->head;
		out->weapon = in->weapon;
		out->accessory = in->accessory;
		out->moveStartTime = in->moveStartTime;
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->headDir = in->headDir;
//		out->robe = in->robe;
		out->GUID = in->GUID;
		out->GEmblemVer = in->GEmblemVer;
		out->honor = in->honor;
		out->virtue = in->virtue;
		out->isPKModeON = in->isPKModeON;
		out->sex = in->sex;
		memcpy(out->MoveData, in->MoveData, 6);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->clevel = in->clevel;
		out->font = in->font;
//		memcpy(out->CName, in->CName, out.count()); // adapt

		return out;
	}
};


// obfuscated and variable-length padded form of v3
struct PACKET_ZC_NOTIFY_MOVEENTRY5
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ unsigned char objecttype;
	/* this+ 5 */ unsigned long GID;
	/* this+ 9 */ short speed;
	/* this+11 */ short bodyState;
	/* this+13 */ short healthState;
	/* this+15 */ int effectState;
	/* this+19 */ short job;
	/* this+21 */ short head;
	/* this+23 */ int weapon;
	/* this+27 */ short accessory;
	/* this+29 */ unsigned long moveStartTime;
	/* this+33 */ short accessory2;
	/* this+35 */ short accessory3;
	/* this+37 */ short headpalette;
	/* this+39 */ short bodypalette;
	/* this+41 */ short headDir;
	/* this+43 */ unsigned long GUID;
	/* this+47 */ short GEmblemVer;
	/* this+49 */ short honor;
	/* this+51 */ int virtue;
	/* this+55 */ bool isPKModeON;
	/* this+56 */ unsigned char sex;
	/* this+57 */ unsigned char MoveData[6];
	/* this+63 */ unsigned char xSize;
	/* this+64 */ unsigned char ySize;
	/* this+65 */ short clevel;
	/* this+67 */ BYTE unknown[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_MOVEENTRY5,BYTE> in(p);
		TPacket<PROTO_ZC_NOTIFY_MOVEENTRY,char> out((size_t)0);

		// xor deobfuscation
		in[57] ^= in[5];

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->PacketVersion = 2;
		out->objecttype = in->objecttype;
		out->GID = in->GID;
		out->speed = in->speed;
		out->bodyState = in->bodyState;
		out->healthState = in->healthState;
		out->effectState = in->effectState;
		out->job = in->job;
		out->head = in->head;
		out->weapon = in->weapon;
		out->accessory = in->accessory;
		out->moveStartTime = in->moveStartTime;
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->headDir = in->headDir;
		out->robe = 0; // adapt
		out->GUID = in->GUID;
		out->GEmblemVer = in->GEmblemVer;
		out->honor = in->honor;
		out->virtue = in->virtue;
		out->isPKModeON = in->isPKModeON;
		out->sex = in->sex;
		memcpy(out->MoveData, in->MoveData, 6);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->clevel = in->clevel;
		out->font = 0; // adapt
		memset(out->CName, 0, out.count()); // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_MOVEENTRY,char> in(p);
		if( in->PacketVersion < 2 ) return NULL;
		TPacket<PACKET_ZC_NOTIFY_MOVEENTRY5,BYTE> out((size_t)0);

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->objecttype = in->objecttype;
		out->GID = in->GID;
		out->speed = in->speed;
		out->bodyState = in->bodyState;
		out->healthState = in->healthState;
		out->effectState = in->effectState;
		out->job = in->job;
		out->head = in->head;
		out->weapon = in->weapon;
		out->accessory = in->accessory;
		out->moveStartTime = in->moveStartTime;
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->headDir = in->headDir;
//		out->robe = in->robe; // adapt
		out->GUID = in->GUID;
		out->GEmblemVer = in->GEmblemVer;
		out->honor = in->honor;
		out->virtue = in->virtue;
		out->isPKModeON = in->isPKModeON;
		out->sex = in->sex;
		memcpy(out->MoveData, in->MoveData, 6);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->clevel = in->clevel;
//		out->font = in->font; // adapt
//		memcpy(out->CName, in->CName, out.count()); // adapt

		// xor obfuscation
		out[57] ^= out[5];

		return out;
	}
};


// obfuscated and variable-length padded form of v4
struct PACKET_ZC_NOTIFY_MOVEENTRY6
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ unsigned char objecttype;
	/* this+ 5 */ unsigned long GID;
	/* this+ 9 */ short speed;
	/* this+11 */ short bodyState;
	/* this+13 */ short healthState;
	/* this+15 */ int effectState;
	/* this+19 */ short job;
	/* this+21 */ short head;
	/* this+23 */ int weapon;
	/* this+27 */ short accessory;
	/* this+29 */ unsigned long moveStartTime;
	/* this+33 */ short accessory2;
	/* this+35 */ short accessory3;
	/* this+37 */ short headpalette;
	/* this+39 */ short bodypalette;
	/* this+41 */ short headDir;
	/* this+43 */ unsigned long GUID;
	/* this+47 */ short GEmblemVer;
	/* this+49 */ short honor;
	/* this+51 */ int virtue;
	/* this+55 */ bool isPKModeON;
	/* this+56 */ unsigned char sex;
	/* this+57 */ unsigned char MoveData[6];
	/* this+63 */ unsigned char xSize;
	/* this+64 */ unsigned char ySize;
	/* this+65 */ short clevel;
	/* this+67 */ short font;
	/* this+69 */ BYTE unknown[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_MOVEENTRY6,BYTE> in(p);
		TPacket<PROTO_ZC_NOTIFY_MOVEENTRY,char> out((size_t)0);

		// xor deobfuscation
		*(DWORD*)&in[5] ^= *(WORD*)&in[0] ^ (in[62] + ((in[57] + ((in[61] + (in[59] << 8)) << 8)) << 8));

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->PacketVersion = 2;
		out->objecttype = in->objecttype;
		out->GID = in->GID;
		out->speed = in->speed;
		out->bodyState = in->bodyState;
		out->healthState = in->healthState;
		out->effectState = in->effectState;
		out->job = in->job;
		out->head = in->head;
		out->weapon = in->weapon;
		out->accessory = in->accessory;
		out->moveStartTime = in->moveStartTime;
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->headDir = in->headDir;
		out->robe = 0; // adapt
		out->GUID = in->GUID;
		out->GEmblemVer = in->GEmblemVer;
		out->honor = in->honor;
		out->virtue = in->virtue;
		out->isPKModeON = in->isPKModeON;
		out->sex = in->sex;
		memcpy(out->MoveData, in->MoveData, 6);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->clevel = in->clevel;
		out->font = in->font;
		memset(out->CName, 0, out.count()); // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_MOVEENTRY,char> in(p);
		if( in->PacketVersion < 2 ) return NULL;
		TPacket<PACKET_ZC_NOTIFY_MOVEENTRY6,BYTE> out((size_t)0);

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->objecttype = in->objecttype;
		out->GID = in->GID;
		out->speed = in->speed;
		out->bodyState = in->bodyState;
		out->healthState = in->healthState;
		out->effectState = in->effectState;
		out->job = in->job;
		out->head = in->head;
		out->weapon = in->weapon;
		out->accessory = in->accessory;
		out->moveStartTime = in->moveStartTime;
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->headDir = in->headDir;
//		out->robe = in->robe; // adapt
		out->GUID = in->GUID;
		out->GEmblemVer = in->GEmblemVer;
		out->honor = in->honor;
		out->virtue = in->virtue;
		out->isPKModeON = in->isPKModeON;
		out->sex = in->sex;
		memcpy(out->MoveData, in->MoveData, 6);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->clevel = in->clevel;
		out->font = in->font;
//		memcpy(out->CName, in->CName, out.count()); // adapt

		// xor obfuscation
		*(DWORD*)&out[5] ^= *(WORD*)&out[0] ^ (out[62] + ((out[57] + ((out[61] + (out[59] << 8)) << 8)) << 8));

		return out;
	}
};


struct PACKET_ZC_NOTIFY_MOVEENTRY7
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ unsigned char objecttype;
	/* this+ 5 */ unsigned long GID;
	/* this+ 9 */ short speed;
	/* this+11 */ short bodyState;
	/* this+13 */ short healthState;
	/* this+15 */ int effectState;
	/* this+19 */ short job;
	/* this+21 */ short head;
	/* this+23 */ int weapon;
	/* this+27 */ short accessory;
	/* this+29 */ unsigned long moveStartTime;
	/* this+33 */ short accessory2;
	/* this+35 */ short accessory3;
	/* this+37 */ short headpalette;
	/* this+39 */ short bodypalette;
	/* this+41 */ short headDir;
	/* this+43 */ unsigned long GUID;
	/* this+47 */ short GEmblemVer;
	/* this+49 */ short honor;
	/* this+51 */ int virtue;
	/* this+55 */ bool isPKModeON;
	/* this+56 */ unsigned char sex;
	/* this+57 */ unsigned char MoveData[6];
	/* this+63 */ unsigned char xSize;
	/* this+64 */ unsigned char ySize;
	/* this+65 */ short clevel;
	/* this+67 */ short font;
	/* this+69 */ char CName[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_MOVEENTRY7,char> in(p);
		TPacket<PROTO_ZC_NOTIFY_MOVEENTRY,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->PacketVersion = 2;
		out->objecttype = in->objecttype;
		out->GID = in->GID;
		out->speed = in->speed;
		out->bodyState = in->bodyState;
		out->healthState = in->healthState;
		out->effectState = in->effectState;
		out->job = in->job;
		out->head = in->head;
		out->weapon = in->weapon;
		out->accessory = in->accessory;
		out->moveStartTime = in->moveStartTime;
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->headDir = in->headDir;
		out->robe = 0; // adapt
		out->GUID = in->GUID;
		out->GEmblemVer = in->GEmblemVer;
		out->honor = in->honor;
		out->virtue = in->virtue;
		out->isPKModeON = in->isPKModeON;
		out->sex = in->sex;
		memcpy(out->MoveData, in->MoveData, 6);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->clevel = in->clevel;
		out->font = in->font;
		memcpy(out->CName, in->CName, out.count());

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_MOVEENTRY,char> in(p);
		if( in->PacketVersion < 2 ) return NULL;
		TPacket<PACKET_ZC_NOTIFY_MOVEENTRY7,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->objecttype = in->objecttype;
		out->GID = in->GID;
		out->speed = in->speed;
		out->bodyState = in->bodyState;
		out->healthState = in->healthState;
		out->effectState = in->effectState;
		out->job = in->job;
		out->head = in->head;
		out->weapon = in->weapon;
		out->accessory = in->accessory;
		out->moveStartTime = in->moveStartTime;
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->headDir = in->headDir;
//		out->robe = in->robe; // adapt
		out->GUID = in->GUID;
		out->GEmblemVer = in->GEmblemVer;
		out->honor = in->honor;
		out->virtue = in->virtue;
		out->isPKModeON = in->isPKModeON;
		out->sex = in->sex;
		memcpy(out->MoveData, in->MoveData, 6);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->clevel = in->clevel;
		out->font = in->font;
		memcpy(out->CName, in->CName, out.count());

		return out;
	}
};


struct PACKET_ZC_NOTIFY_MOVEENTRY8
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ unsigned char objecttype;
	/* this+ 5 */ unsigned long GID;
	/* this+ 9 */ short speed;
	/* this+11 */ short bodyState;
	/* this+13 */ short healthState;
	/* this+15 */ int effectState;
	/* this+19 */ short job;
	/* this+21 */ short head;
	/* this+23 */ int weapon;
	/* this+27 */ short accessory;
	/* this+29 */ unsigned long moveStartTime;
	/* this+33 */ short accessory2;
	/* this+35 */ short accessory3;
	/* this+37 */ short headpalette;
	/* this+39 */ short bodypalette;
	/* this+41 */ short headDir;
	/* this+43 */ short robe;
	/* this+45 */ unsigned long GUID;
	/* this+49 */ short GEmblemVer;
	/* this+51 */ short honor;
	/* this+53 */ int virtue;
	/* this+57 */ bool isPKModeON;
	/* this+58 */ unsigned char sex;
	/* this+59 */ unsigned char MoveData[6];
	/* this+65 */ unsigned char xSize;
	/* this+66 */ unsigned char ySize;
	/* this+67 */ short clevel;
	/* this+69 */ short font;
	/* this+71 */ char CName[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_MOVEENTRY8,char> in(p);
		TPacket<PROTO_ZC_NOTIFY_MOVEENTRY,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->PacketVersion = 2;
		out->objecttype = in->objecttype;
		out->GID = in->GID;
		out->speed = in->speed;
		out->bodyState = in->bodyState;
		out->healthState = in->healthState;
		out->effectState = in->effectState;
		out->job = in->job;
		out->head = in->head;
		out->weapon = in->weapon;
		out->accessory = in->accessory;
		out->moveStartTime = in->moveStartTime;
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->headDir = in->headDir;
		out->robe = in->robe;
		out->GUID = in->GUID;
		out->GEmblemVer = in->GEmblemVer;
		out->honor = in->honor;
		out->virtue = in->virtue;
		out->isPKModeON = in->isPKModeON;
		out->sex = in->sex;
		memcpy(out->MoveData, in->MoveData, 6);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->clevel = in->clevel;
		out->font = in->font;
		memcpy(out->CName, in->CName, out.count());

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_MOVEENTRY,char> in(p);
		if( in->PacketVersion < 2 ) return NULL;
		TPacket<PACKET_ZC_NOTIFY_MOVEENTRY8,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->objecttype = in->objecttype;
		out->GID = in->GID;
		out->speed = in->speed;
		out->bodyState = in->bodyState;
		out->healthState = in->healthState;
		out->effectState = in->effectState;
		out->job = in->job;
		out->head = in->head;
		out->weapon = in->weapon;
		out->accessory = in->accessory;
		out->moveStartTime = in->moveStartTime;
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->headDir = in->headDir;
		out->robe = in->robe;
		out->GUID = in->GUID;
		out->GEmblemVer = in->GEmblemVer;
		out->honor = in->honor;
		out->virtue = in->virtue;
		out->isPKModeON = in->isPKModeON;
		out->sex = in->sex;
		memcpy(out->MoveData, in->MoveData, 6);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->clevel = in->clevel;
		out->font = in->font;
		memcpy(out->CName, in->CName, out.count());

		return out;
	}
};
