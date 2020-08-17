struct PROTO_ZC_COMBODELAY
{
	short PacketType;
	unsigned long AID;
	unsigned long delayTime;
};


struct PACKET_ZC_COMBODELAY
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ unsigned long delayTime;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_COMBODELAY> in(p);
		TPacket<PROTO_ZC_COMBODELAY> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->delayTime = in->delayTime;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_COMBODELAY> in(p);
		TPacket<PACKET_ZC_COMBODELAY> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->delayTime = in->delayTime;

		return out;
	}
};
