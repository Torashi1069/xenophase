struct PROTO_CZ_REQUEST_QUIT
{
	short PacketType;
};


struct PACKET_CZ_REQUEST_QUIT
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQUEST_QUIT> in(p);
		TPacket<PROTO_CZ_REQUEST_QUIT> out;

		out->PacketType = PacketType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQUEST_QUIT> in(p);
		TPacket<PACKET_CZ_REQUEST_QUIT> out;

		out->PacketType = PacketType;

		return out;
	}
};
