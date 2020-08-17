struct PROTO_TEMPLATE
{
};


struct PACKET_TEMPLATE
{
	/* this+0 */ short PacketType;
	/* this+2 */ int XXX;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_TEMPLATE> in(p);
		TPacket<PROTO_TEMPLATE> out;

		out->PacketType = PacketType;
		out->XXX = in->XXX;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_TEMPLATE> in(p);
		TPacket<PACKET_TEMPLATE> out;

		out->PacketType = PacketType;
		out->XXX = in->XXX;

		return out;
	}
};
