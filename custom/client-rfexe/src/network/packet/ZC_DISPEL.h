struct PROTO_ZC_DISPEL
{
	short PacketType;
	unsigned long AID;
};


struct PACKET_ZC_DISPEL
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_DISPEL> in(p);
		TPacket<PROTO_ZC_DISPEL> out;

		out->PacketType = PacketType;
		out->AID = in->AID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_DISPEL> in(p);
		TPacket<PACKET_ZC_DISPEL> out;

		out->PacketType = PacketType;
		out->AID = in->AID;

		return out;
	}
};
