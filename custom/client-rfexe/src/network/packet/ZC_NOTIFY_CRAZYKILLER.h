struct PROTO_ZC_NOTIFY_CRAZYKILLER
{
	short PacketType;
	unsigned long AID;
	int isCrazyKiller;
};


struct PACKET_ZC_NOTIFY_CRAZYKILLER
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ int isCrazyKiller;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_CRAZYKILLER> in(p);
		TPacket<PROTO_ZC_NOTIFY_CRAZYKILLER> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->isCrazyKiller = in->isCrazyKiller;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_CRAZYKILLER> in(p);
		TPacket<PACKET_ZC_NOTIFY_CRAZYKILLER> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->isCrazyKiller = in->isCrazyKiller;

		return out;
	}
};
