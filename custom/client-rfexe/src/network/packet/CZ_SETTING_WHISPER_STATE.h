struct PROTO_CZ_SETTING_WHISPER_STATE
{
	short PacketType;
	unsigned char type;
};


struct PACKET_CZ_SETTING_WHISPER_STATE
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char type;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_SETTING_WHISPER_STATE> in(p);
		TPacket<PROTO_CZ_SETTING_WHISPER_STATE> out;

		out->PacketType = PacketType;
		out->type = in->type;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_SETTING_WHISPER_STATE> in(p);
		TPacket<PACKET_CZ_SETTING_WHISPER_STATE> out;

		out->PacketType = PacketType;
		out->type = in->type;

		return out;
	}
};
