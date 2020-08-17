struct PROTO_ZC_CANCEL_EXCHANGE_ITEM
{
	short PacketType;
};


struct PACKET_ZC_CANCEL_EXCHANGE_ITEM
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_CANCEL_EXCHANGE_ITEM> in(p);
		TPacket<PROTO_ZC_CANCEL_EXCHANGE_ITEM> out;

		out->PacketType = PacketType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_CANCEL_EXCHANGE_ITEM> in(p);
		TPacket<PACKET_ZC_CANCEL_EXCHANGE_ITEM> out;

		out->PacketType = PacketType;

		return out;
	}
};
