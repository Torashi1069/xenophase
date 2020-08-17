struct PROTO_ZC_MSG_VALUE
{
	short PacketType;
	unsigned short msg;
	int value;
};


struct PACKET_ZC_MSG_VALUE
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short msg;
	/* this+4 */ int value;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_MSG_VALUE> in(p);
		TPacket<PROTO_ZC_MSG_VALUE> out;

		out->PacketType = PacketType;
		out->msg = in->msg;
		out->value = in->value;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_MSG_VALUE> in(p);
		TPacket<PACKET_ZC_MSG_VALUE> out;

		out->PacketType = PacketType;
		out->msg = in->msg;
		out->value = in->value;

		return out;
	}
};
