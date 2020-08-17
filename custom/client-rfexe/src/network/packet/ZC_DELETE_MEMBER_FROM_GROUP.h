struct PROTO_ZC_DELETE_MEMBER_FROM_GROUP
{
	short PacketType;
	unsigned long AID;
	char characterName[24];
	unsigned char result;
};


struct PACKET_ZC_DELETE_MEMBER_FROM_GROUP
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ char characterName[24];
	/* this+30 */ unsigned char result;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_DELETE_MEMBER_FROM_GROUP> in(p);
		TPacket<PROTO_ZC_DELETE_MEMBER_FROM_GROUP> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		memcpy(out->characterName, in->characterName, 24);
		out->result = in->result;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_DELETE_MEMBER_FROM_GROUP> in(p);
		TPacket<PACKET_ZC_DELETE_MEMBER_FROM_GROUP> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		memcpy(out->characterName, in->characterName, 24);
		out->result = in->result;

		return out;
	}
};
