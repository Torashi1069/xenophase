struct PROTO_ZC_NOTIFY_UPDATEPLAYER
{
	short PacketType;
	short Style;
	unsigned char Item;
};


struct PACKET_ZC_NOTIFY_UPDATEPLAYER
{
	/* this+0 */ short PacketType;
	/* this+2 */ short Style;
	/* this+4 */ unsigned char Item;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_UPDATEPLAYER> in(p);
		TPacket<PROTO_ZC_NOTIFY_UPDATEPLAYER> out;

		out->PacketType = PacketType;
		out->Style = in->Style;
		out->Item = in->Item;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_UPDATEPLAYER> in(p);
		TPacket<PACKET_ZC_NOTIFY_UPDATEPLAYER> out;

		out->PacketType = PacketType;
		out->Style = in->Style;
		out->Item = in->Item;

		return out;
	}
};
