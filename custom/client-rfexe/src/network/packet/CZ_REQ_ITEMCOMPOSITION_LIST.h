struct PROTO_CZ_REQ_ITEMCOMPOSITION_LIST
{
	short PacketType;
	short cardIndex;
};


struct PACKET_CZ_REQ_ITEMCOMPOSITION_LIST
{
	/* this+0 */ short PacketType;
	/* this+2 */ short cardIndex;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_ITEMCOMPOSITION_LIST> in(p);
		TPacket<PROTO_CZ_REQ_ITEMCOMPOSITION_LIST> out;

		out->PacketType = PacketType;
		out->cardIndex = in->cardIndex;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_ITEMCOMPOSITION_LIST> in(p);
		TPacket<PACKET_CZ_REQ_ITEMCOMPOSITION_LIST> out;

		out->PacketType = PacketType;
		out->cardIndex = in->cardIndex;

		return out;
	}
};
