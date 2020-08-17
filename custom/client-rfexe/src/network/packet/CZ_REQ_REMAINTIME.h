struct PROTO_CZ_REQ_REMAINTIME
{
	short PacketType;
};


struct PACKET_CZ_REQ_REMAINTIME
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_REMAINTIME> in(p);
		TPacket<PROTO_CZ_REQ_REMAINTIME> out;

		out->PacketType = PacketType;
		
		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_REMAINTIME> in(p);
		TPacket<PACKET_CZ_REQ_REMAINTIME> out;

		out->PacketType = PacketType;

		return out;
	}
};
