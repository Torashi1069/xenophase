struct PROTO_CZ_PARTY_JOIN_REQ
{
	short PacketType;
	char characterName[24];
};


struct PACKET_CZ_PARTY_JOIN_REQ
{
	/* this+0 */ short PacketType;
	/* this+2 */ char characterName[24];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_PARTY_JOIN_REQ> in(p);
		TPacket<PROTO_CZ_PARTY_JOIN_REQ> out;

		out->PacketType = PacketType;
		memcpy(out->characterName, in->characterName, 24);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_PARTY_JOIN_REQ> in(p);
		TPacket<PACKET_CZ_PARTY_JOIN_REQ> out;

		out->PacketType = PacketType;
		memcpy(out->characterName, in->characterName, 24);

		return out;
	}
};
