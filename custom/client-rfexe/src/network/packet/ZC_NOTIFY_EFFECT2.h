struct PROTO_ZC_NOTIFY_EFFECT2
{
	short PacketType;
	unsigned long AID;
	int effectID; // enum EFFECTID (EF_*)
};


struct PACKET_ZC_NOTIFY_EFFECT2
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ int effectID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_EFFECT2> in(p);
		TPacket<PROTO_ZC_NOTIFY_EFFECT2> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->effectID = in->effectID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_EFFECT2> in(p);
		TPacket<PACKET_ZC_NOTIFY_EFFECT2> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->effectID = in->effectID;

		return out;
	}
};
