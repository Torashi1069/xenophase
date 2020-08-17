struct PROTO_CZ_REQ_CLOSESTORE
{
	short PacketType;
};


struct PACKET_CZ_REQ_CLOSESTORE
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_CLOSESTORE> in(p);
		TPacket<PROTO_CZ_REQ_CLOSESTORE> out;

		out->PacketType = PacketType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_CLOSESTORE> in(p);
		TPacket<PACKET_CZ_REQ_CLOSESTORE> out;

		out->PacketType = PacketType;

		return out;
	}
};
