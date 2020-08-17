struct PROTO_CZ_RESET
{
	short PacketType;
	short type;
};


struct PACKET_CZ_RESET
{
	/* this+0 */ short PacketType;
	/* this+2 */ short type;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_RESET> in(p);
		TPacket<PROTO_CZ_RESET> out;

		out->PacketType = PacketType;
		out->type = in->type;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_RESET> in(p);
		TPacket<PACKET_CZ_RESET> out;

		out->PacketType = PacketType;
		out->type = in->type;

		return out;
	}
};
