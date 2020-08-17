struct PROTO_CZ_CHANGE_DIRECTION
{
	short PacketType;
	short headDir;
	unsigned char dir;
};


struct PACKET_CZ_CHANGE_DIRECTION
{
	/* this+0 */ short PacketType;
	/* this+2 */ short headDir;
	/* this+4 */ unsigned char dir;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_CHANGE_DIRECTION> in(p);
		TPacket<PROTO_CZ_CHANGE_DIRECTION> out;

		out->PacketType = PacketType;
		out->headDir = in->headDir;
		out->dir = in->dir;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_CHANGE_DIRECTION> in(p);
		TPacket<PACKET_CZ_CHANGE_DIRECTION> out;

		out->PacketType = PacketType;
		out->headDir = in->headDir;
		out->dir = in->dir;

		return out;
	}
};


// NOTE: sent by client-kro-2010-06-22aRagexeRE (0x5BE6EA)
struct PACKET_CZ_CHANGE_DIRECTION__PAD2_3
{
	/* this+0 */ short PacketType;
	/* this+2 */ char pad[2];
	/* this+4 */ short headDir;
	/* this+6 */ char pad2[3];
	/* this+9 */ unsigned char dir;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_CHANGE_DIRECTION__PAD2_3> in(p);
		TPacket<PROTO_CZ_CHANGE_DIRECTION> out;

		out->PacketType = PacketType;
		out->headDir = in->headDir;
		out->dir = in->dir;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_CHANGE_DIRECTION> in(p);
		TPacket<PACKET_CZ_CHANGE_DIRECTION__PAD2_3> out;

		out->PacketType = PacketType;
		out->headDir = in->headDir;
		out->dir = in->dir;
		memset(out->pad, 0, sizeof(out->pad)); // adapt //TODO: generate properly
		memset(out->pad2, 0, sizeof(out->pad2)); // adapt //TODO: generate properly

		return out;
	}
};


struct PACKET_CZ_CHANGE_DIRECTION2
{
	/* this+0 */ short PacketType;
	/* this+2 */ short headDir;
	/* this+4 */ unsigned char dir;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_CHANGE_DIRECTION2> in(p);
		TPacket<PROTO_CZ_CHANGE_DIRECTION> out;

		out->PacketType = PacketType;
		out->headDir = in->headDir;
		out->dir = in->dir;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_CHANGE_DIRECTION> in(p);
		TPacket<PACKET_CZ_CHANGE_DIRECTION2> out;

		out->PacketType = PacketType;
		out->headDir = in->headDir;
		out->dir = in->dir;

		return out;
	}
};
