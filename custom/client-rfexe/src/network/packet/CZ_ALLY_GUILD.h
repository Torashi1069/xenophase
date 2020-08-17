struct PROTO_CZ_ALLY_GUILD
{
	short PacketType;
	unsigned long otherAID;
	int answer;
};


struct PACKET_CZ_ALLY_GUILD
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long otherAID;
	/* this+6 */ int answer;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_ALLY_GUILD> in(p);
		TPacket<PROTO_CZ_ALLY_GUILD> out;

		out->PacketType = PacketType;
		out->otherAID = in->otherAID;
		out->answer = in->answer;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_ALLY_GUILD> in(p);
		TPacket<PACKET_CZ_ALLY_GUILD> out;

		out->PacketType = PacketType;
		out->otherAID = in->otherAID;
		out->answer = in->answer;

		return out;
	}
};
