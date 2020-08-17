struct PROTO_CZ_MOVE_ITEM_FROM_STORE_TO_BODY
{
	short PacketType;
	short index;
	int count;
};


struct PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY
{
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
	/* this+4 */ int count;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY> in(p);
		TPacket<PROTO_CZ_MOVE_ITEM_FROM_STORE_TO_BODY> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->count = in->count;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_MOVE_ITEM_FROM_STORE_TO_BODY> in(p);
		TPacket<PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->count = in->count;

		return out;
	}
};


// NOTE: sent by client-kro-2010-06-22aRagexeRE (0x5BC328)
struct PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY__PAD1_8
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char pad[1];
	/* this+ 3 */ short index;
	/* this+ 5 */ char pad2[8];
	/* this+13 */ int count;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY__PAD1_8> in(p);
		TPacket<PROTO_CZ_MOVE_ITEM_FROM_STORE_TO_BODY> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->count = in->count;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_MOVE_ITEM_FROM_STORE_TO_BODY> in(p);
		TPacket<PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY__PAD1_8> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->count = in->count;
		memset(out->pad, 0, sizeof(out->pad)); // adapt //TODO: generate properly
		memset(out->pad2, 0, sizeof(out->pad2)); // adapt //TODO: generate properly

		return out;
	}
};


struct PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY2
{
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
	/* this+4 */ int count;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY2> in(p);
		TPacket<PROTO_CZ_MOVE_ITEM_FROM_STORE_TO_BODY> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->count = in->count;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_MOVE_ITEM_FROM_STORE_TO_BODY> in(p);
		TPacket<PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY2> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->count = in->count;

		return out;
	}
};
