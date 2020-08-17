struct PROTO_CZ_ACTIVE_QUEST
{
	short PacketType;
	unsigned long questID;
	bool active;
};


struct PACKET_CZ_ACTIVE_QUEST
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long questID;
	/* this+6 */ bool active;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_ACTIVE_QUEST> in(p);
		TPacket<PROTO_CZ_ACTIVE_QUEST> out;

		out->PacketType = PacketType;
		out->questID = in->questID;
		out->active = in->active;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_ACTIVE_QUEST> in(p);
		TPacket<PACKET_CZ_ACTIVE_QUEST> out;

		out->PacketType = PacketType;
		out->questID = in->questID;
		out->active = in->active;

		return out;
	}
};
