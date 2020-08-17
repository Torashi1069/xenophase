struct PROTO_ZC_OPENSTORE
{
	short PacketType;
	short itemcount;
};


struct PACKET_ZC_OPENSTORE
{
	/* this+0 */ short PacketType;
	/* this+2 */ short itemcount;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_OPENSTORE> in(p);
		TPacket<PROTO_ZC_OPENSTORE> out;

		out->PacketType = PacketType;
		out->itemcount = in->itemcount;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_OPENSTORE> in(p);
		TPacket<PACKET_ZC_OPENSTORE> out;

		out->PacketType = PacketType;
		out->itemcount = in->itemcount;

		return out;
	}
};
