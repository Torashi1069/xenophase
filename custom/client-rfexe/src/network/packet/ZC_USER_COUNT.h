struct PROTO_ZC_USER_COUNT
{
	short PacketType;
	int count;
};


struct PACKET_ZC_USER_COUNT
{
	/* this+0 */ short PacketType;
	/* this+2 */ int count;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_USER_COUNT> in(p);
		TPacket<PROTO_ZC_USER_COUNT> out;

		out->PacketType = PacketType;
		out->count = in->count;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_USER_COUNT> in(p);
		TPacket<PACKET_ZC_USER_COUNT> out;

		out->PacketType = PacketType;
		out->count = in->count;

		return out;
	}
};
