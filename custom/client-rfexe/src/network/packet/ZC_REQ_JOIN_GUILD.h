struct PROTO_ZC_REQ_JOIN_GUILD
{
	short PacketType;
	unsigned long GDID;
	char guildName[24];
};


struct PACKET_ZC_REQ_JOIN_GUILD
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GDID;
	/* this+6 */ char guildName[24];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_REQ_JOIN_GUILD> in(p);
		TPacket<PROTO_ZC_REQ_JOIN_GUILD> out;

		out->PacketType = PacketType;
		out->GDID = in->GDID;
		memcpy(out->guildName, in->guildName, 24);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_REQ_JOIN_GUILD> in(p);
		TPacket<PACKET_ZC_REQ_JOIN_GUILD> out;

		out->PacketType = PacketType;
		out->GDID = in->GDID;
		memcpy(out->guildName, in->guildName, 24);

		return out;
	}
};
