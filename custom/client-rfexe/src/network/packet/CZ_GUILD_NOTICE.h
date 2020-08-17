struct PROTO_CZ_GUILD_NOTICE
{
	short PacketType;
	unsigned long GDID;
	char subject[60];
	char notice[120];
};


struct PACKET_CZ_GUILD_NOTICE
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ char subject[60];
	/* this+66 */ char notice[120];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_GUILD_NOTICE> in(p);
		TPacket<PROTO_CZ_GUILD_NOTICE> out;

		out->PacketType = PacketType;
		out->GDID = in->GDID;
		memcpy(out->subject, in->subject, 60);
		memcpy(out->notice, in->notice, 120);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_GUILD_NOTICE> in(p);
		TPacket<PACKET_CZ_GUILD_NOTICE> out;

		out->PacketType = PacketType;
		out->GDID = in->GDID;
		memcpy(out->subject, in->subject, 60);
		memcpy(out->notice, in->notice, 120);

		return out;
	}
};
