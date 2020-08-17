struct PROTO_ZC_RESTART_ACK
{
	short PacketType;
	unsigned char type;
};


struct PACKET_ZC_RESTART_ACK
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char type;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_RESTART_ACK> in(p);
		TPacket<PROTO_ZC_RESTART_ACK> out;

		out->PacketType = PacketType;
		out->type = in->type;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_RESTART_ACK> in(p);
		TPacket<PACKET_ZC_RESTART_ACK> out;

		out->PacketType = PacketType;
		out->type = in->type;

		return out;
	}
};
