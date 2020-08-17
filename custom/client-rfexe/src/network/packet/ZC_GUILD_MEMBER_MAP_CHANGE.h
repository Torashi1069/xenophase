struct PROTO_ZC_GUILD_MEMBER_MAP_CHANGE
{
	short PacketType;
	unsigned long GDID;
	unsigned long AID;
	char mapName[16];
};


struct PACKET_ZC_GUILD_MEMBER_MAP_CHANGE
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ char mapName[16];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_GUILD_MEMBER_MAP_CHANGE> in(p);
		TPacket<PROTO_ZC_GUILD_MEMBER_MAP_CHANGE> out;

		out->PacketType = PacketType;
		out->GDID = in->GDID;
		out->AID = in->AID;
		memcpy(out->mapName, in->mapName, 16);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_GUILD_MEMBER_MAP_CHANGE> in(p);
		TPacket<PACKET_ZC_GUILD_MEMBER_MAP_CHANGE> out;

		out->PacketType = PacketType;
		out->GDID = in->GDID;
		out->AID = in->AID;
		memcpy(out->mapName, in->mapName, 16);

		return out;
	}
};
