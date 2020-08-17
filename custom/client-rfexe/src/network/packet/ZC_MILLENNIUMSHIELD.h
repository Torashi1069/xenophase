struct PROTO_ZC_MILLENNIUMSHIELD
{
	short PacketType;
	unsigned long AID;
	short num;
	short state;
};


struct PACKET_ZC_MILLENNIUMSHIELD
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ short num;
	/* this+8 */ short state;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_MILLENNIUMSHIELD> in(p);
		TPacket<PROTO_ZC_MILLENNIUMSHIELD> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->num = in->num;
		out->state = in->state;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_MILLENNIUMSHIELD> in(p);
		TPacket<PACKET_ZC_MILLENNIUMSHIELD> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->num = in->num;
		out->state = in->state;

		return out;
	}
};
