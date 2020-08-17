struct PROTO_CZ_CLOSE_DIALOG
{
	short PacketType;
	unsigned long NAID;
};


struct PACKET_CZ_CLOSE_DIALOG
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long NAID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_CLOSE_DIALOG> in(p);
		TPacket<PROTO_CZ_CLOSE_DIALOG> out;

		out->PacketType = PacketType;
		out->NAID = in->NAID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_CLOSE_DIALOG> in(p);
		TPacket<PACKET_CZ_CLOSE_DIALOG> out;

		out->PacketType = PacketType;
		out->NAID = in->NAID;

		return out;
	}
};
