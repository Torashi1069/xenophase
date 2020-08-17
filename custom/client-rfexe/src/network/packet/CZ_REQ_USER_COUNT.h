struct PROTO_CZ_REQ_USER_COUNT
{
	short PacketType;
};


struct PACKET_CZ_REQ_USER_COUNT
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_USER_COUNT> in(p);
		TPacket<PROTO_CZ_REQ_USER_COUNT> out;

		out->PacketType = PacketType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_USER_COUNT> in(p);
		TPacket<PACKET_CZ_REQ_USER_COUNT> out;

		out->PacketType = PacketType;

		return out;
	}
};
