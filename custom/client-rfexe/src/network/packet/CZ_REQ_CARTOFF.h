struct PROTO_CZ_REQ_CARTOFF
{
	short PacketType;
};


struct PACKET_CZ_REQ_CARTOFF
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_CARTOFF> in(p);
		TPacket<PROTO_CZ_REQ_CARTOFF> out;

		out->PacketType = PacketType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_CARTOFF> in(p);
		TPacket<PACKET_CZ_REQ_CARTOFF> out;

		out->PacketType = PacketType;

		return out;
	}
};
