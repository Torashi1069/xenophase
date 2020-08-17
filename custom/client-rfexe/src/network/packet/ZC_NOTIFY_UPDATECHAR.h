struct PROTO_ZC_NOTIFY_UPDATECHAR
{
	short PacketType;
	unsigned long GID;
	short Style;
	unsigned char Item;
};


struct PACKET_ZC_NOTIFY_UPDATECHAR
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ short Style;
	/* this+8 */ unsigned char Item;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_UPDATECHAR> in(p);
		TPacket<PROTO_ZC_NOTIFY_UPDATECHAR> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		out->Style = in->Style;
		out->Item = in->Item;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_UPDATECHAR> in(p);
		TPacket<PACKET_ZC_NOTIFY_UPDATECHAR> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		out->Style = in->Style;
		out->Item = in->Item;

		return out;
	}
};
