struct PROTO_ZC_ACK_ADDITEM_TO_CART
{
	short PacketType;
	unsigned char result;
};


struct PACKET_ZC_ACK_ADDITEM_TO_CART
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char result;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_ADDITEM_TO_CART> in(p);
		TPacket<PROTO_ZC_ACK_ADDITEM_TO_CART> out;

		out->PacketType = PacketType;
		out->result = in->result;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACK_ADDITEM_TO_CART> in(p);
		TPacket<PACKET_ZC_ACK_ADDITEM_TO_CART> out;

		out->PacketType = PacketType;
		out->result = in->result;

		return out;
	}
};
