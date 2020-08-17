struct PROTO_ZC_PARTY_JOIN_REQ
{
	short PacketType;
	unsigned long GRID;
	char groupName[24];
};


struct PACKET_ZC_REQ_JOIN_GROUP
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GRID;
	/* this+6 */ char groupName[24];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_REQ_JOIN_GROUP> in(p);
		TPacket<PROTO_ZC_PARTY_JOIN_REQ> out;

		out->PacketType = PacketType;
		out->GRID = in->GRID;
		memcpy(out->groupName, in->groupName, 24);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_PARTY_JOIN_REQ> in(p);
		TPacket<PACKET_ZC_REQ_JOIN_GROUP> out;

		out->PacketType = PacketType;
		out->GRID = in->GRID;
		memcpy(out->groupName, in->groupName, 24);

		return out;
	}
};


struct PACKET_ZC_PARTY_JOIN_REQ
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GRID;
	/* this+6 */ char groupName[24];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_PARTY_JOIN_REQ> in(p);
		TPacket<PROTO_ZC_PARTY_JOIN_REQ> out;

		out->PacketType = PacketType;
		out->GRID = in->GRID;
		memcpy(out->groupName, in->groupName, 24);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_PARTY_JOIN_REQ> in(p);
		TPacket<PACKET_ZC_PARTY_JOIN_REQ> out;

		out->PacketType = PacketType;
		out->GRID = in->GRID;
		memcpy(out->groupName, in->groupName, 24);

		return out;
	}
};
