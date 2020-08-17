struct PROTO_ZC_ACK_MAKE_GROUP
{
	short PacketType;
	unsigned char result;
};


struct PACKET_ZC_ACK_MAKE_GROUP
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char result;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_MAKE_GROUP> in(p);
		TPacket<PROTO_ZC_ACK_MAKE_GROUP> out;

		out->PacketType = PacketType;
		out->result = in->result;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACK_MAKE_GROUP> in(p);
		TPacket<PACKET_ZC_ACK_MAKE_GROUP> out;

		out->PacketType = PacketType;
		out->result = in->result;

		return out;
	}
};
