struct PROTO_CZ_OPEN_SIMPLE_CASHSHOP_ITEMLIST
{
	short PacketType;
};


struct PACKET_CZ_OPEN_SIMPLE_CASHSHOP_ITEMLIST
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_OPEN_SIMPLE_CASHSHOP_ITEMLIST> in(p);
		TPacket<PROTO_CZ_OPEN_SIMPLE_CASHSHOP_ITEMLIST> out;

		out->PacketType = PacketType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_OPEN_SIMPLE_CASHSHOP_ITEMLIST> in(p);
		TPacket<PACKET_CZ_OPEN_SIMPLE_CASHSHOP_ITEMLIST> out;

		out->PacketType = PacketType;

		return out;
	}
};
