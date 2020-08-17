struct PROTO_CZ_REQ_LEAVE_GROUP
{
	short PacketType;
};


struct PACKET_CZ_REQ_LEAVE_GROUP
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_LEAVE_GROUP> in(p);
		TPacket<PROTO_CZ_REQ_LEAVE_GROUP> out;

		out->PacketType = PacketType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_LEAVE_GROUP> in(p);
		TPacket<PACKET_CZ_REQ_LEAVE_GROUP> out;

		out->PacketType = PacketType;

		return out;
	}
};
