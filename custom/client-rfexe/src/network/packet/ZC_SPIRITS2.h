struct PROTO_ZC_SPIRITS2
{
	short PacketType;
	unsigned long AID;
	short num;
};


struct PACKET_ZC_SPIRITS2
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ short num;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_SPIRITS2> in(p);
		TPacket<PROTO_ZC_SPIRITS2> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->num = in->num;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_SPIRITS2> in(p);
		TPacket<PACKET_ZC_SPIRITS2> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->num = in->num;

		return out;
	}
};
