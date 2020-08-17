struct PROTO_ZC_GUILD_CHAT
{
	short PacketType;
	unsigned short PacketLength;
	char Text[];
};


struct PACKET_ZC_GUILD_CHAT
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ char Text[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_GUILD_CHAT,char> in(p);
		TPacket<PROTO_ZC_GUILD_CHAT,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		memcpy(out->Text, in->Text, out.count());

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_GUILD_CHAT,char> in(p);
		TPacket<PACKET_ZC_GUILD_CHAT,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		memcpy(out->Text, in->Text, out.count());

		return out;
	}
};
