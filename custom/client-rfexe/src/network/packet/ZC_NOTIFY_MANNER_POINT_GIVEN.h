struct PROTO_ZC_NOTIFY_MANNER_POINT_GIVEN
{
	short PacketType;
	unsigned char type;
	char otherCharName[24];
};


struct PACKET_ZC_NOTIFY_MANNER_POINT_GIVEN
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char type;
	/* this+3 */ char otherCharName[24];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_MANNER_POINT_GIVEN> in(p);
		TPacket<PROTO_ZC_NOTIFY_MANNER_POINT_GIVEN> out;

		out->PacketType = PacketType;
		out->type = in->type;
		memcpy(out->otherCharName, in->otherCharName, 24);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_MANNER_POINT_GIVEN> in(p);
		TPacket<PACKET_ZC_NOTIFY_MANNER_POINT_GIVEN> out;

		out->PacketType = PacketType;
		out->type = in->type;
		memcpy(out->otherCharName, in->otherCharName, 24);

		return out;
	}
};
