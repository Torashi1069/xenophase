struct PROTO_ZC_COMPASS
{
	short PacketType;
	unsigned long NAID;
	int type;
	int xPos;
	int yPos;
	unsigned char id;
	unsigned long color;
};


struct PACKET_ZC_COMPASS
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long NAID;
	/* this+ 6 */ int type;
	/* this+10 */ int xPos;
	/* this+14 */ int yPos;
	/* this+18 */ unsigned char id;
	/* this+19 */ unsigned long color;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_COMPASS> in(p);
		TPacket<PROTO_ZC_COMPASS> out;

		out->PacketType = PacketType;
		out->NAID = in->NAID;
		out->type = in->type;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->id = in->id;
		out->color = in->color;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_COMPASS> in(p);
		TPacket<PACKET_ZC_COMPASS> out;

		out->PacketType = PacketType;
		out->NAID = in->NAID;
		out->type = in->type;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->id = in->id;
		out->color = in->color;

		return out;
	}
};
