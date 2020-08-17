struct PROTO_ZC_STARSKILL
{
	short PacketType;
	char mapName[24];
	int monsterID;
	unsigned char star;
	unsigned char result;
};


struct PACKET_ZC_STARSKILL
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char mapName[24];
	/* this+26 */ int monsterID;
	/* this+30 */ unsigned char star;
	/* this+31 */ unsigned char result;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_STARSKILL> in(p);
		TPacket<PROTO_ZC_STARSKILL> out;

		out->PacketType = PacketType;
		memcpy(out->mapName, in->mapName, 24);
		out->monsterID = in->monsterID;
		out->star = in->star;
		out->result = in->result;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_STARSKILL> in(p);
		TPacket<PACKET_ZC_STARSKILL> out;

		out->PacketType = PacketType;
		memcpy(out->mapName, in->mapName, 24);
		out->monsterID = in->monsterID;
		out->star = in->star;
		out->result = in->result;

		return out;
	}
};
