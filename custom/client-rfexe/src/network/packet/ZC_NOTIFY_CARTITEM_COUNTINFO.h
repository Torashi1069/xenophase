struct PROTO_ZC_NOTIFY_CARTITEM_COUNTINFO
{
	short PacketType;
	short curCount;
	short maxCount;
	int curWeight;
	int maxWeight;
};


struct PACKET_ZC_NOTIFY_CARTITEM_COUNTINFO
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short curCount;
	/* this+ 4 */ short maxCount;
	/* this+ 6 */ int curWeight;
	/* this+10 */ int maxWeight;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_CARTITEM_COUNTINFO> in(p);
		TPacket<PROTO_ZC_NOTIFY_CARTITEM_COUNTINFO> out;

		out->PacketType = PacketType;
		out->curCount = in->curCount;
		out->maxCount = in->maxCount;
		out->curWeight = in->curWeight;
		out->maxWeight = in->maxWeight;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_CARTITEM_COUNTINFO> in(p);
		TPacket<PACKET_ZC_NOTIFY_CARTITEM_COUNTINFO> out;

		out->PacketType = PacketType;
		out->curCount = in->curCount;
		out->maxCount = in->maxCount;
		out->curWeight = in->curWeight;
		out->maxWeight = in->maxWeight;

		return out;
	}
};
