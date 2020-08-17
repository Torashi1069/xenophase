struct PROTO_CZ_CLOSE_STORE
{
	short PacketType;
};


struct PACKET_CZ_CLOSE_STORE
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_CLOSE_STORE> in(p);
		TPacket<PROTO_CZ_CLOSE_STORE> out;

		out->PacketType = PacketType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_CLOSE_STORE> in(p);
		TPacket<PACKET_CZ_CLOSE_STORE> out;

		out->PacketType = PacketType;

		return out;
	}
};
