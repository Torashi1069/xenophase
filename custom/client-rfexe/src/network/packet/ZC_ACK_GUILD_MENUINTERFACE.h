struct PROTO_ZC_ACK_GUILD_MENUINTERFACE
{
	short PacketType;
	int guildMemuFlag;
};


struct PACKET_ZC_ACK_GUILD_MENUINTERFACE
{
	/* this+0 */ short PacketType;
	/* this+2 */ int guildMemuFlag;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_GUILD_MENUINTERFACE> in(p);
		TPacket<PROTO_ZC_ACK_GUILD_MENUINTERFACE> out;

		out->PacketType = PacketType;
		out->guildMemuFlag = in->guildMemuFlag;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACK_GUILD_MENUINTERFACE> in(p);
		TPacket<PACKET_ZC_ACK_GUILD_MENUINTERFACE> out;

		out->PacketType = PacketType;
		out->guildMemuFlag = in->guildMemuFlag;

		return out;
	}
};
