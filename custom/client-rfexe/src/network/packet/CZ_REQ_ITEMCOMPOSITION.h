struct PROTO_CZ_REQ_ITEMCOMPOSITION
{
	short PacketType;
	short cardIndex;
	short equipIndex;
};


struct PACKET_CZ_REQ_ITEMCOMPOSITION
{
	/* this+0 */ short PacketType;
	/* this+2 */ short cardIndex;
	/* this+4 */ short equipIndex;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_ITEMCOMPOSITION> in(p);
		TPacket<PROTO_CZ_REQ_ITEMCOMPOSITION> out;

		out->PacketType = PacketType;
		out->cardIndex = in->cardIndex;
		out->equipIndex = in->equipIndex;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_ITEMCOMPOSITION> in(p);
		TPacket<PACKET_CZ_REQ_ITEMCOMPOSITION> out;

		out->PacketType = PacketType;
		out->cardIndex = in->cardIndex;
		out->equipIndex = in->equipIndex;

		return out;
	}
};
