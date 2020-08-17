struct PROTO_ZC_SPIRITS
{
	short PacketType;
	unsigned long AID;
	short num;
};


struct PACKET_ZC_SPIRITS
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ short num;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_SPIRITS> in(p);
		TPacket<PROTO_ZC_SPIRITS> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->num = in->num;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_SPIRITS> in(p);
		TPacket<PACKET_ZC_SPIRITS> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->num = in->num;

		return out;
	}
};
