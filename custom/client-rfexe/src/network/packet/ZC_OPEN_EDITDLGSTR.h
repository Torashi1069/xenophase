struct PROTO_ZC_OPEN_EDITDLGSTR
{
	short PacketType;
	unsigned long NAID;
};


struct PACKET_ZC_OPEN_EDITDLGSTR
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long NAID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_OPEN_EDITDLGSTR> in(p);
		TPacket<PROTO_ZC_OPEN_EDITDLGSTR> out;

		out->PacketType = PacketType;
		out->NAID = in->NAID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_OPEN_EDITDLGSTR> in(p);
		TPacket<PACKET_ZC_OPEN_EDITDLGSTR> out;

		out->PacketType = PacketType;
		out->NAID = in->NAID;

		return out;
	}
};
