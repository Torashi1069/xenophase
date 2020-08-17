struct PROTO_CZ_EXEC_EXCHANGE_ITEM
{
	short PacketType;
};


struct PACKET_CZ_EXEC_EXCHANGE_ITEM
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_EXEC_EXCHANGE_ITEM> in(p);
		TPacket<PROTO_CZ_EXEC_EXCHANGE_ITEM> out;

		out->PacketType = PacketType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_EXEC_EXCHANGE_ITEM> in(p);
		TPacket<PACKET_CZ_EXEC_EXCHANGE_ITEM> out;

		out->PacketType = PacketType;

		return out;
	}
};
