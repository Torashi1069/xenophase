struct PROTO_CZ_JOIN_GUILD
{
	short PacketType;
	unsigned long GDID;
	int answer;
};


struct PACKET_CZ_JOIN_GUILD
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GDID;
	/* this+6 */ int answer;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_JOIN_GUILD> in(p);
		TPacket<PROTO_CZ_JOIN_GUILD> out;

		out->PacketType = PacketType;
		out->GDID = in->GDID;
		out->answer = in->answer;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_JOIN_GUILD> in(p);
		TPacket<PACKET_CZ_JOIN_GUILD> out;

		out->PacketType = PacketType;
		out->GDID = in->GDID;
		out->answer = in->answer;

		return out;
	}
};
