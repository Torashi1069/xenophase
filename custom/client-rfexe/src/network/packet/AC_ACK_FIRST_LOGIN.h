struct PROTO_AC_ACK_FIRST_LOGIN
{
	short PacketType;
};


struct PACKET_AC_ACK_FIRST_LOGIN
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_AC_ACK_FIRST_LOGIN> in(p);
		TPacket<PROTO_AC_ACK_FIRST_LOGIN> out;

		out->PacketType = PacketType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_AC_ACK_FIRST_LOGIN> in(p);
		TPacket<PACKET_AC_ACK_FIRST_LOGIN> out;

		out->PacketType = PacketType;

		return out;
	}
};
