struct PROTO_ZC_GUILD_EMBLEM_IMG
{
	short PacketType;
	short PacketLength;
	int GDID;
	int emblemVersion;
	char Emblem[];
};


struct PACKET_ZC_GUILD_EMBLEM_IMG
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ int GDID;
	/* this+ 8 */ int emblemVersion;
	/* this+12 */ char Emblem[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_GUILD_EMBLEM_IMG,char> in(p);
		TPacket<PROTO_ZC_GUILD_EMBLEM_IMG,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->GDID = in->GDID;
		out->emblemVersion = in->emblemVersion;
		memcpy(out->Emblem, in->Emblem, out.count());

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_GUILD_EMBLEM_IMG,char> in(p);
		TPacket<PACKET_ZC_GUILD_EMBLEM_IMG,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->GDID = in->GDID;
		out->emblemVersion = in->emblemVersion;
		memcpy(out->Emblem, in->Emblem, out.count());

		return out;
	}
};
