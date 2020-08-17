struct PROTO_CZ_ACK_SELECT_DEALTYPE
{
	short PacketType;
	unsigned long NAID;
	unsigned char type;
};


struct PACKET_CZ_ACK_SELECT_DEALTYPE
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long NAID;
	/* this+6 */ unsigned char type;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_ACK_SELECT_DEALTYPE> in(p);
		TPacket<PROTO_CZ_ACK_SELECT_DEALTYPE> out;

		out->PacketType = PacketType;
		out->NAID = in->NAID;
		out->type = in->type;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_ACK_SELECT_DEALTYPE> in(p);
		TPacket<PACKET_CZ_ACK_SELECT_DEALTYPE> out;

		out->PacketType = PacketType;
		out->NAID = in->NAID;
		out->type = in->type;

		return out;
	}
};
