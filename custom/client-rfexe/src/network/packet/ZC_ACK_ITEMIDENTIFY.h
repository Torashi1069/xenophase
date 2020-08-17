struct PROTO_ZC_ACK_ITEMIDENTIFY
{
	short PacketType;
	short index;
	unsigned char result;
};


struct PACKET_ZC_ACK_ITEMIDENTIFY
{
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
	/* this+4 */ unsigned char result;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_ITEMIDENTIFY> in(p);
		TPacket<PROTO_ZC_ACK_ITEMIDENTIFY> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->result = in->result;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACK_ITEMIDENTIFY> in(p);
		TPacket<PACKET_ZC_ACK_ITEMIDENTIFY> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->result = in->result;

		return out;
	}
};
