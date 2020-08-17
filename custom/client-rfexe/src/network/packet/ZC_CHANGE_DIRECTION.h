struct PROTO_ZC_CHANGE_DIRECTION
{
	short PacketType;
	unsigned long AID;
	short headDir;
	unsigned char dir;
};


struct PACKET_ZC_CHANGE_DIRECTION
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ short headDir;
	/* this+8 */ unsigned char dir;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_CHANGE_DIRECTION> in(p);
		TPacket<PROTO_ZC_CHANGE_DIRECTION> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->headDir = in->headDir;
		out->dir = in->dir;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_CHANGE_DIRECTION> in(p);
		TPacket<PACKET_ZC_CHANGE_DIRECTION> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->headDir = in->headDir;
		out->dir = in->dir;

		return out;
	}
};
