struct PROTO_ZC_REQ_BABY
{
	short PacketType;
	unsigned long AID;
	unsigned long GID;
	char name[24];
};


struct PACKET_ZC_REQ_BABY
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char name[24];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_REQ_BABY> in(p);
		TPacket<PROTO_ZC_REQ_BABY> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->GID = in->GID;
		memcpy(out->name, in->name, 24);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_REQ_BABY> in(p);
		TPacket<PACKET_ZC_REQ_BABY> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->GID = in->GID;
		memcpy(out->name, in->name, 24);

		return out;
	}
};
