struct PROTO_ZC_PC_PURCHASE_RESULT_FROMMC
{
	short PacketType;
	short index;
	short curcount;
	unsigned char result;
};


struct PACKET_ZC_PC_PURCHASE_RESULT_FROMMC
{
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
	/* this+4 */ short curcount;
	/* this+6 */ unsigned char result;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_PC_PURCHASE_RESULT_FROMMC> in(p);
		TPacket<PROTO_ZC_PC_PURCHASE_RESULT_FROMMC> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->curcount = in->curcount;
		out->result = in->result;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_PC_PURCHASE_RESULT_FROMMC> in(p);
		TPacket<PACKET_ZC_PC_PURCHASE_RESULT_FROMMC> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->curcount = in->curcount;
		out->result = in->result;

		return out;
	}
};
