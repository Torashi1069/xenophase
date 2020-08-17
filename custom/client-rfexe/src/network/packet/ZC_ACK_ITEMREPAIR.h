struct PROTO_ZC_ACK_ITEMREPAIR
{
	short PacketType;
	short index;
	unsigned char result;
};


struct PACKET_ZC_ACK_ITEMREPAIR
{
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
	/* this+4 */ unsigned char result;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_ITEMREPAIR> in(p);
		TPacket<PROTO_ZC_ACK_ITEMREPAIR> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->result = in->result;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACK_ITEMREPAIR> in(p);
		TPacket<PACKET_ZC_ACK_ITEMREPAIR> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->result = in->result;

		return out;
	}
};
