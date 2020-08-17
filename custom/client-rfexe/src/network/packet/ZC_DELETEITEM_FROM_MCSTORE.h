struct PROTO_ZC_DELETEITEM_FROM_MCSTORE
{
	short PacketType;
	short index;
	short count;
};


struct PACKET_ZC_DELETEITEM_FROM_MCSTORE
{
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
	/* this+4 */ short count;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_DELETEITEM_FROM_MCSTORE> in(p);
		TPacket<PROTO_ZC_DELETEITEM_FROM_MCSTORE> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->count = in->count;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_DELETEITEM_FROM_MCSTORE> in(p);
		TPacket<PACKET_ZC_DELETEITEM_FROM_MCSTORE> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->count = in->count;

		return out;
	}
};
