struct PROTO_ZC_EXCHANGEITEM_UNDO
{
	short PacketType;
};


struct PACKET_ZC_EXCHANGEITEM_UNDO
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_EXCHANGEITEM_UNDO> in(p);
		TPacket<PROTO_ZC_EXCHANGEITEM_UNDO> out;

		out->PacketType = PacketType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_EXCHANGEITEM_UNDO> in(p);
		TPacket<PACKET_ZC_EXCHANGEITEM_UNDO> out;

		out->PacketType = PacketType;

		return out;
	}
};
