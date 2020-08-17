struct PROTO_ZC_BAN_LIST
{
	short PacketType;
	short PacketLength;
	struct GUILD_BAN_INFO
	{
		char charname[24];
		char account[24];
		char reason[40];
	}
	Info[];
};


struct PACKET_ZC_BAN_LIST
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ struct GUILD_BAN_INFO
	             {
	             	/* this+ 0 */ char charname[24];
	             	/* this+24 */ char account[24];
	             	/* this+48 */ char reason[40];
	             }
	             Info[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_BAN_LIST,PACKET_ZC_BAN_LIST::GUILD_BAN_INFO> in(p);
		TPacket<PROTO_ZC_BAN_LIST,PROTO_ZC_BAN_LIST::GUILD_BAN_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			memcpy(out->Info[i].charname, in->Info[i].charname, 24);
			memcpy(out->Info[i].account, in->Info[i].account, 24);
			memcpy(out->Info[i].reason, in->Info[i].reason, 40);
		};

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_BAN_LIST,PROTO_ZC_BAN_LIST::GUILD_BAN_INFO> in(p);
		TPacket<PACKET_ZC_BAN_LIST,PACKET_ZC_BAN_LIST::GUILD_BAN_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			memcpy(out->Info[i].charname, in->Info[i].charname, 24);
			memcpy(out->Info[i].account, in->Info[i].account, 24);
			memcpy(out->Info[i].reason, in->Info[i].reason, 40);
		};

		return out;
	}
};
