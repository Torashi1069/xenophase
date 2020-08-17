struct PROTO_CZ_SETTING_WHISPER_PC
{
	short PacketType;
	char name[24];
	unsigned char type;
};


struct PACKET_CZ_SETTING_WHISPER_PC
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char name[24];
	/* this+26 */ unsigned char type;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_SETTING_WHISPER_PC> in(p);
		TPacket<PROTO_CZ_SETTING_WHISPER_PC> out;

		out->PacketType = PacketType;
		memcpy(out->name, in->name, 24);
		out->type = in->type;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_SETTING_WHISPER_PC> in(p);
		TPacket<PACKET_CZ_SETTING_WHISPER_PC> out;

		out->PacketType = PacketType;
		memcpy(out->name, in->name, 24);
		out->type = in->type;

		return out;
	}
};
