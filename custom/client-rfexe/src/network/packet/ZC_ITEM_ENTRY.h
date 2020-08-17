struct PROTO_ZC_ITEM_ENTRY
{
	short PacketType;
	unsigned long ITAID;
	unsigned short ITID;
	bool IsIdentified;
	short xPos;
	short yPos;
	short count;
	unsigned char subX;
	unsigned char subY;
};


struct PACKET_ZC_ITEM_ENTRY
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long ITAID;
	/* this+ 6 */ unsigned short ITID;
	/* this+ 8 */ bool IsIdentified;
	/* this+ 9 */ short xPos;
	/* this+11 */ short yPos;
	/* this+13 */ short count;
	/* this+15 */ unsigned char subX;
	/* this+16 */ unsigned char subY;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ITEM_ENTRY> in(p);
		TPacket<PROTO_ZC_ITEM_ENTRY> out;

		out->PacketType = PacketType;
		out->ITAID = in->ITAID;
		out->ITID = in->ITID;
		out->IsIdentified = in->IsIdentified;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->count = in->count;
		out->subX = in->subX;
		out->subY = in->subY;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ITEM_ENTRY> in(p);
		TPacket<PACKET_ZC_ITEM_ENTRY> out;

		out->PacketType = PacketType;
		out->ITAID = in->ITAID;
		out->ITID = in->ITID;
		out->IsIdentified = in->IsIdentified;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->count = in->count;
		out->subX = in->subX;
		out->subY = in->subY;

		return out;
	}
};
