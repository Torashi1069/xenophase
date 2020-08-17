struct PROTO_ZC_CONCLUDE_EXCHANGE_ITEM
{
	short PacketType;
	unsigned char who;
};


struct PACKET_ZC_CONCLUDE_EXCHANGE_ITEM
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char who;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_CONCLUDE_EXCHANGE_ITEM> in(p);
		TPacket<PROTO_ZC_CONCLUDE_EXCHANGE_ITEM> out;

		out->PacketType = PacketType;
		out->who = in->who;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_CONCLUDE_EXCHANGE_ITEM> in(p);
		TPacket<PACKET_ZC_CONCLUDE_EXCHANGE_ITEM> out;

		out->PacketType = PacketType;
		out->who = in->who;

		return out;
	}
};
