struct PROTO_CZ_DORIDORI
{
	short PacketType;
};


struct PACKET_CZ_DORIDORI
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_DORIDORI> in(p);
		TPacket<PROTO_CZ_DORIDORI> out;

		out->PacketType = PacketType;
		
		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_DORIDORI> in(p);
		TPacket<PACKET_CZ_DORIDORI> out;

		out->PacketType = PacketType;

		return out;
	}
};
