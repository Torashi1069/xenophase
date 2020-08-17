struct PROTO_ZC_DISAPPEAR_ENTRY
{
	short PacketType;
	unsigned long makerAID;
};


struct PACKET_ZC_DISAPPEAR_ENTRY
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long makerAID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_DISAPPEAR_ENTRY> in(p);
		TPacket<PROTO_ZC_DISAPPEAR_ENTRY> out;

		out->PacketType = PacketType;
		out->makerAID = in->makerAID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_DISAPPEAR_ENTRY> in(p);
		TPacket<PACKET_ZC_DISAPPEAR_ENTRY> out;

		out->PacketType = PacketType;
		out->makerAID = in->makerAID;

		return out;
	}
};
