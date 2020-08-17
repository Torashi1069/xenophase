struct PROTO_CZ_CHOPOKGI
{
	short PacketType;
};


struct PACKET_CZ_CHOPOKGI
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_CHOPOKGI> in(p);
		TPacket<PROTO_CZ_CHOPOKGI> out;

		out->PacketType = PacketType;
		
		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_CHOPOKGI> in(p);
		TPacket<PACKET_CZ_CHOPOKGI> out;

		out->PacketType = PacketType;

		return out;
	}
};
