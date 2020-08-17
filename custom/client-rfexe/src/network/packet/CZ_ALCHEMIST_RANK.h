struct PROTO_CZ_ALCHEMIST_RANK
{
	short PacketType;
};


struct PACKET_CZ_ALCHEMIST_RANK
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_ALCHEMIST_RANK> in(p);
		TPacket<PROTO_CZ_ALCHEMIST_RANK> out;

		out->PacketType = PacketType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_ALCHEMIST_RANK> in(p);
		TPacket<PACKET_CZ_ALCHEMIST_RANK> out;

		out->PacketType = PacketType;

		return out;
	}
};
