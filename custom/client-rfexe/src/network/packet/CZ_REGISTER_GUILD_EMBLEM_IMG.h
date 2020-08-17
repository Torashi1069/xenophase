struct PROTO_CZ_REGISTER_GUILD_EMBLEM_IMG
{
	short PacketType;
	short PacketLength;
	BYTE Emblem[];
};


struct PACKET_CZ_REGISTER_GUILD_EMBLEM_IMG
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ BYTE Emblem[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REGISTER_GUILD_EMBLEM_IMG,BYTE> in(p);
		TPacket<PROTO_CZ_REGISTER_GUILD_EMBLEM_IMG,BYTE> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		memcpy(out->Emblem, in->Emblem, out.count());

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REGISTER_GUILD_EMBLEM_IMG,BYTE> in(p);
		TPacket<PACKET_CZ_REGISTER_GUILD_EMBLEM_IMG,BYTE> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		memcpy(out->Emblem, in->Emblem, out.count());

		return out;
	}
};
