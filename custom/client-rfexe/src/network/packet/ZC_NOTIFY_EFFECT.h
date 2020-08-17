struct PROTO_ZC_NOTIFY_EFFECT
{
	short PacketType;
	unsigned long AID;
	int effectID; // enum enumEFFECT (*_EFFECT)
};


struct PACKET_ZC_NOTIFY_EFFECT
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ int effectID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_EFFECT> in(p);
		TPacket<PROTO_ZC_NOTIFY_EFFECT> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->effectID = in->effectID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_EFFECT> in(p);
		TPacket<PACKET_ZC_NOTIFY_EFFECT> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->effectID = in->effectID;

		return out;
	}
};
