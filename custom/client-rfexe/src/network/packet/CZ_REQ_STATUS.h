struct PROTO_CZ_REQ_STATUS
{
	short PacketType;
};


struct PACKET_CZ_REQ_STATUS
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_STATUS> in(p);
		TPacket<PROTO_CZ_REQ_STATUS> out;

		out->PacketType = PacketType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_STATUS> in(p);
		TPacket<PACKET_CZ_REQ_STATUS> out;

		out->PacketType = PacketType;

		return out;
	}
};
