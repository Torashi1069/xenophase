struct PROTO_ZC_OTHER_GUILD_LIST
{
	short PacketType;
	short PacketLength;
	BYTE unknown[]; // TODO
};


struct PACKET_ZC_OTHER_GUILD_LIST
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ BYTE unknown[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_OTHER_GUILD_LIST,BYTE> in(p);
		TPacket<PROTO_ZC_OTHER_GUILD_LIST,BYTE> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		memcpy(out->unknown, in->unknown, out.count());

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_OTHER_GUILD_LIST,BYTE> in(p);
		TPacket<PACKET_ZC_OTHER_GUILD_LIST,BYTE> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		memcpy(out->unknown, in->unknown, out.count());

		return out;
	}
};
