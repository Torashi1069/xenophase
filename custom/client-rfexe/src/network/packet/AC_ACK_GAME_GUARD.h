struct PROTO_AC_ACK_GAME_GUARD
{
	short PacketType;
	unsigned char ucAnswer;
};


struct PACKET_AC_ACK_GAME_GUARD
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char ucAnswer;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_AC_ACK_GAME_GUARD> in(p);
		TPacket<PROTO_AC_ACK_GAME_GUARD> out;

		out->PacketType = PacketType;
		out->ucAnswer = in->ucAnswer;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_AC_ACK_GAME_GUARD> in(p);
		TPacket<PACKET_AC_ACK_GAME_GUARD> out;

		out->PacketType = PacketType;
		out->ucAnswer = in->ucAnswer;

		return out;
	}
};
