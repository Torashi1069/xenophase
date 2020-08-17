struct PROTO_ZC_COUPLESTATUS
{
	short PacketType;
	unsigned long statusType;
	int defaultStatus;
	int plusStatus;
};


struct PACKET_ZC_COUPLESTATUS
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long statusType;
	/* this+ 6 */ int defaultStatus;
	/* this+10 */ int plusStatus;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_COUPLESTATUS> in(p);
		TPacket<PROTO_ZC_COUPLESTATUS> out;

		out->PacketType = PacketType;
		out->statusType = in->statusType;
		out->defaultStatus = in->defaultStatus;
		out->plusStatus = in->plusStatus;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_COUPLESTATUS> in(p);
		TPacket<PACKET_ZC_COUPLESTATUS> out;

		out->PacketType = PacketType;
		out->statusType = in->statusType;
		out->defaultStatus = in->defaultStatus;
		out->plusStatus = in->plusStatus;

		return out;
	}
};
