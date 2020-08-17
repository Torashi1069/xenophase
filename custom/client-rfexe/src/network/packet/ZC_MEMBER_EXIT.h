struct PROTO_ZC_MEMBER_EXIT
{
	short PacketType;
	short curcount;
	char name[24];
	unsigned char type;
};


struct PACKET_ZC_MEMBER_EXIT
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short curcount;
	/* this+ 4 */ char name[24];
	/* this+28 */ unsigned char type;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_MEMBER_EXIT> in(p);
		TPacket<PROTO_ZC_MEMBER_EXIT> out;

		out->PacketType = PacketType;
		out->curcount = in->curcount;
		memcpy(out->name, in->name, 24);
		out->type = in->type;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_MEMBER_EXIT> in(p);
		TPacket<PACKET_ZC_MEMBER_EXIT> out;

		out->PacketType = PacketType;
		out->curcount = in->curcount;
		memcpy(out->name, in->name, 24);
		out->type = in->type;

		return out;
	}
};
