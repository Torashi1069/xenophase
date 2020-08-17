struct PROTO_ZC_USE_ITEM_ACK
{
	short PacketType;
	int PacketVersion; // 1:basic, 2:w/IDs
	unsigned short index;
	unsigned short id;
	unsigned long AID;
	short count;
	bool result;
};


struct PACKET_ZC_USE_ITEM_ACK
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short index;
	/* this+4 */ short count;
	/* this+6 */ bool result;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_USE_ITEM_ACK> in(p);
		TPacket<PROTO_ZC_USE_ITEM_ACK> out;

		out->PacketType = PacketType;
		out->PacketVersion = 1;
		out->index = in->index;
		out->id = 0; // adapt // broken
		out->AID = 0; // adapt // broken
		out->count = in->count;
		out->result = in->result;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_USE_ITEM_ACK> in(p);
		TPacket<PACKET_ZC_USE_ITEM_ACK> out;

		out->PacketType = PacketType;
		out->index = in->index;
//		out->id = in->id;
//		out->AID = in->AID;
		out->count = in->count;
		out->result = in->result;

		return out;
	}
};


struct PACKET_ZC_USE_ITEM_ACK2
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short index;
	/* this+ 4 */ unsigned short id;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ short count;
	/* this+12 */ bool result;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_USE_ITEM_ACK2> in(p);
		TPacket<PROTO_ZC_USE_ITEM_ACK> out;

		out->PacketType = PacketType;
		out->PacketVersion = 2;
		out->index = in->index;
		out->id = in->id;
		out->AID = in->AID;
		out->count = in->count;
		out->result = in->result;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_USE_ITEM_ACK> in(p);
		if( in->PacketVersion < 2 ) return NULL;
		TPacket<PACKET_ZC_USE_ITEM_ACK2> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->id = in->id;
		out->AID = in->AID;
		out->count = in->count;
		out->result = in->result;

		return out;
	}
};
