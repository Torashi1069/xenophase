struct PROTO_CZ_INPUT_EDITDLGSTR
{
	short PacketType;
	unsigned short PacketLength;
	unsigned long NAID;
	char Text[];
};


struct PACKET_CZ_INPUT_EDITDLGSTR
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ unsigned long NAID;
	/* this+8 */ char Text[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_INPUT_EDITDLGSTR,char> in(p);
		TPacket<PROTO_CZ_INPUT_EDITDLGSTR,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->NAID = in->NAID;
		memcpy(out->Text, in->Text, out.count());

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_INPUT_EDITDLGSTR,char> in(p);
		TPacket<PACKET_CZ_INPUT_EDITDLGSTR,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->NAID = in->NAID;
		memcpy(out->Text, in->Text, out.count());

		return out;
	}
};
