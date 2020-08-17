struct PROTO_CZ_REQ_ITEMIDENTIFY
{
	short PacketType;
	short index;
};


struct PACKET_CZ_REQ_ITEMIDENTIFY
{
	/* this+0 */ short PacketType;
	/* this+2 */ short index;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_ITEMIDENTIFY> in(p);
		TPacket<PROTO_CZ_REQ_ITEMIDENTIFY> out;

		out->PacketType = PacketType;
		out->index = in->index;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_ITEMIDENTIFY> in(p);
		TPacket<PACKET_CZ_REQ_ITEMIDENTIFY> out;

		out->PacketType = PacketType;
		out->index = in->index;

		return out;
	}
};
