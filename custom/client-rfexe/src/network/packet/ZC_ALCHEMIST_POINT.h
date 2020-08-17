struct PROTO_ZC_ALCHEMIST_POINT
{
	short PacketType;
	int Point;
	int TotalPoint;
};


struct PACKET_ZC_ALCHEMIST_POINT
{
	/* this+0 */ short PacketType;
	/* this+2 */ int Point;
	/* this+6 */ int TotalPoint;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ALCHEMIST_POINT> in(p);
		TPacket<PROTO_ZC_ALCHEMIST_POINT> out;

		out->PacketType = PacketType;
		out->Point = in->Point;
		out->TotalPoint = in->TotalPoint;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ALCHEMIST_POINT> in(p);
		TPacket<PACKET_ZC_ALCHEMIST_POINT> out;

		out->PacketType = PacketType;
		out->Point = in->Point;
		out->TotalPoint = in->TotalPoint;

		return out;
	}
};
