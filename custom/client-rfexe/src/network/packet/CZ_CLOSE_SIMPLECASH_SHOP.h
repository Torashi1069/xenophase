struct PROTO_CZ_CLOSE_SIMPLECASH_SHOP
{
	short PacketType;
};


struct PACKET_CZ_CLOSE_SIMPLECASH_SHOP
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_CLOSE_SIMPLECASH_SHOP> in(p);
		TPacket<PROTO_CZ_CLOSE_SIMPLECASH_SHOP> out;

		out->PacketType = PacketType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_CLOSE_SIMPLECASH_SHOP> in(p);
		TPacket<PACKET_CZ_CLOSE_SIMPLECASH_SHOP> out;

		out->PacketType = PacketType;

		return out;
	}
};
