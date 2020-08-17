struct PROTO_CZ_REQUEST_MOVE
{
	short PacketType;
	unsigned char dest[3];
};


struct PACKET_CZ_REQUEST_MOVE
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char dest[3];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQUEST_MOVE> in(p);
		TPacket<PROTO_CZ_REQUEST_MOVE> out;

		out->PacketType = PacketType;
		memcpy(out->dest, in->dest, 3);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQUEST_MOVE> in(p);
		TPacket<PACKET_CZ_REQUEST_MOVE> out;

		out->PacketType = PacketType;
		memcpy(out->dest, in->dest, 3);

		return out;
	}
};


// NOTE: sent by client-kro-2010-06-22aRagexeRE (0x5BE68A)
struct PACKET_CZ_REQUEST_MOVE__PAD4
{
	/* this+0 */ short PacketType;
	/* this+2 */ char pad[4];
	/* this+6 */ unsigned char dest[3];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQUEST_MOVE__PAD4> in(p);
		TPacket<PROTO_CZ_REQUEST_MOVE> out;

		out->PacketType = PacketType;
		memcpy(out->dest, in->dest, 3);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQUEST_MOVE> in(p);
		TPacket<PACKET_CZ_REQUEST_MOVE__PAD4> out;

		out->PacketType = PacketType;
		memcpy(out->dest, in->dest, 3);
		memset(out->pad, 0, sizeof(out->pad)); // adapt //TODO: generate properly

		return out;
	}
};


struct PACKET_CZ_REQUEST_MOVE2
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char dest[3];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQUEST_MOVE2> in(p);
		TPacket<PROTO_CZ_REQUEST_MOVE> out;

		out->PacketType = PacketType;
		memcpy(out->dest, in->dest, 3);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQUEST_MOVE> in(p);
		TPacket<PACKET_CZ_REQUEST_MOVE2> out;

		out->PacketType = PacketType;
		memcpy(out->dest, in->dest, 3);

		return out;
	}
};
