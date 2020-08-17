struct PROTO_ZC_ACK_WHISPER
{
	short PacketType; // PROTOID_ZC_ACK_WHISPER
	BYTE result; // enum WHISPER_SEND_*
};


struct PACKET_ZC_ACK_WHISPER
{
	/* this+0 */ short PacketType;
	/* this+2 */ BYTE result;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_WHISPER> in(p);
		TPacket<PROTO_ZC_ACK_WHISPER> out;

		out->PacketType = PacketType;
		out->result = in->result;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACK_WHISPER> in(p);
		TPacket<PACKET_ZC_ACK_WHISPER> out;

		out->PacketType = PacketType;
		out->result = in->result;

		return out;
	}
};
