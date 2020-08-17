struct PROTO_ZC_DEVOTIONLIST
{
	short PacketType;
	unsigned long myAID;
	unsigned long AID[5];
	short range;
};


struct PACKET_ZC_DEVOTIONLIST
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long myAID;
	/* this+ 6 */ unsigned long AID[5];
	/* this+26 */ short range;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_DEVOTIONLIST> in(p);
		TPacket<PROTO_ZC_DEVOTIONLIST> out;

		out->PacketType = PacketType;
		out->myAID = in->myAID;
		out->AID[0] = in->AID[0];
		out->AID[1] = in->AID[1];
		out->AID[2] = in->AID[2];
		out->AID[3] = in->AID[3];
		out->AID[4] = in->AID[4];
		out->range = in->range;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_DEVOTIONLIST> in(p);
		TPacket<PACKET_ZC_DEVOTIONLIST> out;

		out->PacketType = PacketType;
		out->myAID = in->myAID;
		out->AID[0] = in->AID[0];
		out->AID[1] = in->AID[1];
		out->AID[2] = in->AID[2];
		out->AID[3] = in->AID[3];
		out->AID[4] = in->AID[4];
		out->range = in->range;

		return out;
	}
};
