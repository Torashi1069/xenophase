struct PROTO_CZ_EXIT_ROOM
{
	short PacketType;
};


struct PACKET_CZ_EXIT_ROOM
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_EXIT_ROOM> in(p);
		TPacket<PROTO_CZ_EXIT_ROOM> out;

		out->PacketType = PacketType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_EXIT_ROOM> in(p);
		TPacket<PACKET_CZ_EXIT_ROOM> out;

		out->PacketType = PacketType;

		return out;
	}
};
