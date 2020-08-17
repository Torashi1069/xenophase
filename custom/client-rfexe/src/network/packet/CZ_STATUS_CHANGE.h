struct PROTO_CZ_STATUS_CHANGE
{
	short PacketType;
	unsigned short statusID;
	unsigned char changeAmount;
};


struct PACKET_CZ_STATUS_CHANGE
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short statusID;
	/* this+4 */ unsigned char changeAmount;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_STATUS_CHANGE> in(p);
		TPacket<PROTO_CZ_STATUS_CHANGE> out;

		out->PacketType = PacketType;
		out->statusID = in->statusID;
		out->changeAmount = in->changeAmount;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_STATUS_CHANGE> in(p);
		TPacket<PACKET_CZ_STATUS_CHANGE> out;

		out->PacketType = PacketType;
		out->statusID = in->statusID;
		out->changeAmount = in->changeAmount;

		return out;
	}
};
