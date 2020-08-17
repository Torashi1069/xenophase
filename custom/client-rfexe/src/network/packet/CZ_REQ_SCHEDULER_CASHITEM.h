struct PROTO_CZ_REQ_SCHEDULER_CASHITEM
{
	short PacketType;
};


struct PACKET_CZ_REQ_SCHEDULER_CASHITEM
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_SCHEDULER_CASHITEM> in(p);
		TPacket<PROTO_CZ_REQ_SCHEDULER_CASHITEM> out;

		out->PacketType = PacketType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_SCHEDULER_CASHITEM> in(p);
		TPacket<PACKET_CZ_REQ_SCHEDULER_CASHITEM> out;

		out->PacketType = PacketType;

		return out;
	}
};
