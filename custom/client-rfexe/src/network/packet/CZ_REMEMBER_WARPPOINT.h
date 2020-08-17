struct PROTO_CZ_REMEMBER_WARPPOINT
{
	short PacketType;
};


struct PACKET_CZ_REMEMBER_WARPPOINT
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REMEMBER_WARPPOINT> in(p);
		TPacket<PROTO_CZ_REMEMBER_WARPPOINT> out;

		out->PacketType = PacketType;
		
		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REMEMBER_WARPPOINT> in(p);
		TPacket<PACKET_CZ_REMEMBER_WARPPOINT> out;

		out->PacketType = PacketType;

		return out;
	}
};
