struct PROTO_CZ_REQ_EXPEL_GROUP_MEMBER
{
	short PacketType;
	unsigned long AID;
	char characterName[24];
};


struct PACKET_CZ_REQ_EXPEL_GROUP_MEMBER
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ char characterName[24];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_EXPEL_GROUP_MEMBER> in(p);
		TPacket<PROTO_CZ_REQ_EXPEL_GROUP_MEMBER> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		memcpy(out->characterName, in->characterName, 24);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_EXPEL_GROUP_MEMBER> in(p);
		TPacket<PACKET_CZ_REQ_EXPEL_GROUP_MEMBER> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		memcpy(out->characterName, in->characterName, 24);

		return out;
	}
};
