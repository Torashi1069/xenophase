struct PROTO_CZ_PETEGG_INFO
{
	short PacketType;
	short index;
};


struct PACKET_CZ_PETEGG_INFO
{
	/* this+0 */ short PacketType;
	/* this+2 */ short index;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_PETEGG_INFO> in(p);
		TPacket<PROTO_CZ_PETEGG_INFO> out;

		out->PacketType = PacketType;
		out->index = in->index;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_PETEGG_INFO> in(p);
		TPacket<PACKET_CZ_PETEGG_INFO> out;

		out->PacketType = PacketType;
		out->index = in->index;

		return out;
	}
};
