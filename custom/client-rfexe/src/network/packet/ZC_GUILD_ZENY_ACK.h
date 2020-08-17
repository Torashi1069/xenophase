struct PROTO_ZC_GUILD_ZENY_ACK
{
	short PacketType;
	unsigned char ret;
};


struct PACKET_ZC_GUILD_ZENY_ACK
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char ret;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_GUILD_ZENY_ACK> in(p);
		TPacket<PROTO_ZC_GUILD_ZENY_ACK> out;

		out->PacketType = PacketType;
		out->ret = in->ret;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_GUILD_ZENY_ACK> in(p);
		TPacket<PACKET_ZC_GUILD_ZENY_ACK> out;

		out->PacketType = PacketType;
		out->ret = in->ret;

		return out;
	}
};
