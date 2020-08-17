struct PROTO_ZC_ACK_ITEMCOMPOSITION
{
	short PacketType;
	short equipIndex;
	short cardIndex;
	unsigned char result;
};


struct PACKET_ZC_ACK_ITEMCOMPOSITION
{
	/* this+0 */ short PacketType;
	/* this+2 */ short equipIndex;
	/* this+4 */ short cardIndex;
	/* this+6 */ unsigned char result;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_ITEMCOMPOSITION> in(p);
		TPacket<PROTO_ZC_ACK_ITEMCOMPOSITION> out;

		out->PacketType = PacketType;
		out->equipIndex = in->equipIndex;
		out->cardIndex = in->cardIndex;
		out->result = in->result;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACK_ITEMCOMPOSITION> in(p);
		TPacket<PACKET_ZC_ACK_ITEMCOMPOSITION> out;

		out->PacketType = PacketType;
		out->equipIndex = in->equipIndex;
		out->cardIndex = in->cardIndex;
		out->result = in->result;

		return out;
	}
};
