struct PROTO_ZC_REQ_ALLY_GUILD
{
	short PacketType;
	unsigned long otherAID;
	char guildName[24];
};


struct PACKET_ZC_REQ_ALLY_GUILD
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long otherAID;
	/* this+6 */ char guildName[24];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_REQ_ALLY_GUILD> in(p);
		TPacket<PROTO_ZC_REQ_ALLY_GUILD> out;

		out->PacketType = PacketType;
		out->otherAID = in->otherAID;
		memcpy(out->guildName, in->guildName, 24);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_REQ_ALLY_GUILD> in(p);
		TPacket<PACKET_ZC_REQ_ALLY_GUILD> out;

		out->PacketType = PacketType;
		out->otherAID = in->otherAID;
		memcpy(out->guildName, in->guildName, 24);

		return out;
	}
};
