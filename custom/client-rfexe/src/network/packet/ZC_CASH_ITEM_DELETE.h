struct PROTO_ZC_CASH_ITEM_DELETE
{
	short PacketType;
	short index;
	unsigned short ITID;
};


struct PACKET_ZC_CASH_ITEM_DELETE
{
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
	/* this+4 */ unsigned short ITID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_CASH_ITEM_DELETE> in(p);
		TPacket<PROTO_ZC_CASH_ITEM_DELETE> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->ITID = in->ITID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_CASH_ITEM_DELETE> in(p);
		TPacket<PACKET_ZC_CASH_ITEM_DELETE> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->ITID = in->ITID;

		return out;
	}
};
