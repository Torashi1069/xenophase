struct PROTO_ZC_SOUND
{
	short PacketType;
	char fileName[24];
	unsigned char act;
	unsigned long term;
	unsigned long NAID;
};


struct PACKET_ZC_SOUND
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char fileName[24];
	/* this+26 */ unsigned char act;
	/* this+27 */ unsigned long term;
	/* this+31 */ unsigned long NAID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_SOUND> in(p);
		TPacket<PROTO_ZC_SOUND> out;

		out->PacketType = PacketType;
		memcpy(out->fileName, in->fileName, 24);
		out->act = in->act;
		out->term = in->term;
		out->NAID = in->NAID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_SOUND> in(p);
		TPacket<PACKET_ZC_SOUND> out;

		out->PacketType = PacketType;
		memcpy(out->fileName, in->fileName, 24);
		out->act = in->act;
		out->term = in->term;
		out->NAID = in->NAID;

		return out;
	}
};
