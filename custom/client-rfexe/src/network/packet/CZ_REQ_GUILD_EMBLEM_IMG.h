struct PROTO_CZ_REQ_GUILD_EMBLEM_IMG
{
	short PacketType;
	int GDID;
};


struct PACKET_CZ_REQ_GUILD_EMBLEM_IMG
{
	/* this+0 */ short PacketType;
	/* this+2 */ int GDID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_GUILD_EMBLEM_IMG> in(p);
		TPacket<PROTO_CZ_REQ_GUILD_EMBLEM_IMG> out;

		out->PacketType = PacketType;
		out->GDID = in->GDID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_GUILD_EMBLEM_IMG> in(p);
		TPacket<PACKET_CZ_REQ_GUILD_EMBLEM_IMG> out;

		out->PacketType = PacketType;
		out->GDID = in->GDID;

		return out;
	}
};
