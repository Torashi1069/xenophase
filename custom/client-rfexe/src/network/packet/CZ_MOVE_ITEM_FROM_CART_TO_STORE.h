struct PROTO_CZ_MOVE_ITEM_FROM_CART_TO_STORE
{
	short PacketType;
	short index;
	int count;
};


struct PACKET_CZ_MOVE_ITEM_FROM_CART_TO_STORE
{
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
	/* this+4 */ int count;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_MOVE_ITEM_FROM_CART_TO_STORE> in(p);
		TPacket<PROTO_CZ_MOVE_ITEM_FROM_CART_TO_STORE> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->count = in->count;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_MOVE_ITEM_FROM_CART_TO_STORE> in(p);
		TPacket<PACKET_CZ_MOVE_ITEM_FROM_CART_TO_STORE> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->count = in->count;

		return out;
	}
};
