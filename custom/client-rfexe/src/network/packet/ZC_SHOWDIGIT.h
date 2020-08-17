struct PROTO_ZC_SHOWDIGIT
{
	short PacketType;
	unsigned char type;
	int value;
};


struct PACKET_ZC_SHOWDIGIT
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char type;
	/* this+3 */ int value;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_SHOWDIGIT> in(p);
		TPacket<PROTO_ZC_SHOWDIGIT> out;

		out->PacketType = PacketType;
		out->type = in->type;
		out->value = in->value;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_SHOWDIGIT> in(p);
		TPacket<PACKET_ZC_SHOWDIGIT> out;

		out->PacketType = PacketType;
		out->type = in->type;
		out->value = in->value;

		return out;
	}
};
