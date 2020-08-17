struct PROTO_ZC_ITEM_DISAPPEAR
{
	short PacketType;
	unsigned long ITAID;
};


struct PACKET_ZC_ITEM_DISAPPEAR
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long ITAID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ITEM_DISAPPEAR> in(p);
		TPacket<PROTO_ZC_ITEM_DISAPPEAR> out;

		out->PacketType = PacketType;
		out->ITAID = in->ITAID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ITEM_DISAPPEAR> in(p);
		TPacket<PACKET_ZC_ITEM_DISAPPEAR> out;

		out->PacketType = PacketType;
		out->ITAID = in->ITAID;

		return out;
	}
};
