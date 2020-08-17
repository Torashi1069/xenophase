struct PROTO_CZ_SELECT_PETEGG
{
	short PacketType;
	short index;
};


struct PACKET_CZ_SELECT_PETEGG
{
	/* this+0 */ short PacketType;
	/* this+2 */ short index;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_SELECT_PETEGG> in(p);
		TPacket<PROTO_CZ_SELECT_PETEGG> out;

		out->PacketType = PacketType;
		out->index = in->index;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_SELECT_PETEGG> in(p);
		TPacket<PACKET_CZ_SELECT_PETEGG> out;

		out->PacketType = PacketType;
		out->index = in->index;

		return out;
	}
};
