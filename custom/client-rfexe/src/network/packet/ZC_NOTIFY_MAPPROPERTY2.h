struct PROTO_ZC_NOTIFY_MAPPROPERTY2
{
	short PacketType;
	short type;
};


struct PACKET_ZC_NOTIFY_MAPPROPERTY2
{
	/* this+0 */ short PacketType;
	/* this+2 */ short type;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_MAPPROPERTY2> in(p);
		TPacket<PROTO_ZC_NOTIFY_MAPPROPERTY2> out;

		out->PacketType = PacketType;
		out->type = in->type;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_MAPPROPERTY2> in(p);
		TPacket<PACKET_ZC_NOTIFY_MAPPROPERTY2> out;

		out->PacketType = PacketType;
		out->type = in->type;

		return out;
	}
};
