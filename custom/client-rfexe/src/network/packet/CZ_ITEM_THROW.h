struct PROTO_CZ_ITEM_THROW
{
	short PacketType;
	unsigned short Index;
	short count;
};


struct PACKET_CZ_ITEM_THROW
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short Index;
	/* this+4 */ short count;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_ITEM_THROW> in(p);
		TPacket<PROTO_CZ_ITEM_THROW> out;

		out->PacketType = PacketType;
		out->Index = in->Index;
		out->count = in->count;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_ITEM_THROW> in(p);
		TPacket<PACKET_CZ_ITEM_THROW> out;

		out->PacketType = PacketType;
		out->Index = in->Index;
		out->count = in->count;

		return out;
	}
};


// NOTE: sent by client-kro-2010-06-22aRagexeRE (0x5BA207)
struct PACKET_CZ_ITEM_THROW__PAD4_7
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char pad[4];
	/* this+ 6 */ unsigned short Index;
	/* this+ 8 */ char pad2[7];
	/* this+15 */ short count;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_ITEM_THROW__PAD4_7> in(p);
		TPacket<PROTO_CZ_ITEM_THROW> out;

		out->PacketType = PacketType;
		out->Index = in->Index;
		out->count = in->count;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_ITEM_THROW> in(p);
		TPacket<PACKET_CZ_ITEM_THROW__PAD4_7> out;

		out->PacketType = PacketType;
		out->Index = in->Index;
		out->count = in->count;
		memset(out->pad, 0, sizeof(out->pad)); // adapt //TODO: generate properly
		memset(out->pad2, 0, sizeof(out->pad2)); // adapt //TODO: generate properly

		return out;
	}
};


struct PACKET_CZ_ITEM_THROW2
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short Index;
	/* this+4 */ short count;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_ITEM_THROW2> in(p);
		TPacket<PROTO_CZ_ITEM_THROW> out;

		out->PacketType = PacketType;
		out->Index = in->Index;
		out->count = in->count;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_ITEM_THROW> in(p);
		TPacket<PACKET_CZ_ITEM_THROW2> out;

		out->PacketType = PacketType;
		out->Index = in->Index;
		out->count = in->count;

		return out;
	}
};
