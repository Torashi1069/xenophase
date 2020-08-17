struct PROTO_CZ_REQ_GIVE_MANNER_POINT
{
	short PacketType;
	unsigned long otherAID;
	unsigned char type;
	short point;
};


struct PACKET_CZ_REQ_GIVE_MANNER_POINT
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long otherAID;
	/* this+6 */ unsigned char type;
	/* this+7 */ short point;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_GIVE_MANNER_POINT> in(p);
		TPacket<PROTO_CZ_REQ_GIVE_MANNER_POINT> out;

		out->PacketType = PacketType;
		out->otherAID = in->otherAID;
		out->type = in->type;
		out->point = in->point;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_GIVE_MANNER_POINT> in(p);
		TPacket<PACKET_CZ_REQ_GIVE_MANNER_POINT> out;

		out->PacketType = PacketType;
		out->otherAID = in->otherAID;
		out->type = in->type;
		out->point = in->point;

		return out;
	}
};
