struct PROTO_ZC_NOTIFY_STANDENTRY_NPC
{
	short PacketType;
	unsigned char objecttype;
	unsigned long GID;
	short speed;
	short bodyState;
	short healthState;
	short effectState;
	short head;
	short weapon;
	short accessory;
	short job;
	short shield;
	short accessory2;
	short accessory3;
	short headpalette;
	short bodypalette;
	short headDir;
	unsigned long GUID;
	short GEmblemVer;
	short honor;
	short virtue;
	bool isPKModeON;
	unsigned char sex;
	unsigned char PosDir[3];
	unsigned char xSize;
	unsigned char ySize;
	unsigned char state;
	short clevel;
};


struct PACKET_ZC_NOTIFY_STANDENTRY_NPC
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ short speed;
	/* this+ 8 */ short bodyState;
	/* this+10 */ short healthState;
	/* this+12 */ short effectState;
	/* this+14 */ short head;
	/* this+16 */ short weapon;
	/* this+18 */ short accessory;
	/* this+20 */ short job;
	/* this+22 */ short shield;
	/* this+24 */ short accessory2;
	/* this+26 */ short accessory3;
	/* this+28 */ short headpalette;
	/* this+30 */ short bodypalette;
	/* this+32 */ short headDir;
	/* this+34 */ bool isPKModeON;
	/* this+35 */ unsigned char sex;
	/* this+36 */ unsigned char PosDir[3];
	/* this+39 */ unsigned char xSize;
	/* this+40 */ unsigned char ySize;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_STANDENTRY_NPC> in(p);
		TPacket<PROTO_ZC_NOTIFY_STANDENTRY_NPC> out;

		out->PacketType = PacketType;
		out->objecttype = 4; // CLIENTTYPE::UNKNOWN_TYPE // adapt //TODO: verify that this works
		out->GID = in->GID;
		out->speed = in->speed;
		out->bodyState = in->bodyState;
		out->healthState = in->healthState;
		out->effectState = in->effectState;
		out->head = in->head;
		out->weapon = in->weapon;
		out->accessory = in->accessory;
		out->job = in->job;
		out->shield = in->shield;
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->headDir = in->headDir;
		out->GUID = 0; // adapt
		out->GEmblemVer = 0; // adapt
		out->honor = 0; // adapt
		out->virtue = 0; // adapt
		out->isPKModeON = in->isPKModeON;
		out->sex = in->sex;
		memcpy(out->PosDir, in->PosDir, 3);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->state = 0; // adapt //TODO: verify
		out->clevel = 0; // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_STANDENTRY_NPC> in(p);
		TPacket<PACKET_ZC_NOTIFY_STANDENTRY_NPC> out;

		out->PacketType = PacketType;
//		out->objecttype = in->objecttype; // adapt
		out->GID = in->GID;
		out->speed = in->speed;
		out->bodyState = in->bodyState;
		out->healthState = in->healthState;
		out->effectState = in->effectState;
		out->head = in->head;
		out->weapon = in->weapon;
		out->accessory = in->accessory;
		out->job = in->job;
		out->shield = in->shield;
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->headDir = in->headDir;
//		out->GUID = in->GUID; // adapt
//		out->GEmblemVer = in->GEmblemVer; // adapt
//		out->honor = in->honor; // adapt
//		out->virtue = in->virtue; // adapt
		out->isPKModeON = in->isPKModeON;
		out->sex = in->sex;
		memcpy(out->PosDir, in->PosDir, 3);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
//		out->state = in->state; // adapt
//		out->clevel = in->clevel; // adapt

		return out;
	}
};


//NOTE: eathena says 20071106
struct PACKET_ZC_NOTIFY_STANDENTRY_NPC_2009
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned char objecttype;
	/* this+ 3 */ unsigned long GID;
	/* this+ 7 */ short speed;
	/* this+ 9 */ short bodyState;
	/* this+11 */ short healthState;
	/* this+13 */ short effectState;
	/* this+15 */ short head;
	/* this+17 */ short weapon;
	/* this+19 */ short accessory;
	/* this+21 */ short job;
	/* this+23 */ short shield;
	/* this+25 */ short accessory2;
	/* this+27 */ short accessory3;
	/* this+29 */ short headpalette;
	/* this+31 */ short bodypalette;
	/* this+33 */ short headDir;
	/* this+35 */ bool isPKModeON;
	/* this+36 */ unsigned char sex;
	/* this+37 */ unsigned char PosDir[3];
	/* this+40 */ unsigned char xSize;
	/* this+41 */ unsigned char ySize;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_STANDENTRY_NPC_2009> in(p);
		TPacket<PROTO_ZC_NOTIFY_STANDENTRY_NPC> out;

		out->PacketType = PacketType;
		out->objecttype = in->objecttype;
		out->GID = in->GID;
		out->speed = in->speed;
		out->bodyState = in->bodyState;
		out->healthState = in->healthState;
		out->effectState = in->effectState;
		out->head = in->head;
		out->weapon = in->weapon;
		out->accessory = in->accessory;
		out->job = in->job;
		out->shield = in->shield;
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->headDir = in->headDir;
		out->GUID = 0; // adapt
		out->GEmblemVer = 0; // adapt
		out->honor = 0; // adapt
		out->virtue = 0; // adapt
		out->isPKModeON = in->isPKModeON;
		out->sex = in->sex;
		memcpy(out->PosDir, in->PosDir, 3);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->state = 0; // adapt //TODO: verify
		out->clevel = 0; // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_STANDENTRY_NPC> in(p);
		TPacket<PACKET_ZC_NOTIFY_STANDENTRY_NPC_2009> out;

		out->PacketType = PacketType;
		out->objecttype = in->objecttype;
		out->GID = in->GID;
		out->speed = in->speed;
		out->bodyState = in->bodyState;
		out->healthState = in->healthState;
		out->effectState = in->effectState;
		out->head = in->head;
		out->weapon = in->weapon;
		out->accessory = in->accessory;
		out->job = in->job;
		out->shield = in->shield;
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->headDir = in->headDir;
//		out->GUID = in->GUID; // adapt
//		out->GEmblemVer = in->GEmblemVer; // adapt
//		out->honor = in->honor; // adapt
//		out->virtue = in->virtue; // adapt
		out->isPKModeON = in->isPKModeON;
		out->sex = in->sex;
		memcpy(out->PosDir, in->PosDir, 3);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
//		out->state = in->state; // adapt
//		out->clevel = in->clevel; // adapt

		return out;
	}
};


struct PACKET_ZC_NOTIFY_STANDENTRY_NPC_2010
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned char objecttype;
	/* this+ 3 */ unsigned long GID;
	/* this+ 7 */ short speed;
	/* this+ 9 */ short bodyState;
	/* this+11 */ short healthState;
	/* this+13 */ short effectState;
	/* this+15 */ short head;
	/* this+17 */ short weapon;
	/* this+19 */ short accessory;
	/* this+21 */ short job;
	/* this+23 */ short shield;
	/* this+25 */ short accessory2;
	/* this+27 */ short accessory3;
	/* this+29 */ short headpalette;
	/* this+31 */ short bodypalette;
	/* this+33 */ short headDir;
	/* this+35 */ bool isPKModeON;
	/* this+36 */ unsigned char sex;
	/* this+37 */ unsigned char PosDir[3];
	/* this+40 */ unsigned char xSize;
	/* this+41 */ unsigned char ySize;
	/* this+42 */ short clevel;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_STANDENTRY_NPC_2010> in(p);
		TPacket<PROTO_ZC_NOTIFY_STANDENTRY_NPC> out;

		out->PacketType = PacketType;
		out->objecttype = in->objecttype;
		out->GID = in->GID;
		out->speed = in->speed;
		out->bodyState = in->bodyState;
		out->healthState = in->healthState;
		out->effectState = in->effectState;
		out->head = in->head;
		out->weapon = in->weapon;
		out->accessory = in->accessory;
		out->job = in->job;
		out->shield = in->shield;
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->headDir = in->headDir;
		out->GUID = 0; // adapt
		out->GEmblemVer = 0; // adapt
		out->honor = 0; // adapt
		out->virtue = 0; // adapt
		out->isPKModeON = in->isPKModeON;
		out->sex = in->sex;
		memcpy(out->PosDir, in->PosDir, 3);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->state = 0; // adapt //TODO: verify
		out->clevel = in->clevel;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_STANDENTRY_NPC> in(p);
		TPacket<PACKET_ZC_NOTIFY_STANDENTRY_NPC_2010> out;

		out->PacketType = PacketType;
		out->objecttype = in->objecttype;
		out->GID = in->GID;
		out->speed = in->speed;
		out->bodyState = in->bodyState;
		out->healthState = in->healthState;
		out->effectState = in->effectState;
		out->head = in->head;
		out->weapon = in->weapon;
		out->accessory = in->accessory;
		out->job = in->job;
		out->shield = in->shield;
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->headDir = in->headDir;
//		out->GUID = in->GUID; // adapt
//		out->GEmblemVer = in->GEmblemVer; // adapt
//		out->honor = in->honor; // adapt
//		out->virtue = in->virtue; // adapt
		out->isPKModeON = in->isPKModeON;
		out->sex = in->sex;
		memcpy(out->PosDir, in->PosDir, 3);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
//		out->state = in->state; // adapt
		out->clevel = in->clevel;

		return out;
	}
};


struct PACKET_ZC_NOTIFY_NPC_STANDENTRY
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
	/* this+57 */ BYTE unknown[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_NPC_STANDENTRY,BYTE> in(p);
		TPacket<PROTO_ZC_NOTIFY_STANDENTRY_NPC> out;

		out->PacketType = PacketType;
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
		out->shield = in->shield;
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->headDir = in->headDir;
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

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_STANDENTRY_NPC> in(p);
		TPacket<PACKET_ZC_NOTIFY_NPC_STANDENTRY,BYTE> out((size_t)0);

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
		out->shield = in->shield;
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->headDir = in->headDir;
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

		return out;
	}
};
