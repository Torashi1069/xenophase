struct PROTO_ZC_WAIT_DIALOG
{
	short PacketType;
	unsigned long NAID;
};


struct PACKET_ZC_WAIT_DIALOG
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long NAID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_WAIT_DIALOG> in(p);
		TPacket<PROTO_ZC_WAIT_DIALOG> out;

		out->PacketType = PacketType;
		out->NAID = in->NAID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_WAIT_DIALOG> in(p);
		TPacket<PACKET_ZC_WAIT_DIALOG> out;

		out->PacketType = PacketType;
		out->NAID = in->NAID;

		return out;
	}
};
