struct PROTO_CZ_SELECTAUTOSPELL
{
	short PacketType;
	int SKID;
};


struct PACKET_CZ_SELECTAUTOSPELL
{
	/* this+0 */ short PacketType;
	/* this+2 */ int SKID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_SELECTAUTOSPELL> in(p);
		TPacket<PROTO_CZ_SELECTAUTOSPELL> out;

		out->PacketType = PacketType;
		out->SKID = in->SKID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_SELECTAUTOSPELL> in(p);
		TPacket<PACKET_CZ_SELECTAUTOSPELL> out;

		out->PacketType = PacketType;
		out->SKID = in->SKID;

		return out;
	}
};
