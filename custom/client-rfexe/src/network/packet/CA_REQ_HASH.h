struct PROTO_CA_REQ_HASH
{
	short PacketType;
};


struct PACKET_CA_REQ_HASH
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CA_REQ_HASH> in(p);
		TPacket<PROTO_CA_REQ_HASH> out;

		out->PacketType = PacketType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CA_REQ_HASH> in(p);
		TPacket<PACKET_CA_REQ_HASH> out;

		out->PacketType = PacketType;

		return out;
	}
};
