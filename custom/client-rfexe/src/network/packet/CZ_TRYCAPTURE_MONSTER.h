struct PROTO_CZ_TRYCAPTURE_MONSTER
{
	short PacketType;
	unsigned long targetAID;
};


struct PACKET_CZ_TRYCAPTURE_MONSTER
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long targetAID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_TRYCAPTURE_MONSTER> in(p);
		TPacket<PROTO_CZ_TRYCAPTURE_MONSTER> out;

		out->PacketType = PacketType;
		out->targetAID = in->targetAID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_TRYCAPTURE_MONSTER> in(p);
		TPacket<PACKET_CZ_TRYCAPTURE_MONSTER> out;

		out->PacketType = PacketType;
		out->targetAID = in->targetAID;

		return out;
	}
};
