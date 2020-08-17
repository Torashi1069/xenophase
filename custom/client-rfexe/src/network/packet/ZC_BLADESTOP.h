struct PROTO_ZC_BLADESTOP
{
	short PacketType;
	unsigned long srcAID;
	unsigned long destAID;
	int flag;
};


struct PACKET_ZC_BLADESTOP
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long srcAID;
	/* this+ 6 */ unsigned long destAID;
	/* this+10 */ int flag;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_BLADESTOP> in(p);
		TPacket<PROTO_ZC_BLADESTOP> out;

		out->PacketType = PacketType;
		out->srcAID = in->srcAID;
		out->destAID = in->destAID;
		out->flag = in->flag;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_BLADESTOP> in(p);
		TPacket<PACKET_ZC_BLADESTOP> out;

		out->PacketType = PacketType;
		out->srcAID = in->srcAID;
		out->destAID = in->destAID;
		out->flag = in->flag;

		return out;
	}
};
