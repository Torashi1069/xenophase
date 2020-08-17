struct PROTO_ZC_CASH_TIME_COUNTER
{
	short PacketType;
	unsigned short ITID;
	unsigned long RemainSecond;
};


struct PACKET_ZC_CASH_TIME_COUNTER
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short ITID;
	/* this+4 */ unsigned long RemainSecond;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_CASH_TIME_COUNTER> in(p);
		TPacket<PROTO_ZC_CASH_TIME_COUNTER> out;

		out->PacketType = PacketType;
		out->ITID = in->ITID;
		out->RemainSecond = in->RemainSecond;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_CASH_TIME_COUNTER> in(p);
		TPacket<PACKET_ZC_CASH_TIME_COUNTER> out;

		out->PacketType = PacketType;
		out->ITID = in->ITID;
		out->RemainSecond = in->RemainSecond;

		return out;
	}
};
