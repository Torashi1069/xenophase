struct PROTO_ZC_LONGPAR_CHANGE
{
	short PacketType;
	unsigned short varID;
	int amount;
};


struct PACKET_ZC_LONGPAR_CHANGE
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short varID;
	/* this+4 */ int amount;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_LONGPAR_CHANGE> in(p);
		TPacket<PROTO_ZC_LONGPAR_CHANGE> out;

		out->PacketType = PacketType;
		out->varID = in->varID;
		out->amount = in->amount;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_LONGPAR_CHANGE> in(p);
		TPacket<PACKET_ZC_LONGPAR_CHANGE> out;

		out->PacketType = PacketType;
		out->varID = in->varID;
		out->amount = in->amount;

		return out;
	}
};
