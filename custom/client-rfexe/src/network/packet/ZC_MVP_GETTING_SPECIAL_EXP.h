struct PROTO_ZC_MVP_GETTING_SPECIAL_EXP
{
	short PacketType;
	unsigned long exp;
};


struct PACKET_ZC_MVP_GETTING_SPECIAL_EXP
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long exp;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_MVP_GETTING_SPECIAL_EXP> in(p);
		TPacket<PROTO_ZC_MVP_GETTING_SPECIAL_EXP> out;

		out->PacketType = PacketType;
		out->exp = in->exp;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_MVP_GETTING_SPECIAL_EXP> in(p);
		TPacket<PACKET_ZC_MVP_GETTING_SPECIAL_EXP> out;

		out->PacketType = PacketType;
		out->exp = in->exp;

		return out;
	}
};
