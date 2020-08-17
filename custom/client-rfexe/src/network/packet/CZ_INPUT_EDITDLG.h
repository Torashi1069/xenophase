struct PROTO_CZ_INPUT_EDITDLG
{
	short PacketType;
	unsigned long NAID;
	int value;
};


struct PACKET_CZ_INPUT_EDITDLG
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long NAID;
	/* this+6 */ int value;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_INPUT_EDITDLG> in(p);
		TPacket<PROTO_CZ_INPUT_EDITDLG> out;

		out->PacketType = PacketType;
		out->NAID = in->NAID;
		out->value = in->value;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_INPUT_EDITDLG> in(p);
		TPacket<PACKET_CZ_INPUT_EDITDLG> out;

		out->PacketType = PacketType;
		out->NAID = in->NAID;
		out->value = in->value;

		return out;
	}
};
