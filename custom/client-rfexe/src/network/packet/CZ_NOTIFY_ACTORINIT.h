struct PROTO_CZ_NOTIFY_ACTORINIT
{
	short PacketType;
};


struct PACKET_CZ_NOTIFY_ACTORINIT
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_NOTIFY_ACTORINIT> in(p);
		TPacket<PROTO_CZ_NOTIFY_ACTORINIT> out;

		out->PacketType = PacketType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_NOTIFY_ACTORINIT> in(p);
		TPacket<PACKET_CZ_NOTIFY_ACTORINIT> out;

		out->PacketType = PacketType;

		return out;
	}
};
