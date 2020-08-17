struct PROTO_ZC_ACCEPT_ENTER
{
	short PacketType;
	unsigned long startTime;
	unsigned char PosDir[3];
	unsigned char xSize;
	unsigned char ySize;
	short font;
};


struct PACKET_ZC_ACCEPT_ENTER
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long startTime;
	/* this+ 6 */ unsigned char PosDir[3];
	/* this+ 9 */ unsigned char xSize;
	/* this+10 */ unsigned char ySize;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACCEPT_ENTER> in(p);
		TPacket<PROTO_ZC_ACCEPT_ENTER> out;

		out->PacketType = PacketType;
		out->startTime = in->startTime;
		memcpy(out->PosDir, in->PosDir, 3);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->font = 0; // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACCEPT_ENTER> in(p);
		TPacket<PACKET_ZC_ACCEPT_ENTER> out;

		out->PacketType = PacketType;
		out->startTime = in->startTime;
		memcpy(out->PosDir, in->PosDir, 3);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
//		out->font = in->font; // adapt

		return out;
	}
};


struct PACKET_ZC_ACCEPT_ENTER2
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long startTime;
	/* this+ 6 */ unsigned char PosDir[3];
	/* this+ 9 */ unsigned char xSize;
	/* this+10 */ unsigned char ySize;
	/* this+11 */ short font;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACCEPT_ENTER2> in(p);
		TPacket<PROTO_ZC_ACCEPT_ENTER> out;

		out->PacketType = PacketType;
		out->startTime = in->startTime;
		memcpy(out->PosDir, in->PosDir, 3);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->font = in->font;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACCEPT_ENTER> in(p);
		TPacket<PACKET_ZC_ACCEPT_ENTER2> out;

		out->PacketType = PacketType;
		out->startTime = in->startTime;
		memcpy(out->PosDir, in->PosDir, 3);
		out->xSize = in->xSize;
		out->ySize = in->ySize;
		out->font = in->font;

		return out;
	}
};
