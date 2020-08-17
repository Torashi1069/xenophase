struct PROTO_CZ_ITEM_PICKUP
{
	short PacketType;
	unsigned long ITAID;
};


struct PACKET_CZ_ITEM_PICKUP
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long ITAID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_ITEM_PICKUP> in(p);
		TPacket<PROTO_CZ_ITEM_PICKUP> out;

		out->PacketType = PacketType;
		out->ITAID = in->ITAID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_ITEM_PICKUP> in(p);
		TPacket<PACKET_CZ_ITEM_PICKUP> out;

		out->PacketType = PacketType;
		out->ITAID = in->ITAID;

		return out;
	}
};


// NOTE: sent by client-kro-2010-06-22aRagexeRE (0x5BE5F1)
struct PACKET_CZ_ITEM_PICKUP__PAD5
{
	/* this+0 */ short PacketType;
	/* this+2 */ char pad[5];
	/* this+7 */ unsigned long ITAID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_ITEM_PICKUP__PAD5> in(p);
		TPacket<PROTO_CZ_ITEM_PICKUP> out;

		out->PacketType = PacketType;
		out->ITAID = in->ITAID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_ITEM_PICKUP> in(p);
		TPacket<PACKET_CZ_ITEM_PICKUP__PAD5> out;

		out->PacketType = PacketType;
		out->ITAID = in->ITAID;
		memset(out->pad, 0, sizeof(out->pad)); // adapt //TODO: generate properly

		return out;
	}
};


struct PACKET_CZ_ITEM_PICKUP2
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long ITAID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_ITEM_PICKUP2> in(p);
		TPacket<PROTO_CZ_ITEM_PICKUP> out;

		out->PacketType = PacketType;
		out->ITAID = in->ITAID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_ITEM_PICKUP> in(p);
		TPacket<PACKET_CZ_ITEM_PICKUP2> out;

		out->PacketType = PacketType;
		out->ITAID = in->ITAID;

		return out;
	}
};
