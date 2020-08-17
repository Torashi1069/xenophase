struct PROTO_ZC_MEMBER_NEWENTRY
{
	short PacketType;
	short curcount;
	char name[24];
};


struct PACKET_ZC_MEMBER_NEWENTRY
{
	/* this+0 */ short PacketType;
	/* this+2 */ short curcount;
	/* this+4 */ char name[24];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_MEMBER_NEWENTRY> in(p);
		TPacket<PROTO_ZC_MEMBER_NEWENTRY> out;

		out->PacketType = PacketType;
		out->curcount = in->curcount;
		memcpy(out->name, in->name, 24);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_MEMBER_NEWENTRY> in(p);
		TPacket<PACKET_ZC_MEMBER_NEWENTRY> out;

		out->PacketType = PacketType;
		out->curcount = in->curcount;
		memcpy(out->name, in->name, 24);

		return out;
	}
};
