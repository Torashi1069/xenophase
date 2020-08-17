struct PROTO_CZ_LESSEFFECT
{
	short PacketType;
	BOOL isLess;
};


struct PACKET_CZ_LESSEFFECT
{
	/* this+0 */ short PacketType;
	/* this+2 */ BOOL isLess;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_LESSEFFECT> in(p);
		TPacket<PROTO_CZ_LESSEFFECT> out;

		out->PacketType = PacketType;
		out->isLess = in->isLess;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_LESSEFFECT> in(p);
		TPacket<PACKET_CZ_LESSEFFECT> out;

		out->PacketType = PacketType;
		out->isLess = in->isLess;

		return out;
	}
};
