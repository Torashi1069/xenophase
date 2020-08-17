struct PROTO_CZ_CLOSE_WINDOW
{
	short PacketType;
};


struct PACKET_CZ_CLOSE_WINDOW
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_CLOSE_WINDOW> in(p);
		TPacket<PROTO_CZ_CLOSE_WINDOW> out;

		out->PacketType = PacketType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_CLOSE_WINDOW> in(p);
		TPacket<PACKET_CZ_CLOSE_WINDOW> out;

		out->PacketType = PacketType;

		return out;
	}
};
