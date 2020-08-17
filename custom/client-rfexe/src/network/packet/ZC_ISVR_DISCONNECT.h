struct PROTO_ZC_ISVR_DISCONNECT
{
	short PacketType;
};


struct PACKET_ZC_ISVR_DISCONNECT
{
	/* this+ 0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ISVR_DISCONNECT> in(p);
		TPacket<PROTO_ZC_ISVR_DISCONNECT> out;

		out->PacketType = PacketType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ISVR_DISCONNECT> in(p);
		TPacket<PACKET_ZC_ISVR_DISCONNECT> out;

		out->PacketType = PacketType;

		return out;
	}
};
