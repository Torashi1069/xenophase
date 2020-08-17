struct PROTO_CZ_SIMPLE_BUY_CASH_POINT_ITEM
{
	short PacketType;
	unsigned short ITID;
	short count;
};


struct PACKET_CZ_SIMPLE_BUY_CASH_POINT_ITEM
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short ITID;
	/* this+4 */ short count;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_SIMPLE_BUY_CASH_POINT_ITEM> in(p);
		TPacket<PROTO_CZ_SIMPLE_BUY_CASH_POINT_ITEM> out;

		out->PacketType = PacketType;
		out->ITID = in->ITID;
		out->count = in->count;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_SIMPLE_BUY_CASH_POINT_ITEM> in(p);
		TPacket<PACKET_CZ_SIMPLE_BUY_CASH_POINT_ITEM> out;

		out->PacketType = PacketType;
		out->ITID = in->ITID;
		out->count = in->count;

		return out;
	}
};
