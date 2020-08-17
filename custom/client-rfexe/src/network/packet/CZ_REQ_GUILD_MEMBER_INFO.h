struct PROTO_CZ_REQ_GUILD_MEMBER_INFO
{
	short PacketType;
	int GID;
};


struct PACKET_CZ_REQ_GUILD_MEMBER_INFO
{
	/* this+0 */ short PacketType;
	/* this+2 */ int GID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_GUILD_MEMBER_INFO> in(p);
		TPacket<PROTO_CZ_REQ_GUILD_MEMBER_INFO> out;

		out->PacketType = PacketType;
		out->GID = in->GID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_GUILD_MEMBER_INFO> in(p);
		TPacket<PACKET_CZ_REQ_GUILD_MEMBER_INFO> out;

		out->PacketType = PacketType;
		out->GID = in->GID;

		return out;
	}
};
