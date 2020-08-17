struct PROTO_ZC_ACCEPT_QUIT
{
	short PacketType;
};


struct PACKET_ZC_ACCEPT_QUIT
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACCEPT_QUIT> in(p);
		TPacket<PROTO_ZC_ACCEPT_QUIT> out;

		out->PacketType = PacketType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACCEPT_QUIT> in(p);
		TPacket<PACKET_ZC_ACCEPT_QUIT> out;

		out->PacketType = PacketType;

		return out;
	}
};
