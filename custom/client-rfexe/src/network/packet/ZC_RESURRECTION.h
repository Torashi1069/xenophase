struct PROTO_ZC_RESURRECTION
{
	short PacketType;
	unsigned long AID;
	short type;
};


struct PACKET_ZC_RESURRECTION
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ short type;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_RESURRECTION> in(p);
		TPacket<PROTO_ZC_RESURRECTION> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->type = in->type;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_RESURRECTION> in(p);
		TPacket<PACKET_ZC_RESURRECTION> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->type = in->type;

		return out;
	}
};
