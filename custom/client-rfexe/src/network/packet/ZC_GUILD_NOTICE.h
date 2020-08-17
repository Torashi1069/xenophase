struct PROTO_ZC_GUILD_NOTICE
{
	short PacketType;
	char subject[60];
	char notice[120];
};


struct PACKET_ZC_GUILD_NOTICE
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char subject[60];
	/* this+62 */ char notice[120];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_GUILD_NOTICE> in(p);
		TPacket<PROTO_ZC_GUILD_NOTICE> out;

		out->PacketType = PacketType;
		memcpy(out->subject, in->subject, 60);
		memcpy(out->notice, in->notice, 120);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_GUILD_NOTICE> in(p);
		TPacket<PACKET_ZC_GUILD_NOTICE> out;

		out->PacketType = PacketType;
		memcpy(out->subject, in->subject, 60);
		memcpy(out->notice, in->notice, 120);

		return out;
	}
};
