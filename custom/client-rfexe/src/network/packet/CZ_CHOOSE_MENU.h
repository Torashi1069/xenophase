struct PROTO_CZ_CHOOSE_MENU
{
	short PacketType;
	unsigned long NAID;
	unsigned char num;
};


struct PACKET_CZ_CHOOSE_MENU
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long NAID;
	/* this+6 */ unsigned char num;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_CHOOSE_MENU> in(p);
		TPacket<PROTO_CZ_CHOOSE_MENU> out;

		out->PacketType = PacketType;
		out->NAID = in->NAID;
		out->num = in->num;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_CHOOSE_MENU> in(p);
		TPacket<PACKET_CZ_CHOOSE_MENU> out;

		out->PacketType = PacketType;
		out->NAID = in->NAID;
		out->num = in->num;

		return out;
	}
};
