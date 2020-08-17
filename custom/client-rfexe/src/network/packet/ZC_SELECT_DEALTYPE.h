struct PROTO_ZC_SELECT_DEALTYPE
{
	short PacketType;
	unsigned long NAID;
};


struct PACKET_ZC_SELECT_DEALTYPE
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long NAID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_SELECT_DEALTYPE> in(p);
		TPacket<PROTO_ZC_SELECT_DEALTYPE> out;

		out->PacketType = PacketType;
		out->NAID = in->NAID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_SELECT_DEALTYPE> in(p);
		TPacket<PACKET_ZC_SELECT_DEALTYPE> out;

		out->PacketType = PacketType;
		out->NAID = in->NAID;

		return out;
	}
};
