struct PROTO_SC_BILLING_INFO
{
	short PacketType; // PROTOID_SC_BILLING_INFO
	unsigned long dwAmountRemain;
	unsigned long dwQuantityRemain;
	unsigned long dwReserved1;
	unsigned long dwReserved2;
};


struct PACKET_SC_BILLING_INFO
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long dwAmountRemain;
	/* this+ 6 */ unsigned long dwQuantityRemain;
	/* this+10 */ unsigned long dwReserved1;
	/* this+14 */ unsigned long dwReserved2;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_SC_BILLING_INFO> in(p);
		TPacket<PROTO_SC_BILLING_INFO> out;

		out->PacketType = PacketType;
		out->dwAmountRemain = in->dwAmountRemain;
		out->dwQuantityRemain = in->dwQuantityRemain;
		out->dwReserved1 = in->dwReserved1;
		out->dwReserved2 = in->dwReserved2;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_SC_BILLING_INFO> in(p);
		TPacket<PACKET_SC_BILLING_INFO> out;

		out->PacketType = PacketType;
		out->dwAmountRemain = in->dwAmountRemain;
		out->dwQuantityRemain = in->dwQuantityRemain;
		out->dwReserved1 = in->dwReserved1;
		out->dwReserved2 = in->dwReserved2;

		return out;
	}
};
