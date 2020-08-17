struct PROTO_CZ_PKMODE_CHANGE
{
	short PacketType;
	bool isTurnOn;
};


struct PACKET_CZ_PKMODE_CHANGE
{
	/* this+0 */ short PacketType;
	/* this+2 */ bool isTurnOn;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_PKMODE_CHANGE> in(p);
		TPacket<PROTO_CZ_PKMODE_CHANGE> out;

		out->PacketType = PacketType;
		out->isTurnOn = in->isTurnOn;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_PKMODE_CHANGE> in(p);
		TPacket<PACKET_CZ_PKMODE_CHANGE> out;

		out->PacketType = PacketType;
		out->isTurnOn = in->isTurnOn;

		return out;
	}
};
