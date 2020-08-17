struct PROTO_CZ_USE_ITEM
{
	short PacketType;
	unsigned short index;
	unsigned long AID;
};


struct PACKET_CZ_USE_ITEM
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short index;
	/* this+4 */ unsigned long AID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_USE_ITEM> in(p);
		TPacket<PROTO_CZ_USE_ITEM> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->AID = in->AID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_USE_ITEM> in(p);
		TPacket<PACKET_CZ_USE_ITEM> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->AID = in->AID;

		return out;
	}
};


struct PACKET_CZ_USE_ITEM2
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short index;
	/* this+4 */ unsigned long AID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_USE_ITEM2> in(p);
		TPacket<PROTO_CZ_USE_ITEM> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->AID = in->AID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_USE_ITEM> in(p);
		TPacket<PACKET_CZ_USE_ITEM2> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->AID = in->AID;

		return out;
	}
};
