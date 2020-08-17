struct PROTO_CZ_RESTART
{
	short PacketType;
	unsigned char type;
};


struct PACKET_CZ_RESTART
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char type;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_RESTART> in(p);
		TPacket<PROTO_CZ_RESTART> out;

		out->PacketType = PacketType;
		out->type = in->type;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_RESTART> in(p);
		TPacket<PACKET_CZ_RESTART> out;

		out->PacketType = PacketType;
		out->type = in->type;

		return out;
	}
};
