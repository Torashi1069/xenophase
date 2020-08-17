struct PROTO_CZ_GUILD_ZENY
{
	short PacketType;
	int zeny;
};


struct PACKET_CZ_GUILD_ZENY
{
	/* this+0 */ short PacketType;
	/* this+2 */ int zeny;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_GUILD_ZENY> in(p);
		TPacket<PROTO_CZ_GUILD_ZENY> out;

		out->PacketType = PacketType;
		out->zeny = in->zeny;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_GUILD_ZENY> in(p);
		TPacket<PACKET_CZ_GUILD_ZENY> out;

		out->PacketType = PacketType;
		out->zeny = in->zeny;

		return out;
	}
};
