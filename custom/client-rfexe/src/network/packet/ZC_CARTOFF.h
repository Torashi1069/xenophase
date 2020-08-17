struct PROTO_ZC_CARTOFF
{
	short PacketType;
};


struct PACKET_ZC_CARTOFF
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_CARTOFF> in(p);
		TPacket<PROTO_ZC_CARTOFF> out;

		out->PacketType = PacketType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_CARTOFF> in(p);
		TPacket<PACKET_ZC_CARTOFF> out;

		out->PacketType = PacketType;

		return out;
	}
};
