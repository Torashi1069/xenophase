struct PROTO_ZC_FEED_PET
{
	short PacketType;
	char cRet;
	unsigned short ITID;
};


struct PACKET_ZC_FEED_PET
{
	/* this+0 */ short PacketType;
	/* this+2 */ char cRet;
	/* this+3 */ unsigned short ITID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_FEED_PET> in(p);
		TPacket<PROTO_ZC_FEED_PET> out;

		out->PacketType = PacketType;
		out->cRet = in->cRet;
		out->ITID = in->ITID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_FEED_PET> in(p);
		TPacket<PACKET_ZC_FEED_PET> out;

		out->PacketType = PacketType;
		out->cRet = in->cRet;
		out->ITID = in->ITID;

		return out;
	}
};
