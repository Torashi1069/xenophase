struct PROTO_ZC_NOTIFY_MAPINFO
{
	short PacketType;
	short type;
};


struct PACKET_ZC_NOTIFY_MAPINFO
{
	/* this+0 */ short PacketType;
	/* this+2 */ short type;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_MAPINFO> in(p);
		TPacket<PROTO_ZC_NOTIFY_MAPINFO> out;

		out->PacketType = PacketType;
		out->type = in->type;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_MAPINFO> in(p);
		TPacket<PACKET_ZC_NOTIFY_MAPINFO> out;

		out->PacketType = PacketType;
		out->type = in->type;

		return out;
	}
};
