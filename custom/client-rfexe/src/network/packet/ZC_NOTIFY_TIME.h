struct PROTO_ZC_NOTIFY_TIME
{
	short PacketType;
	unsigned long time;
};


struct PACKET_ZC_NOTIFY_TIME
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long time;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_TIME> in(p);
		TPacket<PROTO_ZC_NOTIFY_TIME> out;

		out->PacketType = PacketType;
		out->time = in->time;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_TIME> in(p);
		TPacket<PACKET_ZC_NOTIFY_TIME> out;

		out->PacketType = PacketType;
		out->time = in->time;

		return out;
	}
};
