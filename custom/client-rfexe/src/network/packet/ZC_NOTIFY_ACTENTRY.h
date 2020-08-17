struct PROTO_ZC_NOTIFY_ACTENTRY
{
	short PacketType;
	unsigned long GID;
	short speed;
	short bodyState;
	short healthState;
	short effectState;
	short job;
	short head;
	short weapon;
	short accessory;
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
	unsigned char action;
	unsigned long actStartTime;
	short clevel;
};


struct PACKET_ZC_NOTIFY_ACTENTRY
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
	/* this+51 */ unsigned char action;
	/* this+52 */ unsigned long actStartTime;
	/* this+56 */ short clevel;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_ACTENTRY> in(p);
		TPacket<PROTO_ZC_NOTIFY_ACTENTRY> out;

		out->PacketType = PacketType;
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
		out->action = in->action;
		out->actStartTime = in->actStartTime;
		out->clevel = in->clevel;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_ACTENTRY> in(p);
		TPacket<PACKET_ZC_NOTIFY_ACTENTRY> out;

		out->PacketType = PacketType;
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
		out->action = in->action;
		out->actStartTime = in->actStartTime;
		out->clevel = in->clevel;

		return out;
	}
};
