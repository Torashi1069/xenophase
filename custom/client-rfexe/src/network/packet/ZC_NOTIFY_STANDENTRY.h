struct PROTO_ZC_NOTIFY_STANDENTRY
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
	unsigned char PosDir[3];
	unsigned char xSize;
	unsigned char ySize;
	unsigned char state;
	short clevel;
	short font;
	char CName[];
};


struct PACKET_ZC_NOTIFY_STANDENTRY
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
	/* this+22 */ short shield;
	/* this+24 */ short accessory2;
	/* this+26 */ short accessory3;
	/* this+28 */ short headpalette;
	/* this+30 */ short bodypalette;
	/* this+32 */ short headDir;
	/* this+34 */ unsigned long GUID;
	/* this+38 */ short GEmblemVer;
	/* this+40 */ short honor;
	/* this+42 */ short virtue;
	/* this+44 */ bool isPKModeON;
	/* this+45 */ unsigned char sex;
	/* this+46 */ unsigned char PosDir[3];
	/* this+49 */ unsigned char xSize;
	/* this+50 */ unsigned char ySize;
	/* this+51 */ unsigned char state;
	/* this+52 */ short clevel;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_STANDENTRY> in(p);
		TPacket<PROTO_ZC_NOTIFY_STANDENTRY,char> out((size_t)0);

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
		out->weapon = in->weapon | (in->shield << 16); // adapt
		out->accessory = in->accessory;
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->headDir = in->headDir;
		out->robe = 0; // adapt
		out->GUID = in->GUID;
		out->GEmblemVer = in->GEmblemVer;
		out->honor = in->honor;
		out->virtue = static_cast<int>(in->virtue); // adapt
		out->isPKModeON = in->isPKModeON;
		out->sex = in->sex;
		memcpy(out->PosDir, in->PosDir, 3);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->state = in->state;
		out->clevel = in->clevel;
		out->font = 0; // adapt
		memset(out->CName, 0, out.count()); // adapt

		if( in->job > 45 && in->job < 4000 )
		{
			out->weapon = 0;
			out->GEmblemVer = in->shield;
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_STANDENTRY,char> in(p);
		TPacket<PACKET_ZC_NOTIFY_STANDENTRY> out;

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
		memcpy(out->PosDir, in->PosDir, 3);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->state = in->state;
		out->clevel = in->clevel;
//		out->font = in->font; // adapt
//		memcpy(out->CName, in->CName, out.count()); // adapt

		if( in->job > 45 && in->job < 4000 )
		{
			out->shield = in->GEmblemVer;
		}

		return out;
	}
};


// a peculiar mutation of the above packet (has 'objecttype' field)
struct PACKET_ZC_NOTIFY_STANDENTRY_2009
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned char objecttype;
	/* this+ 3 */ unsigned long GID;
	/* this+ 7 */ short speed;
	/* this+ 9 */ short bodyState;
	/* this+11 */ short healthState;
	/* this+13 */ short effectState;
	/* this+15 */ short job;
	/* this+17 */ short head;
	/* this+19 */ short weapon;
	/* this+21 */ short accessory;
	/* this+23 */ short shield;
	/* this+25 */ short accessory2;
	/* this+27 */ short accessory3;
	/* this+29 */ short headpalette;
	/* this+31 */ short bodypalette;
	/* this+33 */ short headDir;
	/* this+35 */ unsigned long GUID;
	/* this+39 */ short GEmblemVer;
	/* this+41 */ short honor;
	/* this+43 */ short virtue;
	/* this+45 */ bool isPKModeON;
	/* this+46 */ unsigned char sex;
	/* this+47 */ unsigned char PosDir[3];
	/* this+50 */ unsigned char xSize;
	/* this+51 */ unsigned char ySize;
	/* this+52 */ unsigned char state;
	/* this+53 */ short clevel;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_STANDENTRY_2009> in(p);
		TPacket<PROTO_ZC_NOTIFY_STANDENTRY,char> out((size_t)0);

		out->PacketType = PacketType;
		out->PacketLength = out.size(); // adapt
		out->PacketVersion = 2;
		out->objecttype = in->objecttype;
		out->GID = in->GID;
		out->speed = in->speed;
		out->bodyState = in->bodyState;
		out->healthState = in->healthState;
		out->effectState = in->effectState; // adapt
		out->job = in->job;
		out->head = in->head;
		out->weapon = in->weapon | (in->shield << 16); // adapt
		out->accessory = in->accessory;
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->headDir = in->headDir;
		out->robe = 0; // adapt
		out->GUID = in->GUID;
		out->GEmblemVer = in->GEmblemVer;
		out->honor = in->honor;
		out->virtue = static_cast<int>(in->virtue); // adapt
		out->isPKModeON = in->isPKModeON;
		out->sex = in->sex;
		memcpy(out->PosDir, in->PosDir, 3);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->state = in->state;
		out->clevel = in->clevel;
		out->font = 0; // adapt
		memset(out->CName, 0, out.count()); // adapt

		if( in->job > 45 && in->job < 4000 )
		{
			out->weapon = 0;
			out->GEmblemVer = in->shield;
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_STANDENTRY,char> in(p);
		if( in->PacketVersion < 2 ) return NULL;
		TPacket<PACKET_ZC_NOTIFY_STANDENTRY_2009> out;

		out->PacketType = PacketType;
//		out->PacketLength = out.size(); // adapt
		out->objecttype = in->objecttype;
		out->GID = in->GID;
		out->speed = in->speed;
		out->bodyState = in->bodyState;
		out->healthState = in->healthState;
		out->effectState = static_cast<short>(in->effectState); // adapt
		out->job = in->job;
		out->head = in->head;
		out->weapon = LOWORD(in->weapon); // adapt
		out->accessory = in->accessory;
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
		memcpy(out->PosDir, in->PosDir, 3);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->state = in->state;
		out->clevel = in->clevel;
//		out->font = in->font; // adapt
//		memcpy(out->CName, in->CName, out.count()); // adapt

		if( in->job > 45 && in->job < 4000 )
		{
			out->shield = in->GEmblemVer;
		}

		return out;
	}
};


struct PACKET_ZC_NOTIFY_STANDENTRY2
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
	/* this+24 */ short accessory2;
	/* this+26 */ short accessory3;
	/* this+28 */ short headpalette;
	/* this+30 */ short bodypalette;
	/* this+32 */ short headDir;
	/* this+34 */ unsigned long GUID;
	/* this+38 */ short GEmblemVer;
	/* this+40 */ short honor;
	/* this+42 */ short virtue;
	/* this+44 */ bool isPKModeON;
	/* this+45 */ unsigned char sex;
	/* this+46 */ unsigned char PosDir[3];
	/* this+49 */ unsigned char xSize;
	/* this+50 */ unsigned char ySize;
	/* this+51 */ unsigned char state;
	/* this+52 */ short clevel;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_STANDENTRY2> in(p);
		TPacket<PROTO_ZC_NOTIFY_STANDENTRY,char> out((size_t)0);

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
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->headDir = in->headDir;
		out->robe = 0; // adapt
		out->GUID = in->GUID;
		out->GEmblemVer = in->GEmblemVer;
		out->honor = in->honor;
		out->virtue = static_cast<int>(in->virtue); // adapt
		out->isPKModeON = in->isPKModeON;
		out->sex = in->sex;
		memcpy(out->PosDir, in->PosDir, 3);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->state = in->state;
		out->clevel = in->clevel;
		out->font = 0; // adapt
		memset(out->CName, 0, out.count()); // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_STANDENTRY,char> in(p);
		TPacket<PACKET_ZC_NOTIFY_STANDENTRY2> out;

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
		memcpy(out->PosDir, in->PosDir, 3);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->state = in->state;
		out->clevel = in->clevel;
//		out->font = in->font; // adapt
//		memcpy(out->CName, in->CName, out.count()); // adapt

		return out;
	}
};


struct PACKET_ZC_NOTIFY_STANDENTRY3
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ short speed;
	/* this+ 8 */ short bodyState;
	/* this+10 */ short healthState;
	/* this+12 */ int effectState;
	/* this+16 */ short job;
	/* this+18 */ short head;
	/* this+20 */ int weapon;
	/* this+24 */ short accessory;
	/* this+26 */ short accessory2;
	/* this+28 */ short accessory3;
	/* this+30 */ short headpalette;
	/* this+32 */ short bodypalette;
	/* this+34 */ short headDir;
	/* this+36 */ unsigned long GUID;
	/* this+40 */ short GEmblemVer;
	/* this+42 */ short honor;
	/* this+44 */ int virtue;
	/* this+48 */ bool isPKModeON;
	/* this+49 */ unsigned char sex;
	/* this+50 */ unsigned char PosDir[3];
	/* this+53 */ unsigned char xSize;
	/* this+54 */ unsigned char ySize;
	/* this+55 */ unsigned char state;
	/* this+56 */ short clevel;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_STANDENTRY3> in(p);
		TPacket<PROTO_ZC_NOTIFY_STANDENTRY,char> out((size_t)0);

		out->PacketType = PacketType;
		out->PacketLength = out.size(); // adapt
		out->PacketVersion = 1;
		out->objecttype = 4; // OBJECTTYPE::UNKNOWN_TYPE // adapt // broken
		out->GID = in->GID;
		out->speed = in->speed;
		out->bodyState = in->bodyState;
		out->healthState = in->healthState;
		out->effectState = in->effectState;
		out->job = in->job;
		out->head = in->head;
		out->weapon = in->weapon;
		out->accessory = in->accessory;
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
		memcpy(out->PosDir, in->PosDir, 3);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->state = in->state;
		out->clevel = in->clevel;
		out->font = 0; // adapt
		memset(out->CName, 0, out.count()); // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_STANDENTRY,char> in(p);
		TPacket<PACKET_ZC_NOTIFY_STANDENTRY3> out;

		out->PacketType = PacketType;
//		out->PacketLength = out.size(); // adapt
//		out->objecttype = in->objecttype; // adapt
		out->GID = in->GID;
		out->speed = in->speed;
		out->bodyState = in->bodyState;
		out->healthState = in->healthState;
		out->effectState = in->effectState;
		out->job = in->job;
		out->head = in->head;
		out->weapon = in->weapon;
		out->accessory = in->accessory;
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
		memcpy(out->PosDir, in->PosDir, 3);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->state = in->state;
		out->clevel = in->clevel;
//		out->font = in->font; // adapt
//		memcpy(out->CName, in->CName, out.count()); // adapt

		return out;
	}
};


struct PACKET_ZC_NOTIFY_STANDENTRY4
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ short speed;
	/* this+ 8 */ short bodyState;
	/* this+10 */ short healthState;
	/* this+12 */ int effectState;
	/* this+16 */ short job;
	/* this+18 */ short head;
	/* this+20 */ int weapon;
	/* this+24 */ short accessory;
	/* this+26 */ short accessory2;
	/* this+28 */ short accessory3;
	/* this+30 */ short headpalette;
	/* this+32 */ short bodypalette;
	/* this+34 */ short headDir;
	/* this+36 */ unsigned long GUID;
	/* this+40 */ short GEmblemVer;
	/* this+42 */ short honor;
	/* this+44 */ int virtue;
	/* this+48 */ bool isPKModeON;
	/* this+49 */ unsigned char sex;
	/* this+50 */ unsigned char PosDir[3];
	/* this+53 */ unsigned char xSize;
	/* this+54 */ unsigned char ySize;
	/* this+55 */ unsigned char state;
	/* this+56 */ short clevel;
	/* this+58 */ short font;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_STANDENTRY4> in(p);
		TPacket<PROTO_ZC_NOTIFY_STANDENTRY,char> out((size_t)0);

		out->PacketType = PacketType;
		out->PacketLength = out.size(); // adapt
		out->PacketVersion = 1;
		out->objecttype = 4; // OBJECTTYPE::UNKNOWN_TYPE // adapt // broken
		out->GID = in->GID;
		out->speed = in->speed;
		out->bodyState = in->bodyState;
		out->healthState = in->healthState;
		out->effectState = in->effectState;
		out->job = in->job;
		out->head = in->head;
		out->weapon = in->weapon;
		out->accessory = in->accessory;
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
		memcpy(out->PosDir, in->PosDir, 3);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->state = in->state;
		out->clevel = in->clevel;
		out->font = in->font;
		memset(out->CName, 0, out.count()); // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_STANDENTRY,char> in(p);
		TPacket<PACKET_ZC_NOTIFY_STANDENTRY4> out;

		out->PacketType = PacketType;
//		out->PacketLength = out.size(); // adapt
//		out->objecttype = in->objecttype; // adapt
		out->GID = in->GID;
		out->speed = in->speed;
		out->bodyState = in->bodyState;
		out->healthState = in->healthState;
		out->effectState = in->effectState;
		out->job = in->job;
		out->head = in->head;
		out->weapon = in->weapon;
		out->accessory = in->accessory;
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
		memcpy(out->PosDir, in->PosDir, 3);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->state = in->state;
		out->clevel = in->clevel;
		out->font = in->font;
//		memcpy(out->CName, in->CName, out.count()); // adapt

		return out;
	}
};


struct PACKET_ZC_NOTIFY_STANDENTRY6
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ unsigned char objecttype;
	/* this+ 5 */ unsigned long GID;
	/* this+ 9 */ short speed;
	/* this+11 */ short bodyState;
	/* this+13 */ short healthState;
	/* this+15 */ short effectState;
	/* this+17 */ short job;
	/* this+19 */ short head;
	/* this+21 */ short weapon;
	/* this+23 */ short accessory;
	/* this+25 */ short shield;
	/* this+27 */ short accessory2;
	/* this+29 */ short accessory3;
	/* this+31 */ short headpalette;
	/* this+33 */ short bodypalette;
	/* this+35 */ short headDir;
	/* this+37 */ unsigned long GUID;
	/* this+41 */ short GEmblemVer;
	/* this+43 */ short honor;
	/* this+45 */ short virtue;
	/* this+47 */ bool isPKModeON;
	/* this+48 */ unsigned char sex;
	/* this+49 */ unsigned char PosDir[3];
	/* this+52 */ unsigned char xSize;
	/* this+53 */ unsigned char ySize;
	/* this+54 */ unsigned char state;
	/* this+55 */ short clevel;
	/* this+57 */ short font;
	/* this+59 */ BYTE unknown[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_STANDENTRY6,BYTE> in(p);
		TPacket<PROTO_ZC_NOTIFY_STANDENTRY,char> out((size_t)0);

		// xor deobfuscation
		*(DWORD*)&in[5] = (*(WORD*)&in[0] << 16) ^ ((in[49] ^ 0x53) + ((in[51] + ((in[49] + (in[50] << 8)) << 8)) << 8));

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
		out->weapon = in->weapon | (in->shield << 16); // adapt
		out->accessory = in->accessory;
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->headDir = in->headDir;
		out->robe = 0; // adapt
		out->GUID = in->GUID;
		out->GEmblemVer = in->GEmblemVer;
		out->honor = in->honor;
		out->virtue = static_cast<int>(in->virtue); // adapt
		out->isPKModeON = in->isPKModeON;
		out->sex = in->sex;
		memcpy(out->PosDir, in->PosDir, 3);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->state = in->state;
		out->clevel = in->clevel;
		out->font = in->font;
		memset(out->CName, 0, out.count()); // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_STANDENTRY,char> in(p);
 		if( in->PacketVersion < 2 ) return NULL;
		TPacket<PACKET_ZC_NOTIFY_STANDENTRY6,BYTE> out((size_t)0);

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
		out->weapon = LOWORD(in->weapon); // adapt
		out->accessory = in->accessory;
		out->shield = HIWORD(in->weapon); // adapt
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->headDir = in->headDir;
		out->GUID = in->GUID;
		out->GEmblemVer = in->GEmblemVer;
		out->honor = in->honor;
		out->virtue = static_cast<short>(in->virtue); // adapt
		out->isPKModeON = in->isPKModeON;
		out->sex = in->sex;
		memcpy(out->PosDir, in->PosDir, 3);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->state = in->state;
		out->clevel = in->clevel;
		out->font = in->font;
//		memcpy(out->CName, in->CName, out.count()); // adapt

		// xor obfuscation
		*(DWORD*)&out[5] = (*(WORD*)&out[0] << 16) ^ ((out[49] ^ 0x53) + ((out[51] + ((out[49] + (out[50] << 8)) << 8)) << 8));

		return out;
	}
};


struct PACKET_ZC_NOTIFY_STANDENTRY5
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
	/* this+29 */ short accessory2;
	/* this+31 */ short accessory3;
	/* this+33 */ short headpalette;
	/* this+35 */ short bodypalette;
	/* this+37 */ short headDir;
	/* this+39 */ unsigned long GUID;
	/* this+43 */ short GEmblemVer;
	/* this+45 */ short honor;
	/* this+47 */ int virtue;
	/* this+51 */ bool isPKModeON;
	/* this+52 */ unsigned char sex;
	/* this+53 */ unsigned char PosDir[3];
	/* this+56 */ unsigned char xSize;
	/* this+57 */ unsigned char ySize;
	/* this+58 */ unsigned char state;
	/* this+59 */ short clevel;
	/* this+61 */ short font;
	/* this+63 */ char CName[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_STANDENTRY5,char> in(p);
		TPacket<PROTO_ZC_NOTIFY_STANDENTRY,char> out(in.count());

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
		memcpy(out->PosDir, in->PosDir, 3);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->state = in->state;
		out->clevel = in->clevel;
		out->font = in->font;
		memcpy(out->CName, in->CName, out.count());

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_STANDENTRY,char> in(p);
 		if( in->PacketVersion < 2 ) return NULL;
		TPacket<PACKET_ZC_NOTIFY_STANDENTRY5,char> out(in.count());

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
		memcpy(out->PosDir, in->PosDir, 3);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->state = in->state;
		out->clevel = in->clevel;
		out->font = in->font;
		memcpy(out->CName, in->CName, out.count());

		return out;
	}
};


struct PACKET_ZC_NOTIFY_STANDENTRY7
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
	/* this+29 */ short accessory2;
	/* this+31 */ short accessory3;
	/* this+33 */ short headpalette;
	/* this+35 */ short bodypalette;
	/* this+37 */ short headDir;
	/* this+39 */ short robe;
	/* this+41 */ unsigned long GUID;
	/* this+45 */ short GEmblemVer;
	/* this+47 */ short honor;
	/* this+49 */ int virtue;
	/* this+53 */ bool isPKModeON;
	/* this+54 */ unsigned char sex;
	/* this+55 */ unsigned char PosDir[3];
	/* this+58 */ unsigned char xSize;
	/* this+59 */ unsigned char ySize;
	/* this+60 */ unsigned char state;
	/* this+61 */ short clevel;
	/* this+63 */ short font;
	/* this+65 */ char CName[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_STANDENTRY7,char> in(p);
		TPacket<PROTO_ZC_NOTIFY_STANDENTRY,char> out(in.count());

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
		memcpy(out->PosDir, in->PosDir, 3);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->state = in->state;
		out->clevel = in->clevel;
		out->font = in->font;
		memcpy(out->CName, in->CName, out.count());

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_STANDENTRY,char> in(p);
		if( in->PacketVersion < 2 ) return NULL;
		TPacket<PACKET_ZC_NOTIFY_STANDENTRY7,char> out(in.count());

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
		memcpy(out->PosDir, in->PosDir, 3);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->state = in->state;
		out->clevel = in->clevel;
		out->font = in->font;
		memcpy(out->CName, in->CName, out.count());

		return out;
	}
};
