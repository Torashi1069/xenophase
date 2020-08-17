struct PROTO_ZC_SETTING_WHISPER_STATE
{
	short PacketType;
	unsigned char type;
	unsigned char result;
};


struct PACKET_ZC_SETTING_WHISPER_STATE
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char type;
	/* this+3 */ unsigned char result;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_SETTING_WHISPER_STATE> in(p);
		TPacket<PROTO_ZC_SETTING_WHISPER_STATE> out;

		out->PacketType = PacketType;
		out->type = in->type;
		out->result = in->result;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_SETTING_WHISPER_STATE> in(p);
		TPacket<PACKET_ZC_SETTING_WHISPER_STATE> out;

		out->PacketType = PacketType;
		out->type = in->type;
		out->result = in->result;

		return out;
	}
};
