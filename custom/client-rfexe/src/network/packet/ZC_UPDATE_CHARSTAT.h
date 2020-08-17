struct PROTO_ZC_UPDATE_CHARSTAT
{
	short PacketType;
	int PacketVersion; // 1:basic, 2:w/appearance
	unsigned long AID;
	unsigned long GID;
	int status; // enum GM_STATUS { GM_OFFLINE = 0, GM_ONLINE = 1 };
	short sex;
	short head;
	short headPalette;
};


struct PACKET_ZC_UPDATE_CHARSTAT
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ int status;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_UPDATE_CHARSTAT> in(p);
		TPacket<PROTO_ZC_UPDATE_CHARSTAT> out;

		out->PacketType = PacketType;
		out->PacketVersion = 1;
		out->AID = in->AID;
		out->GID = in->GID;
		out->status = in->status;
		out->sex = 0; // adapt // broken
		out->head = 0; // adapt // broken
		out->headPalette = 0; // adapt // broken

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_UPDATE_CHARSTAT> in(p);
		TPacket<PACKET_ZC_UPDATE_CHARSTAT> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->GID = in->GID;
		out->status = in->status;
//		out->sex = in->sex; // adapt
//		out->head = in->head; // adapt
//		out->headPalette = in->headPalette; // adapt

		return out;
	}
};


struct PACKET_ZC_UPDATE_CHARSTAT2
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ int status;
	/* this+14 */ short sex;
	/* this+16 */ short head;
	/* this+18 */ short headPalette;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_UPDATE_CHARSTAT2> in(p);
		TPacket<PROTO_ZC_UPDATE_CHARSTAT> out;

		out->PacketType = PacketType;
		out->PacketVersion = 2;
		out->AID = in->AID;
		out->GID = in->GID;
		out->status = in->status;
		out->sex = in->sex;
		out->head = in->head;
		out->headPalette = in->headPalette;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_UPDATE_CHARSTAT> in(p);
		if( in->PacketVersion < 2 ) return NULL;
		TPacket<PACKET_ZC_UPDATE_CHARSTAT2> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->GID = in->GID;
		out->status = in->status;
		out->sex = in->sex;
		out->head = in->head;
		out->headPalette = in->headPalette;

		return out;
	}
};
