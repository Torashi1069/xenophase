struct PROTO_CZ_REQ_WHISPER_LIST
{
	short PacketType;
};


struct PACKET_CZ_REQ_WHISPER_LIST
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_WHISPER_LIST> in(p);
		TPacket<PROTO_CZ_REQ_WHISPER_LIST> out;

		out->PacketType = PacketType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_WHISPER_LIST> in(p);
		TPacket<PACKET_CZ_REQ_WHISPER_LIST> out;

		out->PacketType = PacketType;

		return out;
	}
};
