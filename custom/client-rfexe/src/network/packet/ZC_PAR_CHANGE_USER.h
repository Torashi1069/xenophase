struct PROTO_ZC_PAR_CHANGE_USER
{
	short PacketType;
	unsigned long AID;
	unsigned short varID;
	int count;
};


struct PACKET_ZC_PAR_CHANGE_USER
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ unsigned short varID;
	/* this+8 */ int count;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_PAR_CHANGE_USER> in(p);
		TPacket<PROTO_ZC_PAR_CHANGE_USER> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->varID = in->varID;
		out->count = in->count;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_PAR_CHANGE_USER> in(p);
		TPacket<PACKET_ZC_PAR_CHANGE_USER> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->varID = in->varID;
		out->count = in->count;

		return out;
	}
};
