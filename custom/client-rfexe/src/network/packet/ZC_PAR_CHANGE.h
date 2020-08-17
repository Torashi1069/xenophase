struct PROTO_ZC_PAR_CHANGE
{
	short PacketType;
	unsigned short varID;
	int count;
};


struct PACKET_ZC_PAR_CHANGE
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short varID;
	/* this+4 */ int count;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_PAR_CHANGE> in(p);
		TPacket<PROTO_ZC_PAR_CHANGE> out;

		out->PacketType = PacketType;
		out->varID = in->varID;
		out->count = in->count;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_PAR_CHANGE> in(p);
		TPacket<PACKET_ZC_PAR_CHANGE> out;

		out->PacketType = PacketType;
		out->varID = in->varID;
		out->count = in->count;

		return out;
	}
};
