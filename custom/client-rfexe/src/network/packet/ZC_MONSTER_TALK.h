struct PROTO_ZC_MONSTER_TALK
{
	short PacketType;
	unsigned long GID;
	unsigned char stateId;
	unsigned char skillId;
	unsigned char arg1;
};


struct PACKET_ZC_MONSTER_TALK
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ unsigned char stateId;
	/* this+7 */ unsigned char skillId;
	/* this+8 */ unsigned char arg1;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_MONSTER_TALK> in(p);
		TPacket<PROTO_ZC_MONSTER_TALK> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		out->stateId = in->stateId;
		out->skillId = in->skillId;
		out->arg1 = in->arg1;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_MONSTER_TALK> in(p);
		TPacket<PACKET_ZC_MONSTER_TALK> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		out->stateId = in->stateId;
		out->skillId = in->skillId;
		out->arg1 = in->arg1;

		return out;
	}
};
