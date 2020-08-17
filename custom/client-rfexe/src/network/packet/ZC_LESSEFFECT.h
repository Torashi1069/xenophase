struct PROTO_ZC_LESSEFFECT
{
	short PacketType;
	BOOL isLess;
};


struct PACKET_ZC_LESSEFFECT
{
	/* this+0 */ short PacketType;
	/* this+2 */ BOOL isLess;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_LESSEFFECT> in(p);
		TPacket<PROTO_ZC_LESSEFFECT> out;

		out->PacketType = PacketType;
		out->isLess = in->isLess;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_LESSEFFECT> in(p);
		TPacket<PACKET_ZC_LESSEFFECT> out;

		out->PacketType = PacketType;
		out->isLess = in->isLess;

		return out;
	}
};
