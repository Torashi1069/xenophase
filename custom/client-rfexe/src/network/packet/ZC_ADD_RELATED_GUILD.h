struct PROTO_ZC_ADD_RELATED_GUILD
{
	short PacketType;
	struct RELATED_GUILD_INFO
	{
		int relation;
		int GDID;
		char guildname[24];
	}
	Info;
};


struct PACKET_ZC_ADD_RELATED_GUILD
{
	/* this+0 */ short PacketType;
	/* this+2 */ struct RELATED_GUILD_INFO
	             {
	             	/* this+0 */ int relation;
	             	/* this+4 */ int GDID;
	             	/* this+8 */ char guildname[24];
	             }
	             Info;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ADD_RELATED_GUILD> in(p);
		TPacket<PROTO_ZC_ADD_RELATED_GUILD> out;

		out->PacketType = PacketType;
		out->Info.relation = in->Info.relation;
		out->Info.GDID = in->Info.GDID;
		memcpy(out->Info.guildname, in->Info.guildname, 24);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ADD_RELATED_GUILD> in(p);
		TPacket<PACKET_ZC_ADD_RELATED_GUILD> out;

		out->PacketType = PacketType;
		out->Info.relation = in->Info.relation;
		out->Info.GDID = in->Info.GDID;
		memcpy(out->Info.guildname, in->Info.guildname, 24);

		return out;
	}
};
