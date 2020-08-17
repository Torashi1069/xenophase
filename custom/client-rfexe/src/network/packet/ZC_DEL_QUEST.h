struct PROTO_ZC_DEL_QUEST
{
	short PacketType;
	unsigned long questID;
};


struct PACKET_ZC_DEL_QUEST
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long questID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_DEL_QUEST> in(p);
		TPacket<PROTO_ZC_DEL_QUEST> out;

		out->PacketType = PacketType;
		out->questID = in->questID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_DEL_QUEST> in(p);
		TPacket<PACKET_ZC_DEL_QUEST> out;

		out->PacketType = PacketType;
		out->questID = in->questID;

		return out;
	}
};
