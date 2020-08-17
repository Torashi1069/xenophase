struct PROTO_AC_ASK_PNGAMEROOM
{
	short PacketType;
};


struct PACKET_AC_ASK_PNGAMEROOM
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_AC_ASK_PNGAMEROOM> in(p);
		TPacket<PROTO_AC_ASK_PNGAMEROOM> out;

		out->PacketType = PacketType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_AC_ASK_PNGAMEROOM> in(p);
		TPacket<PACKET_AC_ASK_PNGAMEROOM> out;

		out->PacketType = PacketType;

		return out;
	}
};
