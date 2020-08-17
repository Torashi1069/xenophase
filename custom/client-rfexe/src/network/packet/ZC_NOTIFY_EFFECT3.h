struct PROTO_ZC_NOTIFY_EFFECT3
{
	short PacketType;
	unsigned long AID;
	int effectID; // enum EFFECTID (EF_*)
	int numdata;
};


struct PACKET_ZC_NOTIFY_EFFECT3
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ int effectID;
	/* this+10 */ int numdata;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_EFFECT3> in(p);
		TPacket<PROTO_ZC_NOTIFY_EFFECT3> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->effectID = in->effectID;
		out->numdata = in->numdata;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_EFFECT3> in(p);
		TPacket<PACKET_ZC_NOTIFY_EFFECT3> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->effectID = in->effectID;
		out->numdata = in->numdata;

		return out;
	}
};
