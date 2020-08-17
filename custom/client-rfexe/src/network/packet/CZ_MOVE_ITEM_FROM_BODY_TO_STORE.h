struct PROTO_CZ_MOVE_ITEM_FROM_BODY_TO_STORE
{
	short PacketType;
	short index;
	int count;
};


struct PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE
{
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
	/* this+4 */ int count;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE> in(p);
		TPacket<PROTO_CZ_MOVE_ITEM_FROM_BODY_TO_STORE> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->count = in->count;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_MOVE_ITEM_FROM_BODY_TO_STORE> in(p);
		TPacket<PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->count = in->count;

		return out;
	}
};


// NOTE: sent by client-kro-2010-06-22aRagexeRE (0x5BC2C3)
struct PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE__PAD1_10
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char pad[1];
	/* this+ 3 */ short index;
	/* this+ 5 */ char pad2[10];
	/* this+15 */ int count;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE__PAD1_10> in(p);
		TPacket<PROTO_CZ_MOVE_ITEM_FROM_BODY_TO_STORE> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->count = in->count;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_MOVE_ITEM_FROM_BODY_TO_STORE> in(p);
		TPacket<PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE__PAD1_10> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->count = in->count;

		return out;
	}
};


struct PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE2
{
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
	/* this+4 */ int count;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE2> in(p);
		TPacket<PROTO_CZ_MOVE_ITEM_FROM_BODY_TO_STORE> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->count = in->count;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_MOVE_ITEM_FROM_BODY_TO_STORE> in(p);
		TPacket<PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE2> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->count = in->count;

		return out;
	}
};
