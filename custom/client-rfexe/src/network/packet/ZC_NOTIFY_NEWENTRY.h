struct PROTO_ZC_NOTIFY_NEWENTRY
{
	short PacketType;
	short PacketLength;
	unsigned char objecttype;
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
	short clevel;
	short font;
	char CName[];
};


struct PACKET_ZC_NOTIFY_NEWENTRY
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
	/* this+51 */ short clevel;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_NEWENTRY> in(p);
		TPacket<PROTO_ZC_NOTIFY_NEWENTRY,char> out((size_t)0);

		out->PacketType = PacketType;
		out->PacketLength = out.size(); // adapt
		out->objecttype = 0; // CLIENTTYPE::PC_TYPE // adapt //FIXME: temporary workaround
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
		TPacket<PROTO_ZC_NOTIFY_NEWENTRY,char> in(p);
		TPacket<PACKET_ZC_NOTIFY_NEWENTRY> out;

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


struct PACKET_ZC_NOTIFY_NEWENTRY2
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
	/* this+51 */ short clevel;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_NEWENTRY2> in(p);
		TPacket<PROTO_ZC_NOTIFY_NEWENTRY,char> out((size_t)0);

		out->PacketType = PacketType;
		out->PacketLength = out.size(); // adapt
		out->objecttype = 0; // CLIENTTYPE::PC_TYPE // adapt //FIXME: temporary workaround
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
		out->clevel = in->clevel;
		out->font = 0; // adapt
		memset(out->CName, 0, out.count()); // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_NEWENTRY,char> in(p);
		TPacket<PACKET_ZC_NOTIFY_NEWENTRY2> out;

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
		out->clevel = in->clevel;
//		out->font = in->font; // adapt
//		memcpy(out->CName, in->CName, out.count()); // adapt

		return out;
	}
};


struct PACKET_ZC_NOTIFY_NEWENTRY3
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
	/* this+55 */ short clevel;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_NEWENTRY3> in(p);
		TPacket<PROTO_ZC_NOTIFY_NEWENTRY,char> out((size_t)0);

		out->PacketType = PacketType;
		out->PacketLength = out.size(); // adapt
		out->objecttype = 0; // CLIENTTYPE::PC_TYPE // adapt //FIXME: temporary workaround
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
		out->clevel = in->clevel;
		out->font = 0; // adapt
		memset(out->CName, 0, out.count()); // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_NEWENTRY,char> in(p);
		TPacket<PACKET_ZC_NOTIFY_NEWENTRY3> out;

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
		out->clevel = in->clevel;
//		out->font = in->font; // adapt
//		memcpy(out->CName, in->CName, out.count()); // adapt

		return out;
	}
};


struct PACKET_ZC_NOTIFY_NEWENTRY4
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
	/* this+55 */ short clevel;
	/* this+57 */ short font;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_NEWENTRY4> in(p);
		TPacket<PROTO_ZC_NOTIFY_NEWENTRY,char> out((size_t)0);

		out->PacketType = PacketType;
		out->PacketLength = out.size(); // adapt
		out->objecttype = 0; // CLIENTTYPE::PC_TYPE // adapt //FIXME: temporary workaround
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
		out->clevel = in->clevel;
		out->font = in->font;
		memset(out->CName, 0, out.count()); // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_NEWENTRY,char> in(p);
		TPacket<PACKET_ZC_NOTIFY_NEWENTRY4> out;

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
		out->clevel = in->clevel;
		out->font = in->font;
//		memcpy(out->CName, in->CName, out.count()); // adapt

		return out;
	}
};


struct PACKET_ZC_NOTIFY_NEWENTRY5
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
	/* this+58 */ short clevel;
	/* this+60 */ short font;
	/* this+62 */ char CName[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_NEWENTRY5,char> in(p);
		TPacket<PROTO_ZC_NOTIFY_NEWENTRY,char> out(in.count());

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
		out->clevel = in->clevel;
		out->font = in->font;
		memcpy(out->CName, in->CName, out.count());

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_NEWENTRY,char> in(p);
		TPacket<PACKET_ZC_NOTIFY_NEWENTRY5,char> out(in.count());

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
		out->clevel = in->clevel;
		out->font = in->font;
		memcpy(out->CName, in->CName, out.count());

		return out;
	}
};


struct PACKET_ZC_NOTIFY_NEWENTRY6
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
	/* this+60 */ short clevel;
	/* this+62 */ short font;
	/* this+64 */ char CName[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_NEWENTRY6,char> in(p);
		TPacket<PROTO_ZC_NOTIFY_NEWENTRY,char> out(in.count());

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
		out->clevel = in->clevel;
		out->font = in->font;
		memcpy(out->CName, in->CName, out.count());

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_NEWENTRY,char> in(p);
		TPacket<PACKET_ZC_NOTIFY_NEWENTRY6,char> out(in.count());

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
		out->clevel = in->clevel;
		out->font = in->font;
		memcpy(out->CName, in->CName, out.count());

		return out;
	}
};


//TODO
struct PACKET_ZC_NOTIFY_NEWENTRY7
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
	/* this+60 */ short clevel;
	/* this+62 */ short font;
	/* this+64 */ int maxHP;
	/* this+68 */ int HP;
	/* this+72 */ unsigned char isBoss;
	/* this+73 */ char CName[]; // guessed
};
