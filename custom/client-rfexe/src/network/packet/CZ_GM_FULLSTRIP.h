struct PROTO_CZ_GM_FULLSTRIP
{
	short PacketType;
	unsigned long TargetAID;
};


struct PACKET_CZ_GM_FULLSTRIP
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long TargetAID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_GM_FULLSTRIP> in(p);
		TPacket<PROTO_CZ_GM_FULLSTRIP> out;

		out->PacketType = PacketType;
		out->TargetAID = in->TargetAID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_GM_FULLSTRIP> in(p);
		TPacket<PACKET_CZ_GM_FULLSTRIP> out;

		out->PacketType = PacketType;
		out->TargetAID = in->TargetAID;

		return out;
	}
};
