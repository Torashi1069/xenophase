struct PROTO_ZC_MYGUILD_BASIC_INFO
{
	short PacketType;
	short PacketLength;
	struct RELATED_GUILD_INFO
	{
		int relation;
		int GDID;
		char guildname[24];
	}
	Info[];
};


struct PACKET_ZC_MYGUILD_BASIC_INFO
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ struct RELATED_GUILD_INFO
	             {
	             	/* this+0 */ int relation;
	             	/* this+4 */ int GDID;
	             	/* this+8 */ char guildname[24];
	             }
	             Info[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_MYGUILD_BASIC_INFO,PACKET_ZC_MYGUILD_BASIC_INFO::RELATED_GUILD_INFO> in(p);
		TPacket<PROTO_ZC_MYGUILD_BASIC_INFO,PROTO_ZC_MYGUILD_BASIC_INFO::RELATED_GUILD_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Info[i].relation = in->Info[i].relation;
			out->Info[i].GDID = in->Info[i].GDID;
			memcpy(out->Info[i].guildname, in->Info[i].guildname, 24);
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_MYGUILD_BASIC_INFO,PROTO_ZC_MYGUILD_BASIC_INFO::RELATED_GUILD_INFO> in(p);
		TPacket<PACKET_ZC_MYGUILD_BASIC_INFO,PACKET_ZC_MYGUILD_BASIC_INFO::RELATED_GUILD_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Info[i].relation = in->Info[i].relation;
			out->Info[i].GDID = in->Info[i].GDID;
			memcpy(out->Info[i].guildname, in->Info[i].guildname, 24);
		}

		return out;
	}
};
