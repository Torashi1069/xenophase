struct PROTO_ZC_ACK_GIVE_MANNER_POINT
{
	short PacketType;
	unsigned long result;
};


struct PACKET_ZC_ACK_GIVE_MANNER_POINT
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long result;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_GIVE_MANNER_POINT> in(p);
		TPacket<PROTO_ZC_ACK_GIVE_MANNER_POINT> out;

		out->PacketType = PacketType;
		out->result = in->result;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACK_GIVE_MANNER_POINT> in(p);
		TPacket<PACKET_ZC_ACK_GIVE_MANNER_POINT> out;

		out->PacketType = PacketType;
		out->result = in->result;

		return out;
	}
};
