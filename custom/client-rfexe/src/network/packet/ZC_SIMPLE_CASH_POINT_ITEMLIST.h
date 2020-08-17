struct PROTO_ZC_SIMPLE_CASH_POINT_ITEMLIST
{
	short PacketType;
	short PacketLength;
	unsigned long CashPoint;
	BYTE unknown[];
};


struct PACKET_ZC_SIMPLE_CASH_POINT_ITEMLIST
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ unsigned long CashPoint;
	/* this+8 */ BYTE unknown[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_SIMPLE_CASH_POINT_ITEMLIST,BYTE> in(p);
		TPacket<PROTO_ZC_SIMPLE_CASH_POINT_ITEMLIST,BYTE> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->CashPoint = in->CashPoint;
		memcpy(out->unknown, in->unknown, out.count());

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_SIMPLE_CASH_POINT_ITEMLIST,BYTE> in(p);
		TPacket<PACKET_ZC_SIMPLE_CASH_POINT_ITEMLIST,BYTE> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->CashPoint = in->CashPoint;
		memcpy(out->unknown, in->unknown, out.count());

		return out;
	}
};
