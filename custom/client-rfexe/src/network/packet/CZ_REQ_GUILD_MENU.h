struct PROTO_CZ_REQ_GUILD_MENU
{
	short PacketType;
	int Type;
};


struct PACKET_CZ_REQ_GUILD_MENU
{
	/* this+0 */ short PacketType;
	/* this+2 */ int Type;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_GUILD_MENU> in(p);
		TPacket<PROTO_CZ_REQ_GUILD_MENU> out;

		out->PacketType = PacketType;
		out->Type = in->Type;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_GUILD_MENU> in(p);
		TPacket<PACKET_CZ_REQ_GUILD_MENU> out;

		out->PacketType = PacketType;
		out->Type = in->Type;

		return out;
	}
};
