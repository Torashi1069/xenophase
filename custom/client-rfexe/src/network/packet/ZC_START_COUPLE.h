struct PROTO_ZC_START_COUPLE
{
	short PacketType;
};


struct PACKET_ZC_START_COUPLE
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_START_COUPLE> in(p);
		TPacket<PROTO_ZC_START_COUPLE> out;

		out->PacketType = PacketType;
		
		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_START_COUPLE> in(p);
		TPacket<PACKET_ZC_START_COUPLE> out;

		out->PacketType = PacketType;

		return out;
	}
};
