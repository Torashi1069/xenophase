struct PROTO_ZC_GANGSI_POINT
{
	short PacketType;
	int Point;
	int TotalPoint;
	short PacketSwitch;
};


struct PACKET_ZC_GANGSI_POINT
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ int Point;
	/* this+ 6 */ int TotalPoint;
	/* this+10 */ short PacketSwitch;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_GANGSI_POINT> in(p);
		TPacket<PROTO_ZC_GANGSI_POINT> out;

		out->PacketType = PacketType;
		out->Point = in->Point;
		out->TotalPoint = in->TotalPoint;
		out->PacketSwitch = in->PacketSwitch;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_GANGSI_POINT> in(p);
		TPacket<PACKET_ZC_GANGSI_POINT> out;

		out->PacketType = PacketType;
		out->Point = in->Point;
		out->TotalPoint = in->TotalPoint;
		out->PacketSwitch = in->PacketSwitch;

		return out;
	}
};
