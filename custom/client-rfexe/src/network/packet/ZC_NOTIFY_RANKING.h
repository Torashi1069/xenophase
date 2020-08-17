struct PROTO_ZC_NOTIFY_RANKING
{
	short PacketType;
	unsigned long AID;
	int ranking;
	int total;
};


struct PACKET_ZC_NOTIFY_RANKING
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ int ranking;
	/* this+10 */ int total;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_RANKING> in(p);
		TPacket<PROTO_ZC_NOTIFY_RANKING> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->ranking = in->ranking;
		out->total = in->total;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_RANKING> in(p);
		TPacket<PACKET_ZC_NOTIFY_RANKING> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->ranking = in->ranking;
		out->total = in->total;

		return out;
	}
};
