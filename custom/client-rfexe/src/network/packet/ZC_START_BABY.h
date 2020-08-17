struct PROTO_ZC_START_BABY
{
	short PacketType;
};


struct PACKET_ZC_START_BABY
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_START_BABY> in(p);
		TPacket<PROTO_ZC_START_BABY> out;

		out->PacketType = PacketType;
		
		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_START_BABY> in(p);
		TPacket<PACKET_ZC_START_BABY> out;

		out->PacketType = PacketType;

		return out;
	}
};
