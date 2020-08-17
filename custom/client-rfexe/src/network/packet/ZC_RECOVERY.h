struct PROTO_ZC_RECOVERY
{
	short PacketType;
	short varID;
	short amount;
};


struct PACKET_ZC_RECOVERY
{
	/* this+0 */ short PacketType;
	/* this+2 */ short varID;
	/* this+4 */ short amount;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_RECOVERY> in(p);
		TPacket<PROTO_ZC_RECOVERY> out;

		out->PacketType = PacketType;
		out->varID = in->varID;
		out->amount = in->amount;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_RECOVERY> in(p);
		TPacket<PACKET_ZC_RECOVERY> out;

		out->PacketType = PacketType;
		out->varID = in->varID;
		out->amount = in->amount;

		return out;
	}
};
