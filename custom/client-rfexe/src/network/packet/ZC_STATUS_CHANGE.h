struct PROTO_ZC_STATUS_CHANGE
{
	short PacketType;
	unsigned short statusID;
	unsigned char value;
};


struct PACKET_ZC_STATUS_CHANGE
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short statusID;
	/* this+4 */ unsigned char value;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_STATUS_CHANGE> in(p);
		TPacket<PROTO_ZC_STATUS_CHANGE> out;

		out->PacketType = PacketType;
		out->statusID = in->statusID;
		out->value = in->value;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_STATUS_CHANGE> in(p);
		TPacket<PACKET_ZC_STATUS_CHANGE> out;

		out->PacketType = PacketType;
		out->statusID = in->statusID;
		out->value = in->value;

		return out;
	}
};
