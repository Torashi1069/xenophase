struct PROTO_ZC_NOTIFY_STOREITEM_COUNTINFO
{
	short PacketType;
	short curCount;
	short maxCount;
};


struct PACKET_ZC_NOTIFY_STOREITEM_COUNTINFO
{
	/* this+0 */ short PacketType;
	/* this+2 */ short curCount;
	/* this+4 */ short maxCount;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_STOREITEM_COUNTINFO> in(p);
		TPacket<PROTO_ZC_NOTIFY_STOREITEM_COUNTINFO> out;

		out->PacketType = PacketType;
		out->curCount = in->curCount;
		out->maxCount = in->maxCount;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_STOREITEM_COUNTINFO> in(p);
		TPacket<PACKET_ZC_NOTIFY_STOREITEM_COUNTINFO> out;

		out->PacketType = PacketType;
		out->curCount = in->curCount;
		out->maxCount = in->maxCount;

		return out;
	}
};
