struct PROTO_ZC_COUPLENAME
{
	short PacketType;
	char CoupleName[24];
};


struct PACKET_ZC_COUPLENAME
{
	/* this+0 */ short PacketType;
	/* this+2 */ char CoupleName[24];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_COUPLENAME> in(p);
		TPacket<PROTO_ZC_COUPLENAME> out;

		out->PacketType = PacketType;
		memcpy(out->CoupleName, in->CoupleName, 24);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_COUPLENAME> in(p);
		TPacket<PACKET_ZC_COUPLENAME> out;

		out->PacketType = PacketType;
		memcpy(out->CoupleName, in->CoupleName, 24);

		return out;
	}
};
